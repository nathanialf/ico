#!/usr/bin/env python3
"""
disasm_vu0.py — reference disassembler for the ICO VU0 microcode blob.

Reads `assets/cod/16F5E0.textbin.bin` (20,704 valid bytes + 64 zero pad)
and emits an annotated assembly listing to stdout. The output is a
**reference** only — every line carries a "REFERENCE ONLY, DO NOT
COMMIT TO GIT" banner because mechanical byte→mnemonic disassembly
is itself extraction and is not IP-safe to commit to the clean-room
repo.

The clean-room path (see decomp/MATCH_VU.md): a developer reads this
output, understands the loop structure and register usage, then
re-types each chunk into `src/cod/16F5E0.S` from understanding —
with hand-chosen labels, comments, and pseudocode annotations. The
disassembler output itself never enters git.

Coverage notes (intentionally conservative):
* VU0 instruction bundles are 64-bit pairs (upper FMAC/special,
  lower I-type/branch/LSU/control). Both halves are decoded
  independently.
* Reliable: nop (upper and lower), the 0x000002FF "upper-pad"
  filler, the lower-half branches (b, bal, jr, jalr, ibeq, ibne,
  ibltz, ibgtz, iblez, ibgez). Branches are decoded specifically
  so labels can be auto-collected for the reader's benefit.
* Not decoded: every FMAC family (add/sub/mul/madd/msub/abs/
  ftoi/itof/opmula/etc.), all LSU forms (lq/sq/ilw/isw/etc.),
  all I-type integer ops, the special-control class (vwaitq,
  vrnext, xgkick, mfir, mtir, etc.). These emit as
  `.word 0x<hex>` with op6 + register-field annotations to aid
  manual decoding against a VU0 reference. The author chose
  honesty over breadth: a wrong mnemonic in the reference would
  mislead the deferred hand-rewrite sprint.
* Every line carries the raw bundle bytes so the developer can
  cross-reference against a VU0 reference manual.
* Future expansion: as the deferred sprint progresses, decode
  tables for FMAC and lower-LSU/integer can be added incrementally
  with confidence built from cross-validating manual rewrites.

This tool only reads bytes; it never writes outside stdout.
"""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
DEFAULT_INPUT = REPO / "assets" / "cod" / "16F5E0.textbin.bin"
VALID_BYTES = 20704  # per decomp/NOTES.md — last 64 bytes are zero pad


# ---------------------------------------------------------------- bitfields

def bits(word: int, lo: int, hi: int) -> int:
    """Extract bits[lo..hi] inclusive (LSB=0)."""
    return (word >> lo) & ((1 << (hi - lo + 1)) - 1)


def dest_bcc(word: int) -> str:
    """Upper-insn destination mask in bits 21-24 (xyzw)."""
    d = bits(word, 21, 24)
    s = ''.join(c for c, b in zip("xyzw", (8, 4, 2, 1)) if d & b)
    return s or "none"


def bc_str(word: int) -> str:
    """Broadcast-component (.bc) lives in bits 0-1: 00=x 01=y 10=z 11=w."""
    return "xyzw"[bits(word, 0, 1)]


def fd_fs_ft(word: int) -> tuple[int, int, int]:
    """Standard upper-insn reg fields: fs in 11-15, ft in 16-20, fd
    in 6-10."""
    return bits(word, 6, 10), bits(word, 11, 15), bits(word, 16, 20)


def vf(n: int) -> str:
    return f"vf{n:02d}"


def vi(n: int) -> str:
    return f"vi{n:02d}"


def signed(value: int, width: int) -> int:
    """Two's-complement sign extension of an N-bit value."""
    sign = 1 << (width - 1)
    return (value & (sign - 1)) - (value & sign)


# --------------------------------------------------------------- upper decode

# FMAC opcodes that take dst.bc form (broadcast). Key: bits[2..5]
# tuple (3-bit op family in bits 2-5, identifies the operation).
# All these read fs (11-15), ft (16-20), write fd (6-10) on dst lanes.
_UPPER_BC_OP = {
    0x0: "add",
    0x1: "sub",
    0x2: "madd",
    0x3: "msub",
    0x4: "max",
    0x5: "mini",
    0x6: "mul",
}

