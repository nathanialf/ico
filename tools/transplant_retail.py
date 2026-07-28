#!/usr/bin/env python3
"""
tools/transplant_retail.py — Phase 3 retail-v2 transplant driver.

Moves matched C function bodies from the OLD `retail` branch (per-function
shards under src/cod/<HEX>.c and ~91 named whole-TU files) into the NEW
retail-v2 TU files (which currently hold only INCLUDE_ASM scaffolds),
renaming symbols via an address-keyed old->new map built from
config/symbol_addrs.us.txt on both branches.

Subcommands:
  extract              Build the old-tree function/decl index (cache to
                        build/transplant_cache/).
  plan <tu>             Show what would be spliced into a given new TU.
  splice <tu> [--apply]  Splice matched old bodies into a new TU file.
                         Without --apply, dry-run (prints diff summary only).
  verify <tu>            Run quick_diff.sh over every spliced function.
  status                 Ledger summary.

See decomp/transplant_ledger.md for accounting.
"""
import argparse
import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
## NOTE: deliberately NOT under build/ — `tools/build.sh setup` wipes that
## directory on every run, and this cache (the extracted old-tree function
## index + the old-tree working copy) is expensive to rebuild.
CACHE_DIR = ROOT / ".transplant_cache"
CACHE_DIR.mkdir(parents=True, exist_ok=True)
OLD_TREE = CACHE_DIR / "old_tree"


def ensure_old_tree(ref="retail"):
    """Materialize the old `retail` branch tree (read-only reference copy)
    under build/ via `git archive` — never merge/checkout retail itself."""
    marker = OLD_TREE / ".ref"
    if OLD_TREE.exists() and marker.exists() and marker.read_text().strip() == ref:
        return
    import shutil
    if OLD_TREE.exists():
        shutil.rmtree(OLD_TREE)
    OLD_TREE.mkdir(parents=True)
    subprocess.run(
        f"git archive {ref} | tar -x -C {OLD_TREE}", shell=True, check=True, cwd=ROOT
    )
    marker.write_text(ref + "\n")

VMA_BASE = 0x100000

QUARANTINE_ADDRS = {0x118A68, 0x1986A8}  # the 2 genuine VU0-inline-asm funcs
QUARANTINE_FILE_PREFIXES = ("src/DisplayList.c",)  # extra_cflags family


def read_latin1(p):
    return Path(p).read_text(encoding="latin-1")


def write_latin1(p, s):
    Path(p).write_text(s, encoding="latin-1")


