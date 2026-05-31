/*
 * include/regpin.h — GCC explicit-register-variable binder.
 *
 * Register pins are NOT inline-asm bodies.  They're a GCC C extension
 * that asks the compiler to allocate a local variable to a specific
 * physical register, which we use as a regalloc nudge to recover the
 * original ICO codegen's register choice.
 *
 * Use as part of a `register T name` declaration:
 *
 *     register int v   REG("$2") = 1;       // pin to $v0
 *     register char *p REG("$8") = D_X;     // pin to $t0
 *     register int *q  REG("$3");           // uninitialized pin
 *
 * The macro expands to GCC's `__asm__(reg)` register-decl extension.
 * Wrapping it keeps src/cod/*.c free of the literal `__asm__` token
 * even for pure regalloc directives — inline-asm BODIES belong in
 * include/matching.h or include/r5900.h, never inline in src/cod/.
 *
 * When these are needed: see decomp/NOTES.md sections "Compiler
 * regalloc nudges" and "Combined sdata-set + return-value".  The
 * pattern is "ee-gcc picked $v0 / $a1, original picked $v1 / something
 * else, and natural-C reformulation can't budge the choice."
 *
 * R5900 GPR mapping (for reference):
 *   $0  = $zero      $8  = $t0     $16 = $s0     $24 = $t8
 *   $1  = $at        $9  = $t1     $17 = $s1     $25 = $t9
 *   $2  = $v0        $10 = $t2     $18 = $s2     $26 = $k0
 *   $3  = $v1        $11 = $t3     $19 = $s3     $27 = $k1
 *   $4  = $a0        $12 = $t4     $20 = $s4     $28 = $gp
 *   $5  = $a1        $13 = $t5     $21 = $s5     $29 = $sp
 *   $6  = $a2        $14 = $t6     $22 = $s6     $30 = $fp/$s8
 *   $7  = $a3        $15 = $t7     $23 = $s7     $31 = $ra
 */

#ifndef REGPIN_H
#define REGPIN_H

/* REG() was deleted as a matching crutch (Bucket A: explicit-register
 * regalloc nudge). A regalloc diff is a SOURCE-SHAPE mismatch — recover the
 * dev's C (decl order, signatures, pointer lifetime) instead of pinning.
 * Functions that depended on REG() were parked to tough_nuts/. This header
 * is retained as an empty stub because TUs still #include it. */

#endif /* REGPIN_H */
