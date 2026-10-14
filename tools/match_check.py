#!/usr/bin/env python3
"""match_check.py: one function's state against the target, without the link.

Compiles a translation unit with tools/compile_c.sh into a scratch object
(build/ is not touched), reads each function of it from the object's .symtab
with its .text relocations, and compares its instruction words with the
target ELF's words at that function's range. The fields the object's
relocations fill are masked on both sides, and no other field: R_MIPS_26
keeps the opcode of a j or jal, R_MIPS_HI16, R_MIPS_LO16, R_MIPS_GPREL16 and
R_MIPS_LITERAL keep the upper half, as tools/correlate_elf.py masks them
(its RELOC_KIND table and its residue classes are used here). Trailing zero
words are left out on both sides, as correlate_elf.py does.

The target ELF is the branch's base ELF (tools/ico_version.py), and the range
of a function is, in this order:
  --at VMA          VMA, for the length of the object's function
  --twins FILE      the function's row of a correlate_elf.py twins.txt
                    (target_vma, target_size)
  the stub list     its text row in config/stubs.<slug>.txt for this TU
                    (vma_lo, vma_hi; the stem when two statics share a name)
  the build         its symbol in build/ico.syms.elf, inside this TU's .text
                    in the link map: the function's place in the last link,
                    which is the target's once the gate passes (only when
                    the target is the branch's own base ELF)
On main, with no rows, every function is found the last way and is compared
with the PAL base at its own address: the self-test, every function equal.

For each function it prints `equal`, or the first differing instruction with
five instructions of context on each side, from both sides, disassembled by
mips-linux-gnu-objdump (the object's side names the relocation at each word),
and correlate_elf.py's residue class: imm:N (N words of one length that
differ only in an I-type immediate), other:N, or length:+D (the target has D
more words). A function still carved (INCLUDE_ASM in the TU, or in its row's
in=<file.c.inc> unless the row is inline) is reported as a stub: its words come from the base and say nothing about the C.

  tools/match_check.py TU FUNC...         the named functions
  tools/match_check.py TU --all           every function of the TU, one line each
  tools/match_check.py TU FUNC --at VMA
  tools/match_check.py TU --all --twins build/correlate/<name>/twins.txt
Exit 0 when every function compared is equal.
"""

from __future__ import annotations

import argparse
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

try:
    from elftools.elf.elffile import ELFFile
    from elftools.elf.relocation import RelocationSection
    from elftools.elf.sections import SymbolTableSection
except ImportError:
    sys.exit("match_check.py: missing pyelftools. Run "
             "`.venv/bin/pip install -r tools/requirements.txt`.")

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from check_elf import parse_map  # noqa: E402
from correlate_elf import RELOC_KIND, describe_reloc, residue  # noqa: E402
from gen_stub_s import LIST, asm_line, parse_stubs  # noqa: E402
from ico_version import baseelf_path, detect_version, link_map_path  # noqa: E402

VERSION = detect_version(ROOT)
TARGET = baseelf_path(ROOT, VERSION)
SYMS = ROOT / "build" / "ico.syms.elf"
MAP = link_map_path(ROOT, VERSION)
OBJDUMP = "mips-linux-gnu-objdump"
CONTEXT = 5

# the bits a relocation of each kind leaves alone
KEEP = {"j": 0xFC000000, "hi": 0xFFFF0000, "lo": 0xFFFF0000}


def fail(msg):
    sys.exit(f"match_check: {msg}")


class Side:
    """One side's words, masked words and per-word relocation notes, in the
    shape correlate_elf.residue reads (n, norm)."""

    def __init__(self, vma, words, keep):
        ws = list(words)
        while ws and ws[-1] == 0:
            ws.pop()
        self.vma, self.words, self.n = vma, ws, len(ws)
        self.norm = [w & keep.get(k, 0xFFFFFFFF) for k, w in enumerate(ws)]


# ------------------------------------------------------------- object ----

def compile_tu(tu: str, out: Path) -> Path:
    obj = out / (Path(tu).stem + ".o")
    p = subprocess.run(["tools/compile_c.sh", tu, str(obj)], cwd=ROOT, capture_output=True, text=True)
    if p.returncode:
        sys.stderr.write(p.stdout + p.stderr)
        fail(f"{tu} does not compile")
    return obj


