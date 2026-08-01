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

Usage: preprocess_old_as.py [--modern] <in.s> <out.s>

--modern: flatten for MODERN gas instead (a TU listed in
config/use_modern_as.txt). Includes are inlined the same way, but the
dialect translation is reversed: %gp_rel spellings are LEFT ALONE (modern
gas parses them natively, no .extern header needed) and the r5900 special
VU0 registers ACC / Q / R — bare in splat's output, the period
assembler's dialect — are rewritten to the `$`-prefixed spelling modern
gas requires. Operand-position only (`<space-or-comma>ACC`), so an
already-`$`-prefixed form is never doubled.
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
# --modern: bare r5900 special VU0 registers (period dialect) -> $-form for
# modern gas. Operand position only; `$ACC` has `$` before it, so no double-$.
BARE_VU0_SPECIAL = re.compile(r"([\t ,])(ACC|Q|R)\b")


def symname(expr):
    m = SYMNAME.match(expr.strip())
    return m.group(0) if m else expr.strip()


def flatten(path, out, syms, seen, modern=False):
    for line in open(path):
        m = INCLUDE.match(line)
        if m:
            inc = m.group(1)
            # Only inline assembly siblings (the splat .s); leave .inc/labels
            # alone so the assembler resolves them on its own include path.
            if inc.endswith(".s") and os.path.exists(inc) and inc not in seen:
                seen.add(inc)
                flatten(inc, out, syms, seen, modern)
                continue
            out.append(line)
            continue
        if modern:
            # Modern gas parses %gp_rel natively; only the VU0 special-register
            # dialect needs translating (bare -> $-form).
            out.append(BARE_VU0_SPECIAL.sub(r"\1$\2", line))
            continue
        # address-take `addiu $d,$28,%gp_rel(SYM)` -> `la $d, SYM` (GPREL16);
        # then load/store `%gp_rel(SYM)($28)` -> `SYM`; then any bare remainder.
        line = GP_REL_ADDR.sub(
            lambda mm: syms.add(symname(mm.group(2))) or "la\t%s, %s" % (mm.group(1), mm.group(2)), line)
        line = GP_REL.sub(lambda mm: syms.add(symname(mm.group(1))) or mm.group(1), line)
        line = GP_REL_ANY.sub(lambda mm: syms.add(symname(mm.group(1))) or mm.group(1), line)
        out.append(line)


def main():
    args = sys.argv[1:]
    modern = False
    if args and args[0] == "--modern":
        modern = True
        args = args[1:]
    src, dst = args[0], args[1]
    out, syms, seen = [], set(), set()
    flatten(src, out, syms, seen, modern)
    hdr = "" if modern else "".join(".extern %s, 4\n" % s for s in sorted(syms))
    with open(dst, "w") as f:
        f.write(hdr)
        f.writelines(out)


if __name__ == "__main__":
    main()
