#!/usr/bin/env python3
"""Regenerate config/symbol_addrs.us.txt for the ICO USA retail boot ELF.

WHAT THIS DOES
--------------
The retail ELF is stripped: no symbol table, no TU boundaries.  This tool
recovers both, from three independent rom-native oracles, and writes:

  * config/symbol_addrs.us.txt        (tracked)   -- one `type:func` entry per
        recovered retail function start, with a name and a source-file trailer.
  * baserom/us_text_tu_boundaries.txt (untracked) -- contiguous .text spans per
        recovered retail source file, in link order.

USAGE
-----
    tools/gen_us_symbol_addrs.py            # regenerate both outputs
    tools/gen_us_symbol_addrs.py --report   # diagnostics only, write nothing
    tools/gen_us_symbol_addrs.py --check    # re-verify sanity gates, write nothing

Idempotent: everything above the BEGIN GENERATED banner in
config/symbol_addrs.us.txt is preserved byte-for-byte (hand-written seeds:
`_start`, the `D_00633BC0` asciz note, the sub-word .sdata `defined:True`
block, splat-lost-symbol fixups, the VU1 *MicroProgram entries).  Re-running
rewrites only the block below the banner.  A generated entry is suppressed if
its VMA or its name is already claimed by the seed block.

METHOD
------
1. FUNCTION STARTS -- branch-aware boundary scan of .text on
   baserom/baseelf.rom (the algorithm in tools/correlate_funcs.py): a
   terminator (jr/j/jalr) ends a function only if no backward-reaching branch
   target lies past it; inter-function zero padding is skipped.  This is
   rom-native and reliable; it is the one part of the output that is not
   provisional.

2. FILE ANCHORS -- the SCE assert macro leaks __FILE__ strings into .rodata.
   For every function, replay lui/%lo pairs and see whether any resolves to a
   "<dir>/<name>.c" string; if so that function provably belongs to that file.
   92 distinct .c paths exist in the retail string pool; 89 of them are
   referenced from .text and thus usable as anchors.  Anchor runs are strictly
   non-overlapping, which is what makes them usable as span boundaries.

3. CROSS-VERSION TWINS -- reloc-normalized instruction-stream SHA-1 equality
   between the Aug-6-2001 prototype rom (baserom/aug6/baseelf.rom, whose
   functions carry recovered names and TU attributions) and the retail rom.
   The normalizer is decomp/retail_port/correlate.py:normalize(): it masks
   j/jal targets, lui immediates, %lo-pair immediates and $gp-relative
   displacements, so a function that was not edited between the two builds
   hashes identically across the two links.  Matching is order-constrained
   (the two link orders agree) and applied recursively inside the gaps it
   opens, then a final order-free pass picks up members that moved.

PROVENANCE OF NAMES  (mirror of config/symbol_addrs.aug6.txt's discipline)
--------------------------------------------------------------------------
Names are NOT from any leaked source.  They come from the aug6 table, which
derived them by ordinal correlation against the prototype's own shipped
metadata (TRFILE.TXT / MAIN.MAP on the SCUS_971.13 disc).  Two tiers here:

  * `twin`     -- the retail function is byte-equivalent (mod relocs) to a
                  named aug6 function.  As trustworthy as the aug6 name is.
  * `ordinal`  -- no hash twin, but the function sits at a determined ordinal
                  between two twins in a gap of equal length on both sides, so
                  the correspondence is forced by link order.  Emitted with a
                  `provisional-ordinal` tag (colon-free: splat parses
                  `key:value` tokens in these comments as attributes).

Anything else keeps splat's `func_<VMA>` auto-name.  A name is dropped
whenever the aug6 attribution contradicts a retail __FILE__ anchor.

!! MAIN.MAP / TRFILE.TXT ADDRESSES ARE A DIFFERENT LINK !!  baserom/aug6/
MAIN.MAP and the text_tu_boundaries.txt derived from it disagree with the aug6
rom's real member layout by up to two whole members (verified here: only
1826/4400 of its ico2000.a spans agree with the aug6 project's own byte-
verified subsegment table).  Its ORDER and its member NAMES are oracles; its
ADDRESSES are not.  aug6 TU spans in this tool therefore come from
config/ico.aug6.yaml -- the aug6 project's rom-native, round-trip-verified
subsegment list -- never from MAIN.MAP.
"""
from __future__ import annotations

import argparse
import bisect
import hashlib
import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

# ---------------------------------------------------------------- constants --
HERE = Path(__file__).resolve().parent
RETAIL = HERE.parent                          # /primary/dev/ico-retail
AUG6 = Path("/primary/dev/ico")               # sibling checkout, branch main

RETAIL_ROM = RETAIL / "baserom" / "baseelf.rom"
RETAIL_SYMS = RETAIL / "config" / "symbol_addrs.us.txt"
RETAIL_TUS = RETAIL / "baserom" / "us_text_tu_boundaries.txt"

AUG6_ROM = AUG6 / "baserom" / "aug6" / "baseelf.rom"
AUG6_SYMS = AUG6 / "config" / "symbol_addrs.aug6.txt"
AUG6_YAML = AUG6 / "config" / "ico.aug6.yaml"

TEXT_VMA = 0x00100000
RETAIL_TEXT_SZ = 0x16F5D4
AUG6_TEXT_SZ = 0x0016B964
# retail .data .. end of .sdata: where the __FILE__ string pool lives
RETAIL_DATA_LO, RETAIL_DATA_HI = 0x00274700, 0x00633BC6

BANNER = ("// ==== BEGIN GENERATED — tools/gen_us_symbol_addrs.py — "
          "do not hand-edit below this line ====")

# retail source-tree layout: the leading per-programmer directory of an aug6 TU
# path is dropped (`sugipon/src/box` -> `src/box.c`).  The one exception is the
# MPEG middleware, which retail keeps namespaced -- its own string pool carries
# "ito/include/mv_defs.h", so `ito/mpeg/*` stays `ito/mpeg/*`.
KEEP_PREFIX = ("ito/mpeg/",)

