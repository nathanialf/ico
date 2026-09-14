/*
 * include/g50climb.h — a `.h` used as an include-once CODE file by the `fumi`
 * programmer's girl_act.c.
 *
 * PROVENANCE.  Dev path `omori/include/g50climb.h`, textually included from
 * `fumi/src/girl_act.c` as `../omori/include/g50climb.h`, so the ROM emits its
 * functions into girl_act's object.  `baserom/pal/SRCFILE.TXT` attributes
 * WHOLE FUNCTIONS to it (census: decomp/pal_source_tree.md, section
 * `fumi/../omori/include/g50climb.h`):
 *
 *   afterGirlHand50    header lines 6-9, 17 insns
 *   actGirlHand50      header lines 14-40, 46 insns
 *   motGirlHand50      header lines 43-73, 98 insns
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
 * with `girl_act.c` `#include`-ing this header at the point the census's
 * emission order requires, only when its retail counterpart has been
 * identified in girl_act and matched.
 */
#ifndef G50CLIMB_H
#define G50CLIMB_H

#endif /* G50CLIMB_H */