# T3 dispatch (op7=0x40) sub-decoders.  Key: (sub6_low_2_bits, sub5).
# Direct sub6 values (without T3 sub-table): IADD/ISUB/IADDI/IAND/IOR.
_T3_INT_DEC = {
    0x30: "iadd", 0x31: "isub", 0x32: "iaddi",
    0x34: "iand", 0x35: "ior",
}
# T3 sub-table entries — (bc, sub5) → (mnemonic, shape).
_T3_SUB_DEC = {
    (0, 0x0C): ("move",    "v2f_mask"),
    (0, 0x0D): ("lqi",     "v2lqi"),
    (0, 0x0E): ("div",     "div2"),
    (0, 0x0F): ("mtir",    "vmtir"),
    (0, 0x10): ("rnext",   "vr_get"),
    (0, 0x19): ("mfp",     "vmfp"),
    (0, 0x1A): ("xtop",    "vi_x"),
    (0, 0x1B): ("xgkick",  "vi_xgkick"),
    (0, 0x1C): ("esadd",   "e_vfs"),    # VU1-only
    (0, 0x1D): ("eatanxy", "e_vfs"),    # VU1-only
    (0, 0x1E): ("esqrt",   "e_ftf"),    # VU1-only
    (0, 0x1F): ("esin",    "e_ftf"),    # VU1-only
    (1, 0x0C): ("mr32",    "v2f_mask"),
    (1, 0x0D): ("sqi",     "v2sqi"),
    (1, 0x0E): ("sqrt",    "div1"),
    (1, 0x0F): ("mfir",    "v2mfir"),
    (1, 0x10): ("rget",    "vr_get"),
    (1, 0x1A): ("xitop",   "vi_x"),
    (1, 0x1C): ("ersadd",  "e_vfs"),    # VU1-only
    (1, 0x1D): ("eatanxz", "e_vfs"),    # VU1-only
    (1, 0x1E): ("ersqrt",  "e_ftf"),    # VU1-only
    (1, 0x1F): ("eatan",   "e_ftf"),    # VU1-only
    (2, 0x0D): ("lqd",     "v2lqi"),
    (2, 0x0E): ("rsqrt",   "div2"),
    (2, 0x0F): ("ilwr",    "v2lqi"),
    (2, 0x10): ("rinit",   "vr_init"),
    (2, 0x1C): ("eleng",   "e_vfs"),    # VU1-only
    (2, 0x1D): ("esum",    "e_vfs"),    # VU1-only
    (2, 0x1E): ("ercpr",   "e_ftf"),    # VU1-only
    (2, 0x1F): ("eexp",    "e_ftf"),    # VU1-only
    (3, 0x0D): ("sqd",     "v2sqi"),
    (3, 0x0E): ("waitq",   "no_op"),
    (3, 0x0F): ("iswr",    "v2sqi"),
    (3, 0x10): ("rxor",    "vr_init"),
    (3, 0x1C): ("erleng",  "e_vfs"),    # VU1-only
    (3, 0x1E): ("waitp",   "no_op"),
}


