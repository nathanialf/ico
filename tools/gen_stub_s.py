#!/usr/bin/env python3
"""tools/gen_stub_s.py -- write the not-yet-matched functions as stubs from the base ELF.

During a target's campaign the functions whose C does not yet give the base's
bytes still have to sit at the base's addresses, so the byte gate passes at
every commit. Each one is listed in config/stubs.<slug>.txt (slug from
tools/ico_version.py) and its translation unit carries `INCLUDE_ASM(stem);`
where the function stands in the file. This tool writes build/stubs/<stem>.s
for every row from the user's own base ELF, as build/data/ is written by
tools/gen_data_c.py: nothing of the ROM is tracked (docs/LEGAL.md). It also
writes the macro's header, build/stubs/include_asm.h, every time it runs; the
tree tracks no copy of it, and tools/compile_c.sh searches build/stubs last,
so a TU that includes "include_asm.h" compiles only while stubs exist. With
the list empty the mechanism is idle.

The list, one row per stub, `#` starts a comment:

    <section> <name> <vma_lo> <vma_hi> <tu> [local] [align=N] [lines=N] [file=<stem>]

  section   text, rodata, data or sdata: the base ELF section the range
            lies in; lit4, rdlit or sdlit for a text row's constants (below)
  name      the symbol the stub defines (MAIN.MAP's name, or D_<VMA>)
  vma_lo/hi the range [lo, hi) in the base ELF, hex; a text row ends at the
            function's last instruction, not at the fill after it
  tu        the tracked C source whose INCLUDE_ASM(stem) includes the stub
            (ninja makes that object depend on build/stubs/<stem>.s)
  local     the name is file-local in the C (a static), so no .globl
  align=N   the stub's alignment in bytes; by default the largest power of
            two dividing vma_lo, at most 8 (ee-gcc's .p2align 3 per function
            and per rodata object)
  lines=N   the stubbed body spanned N source lines in the TU; nothing in
            the build reads it yet (the parser accepts it, --list prints it,
            --carve writes it)
  file=stem the stub's file is build/stubs/<stem>.s and the TU spells
            INCLUDE_ASM(stem), while the symbol stays <name>: two statics of
            one name in two TUs get a row each (default: stem = name; stems
            are unique, and a name is global in one row at most)

A literal row carries the anonymous constants a stubbed function brings
into its TU's data sections. gcc writes the string literals and constants a
function uses as $LC labels just before the function's code (in .rdata, or in
.sdata when they fit -G 8), and with -G 8 ee-as expands `li.s` of a constant
whose low half is not zero into a $gp load and appends the constant to the
TU's .lit4, and `li.d` into a register pair into a load of a constant it
appends to the TU's .rodata, each as it reads the instruction, in load order
and with no merging of equal values. A stub of raw words loads from the same
offsets but brings none of them, so every later constant of the TU would move
up. `lit4 <name> <lo> <hi> <tu>` (`rdlit` for .rodata, `sdlit` for .sdata),
with the name and file= of the function's text row in the same TU, gives the
range of the base ELF's section that function's own constants occupy (one
contiguous run per section, since each sits between the constants of the
functions before and after it); the stub file writes them as bytes of that
section after the function's text, so the TU's other constants keep their
places. A literal row takes no `local`; lit4 aligns to 4 as the assembler
does, rdlit and sdlit to align=N (default as for a data row, the largest
power of two dividing vma_lo, at most 8; gcc aligns its strings to 8 and its
jump tables to 16). A function has one row per run of its constants in a
section, usually one; a static inside the function (gcc's `name.N`) that
gcc wrote among them is part of the run.

`--literals` derives those rows, and --carve and --carve-all run it for the
rows they carve (unless --no-literals) while the functions are still C. Two
sides must agree. The object: the TU compiled on this tree with every
listed function of it in C (a carved one put back from --from for the
compile, the file restored after); every R_MIPS_LITERAL, R_MIPS_GPREL16 and
%lo relocation of a function's text names a place in .lit4, .rodata or
.sdata, and a place inside no named object is a constant: a float of the
assembler's .lit4 (4 bytes), a double of its li.d pool (8, loaded by ld and
never addressed), a jump table (its words relocated against .text), a string
(to its NUL) or a constant run (to the next place). The target: the row's
own words in the target ELF (--elf), scanned for the addresses they form,
`off($gp)` from the target's _gp (its .reginfo) and a lui's %hi carried over
the control flow into a %lo (tools/correlate_elf.py's hi_values). The
distinct places each side references in a section, in the order the function
first references them, are paired one to one (a name the TU only declares
takes its section from --syms, the last link); the size of each constant
comes from the object, and a string's NUL must fall at the same place in the
target. Constants that lie next to each other in the target, with fewer than
8 bytes of zero padding between them, form one row; align=N is written when
the object's section alignment allows more than the default (16 for a jump
table's run) or less.

Ownership follows the order gcc reads the TU. gcc writes a string or a
constant run once per TU, when it first expands a body that uses it, so the
first function in the object that references it owns it and a later stubbed
user needs no row; the assembler interns nothing (equal floats are two
words), so .lit4 and the li.d pool belong to the function whose text loads
them. A constant some function still in C emits needs no row either: the
tool compiles the TU a second time with the listed functions removed, and a
constant that compile still writes (an inline function's body is expanded
where it is defined, even with every caller stubbed) stays the C's. Three
cases print HAND and write nothing, because no row can place them: a
constant the stubbed owner shares with a later function still in C (gcc
writes it again before that function: measured, the stub's copy and gcc's
both land), a constant of an inline function that is stubbed (gcc writes it
where the function is defined, the stub stands at the end of the file), and
one the TU's data also references; a static inside the function that lives
in .data, .sbss or .bss is named the same way. A count or kind that differs
between the sides prints DISAGREE: the target's function is not the
object's, and its rows are measured by hand.

A text row is written as one function: `.set noreorder`, `.globl`,
`.type @function`, `.ent`, one `.word` per instruction, `.end`, `.size`. A
data row is a run of `.word`, `.half` and `.byte` as the address allows. The
words are absolute: there are no relocations, the stub is right only at its
own address, and the gate proves the layout. Each stub returns to the section
it was included from (`.previous`), so the compiler's own section state holds.

    tools/gen_stub_s.py                      write build/stubs/<stem>.s for every row
    tools/gen_stub_s.py --list               print the rows
    tools/gen_stub_s.py --check build/ico.syms.elf
        every row's bytes in the built ELF equal the base's at that range (and,
        when the ELF keeps its symbols, the stub's symbol sits at vma_lo with
        size vma_hi - vma_lo); the gate checks the bytes too, this names the stub
    tools/gen_stub_s.py --carve NAME         the TU's definition of a text row's
                                             function becomes INCLUDE_ASM(stem);
    tools/gen_stub_s.py --restore NAME [--from REV]
                                             the definition back from REV
                                             (default main, the seed)
    tools/gen_stub_s.py --carve-all | --restore-all [--from REV]
                                             the same for every text row
    tools/gen_stub_s.py --literals [NAME] [--dry-run] [--elf ELF] [--syms ELF]
                                             derive a text row's literal rows
                                             (every text row without NAME) and
                                             write them after it, replacing
                                             its old ones; --dry-run prints

NAME is a row's stem, or its name when one row carries it. Only a text
row's function is carved; its literal rows ride on the same INCLUDE_ASM line,
and --carve derives them first (above).
The carve works on the file's bytes, so an EUC-JP source keeps its encoding,
and restore reads REV's file with `git cat-file --filters`, which applies the
working-tree encoding (`git show` would give the UTF-8 that git stores).

The boundary of a definition: the scan follows comments, string and
character literals, preprocessor lines (with their continuations) and the
brace depth; a top-level item starts at its first code line, so a comment
above it is not part of it and stays; a function is an item whose first `{`
at depth 0 follows a `)` with no `=` before it, named by the identifier
before the item's first `(`, and it ends at the `}` that returns to depth 0,
which stands at column 0 (or on the definition's one line). The INCLUDE_ASM
line replaces exactly those lines, and the row gets `lines=N`, the number of
lines replaced, when it has none. When the file uses the name after the
definition and does not declare it before, the signature stays above the
INCLUDE_ASM line as a declaration, since a call with no declaration in scope
is an implicit `int name()` and compiles differently. The first carve in a
file adds `#include "include_asm.h"` after the last `#include` above the
first INCLUDE_ASM line (at the top of the file when there is none), and the
restore of the last one removes it. A file in tools/format_layout.py's
layout before the edit is put back into it after, so `format.sh --check`
holds while the stubs stand and a restore gives the file back byte for byte.

gcc 2.9 emits an `inline` function only after the whole file is read, after
every function defined in place and every file-scope asm (measured on
flyManager.c, whose INCLUDE_ASM at the end of the file still came before the
inline functions left in C), so its stub
cannot stand where the definition did: a carve of an inline function removes
the definition with the blank line after it and puts its INCLUDE_ASM line at
the end of the file, among the stubs there in address order. That places it
before every inline function the compiler still emits at the end, so the
ones the base has before it are carved too (stubcheck names a stub out of
place). An inline function the file uses after its definition, where gcc can
inline it, is refused: the users lose the inlined body. A restore puts the
definition back after the lines that preceded it in REV. A definition inside
`#if`/`#ifdef`, or in a `.c.inc` the TU includes, is refused, and so is a
name the file does not define (a function only the target has): those are
placed by hand.
"""

