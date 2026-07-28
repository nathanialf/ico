#!/usr/bin/env python3
"""
tools/port_from_aug6.py — Phase 4 aug6 -> retail-v2 body port driver.

The aug6 prototype branch (`main` in the AUG6_ROOT checkout) carries a large
and steadily growing population of byte-matched clean-room C function bodies.
A big fraction of those functions survive into retail SLUS-20218 with the
*same instruction stream* — only the reloc literals (call targets, %hi/%lo
data addresses, $gp offsets) moved, because the two links lay memory out
differently.  Recompiling the aug6 C against the RETAIL symbol addresses is
therefore expected to reproduce the retail bytes exactly.

This driver automates that port end-to-end:

  1. `scan`  — correlate retail `type:func` symbols against aug6 matched
               glabels (asm/aug6/matchings/**/*.s) by NAME, diff the two
               instruction streams, and bucket every joined function into a
               wave (see "Waves" below).  Cached to .port_cache/.
  2. `port`  — for one retail TU: for each still-INCLUDE_ASM candidate,
               extract the aug6 C body, REBIND every aug6 symbol to its
               retail counterpart via a lockstep reloc-slot walk of the two
               instruction streams, splice body + externs into the retail TU,
               and gate on `tools/quick_diff.sh`.  Keep on clean, otherwise
               revert to INCLUDE_ASM and ledger the reason.
  3. `revert-func` — post-hoc single-function revert after a batch-level
               `ninja` SHA-1 bisect.

Waves
-----
  wave 1  retail symbol is twin-anchored (named, no `provisional-ordinal`
          tag) AND the retail stream is reloc-normalized identical to the
          aug6 matched twin.  Highest-confidence set.
  wave 2  retail symbol is `provisional-ordinal` and the RAW instruction
          streams are byte-identical (`verdict: identical` in
          decomp/retail_port/near_misses.json).
  wave 3  retail symbol is `provisional-ordinal` and the diff is `trivial`
          (<=4 differing insns, or every diff is immediate-only — i.e. the
          differing fields are exactly the reloc literals this driver
          rebinds).

Symbol rebinding
----------------
The aug6 splat `.s` carries the reloc annotations (`%hi(sym)`, `%lo(sym)`,
`%gp_rel(sym)`, `jal sym`).  Walking it in lockstep with the retail
instruction words lifted straight out of `baserom/baseelf.rom` yields, for
each aug6 symbol, the RETAIL address that occupies the same reloc slot —
and thus the retail symbol name.  For wave-3 functions the streams are not
index-aligned, so a `difflib` opcode-key alignment (the same one
decomp/retail_port/near_miss_scan.py uses to classify the diff) supplies the
aug6-index -> retail-index map instead of the identity.

Any aug6 symbol whose retail counterpart cannot be resolved unambiguously
aborts that function (revert + ledger reason `unresolved-symbol`).  Nothing
is ever hand-tuned here: a body either recompiles to the retail bytes as-is
or it goes back to INCLUDE_ASM.

Skips
-----
Functions whose aug6 `.s` references `%hi/%lo(jtbl_...)` are deferred to the
Phase-5 jump-table queue (ledger reason `jtbl`) — the switch jump table is
rodata this driver does not carve.  `%gp_rel(jtbl_...)` is an ordinary data
function-pointer table and is NOT skipped.

Usage
-----
  tools/port_from_aug6.py scan [--force]
  tools/port_from_aug6.py status [--wave N]
  tools/port_from_aug6.py plan <retail_tu>
  tools/port_from_aug6.py tus [--wave N]
  tools/port_from_aug6.py port <retail_tu> [--apply] [--waves 1,2,3]
  tools/port_from_aug6.py revert-func <retail_tu> <func> [--reason ...]

See decomp/PORTING.md for the operational runbook and
decomp/transplant_ledger.md (Phase 4 section) for per-function accounting.
"""
import argparse
import bisect
import difflib
import hashlib
import json
import os
import re
import struct
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import transplant_retail as T  # noqa: E402  (shared splice/extern/verify plumbing)

AUG6_ROOT = Path(os.environ.get("PORT_AUG6_ROOT", "/primary/dev/ico"))
CACHE = ROOT / ".port_cache"
CACHE.mkdir(parents=True, exist_ok=True)

TEXT_VMA = 0x100000
TEXT_SZ = 0x16F5D4
ROM = ROOT / "baserom" / "baseelf.rom"

LEDGER_PATH = ROOT / "decomp" / "transplant_ledger.md"

AUG6_PROGS = ("common", "omori", "seki", "sugipon", "ito", "fumi", "script")


def read_latin1(p):
    return Path(p).read_text(encoding="latin-1")


def write_latin1(p, s):
    Path(p).write_text(s, encoding="latin-1")


def gp_of(ld_path):
    m = re.search(r"_gp\s*=\s*0x([0-9A-Fa-f]+)", read_latin1(ld_path))
    if not m:
        raise SystemExit(f"{ld_path}: no _gp assignment")
    return int(m.group(1), 16)


RETAIL_GP = gp_of(ROOT / "config" / "ico.us.ld")
AUG6_GP = gp_of(AUG6_ROOT / "config" / "ico.aug6.ld")


# ==========================================================================
# retail symbol table
# ==========================================================================
SYM_LINE_RE = re.compile(
    r"^([A-Za-z_]\w*)\s*=\s*0x([0-9A-Fa-f]+)\s*;\s*(?://\s*(.*))?$")


def load_retail_symbols():
    """[{name, vma, tu, tag, type}] for every symbol_addrs.us.txt entry."""
    out = []
    for ln in read_latin1(ROOT / "config" / "symbol_addrs.us.txt").splitlines():
        m = SYM_LINE_RE.match(ln.strip())
        if not m:
            continue
        name, vma_s, comment = m.group(1), m.group(2), m.group(3) or ""
        parts = [p.strip() for p in comment.split("//")]
        tm = re.search(r"type:(\S+)", parts[0] if parts else "")
        rest = [p for p in parts[1:] if p]
        tag = "provisional-ordinal" if any(
            "provisional-ordinal" in c for c in rest) else None
        tu = next((c for c in rest if c != "provisional-ordinal"), None)
        out.append({
            "name": name, "vma": int(vma_s, 16),
            "tu": tu, "tag": tag,
            "type": tm.group(1) if tm else None,
        })
    return out


def retail_defined_labels():
    """Every label the retail asm tree actually defines (glabel/dlabel/jlabel)
    plus every symbol_addrs entry. Used to reject a rebound symbol that has no
    definition on the retail side BEFORE it can break the batch link."""
    cache_f = CACHE / "retail_labels.json"
    asm_root = ROOT / "asm"
    if cache_f.exists():
        try:
            return set(json.loads(cache_f.read_text()))
        except Exception:
            pass
    labels = set()
    lab_re = re.compile(r"^\s*(?:glabel|dlabel|jlabel|jtbl_label)\s+([A-Za-z_]\w*)")
    for p in asm_root.rglob("*.s"):
        for ln in read_latin1(p).splitlines():
            m = lab_re.match(ln)
            if m:
                labels.add(m.group(1))
    for e in load_retail_symbols():
        labels.add(e["name"])
    cache_f.write_text(json.dumps(sorted(labels)))
    return labels


# ==========================================================================
# instruction-stream machinery (shared with correlate.py / near_miss_scan.py)
# ==========================================================================
MASK_IMM_OPS = set([0x08, 0x09, 0x0D, 0x18, 0x19, 0x1E, 0x1F]) | set(range(0x20, 0x40))
LOAD_OPS = set([0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                0x30, 0x31, 0x33, 0x35, 0x36, 0x37, 0x1E])
ITYPE_WRITE_RT = set([0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
                      0x18, 0x19, 0x0F]) | LOAD_OPS


def sx16(v):
    return v - 0x10000 if v & 0x8000 else v


