#include "common.h"


extern void sceVu0Normalize();
extern void sceVu0SubVector();
extern float sceVu0InnerProduct(void *a0, void *a1);

void RotateAccordingToStick_PatternThree(void *a0, void *a1) {
    char buf[0x10];
    sceVu0SubVector(buf, a0, a1);
    *(int *)(buf + 4) = 0;
    sceVu0InnerProduct(buf, buf);
}

void _DistSqGV(void *a0, void *a1) {
    char buf[0x10];
    sceVu0SubVector(buf, a0, a1);
    sceVu0InnerProduct(buf, buf);
}

extern float FSqrt(float a0);

void _DistGV(void *a0, void *a1) {
    char buf[0x10];
    sceVu0SubVector(buf, a0, a1);
    FSqrt(sceVu0InnerProduct(buf, buf));
}

void _DistxzGV(void *a0, void *a1) {
    char buf[0x10];
    sceVu0SubVector(buf, a0, a1);
    *(int *)(buf + 4) = 0;
    FSqrt(sceVu0InnerProduct(buf, buf));
}

extern void _InterGV(float *a0, float *a1, float *a2, float a3, float a4);

float SetLimitHandCameraCorrect(float *a0, float *a1, float *a2, float a3)
{
    float buf[4];
    float ang;
    sceVu0SubVector(buf, a2, a1);
    ang = FSqrt(buf[0] * buf[0] + buf[1] * buf[1] + buf[2] * buf[2]);
    if (ang < a3) {
        a0[0] = a2[0];
        a0[1] = a2[1];
        a0[2] = a2[2];
    } else {
        _InterGV(a0, a1, a2, a3, ang - a3);
    }
    return ang;
}

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", _RotyGV);

extern int _RotyGV(void *a0, void *a1);

int func_00194590(void *a0, void *a1)
{
    int d = _RotyGV(a0, a1);

    return (d < 0) ? -d : d;
}

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", func_001945B8);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", _GetDirection);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", _RotGV);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", _RotGVF);

void _OrientXZGV(int a0)
{
    int buf[4];
    sceVu0SubVector(buf);
    buf[1] = 0;
    sceVu0Normalize(a0, buf);
}

void func_00194808(int a0)
{
    int buf[4];
    sceVu0SubVector(buf);
    sceVu0Normalize(a0, buf);
}

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", func_00194840);

void SwapGV(float *a, float *b)
{
    float tmp[3];
    tmp[0] = a[0];
    tmp[1] = a[1];
    tmp[2] = a[2];
    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
    b[0] = tmp[0];
    b[1] = tmp[1];
    b[2] = tmp[2];
}

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", GetCorrectDistance);

int RoundDegGV(int a0)
{
    if (a0 > 0) {
        a0 = a0 % 360;
    } else {
        int a = a0 < 0 ? -a0 : a0;
        a0 = (a / 360 + 1) * 360 + a0;
    }
    return (a0 < 181) ? a0 : a0 - 360;
}

