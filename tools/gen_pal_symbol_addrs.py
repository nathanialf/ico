#!/usr/bin/env python3
"""Regenerate config/symbol_addrs.pal.txt for the ICO PAL retail boot ELF.

WHAT THIS DOES
--------------
The PAL retail ELF (SCES_507.60) is stripped: no symbol table, no TU
boundaries.  This tool recovers both and writes:

  * config/symbol_addrs.pal.txt          (tracked)   -- one `type:func` entry
        per recovered PAL function start, with a name and a source-file
        trailer.
  * baserom/pal/text_tu_boundaries.txt   (untracked) -- contiguous .text spans
        per recovered source file, in link order.
  * the `.text` part of config/ico.pal.yaml's subsegment list -- one
        subsegment per recovered TU span, in link order.

USAGE
-----
    tools/gen_pal_symbol_addrs.py            # regenerate all three outputs
    tools/gen_pal_symbol_addrs.py --report   # diagnostics only, write nothing
    tools/gen_pal_symbol_addrs.py --check    # re-verify sanity gates, no write
    tools/gen_pal_symbol_addrs.py --no-yaml  # leave config/ico.pal.yaml alone

Idempotent.  Everything above the BEGIN GENERATED banner in
config/symbol_addrs.pal.txt is preserved byte-for-byte (hand-written seeds);
re-running rewrites only the block below it.  A generated entry is suppressed
if its VMA or its name is already claimed by the seed block.  In the yaml,
only the run of `.text` subsegments is rewritten (everything from the first
subsegment up to but excluding the first entry at or past the end of .text);
the vutext / data / rodata / lit4 / sdata / sbss / bss entries are untouched,
and a subsegment whose start offset survives the regeneration keeps whatever
type and name it already had (so a TU flipped from `asm` to `c` stays `c`).

PROVENANCE OF NAMES -- read before trusting one
-----------------------------------------------
Names and source-file attribution come from the PAL retail disc's OWN
shipped metadata: baserom/pal/SRCFILE.TXT, an `objdump -dl` listing of the
2002-01-16 "MasterVer1.00EU" `main.elf`, and baserom/pal/MAIN.MAP, a GNU ld
link map.  Both files shipped on the retail SCES-50760 disc -- officially
distributed retail media, not leaked source (docs/LEGAL.md).  No leaked SDK,
leaked source, or debug build is an input to this tool.

!! THE LISTING IS A DIFFERENT LINK !!  SRCFILE.TXT's .text is
0x00100000..0x0028DB34 (0x18DB34); the retail PAL ELF's is
0x00100000..0x00289BC4 (0x189BC4) -- 0x3F70 smaller.  MAIN.MAP is a THIRD
link again (.text 0x16A29C, and it carries a `sampleMode.o` member that does
not appear in the listing at all).  So:

  * SRCFILE.TXT's ORDER, NAMES, SOURCE PATHS and INSTRUCTION WORDS are
    oracles; its ADDRESSES are not.  Every address in the output is a PAL rom
    address, recovered by correlation, never copied from the listing.
  * MAIN.MAP is used for its member ORDER and member NAME SET only, and only
    as a cross-check -- never for an address.

METHOD
------
1. FUNCTION STARTS -- branch-aware boundary scan of .text on
   baserom/pal/baseelf.rom (the algorithm in tools/correlate_funcs.py): a
   terminator (jr/j/jalr) ends a function only if no backward-reaching branch
   target lies past it; inter-function zero padding is skipped.  Rom-native
   and reliable; the one part of the output that is not provisional.

2. LISTING FUNCTIONS -- SRCFILE.TXT label lines give a start address, a name
   and (via the interleaved `func():` / `/path:line` lines objdump -l emits)
   an owning source file.  A label's OWN lines -- those under a `func():`
   header equal to the label -- decide its owner, so a static inlined into a
   neighbour does not steal the attribution.  Instruction words come from the
   listing itself; objdump's `...` zero elisions are re-expanded from the
   address gaps.

3. CORRESPONDENCE -- reloc-normalized instruction-stream SHA-1 equality
   between listing functions and rom functions.  The normalizer is
   decomp/retail_port/correlate.py:normalize() (shared with
   tools/gen_us_symbol_addrs.py): it masks j/jal targets, lui immediates,
   %lo-pair immediates and $gp-relative displacements, so a function that was
   not edited between the two links hashes identically across them.  Matching
   is order-constrained (the two link orders agree -- the whole twin set is a
   single monotone run) and applied recursively inside the gaps it opens,
   then re-run per TU window, then an order-free pass for members that moved.
   Finally, ordinal fill: inside a gap of equal length on both sides the
   correspondence is forced by link order.

4. __FILE__ CENSUS -- the SCE assert macro leaks __FILE__ strings into the
   PAL rom's .rodata/.sdata.  For every rom function, replay lui/%lo pairs
   and see whether any resolves to a "<dir>/<name>.c" string; if so that
   function provably belongs to that file.  This is an INDEPENDENT oracle: it
   overrides the listing attribution, and a listing name whose TU contradicts
   a census anchor is dropped.

TIERS (colon-free tags -- splat parses `key:value` in these comments as
attributes, so a tag may never contain a colon)

  * untagged              -- the PAL function is reloc-normalized
                             byte-identical to the named listing function.
  * provisional-ordinal   -- no hash twin; position forced by link order
                             between two twins in a gap of equal length on
                             both sides.  Verify before relying on it.
  Anything else keeps splat's func_<VMA> auto-name.
"""
from __future__ import annotations

import argparse
import bisect
import hashlib
import random
import re
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

# ---------------------------------------------------------------- constants --
HERE = Path(__file__).resolve().parent
ROOT = HERE.parent

PAL_ROM = ROOT / "baserom" / "pal" / "baseelf.rom"
PAL_SYMS = ROOT / "config" / "symbol_addrs.pal.txt"
PAL_TUS = ROOT / "baserom" / "pal" / "text_tu_boundaries.txt"
PAL_YAML = ROOT / "config" / "ico.pal.yaml"
LISTING = ROOT / "baserom" / "pal" / "SRCFILE.TXT"
MAINMAP = ROOT / "baserom" / "pal" / "MAIN.MAP"

TEXT_VMA = 0x00100000
PAL_TEXT_SZ = 0x00189BC4          # .text sh_size from baserom/pal/baseelf.elf
PAL_VUTEXT_VMA = 0x00289BD0       # .text end + 12 B pad
# rom offset == VMA - TEXT_VMA for every section in the objcopy binary view,
# so the __FILE__ string pool (.data .. end of .sdata) is addressable directly.
PAL_DATA_LO, PAL_DATA_HI = 0x0028ED00, 0x0063C0F6

