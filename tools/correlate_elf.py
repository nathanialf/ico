#!/usr/bin/env python3
"""correlate_elf.py: find each PAL function in another ICO boot ELF.

For every function of the PAL build (the STT_FUNC symbols of .text in
build/ico.syms.elf, each with its object from the link map build/ico.pal.map,
in link order) decide whether the same function is present in another boot
ELF of the game, and where, so the PAL source and its name can be carried to
that target. The target is stripped: its function boundaries come from a
branch-aware scan of its .text, and a PAL function and a target function are
the same when their instruction streams are equal once every field a
relocation fills is masked.

The names come from the PAL listing by way of the PAL build: a name is the
PAL symbol of the function, and a target address is where this tool finds
the function's body in the target. No address is copied from another link,
and nothing read from a disc is written into the tree; the outputs go under
build/ and hold names, addresses, sizes and hashes, plus the two instruction
words at the first difference of a pair whose bodies differ.

METHOD
------
1. Target function boundaries: the scan of the retired
   tools/gen_pal_symbol_addrs.py. A j, a jr or an always-taken b ends a
   function only when no conditional branch seen since the function began
   reaches past its delay slot; the zero words after it are alignment
   padding and are skipped, unless the next function's own branch reaches
   back into them (a body of nops ending in `b` to its first word). On the
   PAL build the scan reproduces the extent of 5750 of the 5755 symbols;
   the rest are a function ending in a syscall that does not return, a dead
   jr after a return, and code the symbol table does not cover.

2. Normalized instruction streams. The masked fields are exactly those a
   relocation fills: the target of j and jal (R_MIPS_26), the immediate of
   lui (R_MIPS_HI16), and the low 16 bits of addiu, daddiu, ori and the GPR,
   FPU and VU0 loads and stores, lq and sq included, whose base register is
   $gp (R_MIPS_GPREL16, R_MIPS_LITERAL) or holds a %hi value (R_MIPS_LO16).
   A register holds a %hi value from the lui that sets it; addu, daddu, add
   or dadd of such a register and anything keeps the sum a %hi value (the
   jump-table and array-base form); any other write clears it, and so does
   a call, for the registers the ABI lets a callee clobber (after the call's
   delay slot). The state is followed over the function's control flow, not
   a fixed window: a register set before a branch is live on both of its
   paths and into its delay slot (for a branch-likely, on the taken path
   only), and where paths meet the union holds. The linear stream alone is
   not enough: a block after a return or an unconditional branch is reached
   from an earlier branch, with that branch's registers, and following the
   stream through it leaves 270 relocated fields of the PAL build unmasked.
   Trailing zero words are dropped and the rest is hashed with SHA-1.

3. Matching, in tiers:
   anchor   a normalized body that occurs exactly once in each ELF (three
            instructions or more), kept when it lies on the longest run that
            is increasing in both link orders;
   gap      between consecutive pairs, recursively: bodies unique inside the
            gap on both sides, or occurring the same number of times on both
            sides and paired in order, again on the longest increasing run;
   window   the same inside each gap with the PAL side cut at object
            boundaries and no size floor, so a one- or two-instruction
            function unique inside its object pairs up;
   free     a body of eight or more instructions unique among what is left
            on both sides, wherever it sits (a member that moved);
   ordinal  inside a gap between two pairs of one increasing run, when both
            sides hold the same number of functions, they pair by position;
            when the counts differ, pairs are taken from each end inward
            while the two extents are equal.
   Every pair reports whether the normalized bodies are equal, or the index
   of the first differing instruction and the two words there.

4. Self-test (--self-test, no target): the build's own objects carry the
   relocations, so every relocated field of .text must be masked and every
   masked field is counted against them; then PAL is matched against itself,
   once with the symbol extents (every function must find itself; the only
   ambiguity allowed is functions whose normalized bodies are identical,
   which are listed) and once with the scanned boundaries.

OUTPUTS (under --out, default build/correlate/<name>/; never committed)
-------
  twins.txt       PAL name, PAL VMA, PAL size, target VMA, target size, tier,
                  equal or differs-at:<index> with the PAL and target words
                  there, whether the extents are equal, and a residue class
                  for a pair that differs (imm:N, other:N, length:+D)
  pal_only.txt    PAL functions with no twin, with their object
  target_only.txt target functions no PAL function claims, with size
  tu_spans.txt    per PAL object in link order, the target .text span its
                  twins occupy, with gaps and interleaving flagged
  report.txt      counts per tier, bytes carried, share of target .text
  selftest.txt    (--self-test) the relocation check and the ambiguous groups

Usage:
  tools/correlate_elf.py TARGET.elf [--pal-syms build/ico.syms.elf]
                         [--pal-map build/ico.pal.map] [--out DIR]
  tools/correlate_elf.py --self-test
"""

