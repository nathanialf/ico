#!/usr/bin/env python3
"""
tools/data_diff.py — per-symbol byte oracle for global data and vtables.

Adapted from the LEGO Island decomp toolchain (isledecomp/reccmp,
reccmp/tools/datacmp.py and reccmp/tools/vtable.py): automated per-symbol
comparison of every global-data symbol (and every recorded function-pointer
table) between the rebuilt ELF and the target ELF. reccmp compares typed
values via PDB debug info toward an accuracy %; we are byte-exact with a
stripped target, so the comparison is raw bytes at the symbol's VMA, sized by
the built ELF's own symbol table.

Why it exists: `ninja` ends in a whole-file SHA-1 (tools/verify_elf.py) that
says ONLY "the bytes diverged". When a data carve regresses, this names WHICH
symbol diverged and at what offset — the same localization the per-function
asm diff gives .text, extended to .data/.rodata/.lit4/.sdata. Data carves were
previously verified by hand against decomp/carve_ledger.md; this is the
mechanical check. NOBITS sections (.bss/.sbss) carry no bytes and are skipped
(their layout is already covered by the link + SHA gate).

Vtable mode (--vtables): decomp/vtables.json records every function-pointer
table found in .data (vma range + the function VMAs it holds). For each table,
compare built vs target bytes over the range AND decode the built entries,
checking them against the recorded function VMAs — a wrong-but-linkable
function address in a carved table is exactly the class the whole-file hash
can only report as "mismatch somewhere".

Usage:
    tools/data_diff.py                     # all data symbols, print problems
    tools/data_diff.py --all               # print matches too
    tools/data_diff.py D_00631AE8          # filter by substring
    tools/data_diff.py --section .rodata   # one section only
    tools/data_diff.py --vtables           # vtable oracle (decomp/vtables.json)
    tools/data_diff.py --json ...          # machine-readable
Options --built/--base override the ELF paths (defaults: build/ico.elf,
baserom/baseelf.elf).
Exit: 0 = everything compared matches, 1 = diffs found, 2 = missing inputs.
"""
from __future__ import annotations
import argparse
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BUILT_ELF = ROOT / "build" / "ico.elf"
BASE_ELF = ROOT / "baserom" / "baseelf.elf"
VTABLES_JSON = ROOT / "decomp" / "vtables.json"

# Target data sections that carry bytes (PROGBITS). NOBITS (.bss/.sbss) has
# nothing to compare; .text/.vutext are the asm diff's domain.
DATA_SECTIONS = (".data", ".rodata", ".lit4", ".sdata")

SHT_PROGBITS = 1
SHT_SYMTAB = 2
STT_FUNC = 2
STT_SECTION = 3
STT_FILE = 4


class Elf:
    """Minimal 32-bit LE ELF reader: sections, symbols, bytes-at-VMA."""

    def __init__(self, path: Path):
        self.path = path
        self.data = path.read_bytes()
        d = self.data
        e_shoff = struct.unpack_from("<I", d, 0x20)[0]
        e_shentsize = struct.unpack_from("<H", d, 0x2E)[0]
        e_shnum = struct.unpack_from("<H", d, 0x30)[0]
        e_shstrndx = struct.unpack_from("<H", d, 0x32)[0]
        raw = [struct.unpack_from("<10I", d, e_shoff + i * e_shentsize)
               for i in range(e_shnum)]
        shstr = raw[e_shstrndx]
        strtab = d[shstr[4]:shstr[4] + shstr[5]]

        def name(off):
            return strtab[off:strtab.index(b"\0", off)].decode()

        # (name, type, vma, offset, size)
        self.sections = [(name(sh[0]), sh[1], sh[3], sh[4], sh[5])
                         for sh in raw]
        self._raw = raw

    def progbits_ranges(self, names=None):
        """[(name, vma_start, vma_end, file_off)] for PROGBITS sections."""
        out = []
        for nm, typ, vma, off, size in self.sections:
            if typ != SHT_PROGBITS or size == 0:
                continue
            if names is not None and nm not in names:
                continue
            out.append((nm, vma, vma + size, off))
        return out

    def read_vma(self, vma: int, size: int) -> bytes | None:
        """Bytes at [vma, vma+size) from whichever PROGBITS section holds it,
        or None if unmapped / crosses a section end."""
        for _, start, end, off in self.progbits_ranges():
            if start <= vma and vma + size <= end:
                fo = off + (vma - start)
                return self.data[fo:fo + size]
        return None

    def symbols(self):
        """[(name, value, size, type, shndx)] from .symtab (empty if stripped)."""
        symtab = strtab = None
        for i, (nm, typ, _vma, off, size) in enumerate(self.sections):
            if typ == SHT_SYMTAB:
                symtab = (off, size)
                link = self._raw[i][6]
                soff, ssize = self._raw[link][4], self._raw[link][5]
                strtab = self.data[soff:soff + ssize]
        if symtab is None:
            return []
        out = []
        off, size = symtab
        for p in range(off, off + size, 16):
            st_name, st_value, st_size = struct.unpack_from("<III", self.data, p)
            st_info = self.data[p + 12]
            st_shndx = struct.unpack_from("<H", self.data, p + 14)[0]
            nm = strtab[st_name:strtab.index(b"\0", st_name)].decode(
                "utf-8", "replace")
            out.append((nm, st_value, st_size, st_info & 0xF, st_shndx))
        return out


