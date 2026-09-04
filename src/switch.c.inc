/* switch.c -- lever / switch module; #included into box.c (one box.o, listing SRCFILE.TXT). */

#include "common.h"

#include "ico/types.h"

void switchOnSE(int a0) {
    ExecuteSEPackage(a0, 0x3F);
}

void switchReleaseSE(int a0) {
    ExecuteSEPackage(a0, 0x40);
}

inline void SetSwitchTriggerFunc(char *a0, void *a1) {
    *(void **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x1C) = a1;
}

inline int InitSwitchGeo(void) { return 0; }

inline void SwitchGeo(void) {}

inline void SwitchDL(void) {}

extern void MatrixDrive_TransMatrix(float x, float y, float z);
void GetFloorLeverGlobalHoldPoint(void *dst, char *a1) {
    char *p = *(char **)(*(char **)(a1 + 0x15C) + 0x830);
    GetRootMatrix(MatrixDrive_GetMatrix(), a1);
    MatrixDrive_RotMatrixZ(*(short *)(p + 2));
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    CopyVector(dst, MatrixDrive_GetMatrix() + 0x30);
}

extern int GetSkeltonFocusNode(char *a0, int a1);
extern void GetRootPosition(void *dst, void *obj);
extern void MatrixDrive_SetTransposeMatrix(void *a0, void *a1);
extern void MatrixDrive_GetTurnYAngleXZ(void *a0, void *a1, float x, float y, float z);
extern void MatrixDrive_GetTurnXAngleYZ(void *a0, void *a1, float x, float y, float z);
inline void SetFloorLeverWithNodePoint(char *a0, char *a1, int a2) {
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

inline int CanFloorLeverPull(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4) == 0;
}

extern void ClipFloor(void *a0);
extern void LinkParentOfDObj(void *a0, void *a1);
inline void initParentize(char *a0) {
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

extern FloorLeverGeo D_004E5AA0;
extern char D_0061EF10[];
extern int D_0063A438;
extern char D_002A79B8[];
inline FloorLeverGeo *InitFloorLeverGeo(char *a0, char *a1) {
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

inline void SetSwitchState(char *a0, int a1) {
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

INCLUDE_ASM("asm/nonmatchings/src/box", FloorLeverTriStateGeo);

INCLUDE_ASM("asm/nonmatchings/src/box", FloorLeverGeo);
ASM_LIT4_SLOT(D_006393A0, 0.2f);

inline int GetFloorLeverAngle(char *a0) {
    return *(short *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 2);
}

INCLUDE_ASM("asm/nonmatchings/src/box", FloorLeverDL);

INCLUDE_ASM("asm/nonmatchings/src/box", GetWallLeverGlobalHoldPoint);

inline void SetWallLeverWithNodePoint(char *a0, char *a1, int a2) {
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

inline int CanWallLeverPull(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4) == 0;
}

inline FloorLeverGeo *InitWallLeverGeo(char *a0, char *a1) {
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

inline int GetWallLeverAngle(char *a0) {
    return *(short *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 2);
}

inline int IsWallLeverStatus(char *a0) {
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

INCLUDE_ASM("asm/nonmatchings/src/box", WallLeverGeo);
ASM_LIT4_SLOT(D_006393A4, 0.2f);

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