from __future__ import annotations

import argparse
import bisect
import hashlib
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

try:
    from elftools.elf.elffile import ELFFile
    from elftools.elf.relocation import RelocationSection
except ImportError:
    sys.exit("correlate_elf.py: missing pyelftools. Run "
             "`.venv/bin/pip install -r tools/requirements.txt`.")

REPO_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
from check_elf import parse_map  # noqa: E402

PAL_SYMS = REPO_ROOT / "build" / "ico.syms.elf"
PAL_MAP = REPO_ROOT / "build" / "ico.pal.map"
OUT_ROOT = REPO_ROOT / "build" / "correlate"

ANCHOR_MIN = 3      # instructions, for the anchor and gap tiers
FREE_MIN = 8        # instructions, for the order-free tier


# ----- instruction fields ------------------------------------------------

def _op(w):
    return w >> 26


def _rs(w):
    return (w >> 21) & 31


def _rt(w):
    return (w >> 16) & 31


def _rd(w):
    return (w >> 11) & 31


# Opcodes whose low 16 bits a %lo or %gp_rel relocation fills: addiu, ori,
# daddiu, ldl, ldr, lq, sq, the GPR loads and stores, lwc1, swc1, lqc2,
# sqc2, ld, sd.
LO_OPS = ({0x09, 0x0D, 0x19, 0x1A, 0x1B, 0x1E, 0x1F, 0x31, 0x36, 0x37,
           0x39, 0x3E, 0x3F} | set(range(0x20, 0x2F)))
# I-type opcodes that write rt: the immediate arithmetic, lui, and the GPR
# loads (lq and ld included).
RT_WRITERS = ({0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x18, 0x19,
               0x1A, 0x1B, 0x1E, 0x37} | set(range(0x20, 0x28)))
# SPECIAL functs that write no GPR: jr, syscall, break, sync, mthi, mtlo,
# div, divu, mtsa, the traps.
SPECIAL_NO_RD = {0x08, 0x0C, 0x0D, 0x0F, 0x11, 0x13, 0x1A, 0x1B, 0x29,
                 0x30, 0x31, 0x32, 0x33, 0x34, 0x36}
# MMI functs that write no GPR: mthi1, mtlo1, div1, divu1, pmthl.
MMI_NO_RD = {0x11, 0x13, 0x1A, 0x1B, 0x31}
ADD_FUNCTS = {0x20, 0x21, 0x2C, 0x2D}          # add addu dadd daddu
# The registers a callee may clobber: at, v0-v1, a0-a3, t0-t9, ra.
CALL_CLOBBER_MASK = sum(1 << r for r in list(range(1, 16)) + [24, 25, 31])


def dest_gpr(w: int) -> int | None:
    """The GPR an instruction writes, or None."""
    op = _op(w)
    if op == 0:
        f = w & 63
        return None if f in SPECIAL_NO_RD else _rd(w)
    if op == 1:
        return 31 if _rt(w) in (0x10, 0x11, 0x12, 0x13) else None
    if op == 3:
        return 31
    if op in RT_WRITERS:
        return _rt(w)
    if op == 0x1C:
        f = w & 63
        if f in MMI_NO_RD:
            return None
        if f == 0x29 and ((w >> 6) & 31) in (0x08, 0x09):   # pmthi, pmtlo
            return None
        return _rd(w)
    if op == 0x10 and _rs(w) == 0:                       # mfc0
        return _rt(w)
    if op == 0x11 and _rs(w) in (0, 2):                  # mfc1, cfc1
        return _rt(w)
    if op == 0x12 and _rs(w) in (1, 2):                  # qmfc2, cfc2
        return _rt(w)
    return None


def hi_effect(state: int, w: int) -> int:
    """The set of %hi registers (a bit mask) after one instruction."""
    d = dest_gpr(w)
    if _op(w) == 0x0F:
        return state | (1 << d) if d else state
    if (_op(w) == 0 and (w & 63) in ADD_FUNCTS and d
            and (state >> _rs(w) & 1 or state >> _rt(w) & 1)):
        return state | (1 << d)
    if d is not None:
        return state & ~(1 << d)
    return state