# Label for .text the aug6 project never attributed to an ico2000.a member:
# the crt0 + libkernl prologue and the libc / libgcc tail.  It is a real label
# (not "unknown"), so forward-fill stops at it instead of swallowing the tail
# into the last game TU -- and unlike a source file it may occupy more than one
# span, since the vendor archives bracket the game code.
VENDOR = "(vendor)"

FUNC_NAME_RE = re.compile(r"func_00[0-9A-F]{6}\Z")
PATH_RE = re.compile(r"(?:[A-Za-z0-9_+-]+/)*[A-Za-z0-9_.+-]+\.[ch]\Z")
SYM_RE = re.compile(
    r"^\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)\s*;\s*//\s*type:func(?:\s*//\s*(\S+))?")
ANY_SYM_RE = re.compile(r"^\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)\s*;")
YAML_SUB_RE = re.compile(r"^\s*-\s*\[\s*(0x[0-9A-Fa-f]+)\s*,\s*(\w+)\s*,\s*(\S+?)\s*\]")


# --------------------------------------------------------- boundary scanning --
JR = 0x03E00008


def scan_text(rom: bytes, text_sz: int) -> list[tuple[int, int]]:
    """Branch-aware .text function boundary scan.  Returns [(start,end), ...]."""

    def w(off):
        return struct.unpack_from("<I", rom, off)[0]

    def is_term(x):
        op = (x >> 26) & 0x3F
        return x == JR or op == 2 or (op == 0 and (x & 0x3F) == 8)

    def branch_target(off):
        x = w(off)
        op = (x >> 26) & 0x3F
        if (op in (0x04, 0x05, 0x06, 0x07, 0x14, 0x15, 0x16, 0x17)
                or op == 1 or (op == 0x11 and ((x >> 21) & 0x1F) == 8)):
            imm = x & 0xFFFF
            imm -= 0x10000 if imm >= 0x8000 else 0
            return TEXT_VMA + off + 4 + imm * 4
        return None

    funcs: list[tuple[int, int]] = []
    start = TEXT_VMA
    max_branch = TEXT_VMA
    off = 0
    while off < text_sz:
        va = TEXT_VMA + off
        x = w(off)
        t = branch_target(off)
        if t and t > max_branch:
            max_branch = t
        if is_term(x):
            end = va + 8                       # terminator + delay slot
            if max_branch <= va + 4:
                funcs.append((start, end))
                nxt = end
                while nxt - TEXT_VMA < text_sz and w(nxt - TEXT_VMA) == 0:
                    nxt += 4                   # inter-function alignment padding
                start = nxt
                max_branch = nxt
                off = nxt - TEXT_VMA
                continue
        off += 4
    if start < TEXT_VMA + text_sz:
        funcs.append((start, TEXT_VMA + text_sz))
    return funcs


# ------------------------------------------------- reloc-normalized hashing --
# (identical semantics to decomp/retail_port/correlate.py:normalize)
MASK_IMM_OPS = set([0x08, 0x09, 0x0D, 0x18, 0x19, 0x1E, 0x1F]) | set(range(0x20, 0x40))
LOAD_OPS = set([0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
                0x30, 0x31, 0x33, 0x35, 0x36, 0x37, 0x1E])
ITYPE_WRITE_RT = set([0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x18, 0x19, 0x0F]) | LOAD_OPS


def normalize(words: list[int]) -> list[int]:
    """Mask every field a relink can change: j/jal targets, lui immediates,
    the %lo half of a hi/lo pair, and $gp-relative displacements."""
    taint = [False] * 32
    out = []
    for word in words:
        op = (word >> 26) & 0x3F
        rs = (word >> 21) & 0x1F
        rt = (word >> 16) & 0x1F
        nw = word
        if op in (2, 3):
            nw = word & 0xFC000000
        elif op == 0x0F:
            nw = word & 0xFFFF0000
        elif op in MASK_IMM_OPS:
            if rs == 28 or taint[rs]:
                nw = word & 0xFFFF0000
        wd = None
        if op == 0x0F:
            if rt:
                taint[rt] = True
        else:
            if op == 0:
                wd = (word >> 11) & 0x1F
            elif op == 3:
                wd = 31
            elif op == 1 and rt in (0x10, 0x11):
                wd = 31
            elif op in ITYPE_WRITE_RT and op not in (0x31, 0x35, 0x36, 0x39,
                                                     0x3D, 0x3E, 0x3F, 0x1F):
                wd = rt
            elif op == 0x1C:
                wd = (word >> 11) & 0x1F
            elif op in (0x10, 0x11, 0x12):
                if rs in (0, 1, 2, 3):
                    wd = rt
            if wd:
                taint[wd] = False
        out.append(nw)
    return out


def func_hashes(rom: bytes, funcs) -> list[tuple[str | None, int]]:
    out = []
    for start, end in funcs:
        n = (end - start) // 4
        words = list(struct.unpack(f"<{n}I", rom[start - TEXT_VMA: start - TEXT_VMA + 4 * n]))
        while words and words[-1] == 0:
            words.pop()
        if not words:
            out.append((None, 0))
            continue
        nw = normalize(words)
        h = hashlib.sha1(struct.pack("<%dI" % len(nw), *nw)).hexdigest()
        out.append((h, len(nw)))
    return out


# --------------------------------------------------------- __FILE__ census ---
def string_pool(rom: bytes, lo: int, hi: int) -> dict[int, str]:
    """VMA -> "<dir>/<file>.c" for every path-looking NUL-terminated string."""
    pool: dict[int, str] = {}
    for m in re.finditer(rb"[ -~]{3,}\.[ch]\x00", rom[lo - TEXT_VMA: hi - TEXT_VMA]):
        raw = m.group()[:-1].decode("latin1")
        best = None
        for i in range(len(raw)):
            if PATH_RE.match(raw[i:]):
                best = raw[i:]
                break
        if best:
            pool.setdefault(lo + m.start() + (len(raw) - len(best)), best)
    return pool


