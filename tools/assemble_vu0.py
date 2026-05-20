#!/usr/bin/env python3
"""
assemble_vu0.py — VU0 micromode assembler for hand-written .S chunks.

The mirror of `tools/disasm_vu0.py`. Reads a hand-typed VU0 source file
(syntax described below) and emits a binutils-compatible `.s` file
consisting solely of `.word` directives — which mips-linux-gnu-as can
then assemble into a `.vutext` object. This keeps the build pipeline
unchanged: the existing `as_hasm` ninja rule consumes the emitted `.s`.

The clean-room boundary: this tool encodes mnemonics to bytes from
**published VU0 documentation** (EE User's Manual, ps2dev/ps2sdk
headers, open-source VU disassemblers). It never reads
`assets/cod/16F5E0.textbin.bin`. Hand-written `.S` files commit to
git; their byte expansion is regenerated on build.

# Coverage parity with disasm_vu0.py

This assembler starts where the disassembler ended: only the
opcodes the disassembler reliably decodes are emitted symbolically.
Everything else uses `.word 0x<hex>` (or `.bundle <upper>, <lower>`
for raw-hex bundle pairs), so the hand-writer can encode FMAC / LSU
/ control ops directly until the symbolic tables grow.

Reliable symbolic ops (parity with `decode_upper` / `decode_lower`):
  upper:  nop, .word
  lower:  nop, b, bal, jr, jalr, ibeq, ibne, ibltz, ibgtz, iblez,
          ibgez, .word

Future expansion (add encoders below as the hand-rewrite sprint
discovers and documents each family):
  upper FMAC: add/sub/mul/madd/msub (+bc variants), abs, ftoi/itof,
              opmula, mula/madda/etc. (accumulator chains)
  lower LSU:  lq, sq, ilw, isw, ilwr, iswr
  lower I:    iadd, iaddi, iand, ior, isub, iaddiu
  lower special: vwaitq, vrnext, xgkick, mfir, mtir, fmand, etc.

# Source-file syntax (`.S` files in src/cod/)

A VU0 source file is a sequence of bundles plus labels and pragmas.
Whitespace and `;` after content are flexible — bundles look like:

    <label>:                       ; optional, on its own line or before bundle
        <upper_insn>  ;  <lower_insn>    ; optional `; comment` trailing
        nop           ;  b matrix_loop   ; branch with symbolic target

The `;` separator splits upper (left) and lower (right). A trailing
`;` introduces a comment to end-of-line. The comment may also use `#`.
Bundles are 8 bytes; address counter advances by 8 per bundle.

Escape hatches for opcodes not yet symbolic:

    .word 0x12345678                  ; emit upper or lower half raw
    .bundle 0x12345678, 0x9ABCDEF0    ; emit one full bundle (upper, lower)
    .raw 0x00 0x00 0x00 0x00 ...      ; raw bytes (must be multiple of 8)

Pragmas:

    .vu0                              ; mark file as VU0 (header sanity check)
    .org 0x40                         ; assert current bundle offset (sanity)
    .assert_pc 0x80                   ; alias for .org — never advances pc

Macros (text substitution; one bundle per body line):

    .macro JMP target
        pad ; b target
    .endmacro
    JMP L_1A00      ; expands to: pad ; b L_1A00
    JMP L_1A10      ; one bundle per call

The body of a macro is a sequence of bundle lines (and labels). Each
non-comment, non-pragma line inside `.macro ... .endmacro` becomes
one bundle in the expansion. Parameter names occurring in the body
are textually replaced by the call's argument.

# Output

Default: emits a `.s` file (one `.word` per 32-bit half) ready for
mips-linux-gnu-as. The `.s` file uses the same `.include "macro.inc"`
preamble and `.section .text,"ax"` form as splat-emitted hasm so the
build pipeline doesn't need a special case.

`--raw out.bin` emits a raw binary instead (useful for cross-checking
against `assets/cod/16F5E0.textbin.bin` byte-for-byte).

`--check assets/cod/16F5E0.textbin.bin` reads the textbin and prints
the first byte offset where the assembled output diverges (or "OK"
if it matches end-to-end).

# Invocation

    tools/assemble_vu0.py src/cod/16F5E0.S
        → emits src/cod/16F5E0.s in same dir (or --out path)

    tools/assemble_vu0.py src/cod/16F5E0.S --raw /tmp/check.bin
    cmp /tmp/check.bin assets/cod/16F5E0.textbin.bin
        → byte-for-byte cross-check during incremental hand-writing
"""
from __future__ import annotations

