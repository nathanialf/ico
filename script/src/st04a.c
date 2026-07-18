#include "common.h"

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGate);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGateChk);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aConte06);


extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void func_0017C1B0(void);

void actSt04aConte06Jimaku(volatile int a0) {
    while (actSt25aQueenDeadChk(0x659) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x3C);
    func_0017C1B0();
}

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CBEE0[];
extern int D_004CBF00[];
extern void actSt04aGateOpenChk(volatile int a0);
extern void actConte09(volatile int a0);
void actSt04aGateOpen(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x50) == 0) {
        stage_KillPlayBgAnimation(0x148, 0, 0);
        stage_KillPlayBgAnimation(0x14A, 0, 0);
        D_004CBEE0[1] = (int)actSt04aGateOpenChk;
        gobj->unkB4 = D_004CBEE0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x148, 0, 0x2D);
        stage_KillPlayBgAnimation(0x14A, 0, -1);
        D_004CBF00[1] = (int)actConte09;
        gobj->unkB4 = D_004CBF00;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGateOpenChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actConte09);

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CBF60[];
extern int D_004CBF80[];
extern void actSt04aGateOpen2Chk(volatile int a0);
extern void actConte09_2(volatile int a0);
void actConte09Jimaku(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x51) == 0) {
        stage_KillPlayBgAnimation(0x149, 0, 0);
        stage_KillPlayBgAnimation(0x14C, 0, 0);
        D_004CBF60[1] = (int)actSt04aGateOpen2Chk;
        gobj->unkB4 = D_004CBF60;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x149, 0, 0x2D);
        stage_KillPlayBgAnimation(0x14C, 0, -1);
        D_004CBF80[1] = (int)actConte09_2;
        gobj->unkB4 = D_004CBF80;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGateOpen2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actConte09_2);

extern void func_0017C130(void *a0, float f12, float f13, float f14);
extern void BoxGeo(int a0);
void actSt04aGateOpen3Chk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x10F) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x325) + 0x16C) = 0;
    } else {
        *(int *)(actSt25aQueenDeadChk(0x318) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x323) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x325) + 0x16C) = 1;
        func_0017C130((void *)actSt25aQueenDeadChk(0x325), 0.0f, -200.0f, 0.0f);
        _ACTWait(1);
        BoxGeo(actSt25aQueenDeadChk(0x325));
    }
}


extern void func_00178DD8(int a0);
void actConte09_3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x110) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x326) + 0x16C) = 0;
    } else {
        *(int *)(actSt25aQueenDeadChk(0x319) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x324) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x326) + 0x16C) = 1;
        func_00178DD8(0x59);
        func_0017C130((void *)actSt25aQueenDeadChk(0x326), 0.0f, -400.0f, 0.0f);
        _ACTWait(1);
        BoxGeo(actSt25aQueenDeadChk(0x326));
    }
}


extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void actSt04aGateLChk(void) {
    if (!func_00178DB0(0x52)) {
        AddWayPointTop(7, 0);
    }
    if (func_00178DB0(0x53)) {
        AddWayPointTop(5, 1);
    } else {
        AddWayPointTop(5, 0);
    }
}

extern int D_004CBFE0[];
extern void actSt04aTorchXL(volatile int a0);
void actSt04aGateRChk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CBFE0[1] = (int)actSt04aTorchXL;
    gobj->unkB4 = D_004CBFE0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern void func_00179710(int a0, int a1, int a2, int a3, int a4, float f5, float f6, float f7, float f8, float f9, float f10);
extern float D_006297F0, D_006297F4, D_006297F8;

/* NEAR-MISS (rc4, W3 convergence). LOGIC + STRUCTURE fully recovered. Dev shape:
 *   void actSt04aTorch1(volatile int a0) {
 *       int x = a0;                    // volatile read (the extra `lw v0,0(sp)`)
 *       actInitialize(a0);
 *       _ACTWait(1);
 *       func_00179710(a0, 0x56, 0x43, 0, 0x12, D_006297F0, -400.0f, D_006297F4,
 *                     -1000.0f, -400.0f, D_006297F8);
 *   }
 * Matched: volatile-a0 sp spill + reloads, actInitialize(a0), _ACTWait(1), and the
 * 5-int/6-float call (a0,0x56,0x43,0,0x12, f12=D_006297F0, f13=-400, f14=D_006297F4,
 * f15=-1000, f16=-400 [shared via `mov.s f16,f13`], f17=D_006297F8). Residual = ONE
 * jal delay-slot scheduling swap: ROM emits `lwc1 f17,D_006297F8` BEFORE the jal and
 * `mov.s f16,f13` IN the delay; gcc schedules `mov.s f16` before the jal and fills
 * the delay with `lwc1 f17`. A shared `float n=-400.0f` local FLIPS the delay to
 * `mov.s f16` (verified minimal-TU) but in the coalesced TU makes -400 callee-saved
 * ($f20) + a swc1 spill (rc17) — wrong. NEXT LEVER: get reorg to defer the cheap
 * `mov.s f16` into the jal delay (schedule the f17 load ahead of it) WITHOUT a
 * persistent float local. NOT a floor. */
INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aTorch1);


extern int D_004CC060[];
extern int D_004CC080[];
extern void actSt04bSekizoChk(volatile int a0);
extern void actSt04bEne1Chk(volatile int a0);
void actSt04aTorch1Chk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x5B) == 0) {
        D_004CC060[1] = (int)actSt04bSekizoChk;
        gobj->unkB4 = D_004CC060;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        D_004CC080[1] = (int)actSt04bEne1Chk;
        gobj->unkB4 = D_004CC080;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CC040[];
extern void actSt04bEnd(volatile int a0);
void actSt04aTorchAllFlagfChk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x5D) == 0) {
        D_004CC040[1] = (int)actSt04bEnd;
        gobj->unkB4 = D_004CC040;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int actInitialize(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void actSt04aGateL(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0); Generator_Mask(actSt25aQueenDeadChk(0x331));
 while(func_00178DB0(0x5E)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x14); Generator_Call(a0); Generator_Call(actSt25aQueenDeadChk(0x331)); }

void actSt04aGateR(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern int scpSleepEnemyOne(int a0, int a1, float f);
extern int GetSkeltonFocusNode(int a0);
extern void GetCameraDefaultTargetGObj(void);
extern void InitCamera(int a0, int a1, int a2);
extern void AddPluralCameraSet(int a0);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_004CC000[];
extern void actSt04aGateOpen2(volatile int a0);
void actSt04aTorchXL(volatile int a0) {
    int x = a0;
    GObj *g = *(GObj **)(x + 0x164);
    while (scpSleepEnemyOne(a0, D_00629DE4, 100.0f) == 0 ||
           GetSkeltonFocusNode(D_00629DE4) != 0xC6) {
        _ACTWait(1);
    }
    GetCameraDefaultTargetGObj();
    InitCamera(D_00629DE8, 0, 3);
    _ACTWait(0xF);
    AddPluralCameraSet(0x30);
    D_004CC000[1] = (int)actSt04aGateOpen2;
    g->unkB4 = D_004CC000;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGateOpen2);

void actSt04aGateOpen3(int a0) {
    int buf[4];
    buf[0] = a0;
}
