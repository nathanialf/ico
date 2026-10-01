/*
 * sce/libvu0/libvu0.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the PS2 SDK and newlib header for them (libvu0.h).  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBVU0_LIBVU0_H
#define SCE_LIBVU0_LIBVU0_H

/* The 16-byte aligned float quadword and 4x4 matrix the VU0 entry points
 * work on, under the names the public PS2 SDK documentation gives libvu0's
 * float vector and matrix.  They are quadword aligned: the code copies them
 * with quadword moves.
 */
typedef float sceVu0FVECTOR[4] __attribute__((aligned(16)));

typedef float sceVu0FMATRIX[4][4] __attribute__((aligned(16)));

void sceVpu0Reset(void);                                            /* definition in sce/ */
void sceVu0AddVector(void *dst, void *a, void *b);                  /* definition in sce/ */
void sceVu0ApplyMatrix(void *dst, void *m, void *v);                /* definition in sce/ */
void sceVu0ClampVector(void *dst, void *src, float min, float max); /* definition in sce/ */
void sceVu0CopyMatrix(void *dst, void *src);
void sceVu0CopyVector(void *dst, void *src);
void sceVu0DivVector(void *dst, void *src, float q);             /* definition in sce/ */
void sceVu0FTOI0Vector(void *dst, void *src);                    /* definition in sce/ */
void sceVu0FTOI4Vector(void *dst, void *src);                    /* definition in sce/ */
void sceVu0ITOF0Vector(void *dst, void *src);                    /* definition in sce/ */
float sceVu0InnerProduct(void *a, void *b);                      /* definition in sce/ */
void sceVu0InterVector(void *dst, void *a, void *b, float t);    /* definition in sce/ */
void sceVu0InterVectorXYZ(void *dst, void *a, void *b, float t); /* definition in sce/ */
void sceVu0InversMatrix(void *dst, void *src);
void sceVu0MulMatrix(void *dst, void *m0, void *m1);  /* definition in sce/ */
void sceVu0Normalize(void *dst, void *src);           /* definition in sce/ */
void sceVu0OuterProduct(void *dst, void *a, void *b); /* definition in sce/ */
void sceVu0RotMatrixX(void *d, void *s, float a);
void sceVu0RotMatrixY(void *d, void *s, float a);
void sceVu0RotMatrixZ(void *d, void *s, float a);
void sceVu0RotTransPers(void *dst, void *m, void *src, int mode); /* definition in sce/ */
void sceVu0ScaleVector(void *dst, void *src, float scale);        /* definition in sce/ */
void sceVu0ScaleVectorXYZ(void *dst, void *src, float scale);     /* definition in sce/ */
void sceVu0SubVector(void *dst, void *a, void *b);                /* definition in sce/ */
void sceVu0TransposeMatrix(void *dst, void *src);
void sceVu0UnitMatrix(void *m); /* definition in sce/ */

#endif /* SCE_LIBVU0_LIBVU0_H */
