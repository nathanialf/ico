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

/*
 * LA_INDEXED_ARG_MULT — define a leaf returning `&BASE[arg * STRIDE]`
 * where STRIDE is *not* a power of two (so the codegen uses `mult`
 * instead of `sll`). Original ICO emission:
 *
 *     addiu $v1, $zero, STRIDE
 *     lui   $v0, %hi(BASE)
 *     mult  $a0, $a0, $v1            (R5900 3-operand mult)
 *     addiu $v0, $v0, %lo(BASE)
 *     jr    $ra
 *      addu $v0, $a0, $v0
 *
 * ee-gcc 2.96 ignores __attribute__((naked)), so the inline-asm
 * block ends with `jr $31`; the trailing redundant `j $31` the
 * compiler appends is stripped by tools/postprocess_inline_jr.py.
 *
 * Usage (top-level in a src/cod/<file_off>.c):
 *
 *     extern int D_006812D0[];
 *     DEFINE_LA_INDEXED_ARG_MULT(func_0012FE08, D_006812D0, 0x2E8)
 */
#define DEFINE_LA_INDEXED_ARG_MULT(name, BASE, STRIDE)              \
    int *name(int idx)                                              \
    {                                                               \
        register int *_p __asm__("$2");                             \
        __asm__ volatile (                                          \
            ".set noreorder\n\t"                                    \
            "addiu $3, $0, " #STRIDE "\n\t"                         \
            "lui $2, %%hi(" #BASE ")\n\t"                           \
            "mult $4, $4, $3\n\t"                                   \
            "addiu $2, $2, %%lo(" #BASE ")\n\t"                     \
            "jr $31\n\t"                                            \
            " addu $2, $4, $2\n\t"                                  \
            ".set reorder"                                          \
            : "=r"(_p) :: "$3", "$4"                                \
        );                                                          \
        return _p;                                                  \
    }

/*
 * DEFINE_LA_INDEXED_A1_LW — leaf returning `*(int*)(BASE + (a1 << SCALE)
 * + OFFSET)`. The index lives in $a1; the load lives in jr's delay slot.
 *
 *     lui   $v0, %hi(BASE)
 *     sll   $a1, $a1, SCALE
 *     addiu $v0, $v0, %lo(BASE)
 *     addu  $a1, $a1, $v0
 *     jr    $ra
 *      lw   $v0, OFFSET($a1)
 */
#define DEFINE_LA_INDEXED_A1_LW(name, BASE, SCALE_LOG2, OFFSET)     \
    int name(int unused, int idx)                                   \
    {                                                               \
        register int _r __asm__("$2");                              \
        __asm__ volatile (                                          \
            ".set noreorder\n\t"                                    \
            "lui $2, %%hi(" #BASE ")\n\t"                           \
            "sll $5, $5, " #SCALE_LOG2 "\n\t"                       \
            "addiu $2, $2, %%lo(" #BASE ")\n\t"                     \
            "addu $5, $5, $2\n\t"                                   \
            "jr $31\n\t"                                            \
            " lw $2, " #OFFSET "($5)\n\t"                           \
            ".set reorder"                                          \
            : "=r"(_r) :: "$5"                                      \
        );                                                          \
        return _r;                                                  \
    }

/*
 * DEFINE_LA_INDEXED_A0_LWC1 — leaf returning `BASE[idx]` as float.
 * Index in $a0; load is `lwc1` to $f0 in jr's delay slot.
 */
#define DEFINE_LA_INDEXED_A0_LWC1(name, BASE, SCALE_LOG2)           \
    float name(int idx)                                             \
    {                                                               \
        register float _r __asm__("$f0");                           \
        __asm__ volatile (                                          \
            ".set noreorder\n\t"                                    \
            "lui $2, %%hi(" #BASE ")\n\t"                           \
            "sll $4, $4, " #SCALE_LOG2 "\n\t"                       \
            "addiu $2, $2, %%lo(" #BASE ")\n\t"                     \
            "addu $4, $4, $2\n\t"                                   \
            "jr $31\n\t"                                            \
            " lwc1 $f0, 0($4)\n\t"                                  \
            ".set reorder"                                          \
            : "=f"(_r) :: "$2", "$4"                                \
        );                                                          \
        return _r;                                                  \
    }

/*
 * DEFINE_GETSET_SYM — atomic-looking get-and-set on a single sym:
 * returns the prior value, stores the new one. Shared `lui` for both
 * the lw and the sw, sw in jr's delay slot.
 *
 *     lui $v1, %hi(SYM)
 *     lw  $v0, %lo(SYM)($v1)
 *     jr  $ra
 *      sw $a0, %lo(SYM)($v1)
 */