def census(rom: bytes, funcs, pool: dict[int, str], text_sz: int) -> list[str | None]:
    """Per function: the __FILE__ path it references, if any."""

    def w(off):
        return struct.unpack_from("<I", rom, off)[0]

    anchors: list[str | None] = []
    for start, end in funcs:
        his: dict[int, int] = {}
        got = None
        for q in range(start - TEXT_VMA, min(end, TEXT_VMA + text_sz) - TEXT_VMA, 4):
            x = w(q)
            op = (x >> 26) & 0x3F
            if op == 0x0F:
                his[(x >> 16) & 0x1F] = (x & 0xFFFF) << 16
            elif op in (0x09, 0x0D, 0x19, 0x21, 0x23, 0x25, 0x2B, 0x37, 0x3F):
                rs = (x >> 21) & 0x1F
                lo = x & 0xFFFF
                lo -= 0x10000 if lo >= 0x8000 else 0
                if rs in his and his[rs] + lo in pool:
                    path = pool[his[rs] + lo]
                    if path.endswith(".c"):
                        got = path
                        break
        anchors.append(got)
    return anchors


# --------------------------------------------------------------- aug6 side ---
def aug6_tu_spans() -> list[tuple[int, int, str | None]]:
    """(vma_start, vma_end, tu_path|None) from the aug6 project's own byte-
    verified splat subsegment list.  NOT from MAIN.MAP (different link)."""
    rows = []
    in_subs = False
    for line in AUG6_YAML.read_text().splitlines():
        if re.match(r"^\s*subsegments:", line):
            in_subs = True
            continue
        if not in_subs:
            continue
        m = YAML_SUB_RE.match(line)
        if not m:
            continue
        off = int(m.group(1), 16)
        kind, path = m.group(2), m.group(3)
        if off >= AUG6_TEXT_SZ:
            break                                # left .text
        rows.append((TEXT_VMA + off, kind, path))
    rows.sort()
    out = []
    for i, (vma, kind, path) in enumerate(rows):
        end = rows[i + 1][0] if i + 1 < len(rows) else TEXT_VMA + AUG6_TEXT_SZ
        tu = path if kind == "c" else None       # `asm` blobs = vendor/uncarved
        out.append((vma, end, tu))
    return out


def aug6_syms() -> tuple[dict[int, str], dict[int, str]]:
    """VMA -> name and VMA -> TU path, from config/symbol_addrs.aug6.txt.

    That table's TU column is the finer-grained oracle: it is derived from the
    aug6 rom's own __FILE__ census, so it splits members that the aug6 splat
    yaml coalesces into one subsegment (e.g. box.o + switch.o both live in the
    yaml's `sugipon/src/box`).  Its weakness is the other end -- it forward/
    backward-fills across the vendor prologue and tail, which is why it is
    intersected with the yaml's `asm` (vendor) subsegments below."""
    names, tus = {}, {}
    for line in AUG6_SYMS.read_text().splitlines():
        m = SYM_RE.match(line)
        if m:
            v = int(m.group(2), 16)
            names[v] = m.group(1)
            if m.group(3):
                tus[v] = m.group(3)
    return names, tus


def retail_path(aug_tu: str | None) -> str | None:
    """aug6 TU path (`<programmer>/<subdir>/<stem>[.c]`) -> retail source path."""
    if not aug_tu:
        return None
    if aug_tu == VENDOR:
        return VENDOR
    stem = aug_tu[:-2] if aug_tu.endswith(".c") else aug_tu
    parts = stem.split("/")
    if len(parts) < 2:
        return None
    tail = "/".join(parts[1:]) + ".c"
    for keep in KEEP_PREFIX:
        if tail.startswith(keep.split("/", 1)[1]):
            return parts[0] + "/" + tail
    return tail


# ---------------------------------------------------------------- alignment --
def lis_by_second(pairs: list[tuple[int, int]]) -> list[tuple[int, int]]:
    """Longest strictly-increasing-in-`b` subsequence of pairs sorted by `a`."""
    tails: list[int] = []
    tail_idx: list[int] = []
    parent = [-1] * len(pairs)
    for k, (_, b) in enumerate(pairs):
        i = bisect.bisect_left(tails, b)
        if i == len(tails):
            tails.append(b)
            tail_idx.append(k)
        else:
            tails[i] = b
            tail_idx[i] = k
        parent[k] = tail_idx[i - 1] if i > 0 else -1
    res = []
    k = tail_idx[-1] if tail_idx else -1
    while k >= 0:
        res.append(pairs[k])
        k = parent[k]
    return res[::-1]


def align_range(rh, ah, rlo0, rhi0, alo0, ahi0, max_depth=10, min_insns=3):
    """Order-constrained recursive unique-hash matching inside a rectangle.

    A hash that occurs exactly once on each side within the window is an
    unambiguous correspondence; take the longest order-preserving subset of
    those, then recurse into the gaps they open (where a hash that was
    ambiguous globally is often unique locally).  Returns [(ri, ai)]."""

    def rec(rlo, rhi, alo, ahi, depth):
        if rlo >= rhi or alo >= ahi:
            return []
        abyh, rbyh = defaultdict(list), defaultdict(list)
        for i in range(alo, ahi):
            if ah[i][0] and ah[i][1] >= min_insns:
                abyh[ah[i][0]].append(i)
        for i in range(rlo, rhi):
            if rh[i][0] and rh[i][1] >= min_insns:
                rbyh[rh[i][0]].append(i)
        pairs = []
        for h, ais in abyh.items():
            ris = rbyh.get(h)
            if ris and len(ais) == 1 and len(ris) == 1:
                pairs.append((ris[0], ais[0]))
        if not pairs:
            return []
        pairs.sort()
        pairs = lis_by_second(pairs)
        out = list(pairs)
        if depth < max_depth:
            pr, pa = rlo, alo
            for r, a in pairs + [(rhi, ahi)]:
                out += rec(pr, r, pa, a, depth + 1)
                pr, pa = r + 1, a + 1
        return out

    return sorted(set(rec(rlo0, rhi0, alo0, ahi0, 0)))


