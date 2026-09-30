#!/usr/bin/env python3
"""check_elf.py: compare the built ELF with the base ELF by address, and
derive progress from that comparison and the link map.

  --gate      For every allocated PROGBITS section of the base ELF (.text
              .vutext .data .rodata .lit4 .sdata; a zero-sized one such as
              .vudata is listed and trivially passes) the built ELF must hold
              the same bytes at the same addresses. The built ELF's section
              names do not matter (today everything sits inside `.cod`), only
              addresses. For the NOBITS sections (.sbss .bss) the built ELF
              must allocate the base's address range; the share of it owned
              by an object outside build/asm/ is reported. Then the ROM SHA-1
              against config/sha1sums.txt (gated) and the ELF SHA-1 (reported,
              gated only with --require-elf-sha). A second, informational
              table compares .reginfo, the .DVP.* sections, e_flags, e_entry,
              program and section headers. Exit 0 only when every gated
              check passes.

  --progress  Rewrite README.md's badge block, docs/PROGRESS.md's table and
              docs/progress.json (schema 2) from the same comparison. A byte
              counts for its section when the map row that places it belongs
              to an object under build/ico2/ or build/sce/ AND the byte equals
              the base's (NOBITS: ownership only, there is nothing to
              compare). `*fill*` rows are credited to the input section that
              follows them, since it is that section's alignment that the
              linker padded for. Objects under build/data/ (extracted data
              tables, none today) are counted separately as `extracted`.

  --full-diff The whole file, built vs base, for the ELF-identity work: ELF
              header fields side by side, program headers, section headers
              in file order (name type flags addr offset size align entsize),
              the .shstrtab strings in file order, the .reginfo words, the
              .DVP.ovlytab rows and .DVP.ovlystrtab names, and for every
              section name present in both whether the bytes are equal. It
              reports; it gates nothing and needs no map.

Inputs: build/ico.elf, build/ico.<ver>.map (written by the link, see
tools/gen_ninja.py emit_link), the base ELF and config/sha1sums.txt.
"""

from __future__ import annotations

import argparse
import bisect
import hashlib
import json
import re
import sys
from pathlib import Path

try:
    from elftools.elf.elffile import ELFFile
except ImportError:
    sys.exit("check_elf.py: missing pyelftools. Run "
             "`.venv/bin/pip install -r tools/requirements.txt`.")

REPO_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
from ico_version import detect_version, baseelf_path  # noqa: E402

VERSION = detect_version(REPO_ROOT)
BASE_ELF = baseelf_path(REPO_ROOT, VERSION)
BUILT_ELF = REPO_ROOT / "build" / "ico.elf"
BUILT_ROM = REPO_ROOT / "build" / "ico.rom"
LINK_MAP = REPO_ROOT / "build" / f"ico.{VERSION}.map"
SHA1SUMS = REPO_ROOT / "config" / "sha1sums.txt"
README = REPO_ROOT / "README.md"
PROGRESS_DOC = REPO_ROOT / "docs" / "PROGRESS.md"
PROGRESS_JSON = REPO_ROOT / "docs" / "progress.json"

NOBITS = (".sbss", ".bss")
# Badge / table order: ELF link order, as progress.py has it.
REPORT_ORDER = [".text", ".vutext", ".data", ".vudata", ".rodata",
                ".lit4", ".sdata", ".sbss", ".bss"]
OWNED_ROOTS = ("build/ico2/", "build/sce/")
EXTRACTED_ROOT = "build/data/"
BLOB_ROOT = "build/asm/"
VUTEXT_GROUP = ".vutext"
VUTEXT_NOTE = (
    "VU1 microprograms in the .vutext ELF section — hand-typed src/*.S, "
    "assembled byte-identically. Counted separately from .text so the "
    "headline .text figure is not inflated."
)


# ----- inputs ----------------------------------------------------------

