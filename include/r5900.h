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

#endif /* R5900_H */
