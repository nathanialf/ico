/* libm.a member ef_atan2.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern int __ieee754_rem_pio2f(float x, float *y);
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);

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

extern float atanf(float x);
extern float fabsf(float x);

static const float tiny = 1.0e-30;

static const float zero = 0.0;

static const float pi_o_4 = 7.8539818525e-01;

static const float pi_o_2 = 1.5707963705e+00;

static const float pi = 3.1415925026e+00;

static const float pi_lo = 1.5099578832e-07;

float __ieee754_atan2f(float y, float x)
{
    float z;
    int k, m, hx, hy, ix, iy;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;
    GET_FLOAT_WORD(hy, y);
    iy = hy & 0x7fffffff;
    if ((ix > 0x7f800000) || (iy > 0x7f800000)) {
        return x + y;
    }
    if (hx == 0x3f800000) {
        return atanf(y);
    }
    m = ((hy >> 31) & 1) | ((hx >> 30) & 2);

    if (iy == 0) {
        switch (m) {
        case 0:
        case 1:
            return y;
        case 2:
            return pi + tiny;
        case 3:
            return -pi - tiny;
        }
    }
    if (ix == 0) {
        return (hy < 0) ? -pi_o_2 - tiny : pi_o_2 + tiny;
    }

    if (ix == 0x7f800000) {
        if (iy == 0x7f800000) {
            switch (m) {
            case 0:
                return pi_o_4 + tiny;
            case 1:
                return -pi_o_4 - tiny;
            case 2:
                return (float)3.0 * pi_o_4 + tiny;
            case 3:
                return (float)-3.0 * pi_o_4 - tiny;
            }
        } else {
            switch (m) {
            case 0:
                return zero;
            case 1:
                return -zero;
            case 2:
                return pi + tiny;
            case 3:
                return -pi - tiny;
            }
        }
    }

    if (iy == 0x7f800000) {
        return (hy < 0) ? -pi_o_2 - tiny : pi_o_2 + tiny;
    }

    k = (iy - ix) >> 23;
    if (k > 60) {
        z = pi_o_2 + (float)0.5 * pi_lo;
    } else if (hx < 0 && k < -60) {
        z = 0.0f;
    } else {
        z = atanf(fabsf(y / x));
    }
    switch (m) {
    case 0:
        return z;
    case 1: {
        unsigned int zh;
        GET_FLOAT_WORD(zh, z);
        SET_FLOAT_WORD(z, zh ^ 0x80000000);
    }
        return z;
    case 2:
        return pi - (z - pi_lo);
    default:
        return (z - pi_lo) - pi;
    }
}
