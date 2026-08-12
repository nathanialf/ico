#!/usr/bin/env python3
"""Flatten + gp_rel-translate a gcc-emitted .s so the PERIOD assembler
(ee-as 2.9-991111) can assemble a MIXED TU (C funcs + splat INCLUDE_ASM
siblings).

Why: ee-as 2.9-991111 is the ROM's contemporary assembler — it leaves a
jal/jr delay as `nop` where modern gas (the fallback) over-fills it with a
preceding store. To use it on a partially-decompiled TU we must feed it the
TU's full .s, but splat's INCLUDE_ASM siblings use the modern
`%gp_rel(SYM)($28)` relocation spelling, which 2.9-991111 rejects
("Bad expression"). 2.9-991111 DOES emit the identical R_MIPS_GPREL16
encoding from a BARE small-symbol reference (`lw $5, SYM`) when SYM is
declared gp-addressable via `.extern SYM, <=G>`. So:

  * inline every `.include "….s"` (the gcc .s pulls siblings in this way),
  * rewrite `%gp_rel(SYM)($28)`  ->  `SYM`,
  * prepend `.extern SYM, 4` for each such SYM (size<=G marks it gp-addressable;
    the real definition + size live elsewhere — the linker resolves GPREL16
    against it regardless of this hint).

%hi/%lo are left untouched (2.9-991111 accepts them). The result is
byte-identical to the modern-as encoding for the gp_rel refs, and lets the
period assembler set the delay-slot bytes the ROM actually has.

Usage: preprocess_old_as.py <in.s> <out.s>

--modern is RETIRED (2026-08-05) and now hard-errors. It used to flatten for
MODERN gas (for a TU listed in the since-deleted config/use_modern_as.txt),
reversing the dialect translation. The whole modern-gas path is gone because
that assembler fills delay slots ee-as 2.9-991111 leaves bare, so anything
reaching it could read as MATCHED on the assembler's scheduling rather than on
source shape. See decomp/NOTES.md "There is NO modern-gas path any more".
The `modern` plumbing below is left inert rather than ripped out so the dialect
mapping stays documented in one place.
"""
import os
import re
import sys

# address-take form: `addiu $d, $28, %gp_rel(SYM)` -> `la $d, SYM`.
# MUST use the `la` macro, NOT `addiu $d,$28,SYM`: the period assembler expands
# `la $d,SYM` (SYM gp-addressable via `.extern SYM,<=G>`) to `addiu $d,$gp,SYM`
# with R_MIPS_GPREL16 — the ROM's 32-bit form. A literal `addiu $d,$28,SYM`
# resolves SYM as R_MIPS_LO16 (absolute) in-context, which is wrong.
GP_REL_ADDR = re.compile(r"addiu\s+(\$\w+),\s*\$28,\s*%gp_rel\(([^)]+)\)")
# load/store form: `lw $d, %gp_rel(SYM)($28)` -> `lw $d, SYM`
GP_REL = re.compile(r"%gp_rel\(([^)]+)\)\(\$\d+\)")
# any remaining bare %gp_rel(SYM) -> SYM (fallback)
GP_REL_ANY = re.compile(r"%gp_rel\(([^)]+)\)")
INCLUDE = re.compile(r'^\s*\.include\s+"([^"]+)"')
# A %gp_rel() operand may carry an addend (`%gp_rel(D_00633C00 + 0xC)`).  The
# `.extern` header must name the SYMBOL only — `.extern SYM + 0xC, 4` is a
# syntax error the period assembler rejects, which silently drops the whole TU
# back to modern gas (and its over-filled jr/jal delay slots).
SYMNAME = re.compile(r"[A-Za-z_$.][A-Za-z0-9_$.]*")
# `.lit4_slot SYM, VALUE` — emitted by ASM_LIT4_SLOT() in include/include_asm.h
# for a `.lit4` constant-pool word whose owning function is still INCLUDE_ASM in
# a TU whose pool has been carved (a `[..., .lit4, <TU>]` subsegment in the splat
# yaml). See the macro's comment for the whole model; the part that lands here:
#
#   ee-as 2.9-991111 CANNOT assemble a named symbol that is defined in `.lit4`
#   and referenced from the same file. `nopic_need_relax()` (tc-mips.c:11141)
#   asserts `strcmp (segname, ".lit4") != 0` before deciding gp-addressability,
#   because in its model `.lit4` only ever holds anonymous literals interned by
#   the assembler itself. Defining the slot as data and letting the sibling's
#   `%gp_rel(D_<VMA>)($28)` resolve to it aborts the assembler outright
#   ("Internal error! Assertion failure in nopic_need_relax").
#
# So the sibling's load is restored to the spelling the original .s had before
# splat symbolized the pool address: `li.s $fN, <value>`, which makes ee-as
# intern the word itself at exactly that point in the file — same instruction,
# same R_MIPS_LITERAL gp-relative encoding, and the pool word lands in the
# sibling's shipped slot because ee-as appends literals in file order.
LIT4_SLOT = re.compile(r"^\s*\.lit4_slot\s+([A-Za-z_$.][\w$.]*)\s*,\s*(\S+)\s*$")
# The load to rewrite, before gp_rel translation. FP loads only — a slot reached
# by anything else means the `.lit4_slot` line names the wrong symbol.
LIT4_LOAD = re.compile(r"\b(?:lwc1|l\.s)(\s+)(\$f\d+|\$\w+),\s*%gp_rel\((\w+)\)\(\$\d+\)")
ANY_SYM_REF = re.compile(r"%gp_rel\((\w+)\)")
# --modern: bare r5900 special VU0 registers (period dialect) -> $-form for
# modern gas. Operand position only; `$ACC` has `$` before it, so no double-$.
BARE_VU0_SPECIAL = re.compile(r"([\t ,])(ACC|Q|R)\b")