# ------------------------------------------------------------------
# symbol_addrs parsing
# ------------------------------------------------------------------
SYM_RE = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)\s*=\s*0x([0-9A-Fa-f]+)\s*;\s*(?://\s*(.*))?$")


def parse_symbol_addrs(text):
    """Return dict addr(int) -> (name, typehint_or_None), and name->addr."""
    addr2name = {}
    name2addr = {}
    addr2type = {}
    for ln in text.splitlines():
        ln = ln.strip()
        m = SYM_RE.match(ln)
        if not m:
            continue
        name, addr_hex, comment = m.group(1), m.group(2), m.group(3) or ""
        addr = int(addr_hex, 16)
        addr2name[addr] = name
        name2addr[name] = addr
        tm = re.search(r"type:(\S+)", comment)
        if tm:
            addr2type[addr] = tm.group(1)
    return addr2name, name2addr, addr2type


def load_symbol_maps():
    cache = CACHE_DIR / "symmaps.json"
    new_text = read_latin1(ROOT / "config/symbol_addrs.us.txt")
    old_text = read_latin1(OLD_TREE / "config/symbol_addrs.us.txt")
    new_a2n, new_n2a, new_a2t = parse_symbol_addrs(new_text)
    old_a2n, old_n2a, old_a2t = parse_symbol_addrs(old_text)

    rename = {}  # old_name -> new_name (only where addr matches and names differ)
    for addr, old_name in old_a2n.items():
        new_name = new_a2n.get(addr)
        if new_name and new_name != old_name:
            rename[old_name] = new_name

    # symbol_addrs.us.txt only lists symbols that need explicit annotation;
    # splat auto-derives func_<VMA>/D_<VMA> labels for everything else. Old
    # source overwhelmingly uses those *default* labels verbatim (no
    # explicit old_a2n entry at all), so also rename default-shaped names ->
    # whatever the NEW branch calls that same address, for every address
    # the new table knows about. Explicit old_a2n-derived entries above win
    # over this (already in the dict; skip if a key collision would occur
    # from a *different* default form, which cannot happen here since each
    # address has exactly one default form).
    for addr, new_name in new_a2n.items():
        for default_name in (f"func_{addr:08X}", f"D_{addr:08X}"):
            if new_name != default_name and default_name not in rename:
                rename[default_name] = new_name
    return {
        "new_a2n": new_a2n, "new_n2a": new_n2a, "new_a2t": new_a2t,
        "old_a2n": old_a2n, "old_n2a": old_n2a, "old_a2t": old_a2t,
        "rename": rename,
    }


# ------------------------------------------------------------------
# new yaml segment ranges (216 game TUs + everything else)
# ------------------------------------------------------------------
SEG_RE = re.compile(r"^\s*-\s*\[0x([0-9A-Fa-f]+),\s*([a-zA-Z_]+)(?:,\s*([^\]#]+))?\]")


def parse_yaml_segs(text):
    segs = []
    for ln in text.splitlines():
        m = SEG_RE.match(ln)
        if m:
            addr = int(m.group(1), 16)
            typ = m.group(2)
            name = (m.group(3) or "").strip()
            segs.append((addr, typ, name))
    segs.sort(key=lambda s: s[0])
    return segs


def new_tu_ranges():
    """Return list of (start_vma, end_vma, tu_name) for the 216 c-type game TUs."""
    text = read_latin1(ROOT / "config/ico.us.yaml")
    segs = parse_yaml_segs(text)
    out = []
    for i, (addr, typ, name) in enumerate(segs):
        if typ != "c":
            continue
        start = VMA_BASE + addr
        end = VMA_BASE + (segs[i + 1][0] if i + 1 < len(segs) else 0x7FFFFFFF)
        out.append((start, end, name))
    return out


# ------------------------------------------------------------------
# Old-tree function/decl extraction (character-level brace scanner)
# ------------------------------------------------------------------

def strip_comments_preserve_len(s):
    """Replace comment contents with spaces (keep newlines) so brace/paren
    scanning ignores them but offsets/line numbers stay stable."""
    out = []
    i = 0
    n = len(s)
    while i < n:
        c = s[i]
        if c == '/' and i + 1 < n and s[i + 1] == '/':
            j = s.find('\n', i)
            if j == -1:
                j = n
            out.append(' ' * (j - i))
            i = j
        elif c == '/' and i + 1 < n and s[i + 1] == '*':
            j = s.find('*/', i + 2)
            if j == -1:
                j = n - 2
            chunk = s[i:j + 2]
            out.append(''.join(ch if ch == '\n' else ' ' for ch in chunk))
            i = j + 2
        elif c == '"' or c == "'":
            quote = c
            j = i + 1
            while j < n:
                if s[j] == '\\':
                    j += 2
                    continue
                if s[j] == quote:
                    j += 1
                    break
                j += 1
            chunk = s[i:j]
            # Blank the INTERIOR only — keep the delimiting quote chars so
            # patterns like `__asm__("REALNAME")` still look quote-shaped
            # to downstream regexes (e.g. the decl_index asm-label scan).
            if len(chunk) >= 2:
                middle = ''.join(ch if ch == '\n' else 'x' for ch in chunk[1:-1])
                out.append(chunk[0] + middle + chunk[-1])
            else:
                out.append(chunk)
            i = j
        else:
            out.append(c)
            i += 1
    return ''.join(out)


TOPFUNC_RE = re.compile(
    r"^[A-Za-z_][A-Za-z0-9_ \t\*]*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\([^;{}]*\)\s*$",
    re.MULTILINE,
)


def extract_functions_from_file(path_rel, raw_text):
    """Scan one old-tree C file. Returns list of dicts:
       {name, addr(None if unresolved by name pattern), start, end, text,
        precontext (lines directly above, only extern/typedef, since last
        consumed top-level statement)}
       and set of INCLUDE_ASM'd (still-unmatched) function names.
    """
    clean = strip_comments_preserve_len(raw_text)
    n = len(clean)
    funcs = []
    unmatched = set()

    # Track #if 0 ... #endif to skip dead code. Simple single-level+ stack.
    # We do this via line-based active-mask applied at brace-depth 0 only
    # (matches this project's file style: no #if inside function bodies).
    lines = raw_text.split('\n')
    clean_lines = clean.split('\n')
    active_stack = []
    line_active = []
    for ln in lines:
        s = ln.strip()
        if s.startswith('#if 0'):
            active_stack.append(False)
        elif s.startswith('#if') or s.startswith('#ifdef') or s.startswith('#ifndef'):
            active_stack.append(True)
        elif s.startswith('#else'):
            if active_stack:
                active_stack[-1] = not active_stack[-1]
        elif s.startswith('#endif'):
            if active_stack:
                active_stack.pop()
        line_active.append(all(active_stack) if active_stack else True)

    # Build a char-position -> active bool by expanding line_active, and a
    # char-position -> "this line is a preprocessor directive" flag (these
    # terminate a top-level statement without a trailing ';').
    pos_active = bytearray()
    pos_is_pp_line = bytearray()
    for ln, act in zip(lines, line_active):
        is_pp = 1 if ln.lstrip().startswith('#') else 0
        pos_active += bytes([1 if act else 0]) * (len(ln) + 1)
        pos_is_pp_line += bytes([is_pp]) * (len(ln) + 1)
    while len(pos_active) < n + 1:
        pos_active.append(1)
        pos_is_pp_line.append(0)

    def is_active(pos):
        return pos < len(pos_active) and pos_active[pos]

    def is_pp_line(pos):
        return pos < len(pos_is_pp_line) and pos_is_pp_line[pos]

    # find INCLUDE_ASM(...) calls (only when active)
    for m in re.finditer(r"INCLUDE_ASM(?:_NOAT|_FS)?\s*\(\s*\"[^\"]*\"\s*,\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)", raw_text):
        if is_active(m.start()):
            unmatched.add(m.group(1))

    # Character scan for top-level function defs.
    depth = 0
    i = 0
    stmt_start = 0  # start of current top-level "statement" buffer
    while i < n:
        c = clean[i]
        if depth == 0 and c == '{':
            if is_active(i):
                sig = clean[stmt_start:i]
                sig_stripped = sig.strip()
                m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*\([^()]*(?:\([^()]*\)[^()]*)*\)\s*$", sig_stripped)
                NOT_A_FUNC_NAME = {
                    "__attribute__", "if", "for", "while", "switch", "do",
                    "sizeof", "return",
                }
                if (m and not sig_stripped.startswith('#')
                        and m.group(1) not in NOT_A_FUNC_NAME
                        and 'typedef' not in sig_stripped
                        and '=' not in sig_stripped):
                    fname = m.group(1)
                    # find matching close brace
                    j = i
                    d = 0
                    while j < n:
                        if clean[j] == '{':
                            d += 1
                        elif clean[j] == '}':
                            d -= 1
                            if d == 0:
                                break
                        j += 1
                    end = j + 1
                    func_start = stmt_start + (len(sig) - len(sig.lstrip()))
                    text = raw_text[func_start:end]
                    funcs.append({
                        "name": fname,
                        "start": func_start,
                        "end": end,
                        "text": text,
                    })
                    i = end
                    stmt_start = end
                    depth = 0
                    continue
                else:
                    # not a function def (e.g. struct/union initializer brace) -
                    # still need to track depth so we don't misparse; treat as block
                    depth += 1
                    i += 1
                    continue
            else:
                depth += 1
                i += 1
                continue
        elif c == '{':
            depth += 1
            i += 1
        elif c == '}':
            depth -= 1
            i += 1
            if depth <= 0:
                depth = 0
                stmt_start = i
        elif depth == 0 and c == ';':
            i += 1
            stmt_start = i
        elif depth == 0 and c == '\n' and is_pp_line(i):
            # end of a preprocessor directive line: it's its own statement,
            # never part of a following function signature.
            i += 1
            stmt_start = i
        else:
            i += 1

    return funcs, unmatched


def rom_to_vma(off_hex):
    return VMA_BASE + int(off_hex, 16)


FUNC_NAME_ADDR_RE = re.compile(r"^func_([0-9A-Fa-f]{8})$")
DATA_NAME_ADDR_RE = re.compile(r"^D_([0-9A-Fa-f]{8})$")


def name_to_addr_guess(name):
    m = FUNC_NAME_ADDR_RE.match(name) or DATA_NAME_ADDR_RE.match(name)
    if m:
        return int(m.group(1), 16)
    return None


def build_decl_index(all_file_texts):
    """Global index: top-level `extern ...;` / `typedef ...;` declaration
    text keyed by the identifier they declare (best-effort single regex
    pass per file, at depth 0, active-only)."""
    index = {}
    # Trailing `__asm__("REALNAME")` (gcc asm-label extension) is how the old
    # dev aliased several distinct local C identifiers onto the SAME address
    # (see decomp/COOKBOOK.md dual-root-addr / CSE-defeat lever) — allow it
    # between the (optional) array brackets and the terminating `;`.
    decl_re = re.compile(
        r"^(extern\s+[^;{}]*?|typedef\s+[^;{}]*?)\b([A-Za-z_][A-Za-z0-9_]*)\s*"
        r"(\[[^\]]*\])?\s*(__asm__\s*\(\s*\"[^\"]*\"\s*\))?\s*;\s*$",
        re.MULTILINE,
    )
    # Comma-separated simple extern declarator lists (`extern int A, B;`) —
    # the main pass above only captures the LAST declarator (its non-greedy
    # group1 swallows the earlier ones). Synthesize a single-name extern
    # for each additional name.
    multi_re = re.compile(
        r"^extern\s+([A-Za-z_][A-Za-z0-9_ ]*?)\s+"
        r"([A-Za-z_]\w*(?:\s*,\s*[A-Za-z_]\w*)+)\s*;\s*$",
        re.MULTILINE,
    )
    for path, raw in all_file_texts:
        clean = strip_comments_preserve_len(raw)
        for m in decl_re.finditer(clean):
            ident = m.group(2)
            full_text = raw[m.start():m.end()]
            if ident not in index:
                index[ident] = full_text.strip()
        for m in multi_re.finditer(clean):
            ctype = m.group(1).strip()
            names = [n.strip() for n in m.group(2).split(",")]
            for nm in names:
                if nm not in index:
                    index[nm] = f"extern {ctype} {nm};"
    return index


# ------------------------------------------------------------------
# extract subcommand
# ------------------------------------------------------------------

def cmd_extract(args):
    ensure_old_tree()
    sm = load_symbol_maps()
    old_named_files = []
    text = read_latin1(OLD_TREE / "config/ico.us.yaml")
    for addr, typ, name in parse_yaml_segs(text):
        if typ == "c" and not name.startswith("src/cod/"):
            old_named_files.append(name + ".c")

    cod_files = sorted(
        str(p.relative_to(OLD_TREE)) for p in (OLD_TREE / "src/cod").glob("*.c")
    )

    all_files = old_named_files + cod_files
    all_texts = []
    for relp in all_files:
        p = OLD_TREE / relp
        if not p.exists():
            continue
        all_texts.append((relp, read_latin1(p)))

    functions = {}  # addr(int) -> record
    unmatched_addrs = set()
    helpers = {}  # file -> [ {name, text} ]  (TU-local, non-addressable helpers)

    for relp, raw in all_texts:
        funcs, unmatched_names = extract_functions_from_file(relp, raw)
        for uname in unmatched_names:
            a = name_to_addr_guess(uname) or sm["old_n2a"].get(uname)
            if a:
                unmatched_addrs.add(a)
        for f in funcs:
            addr = name_to_addr_guess(f["name"]) or sm["old_n2a"].get(f["name"])
            if addr is None:
                # Not a directly-addressable game function — a TU-local
                # (usually `static inline`) helper the real dev wrote, fully
                # inlined into its caller(s) in the ROM. Keep its source
                # attached to the file so splice can carry it along.
                helpers.setdefault(relp, []).append({"name": f["name"], "text": f["text"]})
                continue
            quarantine = None
            if addr in QUARANTINE_ADDRS:
                quarantine = "vu0-inline-asm"
            if any(relp.startswith(pfx) for pfx in QUARANTINE_FILE_PREFIXES):
                quarantine = "DisplayList-extra_cflags"
            if "dispatch.h" in raw[:2000] and "func_0013A5B8" in raw:
                # heuristic; refined check happens again at splice time via body scan
                pass
            rec = {
                "addr": addr,
                "old_name": f["name"],
                "file": relp,
                "text": f["text"],
                "quarantine": quarantine,
            }
            # last one wins if dup (shouldn't happen)
            functions[addr] = rec

    decl_index = build_decl_index(all_texts)

    if os.environ.get("TRANSPLANT_DEBUG"):
        for relp, hs in helpers.items():
            for h in hs:
                print("HELPER:", relp, h["name"], file=sys.stderr)

    out = {
        "functions": {str(k): v for k, v in functions.items()},
        "unmatched_addrs": sorted(unmatched_addrs),
        "decl_index": decl_index,
        "helpers": helpers,
    }
    (CACHE_DIR / "old_functions.json").write_text(json.dumps(out, ensure_ascii=False, indent=1))
    (CACHE_DIR / "symmaps.json").write_text(json.dumps({
        "new_a2n": {str(k): v for k, v in sm["new_a2n"].items()},
        "new_n2a": sm["new_n2a"],
        "new_a2t": {str(k): v for k, v in sm["new_a2t"].items()},
        "old_a2n": {str(k): v for k, v in sm["old_a2n"].items()},
        "old_a2t": {str(k): v for k, v in sm["old_a2t"].items()},
        "old_n2a": sm["old_n2a"],
        "rename": sm["rename"],
    }, ensure_ascii=False, indent=1))
    print(f"extracted {len(functions)} matched old functions "
          f"({sum(1 for r in functions.values() if r['quarantine'])} pre-quarantined), "
          f"{len(unmatched_addrs)} still-INCLUDE_ASM, "
          f"{sum(len(v) for v in helpers.values())} TU-local helpers, "
          f"{len(decl_index)} decl-index entries")


# ------------------------------------------------------------------
# splice engine
# ------------------------------------------------------------------

TYPE_HINT_C = {
    "u8": ("unsigned char", 1), "s8": ("signed char", 1),
    "u16": ("unsigned short", 2), "s16": ("short", 2),
    "u32": ("unsigned int", 4), "s32": ("int", 4),
    "f32": ("float", 4), "f64": ("double", 8),
}

INCLUDE_ASM_RE = re.compile(
    r'INCLUDE_ASM(?:_NOAT|_FS)?\(\s*"[^"]*"\s*,\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)\s*;'
)
IDENT_RE = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")


class Cache:
    def __init__(self):
        self.old = json.loads((CACHE_DIR / "old_functions.json").read_text(encoding="utf-8"))
        self.sm = json.loads((CACHE_DIR / "symmaps.json").read_text(encoding="utf-8"))
        self.functions = self.old["functions"]  # str(addr) -> rec
        self.helpers = self.old.get("helpers", {})
        self.decl_index = self.old["decl_index"]
        self.new_n2a = self.sm["new_n2a"]
        self.new_a2n = {int(k): v for k, v in self.sm["new_a2n"].items()}
        self.new_a2t = {int(k): v for k, v in self.sm["new_a2t"].items()}
        self.old_a2n = {int(k): v for k, v in self.sm["old_a2n"].items()}
        self.old_a2t = {int(k): v for k, v in self.sm["old_a2t"].items()}
        rename = self.sm["rename"]
        self.rename = rename
        keys = sorted(rename.keys(), key=len, reverse=True)
        if keys:
            self.rename_re = re.compile(r"\b(" + "|".join(re.escape(k) for k in keys) + r")\b")
        else:
            self.rename_re = None

        # Auxiliary headers whose identifiers a transplanted body might use
        # but which aren't pulled in by common.h alone: the GObj-family
        # entity types (include/ico/types.h — old TUs `#include`d it
        # locally) and the hand-written MMI/VU0 leaf-instruction macro
        # libraries (r5900.h, vu0.h) that many `src/cod/` shards rely on
        # (e.g. QCOPY16, VU0_LSV). Map identifier -> header path once.
        self.header_for_ident = {}
        types_h = read_latin1(ROOT / "include/ico/types.h")
        for name in re.findall(r"^typedef\s+struct\s+(\w+)\s+\1\s*;", types_h, re.MULTILINE):
            self.header_for_ident[name] = "ico/types.h"
        for hdr in ("r5900.h", "vu0.h", "math_private.h"):
            txt = read_latin1(ROOT / "include" / hdr)
            for name in re.findall(r"^#define\s+(\w+)", txt, re.MULTILINE):
                self.header_for_ident.setdefault(name, hdr)
        ident_keys = sorted(self.header_for_ident, key=len, reverse=True)
        if ident_keys:
            self.header_ident_re = re.compile(r"\b(" + "|".join(re.escape(k) for k in ident_keys) + r")\b")
        else:
            self.header_ident_re = None

    def rename_text(self, text):
        if not self.rename_re:
            return text
        return self.rename_re.sub(lambda m: self.rename[m.group(1)], text)

    def needed_headers(self, text):
        """Which auxiliary headers (see header_for_ident) does `text`
        reference identifiers from? Returns an ordered list of header
        paths (types.h before the asm-macro headers, matching old TU decl
        order)."""
        if not self.header_ident_re:
            return []
        hdrs = []
        for name in set(self.header_ident_re.findall(text)):
            h = self.header_for_ident[name]
            if h not in hdrs:
                hdrs.append(h)
        # Stable, deterministic order: types.h, then r5900.h, then vu0.h,
        # then math_private.h, then anything else alphabetically.
        order = {"ico/types.h": 0, "r5900.h": 1, "vu0.h": 2, "math_private.h": 3}
        hdrs.sort(key=lambda h: order.get(h, 99))
        return hdrs


def count_top_level_commas(s):
    depth = 0
    count = 0
    in_str = None
    i = 0
    while i < len(s):
        c = s[i]
        if in_str:
            if c == "\\":
                i += 2
                continue
            if c == in_str:
                in_str = None
        elif c in "\"'":
            in_str = c
        elif c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
        elif c == "," and depth == 0:
            count += 1
        i += 1
    return count


def _paren_group_after(text, end_of_name):
    """`end_of_name` is the index right after `NAME(` (the open paren
    already consumed). Returns the (start, end) span of the argument list
    text up to the matching close paren, or None."""
    depth = 1
    i = end_of_name
    while i < len(text) and depth > 0:
        if text[i] == "(":
            depth += 1
        elif text[i] == ")":
            depth -= 1
        i += 1
    if depth != 0:
        return None
    return end_of_name, i - 1


def param_count_from_sig(sig, name):
    m = re.search(re.escape(name) + r"\s*\(", sig)
    if not m:
        return None
    span = _paren_group_after(sig, m.end())
    if span is None:
        return None
    params = sig[span[0]:span[1]].strip()
    if params in ("", "void"):
        return 0
    return count_top_level_commas(params) + 1


def call_arg_count(body, name):
    m = re.search(r"\b" + re.escape(name) + r"\s*\(", body)
    if not m:
        return None
    span = _paren_group_after(body, m.end())
    if span is None:
        return None
    args = body[span[0]:span[1]].strip()
    if args == "":
        return 0
    return count_top_level_commas(args) + 1


def unprototyped_func_extern(sig, name):
    """`sig` is a function signature/declarator text containing `name(...)`.
    Old-style (K&R) externs like `extern TYPE NAME();` declare an
    unspecified argument list — no arg-count/type checking against the call
    sites — while still fixing the return TYPE so a later real definition
    with a different return type still conflicts loudly (good) but a
    caller passing a different arg count/types (extremely common for VU0
    leaf functions whose C params are placeholders for raw asm registers)
    does not hard-error. Preferred over reusing the full prototype."""
    m = re.search(re.escape(name) + r"\s*\(", sig)
    if not m:
        return None
    prefix = sig[:m.start()].strip()
    if not prefix:
        prefix = "void"
    return f"extern {prefix} {name}();"


def synth_extern(cache, new_name, declared, body=""):
    """Best-effort extern declaration for `new_name` (already the NEW-branch
    identifier). Preference order: (1) the callee's own matched-old
    definition's return type (reduced to an unprototyped decl — see
    unprototyped_func_extern), (2) a scraped old extern declaration for the
    corresponding old name (by address), (2b) a scraped old extern found by
    the identifier's OWN spelling — covers `__asm__("REALNAME")` asm-label
    aliases (e.g. `extern int D_X_a[] __asm__("D_X");`) that address-key
    off a DIFFERENT symbol and so have no address of their own, (3) a
    type-hint guess from symbol_addrs, (4) a bare func/data guess from
    naming convention (array-shaped if `body` subscripts it)."""
    addr = cache.new_n2a.get(new_name)
    if addr is None:
        addr = name_to_addr_guess(new_name)
    if addr is None:
        if new_name in cache.decl_index:
            decl = cache.rename_text(cache.decl_index[new_name])
            decl = decl if decl.rstrip().endswith(";") else decl + ";"
            if "(" in decl:
                ext = unprototyped_func_extern(decl, new_name)
                if ext:
                    return ext
            return decl
        return None
    old_rec = cache.functions.get(str(addr))
    if old_rec is not None:
        sig = old_rec["text"].split("{", 1)[0].strip()
        sig = cache.rename_text(sig)
        sig = re.sub(r"\s+", " ", sig)
        # Prefer the FULL prototype (needed for correct float/double ABI —
        # an unprototyped call applies old-style default argument
        # promotion, which can route a float arg through the wrong
        # register) whenever the call site's arg count matches the
        # callee's own declared param count exactly, so there's no
        # too-few/too-many-arguments risk (common for VU0 leaf functions
        # whose extra formal params are placeholder register reservations
        # the caller doesn't actually pass).
        decl_argc = param_count_from_sig(sig, new_name)
        call_argc = call_arg_count(body, new_name)
        if decl_argc is not None and call_argc is not None and decl_argc == call_argc:
            return f"extern {sig};"
        ext = unprototyped_func_extern(sig, new_name)
        if ext:
            return ext
        return f"extern {sig};"
    old_name = cache.old_a2n.get(addr)
    decl_key = old_name if (old_name and old_name in cache.decl_index) else (
        new_name if new_name in cache.decl_index else None)
    if decl_key:
        decl = cache.decl_index[decl_key]
        decl = cache.rename_text(decl)
        decl = decl if decl.rstrip().endswith(";") else decl + ";"
        if "(" in decl:
            ext = unprototyped_func_extern(decl, new_name)
            if ext:
                return ext
        return decl
    hint = cache.new_a2t.get(addr) or (cache.old_a2t.get(addr) if old_name else None)
    if hint == "func":
        return f"extern void {new_name}();"
    if hint in TYPE_HINT_C:
        ctype, _ = TYPE_HINT_C[hint]
        return f"extern {ctype} {new_name};"
    if new_name.startswith("func_"):
        return f"extern void {new_name}();"
    if re.search(r"\b" + re.escape(new_name) + r"\s*\[", body):
        return f"extern int {new_name}[];"
    return f"extern int {new_name};"


def gather_needed_externs(cache, renamed_body, self_name, declared):
    tokens = set(IDENT_RE.findall(renamed_body))
    needed = []
    for t in tokens:
        if t == self_name or t in declared:
            continue
        # A "known global" is an address-table entry (real semantic name),
        # a still-default func_XXXXXXXX/D_XXXXXXXX name (symbol_addrs.us.txt
        # does not list every default-named one), or an identifier the old
        # tree itself declared with `extern` (covers `__asm__("REALNAME")`
        # asm-label aliases, which have no address of their own).
        if (t not in cache.new_n2a and name_to_addr_guess(t) is None
                and t not in cache.decl_index):
            continue
        ext = synth_extern(cache, t, declared, renamed_body)
        if ext:
            needed.append(ext)
            declared.add(t)
    return needed


def tu_path(tu_name):
    return ROOT / (tu_name + ".c")


def parse_include_asm_entries(text):
    """Return list of (start, end, name) spans for each INCLUDE_ASM(...); in
    file order (byte offsets into `text`)."""
    out = []
    for m in INCLUDE_ASM_RE.finditer(text):
        out.append((m.start(), m.end(), m.group(1)))
    return out


def old_source_files_for_tu(cache, addrs):
    files = set()
    for a in addrs:
        rec = cache.functions.get(str(a))
        if rec:
            files.add(rec["file"])
    return files


LEDGER_PATH = ROOT / "decomp" / "transplant_ledger.md"


def ledger_append(lines):
    with open(LEDGER_PATH, "a", encoding="utf-8") as f:
        for ln in lines:
            f.write(ln + "\n")


CATN_RE = re.compile(r"^\s*\d+\t(.*)$")


def _parse_catn_block(stdout, header_prefix):
    """Extract the lines of a `cat -n`'d block whose banner starts with
    `header_prefix` (quick_diff.sh prints '=== expected: ... ===' /
    '=== built: ... ===' banners, each followed by numbered lines up to the
    next blank line)."""
    lines = stdout.splitlines()
    out = None
    for i, ln in enumerate(lines):
        if ln.startswith(header_prefix):
            out = []
            for ln2 in lines[i + 1:]:
                if ln2.strip() == "":
                    break
                m = CATN_RE.match(ln2)
                out.append(m.group(1) if m else ln2)
            break
    return out


# Matches a disassembly line ending in a bare hex/dec address immediately
# followed by objdump's `<symbol[+off]>` annotation — the shape any
# branch/jump mnemonic (j, jal, jalr, beq, bne, bgez, ...) produces.
BRANCH_TARGET_RE = re.compile(r"^(.*[^0-9a-fA-F])([0-9a-fA-F]+)(\s*<[^>]*>)\s*$")


def _normalize_for_compare(line):
    """quick_diff disassembles the built (multi-function, coalesced TU)
    object and the isolated single-function target baseline SEPARATELY —
    two objects with different absolute layouts pre-link. Two cosmetic,
    NOT-real-difference patterns fall out of that for any branch/jump
    whose target objdump annotates with `<...>`:

      1. Same-function relative branch: the bracket ("<func+0x30>") is
         IDENTICAL on both sides (same relative displacement, verified via
         real bytes) but the raw absolute hex address differs, because the
         function sits at a different absolute .text offset in each
         object (isolated-at-0 vs coalesced-TU-with-siblings-before-it).
      2. Call to an external/not-yet-spliced symbol: the raw address is
         "0" (unresolved placeholder, real value TBD at final link) on
         BOTH sides, but objdump's `<...>` fallback-label is whatever LOCAL
         symbol happens to occupy address 0 in THAT object — different
         objects, different such symbols, purely cosmetic (verified via
         `-r`: the real R_MIPS_26 relocation entry is correct either way).

    Normalize both away: always blank the raw address digits; when they
    were "0" (case 2) also blank the bracket, since its content is
    meaningless there. See decomp/NOTES.md / ninja_gate memory — quick_diff
    is a fast pre-filter, the batch-level full `ninja` SHA gate is the real
    safety net, so tolerating these here does not weaken correctness."""
    m = BRANCH_TARGET_RE.match(line)
    if not m:
        return line
    prefix, addr, bracket = m.groups()
    if addr.lstrip("0") == "":
        return prefix + "ADDR" + " <EXT>"
    return prefix + "ADDR" + bracket


def quick_diff_functionally_matches(stdout):
    left = _parse_catn_block(stdout, "=== built:")
    right = _parse_catn_block(stdout, "=== expected:")
    if left is None or right is None or len(left) != len(right):
        return False
    for l, r in zip(left, right):
        if l == r:
            continue
        if _normalize_for_compare(l) == _normalize_for_compare(r):
            continue
        return False
    return True


ERRORISH_RE = re.compile(
    r"undeclared|parse error|conflicting types|redefinition|too (?:few|many) arguments|"
    r"incompatible|expected .*before|syntax error|fatal error|subscripted value|"
    r"dereferencing|has no member"
)


def summarize_failure_reason(rc, stdout, stderr):
    """Pick the most informative single line to log, rather than always the
    last stderr line (which for gcc's multi-line diagnostics — e.g. the
    "(Each undeclared identifier is reported only once ...)" continuation —
    is often just a continuation of an earlier, more useful line)."""
    # rc != 0 means quick_diff.sh's `set -euo pipefail` aborted before
    # reaching the diff-printing stage (a real compile/assemble error) —
    # stderr is the right source. rc == 0 means it ran to completion (a
    # genuine instruction-stream mismatch); stderr in that case is often
    # just noise from assembling OTHER still-INCLUDE_ASM stub functions
    # coalesced into the same TU object, so prefer stdout (the actual
    # diff / tag_diff hint lives there).
    text = stderr if rc != 0 else stdout
    lines = [l for l in text.strip().splitlines() if l.strip()]
    if not lines:
        text = stdout if rc != 0 else stderr
        lines = [l for l in text.strip().splitlines() if l.strip()]
    if not lines:
        return f"rc={rc}"
    for l in lines:
        if ERRORISH_RE.search(l):
            return l.strip()
    # No compile-error-shaped line: a genuine instruction-stream mismatch.
    # Prefer a tag_diff hint; else find the first ACTUALLY-differing
    # expected/built instruction pair directly from the numbered blocks
    # (diff -y's textual side-by-side is column-padded and its last line
    # is frequently an identical trailing instruction, not the divergence).
    for i, l in enumerate(lines):
        if l.strip() == "=== tag_diff hints ===" and i + 1 < len(lines):
            return lines[i + 1].strip()
    left = _parse_catn_block(stdout, "=== built:")
    right = _parse_catn_block(stdout, "=== expected:")
    if left is not None and right is not None:
        for i in range(max(len(left), len(right))):
            l = left[i] if i < len(left) else "<end>"
            r = right[i] if i < len(right) else "<end>"
            if l != r and _normalize_for_compare(l) != _normalize_for_compare(r):
                return f"insn {i}: expected `{r.strip()}` built `{l.strip()}`"
    return lines[-1].strip()


def run_quick_diff(tu_name, func_name, timeout=60):
    p = subprocess.run(
        ["bash", "tools/quick_diff.sh", tu_name, func_name],
        cwd=ROOT, capture_output=True, text=True, timeout=timeout,
    )
    if p.returncode != 0:
        return False, p.returncode, p.stdout, p.stderr
    if "MATCH (canonical instruction stream identical)" in p.stdout:
        return True, p.returncode, p.stdout, p.stderr
    # Not a literal MATCH — check whether the only differences are the
    # known jal/jalr external-symbol disassembly artifact.
    if quick_diff_functionally_matches(p.stdout):
        return True, p.returncode, p.stdout, p.stderr
    return False, p.returncode, p.stdout, p.stderr


def cmd_plan(args):
    cache = Cache()
    tu = args.tu
    path = tu_path(tu)
    text = read_latin1(path)
    entries = parse_include_asm_entries(text)
    n_total = len(entries)
    n_avail = 0
    n_quar = 0
    for _, _, name in entries:
        addr = cache.new_n2a.get(name)
        if addr is None:
            continue
        rec = cache.functions.get(str(addr))
        if rec is None:
            continue
        if rec["quarantine"]:
            n_quar += 1
        else:
            n_avail += 1
    print(f"{tu}: {n_total} INCLUDE_ASM total, {n_avail} transplantable, {n_quar} quarantined")


def cmd_splice(args):
    cache = Cache()
    tu = args.tu
    path = tu_path(tu)
    text = read_latin1(path)
    entries = parse_include_asm_entries(text)

    addrs = [cache.new_n2a[name] for _, _, name in entries if name in cache.new_n2a]
    old_files = old_source_files_for_tu(cache, addrs)
    helper_texts = []
    for f in old_files:
        for h in cache.helpers.get(f, []):
            helper_texts.append(cache.rename_text(h["text"]))

    declared = set(IDENT_RE.findall(text))  # anything already textually present

    kept, reverted, quarantined, skipped_no_old = [], [], [], []

    # Insert TU-local helpers once, right after the #include "common.h" line.
    if helper_texts and args.apply:
        inc_m = re.search(r'#include\s+"common\.h"\s*\n', text)
        insert_at = inc_m.end() if inc_m else 0
        block = "\n" + "\n\n".join(helper_texts) + "\n"
        text = text[:insert_at] + block + text[insert_at:]
        write_latin1(path, text)

    processed = 0
    # Main per-function loop. Re-parse INCLUDE_ASM entries fresh each time
    # since successful splices shift byte offsets.
    while True:
        cur_text = read_latin1(path) if args.apply else text
        entries = parse_include_asm_entries(cur_text)
        target = None
        for start, end, name in entries:
            addr = cache.new_n2a.get(name)
            if addr is None:
                continue
            rec = cache.functions.get(str(addr))
            if rec is None:
                continue
            if rec["quarantine"]:
                if (addr, "quarantined") not in quarantined:
                    quarantined.append((addr, name, rec["old_name"], rec["quarantine"]))
                continue
            key = (addr, name)
            if key in [k[:2] for k in kept] or key in [k[:2] for k in reverted]:
                continue
            target = (start, end, name, addr, rec)
            break
        if target is None:
            break
        start, end, name, addr, rec = target
        renamed_body = cache.rename_text(rec["text"])
        # Work on a COPY of `declared` for this attempt — on revert we must
        # not leave behind the impression that this attempt's externs are
        # still present in the file (a previous bug: reverted attempts left
        # their names in `declared`, so a LATER function would skip adding
        # its own needed extern for the same symbol even though the text
        # reverting it removed the actual extern line).
        trial_declared = set(declared)
        needed_externs = gather_needed_externs(cache, renamed_body, name, trial_declared)

        candidate = cur_text[:start] + renamed_body + cur_text[end:]
        top_block = list(needed_externs)
        for hdr in reversed(cache.needed_headers(renamed_body)):
            if f'"{hdr}"' not in cur_text:
                top_block.insert(0, f'#include "{hdr}"')
        if top_block:
            inc_m = re.search(r'#include\s+"common\.h"\s*\n', candidate)
            insert_at = inc_m.end() if inc_m else 0
            block = "\n" + "\n".join(top_block) + "\n"
            candidate = candidate[:insert_at] + block + candidate[insert_at:]

        if not args.apply:
            print(f"[dry-run] would splice {name} (old {rec['old_name']}, {rec['file']}), "
                  f"{len(needed_externs)} new externs")
            kept.append((addr, name, rec["old_name"]))
            declared |= trial_declared
            declared.add(name)
            continue

        write_latin1(path, candidate)
        ok, rc, out, err = run_quick_diff(tu, name)
        if ok:
            kept.append((addr, name, rec["old_name"]))
            declared |= trial_declared
            declared.add(name)
            processed += 1
        else:
            write_latin1(path, cur_text)  # revert — trial_declared discarded
            reason = summarize_failure_reason(rc, out, err)
            reverted.append((addr, name, rec["old_name"], reason))

    print(f"{tu}: kept={len(kept)} reverted={len(reverted)} quarantined={len(quarantined)}")
    if args.apply:
        ts_lines = [f"\n## {tu}"]
        for addr, name, old_name in kept:
            ts_lines.append(f"- KEPT `{name}` (old `{old_name}`) @ 0x{addr:08X}")
        for addr, name, old_name, reason in reverted:
            ts_lines.append(f"- REVERTED `{name}` (old `{old_name}`) @ 0x{addr:08X} — {reason}")
        for addr, name, old_name, reason in quarantined:
            ts_lines.append(f"- QUARANTINED `{name}` (old `{old_name}`) @ 0x{addr:08X} — {reason}")
        ledger_append(ts_lines)
    return kept, reverted, quarantined


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("extract")
    p_plan = sub.add_parser("plan")
    p_plan.add_argument("tu")
    p_splice = sub.add_parser("splice")
    p_splice.add_argument("tu")
    p_splice.add_argument("--apply", action="store_true")
    args = ap.parse_args()
    if args.cmd == "extract":
        cmd_extract(args)
    elif args.cmd == "plan":
        cmd_plan(args)
    elif args.cmd == "splice":
        cmd_splice(args)
