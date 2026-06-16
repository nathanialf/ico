#include "common.h"

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
void actSt06aInit(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x3000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x3000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xFB);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0x131, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0x131, 0x1E, 0) == 0) { _ACTWait(1); }
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
void actSt06aSuimon(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x4000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x4000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xFC);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0x132, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0x132, 0x1E, 0) == 0) { _ACTWait(1); }
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
void actSt06aSuimonChk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x5000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x5000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xFD);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0x133, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0x133, 0x1E, 0) == 0) { _ACTWait(1); }
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
void actSt06aDoor(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x6000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x6000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xFE);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0x134, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0x134, 0x1E, 0) == 0) { _ACTWait(1); }
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
void actSt06aDoorUpChk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x7000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x7000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xFF);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0x135, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0x135, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aDoorDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aShutterOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aBoxChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aStatueChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aHeadChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aShutter);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aExit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aBox);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aBox2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aBox3);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aBoxEvent2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aWay);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aWallWay);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aWallWay2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aStatue);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aHead);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st06a", actSt06aTree);
