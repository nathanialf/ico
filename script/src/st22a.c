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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230C10);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230C70);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230E00);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230EC8);

void func_00230F70(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230F80);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230FD8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_002310B8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00231188);

void func_00231258(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00231260);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_002313B0);