def align_twins(rh, ah, n_r, n_a):
    return align_range(rh, ah, 0, n_r, 0, n_a)


def free_pass(rh, ah, n_r, n_a, twin_r, twin_a, min_insns=8):
    """Order-free unique-hash pass for members whose link position moved."""
    abyh, rbyh = defaultdict(list), defaultdict(list)
    for i in range(n_a):
        if i not in twin_a and ah[i][0] and ah[i][1] >= min_insns:
            abyh[ah[i][0]].append(i)
    for i in range(n_r):
        if i not in twin_r and rh[i][0] and rh[i][1] >= min_insns:
            rbyh[rh[i][0]].append(i)
    extra = []
    for h, ais in abyh.items():
        ris = rbyh.get(h)
        if ris and len(ais) == 1 and len(ris) == 1:
            extra.append((ris[0], ais[0]))
    return sorted(extra)


# ------------------------------------------------------------------- driver --
class Model:
    pass


def windows(labels):
    """Maximal contiguous runs of a label: [(path, lo, hi_exclusive), ...]."""
    out = []
    i = 0
    while i < len(labels):
        j = i
        while j + 1 < len(labels) and labels[j + 1] == labels[i]:
            j += 1
        if labels[i]:
            out.append((labels[i], i, j + 1))
        i = j + 1
    return out


def cut_vendor_tail(m, aug_of, labels, src):
    """Stop attribution at the end of the game code.

    Both aug6 oracles run past it: the name table forward-fills its last TU
    trailer, and the aug6 yaml's final .text subsegment (`common/src/PObj`) is
    an uncarved blob that swallows the vendor tail.  MAIN.MAP ORDER -- valid,
    unlike its addresses -- says the ico2000.a members end with PObj.o + vobj.o
    and are immediately followed by libgraph.a, libc.a, libkernl.a(cache.o) and
    libgcc.a.  So: the last retail function with positive game-code evidence (a
    __FILE__ anchor of its own, or a twin carrying a TRFILE-derived name) ends
    the game code; everything past it is vendor.  vobj.o -- the one ico2000.a
    member with no TRFILE-traced function and no retail __FILE__ string -- falls
    on the vendor side of that cut.  Flagged here, not silently claimed."""
    ev = [i for i in range(len(m.rfuncs))
          if m.anchor[i]
          or (i in aug_of and m.aug_name[aug_of[i]]
              and not FUNC_NAME_RE.match(m.aug_name[aug_of[i]]))]
    if not ev or len(m.rfuncs) - 1 - ev[-1] < 300:
        m.vendor_cut = None
        return
    m.vendor_cut = ev[-1] + 1
    for i in range(m.vendor_cut, len(m.rfuncs)):
        labels[i] = VENDOR
        src[i] = "fill"


def self_label(m, twins, ordinal, final=False):
    """Attribute every retail function to a source file.

    census anchor  >  aug6 TU carried over by a twin/ordinal correspondence
                   >  forward fill.
    A linker emits each .o's .text contiguously, so a file may occupy exactly
    one span; where the carried-over attribution says otherwise, the cluster
    holding the census anchors wins (else the largest cluster) and the strays
    are dropped back to fill."""
    n = len(m.rfuncs)
    aug_of = dict(twins)
    for r, a in ordinal.items():
        aug_of.setdefault(r, a)

    labels = [None] * n
    src = [""] * n
    conflicts = []
    for i in range(n):
        derived = retail_path(m.aug_tu[aug_of[i]]) if i in aug_of else None
        if m.anchor[i]:
            labels[i] = m.anchor[i]
            src[i] = "census"
            if derived and derived != m.anchor[i]:
                conflicts.append((f"0x{m.rfuncs[i][0]:08X}", derived, m.anchor[i]))
        elif derived:
            labels[i] = derived
            src[i] = "aug6"

    # --- enforce one span per file ------------------------------------------
    lab_idx = [i for i in range(n) if labels[i]]
    clusters = defaultdict(list)
    prev = None
    for i in lab_idx:
        f = labels[i]
        if f != prev:
            clusters[f].append([])
        clusters[f][-1].append(i)
        prev = f
    split_files = []
    for f, cls in clusters.items():
        if len(cls) < 2 or f == VENDOR:
            continue
        split_files.append((f, [(f"0x{m.rfuncs[c[0]][0]:08X}", len(c)) for c in cls]))
        scored = sorted(cls, key=lambda c: (sum(1 for i in c if m.anchor[i]), len(c)))
        for c in scored[:-1]:
            for i in c:
                if not m.anchor[i]:
                    labels[i] = None
                    src[i] = ""

    last = None
    for i in range(n):
        if labels[i]:
            last = labels[i]
        elif last is not None:
            labels[i] = last
            src[i] = "fill"

    cut_vendor_tail(m, aug_of, labels, src)

    if final:
        return labels, src, conflicts, split_files
    return labels


def align_twins_window(m, r0, r1, a0, a1):
    return align_range(m.rh, m.ah, r0, r1, a0, a1)