def normalize(words):
    """Reloc-normalized instruction stream: blank every field a relocation
    can legitimately move between two different links."""
    taint = [False] * 32
    out = []
    for w in words:
        op = (w >> 26) & 0x3F
        rs = (w >> 21) & 0x1F
        rt = (w >> 16) & 0x1F
        nw = w
        if op in (2, 3):
            nw = w & 0xFC000000
        elif op == 0x0F:
            nw = w & 0xFFFF0000
        elif op in MASK_IMM_OPS:
            if rs == 28 or taint[rs]:
                nw = w & 0xFFFF0000
        wd = None
        if op == 0x0F:
            if rt:
                taint[rt] = True
        else:
            if op == 0:
                wd = (w >> 11) & 0x1F
            elif op == 3:
                wd = 31
            elif op == 1 and rt in (0x10, 0x11):
                wd = 31
            elif op in ITYPE_WRITE_RT and op not in (
                    0x31, 0x35, 0x36, 0x39, 0x3D, 0x3E, 0x3F, 0x1F):
                wd = rt
            elif op == 0x1C:
                wd = (w >> 11) & 0x1F
            elif op in (0x10, 0x11, 0x12):
                if rs in (0, 1, 2, 3):
                    wd = rt
            if wd:
                taint[wd] = False
        out.append(nw)
    return out


def norm_hash(words):
    nw = normalize(words)
    return hashlib.sha1(struct.pack("<%dI" % len(nw), *nw)).hexdigest()


def trim(words):
    words = list(words)
    while words and words[-1] == 0:
        words.pop()
    return words


def op_key(w):
    op = (w >> 26) & 0x3F
    if op == 0:
        return (0, w & 0x3F)
    if op == 1:
        return (1, (w >> 16) & 0x1F)
    if op in (0x10, 0x11, 0x12):
        rs = (w >> 21) & 0x1F
        return (op, rs, w & 0x3F if rs == 0x10 else 0)
    if op == 0x1C:
        return (0x1C, w & 0x3F)
    return (op,)


SHIFT_IMM_FUNCT = {0x00, 0x02, 0x03, 0x38, 0x3A, 0x3B, 0x3C, 0x3E, 0x3F}


def shape(w):
    op = (w >> 26) & 0x3F
    if op in (2, 3):
        return w & 0xFC000000
    if op == 0 and (w & 0x3F) in SHIFT_IMM_FUNCT:
        return w & 0xFFFFF83F
    if op in (0, 0x1C):
        return w
    return w & 0xFFFF0000


def analyze(a, r):
    """near_miss_scan.py's classifier, verbatim in behaviour."""
    a_op = [op_key(w) for w in a]
    r_op = [op_key(w) for w in r]
    sm = difflib.SequenceMatcher(a=a_op, b=r_op, autojunk=False)
    opcodes = sm.get_opcodes()
    total = max(len(a), len(r), 1)
    diff_count = 0
    classes = set()
    blocks = []
    for tag, i1, i2, j1, j2 in opcodes:
        if tag == "equal":
            for k in range(i2 - i1):
                wa, wr = a[i1 + k], r[j1 + k]
                if wa == wr:
                    continue
                diff_count += 1
                classes.add("imm-only" if shape(wa) == shape(wr) else "regalloc")
        else:
            n = max(i2 - i1, j2 - j1)
            diff_count += n
            sub_a, sub_r = a_op[i1:i2], r_op[j1:j2]
            if len(sub_a) == len(sub_r) and sorted(sub_a) == sorted(sub_r) and sub_a:
                classes.add("sched")
            else:
                classes.add("insert/delete-block")
                blocks.append(n)
    return {
        "aug6_insns": len(a), "retail_insns": len(r),
        "diff_count": diff_count, "ratio": round(1.0 - diff_count / total, 4),
        "classes": sorted(classes), "max_block": max(blocks) if blocks else 0,
        "total": total, "opcodes": opcodes,
    }


def verdict_of(res):
    dc = res["diff_count"]
    if dc == 0:
        return "identical"
    if dc <= 4 or res["classes"] == ["imm-only"]:
        return "trivial"
    if res["max_block"] > max(10, 0.3 * res["total"]):
        return "divergent"
    if res["ratio"] < 0.70:
        return "divergent"
    if res["ratio"] >= 0.90 and len(res["classes"]) == 1:
        return "easy"
    return "moderate"


def align_map(a, r, opcodes):
    """aug6 index -> retail index, from the opcode-key alignment. `equal` runs
    map 1:1; an equal-length `replace` run (register/immediate churn with the
    same opcode shape) also maps 1:1; insert/delete runs map to nothing."""
    m = {}
    for tag, i1, i2, j1, j2 in opcodes:
        if tag == "equal" or (tag == "replace" and (i2 - i1) == (j2 - j1)):
            for k in range(i2 - i1):
                m[i1 + k] = j1 + k
    return m


# ==========================================================================
# aug6 .s parsing (words + reloc annotations)
# ==========================================================================
INSN_RE = re.compile(
    r"^\s*/\* [0-9A-Fa-f]+ ([0-9A-Fa-f]{8}) ([0-9A-Fa-f]{8}) \*/\s*(.*)$")

RELOC_RE = [
    ("hi", re.compile(r"%hi\(([A-Za-z_]\w*)")),
    ("lo", re.compile(r"%lo\(([A-Za-z_]\w*)")),
    ("gp", re.compile(r"%gp_rel\(([A-Za-z_]\w*)")),
    ("jal", re.compile(r"\bjal\s+([A-Za-z_]\w*)")),
    ("j", re.compile(r"^\s*j\s+([A-Za-z_]\w*)\s*$")),
]


def parse_aug6_s(path):
    """{func: {'vma':int, 'insns':[(word, kind, sym)]}} for one splat .s."""
    out = {}
    cur = None
    for line in read_latin1(path).splitlines():
        if line.startswith("glabel "):
            cur = line.split()[1].strip()
            out[cur] = {"vma": None, "insns": []}
            continue
        m = INSN_RE.match(line)
        if not m or cur is None:
            continue
        rec = out[cur]
        if rec["vma"] is None:
            rec["vma"] = int(m.group(1), 16)
        word = struct.unpack("<I", bytes.fromhex(m.group(2)))[0]
        rest = m.group(3)
        kind = sym = None
        for k, rx in RELOC_RE:
            mm = rx.search(rest)
            if mm:
                kind, sym = k, mm.group(1)
                break
        rec["insns"].append((word, kind, sym))
    return out


def aug6_matchings_index():
    """func -> {vma, file, stem}. Cached; `scan --force` rebuilds."""
    idx = {}
    root = AUG6_ROOT / "asm" / "aug6" / "matchings"
    for p in root.rglob("*.s"):
        stem = str(p.relative_to(root)).rsplit("/", 1)[0]
        for name, rec in parse_aug6_s(p).items():
            if not rec["insns"]:
                continue
            idx[name] = {
                "vma": rec["vma"],
                "file": str(p.relative_to(AUG6_ROOT)),
                "stem": stem,
            }
    return idx


