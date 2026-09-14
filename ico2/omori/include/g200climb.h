/*
 * include/g200climb.h — a `.h` used as an include-once CODE file by the `fumi`
 * programmer's girl_act.c.
 *
 * PROVENANCE.  Dev path `omori/include/g200climb.h`, textually included from
 * `fumi/src/girl_act.c` as `../omori/include/g200climb.h`, so the ROM emits its
 * functions into girl_act's object.  `baserom/pal/SRCFILE.TXT` attributes
 * WHOLE FUNCTIONS to it (census: decomp/pal_source_tree.md, section
 * `fumi/../omori/include/g200climb.h`):
 *
 *   afterGirlHand200   header lines 7-10, 17 insns
 *   actGirlHand200     header lines 14-32, 36 insns
 *   motGirlHand200     header lines 35-59, 142 insns
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
#ifndef G200CLIMB_H
#define G200CLIMB_H

#endif /* G200CLIMB_H */
