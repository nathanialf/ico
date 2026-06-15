#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aEnd);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt07aChanChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDA) == 0) {
        stage_KillPlayBgAnimation(0x118, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x118, 0, -1);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt07aChanEffect(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDB) == 0) {
        stage_KillPlayBgAnimation(0x119, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x119, 0, -1);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt07aTsuroChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDC) == 0) {
        stage_KillPlayBgAnimation(0x11A, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x11A, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aTsuroEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aSekizoChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aEneChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aChan);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aTsuro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aIntro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aGene1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aGene2);

void actSt07aGene3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF7)) {
        gflagInit(0x5AD);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void gflagInit(int a0);

void actSt07aEne2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF8)) {
        gflagInit(0x5AE);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aGene2_1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aGene2_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07aGene2_3);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st07a", actSt07ChanEvent);
