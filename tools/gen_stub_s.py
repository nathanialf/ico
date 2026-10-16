#!/usr/bin/env python3
"""tools/gen_stub_s.py -- write the not-yet-matched functions as stubs from the base ELF.

During a target's campaign the functions whose C does not yet give the base's
bytes still have to sit at the base's addresses, so the byte gate passes at
every commit. Each one is listed in config/stubs.<slug>.txt (slug from
tools/ico_version.py) and its translation unit carries `INCLUDE_ASM(stem);`
where the function stands in the file. This tool writes
build/<slug>/stubs/<stem>.s for every row from the user's own base ELF, as
build/<slug>/data/ is written by tools/gen_data_c.py: nothing of the ROM is
tracked (docs/LEGAL.md). It also writes the macro's header,
build/<slug>/stubs/include_asm.h, every time it runs; the tree tracks no copy
of it, and tools/compile_c.sh searches build/<slug>/stubs last, so a TU that
includes "include_asm.h" compiles only while stubs exist. With the list empty
the mechanism is idle.

A row names a source by its path (ico2/..., sce/...), the file every target
compiles, and a file read from a revision is <rev>:<path>.

The list, one row per stub, `#` starts a comment:

    <section> <name> <vma_lo> <vma_hi> <tu> [local] [align=N] [lines=N] [file=<stem>]
              [in=<file.c.inc>] [inline] [def]

  section   text, rodata, data or sdata: the base ELF section the range
            lies in; lit4, rdlit or sdlit for a text row's constants (below)
  name      the symbol the stub defines (MAIN.MAP's name, or D_<VMA>)
  vma_lo/hi the range [lo, hi) in the base ELF, hex; a text row ends at the
            function's last instruction, not at the fill after it
  tu        the tracked C source whose INCLUDE_ASM(stem) includes the stub
            (ninja makes that object depend on build/<slug>/stubs/<stem>.s)
  local     the name is file-local in the C (a static), so no .globl
  align=N   the stub's alignment in bytes; by default the largest power of
            two dividing vma_lo, at most 8 (ee-gcc's .p2align 3 per function
            and per rodata object)
  lines=N   the stubbed body spanned N source lines in the TU; nothing in
            the build reads it yet (the parser accepts it, --list prints it,
            --carve writes it)
  file=stem the stub's file is build/<slug>/stubs/<stem>.s and the TU spells
            INCLUDE_ASM(stem), while the symbol stays <name>: two statics of
            one name in two TUs get a row each (default: stem = name; stems
            are unique, and a name is global in one row at most)
  in=path   the function is defined in a .c.inc the TU includes, and its
            INCLUDE_ASM line lives there, at the definition (the tu column
            stays the including .c, whose object reads the stub; ninja makes
            that object depend on the .c.inc too). A literal row takes its
            text row's
  inline    on a text row with in=: the function is an inline function of
            that .c.inc, so its INCLUDE_ASM line stands at the end of the TU
            (where gcc emits it) and only its INCLUDE_ASM_LIT line, if it
            has def rows, and the declaration carve keeps stay in the
            .c.inc; --carve writes it
  def       on an rdlit or sdlit row: the run is written where the function
            is defined, to build/<slug>/stubs/<stem>.lit.s, which the file reads
            with INCLUDE_ASM_LIT(stem); at that place (an inline function's
            strings and gcc's other constants, below)

A literal row carries the anonymous constants a stubbed function brings
into its TU's data sections. gcc writes the string literals and constants a
function uses as $LC labels just before the function's code (in .rdata, or in
.sdata when they fit -G 8), and with -G 8 ee-as expands `li.s` of a constant
whose low half is not zero into a $gp load and appends the constant to the
TU's .lit4, and `li.d` into a register pair into a load of a constant it
appends to the TU's .rodata, each as it reads the instruction, in load order
and with no merging of equal values. A stub of raw words loads from the same
offsets but brings none of them, so every later constant of the TU would move
up, and with them the code: every address of a constant in an instruction
(a %hi and %lo pair, a $gp offset, a literal load) is a relocated field, so
a constant that moves changes the words of each function that loads it, the
TU's own and those of other TUs, and the gate's .text row cannot pass
before .lit4, .rodata and .sdata do. `lit4 <name> <lo> <hi> <tu>` (`rdlit` for .rodata, `sdlit` for .sdata),
with the name and file= of the function's text row in the same TU, gives the
range of the base ELF's section that function's own constants occupy (one
contiguous run per section, since each sits between the constants of the
functions before and after it); the stub file writes them as bytes of that
section after the function's text, so the TU's other constants, and the
code that addresses them, keep their places. A literal row takes no `local`; lit4 aligns to 4 as the assembler
does, rdlit and sdlit to align=N (default as for a data row, the largest
power of two dividing vma_lo, at most 8; gcc aligns its strings to 8 and its
jump tables to 16). A function has one row per run of its constants in a
section, usually one; a static inside the function (gcc's `name.N`) that
gcc wrote among them is part of the run.

`--literals` derives those rows, and --carve and --carve-all run it for the
rows they carve (unless --no-literals) while the functions are still C; for
a function carved earlier without them it puts the definition back from
--from for the compile, and when it adds a def row to such a function it
also puts the INCLUDE_ASM_LIT line where the definition stood (after the
declaration carve kept, else where the lines around the definition in
--from name one place), takes the line out when the function's def rows are
gone, and prints HAND when no place is found. Two
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
first function in reading order that references it owns it and a later
stubbed user needs no row; reading order is definition order (a .c.inc's
definitions at the line that includes it), and an inline function, whose
code comes out at the end of the object, reads where it is defined. The
assembler interns nothing (equal floats are two words), so .lit4 and the
li.d pool belong to the function whose text loads them. A constant some
function still in C emits needs no row either: the tool compiles the TU a
second time with the listed functions removed, and a constant that compile
still writes (an inline function's body is expanded where it is defined,
even with every caller stubbed) stays the C's.

A stubbed inline function's strings and gcc's other constants in .rodata and
.sdata are written where it is defined, among its neighbours' constants,
while its code, and with it the assembler's .lit4 floats and li.d doubles
and its jump tables (referenced from that code), comes out at the end of the
file. Its rdlit and sdlit rows for gcc's constants carry `def`: the stub
writes them to build/<slug>/stubs/<stem>.lit.s, and --carve puts

    INCLUDE_ASM_LIT(stem);

where the definition stood, with INCLUDE_ASM(stem); at the end of the file
as for any inline function. Measured on PAL with ReadSoundSqFile
(charFileManager.c) and stage_CheckAnimationFinish (StageAnimation.c): gate
PASS with the string at the definition, and with the same row written after
the text instead, .rodata and .text differ.

A row with no definition to put back from --from (a function with no C, a
nested function, an inline function carved by hand where the lines around it
no longer name its place) prints ABSENT with the addresses its words form in
each section (the target side alone, which is all such a row has) and gets
no rows; so does a row whose body, put back at its INCLUDE_ASM line, stops
the TU compiling (a target's stub moved ahead of a name its body uses): the
TU is compiled with each carved row put back in turn on those that compiled
before it, and the ones that break it stay stubs. The rest of the TU is
derived as usual.

Three cases print HAND and write nothing, because no row can place them: a
constant the stubbed owner shares with a later function still in C (gcc
writes it again before that function: measured, the stub's copy and gcc's
both land), one the TU's data also references, and a static inside the
function that lives in .data, .sbss or .bss. A count or kind that differs
between the sides prints DISAGREE: the target's function is not the
object's, and its rows are measured by hand.

A text row is written as one function: `.set noreorder`, `.globl`,
`.type @function`, `.ent`, one `.word` per instruction, `.end`, `.size`. A
data row is a run of `.word`, `.half` and `.byte` as the address allows. The
words are absolute: there are no relocations, the stub is right only at its
own address, and the gate proves the layout. Each stub returns to the section
it was included from (`.previous`), so the compiler's own section state holds.

    tools/gen_stub_s.py                      write build/<slug>/stubs/<stem>.s for every row
    tools/gen_stub_s.py --list               print the rows
    tools/gen_stub_s.py --check build/<slug>/ico.syms.elf
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
                                             its old ones, with the
                                             INCLUDE_ASM_LIT line of a carved
                                             one; --dry-run prints

NAME is a row's stem, or its name when one row carries it. Only a text
row's function is carved; its literal rows ride on the same INCLUDE_ASM line
(def rows on INCLUDE_ASM_LIT), and --carve derives them first (above). A row
with in=<file.c.inc> is carved in that file: the uses and declarations of
the name in the TU before and after the line that includes it count with
the file's own.
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
is an implicit `int name()` and compiles differently (and an address of an
undeclared name does not compile). The first carve in a
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
place). An inline function the file calls after its definition, where gcc
can inline it, is refused: the callers lose the inlined body. A later use
that only takes its address (a function pointer in a table or an argument)
inlines nothing, and the declaration alone stays where the definition stood
when nothing above declares the name (measured on PAL: StageManager.c's
stgmgrNextStagePreLoadDiskNotReady, whose address
stgmgrNextStagePreLoadEntry passes, carved with the four inline functions
the base emits before it, gate PASS). So does a call from a function whose
code never reaches the object: one the compiler does not write and no
written function calls, over and over (an inline helper nothing written
uses; the TU is compiled as it stands, stub lines left out, for the
functions its object holds). A helper that is not written but is inlined
into one that is still carries the body, and the carve is refused (measured
on PAL: motionFileManager.c's CheckMotionIncludeFacialData, called only by
relocMotionFile, which InitMotionFile inlines; carved, InitMotionFile's
words differ; and with a helper nothing calls added for the measurement,
ResetDynamicMotionManager carved with its declaration kept, gate PASS).
With def rows the INCLUDE_ASM_LIT line stands there too, after the
declaration. An inline function defined in a .c.inc is carved there and
its INCLUDE_ASM line goes to the end of the including TU, where gcc emits
it, and the row gets `inline` (measured on PAL: motMan_getFinalMatrix.c.inc's
ResetMotionProgramInterpInfo, carved with motionManager.c's
SetHitCollisionDisplay, which the base emits before it, gate PASS). A
restore puts the definition back in place of the INCLUDE_ASM_LIT line or of
the declaration carve kept, else after the lines that preceded it in REV
when the line after that place followed it there, else before the lines
that followed it (a neighbour above it carved too leaves the lines before it
elsewhere). A definition inside `#if`/`#ifdef` and a name the file does not
define (a function only the target has) are refused: those are placed by
hand.
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
from ico_version import baseelf_path, build_dir, config_path, detect_version  # noqa: E402

VERSION = detect_version(ROOT)
LIST = config_path(ROOT, VERSION, "stubs", "txt")
BASE_ELF = baseelf_path(ROOT, VERSION)
OUT_DIR = build_dir(ROOT, VERSION) / "stubs"
# the stub directory as the assembler is given it: relative to the
# repository root, where tools/compile_c.sh runs it
STUBS_REL = OUT_DIR.relative_to(ROOT).as_posix()
HEADER = "include_asm.h"
SECTIONS = ("text", "rodata", "data", "sdata", "lit4", "rdlit", "sdlit")
# a text row's constants: kind -> the base ELF section
LITERALS = {"lit4": ".lit4", "rdlit": ".rodata", "sdlit": ".sdata"}
INCLUDE_LINE = b'#include "include_asm.h"\n'

# build/<slug>/stubs/include_asm.h, written with the stubs; never tracked. Its
# build/stubs/ spellings become the target's stub directory (STUBS_REL).
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

/* An inline function's strings and gcc's other constants are written where
 * the function is defined, while gcc emits its code after the whole file is
 * read, where its INCLUDE_ASM line stands. The row's rdlit and sdlit rows
 * marked def are written to build/stubs/stem.lit.s, which
 *
 *     INCLUDE_ASM_LIT(stem);
 *
 * reads at the definition's place; the text, its .lit4 floats, its li.d
 * doubles and its jump tables stay with INCLUDE_ASM(stem). */
#define INCLUDE_ASM_LIT(NAME) __asm__(".include \\"build/stubs/" #NAME ".lit.s\\"")

#endif /* INCLUDE_ASM_H */
""".replace("build/stubs/", f"{STUBS_REL}/")