class Elf:
    """The parts of an ELF this tool reads, loaded once."""

    def __init__(self, path: Path):
        self.path = path
        raw = path.read_bytes()
        self.raw = raw
        self.sha1 = hashlib.sha1(raw).hexdigest()
        with path.open("rb") as f:
            elf = ELFFile(f)
            self.header = dict(elf.header)
            self.e_flags = elf.header["e_flags"]
            self.e_entry = elf.header["e_entry"]
            self.phdrs = [dict(seg.header) for seg in elf.iter_segments()]
            self.sections = []
            for sec in elf.iter_sections():
                h = sec.header
                flags = h["sh_flags"]
                nobits = h["sh_type"] == "SHT_NOBITS"
                data = b"" if nobits else sec.data()
                self.sections.append({
                    "name": sec.name, "type": h["sh_type"], "addr": h["sh_addr"],
                    "size": h["sh_size"], "offset": h["sh_offset"],
                    "flags": flags, "alloc": bool(flags & 2),
                    "nobits": nobits, "data": data,
                })
            self.funcs = []
            symtab = elf.get_section_by_name(".symtab")
            if symtab is not None:
                for sym in symtab.iter_symbols():
                    if sym["st_info"]["type"] != "STT_FUNC":
                        continue
                    if not isinstance(sym["st_shndx"], int):
                        continue       # SHN_ABS: a script-defined address
                    self.funcs.append((sym["st_value"], sym["st_size"], sym.name))
        self.funcs.sort()
        self._progbits = sorted(
            (s for s in self.sections if s["alloc"] and not s["nobits"] and s["size"]),
            key=lambda s: s["addr"])
        self._alloc = sorted(
            (s for s in self.sections if s["alloc"] and s["size"]),
            key=lambda s: s["addr"])

    def section(self, name: str):
        for s in self.sections:
            if s["name"] == name:
                return s
        return None

    def image(self, lo: int, size: int) -> tuple[bytearray, bytearray]:
        """(bytes, covered) for [lo, lo+size) from the allocated PROGBITS
        sections, whatever their names. covered[i] is 1 where some section
        supplies byte i."""
        buf = bytearray(size)
        cov = bytearray(size)
        hi = lo + size
        for s in self._progbits:
            a, b = s["addr"], s["addr"] + s["size"]
            if b <= lo or a >= hi:
                continue
            x, y = max(a, lo), min(b, hi)
            buf[x - lo:y - lo] = s["data"][x - a:y - a]
            cov[x - lo:y - lo] = b"\x01" * (y - x)
        return buf, cov

    def allocated(self, lo: int, size: int) -> int:
        """Bytes of [lo, lo+size) that some allocated section (NOBITS or
        not) covers."""
        hi = lo + size
        spans = sorted((max(s["addr"], lo), min(s["addr"] + s["size"], hi))
                       for s in self._alloc
                       if s["addr"] < hi and s["addr"] + s["size"] > lo)
        total, cur = 0, lo
        for a, b in spans:
            a = max(a, cur)
            if b > a:
                total += b - a
                cur = b
        return total


_ROW_RE = re.compile(r"^ (\S+)\s+0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)(?:\s+(\S.*?))?\s*$")
_WRAPPED_NAME_RE = re.compile(r"^ (\S+)$")
_WRAPPED_REST_RE = re.compile(r"^\s{2,}0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)(?:\s+(\S.*?))?\s*$")


def parse_map(path: Path) -> list[dict]:
    """Input-section rows of the link map's memory-map part:
    [{sect, addr, size, obj}], `*fill*` rows with obj None, sorted by
    address. The "Discarded input sections" part and /DISCARD/ are skipped;
    rows of size 0 are dropped. ld wraps a row whose section name is too
    long onto two lines; both forms are read."""
    rows = []
    in_map = False
    pending = None
    for line in path.read_text(errors="replace").splitlines():
        if line.startswith("Linker script and memory map"):
            in_map = True
            continue
        if not in_map:
            continue
        if line.startswith("/DISCARD/"):
            break
        if pending is not None:
            m = _WRAPPED_REST_RE.match(line)
            name, pending = pending, None
            if m:
                rows.append((name, int(m.group(1), 16), int(m.group(2), 16), m.group(3)))
                continue
        m = _ROW_RE.match(line)
        if m:
            rows.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16), m.group(4)))
            continue
        m = _WRAPPED_NAME_RE.match(line)
        if m and "(" not in line:
            pending = m.group(1)
    out = []
    for sect, addr, size, obj in rows:
        if not size or sect in ("FILL", "LOAD", "OUTPUT"):
            continue
        if sect == "*fill*":
            out.append({"sect": sect, "addr": addr, "size": size, "obj": None})
        elif obj and (obj.endswith(".o") or ".a(" in obj):
            out.append({"sect": sect, "addr": addr, "size": size, "obj": obj})
    out.sort(key=lambda r: (r["addr"], r["obj"] is not None))
    # Credit each *fill* to the input section that follows it: the pad
    # exists because that section asked for alignment.
    for i, r in enumerate(out):
        if r["obj"] is None:
            nxt = next((q for q in out[i + 1:] if q["obj"] is not None), None)
            r["fill_for"] = nxt["obj"] if nxt and nxt["addr"] == r["addr"] + r["size"] else None
    return out


def row_owner(r: dict) -> str | None:
    return r["obj"] if r["obj"] is not None else r.get("fill_for")


def _rel(p: Path) -> str:
    try:
        return str(p.relative_to(REPO_ROOT))
    except ValueError:
        return str(p)


def owner_class(obj: str | None) -> str:
    if obj is None:
        return "none"
    if obj.startswith("build/plain/"):      # the plain link's objects
        obj = "build/" + obj[len("build/plain/"):]
    if obj.startswith(OWNED_ROOTS):
        return "owned"
    if obj.startswith(EXTRACTED_ROOT):
        return "extracted"
    if obj.startswith(BLOB_ROOT):
        return "blob"
    return "other"


def expected_sha1s() -> dict[str, str]:
    out = {}
    if SHA1SUMS.exists():
        for line in SHA1SUMS.read_text().splitlines():
            m = re.match(r"^([0-9a-fA-F]{40})\s+(\S+)", line)
            if m:
                out[m.group(2)] = m.group(1).lower()
    return out