def _decode_t3(w: int) -> str:
    """Render the T3-dispatch (op7=0x40) instruction symbolically."""
    sub6 = bits(w, 0, 5)
    if sub6 in _T3_INT_DEC:
        n = _T3_INT_DEC[sub6]
        id_ = bits(w, 6, 10) & 0xF
        is_ = bits(w, 11, 15) & 0xF
        it_ = bits(w, 16, 20) & 0xF
        if n == "iaddi":
            imm5 = signed(bits(w, 6, 10), 5)
            return f"iaddi {vi(it_)}, {vi(is_)}, {imm5}"
        return f"{n} {vi(id_)}, {vi(is_)}, {vi(it_)}"
    if 0x3C <= sub6 <= 0x3F:
        bc = sub6 - 0x3C
        sub5 = bits(w, 6, 10)
        key = (bc, sub5)
        if key not in _T3_SUB_DEC:
            return (f".word 0x{w:08X}  ; T3 sub6=0x{sub6:02X} sub5=0x{sub5:02X}"
                    f" (likely E-class transcendental — encoder pending)")
        n, shape = _T3_SUB_DEC[key]
        ft5 = bits(w, 16, 20)
        fs5 = bits(w, 11, 15)
        it4 = ft5 & 0xF
        is4 = fs5 & 0xF
        dst_mask = bits(w, 21, 24)
        dst_str = "." + ''.join(c for c, b in zip("xyzw", (8,4,2,1)) if dst_mask & b) if dst_mask else ""
        fsf = bits(w, 21, 22)
        ftf = bits(w, 23, 24)
        if shape == "v2f_mask":
            return f"{n}{dst_str} {vf(ft5)}, {vf(fs5)}"
        if shape == "v2lqi":
            if n == "ilwr":
                return f"{n}{dst_str} {vi(it4)}, {vi(is4)}"
            return f"{n}{dst_str} {vf(ft5)}, {vi(is4)}"
        if shape == "v2sqi":
            if n == "iswr":
                return f"{n}{dst_str} {vi(it4)}, {vi(is4)}"
            return f"{n}{dst_str} {vf(fs5)}, {vi(it4)}"
        if shape == "v2mfir":
            return f"{n}{dst_str} {vf(ft5)}, {vi(is4)}"
        if shape == "vmfp":
            return f"{n}{dst_str} {vf(ft5)}"
        if shape == "vmtir":
            return f"mtir {vi(it4)}, {vf(fs5)}.{'xyzw'[fsf]}"
        if shape == "vi_x":
            return f"{n} {vi(it4)}"
        if shape == "vi_xgkick":
            return f"{n} {vi(is4)}"
        if shape == "no_op":
            return n
        if shape == "vr_get":
            return f"{n}{dst_str} {vf(ft5)}"
        if shape == "vr_init":
            return f"{n} R, {vf(fs5)}.{'xyzw'[fsf]}"
        if shape == "div2":
            return f"{n} Q, {vf(fs5)}.{'xyzw'[fsf]}, {vf(ft5)}.{'xyzw'[ftf]}"
        if shape == "div1":
            return f"{n} Q, {vf(ft5)}.{'xyzw'[ftf]}"
        if shape == "e_vfs":
            return f"{n} P, {vf(fs5)}"
        if shape == "e_ftf":
            return f"{n} P, {vf(ft5)}.{'xyzw'[ftf]}"
    return (f".word 0x{w:08X}  ; T3 sub6=0x{sub6:02X} (no decoder)")


# Plain (non-broadcast) FMAC ops at op6 0x28-0x2F.
_UPPER_PLAIN_OP = {
    0x28: "add",
    0x29: "madd",
    0x2A: "mul",
    0x2B: "max",
    0x2C: "sub",
    0x2D: "msub",
    0x2E: "opmsub",
    0x2F: "mini",
}

# i/q variants — ft is implicit (I or Q reg), bits 6-10 = fd.
_UPPER_IQ_OP = {
    0x1C: "mulq",  0x1D: "maxi",  0x1E: "muli",  0x1F: "minii",
    0x20: "addq",  0x21: "maddq", 0x22: "addi",  0x23: "maddi",
    0x24: "subq",  0x25: "msubq", 0x26: "subi",  0x27: "msubi",
}