def src_path(rel):
    """The file a row's path names."""
    return ROOT / rel


def rev_spec(rev, rel):
    """The object name of rel at rev."""
    return f"{rev}:{rel}"


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
                 f" [file=<stem>] [in=<file.c.inc>] [def]' with section one of {', '.join(SECTIONS)}")
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
        local, align, span, stem, src, at_def, inl = False, natural_align(lo), None, name, tu, False, False
        for tok in f[5:]:
            m = re.fullmatch(r"align=(\d+)", tok)
            k = re.fullmatch(r"lines=(\d+)", tok)
            st = re.fullmatch(r"file=(\w+)", tok)
            inc = re.fullmatch(r"in=((?:ico2|sce)/\S+\.c\.inc)", tok)
            if tok == "local" and sec not in LITERALS:
                local = True
            elif inc and sec not in LITERALS:
                src = inc.group(1)
            elif tok == "def" and sec in ("rdlit", "sdlit"):
                at_def = True
            elif tok == "inline" and sec == "text":
                inl = True
            elif m and sec != "lit4" and int(m.group(1)) in (1, 2, 4, 8, 16) and lo % int(m.group(1)) == 0:
                align = int(m.group(1))
            elif k and int(k.group(1)) > 0:
                span = int(k.group(1))
            elif st:
                stem = st.group(1)
            else:
                fail(f"{where}:{n}: bad token '{tok}' (local, align=N with N a power of two dividing vma_lo,"
                     " lines=N with N > 0, file=<stem>, in=<path.c.inc> under ico2/ or sce/, inline, or def;"
                     " a literal row takes no local and no in=, a lit4 row no align=, only a text row takes"
                     " inline, and only an rdlit or sdlit row takes def)")
        if inl and src == tu:
            fail(f"{where}:{n}: inline marks a function defined in its in=<file.c.inc> whose INCLUDE_ASM"
                 " stands at the end of the TU; an inline function defined in the TU needs no token")
        if sec in LITERALS:
            if sec == "lit4":
                align = 4
        elif stem in stems:
            fail(f"{where}:{n}: {stem} is listed twice (first at line {stems[stem]['line']});"
                 " two statics of one name take file=<stem>")
        # asm: the file whose INCLUDE_ASM line stands for the row (its in=
        # file, but the TU for an inline function defined there)
        row = dict(section=sec, name=name, lo=lo, hi=hi, tu=tu, local=local, align=align,
                   lines=span, stem=stem, line=n, src=src, at_def=at_def, inline=inl, asm=tu if inl else src)
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
        # a literal row's lines live where its function's do
        r["src"], r["asm"] = t["src"], t["asm"]
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


