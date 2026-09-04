/*
 * include/syscall.h — handwritten EE-syscall leaf wrapper macros.
 *
 * Pattern is the same as ps2sdk's `ee/kernel/src/kernel.S` SYSCALL_SPECIAL
 * macro (4-instruction body: addiu $3, $0, NUM; syscall 0; jr $31; nop).
 * We keep the macro in C-callable form so the leaves live in `src/cod/<off>.c`
 * as a single SYSCALL_WRAPPER(...) line — gcc's epilogue supplies jr/nop.
 *
 * The original ICO ELF places these stubs at fixed file offsets `0x000110`
 * through `0x0009XX`. Each .c file claims one offset via a single macro
 * call; the macro expands to a function definition with inline asm body.
 *
 * Usage:
 *     #include "syscall.h"
 *     SYSCALL_WRAPPER(ResetEE, 0x1)
 *
 * Constraints:
 *   - The function name must be a valid identifier matching the address.
 *   - The syscall number must be a literal that ee-as can place into the
 *     16-bit immediate field of `addiu` (signed -0x8000..0x7FFF).
 */

#ifndef SYSCALL_H
#define SYSCALL_H

#define SYSCALL_WRAPPER(name, num)                                              \
    void name(void) {                                                           \
        __asm__ __volatile__("addiu $3, $zero, " #num "\n\tsyscall 0"           \
                             : : : "$3", "memory");                             \
    }

/* SYSCALL_INLINE(num, dst) — the same four-instruction leaf, but issued
 * INLINE inside a larger function rather than as its own stub. Several
 * libkernl functions do their own syscall and then act on the result, so
 * the leaf form cannot express them.
 *
 * `dst` has to be bound to $v0 explicitly: the syscall's result arrives
 * there by the kernel ABI, and a plain "=r" output would let gcc pick a
 * register the kernel never writes. This is operand binding, not a
 * scheduling pin.
 */
#define SYSCALL_INLINE(num, dst)                                                \
    do {                                                                        \
        register int __sc_ret __asm__("$2");                                    \
        __asm__ __volatile__("addiu $3, $zero, " #num "\n\tsyscall 0"          \
                             : "=r"(__sc_ret) : : "$3", "memory");              \
        (dst) = __sc_ret;                                                       \
    } while (0)

#endif /* SYSCALL_H */
