#!/usr/bin/env python3
"""
test_assemble_vu0.py — round-trip self-test for tools/assemble_vu0.py.

Builds a small synthetic `.S` source using only the symbolic opcodes
`tools/disasm_vu0.py` reliably decodes (`nop`, `pad`, branches, raw
`.word`), assembles it, and verifies the byte output matches an
expected pattern. No disc data — the test is synthetic.

A second test, gated on `--against-textbin`, replays the first 8
bundles from `assets/cod/16F5E0.textbin.bin` through disasm → re-emit
→ assemble → compare. Skipped if the textbin is absent.

Run:
    .venv/bin/python tools/test_assemble_vu0.py
    .venv/bin/python tools/test_assemble_vu0.py --against-textbin
"""
from __future__ import annotations

import argparse
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))

import assemble_vu0  # noqa: E402


def _assemble(src_text: str) -> bytes:
    """Run assemble_vu0 in --raw mode against src_text."""
    with tempfile.TemporaryDirectory() as td:
        s = Path(td) / "in.S"
        s.write_text(src_text)
        out = Path(td) / "out.bin"
        rc = assemble_vu0.main([str(s), "--raw", str(out)])
        if rc != 0:
            raise RuntimeError(f"assemble_vu0 returned {rc}")
        return out.read_bytes()


def test_synthetic() -> None:
    """Mnemonics → bytes spot-checks."""
    cases = [
        # (label, src, expected raw bytes)
        ("zero-zero bundle",
         ".vu0\nnop ; nop\n",
         struct.pack("<II", 0, 0)),  # lower=0, upper=0
        ("upper pad + zero lower",
         ".vu0\npad ; nop\n",
         struct.pack("<II", 0, 0x000002FF)),
        ("raw .word upper + raw .word lower",
         ".vu0\n.word 0x4A000000 ; .word 0x12345678\n",
         struct.pack("<II", 0x12345678, 0x4A000000)),
        ("two-bundle block: pad ; pad",
         ".vu0\npad ; nop\npad ; nop\n",
         struct.pack("<IIII", 0, 0x000002FF, 0, 0x000002FF)),
    ]
    for name, src, expected in cases:
        got = _assemble(src)
        assert got == expected, (
            f"{name}: got {got.hex()} expected {expected.hex()}")
        print(f"  ok: {name}")


def test_branch() -> None:
    """Forward branch to a label resolves to the correct PC offset.

    Layout (16 bytes total):
        0x0000: nop ; b done
        0x0008: pad ; nop        ; delay slot
       done: (label at pc=0x0010 → falls past end)
    """
    src = (
        ".vu0\n"
        "nop ; b done\n"
        "pad ; nop\n"
        "done:\n"
    )
    body = _assemble(src)
    assert len(body) == 16, f"expected 16 bytes, got {len(body)}"
    lower0 = struct.unpack_from("<I", body, 0)[0]
    upper0 = struct.unpack_from("<I", body, 4)[0]
    assert upper0 == 0, f"upper0 should be 0 (nop), got 0x{upper0:08X}"
    # `b done` from pc=0 → target 0x10 → delta = 0x10 - 8 = 8 = 1 bundle.
    # Lower opcode is 7-bit at bits 25-31; b == 0x20; Imm11 == 1.
    expect = (0x20 << 25) | 1
    assert lower0 == expect, (
        f"branch encoding: got 0x{lower0:08X} expected 0x{expect:08X}")
    print(f"  ok: forward branch resolves to +1 bundle")


def test_backward_branch() -> None:
    """Backward branch: b loop where loop is 1 bundle behind."""
    src = (
        ".vu0\n"
        "loop:\n"
        "nop ; nop\n"
        "nop ; b loop\n"
    )
    body = _assemble(src)
    assert len(body) == 16
    lower1 = struct.unpack_from("<I", body, 8)[0]
    # `b loop` from pc=8 → target 0 → delta = 0 - 16 = -16 = -2 bundles.
    # 11-bit signed: -2 = 0x7FE (two's complement, 11-bit).
    expect = (0x20 << 25) | (0x7FE & 0x7FF)
    assert lower1 == expect, (
        f"backward branch: got 0x{lower1:08X} expected 0x{expect:08X}")
    print(f"  ok: backward branch resolves to -2 bundles")


def test_ibeq_with_regs() -> None:
    """ibeq vi02, vi01, target — three-operand branch with vi regs."""
    src = (
        ".vu0\n"
        "nop ; ibeq vi02, vi01, end\n"
        "pad ; nop\n"
        "end:\n"
    )
    body = _assemble(src)
    lower0 = struct.unpack_from("<I", body, 0)[0]
    # ibeq op7=0x28; ft=2 (vi02), fs=1 (vi01); Imm11=1.
    expect = (0x28 << 25) | (2 << 16) | (1 << 11) | 1
    assert lower0 == expect, (
        f"ibeq: got 0x{lower0:08X} expected 0x{expect:08X}")
    print(f"  ok: ibeq vi02, vi01, end encodes correctly")


