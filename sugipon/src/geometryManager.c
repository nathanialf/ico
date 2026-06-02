#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetRootQuaternionByDObj);

extern void GetRootQuaternionByDObj(void *a0);

void UpdateRootMatrixByDObj(int a0) {
    GetRootQuaternionByDObj(*(void **)(a0 + 0x15C));
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetRootQuaternion);

extern void GetRootQuaternion(void *a0, void *a1);

void UpdateRootMatrix(void *a0, int a1) {
    GetRootQuaternion(a0, *(void **)(a1 + 0x15C));
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", SetRootBaseQuaternion);

extern void SetRootBaseQuaternion(void *a0);

void SetRootQuaternion(int a0) {
    SetRootBaseQuaternion(*(void **)(a0 + 0x15C));
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", SetRootMatrixWithTransOffsetByDObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", SetRootMatrixWithTransOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetRootMatrixRotOffsetByDObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetRootMatrixRotOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", SetRootMatrixRotOffsetByDObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", SetRootMatrixRotOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", SetDirectRootPositionNoFittingWithNodePoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", SetDirectRootPositionWithNodePoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", LocalizeGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetGlobalDirectionOrient);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GlobalizeGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetRootVelocity);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetInitialInverseMatrixByDObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetInitialInverseMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetInitialSkeltonMatrixByDObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", MakeCharGObjList);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", cylinderCollisionCheck);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", LocalizeDirectionOrient);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetCylinderCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetCylinderCollisionWithExceptOwnCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", CylinderCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", CylinderCollisionWithControlDynamics);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetRootMatrixByDObj);
