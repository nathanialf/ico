#include "common.h"

typedef struct { unsigned long _0, _8, _10, _18; } CamTgt;





extern int D_00633D84;
extern int D_00633D88;
extern int isysGObjAddHead();
extern int *D_00631AE4;
extern int actBoyCall(void);
extern volatile int D_006D06C0[];
extern int D_00632734;
extern int D_006D0680[];
extern void func_0018B880();
INCLUDE_ASM("asm/nonmatchings/src/camera-root", SetWSMatrix);

void ConvertCameraSet(void)
{
    SetWSMatrix(D_006D0680, 0);
    func_0018B880(D_006D0680);
}

extern int D_006D06A0[];
extern void GetRootMatrixByDObj(void *buf, int obj);
extern float SetLimitHandCameraCorrect(int *a0, int *a1, int *a2, float t);
extern void func_0018B738(int *a0, void *a1);
extern void func_0018B880__p4(int *a0) __asm__("func_0018B880");

void MakeCameraMatrix(void) {
    if (D_006D06A0[6] != 0) {
        if (SetLimitHandCameraCorrect(D_006D0680, D_006D0680, D_006D06A0, 50.0f) < 1.0f) {
            D_006D06A0[6] = 0;
        }
    } else {
        float buf[10];
        SetWSMatrix(D_006D0680, 1);
        buf[0] = ((float *)D_006D0680)[0];
        buf[1] = ((float *)D_006D0680)[1];
        buf[2] = ((float *)D_006D0680)[2];
        buf[8] = ((float *)D_006D0680)[5];
        GetRootMatrixByDObj(&buf[4], D_00633D84);
        func_0018B738(D_006D0680, buf);
    }
    func_0018B880__p4(D_006D0680);
}

extern float ClearHandCameraCorrect(void *, void *);
extern char *D_00631970;
extern float D_00633D98;
extern void MatrixDrive_TurnObjectMatrix(void *, void *);
extern void func_0018B668(void *, void *, float);
extern void func_002438B8(void *, void *, void *);
extern void func_002439B0(void *, void *);
extern void func_00243AD0(void *, void *, void *);
extern void func_00243B18(void *, void *, float);
extern void func_002641D8(void *, int, int);

void CameraEditManual(void) {
    char buf[0x80];
    float f20v;
    func_002641D8(buf, 0, 0x10);
    *(float *)(buf + 8) = 1.0f;
    func_002439B0(buf + 0x20, D_00631970 + 0x80);
    MatrixDrive_TurnObjectMatrix(buf + 0x70, D_00631970 + 0xB0);
    *(int *)(buf + 0x7C) = 0;
    func_002438B8(buf + 0x10, buf + 0x20, buf + 0x70);
    func_00243B18(buf + 0x10, buf + 0x10, -1.0f);
    GetRootMatrixByDObj(buf + 0x60, D_00632734);
    f20v = ClearHandCameraCorrect(buf + 0x10, buf + 0x60);
    *(int *)(buf + 0xC) = 0;
    func_002438B8(buf, buf + 0x20, buf);
    func_00243B18(buf, buf, f20v);
    func_00243AD0(buf, buf, buf + 0x10);
    func_0018B668(buf, buf + 0x10, D_00633D98);
}

extern int D_00632D30;
extern float D_006D0694[];
extern void func_0018CC18(int a0, int a1, int a2);

void DebugCameraManual(int a0, int a1, int a2, int a3, int a4) {
    *(float *)a3 = D_006D0694[0];
    *(float *)a4 = (float)D_00632D30 / 100.0f;
    func_0018CC18(a0, a1, a2);
}

INCLUDE_ASM("asm/nonmatchings/src/camera-root", DebugCameraSemiAuto);

INCLUDE_ASM("asm/nonmatchings/src/camera-root", BackToGameCamera);

void GetCameraInfomationFromGlobalPosition(void) {
    if (D_006D06C0[2] < 4) {
        D_006D06C0[1] = 0;
        D_006D06C0[0] = D_00632734;
        D_006D06C0[2] = 0;
    }
}

void InitCamera(int a0, int a1, int a2)
{
    if (a2 < D_006D06C0[2]) {
        return;
    }
    D_006D06C0[0] = a0;
    D_006D06C0[2] = a2;
    D_006D06C0[1] = a1;
}

int SetCameraMatrix(void) {
    int v = actBoyCall();
    if (v == 0) {
        return D_00631AE4;
    }
    v = isysGObjAddHead(v);
    if (v != 0) {
        return v;
    }
    return D_00631AE4;
}

void Camctrl_ExitEveRock(int a, int b) {
    D_00633D84 = a;
    D_00633D88 = b;
}

extern void func_00243AE8(void *, void *, void *);

void Camctrl_SetTarget(int a0, int a1) {
    char buf[0x30];
    if (a0 == 0) {
        *(int *)(buf + 0) = 0;
        *(int *)(buf + 4) = 0;
        *(int *)(buf + 8) = 0;
    } else {
        GetRootMatrixByDObj(buf + 0x10, a0);
        GetRootMatrixByDObj(buf + 0x20, a1);
        func_00243AE8(buf, buf + 0x20, buf + 0x10);
    }
    *(CamTgt *)D_006D06A0 = *(CamTgt *)D_006D0680;
    func_00243AD0(D_006D06A0, D_006D06A0, buf);
    D_006D06A0[6] = 1;
}

int GetCameraDefaultTargetGObj(void) {
    return D_00633D84;
}

