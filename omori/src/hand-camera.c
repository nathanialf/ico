#include "common.h"

extern void func_00240008();
extern float func_0023FE70(void *a0, void *a1);

void RotateAccordingToStick_PatternThree(void *a0, void *a1) {
    char buf[0x10];
    func_00240008(buf, a0, a1);
    *(int *)(buf + 4) = 0;
    func_0023FE70(buf, buf);
}


void HandyCamera_TargetMoveType(void *a0, void *a1) {
    char buf[0x10];
    func_00240008(buf, a0, a1);
    func_0023FE70(buf, buf);
}

extern void MatrixDrive_GetTurnYAngleXZ(float a0);

void ClearHandCameraCorrect(void *a0, void *a1) {
    char buf[0x10];
    func_00240008(buf, a0, a1);
    MatrixDrive_GetTurnYAngleXZ(func_0023FE70(buf, buf));
}

void InitHandCameraCorrect(void *a0, void *a1) {
    char buf[0x10];
    func_00240008(buf, a0, a1);
    *(int *)(buf + 4) = 0;
    MatrixDrive_GetTurnYAngleXZ(func_0023FE70(buf, buf));
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", SetLimitHandCameraCorrect);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", HandCameraCorrect);

extern int HandCameraCorrect();

int func_00191D90(void) {
    int r = HandCameraCorrect();
    return r < 0 ? -r : r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_00191DB8);

extern float func_0025A968(float a0, float a1);
extern void func_0023FE98(int a0, int *buf);

float func_00191E30(float *a0)
{
    float buf[4];
    buf[1] = 0;
    buf[0] = a0[0];
    buf[2] = a0[2];
    func_0023FE98((int)buf, (int *)buf);
    return func_0025A968(buf[0], buf[2]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_00191E78);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/hand-camera", func_00191F18);

extern void func_0023FE98(int a0, int *buf);

void func_00191FD0(int a0)
{
    int buf[4];
    func_00240008(buf);
    buf[1] = 0;
    func_0023FE98(a0, buf);
}


void func_00192008(void *a0, void *a1, void *a2) {
    char buf[0x10];
    func_00240008(buf, a1, a2);
    func_0023FE98(a0, buf);
}

int func_00192040(int a0, int a1, int a2, int a3)
{
    int *p;
    int buf[8];
    register int sa2 = a2;
    register int sa3 = a3;
    int r;
    p = &buf[4];
    func_00240008(p, a0, a1);
    p = &buf[0];
    buf[5] = 0;
    func_0023FE98(p, &buf[4]);
    r = HandCameraCorrect(p, sa2);
    return __builtin_abs(r) < sa3;
}

void func_001920A8(float *a, float *b)
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

extern float func_0010ED30(int x);
extern unsigned int D_006327B0_far[] __asm__("D_0062C908");

float func_001920F0(int a0, float a1)
{
    float r = func_0010ED30((short)((a0 << 15) / 0xB4));
    if (r == 0.0f)
        return *(float *)D_006327B0_far;
    return a1 / r;
}

int func_00192160(int a0)
{
    if (a0 > 0) {
        a0 = a0 % 360;
    } else {
        int a = a0 < 0 ? -a0 : a0;
        a0 = (a / 360 + 1) * 360 + a0;
    }
    return (a0 < 181) ? a0 : a0 - 360;
}