# ==========================================================================
# scan
# ==========================================================================
def cmd_scan(args):
    out_f = CACHE / "candidates.json"
    if out_f.exists() and not args.force:
        print(f"scan: {out_f} exists (use --force to rebuild)")
        return json.loads(out_f.read_text())

    syms = load_retail_symbols()
    funcs = [e for e in syms if e["type"] == "func"]
    vmas = sorted(set(e["vma"] for e in funcs))
    vmas_arr = vmas + [TEXT_VMA + TEXT_SZ]
    blob = ROM.read_bytes()

    aug6 = aug6_matchings_index()
    # splat never deletes a stale baseline, so asm/aug6/matchings can still
    # hold the .s of a function that has since gone back to INCLUDE_ASM.
    # A candidate is only real if the aug6 TU actually DEFINES it in C.
    src = Aug6Source()
    stale = [n for n, a in aug6.items()
             if n not in src.tu(a["stem"])["funcs"]]
    for n in stale:
        del aug6[n]
    print(f"aug6 matched glabels: {len(aug6)} "
          f"({len(stale)} stale matchings/*.s dropped)", file=sys.stderr)
    print(f"retail type:func symbols: {len(funcs)}", file=sys.stderr)

    records = []
    for e in funcs:
        name = e["name"]
        a = aug6.get(name)
        if a is None:
            continue
        srec = parse_aug6_s(AUG6_ROOT / a["file"])[name]
        a_words = trim([w for w, _, _ in srec["insns"]])
        i = bisect.bisect_right(vmas_arr, e["vma"])
        rend = vmas_arr[i] if i < len(vmas_arr) else TEXT_VMA + TEXT_SZ
        n = (rend - e["vma"]) // 4
        off = e["vma"] - TEXT_VMA
        if off < 0 or off + 4 * n > len(blob) or n <= 0:
            continue
        r_words = trim(list(struct.unpack(f"<{n}I", blob[off:off + 4 * n])))
        if not a_words or not r_words:
            continue
        res = analyze(a_words, r_words)
        res.pop("opcodes")
        verdict = verdict_of(res)
        norm_eq = (len(a_words) == len(r_words)
                   and norm_hash(a_words) == norm_hash(r_words))
        jtbl = any(k in ("hi", "lo") and s and s.startswith("jtbl_")
                   for _, k, s in srec["insns"])

        if e["tag"] is None and norm_eq:
            wave = 1
        elif e["tag"] == "provisional-ordinal" and res["diff_count"] == 0:
            wave = 2
        elif e["tag"] == "provisional-ordinal" and verdict == "trivial":
            wave = 3
        elif e["tag"] is None and verdict in ("identical", "trivial"):
            wave = 3          # named but not norm-identical: same risk class
        else:
            wave = 0          # out of scope for this phase

        records.append({
            "name": name,
            "retail_vma": e["vma"], "retail_end": rend, "retail_tu": e["tu"],
            "tag": e["tag"],
            "aug6_vma": a["vma"], "aug6_file": a["file"], "aug6_stem": a["stem"],
            "norm_equal": norm_eq, "verdict": verdict, "wave": wave,
            "jtbl": jtbl,
            **res,
        })

    hist = defaultdict(int)
    for r in records:
        hist[r["wave"]] += 1
    out = {
        "aug6_root": str(AUG6_ROOT),
        "aug6_head": subprocess.run(
            ["git", "-C", str(AUG6_ROOT), "rev-parse", "HEAD"],
            capture_output=True, text=True).stdout.strip(),
        "aug6_matched_glabels": len(aug6),
        "retail_type_func": len(funcs),
        "joined": len(records),
        "wave_histogram": {str(k): v for k, v in sorted(hist.items())},
        "records": sorted(records, key=lambda r: (r["wave"], r["retail_vma"])),
    }
    out_f.write_text(json.dumps(out, indent=1))
    print(f"joined by name: {len(records)}", file=sys.stderr)
    print(f"wave histogram: {dict(sorted(hist.items()))}", file=sys.stderr)
    print(f"wrote {out_f}", file=sys.stderr)
    return out


def load_candidates():
    f = CACHE / "candidates.json"
    if not f.exists():
        raise SystemExit("no .port_cache/candidates.json — run `scan` first")
    return json.loads(f.read_text())


# ==========================================================================
# symbol rebinding (the lockstep reloc-slot walk)
# ==========================================================================
class Unresolved(Exception):
    pass


def resolve_hi_partner(r_words, j):
    """Retail address behind a %lo slot at retail index `j`: find the most
    recent `lui` writing the base register and combine."""
    w = r_words[j]
    op = (w >> 26) & 0x3F
    if op == 0x0F:
        return None
    rs = (w >> 21) & 0x1F
    for k in range(j - 1, -1, -1):
        wk = r_words[k]
        if ((wk >> 26) & 0x3F) == 0x0F and ((wk >> 16) & 0x1F) == rs:
            return ((wk & 0xFFFF) << 16) + sx16(w & 0xFFFF)
    return None


def build_symbol_map(rec, retail_a2n, retail_func_vmas, defined):
    """aug6 symbol name -> retail symbol name, derived slot-by-slot.

    Raises Unresolved with a human reason on any slot we cannot bind or that
    binds inconsistently."""
    srec = parse_aug6_s(AUG6_ROOT / rec["aug6_file"])[rec["name"]]
    insns = srec["insns"]
    # `trim` only ever removes trailing zero words, so indices below the
    # trimmed length are unaffected.
    a_words = trim([w for w, _, _ in insns])
    blob = ROM.read_bytes()
    n = (rec["retail_end"] - rec["retail_vma"]) // 4
    off = rec["retail_vma"] - TEXT_VMA
    r_words = trim(list(struct.unpack(f"<{n}I", blob[off:off + 4 * n])))

    if len(a_words) == len(r_words) and rec["diff_count"] == 0:
        amap = {i: i for i in range(len(a_words))}
    else:
        res = analyze(a_words, r_words)
        amap = align_map(a_words, r_words, res["opcodes"])

    mapping = {}
    unresolved = []
    for i, (aw, kind, sym) in enumerate(insns):
        if kind is None or i >= len(a_words):
            continue
        if kind == "hi":
            continue                     # the %lo partner carries the address
        j = amap.get(i)
        if j is None or j >= len(r_words):
            unresolved.append((i, sym, "no aligned retail slot"))
            continue
        rw = r_words[j]
        rop = (rw >> 26) & 0x3F
        addr = None
        if kind in ("jal", "j"):
            if rop not in (2, 3):
                unresolved.append((i, sym, f"retail slot is not j/jal (op {rop:#x})"))
                continue
            addr = (rw & 0x3FFFFFF) << 2
        elif kind == "gp":
            if ((rw >> 21) & 0x1F) != 28:
                unresolved.append((i, sym, "retail slot is not $gp-based"))
                continue
            addr = RETAIL_GP + sx16(rw & 0xFFFF)
        elif kind == "lo":
            addr = resolve_hi_partner(r_words, j)
            if addr is None:
                unresolved.append((i, sym, "no retail lui partner for %lo"))
                continue
        if addr is None:
            continue

        rname = retail_a2n.get(addr)
        if rname is None:
            if kind in ("jal", "j") or addr in retail_func_vmas:
                rname = "func_%08X" % addr
            else:
                rname = "D_%08X" % addr
        if rname not in defined:
            unresolved.append((i, sym, f"retail symbol {rname} (0x{addr:08X}) undefined"))
            continue
        prev = mapping.get(sym)
        if prev is not None and prev != rname:
            unresolved.append((i, sym, f"binds to both {prev} and {rname}"))
            continue
        mapping[sym] = rname

    if unresolved:
        i, sym, why = unresolved[0]
        raise Unresolved(f"insn {i} `{sym}`: {why}"
                         + (f" (+{len(unresolved) - 1} more)" if len(unresolved) > 1 else ""))
    return mapping


# ==========================================================================
# aug6 source side
# ==========================================================================
KEYWORDS = {
    "if", "else", "for", "while", "do", "switch", "case", "default", "break",
    "continue", "return", "goto", "sizeof", "typedef", "struct", "union",
    "enum", "static", "extern", "const", "volatile", "register", "signed",
    "unsigned", "char", "short", "int", "long", "float", "double", "void",
    "inline", "asm", "__asm__", "__attribute__", "restrict", "auto",
}


class Aug6Source:
    """Lazily-parsed view of the aug6 dev tree (bodies, decls, typedefs)."""

    def __init__(self):
        self._tus = {}
        self._global_decls = None
        self._global_sigs = None
        self._aug6_syms = None

    def tu(self, stem):
        if stem not in self._tus:
            path = AUG6_ROOT / (stem + ".c")
            raw = read_latin1(path) if path.exists() else ""
            funcs, incasm = T.extract_functions_from_file(stem + ".c", raw)
            self._tus[stem] = {
                "path": path, "raw": raw,
                "funcs": {f["name"]: f for f in funcs},
                "include_asm": incasm,
                "decls": {**T.build_decl_index([(stem + ".c", raw)]),
                          **aug6_decl_index(stem + ".c", raw)},
                "typedefs": aug6_typedef_index(stem + ".c", raw),
                "includes": re.findall(r'^#include\s+"[^"]+"', raw, re.M),
            }
        return self._tus[stem]

    # -- global indices (cached on disk; cheap to rebuild) ------------------
    def _all_texts(self):
        for prog in AUG6_PROGS:
            d = AUG6_ROOT / prog
            if not d.is_dir():
                continue
            for p in sorted(d.rglob("*.c")):
                yield str(p.relative_to(AUG6_ROOT)), read_latin1(p)

    @property
    def global_decls(self):
        if self._global_decls is None:
            f = CACHE / "aug6_decls.json"
            if f.exists():
                self._global_decls = json.loads(f.read_text())
            else:
                texts = list(self._all_texts())
                d = T.build_decl_index(texts)
                for rel, raw in texts:
                    for k, v in aug6_decl_index(rel, raw).items():
                        d.setdefault(k, v)
                self._global_decls = d
                f.write_text(json.dumps(d, ensure_ascii=False))
        return self._global_decls

    @property
    def global_sigs(self):
        """aug6 function name -> its definition's signature text (no body)."""
        if self._global_sigs is None:
            f = CACHE / "aug6_sigs.json"
            if f.exists():
                self._global_sigs = json.loads(f.read_text())
            else:
                sigs = {}
                for rel, raw in self._all_texts():
                    funcs, _ = T.extract_functions_from_file(rel, raw)
                    for fn in funcs:
                        sigs.setdefault(
                            fn["name"],
                            re.sub(r"\s+", " ", fn["text"].split("{", 1)[0].strip()))
                self._global_sigs = sigs
                f.write_text(json.dumps(sigs, ensure_ascii=False))
        return self._global_sigs

    @property
    def aug6_syms(self):
        """Names the aug6 link resolves as real (addressable) symbols."""
        if self._aug6_syms is None:
            names = set()
            p = AUG6_ROOT / "config" / "symbol_addrs.aug6.txt"
            for ln in read_latin1(p).splitlines():
                m = SYM_LINE_RE.match(ln.strip())
                if m:
                    names.add(m.group(1))
            self._aug6_syms = names
        return self._aug6_syms


