#!/usr/bin/env python3
"""Unit tests for tools/data_diff.py (reccmp datacmp/vtable port).

Pure-function tests are hermetic; the ELF-backed tests run against the
in-repo target/built ELFs and are skipped when those artifacts are absent
(fresh clone before extract_elf.sh / ninja).

Run:  .venv/bin/python tools/test_data_diff.py
"""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import data_diff as dd  # noqa: E402

HAVE_ELFS = dd.BUILT_ELF.exists() and dd.BASE_ELF.exists()


class TestEffectiveSizes(unittest.TestCase):
    def test_recorded_size_kept(self):
        syms = [("A", 0x100, 8, ".data", 0x200)]
        self.assertEqual(dd.effective_sizes(syms), [("A", 0x100, 8, ".data")])

    def test_zero_size_gets_gap_to_next(self):
        syms = [("A", 0x100, 0, ".data", 0x200),
                ("B", 0x140, 0, ".data", 0x200)]
        self.assertEqual(dd.effective_sizes(syms),
                         [("A", 0x100, 0x40, ".data"),
                          ("B", 0x140, 0xC0, ".data")])

    def test_gap_skips_other_section(self):
        syms = [("A", 0x100, 0, ".data", 0x200),
                ("R", 0x180, 0, ".rodata", 0x300)]
        # A's gap must run to its own section end, not to R
        self.assertEqual(dd.effective_sizes(syms)[0], ("A", 0x100, 0x100, ".data"))

    def test_alias_at_same_vma_not_zero_gap(self):
        syms = [("A", 0x100, 0, ".data", 0x200),
                ("A_alias", 0x100, 0, ".data", 0x200),
                ("B", 0x110, 0, ".data", 0x200)]
        r = dd.effective_sizes(syms)
        self.assertEqual(r[0][2], 0x10)   # gap to the next DISTINCT vma
        self.assertEqual(r[1][2], 0x10)

    def test_clamped_to_section_end(self):
        # recorded size spilling past the target section end is clamped
        syms = [("A", 0x1F0, 0x40, ".data", 0x200)]
        self.assertEqual(dd.effective_sizes(syms), [("A", 0x1F0, 0x10, ".data")])


@unittest.skipUnless(HAVE_ELFS, "target/built ELFs not present")
class TestRealElfs(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.built = dd.Elf(dd.BUILT_ELF)
        cls.base = dd.Elf(dd.BASE_ELF)

    def test_base_sections_found(self):
        names = {r[0] for r in self.base.progbits_ranges(dd.DATA_SECTIONS)}
        self.assertEqual(names, set(dd.DATA_SECTIONS))

    def test_read_vma_bounds(self):
        # .data starts at 0x274700 in the target
        (nm, start, end, _), = [r for r in
                                self.base.progbits_ranges((".data",))]
        self.assertEqual(start, 0x274700)
        self.assertIsNotNone(self.base.read_vma(start, 16))
        self.assertIsNone(self.base.read_vma(end - 8, 16))   # crosses the end

    def test_built_symtab_nonempty(self):
        self.assertGreater(len(self.built.symbols()), 1000)

    def test_data_symbols_all_in_data_sections(self):
        syms = dd.data_symbols(self.built, self.base)
        self.assertGreater(len(syms), 100)
        secs = {s[3] for s in syms}
        self.assertTrue(secs <= set(dd.DATA_SECTIONS))

    def test_vtable_json_tables_match_target(self):
        # the recorded vtable entries decode identically from the TARGET
        # bytes — vtables.json was derived from it
        import json
        import struct
        tables = json.loads(dd.VTABLES_JSON.read_text())
        t = tables[0]
        raw = self.base.read_vma(t["vma_start"],
                                 t["vma_end"] - t["vma_start"])
        got = [struct.unpack_from("<I", raw, i)[0]
               for i in range(0, len(raw), 4)]
        self.assertEqual(got, t["entries"])

    def test_corrupted_byte_is_localized(self):
        # flip one byte inside a known symbol region in an in-memory copy
        import copy
        built2 = copy.copy(self.built)
        syms = dd.effective_sizes(dd.data_symbols(self.built, self.base))
        nm, vma, size, sec = next(s for s in syms if s[2] >= 8)
        d = bytearray(built2.data)
        for snm, start, end, off in built2.progbits_ranges():
            if start <= vma < end:
                d[off + (vma - start) + 1] ^= 0x5A
                break
        built2.data = bytes(d)
        rows = [r for r in dd.compare_symbols(built2, self.base, name_filter=nm)
                if r["result"] != "MATCH"]
        self.assertTrue(any(r["symbol"] == nm and
                            r["first_diff_offset"] == 1 for r in rows))


if __name__ == "__main__":
    unittest.main()
