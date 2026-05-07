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
 *  TYPED MACROS — preferred form.  Pass operands as tokens; the
 *  macro builds the asm string via stringify-and-paste.
 * ===========================================================
 *
 *  Naming: VU0_<SHAPE>(<mnem-with-mask>, <operands...>)
 *
 *  The mnemonic (including mask, e.g. `vmul.xyzw`, and any
 *  broadcast prefix in the mnemonic, e.g. `vaddz`) is passed as
 *  a SINGLE token; operands are unprefixed register numbers
 *  (e.g. `13` for `$vf13`, `t0` for `$t0`, `f12` for `$f12`).
 *
 *  Memory loads/stores
 *  -------------------
 *    VU0_LSV(mnem, vf, off, base)   -> "<mnem> $vf<vf>, <off>($<base>)"
 *      Use for: lqc2, sqc2, vlqd, vsqi.
 *    VU0_LSGP(mnem, gp, off, base)  -> "<mnem> $<gp>, <off>($<base>)"
 *      Use for: lq, sq, ld, sd.
 *
 *  VU compute (register-only)
 *  --------------------------
 *    VU0_V2OP(mnem, d, a)         -> "<mnem> $vfd, $vfa"
 *      Use for: vmove, vmr32, vftoi0/4/12/15, vsqrt-style 2-arg.
 *    VU0_V3OP(mnem, d, a, b)      -> "<mnem> $vfd, $vfa, $vfb"
 *      Use for: vmul.MASK / vsub.MASK / vadd.MASK with no broadcast.
 *    VU0_V3OP_BC(mnem, d, a, b, bc)
 *                                 -> "<mnem> $vfd, $vfa, $vfb<bc>"
 *      Use for: vmulx.MASK / vaddy.MASK / vmaddw.MASK style ops where
 *      the broadcast letter is part of the mnemonic AND appears as a
 *      register suffix on the b operand.
 *    VU0_V3OP_ACC(mnem, a, b)     -> "<mnem> $ACC, $vfa, $vfb"
 *      Use for: vopmula.MASK, vopmsub.MASK destination=ACC.
 *    VU0_V3OP_ACC_BC(mnem, a, b, bc)
 *                                 -> "<mnem> $ACC, $vfa, $vfb<bc>"
 *      Use for: vmulax/vmadday/vmaddaz.MASK style.
 *
 *  EE<->VU transfer
 *  ----------------
 *    VU0_MFC1(gp, fp)        -> "mfc1 $<gp>, $f<fp>"
 *    VU0_MTC1(gp, fp)        -> "mtc1 $<gp>, $f<fp>"
 *    VU0_QMFC2_NI(gp, vf)    -> "qmfc2.ni $<gp>, $vf<vf>"
 *    VU0_QMTC2_NI(gp, vf)    -> "qmtc2.ni $<gp>, $vf<vf>"
 *    VU0_CFC2_NI(gp, vi)     -> "cfc2.ni $<gp>, $vi<vi>"
 *
 *  Escape hatches (pass full asm string)
 *  -------------------------------------
 *    VU0_MEM(insn) — caller-visible load/store; "memory" clobber.
 *    VU0_REG(insn) — register-only; no clobber.
 *
 *  Use the escape hatches only when no typed macro fits — e.g. for
 *  `vrnext`, `vrxor`, `vrsqrt`, `vdiv`, `viaddi`, `vmulq`, or any
 *  rare opcode without a typed shape above.  When the same shape
 *  shows up in 3+ functions, lift it into a new typed macro here.
 */

/* Escape-hatch macros (raw asm string).  Use sparingly. */
#define VU0_MEM(insn)   __asm__ __volatile__(insn : : : "memory")
#define VU0_REG(insn)   __asm__ __volatile__(insn)

/* Memory load/store: typed forms. */
#define VU0_LSV(mnem, vf, off, base)        VU0_MEM(#mnem " $vf" #vf ", " #off "($" #base ")")
#define VU0_LSGP(mnem, gp, off, base)       VU0_MEM(#mnem " $" #gp ", " #off "($" #base ")")

/* VU compute: 2-operand register-to-register (vmove, vmr32, vftoi*). */
#define VU0_V2OP(mnem, d, a)                VU0_REG(#mnem " $vf" #d ", $vf" #a)

/* VU compute: 3-operand register-to-register. */
#define VU0_V3OP(mnem, d, a, b)             VU0_REG(#mnem " $vf" #d ", $vf" #a ", $vf" #b)

/* Same with broadcast on b operand (mnemonic has broadcast letter,
 * b operand has matching register suffix). */
#define VU0_V3OP_BC(mnem, d, a, b, bc)      VU0_REG(#mnem " $vf" #d ", $vf" #a ", $vf" #b #bc)

/* VU compute to ACC. */
#define VU0_V3OP_ACC(mnem, a, b)            VU0_REG(#mnem " $ACC, $vf" #a ", $vf" #b)
#define VU0_V3OP_ACC_BC(mnem, a, b, bc)     VU0_REG(#mnem " $ACC, $vf" #a ", $vf" #b #bc)

/* EE<->VU transfer ops. */
#define VU0_MFC1(gp, fp)                    VU0_REG("mfc1 $" #gp ", $f" #fp)
#define VU0_MTC1(gp, fp)                    VU0_REG("mtc1 $" #gp ", $f" #fp)
#define VU0_QMFC2_NI(gp, vf)                VU0_REG("qmfc2.ni $" #gp ", $vf" #vf)
#define VU0_QMTC2_NI(gp, vf)                VU0_REG("qmtc2.ni $" #gp ", $vf" #vf)
#define VU0_CFC2_NI(gp, vi)                 VU0_REG("cfc2.ni $" #gp ", $vi" #vi)

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
