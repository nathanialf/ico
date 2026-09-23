/* libm.a member kf_sin.o.  MAIN.MAP member spans tile this run exactly and
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

/* fdlibm's coefficient table: the member's whole .rodata (MAIN.MAP kf_sin.o
 * .rodata 0x1c, seven words in declaration order).  The code loads every one
 * of them as an immediate, so the table is referenced by nothing. */
static const float half = 5.0000000000e-01, /* 0x3f000000 */
    S1 = -1.6666667163e-01,                 /* 0xbe2aaaab */
    S2 = 8.3333337680e-03,                  /* 0x3c088889 */
    S3 = -1.9841270114e-04,                 /* 0xb9500d01 */
    S4 = 2.7557314297e-06,                  /* 0x3638ef1b */
    S5 = -2.5050759689e-08,                 /* 0xb2d72f34 */
    S6 = 1.5896910177e-10;                  /* 0x2f2ec9d3 */

float __kernel_sinf(float x, float y, int iy);

float __kernel_sinf(float x, float y, int iy)
{
    float z, r, v;
    int ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;
    if (ix < 0x32000000) {
        if ((int)x == 0) {
            return x;
        }
    }
    z = x * x;
    v = z * x;
    r = S2 + z * (S3 + z * (S4 + z * (S5 + z * S6)));
    if (iy == 0) {
        return x + v * (S1 + z * r);
    }
    return x - ((z * (half * y - v * r) - y) - v * S1);
}