# ----- comparison ------------------------------------------------------

class Comparison:
    """Per-section byte comparison of built vs base, plus the map rows that
    place each byte."""

    def __init__(self, base: Elf, built: Elf, rows: list[dict]):
        self.base, self.built, self.rows = base, built, rows
        self.row_addrs = [r["addr"] for r in rows]
        self.sections = []        # base allocated sections, in address order
        for s in sorted((s for s in base.sections if s["alloc"]),
                        key=lambda s: (s["addr"], s["name"])):
            ent = {"name": s["name"], "addr": s["addr"], "size": s["size"],
                   "nobits": s["nobits"]}
            if not s["nobits"]:
                buf, cov = built.image(s["addr"], s["size"])
                ent["base"] = s["data"]
                ent["built"] = bytes(buf)
                ent["covered"] = bytes(cov)
            self.sections.append(ent)

    def section(self, name: str):
        for s in self.sections:
            if s["name"] == name:
                return s
        return None

    def section_at(self, addr: int):
        for s in self.sections:
            if s["addr"] <= addr < s["addr"] + s["size"]:
                return s
        return None

    @staticmethod
    def _equal_bytes(a: bytes, b: bytes, cov: bytes) -> int:
        if a == b and cov.count(0) == 0:
            return len(a)
        n = 0
        step = 4096
        for i in range(0, len(a), step):
            x, y, c = a[i:i + step], b[i:i + step], cov[i:i + step]
            if x == y and c.count(0) == 0:
                n += len(x)
            else:
                n += sum(1 for p, q, k in zip(x, y, c) if k and p == q)
        return n

    def identical(self, s: dict, lo: int = None, hi: int = None) -> int:
        lo = s["addr"] if lo is None else lo
        hi = s["addr"] + s["size"] if hi is None else hi
        i, j = lo - s["addr"], hi - s["addr"]
        return self._equal_bytes(s["base"][i:j], s["built"][i:j], s["covered"][i:j])

    def range_equal(self, lo: int, hi: int) -> bool:
        s = self.section_at(lo)
        if s is None or s["nobits"] or hi > s["addr"] + s["size"]:
            return False
        i, j = lo - s["addr"], hi - s["addr"]
        return (s["base"][i:j] == s["built"][i:j]
                and s["covered"][i:j].count(0) == 0)

    def first_mismatch(self, s: dict) -> int | None:
        b, c, cov = s["base"], s["built"], s["covered"]
        if b == c and cov.count(0) == 0:
            return None
        step = 4096
        for i in range(0, len(b), step):
            if b[i:i + step] != c[i:i + step] or cov[i:i + step].count(0):
                for k in range(i, min(i + step, len(b))):
                    if b[k] != c[k] or not cov[k]:
                        return s["addr"] + k
        return None

    def owner_at(self, addr: int) -> str | None:
        i = bisect.bisect_right(self.row_addrs, addr) - 1
        if i >= 0:
            r = self.rows[i]
            if r["addr"] <= addr < r["addr"] + r["size"]:
                return row_owner(r) or "*fill*"
        return None

    def rows_in(self, s: dict):
        """Map rows clipped to section s: yields (row, lo, hi)."""
        lo, hi = s["addr"], s["addr"] + s["size"]
        i = max(0, bisect.bisect_right(self.row_addrs, lo) - 1)
        for r in self.rows[i:]:
            if r["addr"] >= hi:
                break
            a, b = max(r["addr"], lo), min(r["addr"] + r["size"], hi)
            if b > a:
                yield r, a, b

    def credit(self, s: dict) -> dict[str, int]:
        """{owned, extracted, blob, other, none} bytes of section s; for
        PROGBITS only bytes identical to the base count toward `owned` and
        `extracted`."""
        out = {"owned": 0, "extracted": 0, "blob": 0, "other": 0, "none": 0,
               "identical_owned": 0, "identical_extracted": 0}
        placed = 0
        for r, a, b in self.rows_in(s):
            cls = owner_class(row_owner(r))
            out[cls] += b - a
            placed += b - a
            if not s["nobits"] and cls in ("owned", "extracted"):
                out["identical_" + cls] += self.identical(s, a, b)
        out["none"] += max(0, s["size"] - placed)
        return out


# ----- --gate ----------------------------------------------------------