def stub_files(rows):
    """{tu: [the files under build/<slug>/stubs/ the TU's object reads]}: each
    stem's .s, and its .lit.s when a def row asks for INCLUDE_ASM_LIT."""
    out = {}
    for r in rows:
        names = [f"{r['stem']}.s"] + ([f"{r['stem']}.lit.s"] if r["at_def"] else [])
        for n in names:
            if n not in out.setdefault(r["tu"], []):
                out[r["tu"]].append(n)
    return out


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
    out += literal_lines(name, [(r, b) for r, b in zip(rows[1:], bufs[1:]) if not r["at_def"]])
    return "\n".join(out) + "\n"


def literal_lines(name, pairs):
    """The constants the function's code brought into the sections, each run
    in its section and back."""
    out = []
    for r, b in pairs:
        sec = LITERALS[r["section"]]
        out += [f"# {name}'s constants: 0x{r['lo']:08X}..0x{r['hi']:08X} of the base ELF's {sec}.",
                f"    .section {sec}", f"    .p2align {r['align'].bit_length() - 1}"]
        out += data_lines(b, r["lo"])
        out.append("    .previous")
    return out


def write_lit_stub(rows, bufs):
    """The stub file INCLUDE_ASM_LIT reads at the function's definition: its
    def rows' constants only (an inline function's strings and gcc's
    constants, which gcc writes where the function is defined)."""
    row = rows[0]
    out = [f"# {row['name']}: the constants gcc writes where the function is defined, for {row['src']};"
           " generated by tools/gen_stub_s.py, not tracked."]
    out += literal_lines(row["name"], [(r, b) for r, b in zip(rows[1:], bufs[1:]) if r["at_def"]])
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


def lit_line(stem):
    return f"INCLUDE_ASM_LIT({stem});\n".encode()


def is_stub_line(line):
    return line.startswith((b"INCLUDE_ASM(", b"INCLUDE_ASM_LIT("))


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


def include_lines(where, inc):
    """The lines of a .c.inc a file includes, for where as find_definition
    takes it: a path in the tree, or `rev:path` for a file read from a
    revision (the .c.inc then from that revision too); [] when it is not
    there."""
    rev, sep, _ = where.rpartition(":")
    if sep:
        p = subprocess.run(["git", "cat-file", "--filters", rev_spec(rev, inc)], cwd=ROOT, capture_output=True)
        return p.stdout.splitlines(keepends=True) if not p.returncode else []
    return src_path(inc).read_bytes().splitlines(keepends=True) if src_path(inc).is_file() else []


def find_definition(lines, name, where):
    found = [d for d in definitions(lines) if d["name"] == name]
    if not found:
        path = where.rpartition(":")[2]
        there = [i for i in included(path, lines) if any(
            d["name"] == name for d in definitions(include_lines(where, i)))]
        fail(f"{where}: no definition of {name} at file scope"
             + (f"; it is in {', '.join(there)}, which the TU includes: give the row in={there[0]}"
                if there else ""))
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


def included(tu, lines):
    """The .c.inc files tu's lines include, as paths from the root, in order."""
    out = []
    for l in lines:
        m = re.match(rb'\s*#\s*include\s+"([^"]+\.c\.inc)"', l)
        if m:
            out.append(os.path.normpath(os.path.join(os.path.dirname(tu), m.group(1).decode())))
    return out


