/* libm.a member ef_asin.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern int __ieee754_rem_pio2f(float x, float *y);
extern float __kernel_cosf(float x, float y);
extern float __kernel_sinf(float x, float y, int iy);

INCLUDE_ASM("asm/nonmatchings/sce/libm/math/ef_asin", __ieee754_asinf);