BANNER = ("// ==== BEGIN GENERATED — tools/gen_pal_symbol_addrs.py — "
          "do not hand-edit below this line ====")

# The 2002-01-16 EU source tree root the listing's paths are rooted at.
SRC_ROOT = "/backup/ico/20020116MasterVer1.00EU/ico2/"

# Retail source-tree layout, same convention as tools/gen_us_symbol_addrs.py:
# the leading per-programmer directory is dropped (`sugipon/src/box.c` ->
# `src/box`).  The MPEG middleware keeps its namespace -- the rom's own string
# pool carries "ito/include/mv_defs.h" -- so `ito/mpeg/*` stays `ito/mpeg/*`.
KEEP_PREFIX = ("ito/mpeg/",)

VENDOR = "(vendor)"

FUNC_NAME_RE = re.compile(r"func_00[0-9A-F]{6}\Z")
PATH_RE = re.compile(r"(?:[A-Za-z0-9_+-]+/)*[A-Za-z0-9_.+-]+\.[ch]\Z")
SYM_RE = re.compile(
    r"^\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)\s*;\s*//\s*type:func(?:\s*//\s*(\S+))?")
ANY_SYM_RE = re.compile(r"^\s*(\w+)\s*=\s*0x([0-9A-Fa-f]+)\s*;")

# ---- listing grammar --------------------------------------------------------
L_LABEL = re.compile(r"^([0-9a-f]{16}) <(.*)>:$")
L_INSN = re.compile(r"^ *([0-9a-f]+):\t([0-9a-f]{8}) \t")
L_CTX = re.compile(r"^([A-Za-z_$.][\w$.]*)\(\):$")
L_PATH = re.compile(r"^([^\s:]+):(\d+)$")
# A label that names a real function: a C identifier, optionally carrying
# gcc's static-function discriminator suffix (`setMatrix.100`).  Everything
# else objdump prints in .text is an intra-function artifact -- assembler
# local labels (`$L12`) and the stabs `__gnu_compiled_c` / `gcc2_compiled.`
# markers -- and must NOT split a function, or the instruction-stream hash of
# the function it sits inside is destroyed.
L_FUNC_LABEL = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*(?:\.[0-9]+)?$")
L_NOT_FUNC = {"__gnu_compiled_c", "gcc2_compiled."}
DISCRIM_RE = re.compile(r"\.([0-9]+)$")


# --------------------------------------------------------- boundary scanning --
JR = 0x03E00008


def scan_text(rom: bytes, text_sz: int) -> list[tuple[int, int]]:
    """Branch-aware .text function boundary scan.  Returns [(start,end), ...].

    Identical to tools/gen_us_symbol_addrs.py:scan_text (which is
    tools/correlate_funcs.py's algorithm); duplicated rather than imported so
    the two version generators cannot drift apart silently."""

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


def hash_words(words: list[int]) -> tuple[str | None, int]:
    ws = list(words)
    while ws and ws[-1] == 0:
        ws.pop()
    if not ws:
        return None, 0
    nw = normalize(ws)
    return hashlib.sha1(struct.pack("<%dI" % len(nw), *nw)).hexdigest(), len(nw)


def rom_hashes(rom: bytes, funcs) -> list[tuple[str | None, int]]:
    out = []
    for start, end in funcs:
        n = (end - start) // 4
        out.append(hash_words(list(struct.unpack(
            f"<{n}I", rom[start - TEXT_VMA: start - TEXT_VMA + 4 * n]))))
    return out


# ---------------------------------------------------------- listing parsing --
class LFunc:
    __slots__ = ("vma", "label", "name", "discrim", "words_at",
                 "own", "any", "rows", "own_rows", "entry_line", "entry_path",
                 "start", "end", "tu", "hash", "ninsn")

    # `own` / `any`   : Counter path -> instruction rows attributed to it
    #                   (`own` = rows under a `func():` header equal to this
    #                   label, i.e. this function's own code rather than a
    #                   static inlined into it).
    # `rows`/`own_rows`: path -> [rows, first_line, last_line], same split.
    # `entry_line`/`entry_path`: the row describing the function's FIRST
    #                   instruction -- its definition line.  min(rows) is not
    #                   that: a same-file static inlined into the function
    #                   drags the minimum back to wherever it was defined.


