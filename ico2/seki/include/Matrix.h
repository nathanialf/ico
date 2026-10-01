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
void _TransCurrentMatrix(void *v);
void _SetTransCurrentMatrix(void *v);
void _ClearTransCurrentMatrix(void);
void _RotCurrentMatrixX(short angle);
void _RotCurrentMatrixY(short angle);
void _RotCurrentMatrixZ(short angle);
void _ScaleCurrentMatrix(float sx, float sy, float sz);
void _GetCurrentMatrix(void *dst);
void _GetCurrentMatrixTrans(void *dst);
void _SetCurrentMatrix(void *m);
void _MulCurrentMatrixR(void *m);
void _MulCurrentMatrixL(void *m);
void _ApplyCurrentMatrix(void *dst, void *src);
void _RotTransPersCurrentMatrix(void *dst, void *src);
void _TransposeCurrentMatrix(void);
void _TransposeRotationCurrentMatrix(void);
void _InverseCurrentMatrix(void);
/* two parameters: every caller passes two and the body reads only those */
void _NormalizeVector(void *dst, void *src);
/* the inner product of two vectors, returned as a float */
float _InnerProduct(void *a, void *b);
void _OuterProduct(void *dst, void *a, void *b);
void _AddVector(void *dst, void *a, void *b);
void _AddVectorXYZ(void *dst, void *a, void *b);
/* dst = a - b */
void _SubVector(void *dst, void *a, void *b);
void _SubVectorXYZ(void *dst, void *a, void *b);
void _ScaleVector(void *dst, void *src, float s);
void _ScaleVectorXYZ(void *dst, void *src, float s);
void _ScaleVector2XYZ(void *dst, void *a, void *b);
void _FTOI4Vector(void *dst, void *src);
void _FTOI0Vector(void *dst, void *src);
void _CopyVector(void *dst, void *src);
void _CopyIVector(void *dst, void *src);
void _UnitVector(void *dst);
void _InterVector(void *dst, void *a, void *b, float t);
void _InterVectorXYZ(void *dst, void *a, void *b, float t);
float _GetNorm(void *v);
float _GetLength(void *a, void *b);
float _GetLengthXY(void *a, void *b);
float _GetLengthXZ(void *a, void *b);
void _CopyMatrix(void *dst, const void *src);
void _MulMatrix(void *dst, void *a, void *b);
void _ApplyMatrix(void *dst, void *m, void *v);
void _UnitMatrix(void *dst);
void _UnitRotation(void *dst);
void _TransposeMatrix(void *dst, void *src);
void _InversMatrix(void *dst, void *src);
void _ScaleMatrixV(void *dst, void *src, void *v);
void _SetCameraMatrix(void *dst, void *pos, void *dir, void *up);
void _MakeNormalLightMatrix(void *dst, void *s0, void *s1, void *s2);
void _MakeLightColorMatrix(void *dst, void *s0, void *s1, void *s2, void *s3);
/* the seed is one float, which is what ico2/common/src/main.c passes */
void _InitRandom(float seed);
float _GetRandom(void);
void _GetRandomVector(void *dst);
void _GetRandomVector0(void *dst);
void _RotTransCurrentMatrix(void *dst, void *src);
void _PopVu0Registers(void);
void _PushVu0Registers(void);

#endif /* MATRIX_H */