import argparse
import contextlib
import os
import re
from bisect import bisect_right
import subprocess
import sys
import tempfile
from collections import Counter
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
SECTIONS = ("text", "rodata", "data", "sdata", "lit4", "rdlit", "sdlit")
# a text row's constants: kind -> the base ELF section
LITERALS = {"lit4": ".lit4", "rdlit": ".rodata", "sdlit": ".sdata"}
INCLUDE_LINE = b'#include "include_asm.h"\n'

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
 *     INCLUDE_ASM(stem);
 *
 * at the place the function has in the file (the stem is the function's name
 * unless its row gives file=). tools/gen_stub_s.py writes
 * build/stubs/stem.s from the user's own base ELF, and the assembler
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
    rows, stems, lits, where = [], {}, [], f"{path.relative_to(ROOT) if path.is_relative_to(ROOT) else path}"
    for n, line in enumerate(path.read_text().splitlines(), 1):
        f = line.split("#", 1)[0].split()
        if not f:
            continue
        if len(f) < 5 or f[0] not in SECTIONS:
            fail(f"{where}:{n}: expected '<section> <name> <vma_lo> <vma_hi> <tu> [local] [align=N] [lines=N]"
                 f" [file=<stem>]' with section one of {', '.join(SECTIONS)}")
        sec, name, tu = f[0], f[1], f[4]
        if not re.fullmatch(r"[A-Za-z_][\w.]*", name):
            fail(f"{where}:{n}: '{name}' is not a symbol name")
        try:
            lo, hi = int(f[2], 16), int(f[3], 16)
        except ValueError:
            fail(f"{where}:{n}: vma_lo and vma_hi are hex addresses")
        if not lo < hi:
            fail(f"{where}:{n}: empty range")
        if sec in ("text", "lit4") and (lo % 4 or hi % 4):
            fail(f"{where}:{n}: a {sec} range starts and ends on a word")
        if not re.fullmatch(r"(ico2|sce)/\S+\.c", tu):
            fail(f"{where}:{n}: '{tu}' is not a C source under ico2/ or sce/")
        local, align, span, stem = False, natural_align(lo), None, name
        for tok in f[5:]:
            m = re.fullmatch(r"align=(\d+)", tok)
            k = re.fullmatch(r"lines=(\d+)", tok)
            st = re.fullmatch(r"file=(\w+)", tok)
            if tok == "local" and sec not in LITERALS:
                local = True
            elif m and sec != "lit4" and int(m.group(1)) in (1, 2, 4, 8, 16) and lo % int(m.group(1)) == 0:
                align = int(m.group(1))
            elif k and int(k.group(1)) > 0:
                span = int(k.group(1))
            elif st:
                stem = st.group(1)
            else:
                fail(f"{where}:{n}: bad token '{tok}' (local, align=N with N a power of two dividing vma_lo,"
                     " lines=N with N > 0, or file=<stem>; a literal row takes no local, a lit4 row no align=)")
        if sec in LITERALS:
            if sec == "lit4":
                align = 4
        elif stem in stems:
            fail(f"{where}:{n}: {stem} is listed twice (first at line {stems[stem]['line']});"
                 " two statics of one name take file=<stem>")
        row = dict(section=sec, name=name, lo=lo, hi=hi, tu=tu, local=local, align=align,
                   lines=span, stem=stem, line=n)
        if sec in LITERALS:
            lits.append(row)
        else:
            stems[stem] = row
        rows.append(row)
    for r in lits:
        t = stems.get(r["stem"])
        if t is None or t["section"] != "text" or t["name"] != r["name"] or t["tu"] != r["tu"]:
            fail(f"{where}:{r['line']}: the {r['section']} row for {r['stem']} has no text row of that name,"
                 " stem and TU")
    glob = {}
    for r in stems.values():
        if not r["local"]:
            if r["name"] in glob:
                fail(f"{where}:{r['line']}: {r['name']} is global in two rows (first at line {glob[r['name']]})")
            glob[r["name"]] = r["line"]
    by_addr = sorted(rows, key=lambda r: r["lo"])
    for a, b in zip(by_addr, by_addr[1:]):
        if b["lo"] < a["hi"]:
            fail(f"{where}:{b['line']}: {b['name']} overlaps {a['name']} (line {a['line']})")
    return rows


def stub_rows(rows):
    """{stem: [the text or data row, then its literal rows]}, in list order."""
    out = {}
    for r in rows:
        if r["section"] not in LITERALS:
            out[r["stem"]] = [r]
    for r in rows:
        if r["section"] in LITERALS:
            out[r["stem"]].append(r)
    return out


# ------------------------------------------------------------------- ELF ----

def section_bytes(elf, row, what):
    """The ELF's bytes [lo, hi) of the row's section, found by address."""
    lo, hi = row["lo"], row["hi"]
    want = LITERALS.get(row["section"], "." + row["section"])
    for s in elf.iter_sections():
        base, size = s["sh_addr"], s["sh_size"]
        if s["sh_type"] == "SHT_PROGBITS" and s["sh_flags"] & 2 and base <= lo and hi <= base + size:
            if s.name != want:
                fail(f"{row['name']}: 0x{lo:08X}..0x{hi:08X} lies in {what}'s {s.name}, not {want}")
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


