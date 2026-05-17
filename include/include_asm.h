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
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME) \
    __asm__( \
        ".section .rodata\n" \
        "    .include \"" FOLDER "/" #NAME ".s\"\n" \
        ".section .text" \
    )
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
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME)
#endif

#endif /* !defined(M2CTX) && !defined(PERMUTER) */

#endif /* INCLUDE_ASM_H */
