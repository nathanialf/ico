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

extern void CopyQuaternion(void *a0, void *a1);
extern void DivQuaternion(int self, int a1, int a2);
extern int *GetCurrentQuaternion(void);
extern void GetDifferencialQuaternionWithNoRegularize(void *out, void *a, void *b);
extern void GetInverseQuaternion(int a0, int a1);
extern void GetMatrixFromQuaternion(char *a0, char *a1);
extern void GetMatrixFromQuaternionPos(char *a0, char *a1, char *a2);
extern void GetMirrorQuaternion(float *dst, float *src, int mode);
extern void GetSlerpQuaternion(int a0);
extern void GetSlerpQuaternionNoRegularize(void *out, void *qa, void *qb, float t);
extern float IdentityQuaternion[4];
extern void InitQuaternionDrive(void);
extern void MultiMatrixByQuaternion(void *src);
extern void MultiQuaternion(void *p0, void *p1, void *p2);
extern void PopQuaternion(void);
extern void PushQuaternion(void);
extern void PushQuaternionWithNoCopy(void);
extern void RegularizeQuaternion(void *a0);
extern void RotQuaternionX(void *self, int a1);
extern void RotQuaternionY(void *self, int a1);
extern void RotQuaternionZ(void *self, int a1);
extern void SetCurrentQuaternion(int a0);
extern void SetIdentityQuaternion(void *a0);
extern void SetQuaternionByAxisRotate(int *self, short a1, float x, float y, float z);
extern void SetQuaternionByAxisRotateV(int *self, short a1, int *src);
extern void SetQuaternionByAxisRotateVWithNoRegularize(int *self, short a1, void *src);

#endif /* QUATERNION_H */
