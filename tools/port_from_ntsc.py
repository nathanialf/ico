#!/usr/bin/env python3
"""
tools/port_from_ntsc.py — ntsc (USA retail) -> PAL retail body port driver.

Sibling of `tools/port_from_aug6.py` (which stays untouched, for the
aug6 -> pal port).  Source tree here is the `ntsc` checkout (USA retail
SCUS-971.13, default `/primary/dev/ico-ntsc`), which carries ~2900
byte-matched clean-room C bodies under a FLAT `src/ ios/ isys/ sound/ ito/`
layout with per-function splat baselines in `asm/matchings/<dir>/<tu>/`.
Target is this tree: PAL retail SCES-507.60.

The overwhelming majority of PAL functions are the same source recompiled
against a different link: identical instruction streams modulo the reloc
literals (call targets, %hi/%lo data addresses, $gp offsets).  Recompiling
the ntsc C against the PAL symbol addresses reproduces the PAL bytes.

What is different from the aug6 driver
--------------------------------------
1. **Join by name AND by twin hash.**  US symbol names are half splat
   placeholders (`func_<VMA>`), so a name join alone loses every function
   the two trees happened to name differently.  `scan` therefore also
   correlates the two `.text` inventories by reloc-normalized
   instruction-stream hash under the LINK-ORDER constraint (the 214 shared
   TUs link in identical order), via a `difflib` alignment of the two
   VMA-ordered hash sequences.  Equal-block pairs whose names differ are
   emitted as `.port_cache/name_alias.json` ({pal_name: us_name}) — the same
   alias mechanism the aug6 driver already consumes — and the full
   correlation table as `.port_cache/ntsc_pal_twins.json`, so a later
   "rename ntsc from PAL" pass can reuse it.

2. **Target TU files do not exist yet.**  Every PAL `.text` subsegment is
   still `[OFF, asm, src/<tu>]`.  Before a TU's first body can be ported the
   driver writes `src/<tu>.c` as an INCLUDE_ASM scaffold covering every
   function of that PAL span (VMA order, names straight out of the splat
   `.s`), flips the yaml line to `c`, and re-runs `tools/build.sh setup` so
   splat emits `asm/nonmatchings/<tu>/<func>.s`.  Flips are batched: one
   `setup` per chunk, not per TU.  A TU that ends up with zero ported bodies
   is flipped back to `asm` and its scaffold removed.

3. **Coalescers.**  PAL `src/box` spans what ntsc splits into `src/box` +
   `src/switch`; `src/debug`, `src/girl_act`, `src/motionManager` likewise
   absorb `.c.inc` siblings.  No special case is needed: the body source is
   resolved PER FUNCTION from the ntsc matchings index, so one PAL TU can
   draw bodies from two ntsc TUs, and the scaffold's VMA order fixes the
   object layout.

4. **Data.**  The `emits-data` gate is unchanged (a body that grows any
   allocatable non-.text section reverts).  Carves are NOT translated in this
   pass, but every reverted TU's US carve entries (from ntsc's
   `config/ico.us.yaml`, comments included) are recorded in the ledger so the
   carve pass can pick them up.

Waves (same definitions as the aug6 driver)
-------------------------------------------
  wave 1  PAL symbol is twin-anchored (a real name, no `provisional-ordinal`
          tag) AND the PAL stream is reloc-normalized identical to the ntsc
          matched twin.
  wave 2  PAL symbol is `provisional-ordinal` / unnamed and the RAW streams
          are byte-identical.
  wave 3  the diff is `trivial` (<=4 differing insns, or every diff is
          immediate-only — i.e. exactly the reloc literals this driver
          rebinds).
  wave 0  out of scope for this phase.

Usage
-----
  tools/port_from_ntsc.py scan [--force]
  tools/port_from_ntsc.py status [--waves N,...]
  tools/port_from_ntsc.py tus [--waves N,...]
  tools/port_from_ntsc.py plan <pal_tu>
  tools/port_from_ntsc.py port <pal_tu> [--apply] [--waves 1,2,3]
  tools/port_from_ntsc.py port-all [--apply] [--limit N] [--skip N]
  tools/port_from_ntsc.py ledger
  tools/port_from_ntsc.py revert-func <pal_tu> <func>

Environment: PORT_NTSC_ROOT, PORT_DEBUG_DUMP, PORT_LENIENT, OBJDUMP.
"""
import argparse
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

NTSC_ROOT = Path(os.environ.get("PORT_NTSC_ROOT", "/primary/dev/ico-ntsc"))
CACHE = ROOT / ".port_cache"
CACHE.mkdir(parents=True, exist_ok=True)

TEXT_VMA = 0x100000
TEXT_SZ = 0x189BC4                      # PAL .text
NTSC_TEXT_SZ = 0x16F5D4                 # USA .text
ROM = ROOT / "baserom" / "pal" / "baseelf.rom"
NTSC_ROM = NTSC_ROOT / "baserom" / "baseelf.rom"

TARGET_YAML = ROOT / "config" / "ico.pal.yaml"
NTSC_YAML = NTSC_ROOT / "config" / "ico.us.yaml"
TARGET_SYMS = ROOT / "config" / "symbol_addrs.pal.txt"
NTSC_SYMS = NTSC_ROOT / "config" / "symbol_addrs.us.txt"

LEDGER_PATH = ROOT / "decomp" / "port_ledger_pal.md"

# ntsc source roots (flat retail layout)
NTSC_PROGS = ("src", "ios", "isys", "sound", "ito")


def read_latin1(p):
    return Path(p).read_text(encoding="latin-1")


def write_latin1(p, s):
    Path(p).write_text(s, encoding="latin-1")


def gp_of(ld_path):
    m = re.search(r"_gp\s*=\s*0x([0-9A-Fa-f]+)", read_latin1(ld_path))
    if not m:
        raise SystemExit(f"{ld_path}: no _gp assignment")
    return int(m.group(1), 16)


TARGET_GP = gp_of(ROOT / "config" / "ico.pal.ld")
NTSC_GP = gp_of(NTSC_ROOT / "config" / "ico.us.ld")


# ==========================================================================
# symbol tables
# ==========================================================================
SYM_LINE_RE = re.compile(
    r"^([A-Za-z_]\w*)\s*=\s*0x([0-9A-Fa-f]+)\s*;\s*(?://\s*(.*))?$")


def load_symbols(path):
    """[{name, vma, tu, tag, type}] for every symbol_addrs entry."""
    out = []
    for ln in read_latin1(path).splitlines():
        m = SYM_LINE_RE.match(ln.strip())
        if not m:
            continue
        name, vma_s, comment = m.group(1), m.group(2), m.group(3) or ""
        parts = [p.strip() for p in comment.split("//")]
        tm = re.search(r"type:(\S+)", parts[0] if parts else "")
        rest = [p for p in parts[1:] if p]
        tag = "provisional-ordinal" if any(
            "provisional-ordinal" in c for c in rest) else None
        tu = next((c for c in rest
                   if c != "provisional-ordinal" and not c.startswith("(")), None)
        out.append({
            "name": name, "vma": int(vma_s, 16),
            "tu": tu, "tag": tag,
            "type": tm.group(1) if tm else None,
        })
    return out


def target_defined_labels():
    """Every label the PAL asm tree actually defines (glabel/dlabel/...) plus
    every symbol_addrs entry and every splat undefined-symbol table entry.
    Used to reject a rebound symbol that has no definition on the PAL side
    BEFORE it can break the batch link."""
    labels = set()
    lab_re = re.compile(
        r"^\s*(?:glabel|alabel|dlabel|ehlabel|jlabel|jtbl_label)\s+([A-Za-z_]\w*)")
    for p in (ROOT / "asm").rglob("*.s"):
        for ln in read_latin1(p).splitlines():
            m = lab_re.match(ln)
            if m:
                labels.add(m.group(1))
    for e in load_symbols(TARGET_SYMS):
        labels.add(e["name"])
    for f in sorted(ROOT.glob("config/undefined_*.txt")):
        for ln in read_latin1(f).splitlines():
            m = re.match(r"^\s*([A-Za-z_]\w*)\s*=", ln)
            if m:
                labels.add(m.group(1))
    return labels


# ==========================================================================
# instruction-stream machinery (identical behaviour to port_from_aug6.py)
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
        "src_insns": len(a), "pal_insns": len(r),
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
    m = {}
    for tag, i1, i2, j1, j2 in opcodes:
        if tag == "equal" or (tag == "replace" and (i2 - i1) == (j2 - j1)):
            for k in range(i2 - i1):
                m[i1 + k] = j1 + k
    return m


# ==========================================================================
# splat .s parsing (words + reloc annotations)
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


def parse_splat_s(path):
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


# ==========================================================================
# .text inventories (the link-order backbone)
#
# A yaml `[OFF, asm, NAME]` subsegment has ONE whole-TU `asm/NAME.s`; a
# flipped `[OFF, c, NAME]` one has per-function `.s` under
# asm/{matchings,nonmatchings}/NAME/.  Both shapes are read here, so the
# inventory stays complete and authoritative (it names the 214 PAL functions
# symbol_addrs.pal.txt does not name — splat's own `func_<VMA>`) across
# flips.
# ==========================================================================
SEG_RE = re.compile(r"^(\s+- \[0x)([0-9A-Fa-f]+)(, )(asm|c|hasm|textbin)(, )([^\]#]+)(\].*)$")


def yaml_text_subsegs(path):
    """[(offset, type, name, lineno)] for every .text-ish subsegment."""
    out = []
    for i, ln in enumerate(read_latin1(path).splitlines()):
        m = SEG_RE.match(ln)
        if m and m.group(4) in ("asm", "c"):
            out.append((int(m.group(2), 16), m.group(4), m.group(6).strip(), i))
    return out


GLABEL_RE = re.compile(r"^glabel\s+([A-Za-z_]\w*)")


