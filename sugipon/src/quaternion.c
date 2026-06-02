#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", MultiCurrentQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", InvertCurrentQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", SetCurrentQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", RotCurrentQuaternionX);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", RotCurrentQuaternionY);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", RotCurrentQuaternionZ);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", PushQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", InitQuaternionDrive);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", SetIdentityQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", GetMatrixFromQuaternion);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/quaternion", GetLastQuaternion);