#define DEFINE_GETSET_SYM(name, SYM)                                \
    int name(int new_val)                                           \
    {                                                               \
        register int _old __asm__("$2");                            \
        __asm__ volatile (                                          \
            ".set noreorder\n\t"                                    \
            "lui $3, %%hi(" #SYM ")\n\t"                            \
            "lw $2, %%lo(" #SYM ")($3)\n\t"                         \
            "jr $31\n\t"                                            \
            " sw $4, %%lo(" #SYM ")($3)\n\t"                        \
            ".set reorder"                                          \
            : "=r"(_old) :: "$3"                                    \
        );                                                          \
        return _old;                                                \
    }

/*
 * DEFINE_LA_INDEXED_A0_SW_GP — write `gp_rel(GP_VAL)` to
 * `BASE[idx<<SCALE]`. Index in $a0; sw in jr's delay slot.
 *
 *     lui   $v0, %hi(BASE)
 *     sll   $a0, $a0, SCALE
 *     addiu $v0, $v0, %lo(BASE)
 *     lw    $v1, %gp_rel(GP_VAL)($gp)
 *     addu  $a0, $a0, $v0
 *     jr    $ra
 *      sw   $v1, 0($a0)
 */
#define DEFINE_LA_INDEXED_A0_SW_GP(name, BASE, SCALE_LOG2, GP_VAL)  \
    void name(int idx)                                              \
    {                                                               \
        __asm__ volatile (                                          \
            ".set noreorder\n\t"                                    \
            "lui $2, %%hi(" #BASE ")\n\t"                           \
            "sll $4, $4, " #SCALE_LOG2 "\n\t"                       \
            "addiu $2, $2, %%lo(" #BASE ")\n\t"                     \
            "lw $3, %%gp_rel(" #GP_VAL ")($gp)\n\t"                 \
            "addu $4, $4, $2\n\t"                                   \
            "jr $31\n\t"                                            \
            " sw $3, 0($4)\n\t"                                     \
            ".set reorder"                                          \
            ::: "$2", "$3", "$4"                                    \
        );                                                          \
    }

/*
 * DEFINE_TAILCALL_LWA1 — tail-call wrapper:
 *
 *     name(int a0, int a1) {
 *         tail_target(a0, *(int*)(a1 + LW_OFFSET) + ADDIU_OFFSET);
 *     }
 *
 * Compiles to (3 insns):
 *
 *     lw    $a1, LW_OFFSET($a1)
 *     j     <tail_target>
 *      addiu $a1, $a1, ADDIU_OFFSET
 *
 * ee-gcc 2.96 + -fno-optimize-sibling-calls won't tail-call from
 * natural C, and -foptimize-sibling-calls is a no-op (sibcall not
 * implemented for MIPS in this gcc). Use inline asm; postprocess
 * strips the compiler's appended `j $31`.
 */
#define DEFINE_TAILCALL_LWA1(name, tail_target, lw_offset, addiu_offset) \
    void name(int a0, int a1)                                       \
    {                                                               \
        __asm__ volatile (                                          \
            ".set noreorder\n\t"                                    \
            "lw $5, " #lw_offset "($5)\n\t"                         \
            "j " #tail_target "\n\t"                                \
            " addiu $5, $5, " #addiu_offset "\n\t"                  \
            ".set reorder"                                          \
            ::: "$5"                                                \
        );                                                          \
    }

/*
 * DEFINE_LA_INDEXED_A0_LW — leaf returning `BASE[idx]` (4-byte stride
 * = sll+addu form). Index in $a0; lw at offset 0 in jr's delay slot.
 */
#define DEFINE_LA_INDEXED_A0_LW(name, BASE, SCALE_LOG2)             \
    int name(int idx)                                               \
    {                                                               \
        register int _r __asm__("$2");                              \
        __asm__ volatile (                                          \
            ".set noreorder\n\t"                                    \
            "lui $2, %%hi(" #BASE ")\n\t"                           \
            "sll $4, $4, " #SCALE_LOG2 "\n\t"                       \
            "addiu $2, $2, %%lo(" #BASE ")\n\t"                     \
            "addu $4, $4, $2\n\t"                                   \
            "jr $31\n\t"                                            \
            " lw $2, 0($4)\n\t"                                     \
            ".set reorder"                                          \
            : "=r"(_r) :: "$4"                                      \
        );                                                          \
        return _r;                                                  \
    }