def write_stub(rows, bufs):
    """The stub file of one stem: its text or data row, then its constants."""
    row, buf = rows[0], bufs[0]
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
    for r, b in zip(rows[1:], bufs[1:]):
        # the constants the function's code brought into the section
        sec = LITERALS[r["section"]]
        out += [f"# {name}'s constants: 0x{r['lo']:08X}..0x{r['hi']:08X} of the base ELF's {sec}.",
                f"    .section {sec}", f"    .p2align {r['align'].bit_length() - 1}"]
        out += data_lines(b, r["lo"])
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
            span = (f"{r['name']}{' ' + r['section'] if r['section'] in LITERALS else ''} 0x{r['lo']:08X}..0x{r['hi']:08X}"
                    f" ({r['tu']}{'' if r['stem'] == r['name'] else ', file=' + r['stem']})")
            if got != want:
                k = next(i for i in range(len(want)) if got[i] != want[i])
                print(f"gen_stub_s: DIFF {span}: first difference at 0x{r['lo'] + k:08X}")
                bad += 1
                continue
            if syms and r["section"] not in LITERALS and (r["lo"], r["hi"] - r["lo"]) not in syms.get(r["name"], []):
                print(f"gen_stub_s: DIFF {span}: the bytes are equal but the symbol is at "
                      f"{', '.join(f'0x{a:08X} size {s}' for a, s in syms.get(r['name'], [])) or 'no address'}")
                bad += 1
                continue
            print(f"gen_stub_s: ok   {span}")
    print(f"gen_stub_s: {len(rows)} stubs, {bad} differ")
    return 1 if bad else 0


# ----------------------------------------------------------------- carve ----

PP_IF = re.compile(rb"\s*#\s*(if|ifdef|ifndef|endif)\b")
INCLUDE = re.compile(rb"\s*#\s*include\b")
INLINE = re.compile(rb"\binline\b|\b__inline")


def asm_line(stem):
    return f"INCLUDE_ASM({stem});\n".encode()


def scan_code(lines):
    """Per line (bytes): its code with comments and string and character
    literals blanked to spaces (same length, so a column in it is a column
    of the line), whether it is a preprocessor line (continuations included),
    and the #if depth at its start."""
    out, blk, cont, cond = [], False, False, 0
    for raw in lines:
        line = raw.rstrip(b"\n")
        pp = cont or (not blk and line.lstrip().startswith(b"#"))
        at, n, i = cond, len(line), 0
        code = bytearray(b" " * n)
        while i < n:
            if blk:
                j = line.find(b"*/", i)
                if j < 0:
                    break
                blk, i = False, j + 2
            elif line.startswith(b"/*", i):
                blk, i = True, i + 2
            elif line.startswith(b"//", i):
                break
            elif line[i] in b"\"'":
                q, i = line[i], i + 1
                while i < n and line[i] != q:
                    i += 2 if line[i] == 0x5C else 1
                i += 1
            else:
                code[i] = line[i]
                i += 1
        if pp and not cont:
            m = PP_IF.match(code)
            if m:
                cond += -1 if m.group(1) == b"endif" else 1
        cont = pp and line.endswith(b"\\")
        out.append((bytes(code), pp, at))
    return out


def definitions(lines):
    """Every function definition at file scope, in file order, as a dict:
    name, first and last line (0-based), the #if depth, the signature's code,
    and the line and column of its `{`. An item starts at its first code line
    at depth 0; it is a function when its first `{` at depth 0 follows a `)`
    and the text before it has no `=`, and it ends at the `}` that returns to
    depth 0."""
    defs, depth, item, text, func = [], 0, None, bytearray(), None
    for k, (code, pp, cond) in enumerate(scan_code(lines)):
        if pp:
            continue
        for col, ch in enumerate(code):
            c = bytes([ch])
            if depth == 0 and item is None:
                if c.isspace():
                    continue
                item, at, text, func = k, cond, bytearray(), None
            if c == b"{":
                if depth == 0:
                    sig = bytes(text).strip()
                    func = sig if sig.endswith(b")") and b"=" not in sig else None
                    brace = (k, col)
                depth += 1
            elif c == b"}":
                depth -= 1
                if depth == 0 and func is not None:
                    m = re.search(rb"(\w+)\s*\(", func)
                    defs.append(dict(name=m.group(1).decode() if m else "", s=item, e=k, cond=at,
                                     sig=func, brace=brace, inline=bool(INLINE.search(func))))
                    item = func = None
                    continue
            elif c == b";" and depth == 0:
                item = None
                continue
            if depth == 0:
                text += c
    return defs


def find_definition(lines, name, where):
    found = [d for d in definitions(lines) if d["name"] == name]
    if not found:
        inc = [m.group(1).decode() for m in (re.match(rb'\s*#\s*include\s+"([^"]+\.inc)"', l) for l in lines) if m]
        there = [i for i in inc if (ROOT / where).parent.joinpath(i).exists() and any(
            d["name"] == name for d in definitions((ROOT / where).parent.joinpath(i).read_bytes()
                                                   .splitlines(keepends=True)))]
        fail(f"{where}: no definition of {name} at file scope"
             + (f"; it is in {', '.join(there)}, which the TU includes: carve it there by hand" if there else ""))
    top = [d for d in found if d["cond"] == 0]
    if not top:
        fail(f"{where}:{found[0]['s'] + 1}: {name} is defined inside #if/#ifdef; carve it by hand,"
             " since the stub would not follow the condition")
    if len(top) > 1:
        fail(f"{where}: {name} is defined {len(top)} times (lines {', '.join(str(d['s'] + 1) for d in top)})")
    d = top[0]
    if d["e"] > d["s"] and not lines[d["e"]].startswith(b"}"):
        fail(f"{where}:{d['e'] + 1}: {name}'s closing brace is not at column 0")
    return d


def prototype(lines, d):
    """The definition's signature as a declaration: its lines up to the `{`,
    with `;` after the last `)` (a comment after it stays after it)."""
    k, col = d["brace"]
    sig = lines[d["s"]:k] + ([lines[k][:col]] if lines[k][:col].strip() else [])
    code = scan_code(sig)
    j = max(i for i, (c, _, _) in enumerate(code) if b")" in c)
    p = code[j][0].rindex(b")") + 1
    sig[j] = sig[j][:p] + b";" + sig[j][p:]
    return [l.rstrip() + b"\n" for l in sig]


def mentions(lines, name, start, end=None, macros=True):
    """Whether code in lines[start:end] names `name` (with macros, a macro
    body counts: its expansion further on is a use)."""
    pat = re.compile(rb"\b" + re.escape(name.encode()) + rb"\b")
    return any((macros or not pp) and pat.search(c) for c, pp, _ in scan_code(lines[start:end]))


def place_header(lines):
    """#include "include_asm.h" after the last #include above the first
    INCLUDE_ASM line (at the top, with a blank line after it, when there is
    none); removed when no INCLUDE_ASM line is left."""
    asm = [k for k, l in enumerate(lines) if l.startswith(b"INCLUDE_ASM(")]
    have = [k for k, l in enumerate(lines) if l == INCLUDE_LINE]
    if asm and have and have[0] < asm[0] and len(have) == 1:
        return lines
    for k in reversed(have):
        top = k == 0 and k + 1 < len(lines) and lines[k + 1] == b"\n"
        del lines[k:k + 1 + top]
    if not asm:
        return lines
    first = next(k for k, l in enumerate(lines) if l.startswith(b"INCLUDE_ASM("))
    info = scan_code(lines)
    inc = [k for k in range(first) if info[k][1] and INCLUDE.match(lines[k])]
    if inc:
        lines.insert(inc[-1] + 1, INCLUDE_LINE)
    else:
        lines[0:0] = [INCLUDE_LINE, b"\n"]
    return lines