def include_at(tu, tu_lines, src):
    """The line of tu_lines that includes src."""
    rel = os.path.relpath(src, os.path.dirname(tu)).encode()
    at = [k for k, l in enumerate(tu_lines) if re.match(rb'\s*#\s*include\s+"' + re.escape(rel) + rb'"', l)]
    if len(at) != 1:
        fail(f"{tu}: {'does not include' if not at else 'includes more than once'} {src}"
             " (the row's in=)")
    return at[0]


def context(row, tu_lines=None):
    """The TU's lines before and after the line that includes the row's
    in=<file.c.inc> (none for a row in its .c), for the uses and
    declarations of the name around the file."""
    if row["src"] == row["tu"]:
        return [], []
    if tu_lines is None:
        tu_lines = src_path(row["tu"]).read_bytes().splitlines(keepends=True)
    k = include_at(row["tu"], tu_lines, row["src"])
    return tu_lines[:k], tu_lines[k + 1:]


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
    asm = [k for k, l in enumerate(lines) if is_stub_line(l)]
    have = [k for k, l in enumerate(lines) if l == INCLUDE_LINE]
    if asm and have and have[0] < asm[0] and len(have) == 1:
        return lines
    for k in reversed(have):
        top = k == 0 and k + 1 < len(lines) and lines[k + 1] == b"\n"
        del lines[k:k + 1 + top]
    if not asm:
        return lines
    first = next(k for k, l in enumerate(lines) if is_stub_line(l))
    info = scan_code(lines)
    inc = [k for k in range(first) if info[k][1] and INCLUDE.match(lines[k])]
    if inc:
        lines.insert(inc[-1] + 1, INCLUDE_LINE)
    else:
        lines[0:0] = [INCLUDE_LINE, b"\n"]
    return lines


def call_sites(lines, name, start):
    """[(line, the definition around it or None)] of each code line in
    lines[start:] that calls `name` (macros count, outside any definition)."""
    pat = re.compile(rb"\b" + re.escape(name.encode()) + rb"\s*\(")
    defs = definitions(lines)
    out = []
    for k, (c, _, _) in enumerate(scan_code(lines[start:]), start):
        if pat.search(c):
            out.append((k, next((d["name"] for d in defs if d["s"] <= k <= d["e"]), None)))
    return out


def emitted_functions(tu, cache={}):
    """The names of the functions the TU's object holds as it stands on disk
    (an inline function no emitted code calls is not written), compiled
    with its stub lines left out, so build/<slug>/stubs need not exist: a stub
    calls no C."""
    if tu not in cache:
        from elftools.elf.elffile import ELFFile
        tu_lines = src_path(tu).read_bytes().splitlines(keepends=True)
        files = {f: [l for l in src_path(f).read_bytes().splitlines(keepends=True)
                     if not is_stub_line(l) and l != INCLUDE_LINE] for f in [tu] + included(tu, tu_lines)}
        with tempfile.TemporaryDirectory(prefix="gen_stub_s.") as tmp:
            with open(compile_files(tu, files, Path(tmp)), "rb") as fh:
                tab = ELFFile(fh).get_section_by_name(".symtab")
                cache[tu] = {x.name for x in tab.iter_symbols() if x["st_info"]["type"] == "STT_FUNC"}
    return cache[tu]


def live_functions(tu, cache={}):
    """The functions of the TU whose code reaches its object: those the
    object holds, and, over and over, each one a live function calls (gcc
    may inline it there; a call outside a function body, in a macro or an
    initializer, makes it live too). A function outside the set is an
    inline helper nothing written uses, whose body says nothing."""
    if tu not in cache:
        tu_lines = src_path(tu).read_bytes().splitlines(keepends=True)
        files = [tu_lines] + [src_path(f).read_bytes().splitlines(keepends=True) for f in included(tu, tu_lines)]
        names, sites = set(), {}
        for lines in files:
            defs = definitions(lines)
            names |= {d["name"] for d in defs}
            for k, (c, _, _) in enumerate(scan_code(lines)):
                for m in re.finditer(rb"\b(\w+)\s*\(", c):
                    fn = next((d["name"] for d in defs if d["s"] <= k <= d["e"]), None)
                    sites.setdefault(m.group(1).decode(), []).append(fn)
        sites = {n: sites.get(n, []) for n in names}
        live = set(emitted_functions(tu))
        grow = True
        while grow:
            grow = False
            for n in names - live:
                if any(fn is None or fn in live for fn in sites[n]):
                    live.add(n)
                    grow = True
        cache[tu] = live
    return cache[tu]


def place_at_end(lines, row, lo_of):
    """INCLUDE_ASM(stem) at the end of the file, among the stubs there in
    address order."""
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


