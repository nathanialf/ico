/*
 * ico2/sugipon/include/matrixDrive.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what matrixDrive.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MATRIXDRIVE_H
#define MATRIXDRIVE_H

extern void AddVectorXYZ(void *p0, void *p1, void *p2, void *p3);
extern void CopyIVector(void *dst, void *src);
extern void CopyMatrix(void *dst, void *src);
extern void CopyVector(void *dst, void *src);
extern float FSqrt(float a0);
extern float GetPointDistance(void *a0, void *a1);
extern void InitMatrixDrive(void);
extern void *MatrixDrive_GetLastMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_GetTurnXAngleYZ(short *a0, short *a1, float x, float y, float z);
extern void MatrixDrive_GetTurnYAngleXZ(short *a0, short *a1, float x, float y, float z);
extern void MatrixDrive_GetTurnZAngleXY(short *a0, short *a1, float x, float y, float z);
extern void MatrixDrive_GetTurnZAngleYX(short *a0, short *a1, float x, float y, float z);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PushMatrixWithNoCopy(void);
extern void MatrixDrive_RotMatrixX(short a0);
extern void MatrixDrive_RotMatrixY(short a0);
extern void MatrixDrive_RotMatrixZ(short a0);
extern void MatrixDrive_ScaleMatrix(float x, float y, float z);
extern void MatrixDrive_SetTransposeMatrix(float *dst, float *src);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void MatrixDrive_TransMatrixV(char *a0);
extern void MatrixDrive_TurnObjectMatrix(float x, float y, float z);
extern void MatrixDrive_TurnYObjectMatrixXZ(float x, float y, float z);
extern void SubVectorXYZ(void *p0, void *p1, void *p2, void *p3);
extern void UnitRotation(void *m);
extern void VectorLength(void *p0);
extern void VectorLengthSquare(void *p0);
extern float XUnitVector[4];
extern float YUnitVector[4];
extern float ZUnitVector[4];
extern float ZeroPoint[4];
extern float ZeroVector[4];

#endif /* MATRIXDRIVE_H */