def run_gate(args) -> int:
    base, built = Elf(BASE_ELF), Elf(BUILT_ELF)
    rows = parse_map(LINK_MAP)
    cmp_ = Comparison(base, built, rows)
    ok = True

    print(f"check_elf: {_rel(BUILT_ELF)} vs {_rel(BASE_ELF)} (map {_rel(LINK_MAP)})")
    print()
    print(f"{'section':<10} {'addr':>10} {'size':>9}  {'identical/total':>21}  result")
    for s in cmp_.sections:
        if s["nobits"]:
            continue
        same = cmp_.identical(s)
        first = cmp_.first_mismatch(s)
        res = "ok" if first is None else "FAIL"
        if first is not None:
            ok = False
            res += f" first mismatch 0x{first:08X} ({cmp_.owner_at(first) or 'no map row'})"
        print(f"{s['name']:<10} 0x{s['addr']:08X} {s['size']:>9}  "
              f"{same:>10}/{s['size']:<10}  {res}")
    print()
    print(f"{'nobits':<10} {'addr':>10} {'size':>9}  {'allocated':>10}  {'owned':>16}  result")
    for s in cmp_.sections:
        if not s["nobits"]:
            continue
        alloc = built.allocated(s["addr"], s["size"])
        cr = cmp_.credit(s)
        pct = 100.0 * cr["owned"] / s["size"] if s["size"] else 100.0
        res = "ok" if alloc == s["size"] else (
            f"FAIL {s['size'] - alloc} bytes not allocated")
        if alloc != s["size"]:
            ok = False
        print(f"{s['name']:<10} 0x{s['addr']:08X} {s['size']:>9}  {alloc:>10}  "
              f"{cr['owned']:>7} {pct:6.2f} %  {res}")
    print()

    sums = expected_sha1s()
    rom_want = sums.get("baseelf.rom")
    rom_have = hashlib.sha1(BUILT_ROM.read_bytes()).hexdigest() if BUILT_ROM.exists() else None
    rom_ok = rom_want is not None and rom_have == rom_want
    ok &= rom_ok
    print(f"ROM sha1 {rom_have} (want {rom_want}) {'ok' if rom_ok else 'FAIL'}")
    elf_want = sums.get("baseelf.elf")
    elf_ok = built.sha1 == elf_want
    tag = "ok" if elf_ok else ("FAIL" if args.require_elf_sha else "differs (not gated)")
    if args.require_elf_sha:
        ok &= elf_ok
    print(f"ELF sha1 {built.sha1} (want {elf_want}) {tag}")
    print()

    print("informational:")
    b_ri, u_ri = base.section(".reginfo"), built.section(".reginfo")
    if u_ri is None:
        print("  .reginfo          absent in built")
    else:
        eq = b_ri is not None and b_ri["data"] == u_ri["data"]
        print(f"  .reginfo          present, bytes {'equal' if eq else 'differ'}, "
              f"alloc {u_ri['alloc']} (base {b_ri['alloc'] if b_ri else '-'})")
    dvp = [s for s in base.sections if s["name"].startswith(".DVP.")]
    dvp_present = sum(1 for s in dvp if built.section(s["name"]) is not None)
    dvp_equal = sum(1 for s in dvp if (u := built.section(s["name"])) is not None
                    and u["data"] == s["data"] and u["type"] == s["type"])
    print(f"  .DVP.* sections   {dvp_present}/{len(dvp)} present, {dvp_equal}/{len(dvp)} equal")
    print(f"  e_flags           0x{built.e_flags:08X} (base 0x{base.e_flags:08X})"
          f" {'equal' if built.e_flags == base.e_flags else 'differ'}")
    print(f"  e_entry           0x{built.e_entry:08X} (base 0x{base.e_entry:08X})"
          f" {'equal' if built.e_entry == base.e_entry else 'differ'}")

    def ph(p):
        return (f"{p['p_type']} off 0x{p['p_offset']:X} vaddr 0x{p['p_vaddr']:X} "
                f"paddr 0x{p['p_paddr']:X} filesz 0x{p['p_filesz']:X} "
                f"memsz 0x{p['p_memsz']:X} align 0x{p['p_align']:X}")
    print(f"  program headers   {len(built.phdrs)} (base {len(base.phdrs)})")
    for i in range(max(len(built.phdrs), len(base.phdrs))):
        u = ph(built.phdrs[i]) if i < len(built.phdrs) else "-"
        b = ph(base.phdrs[i]) if i < len(base.phdrs) else "-"
        print(f"    [{i}] built {u}")
        print(f"        base  {b}")
    print(f"  section headers   {len(built.sections)} (base {len(base.sections)})")
    print()
    print("check_elf: gate " + ("PASS" if ok else "FAIL"))
    return 0 if ok else 1


# ----- --full-diff -----------------------------------------------------
#
# The whole-file comparison, read straight from the headers with struct so
# that nothing a library normalises (unknown section types, string order) is
# lost. It is the progress meter of the ELF-identity work: the gate above
# compares addresses only, this compares the file.

EHDR_FIELDS = ("e_ident", "e_type", "e_machine", "e_version", "e_entry",
               "e_phoff", "e_shoff", "e_flags", "e_ehsize", "e_phentsize",
               "e_phnum", "e_shentsize", "e_shnum", "e_shstrndx")
PHDR_FIELDS = ("p_type", "p_offset", "p_vaddr", "p_paddr", "p_filesz",
               "p_memsz", "p_flags", "p_align")