import argparse
import dataclasses
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent


# ============================================================================
# Encoders — mirror of decode_upper / decode_lower in disasm_vu0.py.
#
# Each returns a 32-bit int or raises EncodeError. New opcode families
# should be added here with a single-line comment cross-referencing
# the VU0 ref manual section.
# ============================================================================

class EncodeError(Exception):
    pass


def _vf(token: str) -> int:
    m = re.fullmatch(r"vf([0-9]{1,2})", token, re.IGNORECASE)
    if not m:
        raise EncodeError(f"expected vfN register, got {token!r}")
    n = int(m.group(1))
    if n > 31:
        raise EncodeError(f"vf register out of range: {token!r}")
    return n


def _vi(token: str) -> int:
    m = re.fullmatch(r"vi([0-9]{1,2})", token, re.IGNORECASE)
    if not m:
        raise EncodeError(f"expected viN register, got {token!r}")
    n = int(m.group(1))
    if n > 15:
        raise EncodeError(f"vi register out of range: {token!r}")
    return n


def _int(token: str) -> int:
    token = token.strip().rstrip(",")
    try:
        return int(token, 0)
    except ValueError as e:
        raise EncodeError(f"expected integer, got {token!r}") from e


def encode_upper_nop() -> int:
    """True-zero upper. Most VU0 microcode uses 0x000002FF as the
    upper-pad filler instead — the assembler exposes that form as the
    `pad` mnemonic so the byte distinction round-trips through
    disasm_vu0.py."""
    return 0


def encode_upper_pad() -> int:
    """Canonical upper-pad pattern (`0x000002FF`). Disassembled as
    `pad` by disasm_vu0.py; written as `pad ; <lower>` in source.
    Equivalent to NOP per PCSX2: FD_11 sub-op 0x0B."""
    return 0x000002FF


# ----------------------------- Upper FMAC encoders ----------------------------
#
# Bit layout (cross-checked against PCSX2 microVU_Tables.inl + Misc.h, GPL-3.0):
#
#   bits 0-5   : opcode (6-bit dispatch via `code & 0x3F`)
#   bits 6-10  : fd
#   bits 11-15 : fs
#   bits 16-20 : ft
#   bits 21-24 : dest mask (bit 24=x, 23=y, 22=z, 21=w)
#   bits 25-30 : flag bits (I/E/M/D/T/-) — left zero for canonical form
#   bit  31    : reserved
#
# Broadcast variants encode the bc letter in bits 0-1; family in bits 2-5:
#   bits 0-1 : 00=x 01=y 10=z 11=w
#   bits 2-4 : 0=add 1=sub 2=madd 3=msub 4=max 5=mini 6=mul
#   bit  5   : 0
#
# Plain (non-broadcast) variants live at op6 0x28-0x2F directly:
#   ADD=0x28 MADD=0x29 MUL=0x2A MAX=0x2B SUB=0x2C MSUB=0x2D OPMSUB=0x2E MINI=0x2F
#
# FD-sub-table variants live at op6 0x3C-0x3F with bits 6-10 picking
# within the sub-table.  Those land in Phase 2.

_UPPER_BC_FAMILY = {
    "add":  0, "sub":  1, "madd": 2, "msub": 3,
    "max":  4, "mini": 5, "mul":  6,
}

_UPPER_PLAIN_OP6 = {
    "add":    0x28,
    "madd":   0x29,
    "mul":    0x2A,
    "max":    0x2B,
    "sub":    0x2C,
    "msub":   0x2D,
    "opmsub": 0x2E,
    "mini":   0x2F,
}


def _enc_dest_mask(mask: str) -> int:
    """`xyzw`-style mask → 4-bit field in bits 21-24.  Order of letters
    in the input doesn't matter (`.wyx` same as `.xyw`).  Returns 0 for
    an empty mask (still legal — produces an FMAC op with no
    destination write, useful for flag-setting ADD-then-discard)."""
    if mask == "":
        return 0
    bits_out = 0
    for c in mask.lower():
        if c == "x":   bits_out |= 8
        elif c == "y": bits_out |= 4
        elif c == "z": bits_out |= 2
        elif c == "w": bits_out |= 1
        else:
            raise EncodeError(f"unknown dest-mask letter: {c!r}")
    return bits_out


