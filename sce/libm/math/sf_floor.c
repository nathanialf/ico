/* libm.a member sf_floor.o.  MAIN.MAP member spans tile this run exactly and
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
/* fdlibm's `huge` (1.0e30f).  ee-gcc emits `li.s $f0,1e30` for it, and the
   period ee-as expands a TWO-WORD li.s to a .lit4 pool load where the ROM's
   assembler expanded it to the immediate lui/ori/mtc1 triple, so the immediate
   is hand-placed here (the standing fdlibm two-word-float ruling; kf_cos.c
   carries the same idiom).  $1 is the assembler temporary the expansion uses. */
#define LOAD_HUGE(f) __asm__("lui $1,0x7149\n\tori $1,$1,0xf2ca\n\tmtc1 $1,%0" : "=f"(f))

float floorf(float x)
{
    int i0, j0;
    unsigned int i;

    GET_FLOAT_WORD(i0, x);
    j0 = ((i0 >> 23) & 0xff) - 127;
    if (j0 < 23) {
        if (j0 < 0) { /* raise inexact if x != 0 */
            float huge;
            LOAD_HUGE(huge);
            if (x + huge > (float)0.0) { /* return 0*sign(x) if |x|<1 */
                if (i0 >= 0) {
                    i0 = 0;
                } else if ((i0 & 0x7fffffff) != 0) {
                    i0 = 0xbf800000;
                }
            }
        } else {
            i = (0x007fffff) >> j0;
            if ((i0 & i) == 0)
                return x; /* x is integral */
            {
                float huge;
                LOAD_HUGE(huge);
                if (x + huge > (float)0.0) { /* raise inexact flag */
                    if (i0 < 0)
                        i0 += (0x00800000) >> j0;
                    i0 &= (~i);
                }
            }
        }
    } else {
        if (j0 == 0x80)
            return x + x; /* inf or NaN */
        else
            return x; /* x is integral */
    }
    SET_FLOAT_WORD(x, i0);
    return x;
}
