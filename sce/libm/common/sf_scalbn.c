/* libm.a member sf_scalbn.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <math_private.h>

extern int __ieee754_rem_pio2f(float x, float *y);
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);

/* Float<->word access, the public-domain fdlibm idiom (netlib's fdlibm),
   re-derived, not copied from any SDK.  This member's use stands for a
   Sony/newlib-internal math_private.h this tree cannot name. */

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
/* two25 and twom25 have a zero low half, so ee-as expands their `li.s` to the
   immediate lui/mtc1 pair on its own.  huge (0x7149F2CA) and tiny (0x0DA24260)
   are two-word, and the period ee-as expands a two-word `li.s` to a .lit4 pool
   load where the ROM's assembler expanded it to lui/ori/mtc1, so those two are
   hand-placed (the standing fdlibm two-word-float ruling; kf_cos.c and
   sf_floor.c carry the same idiom).  $1 is the assembler temporary. */
#define two25 3.355443200e+07f
#define twom25 2.9802322388e-08f
#define LOAD_HUGE(f) __asm__("lui $1,0x7149\n\tori $1,$1,0xf2ca\n\tmtc1 $1,%0" : "=f"(f))
#define LOAD_TINY(f) __asm__("lui $1,0x0da2\n\tori $1,$1,0x4260\n\tmtc1 $1,%0" : "=f"(f))

extern float copysignf(float x, float y);

float scalbnf(float x, int n)
{
    int k, ix;
    float tiny;
    float scale;

    GET_FLOAT_WORD(ix, x);
    k = (ix & 0x7f800000) >> 23; /* extract exponent */
    if (k == 0) {                /* 0 or subnormal x */
        if ((ix & 0x7fffffff) == 0) {
            return x; /* +-0 */
        }
        x *= two25;
        GET_FLOAT_WORD(ix, x);
        k = ((ix & 0x7f800000) >> 23) - 25;
        if (n < -50000) {
            LOAD_TINY(tiny);
            return x * tiny; /* underflow */
        }
    }
    if (k == 0xff) {
        return x + x; /* NaN or Inf */
    }
    k = k + n;
    if (k > 0xfe) {
        goto overflow; /* overflow */
    }
    if (k > 0) { /* normal result */
        SET_FLOAT_WORD(x, (ix & 0x807fffff) | (k << 23));
        return x;
    }
    if (k <= -25) {
        int over = 50000; /* in case integer overflow in n+k */

        /* The comparison has to be placed ahead of the opaque constant load,
           which is what the ROM's scheduler did when the constant was still a
           compiler-emitted li.s; one block keeps both in ROM's order. */
        __asm__("slt %0,%0,%2\n\tlui $1,0x0da2\n\tori $1,$1,0x4260\n\tmtc1 $1,%1"
                : "+r"(over), "=f"(scale)
                : "r"(n));
        if (over) {
        overflow:
            LOAD_HUGE(scale); /* overflow */
        }
        return copysignf(scale, x) * scale;
    }
    k += 25; /* subnormal result */
    SET_FLOAT_WORD(x, (ix & 0x807fffff) | (k << 23));
    return x * twom25;
}