def _enc_upper_bc(family: str, bc: str, mask: str,
                  fd: int, fs: int, ft: int) -> int:
    """Encode a broadcast FMAC: <family><bc>.<mask> vfd, vfs, vft.
    bc is one of 'x'/'y'/'z'/'w'."""
    fam_idx = _UPPER_BC_FAMILY[family]
    bc_idx = "xyzw".index(bc)
    op6 = (fam_idx << 2) | bc_idx
    return (_enc_dest_mask(mask) << 21) | (ft << 16) | (fs << 11) | (fd << 6) | op6


def _enc_upper_plain(family: str, mask: str,
                     fd: int, fs: int, ft: int) -> int:
    """Encode a plain FMAC: <family>.<mask> vfd, vfs, vft."""
    op6 = _UPPER_PLAIN_OP6[family]
    return (_enc_dest_mask(mask) << 21) | (ft << 16) | (fs << 11) | (fd << 6) | op6


# ----------------------------- Upper i/q variants -----------------------------
#
# Single-source FMAC ops where ft is replaced by the implicit I or Q
# register.  Syntax: <mnem>.<mask> vfd, vfs
# (no ft operand — `I` and `Q` are implicit).
#
# Encoding ignores ft; we always emit ft=0.  A handful of textbin
# bundles have non-zero ft here (likely an emit artifact); those will
# need `.word` form to round-trip.

_UPPER_IQ_OP6 = {
    "mulq":  0x1C, "maxi":  0x1D, "muli":  0x1E, "minii": 0x1F,
    "addq":  0x20, "maddq": 0x21, "addi":  0x22, "maddi": 0x23,
    "subq":  0x24, "msubq": 0x25, "subi":  0x26, "msubi": 0x27,
}


def _enc_upper_iq(family: str, mask: str, fd: int, fs: int) -> int:
    op6 = _UPPER_IQ_OP6[family]
    return (_enc_dest_mask(mask) << 21) | (fs << 11) | (fd << 6) | op6


# --------------------- Upper FD sub-table dispatch (ACC ops) ------------------
#
# op6 0x3C-0x3F selects the FD_00/01/10/11 sub-table by bc field
# (bits 0-1).  Within each table, bits 6-10 are the sub-opcode.
#
# Three operand shapes:
#   ACC ops      — fs source, ft source, destination is implicit ACC
#                  Syntax: <mnem>.<mask> vfs, vft
#   FTOI/ITOF    — fs source, ft destination
#                  Syntax: <mnem>.<mask> vft, vfs
#   ABS          — same shape as FTOI (ft = dest, fs = source)
#   CLIP         — fs and ft both source, no destination (sets CLIP flag)
#                  Syntax: clip vfs, vft.w   (w-broadcast on ft, no mask)
#                  Deferred — operand semantics tricky.
#   NOP (pad)    — FD_11 sub 0x0B, already handled as `pad`.

# Map: mnemonic → (bc, sub_op, operand_shape)
#   operand_shape: 'acc' (vfs, vft) or 'fd2' (vft, vfs)
_UPPER_FD_TABLE = {
    # FD_00 (bc=x)
    "addax":  (0,  0, "acc"),
    "subax":  (0,  1, "acc"),
    "maddax": (0,  2, "acc"),
    "msubax": (0,  3, "acc"),
    "itof0":  (0,  4, "fd2"),
    "ftoi0":  (0,  5, "fd2"),
    "mulax":  (0,  6, "acc"),
    "mulaq":  (0,  7, "acc1"),   # ACC = vfs * Q (no vft operand)
    "addaq":  (0,  8, "acc1"),
    "subaq":  (0,  9, "acc1"),
    "adda":   (0, 10, "acc"),    # plain ACC = vfs + vft
    "suba":   (0, 11, "acc"),
    # FD_01 (bc=y)
    "adday":  (1,  0, "acc"),
    "subay":  (1,  1, "acc"),
    "madday": (1,  2, "acc"),
    "msubay": (1,  3, "acc"),
    "itof4":  (1,  4, "fd2"),
    "ftoi4":  (1,  5, "fd2"),
    "mulay":  (1,  6, "acc"),
    "abs":    (1,  7, "fd2"),
    "maddaq": (1,  8, "acc1"),
    "msubaq": (1,  9, "acc1"),
    "madda":  (1, 10, "acc"),
    "msuba":  (1, 11, "acc"),
    # FD_10 (bc=z)
    "addaz":  (2,  0, "acc"),
    "subaz":  (2,  1, "acc"),
    "maddaz": (2,  2, "acc"),
    "msubaz": (2,  3, "acc"),
    "itof12": (2,  4, "fd2"),
    "ftoi12": (2,  5, "fd2"),
    "mulaz":  (2,  6, "acc"),
    "mulai":  (2,  7, "acc1"),
    "addai":  (2,  8, "acc1"),
    "subai":  (2,  9, "acc1"),
    "mula":   (2, 10, "acc"),
    "opmula": (2, 11, "acc"),
    # FD_11 (bc=w)
    "addaw":  (3,  0, "acc"),
    "subaw":  (3,  1, "acc"),
    "maddaw": (3,  2, "acc"),
    "msubaw": (3,  3, "acc"),
    "itof15": (3,  4, "fd2"),
    "ftoi15": (3,  5, "fd2"),
    "mulaw":  (3,  6, "acc"),
    # "clip":   (3,  7, "clip"),  # special — deferred
    "maddai": (3,  8, "acc1"),
    "msubai": (3,  9, "acc1"),
    # (3, 10) is unknown / reserved
    # (3, 11) is NOP — handled by `pad` mnemonic
}


