/*
 * sce/libvu0/libvu0.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header: a
 * header that only declares leaves no instruction in SRCFILE.TXT and no
 * symbol in MAIN.MAP, so neither its name nor its contents can be read off
 * the ROM.  What places this file is the public naming of the PS2 SDK and of
 * newlib, whose header for these entry points is called libvu0.h and whose
 * archive is this directory's; the declarations themselves are the tree's
 * own facts, each one either the signature of the member that defines the
 * symbol in sce/ or, where the member is still an assembled stub, the
 * spelling the calling TUs already carried and which keeps every one of them
 * byte-identical.  Nothing here is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBVU0_LIBVU0_H
#define SCE_LIBVU0_LIBVU0_H

/* RECONSTRUCTION, PUBLIC SDK NAMING RUNG.  The 16-byte aligned float
 * quadword and 4x4 matrix the VU0 entry points work on; the names are the
 * ones the public PS2 SDK documentation gives libvu0's float vector and
 * matrix, the alignment is the ROM's (its frame copies of these values are
 * quadword moves).
 */
typedef float sceVu0FVECTOR[4] __attribute__((aligned(16)));
typedef float sceVu0FMATRIX[4][4] __attribute__((aligned(16)));

void sceVpu0Reset(void);                                               /* definition in sce/ */
void sceVu0AddVector(void *a0, void *a1, void *a2);                    /* definition in sce/ */
void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);                  /* definition in sce/ */
void sceVu0ClampVector(void *a0, void *a1, float a2, float a3);        /* definition in sce/ */
void sceVu0CopyMatrix(void *a0, void *a1);                             /* dominant spelling at 2 sites */
void sceVu0CopyVector(void *dst, void *src);                           /* dominant spelling at 30 sites */
void sceVu0DivVector(void *a0, void *a1, float a2);                    /* definition in sce/ */
void sceVu0FTOI0Vector(void *a0, void *a1);                            /* definition in sce/ */
void sceVu0ITOF0Vector(void *a0, void *a1);                            /* definition in sce/ */
float sceVu0InnerProduct(void *a0, void *a1);                          /* definition in sce/ */
void sceVu0InterVector(void *a0, void *a1, void *a2, float t);         /* definition in sce/ */
void sceVu0InterVectorXYZ(void *a0, void *a1, void *a2, float a3);     /* definition in sce/ */
void sceVu0InversMatrix(void *dst, void *src);                         /* dominant spelling at 3 sites */
void sceVu0MulMatrix(void *a0, void *a1, void *a2);                    /* definition in sce/ */
void sceVu0Normalize(void *a0, void *a1);                              /* definition in sce/ */
void sceVu0OuterProduct(void *a0, void *a1, void *a2);                 /* definition in sce/ */
void sceVu0RotMatrixX(void *d, void *s, float a);                      /* dominant spelling at 2 sites */
void sceVu0RotMatrixY(void *d, void *s, float a);                      /* dominant spelling at 4 sites */
void sceVu0RotMatrixZ(int a, int b, float f);                          /* dominant spelling at 1 sites */
void sceVu0RotTransPers(void *a0, void *a1, void *a2, int a3);         /* definition in sce/ */
void sceVu0ScaleVector(void *a0, void *a1, float a2);                  /* definition in sce/ */
void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);               /* definition in sce/ */
void sceVu0SubVector(void *a0, void *a1, void *a2);                    /* definition in sce/ */
void sceVu0TransposeMatrix(void *dst, void *src);                      /* dominant spelling at 11 sites */
void sceVu0UnitMatrix(void *a0);                                       /* definition in sce/ */

#endif /* SCE_LIBVU0_LIBVU0_H */
