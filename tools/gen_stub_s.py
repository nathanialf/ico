#!/usr/bin/env python3
"""tools/gen_stub_s.py -- write the not-yet-matched functions as stubs from the base ELF.

During a target's campaign the functions whose C does not yet give the base's
bytes still have to sit at the base's addresses, so the byte gate passes at
every commit. Each one is listed in config/stubs.<slug>.txt (slug from
tools/ico_version.py) and its translation unit carries `INCLUDE_ASM(name);`
where the function stands in the file. This tool writes build/stubs/<name>.s
for every row from the user's own base ELF, as build/data/ is written by
tools/gen_data_c.py: nothing of the ROM is tracked (docs/LEGAL.md). It also
writes the macro's header, build/stubs/include_asm.h, every time it runs; the
tree tracks no copy of it, and tools/compile_c.sh searches build/stubs last,
so a TU that includes "include_asm.h" compiles only while stubs exist. With
the list empty the mechanism is idle.

The list, one row per stub, `#` starts a comment:

    <section> <name> <vma_lo> <vma_hi> <tu> [local] [align=N] [lines=N]

  section   text, rodata, data or sdata: the base ELF section the range lies in
  name      the symbol the stub defines (MAIN.MAP's name, or D_<VMA>)
  vma_lo/hi the range [lo, hi) in the base ELF, hex; a text row ends at the
            function's last instruction, not at the fill after it
  tu        the tracked C source whose INCLUDE_ASM(name) includes the stub
            (ninja makes that object depend on build/stubs/<name>.s)
  local     the name is file-local in the C (a static), so no .globl
  align=N   the stub's alignment in bytes; by default the largest power of
            two dividing vma_lo, at most 8 (ee-gcc's .p2align 3 per function
            and per rodata object)
  lines=N   the stubbed body spanned N source lines in the TU; nothing in
            the build reads it yet (the parser accepts it, --list prints it)

The INCLUDE_ASM line that replaces a body shifts every later line of the TU,
so __LINE__ after it (an assert, a debug print) gives other numbers than the
finished C will. A TU that uses __LINE__ below the stub keeps its numbering
with a `#line` directive after the INCLUDE_ASM line, the number the line
after the body had; `lines=N` records the span it was worked out from. The
directive is written by hand during the campaign, never by a tool, and the
byte gate decides whether it is right.

A text row is written as one function: `.set noreorder`, `.globl`,
`.type @function`, `.ent`, one `.word` per instruction, `.end`, `.size`. A
data row is a run of `.word`, `.half` and `.byte` as the address allows. The
words are absolute: there are no relocations, the stub is right only at its
own address, and the gate proves the layout. Each stub returns to the section
it was included from (`.previous`), so the compiler's own section state holds.

    tools/gen_stub_s.py                      write build/stubs/<name>.s for every row
    tools/gen_stub_s.py --list               print the rows
    tools/gen_stub_s.py --check build/ico.syms.elf
        every row's bytes in the built ELF equal the base's at that range (and,
        when the ELF keeps its symbols, the stub's symbol sits at vma_lo with
        size vma_hi - vma_lo); the gate checks the bytes too, this names the stub
"""

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
# pyelftools is imported where an ELF is read, so parse_stubs serves
# tools/check_dev_native.py under the hook's plain python3.
from ico_version import baseelf_path, config_path, detect_version  # noqa: E402

VERSION = detect_version(ROOT)
LIST = config_path(ROOT, VERSION, "stubs", "txt")
BASE_ELF = baseelf_path(ROOT, VERSION)
OUT_DIR = ROOT / "build/stubs"
HEADER = "include_asm.h"
SECTIONS = ("text", "rodata", "data", "sdata")

# build/stubs/include_asm.h, written with the stubs; never tracked.
HEADER_TEXT = """\
#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

/* Campaign scaffolding, not the developers' source, written by
 * tools/gen_stub_s.py into build/stubs/ (never tracked). While a target is
 * being rebuilt from this tree, a function whose C does not yet give the
 * base's bytes is listed in config/stubs.<slug>.txt and its translation unit
 * carries
 *
 *     INCLUDE_ASM(name);
 *
 * at the place the function has in the file. tools/gen_stub_s.py writes
 * build/stubs/name.s from the user's own base ELF, and the assembler
 * reads it at that point of the compiler's output, so the stub lands between
 * the functions around it. The path is relative to the repository root,
 * where tools/compile_c.sh runs the assembler. tools/check_dev_native.py
 * refuses any other asm of this kind, and this one for a name the list does
 * not carry.
 *
 * The line replaces the function's body, so every later line of the TU moves
 * up. A TU that uses __LINE__ below it keeps its numbering by hand with a
 * `#line` directive after the INCLUDE_ASM line, the number the line after the
 * body had (the row's lines=N records the span); the byte gate decides. */
#define INCLUDE_ASM(NAME) __asm__(".include \\"build/stubs/" #NAME ".s\\"")

#endif /* INCLUDE_ASM_H */
"""


