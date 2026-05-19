/*
 * include/dispatch.h — `func_0013A5B8` dispatch-wrapper macro family.
 *
 * The 8 leaves at offsets 0x37F08..0x380F8 in the original ELF share
 * the same handwritten-asm shape: copy a0 to v1, set up the four
 * call args (a0=&D_00280F88, a1=v1, a2=0, a3=-2 mask), store a small
 * literal at v1[1], mask v1[0] with -2, and tail-jal func_0013A5B8
 * with the masked store in the delay slot.
 *
 * ee-gcc 2.9-991111's natural codegen for this body re-materialises
 * the -2 constant twice (once for AND, once for the 4th arg) and
 * orders the prologue ra-save before the v1=a0 copy.  Neither shape
 * is reachable from C without explicit register-pin inline asm and
 * the early_body_swap postprocess.
 *
 * The macro emits exactly the 0x40-byte body the original ELF has,
 * driven by:
 *   - `name`        — function symbol (e.g. `func_00137F08`)
 *   - `type_lit`    — small literal stored at v1[1] (0..9 in
 *                     the original).  When 0, the addiu/sw pair
 *                     becomes a single `sw $0, 4(v1)` (no v0
 *                     materialisation).
 *
 * Per-file allowlist:
 *   - `config/early_body_swap.txt` — required, swaps prologue ra-save
 *     with the first body op.
 *   - `config/shared_sp_restore.txt` — required for type_lit != 0;
 *     the 037F48-family ends with `jr ra` whose delay slot is
 *     filled by the next function's first instruction.
 */

#ifndef DISPATCH_H
#define DISPATCH_H

extern char D_00280F88[];
/* func_0013A5B8 declared by callers (4-arg int return) -- not
 * declared here so callers control the prototype. */

/* type_lit == 0 base case (func_00137F08).  No literal materialisation
 * needed; the immediate `0` is stored as `sw $0, 4(v1)` directly. */
#define DISPATCH_WRAPPER_TYPE0(name)                                            \
    int name(long *a0) {                                                        \
        register long *v1 __asm__("$3");                                        \
        register int a3 __asm__("$7");                                          \
        register char *a0_arg __asm__("$4");                                    \
        register long *a1_arg __asm__("$5");                                    \
        register int a2_arg __asm__("$6");                                      \
        register long v0 __asm__("$2");                                         \
        register int rv __asm__("$2");                                          \
                                                                                \
        __asm__ volatile("daddu %0, %1, $0" : "=r"(v1) : "r"(a0));              \
        __asm__ volatile("addiu %0, $0, -2" : "=r"(a3));                        \
        __asm__ volatile("sw $0, 4(%0)" : : "r"(v1) : "memory");                \
        __asm__ volatile("lui %0, %%hi(D_00280F88)" : "=r"(a0_arg));            \
        __asm__ volatile("addiu %0, %0, %%lo(D_00280F88)" : "+r"(a0_arg));      \
        __asm__ volatile("daddu %0, %1, $0" : "=r"(a1_arg) : "r"(v1));          \
        __asm__ volatile("ld %0, 0(%1)" : "=r"(v0) : "r"(v1));                  \
        __asm__ volatile("daddu %0, $0, $0" : "=r"(a2_arg));                    \
        __asm__ volatile("and %0, %0, %1" : "+r"(v0) : "r"(a3));                \
        __asm__ volatile("sd %0, 0(%1)" : : "r"(v0), "r"(v1) : "memory");       \
        __asm__ volatile(                                                       \
            "jal func_0013A5B8"                                                 \
            : "=r"(rv)                                                          \
            : "r"(a0_arg), "r"(a1_arg), "r"(a2_arg), "r"(a3)                    \
            : "$31", "memory");                                                 \
        return rv;                                                              \
    }

/* type_lit != 0 case (func_00137F48 family).  Materialises the
 * literal in v0 first, stores at v1[1], THEN sets up the mask in a3,
 * then proceeds.  Function ends with bare `jr ra` (no delay slot
 * fill); shared_sp_restore postprocess strips the gcc-emitted
 * addiu sp from the delay slot. */