def _enc_upper_fd(mnem: str, mask: str,
                  fs: int, ft: int) -> int:
    bc, sub, shape = _UPPER_FD_TABLE[mnem]
    op6 = 0x3C | bc
    return ((_enc_dest_mask(mask) << 21) | (ft << 16) | (fs << 11)
            | (sub << 6) | op6)


def encode_lower_nop() -> int:
    return 0


# 11-bit signed branch offset, in units of bundles (×8 bytes).
_BRANCH_OPS = {
    "b":     0x20,
    "bal":   0x21,
    "ibeq":  0x28,
    "ibne":  0x29,
    "ibltz": 0x2C,
    "ibgtz": 0x2D,
    "iblez": 0x2E,
    "ibgez": 0x2F,
}


def _enc_branch(op7: int, pc: int, target_pc: int,
                ft: int = 0, fs: int = 0) -> int:
    """Encode an 11-bit PC-relative branch.  Lower-half opcode lives
    in bits 25-31 (7-bit dispatch — confirmed against PCSX2
    VU0microInterp `VU0_LOWER_OPCODE[VU->code >> 25]`).  Branch
    immediate is bits 0-10, sign-extended, in units of bundles."""
    delta = target_pc - (pc + 8)
    if delta % 8 != 0:
        raise EncodeError(
            f"branch target 0x{target_pc:04X} not 8-byte aligned from pc 0x{pc:04X}")
    bundles = delta // 8
    if bundles < -1024 or bundles > 1023:
        raise EncodeError(
            f"branch out of range: {bundles} bundles "
            f"(±1024 max) from pc 0x{pc:04X} → 0x{target_pc:04X}")
    offset = bundles & 0x7FF
    return (op7 << 25) | (ft << 16) | (fs << 11) | offset


def _enc_jr(fs: int) -> int:
    return (0x24 << 25) | (fs << 11)


def _enc_jalr(ft: int, fs: int) -> int:
    return (0x25 << 25) | (ft << 16) | (fs << 11)


def encode_lower_nop_swap() -> int:
    """The "BIOS-bug NOP" pattern (0x8000033C) — written as `nop_swap`
    in source so it stays semantically distinct from `nop` (true zero).
    PCSX2 special-cases this exact byte pattern in its bad-op spam
    filter; the actual encoding dispatches to mVU_MOVE with all-zero
    operands and dest mask, i.e. an effective no-op."""
    return 0x8000033C


# ============================================================================
# Parser — line-by-line, bundle-at-a-time.
# ============================================================================

@dataclasses.dataclass
class ParsedBundle:
    pc: int            # byte offset of this bundle
    upper: int | None  # None → resolve from upper_src token
    lower: int | None  # None → resolve from lower_src token
    upper_src: str     # original upper text (for branch-pc fixup)
    lower_src: str
    line_no: int


_LINE_COMMENT_RE = re.compile(r"\s*([;#].*)?$")


def _strip_comment(line: str) -> str:
    """Drop trailing `;`/`#` comment if present. The first `;` is the
    upper/lower separator, NOT a comment — but only the first one. So
    we split on `;` once, allow a second `;` to start a comment."""
    return line.rstrip()


def _split_bundle(text: str) -> tuple[str, str, str]:
    """Split `<upper> ; <lower> [; comment]` into (upper, lower, comment).
    Returns ("", "", "") for an empty/comment-only line."""
    # Strip trailing `# comment` first (alternate comment style).
    hash_idx = text.find("#")
    if hash_idx >= 0:
        text = text[:hash_idx]
    text = text.strip()
    if not text:
        return ("", "", "")
    parts = text.split(";")
    # Re-attach any 3rd+ `;` chunks as comment text (harmless).
    if len(parts) == 1:
        return (parts[0].strip(), "", "")
    if len(parts) == 2:
        return (parts[0].strip(), parts[1].strip(), "")
    return (parts[0].strip(), parts[1].strip(), ";".join(parts[2:]).strip())


