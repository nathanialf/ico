/* libm.a member kf_cos.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

/* Float<->word access, the public-domain fdlibm idiom (netlib's fdlibm),
   re-derived, not copied from any SDK.  This member's use stands for a
   Sony/newlib-internal math_private.h this tree cannot name: the listing
   attributes no row to such a header, so the definition is kept per member. */
typedef union {
    float value;
    unsigned int word;
} ieee_float_shape_type;

#define GET_FLOAT_WORD(i, d)                                                                       \
    do {                                                                                           \
        ieee_float_shape_type gf_u;                                                                \
        gf_u.value = (d);                                                                          \
        (i) = gf_u.word;                                                                           \
    } while (0)
#define SET_FLOAT_WORD(d, i)                                                                       \
    do {                                                                                           \
        ieee_float_shape_type sf_u;                                                                \
        sf_u.word = (i);                                                                           \
        (d) = sf_u.value;                                                                          \
    } while (0)

extern int __ieee754_rem_pio2f(float x, float *y);
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);

float __kernel_cosf(float x, float y)
{
    float a, hz, qx, z;
    int ix;
    register int cmp __asm__("$2");
    register float acc __asm__("$f0");
    register float c2 __asm__("$f2");
    register float c3 __asm__("$f3");
    register float c1 __asm__("$f1");
    register float c4 __asm__("$f4");
    register float c5 __asm__("$f5");

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;
    if (ix < 0x32000000) {
        if (((int)x) == 0) {
            return 1.0f;
        }
    }
    z = x * x;
    /* Emit the six polynomial coefficient loads (into $f0/$f2/$f3/$f1/$f4/$f5),
     * the first Horner multiply (acc = z*c0), and the |x|<0.3 comparison
     * (cmp = 0x3e999999 < ix) in the exact ROM instruction order — the EE
     * scheduler will not interleave GPR comparison ops among asm-opaque coeff
     * loads, so the interleave is hand-placed here. */
    __asm__("lui   $1,0xad47\n\t"
            "ori   $1,$1,0xd74e\n\t"
            "mtc1  $1,%0\n\t"
            "lui   $1,0x310f\n\t"
            "ori   $1,$1,0x74f6\n\t"
            "mtc1  $1,%1\n\t"
            "lui   %6,0x3e99\n\t"
            "lui   $1,0xb493\n\t"
            "ori   $1,$1,0xf27c\n\t"
            "mtc1  $1,%2\n\t"
            "ori   %6,%6,0x9999\n\t"
            "mul.s %0,%7,%0\n\t"
            "lui   $1,0x37d0\n\t"
            "ori   $1,$1,0x0d01\n\t"
            "mtc1  $1,%3\n\t"
            "lui   $1,0xbab6\n\t"
            "ori   $1,$1,0x0b61\n\t"
            "mtc1  $1,%4\n\t"
            "slt   %6,%6,%8\n\t"
            "lui   $1,0x3d2a\n\t"
            "ori   $1,$1,0xaaab\n\t"
            "mtc1  $1,%5"
            : "=f"(acc), "=f"(c2), "=f"(c3), "=f"(c1), "=f"(c4), "=f"(c5), "=r"(cmp)
            : "f"(z), "r"(ix));
    acc = acc + c2;
    acc = z * acc + c3;
    acc = z * acc + c1;
    acc = z * acc + c4;
    acc = z * acc + c5;
    /* r = z*acc: reuse c1 (dead since the a3 step) so r lands in $f1, leaving
     * $f0 free for the 0.5 constant the tail branches load — matches ROM. */
    c1 = z * acc;
    if (!cmp) {
        return 1.0f - (0.5f * z - (z * c1 - x * y));
    } else {
        if (ix > 0x3f480000) {
            qx = 0.28125f;
        } else {
            SET_FLOAT_WORD(qx, ix - 0x01000000);
        }
        /* else-branch z*r lands in $f2 (ROM), not the just-freed $f1: reuse
         * dead c2 ($f2) to force it, leaving $f1 for a = 1.0 - qx. */
        c2 = z * c1;
        hz = 0.5f * z - qx;
        a = 1.0f - qx;
        return a - (hz - (c2 - x * y));
    }
}
