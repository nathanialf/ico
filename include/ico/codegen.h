/*
 * include/ico/codegen.h — codegen workarounds for ee-gcc 2.96
 *
 * The PS2 ICO matching toolchain uses ee-gcc 2.96 + the bundled
 * ee-as 2.10 (per `tools/setup.sh`). For some classes of original
 * codegen, the compiler/assembler can't be coaxed into the right
 * instruction shape from natural C alone. The macros in this header
 * wrap the inline-asm workarounds for those classes so the .c files
 * in src/cod/ can stay free of __asm__ blocks themselves — same
 * convention SOTC follows in include/sdk/ee/.
 *
 * Add a macro here, document the failure mode, and use it from src/.
 * If a future toolchain fix retires the need, drop the macro and the
 * src files become naturally-matching C with no hand-holding.
 */

#ifndef ICO_CODEGEN_H
#define ICO_CODEGEN_H

/*
 * LA_INDEXED_GP — load address of `&BASE_SYM[<scaled idx>]` where the
 * index sits at GP-relative `IDX_SYM` (sdata/sbss). The natural C
 *
 *     return &BASE_SYM[IDX_SYM << SCALE_LOG2 / sizeof(int)];
 *
 * compiles to ee-gcc's `la $X, BASE($X)` macro, which ee-as expands
 * via $at when destination and offset share a register:
 *
 *     lui   $at, %hi(BASE)
 *     addiu $at, $at, %lo(BASE)
 *     addu  $X,  $at, $X
 *
 * The original ICO codegen instead allocates a separate register for
 * the address and the offset, producing a tighter encoding:
 *
 *     lw    $v1, %gp_rel(IDX_SYM)($gp)
 *     lui   $v0, %hi(BASE_SYM)
 *     addiu $v0, $v0, %lo(BASE_SYM)
 *     sll   $v1, $v1, SCALE_LOG2
 *     jr    $ra
 *      addu $v0, $v1, $v0
 *
 * This macro emits exactly that 6-instruction sequence with the load
 * pinned to $v1 and the address pinned to $v0, then returns the $v0
 * value to the caller. Use as the body of a leaf function:
 *
 *     int *func_X(void) { return LA_INDEXED_GP(BASE, IDX, 4); }
 */
#define LA_INDEXED_GP(BASE_SYM, IDX_SYM, SCALE_LOG2)            \
    ({                                                          \
        register int *_p __asm__("$2");                         \
        __asm__ (                                               \
            "lw $3, %%gp_rel(" #IDX_SYM ")($gp)\n\t"            \
            "lui $2, %%hi(" #BASE_SYM ")\n\t"                   \
            "addiu $2, $2, %%lo(" #BASE_SYM ")\n\t"             \
            "sll $3, $3, " #SCALE_LOG2 "\n\t"                   \
            "addu $2, $3, $2"                                    \
            : "=r"(_p) : : "$3"                                  \
        );                                                       \
        _p;                                                      \
    })

#endif /* ICO_CODEGEN_H */
