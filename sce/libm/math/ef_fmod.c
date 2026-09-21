/* libm.a member ef_fmod.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <math.h>
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
extern const float D_00637570[]; /* Zero[] = { 0.0f, -0.0f } */

float __ieee754_fmodf(float x, float y)
{
    unsigned int n;
    int hx, hy, hz, ix, iy, sx, i;

    GET_FLOAT_WORD(hx, x);
    GET_FLOAT_WORD(hy, y);
    sx = hx & 0x80000000;
    hx ^= sx;
    hy &= 0x7fffffff;

    if (hy == 0 || hx >= 0x7f800000 || hy > 0x7f800000) {
        return (x * y) / (x * y);
    }
    if (hx < hy) {
        return x;
    }
    if (hx == hy) {
        return D_00637570[(unsigned int)sx >> 31];
    }

    if (hx < 0x00800000) {
        for (ix = -126, i = (hx << 8); i > 0; i <<= 1) {
            ix -= 1;
        }
    } else {
        ix = (hx >> 23) - 127;
    }

    if (hy < 0x00800000) {
        for (iy = -126, i = (hy << 8); i >= 0; i <<= 1) {
            iy -= 1;
        }
    } else {
        iy = (hy >> 23) - 127;
    }

    if (ix >= -126) {
        hx = 0x00800000 | (0x007fffff & hx);
    } else {
        n = -126 - ix;
        hx = hx << n;
    }
    if (iy >= -126) {
        hy = 0x00800000 | (0x007fffff & hy);
    } else {
        n = -126 - iy;
        hy = hy << n;
    }

    /* The ROM copies n and tests the copy (daddu $2,$4,$0 / bnez $2 /
       addiu $4,$4,-1), which is do_jump's plain path on a QUEUED post
       decrement.  A `while (n--)` folds to `--n != -1` and loses the
       copy; fold refuses that rewrite for an ORDERED comparison, and the
       branch is bne, not bgtz, because n is unsigned, so `> 0` reduces to
       `!= 0` only after the rewrite has been refused.  Measured, both
       spellings compiled. */
    n = ix - iy;
    while (n-- > 0) {
        hz = hx - hy;
        if (hz < 0) {
            hx = hx + hx;
        } else {
            if (hz == 0) {
                return D_00637570[(unsigned int)sx >> 31];
            }
            hx = hz + hz;
        }
    }
    hz = hx - hy;
    if (hz >= 0) {
        hx = hz;
    }

    if (hx == 0) {
        return D_00637570[(unsigned int)sx >> 31];
    }
    while (hx < 0x00800000) {
        hx = hx + hx;
        iy -= 1;
    }
    if (iy >= -126) {
        hx = ((hx - 0x00800000) | ((iy + 127) << 23));
        SET_FLOAT_WORD(x, hx | sx);
    } else {
        n = -126 - iy;
        hx >>= n;
        SET_FLOAT_WORD(x, hx | sx);
    }
    return x;
}