def data_symbols(built: Elf, base: Elf):
    """Data symbols to compare: named non-FUNC symbols from the BUILT ELF whose
    VMA falls inside one of the TARGET's byte-carrying data sections. Sorted by
    VMA; zero-size symbols get the gap to the next symbol (or section end)."""
    ranges = base.progbits_ranges(DATA_SECTIONS)
    def section_of(vma):
        for nm, start, end, _ in ranges:
            if start <= vma < end:
                return nm, end
        return None, None
    syms = []
    for nm, val, size, typ, shndx in built.symbols():
        if typ in (STT_FUNC, STT_SECTION, STT_FILE):
            continue
        if shndx == 0 or not nm or nm.startswith((".", "$", "_gp")):
            continue
        sec, sec_end = section_of(val)
        if sec is None:
            continue
        syms.append([nm, val, size, sec, sec_end])
    syms.sort(key=lambda s: (s[1], s[0]))
    return [tuple(s) for s in syms]


def effective_sizes(syms):
    """Resolve each symbol's compare size: st_size when recorded, else the gap
    to the next DISTINCT symbol VMA in the same section (or the section end).
    Pure function of [(name, vma, size, section, section_end)] sorted by vma."""
    out = []
    for i, (nm, vma, size, sec, sec_end) in enumerate(syms):
        if size == 0:
            nxt = next((v for _, v, _, s, _ in syms[i + 1:]
                        if v > vma and s == sec), sec_end)
            size = max(0, nxt - vma)
        # A recorded st_size can extend into the alignment pad past the
        # TARGET section's end (the rebuilt ELF is one flat section, so the
        # pad is inside the symbol there). Bytes past the target section end
        # are not symbol data — clamp (e.g. D_00553690, last .data symbol).
        size = min(size, sec_end - vma)
        out.append((nm, vma, size, sec))
    return out


def compare_symbols(built: Elf, base: Elf, name_filter=None, section=None):
    """Yield per-symbol comparison dicts."""
    syms = effective_sizes(data_symbols(built, base))
    for nm, vma, size, sec in syms:
        if name_filter and name_filter not in nm:
            continue
        if section and sec != section:
            continue
        if size == 0:
            continue
        bb = built.read_vma(vma, size)
        tb = base.read_vma(vma, size)
        if bb is None or tb is None:
            yield {"symbol": nm, "vma": vma, "size": size, "section": sec,
                   "result": "UNMAPPED",
                   "detail": f"built={'ok' if bb else 'missing'} "
                             f"base={'ok' if tb else 'missing'}"}
            continue
        if bb == tb:
            yield {"symbol": nm, "vma": vma, "size": size, "section": sec,
                   "result": "MATCH"}
            continue
        first = next(i for i in range(size) if bb[i] != tb[i])
        ndiff = sum(1 for i in range(size) if bb[i] != tb[i])
        lo = max(0, first - 4) & ~3
        hi = min(size, first + 12)
        yield {"symbol": nm, "vma": vma, "size": size, "section": sec,
               "result": "DIFF", "first_diff_offset": first,
               "bytes_differing": ndiff,
               "expected": tb[lo:hi].hex(), "built": bb[lo:hi].hex(),
               "excerpt_offset": lo}


def compare_gaps(built: Elf, base: Elf, section=None):
    """Compare the bytes NO symbol owns (holes between symbol intervals —
    e.g. rodata still inside an asm blob, where the built symtab has only
    zero-size markers). Without this, a divergence there is invisible to the
    per-symbol pass and only the whole-file SHA would catch it — with no
    localization. Yields one row per differing gap."""
    intervals = {}
    for nm, vma, size, sec in effective_sizes(data_symbols(built, base)):
        intervals.setdefault(sec, []).append((vma, vma + size))
    for sec, start, end, _ in base.progbits_ranges(DATA_SECTIONS):
        if section and sec != section:
            continue
        covered = sorted(intervals.get(sec, []))
        pos = start
        gaps = []
        for s, e in covered:
            if s > pos:
                gaps.append((pos, s))
            pos = max(pos, e)
        if pos < end:
            gaps.append((pos, end))
        for gs, ge in gaps:
            bb = built.read_vma(gs, ge - gs)
            tb = base.read_vma(gs, ge - gs)
            if bb is None or tb is None or bb == tb:
                continue
            first = next(i for i in range(ge - gs) if bb[i] != tb[i])
            ndiff = sum(1 for i in range(ge - gs) if bb[i] != tb[i])
            lo = max(0, first - 4) & ~3
            hi = min(ge - gs, first + 12)
            yield {"symbol": f"(gap 0x{gs:06x}..0x{ge:06x})", "vma": gs,
                   "size": ge - gs, "section": sec, "result": "DIFF",
                   "first_diff_offset": first, "bytes_differing": ndiff,
                   "expected": tb[lo:hi].hex(), "built": bb[lo:hi].hex(),
                   "excerpt_offset": lo}


