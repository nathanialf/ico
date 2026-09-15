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

/* ASM_LIT4_SLOT(NAME, VALUE), one word of this TU's `.lit4` constant pool
 * whose owning function is still INCLUDE_ASM. Put it next to that sibling.
 *
 * `.lit4` is built by the ASSEMBLER, not the compiler: ee-gcc emits
 * `li.s $fN,<value>` for a float constant and ee-as interns it into the
 * object's anonymous `.lit4`, appending each new literal in the order the
 * macros appear in the emitted `.s`. A TU's pool is therefore ONE output
 * section whose contents are fixed by source order, it cannot be carved per
 * function, so a TU cannot migrate its constants to inline literals (and drop
 * the scheduling crutches the named-global carve forces) until every word of
 * its shipped pool run is produced by that TU.
 *
 * The obvious fix, define the missing words as data in `.lit4` so the
 * siblings' `%gp_rel(D_<VMA>)($28)` still resolves, is IMPOSSIBLE with the
 * period assembler: `nopic_need_relax()` (tc-mips.c:11141) asserts that no
 * symbol it is asked about lives in `.lit4`, since in its model that section
 * only ever holds anonymous literals it interned itself. Defining a named
 * symbol there and referencing it from the same file aborts ee-as with
 * "Internal error! Assertion failure in nopic_need_relax".
 *
 * So this macro emits a `.lit4_slot` directive instead, and
 * tools/preprocess_old_as.py rewrites the sibling's load back to
 * `li.s $fN, VALUE`, the spelling the original .s had before splat
 * symbolized the pool address. Same instruction, same gp-relative encoding,
 * and ee-as interns the word at that point in the file, i.e. in the sibling's
 * shipped slot. No `D_<VMA>` symbol is needed or created.
 *
 * Delete the line when its owner lands in C, that function's own literal
 * then produces the word, and preprocess_old_as.py errors if a stale line is
 * left behind. */
#ifndef ASM_LIT4_SLOT
#define ASM_LIT4_SLOT(NAME, VALUE) \
    __asm__(".lit4_slot " #NAME ", " #VALUE)
#endif

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
/* Pure assembler bookkeeping, nothing for m2c/permuter to model. */
#ifndef ASM_LIT4_SLOT
#define ASM_LIT4_SLOT(NAME, VALUE)
#endif

#endif /* !defined(M2CTX) && !defined(PERMUTER) */

#endif /* INCLUDE_ASM_H */
