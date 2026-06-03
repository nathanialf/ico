#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", MultiCurrentQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", InvertCurrentQuaternion);

extern int D_00629E7C;
extern int D_0065A5C0[];
extern void RegularizeQuaternion(void *a0, void *a1);

void SetCurrentQuaternion(void) {
    void *p = &D_0065A5C0[D_00629E7C * 4];
    RegularizeQuaternion(p, p);
}

extern int D_00629E7C;
extern int D_0065A5C0[];
extern void GetInverseQuaternion(void *a0, void *a1);

void RotCurrentQuaternionX(void *a0) {
    GetInverseQuaternion(&D_0065A5C0[D_00629E7C * 4], a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", RotCurrentQuaternionY);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", RotCurrentQuaternionZ);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", PushQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", InitQuaternionDrive);

extern int D_00629E7C;
extern int D_0065A5C0[];
extern void GetMatrixFromQuaternion(void *a0);

void SetIdentityQuaternion(void) {
    D_00629E7C = 0;
    GetMatrixFromQuaternion(D_0065A5C0);
}

extern void GetInverseQuaternion(void *a0, void *a1);
extern int D_002724B0[];

void GetMatrixFromQuaternion(void *a0) {
    GetInverseQuaternion(a0, D_002724B0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", getQuaternionFromMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", GetQuaternionFromMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", CopyQuaternion);

extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);

void GetInverseQuaternion(void *a0, void *a1) {
    MatrixDrive_TurnObjectMatrix(a0, a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", RegularizeQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", GetSlerpQuaternionNoRegularize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", GetSlerpQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", GetCurrentQuaternion);

void *GetLastQuaternion(void) {
    return &D_0065A5C0[D_00629E7C * 4];
}