def glabels_of(path):
    """[(vma, name)] in file order, from a splat .s."""
    out = []
    cur = None
    for ln in read_latin1(path).splitlines():
        m = GLABEL_RE.match(ln)
        if m:
            cur = m.group(1)
            continue
        if cur:
            mi = INSN_RE.match(ln)
            if mi:
                out.append((int(mi.group(1), 16), cur))
                cur = None
    return out


def inventory(root, yaml_path, text_sz):
    """[{vma, end, name, tu}] for every function in .text, VMA-ordered."""
    funcs = []
    for _off, typ, name, _ln in yaml_text_subsegs(yaml_path):
        if typ == "asm":
            p = root / "asm" / (name + ".s")
            if not p.exists():
                raise SystemExit(f"inventory: missing {p} — run tools/build.sh setup")
            for vma, n in glabels_of(p):
                funcs.append({"vma": vma, "name": n, "tu": name})
        else:
            got = []
            for sub in ("matchings", "nonmatchings"):
                d = root / "asm" / sub / name
                if d.is_dir():
                    for f in sorted(d.glob("*.s")):
                        g = glabels_of(f)
                        if g:
                            got.append({"vma": g[0][0], "name": g[0][1], "tu": name})
            if not got:
                raise SystemExit(f"inventory: no .s for flipped TU {name}")
            funcs += got
    funcs.sort(key=lambda f: f["vma"])
    end = TEXT_VMA + text_sz
    for i, f in enumerate(funcs):
        f["end"] = funcs[i + 1]["vma"] if i + 1 < len(funcs) else end
    return funcs


def words_of(blob, vma, end):
    off = vma - TEXT_VMA
    n = (end - vma) // 4
    if n <= 0 or off < 0 or off + 4 * n > len(blob):
        return []
    return trim(list(struct.unpack(f"<{n}I", blob[off:off + 4 * n])))


# ==========================================================================
# twin correlation (the by-hash join)
# ==========================================================================
PLACEHOLDER_RE = re.compile(r"^func_[0-9A-Fa-f]{8}$")


def _lis(seq):
    """Indices of a longest strictly-increasing subsequence of `seq`."""
    import bisect
    tails, tails_idx, prev = [], [], [-1] * len(seq)
    for k, v in enumerate(seq):
        j = bisect.bisect_left(tails, v)
        if j:
            prev[k] = tails_idx[j - 1]
        if j == len(tails):
            tails.append(v)
            tails_idx.append(k)
        else:
            tails[j] = v
            tails_idx[j] = k
    out = []
    k = tails_idx[-1] if tails_idx else -1
    while k >= 0:
        out.append(k)
        k = prev[k]
    return out[::-1]


def correlate(pal_funcs, us_funcs, pal_blob, us_blob):
    """Pair PAL and US functions under the link-order constraint.

    NAMES CANNOT ANCHOR THIS.  Measured on the two trees as they stand
    (2026-09-04): of the 2525 function names present on both sides, only 29
    have equal reloc-normalized streams and only 115 even have the same
    instruction count.  Spot-checked, the ntsc side is the wrong one — e.g.
    ntsc `MatrixDrive_PopMatrix` is a 59-instruction vector-angle routine
    while PAL's is the 4-instruction stack pop the name describes — because
    a large share of the US names are ordinal guesses.  Anchoring on names
    would therefore mis-bind almost every function.

    A raw `difflib` alignment of the two hash SEQUENCES is not sufficient
    either: normalization blanks every reloc field, so whole families of
    one-line accessor wrappers collapse onto a single hash and the matcher
    locks a long "equal" run onto a shifted position inside the family.

    So the skeleton is CONTENT, made unambiguous: a hash occurring exactly
    once on each side identifies its function uniquely, and those anchors
    (2462 of them, after reduction to a longest increasing subsequence so
    they are monotone in link order) pin the alignment.  `difflib` then only
    has to fill the gaps between consecutive anchors, where every pair it
    emits is still hash-EQUAL — so even an ambiguous pick inside a family of
    identical streams selects a body that compiles to the same code modulo
    the symbols the reloc walk rebinds anyway."""
    for f in pal_funcs:
        f["_w"] = words_of(pal_blob, f["vma"], f["end"])
        f["_h"] = norm_hash(f["_w"]) if f["_w"] else "empty"
    for f in us_funcs:
        f["_w"] = words_of(us_blob, f["vma"], f["end"])
        f["_h"] = norm_hash(f["_w"]) if f["_w"] else "empty"

    pc, uc = defaultdict(int), defaultdict(int)
    for f in pal_funcs:
        pc[f["_h"]] += 1
    for f in us_funcs:
        uc[f["_h"]] += 1
    ui = {}
    for i, f in enumerate(us_funcs):
        ui.setdefault(f["_h"], i)
    cand = [(i, ui[f["_h"]]) for i, f in enumerate(pal_funcs)
            if pc[f["_h"]] == 1 and uc.get(f["_h"]) == 1]
    keep = _lis([j for _i, j in cand])
    anchors = [cand[k] for k in keep]

    pairs = [(pal_funcs[i], us_funcs[j], "anchor") for i, j in anchors]
    bounds = [(-1, -1)] + anchors + [(len(pal_funcs), len(us_funcs))]
    for (pi0, uj0), (pi1, uj1) in zip(bounds, bounds[1:]):
        i1, i2 = pi0 + 1, pi1
        j1, j2 = uj0 + 1, uj1
        if i2 <= i1 or j2 <= j1:
            continue
        a = [f["_h"] for f in pal_funcs[i1:i2]]
        b = [f["_h"] for f in us_funcs[j1:j2]]
        sm = difflib.SequenceMatcher(a=a, b=b, autojunk=False)
        for tag, x1, x2, y1, y2 in sm.get_opcodes():
            if tag == "equal":
                for k in range(x2 - x1):
                    pairs.append((pal_funcs[i1 + x1 + k],
                                  us_funcs[j1 + y1 + k], "gap"))
            elif tag == "replace" and (x2 - x1) == (y2 - y1):
                # equal-length substitution inside a gap: the two links have
                # the same function at the same ordinal with a DIFFERENT
                # stream. Not a twin, but the right pairing for the wave-2/3
                # "raw identical / trivial" buckets, which exist precisely to
                # catch a body whose only divergence is the reloc literals
                # this driver rebinds.
                for k in range(x2 - x1):
                    pairs.append((pal_funcs[i1 + x1 + k],
                                  us_funcs[j1 + y1 + k], "ordinal"))
    pairs.sort(key=lambda t: t[0]["vma"])
    return pairs


def ntsc_matchings_index():
    """func -> {vma, file, stem} for every ntsc per-function matched baseline.
    `stem` is the flat repo path of the source TU (`src/pool`, `ios/cdvd`)."""
    idx = {}
    root = NTSC_ROOT / "asm" / "matchings"
    for p in root.rglob("*.s"):
        stem = str(p.relative_to(root)).rsplit("/", 1)[0]
        for name, rec in parse_splat_s(p).items():
            if not rec["insns"]:
                continue
            idx[name] = {
                "vma": rec["vma"],
                "file": str(p.relative_to(NTSC_ROOT)),
                "stem": stem,
            }
    return idx


# ==========================================================================
# ntsc file-scope handwritten-asm blocks (the VU0/MMI/COP0 exception)
# ==========================================================================
ASM_BLOCK_RE = re.compile(
    r"(?m)^(?:__asm__|asm)(?:\s+(?:__volatile__|volatile))?\s*\(")


def _scan_asm_block(raw, i):
    depth = 0
    parts = []
    j = i
    n = len(raw)
    while j < n:
        c = raw[j]
        if c == '"':
            k = j + 1
            buf = []
            while k < n and raw[k] != '"':
                if raw[k] == "\\" and k + 1 < n:
                    esc = raw[k + 1]
                    buf.append({"n": "\n", "t": "\t", "\\": "\\",
                                '"': '"', "r": "\r", "0": "\0"}.get(esc, esc))
                    k += 2
                    continue
                buf.append(raw[k])
                k += 1
            parts.append("".join(buf))
            j = k + 1
            continue
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return j, "".join(parts)
        j += 1
    raise ValueError("unterminated __asm__ block")


def asm_block_index(raw):
    """name -> {'asm': assembler text, 'names': every symbol it defines}."""
    idx = {}
    for m in ASM_BLOCK_RE.finditer(raw):
        i = raw.index("(", m.start())
        try:
            _, asm = _scan_asm_block(raw, i)
        except ValueError:
            continue
        if ".include" in asm:
            continue                    # an INCLUDE_ASM expansion, not a body
        names = set(re.findall(r"^\s*glabel\s+([A-Za-z_]\w*)", asm, re.M))
        for n in re.findall(r"^\s*\.globa?l\s+([A-Za-z_]\w*)", asm, re.M):
            if (re.search(r"^\s*" + re.escape(n) + r"\s*:", asm, re.M)
                    and re.search(r"^\s*\.type\s+" + re.escape(n)
                                  + r"\s*,\s*@function", asm, re.M)):
                names.add(n)
        if not names:
            continue
        rec = {"asm": asm, "names": sorted(names)}
        for n in names:
            idx[n] = rec
    return idx


_DIRECTIVE_RE = re.compile(r"^\s*\.")
_LABEL_RE = re.compile(r"^\s*(?:\d+|[A-Za-z_.$][\w.$]*)\s*:")


def split_asm_body(asm, name):
    lines = asm.split("\n")
    start = end = None
    for i, ln in enumerate(lines):
        if re.match(r"^\s*glabel\s+" + re.escape(name) + r"\s*$", ln):
            start = i
        elif re.match(r"^\s*" + re.escape(name) + r"\s*:\s*$", ln):
            start = i if start is None else start
        elif re.match(r"^\s*endlabel\s+" + re.escape(name) + r"\s*$", ln):
            end = i
        elif re.match(r"^\s*\.size\s+" + re.escape(name) + r"\s*,", ln):
            end = i if end is None else end
    if start is None or end is None or end <= start:
        raise ValueError(f"cannot delimit {name} in its __asm__ block")
    pro = [l for l in lines[:start] if _DIRECTIVE_RE.match(l)]
    epi = [l for l in lines[end + 1:] if _DIRECTIVE_RE.match(l)]
    body = [l for l in lines[start:end + 1] if l.strip()]
    n_insn = sum(1 for l in body[1:-1]
                 if l.strip() and not _LABEL_RE.match(l)
                 and (not _DIRECTIVE_RE.match(l) or l.strip().startswith(".word")))
    return pro, body, epi, n_insn


