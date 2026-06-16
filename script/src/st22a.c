#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", actSt22aLightningVolime);

void actSt22aIntro(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt22aIntroChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", actSt22aIntroSub);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230A78);

extern void *D_00629DE4;
extern int D_0062C2C4;
extern void func_001790A8(void *a0);
extern void gflagOff(void *a0, int a1);
extern void actSt25aQueenBefore(void *a0);
extern void _ACTWait(int a0);

void func_00230B20(int a0) {
    int buf[4];
    buf[0] = a0;
    func_001790A8(D_00629DE4);
    gflagOff(D_00629DE4, 0x133);
    actSt25aQueenBefore(D_00629DE4);
    _ACTWait(0xF0);
    D_0062C2C4 = 1;
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230B70);

void func_00230BF0(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00230C00(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern int actInitialize(int a0);
extern int func_00178DB0(int a0);
extern void actCreateSubThread(void *entry, int a1);
extern void func_00230C70(int a0);

void func_00230C10(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0x1D) == 0) {
        _ACTWait(1);
    }
    actCreateSubThread(func_00230C70, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230C70);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230E00);

extern void *D_00629DE8;
extern int D_0062A894;
extern void func_00178DD8(int a0);

void func_00230EC8(int a0) {
    volatile int x;
    x = a0;
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (*(int *)((char *)*(void **)((char *)D_00629DE8 + 0x164) + 0x30) != 0x6A) {
        _ACTWait(1);
    }
    func_00178DD8(0x1B);
    D_0062A894 = 1;
    _ACTWait(0xC8);
    func_001790A8(D_00629DE8);
    gflagOff(D_00629DE8, 0x229);
    _ACTWait(0x78);
    func_00178DD8(0x1C);
}

void func_00230F70(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void *D_00629DE4;
extern int GetSkeltonFocusNode(void *a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_00230F80(int a0) {
    volatile int x;
    x = a0;
    while (GetSkeltonFocusNode(D_00629DE4) != 0xE3) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x3F, -1, -2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230FD8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_002310B8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00231188);

void func_00231258(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00231260);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_002313B0);
