#include "common.h"

union PendCopy {
    float f[8];
    long long q[4];
};

typedef struct { unsigned long _0, _8, _10, _18; } CamTgt;

INCLUDE_ASM("asm/nonmatchings/src/camera-root", SetWSMatrix);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", ConvertCameraSet);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", MakeMatrixFromCameraSet2);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", MakeCameraMatrix);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", CameraEditManual);
extern void CameraEditManual();
extern int D_006E66C0[];
extern void MakeCameraMatrix();

void DebugCameraManual(void)
{
    CameraEditManual(D_006E66C0, 0);
    MakeCameraMatrix(D_006E66C0);
}
extern void ConvertCameraSet(int *a0, void *a1);
extern int D_0063C290;
extern int D_006E66E0[];
extern void GetRootPosition(void *buf, int obj);
extern float _MoveGV(int *a0, int *a1, int *a2, float t);

void DebugCameraSemiAuto(void) {
    if (D_006E66E0[6] != 0) {
        if (_MoveGV(D_006E66C0, D_006E66C0, D_006E66E0, 50.0f) < 1.0f) {
            D_006E66E0[6] = 0;
        }
    } else {
        float buf[10];
        CameraEditManual(D_006E66C0, 1);
        buf[0] = ((float *)D_006E66C0)[0];
        buf[1] = ((float *)D_006E66C0)[1];
        buf[2] = ((float *)D_006E66C0)[2];
        buf[8] = ((float *)D_006E66C0)[5];
        GetRootPosition(&buf[4], D_0063C290);
        ConvertCameraSet(D_006E66C0, buf);
    }
    MakeCameraMatrix(D_006E66C0);
}
extern void CopyVector(void *, void *);
extern char *D_00639CF0;
extern int D_0063AB9C;
extern float D_0063C2A8;
extern void SetCameraTargetPosition(void *, void *, float);
extern float _DistGV(void *, void *);
extern void memset(void *, int, int);
extern void sceVu0AddVector(void *, void *, void *);
extern void sceVu0ApplyMatrix(void *, void *, void *);
extern void sceVu0ScaleVector(void *, void *, float);
extern void sceVu0TransposeMatrix(void *, void *);

void BackToGameCamera(void) {
    char buf[0x80];
    float f20v;
    memset(buf, 0, 0x10);
    *(float *)(buf + 8) = 1.0f;
    sceVu0TransposeMatrix(buf + 0x20, D_00639CF0 + 0x80);
    CopyVector(buf + 0x70, D_00639CF0 + 0xB0);
    *(int *)(buf + 0x7C) = 0;
    sceVu0ApplyMatrix(buf + 0x10, buf + 0x20, buf + 0x70);
    sceVu0ScaleVector(buf + 0x10, buf + 0x10, -1.0f);
    GetRootPosition(buf + 0x60, D_0063AB9C);
    f20v = _DistGV(buf + 0x10, buf + 0x60);
    *(int *)(buf + 0xC) = 0;
    sceVu0ApplyMatrix(buf, buf + 0x20, buf);
    sceVu0ScaleVector(buf, buf, f20v);
    sceVu0AddVector(buf, buf, buf + 0x10);
    SetCameraTargetPosition(buf, buf + 0x10, D_0063C2A8);
}
extern void CameraGetOtherObjOffset(int a0, int a1, int a2);
extern int D_0063B1B0;
extern float D_006E66D4[];

void GetCameraInfomationFromGlobalPosition(int a0, int a1, int a2, int a3, int a4) {
    *(float *)a3 = D_006E66D4[0];
    *(float *)a4 = (float)D_0063B1B0 / 100.0f;
    CameraGetOtherObjOffset(a0, a1, a2);
}
INCLUDE_ASM("asm/nonmatchings/src/camera-root", InitCamera);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", SetCameraMatrix);
extern volatile int D_006E6700[];

