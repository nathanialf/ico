/* libm.a member ef_rem_pio2.o.  MAIN.MAP member spans tile this run exactly and
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
/* the 24 bits of 2/pi the large-argument path hands to __kernel_rem_pio2f */
extern const int D_00637578[];
/* the high words of the first 32 multiples of pi/2 */
extern const int D_00637890[];
extern float fabsf(float x);
extern int __kernel_rem_pio2f(float *x, float *y, int e0, int nx, int prec, const int *ipio2);

#define zero 0.0000000000e+00f
#define half 5.0000000000e-01f
#define two8 2.5600000000e+02f    /* 0x43800000 */
#define invpio2 6.3661980629e-01f /* 0x3F22F984 */
#define pio2_1 1.5707855225e+00f  /* 0x3FC90F80 */
#define pio2_1t 1.0804334124e-05f /* 0x37354443 */
#define pio2_2 1.0804273188e-05f  /* 0x37354400 */
#define pio2_2t 6.0770999344e-11f /* 0x2E85A308 */
#define pio2_3 6.0770943833e-11f  /* 0x2E85A300 */
#define pio2_3t 6.1232342629e-17f /* 0x248D3132 */

int __ieee754_rem_pio2f(float x, float *y)
{
    float z, w, t, r, fn;
    float tx[3];
    int e0, i, j, nx, n, ix, hx;

    GET_FLOAT_WORD(hx, x);
    ix = hx & 0x7fffffff;
    if (ix <= 0x3f490fd8) { /* |x| ~<= pi/4, no need for reduction */
        y[0] = x;
        y[1] = 0;
        return 0;
    }
    if (ix < 0x4016cbe4) { /* |x| < 3pi/4, special case with n = +-1 */
        if (hx > 0) {
            z = x - pio2_1;
            if ((ix & 0xfffffff0) != 0x3fc90fd0) { /* 24+24 bit pi OK */
                y[0] = z - pio2_1t;
                y[1] = (z - y[0]) - pio2_1t;
            } else { /* near pi/2, use 24+24+24 bit pi */
                z -= pio2_2;
                y[0] = z - pio2_2t;
                y[1] = (z - y[0]) - pio2_2t;
            }
            return 1;
        } else { /* negative x */
            z = x + pio2_1;
            if ((ix & 0xfffffff0) != 0x3fc90fd0) { /* 24+24 bit pi OK */
                y[0] = z + pio2_1t;
                y[1] = (z - y[0]) + pio2_1t;
            } else { /* near pi/2, use 24+24+24 bit pi */
                z += pio2_2;
                y[0] = z + pio2_2t;
                y[1] = (z - y[0]) + pio2_2t;
            }
            return -1;
        }
    }
    if (ix <= 0x43490f80) { /* |x| ~<= 2^7*(pi/2), medium size */
        t = fabsf(x);
        n = (int)(t * invpio2 + half);
        fn = (float)n;
        r = t - fn * pio2_1;
        w = fn * pio2_1t; /* 1st round good to 40 bit */
        if (n < 32 && (int)(ix & 0xffffff00) != D_00637890[n - 1]) {
            y[0] = r - w; /* quick check no cancellation */
        } else {
            unsigned int high;
            j = ix >> 23;
            y[0] = r - w;
            GET_FLOAT_WORD(high, y[0]);
            i = j - ((high >> 23) & 0xff);
            if (i > 8) { /* 2nd iteration needed, good to 57 */
                t = r;
                w = fn * pio2_2;
                r = t - w;
                w = fn * pio2_2t - ((t - r) - w);
                y[0] = r - w;
                GET_FLOAT_WORD(high, y[0]);
                i = j - ((high >> 23) & 0xff);
                if (i > 25) { /* 3rd iteration needed, 74 bits accuracy */
                    t = r;    /* will cover all possible cases */
                    w = fn * pio2_3;
                    r = t - w;
                    w = fn * pio2_3t - ((t - r) - w);
                    y[0] = r - w;
                }
            }
        }
        y[1] = (r - y[0]) - w;
        if (hx < 0) {
            y[0] = -y[0];
            y[1] = -y[1];
            return -n;
        } else {
            return n;
        }
    }
    /*
     * all other (large) arguments
     */
    if (ix >= 0x7f800000) { /* x is inf or NaN */
        y[0] = y[1] = x - x;
        return 0;
    }
    /* set z = scalbn(|x|, ilogb(x) - 7) */
    e0 = (ix >> 23) - 134; /* e0 = ilogb(z) - 7; */
    SET_FLOAT_WORD(z, ix - (e0 << 23));
    for (i = 0; i < 2; i++) {
        tx[i] = (float)((int)(z));
        z = (z - tx[i]) * two8;
    }
    tx[2] = z;
    nx = 3;
    while (tx[nx - 1] == zero) {
        nx--; /* skip zero term */
    }
    n = __kernel_rem_pio2f(tx, y, e0, nx, 2, D_00637578);
    if (hx < 0) {
        y[0] = -y[0];
        y[1] = -y[1];
        return -n;
    }
    return n;
}
