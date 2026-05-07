/*
 * include/vu0.h — VU0/COP2 instruction macros for handwritten leaves.
 *
 * The R5900's VU0 macro mode exposes ~120 distinct instruction
 * variants (broadcast + dest-mask combinations).  Writing a unique
 * C macro per variant would multiply the surface without buying
 * any analysis power -- the assembler already parses the asm text
 * we'd embed in each macro.
 *
 * Instead we expose ONE generic macro per memory-effect category,
 * each taking the full asm text as a string literal.  Each macro
 * emits a single instruction, satisfying the project rule "one
 * instruction per __asm__ block."
 *
 * Pattern is the same shape ps2sdk uses in its VU0 inline-asm
 * helpers (e.g. ee/include/vif.h's VIF1_FBRST_MACRO style): one
 * `__asm__ __volatile__` per instruction, with `"memory"` clobber
 * on the loads/stores that observe caller-visible state.
 */

#ifndef VU0_H
#define VU0_H

/* COP2 load/store (lqc2, sqc2, lq, sq) — observable to caller's
 * memory.  Caller is responsible for using the right address-form
 * mnemonic in the asm string. */
#define VU0_LOAD(insn)   __asm__ __volatile__(insn : : : "memory")
#define VU0_STORE(insn)  __asm__ __volatile__(insn : : : "memory")

/* Pure compute on VU0 register file (vadd, vsub, vmul, vmove,
 * vftoi0, etc.) — no memory effect, but VOLATILE to suppress
 * gcc reordering. */
#define VU0_COMPUTE(insn) __asm__ __volatile__(insn)

/* Move between EE GPR/FPR and VU0 (mfc1, mtc1, qmfc2.ni,
 * qmtc2.ni, cfc2.ni). */
#define VU0_MOVE(insn)   __asm__ __volatile__(insn)

/* Wait-for-Q-pipeline barrier (vwaitq).  No memory effect but
 * sequences subsequent VU0 ops with prior compute. */
#define VU0_WAIT()       __asm__ __volatile__("vwaitq")

/* Single nop (used as a delay-slot filler or scheduler barrier). */
#define VU0_NOP()        __asm__ __volatile__("nop")

/* Random-VU0 raw escape hatch — for any mnemonic not classified
 * above (e.g., vrnext, vrxor, vsqi, vlqd, vdiv).  Use when none of
 * the typed forms above apply.  The asm string is emitted verbatim,
 * one instruction at a time. */
#define VU0_RAW(insn)    __asm__ __volatile__(insn)

/* Hazard-pair scheduler barriers.
 *
 * Several R5900 COP2 transfer pairs have intrinsic load-delay or
 * Q-pipeline interlocks that gas's default `.set reorder` mode
 * "fixes" by inserting a `nop` between them.  The original ICO
 * codegen does NOT have those nops -- the bytes are tight.  Wrap
 * the affected pair in VU0_NOREORDER_BEGIN/END to suppress gas's
 * auto-fill.
 *
 * Example: `mfc1 $tN, $fM` followed by `qmtc2.ni $tN, $vfK` has a
 * 1-cycle GPR load-delay.  In `.set reorder` gas inserts a nop
 * between them; in `.set noreorder` gas leaves the bytes untouched
 * (the EE pipeline is forwarding-correct already).
 */
#define VU0_NOREORDER_BEGIN()  __asm__ __volatile__(".set noreorder")
#define VU0_NOREORDER_END()    __asm__ __volatile__(".set reorder")

/* Raw 32-bit word emission for COP2 ops without a gas mnemonic
 * (e.g., `vsqrt $Q, $vfNx` -> .word 0x4A0X03BD). */
#define VU0_WORD(w)      __asm__ __volatile__(".word " #w)

#endif /* VU0_H */
