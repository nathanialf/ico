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
    for p in (BASE_ELF, BUILT_ELF, LINK_MAP):
        if not p.exists():
            sys.exit(f"check_elf: {p} not found")
    return run_gate(args) if args.gate else run_progress(args)


if __name__ == "__main__":
    sys.exit(main())