def rebind_text(text, mapping):
    """Word-boundary substitution of aug6 identifiers -> retail identifiers.
    Longest first so no name shadows a prefix of another."""
    if not mapping:
        return text
    rx = re.compile(r"\b(" + "|".join(
        re.escape(k) for k in sorted(mapping, key=len, reverse=True)) + r")\b")
    return rx.sub(lambda m: mapping[m.group(1)], text)


STR_LITERAL_RE = re.compile(r'"(?:[^"\\]|\\.)*"|\'(?:[^\'\\]|\\.)*\'')


def rebind_code_only(text, mapping):
    """Like rebind_text, but never touches string/char literals.

    Used for the `__asm__("REALNAME")` alias renames: an inline-asm body that
    spells `%hi(D_X)` is assembler text, not C, so the gcc asm-label
    indirection does not apply to it — renaming there would emit a reference
    to a symbol that exists nowhere and fail at link.  (The aug6 -> retail
    SYMBOL rebinding is the opposite case and deliberately does rewrite inside
    those strings.)"""
    if not mapping:
        return text
    rx = re.compile(r"\b(" + "|".join(
        re.escape(k) for k in sorted(mapping, key=len, reverse=True)) + r")\b")
    out, pos = [], 0
    for m in STR_LITERAL_RE.finditer(text):
        out.append(rx.sub(lambda mm: mapping[mm.group(1)], text[pos:m.start()]))
        out.append(m.group(0))
        pos = m.end()
    out.append(rx.sub(lambda mm: mapping[mm.group(1)], text[pos:]))
    return "".join(out)


def unprototyped(sig, name):
    m = re.search(re.escape(name) + r"\s*\(", sig)
    if not m:
        return None
    prefix = sig[:m.start()].strip() or "void"
    prefix = re.sub(r"^(?:static|extern)\s+", "", prefix).strip() or "void"
    return f"extern {prefix} {name}();"


def synth_extern(src, aug6_name, retail_name, stem, body):
    """extern declaration for `retail_name`, typed the way the aug6 source
    types its aug6 counterpart (that typing IS part of the matching shape)."""
    tu = src.tu(stem)
    decl = tu["decls"].get(aug6_name) or src.global_decls.get(aug6_name)
    if decl:
        decl = decl.strip()
        if not decl.endswith(";"):
            decl += ";"
        # drop any gcc asm-label alias: it names an aug6 symbol that does not
        # exist on the retail side.
        decl = re.sub(r'__asm__\s*\(\s*"[^"]*"\s*\)', "", decl)
        decl = re.sub(r"\b%s\b" % re.escape(aug6_name), retail_name, decl)
        decl = re.sub(r"\s+", " ", decl).replace(" ;", ";")
        if decl.startswith("typedef"):
            decl = None
        else:
            if re.search(r"\(\s*\*", decl):
                return decl          # function/array POINTER — never reshape
            if "(" in decl and ")" in decl:
                # a function decl: keep the prototype only when the call sites
                # agree on arity, else fall back to K&R (see transplant_retail)
                dargc = T.param_count_from_sig(decl, retail_name)
                cargc = T.call_arg_count(body, retail_name)
                if dargc is None or cargc is None or dargc == cargc:
                    return decl
                return unprototyped(decl, retail_name) or decl
            return decl
    sig = src.global_sigs.get(aug6_name)
    if sig:
        sig = re.sub(r"\b%s\b" % re.escape(aug6_name), retail_name, sig)
        sig = re.sub(r"^static\s+", "", sig)
        dargc = T.param_count_from_sig(sig, retail_name)
        cargc = T.call_arg_count(body, retail_name)
        if dargc is not None and cargc is not None and dargc == cargc:
            return f"extern {sig};"
        return unprototyped(sig, retail_name) or f"extern {sig};"
    # last resort: naming convention
    if retail_name.startswith("func_") or re.search(
            r"\b%s\s*\(" % re.escape(retail_name), body):
        used = T.call_result_probably_used(body, retail_name)
        return f"extern {'int' if used else 'void'} {retail_name}();"
    if re.search(r"\b%s\s*\[" % re.escape(retail_name), body):
        return f"extern int {retail_name}[];"
    return f"extern int {retail_name};"


def _decl_shape(decl):
    """Whitespace/parameter-name-insensitive fingerprint of a declaration, so
    `extern int f(int a0, int a1);` and `extern int f(int, int);` compare
    equal but `extern void f(void);` does not."""
    s = ASM_LABEL_RE.sub("", decl)
    s = re.sub(r"\bextern\b|\bstatic\b|\bconst\b|\bregister\b", " ", s)
    s = re.sub(r"([A-Za-z_]\w*)\s*(?=[,)])", " ", s)   # parameter names
    s = re.sub(r"[^\w*\[\]().,;]+", " ", s)
    return re.sub(r"\s+", "", s)


def conflicting_decl_alias(tok, retail_decls, want):
    """The retail TU already has `tok` in scope with a DIFFERENT type than the
    aug6 body assumes — a Phase-3 body's placeholder signature, typically.

    Redeclaring is a hard error and inheriting the wrong type is a silent
    miss (implicit `int` return where the ROM has an f0 float, a 4-param
    prototype where the aug6 call passes 2, a `struct GObj` without the
    members the aug6 body reads).  Bind a fresh identifier to the same
    linker symbol instead — the aug6 dev tree's own `__asm__("REALNAME")`
    aliasing idiom — so the aug6 typing governs codegen and the call still
    reaches the same address.

    Returns (alias_decl, alias_name) or None."""
    have = retail_decls.get(tok)
    if have is None or want is None:
        return None
    if _decl_shape(have) == _decl_shape(re.sub(r"\bextern\b", "", want)):
        return None
    alias = tok + "__p4"
    body = want.rstrip().rstrip(";")
    body = ASM_LABEL_RE.sub("", body).rstrip()
    body = re.sub(r"\b%s\b" % re.escape(tok), alias, body, count=1)
    if alias not in body:
        return None
    return f'{body} __asm__("{tok}");', alias


_HDR_TYPES = None


def retail_header_types():
    """Type names the retail SHARED headers already define — anything an
    aug6 TU-local definition would collide with."""
    global _HDR_TYPES
    if _HDR_TYPES is None:
        names = set()
        for p in (ROOT / "include").rglob("*.h"):
            txt = read_latin1(p)
            names |= set(re.findall(
                r"^\s*(?:struct|union|enum)\s+([A-Za-z_]\w*)\s*\{", txt, re.M))
            names |= set(re.findall(r"^\s*typedef\s+[^;{}]*?"
                                    r"([A-Za-z_]\w*)\s*;", txt, re.M))
            names |= set(re.findall(r"\}\s*([A-Za-z_]\w*)\s*;", txt))
        _HDR_TYPES = names
    return _HDR_TYPES