def transfer(w: int, i: int):
    """(kind, target index) of a control transfer at word i, else None.
    kind: 'cond', 'likely', 'b' (always taken), 'j', 'jr', 'ret', 'call'."""
    op = _op(w)
    imm = w & 0xFFFF
    if imm >= 0x8000:
        imm -= 0x10000
    t = i + 1 + imm
    if op in (0x04, 0x05, 0x06, 0x07):
        if op == 0x04 and _rs(w) == 0 and _rt(w) == 0:
            return "b", t
        return "cond", t
    if op in (0x14, 0x15, 0x16, 0x17):
        return "likely", t
    if op == 1:
        rt = _rt(w)
        if rt in (0x10, 0x11, 0x12, 0x13):
            return "call", None
        if rt == 1 and _rs(w) == 0:
            return "b", t
        if rt in (0, 1):
            return "cond", t
        if rt in (2, 3):
            return "likely", t
        return None
    if op in (0x10, 0x11, 0x12) and _rs(w) == 8:
        return ("likely" if _rt(w) & 2 else "cond"), t
    if op == 2:
        return "j", None
    if op == 3:
        return "call", None
    if op == 0:
        f = w & 63
        if f == 8:
            return ("ret" if _rs(w) == 31 else "jr"), None
        if f == 9:
            return "call", None
    return None


def hi_states(words) -> list[int]:
    """The %hi registers live into each word, by data flow over the
    function's control flow: the union over every path that reaches it.
    A branch's delay slot runs on both of its paths (on the taken path only
    for a branch-likely); a call clobbers the caller-saved registers after
    its delay slot; j, b, jr and returns do not fall through. Words only a
    jump table reaches (those no branch or fall-through reaches, after a jr
    through a register) get the state at that jr."""
    n = len(words)
    xfer = [transfer(w, i) for i, w in enumerate(words)]
    owner = [None] * n
    for i in range(n - 1):
        if xfer[i] and owner[i] is None:     # a transfer in a delay slot is not one
            owner[i + 1] = i
    state = [0] * n
    reached = [False] * n
    work = []

    def feed(j, s):
        if 0 <= j < n and (not reached[j] or state[j] | s != state[j]):
            state[j] |= s
            reached[j] = True
            work.append(j)

    jr_state = 0

    def run():
        nonlocal jr_state
        while work:
            k = work.pop()
            s = hi_effect(state[k], words[k])
            i = owner[k]
            if i is None:
                feed(k + 1, s)              # the next word, or the delay slot
                continue
            kind, t = xfer[i]
            if kind in ("cond", "b", "likely"):
                feed(t, s)
            if kind == "cond":
                feed(k + 1, s)
            elif kind == "likely":
                feed(k + 1, hi_effect(state[i], words[i]))
            elif kind == "call":
                feed(k + 1, s & ~CALL_CLOBBER_MASK)
            elif kind == "jr":
                jr_state |= s
    feed(0, 0)
    run()
    while True:
        seeds = [k for k in range(n) if not reached[k] and (k == 0 or reached[k - 1])]
        if not seeds:
            break
        for k in seeds:
            feed(k, jr_state)
        run()
    return state


def normalize(words) -> tuple[list[int], list[str | None]]:
    """(normalized words, mask kind per word: 'j', 'hi', 'lo' or None)."""
    live = hi_states(words)
    out: list[int] = []
    kinds: list[str | None] = []
    for w, s in zip(words, live):
        op = _op(w)
        kind = None
        if op in (2, 3):
            kind = "j"
        elif op == 0x0F:
            kind = "hi"
        elif op in LO_OPS and (_rs(w) == 28 or s >> _rs(w) & 1):
            kind = "lo"
        out.append(w & 0xFC000000 if kind == "j" else
                   w & 0xFFFF0000 if kind else w)
        kinds.append(kind)
    return out, kinds


# ----- function boundaries ----------------------------------------------

def branch_target(w: int, va: int) -> int | None:
    op = _op(w)
    if (op in (0x04, 0x05, 0x06, 0x07, 0x14, 0x15, 0x16, 0x17)
            or (op == 1 and _rt(w) in (0, 1, 2, 3, 0x10, 0x11, 0x12, 0x13))
            or (op in (0x10, 0x11, 0x12) and _rs(w) == 8)):
        imm = w & 0xFFFF
        if imm >= 0x8000:
            imm -= 0x10000
        return va + 4 + imm * 4
    return None


