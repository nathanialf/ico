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
    0x0: "addbc",
    0x1: "subbc",
    0x2: "maddbc",
    0x3: "msubbc",
    0x4: "maxbc",
    0x5: "minibc",
    0x6: "mulbc",
}


def decode_upper(w: int) -> str:
    """Decode the 32-bit upper instruction. Conservative: only the
    well-known no-op and LOI patterns are decoded. Every FMAC opcode
    family is emitted as `.word` because hand-typed decode tables
    here would risk mis-decoding — the developer cross-references
    each line against a VU0 reference manual anyway.

    Reliable cases handled:
      * w == 0 → nop
      * w == 0x000002FF → nop (canonical upper-pad filler)
      * bit 31 set → LOI marker (next bundle's lower 32 bits are a
        float immediate)
      * otherwise → `.word 0x<hex>` with field-position annotation
        to aid manual decoding.
    """
    if w == 0 or (w & 0x7FFFFFFF) == 0:
        return "nop"
    if w == 0x000002FF:
        # Canonical upper-pad bit pattern. Distinct from a true zero
        # nop — `tools/assemble_vu0.py` accepts `pad` as the mnemonic
        # for this form (and `nop` for the zero form). Keeping the
        # distinction in disassembly output preserves the bytes
        # across the round trip.
        return "pad"
    if bits(w, 31, 31):
        return f".word 0x{w:08X}  ; I-bit set (likely LOI; next bundle lower = float imm)"
    # Annotate a few fields to help the reader cross-reference against
    # a VU0 instruction encoding table.
    fd, fs, ft = fd_fs_ft(w)
    dst = dest_bcc(w)
    return (f".word 0x{w:08X}"
            f"  ; upper FMAC — dst={dst} fd={fd} fs={fs} ft={ft}"
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
