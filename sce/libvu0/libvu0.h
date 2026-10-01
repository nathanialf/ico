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

void sceVpu0Reset(void);                                        /* definition in sce/ */
void sceVu0AddVector(void *a0, void *a1, void *a2);             /* definition in sce/ */
void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);           /* definition in sce/ */
void sceVu0ClampVector(void *a0, void *a1, float a2, float a3); /* definition in sce/ */
void sceVu0CopyMatrix(void *a0, void *a1);
void sceVu0CopyVector(void *dst, void *src);
void sceVu0DivVector(void *a0, void *a1, float a2);                /* definition in sce/ */
void sceVu0FTOI0Vector(void *a0, void *a1);                        /* definition in sce/ */
void sceVu0FTOI4Vector(void *a0, void *a1);                        /* definition in sce/ */
void sceVu0ITOF0Vector(void *a0, void *a1);                        /* definition in sce/ */
float sceVu0InnerProduct(void *a0, void *a1);                      /* definition in sce/ */
void sceVu0InterVector(void *a0, void *a1, void *a2, float t);     /* definition in sce/ */
void sceVu0InterVectorXYZ(void *a0, void *a1, void *a2, float a3); /* definition in sce/ */
void sceVu0InversMatrix(void *dst, void *src);
void sceVu0MulMatrix(void *a0, void *a1, void *a2);    /* definition in sce/ */
void sceVu0Normalize(void *a0, void *a1);              /* definition in sce/ */
void sceVu0OuterProduct(void *a0, void *a1, void *a2); /* definition in sce/ */
void sceVu0RotMatrixX(void *d, void *s, float a);
void sceVu0RotMatrixY(void *d, void *s, float a);
void sceVu0RotMatrixZ(void *d, void *s, float a);
void sceVu0RotTransPers(void *a0, void *a1, void *a2, int a3); /* definition in sce/ */
void sceVu0ScaleVector(void *a0, void *a1, float a2);          /* definition in sce/ */
void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);       /* definition in sce/ */
void sceVu0SubVector(void *a0, void *a1, void *a2);            /* definition in sce/ */
void sceVu0TransposeMatrix(void *dst, void *src);
void sceVu0UnitMatrix(void *a0); /* definition in sce/ */

#endif /* SCE_LIBVU0_LIBVU0_H */