def test_upper_fmac_broadcast() -> None:
    """Broadcast FMAC mnemonics encode correctly. Spot-checked
    against real ICO bundles (via the cross-validation script in the
    commit log)."""
    src = (
        ".vu0\n"
        "maddw.xyzw vf28, vf04, vf00 ; nop\n"   # 0x01E0270B
        "maddw.xyz  vf28, vf29, vf23 ; nop\n"   # 0x01D7EF0B
        "subw.x     vf30, vf00, vf00 ; nop\n"   # 0x01000787
        "mulx.w     vf25, vf17, vf30 ; nop\n"   # 0x003E8E58
    )
    body = _assemble(src)
    expected_uppers = [0x01E0270B, 0x01D7EF0B, 0x01000787, 0x003E8E58]
    for i, want in enumerate(expected_uppers):
        got = struct.unpack_from("<I", body, i * 8 + 4)[0]
        assert got == want, (
            f"bundle {i}: built upper=0x{got:08X} expected 0x{want:08X}")
    print(f"  ok: 4 broadcast FMAC encodings match real ICO textbin bundles")


def test_upper_fmac_plain() -> None:
    """Plain (non-broadcast) FMAC mnemonics. Two real ICO bundles +
    one synthetic."""
    src = (
        ".vu0\n"
        "add.xy   vf09, vf09, vf16 ; nop\n"     # 0x01904A68 (textbin pc=0x02B0)
        "sub.w    vf00, vf24, vf00 ; nop\n"     # 0x0020C02C (textbin pc=0x05A8)
        "msub.xyzw vf3, vf1, vf2  ; nop\n"      # synthetic
    )
    body = _assemble(src)
    got_b0 = struct.unpack_from("<I", body, 4)[0]
    got_b1 = struct.unpack_from("<I", body, 12)[0]
    got_b2 = struct.unpack_from("<I", body, 20)[0]
    assert got_b0 == 0x01904A68, f"add.xy bundle: 0x{got_b0:08X}"
    assert got_b1 == 0x0020C02C, f"sub.w bundle:  0x{got_b1:08X}"
    expect_b2 = (0xF << 21) | (2 << 16) | (1 << 11) | (3 << 6) | 0x2D
    assert got_b2 == expect_b2, f"msub: 0x{got_b2:08X} != 0x{expect_b2:08X}"
    print(f"  ok: 3 plain FMAC encodings (2 textbin-validated + 1 synthetic)")


def test_upper_pad_and_nop() -> None:
    """`pad` (0x000002FF) is FD_11 sub-op 0x0B = NOP. `nop` is true zero."""
    src = (
        ".vu0\n"
        "nop ; nop\n"
        "pad ; nop\n"
    )
    body = _assemble(src)
    upper0 = struct.unpack_from("<I", body, 4)[0]
    upper1 = struct.unpack_from("<I", body, 12)[0]
    assert upper0 == 0x00000000, f"nop upper: 0x{upper0:08X}"
    assert upper1 == 0x000002FF, f"pad upper: 0x{upper1:08X}"
    print(f"  ok: pad/nop distinct upper encodings preserved")


def test_dest_mask_parsing() -> None:
    """Dest mask is a 4-bit field; letter order in `.xyzw` doesn't matter."""
    import assemble_vu0 as A
    assert A._enc_dest_mask("xyzw") == 0xF
    assert A._enc_dest_mask("wzyx") == 0xF
    assert A._enc_dest_mask("x") == 0x8
    assert A._enc_dest_mask("w") == 0x1
    assert A._enc_dest_mask("xw") == 0x9
    assert A._enc_dest_mask("") == 0
    try:
        A._enc_dest_mask("xq")
    except A.EncodeError:
        pass
    else:
        raise AssertionError(".xq should error")
    print(f"  ok: dest mask parser handles order + invalid letters")


def test_upper_iq_variants() -> None:
    """i/q variants: 2-operand FMACs with I/Q implicit. Validated
    against real ICO bundles."""
    src = (
        ".vu0\n"
        "addi.w  vf14, vf00 ; nop\n"   # real bundle pc=0x10D0 → 0x002003A2
        "addi.xy vf14, vf00 ; nop\n"   # real bundle pc=0x10E0 → 0x018003A2
        "addq.x  vf29, vf00 ; nop\n"   # real bundle pc=0x27B0 → 0x01000760
    )
    body = _assemble(src)
    wants = [0x002003A2, 0x018003A2, 0x01000760]
    for i, want in enumerate(wants):
        got = struct.unpack_from("<I", body, i * 8 + 4)[0]
        assert got == want, f"bundle {i}: 0x{got:08X} != 0x{want:08X}"
    print(f"  ok: 3 i/q variants validated against real ICO bundles")