def carve(lines, row, where, lo_of, lit=False, ctx=([], []), tu_lines=None):
    """Replace row's definition in lines (the file row's src, where) with
    its INCLUDE_ASM line; (the lines it spanned, whether it is an inline
    function of a .c.inc). lo_of gives each stem's vma_lo, to order the
    stubs of inline functions at the end of the file; lit puts
    INCLUDE_ASM_LIT at an inline function's definition; ctx is the TU's
    lines before and after the include of a .c.inc, and tu_lines the TU's
    lines, where the INCLUDE_ASM of an inline function of a .c.inc goes (at
    the end; None: nowhere, for a compile that leaves the stubs out)."""
    d = find_definition(lines, row["name"], where)
    s, e, name = d["s"], d["e"], row["name"]
    # a later use with no declaration above would make a call an implicit
    # `int name()`, which compiles differently, and an address of an
    # undeclared name does not compile: the signature stays as a declaration
    keep = []
    if ((mentions(lines, name, e + 1) or mentions(ctx[1], name, 0))
            and not (mentions(lines, name, 0, s, macros=False) or mentions(ctx[0], name, 0, macros=False))):
        keep = prototype(lines, d) + [b"\n"]
    if not d["inline"]:
        lines[s:e + 1] = keep + [asm_line(row["stem"])]
        place_header(lines)
        return e - s + 1, False
    # gcc 2.9 compiles an inline function it must emit after the whole
    # file is read, after every other definition and every file-scope
    # asm; its stub goes at the end of the TU, with the other stubs there
    # in address order (for one defined in a .c.inc, the end of the
    # including TU). A call after the definition is inlined there, which a
    # stub cannot give, unless the caller is itself an inline function the
    # compiler does not write (no emitted code calls it); a use that only
    # takes the address needs the declaration alone, and so does such a
    # call.
    sites = call_sites(lines, name, e + 1) + call_sites(ctx[1], name, 0)
    if sites:
        loose = [k for k, fn in sites if fn is None]
        callers = sorted({fn for _, fn in sites if fn})
        if loose:
            fail(f"{where}:{s + 1}: inline {name} is called after its definition outside a function body"
                 " (a macro or an initializer), where gcc may inline it; carve it by hand")
        live = [fn for fn in callers if fn in live_functions(row["tu"])]
        if live:
            fail(f"{where}:{s + 1}: inline {name} is called after its definition by {', '.join(live)},"
                 " where gcc may inline it; carve or restore those callers first")
        print(f"gen_stub_s: {name} is called after its definition only by {', '.join(callers)}, which the"
              f" compiler neither writes nor inlines into code it writes ({row['tu']}'s object): carved"
              " with the declaration kept")
    # gcc writes the function's strings and other constants where it is
    # defined: INCLUDE_ASM_LIT there, when the row has def literal rows
    here = keep + [lit_line(row["stem"])] if lit else keep[:-1]
    if here:
        lines[s:e + 1] = here
    elif e + 1 < len(lines) and lines[e + 1] == b"\n":
        del lines[s:e + 2]
    elif s > 0 and lines[s - 1] == b"\n":
        del lines[s - 1:e + 1]
    else:
        del lines[s:e + 1]
    inc = where != row["tu"]
    if not inc:
        place_at_end(lines, row, lo_of)
    elif tu_lines is not None:
        place_at_end(tu_lines, row, lo_of)
        place_header(tu_lines)
    end = row["tu"]
    print(f"gen_stub_s: {name} is inline: INCLUDE_ASM at the end of {end}"
          + (f", INCLUDE_ASM_LIT for its strings where it was defined in {where}" if lit else "")
          + ". Its stub is emitted after everything the file defines in place and before every inline"
          " function the compiler still emits there, so those that come before it in the base are carved"
          " too (stubcheck names a stub out of place)")
    place_header(lines)
    return e - s + 1, inc


def restore(lines, rev_lines, row, where, rev, tu_lines=None):
    """Put row's definition back from rev_lines in place of its INCLUDE_ASM
    line (and the declaration carve left above it; for an inline function,
    in place of its INCLUDE_ASM_LIT line or its declaration, else after the
    lines that preceded it in rev). For an inline function of a .c.inc,
    tu_lines are the TU's, whose INCLUDE_ASM line goes."""
    asm_in = tu_lines if row["asm"] != row["src"] else lines
    if asm_in is None:
        fail(f"{where}: {row['stem']}'s INCLUDE_ASM line is in {row['asm']}, which was not read")
    at = [k for k, l in enumerate(asm_in) if l == asm_line(row["stem"])]
    if len(at) != 1:
        fail(f"{row['asm']}: {'no' if not at else 'more than one'} INCLUDE_ASM({row['stem']}); line")
    d = find_definition(rev_lines, row["name"], f"{rev}:{row['src']}")
    s, e = d["s"], d["e"]
    body = rev_lines[s:e + 1]
    k = at[0]
    keep = prototype(rev_lines, d) + [b"\n"]
    if not d["inline"]:
        if asm_in is not lines:
            fail(f"{where}: {row['name']} is not inline in {rev}, and its row puts the INCLUDE_ASM line in"
                 f" {row['asm']} (the token inline); put it back by hand")
        if lines[k - len(keep):k] == keep:
            k -= len(keep)
        lines[k:at[0] + 1] = body
        place_header(lines)
        return
    del asm_in[k - 1 if k > 0 and asm_in[k - 1] == b"\n" else k:k + 1]
    if asm_in is not lines:
        place_header(asm_in)
    lit = [j for j, l in enumerate(lines) if l == lit_line(row["stem"])]
    if len(lit) > 1:
        fail(f"{where}: more than one INCLUDE_ASM_LIT({row['stem']}); line")
    decl = [j for j in range(len(lines)) if lines[j:j + len(keep) - 1] == keep[:-1]]
    if lit:
        j = lit[0]
        lines[j - len(keep) if lines[j - len(keep):j] == keep else j:j + 1] = body
    elif len(decl) == 1 and not any(rev_lines[j:j + len(keep) - 1] == keep[:-1] for j in range(len(rev_lines))):
        # the declaration carve kept where the definition stood
        lines[decl[0]:decl[0] + len(keep) - 1] = body
    else:
        k = after_preceding(lines, rev_lines, s, f"{where}: the lines around inline {row['name']} in {rev}"
                            " are not found here as they stand there; put it back by hand", e)
        gap = [b"\n"] if s > 0 and rev_lines[s - 1] == b"\n" else []
        lines[k:k] = gap + body + [b"\n"]
    place_header(lines)


def after_preceding(lines, rev_lines, s, refusal, e=None):
    """The index in lines where rev_lines[s:e + 1] stood: just after the
    lines that preceded it in rev, as many of them as it takes to name one
    place, blank lines aside (the layout pass settles those), when the line
    after that place is the one that followed it in rev; else just before
    the lines that followed it in rev, as many as it takes to name one
    place (a neighbour above it that is itself carved leaves the lines
    before it elsewhere, and the same lines can close another function);
    else the place the lines before it name. refusal when none is found."""
    solid = [j for j, l in enumerate(lines) if l.strip()]
    text = [lines[j] for j in solid]

    def unique(ctx_of, n_max, at):
        hits = []
        for n in range(1, n_max + 1):
            ctx = ctx_of(n)
            hits = [at(i, n) for i in range(len(text) - n + 1) if text[i:i + n] == ctx]
            if len(hits) <= 1:
                break
        return hits[0] if len(hits) == 1 else None

    before = [l for l in rev_lines[:s] if l.strip()]
    after = [l for l in rev_lines[e + 1:] if l.strip()] if e is not None else []
    pre = unique(lambda n: before[-n:], len(before), lambda i, n: solid[i + n - 1] + 1)
    if pre is not None:
        nxt = next((l for l in lines[pre:] if l.strip()), None)
        if not after or nxt == after[0]:
            return pre
    post = unique(lambda n: after[:n], len(after), lambda i, n: solid[i])
    if post is not None:
        return post
    if pre is not None:
        return pre
    fail(refusal)