SHDR_FIELDS = ("name", "type", "flags", "addr", "offset", "size", "align", "entsize")
SHT_NAMES = {0: "NULL", 1: "PROGBITS", 2: "SYMTAB", 3: "STRTAB", 4: "RELA",
             6: "DYNAMIC", 8: "NOBITS", 9: "REL", 0x70000006: "MIPS_REGINFO"}


class RawElf:
    """ELF32 little-endian headers and section bytes, as the file has them."""

    def __init__(self, path: Path):
        import struct
        self.path = path
        raw = self.raw = path.read_bytes()
        self.sha1 = hashlib.sha1(raw).hexdigest()
        if raw[:4] != b"\x7fELF" or raw[4] != 1 or raw[5] != 1:
            sys.exit(f"check_elf: {path} is not an ELF32 little-endian file")
        v = struct.unpack_from("<HHIIIIIHHHHHH", raw, 16)
        self.ehdr = dict(zip(EHDR_FIELDS, (raw[:16].hex(),) + v))
        e = self.ehdr
        self.phdrs = [dict(zip(PHDR_FIELDS, struct.unpack_from(
            "<8I", raw, e["e_phoff"] + i * e["e_phentsize"])))
            for i in range(e["e_phnum"])]
        shdrs = [struct.unpack_from("<10I", raw, e["e_shoff"] + i * e["e_shentsize"])
                 for i in range(e["e_shnum"])]
        strtab = shdrs[e["e_shstrndx"]] if e["e_shstrndx"] < len(shdrs) else None
        self.shstrtab = raw[strtab[4]:strtab[4] + strtab[5]] if strtab else b""
        self.sections = []
        for n, t, f, a, o, s, lk, inf, al, es in shdrs:
            name = self.shstrtab[n:self.shstrtab.index(b"\0", n)].decode("latin-1")
            data = b"" if t == 8 else raw[o:o + s]
            self.sections.append(dict(name=name, name_off=n, type=t, flags=f, addr=a,
                                      offset=o, size=s, link=lk, info=inf, align=al,
                                      entsize=es, data=data))

    def section(self, name: str):
        return next((s for s in self.sections if s["name"] == name), None)

    def strings(self) -> list[tuple[int, str]]:
        """.shstrtab's strings in file order, (offset, string), the leading
        empty string left out."""
        out, off = [], 1
        while off < len(self.shstrtab):
            end = self.shstrtab.index(b"\0", off)
            out.append((off, self.shstrtab[off:end].decode("latin-1")))
            off = end + 1
        return out


def _sht(t: int) -> str:
    return SHT_NAMES.get(t, f"0x{t:08X}")


def _shf(f: int) -> str:
    s = "".join(c for bit, c in ((1, "W"), (2, "A"), (4, "X"), (0x10000000, "p")) if f & bit)
    rest = f & ~0x10000007
    return s + (f"+0x{rest:X}" if rest else "") or "-"


def _shrow(s: dict | None) -> str:
    if s is None:
        return "-"
    return (f"{s['name'][:38]:<38} {_sht(s['type']):<12} {_shf(s['flags']):<4} "
            f"{s['addr']:08X} {s['offset']:06X} {s['size']:06X} {s['align']:>3} {s['entsize']:>2}")


def _ovlytab(e: RawElf) -> list[str]:
    """.DVP.ovlytab rows (name, lma, vu address), each name resolved through
    .DVP.ovlystrtab by VMA as the rows address it."""
    import struct
    tab, st = e.section(".DVP.ovlytab"), e.section(".DVP.ovlystrtab")
    if tab is None:
        return []
    rows = []
    for i in range(0, len(tab["data"]) - 11, 12):
        nm, lma, vu = struct.unpack_from("<3I", tab["data"], i)
        name = "?"
        if st is not None and st["addr"] <= nm < st["addr"] + st["size"]:
            d, o = st["data"], nm - st["addr"]
            name = d[o:d.index(b"\0", o)].decode("latin-1")
        rows.append(f"name@0x{nm:08X} lma 0x{lma:08X} vu 0x{vu:04X}  {name}")
    return rows


def _side(label: str, a: list[str], b: list[str]) -> tuple[int, int]:
    """Print two lists row by row, `=` where equal; returns (equal, rows)."""
    n = max(len(a), len(b))
    eq = 0
    print(f"{label}: built {len(a)}, base {len(b)}")
    for i in range(n):
        x = a[i] if i < len(a) else "-"
        y = b[i] if i < len(b) else "-"
        same = x == y
        eq += same
        if same:
            print(f"  = [{i:2}] {x}")
        else:
            print(f"  * [{i:2}] built {x}")
            print(f"         base  {y}")
    return eq, n