# FD_XX sub-table dispatch: (bc, sub_op) -> (mnemonic, operand_shape)
#   "acc"  : vfs, vft     (ACC implicit destination)
#   "fd2"  : vft, vfs     (ft is destination — FTOI/ITOF/ABS)
#   "acc1" : vfs          (vft implicit — I or Q broadcast to ACC)
_UPPER_FD_OP = {
    (0,  0): ("addax",  "acc"),  (0,  1): ("subax",  "acc"),
    (0,  2): ("maddax", "acc"),  (0,  3): ("msubax", "acc"),
    (0,  4): ("itof0",  "fd2"),  (0,  5): ("ftoi0",  "fd2"),
    (0,  6): ("mulax",  "acc"),  (0,  7): ("mulaq",  "acc1"),
    (0,  8): ("addaq",  "acc1"), (0,  9): ("subaq",  "acc1"),
    (0, 10): ("adda",   "acc"),  (0, 11): ("suba",   "acc"),
    (1,  0): ("adday",  "acc"),  (1,  1): ("subay",  "acc"),
    (1,  2): ("madday", "acc"),  (1,  3): ("msubay", "acc"),
    (1,  4): ("itof4",  "fd2"),  (1,  5): ("ftoi4",  "fd2"),
    (1,  6): ("mulay",  "acc"),  (1,  7): ("abs",    "fd2"),
    (1,  8): ("maddaq", "acc1"), (1,  9): ("msubaq", "acc1"),
    (1, 10): ("madda",  "acc"),  (1, 11): ("msuba",  "acc"),
    (2,  0): ("addaz",  "acc"),  (2,  1): ("subaz",  "acc"),
    (2,  2): ("maddaz", "acc"),  (2,  3): ("msubaz", "acc"),
    (2,  4): ("itof12", "fd2"),  (2,  5): ("ftoi12", "fd2"),
    (2,  6): ("mulaz",  "acc"),  (2,  7): ("mulai",  "acc1"),
    (2,  8): ("addai",  "acc1"), (2,  9): ("subai",  "acc1"),
    (2, 10): ("mula",   "acc"),  (2, 11): ("opmula", "acc"),
    (3,  0): ("addaw",  "acc"),  (3,  1): ("subaw",  "acc"),
    (3,  2): ("maddaw", "acc"),  (3,  3): ("msubaw", "acc"),
    (3,  4): ("itof15", "fd2"),  (3,  5): ("ftoi15", "fd2"),
    (3,  6): ("mulaw",  "acc"),  # (3,7) CLIP — deferred
    (3,  8): ("maddai", "acc1"), (3,  9): ("msubai", "acc1"),
    (3, 11): ("nop",    "pad"),  # handled by `pad` mnemonic above
}


def decode_upper(w: int) -> str:
    """Decode the 32-bit upper instruction.  Cross-referenced against
    PCSX2 microVU_Tables.inl + Misc.h (GPL-3.0 — bit-field semantics
    are factual hardware encoding, re-derived for our use).

    Bit layout:
      bits 0-5  : opcode (6-bit, `code & 0x3F`)
        - 0x00..0x1B : broadcast FMAC (family in bits 2-4, bc in bits 0-1)
        - 0x1C..0x27 : i/q broadcast variants (Phase 2)
        - 0x28..0x2F : plain FMAC (add/madd/mul/max/sub/msub/opmsub/mini)
        - 0x3C..0x3F : FD sub-table dispatch (incl NOP=pad) (Phase 2)
      bits 6-10  : fd
      bits 11-15 : fs
      bits 16-20 : ft
      bits 21-24 : dest mask

    Cases handled now:
      * w == 0 (with all flag bits zero)  → nop
      * w == 0x000002FF                   → pad (FD_11 sub-op 0x0B = NOP)
      * op6 in _UPPER_BC_OP * 4           → broadcast FMAC, symbolic
      * op6 in _UPPER_PLAIN_OP            → plain FMAC, symbolic
      * everything else                   → .word with field annotations
    """
    if w == 0 or (w & 0x7FFFFFFF) == 0:
        return "nop"
    if w == 0x000002FF:
        return "pad"
    # Strip flag bits (25-30) for opcode classification; the bytes are
    # still emitted via .word for any bundle that has non-zero flags
    # so the round trip preserves them exactly.
    has_flags = (w >> 25) & 0x3F != 0
    op6 = bits(w, 0, 5)
    fd, fs, ft = fd_fs_ft(w)
    dst = dest_bcc(w)
    dst_str = f".{dst}" if dst != "none" else ""
    if not has_flags:
        if op6 in _UPPER_PLAIN_OP:
            return f"{_UPPER_PLAIN_OP[op6]}{dst_str} {vf(fd)}, {vf(fs)}, {vf(ft)}"
        if op6 in _UPPER_IQ_OP:
            return f"{_UPPER_IQ_OP[op6]}{dst_str} {vf(fd)}, {vf(fs)}"
        if op6 <= 0x1B:
            family_idx = (op6 >> 2) & 0x7
            bc_idx = op6 & 0x3
            if family_idx in _UPPER_BC_OP:
                family = _UPPER_BC_OP[family_idx]
                bc = "xyzw"[bc_idx]
                return f"{family}{bc}{dst_str} {vf(fd)}, {vf(fs)}, {vf(ft)}"
        if 0x3C <= op6 <= 0x3F:
            bc = op6 - 0x3C
            sub = fd  # bits 6-10 ARE the sub-opcode in FD dispatch
            key = (bc, sub)
            if key in _UPPER_FD_OP:
                mnem, shape = _UPPER_FD_OP[key]
                if shape == "acc":
                    return f"{mnem}{dst_str} {vf(fs)}, {vf(ft)}"
                if shape == "fd2":
                    return f"{mnem}{dst_str} {vf(ft)}, {vf(fs)}"
                if shape == "acc1":
                    return f"{mnem}{dst_str} {vf(fs)}"
    if bits(w, 31, 31):
        return f".word 0x{w:08X}  ; I-bit set (likely LOI; next bundle lower = float imm)"
    return (f".word 0x{w:08X}"
            f"  ; upper op6=0x{op6:02X} dst={dst} fd={fd} fs={fs} ft={ft}"
            f" (cross-ref VU0 ref for opcode bits)")


