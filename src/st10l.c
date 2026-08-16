#include "common.h"

typedef struct { char pad[0xC0]; int *unkB0; } ActB0Obj;
typedef struct ActB4Obj { char pad[0xC4]; int *unkC4; } ActB4Obj;

extern long long D_0061BE50[];
extern long long D_0061BE60[];
extern void _ACTWait(int a0);
extern void scpDispOffAllWithKind(int *buf, int a1);

void actSt10lInit(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061BE50[0]; long long v0b=D_0061BE60[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BE50[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BE60[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }


void actSt10lFloorLeft(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061BE60[0]; long long v0b=D_0061BE50[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BE60[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BE50[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern int D_00631AE8;
extern int func_0017B230(int a0);
extern void func_0017B258(int a0);

void actSt10lFloorRight(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (D_00631AE8 == 0 || func_0017B230(0x98) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_0017B258(0x99);
    func_0017B258(0x9A);
}

extern int D_006325B4;
extern int D_00633A44;
extern int _SCPBoySupportGirl(int a0, int a1, int a2);
extern int actSt25aQueenDeadChk(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B288(int a0);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void scpTrans(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt10lGondolaUp(volatile int a0) {
    while (_SCPBoySupportGirl(0x5AC, 0x109, 0x113) == 0) { _ACTWait(1); }
    *(int *)(actSt25aQueenDeadChk(0x5AC) + 0x16C) = 0;
    *(int *)(actSt25aQueenDeadChk(0x5AD) + 0x16C) = 1;
    if (func_0017B230(0xDA) == 0 || func_0017B230(0xDB) == 0 ||
        func_0017B230(0xDC) == 0) {
        lt_fade_status(0x33);
        D_006325B4 = 1;
        scpDispOnAllWithKind();
        scpPlayStart(0x34, (int)&D_00633A44, 1, 1, 1);
        stage_KillPlayBgAnimation(0xED, 1, 0);
        while (func_0012AA80(0xED) == 0) { _ACTWait(1); }
        _ACTWait(1);
        if (D_00633A44 != 0) { scpTrans(D_00633A44, 0x50); }
        lt_fade_status(0x32);
        D_006325B4 = 0;
        scpActivateAllWithKind();
    }
    func_0017B258(0xCF);
    func_0017B288(0xDD);
    func_0017B288(0xDE);
    func_0017B288(0xE0);
    func_0017B258(0xD0);
}

INCLUDE_ASM("asm/nonmatchings/src/st10l", actSt10lGondolaDown);

INCLUDE_ASM("asm/nonmatchings/src/st10l", actSt10lEneCam3Chk);

extern int D_004D2510[];

void actSt10lChainMove(volatile int a0) {
    ActB0Obj *obj = *(ActB0Obj **)(a0 + 0x164);
    obj->unkB0 = D_004D2510;
    while (1) {
        _ACTWait(1);
    }
}

typedef struct St10lBox {
    char pad[0xC0];
    void *field_B0;
    void *field_B4;
} St10lBox;

extern int *D_004D2550[];
extern void actSt10lChain(volatile int a0);

void func_00225DD0(volatile int a0) {
    St10lBox *obj = *(St10lBox **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D2550[1] = (int *)actSt10lChain;
    obj->field_B0 = 0;
    obj->field_B4 = (void *)D_004D2550;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern void AddWayPointTop(int a0, int a1);
extern int actCreateSubThread(void *fn, int a1);
extern void actSt10lFloor();

void actSt10lChain(volatile int a0) {
    lt_fade_status(0x33);
    actCreateSubThread(actSt10lFloor, 0x15);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0xEC, 1, 0);
    stage_KillPlayBgAnimation(0xEB, -1, -2);
    while (func_0012AA80(0xEC) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x5AB) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x5AA) + 0x16C) = 0;
    D_006325B4 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
    AddWayPointTop(5, 1);
}

extern int D_00274EC0[];
extern int func_00262BE8(int a0, long a1);
extern int func_00263160(int a0);
extern int func_00263218(int a0);

void actSt10lFloor(volatile int a0) {
    _ACTWait(func_00263218(func_00262BE8(func_00263160((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]), (long)0x804C << 47)));
    func_0017B258(0xCE);
}


void actSt10lGondola(void) {
    if (func_0017B230(0x5F) == 0) {
        AddWayPointTop(0x9, 0);
        AddWayPointTop(0xA, 0);
    } else {
        AddWayPointTop(0x9, 1);
        AddWayPointTop(0xA, 1);
    }
    if (func_0017B230(0x60) == 0) {
        AddWayPointTop(0xC, 0);
    } else {
        AddWayPointTop(0xC, 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00225FE0);

extern int D_00633A48;
extern void actSt10rCage();
extern void actSt10rTower();
extern float scpSekizou(int a0);

void func_002260A8(volatile int a0) {
    while (!(scpSekizou(0x66C) < -2.0f)) { _ACTWait(1); }
    lt_fade_status(0x33);
    actCreateSubThread(actSt10rTower, 0x15);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    _ACTWait(0x1E);
    scpPlayStart(0x42, (int)&D_00633A48, 1, 1, 1);
    while (D_00633A48 == 0) { _ACTWait(1); }
    actCreateSubThread(actSt10rCage, 0x15);
    stage_KillPlayBgAnimation(0x5C, 1, 0);
    while (func_0012AA80(0x5C) == 0) { _ACTWait(1); }
    _ACTWait(1);
    _ACTWait(1);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
    *(int *)(actSt25aQueenDeadChk(0x65D) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x65E) + 0x16C) = 0;
    AddWayPointTop(0x9, 1);
    AddWayPointTop(0xA, 1);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D25B0[];
extern int D_004D25D0[];
extern int D_00631AE4;
extern int actInitialize(int a0);
extern void func_00226300(volatile int a0);
extern void func_00226478(volatile int a0);
extern int scpSleepEnemyOne(int a0, float a1, int a2);

void func_002261F8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne((int)a0, 200.0f, D_00631AE4) != 0 ||
        (D_00631AE8 != 0 && scpSleepEnemyOne((int)a0, 400.0f, D_00631AE8) != 0)) {
        stage_KillPlayBgAnimation(0x5F, 0, 0);
        _ACTWait(0x3C);
        D_004D25B0[1] = (int)func_00226478;
        gobj->unkC4 = D_004D25B0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x5E, 0, 0);
        D_004D25D0[1] = (int)func_00226300;
        gobj->unkC4 = D_004D25D0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D25F0[];
extern long long D_0061BEA0[];
extern void actSt10rChain();
extern void func_0017E870(float a0, float a1, float a2, float a3);
extern int scpKillSpiderGroup(int a0, int a1);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, long long *a2, int a3);

void func_00226300(volatile int a0) {
    ActB4Obj *gobj = *(ActB4Obj **)(a0 + 0x164);
    long long buf[2];
    while (scpKillSpiderGroup((int)a0, 0x1000000) == 0) { _ACTWait(1); }
    _ACTWait(0xF);
    actCreateSubThread(actSt10rChain, 0x15);
    func_0017E870(-1879.0f, -1047.0f, -620.0f, 100.0f);
    stage_KillPlayBgAnimation(0x5E, 1, 0);
    buf[0] = D_0061BEA0[0];
    buf[1] = D_0061BEA0[1];
    soundSeDefPlayWithVolumeRate(0x4AC, 0, buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, buf, 1);
    while (func_0012AA80(0x5E) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_004D25F0[1] = (int)func_00226478;
    gobj->unkC4 = D_004D25F0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226478);
ASM_LIT4_SLOT(D_0063160C, -1879.0f);
ASM_LIT4_SLOT(D_00631610, -1047.0f);

extern int D_00633A4C;

void func_002265F0(volatile int a0) {
    lt_fade_status(0x33);
    func_0017B258(0x60);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    scpPlayStart(0x51, (int)&D_00633A4C, 1, 1, 1);
    while (D_00633A4C == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x5D, 1, 0);
    while (func_0012AA80(0x5D) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x654) + 0x16C) = 0;
    *(int *)(actSt25aQueenDeadChk(0x655) + 0x16C) = 1;
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
    AddWayPointTop(0xC, 1);
}


void func_002266D0(volatile int a0) {
    while (scpSleepEnemyOne((int)a0, 300.0f, actSt25aQueenDeadChk(0x66B)) == 0 ||
           func_0017B230(0x5F) != 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    func_0017B258(0x62);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x60, 1, 0);
    *(int *)(actSt25aQueenDeadChk(0x66B) + 0x16C) = 0;
    while (func_0012AA80(0x60) == 0) { _ACTWait(1); }
    _ACTWait(1);
    _ACTWait((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1] * 7);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern int func_0012AB50(int a0, int a1, int a2);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void soundSeDefPitchSet(int a0);

void func_002267E8(volatile int a0) {
    int h;
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00631AE4, 0xB000000) == 0 ||
           scpSleepSpiderGroupOne(D_00631AE8, 0xB000000) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    *(int *)(actSt25aQueenDeadChk(0x68E) + 0x16C) = 0;
    stage_KillPlayBgAnimation(0xE7, -1, -2);
    stage_KillPlayBgAnimation(0x62, 1, 0);
    h = soundSeDefPlayWithVolumeRate(0x532, 0, 0, 1);
    while (func_0012AB50(0x62, 0x46, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_0017E870(-3855.0f, -470.0f, 1392.0f, 200.0f);
    while (func_0012AA80(0x62) == 0) { _ACTWait(1); }
    _ACTWait(1);
    soundSeDefPitchSet(h);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
    _ACTWait(0x78);
    func_0017B258(0x66);
}

extern int D_00633A50;

void func_00226958(volatile int a0) {
    int q;
    int t;
    while (scpSleepEnemyOne((int)a0, 70.0f, actSt25aQueenDeadChk(0x667)) == 0 ||
           func_0017B230(0x66) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    func_0017B258(0x67);
    _ACTWait(0x78);
    scpPlayStart(0x35, (int)&D_00633A50, 1, 1, 1);
    while (D_00633A50 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x64, 1, 0);
    while (func_0012AB50(0x64, 0x96, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    soundSeDefPlayWithVolumeRate(0x34F, 0, 0, 1);
    while (func_0012AB50(0x64, 0xD2, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x668) + 0x16C) = 1;
    stage_KillPlayBgAnimation(0x64, 0, -1);
    q = actSt25aQueenDeadChk(0x667);
    t = D_00633A50;
    *(int *)(q + 0x16C) = 0;
    if (t != 0) { scpTrans(t, 0x50); }
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226AF0);

extern int D_004D2690[];
extern void actSt10rEnemy1(volatile int a0);

void func_00226BA0(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004D2690[1] = (int)actSt10rEnemy1;
    gobj->unkC4 = D_004D2690;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D26B0[];
extern void func_002277C0(volatile int a0);

void func_00226C08(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004D26B0[1] = (int)func_002277C0;
    gobj->unkC4 = D_004D26B0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D26D0[];
extern void func_002266D0(volatile int a0);

void func_00226C70(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x61) == 0 && func_0017B230(0x62) == 0) {
        D_004D26D0[1] = (int)func_002266D0;
        gobj->unkC4 = D_004D26D0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        *(int *)(actSt25aQueenDeadChk(0x66B) + 0x16C) = 0;
    }
}

extern int D_004D26F0[];
extern void func_00227868(volatile int a0);

void func_00226D08(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x61) == 0 && func_0017B230(0x62) == 0) {
        D_004D26F0[1] = (int)func_00227868;
        gobj->unkC4 = D_004D26F0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D2710[];
extern void func_002278E0(volatile int a0);

void func_00226D90(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x61) == 0 && func_0017B230(0x62) == 0) {
        D_004D2710[1] = (int)func_002278E0;
        gobj->unkC4 = D_004D2710;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D2750[];
extern int D_004D2770[];
extern void func_002279B0(volatile int a0);
extern void func_00227A48(volatile int a0);

void func_00226E18(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x63) == 0) {
        D_004D2750[1] = (int)func_002279B0;
        gobj->unkC4 = D_004D2750;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        D_004D2770[1] = (int)func_00227A48;
        gobj->unkC4 = D_004D2770;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D27D0[];
extern void func_00227AE0(volatile int a0);

void func_00226EC0(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004D27D0[1] = (int)func_00227AE0;
    gobj->unkC4 = D_004D27D0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D2830[];
extern int D_004D2850[];
extern void func_00227C70(volatile int a0);
extern void func_00227D18(volatile int a0);

void func_00226F28(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x64) == 0) {
        D_004D2830[1] = (int)func_00227C70;
        gobj->unkC4 = D_004D2830;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        AddWayPointTop(0x19, 1);
        AddWayPointTop(0x1A, 1);
        D_004D2850[1] = (int)func_00227D18;
        gobj->unkC4 = D_004D2850;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D28B0[];
extern int D_004D28D0[];
extern void func_00227DC0(volatile int a0);
extern void func_00227E68(volatile int a0);

void func_00226FE8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x65) == 0) {
        D_004D28B0[1] = (int)func_00227DC0;
        gobj->unkC4 = D_004D28B0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        AddWayPointTop(0x19, 1);
        AddWayPointTop(0x1A, 1);
        D_004D28D0[1] = (int)func_00227E68;
        gobj->unkC4 = D_004D28D0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D2930[];
extern void func_002267E8(volatile int a0);

void func_002270A8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x66) == 0) {
        stage_KillPlayBgAnimation(0x62, 0, 0);
        D_004D2930[1] = (int)func_002267E8;
        gobj->unkC4 = D_004D2930;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x62, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x68E) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0xE7, -1, -2);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00227160);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_002271E8);

extern int D_004D2730[];
extern void func_00227940(volatile int a0);

void func_00227280(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004D2730[1] = (int)func_00227940;
    gobj->unkC4 = D_004D2730;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D2990[];
extern void func_002280B8(volatile int a0);

void func_002272E8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004D2990[1] = (int)func_002280B8;
    gobj->unkC4 = D_004D2990;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

