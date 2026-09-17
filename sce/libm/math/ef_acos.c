/* libm.a member ef_acos.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <math_private.h>

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

#define one 1.0000000000e+00f
#define pi 3.1415925026e+00f
#define pio2_hi 1.5707962513e+00f
#define pio2_lo 7.5497894159e-08f
#define pS0 1.6666667163e-01f
#define pS1 -3.2556581497e-01f
#define pS2 2.0121252537e-01f
#define pS3 -4.0055535734e-02f
#define pS4 7.9153501429e-04f
#define pS5 3.4793309169e-05f
#define qS1 -2.4033949375e+00f
#define qS2 2.0209457874e+00f
#define qS3 -6.8828397989e-01f
#define qS4 7.7038154006e-02f

extern float __ieee754_sqrtf(float x);

float __ieee754_acosf(float x)
{
    float z, p, q, r, w, s, c, df;
    int hx, ix;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;
    if (ix == 0x3f800000) {
        if (hx > 0) {
            return 0.0;
        } else {
            return pi + (float)2.0 * pio2_lo;
        }
    } else if (ix > 0x3f800000) {
        return (x - x) / (x - x);
    }
    if (ix < 0x3f000000) {
        if (ix <= 0x23000000) {
            return pio2_hi + pio2_lo;
        }
        z = x * x;
        p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + z * pS5)))));
        q = one + z * (qS1 + z * (qS2 + z * (qS3 + z * qS4)));
        r = p / q;
        return pio2_hi - (x - (pio2_lo - x * r));
    } else if (hx < 0) {
        z = (one + x) * (float)0.5;
        p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + z * pS5)))));
        q = one + z * (qS1 + z * (qS2 + z * (qS3 + z * qS4)));
        s = __ieee754_sqrtf(z);
        r = p / q;
        w = r * s - pio2_lo;
        return pi - (float)2.0 * (s + w);
    } else {
        int idf;
        z = (one - x) * (float)0.5;
        s = __ieee754_sqrtf(z);
        df = s;
        GET_FLOAT_WORD(idf, df);
        SET_FLOAT_WORD(df, idf & 0xfffff000);
        c = (z - df * df) / (s + df);
        p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + z * pS5)))));
        q = one + z * (qS1 + z * (qS2 + z * (qS3 + z * qS4)));
        r = p / q;
        w = r * s + c;
        return (float)2.0 * (df + w);
    }
}