def target_asm_shape(stem, name):
    """(insns inside glabel..endlabel, insns after endlabel) for the PAL splat
    baseline — the boundary quick_diff slices on."""
    # After a re-splat the baseline of an already-ported function moves from
    # nonmatchings/ to matchings/ — check both, or every size check silently
    # no-ops on the second pass.
    for sub in ("nonmatchings", "matchings"):
        p = ROOT / "asm" / sub / stem / (name + ".s")
        if p.exists():
            break
    else:
        return None
    inside = after = 0
    state = 0
    for ln in read_latin1(p).splitlines():
        if re.match(r"^\s*glabel\s+" + re.escape(name) + r"\s*$", ln):
            state = 1
            continue
        if re.match(r"^\s*endlabel\s+" + re.escape(name) + r"\s*$", ln):
            state = 2
            continue
        if not INSN_RE.match(ln):
            continue
        if state == 1:
            inside += 1
        elif state == 2:
            after += 1
    return inside, after


def render_asm_block(pro, body, epi, pad, vma=0):
    pro = [l for l in pro if not re.match(r"^\s*\.align\b", l)]
    # The alignment is a property of THIS link's address, not of the ntsc
    # block's: PAL puts several of these leaves at a 4-mod-8 address
    # (func_00265AE4), where an inherited `.align 3` inserts a pad word the
    # ROM does not have and silently lengthens the object by 4.
    pro.append("    .align 3" if vma % 8 == 0 else "    .align 2")
    lines = pro + list(body) + ["    nop"] * pad + list(epi)
    out = ["__asm__("]
    for ln in lines:
        if not ln.strip():
            continue
        esc = (ln.replace("\\", "\\\\").replace('"', '\\"')
                 .replace("\t", "\\t"))
        out.append('    "%s\\n"' % esc)
    out.append(");")
    return "\n".join(out)


# ==========================================================================
# scan
# ==========================================================================
def cmd_scan(args):
    out_f = CACHE / "candidates.json"
    if out_f.exists() and not args.force:
        print(f"scan: {out_f} exists (use --force to rebuild)")
        return json.loads(out_f.read_text())

    pal_blob = ROM.read_bytes()
    us_blob = NTSC_ROM.read_bytes()
    pal_funcs = inventory(ROOT, TARGET_YAML, TEXT_SZ)
    us_funcs = inventory(NTSC_ROOT, NTSC_YAML, NTSC_TEXT_SZ)
    print(f"pal .text functions: {len(pal_funcs)}", file=sys.stderr)
    print(f"us  .text functions: {len(us_funcs)}", file=sys.stderr)

    ntsc = ntsc_matchings_index()
    src = NtscSource()
    stale = []
    for n, a in ntsc.items():
        atu = src.tu(a["stem"])
        if n not in atu["funcs"] and n not in atu["asm_funcs"]:
            stale.append(n)
    for n in stale:
        del ntsc[n]
    print(f"ntsc matched bodies: {len(ntsc)} "
          f"({len(stale)} stale matchings/*.s dropped)", file=sys.stderr)

    # --- twin correlation -------------------------------------------------
    pairs = correlate(pal_funcs, us_funcs, pal_blob, us_blob)
    twins = [{"pal_name": p["name"], "pal_vma": p["vma"], "pal_tu": p["tu"],
              "us_name": u["name"], "us_vma": u["vma"], "us_tu": u["tu"],
              "via": how, "norm_equal": p["_h"] == u["_h"],
              "us_matched": u["name"] in ntsc}
             for p, u, how in pairs]
    via = defaultdict(int)
    for t in twins:
        via[t["via"]] += 1
    (CACHE / "ntsc_pal_twins.json").write_text(json.dumps(
        {"pal_functions": len(pal_funcs), "us_functions": len(us_funcs),
         "pairs": len(twins), "via": dict(via),
         "name_agreement": sum(1 for t in twins
                               if t["pal_name"] == t["us_name"]),
         "twins": twins}, indent=1))

    # `.port_cache/name_alias.json` is the alias mechanism the port loop
    # consumes ({pal_name: us_name}).  It is REGENERATED here rather than
    # merged with whatever is on disk: this working tree still carries the
    # US-era aug6 alias file, whose right-hand side names aug6 symbols and
    # would silently mis-bind.  Hand entries go in name_alias_manual.json.
    alias_f = CACHE / "name_alias.json"
    manual_f = CACHE / "name_alias_manual.json"
    manual = json.loads(manual_f.read_text()) if manual_f.exists() else {}
    alias = {}
    for t in twins:
        if t["pal_name"] == t["us_name"] or not t["us_matched"]:
            continue
        alias.setdefault(t["pal_name"], t["us_name"])
    alias.update(manual)      # a hand entry always wins
    alias_f.write_text(json.dumps(alias, indent=1, sort_keys=True))
    print(f"twin pairs: {len(twins)} {dict(via)}  "
          f"name agreement {sum(1 for t in twins if t['pal_name'] == t['us_name'])}"
          f"  aliases: {len(alias)} ({len(manual)} hand)", file=sys.stderr)

    # --- PAL symbol tiers -------------------------------------------------
    tier = {}
    for e in load_symbols(TARGET_SYMS):
        if e["type"] == "func":
            tier[e["name"]] = e["tag"]

    # The join is the correlation table, keyed by PAL VMA — NOT a blind
    # name lookup.  A name fallback would mis-bind: see correlate().
    join = {}
    for t, (_p, _u, how) in zip(twins, pairs):
        if t["us_matched"]:
            join[t["pal_vma"]] = (t["us_name"], how)
    for pal_name, us_name in manual.items():
        for f in pal_funcs:
            if f["name"] == pal_name and us_name in ntsc:
                join[f["vma"]] = (us_name, "manual")

    records = []
    for f in pal_funcs:
        name = f["name"]
        got = join.get(f["vma"])
        if got is None:
            continue
        uname, via_kind = got
        a = ntsc.get(uname)
        if a is None:
            continue
        srec = parse_splat_s(NTSC_ROOT / a["file"])[uname]
        a_words = trim([w for w, _, _ in srec["insns"]])
        r_words = f["_w"]
        if not a_words or not r_words:
            continue
        res = analyze(a_words, r_words)
        res.pop("opcodes")
        verdict = verdict_of(res)
        norm_eq = (len(a_words) == len(r_words)
                   and norm_hash(a_words) == norm_hash(r_words))
        jtbl = any(k in ("hi", "lo") and s and s.startswith("jtbl_")
                   for _, k, s in srec["insns"])
        named = not PLACEHOLDER_RE.match(name)
        tag = tier.get(name, "provisional-ordinal" if not named else None)

        # Wave 1 is the unambiguous-twin population.  The aug6 driver keys it
        # off a NAMED, untagged target symbol; here the name carries no such
        # weight (correlate() documents the measurement), so the anchor is
        # the globally-unique normalized stream instead.
        if norm_eq and via_kind == "anchor":
            wave = 1
        elif norm_eq or res["diff_count"] == 0:
            wave = 2
        elif verdict == "trivial":
            wave = 3
        else:
            wave = 0

        records.append({
            "name": name, "us_name": uname, "via": via_kind,
            "pal_vma": f["vma"], "pal_end": f["end"], "pal_tu": f["tu"],
            "tag": tag,
            "us_vma": a["vma"], "us_file": a["file"], "us_stem": a["stem"],
            "norm_equal": norm_eq, "verdict": verdict, "wave": wave,
            "jtbl": jtbl,
            **res,
        })

    hist = defaultdict(int)
    for r in records:
        hist[r["wave"]] += 1
    out = {
        "ntsc_root": str(NTSC_ROOT),
        "ntsc_head": subprocess.run(
            ["git", "-C", str(NTSC_ROOT), "rev-parse", "HEAD"],
            capture_output=True, text=True).stdout.strip(),
        "ntsc_matched_bodies": len(ntsc),
        "pal_functions": len(pal_funcs),
        "twin_pairs": len(twins),
        "joined": len(records),
        "wave_histogram": {str(k): v for k, v in sorted(hist.items())},
        "records": sorted(records, key=lambda r: (r["wave"], r["pal_vma"])),
    }
    out_f.write_text(json.dumps(out, indent=1))
    print(f"joined: {len(records)}", file=sys.stderr)
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


_CONST_SYMS = None


def target_const_syms():
    global _CONST_SYMS
    if _CONST_SYMS is None:
        d = {}
        for f in sorted(ROOT.glob("config/undefined_*.txt")):
            for ln in read_latin1(f).splitlines():
                m = re.match(r"^\s*([A-Za-z_]\w*)\s*=\s*(0[xX][0-9A-Fa-f]+|\d+)", ln)
                if m:
                    d[m.group(1)] = int(m.group(2), 0)
        _CONST_SYMS = d
    return _CONST_SYMS


