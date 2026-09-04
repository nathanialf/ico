#include "common.h"

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
extern int actInitialize(int a0);
extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);

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

extern void lt_fade_status(int a0);
extern void scpWakeupItemWithBoundary(float a0, float a1, float a2, float a3);
extern int func_0012A958(int a0);
extern void func_00178E08(int a0);
extern volatile float D_006298D0;
extern volatile float D_006298D4;
extern int D_004CCEA0[];
extern void actSt08bDoorUpChk(void);

void actSt06aDoorDownChk(int a0) {
    volatile int buf[4];
    ActB4Obj *s;
    buf[0] = a0;
    s = (ActB4Obj *)*(int *)(buf[0] + 0x164);
    while (scpSleepSpiderGroupOne(D_00629DE4, 0xA000000) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    _ACTWait(0xF);
    if (func_00178DB0(0x101) != 0) {
        stage_KillPlayBgAnimation(0xC8, 1, 0xC8);
        scpWakeupItemWithBoundary(D_006298D0, -150.0f, -1600.0f, 200.0f);
        while (func_0012AA28(0xC8, 0xDC, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x511, 0, 0, 1);
        while (func_0012AA28(0xC8, 0xF0, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x512, 0, 0, 1);
        while (func_0012AA28(0xC8, 0xFA, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x50F, 0, 0, 1);
        while (func_0012AA28(0xC8, 0x19F, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x510, 0, 0, 1);
        while (func_0012A958(0xC8) == 0) { _ACTWait(1); }
        _ACTWait(1);
        func_00178E08(0x101);
        D_0062A894 = 0;
    } else {
        stage_KillPlayBgAnimation(0xC8, 1, 0);
        scpWakeupItemWithBoundary(D_006298D4, -1200.0f, -1600.0f, 200.0f);
        soundSeDefPlayWithVolumeRate(0x50F, 0, 0, 1);
        while (func_0012AA28(0xC8, 0x91, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x510, 0, 0, 1);
        soundSeDefPlayWithVolumeRate(0x511, 0, 0, 1);
        while (func_0012AA28(0xC8, 0xAA, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x512, 0, 0, 1);
        while (func_0012AA28(0xC8, 0xC8, 1) == 0) { _ACTWait(1); }
        _ACTWait(1);
        func_00178DD8(0x101);
        D_0062A894 = 0;
    }
    lt_fade_status(0x32);
    scpActivateAllWithKind();
    D_004CCEA0[1] = (int)actSt08bDoorUpChk;
    s->unkB4 = D_004CCEA0;
    BoxBarSoundOn(buf[0], 0x189);
    _ACTWait(0);
}


extern int D_004CCC00[];
extern void actSt08aEnemy1(void);

void actSt06aShutterOpen(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xD1) == 0) {
        D_004CCC00[1] = (int)actSt08aEnemy1;
        gobj->unkB4 = D_004CCC00;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CCB80[];
extern void actSt05eWaterFlagOn(void);

void actSt06aBoxChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDA) == 0) {
        stage_KillPlayBgAnimation(0x113, 0, 0);
        D_004CCB80[1] = (int)actSt05eWaterFlagOn;
        gobj->unkB4 = D_004CCB80;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x113, 0, -1);
        D_0062A894 = 0;
    }
}


extern int D_004CCBC0[];
extern void func_0021D668(void);

void actSt06aStatueChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDC) == 0) {
        stage_KillPlayBgAnimation(0x117, 0, 0);
        D_004CCBC0[1] = (int)func_0021D668;
        gobj->unkB4 = D_004CCBC0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x117, 0, -1);
        D_0062A894 = 0;
    }
}


extern int actSt25aQueenDeadChk(int a0);
extern int D_004CCA80[];
extern void actSt08aDoor(void);

void actSt06aHeadChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xE1) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x514) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x515) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x11B, 0, 0);
        D_004CCA80[1] = (int)actSt08aDoor;
        gobj->unkB4 = D_004CCA80;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x11B, 0, -1);
    }
}


extern int actSt25aQueenDeadChk(int a0);
extern int D_004CCAE0[];
extern void actSt08aEne1(void);