def scan_text(words, base: int) -> list[tuple[int, int]]:
    """Branch-aware boundary scan: [(start_vma, end_vma)], end exclusive.

    j, jr and an always-taken b end a function when no conditional branch
    since its start reaches past the delay slot; the zero words after it
    are alignment padding. A function whose own branch reaches back into
    that padding (a body of nops that ends in `b` to its first word) starts
    at the branch's target instead."""
    n = len(words)
    funcs = []
    i = 0
    while i < n and words[i] == 0:
        i += 1
    prev_end = 0
    start = reach = low = i
    while i < n:
        w = words[i]
        t = branch_target(w, base + 4 * i)
        if t is not None:
            reach = max(reach, (t - base) // 4)
            low = min(low, (t - base) // 4)
        x = transfer(w, i)
        if x and x[0] in ("j", "jr", "ret", "b"):
            end = i + 2
            if reach < end:
                if prev_end <= low < start:
                    start = low
                funcs.append((base + 4 * start, base + 4 * min(end, n)))
                i = prev_end = end
                while i < n and words[i] == 0:
                    i += 1
                start = reach = low = i
                continue
        i += 1
    if start < n:
        funcs.append((base + 4 * start, base + 4 * n))
    return funcs


# ----- the two sides ----------------------------------------------------

class Func:
    __slots__ = ("vma", "size", "name", "obj", "words", "norm", "kinds",
                 "h", "n")

    def __init__(self, vma, size, words, name=None, obj=None):
        self.vma, self.size, self.name, self.obj = vma, size, name, obj
        ws = list(words)
        while ws and ws[-1] == 0:
            ws.pop()
        self.words = ws
        self.norm, self.kinds = normalize(ws)
        self.n = len(ws)
        self.h = (hashlib.sha1(struct.pack("<%dI" % self.n, *self.norm)).digest()
                  if self.n else None)


def text_words(path: Path) -> tuple[int, tuple[int, ...]]:
    with path.open("rb") as f:
        sec = ELFFile(f).get_section_by_name(".text")
        if sec is None:
            sys.exit(f"correlate_elf.py: {path} has no .text")
        data = sec.data()
        return sec["sh_addr"], struct.unpack("<%dI" % (len(data) // 4),
                                             data[: len(data) // 4 * 4])


def text_objects(map_path: Path) -> list[tuple[int, int, str]]:
    """(addr, size, object) of each .text input section, in link order."""
    return [(r["addr"], r["size"], r["obj"]) for r in parse_map(map_path)
            if r["sect"] == ".text" and r["obj"]]


def load_pal(syms: Path, map_path: Path):
    base, words = text_words(syms)
    end = base + 4 * len(words)
    seen = {}
    with syms.open("rb") as f:
        st = ELFFile(f).get_section_by_name(".symtab")
        if st is None:
            sys.exit(f"correlate_elf.py: {syms} has no symbol table")
        for s in st.iter_symbols():
            if s["st_info"]["type"] != "STT_FUNC" or not base <= s["st_value"] < end:
                continue
            v = s["st_value"]
            if v not in seen or (s["st_info"]["bind"] == "STB_GLOBAL"
                                 and seen[v][2] != "STB_GLOBAL"):
                seen[v] = (s["st_size"], s.name, s["st_info"]["bind"])
    objs = text_objects(map_path)
    starts = [o[0] for o in objs]
    vmas = sorted(seen)
    funcs = []
    for k, v in enumerate(vmas):
        size, name, _ = seen[v]
        nxt = vmas[k + 1] if k + 1 < len(vmas) else end
        stop = min(v + size, nxt) if size else nxt
        j = bisect.bisect_right(starts, v) - 1
        obj = objs[j][2] if j >= 0 and v < objs[j][0] + objs[j][1] else None
        lo = (v - base) // 4
        funcs.append(Func(v, size or stop - v, words[lo:(stop - base) // 4],
                          name, obj))
    return funcs, objs, base, words


def load_target(path: Path):
    base, words = text_words(path)
    funcs = [Func(a, b - a, words[(a - base) // 4:(b - base) // 4])
             for a, b in scan_text(words, base)]
    return funcs, base, words


# ----- matching ---------------------------------------------------------

def lis(pairs):
    """Longest run of (p, t) pairs increasing in both, pairs sorted by p."""
    tails, tail_idx = [], []
    parent = [-1] * len(pairs)
    for k, (_, t) in enumerate(pairs):
        i = bisect.bisect_left(tails, t)
        if i == len(tails):
            tails.append(t)
            tail_idx.append(k)
        else:
            tails[i] = t
            tail_idx[i] = k
        parent[k] = tail_idx[i - 1] if i else -1
    out = []
    k = tail_idx[-1] if tail_idx else -1
    while k >= 0:
        out.append(pairs[k])
        k = parent[k]
    return out[::-1]


def hash_pairs(P, T, prange, trange, min_n, multi):
    pb, tb = defaultdict(list), defaultdict(list)
    for i in prange:
        if P[i].h and P[i].n >= min_n:
            pb[P[i].h].append(i)
    for j in trange:
        if T[j].h and T[j].n >= min_n:
            tb[T[j].h].append(j)
    out = []
    for h, ps in pb.items():
        ts = tb.get(h)
        if ts and len(ps) == len(ts) and (len(ps) == 1 or multi):
            out.extend(zip(ps, ts))
    out.sort()
    return out


def gaps_of(pairs, np_, nt):
    """The rectangles between consecutive pairs of a monotone pair list."""
    out = []
    prev = (-1, -1)
    for p, t in sorted(pairs) + [(np_, nt)]:
        if p - prev[0] > 1 and t - prev[1] > 1:
            out.append((prev[0] + 1, p, prev[1] + 1, t))
        prev = (p, t)
    return out


def fill_gaps(P, T, pairs, min_n, multi):
    """Recursive order-constrained fill of every gap of a monotone set."""
    found = []
    stack = gaps_of(pairs, len(P), len(T))
    while stack:
        p0, p1, t0, t1 = stack.pop()
        got = lis(hash_pairs(P, T, range(p0, p1), range(t0, t1), min_n, multi))
        if not got:
            continue
        found += got
        prev = (p0 - 1, t0 - 1)
        for p, t in got + [(p1, t1)]:
            if p - prev[0] > 1 and t - prev[1] > 1:
                stack.append((prev[0] + 1, p, prev[1] + 1, t))
            prev = (p, t)
    return found


def window_fill(P, T, pairs):
    """Inside each gap, the PAL side cut at object boundaries, no floor."""
    found = []
    for p0, p1, t0, t1 in gaps_of(pairs, len(P), len(T)):
        cand = []
        k = p0
        while k < p1:
            m = k
            while m + 1 < p1 and P[m + 1].obj == P[k].obj:
                m += 1
            cand += hash_pairs(P, T, range(k, m + 1), range(t0, t1), 1, False)
            k = m + 1
        # a target body may pair with two object segments; keep it unique
        tc = Counter(t for _, t in cand)
        found += lis(sorted(c for c in cand if tc[c[1]] == 1))
    return found


def correlate(P, T):
    """{pal index: (target index, tier)}."""
    pc = Counter(f.h for f in P if f.h)
    tc = Counter(f.h for f in T if f.h)
    tpos = {f.h: j for j, f in enumerate(T) if f.h and tc[f.h] == 1}
    cand = [(i, tpos[f.h]) for i, f in enumerate(P)
            if f.h and f.n >= ANCHOR_MIN and pc[f.h] == 1 and f.h in tpos]
    match = {p: (t, "anchor") for p, t in lis(sorted(cand))}

    def mono():
        return sorted((p, t) for p, (t, tier) in match.items() if tier != "free")

    for p, t in fill_gaps(P, T, mono(), ANCHOR_MIN, True):
        match[p] = (t, "gap")
    while True:
        got = window_fill(P, T, mono())
        if not got:
            break
        for p, t in got:
            match[p] = (t, "window")
        for p, t in fill_gaps(P, T, mono(), 1, False):
            match[p] = (t, "window")

    used_t = {t for t, _ in match.values()}
    rest_p = [i for i in range(len(P)) if i not in match]
    rest_t = [j for j in range(len(T)) if j not in used_t]
    for p, t in hash_pairs(P, T, rest_p, rest_t, FREE_MIN, False):
        match[p] = (t, "free")

    # ordinal: inside the gaps of each increasing run
    runs, cur = [], [(-1, -1)]
    for p, t in sorted((p, t) for p, (t, _) in match.items()):
        if t <= cur[-1][1]:
            runs.append(cur)
            cur = [(p, t)]
        else:
            cur.append((p, t))
    cur.append((len(P), len(T)))
    runs.append(cur)
    used_t = {t for t, _ in match.values()}
    for run in runs:
        for (p0, t0), (p1, t1) in zip(run, run[1:]):
            dp, dt = p1 - p0 - 1, t1 - t0 - 1
            if dp <= 0 or dt <= 0:
                continue
            if dp == dt:
                new = [(p0 + 1 + k, t0 + 1 + k) for k in range(dp)]
            else:
                new = []
                lo = 0
                while (lo < min(dp, dt)
                       and P[p0 + 1 + lo].size == T[t0 + 1 + lo].size):
                    new.append((p0 + 1 + lo, t0 + 1 + lo))
                    lo += 1
                hi = 0
                while (hi < min(dp, dt) - lo
                       and P[p1 - 1 - hi].size == T[t1 - 1 - hi].size):
                    new.append((p1 - 1 - hi, t1 - 1 - hi))
                    hi += 1
            for p, t in new:
                if p not in match and t not in used_t:
                    match[p] = (t, "ordinal")
                    used_t.add(t)
    return match


def first_diff(a: Func, b: Func) -> int | None:
    n = min(a.n, b.n)
    for k in range(n):
        if a.norm[k] != b.norm[k]:
            return k
    return None if a.n == b.n else n


def residue(a: Func, b: Func) -> str:
    """A first triage of a pair whose bodies differ: 'imm:N' when both have
    the same length and the N differing words are I-type instructions that
    differ only in their immediate (a constant, a __LINE__, a structure
    offset), 'other:N' when some differing word differs elsewhere (a
    register, a shift amount, an opcode), 'length:+D' when the target has D
    more words."""
    if a.n != b.n:
        return f"length:{b.n - a.n:+d}"
    diff = [k for k in range(a.n) if a.norm[k] != b.norm[k]]
    if all(a.norm[k] >> 16 == b.norm[k] >> 16
           and _op(a.norm[k]) not in (0, 0x10, 0x11, 0x12, 0x1C) for k in diff):
        return f"imm:{len(diff)}"
    return f"other:{len(diff)}"


# ----- reports ----------------------------------------------------------

TIERS = ("anchor", "gap", "window", "free", "ordinal")


def word_at(f: Func, k: int) -> str:
    return f"{f.words[k]:08x}" if k < f.n else "end"


def write_outputs(out: Path, label: str, P, T, objs, match, text_size):
    out.mkdir(parents=True, exist_ok=True)
    rows = []
    stat = {tier: Counter() for tier in TIERS}
    resid = Counter()
    for i, f in enumerate(P):
        if i not in match:
            continue
        j, tier = match[i]
        g = T[j]
        k = first_diff(f, g)
        if k is None:
            st, res = "equal\t-\t-", "-"
        else:
            st, res = f"differs-at:{k}\t{word_at(f, k)}\t{word_at(g, k)}", residue(f, g)
            resid[res.split(":")[0]] += 1
        ext = "extent-equal" if f.size == g.size else "extent-differs"
        rows.append(f"{f.name}\t0x{f.vma:08x}\t{f.size}\t0x{g.vma:08x}\t"
                    f"{g.size}\t{tier}\t{st}\t{ext}\t{res}")
        c = stat[tier]
        c["n"] += 1
        c["equal" if k is None else "differs"] += 1
        c["ext_eq"] += f.size == g.size
        c["pal_bytes_equal" if k is None else "pal_bytes_differs"] += f.size
        c["tgt_bytes_equal" if k is None else "tgt_bytes_differs"] += g.size
    hdr = ("# pal_name\tpal_vma\tpal_size\ttarget_vma\ttarget_size\ttier\tbody"
           "\tpal_word\ttarget_word\textent\tresidue\n")
    (out / "twins.txt").write_text(hdr + "\n".join(rows) + "\n")

    only = [f"{f.name}\t0x{f.vma:08x}\t{f.size}\t{f.obj}"
            for i, f in enumerate(P) if i not in match]
    (out / "pal_only.txt").write_text(
        "# pal_name\tpal_vma\tpal_size\tobject\n" + "\n".join(only) + "\n")

    claimed = {j for j, _ in match.values()}
    tonly = [f"0x{g.vma:08x}\t{g.size}" for j, g in enumerate(T) if j not in claimed]
    (out / "target_only.txt").write_text(
        "# target_vma\tsize\n" + "\n".join(tonly) + "\n")

    owner = {}
    for i, (j, _) in match.items():
        owner[j] = P[i].obj
    by_obj = defaultdict(list)
    for i, f in enumerate(P):
        by_obj[f.obj].append(i)
    lines = ["# object\tfuncs\ttwins\ttarget_lo\ttarget_hi\tflags"]
    for _, _, obj in objs:
        idx = by_obj.get(obj)
        if not idx:
            continue
        tw = [match[i][0] for i in idx if i in match]
        if not tw:
            lines.append(f"{obj}\t{len(idx)}\t0\t-\t-\tabsent")
            continue
        lo, hi = min(tw), max(tw)
        flags = []
        if len(tw) < len(idx):
            flags.append(f"partial:{len(idx) - len(tw)}")
        if tw != sorted(tw):
            flags.append("out-of-order")
        foreign = sum(1 for j in range(lo, hi + 1) if j in owner and owner[j] != obj)
        unclaimed = sum(1 for j in range(lo, hi + 1) if j not in owner)
        if unclaimed:
            flags.append(f"gap:{unclaimed}")
        if foreign:
            flags.append(f"interleaved:{foreign}")
        lines.append(f"{obj}\t{len(idx)}\t{len(tw)}\t0x{T[lo].vma:08x}\t"
                     f"0x{T[hi].vma + T[hi].size:08x}\t{','.join(flags) or 'contiguous'}")
    (out / "tu_spans.txt").write_text("\n".join(lines) + "\n")

    tot = Counter()
    for c in stat.values():
        tot.update(c)
    rep = [f"target {label}: {len(T)} scanned functions, .text {text_size} bytes",
           f"PAL: {len(P)} functions in {len({f.obj for f in P})} objects", "",
           "tier      twins  equal  differs  extent-equal  pal-bytes(eq)  target-bytes(eq)"]
    for tier in TIERS + ("total",):
        c = tot if tier == "total" else stat[tier]
        rep.append(f"{tier:8} {c['n']:6} {c['equal']:6} {c['differs']:8} "
                   f"{c['ext_eq']:13} {c['pal_bytes_equal']:14} {c['tgt_bytes_equal']:17}")
    cov_eq = tot["tgt_bytes_equal"]
    cov = cov_eq + tot["tgt_bytes_differs"]
    rep += ["",
            f"PAL only: {len(P) - len(match)} functions, "
            f"{sum(f.size for i, f in enumerate(P) if i not in match)} bytes",
            f"target only: {len(T) - len(claimed)} functions, "
            f"{sum(g.size for j, g in enumerate(T) if j not in claimed)} bytes",
            "pairs whose bodies differ, by residue: "
            + ", ".join(f"{k} {v}" for k, v in sorted(resid.items())),
            f"carried with equal bodies: {tot['equal']} functions, "
            f"{tot['pal_bytes_equal']} PAL bytes",
            f"target .text covered by equal twins: {cov_eq} bytes "
            f"({100.0 * cov_eq / text_size:.2f}%)",
            f"target .text covered by all twins: {cov} bytes "
            f"({100.0 * cov / text_size:.2f}%)"]
    (out / "report.txt").write_text("\n".join(rep) + "\n")
    return rep


# ----- self-test --------------------------------------------------------

RELOC_KIND = {"R_MIPS_26": "j", "R_MIPS_HI16": "hi", "R_MIPS_LO16": "lo",
              "R_MIPS_GPREL16": "lo", "R_MIPS_LITERAL": "lo"}


def reloc_check(P, objs, base, lines):
    """Every relocated .text field of the build's objects must be masked."""
    kind_at = {}
    for f in P:
        for k, kd in enumerate(f.kinds):
            if kd:
                kind_at[f.vma + 4 * k] = kd
    func_starts = [f.vma for f in P]
    relocated = {}
    other = Counter()
    missing_obj = 0
    for addr, _, obj in objs:
        path = REPO_ROOT / obj
        if not path.exists():
            missing_obj += 1
            continue
        with path.open("rb") as fh:
            elf = ELFFile(fh)
            for sec in elf.iter_sections():
                if not isinstance(sec, RelocationSection):
                    continue
                if elf.get_section(sec["sh_info"]).name != ".text":
                    continue
                for r in sec.iter_relocations():
                    t = r["r_info_type"]
                    name = describe_reloc(elf, t)
                    if name in RELOC_KIND:
                        relocated[addr + r["r_offset"]] = RELOC_KIND[name]
                    else:
                        other[name] += 1
    spans = [(f.vma, f.vma + 4 * f.n) for f in P]
    outside = []
    under = []
    wrong = []
    for a, kd in sorted(relocated.items()):
        k = bisect.bisect_right(func_starts, a) - 1
        if k < 0 or a >= spans[k][1]:
            outside.append(a)
            continue
        got = kind_at.get(a)
        if got is None:
            under.append((a, kd, P[k].name))
        elif got != kd:
            wrong.append((a, kd, got))
    over = Counter(kd for a, kd in kind_at.items() if a not in relocated)
    lines.append(f"relocation check: {len(relocated)} relocated .text fields "
                 f"in {len(objs) - missing_obj} objects ({missing_obj} objects missing)")
    lines.append(f"  outside every PAL function symbol: {len(outside)}"
                 + (f" (0x{outside[0]:08x}..0x{outside[-1]:08x})" if outside else ""))
    lines.append(f"  inside a function and masked as their kind: "
                 f"{len(relocated) - len(outside) - len(under) - len(wrong)}")
    lines.append(f"  inside a function and not masked: {len(under)}")
    for a, kd, name in under[:40]:
        lines.append(f"    0x{a:08x} {kd} in {name}")
    lines.append(f"  masked as the wrong kind: {len(wrong)}")
    lines.append("  masked with no relocation (lui of a constant, and low halves "
                 "on a register a lui of a constant set): "
                 + ", ".join(f"{k} {v}" for k, v in sorted(over.items())))
    if other:
        lines.append("  other relocation types in .text: "
                     + ", ".join(f"{k} {v}" for k, v in sorted(other.items())))
    return not under and not wrong


def describe_reloc(elf, t):
    from elftools.elf.descriptions import describe_reloc_type
    return describe_reloc_type(t, elf)


def self_test(args) -> int:
    P, objs, base, words = load_pal(args.pal_syms, args.pal_map)
    lines = []
    ok = reloc_check(P, objs, base, lines)

    # PAL against itself with the symbol extents
    T = [Func(f.vma, f.size, f.words) for f in P]
    match = correlate(P, T)
    wrong = [i for i in range(len(P)) if match.get(i, (None,))[0] != i]
    groups = defaultdict(list)
    for i, f in enumerate(P):
        if f.h:
            groups[f.h].append(i)
    amb = [g for g in groups.values() if len(g) > 1]
    lines.append("")
    lines.append(f"PAL against itself, symbol extents: {len(P) - len(wrong)} of "
                 f"{len(P)} functions find themselves")
    for i in wrong:
        lines.append(f"  not found: {P[i].name} 0x{P[i].vma:08x}"
                     f" -> {match[i] if i in match else 'none'}")
    raw_same = sum(1 for g in amb if len({tuple(P[i].words) for i in g}) == 1)
    lines.append(f"  groups of functions with identical normalized bodies: {len(amb)} "
                 f"({sum(len(g) for g in amb)} functions; {raw_same} groups also "
                 f"identical before masking)")
    tiers = Counter(match[i][1] for g in amb for i in g if i in match)
    lines.append("  how they were placed: "
                 + ", ".join(f"{k} {v}" for k, v in sorted(tiers.items())))
    for g in sorted(amb, key=lambda g: P[g[0]].vma):
        same = len({tuple(P[i].words) for i in g}) == 1
        lines.append(f"    {P[g[0]].n:4} insns {'raw-identical' if same else 'reloc-only'}: "
                     + " ".join(f"{P[i].name}@0x{P[i].vma:08x}" for i in g))
    ok = ok and not wrong and all(i in match for g in amb for i in g)

    # PAL against itself with the scanned boundaries
    T2 = [Func(a, b - a, words[(a - base) // 4:(b - base) // 4])
          for a, b in scan_text(words, base)]
    m2 = correlate(P, T2)
    sym = {(f.vma, f.vma + f.size) for f in P}
    scn = {(g.vma, g.vma + g.size) for g in T2}
    self_found = sum(1 for i, (j, _) in m2.items()
                     if T2[j].vma == P[i].vma and T2[j].size == P[i].size)
    misplaced = [(P[i].name, P[i].vma, T2[j].vma) for i, (j, _) in m2.items()
                 if T2[j].vma != P[i].vma]
    lines.append("")
    lines.append(f"PAL against itself, scanned boundaries: {len(T2)} scanned functions, "
                 f"{len(sym & scn)} with the extent of a PAL symbol")
    lines.append(f"  {self_found} of {len(P)} PAL functions find themselves with the "
                 f"same extent; {len(misplaced)} paired to another address")
    for name, a, b in misplaced[:40]:
        lines.append(f"    {name} 0x{a:08x} -> 0x{b:08x}")
    lines.append("  PAL functions whose extent the scan does not reproduce:")
    for f in P:
        if (f.vma, f.vma + f.size) in scn:
            continue
        cover = [g for g in T2 if g.vma < f.vma + f.size and f.vma < g.vma + g.size]
        lines.append(f"    {f.name} 0x{f.vma:08x}+{f.size}: scanned "
                     + ", ".join(f"0x{g.vma:08x}+{g.size}" for g in cover))
    lines.append("  (informational: the scan cannot see a function that ends in a"
                 " call that does not return, a dead jr after a return, or code"
                 " the symbol table does not cover)")
    lines.append("")
    lines.append("self-test " + ("PASS" if ok else "FAIL"))

    out = args.out or OUT_ROOT / "pal"
    rep = write_outputs(out, "PAL (scanned)", P, T2, objs, m2, 4 * len(words))
    (out / "selftest.txt").write_text("\n".join(lines) + "\n")
    print("\n".join(lines))
    print()
    print("\n".join(rep))
    print(f"outputs in {out}")
    return 0 if ok else 1


# ----- main -------------------------------------------------------------

def default_name(path: Path) -> str:
    return path.parent.name if path.stem == "baseelf" else path.stem


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("target", nargs="?", type=Path, help="the other boot ELF")
    ap.add_argument("--pal-syms", type=Path, default=PAL_SYMS)
    ap.add_argument("--pal-map", type=Path, default=PAL_MAP)
    ap.add_argument("--out", type=Path, default=None)
    ap.add_argument("--self-test", action="store_true",
                    help="check the normalizer against the build's relocations "
                         "and match PAL against itself")
    args = ap.parse_args()
    if args.self_test:
        return self_test(args)
    if args.target is None:
        ap.error("a target ELF is required (or --self-test)")
    P, objs, _, _ = load_pal(args.pal_syms, args.pal_map)
    T, _, twords = load_target(args.target)
    match = correlate(P, T)
    out = args.out or OUT_ROOT / default_name(args.target)
    rep = write_outputs(out, str(args.target), P, T, objs, match, 4 * len(twords))
    print("\n".join(rep))
    print(f"outputs in {out}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
