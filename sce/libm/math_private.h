/*
 * sce/libm/math_private.h
 *
 * The record shapes this archive's members share, under the public name the
 * archive's own sources use for this header.  The shapes follow the members'
 * loads and stores; nothing here is copied from an SDK header.
 */
#ifndef SCE_LIBM_MATH_PRIVATE_H
#define SCE_LIBM_MATH_PRIVATE_H

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