void actSt06aShutter(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xE2) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x560) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x561) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x11C, 0, 0);
        D_004CCAE0[1] = (int)actSt08aEne1;
        gobj->unkB4 = D_004CCAE0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x11C, 0, -1);
    }
}


extern int actSt25aQueenDeadChk(int a0);
extern int D_004CCB40[];
extern void actSt08aEne2(void);

void actSt06aExit(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xE3) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x562) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x563) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x11D, 0, 0);
        D_004CCB40[1] = (int)actSt08aEne2;
        gobj->unkB4 = D_004CCB40;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x11D, 0, -1);
    }
}


extern int actSt25aQueenDeadChk(int a0);
extern int D_004CCC20[];
extern void func_0021DAF8(void);

void actSt06aBox(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xE4) == 0) {
        if (D_00629DE8 != 0) {
            D_004CCC20[1] = (int)func_0021DAF8;
            gobj->unkB4 = D_004CCC20;
            BoxBarSoundOn(a0, 0x189);
            _ACTWait(0);
        }
    } else {
        *(int *)(actSt25aQueenDeadChk(0x586) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x13D, -1, -2);
    }
}


extern int D_004CCCA0[];
extern void func_0021E300(void);

void actSt06aBox2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xEA) == 0) {
        D_004CCCA0[1] = (int)func_0021E300;
        gobj->unkB4 = D_004CCCA0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CCD00[];
extern void func_0021E6B0(void);

void actSt06aBox3(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xEB) == 0) {
        D_004CCD00[1] = (int)func_0021E6B0;
        gobj->unkB4 = D_004CCD00;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CCD20[];
extern void actSt08aIntroChk(void);

void actSt06aBoxEvent2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xEA) == 0) {
        D_004CCD20[1] = (int)actSt08aIntroChk;
        gobj->unkB4 = D_004CCD20;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}

extern int D_004CCD40[];
extern void func_00220BD0(void);

void actSt06aWay(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xEB) == 0) {
        D_004CCD40[1] = (int)func_00220BD0;
        gobj->unkB4 = D_004CCD40;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}

extern int actSt25aQueenDeadChk(int a0);
extern int D_004CCC60[];
extern void func_0021E080(void);

void actSt06aWallWay(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xEC) == 0) {
        stage_KillPlayBgAnimation(0x11E, 0, 0);
        D_004CCC60[1] = (int)func_0021E080;
        gobj->unkB4 = D_004CCC60;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x11E, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x547) + 0x16C) = 0;
    }
}


extern int actSt25aQueenDeadChk(int a0);
extern int D_004CCC80[];
extern void func_0021E1C0(void);

void actSt06aWallWay2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xED) == 0) {
        stage_KillPlayBgAnimation(0x11F, 0, 0);
        D_004CCC80[1] = (int)func_0021E1C0;
        gobj->unkB4 = D_004CCC80;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x11F, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x548) + 0x16C) = 0;
    }
}


extern int actSt25aQueenDeadChk(int a0);
extern int D_004CCCC0[];
extern void func_0021E430(void);

void actSt06aStatue(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xEE) == 0) {
        stage_KillPlayBgAnimation(0x120, 0, 0);
        D_004CCCC0[1] = (int)func_0021E430;
        gobj->unkB4 = D_004CCCC0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x120, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x549) + 0x16C) = 0;
    }
}


extern int actSt25aQueenDeadChk(int a0);
extern int D_004CCCE0[];
extern void func_0021E570(void);

void actSt06aHead(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xEF) == 0) {
        stage_KillPlayBgAnimation(0x121, 0, 0);
        D_004CCCE0[1] = (int)func_0021E570;
        gobj->unkB4 = D_004CCCE0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x121, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x54A) + 0x16C) = 0;
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CCC40[];
extern void func_0021DDC8(void);

void actSt06aTree(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xE5) == 0) {
        stage_KillPlayBgAnimation(0x129, 0, 0);
        D_004CCC40[1] = (int)func_0021DDC8;
        gobj->unkB4 = D_004CCC40;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x129, 0, -1);
    }
}