def alias_extern(src, tok, stem, mapping):
    """`extern char wcf_c[] __asm__("D_004C7CF0");` — a C identifier the aug6
    dev aliased onto a real symbol so two references to the same address stay
    distinct roots (defeats CSE; see decomp/COOKBOOK.md dual-root-addr).
    Only the __asm__ label is a linkable symbol, so rebind THAT and keep the
    alias identifier exactly as the body spells it."""
    decl = src.tu(stem)["decls"].get(tok) or src.global_decls.get(tok)
    if not decl:
        return None
    m = ASM_LABEL_RE.search(decl)
    if not m:
        return None
    real = re.search(r'"([^"]*)"', m.group(0)).group(1)
    if real not in mapping:
        return None
    out = decl.replace(m.group(0), f'__asm__("{mapping[real]}")')
    return out if out.rstrip().endswith(";") else out + ";"


def collect_helpers(src, stem, body, mapping, seen):
    """TU-local (fully inlined, non-addressable) helper functions the aug6
    body calls. They carry no relocation, so the symbol map never sees them —
    their SOURCE has to travel with the body. Recurses."""
    tu = src.tu(stem)
    out = []
    frontier = [body]
    while frontier:
        txt = frontier.pop()
        for tok in set(T.IDENT_RE.findall(txt)):
            if tok in seen or tok in KEYWORDS or tok in mapping:
                continue
            fn = tu["funcs"].get(tok)
            if fn is None:
                continue
            if tok in src.aug6_syms or re.match(r"^func_[0-9A-Fa-f]{8}$", tok):
                continue           # addressable: must have come via a reloc
            seen.add(tok)
            out.append(fn["text"])
            frontier.append(fn["text"])
    return out


# ==========================================================================
# port
# ==========================================================================
def retail_tu_path(tu):
    return ROOT / (tu if tu.endswith(".c") else tu + ".c")


def top_insertion_point(text, before):
    """Byte offset just past the LAST `#include` of the file's leading header
    block (bounded by `before`, normally the splice site).

    Inserting after common.h alone is not enough: retail TUs carry
    `#include "vu0.h"` / `"r5900.h"` further down the header block, and an
    extern whose type comes from one of those (`Qw128`, ...) must land AFTER
    it or the TU does not parse."""
    at = 0
    for m in re.finditer(r'^[ \t]*#include\s+[<"][^>"]+[>"][^\n]*\n', text, re.M):
        if m.start() < before:
            at = m.end()
    return at


def tu_stem(tu):
    return tu[:-2] if tu.endswith(".c") else tu


PHASE4_HEADER = """
# Phase 4 — aug6 -> retail body port (`tools/port_from_aug6.py`)

Bodies below were carried over from the aug6 prototype branch's matched C
(clean-room, `main` in AUG6_ROOT) with every aug6 symbol rebound to its
retail counterpart by the lockstep reloc-slot walk.  Nothing here was
hand-tuned: each function either reproduced the retail instruction stream
as-is (`PORTED`) or went straight back to `INCLUDE_ASM` (`REVERTED`, with
the first divergence or compiler diagnostic recorded).  `SKIPPED` = deferred
to the Phase-5 jump-table queue.

Revert-reason classes: `unresolved-symbol` (a reloc slot the walk could not
bind), `callee-sig-conflict` / `arity` (a Phase-3 retail body in the same TU
declares the callee with a placeholder signature the aug6 body contradicts),
`undeclared` / `parse` (decl context), `codegen` (compiles, wrong bytes).
"""


def ledger_append(lines):
    txt = LEDGER_PATH.read_text(encoding="utf-8") if LEDGER_PATH.exists() else ""
    with open(LEDGER_PATH, "a", encoding="utf-8") as f:
        if "# Phase 4 — aug6 -> retail body port" not in txt:
            f.write(PHASE4_HEADER)
        for ln in lines:
            f.write(ln + "\n")


def candidates_for_tu(cand, tu, waves):
    stem = tu_stem(tu)
    out = []
    for r in cand["records"]:
        if r["wave"] not in waves:
            continue
        rtu = r["retail_tu"]
        if rtu is None:
            continue
        if tu_stem(rtu) != stem:
            continue
        out.append(r)
    return out


def cmd_tus(args):
    cand = load_candidates()
    waves = set(args.waves)
    per = defaultdict(int)
    for r in cand["records"]:
        if r["wave"] in waves and r["retail_tu"]:
            per[tu_stem(r["retail_tu"])] += 1
    for tu, n in sorted(per.items(), key=lambda kv: (-kv[1], kv[0])):
        print(f"{n:5d}  {tu}")
    print(f"# {len(per)} TUs, {sum(per.values())} candidates", file=sys.stderr)


def cmd_plan(args):
    cand = load_candidates()
    rows = candidates_for_tu(cand, args.tu, {1, 2, 3})
    path = retail_tu_path(args.tu)
    text = read_latin1(path)
    inc = {n for _, _, n in T.parse_include_asm_entries(text)}
    todo = [r for r in rows if r["name"] in inc]
    print(f"{args.tu}: {len(rows)} candidates, {len(todo)} still INCLUDE_ASM")
    for r in sorted(todo, key=lambda r: r["wave"]):
        print(f"  w{r['wave']} {r['name']:<40s} {r['aug6_insns']:5d} insn "
              f"dc={r['diff_count']:<4d} {r['verdict']}"
              + ("  [jtbl]" if r["jtbl"] else ""))