def build() -> Model:
    m = Model()
    m.rrom = RETAIL_ROM.read_bytes()
    m.arom = AUG6_ROM.read_bytes()
    m.rfuncs = scan_text(m.rrom, RETAIL_TEXT_SZ)
    m.afuncs = scan_text(m.arom, AUG6_TEXT_SZ)
    m.rh = func_hashes(m.rrom, m.rfuncs)
    m.ah = func_hashes(m.arom, m.afuncs)

    pool = string_pool(m.rrom, RETAIL_DATA_LO, RETAIL_DATA_HI)
    m.pool_files = sorted({p for p in pool.values() if p.endswith(".c")})
    m.anchor = census(m.rrom, m.rfuncs, pool, RETAIL_TEXT_SZ)

    # aug6 TU per function: the fine-grained census-derived trailer from
    # symbol_addrs.aug6.txt, gated by the yaml's byte-verified partition (a
    # function inside an `asm` subsegment is vendor code the aug6 project never
    # attributed, so its trailer there is a fill artifact -- drop it).
    spans = aug6_tu_spans()
    span_starts = [s for s, _, _ in spans]
    anames, atus = aug6_syms()
    m.aug_tu, m.aug_name = [], []
    for s, _ in m.afuncs:
        i = bisect.bisect_right(span_starts, s) - 1
        carved = (0 <= i < len(spans) and spans[i][0] <= s < spans[i][1]
                  and spans[i][2] is not None)
        m.aug_tu.append(atus.get(s) if carved else VENDOR)
        m.aug_name.append(anames.get(s) if carved else None)

    # Both aug6 attribution oracles run past the end of the game code: the
    # name table forward-fills its last TU trailer, and the yaml's final .text
    # subsegment (`common/src/PObj`) is an uncarved blob that swallows the
    # vendor tail.  MAIN.MAP ORDER -- valid, unlike its addresses -- says the
    # ico2000.a members end with PObj.o + vobj.o and are immediately followed
    # by libgraph.a, libc.a, libkernl.a(cache.o) and libgcc.a.  The aug6 name
    # table (TRFILE-derived, so ico2000.a-only) stops dead at FreePObj with a
    # ~770-function unnamed run behind it: that run is the vendor tail.  Cut
    # there.  vobj.o, the one ico2000.a member with no TRFILE-traced function,
    # is folded into the vendor head -- flagged, not silently claimed.
    # The cut is made on the RETAIL side (see cut_vendor_tail), because TRFILE
    # only names functions its trace actually executed -- cutting aug6 at its
    # last named function would truncate PObj.o itself.

    # aug6 index range per retail-path TU (aug6 emits each .o contiguously)
    m.aug_tu_range = {}
    for j, tu in enumerate(m.aug_tu):
        p = retail_path(tu)
        if not p:
            continue
        lo, hi = m.aug_tu_range.get(p, (j, j))
        m.aug_tu_range[p] = (min(lo, j), max(hi, j))

    # ---- correspondence -----------------------------------------------------
    # Pass A: global order-constrained unique-hash alignment.  The two link
    # orders agree almost everywhere, so this is the bulk of the signal.
    pairs = align_twins(m.rh, m.ah, len(m.rfuncs), len(m.afuncs))
    m.twins = dict(pairs)
    m.n_global = len(pairs)

    # Pass B: provisional file labels from census + Pass-A twins, made
    # contiguous, so each source file gets a retail index window.
    prov = self_label(m, m.twins, {})

    # Pass C: re-align inside each (retail window x aug6 TU range) rectangle.
    # This recovers members whose position changed between the two links
    # (adpcm_init.o moved; box.o/switch.o swapped) which the monotone Pass A
    # necessarily missed.
    m.moved = {}
    for path, r0, r1 in windows(prov):
        rng = m.aug_tu_range.get(path)
        if not rng:
            continue
        a0, a1 = rng[0], rng[1] + 1
        sub = align_twins_window(m, r0, r1, a0, a1)
        for r, a in sub:
            if r not in m.twins and a not in set(m.twins.values()):
                m.twins[r] = a
                m.moved[r] = a
    # Pass C': global order-free unique-hash sweep for anything still adrift.
    used_a = set(m.twins.values())
    for r, a in free_pass(m.rh, m.ah, len(m.rfuncs), len(m.afuncs),
                          set(m.twins), used_a):
        if r not in m.twins and a not in used_a:
            m.twins[r] = a
            m.moved[r] = a
            used_a.add(a)

    # Pass D: ordinal fill.  Split the twin set into maximal runs that are
    # monotone in BOTH indices; inside a run, a gap of equal length on both
    # sides forces a 1:1 correspondence by link order.
    m.ordinal = {}
    m.gap_unequal = []
    tw = sorted(m.twins.items())
    runs, cur = [], []
    for p in tw:
        if cur and p[1] <= cur[-1][1]:
            runs.append(cur)
            cur = []
        cur.append(p)
    if cur:
        runs.append(cur)
    for run in runs:
        for k in range(1, len(run)):
            r0, a0 = run[k - 1]
            r1, a1 = run[k]
            dr, da = r1 - r0 - 1, a1 - a0 - 1
            if dr == 0 and da == 0:
                continue
            if dr == da:
                for j in range(dr):
                    m.ordinal.setdefault(r0 + 1 + j, a0 + 1 + j)
            else:
                m.gap_unequal.append((r0 + 1, r1, a0 + 1, a1))

    # ---- source-file attribution -------------------------------------------
    m.aug_of = dict(m.twins)
    for r, a in m.ordinal.items():
        m.aug_of.setdefault(r, a)
    m.tu, m.tu_src, m.conflicts, m.split_files = self_label(
        m, m.twins, m.ordinal, final=True)
    retail_carved_overlay(m)

    # ---- names --------------------------------------------------------------
    m.name = [None] * len(m.rfuncs)
    m.name_src = [""] * len(m.rfuncs)
    for i in range(len(m.rfuncs)):
        a = m.aug_of.get(i)
        if a is None:
            continue
        nm = m.aug_name[a]
        if not nm or FUNC_NAME_RE.match(nm):
            continue
        if m.aug_tu[a] is None:
            continue                             # vendor/uncarved aug6 blob
        if m.anchor[i] and retail_path(m.aug_tu[a]) != m.anchor[i]:
            continue                             # aug6 contradicts a hard anchor
        m.name[i] = nm
        m.name_src[i] = "twin" if i in m.twins else "ordinal"
    return m


