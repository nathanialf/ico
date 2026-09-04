#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/rotObject", moveStartSE);
INCLUDE_ASM("asm/nonmatchings/src/rotObject", moveEndSE);
extern void gamesysObjInfoUniqDataSet(void *a0);
void RotObjectGeo(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if ((*(int *)(p + 0x30))++ >= 0x1F) {
        *(int *)(p + 0x30) = 0;
        gamesysObjInfoUniqDataSet(a0);
    }
}
extern void AdjustVerticalSidePlaneOfWall(void *a0, void *a1, void *a2, float a3);
extern void GetGlobalWallPlane(void *a0, void *a1);
extern void GetProjectionPosOfPlane(void *a0, void *a1, void *a2);
extern void GetRootPosition(void *a0, void *a1);
extern void MatrixDrive_SetTransposeMatrix(void *a0, int a1);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);

void GetRotObjectHoldPoint(void *a0, void *a1, void *a2, void *a3) {
    char buf[0x60];

    GetRootPosition(buf + 0x10, a3);
    GetGlobalWallPlane(buf, a2);
    sceVu0ScaleVectorXYZ(a1, buf, -1.0f);
    *(int *)((char *)a1 + 0xC) = 0;
    AdjustVerticalSidePlaneOfWall(a0, a2, buf + 0x10, 10.0f);
    GetProjectionPosOfPlane(a0, buf, a0);
    MatrixDrive_SetTransposeMatrix(buf + 0x20,
        *(int *)(*(char **)(*(int *)a2 + 0x15C) + 0xC) + (*(int *)((char *)a2 + 4) << 6));
    sceVu0ApplyMatrix(a0, buf + 0x20, a0);
    sceVu0ApplyMatrix(a1, buf + 0x20, a1);
    *(float *)((char *)a0 + 4) = -50.0f;
    sceVu0Normalize(a1, a1);
}
INCLUDE_ASM("asm/nonmatchings/src/rotObject", MoveRotObjectWithHoldPoint);
extern void moveStartSE();

void ExecRotObjectMoveStartReaction(int a0, int a1, int a2, int a3)
{
    moveStartSE(a0, a1, a2, a3);
}
extern void moveEndSE();

void ExecRotObjectMoveEndReaction(int a0, int a1, int a2, int a3)
{
    moveEndSE(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/rotObject", SetRotObjectArmRadius);
INCLUDE_ASM("asm/nonmatchings/src/rotObject", GetRotObjectGlobalHoldGeometry);
INCLUDE_ASM("asm/nonmatchings/src/rotObject", InitRotObjectGeo);
INCLUDE_ASM("asm/nonmatchings/src/rotObject", GetRotObjectGameSysObjInfoExtData);
INCLUDE_ASM("asm/nonmatchings/src/rotObject", RotObjectDL);
INCLUDE_ASM("asm/nonmatchings/src/rotObject", GetRotObjectRotCount);
INCLUDE_ASM("asm/nonmatchings/src/rotObject", GetRotObjectZPlusDirection);
int RestoreRotObjectGeo(void)
{
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/rotObject", RestoreRotObjectExtGeo);
INCLUDE_ASM("asm/nonmatchings/src/rotObject", MemoryRotObject);
void SetRotObjectLockFlag(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x34) = a1;
}