def cmd_port(args):
    cand = load_candidates()
    waves = set(args.waves)
    rows = candidates_for_tu(cand, args.tu, waves)
    if not rows:
        print(f"{args.tu}: no candidates in waves {sorted(waves)}")
        return [], [], []

    src = Aug6Source()
    retail_syms = load_retail_symbols()
    retail_a2n = {}
    for e in retail_syms:                    # named entries win over defaults
        retail_a2n.setdefault(e["vma"], e["name"])
    retail_func_vmas = set(e["vma"] for e in retail_syms if e["type"] == "func")
    defined = retail_defined_labels()

    path = retail_tu_path(args.tu)
    stem = tu_stem(args.tu)
    kept, reverted, skipped = [], [], []
    data_baseline = None

    # order: wave 1 first (highest confidence), then by address
    rows.sort(key=lambda r: (r["wave"], r["retail_vma"]))

    for rec in rows:
        name = rec["name"]
        cur_text = read_latin1(path)
        entries = T.parse_include_asm_entries(cur_text)
        span = next(((s, e) for s, e, n in entries if n == name), None)
        if span is None:
            continue                          # already ported / not in this TU
        if rec["jtbl"]:
            skipped.append((rec, "jtbl"))
            continue

        try:
            mapping = build_symbol_map(rec, retail_a2n, retail_func_vmas, defined)
        except Unresolved as ex:
            reverted.append((rec, f"unresolved-symbol: {ex}"))
            continue
        except Exception as ex:                # noqa: BLE001 - diagnostic only
            reverted.append((rec, f"map-error: {type(ex).__name__}: {ex}"))
            continue

        atu = src.tu(rec["aug6_stem"])
        fn = atu["funcs"].get(name)
        if fn is None:
            reverted.append((rec, f"aug6 body not found in {rec['aug6_stem']}.c"))
            continue

        # self-name must NOT be rebound to a retail alias of a different func
        mapping.pop(name, None)
        body = rebind_text(fn["text"], mapping)

        helper_seen = {name}
        helpers = [rebind_text(h, mapping)
                   for h in collect_helpers(src, rec["aug6_stem"], fn["text"],
                                            mapping, helper_seen)]

        # Identifiers already in scope AT THE SPLICE POINT. Two exclusions
        # matter: (a) INCLUDE_ASM lines — their function-name argument is not
        # a C declaration; (b) everything BELOW the splice point — a callee
        # defined later in the same TU is not in scope here, so the body still
        # needs its own extern (without it gcc falls back to implicit
        # `int f()` and, for an f0-returning callee, emits mtc1/cvt where the
        # ROM has a plain lwc1 — a silent, whole-function-shifting miss).
        declared = set(T.IDENT_RE.findall(
            re.sub(r"INCLUDE_ASM[^\n]*\n", "", cur_text[:span[0]])))
        top = []

        # TU-local struct/union/enum typedefs the body (or helpers) needs
        scan_txt = "\n".join([body] + helpers)
        # An aug6 TU routinely defines its OWN `struct GObj { ... }` with mined
        # member names while the retail tree's shared include/ico/types.h
        # already defines that tag differently. Redefining it is an error;
        # silently using the header's is worse (`structure has no member named
        # f_0`). A struct tag is purely internal to the C, so rename the
        # aug6-local one: identical layout, identical codegen, no clash.
        type_rename = {t: t + "__p4" for t in atu["typedefs"]
                       if t in retail_header_types()}

        typedef_blocks = []
        for tname, blk in _needed_typedefs(atu, scan_txt, declared, mapping,
                                           type_rename):
            declared.add(type_rename.get(tname, tname))
            typedef_blocks.append(blk)

        # Declarations already in scope at the splice point, so a conflicting
        # one can be detected rather than tripped over. Both forms count: an
        # `extern` above, and a real definition above (Phase-3 bodies carry
        # placeholder signatures the aug6 caller contradicts).
        # Every declaration the WHOLE retail TU makes for a symbol — above the
        # splice point (already in scope) and below it (a later definition
        # that would collide with an extern spliced here). Phase-3 bodies in
        # particular carry placeholder signatures the aug6 caller contradicts.
        retail_decls = aug6_decl_index(stem + ".c", cur_text)
        tu_funcs, _ = T.extract_functions_from_file(stem + ".c", cur_text)
        for fdef in tu_funcs:
            retail_decls.setdefault(
                fdef["name"],
                re.sub(r"\s+", " ", fdef["text"].split("{", 1)[0].strip()) + ";")

        # externs, keyed off the aug6 identifier so the aug6 TYPE carries over
        inv = {v: k for k, v in mapping.items()}
        body_alias = {}
        for tok in sorted(set(T.IDENT_RE.findall(scan_txt))):
            if tok in KEYWORDS or tok == name:
                continue
            a_name = inv.get(tok)
            if a_name is None:
                if tok in declared:
                    continue
                # An asm-label alias (`extern char wcf_c[] __asm__("D_X");`) —
                # the aug6 dev's dual-root-addr / CSE-defeat idiom. The C
                # identifier has no address of its own, so the reloc walk never
                # sees it; bind it through the REAL symbol named in its
                # __asm__ label instead.
                alias = alias_extern(src, tok, rec["aug6_stem"], mapping)
                if alias:
                    top.append(alias)
                    declared.add(tok)
                    continue
                # otherwise: only declare a raw splat default that somehow
                # survived unrebound
                if not re.match(r"^(func|D)_[0-9A-Fa-f]{8}$", tok):
                    continue
                a_name = tok
            ext = synth_extern(src, a_name, tok, rec["aug6_stem"], scan_txt)
            # Compare against the retail declaration in the SAME spelling the
            # body will use: an aug6 extern typed `struct GObj *` is textually
            # identical to the retail one, yet after the TU-local tag rename
            # it denotes a different (correctly-mined) layout — that IS a
            # conflict and must be aliased, not skipped.
            if ext and type_rename:
                ext = rebind_text(ext, type_rename)
            got = conflicting_decl_alias(tok, retail_decls, ext)
            if got:
                if got[1] not in declared:      # one alias decl per TU
                    top.append(got[0])
                    declared.add(got[1])
                body_alias[tok] = got[1]
                continue
            if tok in declared:
                continue
            if ext:
                top.append(ext)
                declared.add(tok)

        # An extern can itself name a TU-local struct/union/enum the body
        # never mentions (`extern struct GObjEnt D_X[];` -> `.f_0`); pull
        # those in too, then re-run in case they chain.
        for _ in range(4):
            more = _needed_typedefs(atu, "\n".join(top), declared, mapping,
                                    type_rename)
            if not more:
                break
            for tname, blk in more:
                declared.add(type_rename.get(tname, tname))
                typedef_blocks.append(blk)

        if type_rename:
            body = rebind_text(body, type_rename)
            helpers = [rebind_text(h, type_rename) for h in helpers]
            typedef_blocks = [rebind_text(b, type_rename) for b in typedef_blocks]
            top = [rebind_text(t, type_rename) for t in top]
        if body_alias:
            body = rebind_code_only(body, body_alias)
            helpers = [rebind_code_only(h, body_alias) for h in helpers]

        # headers the aug6 TU pulled in that the retail TU lacks
        heads = []
        for inc_line in atu["includes"]:
            if inc_line.split('"')[1] == "common.h":
                continue
            if inc_line not in cur_text:
                heads.append(inc_line)

        # Externs go IMMEDIATELY ABOVE the body, which is both what the aug6
        # dev source itself does and what keeps the declaration context of the
        # body identical to the TU it was matched in (decl order is part of
        # the matching shape). Headers, TU-local typedefs and carried-along
        # static helpers go into the file's leading header block instead.
        local = ("\n".join(top) + "\n\n") if top else ""
        candidate = cur_text[:span[0]] + local + body + cur_text[span[1]:]
        block_parts = heads + typedef_blocks + helpers
        if block_parts:
            at = top_insertion_point(candidate, span[0])
            candidate = (candidate[:at] + "\n" + "\n".join(block_parts)
                         + "\n" + candidate[at:])

        if os.environ.get("PORT_DEBUG_DUMP"):
            Path(os.environ["PORT_DEBUG_DUMP"], f"{name}.c").write_text(
                candidate, encoding="latin-1")

        if not args.apply:
            print(f"[dry-run] w{rec['wave']} {name}: "
                  f"{len(mapping)} syms, {len(top)} externs, "
                  f"{len(helpers)} helpers, {len(heads)} includes")
            kept.append((rec, mapping))
            continue

        if data_baseline is None:
            # Compile the TU as-is once, so "did this body add data?" has a
            # reference point. An INCLUDE_ASM'd function assembles to exactly
            # the ROM bytes, so this run is also a free sanity check.
            T.run_quick_diff(stem, name)
            data_baseline = data_bytes(stem)

        write_latin1(path, candidate)
        allowed = set(mapping.values()) | {name}
        ok, rc, out, err = verify_port(stem, name, allowed)
        if ok:
            grew = data_bytes(stem)
            if (data_baseline is not None and grew is not None
                    and grew > data_baseline):
                write_latin1(path, cur_text)
                reverted.append((rec, f"emits-data: +{grew - data_baseline} "
                                      f"bytes of .rodata/.sdata/.lit4 "
                                      f"(string or out-of-line float literal; "
                                      f"needs a Phase-5 rodata carve)"))
                continue
            kept.append((rec, mapping))
        else:
            write_latin1(path, cur_text)
            reverted.append((rec, failure_reason(rc, out, err)))

    print(f"{args.tu}: kept={len(kept)} reverted={len(reverted)} "
          f"skipped={len(skipped)}")
    if args.apply:
        lines = [f"\n### {args.tu}"]
        for rec, mapping in kept:
            lines.append(f"- PORTED `{rec['name']}` w{rec['wave']} @ "
                         f"0x{rec['retail_vma']:08X} <- aug6 {rec['aug6_stem']}"
                         f" ({len(mapping)} syms rebound)")
        for rec, reason in reverted:
            lines.append(f"- REVERTED `{rec['name']}` w{rec['wave']} @ "
                         f"0x{rec['retail_vma']:08X} — "
                         f"[{classify_reason(reason)}] {reason}")
        for rec, reason in skipped:
            lines.append(f"- SKIPPED `{rec['name']}` w{rec['wave']} @ "
                         f"0x{rec['retail_vma']:08X} — {reason}")
        ledger_append(lines)
    return kept, reverted, skipped


BRACKET_SYM_RE = re.compile(r"<([A-Za-z_][\w.]*)(?:\+0x[0-9a-f]+)?>")


