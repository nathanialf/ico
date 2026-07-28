#include "common.h"
extern int D_004D0E10[];

typedef struct GObjB4a { char pad[0xC4]; int *unkB4; } GObjB4a;

typedef struct GObj_B4 {
    char pad[0xC4];
    int *unkB4;
} GObj_B4;

extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void *actSt25aQueenDeadChk(int a0);
extern int func_0017B230(int a0);

void actSt03tSwitchL(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x62) != 0) {
        ((int *)actSt25aQueenDeadChk(0x630))[0x16C / 4] = 0;
        if (func_0017B230(0x5F) != 0) {
            ((int *)actSt25aQueenDeadChk(0x630))[0x16C / 4] = 0;
            ((int *)actSt25aQueenDeadChk(0x631))[0x16C / 4] = 0;
        } else {
            ((int *)actSt25aQueenDeadChk(0x632))[0x16C / 4] = 0;
        }
    }
    if (func_0017B230(0x61) != 0) {
        ((int *)actSt25aQueenDeadChk(0x631))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x632))[0x16C / 4] = 0;
    }
    if (func_0017B230(0x61) == 0 && func_0017B230(0x62) == 0) {
        ((int *)actSt25aQueenDeadChk(0x630))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x631))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x632))[0x16C / 4] = 0;
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1110[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int actSt03tSekizoEvent[];
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt03tSwitchLChk(volatile int a0) {
    int x = a0;
    struct { char pad[0xC4]; int *unkB4; } *gobj = (void *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x6A) != 0) {
        stage_KillPlayBgAnimation(0x57, 0, 0);
        _ACTWait(0xA);
        stage_KillPlayBgAnimation(0x57, 0, 0x95);
    } else {
        stage_KillPlayBgAnimation(0x57, 0, 0x12C);
    }
    D_004D1110[1] = (int)actSt03tSekizoEvent;
    gobj->unkB4 = D_004D1110;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1090[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt03tGirlCamStartChk(volatile int a0);
extern int func_0017B230(int a0);

void actSt03tSwitchLUpChk(volatile int a0) {
    int x = a0;
    GObjB4a *gobj = (GObjB4a *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x69) == 0) {
        D_004D1090[1] = (int)actSt03tGirlCamStartChk;
        gobj->unkB4 = D_004D1090;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D10D0[];
extern void actCreateSubThread(int a0, int a1);
extern void actSt02aSecretItem(volatile int a0);
extern void actSt02aTakiWay(void);
extern void func_00211EC8(void);

void actSt03tSwitchR(volatile int a0) {
    int x = a0;
    GObjB4a *gobj = (GObjB4a *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x5F) != 0) {
        D_004D10D0[1] = (int)func_00211EC8;
        gobj->unkB4 = D_004D10D0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
    ((int *)actSt25aQueenDeadChk(0x61A))[0x16C / 4] = 0;
    actCreateSubThread((int)actSt02aTakiWay, 0x15);
    actCreateSubThread((int)actSt02aSecretItem, 0x15);
}

extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void *actSt25aQueenDeadChk(int a0);
extern int func_0017B230(int a0);

void actSt03tSwitchRChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x63) == 0) {
        ((int *)actSt25aQueenDeadChk(0x634))[0x16C / 4] = 0;
    }
}

extern int D_004D11B0[];
extern void actSt03tEneChk(volatile int a0);

void actSt03tSwitchRUpChk(volatile int a0) {
    int x = a0;
    GObjB4a *gobj = (GObjB4a *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x6C) == 0) {
        D_004D11B0[1] = (int)actSt03tEneChk;
        gobj->unkB4 = D_004D11B0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);

void actSt03tBoxA(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_0017B230(0x6D)==0){
  _ACTWait(1);
 }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

void actSt03tBoxB(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_0017B230(0x6D)==0){ _ACTWait(1); }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

extern float D_006314FC;
extern float D_00631500;
extern void func_0017BF78(int, int, int, int, int, float, float, float, float, float, float);

void actSt03tInit(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_0017BF78(a0, 0x6E, 0x58, 0, 0x12, 900.0f, D_006314FC, D_00631500, 800.0f, D_006314FC, D_00631500);
}

