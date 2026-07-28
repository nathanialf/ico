#include "common.h"





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

INCLUDE_ASM("asm/nonmatchings/src/camera-root", MakeCameraMatrix);

INCLUDE_ASM("asm/nonmatchings/src/camera-root", CameraEditManual);

INCLUDE_ASM("asm/nonmatchings/src/camera-root", DebugCameraManual);

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

INCLUDE_ASM("asm/nonmatchings/src/camera-root", Camctrl_SetTarget);

int GetCameraDefaultTargetGObj(void) {
    return D_00633D84;
}