def compare_vtables(built: Elf, base: Elf, tables):
    """Per-table oracle: raw byte equality over the range, plus a decode of
    the built entries against the recorded function VMAs."""
    func_names = {}
    for nm, val, _sz, typ, shndx in built.symbols():
        if typ == STT_FUNC and shndx != 0:
            func_names.setdefault(val, nm)
    for t in tables:
        vs, ve = t["vma_start"], t["vma_end"]
        size = ve - vs
        bb = built.read_vma(vs, size)
        tb = base.read_vma(vs, size)
        row = {"vma_start": vs, "vma_end": ve, "section": t["section"],
               "count": t["count"]}
        if bb is None or tb is None:
            row["result"] = "UNMAPPED"
            yield row
            continue
        entries_built = [struct.unpack_from("<I", bb, i)[0]
                         for i in range(0, size, 4)]
        expected_entries = t["entries"]
        bad = [
            {"index": i, "expected_vma": exp, "built_vma": got,
             "expected_func": func_names.get(exp, "?"),
             "built_func": func_names.get(got, "?")}
            for i, (exp, got) in enumerate(zip(expected_entries, entries_built))
            if exp != got
        ]
        row["bytes_match"] = bb == tb
        row["entries_bad"] = bad
        row["entry_funcs"] = [func_names.get(e, f"0x{e:06x}")
                              for e in entries_built]
        row["result"] = "MATCH" if (bb == tb and not bad) else "DIFF"
        yield row


def main() -> int:
    ap = argparse.ArgumentParser(description="per-symbol data/vtable byte "
                                             "oracle (reccmp datacmp/vtable port)")
    ap.add_argument("filter", nargs="?", default=None,
                    help="symbol-name substring filter")
    ap.add_argument("--section", default=None, choices=DATA_SECTIONS,
                    help="restrict to one target section")
    ap.add_argument("--all", action="store_true",
                    help="print MATCH rows too (default: problems only)")
    ap.add_argument("--vtables", action="store_true",
                    help="compare the decomp/vtables.json function-pointer "
                         "tables instead of data symbols")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--built", type=Path, default=BUILT_ELF)
    ap.add_argument("--base", type=Path, default=BASE_ELF)
    args = ap.parse_args()

    for p in (args.built, args.base):
        if not p.exists():
            print(f"data_diff: missing {p} (run ninja / extract_elf.sh first)",
                  file=sys.stderr)
            return 2
    built, base = Elf(args.built), Elf(args.base)

    problems = total = 0
    rows = []
    if args.vtables:
        if not VTABLES_JSON.exists():
            print(f"data_diff: missing {VTABLES_JSON}", file=sys.stderr)
            return 2
        tables = json.loads(VTABLES_JSON.read_text())
        for row in compare_vtables(built, base, tables):
            total += 1
            ok = row["result"] == "MATCH"
            problems += 0 if ok else 1
            if args.json:
                if not ok or args.all:
                    rows.append(row)
            elif not ok or args.all:
                print(f"vtable 0x{row['vma_start']:06x}..0x{row['vma_end']:06x} "
                      f"({row['count']} entries) ... {row['result']}")
                if args.all and ok:
                    for i, fn in enumerate(row.get("entry_funcs", [])):
                        print(f"    [{i}] {fn}")
                for b in row.get("entries_bad", []):
                    print(f"    [{b['index']}] expected 0x{b['expected_vma']:06x} "
                          f"{b['expected_func']} != built 0x{b['built_vma']:06x} "
                          f"{b['built_func']}")
        label = "Vtables"
    else:
        import itertools
        gap_rows = (compare_gaps(built, base, args.section)
                    if not args.filter else iter(()))
        for row in itertools.chain(
                compare_symbols(built, base, args.filter, args.section),
                gap_rows):
            total += 1
            ok = row["result"] == "MATCH"
            problems += 0 if ok else 1
            if args.json:
                if not ok or args.all:
                    rows.append(row)
            elif not ok or args.all:
                line = (f"{row['symbol']:<32} 0x{row['vma']:06x} "
                        f"{row['section']:<8} size={row['size']:<6} "
                        f"{row['result']}")
                print(line)
                if row["result"] == "DIFF":
                    print(f"    first diff at +0x{row['first_diff_offset']:x} "
                          f"({row['bytes_differing']} bytes differ)")
                    print(f"    expected@+0x{row['excerpt_offset']:x}: "
                          f"{row['expected']}")
                    print(f"    built   @+0x{row['excerpt_offset']:x}: "
                          f"{row['built']}")
        label = "Data symbols"
    if args.json:
        print(json.dumps({"total": total, "problems": problems,
                          "rows": rows}, indent=2))
    else:
        print(f"{label}: {total}. Issues: {problems}.")
    return 0 if problems == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