def build_symbol_map(rec, pal_a2n, pal_func_vmas, defined, local_defs=()):
    """ntsc symbol name -> PAL symbol name, derived slot-by-slot."""
    srec = parse_splat_s(NTSC_ROOT / rec["us_file"])[rec["us_name"]]
    insns = srec["insns"]
    a_words = trim([w for w, _, _ in insns])
    blob = ROM.read_bytes()
    r_words = words_of(blob, rec["pal_vma"], rec["pal_end"])

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
            unresolved.append((i, sym, "no aligned pal slot"))
            continue
        rw = r_words[j]
        rop = (rw >> 26) & 0x3F
        addr = None
        if kind in ("jal", "j"):
            if rop not in (2, 3):
                unresolved.append((i, sym, f"pal slot is not j/jal (op {rop:#x})"))
                continue
            addr = (rw & 0x3FFFFFF) << 2
        elif kind == "gp":
            if ((rw >> 21) & 0x1F) != 28:
                unresolved.append((i, sym, "pal slot is not $gp-based"))
                continue
            addr = TARGET_GP + sx16(rw & 0xFFFF)
        elif kind == "lo":
            addr = resolve_hi_partner(r_words, j)
            if addr is None:
                cm = re.match(r"^D_([0-9A-Fa-f]+)$", sym or "")
                if (cm and r_words[j] == a_words[i]
                        and target_const_syms().get(sym) == int(cm.group(1), 16)):
                    mapping.setdefault(sym, sym)
                    continue
                unresolved.append((i, sym, "no pal lui partner for %lo"))
                continue
        if addr is None:
            continue

        rname = pal_a2n.get(addr)
        if rname is None:
            if kind in ("jal", "j") or addr in pal_func_vmas:
                rname = "func_%08X" % addr
            elif sym.startswith("jtbl_") and ("jtbl_%08X" % addr) in defined:
                rname = "jtbl_%08X" % addr
            else:
                rname = "D_%08X" % addr
        if rname not in defined and sym not in local_defs:
            if ("D_%X" % addr) in defined:
                rname = "D_%X" % addr
            else:
                got = None
                am = re.match(r"^func_([0-9A-Fa-f]{8})$", sym)
                a_addr = (resolve_hi_partner(a_words, i) if kind == "lo"
                          else None)
                if am and a_addr is not None:
                    aoff = a_addr - int(am.group(1), 16)
                    cand = "func_%08X" % (addr - aoff)
                    if 0 < aoff < 0x1000 and cand in defined:
                        got = cand
                if got is None:
                    unresolved.append(
                        (i, sym, f"pal symbol {rname} (0x{addr:08X}) undefined"))
                    continue
                rname = got
        prev = mapping.get(sym)
        if prev is not None and prev != rname:
            unresolved.append((i, sym, f"binds to both {prev} and {rname}"))
            continue
        mapping[sym] = rname

    if unresolved:
        if os.environ.get("PORT_LENIENT"):
            for i, sym, why in unresolved:
                print(f"    [lenient] insn {i} `{sym}`: {why}", file=sys.stderr)
            return mapping
        i, sym, why = unresolved[0]
        raise Unresolved(f"insn {i} `{sym}`: {why}"
                         + (f" (+{len(unresolved) - 1} more)" if len(unresolved) > 1 else ""))
    return mapping


# ==========================================================================
# ntsc source side
# ==========================================================================
KEYWORDS = {
    "if", "else", "for", "while", "do", "switch", "case", "default", "break",
    "continue", "return", "goto", "sizeof", "typedef", "struct", "union",
    "enum", "static", "extern", "const", "volatile", "register", "signed",
    "unsigned", "char", "short", "int", "long", "float", "double", "void",
    "inline", "asm", "__asm__", "__attribute__", "restrict", "auto",
}


class NtscSource:
    """Lazily-parsed view of the ntsc tree (bodies, decls, typedefs)."""

    def __init__(self):
        self._tus = {}
        self._global_decls = None
        self._global_sigs = None
        self._syms = None

    def tu(self, stem):
        if stem not in self._tus:
            path = NTSC_ROOT / (stem + ".c")
            raw = read_latin1(path) if path.exists() else ""
            funcs, incasm = T.extract_functions_from_file(stem + ".c", raw)
            self._tus[stem] = {
                "path": path, "raw": raw,
                "funcs": {f["name"]: f for f in funcs},
                "asm_funcs": asm_block_index(raw),
                "include_asm": incasm,
                "decls": {**T.build_decl_index([(stem + ".c", raw)]),
                          **decl_index(stem + ".c", raw)},
                "typedefs": typedef_index(stem + ".c", raw),
                "includes": re.findall(r'^#include\s+"[^"]+"', raw, re.M),
            }
        return self._tus[stem]

    def _all_texts(self):
        for prog in NTSC_PROGS:
            d = NTSC_ROOT / prog
            if not d.is_dir():
                continue
            for p in sorted(d.rglob("*.c")):
                yield str(p.relative_to(NTSC_ROOT)), read_latin1(p)

    @property
    def global_decls(self):
        if self._global_decls is None:
            f = CACHE / "ntsc_decls.json"
            if f.exists():
                self._global_decls = json.loads(f.read_text())
            else:
                texts = list(self._all_texts())
                d = T.build_decl_index(texts)
                for rel, raw in texts:
                    for k, v in decl_index(rel, raw).items():
                        d.setdefault(k, v)
                self._global_decls = d
                f.write_text(json.dumps(d, ensure_ascii=False))
        return self._global_decls

    @property
    def global_sigs(self):
        if self._global_sigs is None:
            f = CACHE / "ntsc_sigs.json"
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
    def syms(self):
        """Names the ntsc link resolves as real (addressable) symbols."""
        if self._syms is None:
            names = set()
            for ln in read_latin1(NTSC_SYMS).splitlines():
                m = SYM_LINE_RE.match(ln.strip())
                if m:
                    names.add(m.group(1))
            self._syms = names
        return self._syms


def rebind_text(text, mapping):
    if not mapping:
        return text
    rx = re.compile(r"\b(" + "|".join(
        re.escape(k) for k in sorted(mapping, key=len, reverse=True)) + r")\b")
    return rx.sub(lambda m: mapping[m.group(1)], text)


STR_LITERAL_RE = re.compile(r'"(?:[^"\\]|\\.)*"|\'(?:[^\'\\]|\\.)*\'')


def rebind_code_only(text, mapping):
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


MACRO_CALL_RE = re.compile(r"\b[A-Z][A-Z0-9_]{3,}\s*\(")


def _plausible_decl(decl):
    """Is this really ONE declaration, and not a run of macro invocations the
    statement splitter glued together?"""
    if len(decl) > 400:
        return False
    if MACRO_CALL_RE.search(decl):
        return False
    if "{" in decl or "}" in decl:
        return False
    return True


def synth_extern(src, us_name, pal_name, stem, body):
    """extern declaration for `pal_name`, typed the way the ntsc source types
    its US counterpart (that typing IS part of the matching shape)."""
    tu = src.tu(stem)
    decl = tu["decls"].get(us_name) or src.global_decls.get(us_name)
    if decl and not _plausible_decl(decl):
        # The ntsc statement scanner glues a file-scope MACRO INVOCATION run
        # onto the following declaration, because a macro call carries no `;`
        # of its own: `SYSCALL_WRAPPER(a,1) SYSCALL_WRAPPER(b,2) ... void
        # setup(int,int);` comes back as one "extern".  Splicing that emits
        # 111 real function DEFINITIONS (measured: +1776 bytes in
        # src/cod/vendor_100110) that no per-function diff can see.
        decl = None
    if decl:
        decl = decl.strip()
        if not decl.endswith(";"):
            decl += ";"
        decl = re.sub(r'__asm__\s*\(\s*"[^"]*"\s*\)', "", decl)
        decl = re.sub(r"\b%s\b" % re.escape(us_name), pal_name, decl)
        decl = re.sub(r"\s+", " ", decl).replace(" ;", ";")
        if decl.startswith("typedef"):
            decl = None
        else:
            if re.search(r"\(\s*\*", decl):
                return decl          # function/array POINTER — never reshape
            if "(" in decl and ")" in decl:
                dargc = T.param_count_from_sig(decl, pal_name)
                cargc = T.call_arg_count(body, pal_name)
                if dargc is None or cargc is None or dargc == cargc:
                    return decl
                return unprototyped(decl, pal_name) or decl
            return decl
    sig = src.global_sigs.get(us_name)
    if sig and not _plausible_decl(sig):
        sig = None
    if sig:
        sig = re.sub(r"\b%s\b" % re.escape(us_name), pal_name, sig)
        sig = re.sub(r"^static\s+", "", sig)
        dargc = T.param_count_from_sig(sig, pal_name)
        cargc = T.call_arg_count(body, pal_name)
        if dargc is not None and cargc is not None and dargc == cargc:
            return f"extern {sig};"
        return unprototyped(sig, pal_name) or f"extern {sig};"
    if pal_name.startswith("func_") or re.search(
            r"\b%s\s*\(" % re.escape(pal_name), body):
        used = T.call_result_probably_used(body, pal_name)
        return f"extern {'int' if used else 'void'} {pal_name}();"
    if re.search(r"\b%s\s*\[" % re.escape(pal_name), body):
        return f"extern int {pal_name}[];"
    return f"extern int {pal_name};"


def _decl_shape(decl):
    s = ASM_LABEL_RE.sub("", decl)
    s = re.sub(r"\bextern\b|\bstatic\b|\bconst\b|\bregister\b", " ", s)
    s = re.sub(r"([A-Za-z_]\w*)\s*(?=[,)])", " ", s)   # parameter names
    s = re.sub(r"[^\w*\[\]().,;]+", " ", s)
    return re.sub(r"\s+", "", s)


def conflicting_decl_alias(tok, pal_decls, want):
    """The PAL TU already has `tok` in scope with a DIFFERENT type than the
    ntsc body assumes. Bind a fresh identifier to the same linker symbol via
    the dev tree's own `__asm__("REALNAME")` idiom."""
    have = pal_decls.get(tok)
    if have is None or want is None:
        return None
    if _decl_shape(have) == _decl_shape(re.sub(r"\bextern\b", "", want)):
        return None
    alias = tok + "__pn"
    body = want.rstrip().rstrip(";")
    body = ASM_LABEL_RE.sub("", body).rstrip()
    body = re.sub(r"\b%s\b" % re.escape(tok), alias, body, count=1)
    if alias not in body:
        return None
    return f'{body} __asm__("{tok}");', alias


_HDR_TYPES = None


