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
"""
import os
import re
import sys

GP_REL = re.compile(r"%gp_rel\(([^)]+)\)\(\$\d+\)")
INCLUDE = re.compile(r'^\s*\.include\s+"([^"]+)"')


def flatten(path, out, syms, seen):
    for line in open(path):
        m = INCLUDE.match(line)
        if m:
            inc = m.group(1)
            # Only inline assembly siblings (the splat .s); leave .inc/labels
            # alone so the assembler resolves them on its own include path.
            if inc.endswith(".s") and os.path.exists(inc) and inc not in seen:
                seen.add(inc)
                flatten(inc, out, syms, seen)
                continue
            out.append(line)
            continue
        out.append(GP_REL.sub(lambda mm: syms.add(mm.group(1)) or mm.group(1), line))


def main():
    src, dst = sys.argv[1], sys.argv[2]
    out, syms, seen = [], set(), set()
    flatten(src, out, syms, seen)
    hdr = "".join(".extern %s, 4\n" % s for s in sorted(syms))
    with open(dst, "w") as f:
        f.write(hdr)
        f.writelines(out)


if __name__ == "__main__":
    main()
