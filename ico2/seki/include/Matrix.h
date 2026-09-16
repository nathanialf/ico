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

extern void _AddVector(void *p0, void *p1, void *p2, void *p3);
extern void _AddVectorXYZ(void *p0, void *p1, void *p2, void *p3);
extern void _ApplyCurrentMatrix(void *p0, void *p1, void *p2);
extern void _ApplyMatrix(void *p0, void *p1, void *p2, void *p3);
extern void _ClearTransCurrentMatrix(void);
extern void _CopyIVector(void *dst, void *src);
extern void _CopyMatrix(void *dst, void *src);
extern void _CopyVector(void *dst, void *src);
extern void _FTOI0Vector(void *p0, void *p1, void *p2);
extern void _FTOI4Vector(void *p0, void *p1, void *p2);
extern void _GetCurrentMatrix(void *p0);
extern void _GetLength(void *p0, void *p1, void *p2);
extern void _GetLengthXZ(void *p0, void *p1, void *p2);
extern void _GetNorm(void *p0);
extern void _InitCurrentMatrix(void);
extern void _InnerProduct(void *p0, void *p1, void *p2);
extern void _InterVector(void *p0, void *p1, void *p2, void *p3);
extern void _InterVectorXYZ(void *p0, void *p1, void *p2, void *p3);
extern void _InverseCurrentMatrix(void);
extern void _MakeLightColorMatrix(void *dst, void *s0, void *s1, void *s2, void *s3);
extern void _MakeNormalLightMatrix(void *dst, void *s0, void *s1, void *s2);
extern void _MulCurrentMatrixL(void *m);
extern void _MulCurrentMatrixR(void *a0);
extern void _MulMatrix(void *p0, void *p1, void *p2);
extern void _NormalizeVector(void *p0, void *p1, void *p2);
extern void _OuterProduct(void *p0, void *p1, void *p2, void *p3);
extern void _PopCurrentMatrix(void);
extern void _PopVu0Registers(void);
extern void _PushCurrentMatrix(void);
extern void _PushVu0Registers(void);
extern void _RotCurrentMatrixX(short a0);
extern void _RotCurrentMatrixY(short a0);
extern void _RotCurrentMatrixZ(short a0);
extern void _RotTransPersCurrentMatrix(void *p0, void *p1, void *p2);
extern void _ScaleCurrentMatrix(float a0, float a1, float a2);
extern void _ScaleVector(void *p0, void *p1, void *p2);
extern void _ScaleVector2XYZ(void *p0, void *p1, void *p2, void *p3);
extern void _ScaleVectorXYZ(void *p0, void *p1, void *p2);
extern void _SetCurrentMatrix(void *p0);
extern void _Sqrt(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5);
extern void _SubVector(void *p0, void *p1, void *p2, void *p3);
extern void _SubVectorXYZ(void *p0, void *p1, void *p2, void *p3);
extern void _TransCurrentMatrix(void *p0);
extern void _TransposeCurrentMatrix(void);
extern void _TransposeMatrix(void *dst, void *src);
extern void _UnitMatrix(void *p0);

#endif /* MATRIX_H */