def target_header_types():
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
    """`extern char wcf_c[] __asm__("D_004C7CF0");` — a C identifier aliased
    onto a real symbol. Only the __asm__ label is linkable, so rebind THAT."""
    decl = src.tu(stem)["decls"].get(tok) or src.global_decls.get(tok)
    if not decl or not _plausible_decl(decl):
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
    """TU-local (fully inlined, non-addressable) helpers the body calls."""
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
            if tok in src.syms or re.match(r"^func_[0-9A-Fa-f]{8}$", tok):
                continue           # addressable: must have come via a reloc
            seen.add(tok)
            out.append(fn["text"])
            frontier.append(fn["text"])
    return out


# ==========================================================================
# PAL TU scaffolding + yaml flipping
# ==========================================================================
def target_tu_path(tu):
    return ROOT / (tu if tu.endswith(".c") else tu + ".c")


def tu_stem(tu):
    return tu[:-2] if tu.endswith(".c") else tu


def yaml_flip(tu, to_type):
    """Flip `[OFF, asm, NAME]` <-> `[OFF, c, NAME]` in config/ico.pal.yaml,
    keeping the trailing comment. Returns True if the line changed."""
    lines = read_latin1(TARGET_YAML).splitlines(keepends=True)
    changed = False
    for i, ln in enumerate(lines):
        m = SEG_RE.match(ln.rstrip("\n"))
        if not m or m.group(6).strip() != tu:
            continue
        if m.group(4) == to_type:
            return False
        nl = "\n" if ln.endswith("\n") else ""
        lines[i] = (m.group(1) + m.group(2) + m.group(3) + to_type
                    + m.group(5) + m.group(6) + m.group(7) + nl)
        changed = True
        break
    if changed:
        write_latin1(TARGET_YAML, "".join(lines))
    return changed


def tu_functions(tu):
    """[(vma, name)] for every function of one PAL .text subsegment, in VMA
    order — read from the whole-TU splat `.s` (still `asm`) or from the
    per-function baselines (already flipped to `c`)."""
    p = ROOT / "asm" / (tu + ".s")
    if p.exists():
        return glabels_of(p)
    got = []
    for sub in ("matchings", "nonmatchings"):
        d = ROOT / "asm" / sub / tu
        if d.is_dir():
            for f in sorted(d.glob("*.s")):
                g = glabels_of(f)
                if g:
                    got.append(g[0])
    got.sort()
    return got


SCAFFOLD_HEADER = '#include "common.h"\n\n'


def ensure_scaffold(tu, apply=True):
    """Create `<tu>.c` as an INCLUDE_ASM scaffold over the whole PAL span and
    flip the yaml line to `c`. Returns (created, flipped)."""
    path = target_tu_path(tu)
    funcs = tu_functions(tu)
    created = flipped = False
    if not funcs:
        raise SystemExit(f"ensure_scaffold: no functions found for {tu}")
    if not path.exists():
        body = "".join('INCLUDE_ASM("asm/nonmatchings/%s", %s);\n' % (tu, n)
                       for _v, n in funcs)
        if apply:
            path.parent.mkdir(parents=True, exist_ok=True)
            write_latin1(path, SCAFFOLD_HEADER + body)
        created = True
    if apply:
        flipped = yaml_flip(tu, "c")
    return created, flipped


def unscaffold(tu):
    """Undo ensure_scaffold for a TU that ported nothing: drop the file (only
    if it is still a pure INCLUDE_ASM scaffold) and flip the yaml back."""
    path = target_tu_path(tu)
    if path.exists():
        txt = read_latin1(path)
        stripped = T.INCLUDE_ASM_RE.sub("", txt)
        stripped = re.sub(r'#include\s+"[^"]+"', "", stripped)
        if stripped.strip():
            return False               # somebody put real C in it — keep it
        path.unlink()
    yaml_flip(tu, "asm")
    return True


def build_setup(timeout=1200):
    """`tools/build.sh setup` — required after any yaml flip before
    quick_diff can see the new asm/nonmatchings baselines."""
    p = subprocess.run(["bash", "tools/build.sh", "setup"], cwd=ROOT,
                       capture_output=True, text=True, timeout=timeout)
    if p.returncode != 0:
        sys.stderr.write(p.stdout[-4000:] + p.stderr[-4000:])
        raise SystemExit("build.sh setup failed")
    return p


# ==========================================================================
# ntsc data carves (recorded, never translated, in this pass)
# ==========================================================================
CARVE_RE = re.compile(
    r"^\s+- \[0x([0-9A-Fa-f]+), (\.(?:data|rodata|lit4|sdata|bss|sbss)), "
    r"([^\]#]+)\](.*)$")


_CARVES = None


def ntsc_carves():
    """pal/us TU stem -> [carve yaml line text] from ntsc's ico.us.yaml."""
    global _CARVES
    if _CARVES is None:
        d = defaultdict(list)
        for ln in read_latin1(NTSC_YAML).splitlines():
            m = CARVE_RE.match(ln)
            if m:
                d[m.group(3).strip()].append(ln.strip())
        _CARVES = dict(d)
    return _CARVES


# ==========================================================================
# port
# ==========================================================================
def top_insertion_point(text, before):
    at = 0
    for m in re.finditer(r'^[ \t]*#include\s+[<"][^>"]+[>"][^\n]*\n', text, re.M):
        if m.start() < before:
            at = m.end()
    return at


PHASE_HEADER = """
# ntsc -> PAL body port (`tools/port_from_ntsc.py`)

Bodies below were carried over from the `ntsc` (USA retail SCUS-971.13)
checkout's matched clean-room C with every US symbol rebound to its PAL
counterpart by the lockstep reloc-slot walk.  Nothing here was hand-tuned:
each function either reproduced the PAL instruction stream as-is (`PORTED`)
or went straight back to `INCLUDE_ASM` (`REVERTED`, with the first
divergence or compiler diagnostic recorded).  `SKIPPED` = deferred to the
jump-table queue.

Revert-reason classes: `unresolved-symbol` (a reloc slot the walk could not
bind) · `emits-data` (needs a data carve; the TU's US carve entries are
listed under `CARVES`) · `callee-sig-conflict` / `arity` · `undeclared` /
`parse` · `missing-body` · `codegen` (compiles, wrong bytes — a genuine
PAL-vs-USA source difference) · `jtbl`.
"""


def ledger_append(lines):
    txt = LEDGER_PATH.read_text(encoding="utf-8") if LEDGER_PATH.exists() else ""
    LEDGER_PATH.parent.mkdir(parents=True, exist_ok=True)
    with open(LEDGER_PATH, "a", encoding="utf-8") as f:
        if "# ntsc -> PAL body port" not in txt:
            f.write(PHASE_HEADER)
        for ln in lines:
            f.write(ln + "\n")


def candidates_for_tu(cand, tu, waves):
    stem = tu_stem(tu)
    return [r for r in cand["records"]
            if r["wave"] in waves and r["pal_tu"] and tu_stem(r["pal_tu"]) == stem]


def cmd_tus(args):
    cand = load_candidates()
    waves = set(args.waves)
    per = defaultdict(int)
    for r in cand["records"]:
        if r["wave"] in waves and r["pal_tu"]:
            per[tu_stem(r["pal_tu"])] += 1
    for tu, n in sorted(per.items(), key=lambda kv: (-kv[1], kv[0])):
        print(f"{n:5d}  {tu}")
    print(f"# {len(per)} TUs, {sum(per.values())} candidates", file=sys.stderr)


def cmd_plan(args):
    cand = load_candidates()
    rows = candidates_for_tu(cand, args.tu, {1, 2, 3})
    path = target_tu_path(args.tu)
    if path.exists():
        inc = {n for _, _, n in T.parse_include_asm_entries(read_latin1(path))}
    else:
        inc = {n for _v, n in tu_functions(tu_stem(args.tu))}
    todo = [r for r in rows if r["name"] in inc]
    print(f"{args.tu}: {len(rows)} candidates, {len(todo)} still INCLUDE_ASM")
    for r in sorted(todo, key=lambda r: r["wave"]):
        print(f"  w{r['wave']} {r['name']:<40s} <- {r['us_name']:<32s} "
              f"{r['src_insns']:5d} insn dc={r['diff_count']:<4d} {r['verdict']}"
              + ("  [jtbl]" if r["jtbl"] else ""))


