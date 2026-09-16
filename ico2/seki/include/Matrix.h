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

void _AddVector(void *p0, void *p1, void *p2, void *p3);
void _AddVectorXYZ(void *p0, void *p1, void *p2, void *p3);
void _ApplyCurrentMatrix(void *p0, void *p1, void *p2);
void _ApplyMatrix(void *p0, void *p1, void *p2, void *p3);
void _ClearTransCurrentMatrix(void);
void _CopyIVector(void *dst, void *src);
void _CopyMatrix(void *dst, void *src);
void _CopyVector(void *dst, void *src);
void _FTOI0Vector(void *p0, void *p1, void *p2);
void _FTOI4Vector(void *p0, void *p1, void *p2);
void _GetCurrentMatrix(void *p0);
void _GetLength(void *p0, void *p1, void *p2);
void _GetLengthXZ(void *p0, void *p1, void *p2);
void _GetNorm(void *p0);
void _InitCurrentMatrix(void);
void _InnerProduct(void *p0, void *p1, void *p2);
void _InterVector(void *p0, void *p1, void *p2, void *p3);
void _InterVectorXYZ(void *p0, void *p1, void *p2, void *p3);
void _InverseCurrentMatrix(void);
void _MakeLightColorMatrix(void *dst, void *s0, void *s1, void *s2, void *s3);
void _MakeNormalLightMatrix(void *dst, void *s0, void *s1, void *s2);
void _MulCurrentMatrixL(void *m);
void _MulCurrentMatrixR(void *a0);
void _MulMatrix(void *p0, void *p1, void *p2);
void _NormalizeVector(void *p0, void *p1, void *p2);
void _OuterProduct(void *p0, void *p1, void *p2, void *p3);
void _PopCurrentMatrix(void);
void _PopVu0Registers(void);
void _PushCurrentMatrix(void);
void _PushVu0Registers(void);
void _RotCurrentMatrixX(short a0);
void _RotCurrentMatrixY(short a0);
void _RotCurrentMatrixZ(short a0);
void _RotTransPersCurrentMatrix(void *p0, void *p1, void *p2);
void _ScaleCurrentMatrix(float a0, float a1, float a2);
void _ScaleVector(void *p0, void *p1, void *p2);
void _ScaleVector2XYZ(void *p0, void *p1, void *p2, void *p3);
void _ScaleVectorXYZ(void *p0, void *p1, void *p2);
void _SetCurrentMatrix(void *p0);
void _Sqrt(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5);
void _SubVector(void *p0, void *p1, void *p2, void *p3);
void _SubVectorXYZ(void *p0, void *p1, void *p2, void *p3);
void _TransCurrentMatrix(void *p0);
void _TransposeCurrentMatrix(void);
void _TransposeMatrix(void *dst, void *src);
void _UnitMatrix(void *p0);

#endif /* MATRIX_H */
