#include "common.h"


extern void func_00243978();
extern void func_00243AE8();
extern float func_00243950(void *a0, void *a1);

void RotateAccordingToStick_PatternThree(void *a0, void *a1) {
    char buf[0x10];
    func_00243AE8(buf, a0, a1);
    *(int *)(buf + 4) = 0;
    func_00243950(buf, buf);
}

void HandyCamera_TargetMoveType(void *a0, void *a1) {
    char buf[0x10];
    func_00243AE8(buf, a0, a1);
    func_00243950(buf, buf);
}

extern float MatrixDrive_GetTurnYAngleXZ(float a0);

void ClearHandCameraCorrect(void *a0, void *a1) {
    char buf[0x10];
    func_00243AE8(buf, a0, a1);
    MatrixDrive_GetTurnYAngleXZ(func_00243950(buf, buf));
}

void InitHandCameraCorrect(void *a0, void *a1) {
    char buf[0x10];
    func_00243AE8(buf, a0, a1);
    *(int *)(buf + 4) = 0;
    MatrixDrive_GetTurnYAngleXZ(func_00243950(buf, buf));
}

extern void _OrientXZGV(float *a0, float *a1, float *a2, float a3, float a4);

float SetLimitHandCameraCorrect(float *a0, float *a1, float *a2, float a3)
{
    float buf[4];
    float ang;
    func_00243AE8(buf, a2, a1);
    ang = MatrixDrive_GetTurnYAngleXZ(buf[0] * buf[0] + buf[1] * buf[1] + buf[2] * buf[2]);
    if (ang < a3) {
        a0[0] = a2[0];
        a0[1] = a2[1];
        a0[2] = a2[2];
    } else {
        _OrientXZGV(a0, a1, a2, a3, ang - a3);
    }
    return ang;
}

INCLUDE_ASM("asm/nonmatchings/src/hand-camera", HandCameraCorrect);

extern int HandCameraCorrect(void *a0, void *a1);

int func_00194590(void *a0, void *a1)
{
    int d = HandCameraCorrect(a0, a1);

    return (d < 0) ? -d : d;
}

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

