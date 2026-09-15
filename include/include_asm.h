#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#if !defined(M2CTX) && !defined(PERMUTER)

#ifndef INCLUDE_ASM
/* .set at: splat-emitted .s files use compact gp_rel pseudos like
 * `lwc1 $f21, (D_006313F4)` that ee-as resolves via a macro which may
 * need $at for the %hi/%lo fallback. Under .set noat ee-as errors out
 * on these ("macro used $at after .set noat"). Most .s files work
 * with .set at as default, and every .s file in the tree does. A `.set noat`
 * variant and a `.text.<NAME>` function-section variant both lived here and
 * were never used by any TU; recover either from git history if one is ever
 * needed. */
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__( \
        ".section .text\n" \
        "    .set at\n" \
        "    .set noreorder\n" \
        "    .include \"" FOLDER "/" #NAME ".s\"\n" \
        "    .set reorder\n" \
        "    .set at\n" \
    )

#endif

/* A carved `.lit4` constant pool is built by the ASSEMBLER, not the compiler:
 * ee-gcc emits `li.s $fN,<value>` for a float constant and ee-as interns it
 * into the object's anonymous `.lit4`, appending each new literal in the order
 * the loads appear in the emitted `.s`. A TU's pool is therefore ONE output
 * section whose contents are fixed by source order, so a TU cannot anchor its
 * pool at the shipped VMA until every word of that run is produced by its own
 * object.
 *
 * Nothing in the C is needed for the words whose owner is still a stub. The
 * literal belongs to the function that owns it, so splat renders that stub's
 * load as `li.s $fN, <ROM value>` (tools/patch_splat.py, "carved .lit4
 * literal") and ee-as interns the word at the stub's own place in the file.
 * The ASM_LIT4_SLOT macro that used to carry those words on a line beside the
 * stub went with that change on 2026-09-15; recover it from git history if the
 * model is ever needed again. */

/* The label macros. There is one dialect and one assembler: include/labels.inc
 * speaks the period ee-as 2.9-991111's spelling, and that assembler builds
 * every object in the tree. The modern-gas twin (include/macro.inc, selected by
 * an INCLUDE_ASM_USE_MACRO_INC toggle) went with the last modern-gas objects on
 * 2026-09-15. */
__asm__(".include \"include/labels.inc\"\n");

#else

#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)
#endif

#endif /* !defined(M2CTX) && !defined(PERMUTER) */

#endif /* INCLUDE_ASM_H */