def place_lit(lines, rev_lines, row, where, rev, want):
    """Give a carved function's file its INCLUDE_ASM_LIT line when want
    (a def row was added after the carve) or take it out when not (its def
    rows are gone); what was done, or None. The line goes where carve puts
    it: after the declaration carve kept where the definition stood, else
    where the definition stood in rev, after the lines that preceded it."""
    have = [j for j, l in enumerate(lines) if l == lit_line(row["stem"])]
    if bool(have) == want:
        return None
    if not want:
        for j in reversed(have):
            gap = j > 0 and lines[j - 1] == b"\n" and (j + 1 >= len(lines) or lines[j + 1] == b"\n")
            del lines[j - gap:j + 1]
        return "INCLUDE_ASM_LIT removed (no def row left)"
    d = find_definition(rev_lines, row["name"], f"{rev}:{row['src']}")
    if not d["inline"]:
        fail(f"{where}: {row['name']} is not inline in {rev}, and only an inline function's constants"
             " are written at its definition; the def rows are measured by hand")
    s = d["s"]
    keep = prototype(rev_lines, d)
    decl = [j for j in range(len(lines)) if lines[j:j + len(keep)] == keep]
    if len(decl) == 1 and not any(rev_lines[j:j + len(keep)] == keep for j in range(len(rev_lines))):
        k = decl[0] + len(keep)
        lines[k:k] = [b"\n", lit_line(row["stem"])]
        return "INCLUDE_ASM_LIT after the declaration carve kept"
    k = after_preceding(lines, rev_lines, s, f"{where}: {row['name']}'s definition in {rev} cannot be"
                        " located here (the lines around it are not found as they stand there); place"
                        f" INCLUDE_ASM_LIT({row['stem']}); by hand", d["e"])
    gap = [b"\n"] if s > 0 and rev_lines[s - 1] == b"\n" else []
    lines[k:k] = gap + [lit_line(row["stem"]), b"\n"]
    return "INCLUDE_ASM_LIT where the definition stood"


def place_lits(rows, results, rev):
    """After --literals wrote its rows: each carved function whose def rows
    came or went gets its INCLUDE_ASM_LIT line put in or taken out, one
    write per file; a place no rule finds is HAND. The status: 1 when one
    is left for the hand."""
    want = {}
    for r in rows:
        res = results.get(r["stem"])
        if r["section"] == "text" and res and res["status"] in ("ok", "none"):
            want[r["stem"]] = (r, any(x.split()[0] in ("rdlit", "sdlit") and "def" in x.split("#")[0].split()[5:]
                                      for x in res["rows"]))
    by_src = {}
    for r, w in want.values():
        by_src.setdefault(r["src"], []).append((r, w))
    bad = 0
    for src, rs in by_src.items():
        path = src_path(src)
        lines = path.read_bytes().splitlines(keepends=True)
        carved = [(r, w) for r, w in rs if asm_line(r["stem"]) in (
            lines if r["asm"] == src else src_path(r["asm"]).read_bytes().splitlines(keepends=True))]
        if not carved:
            continue
        old = list(lines)
        clean = layout(lines) == lines
        rev_lines = None
        for r, w in carved:
            try:
                if w and rev_lines is None:
                    rev_lines = rev_file(rev, src)
                did = place_lit(lines, rev_lines, r, src, rev, w)
            except SystemExit as ex:
                print(f"gen_stub_s: HAND     {r['stem']} ({r['tu']})\n    {str(ex).removeprefix('gen_stub_s: ')}")
                bad += 1
                continue
            if did:
                print(f"gen_stub_s: {r['stem']}: {did} in {src}")
        if clean:
            lines = layout(lines)
        if lines != old:
            path.write_bytes(b"".join(lines))
    return 1 if bad else 0


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
    p = subprocess.run(["git", "cat-file", "--filters", rev_spec(rev, tu)], cwd=ROOT, capture_output=True)
    if p.returncode:
        fail(f"{rev}:{tu}: {p.stderr.decode(errors='replace').strip()}")
    return p.stdout.splitlines(keepends=True)


def set_tokens(path, toks):
    """Append tokens to rows of the list (by list line): lines=N to a row
    that has none, inline to a carved inline function of a .c.inc."""
    text = path.read_bytes().splitlines(keepends=True)
    for n, add in toks.items():
        line = text[n - 1].rstrip(b"\n")
        code, sep, cmt = line.partition(b"#")
        ws = code[len(code.rstrip()):] if sep else b""
        text[n - 1] = code.rstrip() + "".join(" " + t for t in add).encode() + ws + sep + cmt + b"\n"
    path.write_bytes(b"".join(text))