def parse_listing(path: Path) -> list[LFunc]:
    """SRCFILE.TXT -> ordered listing functions, .text only.

    Non-function labels ($L12, __gnu_compiled_c) are dropped so they cannot
    split the function they sit inside."""
    out: list[LFunc] = []
    cur: LFunc | None = None
    ctx: str | None = None
    with path.open(errors="replace") as fh:
        for line in fh:                        # universal newlines: file is CRLF
            line = line.rstrip("\n")
            if line.startswith("Disassembly of section .vutext"):
                break
            m = L_LABEL.match(line)
            if m:
                label = m.group(2)
                if label in L_NOT_FUNC or not L_FUNC_LABEL.match(label):
                    continue                   # intra-function artifact
                f = LFunc()
                f.vma = int(m.group(1), 16)
                f.label = label
                d = DISCRIM_RE.search(label)
                f.discrim = d.group(1) if d else None
                f.name = label[: d.start()] if d else label
                f.words_at = []
                f.own = Counter()
                f.any = Counter()
                f.rows = {}
                f.own_rows = {}
                f.entry_line = None
                f.entry_path = None
                out.append(f)
                cur, ctx = f, None
                continue
            if cur is None:
                continue
            mc = L_CTX.match(line)
            if mc:
                ctx = mc.group(1)
                continue
            mp = L_PATH.match(line)
            if mp:
                p = relpath(mp.group(1))
                ln = int(mp.group(2))
                cur.any[p] += 1
                if cur.entry_line is None:
                    cur.entry_line, cur.entry_path = ln, p
                r = cur.rows.setdefault(p, [0, ln, ln])
                r[0] += 1
                r[1], r[2] = min(r[1], ln), max(r[2], ln)
                if ctx == cur.label:
                    cur.own[p] += 1
                    r = cur.own_rows.setdefault(p, [0, ln, ln])
                    r[0] += 1
                    r[1], r[2] = min(r[1], ln), max(r[2], ln)
                continue
            mi = L_INSN.match(line)
            if mi:
                cur.words_at.append((int(mi.group(1), 16), int(mi.group(2), 16)))
    # spans + words (objdump's `...` elides runs of ZERO bytes; re-expand them
    # from the address gaps, then strip the trailing inter-function padding).
    for i, f in enumerate(out):
        f.start = f.vma
        f.end = out[i + 1].vma if i + 1 < len(out) else (
            f.words_at[-1][0] + 4 if f.words_at else f.vma)
        n = max(0, (f.end - f.start) // 4)
        ws = [0] * n
        for off, w in f.words_at:
            k = (off - f.start) // 4
            if 0 <= k < n:
                ws[k] = w
        f.hash, f.ninsn = hash_words(ws)
        f.words_at = None                      # free
    return out


def relpath(p: str) -> str:
    return p[len(SRC_ROOT):] if p.startswith(SRC_ROOT) else p


def retail_path(listing_path: str | None) -> str | None:
    """listing source path (`<programmer>/<subdir>/<stem>.c`) -> repo TU path."""
    if not listing_path or listing_path == VENDOR:
        return listing_path
    if not listing_path.endswith(".c") or listing_path.startswith("/"):
        return None
    stem = listing_path[:-2]
    parts = stem.split("/")
    if len(parts) < 2:
        return None
    tail = "/".join(parts[1:])
    for keep in KEEP_PREFIX:
        if tail.startswith(keep.split("/", 1)[1]):
            return parts[0] + "/" + tail
    return tail


def mainmap_archives() -> tuple[dict[str, str], list[str]]:
    """symbol -> archive short name, plus the archive ORDER, from MAIN.MAP.

    MAIN.MAP is a third link: its ADDRESSES describe neither the listing nor
    the retail rom and are ignored here.  Its member ORDER and the
    symbol->member association are what it is used for -- enough to say which
    library archive owns a vendor function, which is how the vendor head and
    the 783-function vendor tail get labelled instead of being one opaque
    blob."""
    sym: dict[str, str] = {}
    order: list[str] = []
    cur = None
    if not MAINMAP.exists():
        return sym, order
    for line in MAINMAP.read_text(errors="replace").splitlines():
        line = line.rstrip()
        m = re.match(r"^ \.text\s+0x[0-9a-f]+\s+0x[0-9a-f]+\s+(\S+)\s*$", line)
        if m:
            path = m.group(1)
            cur = path.rsplit("/", 1)[-1].split("(", 1)[0]
            if cur not in order:
                order.append(cur)
            continue
        m = re.match(r"^ {16}0x[0-9a-f]+\s+(\S+)\s*$", line)
        if m and cur:
            sym.setdefault(m.group(1), cur)
    return sym, order


def mainmap_members() -> list[str]:
    """ico2000.a / vendor .text member names, in MAIN.MAP pull-in order.

    ORDER and NAMES only -- MAIN.MAP is a third link and its ADDRESSES do not
    describe either the listing or the retail rom."""
    out = []
    if not MAINMAP.exists():
        return out
    for line in MAINMAP.read_text(errors="replace").splitlines():
        m = re.match(r"^ \.text\s+0x[0-9a-f]+\s+0x[0-9a-f]+\s+(\S+)\s*$", line.rstrip())
        if not m:
            continue
        member = m.group(1)
        stem = member.rsplit("(", 1)[-1].rstrip(")")
        out.append(stem[:-2] if stem.endswith(".o") else stem)
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


def census(rom: bytes, funcs, pool: dict[int, str], text_sz: int,
           known: set[str] | None = None,
           alias: dict[str, str] | None = None) -> list[str | None]:
    """Per rom function: the __FILE__ path it references, if any.

    Only ADDRESS FORMATION counts (`lui` + `addiu` / `ori` / `daddiu`): the
    SCE assert macro passes __FILE__ as a pointer, so a load or a store that
    merely happens to land on the string's VMA is a coincidence, not a
    reference.  Measured on the PAL rom: allowing loads/stores (the shape
    tools/gen_us_symbol_addrs.py uses) makes `sw $zero,0x28($v0)` after an
    unrelated `lui $v0,0x55` anchor six vendor-tail functions to
    src/StageAnimation.c, whose string sits at 0x00550028.  The hi register
    is also killed as soon as anything else redefines it, so a stale `lui`
    cannot pair with an `addiu` hundreds of instructions later.

    `known`, when given, is the set of TUs the listing actually attributes.
    An anchor outside it (`libscf.c` -- an SCE library's own __FILE__, in the
    vendor tail) is dropped rather than manufacturing a game TU."""

    def w(off):
        return struct.unpack_from("<I", rom, off)[0]

    def dest(x):
        """The GPR this instruction writes, or None.  Deliberately
        conservative: anything not recognised writes nothing, which can only
        keep a `lui` alive too long, never kill a real hi/lo pair."""
        op = (x >> 26) & 0x3F
        if op == 0:
            f = x & 0x3F
            return None if f in (8, 9) else (x >> 11) & 0x1F
        if op == 3:
            return 31
        if op == 1 and ((x >> 16) & 0x1F) in (0x10, 0x11):
            return 31
        if op in ITYPE_WRITE_RT and op not in (0x28, 0x29, 0x2A, 0x2B, 0x2E,
                                               0x2F, 0x31, 0x35, 0x36, 0x39,
                                               0x3D, 0x3E, 0x3F, 0x1F):
            return (x >> 16) & 0x1F
        if op == 0x1C:
            return (x >> 11) & 0x1F
        if op in (0x10, 0x11, 0x12) and ((x >> 21) & 0x1F) in (0, 1, 2, 3):
            return (x >> 16) & 0x1F
        return None

    anchors: list[str | None] = []
    for start, end in funcs:
        his: dict[int, int] = {}
        got = None
        for q in range(start - TEXT_VMA, min(end, TEXT_VMA + text_sz) - TEXT_VMA, 4):
            x = w(q)
            op = (x >> 26) & 0x3F
            if op == 0x0F:                      # lui
                rt = (x >> 16) & 0x1F
                if rt:
                    his[rt] = (x & 0xFFFF) << 16
                continue
            if op in (0x09, 0x0D, 0x19):        # addiu / ori / daddiu
                rs = (x >> 21) & 0x1F
                lo = x & 0xFFFF
                if op != 0x0D and lo >= 0x8000:
                    lo -= 0x10000
                if rs in his and his[rs] + lo in pool:
                    path = pool[his[rs] + lo]
                    if path.endswith(".c") and (known is None
                                                or retail_tu(path) in known):
                        tu = retail_tu(path)
                        if alias and tu in alias:
                            tu = alias[tu]
                        got = tu + ".c"
                        break
            d = dest(x)
            if d is not None and d in his:
                del his[d]
        anchors.append(got)
    return anchors


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


def align_range(rh, lh, rlo0, rhi0, llo0, lhi0, max_depth=10, min_insns=3):
    """Order-constrained recursive unique-hash matching inside a rectangle."""

    def rec(rlo, rhi, llo, lhi, depth):
        if rlo >= rhi or llo >= lhi:
            return []
        lbyh, rbyh = defaultdict(list), defaultdict(list)
        for i in range(llo, lhi):
            if lh[i][0] and lh[i][1] >= min_insns:
                lbyh[lh[i][0]].append(i)
        for i in range(rlo, rhi):
            if rh[i][0] and rh[i][1] >= min_insns:
                rbyh[rh[i][0]].append(i)
        pairs = []
        for h, lis in lbyh.items():
            ris = rbyh.get(h)
            if ris and len(lis) == 1 and len(ris) == 1:
                pairs.append((ris[0], lis[0]))
        if not pairs:
            return []
        pairs.sort()
        pairs = lis_by_second(pairs)
        out = list(pairs)
        if depth < max_depth:
            pr, pl = rlo, llo
            for r, a in pairs + [(rhi, lhi)]:
                out += rec(pr, r, pl, a, depth + 1)
                pr, pl = r + 1, a + 1
        return out

    return sorted(set(rec(rlo0, rhi0, llo0, lhi0, 0)))


def free_pass(rh, lh, n_r, n_l, twin_r, twin_l, min_insns=8):
    """Order-free unique-hash pass for members whose link position moved."""
    lbyh, rbyh = defaultdict(list), defaultdict(list)
    for i in range(n_l):
        if i not in twin_l and lh[i][0] and lh[i][1] >= min_insns:
            lbyh[lh[i][0]].append(i)
    for i in range(n_r):
        if i not in twin_r and rh[i][0] and rh[i][1] >= min_insns:
            rbyh[rh[i][0]].append(i)
    extra = []
    for h, lis in lbyh.items():
        ris = rbyh.get(h)
        if ris and len(lis) == 1 and len(ris) == 1:
            extra.append((ris[0], lis[0]))
    return sorted(extra)


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


# ------------------------------------------------------------------- driver --
class Model:
    pass


def listing_tus(lf: list[LFunc], members: set[str], verbose=False) -> dict:
    """Assign each listing function a TU key (repo path), in place as `.tu`.

    A .o's .text is contiguous, which is the whole lever:

      * a function's owner is the dominant path of its OWN line records (the
        rows under a `func():` header equal to its label), so a static that
        was inlined into a neighbour cannot steal the attribution;
      * only a `.c` under the EU source root can NAME a TU.  A `.h` or a
        `.c.inc` owner means the body was #included, so it inherits the TU it
        sits inside;
      * if two `.c` files' function ranges OVERLAP they cannot be two members
        -- one was #included into the other.  Merging overlapping ranges
        therefore recovers the real .o partition.  The listing proves
        sugipon/src/switch.c is compiled inside sugipon/src/box.c exactly
        this way (its functions bracket box.c's on both sides).  The merged
        member is named after the file MAIN.MAP lists as a `.o`, when exactly
        one of the overlapping files is;
      * pathless functions are vendor archive members with no debug info.
        They are labelled VENDOR and never forward-filled from a game TU.
    """
    n = len(lf)
    raw = []
    for f in lf:
        c = f.own or f.any
        raw.append(c.most_common(1)[0][0] if c else None)
    key = [p if (p and p.endswith(".c") and not p.startswith("/")) else None
           for p in raw]

    # --- merge overlapping per-file ranges into .o groups --------------------
    rng: dict[str, list[int]] = {}
    for i, p in enumerate(key):
        if not p:
            continue
        r = rng.setdefault(p, [i, i])
        r[0], r[1] = min(r[0], i), max(r[1], i)
    order = sorted(rng.items(), key=lambda kv: kv[1][0])
    groups: list[tuple[int, int, list[str]]] = []
    for path, (lo, hi) in order:
        if groups and lo <= groups[-1][1]:
            g = groups[-1]
            groups[-1] = (g[0], max(g[1], hi), g[2] + [path])
        else:
            groups.append((lo, hi, [path]))
    coalesced = {}
    for lo, hi, paths in groups:
        if len(paths) == 1:
            name = paths[0]
        else:
            named = [p for p in paths if p.rsplit("/", 1)[-1][:-2] in members]
            if len(named) == 1:
                name = named[0]
            else:
                cnt = Counter(key[i] for i in range(lo, hi + 1) if key[i])
                name = cnt.most_common(1)[0][0]
            coalesced[name] = sorted(p for p in paths if p != name)
        for i in range(lo, hi + 1):
            key[i] = name

    # --- interpolate the #included bodies at a member's edges ----------------
    # Everything between two functions of the same member is that member's.
    # A `.h` / `.c.inc` body that lands at a member BOUNDARY is ambiguous; it
    # goes to the member it follows, since the linker emits each .o's .text as
    # one block and the run it trails is the one still open.
    lo_game = next((i for i, p in enumerate(key) if p), n)
    hi_game = next((i for i in range(n - 1, -1, -1) if key[i]), -1)
    prev = None
    stray = []
    for i in range(n):
        if key[i]:
            prev = key[i]
        elif lo_game < i < hi_game and prev is not None:
            key[i] = prev
            stray.append(i)

    for i, f in enumerate(lf):
        f.tu = retail_path(key[i]) if key[i] else VENDOR
        if f.tu is None:
            f.tu = VENDOR
    return {"coalesced": coalesced, "edge_filled": len(stray),
            "groups": len(groups)}


def self_label(m, corr, final=False):
    """Attribute every rom function to a source file.

    census anchor  >  listing TU carried over by a twin/ordinal
                   >  forward fill inside an already-attributed region.
    A linker emits each .o's .text contiguously, so a file occupies exactly
    one span; where the carried-over attribution says otherwise, the cluster
    holding the census anchors wins (else the largest) and the strays drop
    back to fill."""
    n = len(m.rfuncs)
    labels: list[str | None] = [None] * n
    src = [""] * n
    conflicts = []
    for i in range(n):
        derived = m.lf[corr[i]].tu if i in corr else None
        if m.anchor[i]:
            labels[i] = m.anchor[i][:-2] if m.anchor[i].endswith(".c") else m.anchor[i]
            src[i] = "census"
            if derived and derived != VENDOR and derived != labels[i]:
                conflicts.append((f"0x{m.rfuncs[i][0]:08X}", derived, labels[i]))
        elif derived:
            labels[i] = derived
            src[i] = "listing"

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
    if final:
        return labels, src, conflicts, split_files
    return labels


def build() -> Model:
    m = Model()
    m.rom = PAL_ROM.read_bytes()
    m.rfuncs = scan_text(m.rom, PAL_TEXT_SZ)
    m.rh = rom_hashes(m.rom, m.rfuncs)
    m.lf = parse_listing(LISTING)
    m.lh = [(f.hash, f.ninsn) for f in m.lf]
    m.members = mainmap_members()
    m.sym_arch, m.arch_order = mainmap_archives()
    m.tu_meta = listing_tus(m.lf, set(m.members))

    pool = string_pool(m.rom, PAL_DATA_LO, PAL_DATA_HI)
    m.pool_files = sorted({p for p in pool.values() if p.endswith(".c")})
    # __FILE__ strings in this rom are already repo-relative ("src/Matrix.c",
    # "ios/cdvd.c"), i.e. the listing path with its per-programmer directory
    # already stripped -- so they compare directly against LFunc.tu.
    m.known_tus = {f.tu for f in m.lf if f.tu != VENDOR}
    # A file the listing proves was #included into a member (switch.c inside
    # box.c) still has its own __FILE__ string in the rom; map that anchor
    # onto the host TU rather than dropping it.
    m.tu_alias = {}
    for host, kids in m.tu_meta["coalesced"].items():
        h = retail_path(host)
        for kid in kids:
            k = retail_path(kid)
            if h and k:
                m.tu_alias[k] = h
    m.anchor = census(m.rom, m.rfuncs, pool, PAL_TEXT_SZ,
                      m.known_tus | set(m.tu_alias), m.tu_alias)
    m.pool_foreign = sorted(p for p in m.pool_files
                            if retail_tu(p) not in m.known_tus)

    # ---- correspondence -----------------------------------------------------
    n_r, n_l = len(m.rfuncs), len(m.lf)
    pairs = align_range(m.rh, m.lh, 0, n_r, 0, n_l)
    m.twins = dict(pairs)
    m.n_global = len(pairs)

    prov = self_label(m, dict(m.twins))
    m.lis_tu_range: dict[str, tuple[int, int]] = {}
    for j, f in enumerate(m.lf):
        if f.tu == VENDOR:
            continue
        lo, hi = m.lis_tu_range.get(f.tu, (j, j))
        m.lis_tu_range[f.tu] = (min(lo, j), max(hi, j))

    m.moved = {}
    used_l = set(m.twins.values())
    for path, r0, r1 in windows(prov):
        rng = m.lis_tu_range.get(path)
        if not rng:
            continue
        for r, a in align_range(m.rh, m.lh, r0, r1, rng[0], rng[1] + 1):
            if r not in m.twins and a not in used_l:
                m.twins[r] = a
                m.moved[r] = a
                used_l.add(a)
    for r, a in free_pass(m.rh, m.lh, n_r, n_l, set(m.twins), used_l):
        if r not in m.twins and a not in used_l:
            m.twins[r] = a
            m.moved[r] = a
            used_l.add(a)

    # Pass D: ordinal fill inside gaps of equal length on both sides.
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
    m.n_runs = len(runs)
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

    # Pass D': inside a gap the lengths DISAGREE on, the correspondence is
    # still forced at the two ends -- link order pins the first unmatched
    # function on each side to the other, and the next, until the two streams
    # actually diverge.  Extend inward from both ends while the instruction
    # counts agree exactly, and stop at the first disagreement.  Size equality
    # plus link order is weaker than a hash twin, so these are tagged
    # `provisional-ordinal` like the rest of the ordinal tier.  It is what
    # recovers e.g. haveParentSimpleObj.o, whose whole PAL content is three
    # one-and-two-instruction stubs -- too short for the hash floor.
    m.gap_edge = {}
    for r0, r1, a0, a1 in m.gap_unequal:
        lo = 0
        while (r0 + lo < r1 and a0 + lo < a1
               and m.rh[r0 + lo][1] and m.rh[r0 + lo][1] == m.lh[a0 + lo][1]):
            lo += 1
        hi = 0
        while (r1 - 1 - hi >= r0 + lo and a1 - 1 - hi >= a0 + lo
               and m.rh[r1 - 1 - hi][1]
               and m.rh[r1 - 1 - hi][1] == m.lh[a1 - 1 - hi][1]):
            hi += 1
        for k in range(lo):
            m.gap_edge.setdefault(r0 + k, a0 + k)
        for k in range(hi):
            m.gap_edge.setdefault(r1 - 1 - k, a1 - 1 - k)
    used_l = set(m.twins.values()) | set(m.ordinal.values())
    for r, a in sorted(m.gap_edge.items()):
        if r in m.twins or r in m.ordinal or a in used_l:
            continue
        m.ordinal[r] = a
        used_l.add(a)

    m.corr = dict(m.twins)
    for r, a in m.ordinal.items():
        m.corr.setdefault(r, a)
    m.tu, m.tu_src, m.conflicts, m.split_files = self_label(m, m.corr, final=True)

    # ---- vendor archive attribution ----------------------------------------
    # For a function the listing names, MAIN.MAP says which archive member
    # defines that name.  That turns the vendor head and the vendor tail from
    # two opaque blobs into labelled per-archive spans.  Names only -- no
    # MAIN.MAP address is used.  Where the listing gives a newlib source path
    # instead (libc / libm are compiled with -g), that path is the fallback.
    m.arch = [None] * n_r
    for i in range(n_r):
        if m.tu[i] not in (None, VENDOR):
            continue
        a = m.corr.get(i)
        if a is None:
            continue
        f = m.lf[a]
        got = m.sym_arch.get(f.label) or m.sym_arch.get(f.name)
        if not got:
            src = (f.own or f.any)
            if src:
                pth = src.most_common(1)[0][0]
                mm = re.search(r"/src/newlib/(libc|libm)/", pth)
                if mm:
                    got = f"{mm.group(1)}.a"
                elif pth.endswith("crt0.s"):
                    got = "crt0.o"
        m.arch[i] = got
    # Fill archive runs forward inside the vendor blocks: MAIN.MAP lists only
    # a member's DEFINED symbols, so a static sits inside the run it follows.
    # The fill is not free evidence, and MAIN.MAP is a third link that is
    # missing whole archives the retail PAL ELF has (`libscf.a`: no MAIN.MAP
    # row at all, though sceScfGetLanguage &c are right there in the listing
    # and in the rom).  Such a block inherits its predecessor's archive label
    # by fill and would otherwise be silently mis-attributed -- so keep the
    # direct/filled split and report the ratio on every vendor span.
    m.arch_direct = [a is not None for a in m.arch]
    last = None
    for i in range(n_r):
        if m.tu[i] not in (None, VENDOR):
            last = None
            continue
        if m.arch[i]:
            last = m.arch[i]
        elif last:
            m.arch[i] = last

    # ---- names --------------------------------------------------------------
    m.name = [None] * n_r
    m.name_src = [""] * n_r
    for i in range(n_r):
        a = m.corr.get(i)
        if a is None:
            continue
        f = m.lf[a]
        if f.tu == VENDOR and f.name.startswith("func_"):
            continue
        if m.anchor[i] and f.tu != VENDOR and retail_tu(m.anchor[i]) != m.tu[i]:
            continue                            # listing contradicts a hard anchor
        m.name[i] = f.name
        m.name_src[i] = "twin" if i in m.twins else "ordinal"
    return m


def retail_tu(anchor: str | None) -> str | None:
    if not anchor:
        return None
    return anchor[:-2] if anchor.endswith(".c") else anchor


def span_key(m, i):
    """A span is one TU -- or, inside the vendor blocks, one archive."""
    tu = m.tu[i]
    return (tu, m.arch[i] if tu in (None, VENDOR) else None)


def spans_from(m: Model):
    """Contiguous (start_vma, end_vma, path, nfuncs) runs of m.tu.

    Vendor runs are additionally split at archive boundaries, so the report
    and the yaml say `libgraph.a` / `libc.a` / `libgcc.a` rather than one
    783-function blob."""
    out = []
    i = 0
    while i < len(m.rfuncs):
        j = i
        while j + 1 < len(m.rfuncs) and span_key(m, j + 1) == span_key(m, i):
            j += 1
        out.append((m.rfuncs[i][0], m.rfuncs[j][1], m.tu[i], j - i + 1))
        i = j + 1
    return out


# ---------------------------------------------------------------- emitters --
def read_seed() -> tuple[str, set[int], set[str]]:
    text = PAL_SYMS.read_text() if PAL_SYMS.exists() else ""
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
// Recovered PAL (SCES-50760 / SCES_507.60) function symbols.  Regenerate with:
//     tools/gen_pal_symbol_addrs.py
//
// PROVENANCE — read before trusting a name.
//
//   Function STARTS are rom-native: branch-aware boundary detection on
//   baserom/pal/baseelf.rom.  Reliable.
//
//   NAMES and SOURCE-FILE trailers come from the PAL retail disc's own
//   shipped build metadata — baserom/pal/SRCFILE.TXT (an `objdump -dl`
//   listing of the 2002-01-16 MasterVer1.00EU main.elf) and
//   baserom/pal/MAIN.MAP (its GNU ld link map).  Both are files on the
//   officially distributed retail disc; no leaked source, leaked SDK or
//   debug build is an input.  See docs/LEGAL.md.
//
//   !! THE LISTING IS A DIFFERENT LINK !!  Its .text is 0x00100000..0x0028DB34;
//   the retail PAL ELF's is 0x00100000..0x00289BC4.  MAIN.MAP is a third link
//   again (.text size 0x16A29C, and it carries a sampleMode.o member the
//   listing does not have).  Their ORDER, NAMES and (for the listing)
//   INSTRUCTION WORDS are oracles; their ADDRESSES are not.  Every address
//   below is a PAL rom address recovered by correlation.
//
//   Two name tiers:
//     * untagged            — the PAL function is reloc-normalized
//                             byte-identical to the named listing function.
//     * provisional-ordinal — no hash twin; position forced by link order
//                             between two twins.  Verify before relying on it.
//   Functions with neither keep splat's func_<VMA> auto-name.
//
//   The trailer after the name is the recovered TU.  `census` in the TU
//   boundary file means the rom's own __FILE__ string proves it; that oracle
//   is independent of the listing and overrides it.
// ---------------------------------------------------------------------------
""".strip("\n")


def emit_syms(m: Model) -> tuple[int, int, int]:
    span_of = {}
    for s_, e_, sname, _n, stag in yaml_spans(m):
        if not sname.startswith("src/cod/vendor_"):
            continue
        for i_, f_ in enumerate(m.rfuncs):
            if s_ <= f_[0] < e_:
                span_of[i_] = (sname, stag)
    head, seed_vmas, seed_names = read_seed()
    lines = [head, "", BANNER, HEADER, ""]
    used = set(seed_names)
    n_twin = n_ord = n_anon = 0
    cur_tu = object()
    for i, (start, _end) in enumerate(m.rfuncs):
        name = m.name[i]
        if name and name in used:
            # A static's bare name already taken by another TU: fall back to
            # gcc's own discriminator from the listing label (`setMatrix.105`
            # -> `setMatrix_105`), which is still a rom-derived name.
            a = m.corr.get(i)
            d = m.lf[a].discrim if a is not None else None
            cand = f"{name}_{d}" if d else None
            name = cand if cand and cand not in used else None
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
        # Vendor functions name their owning `src/cod/vendor_<VMA>` yaml span
        # so tools/progress_tree.py can attribute them to a TU file (and count a
        # port into that span), then the archive MAIN.MAP assigns the span to.
        if m.tu[i] in (None, VENDOR):
            sp = span_of.get(i)
            tu = (f"{sp[0]}  // {VENDOR} {sp[1].removeprefix('vendor ')}"
                  if sp else VENDOR)
        else:
            tu = m.tu[i]
        tag = "  // provisional-ordinal" if m.name_src[i] == "ordinal" else ""
        lines.append(f"{name} = 0x{start:08X}; // type:func  // {tu}{tag}")
    PAL_SYMS.write_text("\n".join(lines).rstrip("\n") + "\n")
    return n_twin, n_ord, n_anon


def emit_tus(m: Model) -> int:
    tu_lines = [
        "# PAL retail (SCES-50760 / SCES_507.60) .text source-file spans, link order.",
        "# Generated by tools/gen_pal_symbol_addrs.py — untracked, regenerate at will.",
        "# Columns: start_vma end_vma path  (n_funcs, attribution)",
        "# Attribution: census  = a function in the span references that __FILE__",
        "#                        string directly (rom-native, independent oracle);",
        "#              listing = carried over from baserom/pal/SRCFILE.TXT by",
        "#                        reloc-normalized instruction-stream equality;",
        "#              fill    = forward-filled inside an attributed region.",
        "# SRCFILE.TXT / MAIN.MAP addresses are DIFFERENT links and are not used here.",
        "",
    ]
    sp = spans_from(m)
    idx = {f[0]: i for i, f in enumerate(m.rfuncs)}
    for s, e, path, n in sp:
        if path and path != VENDOR:
            srcs = Counter(m.tu_src[i] for i in range(len(m.rfuncs))
                           if m.rfuncs[i][0] >= s and m.rfuncs[i][1] <= e)
            best = ("census" if srcs.get("census") else
                    ("listing" if srcs.get("listing") else "fill"))
            label = path
        else:
            best = vendor_tag(m, idx[s], s, e)
            label = VENDOR
        tu_lines.append(f"0x{s:08X} 0x{e:08X} {label}  # {n} funcs, {best}")
    PAL_TUS.parent.mkdir(parents=True, exist_ok=True)
    PAL_TUS.write_text("\n".join(tu_lines) + "\n")
    return len(sp)


YAML_SUB_RE = re.compile(
    r"^(\s*)-\s*\[\s*(0x[0-9A-Fa-f]+)\s*,\s*([\w.]+)\s*,\s*(\S+?)\s*\](.*)$")

YAML_TEXT_HEADER = """\
      # --- .text 0x00100000..0x00289BC4 (+12 B pad folded into the last span,
      # which therefore runs to the 0x00289BD0 .vutext start).  One subsegment
      # per translation unit, in link order, recovered by
      # tools/gen_pal_symbol_addrs.py from the PAL disc's own SRCFILE.TXT /
      # MAIN.MAP metadata — read the provenance header in
      # config/symbol_addrs.pal.txt before trusting a name.  Every start below
      # is a rom-native, 8-byte-aligned function start (an unaligned split
      # would make the assembler insert pad and break the SHA-1).
      #
      # `src/cod/vendor_*` spans are library archive members, NOT ICO TUs.
      # They are named by VMA — a file named `libc` would assert a per-file
      # partition this tree has not verified — while the trailing comment
      # names the archive MAIN.MAP's symbol table attributes the span's
      # functions to.  Attribution tags: `census` = the rom's own __FILE__
      # string proves the file; `listing` = carried over from SRCFILE.TXT by
      # reloc-normalized instruction-stream equality; `fill` = forward-filled
      # inside an already-attributed region.
      #
      # Everything is `asm` until a TU is ported from ntsc or matched; flip
      # [OFF, asm, NAME] -> [OFF, c, NAME] as that happens.  Regenerating
      # preserves the type and name of any subsegment whose start offset
      # survives, so a flipped TU is not clobbered.
"""


def emit_yaml(m: Model, spans) -> int:
    """Rewrite the .text run of config/ico.pal.yaml's subsegment list."""
    text = PAL_YAML.read_text()
    lines = text.splitlines()
    # locate the subsegment block
    try:
        i0 = next(i for i, l in enumerate(lines) if re.match(r"^\s*subsegments:", l))
    except StopIteration:
        raise SystemExit("ico.pal.yaml: no `subsegments:` key")
    # existing entries, and where the .text run ends
    first = None
    end = None
    keep: dict[int, tuple[str, str]] = {}
    for i in range(i0 + 1, len(lines)):
        mm = YAML_SUB_RE.match(lines[i])
        if mm:
            off = int(mm.group(2), 16)
            if off < PAL_VUTEXT_VMA - TEXT_VMA:
                if first is None:
                    first = i
                keep[off] = (mm.group(3), mm.group(4))
                end = i + 1
                continue
        if re.match(r"^\s*-\s*[\[{]", lines[i]) or re.match(r"^\s*-\s*name:", lines[i]):
            if first is not None:
                break
        if first is None and re.match(r"^\s*#", lines[i]):
            continue
    if first is None:
        raise SystemExit("ico.pal.yaml: no .text subsegment found")
    # the comment block immediately above the first .text entry belongs to it
    j = first
    while j - 1 > i0 and lines[j - 1].strip().startswith("#"):
        j -= 1
    out = []
    for s, e, path, n, tag in spans:
        off = s - TEXT_VMA
        kind, name = keep.get(off, ("asm", path))
        if off in keep and keep[off][1] != path and keep[off][0] == "asm":
            name = path                        # asm spans always take the fresh name
        out.append(f"      - [0x{off:X}, {kind}, {name}]  # {n} funcs, {tag}")
    new = lines[:j] + YAML_TEXT_HEADER.rstrip("\n").splitlines() + out + lines[end:]
    PAL_YAML.write_text("\n".join(new) + "\n")
    return len(out)


KNOWN_DIRS = ("src/", "ios/", "isys/", "sound/", "ito/")


def vendor_tag(m, i0, s, e):
    """Archive label for a vendor span, with the evidence ratio.

    `d/n MAIN.MAP` = d of the span's n functions carry a name MAIN.MAP's
    symbol table attributes to that archive directly; the rest inherited the
    label by forward fill and could belong to an archive MAIN.MAP's link did
    not contain (it is missing libscf.a outright)."""
    arch = m.arch[i0]
    if not arch:
        return "vendor unattributed"
    n = d = 0
    for i in range(i0, len(m.rfuncs)):
        if m.rfuncs[i][0] >= e:
            break
        n += 1
        d += 1 if m.arch_direct[i] else 0
    return f"vendor {arch} ({d}/{n} MAIN.MAP)"


def yaml_spans(m: Model):
    """(start, end, yaml_name, nfuncs, attribution) per .text subsegment."""
    out = []
    seen = Counter()
    idx = {f[0]: i for i, f in enumerate(m.rfuncs)}
    for s, e, path, n in spans_from(m):
        if path and path != VENDOR:
            name = path if path.startswith(KNOWN_DIRS) else "src/" + path
            srcs = Counter(m.tu_src[i] for i in range(len(m.rfuncs))
                           if m.rfuncs[i][0] >= s and m.rfuncs[i][1] <= e)
            tag = ("census" if srcs.get("census") else
                   ("listing" if srcs.get("listing") else "fill"))
        else:
            name = f"src/cod/vendor_{s:06X}"
            tag = vendor_tag(m, idx[s], s, e)
        seen[name] += 1
        if seen[name] > 1:
            name = f"{name}__{s:06X}"
        out.append((s, e, name, n, tag))
    return out


# ------------------------------------------------------------------- checks --
def gates(m: Model, spans) -> bool:
    ok = True

    def chk(cond, label, detail=""):
        nonlocal ok
        print(f"  [{'OK ' if cond else 'FAIL'}] {label}{(' — ' + detail) if detail else ''}")
        if not cond:
            ok = False

    n = len(m.rfuncs)
    chk(5200 <= n <= 5900, "function-start count in 5200..5900", str(n))
    starts = {s for s, _ in m.rfuncs}
    chk(TEXT_VMA in starts, "0x00100000 is a function start (crt0 block holding _start)")
    chk(TEXT_VMA + PAL_TEXT_SZ == m.rfuncs[-1][1], ".text fully covered",
        f"0x{m.rfuncs[-1][1]:08X}")

    bad = []
    for s, e, path, _ in spans_from(m):
        for i, (fs, fe) in enumerate(m.rfuncs):
            if fs >= s and fe <= e and m.anchor[i] and retail_tu(m.anchor[i]) != path:
                bad.append((hex(fs), m.anchor[i], path))
    chk(not bad, "no TU span crosses a __FILE__ census anchor",
        f"{len(bad)} violations {bad[:3]}" if bad else "")

    edges = {s for s, _, _, _, _ in spans}
    chk(edges <= starts, "every yaml subsegment start is a rom function start")
    unal = sorted(s for s in edges if s % 8)
    chk(not unal, "every yaml subsegment start is 8-byte aligned",
        f"{len(unal)}: {[hex(x) for x in unal[:5]]}" if unal else "")

    names = [nm for _, _, nm, _, _ in spans]
    chk(len(names) == len(set(names)), "yaml subsegment names are unique")

    seq = [p for _, _, p, _ in spans_from(m) if p and p != VENDOR]
    chk(len(seq) == len(set(seq)), "each source file occupies exactly one span",
        f"repeats: {[k for k, v in Counter(seq).items() if v > 1][:5]}")

    rng = random.Random(20260904)
    sample = rng.sample(sorted(m.twins.items()), min(60, len(m.twins)))
    bad_h = 0
    for ri, li in sample:
        rs, re_ = m.rfuncs[ri]
        rw = list(struct.unpack(f"<{(re_-rs)//4}I", m.rom[rs - TEXT_VMA: re_ - TEXT_VMA]))
        if hash_words(rw)[0] != m.lf[li].hash:
            bad_h += 1
    chk(bad_h == 0, f"{len(sample)} sampled twins recompute equal (reloc-normalized)",
        f"{bad_h} mismatched" if bad_h else "")

    chk(not m.conflicts, "no listing attribution contradicts a __FILE__ anchor",
        f"{len(m.conflicts)}: {m.conflicts[:3]}" if m.conflicts else "")

    sym_names = set()
    dup = 0
    for i in range(n):
        if m.name[i]:
            if m.name[i] in sym_names:
                dup += 1
            sym_names.add(m.name[i])
    print(f"  [i  ] name collisions resolved via gcc discriminator: {dup}")
    return ok


def report(m: Model, spans):
    n = len(m.rfuncs)
    named_twin = sum(1 for i in range(n) if m.name[i] and m.name_src[i] == "twin")
    named_ord = sum(1 for i in range(n) if m.name[i] and m.name_src[i] == "ordinal")
    print(f"PAL rom .text functions      : {n}")
    print(f"listing .text functions      : {len(m.lf)}"
          f"   (.text 0x{m.lf[0].start:08X}..0x{m.lf[-1].end:08X})")
    print(f"  hash twins (order-const.)  : {m.n_global}")
    print(f"  hash twins (window/free)   : {len(m.moved)}")
    print(f"  ordinal-forced             : {len(m.ordinal)}")
    print(f"  no counterpart             : {n - len(m.corr)}")
    print(f"  monotone runs in twin set  : {m.n_runs}")
    print(f"named — twin                 : {named_twin}")
    print(f"named — provisional-ordinal  : {named_ord}")
    print(f"unnamed (func_<VMA>)         : {n - named_twin - named_ord}")
    print(f"MAIN.MAP .text members       : {len(m.members)}")
    print(f"__FILE__ .c strings in pool  : {len(m.pool_files)}"
          f"  (anchored from .text: {len({a for a in m.anchor if a})})")
    print(f"functions with a source file : {sum(1 for t in m.tu if t and t != VENDOR)}"
          f"  (census {m.tu_src.count('census')}, listing {m.tu_src.count('listing')},"
          f" fill {m.tu_src.count('fill')})")
    agree = sum(1 for i in range(n)
                if m.anchor[i] and i in m.corr
                and m.lf[m.corr[i]].tu == retail_tu(m.anchor[i]))
    both = sum(1 for i in range(n) if m.anchor[i] and i in m.corr
               and m.lf[m.corr[i]].tu != VENDOR)
    print(f"listing x census cross-check : {agree}/{both} agree"
          f"  (independent oracles: __FILE__ string vs listing path)")
    sp = spans_from(m)
    ngame = sum(1 for _, _, p, _ in sp if p and p != VENDOR)
    print(f"source-file spans            : {ngame}"
          f" (+{len(sp) - ngame} vendor)  -> {len(spans)} yaml subsegments")
    bydir = Counter(p.rsplit("/", 1)[0] for _, _, p, _ in sp if p and p != VENDOR)
    print("  by repo directory          : "
          + ", ".join(f"{d}/ {c}" for d, c in sorted(bydir.items())))
    print(f"unequal alignment gaps       : {len(m.gap_unequal)}"
          f" ({sum(r1-r0 for r0,r1,_,_ in m.gap_unequal)} PAL funcs unaligned)")
    if m.split_files:
        print(f"files whose carried-over attribution was non-contiguous "
              f"(repaired): {len(m.split_files)}")
        for f, cls in m.split_files[:10]:
            print(f"    {f:34s} clusters {cls}")
    if m.gap_unequal:
        print("  ambiguous regions (PAL funcs | listing funcs | files touched):")
        for r0, r1, a0, a1 in m.gap_unequal:
            if (r1 - r0) < 6 and (a1 - a0) < 6:
                continue
            files = sorted({m.tu[i] for i in range(r0, min(r1, len(m.tu))) if m.tu[i]})
            print(f"    0x{m.rfuncs[min(r0,len(m.rfuncs)-1)][0]:08X}"
                  f"  {r1-r0:3d} | {a1-a0:3d}   {files}")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--report", action="store_true", help="diagnostics only, write nothing")
    ap.add_argument("--check", action="store_true", help="run sanity gates, write nothing")
    ap.add_argument("--no-yaml", action="store_true", help="do not touch config/ico.pal.yaml")
    args = ap.parse_args()
    m = build()
    spans = yaml_spans(m)
    if args.report or args.check:
        report(m, spans)
        print("gates:")
        return 0 if gates(m, spans) else 1
    n_twin, n_ord, n_anon = emit_syms(m)
    n_sp = emit_tus(m)
    n_yaml = emit_yaml(m, spans) if not args.no_yaml else 0
    report(m, spans)
    print("gates:")
    ok = gates(m, spans)
    print(f"wrote {PAL_SYMS.relative_to(ROOT)}  "
          f"({n_twin} twin-named, {n_ord} ordinal-named, {n_anon} func_<VMA>)")
    print(f"wrote {PAL_TUS.relative_to(ROOT)}  ({n_sp} spans)")
    if n_yaml:
        print(f"rewrote {PAL_YAML.relative_to(ROOT)} .text ({n_yaml} subsegments)")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