def _is_label(token: str) -> str | None:
    m = re.fullmatch(r"([A-Za-z_][A-Za-z0-9_]*):", token)
    return m.group(1) if m else None


_FMAC_MNEM_RE = re.compile(
    r"^([a-zA-Z][a-zA-Z0-9]*?)(?:\.([xyzwXYZW]+))?$"
)


def _try_encode_upper(text: str) -> int | None:
    """Encode a textual upper insn to a 32-bit int. Returns None if
    text is empty (caller treats as nop) or needs late resolution
    (currently no upper ops need a label)."""
    if not text or text.lower() == "nop":
        return encode_upper_nop()
    tok = text.split()
    head_raw = tok[0]
    head = head_raw.lower()
    if head == "pad":
        return encode_upper_pad()
    if head == ".word":
        if len(tok) != 2:
            raise EncodeError(f".word needs exactly one operand, got {text!r}")
        return _int(tok[1]) & 0xFFFFFFFF

    # FMAC mnemonics: <name>[.<mask>] vfd, vfs, vft
    #   broadcast:   addx.xy vf3, vf1, vf2      → family=add, bc=x
    #   plain:       add.xyzw vf3, vf1, vf2     → family=add (no bc)
    #   i/q variant: addi.w vf3, vf1            → I/Q implicit (no ft)
    #   ACC variant: mulax.xyzw vf1, vf30       → ACC implicit (no fd)
    m = _FMAC_MNEM_RE.match(head_raw)
    if m:
        name = m.group(1).lower()
        mask = m.group(2) or ""
        if name in _UPPER_PLAIN_OP6:
            operands = _parse_three_vf(tok[1:])
            if operands is not None:
                fd, fs, ft = operands
                return _enc_upper_plain(name, mask, fd, fs, ft)
        if name in _UPPER_IQ_OP6:
            operands = _parse_n_vf(tok[1:], n=2)
            if operands is not None:
                fd, fs = operands
                return _enc_upper_iq(name, mask, fd, fs)
        if name in _UPPER_FD_TABLE:
            _bc, _sub, shape = _UPPER_FD_TABLE[name]
            if shape == "acc":
                # vfs, vft — ACC implicit destination
                operands = _parse_n_vf(tok[1:], n=2)
                if operands is not None:
                    fs, ft = operands
                    return _enc_upper_fd(name, mask, fs, ft)
            elif shape == "fd2":
                # vft, vfs — ft is the destination
                operands = _parse_n_vf(tok[1:], n=2)
                if operands is not None:
                    ft, fs = operands
                    return _enc_upper_fd(name, mask, fs, ft)
            elif shape == "acc1":
                # vfs — vft implicit (ACC = fs op {I,Q})
                operands = _parse_n_vf(tok[1:], n=1)
                if operands is not None:
                    (fs,) = operands
                    return _enc_upper_fd(name, mask, fs, 0)
        # Broadcast: name ends in x/y/z/w AND the prefix is a known family.
        if len(name) >= 2 and name[-1] in "xyzw" and name[:-1] in _UPPER_BC_FAMILY:
            family, bc = name[:-1], name[-1]
            operands = _parse_three_vf(tok[1:])
            if operands is not None:
                fd, fs, ft = operands
                return _enc_upper_bc(family, bc, mask, fd, fs, ft)
    raise EncodeError(f"unknown upper insn: {text!r}")


def _parse_three_vf(tokens: list[str]) -> tuple[int, int, int] | None:
    out = _parse_n_vf(tokens, n=3)
    return out  # type: ignore[return-value]


def _parse_n_vf(tokens: list[str], n: int) -> tuple[int, ...] | None:
    """Parse N vfX operands after a mnemonic.  Returns None (not an
    exception) on shape mismatch so the caller can fall through to
    other mnemonic candidates."""
    joined = " ".join(tokens)
    parts = [p.strip() for p in joined.split(",")]
    if len(parts) != n:
        return None
    try:
        return tuple(_vf(p) for p in parts)
    except EncodeError:
        return None


