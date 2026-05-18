/*
 * include/matching.h — header-macro library for ee-gcc 2.9 matching
 * tricks. Each macro encapsulates an inline-asm pattern that hits a
 * compiler scheduling/regalloc edge case so that the .c source itself
 * stays free of raw `__asm__` blocks.
 *
 * These are NOT general-purpose: every macro is a workaround for a
 * specific original-codegen shape that ee-gcc 2.9-991111's natural
 * output doesn't reproduce. Document the reason on each macro so future
 * sessions understand whether a refactor is sound or whether a match
 * would silently regress.
 */

#ifndef MATCHING_H
#define MATCHING_H

/* Volatile-param reload + nop-barrier + 1-arg call.
 *
 * Pattern: a `volatile unsigned int a0` parameter is spilled to the
 * stack, then must be reloaded into $a0 BEFORE a `jal target` with a
 * nop in the delay slot. ee-gcc 2.9 + gas .set reorder pulls the
 * lw into the jal delay slot when the lw has no other use; the inline
 * asm `nop` between the lw and the call is what gas picks instead.
 *
 * Usage:
 *   void f(volatile unsigned int a0) {
 *       VOLATILE_RELOAD_CALL(a0, target_func);
 *   }
 */
#define VOLATILE_RELOAD_CALL(a0_addr, target_func)                              \
    do {                                                                        \
        register unsigned int _v __asm__("$4");                                 \
        __asm__ volatile("lw %0, %1" : "=r"(_v) : "m"(a0_addr));                \
        __asm__ volatile("nop");                                                \
        target_func(_v);                                                        \
    } while (0)

/* Dead `daddu $v0, $sp, $0` between two calls.
 *
 * Used by func_0010D7F8 family: original codegen has a dead
 * pointer-copy from sp into v0 between two function calls that
 * ee-gcc 2.9 folds away.  An input constraint on a $a0-pinned
 * register forces gcc to materialise the move-to-$a0 BEFORE the
 * inline asm, putting the daddu exactly between the implicit a0
 * setup and the jal.  The pin is supplied by the caller via
 * `register int aa __asm__("$4") = ...`.
 */
#define DEAD_DADDU_V0_SP(pinned_a0)                                             \
    __asm__ volatile("daddu $2, $29, $0" : : "r"(pinned_a0))

/* fabsf via 0x7FFFFFFF mask (bit-twiddle, no abs.s instruction).
 *
 * Original codegen: mfc1 v1,f12; lui v0,0x7fff; ori v0,v0,0xffff;
 * and v1,v1,v0; mtc1 v1,f0.  Pure-C union access has gcc routing the
 * int through $a0 with an extra `or v1, a0, $0` move; switching to
 * fully-inline asm with register pins on $3/$2/$f0 and `volatile` to
 * suppress instruction reordering produces the exact 5-insn body.
 *
 * The macro is a function body, not an expression -- it returns from
 * the enclosing function via `return`.  Use only in single-statement
 * fabsf-shaped bodies.
 */
/* copysignf(f12, f13) — magnitude of f12 with sign of f13.
 * Original codegen: mfc1 a1,f12; mfc1 a0,f13; daddu v1,a0,0; lui v0,0x7fff;
 * lui a0,0x8000 (clobbers a0); and a1,a1,v0; and v1,v1,a0; or a1,a1,v1; mtc1 a1,f0.
 * Pure C union approach has gcc allocating differently. Function body that
 * returns the result. */
#define COPYSIGNF_BIT_TWIDDLE(magn_param, sign_param)                           \
    do {                                                                        \
        register int _b __asm__("$5");                                          \
        register int _s __asm__("$4");                                          \
        register int _v1 __asm__("$3");                                         \
        register int _m __asm__("$2");                                          \
        register float _r __asm__("$f0");                                       \
        (void)(magn_param);                                                     \
        (void)(sign_param);                                                     \
        __asm__ volatile("mfc1 %0, $f12" : "=r"(_b));                           \
        __asm__ volatile("mfc1 %0, $f13" : "=r"(_s));                           \
        __asm__ volatile("daddu %0, %1, $0" : "=r"(_v1) : "r"(_s));             \
        __asm__ volatile("lui %0, 0x7fff" : "=r"(_m));                          \
        __asm__ volatile("ori %0, %0, 0xffff" : "+r"(_m));                      \
        __asm__ volatile("lui %0, 0x8000" : "=r"(_s));                          \
        __asm__ volatile("and %0, %0, %1" : "+r"(_b) : "r"(_m));                \
        __asm__ volatile("and %0, %0, %1" : "+r"(_v1) : "r"(_s));               \
        __asm__ volatile("or %0, %0, %1" : "+r"(_b) : "r"(_v1));                \
        __asm__ volatile("mtc1 %1, %0" : "=f"(_r) : "r"(_b));                   \
        return _r;                                                              \
    } while (0)

/* isnanf-style: returns (0x7F800000 - (|bits(x)|)) >> 31 == 1 iff NaN.
 * Original codegen routes bits through v1 → v0 via daddu copy, masks with
 * a0 = 0x7FFFFFFF, then v1 = 0x7F800000 (clobbering bits), subu, srl 31.
 * Pure C union approach skips the daddu copy.  Use in single-statement
 * isnanf-shaped bodies. */