/*
 * DEFINE_LA_INDEXED_A0_SW_A1 — write $a1 to `BASE[idx]` (4-byte stride =
 * sll+addu). Index in $a0; sw of $a1 in jr's delay slot.
 */
#define DEFINE_LA_INDEXED_A0_SW_A1(name, BASE, SCALE_LOG2)          \
    void name(int idx, int val)                                     \
    {                                                               \
        __asm__ volatile (                                          \
            ".set noreorder\n\t"                                    \
            "lui $2, %%hi(" #BASE ")\n\t"                           \
            "sll $4, $4, " #SCALE_LOG2 "\n\t"                       \
            "addiu $2, $2, %%lo(" #BASE ")\n\t"                     \
            "addu $4, $4, $2\n\t"                                   \
            "jr $31\n\t"                                            \
            " sw $5, 0($4)\n\t"                                     \
            ".set reorder"                                          \
            ::: "$2", "$4"                                          \
        );                                                          \
    }

/*
 * DEFINE_LA_INDEXED_A0_MULT_LW0 — non-power-of-two stride (uses mult),
 * returns `*(int*)(BASE + idx*STRIDE)`. Original puts `addu` into $a0
 * (since the lw offset is 0).
 */
#define DEFINE_LA_INDEXED_A0_MULT_LW0(name, BASE, STRIDE)           \
    int name(int idx)                                               \
    {                                                               \
        register int _r __asm__("$2");                              \
        __asm__ volatile (                                          \
            ".set noreorder\n\t"                                    \
            "addiu $3, $0, " #STRIDE "\n\t"                         \
            "lui $2, %%hi(" #BASE ")\n\t"                           \
            "mult $4, $4, $3\n\t"                                   \
            "addiu $2, $2, %%lo(" #BASE ")\n\t"                     \
            "addu $4, $4, $2\n\t"                                   \
            "jr $31\n\t"                                            \
            " lw $2, 0($4)\n\t"                                     \
            ".set reorder"                                          \
            : "=r"(_r) :: "$3", "$4"                                \
        );                                                          \
        return _r;                                                  \
    }

/*
 * DEFINE_LA_INDEXED_A0_MULT_LW — non-power-of-two stride, returns
 * `*(int*)(BASE + idx*STRIDE + OFFSET)`. The original allocates $v0
 * as the stride, $v1 as the base — register layout differs from the
 * offset-0 form because `lw` at non-zero offset needs the base to
 * survive the `addu` into a separate result register ($v1).
 */
#define DEFINE_LA_INDEXED_A0_MULT_LW(name, BASE, STRIDE, OFFSET)    \
    int name(int idx)                                               \
    {                                                               \
        register int _r __asm__("$2");                              \
        __asm__ volatile (                                          \
            ".set noreorder\n\t"                                    \
            "addiu $2, $0, " #STRIDE "\n\t"                         \
            "lui $3, %%hi(" #BASE ")\n\t"                           \
            "mult $4, $4, $2\n\t"                                   \
            "addiu $3, $3, %%lo(" #BASE ")\n\t"                     \
            "addu $3, $3, $4\n\t"                                   \
            "jr $31\n\t"                                            \
            " lw $2, " #OFFSET "($3)\n\t"                           \
            ".set reorder"                                          \
            : "=r"(_r) :: "$3", "$4"                                \
        );                                                          \
        return _r;                                                  \
    }

/*
 * DEFINE_LA_INDEXED_A0_MULT_SW_A1 — non-power-of-two stride, writes
 * $a1 to `*(int*)(BASE + idx*STRIDE + OFFSET)`. Same register layout
 * as DEFINE_LA_INDEXED_A0_MULT_LW (stride in $v0, base in $v0 via
 * mult-then-addu… actually picks $v0 for stride+base reuse).
 */
#define DEFINE_LA_INDEXED_A0_MULT_SW_A1(name, BASE, STRIDE, OFFSET) \
    void name(int idx, int val)                                     \
    {                                                               \
        __asm__ volatile (                                          \
            ".set noreorder\n\t"                                    \
            "addiu $3, $0, " #STRIDE "\n\t"                         \
            "lui $2, %%hi(" #BASE ")\n\t"                           \
            "mult $4, $4, $3\n\t"                                   \
            "addiu $2, $2, %%lo(" #BASE ")\n\t"                     \
            "addu $2, $2, $4\n\t"                                   \
            "jr $31\n\t"                                            \
            " sw $5, " #OFFSET "($2)\n\t"                           \
            ".set reorder"                                          \
            ::: "$2", "$3", "$4"                                    \
        );                                                          \
    }

#endif /* ICO_CODEGEN_H */