def test_upper_fd_acc_ops() -> None:
    """FD sub-table ACC ops: bc is implicit in mnemonic suffix,
    bits 6-10 carry the sub-opcode."""
    src = (
        ".vu0\n"
        "mulax.xyzw  vf01, vf21 ; nop\n"  # pc=0x04C8 → 0x01F509BC
        "madday.xyzw vf02, vf21 ; nop\n"  # pc=0x04D0 → 0x01F510BD
        "maddaz.xyzw vf03, vf21 ; nop\n"  # pc=0x04D8 → 0x01F518BE
    )
    body = _assemble(src)
    wants = [0x01F509BC, 0x01F510BD, 0x01F518BE]
    for i, want in enumerate(wants):
        got = struct.unpack_from("<I", body, i * 8 + 4)[0]
        assert got == want, f"bundle {i}: 0x{got:08X} != 0x{want:08X}"
    print(f"  ok: 3 ACC FMAC bundles validated (matrix-mul mulax/madday/maddaz idiom)")


def test_upper_fd_ftoi() -> None:
    """FTOI/ITOF: 2-operand, ft is destination."""
    src = (
        ".vu0\n"
        "ftoi4.xyzw vf10, vf09 ; nop\n"   # pc=0x02D8 → 0x01EA497D
    )
    body = _assemble(src)
    got = struct.unpack_from("<I", body, 4)[0]
    assert got == 0x01EA497D, f"0x{got:08X}"
    print(f"  ok: ftoi4.xyzw vf10,vf09 → 0x{got:08X} (ft=dest, fs=source)")


def test_lower_lsu() -> None:
    """LQ/SQ load/store quadword. Note: LQ and SQ swap vf and vi
    bit positions (vf at 11-15 for SQ, at 16-20 for LQ; vi at the
    other position). All cases cross-validated against real ICO
    bundles."""
    src = (
        ".vu0\n"
        "nop ; lq.xyzw vf30, 2(vi00)\n"   # pc=0x01A0 → lower 0x01FE0002
        "nop ; sq.xyzw vf30, 2(vi00)\n"   # pc=0x01B8 → lower 0x03E0F002
    )
    body = _assemble(src)
    wants = [0x01FE0002, 0x03E0F002]
    for i, want in enumerate(wants):
        got = struct.unpack_from("<I", body, i * 8)[0]
        assert got == want, f"bundle {i}: 0x{got:08X} != 0x{want:08X}"
    print(f"  ok: lq + sq encodings validated against real ICO bundles")


def test_lower_iaddiu_isubiu() -> None:
    """IADDIU/ISUBIU integer add/subtract immediate. Imm15 splits
    across bits 21-24 (upper 4) and bits 0-10 (lower 11)."""
    src = (
        ".vu0\n"
        "nop ; iaddiu vi07, vi12, 191\n"  # pc=0x0120 → 0x100760BF
        "nop ; isubiu vi10, vi10, 1\n"    # pc=0x2180 → 0x120A5001
    )
    body = _assemble(src)
    wants = [0x100760BF, 0x120A5001]
    for i, want in enumerate(wants):
        got = struct.unpack_from("<I", body, i * 8)[0]
        assert got == want, f"bundle {i}: 0x{got:08X} != 0x{want:08X}"
    print(f"  ok: iaddiu + isubiu encodings validated against real ICO bundles")


def test_iaddiu_imm15_split() -> None:
    """Imm15 high-nibble survives the upper-bits split correctly."""
    import assemble_vu0 as A
    # imm15 = 0x4321: upper 4 bits = 0x8 (= 0x4321 >> 11), lower 11 = 0x321
    got = A._enc_lower_iaddiu(0, 0, 0x4321)
    expected = (0x08 << 25) | (0x8 << 21) | (0 << 16) | (0 << 11) | 0x321
    assert got == expected, f"got 0x{got:08X} expected 0x{expected:08X}"
    print(f"  ok: iaddiu imm15 0x4321 splits as 0x8<<21 | 0x321")


def test_nop_swap() -> None:
    """The 0x8000033C BIOS-bug NOP pattern is its own mnemonic now.

    PCSX2 microVU_Compile.inl mVUcheckBadOp: this exact byte pattern
    is what the BIOS emits when upper/lower NOP slots get swapped;
    PCSX2 silently passes it as a no-op. Treat it as a distinct
    mnemonic so the byte-perfect round trip stays explicit."""
    src = (
        ".vu0\n"
        "pad ; nop_swap\n"
    )
    body = _assemble(src)
    lower = struct.unpack_from("<I", body, 0)[0]
    upper = struct.unpack_from("<I", body, 4)[0]
    assert lower == 0x8000033C, f"got 0x{lower:08X}"
    assert upper == 0x000002FF, f"got 0x{upper:08X}"
    print(f"  ok: nop_swap encodes 0x8000033C (BIOS-bug NOP)")