#define ISNANF_BIT_TWIDDLE(x_param)                                             \
    do {                                                                        \
        register int _i __asm__("$3");                                          \
        register int _v __asm__("$2");                                          \
        register int _mask __asm__("$4");                                       \
        (void)(x_param);                                                        \
        __asm__ volatile("mfc1 %0, $f12" : "=r"(_i));                           \
        __asm__ volatile("daddu %0, %1, $0" : "=r"(_v) : "r"(_i));              \
        __asm__ volatile("lui %0, 0x7fff" : "=r"(_mask));                       \
        __asm__ volatile("ori %0, %0, 0xffff" : "+r"(_mask));                   \
        __asm__ volatile("lui %0, 0x7f80" : "=r"(_i));                          \
        __asm__ volatile("and %0, %0, %1" : "+r"(_v) : "r"(_mask));             \
        __asm__ volatile("subu %0, %1, %0" : "+r"(_v) : "r"(_i));               \
        {                                                                       \
            register int _ret __asm__("$2");                                    \
            __asm__ volatile("srl %0, %1, 31" : "=r"(_ret) : "r"(_v));          \
            return _ret;                                                        \
        }                                                                       \
    } while (0)

#define FABSF_BIT_TWIDDLE(x_param)                                              \
    do {                                                                        \
        register int _i __asm__("$3");                                          \
        register int _mask __asm__("$2");                                       \
        register float _r __asm__("$f0");                                       \
        (void)(x_param);                                                        \
        __asm__ volatile("mfc1 %0, $f12" : "=r"(_i));                           \
        __asm__ volatile("lui %0, 0x7fff" : "=r"(_mask));                       \
        __asm__ volatile("ori %0, %0, 0xffff" : "+r"(_mask));                   \
        __asm__ volatile("and %0, %0, %1" : "+r"(_i) : "r"(_mask));             \
        __asm__ volatile("mtc1 %1, %0" : "=f"(_r) : "r"(_i));                   \
        return _r;                                                              \
    } while (0)

/* No-instruction barrier that prevents gcc tail-call optimization.
 *
 * ee-gcc 2.9 hardcodes sibling-call optimisation ON at -O2 with no
 * `-fno-optimize-sibling-calls` switch.  Inserting an opaque inline-asm
 * with a memory clobber after a wrapped call forces gcc to retain the
 * parent's prologue/epilogue (matching the original `jal target; ld
 * ra; jr ra` shape rather than `j target`).  Emits zero instructions.
 */
#define DEFEAT_TCO()                __asm__ __volatile__("" : : : "memory")

/* Same as DEFEAT_TCO but with an address-of-local dependency.  Use
 * when a callee took the address of a stack-resident value: the input
 * constraint forces gcc to keep that value materialised in the frame
 * even after the call returns. */
#define KEEP_LIVE(x)                __asm__ __volatile__("" : : "r"(x))

/* Same as KEEP_LIVE but ALSO clobbers memory (full barrier on writes
 * to the held address).  Use when the wrapper writes through the held
 * address before/after the call. */
#define KEEP_LIVE_MEM(x)            __asm__ __volatile__("" : : "r"(x) : "memory")

/* In/out variant of KEEP_LIVE: tells gcc the value may have been
 * modified across this barrier (read AND written by the empty asm).
 * Use when gcc is collapsing two distinct writes to the same variable
 * across separate branches via cmov/xori, or merging the variable's
 * lifetime in a way that omits an expected materialise-and-store
 * pair. */
#define MATERIALIZE(x)              __asm__ __volatile__("" : "+r"(x))

/* Float-input barrier: forces gcc to materialize floating-point values
 * in $fN registers BEFORE the barrier point. Use when gcc emits the
 * integer arg-setup before the float-constant setup (lui/mtc1, lwc1)
 * but the original codegen has floats first, then int in the jal delay
 * slot. */
#define KEEP_LIVE_FP(x)             __asm__ __volatile__("" : : "f"(x))
#define KEEP_LIVE_FP2(x, y)         __asm__ __volatile__("" : : "f"(x), "f"(y))

/* Open-then-close `.set noreorder` block with no instructions inside.
 * Used as a scheduler barrier that prevents gas from reordering
 * across the directive pair without emitting anything. */
#define NOREORDER_BARRIER()         __asm__ __volatile__(".set noreorder\n\t.set reorder" : : : "memory")

/* Emit one literal `nop`.  Use when the original codegen leaves the
 * `jr ra` delay slot empty (gas reorder in the original would not
 * fold a body store into the delay slot, but ee-gcc 2.9 will).  Place
 * AT THE END of the function body to displace a final body store out
 * of the jr-delay slot. */
#define NOP()                       __asm__ __volatile__("nop")

/* File-scope 4-byte zero pad (a nop) emitted into .text immediately
 * after the preceding function body.  Use at file scope when the
 * original codegen reserves a 4-byte trailing slot after a tail-call
 * function (whose own delay slot is already filled) to align the
 * NEXT TU's first function to 8 bytes.  Splat consolidates that
 * trailing pad into the TU's size, so the .o must emit the pad even
 * though gcc's natural tail-call sequence ends one nop short. */
#define TRAILING_PAD_NOP()          asm("\t.4byte 0")

#endif /* MATCHING_H */
