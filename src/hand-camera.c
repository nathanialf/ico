#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", RotateAccordingToStick_PatternThree);
INCLUDE_ASM("asm/nonmatchings/src/hand-camera", SetCurrentInfo);
INCLUDE_ASM("asm/nonmatchings/src/hand-camera", HandyCamera_TargetMoveType);
INCLUDE_ASM("asm/nonmatchings/src/hand-camera", HandCameraCorrect);
extern int D_0028F4C0[];
extern float D_0063C2E0;
extern float D_006E9990[];

void ClearHandCameraCorrect(void)
{
    int a = D_0028F4C0[0];
    int b = D_0028F4C0[1];
    int t = a * 10;
    int diff = 0x3C - t;
    int q;
    *(int *)&D_006E9990[0] = 0;
    *(int *)&D_006E9990[1] = 0;
    q = diff / b;
    D_0063C2E0 = 60.0f / (float)q;
}
void InitHandCameraCorrect(void)
{
    int a = D_0028F4C0[0];
    int b = D_0028F4C0[1];
    int t = a * 10;
    int diff = 0x3C - t;
    int q;
    *(int *)&D_006E9990[0] = 0;
    *(int *)&D_006E9990[1] = 0;
    q = diff / b;
    D_006E9990[5] = 120.0f;
    D_006E9990[6] = 80.0f;
    D_0063C2E0 = 60.0f / (float)q;
}
void SetLimitHandCameraCorrect(float a0, float a1) {
    D_006E9990[5] = a0;
    D_006E9990[6] = a1;
}