# --------------------------------------------------------------- lower decode

def decode_lower(w: int, pc: int, branch_targets: list[int] | None = None) -> str:
    """Decode the 32-bit lower instruction.  Cross-referenced against
    PCSX2's microVU dispatch (GPL-3.0; the bit-field semantics are
    factual hardware encoding, re-derived here for our own use).

    Lower opcode dispatch is via **bits 25-31** (7-bit field), NOT
    bits 26-31 — an earlier version of this file got that wrong, and
    every "branch" the prior disasm reported in the [0x8xxxxxxx]
    encoding range was actually a `vmove vf<N>, vf0` with no
    destination mask (the bit pattern PCSX2 calls out as the
    "BIOS-bug NOP" because the BIOS emits upper/lower NOP slots
    swapped).  Real VU0 branches live in [0x4xxxxxxx].

    Reliable cases handled now:
      * w == 0                  → nop (true zero)
      * w == 0x8000033C         → nop_swap (BIOS-bug NOP padding)
      * op7 == 0x20 (b)         } symbolic with PC-relative target
      * op7 == 0x21 (bal)       }
      * op7 == 0x24 (jr)        } symbolic, register only
      * op7 == 0x25 (jalr)      }
      * op7 in 0x28..0x2F       } symbolic conditional branches
                                  (ibeq/ibne/ibltz/ibgtz/iblez/ibgez)

    All other encodings emit `.word 0x<hex>` with the op7 + fs/ft
    fields annotated so the manual rewrite can identify the family
    against a VU0 reference."""
    if w == 0:
        return "nop"
    if w == 0x8000033C:
        # PCSX2 microVU_Compile.inl mVUcheckBadOp: "The BIOS writes
        # upper and lower NOPs in reversed slots (bug)". Treat as a
        # distinct mnemonic so the round trip stays byte-perfect.
        return "nop_swap"
    op7 = bits(w, 25, 31)
    fs = bits(w, 11, 15)
    ft = bits(w, 16, 20)
    cond_branch_table = {
        0x28: "ibeq",
        0x29: "ibne",
        0x2C: "ibltz",
        0x2D: "ibgtz",
        0x2E: "iblez",
        0x2F: "ibgez",
    }
    if op7 in cond_branch_table:
        op = cond_branch_table[op7]
        offset = signed(bits(w, 0, 10), 11) * 8
        target = pc + 8 + offset
        if branch_targets is not None:
            branch_targets.append(target)
        if op7 in (0x28, 0x29):
            return f"{op} {vi(ft)}, {vi(fs)}, L_{target:04X}"
        return f"{op} {vi(fs)}, L_{target:04X}"
    # LSU + I-type — operand layout differs per op:
    #   LQ  (0x00): vft = vf dest, vfs = vi base
    #   SQ  (0x01): vfs = vf source, vft = vi base   (swapped vs LQ!)
    #   ILW (0x04): vit = vi dest, vis = vi base
    #   ISW (0x05): vit = vi src,  vis = vi base
    dst_mask = bits(w, 21, 24)
    dst_str_lsu = ""
    if dst_mask:
        dst_str_lsu = "." + ''.join(c for c, b in zip("xyzw", (8,4,2,1))
                                    if dst_mask & b)
    imm11 = signed(bits(w, 0, 10), 11)
    if op7 == 0x00:
        return f"lq{dst_str_lsu} {vf(ft)}, {imm11:+d}({vi(fs & 0xF)})"
    if op7 == 0x01:
        return f"sq{dst_str_lsu} {vf(fs)}, {imm11:+d}({vi(ft & 0xF)})"
    if op7 == 0x04:
        return f"ilw{dst_str_lsu} {vi(ft & 0xF)}, {imm11:+d}({vi(fs & 0xF)})"
    if op7 == 0x05:
        return f"isw{dst_str_lsu} {vi(ft & 0xF)}, {imm11:+d}({vi(fs & 0xF)})"
    if op7 == 0x08:
        imm15 = (bits(w, 21, 24) << 11) | bits(w, 0, 10)
        return f"iaddiu {vi(ft & 0xF)}, {vi(fs & 0xF)}, {imm15}"
    if op7 == 0x09:
        imm15 = (bits(w, 21, 24) << 11) | bits(w, 0, 10)
        return f"isubiu {vi(ft & 0xF)}, {vi(fs & 0xF)}, {imm15}"
    # Flag ops (op7 0x10-0x1C) — varied operand shapes.
    if op7 == 0x11:
        return f"fcset 0x{bits(w, 0, 23):X}"
    if op7 in (0x12, 0x10, 0x13):
        n = {0x12: "fcand", 0x10: "fceq", 0x13: "fcor"}[op7]
        return f"{n} vi01, 0x{bits(w, 0, 23):X}"
    if op7 == 0x15:
        imm12 = (bits(w, 21, 21) << 11) | bits(w, 0, 10)
        return f"fsset 0x{imm12:X}"
    if op7 in (0x14, 0x16, 0x17):
        n = {0x14: "fseq", 0x16: "fsand", 0x17: "fsor"}[op7]
        imm12 = (bits(w, 21, 21) << 11) | bits(w, 0, 10)
        return f"{n} {vi(ft & 0xF)}, 0x{imm12:X}"
    if op7 in (0x18, 0x1A, 0x1B):
        n = {0x18: "fmeq", 0x1A: "fmand", 0x1B: "fmor"}[op7]
        return f"{n} {vi(ft & 0xF)}, {vi(fs & 0xF)}"
    if op7 == 0x1C:
        return f"fcget {vi(ft & 0xF)}"
    # T3 dispatch (op7 = 0x40).
    if op7 == 0x40:
        return _decode_t3(w)
    if op7 == 0x20:
        offset = signed(bits(w, 0, 10), 11) * 8
        target = pc + 8 + offset
        if branch_targets is not None:
            branch_targets.append(target)
        return f"b L_{target:04X}"
    if op7 == 0x21:
        offset = signed(bits(w, 0, 10), 11) * 8
        target = pc + 8 + offset
        if branch_targets is not None:
            branch_targets.append(target)
        return f"bal {vi(ft)}, L_{target:04X}"
    if op7 == 0x24:
        return f"jr {vi(fs)}"
    if op7 == 0x25:
        return f"jalr {vi(ft)}, {vi(fs)}"
    return (f".word 0x{w:08X}"
            f"  ; lower op7=0x{op7:02X} fs={fs} ft={ft}"
            f" (cross-ref VU0 ref)")