def symname(expr):
    m = SYMNAME.match(expr.strip())
    return m.group(0) if m else expr.strip()


def flatten(path, out, seen, slots):
    """Inline every `.include "….s"` sibling, and lift out `.lit4_slot` lines.

    Collected untranslated: a `.lit4_slot` directive may appear either side of
    the load it governs, so the gp_rel translation runs as a second pass.
    """
    for line in open(path):
        m = INCLUDE.match(line)
        if m:
            inc = m.group(1)
            # Only inline assembly siblings (the splat .s); leave .inc/labels
            # alone so the assembler resolves them on its own include path.
            if inc.endswith(".s") and os.path.exists(inc) and inc not in seen:
                seen.add(inc)
                flatten(inc, out, seen, slots)
                continue
            out.append(line)
            continue
        m = LIT4_SLOT.match(line)
        if m:
            # `100000.0f` is C's spelling; the assembler wants `100000.0`.
            slots[m.group(1)] = m.group(2).rstrip("fF")
            continue
        out.append(line)


def translate(out, syms, slots, modern=False):
    used = set()
    for i, line in enumerate(out):
        if modern:
            # Modern gas parses %gp_rel natively; only the VU0 special-register
            # dialect needs translating (bare -> $-form).
            out[i] = BARE_VU0_SPECIAL.sub(r"\1$\2", line)
            continue
        if slots:
            # A carved-pool slot owned by an INCLUDE_ASM sibling: restore the
            # `li.s` the original .s had, so ee-as interns the word itself.
            def _lit4(mm):
                if mm.group(3) not in slots:
                    return mm.group(0)
                used.add(mm.group(3))
                return "li.s%s%s, %s" % (mm.group(1), mm.group(2), slots[mm.group(3)])
            line = LIT4_LOAD.sub(_lit4, line)
            bad = [s for s in ANY_SYM_REF.findall(line) if s in slots]
            if bad:
                sys.exit("preprocess_old_as.py: %s is declared ASM_LIT4_SLOT but is "
                         "referenced by something other than an FP load:\n  %s"
                         % (", ".join(bad), line.strip()))
        # address-take `addiu $d,$28,%gp_rel(SYM)` -> `la $d, SYM` (GPREL16);
        # then load/store `%gp_rel(SYM)($28)` -> `SYM`; then any bare remainder.
        line = GP_REL_ADDR.sub(
            lambda mm: syms.add(symname(mm.group(2))) or "la\t%s, %s" % (mm.group(1), mm.group(2)), line)
        line = GP_REL.sub(lambda mm: syms.add(symname(mm.group(1))) or mm.group(1), line)
        line = GP_REL_ANY.sub(lambda mm: syms.add(symname(mm.group(1))) or mm.group(1), line)
        out[i] = line
    stale = sorted(set(slots) - used)
    if stale and not modern:
        # A slot whose owner has landed in C: the function's own literal now
        # produces the word, so the ASM_LIT4_SLOT line must go or the pool ends
        # up one word short and the link shifts.
        sys.exit("preprocess_old_as.py: ASM_LIT4_SLOT declared for %s but no "
                 "INCLUDE_ASM sibling loads it — delete the line (its owner is "
                 "in C now?)." % ", ".join(stale))


def main():
    args = sys.argv[1:]
    modern = False
    if args and args[0] == "--modern":
        sys.exit(
            "preprocess_old_as.py: --modern is RETIRED (2026-08-05).\n"
            "  There is no modern-gas path: it fills delay slots ee-as\n"
            "  2.9-991111 leaves bare, so a TU assembled with it can read as\n"
            "  MATCHED on the assembler's scheduling instead of on source\n"
            "  shape (that produced 8 false matches, all reverted 2026-08-01).\n"
            "  A period-assembler rejection is a source defect to FIX — see\n"
            "  decomp/NOTES.md \"There is NO modern-gas path any more\"."
        )
    src, dst = args[0], args[1]
    out, syms, seen, slots = [], set(), set(), {}
    flatten(src, out, seen, slots)
    translate(out, syms, slots, modern)
    hdr = "" if modern else "".join(".extern %s, 4\n" % s for s in sorted(syms))
    with open(dst, "w") as f:
        f.write(hdr)
        f.writelines(out)


if __name__ == "__main__":
    main()
