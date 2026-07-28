#include "common.h"


extern void func_00243978();
extern void func_00243AE8();
INCLUDE_ASM("asm/nonmatchings/src/hand-camera", RotateAccordingToStick_PatternThree);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", HandyCamera_TargetMoveType);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", ClearHandCameraCorrect);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", InitHandCameraCorrect);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", SetLimitHandCameraCorrect);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", HandCameraCorrect);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", func_00194590);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", func_001945B8);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", func_00194630);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", func_00194678);

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", func_00194718);

void func_001947D0(int a0)
{
    int buf[4];
    func_00243AE8(buf);
    buf[1] = 0;
    func_00243978(a0, buf);
}

void func_00194808(int a0)
{
    int buf[4];
    func_00243AE8(buf);
    func_00243978(a0, buf);
}

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", func_00194840);

void func_001948A8(float *a, float *b)
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
    __asm__ __volatile__("" : : "r"(tmp) : "memory");
}

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", func_001948F0);

int func_00194960(int a0)
{
    if (a0 > 0) {
        a0 = a0 % 360;
    } else {
        int a = a0 < 0 ? -a0 : a0;
        a0 = (a / 360 + 1) * 360 + a0;
    }
    return (a0 < 181) ? a0 : a0 - 360;
}

