#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#if !defined(M2CTX) && !defined(PERMUTER)

#ifndef INCLUDE_ASM
/* .set at (not noat): splat-emitted .s files use compact gp_rel pseudo
 * forms like `lwc1 $f21, (D_006313F4)` that ee-as resolves via a macro
 * which may need $at for the %hi/%lo fallback path. Under .set noat,
 * ee-as errors out ("macro used $at after .set noat") on these lines.
 * .set at lets the macro use $at as needed; for gp_rel-reachable
 * symbols ee-as still prefers the 1-insn gp_rel form (no $at needed).
 * .set noreorder stays — delay-slot scheduling must be hand-controlled. */
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
