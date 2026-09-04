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
extern int p2o_SetDefaultEnviroment(int a0);
extern void p2o_DispVU1(void *a0);
extern void StopSEPackageWithGroupVariation(int a0, int a1);
extern void dispWheels(char *a0);
extern int D_0028F4D4[];
void BoxDL(char *a0) {
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    p2o_SetDefaultEnviroment((int)a0);
    p2o_DispVU1(a0);
    if (*(int *)(q + 0x58) != 0) {
        dispWheels(a0);
    }
    if (D_0028F4D4[0] != 0) {
        StopSEPackageWithGroupVariation((int)a0, 1);
        *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x138) = 0;
    }
}
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
void ExecBoxMoveStartReaction(char *a0, int a1) {
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if (*(int *)(q + 0x58) != 0) {
        if (*(int *)(q + 0x110) != 0) {
            goto end;
        }
    }
    if (a1 >= 0) {
        pushStartSE((int)a0);
        *(int *)(q + 0x114) = 0;
    } else {
        pullStartSE((int)a0);
        *(int *)(q + 0x114) = 0;
    }
end:
    *(int *)(q + 0x110) = 1;
}
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
extern char D_0061F148[];
extern void debug_StdPrintfDummy(char *fmt, ...);
int BoxGeoRestore(float *a0, float *a1) {
    a0[0] = a1[4];
    a0[1] = a1[5];
    a0[2] = a1[6];
    a0[4] = a1[8];
    a0[5] = a1[9];
    a0[6] = a1[10];
    debug_StdPrintfDummy(D_0061F148, a0[8], a0[9], a0[10]);
    return 1;
}
int BoxExtGeoRestore(void) { return 1; }
int BoxMemoryFunc(void) { return 1; }
int InitSwitchGeo(void) { return 0; }
void SwitchGeo(void) {}
void SwitchDL(void) {}
void SetSwitchTriggerFunc(char *a0, void *a1) {
    *(void **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x1C) = a1;
}
void SetSwitchState(char *a0, int a1) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int cur = *(int *)(p + 4);
    unsigned char ne = cur != a1;
    if (ne) {
        switchOnSE((int)a0);
        *(int *)(p + 4) = a1;
    } else {
        *(int *)(p + 4) = a1;
    }
}
extern int GetSkeltonFocusNode(char *a0, int a1);
extern void GetRootPosition(void *dst, void *obj);
extern void MatrixDrive_SetTransposeMatrix(void *a0, void *a1);
extern void MatrixDrive_GetTurnYAngleXZ(void *a0, void *a1, float x, float y, float z);
extern void MatrixDrive_GetTurnXAngleYZ(void *a0, void *a1, float x, float y, float z);
void SetFloorLeverWithNodePoint(char *a0, char *a1, int a2) {
    float buf[4];
    float pos[4];
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int idx = GetSkeltonFocusNode(a1, a2);
    void *m;
    GetRootPosition(pos, a0);
    sceVu0SubVector(buf, *(char **)(*(char **)(a1 + 0x15C) + 0xC) + (idx << 6) + 0x30, pos);
    *(int *)&buf[3] = 0;
    GetRootMatrix(MatrixDrive_GetMatrix(), a0);
    m = MatrixDrive_GetMatrix();
    MatrixDrive_SetTransposeMatrix(m, MatrixDrive_GetMatrix());
    sceVu0ApplyMatrix(buf, MatrixDrive_GetMatrix(), buf);
    MatrixDrive_GetTurnYAngleXZ(q, q + 2, buf[0], -buf[1], buf[2] * 0.0f);
}
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
void SetWallLeverWithNodePoint(char *a0, char *a1, int a2) {
    float buf[4];
    float pos[4];
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int idx = GetSkeltonFocusNode(a1, a2);
    void *m;
    GetRootPosition(pos, a0);
    sceVu0SubVector(buf, *(char **)(*(char **)(a1 + 0x15C) + 0xC) + (idx << 6) + 0x30, pos);
    *(int *)&buf[3] = 0;
    GetRootMatrix(MatrixDrive_GetMatrix(), a0);
    m = MatrixDrive_GetMatrix();
    MatrixDrive_SetTransposeMatrix(m, MatrixDrive_GetMatrix());
    sceVu0ApplyMatrix(buf, MatrixDrive_GetMatrix(), buf);
    MatrixDrive_GetTurnXAngleYZ(q, q + 2, buf[0], buf[1], buf[2] * 0.0f);
    *(int *)(q + 8) = 0;
}
int CanWallLeverPull(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4) == 0;
}
int IsWallLeverStatus(char *a0) {
    short *p = (short *)*(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = 0;
    if (__builtin_abs(p[1]) < 0xBB9) {
        if (__builtin_abs(p[0]) < 0xBB9) {
            goto end;
        }
    }
    ret = 1;
end:
    return ret;
}
FloorLeverGeo *InitWallLeverGeo(char *a0, char *a1) {
    FloorLeverGeo *g = (FloorLeverGeo *)iosMallocDebug(D_0063A438, 0x20, D_0061EF10, 0x12C);
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
int GetWallLeverAngle(char *a0) {
    return *(short *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 2);
}
extern void ClipFloor(void *a0);
extern void LinkParentOfDObj(void *a0, void *a1);
void initParentize(char *a0) {
    char buf[0xC0] __attribute__((aligned(16)));
    GetRootPosition(buf, a0);
    CopyVector(buf + 0x10, buf);
    *(float *)(buf + 4) -= 10.0f;
    *(float *)(buf + 0x14) += 200.0f;
    ClipFloor(buf);
    if (*(int *)(buf + 0x94) != 0) {
        LinkParentOfDObj(a0, buf + 0x8C);
    }
}
static float getAlign(float v, float g) {
    if (0.0f <= v) {
        return (float)(int)((v + g * 0.5f) / g) * g;
    }
    return -getAlign(-v, g);
}
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
int moveXPlus(float *a0, float f12, float f13, float f14) {
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[2];
    if (w < 0.0f) {
        if (-w < f13) goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13) goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < a0[0])) { rv = 0; goto end; }
    if (a0[0] < f12 + f13) return 1;
    rv = 0;
end:
    return rv;
}
int moveXMinus(float *a0, float f12, float f13, float f14) {
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[2];
    if (w < 0.0f) {
        if (-w < f13) goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13) goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < -a0[0])) { rv = 0; goto end; }
    if (-a0[0] < f12 + f13) return 1;
    rv = 0;
end:
    return rv;
}
int moveZPlus(float *a0, float f12, float f13, float f14) {
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[0];
    if (w < 0.0f) {
        if (-w < f13) goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13) goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < a0[2])) { rv = 0; goto end; }
    if (a0[2] < f12 + f13) return 1;
    rv = 0;
end:
    return rv;
}
int moveZMinus(float *a0, float f12, float f13, float f14) {
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[0];
    if (w < 0.0f) {
        if (-w < f13) goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13) goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13)) goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < -a0[2])) { rv = 0; goto end; }
    if (-a0[2] < f12 + f13) return 1;
    rv = 0;
end:
    return rv;
}
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
