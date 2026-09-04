#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/box", switchOnSE);
INCLUDE_ASM("asm/nonmatchings/src/box", switchReleaseSE);
INCLUDE_ASM("asm/nonmatchings/src/box", GetFloorLeverGlobalHoldPoint);
INCLUDE_ASM("asm/nonmatchings/src/box", FloorLeverTriStateGeo);
INCLUDE_ASM("asm/nonmatchings/src/box", FloorLeverGeo);
INCLUDE_ASM("asm/nonmatchings/src/box", FloorLeverDL);
INCLUDE_ASM("asm/nonmatchings/src/box", GetWallLeverGlobalHoldPoint);
INCLUDE_ASM("asm/nonmatchings/src/box", WallLeverGeo);
INCLUDE_ASM("asm/nonmatchings/src/box", WallLeverDL);
INCLUDE_ASM("asm/nonmatchings/src/box", CheckReadyAllSwitches);
extern void ExecuteSEPackage(int a0, int a1);

void landingSE(int a0)
{
    ExecuteSEPackage(a0, 0x2);
}
void fallDownStartSE(int a0)
{
    ExecuteSEPackage(a0, 0x24);
}
void pushStartSE(int a0)
{
    ExecuteSEPackage(a0, 0x4);
}
void pullStartSE(int a0)
{
    ExecuteSEPackage(a0, 0xD);
}
void wallHitSE(int a0)
{
    ExecuteSEPackage(a0, 0x1E);
}
INCLUDE_ASM("asm/nonmatchings/src/box", initFallDown);
INCLUDE_ASM("asm/nonmatchings/src/box", checkFieldContact);
INCLUDE_ASM("asm/nonmatchings/src/box", execNormalMove);
INCLUDE_ASM("asm/nonmatchings/src/box", execAutoMove);
INCLUDE_ASM("asm/nonmatchings/src/box", AlignBox);
INCLUDE_ASM("asm/nonmatchings/src/box", initWheels);
INCLUDE_ASM("asm/nonmatchings/src/box", dispWheels);
INCLUDE_ASM("asm/nonmatchings/src/box", getNearestPosition);
INCLUDE_ASM("asm/nonmatchings/src/box", onPathInitialize);
INCLUDE_ASM("asm/nonmatchings/src/box", onPath);
INCLUDE_ASM("asm/nonmatchings/src/box", playAnimationCore);
INCLUDE_ASM("asm/nonmatchings/src/box", MoveFloatingBox);
INCLUDE_ASM("asm/nonmatchings/src/box", avoidCharGObj);
INCLUDE_ASM("asm/nonmatchings/src/box", execFloating);
INCLUDE_ASM("asm/nonmatchings/src/box", initFloating);
INCLUDE_ASM("asm/nonmatchings/src/box", _checkItemBreak);
INCLUDE_ASM("asm/nonmatchings/src/box", initLanding);
INCLUDE_ASM("asm/nonmatchings/src/box", execFallDown);
INCLUDE_ASM("asm/nonmatchings/src/box", inertiaMove);
INCLUDE_ASM("asm/nonmatchings/src/box", action);
INCLUDE_ASM("asm/nonmatchings/src/box", GetBoxHoldPoint);
INCLUDE_ASM("asm/nonmatchings/src/box", _checkItemCollision);
INCLUDE_ASM("asm/nonmatchings/src/box", moveBoxAutoMatic);
INCLUDE_ASM("asm/nonmatchings/src/box", MoveBoxWithHoldPoint);
INCLUDE_ASM("asm/nonmatchings/src/box", ReInitBoxGeo);
INCLUDE_ASM("asm/nonmatchings/src/box", InitBoxGeo);
INCLUDE_ASM("asm/nonmatchings/src/box", BoxGeo);
int GetBoxMode(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x20);
}
int CanHoldBox(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x20) == 0;
}
INCLUDE_ASM("asm/nonmatchings/src/box", BoxDL);
extern void GetRootMatrix();
extern void sceVu0ApplyMatrix();

void GetBoxGlobalHoldPoint(int a0, int a1, int a2)
{
    int buf[16];
    GetRootMatrix(buf);
    sceVu0ApplyMatrix(a0, buf, a2);
}
int IsThisBoxTruck(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x58);
}
INCLUDE_ASM("asm/nonmatchings/src/box", ExecBoxMoveStartReaction);
INCLUDE_ASM("asm/nonmatchings/src/box", ExecBoxMoveEndReaction);
INCLUDE_ASM("asm/nonmatchings/src/box", BoxGeoRestore);
int BoxExtGeoRestore(void) { return 1; }
int BoxMemoryFunc(void) { return 1; }
int InitSwitchGeo(void) { return 0; }
void SwitchGeo(void) {}
void SwitchDL(void) {}
void SetSwitchTriggerFunc(char *a0, void *a1) {
    *(void **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x1C) = a1;
}
INCLUDE_ASM("asm/nonmatchings/src/box", SetSwitchState);
INCLUDE_ASM("asm/nonmatchings/src/box", SetFloorLeverWithNodePoint);
int CanFloorLeverPull(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4) == 0;
}
INCLUDE_ASM("asm/nonmatchings/src/box", InitFloorLeverGeo);
int GetFloorLeverAngle(char *a0) {
    return *(short *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 2);
}
INCLUDE_ASM("asm/nonmatchings/src/box", SetWallLeverWithNodePoint);
int CanWallLeverPull(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4) == 0;
}
INCLUDE_ASM("asm/nonmatchings/src/box", IsWallLeverStatus);
INCLUDE_ASM("asm/nonmatchings/src/box", InitWallLeverGeo);
int GetWallLeverAngle(char *a0) {
    return *(short *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 2);
}
INCLUDE_ASM("asm/nonmatchings/src/box", initParentize);
INCLUDE_ASM("asm/nonmatchings/src/box", getAlign);
INCLUDE_ASM("asm/nonmatchings/src/box", GetDistanceOfGObj);
INCLUDE_ASM("asm/nonmatchings/src/box", moveXPlus);
INCLUDE_ASM("asm/nonmatchings/src/box", moveXMinus);
INCLUDE_ASM("asm/nonmatchings/src/box", moveZPlus);
INCLUDE_ASM("asm/nonmatchings/src/box", moveZMinus);
INCLUDE_ASM("asm/nonmatchings/src/box", BoxRideFunc);