# ---------------------------------------------------------------- bundles

def read_bundles(data: bytes) -> list[tuple[int, int, int]]:
    """Return [(pc, upper, lower), ...] for 64-bit bundles."""
    out = []
    pc = 0
    while pc + 8 <= len(data):
        # Bundle layout in memory: lower 32 bits at +0, upper 32 bits at +4
        # (little-endian). VU0 conventions vary; we follow PS2/EE LE
        # bundle order: word[0]=lower, word[1]=upper.
        lower, upper = struct.unpack_from("<II", data, pc)
        out.append((pc, upper, lower))
        pc += 8
    return out


def collect_branch_targets(bundles: list[tuple[int, int, int]]) -> set[int]:
    """First pass: decode lowers to find branch targets for label
    generation. Targets that fall outside the bundle range are dropped."""
    targets: list[int] = []
    for pc, _upper, lower in bundles:
        decode_lower(lower, pc, branch_targets=targets)
    valid = {pc for pc, _, _ in bundles}
    return {t for t in targets if t in valid}


def render(bundles: list[tuple[int, int, int]],
           targets: set[int],
           start_pc: int = 0,
           end_pc: int | None = None,
           annotate: bool = False) -> list[str]:
    out = [
        "; VU0 microcode disassembly — REFERENCE ONLY, DO NOT COMMIT TO GIT",
        f"; Source: {DEFAULT_INPUT.relative_to(REPO)}",
        f"; Bundles: {len(bundles)} ({len(bundles) * 8} bytes)",
        f"; Bundle format: <addr>:  <upper> ; <lower>    [raw lower upper]",
        "",
    ]
    if annotate:
        out.append("; --annotate is best-effort heuristic; verify against a VU0 ref.")
        out.append("")
    for pc, upper, lower in bundles:
        if end_pc is not None and pc >= end_pc:
            break
        if pc < start_pc:
            continue
        if pc in targets:
            out.append(f"L_{pc:04X}:")
        up = decode_upper(upper)
        lo = decode_lower(lower, pc)
        raw = f"[{lower:08X} {upper:08X}]"
        out.append(f"    0x{pc:04X}:  {up:<44} ; {lo:<44} {raw}")
    return out