def _try_encode_lower_late(text: str, pc: int,
                           labels: dict[str, int]) -> int:
    """Encode a textual lower insn. Branches resolve labels here.
    Called after the first pass collects label PCs."""
    if not text or text.lower() == "nop":
        return encode_lower_nop()
    if text.lower() == "nop_swap":
        return encode_lower_nop_swap()
    tok = re.split(r"[ ,]+", text)
    tok = [t for t in tok if t]
    head = tok[0].lower()
    if head == ".word":
        return _int(tok[1]) & 0xFFFFFFFF
    if head in _BRANCH_OPS:
        op6 = _BRANCH_OPS[head]
        # ibeq/ibne: ibeq vi_ft, vi_fs, target
        # bal:        bal  vi_ft, target
        # b/ibltz/...: <op> [vi_fs,] target
        if head in ("ibeq", "ibne"):
            if len(tok) != 4:
                raise EncodeError(f"{head} needs (ft, fs, target): {text!r}")
            ft = _vi(tok[1])
            fs = _vi(tok[2])
            target = _resolve_target(tok[3], labels)
            return _enc_branch(op6, pc, target, ft=ft, fs=fs)
        if head == "bal":
            if len(tok) != 3:
                raise EncodeError(f"bal needs (ft, target): {text!r}")
            ft = _vi(tok[1])
            target = _resolve_target(tok[2], labels)
            return _enc_branch(op6, pc, target, ft=ft)
        if head in ("ibltz", "ibgtz", "iblez", "ibgez"):
            if len(tok) != 3:
                raise EncodeError(f"{head} needs (fs, target): {text!r}")
            fs = _vi(tok[1])
            target = _resolve_target(tok[2], labels)
            return _enc_branch(op6, pc, target, fs=fs)
        # plain b: just target
        if head == "b":
            if len(tok) != 2:
                raise EncodeError(f"b needs (target): {text!r}")
            target = _resolve_target(tok[1], labels)
            return _enc_branch(op6, pc, target)
        raise EncodeError(f"unhandled branch shape: {text!r}")
    if head == "jr":
        if len(tok) != 2:
            raise EncodeError(f"jr needs (fs): {text!r}")
        return _enc_jr(_vi(tok[1]))
    if head == "jalr":
        if len(tok) != 3:
            raise EncodeError(f"jalr needs (ft, fs): {text!r}")
        return _enc_jalr(_vi(tok[1]), _vi(tok[2]))
    raise EncodeError(f"unknown lower insn: {text!r}")


def _resolve_target(tok: str, labels: dict[str, int]) -> int:
    """Branch target: either L_<hex> form, numeric (0x…), or a user
    label declared elsewhere in the file."""
    if tok in labels:
        return labels[tok]
    if re.fullmatch(r"L_[0-9A-Fa-f]+", tok):
        return int(tok[2:], 16)
    if re.fullmatch(r"0[xX][0-9A-Fa-f]+", tok) or tok.isdigit():
        return int(tok, 0)
    raise EncodeError(f"unresolved branch target: {tok!r}")


def _expand_macros(text: str) -> str:
    """Pre-pass: scan for `.macro NAME params... ... .endmacro` blocks,
    register them, then re-emit `text` with each call site replaced by
    the macro body (textual parameter substitution).

    Body lines that start with `.macro` themselves are an error;
    macros don't nest.  Comments inside the body are preserved
    verbatim (so the expanded source remains readable in --listing
    output)."""
    lines = text.splitlines()
    out: list[str] = []
    macros: dict[str, tuple[list[str], list[str]]] = {}
    i = 0
    while i < len(lines):
        line = lines[i]
        stripped = line.strip()
        if stripped.startswith(".macro"):
            # `.macro NAME p1 p2 ...`
            head = stripped[len(".macro"):].split()
            if not head:
                raise EncodeError(f"line {i+1}: .macro needs a name")
            name, *params = head
            body: list[str] = []
            i += 1
            while i < len(lines):
                inner = lines[i].strip()
                if inner.startswith(".macro"):
                    raise EncodeError(
                        f"line {i+1}: nested .macro not supported")
                if inner.startswith(".endmacro") or inner.startswith(".endm"):
                    break
                body.append(lines[i])
                i += 1
            else:
                raise EncodeError(f"line {i+1}: unterminated .macro {name}")
            macros[name] = (params, body)
            i += 1
            continue
        # Macro call? — first whitespace token matches a known macro name,
        # rest of line is arg list (comma- or whitespace-separated).
        head_tok = stripped.split()[0] if stripped.split() else ""
        if head_tok in macros:
            params, body = macros[head_tok]
            arg_text = stripped[len(head_tok):].strip()
            args = [a.strip() for a in re.split(r"[,\s]+", arg_text) if a.strip()]
            if len(args) != len(params):
                raise EncodeError(
                    f"line {i+1}: macro {head_tok} expects "
                    f"{len(params)} arg(s), got {len(args)}")
            subs = dict(zip(params, args))
            for body_line in body:
                # Whole-word textual substitution (avoid matching inside
                # other identifiers).
                expanded = body_line
                for p, a in subs.items():
                    expanded = re.sub(rf"\b{re.escape(p)}\b", a, expanded)
                out.append(expanded)
            i += 1
            continue
        out.append(line)
        i += 1
    return "\n".join(out)


