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
    `pad` by disasm_vu0.py; written as `pad ; <lower>` in source."""
    return 0x000002FF


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


def _enc_branch(op6: int, pc: int, target_pc: int,
                ft: int = 0, fs: int = 0) -> int:
    """Encode an 11-bit PC-relative branch in units of bundles."""
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
    return (op6 << 26) | (ft << 16) | (fs << 11) | offset


def _enc_jr(fs: int) -> int:
    return (0x24 << 26) | (fs << 11)


def _enc_jalr(ft: int, fs: int) -> int:
    return (0x25 << 26) | (ft << 16) | (fs << 11)


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


def _try_encode_upper(text: str) -> int | None:
    """Encode a textual upper insn to a 32-bit int. Returns None if
    text is empty (caller treats as nop) or needs late resolution
    (currently no upper ops need a label)."""
    if not text or text.lower() == "nop":
        return encode_upper_nop()
    tok = text.split()
    head = tok[0].lower()
    if head == "pad":
        return encode_upper_pad()
    if head == ".word":
        if len(tok) != 2:
            raise EncodeError(f".word needs exactly one operand, got {text!r}")
        return _int(tok[1]) & 0xFFFFFFFF
    raise EncodeError(f"unknown upper insn: {text!r}")


def _try_encode_lower_late(text: str, pc: int,
                           labels: dict[str, int]) -> int:
    """Encode a textual lower insn. Branches resolve labels here.
    Called after the first pass collects label PCs."""
    if not text or text.lower() == "nop":
        return encode_lower_nop()
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


def parse(text: str) -> tuple[list[ParsedBundle], dict[str, int], list[tuple[int, list[int]]]]:
    """Two-pass shell: pass 1 collects labels and per-bundle source text;
    pass 2 (caller) resolves branch targets via the labels map.

    Returns (bundles, labels, raw_blocks). `raw_blocks` are
    `.raw`-style byte sequences keyed by their start pc.
    """
    bundles: list[ParsedBundle] = []
    labels: dict[str, int] = {}
    raw_blocks: list[tuple[int, list[int]]] = []
    pc = 0
    seen_vu0 = False

    for line_no, raw_line in enumerate(text.splitlines(), 1):
        line = _strip_comment(raw_line)
        if not line.strip():
            continue
        stripped = line.strip()

        # Pragmas.
        if stripped == ".vu0":
            seen_vu0 = True
            continue
        if stripped.startswith(".org"):
            want = _int(stripped.split(None, 1)[1])
            if want != pc:
                raise EncodeError(
                    f"line {line_no}: .org 0x{want:X} != current pc 0x{pc:X}")
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
        n = min(len(body), len(ref))
        for i in range(n):
            if body[i] != ref[i]:
                print(f"mismatch at 0x{i:04X}: built=0x{body[i]:02X} "
                      f"ref=0x{ref[i]:02X}")
                return 1
        if len(body) != len(ref):
            print(f"length differs: built={len(body)} ref={len(ref)}")
            return 1
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
