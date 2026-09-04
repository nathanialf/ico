/*
 * include/b50climb.h — a `.h` used as an include-once CODE file by the `fumi`
 * programmer's boyact.c.
 *
 * PROVENANCE.  Dev path `omori/include/b50climb.h`, textually included from
 * `fumi/src/boyact.c` as `../omori/include/b50climb.h`, so the ROM emits its
 * functions into boyact's object.  `baserom/pal/SRCFILE.TXT` attributes
 * WHOLE FUNCTIONS to it (census: decomp/pal_source_tree.md, section
 * `fumi/../omori/include/b50climb.h`):
 *
 *   afterBoyHand50     header lines 5-7, 16 insns
 *   actBoyHand50       header lines 11-30, 36 insns
 *   motBoyHand50       header lines 33-52, 68 insns
 *
 * The names above ARE the developer's: each function is emitted out of line
 * and carries a label in the listing's symbol table.
 *
 * TODO — no bodies are written here, and none may be derived from the
 * listing.  `SRCFILE.TXT` disassembles a DIFFERENT LINK from the retail ELF
 * we build (its .text is 0x00100000..0x0028DB34 vs retail's
 * 0x00100000..0x00289BC4), and these functions are instrumented there:
 * every act*Hand* entry point in the six climb headers opens with a `printf`
 * gated on a debug global (checked for all six).
 * None of them correlates to a retail VMA — every `pal vma` cell in the
 * census section is blank — so nothing written from the listing could be
 * gated against the ROM we build.  Write each function here,
 * with `boyact.c` `#include`-ing this header at the point the census's
 * emission order requires, only when its retail counterpart has been
 * identified in boyact and matched.
 */
#ifndef B50CLIMB_H
#define B50CLIMB_H

#endif /* B50CLIMB_H */
