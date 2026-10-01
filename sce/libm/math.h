/*
 * sce/libm/math.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (math.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBM_MATH_H
#define SCE_LIBM_MATH_H

/* newlib's library-version switch (its math.h names): s_lib_ver.c defines
   the one word, the float wrappers test it. */
enum __fdlibm_version { __fdlibm_ieee = -1, __fdlibm_svid, __fdlibm_xopen, __fdlibm_posix };

#define _LIB_VERSION_TYPE enum __fdlibm_version
#define _LIB_VERSION __fdlib_version

extern const _LIB_VERSION_TYPE _LIB_VERSION; /* definition in sce/ */

#define _IEEE_ __fdlibm_ieee
#define _SVID_ __fdlibm_svid
#define _XOPEN_ __fdlibm_xopen
#define _POSIX_ __fdlibm_posix

float acosf(float x);                /* definition in sce/ */
float asinf(float x);                /* definition in sce/ */
float atan2f(float y, float x);      /* definition in sce/ */
float atanf(float x);                /* definition in sce/ */
float fabsf(float a0);               /* definition in sce/ */
float floorf(float x);               /* definition in sce/ */
float fmodf(float x, float y);       /* definition in sce/ */
float sinf(float x);                 /* definition in sce/ */
float copysignf(float a0, float a1); /* definition in sce/ */
int isnanf(float x);                 /* definition in sce/ */

/* newlib's math.h: the record the wrappers hand matherr */
struct exception {
    int type;      /* 0x0 */
    char *name;    /* 0x4 */
    double arg1;   /* 0x8 */
    double arg2;   /* 0x10 */
    double retval; /* 0x18 */
    int err;       /* 0x20 */
};

int matherr(struct exception *x); /* definition in sce/ */
float scalbnf(float x, int n);    /* definition in sce/ */
int isinf(long long x);           /* definition in sce/ */
int isnan(long long x);           /* definition in sce/ */

#endif /* SCE_LIBM_MATH_H */