def cmd_port(args, shared=None):
    cand = load_candidates()
    waves = set(args.waves)
    rows = candidates_for_tu(cand, args.tu, waves)
    only = set(getattr(args, "only", None) or [])
    if only:
        rows = [r for r in rows if r["name"] in only]
    if not rows:
        print(f"{args.tu}: no candidates in waves {sorted(waves)}")
        return [], [], []

    allow_jtbl = set(getattr(args, "allow_jtbl", None) or [])

    if shared is None:
        shared = PortContext()
    src = shared.src
    pal_a2n = shared.pal_a2n
    pal_func_vmas = shared.pal_func_vmas
    defined = shared.defined

    path = target_tu_path(args.tu)
    stem = tu_stem(args.tu)
    if not path.exists():
        print(f"{args.tu}: no scaffold — run port-all, or `port` after "
              f"ensure_scaffold + build.sh setup", file=sys.stderr)
        return [], [], []
    kept, reverted, skipped = [], [], []
    data_baseline = None

    rows.sort(key=lambda r: (r["wave"], r["pal_vma"]))

    for rec in rows:
        name = rec["name"]
        cur_text = read_latin1(path)
        entries = T.parse_include_asm_entries(cur_text)
        span = next(((s, e) for s, e, n in entries if n == name), None)
        if span is None:
            continue                          # already ported / not in this TU
        if rec["jtbl"] and name not in allow_jtbl:
            skipped.append((rec, "jtbl"))
            continue

        atu = src.tu(rec["us_stem"])
        aname = rec["us_name"]
        fn = atu["funcs"].get(aname)
        ablk = None if fn is not None else atu["asm_funcs"].get(aname)
        if fn is None and ablk is None:
            reverted.append((rec, f"ntsc body not found in {rec['us_stem']}.c"))
            continue

        local_defs = ()
        if ablk is not None:
            local_defs = {l for l in re.findall(r"^\s*([A-Za-z_]\w*)\s*:",
                                                ablk["asm"], re.M)
                          if l != aname}

        try:
            mapping = build_symbol_map(rec, pal_a2n, pal_func_vmas,
                                       defined, local_defs)
        except Unresolved as ex:
            reverted.append((rec, f"unresolved-symbol: {ex}"))
            continue
        except Exception as ex:                # noqa: BLE001 - diagnostic only
            reverted.append((rec, f"map-error: {type(ex).__name__}: {ex}"))
            continue

        # Drop only the SELF binding.  Do NOT also drop `name`: the US names
        # and the PAL names are two independent assignments, so the PAL name
        # of the function being ported is very often the US name of one of
        # its SIBLINGS — and popping it leaves that sibling call unrebound,
        # pointing at the ported function itself.  (Measured: PAL
        # `GetQuaternionFromMatrix` is ntsc `CopyQuaternion`, whose body
        # calls ntsc `GetQuaternionFromMatrix` = PAL
        # `getQuaternionFromMatrix`; three such `jal`s survived quick_diff's
        # in-TU-call tolerance and only the batch SHA caught them.)
        mapping.pop(aname, None)
        if aname != name:
            mapping[aname] = name

        if ablk is not None:
            if len(ablk["names"]) != 1 or ablk["names"][0] != aname:
                reverted.append((rec, "asm-block defines "
                                      f"{ablk['names']} — not a 1:1 body"))
                continue
            atext = rebind_text(ablk["asm"], mapping)
            local_labels = set(re.findall(r"^\s*(\.L\w+)\s*:", atext, re.M))
            if local_labels:
                lrx = re.compile(r"(?<![\w.])(" + "|".join(
                    re.escape(l) for l in sorted(local_labels, key=len,
                                                 reverse=True)) + r")\b")
                atext = lrx.sub(
                    lambda m: ".L%s%s" % (name[-8:], m.group(1)[2:]), atext)
            try:
                pro, ab, epi, n_insn = split_asm_body(atext, name)
            except ValueError as ex:
                reverted.append((rec, f"asm-block: {ex}"))
                continue
            sh = target_asm_shape(stem, name)
            if sh is None:
                reverted.append((rec, "asm-block: no pal baseline .s"))
                continue
            n_body, pad = sh
            while n_insn > n_body and ab[-2].strip() == "nop":
                del ab[-2]
                n_insn -= 1
            if n_insn != n_body:
                reverted.append((rec, f"asm-block: ntsc body is {n_insn} insns, "
                                      f"pal baseline is {n_body}"))
                continue
            body = render_asm_block(pro, ab, epi, pad, rec["pal_vma"])
            candidate = cur_text[:span[0]] + body + cur_text[span[1]:]
            if os.environ.get("PORT_DEBUG_DUMP"):
                Path(os.environ["PORT_DEBUG_DUMP"], f"{name}.c").write_text(
                    candidate, encoding="latin-1")
            if not args.apply:
                print(f"[dry-run] w{rec['wave']} {name}: handwritten-asm body, "
                      f"{len(mapping)} syms")
                kept.append((rec, mapping))
                continue
            if data_baseline is None:
                T.run_quick_diff(stem, name)
                data_baseline = data_bytes(stem)
            write_latin1(path, candidate)
            ok, rc, out, err = verify_port(stem, name, set(mapping.values()))
            if ok:
                grew = data_bytes(stem)
                if (data_baseline is not None and grew is not None
                        and grew > data_baseline):
                    write_latin1(path, cur_text)
                    reverted.append((rec, f"emits-data: +{grew - data_baseline} "
                                          f"bytes of .rodata/.sdata/.lit4"))
                    continue
                kept.append((rec, mapping))
            else:
                write_latin1(path, cur_text)
                reverted.append((rec, failure_reason(rc, out, err)))
            continue

        body = rebind_text(fn["text"], mapping)

        helper_seen = {name, aname}
        helpers = [rebind_text(h, mapping)
                   for h in collect_helpers(src, rec["us_stem"], fn["text"],
                                            mapping, helper_seen)]

        above = re.sub(r"INCLUDE_ASM[^\n]*\n", "", cur_text[:span[0]])
        above = STR_LITERAL_RE.sub('""', above)
        for _fd in reversed(T.extract_functions_from_file(stem + ".c", above)[0]):
            _b = _fd["text"].find("{")
            if _b >= 0:
                _at = above.find(_fd["text"])
                if _at >= 0:
                    above = (above[:_at + _b] + " "
                             * (len(_fd["text"]) - _b) + above[_at + len(_fd["text"]):])
        declared = set(T.IDENT_RE.findall(above))
        top = []

        scan_txt = "\n".join([body] + helpers)
        type_rename = {t: t + "__pn" for t in atu["typedefs"]
                       if t in target_header_types()}

        typedef_blocks = []
        for tname, blk in _needed_typedefs(atu, scan_txt, declared, mapping,
                                           type_rename):
            declared.add(type_rename.get(tname, tname))
            typedef_blocks.append(blk)

        pal_decls = decl_index(stem + ".c", cur_text)
        tu_funcs, _ = T.extract_functions_from_file(stem + ".c", cur_text)
        for fdef in tu_funcs:
            pal_decls.setdefault(
                fdef["name"],
                re.sub(r"\s+", " ", fdef["text"].split("{", 1)[0].strip()) + ";")

        inv = {v: k for k, v in mapping.items()}
        body_alias = {}
        undefined_toks = []
        for tok in sorted(set(T.IDENT_RE.findall(scan_txt))):
            if tok in KEYWORDS or tok == name:
                continue
            # A splat-default name the PAL link cannot resolve.  Checked
            # BEFORE `declared`, because an earlier revert leaves its extern
            # behind in the file and that would otherwise suppress the check.
            # quick_diff cannot see this: the reloc is resolved at link time,
            # not in the object.  (Origin: the ntsc `.s` spells the reference
            # as a raw constant — `lui $3,(0x720000>>16); lw $2,-0x1498($3)`
            # — so the walk never sees a slot to rebind, and the ntsc C names
            # it through a hand-added config/undefined_funcs_extra entry that
            # this tree has no counterpart for.)
            if re.match(r"^(func|D)_[0-9A-Fa-f]{8}$", tok) and tok not in defined:
                undefined_toks.append(tok)
                continue
            a_name = inv.get(tok)
            if a_name is None:
                if tok in declared:
                    continue
                alias = alias_extern(src, tok, rec["us_stem"], mapping)
                if alias:
                    top.append(alias)
                    declared.add(tok)
                    continue
                if not re.match(r"^(func|D)_[0-9A-Fa-f]{8}$", tok):
                    continue
                a_name = tok
            ext = synth_extern(src, a_name, tok, rec["us_stem"], scan_txt)
            if ext and type_rename:
                ext = rebind_text(ext, type_rename)
            got = conflicting_decl_alias(tok, pal_decls, ext)
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

        if undefined_toks:
            reverted.append((rec, "unresolved-symbol: %s undefined on the PAL "
                                  "side (unrebindable raw-constant reference)"
                                  % ", ".join(sorted(undefined_toks))))
            continue

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

        heads = []
        for inc_line in atu["includes"]:
            if inc_line.split('"')[1] == "common.h":
                continue
            if inc_line not in cur_text:
                heads.append(inc_line)

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
            T.run_quick_diff(stem, name)
            data_baseline = data_bytes(stem)

        write_latin1(path, candidate)
        allowed = set(mapping.values())
        ok, rc, out, err = verify_port(stem, name, allowed)
        if ok:
            grew = data_bytes(stem)
            if (name not in allow_jtbl and data_baseline is not None
                    and grew is not None and grew > data_baseline):
                write_latin1(path, cur_text)
                reverted.append((rec, f"emits-data: +{grew - data_baseline} "
                                      f"bytes of .rodata/.sdata/.lit4 "
                                      f"(string or out-of-line float literal; "
                                      f"needs a data carve)"))
                continue
            kept.append((rec, mapping))
        else:
            write_latin1(path, cur_text)
            reverted.append((rec, failure_reason(rc, out, err)))

    if args.apply and kept:
        # Reconcile against EVERY spliced body in the TU, not just this run's
        # — an earlier run's body can be the one making the object the wrong
        # size, and quick_diff never sees that.
        by_name = {r["name"]: r for r in cand["records"]}
        undone = []
        reconcile_tu(stem, spliced_bodies(stem, by_name), undone)
        names = {r["name"] for r, _ in undone}
        kept[:] = [(r, m) for r, m in kept if r["name"] not in names]
        reverted += undone
    print(f"{args.tu}: kept={len(kept)} reverted={len(reverted)} "
          f"skipped={len(skipped)}")
    if args.apply:
        lines = [f"\n### {args.tu}"]
        for rec, mapping in kept:
            lines.append(f"- PORTED `{rec['name']}` w{rec['wave']} @ "
                         f"0x{rec['pal_vma']:08X} <- ntsc {rec['us_stem']}"
                         f":{rec['us_name']} ({len(mapping)} syms rebound)")
        for rec, reason in reverted:
            lines.append(f"- REVERTED `{rec['name']}` w{rec['wave']} @ "
                         f"0x{rec['pal_vma']:08X} — "
                         f"[{classify_reason(reason)}] {reason}")
        for rec, reason in skipped:
            lines.append(f"- SKIPPED `{rec['name']}` w{rec['wave']} @ "
                         f"0x{rec['pal_vma']:08X} — {reason}")
        carves = carve_note(stem, reverted)
        if carves:
            lines.append(carves)
        ledger_append(lines)
    return kept, reverted, skipped


