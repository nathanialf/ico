/*
 * ico2/sugipon/include/quaternion.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what quaternion.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef QUATERNION_H
#define QUATERNION_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order quaternion.c's inline tail has. */
int *GetCurrentQuaternion(void);
int *GetLastQuaternion(void);
void PushQuaternionWithNoCopy(void);
void PopQuaternion(void);
void SetQuaternionByAxisRotate(int *self, short a1, float x, float y, float z);
void SetQuaternionByAxisRotateWithNoRegularize(int *self, int a1, float x, float y, float z);
void SetQuaternionByAxisRotateEAngle(float *out, float *in, float x, float y, float z);
void SetQuaternionByAxisRotateV(int *self, short a1, int *src);
void SetQuaternionByAxisRotateVWithNoRegularize(int *self, short a1, void *src);
void MultiQuaternion(void *p0, void *p1, void *p2);
void DivQuaternion(int self, int a1, int a2);
void GetMatrixFromQuaternionRotElem(char *a0, char *a1);
void GetMatrixFromQuaternionPos(char *a0, char *a1, char *a2);
void MultiMatrixByQuaternion(void *src);
void GetMirrorQuaternion(float *dst, float *src, int mode);
void RotQuaternionX(void *self, int a1);
void RotQuaternionY(void *self, int a1);
void RotQuaternionZ(void *self, int a1);
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
void GetInverseQuaternion(int a0, int a1);
void GetMatrixFromQuaternion(char *a0, char *a1);
/* The ROM proves the arity: GetSlerpQuaternion is a forwarder that saves a0,
 * calls GetSlerpQuaternionNoRegularize and tail-calls RegularizeQuaternion,
 * so its other three arguments reach the callee untouched in $5, $6 and $f12
 * (0x0010DA40). Its callers pass four. */
void GetSlerpQuaternion(void *out, void *qa, void *qb, float t);
void GetSlerpQuaternionNoRegularize(void *out, void *qa, void *qb, float t);
extern float IdentityQuaternion[4];
void InitQuaternionDrive(void);
void PushQuaternion(void);
void RegularizeQuaternion(void *a0);
void SetCurrentQuaternion(int a0);
void SetIdentityQuaternion(void *a0);

#endif /* QUATERNION_H */