def retail_carved_vendor_spans() -> list[tuple[int, int, str]]:
    """(vma_start, vma_end, path) for every `c` subsegment this project has
    carved out of the retail vendor blobs (`src/cod/*`), read from
    config/ico.us.yaml.

    The two aug6 oracles this generator runs on cannot see these: the aug6
    yaml's final .text subsegment is an uncarved `common/src/PObj` blob that
    swallows the whole vendor tail, so cut_vendor_tail() correctly labels the
    entire run `(vendor)`.  Once WE carve a piece of that run into a real
    retail `c` TU and port bodies into it, the yaml is a harder fact than the
    fill, and the TU note has to say so or the progress dashboard reports the
    ported functions as undecompiled vendor passthrough forever."""
    yaml_p = RETAIL / "config" / "ico.us.yaml"
    if not yaml_p.exists():
        return []
    rows, in_subs = [], False
    for line in yaml_p.read_text().splitlines():
        if re.match(r"^\s*subsegments:", line):
            in_subs = True
            continue
        if not in_subs:
            continue
        mm = YAML_SUB_RE.match(line)
        if not mm:
            continue
        off, kind, path = int(mm.group(1), 16), mm.group(2), mm.group(3)
        if off >= RETAIL_TEXT_SZ:
            break                                # left .text
        rows.append((TEXT_VMA + off, kind, path))
    rows.sort()
    out = []
    for i, (vma, kind, path) in enumerate(rows):
        end = rows[i + 1][0] if i + 1 < len(rows) else TEXT_VMA + RETAIL_TEXT_SZ
        if kind == "c" and path.startswith("src/cod/"):
            out.append((vma, end, path + ".c"))
    return out


def retail_carved_overlay(m) -> None:
    """Overlay retail_carved_vendor_spans() onto m.tu.  Highest precedence:
    an explicit yaml carve is a decision this repo made, not an inference."""
    for lo, hi, path in retail_carved_vendor_spans():
        for i, (s, _e) in enumerate(m.rfuncs):
            if lo <= s < hi:
                m.tu[i] = path
                m.tu_src[i] = "yaml-carve"


def spans_from(m: Model):
    """Contiguous (start_vma, end_vma, path, nfuncs) runs of m.tu."""
    out = []
    i = 0
    while i < len(m.rfuncs):
        j = i
        while j + 1 < len(m.rfuncs) and m.tu[j + 1] == m.tu[i]:
            j += 1
        out.append((m.rfuncs[i][0], m.rfuncs[j][1], m.tu[i], j - i + 1))
        i = j + 1
    return out


def read_seed() -> tuple[str, set[int], set[str]]:
    text = RETAIL_SYMS.read_text() if RETAIL_SYMS.exists() else ""
    head = text.split(BANNER)[0].rstrip("\n")
    vmas, names = set(), set()
    for line in head.splitlines():
        mm = ANY_SYM_RE.match(line)
        if mm:
            names.add(mm.group(1))
            vmas.add(int(mm.group(2), 16))
    return head, vmas, names


HEADER = """
// ---------------------------------------------------------------------------
// Recovered retail function symbols.  Regenerate with:
//     tools/gen_us_symbol_addrs.py
//
// PROVENANCE — read before trusting a name.
//
//   Function STARTS are rom-native: branch-aware boundary detection on
//   baserom/baseelf.rom.  Reliable.
//
//   Source-file trailers come from the retail ELF's own leaked __FILE__
//   strings (SCE assert macro) where a function references one directly
//   (`file:census`, authoritative), otherwise from the aug6 prototype's TU
//   attribution carried across by instruction-stream equality, otherwise
//   filled forward inside an already-attributed region.
//
//   NAMES are provisional.  They are lifted from config/symbol_addrs.aug6.txt
//   in the sibling aug6 checkout, which recovered them by ordinal correlation
//   against the prototype's own disc-shipped metadata (TRFILE.TXT / MAIN.MAP).
//   No leaked source is involved.  Two tiers:
//     * untagged            — the retail function is reloc-normalized
//                             byte-identical to the named aug6 function.
//     * provisional-ordinal — no hash twin; position forced by link order
//                             between two twins.  Verify before relying on it.
//   Functions with neither keep splat's func_<VMA> auto-name.
//
//   !! MAIN.MAP / TRFILE.TXT ADDRESSES ARE A DIFFERENT LINK !!  They drift
//   from the real member layout by up to two whole members.  Their ORDER and
//   member NAMES are oracles; their ADDRESSES are not, for aug6 or for retail.
//   aug6 TU spans used here come from config/ico.aug6.yaml (byte-verified),
//   never from MAIN.MAP.
// ---------------------------------------------------------------------------
""".strip("\n")