def _tolerable_pair(built, expected, allowed):
    """Is a built/expected disassembly line pair a KNOWN cosmetic artifact?

    On top of transplant_retail's two cases (same-function relative branch,
    both-sides-unresolved external call) there is a third that only shows up
    once bodies are spliced into a coalesced TU: a call whose target is
    ANOTHER function of the same TU.  In the isolated single-function
    baseline object that call is an unresolved R_MIPS_26 (`jal 0 <whatever
    symbol sits at offset 0>`); in the built multi-function object the
    assembler resolves it in-object, so it disassembles as a real offset and
    the real callee name.  Same bytes after linking — see the `intu_falseneg`
    note in decomp/NOTES.md.

    That tolerance is only granted when the resolved side names a symbol this
    function's OWN reloc-slot walk bound (`allowed`), so a call retargeted to
    the wrong function is still caught here rather than at the batch gate."""
    mb = T.BRANCH_TARGET_RE.match(built)
    me = T.BRANCH_TARGET_RE.match(expected)
    if not mb or not me:
        return False
    if mb.group(1) != me.group(1):
        return False                       # different mnemonic/operands
    zb = mb.group(2).lstrip("0") == ""
    ze = me.group(2).lstrip("0") == ""
    if not (zb or ze):
        return False
    resolved = mb.group(3) if not zb else me.group(3)
    sym = BRACKET_SYM_RE.search(resolved)
    return bool(sym) and sym.group(1) in allowed


def verify_port(stem, name, allowed, timeout=120):
    """quick_diff.sh gate, with the coalesced-TU artifact tolerances."""
    p = subprocess.run(["bash", "tools/quick_diff.sh", stem, name],
                       cwd=ROOT, capture_output=True, text=True, timeout=timeout)
    if p.returncode != 0:
        return False, p.returncode, p.stdout, p.stderr
    if "MATCH (canonical instruction stream identical)" in p.stdout:
        return True, p.returncode, p.stdout, p.stderr
    if T.quick_diff_functionally_matches(p.stdout):
        return True, p.returncode, p.stdout, p.stderr
    left = T._parse_catn_block(p.stdout, "=== built:")
    right = T._parse_catn_block(p.stdout, "=== expected:")
    if left is None or right is None or len(left) != len(right):
        return False, p.returncode, p.stdout, p.stderr
    for b, e in zip(left, right):
        if b == e or T._normalize_for_compare(b) == T._normalize_for_compare(e):
            continue
        if _tolerable_pair(b, e, allowed):
            continue
        return False, p.returncode, p.stdout, p.stderr
    return True, p.returncode, p.stdout, p.stderr


DATA_SECTION_PREFIXES = (".data", ".rodata", ".sdata", ".lit4", ".lit8")
OBJDUMP = os.environ.get("OBJDUMP", "mips-linux-gnu-objdump")


def data_bytes(stem):
    """Allocatable NON-.text bytes in the TU object quick_diff just built.

    Retail carves no data: every string literal and every out-of-line float
    constant in a ported body would be NEW bytes appended to .sdata/.rodata/
    .lit4, shifting the whole data layout and every %hi/%lo and $gp-relative
    reference in the game — a link that is byte-identical nowhere yet passes
    the per-function instruction diff cleanly.  So the port carries a hard
    invariant: it may add code, never data."""
    o = ROOT / "build" / "quick_diff" / (stem + ".o")
    if not o.exists():
        return None
    p = subprocess.run([OBJDUMP, "-h", str(o)], capture_output=True, text=True)
    total = 0
    for ln in p.stdout.splitlines():
        m = re.match(r"\s*\d+\s+(\S+)\s+([0-9a-f]+)", ln)
        if m and m.group(1).startswith(DATA_SECTION_PREFIXES):
            total += int(m.group(2), 16)
    return total


def failure_reason(rc, out, err):
    """transplant_retail.summarize_failure_reason, minus gcc *warnings* —
    `passing arg N of X from incompatible pointer type` matches its
    error-ish regex but is never the reason a function failed to match, and
    letting it win hides the real first differing instruction."""
    filtered_out = "\n".join(l for l in out.splitlines() if "warning:" not in l)
    filtered_err = "\n".join(l for l in err.splitlines() if "warning:" not in l)
    reason = T.summarize_failure_reason(rc, filtered_out, filtered_err)
    if reason.strip() in ("", f"rc={rc}"):
        reason = T.summarize_failure_reason(rc, out, err)
    return reason


REASON_CLASSES = [
    ("unresolved-symbol", r"^unresolved-symbol:"),
    ("map-error", r"^map-error:"),
    ("callee-sig-conflict", r"conflicting types for"),
    ("undeclared", r"undeclared|has no member|dereferencing"),
    ("arity", r"too (?:few|many) arguments"),
    ("parse", r"parse error|syntax error|expected .*before"),
    ("redefinition", r"redefinition"),
    ("missing-body", r"aug6 body not found"),
    ("emits-data", r"^emits-data:"),
]


def classify_reason(reason):
    for tag, rx in REASON_CLASSES:
        if re.search(rx, reason):
            return tag
    return "codegen"


def _needed_typedefs(atu, text, declared, mapping, rename=None):
    """TU-local type definitions the body needs, in DEPENDENCY order.

    `typedef int Qw128 __attribute__((mode(TI)));` /
    `typedef struct { ... Qw128 q; } MatDrive;` is the common aug6 idiom, so
    resolving one typedef routinely uncovers another: iterate until closed and
    emit the later (more primitive) rounds first."""
    idx = atu["typedefs"]
    if not idx:
        return []
    rx = re.compile(r"\b(" + "|".join(
        re.escape(k) for k in sorted(idx, key=len, reverse=True)) + r")\b")
    # transitive closure of the type names the body needs. A name is "already
    # in scope" only under the spelling we would EMIT it as: a tag that
    # collides with a retail shared header gets renamed, so the retail
    # header's own (differently-shaped) definition must not suppress it.
    rename = rename or {}
    need = {}
    seen = set()
    frontier = [text]
    while frontier:
        chunk = frontier.pop()
        for nm in sorted(set(rx.findall(chunk))):
            if nm in seen or rename.get(nm, nm) in declared:
                continue
            seen.add(nm)
            blk = rebind_text(idx[nm], mapping)
            need[nm] = blk
            frontier.append(blk)
    # topological order: a typedef must follow every typedef it mentions
    deps = {nm: {d for d in rx.findall(blk) if d in need and d != nm}
            for nm, blk in need.items()}
    out, emitted = [], set()
    while len(emitted) < len(need):
        ready = sorted(nm for nm in need
                       if nm not in emitted and not (deps[nm] - emitted))
        if not ready:                       # cycle: emit the rest as-is
            ready = sorted(nm for nm in need if nm not in emitted)
        for nm in ready:
            emitted.add(nm)
            out.append((nm, need[nm]))
    return out


SIMPLE_TYPEDEF_TRAILER = re.compile(
    r"__attribute__\s*\(\(.*\)\)\s*$|\[[^\]]*\]\s*$")

ASM_LABEL_RE = re.compile(r'__asm__\s*\(\s*"[^"]*"\s*\)')


def declarator_name(stmt):
    """The identifier a C declaration introduces.

    Handles the three shapes the aug6 dev tree uses, in priority order:
      `extern int (*jtbl_0062A6D0)(void *, int);`   function/array POINTER
      `extern float MatrixDrive_GetTurnYAngleXZ(float);`  function prototype
      `extern float D_00628C2C;` / `extern int D_X[];`     object

    The pointer case is the one that matters most: the shared
    transplant_retail decl index does not match it at all, and losing it
    turns an indirect `lw $v0,%gp_rel(ptr); jalr $v0` into a direct `jal` —
    a whole-function miss that reads like an unrelated scheduling diff."""
    s = ASM_LABEL_RE.sub("", stmt).strip().rstrip(";").strip()
    m = re.search(r"\(\s*\*+\s*([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*\)", s)
    if m:
        return m.group(1)
    m = re.search(r"([A-Za-z_]\w*)\s*\(", s)
    if m and m.group(1) not in KEYWORDS:
        return m.group(1)
    s2 = re.sub(r"(?:\[[^\]]*\]\s*)+$", "", s).strip()
    s2 = re.sub(r"=\s*.*$", "", s2, flags=re.S).strip()
    m = re.search(r"([A-Za-z_]\w*)\s*$", s2)
    return m.group(1) if m and m.group(1) not in KEYWORDS else None