def carve_rows(rows, todo, list_path, back, rev):
    """Carve (or with back, restore) each row of todo, one write per file
    (the TU, the row's in=<file.c.inc>, and for an inline function of a
    .c.inc both)."""
    by_src, errors, done, skipped, toks = {}, [], 0, 0, {}
    lo_of = {r["stem"]: r["lo"] for r in rows if r["section"] == "text"}
    lit = {r["stem"] for r in rows if r["at_def"]}
    files, old, clean = {}, {}, {}

    def read(path):
        if path not in files:
            files[path] = src_path(path).read_bytes().splitlines(keepends=True)
            old[path] = list(files[path])
            # a file in the layout format.sh keeps stays in it (a
            # declaration carve leaves can join the block above it);
            # restore gives it back
            clean[path] = layout(files[path]) == files[path]
        return files[path]

    for r in todo:
        by_src.setdefault(r["src"], []).append(r)
    for src, rs in by_src.items():
        lines = read(src)
        rev_lines = rev_file(rev, src) if back else None
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
            tu_lines = read(r["tu"]) if r["tu"] != src else None
            present = asm_line(r["stem"]) in read(r["asm"])
            if present != back:
                skipped += 1
                continue
            try:
                if back:
                    restore(lines, rev_lines, r, src, rev, tu_lines)
                else:
                    n, inc = carve(lines, r, src, lo_of, r["stem"] in lit, context(r, tu_lines), tu_lines)
                    add = ([] if r["lines"] else [f"lines={n}"]) + (["inline"] if inc and not r["inline"] else [])
                    if add:
                        toks[r["line"]] = add
                done += 1
            except SystemExit as ex:
                errors.append(str(ex))
    for path, lines in files.items():
        if clean[path]:
            lines = layout(lines)
        if lines != old[path]:
            src_path(path).write_bytes(b"".join(lines))
    if toks:
        set_tokens(list_path, toks)
    for m in errors:
        print(m, file=sys.stderr)
    verb = "restored" if back else "carved"
    nl = sum(1 for t in toks.values() if any(x.startswith("lines=") for x in t))
    ni = sum(1 for t in toks.values() if "inline" in t)
    print(f"gen_stub_s: {done} {verb}, {skipped} already {verb}, {len(errors)} refused"
          + (f", lines=N written to {nl} rows" if nl else "")
          + (f", inline written to {ni} rows (INCLUDE_ASM at the end of the TU)" if ni else ""))
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


SYMS_ELF = build_dir(ROOT, VERSION) / "ico.syms.elf"
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


def compile_files(tu, files, out):
    """tu compiled with files ({path: lines}: the TU and the .c.inc files it
    includes) written in place for the compile, so the compiler sees each
    file's own name and directory, and put back after."""
    from match_check import compile_tu
    orig = {f: src_path(f).read_bytes() for f in files}
    changed = [f for f, lines in files.items() if b"".join(lines) != orig[f]]
    try:
        for f in changed:
            src_path(f).write_bytes(b"".join(files[f]))
        return compile_tu(tu, out)
    finally:
        for f in changed:
            src_path(f).write_bytes(orig[f])


def whole_files(tu, rows_tu, rev, keep=frozenset()):
    """({path: lines} of the TU and of each in= file of its rows, with every
    listed function in C: a carved one is put back from rev; {stem: why}
    of the carved rows left as stubs). A row rev has no definition for (a
    function with no C, a nested function, one carved by hand where restore
    cannot place it) stays a stub and is named with the reason; so is each
    stem of keep."""
    files, absent = {}, {}
    for src in dict.fromkeys([tu] + [r["src"] for r in rows_tu]):
        files[src] = src_path(src).read_bytes().splitlines(keepends=True)
    for src in list(files):
        lines = files[src]
        # an inline function of a .c.inc has its INCLUDE_ASM line in the TU
        carved = [r for r in rows_tu if r["src"] == src and asm_line(r["stem"]) in files[r["asm"]]]
        for r in carved:
            if r["stem"] in keep:
                absent[r["stem"]] = keep[r["stem"]]
        carved = [r for r in carved if r["stem"] not in keep]
        if carved:
            try:
                rev_lines = rev_file(rev, src)
            except SystemExit as ex:
                absent.update({r["stem"]: str(ex) for r in carved})
                carved, rev_lines = [], []
            at = {d["name"]: (d["inline"], d["s"] if d["inline"] else 0) for d in definitions(rev_lines)}
            for r in sorted(carved, key=lambda r: at.get(r["name"], (False, 0))):
                before, tu_before = list(lines), list(files[tu])
                try:
                    restore(lines, rev_lines, r, src, rev, files[tu] if src != tu else None)
                except SystemExit as ex:
                    lines[:], files[tu][:] = before, tu_before
                    absent[r["stem"]] = str(ex)
    return files, absent


def compile_whole(tu, rows_tu, rev, out):
    """(the object of the TU with every listed function in C that can be,
    the files, {stem: why} of the rows left as stubs). A body put back at
    its INCLUDE_ASM line can stand ahead of what it names (a target's
    stub moved to the target's order): when the TU does not compile so,
    each carved row is put back alone on the ones that compiled before it,
    and one that breaks the compile stays a stub."""
    files, absent = whole_files(tu, rows_tu, rev)
    try:
        with open(os.devnull, "w") as quiet, contextlib.redirect_stderr(quiet):
            return compile_files(tu, files, out), files, absent
    except SystemExit:
        pass
    back = [r["stem"] for r in rows_tu if r["stem"] not in absent
            and asm_line(r["stem"]) in src_path(r["asm"]).read_bytes().splitlines(keepends=True)]
    why = f"put back from {rev} at its INCLUDE_ASM line, the TU does not compile"
    keep = {s: why for s in back}
    for stem in back:
        del keep[stem]
        files, absent = whole_files(tu, rows_tu, rev, keep)
        try:
            with open(os.devnull, "w") as quiet, contextlib.redirect_stderr(quiet):
                compile_files(tu, files, out)
        except SystemExit:
            keep[stem] = why + " (its body stands ahead of a name it uses, or breaks the file)"
    files, absent = whole_files(tu, rows_tu, rev, keep)
    return compile_files(tu, files, out), files, absent


def without_files(whole, rows_tu, tu):
    """The files with every listed function's definition gone (a
    declaration kept where carve keeps one), to see which constants the rest
    of the C still emits. A definition carve refuses stays."""
    lo_of = {r["stem"]: r["lo"] for r in rows_tu}
    out = {}
    for src, lines in whole.items():
        lines = list(lines)
        at = {d["name"]: d["s"] for d in definitions(lines)}
        for r in sorted((r for r in rows_tu if r["src"] == src), key=lambda r: -at.get(r["name"], -1)):
            try:
                with open(os.devnull, "w") as quiet, contextlib.redirect_stdout(quiet):
                    carve(lines, r, src, lo_of, False, context(r, whole[tu]))
            except SystemExit:
                pass
        out[src] = [l for l in lines if not is_stub_line(l) and l != INCLUDE_LINE]
    return out


