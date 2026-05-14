#!/usr/bin/env python3
"""
mask_gp_rel.py — mask the quick_diff vs full-build gp-rel cosmetic.

Background: `tools/quick_diff.sh` builds two `.o` files — one from
the splat-extracted `asm/matchings/<func>.s` (the "target") and one
from compiling the candidate `src/<TU>.c` with ee-gcc (the "built").
Both are *unlinked* relocatable objects, but each goes through a
different assembler path that handles gp-relative addressing
differently:

* The target asm carries the splat-emitted mnemonic
  `lw $a0, %gp_rel(D_00632014)($gp)`. ee-as (and mips-linux-gnu-as)
  emit this as a `R_MIPS_GPREL16` relocation against `D_00632014`
  with **immediate 0** in the instruction word. `objdump -d` shows:

      lw   a0, 0(gp)

* The built side comes from ee-gcc emitting `lw $a0, D_00632014`. If
  the symbol is **defined locally** in the same .c (e.g. after a
  Phase 3d promotion that brought the function and its sdata def
  into one TU), ee-as resolves the gp-relative offset at assembly
  time, encoding it as a literal immediate. `objdump -d` shows:

      lw   a0, -16384(gp)

The two values describe the same load. They diverge only because
the splat side defers offset resolution to the linker while the
ee-gcc side folds it in. The full build links both flavors to the
same bytes, which is why the round-trip SHA still matches.

This script reads `<target_file> <built_file>` in parallel and, at
each line position where the diagnostic signature is present —

    target has `,0(gp)`     AND     built has `,<N>(gp)` for N != 0

rewrites both occurrences to `,GP_REL(gp)` so the downstream diff
collapses to MATCH. Every other gp-rel shape (both 0, both same N,
or `(gp)` against any non-gp register that the regex never matches)
is left untouched.

The narrow signature is deliberate. A looser mask — say, normalize
*any* `,<N>(gp)` on either side — would hide real divergence
between two different gp-rel symbols that happen to share an
instruction position (e.g. a typo where the candidate references
`D_00632018` instead of `D_00632014`, both small-data, both
gp_rel). The exact-`0` anchor on the target side keeps that
bug-finding signal intact.

Without this guardrail: every quick_diff run on a function with
gp_rel references produces a noisy side-by-side diff where the
developer has to visually filter the offset column to confirm the
codegen agrees. Easy to mis-read; easy to assume a true mismatch
and park a function that actually matches.

Usage: mask_gp_rel.py <target_file> <built_file>

Rewrites both files in place.
"""

from __future__ import annotations

import re
import sys

ZERO_GP_RE = re.compile(r',0\(gp\)')
ANY_GP_RE = re.compile(r',-?\d+\(gp\)')


def main(argv: list[str]) -> int:
    if len(argv) != 3:
        sys.exit("usage: mask_gp_rel.py <target_file> <built_file>")
    target_path, built_path = argv[1], argv[2]

    target_lines = open(target_path).readlines()
    built_lines = open(built_path).readlines()

    n = min(len(target_lines), len(built_lines))
    for i in range(n):
        t, b = target_lines[i], built_lines[i]
        # Only mask the quick_diff cosmetic: target has the
        # unresolved `,0(gp)` (splat-emitted %gp_rel reloc) AND
        # built has a resolved non-zero gp-rel offset (ee-as folded
        # in the local symbol). If both sides agree (both 0, both
        # same N), the diff already matches and masking is a no-op.
        # If they disagree any other way, masking would hide a real
        # divergence.
        if (
            ZERO_GP_RE.search(t)
            and ANY_GP_RE.search(b)
            and not ZERO_GP_RE.search(b)
        ):
            target_lines[i] = ZERO_GP_RE.sub(',GP_REL(gp)', t)
            built_lines[i] = ANY_GP_RE.sub(',GP_REL(gp)', b)

    open(target_path, 'w').writelines(target_lines)
    open(built_path, 'w').writelines(built_lines)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