def carve(lines, row, where, lo_of):
    """Replace row's definition with its INCLUDE_ASM line; the lines it
    spanned. lo_of gives each stem's vma_lo, to order the stubs of inline
    functions at the end of the file."""
    d = find_definition(lines, row["name"], where)
    s, e = d["s"], d["e"]
    if not d["inline"]:
        # a later use with no declaration above would make the call an
        # implicit `int name()`, which compiles differently: the signature
        # stays as a declaration
        keep = []
        if mentions(lines, row["name"], e + 1) and not mentions(lines, row["name"], 0, s, macros=False):
            keep = prototype(lines, d) + [b"\n"]
        lines[s:e + 1] = keep + [asm_line(row["stem"])]
    else:
        # gcc 2.9 compiles an inline function it must emit after the whole
        # file is read, after every other definition and every file-scope
        # asm; its stub goes at the end of the file, with the other stubs
        # there in address order. A use after the definition is inlined
        # there, which a stub cannot give.
        if mentions(lines, row["name"], e + 1):
            fail(f"{where}:{s + 1}: inline {row['name']} is used after its definition, where gcc may"
                 " inline it; carve or restore those users first")
        if e + 1 < len(lines) and lines[e + 1] == b"\n":
            del lines[s:e + 2]
        elif s > 0 and lines[s - 1] == b"\n":
            del lines[s - 1:e + 1]
        else:
            del lines[s:e + 1]
        if lines and not lines[-1].endswith(b"\n"):
            lines[-1] += b"\n"
        k = len(lines)
        while k > 0 and (lines[k - 1] == b"\n" or lines[k - 1].startswith(b"INCLUDE_ASM(")):
            k -= 1
        later = [j for j in range(k, len(lines)) if lines[j].startswith(b"INCLUDE_ASM(")
                 and lo_of.get(lines[j][12:].split(b")")[0].decode(), 0) > row["lo"]]
        if later:
            lines[later[0]:later[0]] = [asm_line(row["stem"]), b"\n"]
        else:
            lines += [b"\n", asm_line(row["stem"])]
        print(f"gen_stub_s: {row['name']} is inline: INCLUDE_ASM at the end of {where}. Its stub is emitted"
              " after everything the file defines in place and before every inline function the compiler"
              " still emits there, so those that come before it in the base are carved too"
              " (stubcheck names a stub out of place)")
    place_header(lines)
    return e - s + 1


def restore(lines, rev_lines, row, where, rev):
    """Put row's definition back from rev_lines in place of its INCLUDE_ASM
    line (and the declaration carve left above it)."""
    at = [k for k, l in enumerate(lines) if l == asm_line(row["stem"])]
    if len(at) != 1:
        fail(f"{where}: {'no' if not at else 'more than one'} INCLUDE_ASM({row['stem']}); line")
    d = find_definition(rev_lines, row["name"], f"{rev}:{row['tu']}")
    s, e = d["s"], d["e"]
    body = rev_lines[s:e + 1]
    k = at[0]
    if not d["inline"]:
        keep = prototype(rev_lines, d) + [b"\n"]
        if lines[k - len(keep):k] == keep:
            k -= len(keep)
        lines[k:at[0] + 1] = body
    else:
        del lines[k - 1 if k > 0 and lines[k - 1] == b"\n" else k:k + 1]
        # after the lines that preceded it in rev, as many as it takes to
        # name one place, blank lines aside (the layout pass settles those)
        before = [l for l in rev_lines[:s] if l.strip()]
        solid = [j for j, l in enumerate(lines) if l.strip()]
        text = [lines[j] for j in solid]
        for n in range(1, len(before) + 1):
            ctx = before[-n:]
            hits = [solid[i + n - 1] for i in range(len(text) - n + 1) if text[i:i + n] == ctx]
            if len(hits) <= 1:
                break
        if len(hits) != 1:
            fail(f"{where}: the lines before inline {row['name']} in {rev} are not found here"
                 " as they stand there; put it back by hand")
        gap = [b"\n"] if s > 0 and rev_lines[s - 1] == b"\n" else []
        lines[hits[0] + 1:hits[0] + 1] = gap + body + [b"\n"]
    place_header(lines)


def layout(lines):
    """tools/format_layout.py's top-level blank-line layout of lines, bytes
    kept as they are (it reads and writes with surrogateescape)."""
    from format_layout import process
    text = process(b"".join(lines).decode("utf-8", "surrogateescape"))
    return text.encode("utf-8", "surrogateescape").splitlines(keepends=True)


def text_row(rows, key):
    """The text row whose stem is key, else the one text row named key."""
    t = [r for r in rows if r["section"] == "text"]
    hit = [r for r in t if r["stem"] == key] or [r for r in t if r["name"] == key]
    if not hit:
        other = [r for r in rows if key in (r["stem"], r["name"])]
        fail(f"{key}: {'only a text row is carved' if other else 'no row of that stem or name'}")
    if len(hit) > 1:
        fail(f"{key}: {len(hit)} rows carry the name; give the stem ("
             + ", ".join(r["stem"] for r in hit) + ")")
    return hit[0]


def rev_file(rev, tu):
    """tu at rev with the working-tree filters (EUC-JP files stay EUC-JP)."""
    p = subprocess.run(["git", "cat-file", "--filters", f"{rev}:{tu}"], cwd=ROOT, capture_output=True)
    if p.returncode:
        fail(f"{rev}:{tu}: {p.stderr.decode(errors='replace').strip()}")
    return p.stdout.splitlines(keepends=True)


def set_lines(path, spans):
    """Write lines=N into the rows (by list line) that have none."""
    text = path.read_bytes().splitlines(keepends=True)
    for n, span in spans.items():
        line = text[n - 1].rstrip(b"\n")
        code, sep, cmt = line.partition(b"#")
        ws = code[len(code.rstrip()):] if sep else b""
        text[n - 1] = code.rstrip() + f" lines={span}".encode() + ws + sep + cmt + b"\n"
    path.write_bytes(b"".join(text))