extern int D_004D11D0[];
extern int D_004D11F0[];
extern void actSt03tWayOffChk(volatile int a0);
extern void actSt04aGate(void);
extern int func_0017EB50(void);

void actSt03tGirlCam(volatile int a0) {
    int x = a0;
    GObjB4a *gobj = (GObjB4a *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x6F) == 0) {
        D_004D11D0[1] = (int)actSt04aGate;
        gobj->unkB4 = D_004D11D0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        D_004D11F0[1] = (int)actSt03tWayOffChk;
        gobj->unkB4 = D_004D11F0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1250[];
extern void actSt04aGateChk(void);

void actSt03tSekizo(volatile int a0) {
    int x = a0;
    GObj_B4 *gobj = (GObj_B4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x5F) != 0) {
        D_004D1250[1] = (int)actSt04aGateChk;
        gobj->unkB4 = D_004D1250;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D12B0[];
extern void actSt04aConte06Jimaku(void);

void actSt03tWay(volatile int a0) {
    int x = a0;
    GObjB4a *gobj = (GObjB4a *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x67) == 0) {
        D_004D12B0[1] = (int)actSt04aConte06Jimaku;
        gobj->unkB4 = D_004D12B0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

void actSt03tEne(int x) {
    volatile int local = x;
}

extern long long D_0061BA20[];
extern long long D_0061BA30[];
extern void scpDispOffAllWithKind(int *buf, int a1);

void actSt03tGene(volatile int a0){
 long long b1[2]; long long b2[2];
 long long v0a=D_0061BA20[0]; long long v0b=D_0061BA30[0];
 int i;
 for(i=0;i<0x32;i++){
  switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BA20[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BA30[1]; scpDispOffAllWithKind((int*)b2,0); break;
  }
  _ACTWait(1);
 } }

void actSt03tGirlCamEvent(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061BA30[0]; long long v0b=D_0061BA20[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BA30[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BA20[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern int D_004D1070[];
extern int D_0062A894;

void actSt03tGirlCamStartChk(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    *(int *)(gobj + 0xC0) = (int)D_004D1070;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct St03tBox { char pad[0xC0]; void *field_B0; void *field_B4; } St03tBox;
extern int *D_004D10B0[];
void actSt03tGirlCamEndChk(volatile int a0);
extern void lt_fade_status(int a0);
extern int D_006325B4;

void func_00212AF8(volatile int a0) {
    St03tBox *obj = *(St03tBox **)(a0 + 0x164);
    obj->field_B0 = 0;
    lt_fade_status(0x33);
    D_006325B4 = 1;
    D_004D10B0[1] = (int *)actSt03tGirlCamEndChk;
    obj->field_B4 = (void *)D_004D10B0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern void AddWayPointTop(int a0, int a1);
extern int D_006325B4;
extern int D_00633970;
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);

void actSt03tGirlCamEndChk(volatile int a0) {
    scpDispOnAllWithKind();
    func_0017B258(0x69);
    scpPlayStart(0x5E, (int)&D_00633970, 1, 1, 1);
    while (D_00633970 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x55, 1, 0);
    stage_KillPlayBgAnimation(0x56, 1, 0);
    while (func_0012AA80(0x56) == 0) { _ACTWait(1); }
    _ACTWait(1);
    AddWayPointTop(0x1A, 1);
    D_006325B4 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
}

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSekizoEvent);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tEneChk);

void actSt03tWayOnChk(int x) {
    volatile int local = x;
}

extern int D_004D1210[];
extern int D_00631AE8;
extern void func_0017B288(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actSt03tWayOffChk(volatile int a0) {
    GObjB4a *gobj = *(GObjB4a **)(a0 + 0x164);
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    while (func_0017EB50() != 0 || scpSleepSpiderGroupOne(D_00631AE8, 0x4000000) == 0) {
        _ACTWait(1);
    }
    AddWayPointTop(0x35, 1);
    AddWayPointTop(0x37, 1);
    AddWayPointTop(0x38, 1);
    AddWayPointTop(0x39, 1);
    func_0017B288(0x6F);
    {
        int *p = D_004D11B0 + 24;
        p[1] = (int)actSt04aGate;
        gobj->unkB4 = p;
    }
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

