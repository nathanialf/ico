/*
 * ico2/sugipon/include/quaternion.h
 *
 * The declarations of what quaternion.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef QUATERNION_H
#define QUATERNION_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order quaternion.c's inline tail has. */
float *GetCurrentQuaternion(void);
float *GetLastQuaternion(void);
void PushQuaternionWithNoCopy(void);
void PopQuaternion(void);
void SetQuaternionByAxisRotate(float *self, short a1, float x, float y, float z);
void SetQuaternionByAxisRotateWithNoRegularize(float *self, short a1, float x, float y, float z);
void SetQuaternionByAxisRotateEAngle(float *out, float *in, float x, float y, float z);
void SetQuaternionByAxisRotateV(float *self, short a1, float *src);
void SetQuaternionByAxisRotateVWithNoRegularize(float *self, short a1, float *src);
void MultiQuaternion(void *p0, void *p1, void *p2);
void DivQuaternion(void *self, void *a1, void *a2);
void GetMatrixFromQuaternionRotElem(void *a0, void *a1);
void GetMatrixFromQuaternionPos(void *mtx, void *a1, void *a2);
void MultiMatrixByQuaternion(void *src);
void GetMirrorQuaternion(float *dst, float *src, int mode);
void RotQuaternionX(void *self, short a1);
void RotQuaternionY(void *self, short a1);
void RotQuaternionZ(void *self, short a1);
void RotQuaternionEAX(void *self, float *in);
void RotQuaternionEAZ(void *self, float *in);
void GetXUnitVectorOfQuaternion(float *out, float *q);
void GetYUnitVectorOfQuaternion(float *out, float *q);
void GetZUnitVectorOfQuaternion(float *out, float *q);
void GetDifferencialQuaternionWithNoRegularize(void *out, void *a, void *b);
float GetQuaternionMagnitude(void *a0);
void SetQuaternionByCosineAxisRotateVWithNoRegularize(void *a0, void *a1, float angle);
void SetQuaternionByCosineAxisRotateV(void *a0, void *a1, float angle);
void SetQuaternionByAxisRotateVEAngle(void *a0, float *a1, void *a2);
float GetQuaternionCosRadian(void *p0, void *p1);
void CopyQuaternion(void *a0, void *a1);
void GetInverseQuaternion(void *a0, void *a1);
void GetMatrixFromQuaternion(void *mtx, void *a1);
/* GetSlerpQuaternion passes its arguments on to
 * GetSlerpQuaternionNoRegularize and regularizes the result; its callers
 * pass four. */
void GetSlerpQuaternion(void *out, void *qa, void *qb, float t);
void GetSlerpQuaternionNoRegularize(void *out, void *qa, void *qb, float t);
extern float IdentityQuaternion[4];
void InitQuaternionDrive(void);
void PushQuaternion(void);
void RegularizeQuaternion(void *a0);
void SetCurrentQuaternion(float *a0);
void SetIdentityQuaternion(void *a0);
void MultiCurrentQuaternion(void *a0);
void RotCurrentQuaternionX(short a0);
void RotCurrentQuaternionY(short a0);
void RotCurrentQuaternionZ(short a0);

#endif /* QUATERNION_H */