def carve_rows(rows, todo, list_path, back, rev):
    """Carve (or with back, restore) each row of todo, one write per TU."""
    by_tu, errors, done, skipped, spans = {}, [], 0, 0, {}
    lo_of = {r["stem"]: r["lo"] for r in rows if r["section"] == "text"}
    for r in todo:
        by_tu.setdefault(r["tu"], []).append(r)
    for tu, rs in by_tu.items():
        path = ROOT / tu
        lines = path.read_bytes().splitlines(keepends=True)
        old = list(lines)
        # a file in the layout format.sh keeps stays in it (a declaration
        # carve leaves can join the block above it); restore gives it back
        clean = layout(lines) == lines
        rev_lines = rev_file(rev, tu) if back else None
        if back:
            # an inline function goes back after the others, so the lines
            # before it in rev are in place first
            at = {d["name"]: (d["inline"], d["s"] if d["inline"] else 0) for d in definitions(rev_lines)}
            rs = sorted(rs, key=lambda r: at.get(r["name"], (False, 0)))
        else:
            # the last definition first, so the users of an inline function
            # that are carved too are gone before it is
            at = {d["name"]: d["s"] for d in definitions(lines)}
            rs = sorted(rs, key=lambda r: -at.get(r["name"], -1))
        for r in rs:
            present = asm_line(r["stem"]) in lines
            if present != back:
                skipped += 1
                continue
            try:
                if back:
                    restore(lines, rev_lines, r, tu, rev)
                else:
                    n = carve(lines, r, tu, lo_of)
                    if not r["lines"]:
                        spans[r["line"]] = n
                done += 1
            except SystemExit as ex:
                errors.append(str(ex))
        if clean:
            lines = layout(lines)
        if lines != old:
            path.write_bytes(b"".join(lines))
    if spans:
        set_lines(list_path, spans)
    for m in errors:
        print(m, file=sys.stderr)
    verb = "restored" if back else "carved"
    print(f"gen_stub_s: {done} {verb}, {skipped} already {verb}, {len(errors)} refused"
          + (f", lines=N written to {len(spans)} rows" if spans else ""))
    return 1 if errors else 0


# -------------------------------------------------------------- literals ----
#
# A text row's literal rows, derived from two sides that must agree. The
# object side: the TU compiled on this tree with every listed function of it
# in C (a carved one restored from --from for the compile and put back after),
# read with its relocations. Every R_MIPS_LITERAL, R_MIPS_GPREL16 or %lo
# relocation of a function's text names a place in .lit4, .rodata or .sdata;
# a place inside no named symbol of the object is a literal (gcc's $LC strings
# and constants and its jump tables, the assembler's li.s and li.d pools),
# anything else a variable. The target side: the row's own words in the target
# ELF, scanned for the addresses they form, `off($gp)` from the target's _gp
# (its .reginfo) and a lui's %hi carried over the control flow
# (tools/correlate_elf.py's register flow) into a %lo. The distinct places
# each side references in a section, in the order the function first
# references them, are paired one to one; a count that differs between the
# sides, a place of a kind the other side does not have, or a string whose
# NUL is elsewhere in the target is a disagreement, and the function gets no
# literal rows until it is settled by hand.

LIT_CLASS = {".lit4": "lit4", ".rodata": "rdlit", ".sdata": "sdlit"}
FSTATIC = re.compile(r"\.\d+$")      # gcc's name for a static inside a function
LOAD8 = {0x37}                        # ld
LOAD4 = {0x23, 0x31}                  # lw, lwc1


def sext16(v):
    return v - 0x10000 if v & 0x8000 else v