def run_full_diff(args) -> int:
    built, base = RawElf(BUILT_ELF), RawElf(BASE_ELF)
    tally = {}
    print(f"check_elf --full-diff: {_rel(BUILT_ELF)} vs {_rel(BASE_ELF)}")
    print(f"  file size  built {len(built.raw)}  base {len(base.raw)}")
    print(f"  sha1       built {built.sha1}  base {base.sha1}"
          f"  {'equal' if built.sha1 == base.sha1 else 'differ'}")
    print()

    print("ELF header:")
    eq = 0
    for f in EHDR_FIELDS:
        x, y = built.ehdr[f], base.ehdr[f]
        fx = (lambda v: v) if f == "e_ident" else (lambda v: f"0x{v:X}")
        eq += x == y
        print(f"  {'=' if x == y else '*'} {f:<12} built {fx(x):<34} base {fx(y)}")
    tally["ELF header fields"] = (eq, len(EHDR_FIELDS))
    print()

    def phs(e):
        return [" ".join(f"{k[2:]}=0x{p[k]:X}" for k in PHDR_FIELDS) for p in e.phdrs]
    tally["program headers"] = _side("program headers", phs(built), phs(base))
    print()

    print("  columns: name type flags addr offset size align entsize")
    tally["section headers"] = _side("section headers (file order)",
                                     [_shrow(s) for s in built.sections],
                                     [_shrow(s) for s in base.sections])
    bn = [s["name"] for s in built.sections]
    print(f"  base names absent in built: "
          f"{', '.join(s['name'] or '(null)' for s in base.sections if s['name'] not in bn) or 'none'}")
    an = [s["name"] for s in base.sections]
    print(f"  built names absent in base: "
          f"{', '.join(n or '(null)' for n in bn if n not in an) or 'none'}")
    print()

    def strs(e):
        return [f"0x{o:03X} {s}" for o, s in e.strings()]
    tally[".shstrtab strings"] = _side(".shstrtab strings (offset, file order)",
                                       strs(built), strs(base))
    print(f"  .shstrtab bytes {'equal' if built.shstrtab == base.shstrtab else 'differ'}"
          f" (built {len(built.shstrtab)} B, base {len(base.shstrtab)} B)")
    print()

    def reginfo(e):
        import struct
        s = e.section(".reginfo")
        if s is None:
            return []
        names = ("ri_gprmask", "ri_cprmask[0]", "ri_cprmask[1]", "ri_cprmask[2]",
                 "ri_cprmask[3]", "ri_gp_value")
        return [f"{n:<14} 0x{w:08X}" for n, w in
                zip(names, struct.unpack_from(f"<{len(s['data']) // 4}I", s["data"]))]
    tally[".reginfo words"] = _side(".reginfo words", reginfo(built), reginfo(base))
    print()

    tally[".DVP.ovlytab rows"] = _side(".DVP.ovlytab rows", _ovlytab(built), _ovlytab(base))
    print()

    def ovlstr(e):
        s = e.section(".DVP.ovlystrtab")
        return [x.decode("latin-1") for x in s["data"].split(b"\0") if x] if s else []
    tally[".DVP.ovlystrtab names"] = _side(".DVP.ovlystrtab names (file order)",
                                           ovlstr(built), ovlstr(base))
    print()

    print("section bytes (every name in both; NOBITS compares sizes only):")
    eq = n = 0
    for s in base.sections:
        u = built.section(s["name"])
        if u is None or not s["name"]:
            continue
        n += 1
        if s["type"] == 8 or u["type"] == 8:
            same = s["type"] == u["type"] and s["size"] == u["size"]
            what = "NOBITS size " + ("equal" if same else f"built {u['size']:#x} base {s['size']:#x}")
        else:
            same = u["data"] == s["data"]
            what = ("equal" if same else
                    f"differ (built {u['size']:#x} B, base {s['size']:#x} B)")
        eq += same
        print(f"  {'=' if same else '*'} {s['name']:<38} {what}")
    tally["sections with equal bytes"] = (eq, n)
    print()

    print("summary (equal / compared):")
    for k, (e_, t) in tally.items():
        print(f"  {k:<28} {e_:>3} / {t}")
    print(f"  {'file sha1':<28} {'equal' if built.sha1 == base.sha1 else 'differ'}")
    return 0


# ----- --progress ------------------------------------------------------

def _strip_suffix(name: str) -> str:
    return re.sub(r"\.\d+$", "", name)


def _tu_of(obj: str) -> str:
    p = obj[len("build/"):] if obj.startswith("build/") else obj
    return p[:-2] if p.endswith(".o") else p


def _group_of(tu: str, in_vutext: bool) -> str:
    if in_vutext:
        return VUTEXT_GROUP
    parts = tu.split("/")
    if parts[0] == "ico2" and len(parts) > 2:
        return parts[1]
    return parts[0]


def compute(cmp_: Comparison) -> dict:
    sections: dict[str, list[int]] = {}
    extracted: dict[str, int] = {}
    for name in REPORT_ORDER:
        s = cmp_.section(name)
        if s is None:
            continue
        cr = cmp_.credit(s)
        if s["nobits"]:
            sections[name] = [cr["owned"], s["size"]]
            extracted[name] = cr["extracted"]
        else:
            sections[name] = [cr["identical_owned"], s["size"]]
            extracted[name] = cr["identical_extracted"]
    return {"sections": sections, "extracted": extracted}


