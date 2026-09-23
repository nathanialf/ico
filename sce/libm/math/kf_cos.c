/* libm.a member kf_cos.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <math_private.h>

/* Float<->word access, the public-domain fdlibm idiom (netlib's fdlibm),
   re-derived, not copied from any SDK.  This member's use stands for a
   Sony/newlib-internal math_private.h this tree cannot name: the listing
   attributes no row to such a header, so the definition is kept per member. */

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

/* fdlibm's coefficient table: the member's whole .rodata (MAIN.MAP kf_cos.o
 * .rodata 0x1c, seven words in declaration order).  The code loads every one
 * of them as an immediate, so the table is referenced by nothing. */
static const float one = 1.0000000000e+00, /* 0x3f800000 */
    C1 = 4.1666667908e-02,                 /* 0x3d2aaaab */
    C2 = -1.3888889225e-03,                /* 0xbab60b61 */
    C3 = 2.4801587642e-05,                 /* 0x37d00d01 */
    C4 = -2.7557314297e-07,                /* 0xb493f27c */
    C5 = 2.0875723372e-09,                 /* 0x310f74f6 */
    C6 = -1.1359647598e-11;                /* 0xad47d74e */

float __kernel_cosf(float x, float y)
{
    float a, hz, z, r, qx;
    int ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;
    if (ix < 0x32000000) {
        if ((int)x == 0) {
            return one;
        }
    }
    z = x * x;
    r = z * (C1 + z * (C2 + z * (C3 + z * (C4 + z * (C5 + z * C6)))));
    if (ix < 0x3e99999a) {
        return one - ((float)0.5 * z - (z * r - x * y));
    } else {
        if (ix > 0x3f480000) {
            qx = (float)0.28125;
        } else {
            SET_FLOAT_WORD(qx, ix - 0x01000000);
        }
        hz = (float)0.5 * z - qx;
        a = one - qx;
        return a - (hz - (z * r - x * y));
    }
}