class ObjectRefs:
    """A compiled TU: its functions (text order), and per function the
    places each references in .lit4, .rodata and .sdata, with what each
    literal is (kind, size) and which function owns it."""

    def __init__(self, obj, sec_of_name):
        from elftools.elf.elffile import ELFFile
        from elftools.elf.relocation import RelocationSection
        from elftools.elf.sections import SymbolTableSection
        with open(obj, "rb") as fh:
            elf = ELFFile(fh)
            secs = list(elf.iter_sections())
            names = [s.name for s in secs]
            reginfo = elf.get_section_by_name(".reginfo")
            gp0 = int.from_bytes(reginfo.data()[20:24], "little") if reginfo else 0
            symtab = next(s for s in secs if isinstance(s, SymbolTableSection))
            syms = list(symtab.iter_symbols())
            self.data = {s.name: s.data() for s in secs if s.name in LIT_CLASS and s["sh_type"] == "SHT_PROGBITS"}
            self.align = {s.name: s["sh_addralign"] for s in secs if s.name in LIT_CLASS}
            text = names.index(".text")
            words = secs[text].data()
            self.funcs = sorted((s["st_value"], s["st_size"], s.name) for s in syms
                                if s["st_info"]["type"] == "STT_FUNC" and s["st_shndx"] == text)
            # named objects per section: (lo, hi, name)
            self.named = {}
            for s in syms:
                if (isinstance(s["st_shndx"], int) and s.name and s["st_info"]["type"] != "STT_SECTION"
                        and s["st_shndx"] != text):
                    self.named.setdefault(names[s["st_shndx"]], []).append(
                        (s["st_value"], s["st_value"] + max(s["st_size"], 1), s.name))
            # every place any relocation names in the three sections, and
            # where each is referenced from
            self.starts = {n: set() for n in LIT_CLASS}
            self.from_data = set()
            self.jtbl = {}
            uses = []                  # (text offset, section or None, offset or symbol, opcode)
            for rs in secs:
                if not isinstance(rs, RelocationSection):
                    continue
                into = names[rs["sh_info"]]
                hi = {}
                for r in rs.iter_relocations():
                    t = r["r_info_type"]
                    sym = syms[r["r_info_sym"]]
                    shn = sym["st_shndx"]
                    tsec = names[shn] if isinstance(shn, int) else None
                    off = r["r_offset"]
                    if into == ".text":
                        w = int.from_bytes(words[off:off + 4], "little")
                        if t == 5:                      # R_MIPS_HI16
                            hi[r["r_info_sym"]] = w & 0xFFFF
                            continue
                        if t not in (6, 7, 8):          # LO16, GPREL16, LITERAL
                            continue
                        # the in-place addend: %hi and %lo together, or a
                        # gp-relative offset (from the object's gp0 for a
                        # section symbol, as the assembler writes it)
                        if t == 6:
                            a = (hi.get(r["r_info_sym"], 0) << 16) + sext16(w & 0xFFFF)
                        else:
                            a = sext16(w & 0xFFFF)
                        if sym["st_info"]["type"] == "STT_SECTION":
                            a += gp0 if t != 6 else 0
                            if tsec in LIT_CLASS:
                                self.starts[tsec].add(a)
                                uses.append((off, tsec, a, w >> 26))
                            elif tsec:
                                uses.append((off, tsec, a, w >> 26))
                        elif sym.name:
                            sec = tsec if tsec else sec_of_name.get(sym.name)
                            if sec in LIT_CLASS or FSTATIC.search(sym.name):
                                uses.append((off, sec, (sym.name, a), w >> 26))
                    elif tsec == ".text" and into in LIT_CLASS and t == 2:
                        self.jtbl.setdefault(into, set()).add(off)
                    elif tsec in LIT_CLASS and t == 2:
                        if sym["st_info"]["type"] == "STT_SECTION":
                            a = int.from_bytes(secs[rs["sh_info"]].data()[off:off + 4], "little")
                            self.starts[tsec].add(a)
                            self.from_data.add((tsec, a))
        for sec, lst in self.named.items():
            for lo, _, _ in lst:
                if sec in self.starts:
                    self.starts[sec].add(lo)
        # each use, attributed to its function, and named when it falls in a
        # named object
        starts = [v for v, _, _ in self.funcs]
        self.refs = {n: [] for _, _, n in self.funcs}
        self.elsewhere = {}
        self.users = {}
        self.ops = {}
        for off, sec, what, op in sorted(uses):
            k = bisect_right(starts, off) - 1
            if k < 0:
                continue
            fn = self.funcs[k][2]
            if isinstance(what, int):
                hit = [(lo, n) for lo, hi_, n in self.named.get(sec, []) if lo <= what < hi_]
                key = (sec, hit[0][1], what - hit[0][0]) if hit else (sec, None, what)
            else:
                key = (sec,) + what
            if key[1] and FSTATIC.search(key[1]):
                # a static inside a function: gcc writes it while compiling
                # that function, among its constants
                u = self.users.setdefault((sec, key[1]), [])
                if fn not in u:
                    u.append(fn)
            if sec not in LIT_CLASS:
                if key[1] and FSTATIC.search(key[1]) and (sec, key[1]) not in self.elsewhere.setdefault(fn, []):
                    self.elsewhere[fn].append((sec, key[1]))
                continue
            if key not in self.refs[fn]:
                self.refs[fn].append(key)
            if key[1] is None:
                self.users.setdefault(key, [])
                if fn not in self.users[key]:
                    self.users[key].append(fn)
                self.ops.setdefault(key, set()).add(op)

    def literal(self, key):
        """(kind, size) of a literal place."""
        sec, _, a = key
        data = self.data.get(sec, b"")
        if sec == ".lit4":
            return "float", 4
        jt = self.jtbl.get(sec, set())
        if a in jt:
            n = 0
            while a + 4 * n in jt and (n == 0 or a + 4 * n not in self.starts[sec]):
                n += 1
            return "jtbl", 4 * n
        nxt = min([b for b in self.starts[sec] if b > a] + [len(data)])
        ext = data[a:nxt]
        # loaded and never addressed: the load's width (the assembler's li.d
        # pool, an ld; a word, an lw); addressed: a string to its NUL, or
        # gcc's constant run to the next place
        ops = self.ops.get(key, set())
        if ops and ops <= LOAD8:
            return "double", 8
        if ops and ops <= LOAD4:
            return "word", 4
        z = ext.find(b"\0")
        if z >= 0 and not ext[z:].strip(b"\0"):
            return "string", z + 1
        body = len(ext.rstrip(b"\0"))
        return "data", max(4, (body + 3) // 4 * 4)


class TargetRefs:
    """The addresses a stretch of target words forms in .lit4, .rodata and
    .sdata, in first-reference order per section."""

    def __init__(self, elf_path):
        from elftools.elf.elffile import ELFFile
        self.secs = []
        with open(elf_path, "rb") as fh:
            elf = ELFFile(fh)
            for s in elf.iter_sections():
                if s["sh_flags"] & 2 and s["sh_size"]:
                    self.secs.append((s["sh_addr"], s["sh_addr"] + s["sh_size"], s.name,
                                      s.data() if s["sh_type"] == "SHT_PROGBITS" else b""))
            ri = elf.get_section_by_name(".reginfo")
            self.gp = int.from_bytes(ri.data()[20:24], "little")

    def section(self, a):
        for lo, hi, name, data in self.secs:
            if lo <= a < hi:
                return name, data[a - lo:]
        return None, b""

    def words(self, lo, hi):
        name, data = self.section(lo)
        return [int.from_bytes(data[i:i + 4], "little") for i in range(0, hi - lo, 4)]

    def refs(self, lo, hi):
        """({section: [address, ...]}, [(index, addresses) where a %lo has
        more than one %hi reaching it])."""
        from correlate_elf import LO_OPS, _op, _rs, hi_values
        words = self.words(lo, hi)
        out, amb = {n: [] for n in LIT_CLASS}, []
        for i, (w, his) in enumerate(zip(words, hi_values(words))):
            if _op(w) not in LO_OPS:
                continue
            base = _rs(w)
            if base == 28:
                cand = {self.gp + sext16(w & 0xFFFF)}
            elif his.get(base):
                cand = {((h << 16) + sext16(w & 0xFFFF)) & 0xFFFFFFFF for h in his[base]}
            else:
                continue
            got = {a for a in cand if self.section(a)[0] in LIT_CLASS}
            if len(got) > 1:
                amb.append((i, sorted(got)))
            for a in sorted(got):
                lst = out[self.section(a)[0]]
                if a not in lst:
                    lst.append(a)
        return out, amb


SYMS_ELF = ROOT / "build/ico.syms.elf"
PLURAL = {"float": "floats", "double": "doubles", "string": "strings", "jtbl": "jump tables",
          "word": "words", "data": "data runs", "static": "statics"}


def symbol_sections(path):
    """{name: section} of a linked ELF's symbols: the section of a symbol a
    TU uses but does not define."""
    from elftools.elf.elffile import ELFFile
    if not path.exists():
        fail(f"{path}: no such ELF; --literals reads the section of each name a TU uses from a link"
             " (build first, or give --syms)")
    with open(path, "rb") as fh:
        elf = ELFFile(fh)
        secs = list(elf.iter_sections())
        tab = elf.get_section_by_name(".symtab")
        out = {}
        for s in tab.iter_symbols() if tab else []:
            if not s.name:
                continue
            if isinstance(s["st_shndx"], int):
                out[s.name] = secs[s["st_shndx"]].name
            elif s["st_shndx"] == "SHN_ABS":
                # a label the link script binds (a D_<VMA> inside a data
                # member): its section by address
                v = s["st_value"]
                hit = [x.name for x in secs if x["sh_flags"] & 2 and x["sh_addr"] <= v < x["sh_addr"] + x["sh_size"]]
                if hit:
                    out[s.name] = hit[0]
        return out


def compile_lines(tu, lines, out):
    """tu compiled as lines (written in place for the compile, so the
    compiler sees the file's own name and directory, and put back after)."""
    from match_check import compile_tu
    path = ROOT / tu
    orig = path.read_bytes()
    if b"".join(lines) == orig:
        return compile_tu(tu, out)
    try:
        path.write_bytes(b"".join(lines))
        return compile_tu(tu, out)
    finally:
        path.write_bytes(orig)


def whole_lines(tu, rows_tu, rev):
    """The TU with every listed function of it in C: a carved one is put
    back from rev."""
    lines = (ROOT / tu).read_bytes().splitlines(keepends=True)
    carved = [r for r in rows_tu if asm_line(r["stem"]) in lines]
    if not carved:
        return lines
    rev_lines = rev_file(rev, tu)
    at = {d["name"]: (d["inline"], d["s"] if d["inline"] else 0) for d in definitions(rev_lines)}
    for r in sorted(carved, key=lambda r: at.get(r["name"], (False, 0))):
        restore(lines, rev_lines, r, tu, rev)
    return lines


def without_lines(whole, rows_tu, tu):
    """The TU with every listed function's definition gone (a declaration
    kept where carve keeps one), to see which constants the rest of the C
    still emits. A definition carve refuses stays."""
    lines = list(whole)
    lo_of = {r["stem"]: r["lo"] for r in rows_tu}
    at = {d["name"]: d["s"] for d in definitions(lines)}
    for r in sorted(rows_tu, key=lambda r: -at.get(r["name"], -1)):
        try:
            with open(os.devnull, "w") as quiet, contextlib.redirect_stdout(quiet):
                carve(lines, r, tu, lo_of)
        except SystemExit:
            pass
    return [l for l in lines if not l.startswith(b"INCLUDE_ASM(") and l != INCLUDE_LINE]


def still_emits(obj, sec, kind, content):
    """Whether obj's section holds content as a constant of its own: at an
    item's start (offset 0, or after a NUL for a string, on a word for a
    constant run) and inside no named object. The object need not reference
    it: an inline function nobody calls still has its strings written."""
    data = obj.data.get(sec, b"")
    o = data.find(content)
    while o >= 0:
        start = o == 0 or (data[o - 1] == 0 if kind == "string" else o % 4 == 0)
        if start and not any(lo <= o < hi for lo, hi, _ in obj.named.get(sec, [])):
            return True
        o = data.find(content, o + 1)
    return False


def describe(obj, key):
    sec, name, a = key
    if name is not None:
        return f"{name}{'+' + str(a) if a else ''}"
    kind, size = obj.literal(key)
    return f"{kind}({size}) at {sec}+0x{a:X}"


def derive_tu(tu, rows_tu, target, sec_of_name, rev):
    """{stem: result} for the TU's text rows: result has `status` (none,
    ok, hand, absent or disagree), `rows` (the literal rows) and `notes`."""
    src_lines = whole_lines(tu, rows_tu, rev)
    with tempfile.TemporaryDirectory(prefix="gen_stub_s.") as tmp:
        obj = ObjectRefs(compile_lines(tu, src_lines, Path(tmp) / "whole"), sec_of_name)
        # gcc writes a string or constant run when it first expands a body
        # that uses it, and an inline function's body is expanded where it is
        # defined even when every user is a stub: what the C still emits
        # with the listed functions gone needs no row
        rest = None
        if any(obj.literal(k)[0] in ("string", "data") for r in rows_tu for k in obj.refs.get(r["name"], [])
               if k[1] is None):
            rest = ObjectRefs(compile_lines(tu, without_lines(src_lines, rows_tu, tu), Path(tmp) / "without"),
                              sec_of_name)
    stubbed = {r["name"] for r in rows_tu}
    inline = {d["name"] for d in definitions(src_lines) if d["inline"]}
    out = {}
    for row in rows_tu:
        name, notes, hand, lits = row["name"], [], [], []
        if name not in obj.refs:
            out[row["stem"]] = dict(status="absent", rows=[], notes=[f"{tu} compiles no function {name}"])
            continue
        tgt, amb = target.refs(row["lo"], row["hi"])
        for i, adrs in amb:
            notes.append(f"ambiguous %hi at 0x{row['lo'] + 4 * i:08X}: {', '.join(f'0x{a:08X}' for a in adrs)}")
        mine, seen = 0, set()
        for sec_, n_ in obj.elsewhere.get(name, []):
            if obj.users[sec_, n_][0] == name:
                hand.append(f"{n_}, a static inside {name}, is in {sec_}, which no literal row carries; it"
                            " goes with the function, so the TU's later data there moves")
        for sec in LIT_CLASS:
            keys = [k for k in obj.refs[name] if k[0] == sec]
            mine += sum(1 for k in keys if k[1] is None and obj.users[k][0] == name)
            if len(keys) != len(tgt[sec]):
                ours = ", ".join(describe(obj, k) for k in keys) or "none"
                theirs = ", ".join(f"0x{a:08X}" for a in tgt[sec]) or "none"
                notes.append(f"count mismatch in {sec}: the object references {len(keys)} ({ours}),"
                             f" the target {len(tgt[sec])} ({theirs})")
                continue
            for k, addr in zip(keys, tgt[sec]):
                if k[1] is not None:
                    if FSTATIC.search(k[1]) and obj.users[sec, k[1]][0] == name and k[1] not in seen:
                        # the function's own static: the target's object
                        # around this place, the size the object gives it
                        seen.add(k[1])
                        lo, hi, _ = next(x for x in obj.named[sec] if x[2] == k[1])
                        lits.append((LIT_CLASS[sec], addr - k[2], hi - lo, "static", sec))
                    continue
                users = obj.users[k]
                if users[0] != name:
                    continue          # the owner's literal: its row, or its C
                kind, size = obj.literal(k)
                later = [u for u in users[1:] if u not in stubbed]
                if later:
                    hand.append(f"{describe(obj, k)} is used again by {', '.join(later)}, still in C,"
                                " where gcc emits it again once this function is a stub")
                elif rest and kind in ("string", "data") and still_emits(rest, sec, kind,
                                                                     obj.data[sec][k[2]:k[2] + size]):
                    continue          # the C emits it still, where an inline function is defined
                if (sec, k[2]) in obj.from_data:
                    hand.append(f"{describe(obj, k)} is also referenced from the TU's data, whose"
                                " initializer may emit it before this function")
                if name in inline and kind not in ("float", "double", "jtbl"):
                    hand.append(f"{describe(obj, k)}: {name} is inline; gcc emits its constants where it is"
                                " defined and its stub stands at the end of the file")
                _, data = target.section(addr)
                if kind == "string":
                    z = data.find(b"\0", 0, max(size, 4096))
                    if z != size - 1:
                        notes.append(f"{describe(obj, k)}: the target's string at 0x{addr:08X} has its NUL at"
                                     f" +{z} where the object's has it at +{size - 1}")
                elif kind == "jtbl":
                    tx = [t for t in target.secs if t[2] == ".text"][0]
                    ws = [int.from_bytes(data[i:i + 4], "little") for i in range(0, size, 4)]
                    if not all(tx[0] <= w < tx[1] for w in ws):
                        notes.append(f"{describe(obj, k)}: the target's words at 0x{addr:08X} are not all"
                                     " addresses in .text")
                elif kind == "double" and addr % 8:
                    notes.append(f"{describe(obj, k)}: the target's address 0x{addr:08X} is not 8-aligned")
                lits.append((LIT_CLASS[sec], addr, size, kind, sec))
        if notes:
            out[row["stem"]] = dict(status="disagree", rows=[], notes=notes, own=mine)
            continue
        out[row["stem"]] = dict(status="hand" if hand else "ok" if lits else "none", notes=hand,
                                rows=literal_rows(row, lits, target, obj), own=mine)
    return out


def literal_rows(row, lits, target, obj):
    """The literals as rows: one per run of a section's literals that lie
    next to each other in the target (with at most the alignment padding of
    the next one between them: fewer than 8 zero bytes)."""
    rows = []
    for cls, sec in (("lit4", ".lit4"), ("rdlit", ".rodata"), ("sdlit", ".sdata")):
        mine = sorted((a, a + n, k) for c, a, n, k, _ in lits if c == cls)
        runs = []
        for lo, hi, k in mine:
            if runs:
                plo, phi, ks = runs[-1]
                gap = target.section(phi)[1][:max(lo - phi, 0)]
                if lo <= phi or (lo - phi < 8 and not gap.strip(b"\0")):
                    runs[-1] = (plo, max(phi, hi), ks + [k])
                    continue
            runs.append((lo, hi, [k]))
        for lo, hi, ks in runs:
            toks = []
            if cls != "lit4":
                a = natural_align(lo, min(16, obj.align.get(sec, 8) or 1))
                if a != natural_align(lo):
                    toks.append(f"align={a}")
            if row["stem"] != row["name"]:
                toks.append(f"file={row['stem']}")
            c = Counter(ks)
            what = ", ".join(f"{n} {PLURAL[k] if n > 1 else k}" for k, n in c.items())
            rows.append(f"{cls} {row['name']} 0x{lo:08X} 0x{hi:08X} {row['tu']}"
                        + "".join(" " + t for t in toks) + f"  # {what}")
    return rows


def derive(rows, todo, elf, syms, rev):
    """{stem: result} for the text rows of todo, one compile per TU."""
    target = TargetRefs(elf)
    sec_of_name = symbol_sections(syms)
    by_tu = {}
    for r in todo:
        by_tu.setdefault(r["tu"], []).append(r)
    out = {}
    for tu, rs in by_tu.items():
        rows_tu = [r for r in rows if r["section"] == "text" and r["tu"] == tu]
        try:
            got = derive_tu(tu, rows_tu, target, sec_of_name, rev)
        except SystemExit as ex:
            got = {r["stem"]: dict(status="absent", rows=[], notes=[str(ex)]) for r in rows_tu}
        for r in rs:
            out[r["stem"]] = got[r["stem"]]
    return out


def write_literal_rows(path, rows, results):
    """Replace each derived stem's literal rows in the list with the new
    ones, after its text row."""
    text = path.read_text().splitlines(keepends=True)
    by_line = {r["line"]: r for r in rows}
    redo = {s for s, res in results.items() if res["status"] in ("ok", "none")}
    out = []
    for n, line in enumerate(text, 1):
        r = by_line.get(n)
        if r and r["section"] in LITERALS and r["stem"] in redo:
            continue
        out.append(line)
        if r and r["section"] == "text" and r["stem"] in redo:
            out += [x + "\n" for x in results[r["stem"]]["rows"]]
    path.write_text("".join(out))


def report_literals(rows, results, show_rows):
    """Print each row's derivation and the totals; the exit status."""
    c = Counter(res["status"] for res in results.values())
    for r in rows:
        res = results.get(r["stem"])
        if res is None or r["section"] != "text":
            continue
        tag = {"ok": "rows", "none": "none", "absent": "ABSENT", "disagree": "DISAGREE", "hand": "HAND"}[res["status"]]
        if res["status"] != "none" or show_rows:
            print(f"gen_stub_s: {tag:<8} {r['stem']} ({r['tu']})")
        for x in res["notes"]:
            print(f"    {x}")
        if show_rows:
            for x in res["rows"]:
                print(f"    {x}")
    dis_own = sum(1 for res in results.values() if res["status"] == "disagree" and res.get("own"))
    written = sum(len(res["rows"]) for res in results.values() if res["status"] == "ok")
    print(f"gen_stub_s: {len(results)} text rows, {c['ok'] + c['hand'] + dis_own} of them own constants on the"
          f" object side: {c['ok']} derived ({written} literal rows), {c['hand']} HAND, {dis_own} DISAGREE;"
          f" {c['none']} own none, {c['disagree'] - dis_own} more DISAGREE owning none,"
          f" {c['absent']} not in the compiled TU")
    return 1 if c["disagree"] or c["absent"] or c["hand"] else 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    g = ap.add_mutually_exclusive_group()
    g.add_argument("--list", action="store_true", help="print the rows")
    g.add_argument("--check", type=Path, metavar="ELF", help="compare each row's range in a built ELF with the base")
    g.add_argument("--carve", metavar="NAME", help="replace a text row's definition in its TU with INCLUDE_ASM")
    g.add_argument("--restore", metavar="NAME", help="put a carved definition back from --from")
    g.add_argument("--carve-all", action="store_true", help="--carve for every text row")
    g.add_argument("--restore-all", action="store_true", help="--restore for every text row")
    g.add_argument("--literals", nargs="?", const="", metavar="NAME",
                   help="derive the literal rows of a text row (every text row without NAME) and write them")
    ap.add_argument("--no-literals", action="store_true", help="--carve and --carve-all leave the literal rows alone")
    ap.add_argument("--dry-run", action="store_true", help="--literals prints the rows and writes nothing")
    ap.add_argument("--elf", type=Path, default=BASE_ELF,
                    help=f"the target ELF --literals reads (default {BASE_ELF.relative_to(ROOT)})")
    ap.add_argument("--syms", type=Path, default=SYMS_ELF,
                    help="a linked ELF with symbols, for the section of a name the TU does not define"
                         f" (default {SYMS_ELF.relative_to(ROOT)})")
    ap.add_argument("--from", dest="rev", default="main", metavar="REV",
                    help="the revision --restore (and --literals, for a carved function) reads the definition"
                         " from (default main, the seed)")
    ap.add_argument("--stubs", type=Path, default=LIST, help=f"the list (default {LIST.relative_to(ROOT)})")
    ap.add_argument("--out-dir", type=Path, default=OUT_DIR)
    a = ap.parse_args()
    rows = parse_stubs(a.stubs)
    if a.list:
        for r in rows:
            extra = ((" local" if r["local"] else "")
                     + (f" align={r['align']}" if r["section"] != "lit4" and r["align"] != natural_align(r["lo"])
                        else "")
                     + (f" lines={r['lines']}" if r["lines"] else "")
                     + (f" file={r['stem']}" if r["stem"] != r["name"] else ""))
            print(f"{r['section']:<6} {r['name']} {r['lo']:08X} {r['hi']:08X} {r['tu']}{extra}")
        print(f"gen_stub_s: {len(rows)} stubs in {a.stubs}" + ("" if rows else " (idle)"), file=sys.stderr)
        return 0
    if a.check:
        return check(rows, a.check)
    if a.literals is not None:
        todo = [text_row(rows, a.literals)] if a.literals else [r for r in rows if r["section"] == "text"]
        results = derive(rows, todo, a.elf, a.syms, a.rev)
        rc = report_literals(rows, results, a.dry_run or bool(a.literals))
        if not a.dry_run:
            write_literal_rows(a.stubs, rows, results)
        return rc
    if a.carve or a.carve_all:
        todo = [text_row(rows, a.carve)] if a.carve else [r for r in rows if r["section"] == "text"]
        rc = 0
        if not a.no_literals:
            # derived while the functions are still C
            src = {}
            fresh = [r for r in todo if asm_line(r["stem"]) not in src.setdefault(
                r["tu"], (ROOT / r["tu"]).read_bytes().splitlines(keepends=True))]
            if fresh:
                results = derive(rows, fresh, a.elf, a.syms, a.rev)
                rc = report_literals(rows, results, True)
                write_literal_rows(a.stubs, rows, results)
                rows = parse_stubs(a.stubs)
                todo = [next(x for x in rows if x["section"] == "text" and x["stem"] == r["stem"]) for r in todo]
        return carve_rows(rows, todo, a.stubs, False, a.rev) or rc
    if a.restore or a.restore_all:
        todo = [text_row(rows, a.restore)] if a.restore else [r for r in rows if r["section"] == "text"]
        return carve_rows(rows, todo, a.stubs, True, a.rev)
    from elftools.elf.elffile import ELFFile
    a.out_dir.mkdir(parents=True, exist_ok=True)
    wrote = write_if_changed(a.out_dir / HEADER, HEADER_TEXT)
    stems = stub_rows(rows)
    with open(BASE_ELF, "rb") as fh:
        elf = ELFFile(fh)
        for stem, rs in stems.items():
            text = write_stub(rs, [section_bytes(elf, r, "the base ELF") for r in rs])
            wrote += write_if_changed(a.out_dir / f"{stem}.s", text)
    print(f"gen_stub_s: {len(stems)} stubs and {HEADER}, {wrote} written to {a.out_dir}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
