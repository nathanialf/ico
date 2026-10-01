/*
 * ico2/sugipon/include/matrixDrive.h
 *
 * The declarations of what matrixDrive.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MATRIXDRIVE_H
#define MATRIXDRIVE_H

void AddVectorXYZ(void *p0, void *p1, void *p2);
void CopyIVector(void *dst, void *src);
void CopyMatrix(void *dst, void *src);
void CopyVector(void *dst, void *src);
float FSqrt(float a0);
float GetPointDistance(void *a0, void *a1);
void InitMatrixDrive(void);

float (*MatrixDrive_GetLastMatrix(void))[4];

float (*MatrixDrive_GetMatrix(void))[4];

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
void MatrixDrive_SetTransposeMatrix(void *dst, void *src);
void MatrixDrive_TransMatrix(float x, float y, float z);
void MatrixDrive_TransMatrixV(void *a0);
void MatrixDrive_TurnObjectMatrix(float x, float y, float z);
void MatrixDrive_TurnYObjectMatrixXZ(float x, float y, float z);
void SubVectorXYZ(void *p0, void *p1, void *p2);
void UnitRotation(void *m);
float VectorLength(void *p0);
float VectorLengthSquare(void *p0);
extern float XUnitVector[4];
extern float YUnitVector[4];
extern float ZUnitVector[4];
extern float ZeroPoint[4];
extern float ZeroVector[4];
void MatrixDrive_TurnXObjectMatrixYZ(float x, float y, float z);
void MatrixDrive_GetTurnXAngleZY(short *a0, short *a1, float x, float y, float z);
void MatrixDrive_GetTurnMinusZAngleXY(short *a0, short *a1, float x, float y, float z);
void MatrixDrive_TurnViewMatrix(float x, float y, float z);
void MatrixDrive_TurnXObjectMatrixZY(float x, float y, float z);
void MatrixDrive_TurnZObjectMatrixXY(float x, float y, float z);
void MatrixDrive_GetTurnYEAngleXZ(float *a0, float *a1, float x, float y, float z);
void CopyMatrixUncached(void *dst, void *src);

#endif /* MATRIXDRIVE_H */
