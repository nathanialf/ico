#include "common.h"

/* prototypes: their order is the inline tail's emission order */
void ClearHandCameraCorrect(void);
void InitHandCameraCorrect(void);
void SetLimitHandCameraCorrect(float a0, float a1);
extern int D_0028F4C0[];
extern float D_0063C2E0;
extern float D_006E9990[];

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", RotateAccordingToStick_PatternThree);
INCLUDE_ASM("asm/nonmatchings/src/hand-camera", SetCurrentInfo);
INCLUDE_ASM("asm/nonmatchings/src/hand-camera", HandyCamera_TargetMoveType);

inline void ClearHandCameraCorrect(void)
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

inline void InitHandCameraCorrect(void)
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

inline void SetLimitHandCameraCorrect(float a0, float a1)
{
    D_006E9990[5] = a0;
    D_006E9990[6] = a1;
}

extern char D_0063C2E4;
extern void SetCurrentInfo(void *a0, void *a1);
extern void RotateAccordingToStick_PatternThree(float *a, float *b, float rot, float y);
extern void HandyCamera_TargetMoveType(void *a0, void *a1);

void HandCameraCorrect(void *a0, void *a1, int a2, float f12, float f13, float f14)
{
    float *p = D_006E9990;

    D_0063C2E0 = f14;
    D_0063C2E4 = a2;

    SetCurrentInfo(a0, a1);

    RotateAccordingToStick_PatternThree(p, p + 1, f12, -f13);

    HandyCamera_TargetMoveType(a0, a1);
}