def carve_note(stem, reverted):
    """Record the US carve entries of a TU that had `emits-data` reverts, so
    the carve pass can pick them up without re-deriving them."""
    if not any(classify_reason(r) == "emits-data" for _rec, r in reverted):
        return None
    entries = ntsc_carves().get(stem, [])
    if not entries:
        return f"- CARVES `{stem}` — none in ntsc's ico.us.yaml"
    return ("- CARVES `%s` — %d US carve entr%s to translate:\n%s"
            % (stem, len(entries), "y" if len(entries) == 1 else "ies",
               "\n".join("    - %s" % e for e in entries)))


class PortContext:
    """Indices shared by every TU in a port-all run (each is seconds to
    build, and rebuilding per TU dominates the runtime)."""

    def __init__(self):
        self.src = NtscSource()
        syms = load_symbols(TARGET_SYMS)
        self.pal_a2n = {}
        for e in syms:
            self.pal_a2n.setdefault(e["vma"], e["name"])
        self.pal_func_vmas = set(e["vma"] for e in syms if e["type"] == "func")
        for f in inventory(ROOT, TARGET_YAML, TEXT_SZ):
            self.pal_func_vmas.add(f["vma"])
            self.pal_a2n.setdefault(f["vma"], f["name"])
        self.defined = target_defined_labels()


BRACKET_SYM_RE = re.compile(r"<([A-Za-z_][\w.]*)(?:\+0x[0-9a-f]+)?>")


