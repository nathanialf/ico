/*
 * ico2/seki/include/Matrix.h
 *
 * The declarations of what Matrix.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MATRIX_H
#define MATRIX_H

/* Matrix.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
float _Sqrt(float x);
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
void _ApplyCurrentMatrix(void *p0, void *p1);
void _RotTransPersCurrentMatrix(void *p0, void *p1);
void _TransposeCurrentMatrix(void);
void _TransposeRotationCurrentMatrix(void);
void _InverseCurrentMatrix(void);
/* two parameters: every caller passes two and the body reads only those */
void _NormalizeVector(void *p0, void *p1);
/* the inner product of two vectors, returned as a float */
float _InnerProduct(void *a, void *b);
void _OuterProduct(void *p0, void *p1, void *p2);
void _AddVector(void *p0, void *p1, void *p2);
void _AddVectorXYZ(void *p0, void *p1, void *p2);
/* dst = a - b */
void _SubVector(void *dst, void *a, void *b);
void _SubVectorXYZ(void *p0, void *p1, void *p2);
void _ScaleVector(void *p0, void *p1, float s);
void _ScaleVectorXYZ(void *p0, void *p1, float s);
void _ScaleVector2XYZ(void *p0, void *p1, void *p2);
void _FTOI4Vector(void *p0, void *p1);
void _FTOI0Vector(void *p0, void *p1);
void _CopyVector(void *dst, void *src);
void _CopyIVector(void *dst, void *src);
void _UnitVector(void *p0);
void _InterVector(void *p0, void *p1, void *p2, float t);
void _InterVectorXYZ(void *p0, void *p1, void *p2, float t);
float _GetNorm(void *v);
float _GetLength(void *a, void *b);
float _GetLengthXY(void *a, void *b);
float _GetLengthXZ(void *a, void *b);
void _CopyMatrix(void *dst, const void *src);
void _MulMatrix(void *p0, void *p1, void *p2);
void _ApplyMatrix(void *p0, void *p1, void *p2);
void _UnitMatrix(void *p0);
void _UnitRotation(void *p0);
void _TransposeMatrix(void *dst, void *src);
void _InversMatrix(void *dst, void *src);
void _ScaleMatrixV(void *dst, void *src, void *v);
void _SetCameraMatrix(void *dst, void *pos, void *dir, void *up);
void _MakeNormalLightMatrix(void *dst, void *s0, void *s1, void *s2);
void _MakeLightColorMatrix(void *dst, void *s0, void *s1, void *s2, void *s3);
/* the seed is one float, which is what ico2/common/src/main.c passes */
void _InitRandom(float seed);
float _GetRandom(void);
void _GetRandomVector(void *p0);
void _GetRandomVector0(void *p0);
void _RotTransCurrentMatrix(void *p0, void *p1);
void _PopVu0Registers(void);
void _PushVu0Registers(void);

#endif /* MATRIX_H */
