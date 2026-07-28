#include "common.h"

typedef struct ActB4Obj {
    char pad[0xC4];
    int *unkC4;
} ActB4Obj;

extern void _ACTWait(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_00631AE4;
extern int D_00631AE8;
extern int D_006325B4;
extern int ACTEnvGetTest(void);
extern void BoySekikaTexScroll(int a0, int a1);
extern void GetTarget(void);
extern void func_0017B528(int a0);
extern void func_0017B568(int a0);
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);

void actSt06aInit(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00631AE4, 0x3000000) == 0 ||
           scpSleepSpiderGroupOne(D_00631AE8, 0x3000000) == 0) {
        _ACTWait(1);
    }
    D_006325B4 = 1;
    func_0017B258(0xFB);
    scpDispOnAllWithKind();
    if (ACTEnvGetTest() != 0) {
        func_0017B528(D_00631AE4);
        func_0017B528(D_00631AE8);
        BoySekikaTexScroll(D_00631AE4, 1);
        BoySekikaTexScroll(D_00631AE8, 1);
        _ACTWait(1);
        GetTarget();
    }
    stage_KillPlayBgAnimation(0x132, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AB50(0x132, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    func_0017B568(D_00631AE4);
    func_0017B568(D_00631AE8);
    _ACTWait(1);
    if (ACTEnvGetTest() != 0) {
        iosOmBeforeFuncStandard(D_00631AE8, 0x3C, D_00631AE4);
    }
    D_006325B4 = 0;
}

extern void _ACTWait(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_00631AE4;
extern int D_00631AE8;
extern int D_006325B4;
extern int ACTEnvGetTest(void);
extern void BoySekikaTexScroll(int a0, int a1);
extern void GetTarget(void);
extern void func_0017B528(int a0);
extern void func_0017B568(int a0);
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);

void actSt06aSuimon(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00631AE4, 0x4000000) == 0 ||
           scpSleepSpiderGroupOne(D_00631AE8, 0x4000000) == 0) {
        _ACTWait(1);
    }
    D_006325B4 = 1;
    func_0017B258(0xFC);
    scpDispOnAllWithKind();
    if (ACTEnvGetTest() != 0) {
        func_0017B528(D_00631AE4);
        func_0017B528(D_00631AE8);
        BoySekikaTexScroll(D_00631AE4, 1);
        BoySekikaTexScroll(D_00631AE8, 1);
        _ACTWait(1);
        GetTarget();
    }
    stage_KillPlayBgAnimation(0x133, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AB50(0x133, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    func_0017B568(D_00631AE4);
    func_0017B568(D_00631AE8);
    _ACTWait(1);
    if (ACTEnvGetTest() != 0) {
        iosOmBeforeFuncStandard(D_00631AE8, 0x3C, D_00631AE4);
    }
    D_006325B4 = 0;
}

extern void _ACTWait(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_00631AE4;
extern int D_00631AE8;
extern int D_006325B4;
extern int ACTEnvGetTest(void);
extern void BoySekikaTexScroll(int a0, int a1);
extern void GetTarget(void);
extern void func_0017B528(int a0);
extern void func_0017B568(int a0);
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);

void actSt06aSuimonChk(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00631AE4, 0x5000000) == 0 ||
           scpSleepSpiderGroupOne(D_00631AE8, 0x5000000) == 0) {
        _ACTWait(1);
    }
    D_006325B4 = 1;
    func_0017B258(0xFD);
    scpDispOnAllWithKind();
    if (ACTEnvGetTest() != 0) {
        func_0017B528(D_00631AE4);
        func_0017B528(D_00631AE8);
        BoySekikaTexScroll(D_00631AE4, 1);
        BoySekikaTexScroll(D_00631AE8, 1);
        _ACTWait(1);
        GetTarget();
    }
    stage_KillPlayBgAnimation(0x134, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AB50(0x134, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    func_0017B568(D_00631AE4);
    func_0017B568(D_00631AE8);
    _ACTWait(1);
    if (ACTEnvGetTest() != 0) {
        iosOmBeforeFuncStandard(D_00631AE8, 0x3C, D_00631AE4);
    }
    D_006325B4 = 0;
}

extern void _ACTWait(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_00631AE4;
extern int D_00631AE8;
extern int D_006325B4;
extern int ACTEnvGetTest(void);
extern void BoySekikaTexScroll(int a0, int a1);
extern void GetTarget(void);
extern void func_0017B528(int a0);
extern void func_0017B568(int a0);
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);

void actSt06aDoor(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00631AE4, 0x6000000) == 0 ||
           scpSleepSpiderGroupOne(D_00631AE8, 0x6000000) == 0) {
        _ACTWait(1);
    }
    D_006325B4 = 1;
    func_0017B258(0xFE);
    scpDispOnAllWithKind();
    if (ACTEnvGetTest() != 0) {
        func_0017B528(D_00631AE4);
        func_0017B528(D_00631AE8);
        BoySekikaTexScroll(D_00631AE4, 1);
        BoySekikaTexScroll(D_00631AE8, 1);
        _ACTWait(1);
        GetTarget();
    }
    stage_KillPlayBgAnimation(0x135, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AB50(0x135, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    func_0017B568(D_00631AE4);
    func_0017B568(D_00631AE8);
    _ACTWait(1);
    if (ACTEnvGetTest() != 0) {
        iosOmBeforeFuncStandard(D_00631AE8, 0x3C, D_00631AE4);
    }
    D_006325B4 = 0;
}

extern void _ACTWait(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_00631AE4;
extern int D_00631AE8;
extern int D_006325B4;
extern int ACTEnvGetTest(void);
extern void BoySekikaTexScroll(int a0, int a1);
extern void GetTarget(void);
extern void func_0017B528(int a0);
extern void func_0017B568(int a0);
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);

void actSt06aDoorUpChk(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00631AE4, 0x7000000) == 0 ||
           scpSleepSpiderGroupOne(D_00631AE8, 0x7000000) == 0) {
        _ACTWait(1);
    }
    D_006325B4 = 1;
    func_0017B258(0xFF);
    scpDispOnAllWithKind();
    if (ACTEnvGetTest() != 0) {
        func_0017B528(D_00631AE4);
        func_0017B528(D_00631AE8);
        BoySekikaTexScroll(D_00631AE4, 1);
        BoySekikaTexScroll(D_00631AE8, 1);
        _ACTWait(1);
        GetTarget();
    }
    stage_KillPlayBgAnimation(0x136, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AB50(0x136, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    func_0017B568(D_00631AE4);
    func_0017B568(D_00631AE8);
    _ACTWait(1);
    if (ACTEnvGetTest() != 0) {
        iosOmBeforeFuncStandard(D_00631AE8, 0x3C, D_00631AE4);
    }
    D_006325B4 = 0;
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D2290[];
extern volatile float D_006315E4;
extern volatile float D_006315E8;
extern int D_00631AE4;
extern int D_006325B4;
extern void _ACTWait(int a0);
extern void actSt08bDoorUpChk(void);
extern int func_0012AA80(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern int func_0017B230(int a0);
extern void func_0017B258(int a0);
extern void func_0017B288(int a0);
extern void func_0017E870(float a0, float a1, float a2, float a3);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt06aDoorDownChk(int a0) {
    volatile int buf[4];
    ActB4Obj *s;
    buf[0] = a0;
    s = (ActB4Obj *)*(int *)(buf[0] + 0x164);
    while (scpSleepSpiderGroupOne(D_00631AE4, 0xA000000) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    _ACTWait(0xF);
    if (func_0017B230(0x101) != 0) {
        stage_KillPlayBgAnimation(0xC9, 1, 0xC8);
        func_0017E870(D_006315E4, -150.0f, -1600.0f, 200.0f);
        while (func_0012AB50(0xC9, 0xDC, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x511, 0, 0, 1);
        while (func_0012AB50(0xC9, 0xF0, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x512, 0, 0, 1);
        while (func_0012AB50(0xC9, 0xFA, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x50F, 0, 0, 1);
        while (func_0012AB50(0xC9, 0x19F, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x510, 0, 0, 1);
        while (func_0012AA80(0xC9) == 0) { _ACTWait(1); }
        _ACTWait(1);
        func_0017B288(0x101);
        D_006325B4 = 0;
    } else {
        stage_KillPlayBgAnimation(0xC9, 1, 0);
        func_0017E870(D_006315E8, -1200.0f, -1600.0f, 200.0f);
        soundSeDefPlayWithVolumeRate(0x50F, 0, 0, 1);
        while (func_0012AB50(0xC9, 0x91, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x510, 0, 0, 1);
        soundSeDefPlayWithVolumeRate(0x511, 0, 0, 1);
        while (func_0012AB50(0xC9, 0xAA, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        soundSeDefPlayWithVolumeRate(0x512, 0, 0, 1);
        while (func_0012AB50(0xC9, 0xC8, 1) == 0) { _ACTWait(1); }
        _ACTWait(1);
        func_0017B258(0x101);
        D_006325B4 = 0;
    }
    lt_fade_status(0x32);
    scpActivateAllWithKind();
    D_004D2290[1] = (int)actSt08bDoorUpChk;
    s->unkC4 = D_004D2290;
    BoxBarSoundOn(buf[0], 0x18D);
    _ACTWait(0);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1FF0[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt08aEnemy1(void);
extern int func_0017B230(int a0);

void actSt06aShutterOpen(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xD1) == 0) {
        D_004D1FF0[1] = (int)actSt08aEnemy1;
        gobj->unkC4 = D_004D1FF0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D1F70[];
extern int D_006325B4;
extern void actSt05eWaterFlagOn(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt06aBoxChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xDA) == 0) {
        stage_KillPlayBgAnimation(0x114, 0, 0);
        D_004D1F70[1] = (int)actSt05eWaterFlagOn;
        gobj->unkC4 = D_004D1F70;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x114, 0, -1);
        D_006325B4 = 0;
    }
}

extern int D_004D1FB0[];
extern void func_00220670(void);

void actSt06aStatueChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xDC) == 0) {
        stage_KillPlayBgAnimation(0x118, 0, 0);
        D_004D1FB0[1] = (int)func_00220670;
        gobj->unkC4 = D_004D1FB0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x118, 0, -1);
        D_006325B4 = 0;
    }
}

extern int D_004D1E70[];
extern void actSt08aDoor(void);
extern int actSt25aQueenDeadChk(int a0);

void actSt06aHeadChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xE1) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x518) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x519) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x11C, 0, 0);
        D_004D1E70[1] = (int)actSt08aDoor;
        gobj->unkC4 = D_004D1E70;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x11C, 0, -1);
    }
}