def object_functions(obj: Path):
    """{name: (offset, words, {word index: (kind or None, relocation, symbol)})}
    of the object's .text functions, in address order."""
    with obj.open("rb") as fh:
        elf = ELFFile(fh)
        text = elf.get_section_by_name(".text")
        tidx = next(i for i, s in enumerate(elf.iter_sections()) if s.name == ".text")
        data = text.data()
        symtab = elf.get_section_by_name(".symtab")
        if not isinstance(symtab, SymbolTableSection):
            fail(f"{obj} has no symbol table")
        funcs = sorted((s["st_value"], s["st_size"], s.name) for s in symtab.iter_symbols()
                       if s["st_info"]["type"] == "STT_FUNC" and s["st_shndx"] == tidx)
        relocs = {}
        for sec in elf.iter_sections():
            if isinstance(sec, RelocationSection) and elf.get_section(sec["sh_info"]).name == ".text":
                for r in sec.iter_relocations():
                    t = describe_reloc(elf, r["r_info_type"])
                    sym = symtab.get_symbol(r["r_info_sym"])
                    name = sym.name or (elf.get_section(sym["st_shndx"]).name
                                        if isinstance(sym["st_shndx"], int) else "")
                    relocs[r["r_offset"]] = (RELOC_KIND.get(t), t, name)
    starts = [v for v, _, _ in funcs]
    out = {}
    for k, (v, size, name) in enumerate(funcs):
        end = v + size if size else (starts[k + 1] if k + 1 < len(starts) else len(data))
        words = struct.unpack("<%dI" % ((end - v) // 4), data[v:v + (end - v) // 4 * 4])
        notes = {(a - v) // 4: relocs[a] for a in relocs if v <= a < end}
        out[name] = (v, words, notes)
    return out


# ------------------------------------------------------------- target ----

class Elf:
    def __init__(self, path: Path):
        self.path = path
        self.secs = []
        with path.open("rb") as fh:
            for s in ELFFile(fh).iter_sections():
                if s["sh_type"] == "SHT_PROGBITS" and s["sh_flags"] & 2:
                    self.secs.append((s["sh_addr"], s.data()))

    def words(self, lo, hi):
        for base, data in self.secs:
            if base <= lo and hi <= base + len(data):
                return struct.unpack("<%dI" % ((hi - lo) // 4), data[lo - base:hi - base])
        fail(f"0x{lo:08X}..0x{hi:08X} is not inside one allocated section of {self.path}")


def build_symbols(tu: str):
    """{name: (vma, size)} of build/ico.syms.elf's functions inside this TU's
    .text, by the link map."""
    if not SYMS.exists() or not MAP.exists():
        return {}
    obj = "build/" + str(Path(tu).with_suffix(".o"))
    spans = [(r["addr"], r["addr"] + r["size"]) for r in parse_map(MAP)
             if r["sect"] == ".text" and r["obj"] == obj]
    out = {}
    with SYMS.open("rb") as fh:
        for s in ELFFile(fh).get_section_by_name(".symtab").iter_symbols():
            v = s["st_value"]
            if s["st_info"]["type"] == "STT_FUNC" and any(a <= v < b for a, b in spans):
                out[s.name] = (v, s["st_size"])
    return out


def read_twins(path: Path):
    """{name: [(target_vma, target_size)]} of a twins.txt."""
    out = {}
    for line in path.read_text().splitlines():
        if line.startswith("#") or not line.strip():
            continue
        f = line.split("\t")
        out.setdefault(f[0], []).append((int(f[3], 16), int(f[4])))
    return out


# ------------------------------------------------------------ compare ----

def disasm(words, vma, notes=None):
    """objdump's lines for the words, one per word; with notes, each
    relocated word names its relocation."""
    with tempfile.NamedTemporaryFile(suffix=".bin") as fh:
        fh.write(struct.pack("<%dI" % len(words), *words))
        fh.flush()
        p = subprocess.run([OBJDUMP, "-D", "-b", "binary", "-m", "mips:5900", "-EL",
                            f"--adjust-vma=0x{vma:x}", fh.name], capture_output=True, text=True)
    lines = [l for l in p.stdout.splitlines() if l[:1] == " " and ":\t" in l]
    if len(lines) != len(words):
        lines = [f"  {vma + 4 * k:x}:\t{w:08x}" for k, w in enumerate(words)]
    if notes:
        lines = [l + (f"\t<{notes[k][1]} {notes[k][2]}>" if k in notes else "") for k, l in enumerate(lines)]
    return lines


def compare(name, obj_fn, lo, hi, target, label):
    v, words, notes = obj_fn
    keep = {k: KEEP.get(kd, 0) for k, (kd, _, _) in notes.items()}
    a = Side(v, words, keep)
    b = Side(lo, target.words(lo, hi), keep)
    k = next((i for i in range(min(a.n, b.n)) if a.norm[i] != b.norm[i]), None)
    if k is None and a.n == b.n:
        return True, f"equal ({a.n} instructions, {len(notes)} relocated fields masked; {label})"
    if k is None:
        k = min(a.n, b.n)
    res = residue(a, b)
    head = (f"differs at instruction {k} (object +0x{4 * k:x}, target 0x{lo + 4 * k:08X}), {res}; "
            f"{a.n} against {b.n} instructions; {label}")
    s, e = max(0, k - CONTEXT), k + CONTEXT + 1
    da = disasm(a.words[s:e], v + 4 * s, {i - s: n for i, n in notes.items() if s <= i < e})
    db = disasm(b.words[s:e], lo + 4 * s)
    body = ["    object:"] + [("  > " if s + i == k else "    ") + l for i, l in enumerate(da)]
    body += ["    target:"] + [("  > " if s + i == k else "    ") + l for i, l in enumerate(db)]
    return False, head + "\n" + "\n".join(body)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("tu", help="the C source, repo-relative (ico2/... or sce/...)")
    ap.add_argument("funcs", nargs="*", metavar="FUNC", help="function names (a row's stem works too)")
    ap.add_argument("--all", action="store_true", help="every function of the TU, one line each")
    ap.add_argument("--at", type=lambda x: int(x, 16), metavar="VMA", help="the target address of the one FUNC")
    ap.add_argument("--twins", type=Path, metavar="FILE", help="a correlate_elf.py twins.txt")
    ap.add_argument("--elf", type=Path, default=TARGET, help=f"the target ELF (default {TARGET.relative_to(ROOT)})")
    ap.add_argument("--stubs", type=Path, default=LIST, help=f"the stub list (default {LIST.relative_to(ROOT)})")
    a = ap.parse_args()
    tu = a.tu
    if not (ROOT / tu).is_file():
        fail(f"{tu}: no such source")
    if a.at is not None and len(a.funcs) != 1:
        fail("--at takes exactly one FUNC")
    if not a.funcs and not a.all:
        fail("name a function, or --all")
    rows = [r for r in parse_stubs(a.stubs) if r["section"] == "text" and r["tu"] == tu]
    by_key = {}
    for r in rows:
        by_key[r["stem"]] = r
        by_key.setdefault(r["name"], r)
    src = (ROOT / tu).read_bytes().splitlines(keepends=True)
    with tempfile.TemporaryDirectory(prefix="match_check.") as tmp:
        fns = object_functions(compile_tu(tu, Path(tmp)))
    twins = read_twins(a.twins) if a.twins else {}
    # the last link's addresses are the target's only for the branch's own base
    built = build_symbols(tu) if a.elf.resolve() == TARGET.resolve() else {}
    target = Elf(a.elf)
    bad = equal = none = 0
    keys = list(fns) if a.all else a.funcs
    for key in keys:
        row = by_key.get(key)
        name = row["name"] if row else key
        if name not in fns:
            print(f"match_check: {name}: not a function of the compiled {tu}")
            none += 1
            continue
        v, words, notes = fns[name]
        # the INCLUDE_ASM line lives in the TU, or in the row's in=<file.c.inc>
        # (for an inline function of a .c.inc, in the TU: the row's asm file)
        stub = row is not None and asm_line(row["stem"]) in (
            src if row["asm"] == tu else (ROOT / row["asm"]).read_bytes().splitlines(keepends=True))
        if a.at is not None:
            lo, hi, label = a.at, a.at + 4 * len(words), f"--at 0x{a.at:08X}"
        elif twins.get(name):
            if len(twins[name]) > 1:
                print(f"match_check: {name}: {len(twins[name])} rows in {a.twins}; give --at")
                none += 1
                continue
            t, size = twins[name][0]
            lo, hi, label = t, t + size, f"twin 0x{t:08X} in {a.twins}"
        elif row is not None:
            lo, hi, label = row["lo"], row["hi"], f"row {row['stem']} 0x{row['lo']:08X} in {a.stubs.name}"
        elif name in built:
            t, size = built[name]
            # an asm-defined function may carry no .size: the object's length
            lo, hi, label = t, t + (size or 4 * len(words)), f"0x{t:08X} from {SYMS.relative_to(ROOT)}"
        else:
            print(f"match_check: {name}: no target range (no row, no twin, no symbol in the last link); give --at")
            none += 1
            continue
        ok, text = compare(name, fns[name], lo, hi, target, label)
        if stub:
            text = "stub (INCLUDE_ASM: the base's words, not the C's); " + text
        if a.all and not ok:
            text = text.split("\n", 1)[0]
        print(f"match_check: {name}: {text}")
        equal += ok
        bad += not ok
    if a.all or len(keys) > 1:
        print(f"match_check: {tu}: {equal} equal, {bad} differ, {none} with no target range, against "
              f"{a.elf.relative_to(ROOT) if a.elf.is_relative_to(ROOT) else a.elf}")
    return 1 if bad or none else 0


if __name__ == "__main__":
    raise SystemExit(main())
