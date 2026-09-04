#!/usr/bin/env python3
"""Unit tests for tools/match_diff.py's pure-stream analyses:

  * detect_register_bijection (adapted from isledecomp/reccmp swap.py)
  * call-site-pinned alignment (adapted from isledecomp/reccmp
    pinned_sequences.py SequenceMatcherWithPins)
  * the count_and_pairs / _refined_count metric invariants the pinned pass
    must preserve

Run:  .venv/bin/python -m pytest tools/test_match_diff.py -q
  or: .venv/bin/python tools/test_match_diff.py
No compile pipeline involved — these operate on hand-built canonical streams
(the `mnem\\top1,op2` form quick_diff emits), so they are fast and hermetic.
"""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import match_diff as md  # noqa: E402


def n(lines):
    """Build a canonical stream from 'mnem op1,op2' strings (space -> tab)."""
    return [l.replace(" ", "\t", 1) for l in lines]


class TestRegisterBijection(unittest.TestCase):
    # -- positives ---------------------------------------------------------
    def test_simple_swap(self):
        exp = n(["addu v0,a0,a1", "sw v0,0(a2)", "jr ra"])
        blt = n(["addu v1,a0,a1", "sw v1,0(a2)", "jr ra"])
        r = md.detect_register_bijection(exp, blt)
        self.assertIsNotNone(r)
        self.assertEqual(r["map"], {"v0": "v1"})

    def test_two_reg_cycle(self):
        exp = n(["daddu s0,a0,zero", "daddu s1,a1,zero",
                 "lw t0,0(s0)", "lw t1,0(s1)", "jr ra"])
        blt = n(["daddu s1,a0,zero", "daddu s0,a1,zero",
                 "lw t0,0(s1)", "lw t1,0(s0)", "jr ra"])
        r = md.detect_register_bijection(exp, blt)
        self.assertIsNotNone(r)
        self.assertEqual(r["map"], {"s0": "s1", "s1": "s0"})

    def test_mem_operand_base_reg(self):
        exp = n(["lw v0,4(s0)", "jr ra"])
        blt = n(["lw v0,4(s1)", "jr ra"])
        r = md.detect_register_bijection(exp, blt)
        self.assertIsNotNone(r)
        self.assertEqual(r["map"], {"s0": "s1"})

    def test_fpr_swap(self):
        exp = n(["lwc1 $f0,0(a0)", "swc1 $f0,4(a0)", "jr ra"])
        blt = n(["lwc1 $f2,0(a0)", "swc1 $f2,4(a0)", "jr ra"])
        r = md.detect_register_bijection(exp, blt)
        self.assertIsNotNone(r)
        self.assertEqual(r["map"], {"f0": "f2"})

    def test_s8_is_parsed(self):
        # objdump spells $30 as `s8` in the canonical stream (measured on
        # build/quick_diff objects); the token regex must accept it.
        exp = n(["daddu s8,a0,zero", "lw v0,8(s8)", "jr ra"])
        blt = n(["daddu s7,a0,zero", "lw v0,8(s7)", "jr ra"])
        r = md.detect_register_bijection(exp, blt)
        self.assertIsNotNone(r)
        self.assertEqual(r["map"], {"s8": "s7"})

    # -- negatives: structural, not a renaming -----------------------------
    def test_different_mnemonic(self):
        exp = n(["addu v0,a0,a1", "jr ra"])
        blt = n(["subu v0,a0,a1", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    def test_insert_delete(self):
        exp = n(["addu v0,a0,a1", "nop", "jr ra"])
        blt = n(["addu v0,a0,a1", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    def test_immediate_diff(self):
        exp = n(["addiu v0,a0,8", "jr ra"])
        blt = n(["addiu v0,a0,16", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    def test_mem_offset_diff(self):
        # same base, different frame slot: stack_diff territory, not a rename
        exp = n(["lw v0,16(sp)", "jr ra"])
        blt = n(["lw v0,24(sp)", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    def test_gpr_fpr_class_mismatch(self):
        exp = n(["mtc1 v0,$f0", "jr ra"])
        blt = n(["mtc1 v1,$f2", "jr ra"])
        r = md.detect_register_bijection(exp, blt)
        self.assertIsNotNone(r)          # v0->v1 and f0->f2, classes kept apart
        exp = n(["daddu v0,a0,zero", "jr ra"])
        blt = n(["daddu $f2,a0,zero", "jr ra"])   # nonsense, but must not pair
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    def test_non_injective(self):
        # v0->t0 in one line, v1->t0 in another: two sources, one target
        exp = n(["addu v0,a0,a1", "sw v0,0(a2)",
                 "addu v1,a0,a3", "sw v1,4(a2)", "jr ra"])
        blt = n(["addu t0,a0,a1", "sw t0,0(a2)",
                 "addu t0,a0,a3", "sw t0,4(a2)", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    def test_inconsistent_map(self):
        # v0->v1 in one line, v0->t0 in another
        exp = n(["addu v0,a0,a1", "nop", "sw v0,0(a2)", "jr ra"])
        blt = n(["addu v1,a0,a1", "nop", "sw t0,0(a2)", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    # -- negatives: the holes closed in this pass --------------------------
    def test_identity_conflict_in_same_line(self):
        # expected `addu v0,v1,a0` vs built `addu v1,v1,a0`: operand 1 claims
        # v0->v1, but operand 2 keeps v1 as itself — renaming built's v1 back
        # to v0 would also change operand 2, so this is NOT one consistent
        # injective renaming and must not be flagged as one.
        exp = n(["addu v0,v1,a0", "jr ra"])
        blt = n(["addu v1,v1,a0", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    def test_identity_conflict_mem_base(self):
        # same conflict via a memory-operand base register
        exp = n(["lw v0,0(v1)", "jr ra"])
        blt = n(["lw v1,0(v1)", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    def test_identity_conflict_across_lines(self):
        # v0->v1 in line 1; line 2 differs elsewhere but keeps v1 unchanged
        exp = n(["addu v0,a0,a1", "nop", "addu t0,v1,a2", "jr ra"])
        blt = n(["addu v1,a0,a1", "nop", "addu t1,v1,a2", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    def test_zero_not_renameable(self):
        # `daddu a0,s1,zero` vs `daddu a0,s1,v0` is register REUSE of a value
        # that happens to be 0 (remat-0 / const-temp source-shape class), not a
        # coloring convergence — zero is hardwired and cannot be renamed.
        exp = n(["daddu a0,s1,zero", "jr ra"])
        blt = n(["daddu a0,s1,v0", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    def test_sp_not_renameable(self):
        exp = n(["lw v0,16(sp)", "jr ra"])
        blt = n(["lw v0,16(s0)", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))

    def test_identity_only_residual_is_none(self):
        # all differing operands non-register -> None (unchanged behavior)
        exp = n(["lui v0,0x10", "jr ra"])
        blt = n(["lui v0,0x20", "jr ra"])
        self.assertIsNone(md.detect_register_bijection(exp, blt))


class TestCallSitePins(unittest.TestCase):
    def test_pins_matched_counts(self):
        a = n(["nop", "jal T", "nop", "jal T", "jr ra"])
        b = n(["nop", "nop", "jal T", "jal T", "jr ra"])
        self.assertEqual(md.call_site_pins(a, b), [(1, 2), (3, 3)])

    def test_no_pins_on_count_mismatch(self):
        a = n(["jal T", "jal T", "jr ra"])
        b = n(["jal T", "jr ra"])
        self.assertEqual(md.call_site_pins(a, b), [])

    def test_no_pins_without_calls(self):
        a = n(["nop", "jr ra"])
        self.assertEqual(md.call_site_pins(a, a), [])


class TestPinnedAlignment(unittest.TestCase):
    def _counts(self, a, b):
        sm_ops = md.difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes()
        unpinned = md._refined_count(a, b, sm_ops)
        pinned, npins = md.count_pinned(a, b)
        return unpinned, pinned, npins

    def test_identical_streams_zero(self):
        a = n(["addiu sp,sp,-16", "jal T", "nop", "jr ra"])
        u, p, npins = self._counts(a, list(a))
        self.assertEqual((u, p), (0, 0))
        self.assertEqual(npins, 1)

    def test_no_calls_equals_unpinned(self):
        a = n(["addu v0,a0,a1", "sw v0,0(a2)", "nop", "jr ra"])
        b = n(["addu v1,a0,a1", "sw v1,0(a2)", "nop", "jr ra"])
        u, p, npins = self._counts(a, b)
        self.assertEqual(npins, 0)
        self.assertEqual(p, u)

    def test_cross_call_cascade_contained(self):
        # A repetitive body around two calls, with one real one-line diff in
        # the SECOND call's segment. Greedy whole-stream matching can anchor
        # the repeated `lw v0,0(s0)` lines across the call boundary and charge
        # the same region twice; pinning at the calls forbids any pairing that
        # crosses a call, so the pinned count can never exceed the unpinned
        # one on this shape, and localizes the diff to one segment.
        seg = ["lw v0,0(s0)", "addiu v0,v0,1", "sw v0,0(s0)"]
        a = n(seg + ["jal T", "nop"] + seg + ["jal T", "nop", "jr ra"])
        bseg2 = ["lw v0,0(s0)", "addiu v0,v0,2", "sw v0,0(s0)"]
        b = n(seg + ["jal T", "nop"] + bseg2 + ["jal T", "nop", "jr ra"])
        u, p, npins = self._counts(a, b)
        self.assertEqual(npins, 2)
        self.assertEqual(p, 1)
        self.assertLessEqual(p, u)

    def test_pinned_never_pairs_across_pin(self):
        # An instruction deleted before call 1 and an identical one inserted
        # after call 1: unpinned difflib may pair them (charging a move);
        # pinned alignment treats them as one delete + one insert, each in its
        # own segment. Both charge 2 here; assert the pinned structure.
        a = n(["sw s0,0(sp)", "jal T", "nop", "jr ra"])
        b = n(["jal T", "nop", "sw s0,0(sp)", "jr ra"])
        pins = md.call_site_pins(a, b)
        self.assertEqual(pins, [(1, 0)])
        ops = md.pinned_opcodes(a, b, pins)
        # segment 1: pure delete of sw; segment 2: insert of sw, each kept in
        # its own segment (separated by the equal jal/nop run — no merge)
        kinds = [op for op, *_ in ops]
        self.assertEqual(kinds, ["delete", "equal", "insert", "equal"])
        p, _ = md.count_pinned(a, b)
        self.assertEqual(p, 2)

    def test_zero_iff_identical(self):
        # pinned count 0 must imply stream equality (no false rc0)
        a = n(["jal T", "nop", "addu v0,a0,a1", "jr ra"])
        b = n(["jal T", "nop", "addu v1,a0,a1", "jr ra"])
        p, _ = md.count_pinned(a, b)
        self.assertGreater(p, 0)

    def test_merge_opcode_regions(self):
        ops = [("equal", 0, 2, 0, 2), ("delete", 2, 3, 2, 2),
               ("insert", 3, 3, 2, 3), ("equal", 3, 5, 3, 5),
               ("equal", 5, 7, 5, 7)]
        merged = md._merge_opcode_regions(ops)
        self.assertEqual(merged, [("equal", 0, 2, 0, 2),
                                  ("replace", 2, 3, 2, 3),
                                  ("equal", 3, 7, 3, 7)])

    def test_nonmonotonic_pins_fall_back(self):
        a = n(["nop"] * 4)
        b = n(["nop"] * 4)
        ops = md.pinned_opcodes(a, b, [(3, 1), (1, 3)])
        self.assertEqual(ops, [("equal", 0, 4, 0, 4)])


class TestMetricInvariants(unittest.TestCase):
    def test_count_and_pairs_unchanged_semantics(self):
        # the gated metric: one replace region charges max(len_e, len_b)
        a = n(["addu v0,a0,a1", "nop", "jr ra"])
        b = n(["addu v1,a0,a1", "addu v1,v1,a2", "nop", "jr ra"])
        count, pairs = md.count_and_pairs(a, b)
        self.assertEqual(count, 2)
        self.assertEqual(len(pairs), 2)


if __name__ == "__main__":
    unittest.main()
