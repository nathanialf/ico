#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#if !defined(M2CTX) && !defined(PERMUTER)

#ifndef INCLUDE_ASM
/* .set at: splat-emitted .s files use compact gp_rel pseudos like
 * `lwc1 $f21, (D_006313F4)` that ee-as resolves via a macro which may
 * need $at for the %hi/%lo fallback. Under .set noat ee-as errors out
 * on these ("macro used $at after .set noat"). Most .s files work
 * with .set at as default; for files whose explicit `daddu reg,reg,$0`
 * instructions get canonicalized away under .set at, use the
 * INCLUDE_ASM_NOAT variant. */
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__( \
        ".section .text\n" \
        "    .set at\n" \
        "    .set noreorder\n" \
        "    .include \"" FOLDER "/" #NAME ".s\"\n" \
        "    .set reorder\n" \
        "    .set at\n" \
    )

/* INCLUDE_ASM_NOAT — variant of INCLUDE_ASM with .set noat, for the
 * rare .s file whose explicit `daddu reg,reg,$0` instructions get
 * canonicalized to `or reg,reg,$0` under the default .set at (same
 * semantics, different encoding → SHA mismatch). Trades macro
 * resolution for verbatim opcode preservation. */
#ifndef INCLUDE_ASM_NOAT
#define INCLUDE_ASM_NOAT(FOLDER, NAME) \
    __asm__( \
        ".section .text\n" \
        "    .set noat\n" \
        "    .set noreorder\n" \
        "    .include \"" FOLDER "/" #NAME ".s\"\n" \
        "    .set reorder\n" \
        "    .set at\n" \
    )
#endif

#endif

/* INCLUDE_ASM_FS — function-section variant: place the included asm function
 * in its own `.text.<NAME>` section (mirroring gcc's -ffunction-sections for C
 * functions) so a TU whose final link order differs from source order (e.g. a
 * trace-reordered unit like box.o) can have its function sections placed
 * explicitly by VMA in the linker script. Byte-identical to INCLUDE_ASM modulo
 * the section name. Used in box.c/switch.c (see config/extra_cflags.txt BOX). */
#ifndef INCLUDE_ASM_FS
#define INCLUDE_ASM_FS(FOLDER, NAME) \
    __asm__( \
        ".section .text." #NAME ",\"ax\",@progbits\n" \
        "    .set at\n" \
        "    .set noreorder\n" \
        "    .include \"" FOLDER "/" #NAME ".s\"\n" \
        "    .set reorder\n" \
        "    .set at\n" \
    )
#endif

#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME) \
    __asm__( \
        ".section .rodata\n" \
        "    .include \"" FOLDER "/" #NAME ".s\"\n" \
        ".section .text" \
    )
#endif

/* ASM_LIT4_SLOT(NAME, VALUE) — one word of this TU's `.lit4` constant pool
 * whose owning function is still INCLUDE_ASM. Put it next to that sibling.
 *
 * `.lit4` is built by the ASSEMBLER, not the compiler: ee-gcc emits
 * `li.s $fN,<value>` for a float constant and ee-as interns it into the
 * object's anonymous `.lit4`, appending each new literal in the order the
 * macros appear in the emitted `.s`. A TU's pool is therefore ONE output
 * section whose contents are fixed by source order — it cannot be carved per
 * function, so a TU cannot migrate its constants to inline literals (and drop
 * the scheduling crutches the named-global carve forces) until every word of
 * its shipped pool run is produced by that TU.
 *
 * The obvious fix — define the missing words as data in `.lit4` so the
 * siblings' `%gp_rel(D_<VMA>)($28)` still resolves — is IMPOSSIBLE with the
 * period assembler: `nopic_need_relax()` (tc-mips.c:11141) asserts that no
 * symbol it is asked about lives in `.lit4`, since in its model that section
 * only ever holds anonymous literals it interned itself. Defining a named
 * symbol there and referencing it from the same file aborts ee-as with
 * "Internal error! Assertion failure in nopic_need_relax".
 *
 * So this macro emits a `.lit4_slot` directive instead, and
 * tools/preprocess_old_as.py rewrites the sibling's load back to
 * `li.s $fN, VALUE` — the spelling the original .s had before splat
 * symbolized the pool address. Same instruction, same gp-relative encoding,
 * and ee-as interns the word at that point in the file, i.e. in the sibling's
 * shipped slot. No `D_<VMA>` symbol is needed or created.
 *
 * Delete the line when its owner lands in C — that function's own literal
 * then produces the word, and preprocess_old_as.py errors if a stale line is
 * left behind. */
#ifndef ASM_LIT4_SLOT
#define ASM_LIT4_SLOT(NAME, VALUE) \
    __asm__(".lit4_slot " #NAME ", " #VALUE)
#endif

/* INCLUDE_ASM_NOP_PAD(label) — emit a single 4-byte nop in .text.
 *
 * Splat omits per-function .s files for tiny pad functions (verified
 * 4-byte nops sitting between real functions for alignment). When a
 * coalesced TU's c subseg covers a range that includes such a pad,
 * INCLUDE_ASM(... pad_func) fails with "can't open .../<pad>.s for
 * reading". This macro emits the exact 4-byte nop the original ELF
 * has at that location — functionally identical, not a fabrication.
 * The `label` argument is the func name from the original disasm
 * (e.g. func_001FA5DC); it's used as a label in the emitted asm so
 * relocations targeting it still resolve. */
#ifndef INCLUDE_ASM_NOP_PAD
#define INCLUDE_ASM_NOP_PAD(LABEL) \
    __asm__( \
        ".section .text\n" \
        "    .align 2\n" \
        "    .globl " #LABEL "\n" \
        "    .type " #LABEL ", @function\n" \
        #LABEL ":\n" \
        "    nop\n" \
        "    .size " #LABEL ", . - " #LABEL "\n" \
    )
#endif

#if INCLUDE_ASM_USE_MACRO_INC
__asm__(".include \"include/macro.inc\"\n");
#else
__asm__(".include \"include/labels.inc\"\n");
#endif

#else

#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)
#endif
#ifndef INCLUDE_ASM_NOAT
#define INCLUDE_ASM_NOAT(FOLDER, NAME)
#endif
#ifndef INCLUDE_ASM_FS
#define INCLUDE_ASM_FS(FOLDER, NAME)
#endif
#ifndef INCLUDE_ASM_NOP_PAD
#define INCLUDE_ASM_NOP_PAD(LABEL)
#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME)
#endif
/* Pure assembler bookkeeping — nothing for m2c/permuter to model. */
#ifndef ASM_LIT4_SLOT
#define ASM_LIT4_SLOT(NAME, VALUE)
#endif

#endif /* !defined(M2CTX) && !defined(PERMUTER) */

#endif /* INCLUDE_ASM_H */
