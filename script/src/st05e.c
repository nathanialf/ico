#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", actSt05eSolarChk);

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05eWater(void) {
    if (func_00178DB0(0xCE) == 0) {
        AddWayPointTop(5, 0);
    } else {
        AddWayPointTop(5, 1);
    }
    if (func_00178DB0(0xEA) == 0) {
        stage_KillPlayBgAnimation(0x126, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x126, 0, -1);
    }
    if (func_00178DB0(0xEB) == 0) {
        stage_KillPlayBgAnimation(0x127, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x127, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", actSt05eSolar);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", actSt05eWaterMain);

#include "common.h"
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BD14;
extern int D_0062A894;
void actSt05eWaterSwitch(volatile int a0) {
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_00178DD8(0xE3);
    _ACTWait(0x3C);
    scpPlayStart(0x50, (int)&D_0062BD14, 1, 1, 1);
    while (D_0062BD14 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x11D, 1, 0);
    while (func_0012A958(0x11D) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x562) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x563) + 0x16C) = 1;
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", actSt05eWaterStop);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", actSt05eWaterFlagOn);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021D370);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021D668);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021D850);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021D9C0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021DAF8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021DDC8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E080);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E1C0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E300);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E430);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E570);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E6B0);

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpActivateAllWithKind(void);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_0062A894;
void func_0021E7E0(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x1000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x1000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xF9);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0x12F, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0x12F, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpActivateAllWithKind(void);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_0062A894;
void func_0021E8D8(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x2000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xFA);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0x130, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0x130, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
}