def emit(m: Model) -> tuple[int, int, int]:
    head, seed_vmas, seed_names = read_seed()
    lines = [head, "", BANNER, HEADER, ""]
    used = set(seed_names)
    n_twin = n_ord = n_anon = 0
    cur_tu = object()
    for i, (start, _end) in enumerate(m.rfuncs):
        name = m.name[i]
        if name and name in used:
            name = None                          # never shadow an existing symbol
        if name:
            if m.name_src[i] == "twin":
                n_twin += 1
            else:
                n_ord += 1
            used.add(name)
        else:
            n_anon += 1
            name = f"func_{start:08X}"
        if m.tu[i] != cur_tu:
            cur_tu = m.tu[i]
            lines.append("")
            lines.append(f"// ---- {cur_tu or VENDOR}")
        if start in seed_vmas:
            continue                             # hand-written seed wins
        tu = m.tu[i] or VENDOR
        tag = "  // provisional-ordinal" if m.name_src[i] == "ordinal" else ""
        lines.append(f"{name} = 0x{start:08X}; // type:func  // {tu}{tag}")
    RETAIL_SYMS.write_text("\n".join(lines).rstrip("\n") + "\n")

    tu_lines = [
        "# Retail (SLUS-20218 / SCUS_971.13) .text source-file spans, in link order.",
        "# Generated by tools/gen_us_symbol_addrs.py — untracked, regenerate at will.",
        "# Columns: start_vma end_vma path  (n_funcs, attribution)",
        "# Attribution: census = a function in the span references that __FILE__",
        "#              string directly; aug6 = carried over from the prototype by",
        "#              instruction-stream equality; fill = forward-filled.",
        "# MAIN.MAP addresses are a DIFFERENT link and are not used here.",
        "",
    ]
    for s, e, path, n in spans_from(m):
        srcs = Counter(m.tu_src[i] for i in range(len(m.rfuncs))
                       if m.rfuncs[i][0] >= s and m.rfuncs[i][1] <= e)
        best = "census" if srcs.get("census") else ("aug6" if srcs.get("aug6") else "fill")
        tu_lines.append(f"0x{s:08X} 0x{e:08X} {path or VENDOR}  # {n} funcs, {best}")
    RETAIL_TUS.write_text("\n".join(tu_lines) + "\n")
    return n_twin, n_ord, n_anon


# ------------------------------------------------------------------- checks --
AUG6_ASM = AUG6 / "asm" / "aug6"
INSN_RE = re.compile(r"^\s*/\* [0-9A-Fa-f]+ ([0-9A-Fa-f]{8}) ([0-9A-Fa-f]{8}) \*/\s*(.*)$")
RELOC_RE = re.compile(r"%hi\(|%lo\(|%gp_rel\(|\bjal\s+\w|\bj\s+[A-Za-z_]")


def parse_s(path: Path, want: set[str]) -> dict[str, list[tuple[int, bool]]]:
    """glabel -> [(word, carries_a_reloc_annotation), ...] for the wanted names."""
    out: dict[str, list[tuple[int, bool]]] = {}
    cur = None
    for line in path.read_text(errors="replace").splitlines():
        if line.startswith("glabel "):
            cur = line.split()[1].strip()
            if cur in want:
                out.setdefault(cur, [])
            continue
        if cur not in out:
            continue
        mm = INSN_RE.match(line)
        if mm:
            out[cur].append((struct.unpack("<I", bytes.fromhex(mm.group(2)))[0],
                             bool(RELOC_RE.search(mm.group(3)))))
    return out


def lockstep_verify(m, rng, want=40):
    """Compare retail words against splat's symbolic aug6 disassembly.

    Uses splat's own reloc annotations rather than this tool's normalizer, so
    it is an independent check on the twin correspondence."""
    import subprocess
    if not AUG6_ASM.is_dir():
        return 0, 0, len(m.twins)
    names, _ = aug6_syms()
    cand = [(r, a) for r, a in sorted(m.twins.items()) if names.get(m.afuncs[a][0])]
    if not cand:
        return 0, 0, 0
    sample = rng.sample(cand, min(want, len(cand)))
    by_name = {names[m.afuncs[a][0]]: (r, a) for r, a in sample}
    pat = "^glabel (" + "|".join(re.escape(n) for n in by_name) + ")$"
    try:
        files = subprocess.run(["grep", "-rlE", pat, str(AUG6_ASM)],
                               capture_output=True, text=True, timeout=300).stdout.split()
    except Exception:
        return 0, 0, len(sample)
    parsed: dict[str, list[tuple[int, bool]]] = {}
    for f in files:
        for k, v in parse_s(Path(f), set(by_name)).items():
            if v and k not in parsed:
                parsed[k] = v
    ok = bad = 0
    for name, (r, a) in by_name.items():
        aw = parsed.get(name)
        if not aw:
            continue
        rs, re_ = m.rfuncs[r]
        rw = list(struct.unpack(f"<{(re_-rs)//4}I", m.rrom[rs - TEXT_VMA: re_ - TEXT_VMA]))
        while rw and rw[-1] == 0:
            rw.pop()
        aa = [w for w, _ in aw]
        while aa and aa[-1] == 0:
            aa.pop()
        aw = aw[:len(aa)]
        if len(aw) != len(rw):
            bad += 1
            continue
        if all(w == rw[k] or reloc for k, (w, reloc) in enumerate(aw)):
            ok += 1
        else:
            bad += 1
    return ok, bad, len(sample) - ok - bad