def parse(text: str) -> tuple[list[ParsedBundle], dict[str, int], list[tuple[int, list[int]]]]:
    """Two-pass shell: pass 1 collects labels and per-bundle source text;
    pass 2 (caller) resolves branch targets via the labels map.

    Returns (bundles, labels, raw_blocks). `raw_blocks` are
    `.raw`-style byte sequences keyed by their start pc.
    """
    # First: expand macros into the raw text stream so the line-by-line
    # loop below sees only bundle lines / pragmas.
    text = _expand_macros(text)

    bundles: list[ParsedBundle] = []
    labels: dict[str, int] = {}
    raw_blocks: list[tuple[int, list[int]]] = []
    pc = 0
    seen_vu0 = False

    for line_no, raw_line in enumerate(text.splitlines(), 1):
        line = _strip_comment(raw_line)
        stripped = line.strip()
        # Whole-line comments. A leading `;` or `#` means there's no
        # upper-half before the separator, so the entire line is a
        # comment (NOT a bundle with an empty upper).
        if not stripped or stripped.startswith(";") or stripped.startswith("#"):
            continue

        # Pragmas.
        if stripped == ".vu0":
            seen_vu0 = True
            continue
        if stripped.startswith(".org") or stripped.startswith(".assert_pc"):
            want = _int(stripped.split(None, 1)[1])
            if want != pc:
                raise EncodeError(
                    f"line {line_no}: assertion failed — expected pc "
                    f"0x{want:X}, currently at 0x{pc:X}")
            continue
        if stripped.startswith(".bundle"):
            args = [a.strip() for a in stripped[len(".bundle"):].split(",")]
            if len(args) != 2:
                raise EncodeError(
                    f"line {line_no}: .bundle needs two operands (upper, lower)")
            upper = _int(args[0]) & 0xFFFFFFFF
            lower = _int(args[1]) & 0xFFFFFFFF
            bundles.append(ParsedBundle(pc, upper, lower, args[0], args[1], line_no))
            pc += 8
            continue
        if stripped.startswith(".raw"):
            byte_tokens = stripped[len(".raw"):].split()
            byte_vals = [_int(t) & 0xFF for t in byte_tokens]
            if len(byte_vals) % 8 != 0:
                raise EncodeError(
                    f"line {line_no}: .raw needs multiple-of-8 bytes")
            raw_blocks.append((pc, byte_vals))
            pc += len(byte_vals)
            continue

        # Standalone label line.
        label = _is_label(stripped)
        if label:
            if label in labels:
                raise EncodeError(f"line {line_no}: duplicate label {label}")
            labels[label] = pc
            continue

        # Bundle line: <upper> ; <lower>
        upper_src, lower_src, _comment = _split_bundle(line)

        # Inline label before bundle: "loop: nop ; nop"
        if ":" in upper_src and upper_src.split(None, 1)[0].endswith(":"):
            lab_tok, _, rest = upper_src.partition(" ")
            lab = _is_label(lab_tok)
            if lab:
                labels[lab] = pc
                upper_src = rest.strip()

        try:
            upper = _try_encode_upper(upper_src)
        except EncodeError as e:
            raise EncodeError(f"line {line_no}: upper: {e}") from e
        # Lower may need late resolution (branches with labels).
        bundles.append(ParsedBundle(pc, upper, None, upper_src, lower_src, line_no))
        pc += 8

    if not seen_vu0:
        # Soft warning, not an error — helps catch mis-routed files.
        print("warn: input lacks `.vu0` header pragma", file=sys.stderr)
    return bundles, labels, raw_blocks