extern int D_004D1ED0[];
extern void actSt08aEne1(void);

void actSt06aShutter(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xE2) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x566) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x567) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x11D, 0, 0);
        D_004D1ED0[1] = (int)actSt08aEne1;
        gobj->unkC4 = D_004D1ED0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x11D, 0, -1);
    }
}

extern int D_004D1F30[];
extern void actSt08aEne2(void);

void actSt06aExit(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xE3) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x568) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x569) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x11E, 0, 0);
        D_004D1F30[1] = (int)actSt08aEne2;
        gobj->unkC4 = D_004D1F30;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x11E, 0, -1);
    }
}

extern int D_004D2010[];
extern int D_00631AE8;
extern int actSt25aQueenDeadChk(int a0);
extern void func_00220B00(void);

void actSt06aBox(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xE4) == 0) {
        if (D_00631AE8 != 0) {
            D_004D2010[1] = (int)func_00220B00;
            gobj->unkC4 = D_004D2010;
            BoxBarSoundOn(a0, 0x18D);
            _ACTWait(0);
        }
    } else {
        *(int *)(actSt25aQueenDeadChk(0x58C) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x13E, -1, -2);
    }
}

extern int D_004D2090[];
extern void func_00221340(void);

void actSt06aBox2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xEA) == 0) {
        D_004D2090[1] = (int)func_00221340;
        gobj->unkC4 = D_004D2090;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D20F0[];
extern void func_002216F0(void);

void actSt06aBox3(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xEB) == 0) {
        D_004D20F0[1] = (int)func_002216F0;
        gobj->unkC4 = D_004D20F0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D2110[];
extern void actSt08aIntroChk(void);

void actSt06aBoxEvent2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xEA) == 0) {
        D_004D2110[1] = (int)actSt08aIntroChk;
        gobj->unkC4 = D_004D2110;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D2130[];
extern void func_00223E98(void);

void actSt06aWay(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xEB) == 0) {
        D_004D2130[1] = (int)func_00223E98;
        gobj->unkC4 = D_004D2130;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D2050[];
extern void func_002210C0(void);

void actSt06aWallWay(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xEC) == 0) {
        stage_KillPlayBgAnimation(0x11F, 0, 0);
        D_004D2050[1] = (int)func_002210C0;
        gobj->unkC4 = D_004D2050;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x11F, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x54B) + 0x16C) = 0;
    }
}

