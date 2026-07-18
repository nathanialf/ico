#include "common.h"

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void *actSt25aQueenDeadChk(int a0);

void actSt03tSwitchL(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x62) != 0) {
        ((int *)actSt25aQueenDeadChk(0x626))[0x16C / 4] = 0;
        if (func_00178DB0(0x5F) != 0) {
            ((int *)actSt25aQueenDeadChk(0x626))[0x16C / 4] = 0;
            ((int *)actSt25aQueenDeadChk(0x627))[0x16C / 4] = 0;
        } else {
            ((int *)actSt25aQueenDeadChk(0x628))[0x16C / 4] = 0;
        }
    }
    if (func_00178DB0(0x61) != 0) {
        ((int *)actSt25aQueenDeadChk(0x627))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x628))[0x16C / 4] = 0;
    }
    if (func_00178DB0(0x61) == 0 && func_00178DB0(0x62) == 0) {
        ((int *)actSt25aQueenDeadChk(0x626))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x627))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x628))[0x16C / 4] = 0;
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CBD20[];
extern int func_0020FF58[];

void actSt03tSwitchLChk(volatile int a0) {
    int x = a0;
    struct { char pad[0xB4]; int *unkB4; } *gobj = (void *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x6A) != 0) {
        stage_KillPlayBgAnimation(0x56, 0, 0);
        _ACTWait(0xA);
        stage_KillPlayBgAnimation(0x56, 0, 0x95);
    } else {
        stage_KillPlayBgAnimation(0x56, 0, 0x12C);
    }
    D_004CBD20[1] = (int)func_0020FF58;
    gobj->unkB4 = D_004CBD20;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


typedef struct GObjB4a { char pad[0xB4]; int *unkB4; } GObjB4a;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void actSt03tGirlCamStartChk(volatile int a0);
extern int D_004CBCA0[];

void actSt03tSwitchLUpChk(volatile int a0) {
    int x = a0;
    GObjB4a *gobj = (GObjB4a *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x69) == 0) {
        D_004CBCA0[1] = (int)actSt03tGirlCamStartChk;
        gobj->unkB4 = D_004CBCA0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern void *actSt25aQueenDeadChk(int a0);
extern void actCreateSubThread(int a0, int a1);
extern void actSt02aSecretItem(void);
extern void actSt02aTakiWay(void);
extern void actSt03tSekizoEvent(volatile int a0);
extern int D_004CBCE0[];

void actSt03tSwitchR(volatile int a0) {
    int x = a0;
    GObjB4a *gobj = (GObjB4a *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x5F) != 0) {
        D_004CBCE0[1] = (int)actSt02aSecretItem;
        gobj->unkB4 = D_004CBCE0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
    ((int *)actSt25aQueenDeadChk(0x60C))[0x16C / 4] = 0;
    actCreateSubThread((int)actSt02aTakiWay, 0x15);
    actCreateSubThread((int)actSt03tSekizoEvent, 0x15);
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void *actSt25aQueenDeadChk(int a0);

void actSt03tSwitchRChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x63) == 0) {
        ((int *)actSt25aQueenDeadChk(0x62A))[0x16C / 4] = 0;
    }
}

extern void actSt03tEneChk(volatile int a0);
extern int D_004CBDC0[];

void actSt03tSwitchRUpChk(volatile int a0) {
    int x = a0;
    GObjB4a *gobj = (GObjB4a *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x6C) == 0) {
        D_004CBDC0[1] = (int)actSt03tEneChk;
        gobj->unkB4 = D_004CBDC0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void actSt03tBoxA(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_00178DB0(0x6D)==0){
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
 while(func_00178DB0(0x6D)==0){ _ACTWait(1); }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
extern float D_006297E8;
extern float D_006297EC;

void actSt03tInit(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x6E, 0x57, 0, 0x12, 900.0f, D_006297E8, D_006297EC, 800.0f, D_006297E8, D_006297EC);
}

extern void actSt04aGate(void);
extern void actSt03tWayOffChk(volatile int a0);
extern int D_004CBDE0[];
extern int D_004CBE00[];

void actSt03tGirlCam(volatile int a0) {
    int x = a0;
    GObjB4a *gobj = (GObjB4a *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x6F) == 0) {
        D_004CBDE0[1] = (int)actSt04aGate;
        gobj->unkB4 = D_004CBDE0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        D_004CBE00[1] = (int)actSt03tWayOffChk;
        gobj->unkB4 = D_004CBE00;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


typedef struct GObj_B4 {
    char pad[0xB4];
    int *unkB4;
} GObj_B4;

extern void BoxBarSoundOn(int a0, int a1);
extern void actSt04aGateChk(void);
extern int D_004CBE60[];

void actSt03tSekizo(volatile int a0) {
    int x = a0;
    GObj_B4 *gobj = (GObj_B4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x5F) != 0) {
        D_004CBE60[1] = (int)actSt04aGateChk;
        gobj->unkB4 = D_004CBE60;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern void actSt04aConte06Jimaku(void);
extern int D_004CBEC0[];

void actSt03tWay(volatile int a0) {
    int x = a0;
    GObjB4a *gobj = (GObjB4a *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x67) == 0) {
        D_004CBEC0[1] = (int)actSt04aConte06Jimaku;
        gobj->unkB4 = D_004CBEC0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


void actSt03tEne(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_006145B0[]; extern long long D_006145C0[];
void actSt03tGene(volatile int a0){
 long long b1[2]; long long b2[2];
 long long v0a=D_006145B0[0]; long long v0b=D_006145C0[0];
 int i;
 for(i=0;i<0x32;i++){
  switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006145B0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006145C0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  }
  _ACTWait(1);
 } }

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_006145C0[]; extern long long D_006145B0[];
void actSt03tGirlCamEvent(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006145C0[0]; long long v0b=D_006145B0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006145C0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006145B0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern int D_0062A894;
extern int D_004CBC80[];

void actSt03tGirlCamStartChk(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CBC80;
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", func_0020FD50);

#include "common.h"
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BC78;
extern int D_0062A894;
void actSt03tGirlCamEndChk(volatile int a0) {
    scpDispOnAllWithKind();
    func_00178DD8(0x69);
    scpPlayStart(0x5E, (int)&D_0062BC78, 1, 1, 1);
    while (D_0062BC78 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x54, 1, 0);
    stage_KillPlayBgAnimation(0x55, 1, 0);
    while (func_0012A958(0x55) == 0) { _ACTWait(1); }
    _ACTWait(1);
    AddWayPointTop(0x1A, 1);
    D_0062A894 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSekizoEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", func_0020FF58);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", func_0020FFA0);

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);
void actSt03tEneChk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x3000000) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178DD8(0x6C);
    func_00178DD8(0x6D);
}

void actSt03tWayOnChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern int D_00629DE8;
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void AddWayPointTop(int a0, int a1);
extern void func_00178E08(int a0);
extern void actSt04aGate(void);
extern int D_004CBE20[];

void actSt03tWayOffChk(volatile int a0) {
    struct { char pad[0xB4]; int *unkB4; } *gobj = (void *)((int *)a0)[0x59];
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x4000000) == 0) {
        _ACTWait(1);
    }
    AddWayPointTop(0x35, 1);
    AddWayPointTop(0x37, 1);
    AddWayPointTop(0x38, 1);
    AddWayPointTop(0x39, 1);
    func_00178E08(0x6F);
    D_004CBE20[1] = (int)actSt04aGate;
    gobj->unkB4 = D_004CBE20;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}



/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_00614610;

/* end struct shapes */
