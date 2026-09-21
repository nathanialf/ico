/*
 * ico2/seki/include/Matrix.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what Matrix.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MATRIX_H
#define MATRIX_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order Matrix.c's inline tail has. */
void _Sqrt(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5);
void _InitCurrentMatrix(void);
void _UnitCurrentMatrix(void);
void _PushCurrentMatrix(void);
void _PopCurrentMatrix(void);
void _TransCurrentMatrix(void *p0);
void _SetTransCurrentMatrix(void *p0);
void _ClearTransCurrentMatrix(void);
void _RotCurrentMatrixX(short a0);
void _RotCurrentMatrixY(short a0);
void _RotCurrentMatrixZ(short a0);
void _ScaleCurrentMatrix(float a0, float a1, float a2);
void _GetCurrentMatrix(void *p0);
void _GetCurrentMatrixTrans(void *p0);
void _SetCurrentMatrix(void *p0);
void _MulCurrentMatrixR(void *a0);
void _MulCurrentMatrixL(void *m);
void _ApplyCurrentMatrix(void *p0, void *p1, void *p2);
void _RotTransPersCurrentMatrix(void *p0, void *p1, void *p2);
void _TransposeCurrentMatrix(void);
void _TransposeRotationCurrentMatrix(void);
void _InverseCurrentMatrix(void);
void _NormalizeVector(void *p0, void *p1, void *p2);
void _InnerProduct(void *p0, void *p1, void *p2);
void _OuterProduct(void *p0, void *p1, void *p2, void *p3);
void _AddVector(void *p0, void *p1, void *p2, void *p3);
void _AddVectorXYZ(void *p0, void *p1, void *p2, void *p3);
void _SubVector(void *p0, void *p1, void *p2, void *p3);
void _SubVectorXYZ(void *p0, void *p1, void *p2, void *p3);
void _ScaleVector(void *p0, void *p1, void *p2);
void _ScaleVectorXYZ(void *p0, void *p1, void *p2);
void _ScaleVector2XYZ(void *p0, void *p1, void *p2, void *p3);
void _FTOI4Vector(void *p0, void *p1, void *p2);
void _FTOI0Vector(void *p0, void *p1, void *p2);
void _CopyVector(void *dst, void *src);
void _CopyIVector(void *dst, void *src);
void _UnitVector(void *p0);
void _InterVector(void *p0, void *p1, void *p2, void *p3);
void _InterVectorXYZ(void *p0, void *p1, void *p2, void *p3);
void _GetNorm(void *p0);
void _GetLength(void *p0, void *p1, void *p2);
void _GetLengthXY(void *p0, void *p1, void *p2);
void _GetLengthXZ(void *p0, void *p1, void *p2);
void _CopyMatrix(void *dst, void *src);
void _MulMatrix(void *p0, void *p1, void *p2);
void _ApplyMatrix(void *p0, void *p1, void *p2, void *p3);
void _UnitMatrix(void *p0);
void _UnitRotation(void *p0);
void _TransposeMatrix(void *dst, void *src);
void _InversMatrix(void *dst, void *src);
void _ScaleMatrixV(void *dst, void *src, void *v);
void _SetCameraMatrix(void *dst, void *pos, void *dir, void *up);
void _MakeNormalLightMatrix(void *dst, void *s0, void *s1, void *s2);
void _MakeLightColorMatrix(void *dst, void *s0, void *s1, void *s2, void *s3);
/* corrected from the reconstruction: the ROM body reads $f12 (VU0_MFC1(a2, 12)), so
 * the call takes ONE float, which is what ico2/common/src/main.c passes. */
void _InitRandom(float seed);
float _GetRandom(void);
void _GetRandomVector(void *p0);
void _GetRandomVector0(void *p0);
void _RotTransCurrentMatrix(void *p0, void *p1);
void _PopVu0Registers(void);
void _PushVu0Registers(void);

#endif /* MATRIX_H */