void Camctrl_ExitEveRock(void) {
    if (D_006E6700[2] < 4) {
        D_006E6700[1] = 0;
        D_006E6700[0] = D_0063AB9C;
        D_006E6700[2] = 0;
    }
}
void Camctrl_SetTarget(int a0, int a1, int a2)
{
    if (a2 < D_006E6700[2]) {
        return;
    }
    D_006E6700[0] = a0;
    D_006E6700[2] = a2;
    D_006E6700[1] = a1;
}
extern int *D_00639EA4;
extern int GetEfStageCameraTargetID(void);
extern int isysGObjSearchFromObjLayoutID();

int GetCameraDefaultTargetGObj(void) {
    int v = GetEfStageCameraTargetID();
    if (v == 0) {
        return D_00639EA4;
    }
    v = isysGObjSearchFromObjLayoutID(v);
    if (v != 0) {
        return v;
    }
    return D_00639EA4;
}
extern int D_0063C294;

void CameraSetTargetGObj(int a, int b) {
    D_0063C290 = a;
    D_0063C294 = b;
}
extern void sceVu0SubVector(void *, void *, void *);

void CameraChangeTargetParallel(int a0, int a1) {
    char buf[0x30];
    if (a0 == 0) {
        *(int *)(buf + 0) = 0;
        *(int *)(buf + 4) = 0;
        *(int *)(buf + 8) = 0;
    } else {
        GetRootPosition(buf + 0x10, a0);
        GetRootPosition(buf + 0x20, a1);
        sceVu0SubVector(buf, buf + 0x20, buf + 0x10);
    }
    *(CamTgt *)D_006E66E0 = *(CamTgt *)D_006E66C0;
    sceVu0AddVector(D_006E66E0, D_006E66E0, buf);
    D_006E66E0[6] = 1;
}
int CameraGetTarget(void) {
    return D_0063C290;
}
extern int D_0063C294;

void CameraGetTargets(int *a0, int *a1) {
    *a0 = D_0063C290;
    *a1 = D_0063C294;
}
extern int D_0063C2A0;
extern int D_006E66F8[];

void CameraSetMode(int x) {
    D_0063C2A0 = x;
    D_006E66F8[0] = 0;
}
int CameraGetMode(void) {
    return D_0063C2A0;
}
INCLUDE_ASM("asm/nonmatchings/src/camera-root", CameraGetOtherObjOffset);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", InsertCamera_Set);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", InsertCamera_SetNoraml);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", InsertCamera_SetDetail);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", InsertCamera_Exec);
int *GetCurrentCameraSet2(void) {
    return D_006E66C0;
}
extern char D_0063C2AC;

void SetCameraFlag_LwsCutBack(void) {
    D_0063C2AC = 1;
}
extern char D_0063C298;

void SetCameraFlag_GamecamCutBack(void) {
    D_0063C298 = 1;
}
INCLUDE_ASM("asm/nonmatchings/src/camera-root", SetHandCameraLimitInDemo);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", ResetHandCameraLimitInDemo);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", SetZoomMaxValInDemo);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", ResetZoomMaxValInDemo);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", UpdateHandCameraLimitP);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", UpdateHandCameraLimitV);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", UpdateZoomMaxVallInDemo);
extern int D_006E6708[];

int InsertCamera_isEnable(void) {
    return D_006E6708[0] < 2;
}
INCLUDE_ASM("asm/nonmatchings/src/camera-root", CameraSetCameraPosition);
void CameraSetTargetPos(void) {}
extern int D_0063AB98;

void *GetCameraPos(void) {
    if (D_0063AB98 == 0) {
        return 0;
    }
    return D_006E66C0;
}
void GetCameraInfo_tmp(void *dst, float *out) {
    union PendCopy *s = (union PendCopy *)D_006E66C0;
    union PendCopy *d = (union PendCopy *)dst;
    d->q[0] = s->q[0];
    d->q[1] = s->q[1];
    d->q[2] = s->q[2];
    d->q[3] = s->q[3];
    *out = D_0063B1B0 / 100.0f;
}
extern unsigned char D_0063C299;

void testcamerazoom(void) {
    D_0063C299 = 1;
}
extern int D_0063AB6C;

INCLUDE_ASM("asm/nonmatchings/src/camera-root", SetMonitorCameraInitializeFlag);
