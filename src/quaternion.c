#include "common.h"







extern void MatrixDrive_TurnObjectMatrix();
extern char D_00276140[];
extern void func_0010E1F8();
extern void func_0010E158();
extern void func_0010E0B8();
extern int D_00660A40[];
extern void func_0010DDB8();
extern int D_00631B7C;
INCLUDE_ASM("asm/nonmatchings/src/quaternion", MultiCurrentQuaternion);

void InvertCurrentQuaternion(int a0)
{
    int *p = &D_00660A40[D_00631B7C * 4];
    func_0010DDB8(p, p, a0);
}

void SetCurrentQuaternion(void)
{
    int *p = &D_00660A40[D_00631B7C * 4];
    RegularizeQuaternion(p, p);
}

void RotCurrentQuaternionX(int a0)
{
    GetInverseQuaternion(&D_00660A40[D_00631B7C * 4], a0);
}

void RotCurrentQuaternionY(short a0)
{
    func_0010E0B8(&D_00660A40[D_00631B7C * 4], a0);
}

void RotCurrentQuaternionZ(short a0)
{
    func_0010E158(&D_00660A40[D_00631B7C * 4], a0);
}

void PushQuaternion(short a0)
{
    func_0010E1F8(&D_00660A40[D_00631B7C * 4], a0);
}

INCLUDE_ASM("asm/nonmatchings/src/quaternion", InitQuaternionDrive);

void SetIdentityQuaternion(void)
{
    D_00631B7C = 0;
    GetMatrixFromQuaternion(D_00660A40);
}

void GetMatrixFromQuaternion(int a0)
{
    GetInverseQuaternion(a0, D_00276140);
}

INCLUDE_ASM("asm/nonmatchings/src/quaternion", getQuaternionFromMatrix);

INCLUDE_ASM("asm/nonmatchings/src/quaternion", GetQuaternionFromMatrix);

INCLUDE_ASM("asm/nonmatchings/src/quaternion", CopyQuaternion);

void GetInverseQuaternion(int a0, int a1, int a2, int a3)
{
    MatrixDrive_TurnObjectMatrix(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/quaternion", RegularizeQuaternion);

INCLUDE_ASM("asm/nonmatchings/src/quaternion", GetSlerpQuaternionNoRegularize);

INCLUDE_ASM("asm/nonmatchings/src/quaternion", GetSlerpQuaternion);

void GetCurrentQuaternion(int a0)
{
    GetSlerpQuaternion(a0);
    GetSlerpQuaternionNoRegularize(a0);
}

int *GetLastQuaternion(void)
{
    return &D_00660A40[D_00631B7C * 4];
}