def fail(msg):
    sys.exit(f"gen_stub_s: {msg}")


def natural_align(addr, cap=8):
    """The largest power of two dividing addr, at most cap."""
    a = 1
    while a < cap and addr % (a * 2) == 0:
        a *= 2
    return a


# ------------------------------------------------------------------ list ----

def parse_stubs(path=LIST):
    """config/stubs.<slug>.txt's rows, in file order; [] when the file is
    absent or holds only comments (the mechanism is idle)."""
    if not path.exists():
        return []
    rows, names, where = [], {}, f"{path.relative_to(ROOT) if path.is_relative_to(ROOT) else path}"
    for n, line in enumerate(path.read_text().splitlines(), 1):
        f = line.split("#", 1)[0].split()
        if not f:
            continue
        if len(f) < 5 or f[0] not in SECTIONS:
            fail(f"{where}:{n}: expected '<section> <name> <vma_lo> <vma_hi> <tu> [local] [align=N] [lines=N]'"
                 f" with section one of {', '.join(SECTIONS)}")
        sec, name, tu = f[0], f[1], f[4]
        if not re.fullmatch(r"[A-Za-z_][\w.]*", name):
            fail(f"{where}:{n}: '{name}' is not a symbol name")
        try:
            lo, hi = int(f[2], 16), int(f[3], 16)
        except ValueError:
            fail(f"{where}:{n}: vma_lo and vma_hi are hex addresses")
        if not lo < hi:
            fail(f"{where}:{n}: empty range")
        if sec == "text" and (lo % 4 or hi % 4):
            fail(f"{where}:{n}: a text range starts and ends on a word")
        if not re.fullmatch(r"(ico2|sce)/\S+\.c", tu):
            fail(f"{where}:{n}: '{tu}' is not a C source under ico2/ or sce/")
        local, align, span = False, natural_align(lo), None
        for tok in f[5:]:
            m = re.fullmatch(r"align=(\d+)", tok)
            k = re.fullmatch(r"lines=(\d+)", tok)
            if tok == "local":
                local = True
            elif m and int(m.group(1)) in (1, 2, 4, 8, 16) and lo % int(m.group(1)) == 0:
                align = int(m.group(1))
            elif k and int(k.group(1)) > 0:
                span = int(k.group(1))
            else:
                fail(f"{where}:{n}: bad token '{tok}' (local, align=N with N a power of two dividing vma_lo,"
                     " or lines=N with N > 0)")
        if name in names:
            fail(f"{where}:{n}: {name} is listed twice (first at line {names[name]})")
        names[name] = n
        rows.append(dict(section=sec, name=name, lo=lo, hi=hi, tu=tu, local=local, align=align,
                         lines=span, line=n))
    by_addr = sorted(rows, key=lambda r: r["lo"])
    for a, b in zip(by_addr, by_addr[1:]):
        if b["lo"] < a["hi"]:
            fail(f"{where}:{b['line']}: {b['name']} overlaps {a['name']} (line {a['line']})")
    return rows


# ------------------------------------------------------------------- ELF ----

def section_bytes(elf, row, what):
    """The ELF's bytes [lo, hi) of the row's section, found by address."""
    lo, hi = row["lo"], row["hi"]
    for s in elf.iter_sections():
        base, size = s["sh_addr"], s["sh_size"]
        if s["sh_type"] == "SHT_PROGBITS" and s["sh_flags"] & 2 and base <= lo and hi <= base + size:
            if s.name != "." + row["section"]:
                fail(f"{row['name']}: 0x{lo:08X}..0x{hi:08X} lies in {what}'s {s.name}, not .{row['section']}")
            return s.data()[lo - base:hi - base]
    fail(f"{row['name']}: 0x{lo:08X}..0x{hi:08X} is not inside one allocated section of {what}")


# ----------------------------------------------------------------- write ----

def data_lines(buf, lo):
    """.word, .half and .byte as the address allows, eight values a line."""
    out, i, run, kind = [], 0, [], None

    def flush():
        if run:
            out.append(f"    {kind} " + ", ".join(run))
            run.clear()

    while i < len(buf):
        a = lo + i
        if a % 4 == 0 and len(buf) - i >= 4:
            k, v, w = ".word", int.from_bytes(buf[i:i + 4], "little"), 4
            t = f"0x{v:08X}"
        elif a % 2 == 0 and len(buf) - i >= 2:
            k, v, w = ".half", int.from_bytes(buf[i:i + 2], "little"), 2
            t = f"0x{v:04X}"
        else:
            k, w, t = ".byte", 1, f"0x{buf[i]:02X}"
        if k != kind or len(run) == 8:
            flush()
            kind = k
        run.append(t)
        i += w
    flush()
    return out


