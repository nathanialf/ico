#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", actSt17bTest);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", actSt17bCheck);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", actSt17bIntro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", actSt17bCheckChk);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
extern float D_00629940;
extern float D_00629944;

void actSt17bIntroChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x115, 0x161, 0, 0x12, 0.0f, D_00629940, D_00629944, -75.0f, D_00629940, D_00629944);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022B150);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022B1C8);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);

void func_0022B270(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_00178DB0(0x117) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022B2E0);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);

void func_0022B360(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDA) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x5CF) + 0x16C) = 0;
    } else {
        *(int *)(actSt25aQueenDeadChk(0x5CE) + 0x16C) = 0;
    }
}

extern void actSt25aQueenTalkChk(int a0, int a1, int *buf, int a3, float f);
extern void _ACTWait(int x);
extern int D_00629DE8;
extern long long D_00614BD0[];

void func_0022B3B0(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_00614BD0[0];
    buf[1] = D_00614BD0[1];
    actSt25aQueenTalkChk(D_00629DE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022B408);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022B4D8);

void func_0022B568(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022B578);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022B5F0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022B790);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022B8E8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022BAE8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022BB88);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022BC58);