def build_tree(cmp_: Comparison, secs: dict) -> dict:
    text_like = [s for s in cmp_.sections if s["name"] in (".text", ".vutext")]
    vut = cmp_.section(".vutext")
    funcs = cmp_.built.funcs
    func_addrs = [f[0] for f in funcs]

    # TU .text spans from the map rows (fill excluded; a TU is the object).
    spans: dict[str, list[tuple[int, int]]] = {}
    for s in text_like:
        for r, a, b in cmp_.rows_in(s):
            if r["obj"] is None or owner_class(r["obj"]) not in ("owned", "extracted"):
                continue
            spans.setdefault(r["obj"], []).append((a, b))

    # Non-text bytes each TU's object places, for `section_bytes`.
    sec_bytes: dict[str, dict[str, int]] = {}
    for s in cmp_.sections:
        if s["name"] in (".text", ".vutext") or not s["size"]:
            continue
        for r, a, b in cmp_.rows_in(s):
            if r["obj"] is None or owner_class(r["obj"]) != "owned":
                continue
            d = sec_bytes.setdefault(_tu_of(r["obj"]), {})
            d[s["name"]] = d.get(s["name"], 0) + (b - a)

    programmers: dict[str, dict] = {}
    sym_sections: dict[str, list[int]] = {}
    for obj, sp in spans.items():
        tu = _tu_of(obj)
        in_vu = vut is not None and all(vut["addr"] <= a < vut["addr"] + vut["size"] for a, _ in sp)
        prog = _group_of(tu, in_vu)
        tu_name = tu.split("/", 2)[-1] if tu.startswith("ico2/") else tu.split("/", 1)[-1]
        node = {"name": tu_name, "path": tu, "funcs": []}
        if prog == "sce" and "/" in tu:
            node["archive"] = tu.split("/")[1]
        for lo, hi in sp:
            sect = cmp_.section_at(lo)["name"]
            i = bisect.bisect_left(func_addrs, lo)
            inside = []
            while i < len(funcs) and funcs[i][0] < hi:
                inside.append(funcs[i])
                i += 1
            for k, (addr, size, name) in enumerate(inside):
                if size == 0:
                    nxt = inside[k + 1][0] if k + 1 < len(inside) else hi
                    size = nxt - addr
                size = min(size, hi - addr)
                matched = cmp_.range_equal(addr, addr + size)
                node["funcs"].append({
                    "name": _strip_suffix(name), "addr": f"0x{addr:08X}",
                    "size": size, "section": sect, "matched": matched,
                })
                ss = sym_sections.setdefault(sect, [0, 0])
                ss[1] += size
                if matched:
                    ss[0] += size
        p = programmers.setdefault(prog, {"name": prog, "tus": {}})
        p["tus"][tu] = node

    prog_list = []
    tot_mf = tot_f = 0
    for prog in sorted(programmers.values(), key=lambda p: p["name"]):
        tus = []
        pmf = pf = pmb = pb = 0
        for t in sorted(prog["tus"].values(), key=lambda t: t["path"]):
            fs = sorted(t["funcs"], key=lambda f: f["addr"])
            mf = sum(1 for f in fs if f["matched"])
            mb = sum(f["size"] for f in fs if f["matched"])
            b = sum(f["size"] for f in fs)
            node = {"name": t["name"], "path": t["path"],
                    **({"archive": t["archive"]} if "archive" in t else {}),
                    "matched_funcs": mf, "total_funcs": len(fs),
                    "matched_bytes": mb, "total_bytes": b, "funcs": fs}
            sb = sec_bytes.get(t["path"])
            if sb:
                node["section_bytes"] = {k: sb[k] for k in sorted(sb)}
            tus.append(node)
            pmf += mf; pf += len(fs); pmb += mb; pb += b
        entry = {"name": prog["name"], "matched_funcs": pmf, "total_funcs": pf,
                 "matched_bytes": pmb, "total_bytes": pb, "tus": tus}
        if prog["name"] == VUTEXT_GROUP:
            entry["note"] = VUTEXT_NOTE
        prog_list.append(entry)
        tot_mf += pmf; tot_f += pf

    sections = {k: v for k, v in secs["sections"].items() if v[1]}
    text = sections.get(".text", [0, 0])
    return {
        "schema": 2,
        "version": VERSION,
        "totals": {
            "matched_funcs": tot_mf, "total_funcs": tot_f,
            "matched_bytes": text[0], "total_bytes": text[1],
            "sections": sections,
            "extracted": {k: secs["extracted"].get(k, 0) for k in sections},
            "nobits_sections": [s for s in NOBITS if s in sections],
            "sections_from_symbols": {k: v for k, v in sorted(sym_sections.items())},
        },
        "programmers": prog_list,
    }


def _fmt_pct(m: int, t: int) -> str:
    return "-" if t == 0 else f"{100.0 * m / t:.2f} %"


