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

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CDFD0[];
void actSt19aOriMain(volatile int a0);

void actSt19aHaguruma(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004CDFD0[1] = (int)actSt19aOriMain;
    gobj->unkB4 = D_004CDFD0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int D_004CE010[];
void actSt19aOriSwitch(volatile int a0);

void actSt19aHagurumaChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004CE010[1] = (int)actSt19aOriSwitch;
    gobj->unkB4 = D_004CE010;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_00178DB0(int a0);
extern int D_004CE090[];
void actSt19aOriUp(volatile int a0);

void actSt19aPipeChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x10) == 0) {
        stage_KillPlayBgAnimation(0x28, 0, 0);
        D_004CE090[1] = (int)actSt19aOriUp;
        gobj->unkB4 = D_004CE090;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x28, 0, -1);
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void gflagInit(int a0);
void actSt19aChainDown(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
stage_KillPlayBgAnimation(0x1F,0,-1); stage_KillPlayBgAnimation(0x19,0,0); stage_KillPlayBgAnimation(0x22,0,0); stage_KillPlayBgAnimation(0x23,0,0); stage_KillPlayBgAnimation(0x25,0,0); }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aChainUp);

void actSt19aOri(int a0) {
    int buf[4];
    buf[0] = a0;
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void lt_fade_status(int a0);
extern void func_001790A8(int a0);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt19aPipe();
extern int D_00629DE4;
extern int D_0062BDB8;
extern int D_0062A894;
void actSt19aOriXL(volatile int a0) {
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x1000000) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_001790A8(D_00629DE4);
    gflagOff(D_00629DE4, 0);
    func_00178DD8(0xC);
    scpPlayStart(0x22, (int)&D_0062BDB8, 1, 1, 1);
    while (D_0062BDB8 == 0) { _ACTWait(1); }
    actCreateSubThread(actSt19aPipe, 0x15);
}

#include "common.h"
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int stage_DispBgAnimation(int a0, int a1);
extern void _ACTWait(int a0);
extern void gflagOff(int a0, int a1);
extern void func_0018A380(void);
extern int func_0012A958(int a0);
extern void func_001790E8(int a0);
extern void lt_fade_status(int a0);
extern int D_00629DE4;
extern int D_0062A894;
void actSt19aPipe(volatile int a0) {
    stage_KillPlayBgAnimation(0x2AD, 1, 0);
    while (stage_DispBgAnimation(0x2AD, 0x2AE) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x189);
    func_0018A380();
    while (func_0012A958(0x2AE) == 0) { _ACTWait(1); }
    _ACTWait(1);
    gflagOff(D_00629DE4, 0);
    func_001790E8(D_00629DE4);
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void func_001790A8(int a0);
extern void gflagOff(int a0, int a1);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt18aEne2();
extern int D_00629DE4;
extern int D_0062BDC0;
extern int D_0062BDBC;
extern float D_0062A898;
extern int D_0062A894;
void actSt19aPipeXL(volatile int a0) {
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x2000000) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    func_00178DD8(0xD);
    D_0062A894 = 1;
    func_001790A8(D_00629DE4);
    gflagOff(D_00629DE4, 0);
    scpPlayStart(0x23, (int)&D_0062BDC0, 1, 1, 1);
    while (D_0062BDC0 == 0) { _ACTWait(1); }
    D_0062A898 = 0.5f;
    actCreateSubThread(actSt18aEne2, 0x15);
    scpPlayStart(0x24, (int)&D_0062BDBC, 1, 0, 0);
}

#include "common.h"
extern int itou_boss_gflag_init(void);
extern void _ACTWait(int a0);
extern void lt_fade_status(int a0);
extern void func_001790A8(int a0);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void soundSeVolSet(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt19bIntro();
extern int D_00629DE4;
extern int D_0062BDBC;
extern int D_0062BDC4;
extern int D_0062A894;
void actSt19aChain(volatile int a0) {
    while (itou_boss_gflag_init() == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_001790A8(D_00629DE4);
    gflagOff(D_00629DE4, 0);
    func_00178DD8(0xE);
    if (D_0062BDBC != 0) {
        soundSeVolSet(D_0062BDBC);
    }
    _ACTWait(0x78);
    scpPlayStart(0x25, (int)&D_0062BDC4, 1, 1, 1);
    while (D_0062BDC4 == 0) { _ACTWait(1); }
    actCreateSubThread(actSt19bIntro, 0x15);
}

#include "common.h"
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern void _ACTWait(int a0);
extern int func_0012A958(int a0);
extern void gflagOff(int a0, int a1);
extern void func_001790E8(int a0);
extern void lt_fade_status(int a0);
extern int D_00629DE4;
extern int D_0062A894;
void actSt19bIntro(volatile int a0) {
    stage_KillPlayBgAnimation(0x2B0, 1, 0);
    while (func_0012AA28(0x2B0, 0x12C, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x22, 1, 0);
    while (func_0012A958(0x2B0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    gflagOff(D_00629DE4, 0);
    func_001790E8(D_00629DE4);
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern int D_00629DE4;
extern void RequestStageChange(int a0, int a1, int a2, float f12, float f13);
void actSt19aOriMain(volatile int a0) {
    while (scpTriggerBall(a0, D_00629DE4, 400.0f) == 0 ||
           func_00178DB0(0x127) != 0) {
        _ACTWait(1);
    }
    RequestStageChange(3, D_00629DE4, 0, 2.0f, 4.0f);
}

typedef struct { char pad[0xB0]; int *unkB0; } ActB0Obj;
extern int D_004CDFF0[];

void actSt19aOriSwitch(volatile int a0) {
    ActB0Obj *gobj = *(ActB0Obj **)(a0 + 0x164);
    gobj->unkB0 = D_004CDFF0;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct { char pad[0xB0]; void *f_B0; void *unkB4; } BoxObj_st19a;
extern int *D_004CE030[];
extern void actSt18aEnemy2_2(volatile int a0);
void func_0022E0E8(volatile int a0) {
    BoxObj_st19a *obj = *(BoxObj_st19a **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CE030[1] = (int *)actSt18aEnemy2_2;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004CE030;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

extern int D_004CE070[];

void actSt19aOriUp(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CE070;
    for (;;) {
        _ACTWait(1);
    }
}

extern int *D_004CE0B0[];
extern void actSt19aChainMain(volatile int a0);
void func_0022E178(volatile int a0) {
    BoxObj_st19a *obj = *(BoxObj_st19a **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CE0B0[1] = (int *)actSt19aChainMain;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004CE0B0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

#include "common.h"
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012A958(int a0);
extern int D_004CE0D0[];
extern int D_0062A894;
void actSt19aChainMain(volatile int a0) {
    lt_fade_status(0x33);
    func_00178DD8(0x10);
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x28, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, (int)D_004CE0D0, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, (int)D_004CE0D0, 1);
    while (func_0012A958(0x28) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

extern void Generator_Mask(int a0);
extern void Generator_ResetCount(int a0);

void actSt19aChainSwitch(volatile int a0) {
    Generator_Mask(a0);
    Generator_ResetCount(a0);
}

extern int func_00178DB0(int a0);
extern void SetWayGroupActive(int a0, int a1);

void actSt19bIntroChk(void) {
    if (func_00178DB0(0x14)) {
        SetWayGroupActive(9, 0);
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
