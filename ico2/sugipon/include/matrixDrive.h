/*
 * ico2/sugipon/include/matrixDrive.h
 *
 * The declarations of what matrixDrive.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MATRIXDRIVE_H
#define MATRIXDRIVE_H

void AddVectorXYZ(void *d, void *a, void *b);
void CopyIVector(void *dst, void *src);
void CopyMatrix(void *dst, void *src);
void CopyVector(void *dst, void *src);
float FSqrt(float x);
float GetPointDistance(void *a, void *b);
void InitMatrixDrive(void);

float (*MatrixDrive_GetLastMatrix(void))[4];

float (*MatrixDrive_GetMatrix(void))[4];

void MatrixDrive_GetTurnXAngleYZ(short *ay, short *az, float x, float y, float z);
void MatrixDrive_GetTurnYAngleXZ(short *ax, short *az, float x, float y, float z);
void MatrixDrive_GetTurnZAngleXY(short *ax, short *ay, float x, float y, float z);
void MatrixDrive_GetTurnZAngleYX(short *ay, short *ax, float x, float y, float z);
void MatrixDrive_PopMatrix(void);
void MatrixDrive_PushMatrix(void);
void MatrixDrive_PushMatrixWithNoCopy(void);
void MatrixDrive_RotMatrixX(short angle);
void MatrixDrive_RotMatrixY(short angle);
void MatrixDrive_RotMatrixZ(short angle);
void MatrixDrive_ScaleMatrix(float x, float y, float z);
void MatrixDrive_SetTransposeMatrix(void *dst, void *src);
void MatrixDrive_TransMatrix(float x, float y, float z);
void MatrixDrive_TransMatrixV(void *v);
void MatrixDrive_TurnObjectMatrix(float x, float y, float z);
void MatrixDrive_TurnYObjectMatrixXZ(float x, float y, float z);
void SubVectorXYZ(void *d, void *a, void *b);
void UnitRotation(void *m);
float VectorLength(void *v);
float VectorLengthSquare(void *v);
extern float XUnitVector[4];
extern float YUnitVector[4];
extern float ZUnitVector[4];
extern float ZeroPoint[4];
extern float ZeroVector[4];
void MatrixDrive_TurnXObjectMatrixYZ(float x, float y, float z);
void MatrixDrive_GetTurnXAngleZY(short *az, short *ay, float x, float y, float z);
void MatrixDrive_GetTurnMinusZAngleXY(short *ax, short *ay, float x, float y, float z);
void MatrixDrive_TurnViewMatrix(float x, float y, float z);
void MatrixDrive_TurnXObjectMatrixZY(float x, float y, float z);
void MatrixDrive_TurnZObjectMatrixXY(float x, float y, float z);
void MatrixDrive_GetTurnYEAngleXZ(float *ex, float *ez, float x, float y, float z);
void CopyMatrixUncached(void *dst, void *src);

#endif /* MATRIXDRIVE_H */
