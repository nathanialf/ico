#!/usr/bin/env python3
"""Unit tests for tools/stack_diff.py (reccmp stackcmp port).

Hermetic: operates on hand-built canonical streams, no compile pipeline.
Run:  .venv/bin/python tools/test_stack_diff.py
"""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import stack_diff as sd  # noqa: E402


def n(lines):
    return [l.replace(" ", "\t", 1) for l in lines]


class TestStackRefExtraction(unittest.TestCase):
    def test_load_store(self):
        self.assertEqual(sd.stack_ref("sd\ts0,48(sp)"), ("sp", 48, "sd"))
        self.assertEqual(sd.stack_ref("lwc1\t$f0,-8(s8)"), ("s8", -8, "lwc1"))
        self.assertEqual(sd.stack_ref("lq\tv0,16(fp)"), ("fp", 16, "lq"))

    def test_address_of_slot(self):
        self.assertEqual(sd.stack_ref("addiu\ta0,sp,16"), ("sp", 16, "addiu"))
        self.assertEqual(sd.stack_ref("daddiu\ts2,sp,32"), ("sp", 32, "daddiu"))

    def test_frame_adjust_is_not_a_slot(self):
        self.assertIsNone(sd.stack_ref("addiu\tsp,sp,-192"))
        self.assertIsNone(sd.stack_ref("addiu\tsp,sp,192"))

    def test_non_stack(self):
        self.assertIsNone(sd.stack_ref("lw\tv0,0(a0)"))
        self.assertIsNone(sd.stack_ref("addiu\tv0,zero,30"))
        self.assertIsNone(sd.stack_ref("lw\tv0,-32760(gp)"))

    def test_frame_size(self):
        self.assertEqual(sd.frame_size(n(["addiu sp,sp,-96", "sd ra,80(sp)"])), 96)
        self.assertIsNone(sd.frame_size(n(["addu v0,a0,a1", "jr ra"])))


class TestSlotPairing(unittest.TestCase):
    def test_identical_streams_identity_map(self):
        a = n(["addiu sp,sp,-32", "sd s0,16(sp)", "sd ra,24(sp)",
               "ld ra,24(sp)", "ld s0,16(sp)", "jr ra", "addiu sp,sp,32"])
        r = sd.analyze_streams(a, list(a))
        self.assertTrue(r["bijective"])
        self.assertEqual(r["frame_expected"], 32)
        self.assertEqual({(tuple(e), tuple(b)) for e, b in r["pairs"]},
                         {(("sp", 16), ("sp", 16)), (("sp", 24), ("sp", 24))})

    def test_consistent_slot_shift(self):
        # every slot moved by +16 but the map is still a bijection: the
        # "layout shifted as a block" signature (one decl moved)
        a = n(["addiu sp,sp,-48", "sd s0,16(sp)", "sd ra,32(sp)",
               "ld ra,32(sp)", "ld s0,16(sp)", "jr ra"])
        b = n(["addiu sp,sp,-64", "sd s0,32(sp)", "sd ra,48(sp)",
               "ld ra,48(sp)", "ld s0,32(sp)", "jr ra"])
        r = sd.analyze_streams(a, b)
        self.assertTrue(r["bijective"])
        self.assertNotEqual(r["frame_expected"], r["frame_built"])
        m = {tuple(e): tuple(bb) for e, bb in r["pairs"]}
        self.assertEqual(m[("sp", 16)], ("sp", 32))
        self.assertEqual(m[("sp", 32)], ("sp", 48))

    def test_non_bijective_coalesced_slots(self):
        # expected uses two distinct slots where built reuses one
        a = n(["sw v0,16(sp)", "nop", "sw v1,20(sp)", "jr ra"])
        b = n(["sw v0,16(sp)", "nop", "sw v1,16(sp)", "jr ra"])
        r = sd.analyze_streams(a, b)
        self.assertFalse(r["bijective"])
        self.assertEqual(r["non_bijective_built"], [("sp", 16)])

    def test_non_bijective_split_slot(self):
        a = n(["sw v0,16(sp)", "nop", "sw v1,16(sp)", "jr ra"])
        b = n(["sw v0,16(sp)", "nop", "sw v1,20(sp)", "jr ra"])
        r = sd.analyze_streams(a, b)
        self.assertFalse(r["bijective"])
        self.assertEqual(r["non_bijective_expected"], [("sp", 16)])

    def test_structural_mismatch_flagged(self):
        # built has an extra spill: no positional correspondence for it
        a = n(["addiu sp,sp,-32", "sd ra,24(sp)", "jal T", "nop", "jr ra"])
        b = n(["addiu sp,sp,-32", "sd ra,24(sp)", "sd s0,16(sp)",
               "jal T", "nop", "jr ra"])
        r = sd.analyze_streams(a, b)
        self.assertGreaterEqual(r["structural_blocks"], 1)
        self.assertIn(("sp", 16), r["built_unpaired"])
        self.assertFalse(r["bijective"])

    def test_one_sided_ref_in_paired_line(self):
        # replace pair where only one side touches the stack
        a = n(["sw v0,16(sp)", "jr ra"])
        b = n(["sw v0,0(a0)", "jr ra"])
        r = sd.analyze_streams(a, b)
        self.assertGreaterEqual(r["structural_blocks"], 1)
        self.assertIn(("sp", 16), r["expected_unpaired"])

    def test_sp_and_fp_kept_apart(self):
        a = n(["sw v0,16(sp)", "sw v1,16(s8)", "jr ra"])
        r = sd.analyze_streams(a, list(a))
        self.assertTrue(r["bijective"])
        self.assertEqual(len(r["pairs"]), 2)

    def test_no_stack_refs_is_clean(self):
        a = n(["addu v0,a0,a1", "jr ra"])
        r = sd.analyze_streams(a, list(a))
        self.assertTrue(r["bijective"])
        self.assertEqual(r["pairs"], [])


if __name__ == "__main__":
    unittest.main()
