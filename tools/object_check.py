#!/usr/bin/env python3
"""object_check.py: each object's .text against the target, and a TU's emission order.

Two measurements a target campaign makes after a link, or after a link that
fails.

Objects (the default). For each object of the link with a .text, its words
are compared with the target ELF's words at the object's address, the fields
the object's own .text relocations fill masked on both sides and no other
field, as tools/match_check.py masks one function (R_MIPS_26 keeps the
opcode of a j or jal; R_MIPS_HI16, R_MIPS_LO16, R_MIPS_GPREL16 and
R_MIPS_LITERAL keep the upper half; tools/correlate_elf.py's RELOC_KIND). A
relocation of another kind in .text masks its whole word and is counted.
The object's address is its .text row in the link map
(build/<slug>/ico.<slug>.map, tools/check_elf.py's parse_map). When the real link
failed and wrote no map, the layout link build/<slug>/ico.layout.elf (the same
objects with a zero stand-in for each data member, tools/gen_ninja.py) gives
it: the objects of config/link_order.<slug>.txt in order, each placed by a
function symbol it defines whose name is unique in that ELF (a global first),
the offset of the symbol in the object taken off (an object no such symbol
places follows the one before it at its alignment). Each object prints `equal`,
or the first differing word, with the function around it and both words
disassembled; a stub (INCLUDE_ASM) carries the base's words and compares
equal at its own address whatever the C around it does, so an object that
differs differs in its C or in a stub's place.

Order (--order [TU...]). gcc writes a TU's functions in definition order,
then the inline functions it must emit after the whole file is read (and a
stub of an inline function stands at the end of the file, before every
inline function still in C). The functions of each TU's object (build/<slug>/<tu>.o,
or the TU compiled into a scratch object when there is none, --compile to
always compile) are read in their order in the object, and each is given
its target address: a --twins row (tools/correlate_elf.py's twins.txt, the
function's target_vma), else its text row in config/stubs.<slug>.txt
(vma_lo), else its symbol in the last link (build/<slug>/ico.syms.elf), which is
the target's only once the gate passes. The target addresses must rise in
object order. A function placed before others the target emits earlier is
named with them; when it is a stub (its INCLUDE_ASM line stands in its
file), the line is out of place, and for an inline function's stub at the
end of the file the functions named are inline functions the target emits
before it, still in C, which are carved too.

On main the stub list is empty and the target is the PAL base: --self-test
runs both over every object against build/<slug>/ico.syms.elf (the last link,
whose symbols also give the order its addresses), and every object compares
equal and every TU's order rises.

  tools/object_check.py                      every object of the map
  tools/object_check.py ico2/x/y.c ...       those TUs' objects (a path or an object)
  tools/object_check.py --layout             objects placed from build/<slug>/ico.layout.elf
  tools/object_check.py --order [TU ...] [--twins FILE] [--compile]
  tools/object_check.py --self-test
Options: --elf ELF (the target, default the detected target's base ELF), -v (print the
equal objects too). Exit 0 when every object compared is equal and every
order rises.
"""

from __future__ import annotations

import argparse
import struct
import sys
import tempfile
from pathlib import Path

try:
    from elftools.elf.elffile import ELFFile
    from elftools.elf.relocation import RelocationSection
    from elftools.elf.sections import SymbolTableSection
except ImportError:
    sys.exit("object_check.py: missing pyelftools. Run "
             "`.venv/bin/pip install -r tools/requirements.txt`.")

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from check_elf import parse_map  # noqa: E402
from correlate_elf import RELOC_KIND, describe_reloc  # noqa: E402
from gen_stub_s import LIST, asm_line, parse_stubs  # noqa: E402
from ico_version import baseelf_path, build_dir, detect_version, link_map_path  # noqa: E402
from match_check import KEEP, build_symbols, compile_tu, disasm, read_twins  # noqa: E402

VERSION = detect_version(ROOT)
TARGET = baseelf_path(ROOT, VERSION)
OUT = build_dir(ROOT, VERSION)
OUT_REL = OUT.relative_to(ROOT).as_posix()
SYMS = OUT / "ico.syms.elf"
LAYOUT = OUT / "ico.layout.elf"
MAP = link_map_path(ROOT, VERSION)