extern int D_004D2070[];
extern void func_00221200(void);

void actSt06aWallWay2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xED) == 0) {
        stage_KillPlayBgAnimation(0x120, 0, 0);
        D_004D2070[1] = (int)func_00221200;
        gobj->unkC4 = D_004D2070;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x120, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x54C) + 0x16C) = 0;
    }
}

extern int D_004D20B0[];
extern void func_00221470(void);

void actSt06aStatue(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xEE) == 0) {
        stage_KillPlayBgAnimation(0x121, 0, 0);
        D_004D20B0[1] = (int)func_00221470;
        gobj->unkC4 = D_004D20B0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x121, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x54D) + 0x16C) = 0;
    }
}

extern int D_004D20D0[];
extern void func_002215B0(void);

void actSt06aHead(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xEF) == 0) {
        stage_KillPlayBgAnimation(0x122, 0, 0);
        D_004D20D0[1] = (int)func_002215B0;
        gobj->unkC4 = D_004D20D0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x122, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x54E) + 0x16C) = 0;
    }
}

extern int D_004D2030[];
extern void func_00220DD0(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt06aTree(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xE5) == 0) {
        stage_KillPlayBgAnimation(0x12A, 0, 0);
        D_004D2030[1] = (int)func_00220DD0;
        gobj->unkC4 = D_004D2030;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x12A, 0, -1);
    }
}

