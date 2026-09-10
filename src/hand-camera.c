#include "common.h"

/* prototypes: their order is the inline tail's emission order */
void ClearHandCameraCorrect(void);
void InitHandCameraCorrect(void);
void SetLimitHandCameraCorrect(float a0, float a1);
extern int D_0028F4C0[];
extern float D_0063C2E0;
extern float D_006E9990[];

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", RotateAccordingToStick_PatternThree);
ASM_LIT4_SLOT(D_00639200, 0.1f);
ASM_LIT4_SLOT(D_00639204, 0.008726646f);
ASM_LIT4_SLOT(D_00639208, 3.1415927f);

extern unsigned char D_0063C2E4;
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern float _RotGVF(float *a0, float *a1);

void SetCurrentInfo(void *a0, void *a1)
{
    float *p = D_006E9990;
    float v[4];
    float w[4];
    float ang;
    float t;
    float mx;
    float mn;

    sceVu0SubVector(v, a1, a0);
    w[0] = v[0];
    w[1] = 0.0f;
    w[2] = v[2];
    ang = _RotGVF(w, v);
    p[4] = ang;
    if (v[1] > 0.0f)
        p[4] = -ang;

    if (D_0063C2E4 == 0) {
        t = p[6] * 3.1415927f / 180.0f;
        mx = (t < p[4]) ? p[4] : t;
        p[2] = mx - p[4];
        mn = (p[4] < -t) ? p[4] : -t;
        p[3] = mn - p[4];
    } else {
        mx = p[4] + p[6] * 3.1415927f / 180.0f;
        mx = (mx < -1.4835298f) ? -1.4835298f : ((1.4835298f < mx) ? 1.4835298f : mx);
        p[2] = mx - p[4];
        mn = p[4] - p[6] * 3.1415927f / 180.0f;
        mn = (mn < -1.4835298f) ? -1.4835298f : ((1.4835298f < mn) ? 1.4835298f : mn);
        p[3] = mn - p[4];
    }
}

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", HandyCamera_TargetMoveType);
ASM_LIT4_SLOT(D_00639228, 3.1415927f);

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
