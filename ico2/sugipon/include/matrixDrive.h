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

void AddVectorXYZ(void *p0, void *p1, void *p2, void *p3);
void CopyIVector(void *dst, void *src);
void CopyMatrix(void *dst, void *src);
void CopyVector(void *dst, void *src);
float FSqrt(float a0);
float GetPointDistance(void *a0, void *a1);
void InitMatrixDrive(void);
void *MatrixDrive_GetLastMatrix(void);
void *MatrixDrive_GetMatrix(void);
void MatrixDrive_GetTurnXAngleYZ(short *a0, short *a1, float x, float y, float z);
void MatrixDrive_GetTurnYAngleXZ(short *a0, short *a1, float x, float y, float z);
void MatrixDrive_GetTurnZAngleXY(short *a0, short *a1, float x, float y, float z);
void MatrixDrive_GetTurnZAngleYX(short *a0, short *a1, float x, float y, float z);
void MatrixDrive_PopMatrix(void);
void MatrixDrive_PushMatrix(void);
void MatrixDrive_PushMatrixWithNoCopy(void);
void MatrixDrive_RotMatrixX(short a0);
void MatrixDrive_RotMatrixY(short a0);
void MatrixDrive_RotMatrixZ(short a0);
void MatrixDrive_ScaleMatrix(float x, float y, float z);
void MatrixDrive_SetTransposeMatrix(float *dst, float *src);
void MatrixDrive_TransMatrix(float x, float y, float z);
void MatrixDrive_TransMatrixV(char *a0);
void MatrixDrive_TurnObjectMatrix(float x, float y, float z);
void MatrixDrive_TurnYObjectMatrixXZ(float x, float y, float z);
void SubVectorXYZ(void *p0, void *p1, void *p2, void *p3);
void UnitRotation(void *m);
float VectorLength(void *p0);
float VectorLengthSquare(void *p0);
extern float XUnitVector[4];
extern float YUnitVector[4];
extern float ZUnitVector[4];
extern float ZeroPoint[4];
extern float ZeroVector[4];

#endif /* MATRIXDRIVE_H */
