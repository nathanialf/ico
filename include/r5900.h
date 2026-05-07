/*
 * include/r5900.h — R5900-specific opcode macros that have no native
 * C representation (memory barriers, cache ops, etc.).
 *
 * Each macro emits exactly one R5900 instruction inside a volatile
 * inline-asm block, satisfying the project rule "one instruction per
 * __asm__ block."  The asm body lives here in the header so that
 * src/cod/<off>.c source remains free of raw inline asm.
 *
 * Naming follows ps2sdk's `ee/kernel/include/kernel.h` style.
 */

#ifndef R5900_H
#define R5900_H

/* Memory sync barrier — stalls the CPU until pending stores commit.
 * EE-kernel-flavoured; equivalent of MIPS `sync` opcode.
 * Used as a fence between a write and an external observer (e.g.
 * GS, IPU, VU0/1, DMAC). */
#define SYNC()      __asm__ __volatile__("sync"   : : : "memory")

/* Quadword copy — single 128-bit `lq`/`sq` pair via a scratch GPR
 * (e.g. `$a2`, `$t0`).  The original ICO codegen uses a different
 * scratch register per call site, so the scratch is exposed as a
 * macro argument.  A trailing nop is required to match the
 * original's lq+sq+nop shape.
 *
 * The dst/src are implicit from gcc's $a0/$a1 setup — the wrapper
 * is intended to be called as `qcopy16(dst, src)` with pointer args
 * in normal calling convention; the macro is the BODY of that
 * wrapper.  Caller must declare with `(void *dst, void *src)`
 * signature so a0/a1 carry the pointers. */
#define QCOPY16(scratch)                                                       \
    __asm__ __volatile__("lq " scratch ", 0($a1)" : : : "memory");             \
    __asm__ __volatile__("sq " scratch ", 0($a0)" : : : "memory");             \
    __asm__ __volatile__("nop")

/* Same, but no trailing nop — matches the variant where the next
 * function's first insn fills the implicit jr-ra delay slot. */
#define QCOPY16_NO_NOP(scratch)                                                \
    __asm__ __volatile__("lq " scratch ", 0($a1)" : : : "memory");             \
    __asm__ __volatile__("sq " scratch ", 0($a0)" : : : "memory")

#endif /* R5900_H */
