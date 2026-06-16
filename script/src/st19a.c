#include "common.h"

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int D_00629E14;
extern int actSt25aQueenDeadChk(int a0);
extern void gflagOff(int a0, int a1);

void actSt19aOriDown(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (D_00629E14 == 0x2E) {
        gflagOff(actSt25aQueenDeadChk(0x8B7), 0x2FD);
        *(int *)(actSt25aQueenDeadChk(0x8B7) + 0x16C) = 1;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aHaguruma);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aHagurumaChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aPipeChk);

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void gflagInit(int a0);
void actSt19aChainDown(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
stage_KillPlayBgAnimation(0x1F,0,-1); stage_KillPlayBgAnimation(0x19,0,0); stage_KillPlayBgAnimation(0x22,0,0); stage_KillPlayBgAnimation(0x23,0,0); stage_KillPlayBgAnimation(0x25,0,0); }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aChainUp);

void actSt19aOri(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aOriXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aPipe);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aPipeXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aChain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19bIntro);

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern int D_00629DE4;
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
void actSt19aOriMain(volatile int a0) {
    while (scpSleepEnemyOne(a0, D_00629DE4, 400.0f) == 0 ||
           func_00178DB0(0x127) != 0) {
        _ACTWait(1);
    }
    actSt25aQueenDead(3, D_00629DE4, 0, 2.0f, 4.0f);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aOriSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aOriUp);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aChainMain);

extern void Generator_Mask(int a0);
extern void Generator_ResetCount(int a0);

void actSt19aChainSwitch(volatile int a0) {
    Generator_Mask(a0);
    Generator_ResetCount(a0);
}

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void actSt19bIntroChk(void) {
    if (func_00178DB0(0x14)) {
        AddWayPointTop(9, 0);
    }
}

extern void func_00178DD8(int a0);
extern void func_00178E08(int a0);

void func_0022E2E8(void) {
    if (func_00178DB0(0x1D) == 0) {
        func_00178DD8(0x164);
    } else {
        func_00178E08(0x164);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", func_0022E318);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", func_0022E438);