def _tolerable_pair(built, expected, allowed):
    mb = T.BRANCH_TARGET_RE.match(built)
    me = T.BRANCH_TARGET_RE.match(expected)
    if not mb or not me:
        return False
    if mb.group(1) != me.group(1):
        return False
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

    This pass carves no data: a string literal or an out-of-line float
    constant in a ported body would be NEW bytes appended to
    .sdata/.rodata/.lit4, shifting the whole data layout and every %hi/%lo
    and $gp-relative reference in the game — while passing the per-function
    instruction diff cleanly. The port may add code, never data."""
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


def text_bytes(stem):
    """Total .text* bytes in the TU object quick_diff just built."""
    o = ROOT / "build" / "quick_diff" / (stem + ".o")
    if not o.exists():
        return None
    p = subprocess.run([OBJDUMP, "-h", str(o)], capture_output=True, text=True)
    total = 0
    for ln in p.stdout.splitlines():
        m = re.match(r"\s*\d+\s+(\S+)\s+([0-9a-f]+)", ln)
        if m and m.group(1).startswith(".text"):
            total += int(m.group(2), 16)
    return total


def object_func_sizes(stem):
    """symbol -> size, for every FUNC symbol of the built TU object."""
    o = ROOT / "build" / "quick_diff" / (stem + ".o")
    if not o.exists():
        return {}
    p = subprocess.run([OBJDUMP, "-t", str(o)], capture_output=True, text=True)
    out = {}
    for ln in p.stdout.splitlines():
        if "\t" not in ln or " F " not in ln:
            continue
        rhs = ln.split("\t", 1)[1].split()
        if len(rhs) >= 2:
            try:
                out[rhs[1]] = int(rhs[0], 16)
            except ValueError:
                pass
    return out


_SPANS = None


def tu_span_size(tu):
    """Byte size of one PAL .text subsegment, from the yaml."""
    global _SPANS
    if _SPANS is None:
        rows = []
        for ln in read_latin1(TARGET_YAML).splitlines():
            m = SEG_RE.match(ln)
            if m:
                rows.append((int(m.group(2), 16), m.group(6).strip()))
        rows.sort()
        _SPANS = {}
        _SPAN_OFF.clear()
        for i, (off, name) in enumerate(rows):
            end = rows[i + 1][0] if i + 1 < len(rows) else TEXT_SZ
            _SPANS[name] = end - off
            _SPAN_OFF[name] = off
    return _SPANS.get(tu)


_SPAN_OFF: dict = {}


def span_tail_is_zero_pad(tu, got, exp):
    """True when an object that is `got` bytes long still lays out the
    `exp`-byte span exactly: the shortfall is under one 8-byte alignment
    unit, the next input section's 8-byte alignment therefore places it at
    the span end, and the ROM bytes in that tail are zero — i.e. the
    trailing `nop` pad that ld's zero fill reproduces.  Measured on
    MapCollisionData / src/fieldCollision (0x41AC vs 0x41B0): the full SHA
    gate is byte-identical.  Only that case is a false negative of the
    size check; a shortfall of >= 8, a surplus, or non-zero ROM tail bytes
    still mean the object really differs."""
    tu_span_size(tu)
    off = _SPAN_OFF.get(tu)
    if off is None or got >= exp or exp - got >= 8:
        return False
    if (got + 7) // 8 * 8 != exp and exp % 8 == 0:
        return False
    tail = ROM.read_bytes()[off + got: off + exp]
    return bool(tail) and not any(tail)


def revert_one(path, func):
    """Put one spliced function back to its INCLUDE_ASM stub."""
    text = read_latin1(path)
    stem = str(path.relative_to(ROOT))[:-2]
    funcs, _ = T.extract_functions_from_file(stem + ".c", text)
    target = next((f for f in funcs if f["name"] == func), None)
    stub = f'INCLUDE_ASM("asm/nonmatchings/{stem}", {func});'
    if target is not None:
        write_latin1(path, text[:target["start"]] + stub + text[target["end"]:])
        return True
    # a handwritten-asm body: not a C function definition, so
    # extract_functions_from_file cannot see it — find its `__asm__(...)`
    # block by the glabel it defines.
    for m in ASM_BLOCK_RE.finditer(text):
        i = text.index("(", m.start())
        try:
            close, asm = _scan_asm_block(text, i)
        except ValueError:
            continue
        if not re.search(r"^\s*glabel\s+%s\s*$" % re.escape(func), asm, re.M):
            continue
        end = close + 1
        while end < len(text) and text[end] in " \t":
            end += 1
        if end < len(text) and text[end] == ";":
            end += 1
        write_latin1(path, text[:m.start()] + stub + text[end:])
        return True
    return False


def spliced_bodies(stem, by_name):
    """[(record, {})] for every function in `<stem>.c` that is a real C body
    rather than an INCLUDE_ASM stub, in file order."""
    path = target_tu_path(stem)
    if not path.exists():
        return []
    text = read_latin1(path)
    inc = {n for _s, _e, n in T.parse_include_asm_entries(text)}
    funcs, _ = T.extract_functions_from_file(stem + ".c", text)
    return [(by_name.get(f["name"]) or {"name": f["name"], "wave": 0,
                                        "pal_vma": 0}, {})
            for f in funcs if f["name"] not in inc]


def reconcile_tu(stem, kept, reverted):
    """Make the TU object's .text EXACTLY the size of its PAL span.

    quick_diff compares ONE function's instruction stream and is blind to
    two ways a spliced body still changes the object's length:

      * a carried TU-local helper gcc declines to inline, emitted as an
        extra out-of-line function (the whole point of the ntsc `.c` being
        a different TU partition);
      * the ROM's inter-function PAD word.  splat parks the TU's trailing
        pad after the last `.s`'s `endlabel`, so porting the LAST function
        of a span drops 4 bytes that nothing re-emits.

    Either shifts every later object in the link — a byte-identical-nowhere
    ELF that passes every per-function diff.  So: compare each ported
    function's symbol size against its splat baseline, revert the ones that
    disagree, and then revert from the tail until the whole object is
    exactly the span size."""
    path = target_tu_path(stem)
    exp = tu_span_size(stem)
    if exp is None or not kept:
        return
    def measure():
        T.run_quick_diff(stem, kept[-1][0]["name"] if kept else "")
        return text_bytes(stem), object_func_sizes(stem)

    got, sizes = measure()
    # 1. per-function size disagreement
    for rec, _m in list(kept):
        sh = target_asm_shape(stem, rec["name"])
        want = sh[0] * 4 if sh else None
        have = sizes.get(rec["name"])
        if want is None or have is None or want == have:
            continue
        if revert_one(path, rec["name"]):
            kept.remove((rec, _m))
            reverted.append((rec, f"tu-size: body is 0x{have:X} bytes, ROM "
                                  f"function is 0x{want:X} (out-of-line "
                                  f"helper or extra code)"))
    if not kept:
        return
    got, sizes = measure()
    # 2. residual: the span's trailing pad word, dropped with the last body
    stuck = 0
    while kept and got != exp and not span_tail_is_zero_pad(stem, got, exp):
        rec, _m = kept.pop()
        if not revert_one(path, rec["name"]):
            # a handwritten-asm body: not a C definition, so there is nothing
            # for extract_functions_from_file to replace. Leave it in place.
            stuck += 1
            if stuck > 8:
                reverted.append((rec, f"tu-size: TU .text 0x{got:X} != PAL "
                                      f"span 0x{exp:X}, and the residual is "
                                      f"not in a revertible C body"))
                return
            continue
        stuck = 0
        reverted.append((rec, f"tu-size: TU .text 0x{got:X} != PAL span "
                              f"0x{exp:X} (trailing pad word / extra code)"))
        if not kept:
            return
        got, sizes = measure()


def failure_reason(rc, out, err):
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
    ("missing-body", r"ntsc body not found"),
    ("emits-data", r"^emits-data:"),
]


def classify_reason(reason):
    for tag, rx in REASON_CLASSES:
        if re.search(rx, reason):
            return tag
    return "codegen"


def _needed_typedefs(atu, text, declared, mapping, rename=None):
    idx = atu["typedefs"]
    if not idx:
        return []
    rx = re.compile(r"\b(" + "|".join(
        re.escape(k) for k in sorted(idx, key=len, reverse=True)) + r")\b")
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
    deps = {nm: {d for d in rx.findall(blk) if d in need and d != nm}
            for nm, blk in need.items()}
    out, emitted = [], set()
    while len(emitted) < len(need):
        ready = sorted(nm for nm in need
                       if nm not in emitted and not (deps[nm] - emitted))
        if not ready:
            ready = sorted(nm for nm in need if nm not in emitted)
        for nm in ready:
            emitted.add(nm)
            out.append((nm, need[nm]))
    return out


SIMPLE_TYPEDEF_TRAILER = re.compile(
    r"__attribute__\s*\(\(.*\)\)\s*$|\[[^\]]*\]\s*$")

ASM_LABEL_RE = re.compile(r'__asm__\s*\(\s*"[^"]*"\s*\)')


def declarator_name(stmt):
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


def decl_index(rel, raw):
    """name -> full `extern ...;` statement, for every top-level extern in one
    TU. Paren/brace-aware statement splitting."""
    clean = T.strip_comments_preserve_len(raw)
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


def typedef_index(rel, raw):
    """All top-level `typedef ...;` statements keyed by the name introduced —
    struct/union/enum (via transplant_retail) plus the SCALAR forms
    (`typedef int Qw128 __attribute__((mode(TI)));`)."""
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


# ==========================================================================
# port-all
# ==========================================================================
def cmd_port_all(args):
    """Port every PAL TU that still has pending candidates.

    Runs in two phases so `tools/build.sh setup` (~35 s) is paid ONCE per
    chunk rather than once per TU: first scaffold + flip every TU in the
    chunk, then splat, then splice."""
    cand = load_candidates()
    waves = set(args.waves)
    per = defaultdict(int)
    for r in cand["records"]:
        if r["wave"] in waves and r["pal_tu"]:
            per[tu_stem(r["pal_tu"])] += 1
    tus = [t for t, _ in sorted(per.items(), key=lambda kv: (-kv[1], kv[0]))]
    if args.skip:
        tus = tus[args.skip:]
    if args.limit:
        tus = tus[:args.limit]

    if args.apply and not args.no_setup:
        made = []
        for tu in tus:
            created, flipped = ensure_scaffold(tu)
            if created or flipped:
                made.append(tu)
        if made:
            print(f"== scaffolded/flipped {len(made)} TUs; running "
                  f"tools/build.sh setup", flush=True)
            build_setup()

    shared = PortContext() if args.apply else None
    tot_k = tot_r = tot_s = 0
    classes = defaultdict(int)
    emptied = []
    for tu in tus:
        if not target_tu_path(tu).exists():
            print(f"{tu}: no TU file — skipped", file=sys.stderr)
            continue
        sub = argparse.Namespace(tu=tu, apply=args.apply, waves=args.waves,
                                 only=[], allow_jtbl=[])
        k, r, s = cmd_port(sub, shared)
        tot_k += len(k)
        tot_r += len(r)
        tot_s += len(s)
        for _, reason in r:
            classes[classify_reason(reason)] += 1
        if args.apply and not k and not args.keep_empty:
            if unscaffold(tu):
                emptied.append(tu)
    print(f"\n== port-all: {len(tus)} TUs  ported={tot_k} reverted={tot_r} "
          f"skipped={tot_s}")
    for c, n in sorted(classes.items(), key=lambda kv: -kv[1]):
        print(f"   {n:5d}  {c}")
    if emptied:
        print(f"   {len(emptied)} TUs reverted to `asm` (nothing ported): "
              + ", ".join(emptied))


def cmd_fixup(args):
    """Re-run the TU-size reconciliation over every already-flipped TU.

    Used after a batch link comes back the wrong LENGTH: the per-function
    quick_diff gate cannot see an object that is the wrong size (see
    reconcile_tu), so this recovers without unwinding the whole chunk."""
    rows = [(off, name) for off, typ, name, _ln
            in yaml_text_subsegs(TARGET_YAML) if typ == "c"]
    cand = load_candidates()
    by_name = {r["name"]: r for r in cand["records"]}
    total = 0
    for _off, tu in rows:
        path = target_tu_path(tu)
        if not path.exists():
            continue
        kept = spliced_bodies(tu, by_name)
        if not kept:
            continue
        reverted = []
        reconcile_tu(tu, kept, reverted)
        if reverted:
            total += len(reverted)
            print(f"{tu}: reverted {len(reverted)}")
            ledger_append([f"\n### {tu}"] + [
                f"- REVERTED `{rec['name']}` w{rec.get('wave', 0)} @ "
                f"0x{rec.get('pal_vma', 0):08X} — [tu-size] {reason}"
                for rec, reason in reverted])
    print(f"fixup: reverted {total} functions")


LEDGER_ENTRY_RE = re.compile(r"^- (PORTED|REVERTED|SKIPPED|PRE-MATCHED) `([^`]+)`")


def cmd_ledger(args):
    """Rewrite decomp/port_ledger_pal.md: one entry per function (last attempt
    wins), TUs alphabetical, plus an accounting header."""
    txt = LEDGER_PATH.read_text(encoding="utf-8") if LEDGER_PATH.exists() else ""
    lines = txt.split("\n")
    body_at = next((k for k, l in enumerate(lines) if l.startswith("### ")),
                   len(lines))
    cur, order, per, carves = None, [], {}, {}
    pend_carve = None
    for l in lines[body_at:]:
        if l.startswith("### "):
            cur = l[4:].strip()
            if cur not in per:
                per[cur] = {}
                order.append(cur)
            pend_carve = None
            continue
        if l.startswith("- CARVES ") and cur:
            carves[cur] = [l]
            pend_carve = cur
            continue
        if pend_carve and l.startswith("    - "):
            carves[pend_carve].append(l)
            continue
        pend_carve = None
        m = LEDGER_ENTRY_RE.match(l)
        if m and cur:
            per[cur][m.group(2)] = l

    cand = load_candidates()
    rows = [r for r in cand["records"] if r["wave"] in (1, 2, 3) and r["pal_tu"]]
    logged = {}
    for tu, d in per.items():
        for fn, l in d.items():
            logged[fn] = LEDGER_ENTRY_RE.match(l).group(1).lower()
    tu_cache = {}
    stats = defaultdict(lambda: defaultdict(int))
    for r in rows:
        w, fn = r["wave"], r["name"]
        stats[w]["candidates"] += 1
        if fn in logged:
            stats[w][logged[fn]] += 1
            continue
        p = target_tu_path(r["pal_tu"])
        if p not in tu_cache:
            tu_cache[p] = read_latin1(p) if p.exists() else ""
        if not tu_cache[p] or re.search(
                r"INCLUDE_ASM[_A-Z]*\([^)]*,\s*%s\s*\)" % re.escape(fn),
                tu_cache[p]):
            stats[w]["unattempted"] += 1
        else:
            stats[w]["pre-matched"] += 1
            tu = tu_stem(r["pal_tu"])
            per.setdefault(tu, {})
            if tu not in order:
                order.append(tu)
            per[tu][fn] = (f"- PRE-MATCHED `{fn}` w{w} @ "
                           f"0x{r['pal_vma']:08X} — already had a PAL body")

    head = [l for l in lines[:body_at]
            if not l.startswith("|") and not l.startswith("## Accounting")]
    while head and not head[-1].strip():
        head.pop()
    cols = ("candidates", "ported", "reverted", "skipped", "pre-matched",
            "unattempted")
    acc = ["", "## Accounting", "",
           "| wave | " + " | ".join(cols) + " |",
           "|---" * (len(cols) + 1) + "|"]
    tot = defaultdict(int)
    for w in sorted(stats):
        acc.append("| %d | " % w + " | ".join(
            str(stats[w][c]) for c in cols) + " |")
        for c in cols:
            tot[c] += stats[w][c]
    acc.append("| **all** | " + " | ".join(str(tot[c]) for c in cols) + " |")

    out = head + acc + [""]
    for tu in sorted(order):
        if not per[tu] and tu not in carves:
            continue
        out.append(f"### {tu}")
        out += [per[tu][fn] for fn in sorted(per.get(tu, {}))]
        out += carves.get(tu, [])
        out.append("")
    LEDGER_PATH.write_text("\n".join(out).rstrip() + "\n", encoding="utf-8")
    print("\n".join(acc[1:]))
    print(f"\nwrote {LEDGER_PATH} ({LEDGER_PATH.stat().st_size} bytes, "
          f"{len(order)} TUs)")


def cmd_revert_func(args):
    if not revert_one(target_tu_path(args.tu), args.func):
        print(f"revert-func: {args.func} is not a spliced function in "
              f"{args.tu}.c", file=sys.stderr)
        sys.exit(1)
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
        if r["wave"] not in waves or not r["pal_tu"]:
            continue
        tot += 1
        p = target_tu_path(r["pal_tu"])
        if p not in tu_text_cache:
            tu_text_cache[p] = (read_latin1(p) if p.exists() else "")
        txt = tu_text_cache[p]
        inc = (not txt) or bool(re.search(
            r"INCLUDE_ASM[_A-Z]*\([^)]*,\s*%s\s*\)" % re.escape(r["name"]), txt))
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
    p.add_argument("--allow-jtbl", dest="allow_jtbl",
                   type=lambda s: [x for x in s.split(",") if x], default=[])
    p.add_argument("--only", dest="only",
                   type=lambda s: [x for x in s.split(",") if x], default=[])

    p = sub.add_parser("port-all")
    p.add_argument("--apply", action="store_true")
    p.add_argument("--waves", type=lambda s: [int(x) for x in s.split(",")],
                   default=[1, 2, 3])
    p.add_argument("--limit", type=int, default=0)
    p.add_argument("--skip", type=int, default=0)
    p.add_argument("--no-setup", action="store_true",
                   help="skip the scaffold/flip + build.sh setup phase "
                        "(the TUs are already flipped and split)")
    p.add_argument("--keep-empty", action="store_true",
                   help="leave a TU flipped to `c` even when nothing ported")

    sub.add_parser("ledger")
    sub.add_parser("fixup")

    p = sub.add_parser("revert-func")
    p.add_argument("tu")
    p.add_argument("func")
    p.add_argument("--reason", default=None)

    args = ap.parse_args()
    {"scan": cmd_scan, "status": cmd_status, "tus": cmd_tus, "plan": cmd_plan,
     "port": cmd_port, "port-all": cmd_port_all, "ledger": cmd_ledger,
     "fixup": cmd_fixup, "revert-func": cmd_revert_func}[args.cmd](args)
