/* libm.a member sf_copysign.o */
#include <math_private.h>
#include <math.h>

/* Float<->word access, the public-domain fdlibm idiom (netlib's fdlibm,
   math_private.h), defined in this member. */

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

float copysignf(float a0, float a1)
{
    unsigned int ix, iy;
    GET_FLOAT_WORD(ix, a0);
    GET_FLOAT_WORD(iy, a1);
    SET_FLOAT_WORD(a0, (ix & 0x7fffffff) | (iy & 0x80000000));
    return a0;
}