def reading_order(tu, files):
    """{function: rank} in the order gcc reads the TU's definitions, a
    .c.inc's at the line that includes it. gcc writes a string or constant
    run when it first expands a body that uses it: for an inline function
    where it is defined, though its code comes out at the end of the
    object."""
    tu_lines = files[tu]
    items = [(d["s"], 0, d["name"]) for d in definitions(tu_lines)]
    for inc in included(tu, tu_lines):
        lines = files.get(inc) or (src_path(inc).read_bytes().splitlines(keepends=True)
                                   if src_path(inc).exists() else [])
        k = include_at(tu, tu_lines, inc)
        items += [(k, d["s"], d["name"]) for d in definitions(lines)]
    return {n: i for i, (_, _, n) in enumerate(sorted(items))}


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
    with tempfile.TemporaryDirectory(prefix="gen_stub_s.") as tmp:
        built, files, absent = compile_whole(tu, rows_tu, rev, Path(tmp) / "whole")
        obj = ObjectRefs(built, sec_of_name)
        # the owner of a constant is its first user in reading order
        rank = reading_order(tu, files)
        for u in obj.users.values():
            u.sort(key=lambda f: rank.get(f, len(rank)))
        # gcc writes a string or constant run when it first expands a body
        # that uses it, and an inline function's body is expanded where it is
        # defined even when every user is a stub: what the C still emits
        # with the listed functions gone needs no row
        rest = None
        if any(obj.literal(k)[0] in ("string", "data") for r in rows_tu for k in obj.refs.get(r["name"], [])
               if k[1] is None):
            rest = ObjectRefs(compile_files(tu, without_files(files, rows_tu, tu), Path(tmp) / "without"),
                              sec_of_name)
    stubbed = {r["name"] for r in rows_tu}
    inline = {d["name"] for lines in files.values() for d in definitions(lines) if d["inline"]}
    out = {}
    for row in rows_tu:
        name, notes, hand, lits = row["name"], [], [], []
        if row["stem"] in absent or name not in obj.refs:
            why = absent.get(row["stem"]) or f"{tu} compiles no function {name}"
            out[row["stem"]] = absent_result(row, target, why)
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
                        lits.append((LIT_CLASS[sec], addr - k[2], hi - lo, "static", sec, False))
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
                # gcc writes an inline function's strings and constants where
                # it is defined (a def row, INCLUDE_ASM_LIT there); the
                # assembler's floats and doubles and the jump tables follow
                # its code to the end of the file
                at_def = name in inline and kind in ("string", "data", "word")
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
                lits.append((LIT_CLASS[sec], addr, size, kind, sec, at_def))
        if notes:
            out[row["stem"]] = dict(status="disagree", rows=[], notes=notes, own=mine)
            continue
        out[row["stem"]] = dict(status="hand" if hand else "ok" if lits else "none", notes=hand,
                                rows=literal_rows(row, lits, target, obj), own=mine)
    return out


def absent_result(row, target, why):
    """A row with no object side (no definition to compile): the target
    side alone, the places its words form in each section, which is all a
    row with no C has; no rows are written for it."""
    notes = [why.removeprefix("gen_stub_s: ")]
    tgt, amb = target.refs(row["lo"], row["hi"])
    for sec in LIT_CLASS:
        if tgt[sec]:
            notes.append(f"the target's words reference {len(tgt[sec])} in {sec}: "
                         + ", ".join(f"0x{a:08X}" for a in tgt[sec]))
    for i, adrs in amb:
        notes.append(f"ambiguous %hi at 0x{row['lo'] + 4 * i:08X}: {', '.join(f'0x{a:08X}' for a in adrs)}")
    if len(notes) == 1:
        notes.append("the target's words reference nothing in .lit4, .rodata or .sdata")
    return dict(status="absent", rows=[], notes=notes)


def literal_rows(row, lits, target, obj):
    """The literals as rows: one per run of a section's literals that lie
    next to each other in the target (with at most the alignment padding of
    the next one between them: fewer than 8 zero bytes), those written at
    the definition (def) and those after the code apart."""
    rows = []
    for cls, sec, at_def in (("lit4", ".lit4", False), ("rdlit", ".rodata", False), ("sdlit", ".sdata", False),
                             ("rdlit", ".rodata", True), ("sdlit", ".sdata", True)):
        mine = sorted((a, a + n, k) for c, a, n, k, _, d in lits if c == cls and d == at_def)
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
            if at_def:
                toks.append("def")
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
            got = {r["stem"]: absent_result(r, target, str(ex)) for r in rows_tu}
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
                     + (f" file={r['stem']}" if r["stem"] != r["name"] else "")
                     + (f" in={r['src']}" if r["src"] != r["tu"] and r["section"] not in LITERALS else "")
                     + (" inline" if r["inline"] else "")
                     + (" def" if r["at_def"] else ""))
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
            # a def row added to a function carved without it needs its
            # INCLUDE_ASM_LIT line where the definition stood
            rc = place_lits(parse_stubs(a.stubs), results, a.rev) or rc
        return rc
    if a.carve or a.carve_all:
        todo = [text_row(rows, a.carve)] if a.carve else [r for r in rows if r["section"] == "text"]
        rc = 0
        if not a.no_literals:
            # derived while the functions are still C
            src = {}
            fresh = [r for r in todo if asm_line(r["stem"]) not in src.setdefault(
                r["asm"], src_path(r["asm"]).read_bytes().splitlines(keepends=True))]
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
            bufs = [section_bytes(elf, r, "the base ELF") for r in rs]
            wrote += write_if_changed(a.out_dir / f"{stem}.s", write_stub(rs, bufs))
            if any(r["at_def"] for r in rs):
                wrote += write_if_changed(a.out_dir / f"{stem}.lit.s", write_lit_stub(rs, bufs))
    print(f"gen_stub_s: {len(stems)} stubs and {HEADER}, {wrote} written to {a.out_dir}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