def _badge_color(m: int, t: int) -> str:
    if t == 0:
        return "lightgrey"
    pct = 100.0 * m / t
    for floor, color in ((100.0, "brightgreen"), (75.0, "green"),
                         (50.0, "yellowgreen"), (25.0, "yellow")):
        if pct >= floor:
            return color
    return "orange" if pct > 0.0 else "red"


def _badges(sections: dict) -> str:
    from urllib.parse import quote
    lines = []
    for sec in REPORT_ORDER:
        m, t = sections.get(sec, (0, 0))
        if not t:
            continue
        pct = quote(_fmt_pct(m, t), safe="").replace("-", "%2D")
        url = f"https://img.shields.io/badge/{sec.lstrip('.')}-{pct}-{_badge_color(m, t)}.svg"
        lines.append(f"![{sec} progress]({url})")
    return "\n".join(lines)


def _table(sections: dict) -> str:
    lines = ["| Section | Matched bytes | Total bytes | % |",
             "| --- | ---: | ---: | ---: |"]
    for sec in REPORT_ORDER:
        m, t = sections.get(sec, (0, 0))
        if not t:
            continue
        metric = " (owned)" if sec in NOBITS else ""
        lines.append(f"| `{sec}`{metric} | {m} | {t} | {_fmt_pct(m, t)} |")
    lines.append("")
    lines.append(
        "`.sbss` and `.bss` are NOBITS: they hold no ROM bytes, so their "
        "figure is **ownership**, how much of the section a compiled C "
        "object defines and the link seats at the ROM's VMAs, not "
        "reproduced bytes. A section the ELF sizes at zero (`.vudata` on "
        "this target) is omitted.")
    return "\n".join(lines)


BEGIN, END = "<!-- progress:begin -->", "<!-- progress:end -->"


def _splice(path: Path, body: str) -> bool:
    text = path.read_text()
    if BEGIN not in text or END not in text:
        sys.exit(f"check_elf: {path} has no {BEGIN} / {END} markers")
    pat = re.compile(re.escape(BEGIN) + r".*?" + re.escape(END), re.DOTALL)
    new = pat.sub(lambda _: BEGIN + "\n" + body + "\n" + END, text)
    if new == text:
        return False
    path.write_text(new)
    return True


def run_progress(args) -> int:
    base, built = Elf(BASE_ELF), Elf(BUILT_ELF)
    cmp_ = Comparison(base, built, parse_map(LINK_MAP))
    secs = compute(cmp_)
    tree = build_tree(cmp_, secs)
    sections = tree["totals"]["sections"]
    print("progress (from C or owned / total):")
    for sec in REPORT_ORDER:
        if sec in sections:
            m, t = sections[sec]
            print(f"  {sec:<10} {m:>10} / {t:<10} {_fmt_pct(m, t):>8}"
                  f"  extracted {tree['totals']['extracted'].get(sec, 0)}")
    t = tree["totals"]
    print(f"  functions  {t['matched_funcs']}/{t['total_funcs']}, "
          f"{len(tree['programmers'])} groups")
    out = Path(args.out_dir) if args.out_dir else None
    readme = (out / "README.md") if out else README
    doc = (out / "PROGRESS.md") if out else PROGRESS_DOC
    js = (out / "progress.json") if out else PROGRESS_JSON
    if out:
        out.mkdir(parents=True, exist_ok=True)
        readme.write_text(README.read_text())
        doc.write_text(PROGRESS_DOC.read_text())
    for path, body in ((readme, _badges(sections)), (doc, _table(sections))):
        print(f"check_elf: {'rewrote' if _splice(path, body) else 'unchanged'} {path}")
    js.write_text(json.dumps(tree, separators=(",", ":")) + "\n")
    print(f"check_elf: wrote {js}")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument("--gate", action="store_true")
    mode.add_argument("--progress", action="store_true")
    mode.add_argument("--full-diff", action="store_true")
    ap.add_argument("--require-elf-sha", action="store_true",
                    help="--gate: also require the built ELF's SHA-1 to equal baseelf.elf's")
    ap.add_argument("--out-dir", help="--progress: write the three files here "
                    "instead of README.md, docs/PROGRESS.md, docs/progress.json")
    ap.add_argument("--elf", help="built ELF (default build/ico.elf)")
    ap.add_argument("--map", help="link map (default build/ico.<ver>.map)")
    ap.add_argument("--rom", help="built ROM (default build/ico.rom)")
    args = ap.parse_args()
    global BUILT_ELF, LINK_MAP, BUILT_ROM
    if args.elf:
        BUILT_ELF = Path(args.elf).resolve()
    if args.map:
        LINK_MAP = Path(args.map).resolve()
    if args.rom:
        BUILT_ROM = Path(args.rom).resolve()
    for p in (BASE_ELF, BUILT_ELF) + (() if args.full_diff else (LINK_MAP,)):
        if not p.exists():
            sys.exit(f"check_elf: {p} not found")
    if args.full_diff:
        return run_full_diff(args)
    return run_gate(args) if args.gate else run_progress(args)


if __name__ == "__main__":
    sys.exit(main())
