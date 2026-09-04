#include "common.h"

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);

extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int D_004CD2C0[];
extern void actSt10lEnemy2_3(volatile int a0);
void actSt10rInit(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x61) == 0 && func_00178DB0(0x62) == 0) {
        D_004CD2C0[1] = (int)actSt10lEnemy2_3;
        gobj->unkB4 = D_004CD2C0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        *(int *)(actSt25aQueenDeadChk(0x65D) + 0x16C) = 0;
    }
}


extern int func_00178DB0(int a0);
extern int D_004CD2E0[];
extern void actSt10rEnemy2(volatile int a0);
void actSt10rFloorChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x61) == 0 && func_00178DB0(0x62) == 0) {
        D_004CD2E0[1] = (int)actSt10rEnemy2;
        gobj->unkB4 = D_004CD2E0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int func_00178DB0(int a0);
extern int D_004CD300[];
extern void actSt10rElv(volatile int a0);
void actSt10rCageMain(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x61) == 0 && func_00178DB0(0x62) == 0) {
        D_004CD300[1] = (int)actSt10rElv;
        gobj->unkB4 = D_004CD300;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int func_00178DB0(int a0);
extern int D_004CD340[];
extern int D_004CD360[];
extern void actSt13aElevUp(volatile int a0);
extern void actSt13aElevDownChk(volatile int a0);
void actSt10rTowerChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x63) == 0) {
        D_004CD340[1] = (int)actSt13aElevUp;
        gobj->unkB4 = D_004CD340;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        D_004CD360[1] = (int)actSt13aElevDownChk;
        gobj->unkB4 = D_004CD360;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CD3C0[];
extern void actSt13aSekizoChk(volatile int a0);
void actSt10rTowerConte(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004CD3C0[1] = (int)actSt13aSekizoChk;
    gobj->unkB4 = D_004CD3C0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int func_00178DB0(int a0);
extern void SetWayGroupActive(int a0, int a1);
extern int D_004CD420[];
extern int D_004CD440[];
extern void actSt13aElevDown(volatile int a0);
extern void actSt13aSekizo(volatile int a0);
void actSt10rChainMove(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x64) == 0) {
        D_004CD420[1] = (int)actSt13aElevDown;
        gobj->unkB4 = D_004CD420;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        SetWayGroupActive(0x19, 1);
        SetWayGroupActive(0x1A, 1);
        D_004CD440[1] = (int)actSt13aSekizo;
        gobj->unkB4 = D_004CD440;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int func_00178DB0(int a0);
extern void SetWayGroupActive(int a0, int a1);
extern int D_004CD4A0[];
extern int D_004CD4C0[];
extern void actSt13aExit(volatile int a0);
extern void actSt13aCheck(volatile int a0);
void actSt10rFence(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x65) == 0) {
        D_004CD4A0[1] = (int)actSt13aExit;
        gobj->unkB4 = D_004CD4A0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        SetWayGroupActive(0x19, 1);
        SetWayGroupActive(0x1A, 1);
        D_004CD4C0[1] = (int)actSt13aCheck;
        gobj->unkB4 = D_004CD4C0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CD520[];
extern void actSt10lEnemy3_1(volatile int a0);
void actSt10rFenceDownChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x66) == 0) {
        stage_KillPlayBgAnimation(0x61, 0, 0);
        D_004CD520[1] = (int)actSt10lEnemy3_1;
        gobj->unkB4 = D_004CD520;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x61, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x67E) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0xE6, -1, -2);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFenceUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFenceDownChk2);


extern int D_004CD320[];
extern void actSt10rGateXL(volatile int a0);
void actSt10rFenceUpChk2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004CD320[1] = (int)actSt10rGateXL;
    gobj->unkB4 = D_004CD320;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


void actSt10rFloor(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rCage);

extern int litodp(int a0);
extern int dpmul(int a0, long a1);
extern int dptoli(int a0);
extern void _ACTWait(int a0);
extern void func_00178DD8(int a0);
extern int D_00271240[];
void actSt10rTower(volatile int a0) {
    _ACTWait(dptoli(dpmul(litodp((0x3C - D_00271240[0] * 0xA) / D_00271240[1]), (long)0x8054 << 47)));
    func_00178DD8(0x5F);
}

void actSt10rExit(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void scpEffectStart(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_006149E0[]; extern long long D_006149F0[];
void actSt10rChain(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006149E0[0]; long long v0b=D_006149F0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006149E0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006149F0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }

extern void scpEffectStart(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_006149F0[]; extern long long D_006149E0[];
void actSt10rSekizo(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006149F0[0]; long long v0b=D_006149E0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006149F0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006149E0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }

extern int D_0062A894;
extern int D_004CD240[];

void actSt10rEne(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CD240;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct { char pad[0xB0]; void *f_B0; void *unkB4; } BoxObj_st10r;
extern int *D_004CD280[];
extern void actSt10lEnemy2_2(volatile int a0);
void func_00224370(volatile int a0) {
    BoxObj_st10r *obj = *(BoxObj_st10r **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CD280[1] = (int *)actSt10lEnemy2_2;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004CD280;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern int D_00629DE4;
extern void RequestStageChange(int a0, int a1, int a2, float f12, float f13);
void actSt10rEnemy1(volatile int a0) {
    while (func_00178DB0(0x5F) != 0 || scpTriggerBall(a0, D_00629DE4, 400.0f) == 0) {
        _ACTWait(1);
    }
    RequestStageChange(3, D_00629DE4, 0, 16.0f, 16.0f);
}

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
void actSt10rEnemy2(volatile int a0) {
    while (scpTriggerBall(a0, actSt25aQueenDeadChk(0x65D), 200.0f) == 0 ||
           func_00178DB0(0x5F) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x61);
    *(int *)(actSt25aQueenDeadChk(0x65D) + 0x16C) = 0;
}

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern int func_00178DB0(int a0);

void actSt10rElv(volatile int a0) {
    while (scpTriggerBall(a0, actSt25aQueenDeadChk(0x65D), 200.0f) == 0 ||
           func_00178DB0(0x5F) != 0) {
        _ACTWait(1);
    }
}

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern int func_00178DB0(int a0);
void actSt10rGateXL(volatile int a0) {
    while (scpTriggerBall(a0, actSt25aQueenDeadChk(0x659), 200.0f) == 0 ||
           func_00178DB0(0x5F) != 0) {
        _ACTWait(1);
    }
    *(int *)(actSt25aQueenDeadChk(0x659) + 0x16C) = 0;
}