#define DISPATCH_WRAPPER_TYPEN(name, type_lit)                                  \
    int name(long *a0) {                                                        \
        register long *v1 __asm__("$3");                                        \
        register int a3 __asm__("$7");                                          \
        register char *a0_arg __asm__("$4");                                    \
        register long *a1_arg __asm__("$5");                                    \
        register int a2_arg __asm__("$6");                                      \
        register long v0 __asm__("$2");                                         \
        register int rv __asm__("$2");                                          \
                                                                                \
        __asm__ volatile("daddu %0, %1, $0" : "=r"(v1) : "r"(a0));              \
        __asm__ volatile("addiu %0, $0, " #type_lit : "=r"(v0));                \
        __asm__ volatile("sw %0, 4(%1)" : : "r"(v0), "r"(v1) : "memory");       \
        __asm__ volatile("addiu %0, $0, -2" : "=r"(a3));                        \
        __asm__ volatile("lui %0, %%hi(D_00280F88)" : "=r"(a0_arg));            \
        __asm__ volatile("daddu %0, %1, $0" : "=r"(a1_arg) : "r"(v1));          \
        __asm__ volatile("ld %0, 0(%1)" : "=r"(v0) : "r"(v1));                  \
        __asm__ volatile("addiu %0, %0, %%lo(D_00280F88)" : "+r"(a0_arg));      \
        __asm__ volatile("daddu %0, $0, $0" : "=r"(a2_arg));                    \
        __asm__ volatile("and %0, %0, %1" : "+r"(v0) : "r"(a3));                \
        __asm__ volatile("sd %0, 0(%1)" : : "r"(v0), "r"(v1) : "memory");       \
        __asm__ volatile(                                                       \
            "jal func_0013A5B8"                                                 \
            : "=r"(rv)                                                          \
            : "r"(a0_arg), "r"(a1_arg), "r"(a2_arg), "r"(a3)                    \
            : "$31", "memory");                                                 \
        return rv;                                                              \
    }

/* Same as DISPATCH_WRAPPER_TYPEN but ALSO stores the original a1 arg
 * into v1[0x48/4] BEFORE the call. Used by func_00138188 / func_00138140
 * family (type_lit 0xB, 0xA): same dispatch shape with one extra
 * pre-call store of `a1` at struct offset 0x48. */
#define DISPATCH_WRAPPER_TYPEN_A1(name, type_lit)                               \
    int name(long *a0, long a1_in) {                                            \
        register long *v1 __asm__("$3");                                        \
        register int a3 __asm__("$7");                                          \
        register char *a0_arg __asm__("$4");                                    \
        register long *a1_arg __asm__("$5");                                    \
        register int a2_arg __asm__("$6");                                      \
        register long v0 __asm__("$2");                                         \
        register int rv __asm__("$2");                                          \
                                                                                \
        __asm__ volatile("daddu %0, %1, $0" : "=r"(v1) : "r"(a0));              \
        __asm__ volatile("addiu %0, $0, " #type_lit : "=r"(v0));                \
        __asm__ volatile("sw %0, 4(%1)" : : "r"(v0), "r"(v1) : "memory");       \
        __asm__ volatile("addiu %0, $0, -2" : "=r"(a3));                        \
        __asm__ volatile("sw %0, 0x48(%1)" : : "r"(a1_in), "r"(v1) : "memory"); \
        __asm__ volatile("lui %0, %%hi(D_00280F88)" : "=r"(a0_arg));            \
        __asm__ volatile("ld %0, 0(%1)" : "=r"(v0) : "r"(v1));                  \
        __asm__ volatile("addiu %0, %0, %%lo(D_00280F88)" : "+r"(a0_arg));      \
        __asm__ volatile("daddu %0, %1, $0" : "=r"(a1_arg) : "r"(v1));          \
        __asm__ volatile("daddu %0, $0, $0" : "=r"(a2_arg));                    \
        __asm__ volatile("and %0, %0, %1" : "+r"(v0) : "r"(a3));                \
        __asm__ volatile("sd %0, 0(%1)" : : "r"(v0), "r"(v1) : "memory");       \
        __asm__ volatile(                                                       \
            "jal func_0013A5B8"                                                 \
            : "=r"(rv)                                                          \
            : "r"(a0_arg), "r"(a1_arg), "r"(a2_arg), "r"(a3)                    \
            : "$31", "memory");                                                 \
        return rv;                                                              \
    }

#endif /* DISPATCH_H */
