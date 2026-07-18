#include "common.h"

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614980[]; extern long long D_00614990[];
void actSt10lInit(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614980[0]; long long v0b=D_00614990[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614980[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614990[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614990[]; extern long long D_00614980[];
void actSt10lFloorLeft(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614990[0]; long long v0b=D_00614980[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614990[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614980[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
void actSt10lFloorRight(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (D_00629DE8 == 0 || func_00178DB0(0x98) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178DD8(0x99);
    func_00178DD8(0x9A);
}

extern int _SCPBoySupportGirl(int a0, int a1, int a2);
extern int actSt25aQueenDeadChk(int a0);
extern int func_00178DB0(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void _ACTWait(int a0);
extern void scpTrans(int a0, int a1);
extern void scpActivateAllWithKind(void);
extern void func_00178DD8(int a0);
extern void func_00178E08(int a0);
extern int D_0062A894;
extern int D_0062BD4C;
void actSt10lGondolaUp(volatile int a0) {
    while (_SCPBoySupportGirl(0x5A6, 0x109, 0x113) == 0) { _ACTWait(1); }
    *(int *)(actSt25aQueenDeadChk(0x5A6) + 0x16C) = 0;
    *(int *)(actSt25aQueenDeadChk(0x5A7) + 0x16C) = 1;
    if (func_00178DB0(0xDA) == 0 || func_00178DB0(0xDB) == 0 ||
        func_00178DB0(0xDC) == 0) {
        lt_fade_status(0x33);
        D_0062A894 = 1;
        scpDispOnAllWithKind();
        scpPlayStart(0x34, (int)&D_0062BD4C, 1, 1, 1);
        stage_KillPlayBgAnimation(0xEC, 1, 0);
        while (func_0012A958(0xEC) == 0) { _ACTWait(1); }
        _ACTWait(1);
        if (D_0062BD4C != 0) { scpTrans(D_0062BD4C, 0x50); }
        lt_fade_status(0x32);
        D_0062A894 = 0;
        scpActivateAllWithKind();
    }
    func_00178DD8(0xCF);
    func_00178E08(0xDD);
    func_00178E08(0xDE);
    func_00178E08(0xE0);
    func_00178DD8(0xD0);
}


typedef struct { char pad[0xB4]; int unkB4; } ActB4GD;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int actSt25aQueenDeadChk(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CD140[];
extern void actSt10lChainMove(volatile int a0);
INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lGondolaDown);



INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEneCam3Chk);



typedef struct { char pad[0xB0]; int *unkB0; } ActB0Obj;
extern int D_004CD120[];
void actSt10lChainMove(volatile int a0) {
    ActB0Obj *obj = *(ActB0Obj **)(a0 + 0x164);
    obj->unkB0 = D_004CD120;
    while (1) {
        _ACTWait(1);
    }
}


typedef struct { char pad[0xB0]; void *f_B0; void *unkB4; } BoxObj_st10l;
extern int *D_004CD160[];
extern void actSt10lChain(volatile int a0);
void func_00222B00(volatile int a0) {
    BoxObj_st10l *obj = *(BoxObj_st10l **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CD160[1] = (int *)actSt10lChain;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004CD160;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

#include "common.h"
extern void lt_fade_status(int a0);
extern int actCreateSubThread(void *fn, int a1);
extern void actSt10lFloor();
extern void scpDispOnAllWithKind(void);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern void AddWayPointTop(int a0, int a1);
extern int D_0062A894;
void actSt10lChain(volatile int a0) {
    lt_fade_status(0x33);
    actCreateSubThread(actSt10lFloor, 0x15);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0xEB, 1, 0);
    stage_KillPlayBgAnimation(0xEA, -1, -2);
    while (func_0012A958(0xEB) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x5A5) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x5A4) + 0x16C) = 0;
    D_0062A894 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
    AddWayPointTop(5, 1);
}

extern int func_0025F4F0(int a0);
extern int func_0025EF78(int a0, long a1);
extern int func_0025F5A8(int a0);
extern void _ACTWait(int a0);
extern void func_00178DD8(int a0);
extern int D_00271240[];
void actSt10lFloor(volatile int a0) {
    _ACTWait(func_0025F5A8(func_0025EF78(func_0025F4F0((0x3C - D_00271240[0] * 0xA) / D_00271240[1]), (long)0x804C << 47)));
    func_00178DD8(0xCE);
}

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void actSt10lGondola(void) {
    if (func_00178DB0(0x5F) == 0) {
        AddWayPointTop(0x9, 0);
        AddWayPointTop(0xA, 0);
    } else {
        AddWayPointTop(0x9, 1);
        AddWayPointTop(0xA, 1);
    }
    if (func_00178DB0(0x60) == 0) {
        AddWayPointTop(0xC, 0);
    } else {
        AddWayPointTop(0xC, 1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lSekizo);

extern float scpSekizou(int a0);
extern void lt_fade_status(int a0);
extern int actCreateSubThread(void *fn, int a1);
extern void scpDispOnAllWithKind(void);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern int actSt25aQueenDeadChk(int a0);
extern void AddWayPointTop(int a0, int a1);
extern int D_0062A894;
extern int D_0062BD50;
extern void actSt10rTower(volatile int a0);
extern void actSt10rCage(volatile int a0);
void actSt10lBox(volatile int a0) {
    while (!(scpSekizou(0x65E) < -2.0f)) { _ACTWait(1); }
    lt_fade_status(0x33);
    actCreateSubThread(actSt10rTower, 0x15);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    _ACTWait(0x1E);
    scpPlayStart(0x42, (int)&D_0062BD50, 1, 1, 1);
    while (D_0062BD50 == 0) { _ACTWait(1); }
    actCreateSubThread(actSt10rCage, 0x15);
    stage_KillPlayBgAnimation(0x5B, 1, 0);
    while (func_0012A958(0x5B) == 0) { _ACTWait(1); }
    _ACTWait(1);
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
    *(int *)(actSt25aQueenDeadChk(0x653) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x654) + 0x16C) = 0;
    AddWayPointTop(0x9, 1);
    AddWayPointTop(0xA, 1);
}


typedef struct { char pad[0xB4]; int *unkB4; } ActB4E1;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_004CD1C0[];
extern int D_004CD1E0[];
extern void actSt10lEnemy2_1(volatile int a0);
extern void actSt10lEnemy1_2(volatile int a0);
void actSt10lEnemy1_1(volatile int a0) {
    int x = a0;
    ActB4E1 *gobj = (ActB4E1 *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne(a0, D_00629DE4, 200.0f) != 0 ||
        (D_00629DE8 != 0 && scpSleepEnemyOne(a0, D_00629DE8, 400.0f) != 0)) {
        stage_KillPlayBgAnimation(0x5E, 0, 0);
        _ACTWait(0x3C);
        D_004CD1C0[1] = (int)actSt10lEnemy2_1;
        gobj->unkB4 = D_004CD1C0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x5D, 0, 0);
        D_004CD1E0[1] = (int)actSt10lEnemy1_2;
        gobj->unkB4 = D_004CD1E0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy1_2);


typedef struct { char pad[0xB4]; int *unkB4; } ActB4E21;
struct SndBuf16_21 { long long a, b; };
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int scpKillSpiderGroup(int a0, int a1);
extern int actCreateSubThread(void *fn, int a1);
extern void func_0017BF50(float a0, float a1, float a2, float a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012A958(int a0);
extern volatile float D_006298F8, D_006298FC;
extern struct SndBuf16_21 D_006149D0;
extern int D_004CD220[];
extern void actSt10rSekizo(volatile int a0);
extern void actSt10lEnemy1_2(volatile int a0);
void actSt10lEnemy2_1(volatile int a0) {
    struct SndBuf16_21 buf;
    ActB4E21 *obj = *(ActB4E21 **)(a0 + 0x164);
    while (scpKillSpiderGroup(a0, 0x1000000) != 0) { _ACTWait(1); }
    _ACTWait(0xF);
    actCreateSubThread(actSt10rSekizo, 0x15);
    func_0017BF50(D_006298F8, D_006298FC, -620.0f, 100.0f);
    stage_KillPlayBgAnimation(0x5E, 1, 0);
    buf = D_006149D0;
    soundSeDefPlayWithVolumeRate(0x4AC, 0, (int)&buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, (int)&buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, (int)&buf, 1);
    while (func_0012A958(0x5E) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_004CD220[1] = (int)actSt10lEnemy1_2;
    obj->unkB4 = D_004CD220;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


#include "common.h"
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern void AddWayPointTop(int a0, int a1);
extern int D_0062BD54;
extern int D_0062A894;
void actSt10lEnemy2_2(volatile int a0) {
    lt_fade_status(0x33);
    func_00178DD8(0x60);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    scpPlayStart(0x51, (int)&D_0062BD54, 1, 1, 1);
    while (D_0062BD54 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x5C, 1, 0);
    while (func_0012A958(0x5C) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x64A) + 0x16C) = 0;
    *(int *)(actSt25aQueenDeadChk(0x64B) + 0x16C) = 1;
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
    AddWayPointTop(0xC, 1);
}

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern int func_00178DB0(int a0);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062A894;
extern int D_00271240[];
void actSt10lEnemy2_3(volatile int a0) {
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x65D), 300.0f) == 0 ||
           func_00178DB0(0x5F) != 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    func_00178DD8(0x62);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x5F, 1, 0);
    *(int *)(actSt25aQueenDeadChk(0x65D) + 0x16C) = 0;
    while (func_0012A958(0x5F) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(((0x3C - D_00271240[0] * 0xA) / D_00271240[1]) * 7);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern int actSt25aQueenDeadChk(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void _ACTWait(int a0);
extern void func_0017BF50(float a0, float a1, float a2, float a3);
extern int func_0012A958(int a0);
extern void soundSeDefPitchSet(int a0);
extern void scpActivateAllWithKind(void);
extern void func_00178DD8(int a0);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_0062A894;
extern volatile float D_00629900;
void actSt10lEnemy3_1(volatile int a0) {
    int se;
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0xB000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0xB000000) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    *(int *)(actSt25aQueenDeadChk(0x67E) + 0x16C) = 0;
    stage_KillPlayBgAnimation(0xE6, -1, -2);
    stage_KillPlayBgAnimation(0x61, 1, 0);
    se = soundSeDefPlayWithVolumeRate(0x532, 0, 0, 1);
    while (func_0012AA28(0x61, 0x46, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_0017BF50(D_00629900, -470.0f, 1392.0f, 200.0f);
    while (func_0012A958(0x61) == 0) { _ACTWait(1); }
    _ACTWait(1);
    soundSeDefPitchSet(se);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
    _ACTWait(0x78);
    func_00178DD8(0x66);
}


extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern int func_00178DB0(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern void scpTrans(int a0, int a1);
extern void scpActivateAllWithKind(void);
extern int D_0062A894;
extern int D_0062BD58;
void actSt10lEnemy3_2(volatile int a0) {
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x659), 70.0f) == 0 ||
           func_00178DB0(0x66) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    func_00178DD8(0x67);
    _ACTWait(0x78);
    scpPlayStart(0x35, (int)&D_0062BD58, 1, 1, 1);
    while (D_0062BD58 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x63, 1, 0);
    while (func_0012AA28(0x63, 0x96, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    soundSeDefPlayWithVolumeRate(0x34F, 0, 0, 1);
    while (func_0012AA28(0x63, 0xD2, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x65A) + 0x16C) = 1;
    stage_KillPlayBgAnimation(0x63, 0, -1);
    {
        int *q = (int *)actSt25aQueenDeadChk(0x659);
        int t = D_0062BD58;
        *(int *)((char *)q + 0x16C) = 0;
        if (t != 0) { scpTrans(t, 0x50); }
    }
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEneCam1);


typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CD2A0[];
extern void actSt10rEnemy1(volatile int a0);
void actSt10lEneCam2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004CD2A0[1] = (int)actSt10rEnemy1;
    gobj->unkB4 = D_004CD2A0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

