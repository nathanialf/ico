#include "common.h"

#include "ico/types.h"

void switchOnSE(int a0) {
    ExecuteSEPackage(a0, 0x3F);
}
void switchReleaseSE(int a0) {
    ExecuteSEPackage(a0, 0x40);
}
extern void MatrixDrive_TransMatrix(float x, float y, float z);
void GetFloorLeverGlobalHoldPoint(void *dst, char *a1) {
    char *p = *(char **)(*(char **)(a1 + 0x15C) + 0x830);
    GetRootMatrix(MatrixDrive_GetMatrix(), a1);
    MatrixDrive_RotMatrixZ(*(short *)(p + 2));
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    CopyVector(dst, MatrixDrive_GetMatrix() + 0x30);
}
INCLUDE_ASM("asm/nonmatchings/src/box", FloorLeverTriStateGeo);
INCLUDE_ASM("asm/nonmatchings/src/box", FloorLeverGeo);
INCLUDE_ASM("asm/nonmatchings/src/box", FloorLeverDL);
INCLUDE_ASM("asm/nonmatchings/src/box", GetWallLeverGlobalHoldPoint);
INCLUDE_ASM("asm/nonmatchings/src/box", WallLeverGeo);
void WallLeverDL(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    char *d;
    p2o_DispVU1(a0);
    MatrixDrive_PushMatrix();
    GetRootMatrix(MatrixDrive_GetMatrix(), a0);
    MatrixDrive_RotMatrixZ(*(short *)(p + 2));
    MatrixDrive_RotMatrixX(*(short *)(p + 0));
    d = *(char **)(p + 0x10);
    CopyMatrix(*(char **)(d + 0xC), MatrixDrive_GetMatrix());
    p2o_DispVU1DObj(*(int *)(p + 0x10));
    MatrixDrive_PopMatrix();
}
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
void ExecBoxMoveEndReaction(char *a0) {
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if (*(int *)(q + 0x58) == 0 || *(int *)(q + 0x110) != 0) {
        StopSEPackage((int)a0);
        StopSEPackageWithGroupVariation((int)a0, 1);
        ExecuteSEPackage((int)a0, 0x16);
        if (*(int *)(q + 0x140) != 0) {
            wallHitSE((int)a0);
            *(int *)(q + 0x140) = 0;
        }
    }
    *(int *)(q + 0x110) = 0;
}
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
typedef struct { int w[8]; } FloorLeverGeo;
extern FloorLeverGeo D_004E5AA0;
extern char D_0061EF10[];
extern int D_0063A438;
extern char D_002A79B8[];
FloorLeverGeo *InitFloorLeverGeo(char *a0, char *a1) {
    FloorLeverGeo *g = (FloorLeverGeo *)iosMallocDebug(D_0063A438, 0x20, D_0061EF10, 0x8D);
    *g = D_004E5AA0;
    if (*(int *)(a1 + 0x30) != 0) {
        g->w[5] = 1;
    } else {
        g->w[5] = 0;
    }
    g->w[3] = CSVSYSTEM_InitDObj(*(int *)(D_002A79B8 + *(int *)(*(char **)(a0 + 0x15C) + 0x844) * 0x28), a1);
    g->w[4] = CSVSYSTEM_InitDObj(*(int *)(D_002A79B8 + *(int *)(*(char **)(a0 + 0x15C) + 0x844) * 0x28 + 4), a1);
    return g;
}
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
extern float sceVu0InnerProduct(void *a0, void *a1);
extern float FSqrt(float f);
float GetDistanceOfGObj(void *a0, void *a1) {
    char v[0x10];
    char w[0x10];
    GetRootPosition(v, a1);
    GetRootPosition(w, a0);
    sceVu0SubVector(v, v, w);
    return FSqrt(sceVu0InnerProduct(v, v));
}
INCLUDE_ASM("asm/nonmatchings/src/box", moveXPlus);
INCLUDE_ASM("asm/nonmatchings/src/box", moveXMinus);
INCLUDE_ASM("asm/nonmatchings/src/box", moveZPlus);
INCLUDE_ASM("asm/nonmatchings/src/box", moveZMinus);
int BoxRideFunc(int *a0, char *a1) {
    char *obj = (char *)*a0;
    char *p15c = *(char **)(obj + 0x15C);
    char *s0 = *(char **)(p15c + 0x830);
    char buf[0x20];
    if (*(int *)(s0 + 0x20) != 5) {
        return 0;
    }
    *(float *)(p15c + 0x134) += 0.5f;
    GetRootPosition(buf + 0x10, obj);
    CopyVector(buf, *(char **)(a1 + 0x15C) + 0xA0);
    *(int *)(buf + 4) = 0;
    sceVu0AddVector(s0 + 0xD0, s0 + 0xD0, buf);
    return 1;
}
