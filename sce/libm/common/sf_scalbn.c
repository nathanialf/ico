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

/* fdlibm's constant table: the member's whole .rodata (MAIN.MAP sf_scalbn.o
 * .rodata 0x10, four words in declaration order).  The code loads each one as
 * an immediate, so the table is referenced by nothing. */
static const float two25 = 3.355443200e+07, /* 0x4c000000 */
    twom25 = 2.9802322388e-08,              /* 0x33000000 */
    huge = 1.0e+30, tiny = 1.0e-30;

extern float copysignf(float x, float y);

float scalbnf(float x, int n)
{
    int k, ix;

    GET_FLOAT_WORD(ix, x);
    k = (ix & 0x7f800000) >> 23; /* extract exponent */
    if (k == 0) {                /* 0 or subnormal x */
        if ((ix & 0x7fffffff) == 0)
            return x; /* +-0 */
        x *= two25;
        GET_FLOAT_WORD(ix, x);
        k = ((ix & 0x7f800000) >> 23) - 25;
        if (n < -50000)
            return tiny * x; /*underflow*/
    }
    if (k == 0xff)
        return x + x; /* NaN or Inf */
    k = k + n;
    if (k > 0xfe)
        return huge * copysignf(huge, x); /* overflow  */
    if (k > 0) {                          /* normal result */
        SET_FLOAT_WORD(x, (ix & 0x807fffff) | (k << 23));
        return x;
    }
    if (k <= -25)
        if (n > 50000)                        /* in case integer overflow in n+k */
            return huge * copysignf(huge, x); /*overflow*/
        else
            return tiny * copysignf(tiny, x); /*underflow*/
    k += 25;                                  /* subnormal result */
    SET_FLOAT_WORD(x, (ix & 0x807fffff) | (k << 23));
    return x * twom25;
}
