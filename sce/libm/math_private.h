/*
 * sce/libm/math_private.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header.  This
 * file carries the record shapes that this archive's members all carried a
 * private copy of; its name is the public one the archive's own sources use.
 * The shapes are read back from the ROM's loads and stores, not copied from
 * any SDK header.
 */
#ifndef SCE_LIBM_MATH_PRIVATE_H
#define SCE_LIBM_MATH_PRIVATE_H

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 14 TUs. */
typedef union {
    float value;
    unsigned int word;
} ieee_float_shape_type;

float __ieee754_acosf(float x);             /* definition in sce/ */
float __ieee754_asinf(float x);             /* definition in sce/ */
float __ieee754_atan2f(float y, float x);   /* definition in sce/ */
float __ieee754_fmodf(float x, float y);    /* definition in sce/ */
int __ieee754_rem_pio2f(float x, float *y); /* definition in sce/ */
float __ieee754_sqrtf(float x);             /* definition in sce/ */
float __kernel_cosf(float x, float y);      /* definition in sce/ */

int __kernel_rem_pio2f(float *x, float *y, int e0, int nx, int prec,
                       const int *ipio2); /* definition in sce/ */

float __kernel_sinf(float x, float y, int iy); /* definition in sce/ */

#endif /* SCE_LIBM_MATH_PRIVATE_H */