def test_dot_bundle_escape() -> None:
    """`.bundle` directive emits upper/lower verbatim."""
    src = (
        ".vu0\n"
        ".bundle 0xDEADBEEF, 0xCAFEBABE\n"
    )
    body = _assemble(src)
    # Order on disk: lower @+0, upper @+4
    expect = struct.pack("<II", 0xCAFEBABE, 0xDEADBEEF)
    assert body == expect, f"got {body.hex()} expected {expect.hex()}"
    print(f"  ok: .bundle escape preserves bytes verbatim")


def test_macro_expansion() -> None:
    """Macro defs expand to bundle sequences with arg substitution."""
    src = (
        ".vu0\n"
        ".macro JMP target\n"
        "    pad ; b target\n"
        ".endmacro\n"
        "JMP done\n"
        "pad ; nop\n"
        "done:\n"
    )
    body = _assemble(src)
    assert len(body) == 16, f"expected 16 bytes, got {len(body)}"
    # First bundle: pad upper, b done (forward 1 bundle)
    lower0 = struct.unpack_from("<I", body, 0)[0]
    upper0 = struct.unpack_from("<I", body, 4)[0]
    assert upper0 == 0x000002FF, f"upper0 not pad: 0x{upper0:08X}"
    # b done: pc=0, target=0x10, delta=8, bundles=1, op7=0x20 (7-bit dispatch)
    assert lower0 == (0x20 << 25) | 1, f"branch enc wrong: 0x{lower0:08X}"
    print(f"  ok: .macro JMP target expands to pad ; b target")


def test_assert_pc_directive() -> None:
    """`.assert_pc` catches stale PC expectations without advancing."""
    src = (
        ".vu0\n"
        "pad ; nop\n"
        "pad ; nop\n"
        ".assert_pc 0x10\n"
        "pad ; nop\n"
    )
    body = _assemble(src)
    assert len(body) == 24, f"expected 24 bytes, got {len(body)}"
    print(f"  ok: .assert_pc 0x10 accepted at pc=0x10")
    # Negative case: mismatched assert
    bad = (
        ".vu0\n"
        "pad ; nop\n"
        ".assert_pc 0x10\n"   # we're actually at 0x08
    )
    try:
        _assemble(bad)
    except RuntimeError:
        print(f"  ok: .assert_pc 0x10 rejected at pc=0x08")
        return
    raise AssertionError(".assert_pc mismatch did not raise")


def test_against_textbin() -> None:
    """Disassemble first 8 bundles, re-emit as `.bundle` lines, assemble,
    compare. This tests that the round-trip via the `.bundle` escape
    hatch is byte-perfect.  Symbolic round-trip will be tested per
    opcode family as encoders land."""
    textbin = REPO / "assets" / "cod" / "16F5E0.textbin.bin"
    if not textbin.exists():
        print("  skip: assets/cod/16F5E0.textbin.bin not found")
        return
    data = textbin.read_bytes()[:64]  # first 8 bundles
    lines = [".vu0"]
    for pc in range(0, 64, 8):
        lower, upper = struct.unpack_from("<II", data, pc)
        lines.append(f".bundle 0x{upper:08X}, 0x{lower:08X}")
    src = "\n".join(lines) + "\n"
    body = _assemble(src)
    assert body == data, (
        f"textbin round-trip: divergence at "
        f"byte {next((i for i in range(len(data)) if i < len(body) and body[i] != data[i]), -1)}")
    print(f"  ok: first 8 bundles round-trip via .bundle escape (64 bytes)")


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--against-textbin", action="store_true",
                    help="also test against assets/cod/16F5E0.textbin.bin")
    args = ap.parse_args(argv)
    print("test_assemble_vu0:")
    test_synthetic()
    test_branch()
    test_backward_branch()
    test_ibeq_with_regs()
    test_dot_bundle_escape()
    test_macro_expansion()
    test_assert_pc_directive()
    test_dest_mask_parsing()
    test_upper_pad_and_nop()
    test_upper_fmac_broadcast()
    test_upper_fmac_plain()
    test_upper_iq_variants()
    test_upper_fd_acc_ops()
    test_upper_fd_ftoi()
    test_lower_lsu()
    test_lower_iaddiu_isubiu()
    test_iaddiu_imm15_split()
    test_nop_swap()
    if args.against_textbin:
        test_against_textbin()
    print("all tests passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