def fail(msg):
    sys.exit(f"object_check: {msg}")


def rel(p: Path) -> str:
    return str(p.relative_to(ROOT)) if p.is_relative_to(ROOT) else str(p)


# ------------------------------------------------------------- object ----

class Obj:
    """An object's .text: its words, the bits each word keeps once its
    relocated field is masked, and its function symbols (offset order)."""

    def __init__(self, path: Path):
        self.path = path
        with path.open("rb") as fh:
            elf = ELFFile(fh)
            secs = list(elf.iter_sections())
            tidx = next((i for i, s in enumerate(secs) if s.name == ".text"), None)
            data = secs[tidx].data() if tidx is not None else b""
            self.align = secs[tidx]["sh_addralign"] if tidx is not None else 1
            n = len(data) // 4
            self.words = list(struct.unpack("<%dI" % n, data[:4 * n]))
            self.keep = {}
            self.other = 0
            symtab = next((s for s in secs if isinstance(s, SymbolTableSection)), None)
            self.funcs = []
            if symtab is not None and tidx is not None:
                self.funcs = sorted((s["st_value"], s.name, s["st_info"]["bind"]) for s in symtab.iter_symbols()
                                    if s["st_info"]["type"] == "STT_FUNC" and s["st_shndx"] == tidx and s.name)
            for rs in secs:
                if not isinstance(rs, RelocationSection) or tidx is None or rs["sh_info"] != tidx:
                    continue
                for r in rs.iter_relocations():
                    kind = RELOC_KIND.get(describe_reloc(elf, r["r_info_type"]))
                    if kind is None:
                        self.other += 1
                    self.keep[r["r_offset"] // 4] = KEEP.get(kind, 0)

    def func_at(self, off):
        """(name, offset in it) of the function holding byte offset off."""
        best = None
        for v, name, _ in self.funcs:
            if v <= off:
                best = (name, off - v)
        return best


class Target:
    """The target ELF's allocated PROGBITS sections, read by address."""

    def __init__(self, path: Path):
        self.path = path
        self.secs = []
        with path.open("rb") as fh:
            for s in ELFFile(fh).iter_sections():
                if s["sh_type"] == "SHT_PROGBITS" and s["sh_flags"] & 2:
                    self.secs.append((s["sh_addr"], s.data()))

    def words(self, lo, n):
        for base, data in self.secs:
            if base <= lo and lo + 4 * n <= base + len(data):
                return list(struct.unpack("<%dI" % n, data[lo - base:lo - base + 4 * n]))
        return None


def symbols(path: Path):
    """{name: [values]} of an ELF's function symbols."""
    out = {}
    with path.open("rb") as fh:
        tab = ELFFile(fh).get_section_by_name(".symtab")
        if not isinstance(tab, SymbolTableSection):
            fail(f"{rel(path)} has no symbol table")
        for s in tab.iter_symbols():
            if s["st_info"]["type"] == "STT_FUNC" and s.name:
                out.setdefault(s.name, []).append(s["st_value"])
    return out


# ------------------------------------------------------------ placing ----

def from_map(map_path: Path):
    """[(object path, address, size)] of the map's .text rows, in address order."""
    return [(r["obj"], r["addr"], r["size"]) for r in parse_map(map_path)
            if r["sect"] == ".text" and r["obj"] and r["obj"].endswith(".o")]


def from_layout(layout: Path):
    """[(object path, address, size)] of the link order's objects, each placed
    in the layout link by a function symbol of a name unique there; one no
    symbol places (an assembler source whose labels recur) follows the one
    before it, at its .text alignment, when it fits before the next; else
    its address is None."""
    from gen_ninja import objects, parse_list
    syms = symbols(layout)
    out = []
    for e in parse_list():
        for o in objects(e, layout=True):
            p = ROOT / o
            if not p.exists():
                out.append([o, None, 0, 1])
                continue
            obj = Obj(p)
            if not obj.words:
                continue
            # a global first: a static's name may recur in other objects
            cand = sorted(obj.funcs, key=lambda f: f[2] != "STB_GLOBAL")
            at = next((syms[n][0] - v for v, n, _ in cand if len(syms.get(n, [])) == 1), None)
            out.append([o, at, 4 * len(obj.words), obj.align])
    for i, x in enumerate(out):
        if x[1] is None and x[2] and i and out[i - 1][1] is not None:
            a = -(-(out[i - 1][1] + out[i - 1][2]) // x[3]) * x[3]
            nxt = next((y[1] for y in out[i + 1:] if y[1] is not None), None)
            if nxt is None or a + x[2] <= nxt:
                x[1] = a
    return [(o, at, size) for o, at, size, _ in out]


# ------------------------------------------------------------ objects ----

def check_objects(placed, target: Target, verbose: bool):
    """Each object's words against the target's at its address; the counts."""
    equal = differ = unplaced = 0
    for o, at, size in placed:
        p = ROOT / o
        if at is None or not p.exists():
            print(f"object_check: {o}: {'no object' if not p.exists() else 'not placed (no unique symbol)'}")
            unplaced += 1
            continue
        obj = Obj(p)
        n = len(obj.words)
        if 4 * n != size:
            print(f"object_check: {o} 0x{at:08X}: the object's .text is 0x{4 * n:X} bytes, its place 0x{size:X}")
            differ += 1
            continue
        tw = target.words(at, n)
        if tw is None:
            print(f"object_check: {o} 0x{at:08X}: outside the target's sections")
            differ += 1
            continue
        k = next((i for i in range(n) if (obj.words[i] ^ tw[i]) & obj.keep.get(i, 0xFFFFFFFF)), None)
        if k is None:
            equal += 1
            if verbose:
                print(f"object_check: {o} 0x{at:08X} +0x{4 * n:X}: equal ({n} words,"
                      f" {len(obj.keep)} relocated fields masked"
                      + (f", {obj.other} of another kind, whole word" if obj.other else "") + ")")
            continue
        differ += 1
        fn = obj.func_at(4 * k)
        where = f"{fn[0]}+0x{fn[1]:X}" if fn else f"+0x{4 * k:X}"
        print(f"object_check: {o} 0x{at:08X}: differs at 0x{at + 4 * k:08X} ({where}),"
              f" {sum(1 for i in range(n) if (obj.words[i] ^ tw[i]) & obj.keep.get(i, 0xFFFFFFFF))} of {n}"
              " words differ")
        print(f"    object: {disasm([obj.words[k]], at + 4 * k)[0].strip()}")
        print(f"    target: {disasm([tw[k]], at + 4 * k)[0].strip()}")
    print(f"object_check: {equal + differ + unplaced} objects with .text: {equal} equal, {differ} differ,"
          f" {unplaced} not placed; against {rel(target.path)}")
    return differ + unplaced


# -------------------------------------------------------------- order ----

def tus_of(placed):
    """The C sources of the placed objects, in link order."""
    out = []
    for o, _, _ in placed:
        src = Path(o).relative_to(OUT_REL).with_suffix(".c")
        if (ROOT / src).exists() and str(src) not in out:
            out.append(str(src))
    return out


def object_of(tu: str, fresh: bool, tmp: Path):
    o = OUT / Path(tu).with_suffix(".o")
    return Obj(o if o.exists() and not fresh else compile_tu(tu, tmp))


def check_order(tus, rows, twins, use_link, fresh: bool, verbose: bool):
    """Each TU's functions in object order against their target addresses
    (use_link: the last link's symbols inside the TU's .text by the map,
    for a function with no twin and no row); the number of TUs whose order
    does not rise or that have a function with no address."""
    bad = none = 0
    by_tu = {}
    for r in rows:
        if r["section"] == "text":
            by_tu.setdefault(r["tu"], []).append(r)
    with tempfile.TemporaryDirectory(prefix="object_check.") as tmp:
        for tu in tus:
            obj = object_of(tu, fresh, Path(tmp))
            mine = {r["name"]: r for r in by_tu.get(tu, [])}
            built = build_symbols(tu) if use_link else {}
            seq, missing = [], []
            for v, name, _ in obj.funcs:
                t = twins.get(name)
                if t and len(t) == 1:
                    seq.append((name, t[0][0], "twin"))
                elif name in mine:
                    seq.append((name, mine[name]["lo"], "row"))
                elif name in built:
                    seq.append((name, built[name][0], "link"))
                else:
                    missing.append(name)
            stub = set()
            for name, r in mine.items():
                if asm_line(r["stem"]) in (ROOT / r["asm"]).read_bytes().splitlines(keepends=True):
                    stub.add(name)
            out = []
            for i, (name, t, how) in enumerate(seq):
                early = [(n2, t2) for n2, t2, _ in seq[i + 1:] if t2 < t]
                if not early:
                    continue
                what = "stub" if name in stub else "C"
                names = ", ".join(f"{n2} 0x{t2:08X}" for n2, t2 in early[:8]) + (" ..." if len(early) > 8 else "")
                line = (f"    {name} ({what}, target 0x{t:08X} by {how}) is placed before {len(early)} the target"
                        f" emits earlier: {names}")
                if name in stub:
                    line += ("; its INCLUDE_ASM line is out of place (an inline function's stub at the end of the"
                             " file comes before every inline function still in C: carve those the target emits"
                             " before it)")
                out.append(line)
            if out:
                bad += 1
                print(f"object_check: {tu}: order differs ({len(seq)} functions placed)")
                print("\n".join(out))
            elif verbose:
                print(f"object_check: {tu}: order rises ({len(seq)} functions placed)")
            if missing:
                none += 1
                print(f"object_check: {tu}: no target address for {', '.join(missing)}"
                      " (no unique twin, row or symbol in the last link)")
    print(f"object_check: {len(tus)} TUs: {len(tus) - bad} in the target's order, {bad} out of it,"
          f" {none} with functions not placed")
    return bad + none


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("tus", nargs="*", metavar="TU", help="C sources or objects (default every one)")
    ap.add_argument("--elf", type=Path, default=TARGET, help=f"the target ELF (default {rel(TARGET)})")
    ap.add_argument("--layout", action="store_true", help=f"place the objects from {rel(LAYOUT)}")
    ap.add_argument("--order", action="store_true", help="the TUs' emission order against the target")
    ap.add_argument("--twins", type=Path, metavar="FILE", help="a correlate_elf.py twins.txt (--order)")
    ap.add_argument("--compile", action="store_true", help="--order compiles each TU into a scratch object")
    ap.add_argument("--stubs", type=Path, default=LIST, help=f"the stub list (default {rel(LIST)})")
    ap.add_argument("--self-test", action="store_true",
                    help=f"both checks on every object against {rel(SYMS)}")
    ap.add_argument("-v", "--verbose", action="store_true", help="print the equal objects and rising TUs too")
    a = ap.parse_args()
    if a.self_test:
        if not SYMS.exists() or not MAP.exists():
            fail(f"{rel(SYMS)} or {rel(MAP)} is missing: build first")
        placed = from_map(MAP)
        rc = check_objects(placed, Target(SYMS), a.verbose)
        rc += check_order(tus_of(placed), [], {}, True, False, a.verbose)
        print(f"object_check: self-test {'PASS' if not rc else 'FAIL'}")
        return 1 if rc else 0
    if a.layout or not MAP.exists():
        if not LAYOUT.exists():
            fail(f"no {rel(MAP)} and no {rel(LAYOUT)}: build first")
        print(f"object_check: objects placed from {rel(LAYOUT)}"
              + ("" if a.layout else f" ({rel(MAP)} is missing)"))
        placed = from_layout(LAYOUT)
    else:
        placed = from_map(MAP)
    if a.tus:
        want = {f"{OUT_REL}/{Path(t).with_suffix('.o')}" if t.endswith(".c") else t for t in a.tus}
        placed = [p for p in placed if p[0] in want]
        if not placed:
            fail("none of the named TUs has an object with .text in the link")
    if a.order:
        rows = parse_stubs(a.stubs)
        twins = read_twins(a.twins) if a.twins else {}
        # the last link's addresses are the target's only for the detected target's own base
        use_link = SYMS.exists() and MAP.exists() and a.elf.resolve() == TARGET.resolve()
        return 1 if check_order(tus_of(placed), rows, twins, use_link, a.compile, a.verbose) else 0
    return 1 if check_objects(placed, Target(a.elf), a.verbose) else 0


if __name__ == "__main__":
    raise SystemExit(main())
