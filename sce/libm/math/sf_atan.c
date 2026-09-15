/* libm.a member sf_atan.o.  MAIN.MAP member spans tile this run exactly and
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
extern float fabsf(float x);
extern const float D_006379D0[]; /* atanhi[4] */
extern const float D_006379E0[]; /* atanlo[4] */
extern const float D_006379F0[]; /* aT[11]   */

float atanf(float x)
{
    float w, s1, s2, z;
    int ix, hx, id;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;
    if (ix >= 0x50800000) {
        if (ix > 0x7f800000) {
            return x + x;
        }
        if (hx > 0) {
            return D_006379D0[3] + D_006379E0[3];
        } else {
            return -D_006379D0[3] - D_006379E0[3];
        }
    }
    if (ix < 0x3ee00000) {
        if (ix < 0x31000000) {
            if (1.0e30f + x > 1.0f) {
                return x;
            }
        }
        id = -1;
    } else {
        x = fabsf(x);
        if (ix < 0x3f980000) {
            if (ix < 0x3f300000) {
                id = 0;
                x = (2.0f * x - 1.0f) / (2.0f + x);
            } else {
                id = 1;
                x = (x - 1.0f) / (x + 1.0f);
            }
        } else {
            if (ix < 0x401c0000) {
                id = 2;
                x = (x - 1.5f) / (1.0f + 1.5f * x);
            } else {
                id = 3;
                x = -1.0f / x;
            }
        }
    }
    z = x * x;
    w = z * z;
    s1 = z * (D_006379F0[0] +
              w * (D_006379F0[2] +
                   w * (D_006379F0[4] +
                        w * (D_006379F0[6] + w * (D_006379F0[8] + w * D_006379F0[10])))));
    s2 = w * (D_006379F0[1] +
              w * (D_006379F0[3] + w * (D_006379F0[5] + w * (D_006379F0[7] + w * D_006379F0[9]))));
    if (id < 0) {
        return x - x * (s1 + s2);
    }
    z = D_006379D0[id] - ((x * (s1 + s2) - D_006379E0[id]) - x);
    return (hx < 0) ? -z : z;
}