def aug6_decl_index(rel, raw):
    """name -> full `extern ...;` statement, for every top-level extern in one
    aug6 TU. Paren/brace-aware statement splitting, so multi-line prototypes
    and function-pointer declarators survive intact."""
    clean = T.strip_comments_preserve_len(raw)
    # Preprocessor lines terminate a top-level statement without a `;`.
    # Blank them (length-preserving) or the leading `#include` block glues
    # itself onto the first real declaration and no `extern` is ever seen.
    clean = "\n".join(
        " " * len(ln) if ln.lstrip().startswith("#") else ln
        for ln in clean.split("\n"))
    n = len(clean)
    idx = {}
    i = 0
    depth = 0
    stmt_start = 0
    while i < n:
        c = clean[i]
        if c in "{([":
            depth += 1
        elif c in "})]":
            depth -= 1
            if depth < 0:
                depth = 0
            if c == "}" and depth == 0:
                stmt_start = i + 1
        elif c == ";" and depth == 0:
            seg = clean[stmt_start:i + 1]
            lead = len(seg) - len(seg.lstrip())
            st = clean[stmt_start + lead:i + 1]
            body = raw[stmt_start + lead:i + 1]
            if st.startswith("extern") and not st.startswith("externs"):
                if ("(" not in st and "[" not in st
                        and T.count_top_level_commas(st) > 0):
                    m = re.match(r"extern\s+([\w \t\*]+?)\s*"
                                 r"([A-Za-z_]\w*(?:\s*,\s*[A-Za-z_]\w*)+)\s*;",
                                 st)
                    if m:
                        for nm in [x.strip() for x in m.group(2).split(",")]:
                            idx.setdefault(nm, f"extern {m.group(1).strip()} {nm};")
                        i += 1
                        stmt_start = i
                        continue
                nm = declarator_name(st)
                if nm:
                    idx.setdefault(nm, " ".join(body.split()))
            stmt_start = i + 1
        i += 1
    return idx


def aug6_typedef_index(rel, raw):
    """All top-level `typedef ...;` statements in one aug6 TU, keyed by the
    name they introduce. Extends transplant_retail's struct/union/enum index
    with the SCALAR forms (`typedef int Qw128 __attribute__((mode(TI)));`)
    that the aug6 dev tree uses for the 128-bit / TI-mode quadword shapes."""
    idx = dict(T.build_typedef_index([(rel, raw)]))
    clean = T.strip_comments_preserve_len(raw)
    n = len(clean)
    for m in re.finditer(r"\btypedef\b", clean):
        depth = 0
        j = m.end()
        while j < n:
            c = clean[j]
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
            elif c == ";" and depth == 0:
                break
            j += 1
        if j >= n:
            continue
        stmt_clean = clean[m.start():j].strip()
        name = None
        fp = re.search(r"\(\s*\*\s*([A-Za-z_]\w*)\s*\)", stmt_clean)
        if fp:
            name = fp.group(1)
        else:
            tail = stmt_clean
            for _ in range(4):
                new = SIMPLE_TYPEDEF_TRAILER.sub("", tail).strip()
                if new == tail:
                    break
                tail = new
            mm = re.search(r"([A-Za-z_]\w*)\s*$", tail)
            if mm:
                name = mm.group(1)
        if name and name not in idx:
            idx[name] = raw[m.start():j + 1].strip()
    return idx


def cmd_port_all(args):
    """Port every TU that still has pending candidates, in descending
    candidate-count order. This is the normal entry point; `port` is the
    single-TU form used when bisecting."""
    cand = load_candidates()
    waves = set(args.waves)
    per = defaultdict(int)
    for r in cand["records"]:
        if r["wave"] in waves and r["retail_tu"]:
            per[tu_stem(r["retail_tu"])] += 1
    tus = [t for t, _ in sorted(per.items(), key=lambda kv: (-kv[1], kv[0]))]
    if args.skip:
        tus = tus[args.skip:]
    if args.limit:
        tus = tus[:args.limit]

    tot_k = tot_r = tot_s = 0
    classes = defaultdict(int)
    for tu in tus:
        if not retail_tu_path(tu).exists():
            print(f"{tu}: no such retail TU — skipped", file=sys.stderr)
            continue
        sub = argparse.Namespace(tu=tu, apply=args.apply, waves=args.waves)
        k, r, s = cmd_port(sub)
        tot_k += len(k)
        tot_r += len(r)
        tot_s += len(s)
        for _, reason in r:
            classes[classify_reason(reason)] += 1
    print(f"\n== port-all: {len(tus)} TUs  ported={tot_k} reverted={tot_r} "
          f"skipped={tot_s}")
    for c, n in sorted(classes.items(), key=lambda kv: -kv[1]):
        print(f"   {n:5d}  {c}")


def cmd_revert_func(args):
    path = retail_tu_path(args.tu)
    text = read_latin1(path)
    funcs, _ = T.extract_functions_from_file(args.tu + ".c", text)
    target = next((f for f in funcs if f["name"] == args.func), None)
    if target is None:
        print(f"revert-func: {args.func} is not a spliced function in "
              f"{args.tu}.c", file=sys.stderr)
        sys.exit(1)
    m = re.search(r'INCLUDE_ASM\("([^"]+)"', text)
    folder = m.group(1) if m else f"asm/nonmatchings/{tu_stem(args.tu)}"
    stub = f'INCLUDE_ASM("{folder}", {args.func});'
    write_latin1(path, text[:target["start"]] + stub + text[target["end"]:])
    reason = args.reason or ("post-hoc: passed quick_diff but broke the "
                             "batch-level ninja SHA-1 gate")
    ledger_append([f"- REVERTED `{args.func}` — {reason} (post-hoc, bisected)"])
    print(f"revert-func: reverted {args.func} in {args.tu}.c")


def cmd_status(args):
    cand = load_candidates()
    waves = set(args.waves) if args.waves else {1, 2, 3}
    tot = done = todo = jtbl = 0
    by_wave = defaultdict(lambda: [0, 0, 0])
    tu_text_cache = {}
    for r in cand["records"]:
        if r["wave"] not in waves or not r["retail_tu"]:
            continue
        tot += 1
        p = retail_tu_path(r["retail_tu"])
        if p not in tu_text_cache:
            tu_text_cache[p] = (read_latin1(p) if p.exists() else "")
        inc = f", {r['name']});" in tu_text_cache[p] or re.search(
            r"INCLUDE_ASM[_A-Z]*\([^)]*,\s*%s\s*\)" % re.escape(r["name"]),
            tu_text_cache[p])
        by_wave[r["wave"]][0] += 1
        if r["jtbl"]:
            jtbl += 1
            by_wave[r["wave"]][2] += 1
        elif not inc:
            done += 1
            by_wave[r["wave"]][1] += 1
        else:
            todo += 1
    print(f"waves {sorted(waves)}: {tot} candidates, {done} ported, "
          f"{todo} pending, {jtbl} jtbl-skip")
    for w in sorted(by_wave):
        t, d, j = by_wave[w]
        print(f"  wave {w}: {t:5d} total  {d:5d} ported  {j:4d} jtbl")


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)

    p = sub.add_parser("scan")
    p.add_argument("--force", action="store_true")

    p = sub.add_parser("status")
    p.add_argument("--waves", type=lambda s: [int(x) for x in s.split(",")],
                   default=None)

    p = sub.add_parser("tus")
    p.add_argument("--waves", type=lambda s: [int(x) for x in s.split(",")],
                   default=[1, 2, 3])

    p = sub.add_parser("plan")
    p.add_argument("tu")

    p = sub.add_parser("port")
    p.add_argument("tu")
    p.add_argument("--apply", action="store_true")
    p.add_argument("--waves", type=lambda s: [int(x) for x in s.split(",")],
                   default=[1, 2, 3])

    p = sub.add_parser("port-all")
    p.add_argument("--apply", action="store_true")
    p.add_argument("--waves", type=lambda s: [int(x) for x in s.split(",")],
                   default=[1, 2, 3])
    p.add_argument("--limit", type=int, default=0)
    p.add_argument("--skip", type=int, default=0)

    p = sub.add_parser("revert-func")
    p.add_argument("tu")
    p.add_argument("func")
    p.add_argument("--reason", default=None)

    args = ap.parse_args()
    {"scan": cmd_scan, "status": cmd_status, "tus": cmd_tus, "plan": cmd_plan,
     "port": cmd_port, "port-all": cmd_port_all,
     "revert-func": cmd_revert_func}[args.cmd](args)