def write_stub(row, buf):
    name, lo, hi = row["name"], row["lo"], row["hi"]
    p2 = row["align"].bit_length() - 1
    out = [f"# {name}: 0x{lo:08X}..0x{hi:08X} of the base ELF's .{row['section']}, "
           f"for {row['tu']}; generated by tools/gen_stub_s.py, not tracked."]
    if row["section"] == "text":
        out += ["    .text", f"    .p2align {p2}", "    .set noreorder"]
        if not row["local"]:
            out.append(f"    .globl {name}")
        out += [f"    .type {name},@function", f"    .ent {name}", f"{name}:"]
        out += [f"    .word 0x{int.from_bytes(buf[i:i + 4], 'little'):08X}" for i in range(0, len(buf), 4)]
        out += [f"    .end {name}", f"    .size {name},.-{name}", "    .set reorder"]
    else:
        out += [f"    .section .{row['section']}", f"    .p2align {p2}"]
        if not row["local"]:
            out.append(f"    .globl {name}")
        out += [f"    .type {name},@object", f"{name}:"]
        out += data_lines(buf, lo)
        out.append(f"    .size {name},.-{name}")
    out.append("    .previous")
    return "\n".join(out) + "\n"


def write_if_changed(path, text):
    """Write text unless the file already holds it (ninja's restat)."""
    if path.exists() and path.read_text() == text:
        return False
    path.write_text(text)
    return True


# ----------------------------------------------------------------- check ----

def check(rows, built_path):
    from elftools.elf.elffile import ELFFile
    from elftools.elf.sections import SymbolTableSection
    with open(BASE_ELF, "rb") as fb, open(built_path, "rb") as fe:
        base, built = ELFFile(fb), ELFFile(fe)
        symtab = built.get_section_by_name(".symtab")
        syms = {}
        if isinstance(symtab, SymbolTableSection):
            for s in symtab.iter_symbols():
                syms.setdefault(s.name, []).append((s["st_value"], s["st_size"]))
        bad = 0
        for r in rows:
            want = section_bytes(base, r, "the base ELF")
            got = section_bytes(built, r, str(built_path))
            span = f"{r['name']} 0x{r['lo']:08X}..0x{r['hi']:08X} ({r['tu']})"
            if got != want:
                k = next(i for i in range(len(want)) if got[i] != want[i])
                print(f"gen_stub_s: DIFF {span}: first difference at 0x{r['lo'] + k:08X}")
                bad += 1
                continue
            if syms and (r["lo"], r["hi"] - r["lo"]) not in syms.get(r["name"], []):
                print(f"gen_stub_s: DIFF {span}: the bytes are equal but the symbol is at "
                      f"{', '.join(f'0x{a:08X} size {s}' for a, s in syms.get(r['name'], [])) or 'no address'}")
                bad += 1
                continue
            print(f"gen_stub_s: ok   {span}")
    print(f"gen_stub_s: {len(rows)} stubs, {bad} differ")
    return 1 if bad else 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--list", action="store_true", help="print the rows")
    g.add_argument("--check", type=Path, metavar="ELF", help="compare each row's range in a built ELF with the base")
    ap.add_argument("--stubs", type=Path, default=LIST, help=f"the list (default {LIST.relative_to(ROOT)})")
    ap.add_argument("--out-dir", type=Path, default=OUT_DIR)
    a = ap.parse_args()
    rows = parse_stubs(a.stubs)
    if a.list:
        for r in rows:
            extra = ((" local" if r["local"] else "")
                     + (f" align={r['align']}" if r["align"] != natural_align(r["lo"]) else "")
                     + (f" lines={r['lines']}" if r["lines"] else ""))
            print(f"{r['section']:<6} {r['name']} {r['lo']:08X} {r['hi']:08X} {r['tu']}{extra}")
        print(f"gen_stub_s: {len(rows)} stubs in {a.stubs}" + ("" if rows else " (idle)"), file=sys.stderr)
        return 0
    if a.check:
        return check(rows, a.check)
    from elftools.elf.elffile import ELFFile
    a.out_dir.mkdir(parents=True, exist_ok=True)
    wrote = write_if_changed(a.out_dir / HEADER, HEADER_TEXT)
    with open(BASE_ELF, "rb") as fh:
        elf = ELFFile(fh)
        for r in rows:
            wrote += write_if_changed(a.out_dir / f"{r['name']}.s", write_stub(r, section_bytes(elf, r, "the base ELF")))
    print(f"gen_stub_s: {len(rows)} stubs and {HEADER}, {wrote} written to {a.out_dir}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