# ---------------------------------------------------------------- main

def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[1])
    ap.add_argument("--input", default=str(DEFAULT_INPUT),
                    help=f"path to textbin (default: {DEFAULT_INPUT})")
    ap.add_argument("--range", default=None,
                    help="byte range to disassemble, e.g. 0x0-0x40")
    ap.add_argument("--bundles", type=int, default=0,
                    help="only emit the first N bundles (overrides --range hi)")
    ap.add_argument("--upper-only", action="store_true",
                    help="only decode upper insn; lower printed as raw hex")
    ap.add_argument("--lower-only", action="store_true",
                    help="only decode lower insn; upper printed as raw hex")
    ap.add_argument("--annotate", action="store_true",
                    help="add heuristic register-usage comments (best-effort)")
    args = ap.parse_args(argv)

    data = Path(args.input).read_bytes()
    if len(data) > VALID_BYTES:
        # Trim the 64-byte zero pad documented in NOTES.md.
        trailing = data[VALID_BYTES:]
        if all(b == 0 for b in trailing):
            data = data[:VALID_BYTES]
        # else: keep all bytes; let the developer see the unexpected tail.

    bundles = read_bundles(data)
    targets = collect_branch_targets(bundles)

    start_pc = 0
    end_pc: int | None = None
    if args.range:
        lo_s, hi_s = args.range.split("-", 1)
        start_pc = int(lo_s, 0)
        end_pc = int(hi_s, 0)
    if args.bundles:
        end_pc = start_pc + args.bundles * 8

    # The --upper-only / --lower-only flags swap one half for raw hex;
    # render() doesn't currently honor them — we patch the decoders.
    global decode_upper, decode_lower  # noqa: PLW0603
    orig_upper, orig_lower = decode_upper, decode_lower
    if args.upper_only:
        def decode_lower(w, pc, branch_targets=None):  # type: ignore[no-redef]
            return f".word 0x{w:08X}"
    if args.lower_only:
        def decode_upper(w):  # type: ignore[no-redef]
            return f".word 0x{w:08X}"

    lines = render(bundles, targets, start_pc=start_pc, end_pc=end_pc,
                   annotate=args.annotate)

    # Restore (in case we get imported and re-called)
    decode_upper, decode_lower = orig_upper, orig_lower  # noqa: F841

    sys.stdout.write("\n".join(lines) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
