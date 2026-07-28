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
 *     SYSCALL_WRAPPER(func_00100110, 0x1)
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

#endif /* SYSCALL_H */
