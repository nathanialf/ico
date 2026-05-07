/*
 * include/vu0.h — VU0/COP2 instruction macros for handwritten leaves.
 *
 * The R5900's VU0 macro mode exposes ~120 distinct instruction
 * variants (broadcast + dest-mask combinations).  Writing a unique
 * C macro per variant would multiply the surface without buying
 * any analysis power -- the assembler already parses the asm text
 * we'd embed in each macro.
 *
 * Instead we expose ONE macro per *side-effect class*, each taking
 * the full asm text as a string literal.  Each macro emits exactly
 * one instruction, satisfying the project rule "one instruction per
 * __asm__ block."
 *
 * Pattern is the same shape ps2sdk uses in its VU0 inline-asm
 * helpers (e.g. ee/include/vif.h's VIF1_FBRST_MACRO style): one
 * `__asm__ __volatile__` per instruction, with `"memory"` clobber
 * on the loads/stores that observe caller-visible state.
 */

#ifndef VU0_H
#define VU0_H

/* ===========================================================
 *  Pick one of VU0_MEM / VU0_REG depending on what the
 *  instruction does to the OBSERVABLE state of the caller.
 * ===========================================================
 *
 *  VU0_MEM(insn) — for instructions that load from or store to
 *  caller-visible memory (typed as `void *` arguments in the
 *  wrapper signature).  Adds a `"memory"` clobber so gcc can't
 *  cache stack/global state across the asm.
 *
 *      Use for: lqc2, sqc2, lq, sq, ld, sd, lwu, lw, sw, etc.
 *
 *  VU0_REG(insn) — for instructions that touch ONLY the VU0
 *  register file or move between EE GPR/FPR and VU0.  No memory
 *  effect, but `volatile` to suppress gcc reordering.
 *
 *      Use for: vadd, vsub, vmul, vmove, vftoi*, vmadd*, vopm*,
 *               vftoi*, mfc1, mtc1, qmfc2(.ni), qmtc2(.ni),
 *               cfc2(.ni), and any other COP2/VU0 op.
 *
 *  Use VU0_WORD(w) for COP2 ops that have no gas mnemonic
 *  (e.g., `vsqrt $Q, $vfNx` -> .word 0x4A0X03BD), VU0_NOP() and
 *  VU0_WAIT() for the literals "nop" and "vwaitq".
 */
#define VU0_MEM(insn)   __asm__ __volatile__(insn : : : "memory")
#define VU0_REG(insn)   __asm__ __volatile__(insn)

/* Single nop (used as a delay-slot filler or scheduler barrier). */
#define VU0_NOP()       __asm__ __volatile__("nop")

/* Wait-for-Q-pipeline barrier (vwaitq).  No memory effect but
 * sequences subsequent VU0 ops with prior compute. */
#define VU0_WAIT()      __asm__ __volatile__("vwaitq")

/* Raw 32-bit word emission for COP2 ops without a gas mnemonic
 * (e.g., `vsqrt $Q, $vfNx` -> .word 0x4A0X03BD). */
#define VU0_WORD(w)     __asm__ __volatile__(".word " #w)

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

#endif /* VU0_H */
