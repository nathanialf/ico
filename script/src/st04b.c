#include "common.h"

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
extern void BoxBarSoundOn(int a0, int a1);
extern int actInitialize(int a0);

#include "common.h"
extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern void lt_fade_status(int a0);
extern void scpSleepEnemyOne(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void scpWakeupEnemyOne(int a0);
extern void *D_00629DE8;
extern int D_00629DE4;
extern int D_0062A894;
void actSt04bEnd(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpTriggerBall(a0, D_00629DE4, 100.0f) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpSleepEnemyOne(0xD57);
    func_00178DD8(0x5D);
    func_00178DD8(0x5E);
    stage_KillPlayBgAnimation(0x44, 1, 0);
    while (func_0012A958(0x44) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    scpWakeupEnemyOne(0xD57);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bSekizoChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bEne1Chk);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bCrest01XL);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bDoorXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bMonyoDoorXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bEne1);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bEnemy1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bBallXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bSolarXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bSekizoEvent);

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern void func_00178DD8(int a0);
extern void lt_fade_status(int a0);
extern void func_001790A8(void *a0);
extern void scpTrans(void *a0, int a1);
extern void AdpcmClose(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt04aEnvSeWakare2(volatile int a0);
extern void func_00213960(volatile int a0);
extern void actConte09_3Jimaku(volatile int a0);
extern void *D_00629DE8;
extern int D_00629DE4;
extern int D_0062A894;
extern void *D_0062BC8C;
extern char *D_0062BC90;

void actSt04bGirlWay(volatile int a0) {
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (func_00178DB0(0x7F) == 0 || scpTriggerBall(a0, D_00629DE4, 450.0f) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x80);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_001790A8((void *)D_00629DE4);
    func_001790A8(D_00629DE8);
    if (D_0062BC8C != 0) {
        scpTrans(D_0062BC8C, 0x50);
    }
    while (D_0062BC90 == 0) {
        _ACTWait(1);
    }
    AdpcmClose(*(int *)(D_0062BC90 + 0x2C));
    actCreateSubThread(actSt04aEnvSeWakare2, 0x15);
    actCreateSubThread(func_00213960, 0x15);
    actCreateSubThread(actConte09_3Jimaku, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", func_00213960);

#include "common.h"
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void scpFadeIn(float f);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void RequestStageChange(int a0, int a1, int a2, float f0, float f1);
extern int D_0062BC94;
extern int D_00629DE4;
extern void *D_00629DE8;
extern int D_0062A894;
void func_00214368(volatile int a0) {
    while (func_00178DB0(0x9B) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_00178DD8(0x7C);
    scpPlayStart(0x1C, (int)&D_0062BC94, 1, 1, 1);
    while (D_0062BC94 == 0) { _ACTWait(1); }
    scpFadeIn(6.0f);
    stage_KillPlayBgAnimation(0x103, 1, 0);
    while (func_0012A958(0x103) == 0) { _ACTWait(1); }
    _ACTWait(1);
    RequestStageChange(4, D_00629DE4, (int)D_00629DE8, 1.0f, 8.0f);
}

extern void func_0018F940(void);
extern int fightSoundClose(void);
extern void scpFadeIn(float f);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void RequestStageChange(int a0, int a1, int a2, float f0, float f1);
extern int D_0062BC98;

void func_00214468(volatile int a0) {
    while (func_00178DB0(0xD1) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_00178DD8(0x7D);
    func_0018F940();
    while (fightSoundClose() != 0) { _ACTWait(1); }
    scpPlayStart(0x1D, (int)&D_0062BC98, 1, 1, 1);
    while (D_0062BC98 == 0) { _ACTWait(1); }
    scpFadeIn(6.0f);
    stage_KillPlayBgAnimation(0x105, 1, 0);
    while (func_0012A958(0x105) == 0) { _ACTWait(1); }
    _ACTWait(1);
    if (func_00178DB0(0xDD) != 0) { RequestStageChange(5, D_00629DE4, (int)D_00629DE8, 1.0f, 8.0f); }
    if (func_00178DB0(0xDE) != 0) { RequestStageChange(6, D_00629DE4, (int)D_00629DE8, 1.0f, 8.0f); }
    if (func_00178DB0(0xDF) != 0) { RequestStageChange(9, D_00629DE4, (int)D_00629DE8, 1.0f, 8.0f); }
    if (func_00178DB0(0xE0) != 0) { RequestStageChange(7, D_00629DE4, (int)D_00629DE8, 1.0f, 8.0f); }
    if (func_00178DB0(0xD0) != 0) { RequestStageChange(8, D_00629DE4, (int)D_00629DE8, 1.0f, 8.0f); }
}


extern int actSt25aQueenDeadChk(int a0);
extern void gflagInit(int a0);
extern int D_004CC200[];
extern void func_00214950(volatile int a0);

void func_00214640(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x8B) == 0) {
        if (func_00178DB0(0x83) != 0) { *(int *)(actSt25aQueenDeadChk(0x209) + 0x16C) = 0; stage_KillPlayBgAnimation(0xF9, 0, -1); }
        if (func_00178DB0(0x84) != 0) { *(int *)(actSt25aQueenDeadChk(0x20A) + 0x16C) = 0; stage_KillPlayBgAnimation(0xFA, 0, -1); }
        if (func_00178DB0(0x85) != 0) { *(int *)(actSt25aQueenDeadChk(0x20B) + 0x16C) = 0; stage_KillPlayBgAnimation(0xFB, 0, -1); }
        if (func_00178DB0(0x86) != 0) { *(int *)(actSt25aQueenDeadChk(0x20C) + 0x16C) = 0; stage_KillPlayBgAnimation(0xFC, 0, -1); }
        if (func_00178DB0(0x87) != 0) { *(int *)(actSt25aQueenDeadChk(0x20D) + 0x16C) = 0; stage_KillPlayBgAnimation(0xFD, 0, -1); }
        if (func_00178DB0(0x88) != 0) { *(int *)(actSt25aQueenDeadChk(0x20E) + 0x16C) = 0; stage_KillPlayBgAnimation(0xFE, 0, -1); }
        if (func_00178DB0(0x89) != 0) { *(int *)(actSt25aQueenDeadChk(0x20F) + 0x16C) = 0; stage_KillPlayBgAnimation(0xFF, 0, -1); }
        if (func_00178DB0(0x8A) != 0) { *(int *)(actSt25aQueenDeadChk(0x210) + 0x16C) = 0; stage_KillPlayBgAnimation(0x100, 0, -1); }
        D_004CC200[1] = (int)func_00214950;
        gobj->unkB4 = D_004CC200;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        *(int *)(actSt25aQueenDeadChk(0x209) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x20A) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x20B) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x20C) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x20D) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x20E) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x20F) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x210) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0xF9, 0, -1);
        stage_KillPlayBgAnimation(0xFA, 0, -1);
        stage_KillPlayBgAnimation(0xFB, 0, -1);
        stage_KillPlayBgAnimation(0xFC, 0, -1);
        stage_KillPlayBgAnimation(0xFD, 0, -1);
        stage_KillPlayBgAnimation(0xFE, 0, -1);
        stage_KillPlayBgAnimation(0xFF, 0, -1);
        stage_KillPlayBgAnimation(0x100, 0, -1);
        gflagInit(0x211);
        gflagInit(0x212);
        gflagInit(0x213);
        gflagInit(0x214);
        gflagInit(0x215);
        gflagInit(0x216);
        gflagInit(0x217);
        gflagInit(0x218);
        gflagInit(0x219);
        gflagInit(0x21A);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", func_00214950);

extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern int func_0012AA28(int a0, int a1, int a2);
extern void gflagInit(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BC9C;

void func_00214B20(volatile int a0) {
    while (func_00178DB0(0x83) == 0 || func_00178DB0(0x84) == 0 ||
           func_00178DB0(0x85) == 0 || func_00178DB0(0x86) == 0 ||
           func_00178DB0(0x87) == 0 || func_00178DB0(0x88) == 0 ||
           func_00178DB0(0x89) == 0 || func_00178DB0(0x8A) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    func_00178DD8(0x8B);
    scpPlayStart(0x53, (int)&D_0062BC9C, 1, 1, 1);
    while (D_0062BC9C == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0xF8, 1, 0);
    while (func_0012AA28(0xF8, 0x3C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagInit(0x211);
    gflagInit(0x212);
    gflagInit(0x213);
    gflagInit(0x214);
    gflagInit(0x215);
    gflagInit(0x216);
    gflagInit(0x217);
    gflagInit(0x218);
    gflagInit(0x219);
    gflagInit(0x21A);
    while (func_0012A958(0xF8) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(0x3C);
    D_0062A894 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
}


extern void scpFadeOut(int a0, int a1, int a2, float f);
extern int D_004CC1C0[];

void func_00214CF0(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x7C) == 0) {
        func_00178DD8(0x163);
        scpFadeOut(0, 0, 0, 255.0f);
        stage_KillPlayBgAnimation(0x105, 0, 0);
        D_004CC1C0[1] = (int)func_00214368;
        gobj->unkB4 = D_004CC1C0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}



/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00614810;  /* stride 0x4 */

/* end struct shapes */
