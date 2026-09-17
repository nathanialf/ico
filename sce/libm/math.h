/*
 * sce/libm/math.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called math.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBM_MATH_H
#define SCE_LIBM_MATH_H

float acosf(float x);                                                  /* definition in sce/ */
float asinf(float x);                                                  /* definition in sce/ */
float atan2f(float y, float x);                                        /* definition in sce/ */
float atanf(float x);                                                  /* definition in sce/ */
float fabsf(float a0);                                                 /* definition in sce/ */
float floorf(float x);                                                 /* definition in sce/ */
float fmodf(float x, float y);                                         /* definition in sce/ */
float sinf(float x);                                                   /* definition in sce/ */

#endif /* SCE_LIBM_MATH_H */