def gates(m: Model) -> bool:
    ok = True

    def chk(cond, label, detail=""):
        nonlocal ok
        print(f"  [{'OK ' if cond else 'FAIL'}] {label}{(' — ' + detail) if detail else ''}")
        if not cond:
            ok = False

    n = len(m.rfuncs)
    chk(5100 <= n <= 5300, f"function-start count in 5100..5300", str(n))
    starts = {s for s, _ in m.rfuncs}
    chk(0x100000 in starts, "0x00100000 is a function start (crt0 block holding _start)")
    chk(TEXT_VMA + RETAIL_TEXT_SZ == m.rfuncs[-1][1], ".text fully covered",
        f"0x{m.rfuncs[-1][1]:08X}")

    # no span crosses a census anchor
    bad = []
    for s, e, path, _ in spans_from(m):
        for i, (fs, fe) in enumerate(m.rfuncs):
            if fs >= s and fe <= e and m.anchor[i] and m.anchor[i] != path:
                bad.append((hex(fs), m.anchor[i], path))
    chk(not bad, "no TU span crosses a __FILE__ census anchor",
        f"{len(bad)} violations {bad[:3]}" if bad else "")

    # every span edge is a function start
    edges = {s for s, _, _, _ in spans_from(m)}
    chk(edges <= starts, "every span edge coincides with a function start")

    # spans are contiguous per file (a file must not reappear)
    seq = [p for _, _, p, _ in spans_from(m) if p and p != VENDOR]
    chk(len(seq) == len(set(seq)), "each source file occupies exactly one span",
        f"repeats: {[k for k, v in Counter(seq).items() if v > 1][:5]}")

    # re-verify a sample of twins by recomputing the normalized hash
    import random
    rng = random.Random(20260728)
    sample = rng.sample(sorted(m.twins.items()), min(40, len(m.twins)))
    bad_h = 0
    for ri, ai in sample:
        rs, re_ = m.rfuncs[ri]
        as_, ae = m.afuncs[ai]
        rw = list(struct.unpack(f"<{(re_-rs)//4}I", m.rrom[rs - TEXT_VMA: re_ - TEXT_VMA]))
        aw = list(struct.unpack(f"<{(ae-as_)//4}I", m.arom[as_ - TEXT_VMA: ae - TEXT_VMA]))
        while rw and rw[-1] == 0:
            rw.pop()
        while aw and aw[-1] == 0:
            aw.pop()
        if normalize(rw) != normalize(aw):
            bad_h += 1
    chk(bad_h == 0, f"{len(sample)} sampled twins recompute equal (reloc-normalized)",
        f"{bad_h} mismatched" if bad_h else "")

    # Independent of the hash: lockstep-walk splat's SYMBOLIC aug6 disassembly
    # against the retail words (the decomp/retail_port/portmap.py technique).
    # Every word that differs must be explained by a relocation splat itself
    # annotated (%hi / %lo / %gp_rel / j / jal) -- nothing may differ silently.
    ok_n, bad_n, skipped = lockstep_verify(m, rng, want=40)
    chk(bad_n == 0 and ok_n >= 30,
        f"lockstep symbolic walk vs splat aug6 .s: {ok_n} verified, "
        f"{bad_n} unexplained, {skipped} without a .s")

    chk(not m.conflicts, "no aug6 attribution contradicts a __FILE__ anchor",
        f"{len(m.conflicts)}: {m.conflicts[:3]}" if m.conflicts else "")
    return ok


def report(m: Model):
    n = len(m.rfuncs)
    named_twin = sum(1 for i in range(n) if m.name[i] and m.name_src[i] == "twin")
    named_ord = sum(1 for i in range(n) if m.name[i] and m.name_src[i] == "ordinal")
    print(f"retail .text functions       : {n}")
    print(f"aug6  .text functions        : {len(m.afuncs)}")
    print(f"  hash twins (order-const.)  : {m.n_global}")
    print(f"  hash twins (relocated .o)  : {len(m.moved)}")
    print(f"  ordinal-forced             : {len(m.ordinal)}")
    print(f"  no counterpart             : {n - len(m.aug_of)}")
    print(f"named — twin                 : {named_twin}")
    print(f"named — provisional-ordinal  : {named_ord}")
    print(f"unnamed (func_<VMA>)         : {n - named_twin - named_ord}")
    print(f"__FILE__ .c strings in pool  : {len(m.pool_files)}"
          f"  (anchored from .text: {len({a for a in m.anchor if a})})")
    print(f"functions with a source file : {sum(1 for t in m.tu if t and t != VENDOR)}"
          f"  (census {m.tu_src.count('census')}, aug6 {m.tu_src.count('aug6')},"
          f" fill {m.tu_src.count('fill')})")
    agree = sum(1 for i in range(n)
                if m.anchor[i] and i in m.aug_of
                and retail_path(m.aug_tu[m.aug_of[i]]) == m.anchor[i])
    both = sum(1 for i in range(n) if m.anchor[i] and i in m.aug_of)
    print(f"twin x census cross-check    : {agree}/{both} agree"
          f"  (independent oracles: __FILE__ string vs aug6 TU)")
    sp = spans_from(m)
    print(f"source-file spans            : {sum(1 for _,_,p,_ in sp if p and p != VENDOR)}"
          f" (+{sum(1 for _,_,p,_ in sp if not p or p == VENDOR)} vendor)")
    bydir = Counter(p.rsplit("/", 1)[0] for _, _, p, _ in sp if p and p != VENDOR)
    print("  by retail directory        : "
          + ", ".join(f"{d}/ {c}" for d, c in sorted(bydir.items())))
    anchored = {a for a in m.anchor if a}
    print(f"  spans backed by a __FILE__ anchor : {len(anchored)}"
          f" of {sum(1 for _,_,p,_ in sp if p and p != VENDOR)}")
    print(f"unequal alignment gaps       : {len(m.gap_unequal)}"
          f" ({sum(r1-r0 for r0,r1,_,_ in m.gap_unequal)} retail funcs unaligned)")
    if m.split_files:
        print(f"files whose carried-over attribution was non-contiguous "
              f"(repaired): {len(m.split_files)}")
        for f, cls in m.split_files:
            print(f"    {f:34s} clusters {cls}")
    if m.gap_unequal:
        print("  ambiguous regions (retail funcs | aug6 funcs | files touched):")
        for r0, r1, a0, a1 in m.gap_unequal:
            if (r1 - r0) < 5 and (a1 - a0) < 5:
                continue
            files = sorted({m.tu[i] for i in range(r0, min(r1, len(m.tu))) if m.tu[i]})
            print(f"    0x{m.rfuncs[min(r0,len(m.rfuncs)-1)][0]:08X}"
                  f"  {r1-r0:3d} | {a1-a0:3d}   {files}")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--report", action="store_true", help="diagnostics only, write nothing")
    ap.add_argument("--check", action="store_true", help="run sanity gates, write nothing")
    args = ap.parse_args()
    m = build()
    if args.report or args.check:
        report(m)
        print("gates:")
        return 0 if gates(m) else 1
    n_twin, n_ord, n_anon = emit(m)
    report(m)
    print("gates:")
    ok = gates(m)
    print(f"wrote {RETAIL_SYMS.relative_to(RETAIL)}  "
          f"({n_twin} twin-named, {n_ord} ordinal-named, {n_anon} func_<VMA>)")
    print(f"wrote {RETAIL_TUS.relative_to(RETAIL)}")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