def resolve(bundles: list[ParsedBundle], labels: dict[str, int]) -> bytes:
    """Pass 2: resolve lower-half branches, emit bundle bytes."""
    out = bytearray()
    expected_pc = 0
    for b in bundles:
        if b.pc != expected_pc:
            # Gap (raw block or pragma error). Caller's responsibility.
            out.extend(b"\x00" * (b.pc - expected_pc))
            expected_pc = b.pc
        try:
            lower = b.lower if b.lower is not None else \
                _try_encode_lower_late(b.lower_src, b.pc, labels)
        except EncodeError as e:
            raise EncodeError(f"line {b.line_no}: lower: {e}") from e
        # Bundle on disk: lower @+0, upper @+4, little-endian (matches
        # disasm_vu0.read_bundles which struct.unpack_from("<II", …) as
        # (lower, upper)).
        out.extend(int(lower).to_bytes(4, "little"))
        out.extend(int(b.upper or 0).to_bytes(4, "little"))
        expected_pc += 8
    return bytes(out)


def merge_raw(body: bytes, raw_blocks: list[tuple[int, list[int]]]) -> bytes:
    """Splice raw-byte blocks (.raw directive) into the bundle stream."""
    if not raw_blocks:
        return body
    buf = bytearray(body)
    for pc, byte_vals in raw_blocks:
        # Extend buffer if .raw lands past current end.
        if pc + len(byte_vals) > len(buf):
            buf.extend(b"\x00" * (pc + len(byte_vals) - len(buf)))
        for i, bv in enumerate(byte_vals):
            buf[pc + i] = bv & 0xFF
    return bytes(buf)


# ============================================================================
# Emission — generate a binutils-compatible .s file.
# ============================================================================

def emit_s_file(body: bytes, label: str, section: str) -> str:
    """Render body bytes as a `.word`-only `.s` file. The label/section
    mirror what splat's textbin emitter produced so the rest of the
    build (ld, postprocess passes) doesn't need to change."""
    lines = [
        '.include "macro.inc"',
        '',
        f'.section {section},"ax"',
        '',
        f'nonmatching {label}',
        '',
        f'glabel {label}',
    ]
    # Emit one .word per 32-bit half, 2 per bundle.
    for i in range(0, len(body), 4):
        word = int.from_bytes(body[i:i + 4], "little")
        lines.append(f"    .word 0x{word:08X}")
    lines.append(f'endlabel {label}')
    lines.append('')
    return "\n".join(lines)


# ============================================================================
# CLI
# ============================================================================

def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[1])
    ap.add_argument("input", help="path to .S source")
    ap.add_argument("--out", help="output .s path (default: <input stem>.s)")
    ap.add_argument("--raw", help="write raw bytes here instead of .s")
    ap.add_argument("--check", help="compare assembled bytes vs textbin path")
    ap.add_argument("--check-offset", type=lambda s: int(s, 0), default=0,
                    help="offset into --check file where assembled bytes start")
    ap.add_argument("--allow-short", action="store_true",
                    help="with --check, allow built bytes to be a prefix of ref")
    ap.add_argument("--label", default=None,
                    help="symbol name (default: __<dotted_input_path>)")
    ap.add_argument("--section", default=".text",
                    help='section name (default: .text — emitted as `.section <name>,"ax"`)')
    args = ap.parse_args(argv)

    src = Path(args.input)
    text = src.read_text()
    try:
        bundles, labels, raw_blocks = parse(text)
        body = resolve(bundles, labels)
        body = merge_raw(body, raw_blocks)
    except EncodeError as e:
        print(f"assemble_vu0: {src}: {e}", file=sys.stderr)
        return 2

    if args.check:
        ref = Path(args.check).read_bytes()
        ref_slice = ref[args.check_offset:args.check_offset + len(body)]
        n = min(len(body), len(ref_slice))
        for i in range(n):
            if body[i] != ref_slice[i]:
                print(f"mismatch at 0x{i:04X} (file offset 0x{args.check_offset + i:04X}):"
                      f" built=0x{body[i]:02X} ref=0x{ref_slice[i]:02X}")
                return 1
        if len(body) != len(ref):
            if not args.allow_short or len(body) > len(ref):
                print(f"length differs: built={len(body)} ref={len(ref)}"
                      f" (--allow-short to accept built as a prefix of ref)")
                return 1
            print(f"OK ({n} bytes match — built is a {len(body)}/{len(ref)} prefix)")
            return 0
        print(f"OK ({n} bytes match)")
        return 0

    if args.raw:
        Path(args.raw).write_bytes(body)
        return 0

    out_path = Path(args.out) if args.out else src.with_suffix(".s")
    label = args.label or "__" + src.stem
    s_text = emit_s_file(body, label, args.section)
    out_path.write_text(s_text)
    return 0


if __name__ == "__main__":
    sys.exit(main())
