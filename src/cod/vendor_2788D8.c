#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

extern int __ieee754_rem_pio2f(float x, float *y);
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);

float sinf(float x) {
    float y[2];
    int n;
    int ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;

    if (ix <= 0x3f490fd8) {
        return __kernel_sinf(x, 0.0f, 0);
    } else if (ix >= 0x7f800000) {
        return x - x;
    } else {
        n = __ieee754_rem_pio2f(x, y);
        switch (n & 3) {
        case 0:
            return __kernel_sinf(y[0], y[1], 1);
        case 1:
            return __kernel_cosf(y[0], y[1]);
        case 2:
            return -__kernel_sinf(y[0], y[1], 1);
        default:
            return -__kernel_cosf(y[0], y[1]);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", acosf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", asinf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", atan2f);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", fmodf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", __ieee754_acosf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", __ieee754_asinf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", __ieee754_atan2f);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", __ieee754_fmodf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", __ieee754_rem_pio2f);
float __ieee754_sqrtf(float x) {
    int ix, s, q, m, t, i;
    unsigned int r;
    float z;

    GET_FLOAT_WORD(ix, x);
    if ((ix & 0x7F800000) == 0x7F800000) {
        return x * x + x;
    }
    m = ix >> 23;
    if (ix <= 0) {
        if ((ix & 0x7FFFFFFF) == 0) {
            return x;
        }
        if (ix < 0) {
            return (x - x) / (x - x);
        }
    }
    if (m == 0) {
        for (i = 0; (ix & 0x800000) == 0; i++) {
            ix <<= 1;
        }
        m -= i - 1;
    }
    m -= 0x7F;
    ix = (ix & 0x7FFFFF) | 0x800000;
    ix <<= (m & 1);
    m >>= 1;
    ix <<= 1;
    q = s = 0;
    r = 0x1000000;
    do {
        t = s + r;
        if (t <= ix) {
            s = t + r;
            ix -= t;
            q += r;
        }
        r >>= 1;
        ix <<= 1;
    } while (r != 0);
    if (ix != 0) {
        q += q & 1;
    }
    ix = (q >> 1) + 0x3F000000;
    ix += m << 23;
    SET_FLOAT_WORD(z, ix);
    return z;
}
float __kernel_cosf(float x, float y) {
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
    __asm__(
        "lui   $1,0xad47\n\t"
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", __kernel_rem_pio2f);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", __kernel_sinf);
extern int dpcmp(long a0, long a1);

int matherr(void *a0) {
    long p = *(long *)((char *)a0 + 8);
    dpcmp(p, p);
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", atanf);
float fabsf(float a0) {
    unsigned int ix;
    GET_FLOAT_WORD(ix, a0);
    SET_FLOAT_WORD(a0, ix & 0x7fffffff);
    return a0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", floorf);
int isnanf(float x) {
    int hx;
    GET_FLOAT_WORD(hx, x);
    hx &= 0x7fffffff;
    hx = 0x7f800000 - hx;
    return (unsigned)hx >> 31;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2788D8", scalbnf);
float copysignf(float a0, float a1) {
    unsigned int ix, iy;
    GET_FLOAT_WORD(ix, a0);
    GET_FLOAT_WORD(iy, a1);
    SET_FLOAT_WORD(a0, (ix & 0x7fffffff) | (iy & 0x80000000));
    return a0;
}
