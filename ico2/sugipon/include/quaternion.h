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

void CopyQuaternion(void *a0, void *a1);
void DivQuaternion(int self, int a1, int a2);
int *GetCurrentQuaternion(void);
void GetDifferencialQuaternionWithNoRegularize(void *out, void *a, void *b);
void GetInverseQuaternion(int a0, int a1);
void GetMatrixFromQuaternion(char *a0, char *a1);
void GetMatrixFromQuaternionPos(char *a0, char *a1, char *a2);
void GetMirrorQuaternion(float *dst, float *src, int mode);
void GetSlerpQuaternion(int a0);
void GetSlerpQuaternionNoRegularize(void *out, void *qa, void *qb, float t);
extern float IdentityQuaternion[4];
void InitQuaternionDrive(void);
void MultiMatrixByQuaternion(void *src);
void MultiQuaternion(void *p0, void *p1, void *p2);
void PopQuaternion(void);
void PushQuaternion(void);
void PushQuaternionWithNoCopy(void);
void RegularizeQuaternion(void *a0);
void RotQuaternionX(void *self, int a1);
void RotQuaternionY(void *self, int a1);
void RotQuaternionZ(void *self, int a1);
void SetCurrentQuaternion(int a0);
void SetIdentityQuaternion(void *a0);
void SetQuaternionByAxisRotate(int *self, short a1, float x, float y, float z);
void SetQuaternionByAxisRotateV(int *self, short a1, int *src);
void SetQuaternionByAxisRotateVWithNoRegularize(int *self, short a1, void *src);

#endif /* QUATERNION_H */
