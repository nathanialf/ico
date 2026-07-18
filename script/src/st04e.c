#include "common.h"

typedef struct ActB4Obj { char pad[0xB4]; int *unkB4; } ActB4Obj;
struct SndBuf { long long a, b; };
extern struct SndBuf D_006148C0;
extern struct SndBuf D_00614890;
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void BoxBarSoundOn(int a0, int a1);
extern int scpKillSpiderGroup(int a0, int a1);
extern void actCreateSubThread(void *fn, int a1);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern int func_0012A958(int a0);
extern void func_002171A8(int a0);
extern void actSt04eWaterMain(int a0);
extern int D_004CC340[];
void actSt04eWater(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    struct SndBuf buf;
    while (scpKillSpiderGroup(a0, 0x1000000) == 0) { _ACTWait(1); }
    _ACTWait(0xF);
    actCreateSubThread(func_002171A8, 0x15);
    stage_KillPlayBgAnimation(0xE1, 1, 0);
    buf = D_00614890;
    soundSeDefPlayWithVolumeRate(0x4AC, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012A958(0xE1) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_004CC340[1] = (int)actSt04eWaterMain;
    obj->unkB4 = D_004CC340;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWaterMain);


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void BoxBarSoundOn(int a0, int a1);
extern void actSt04eWaterFlagOn(int a0);
extern void actSt04eWaterStop(int a0);
extern int D_004CC380[]; extern int D_004CC3A0[];
extern int D_00629DE4; extern int D_00629DE8;
void actSt04eWaterSwitch(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne(a0, D_00629DE4, 400.0f) != 0) goto flagon;
    if (D_00629DE8 == 0) goto stop;
    if (scpSleepEnemyOne(a0, D_00629DE8, 400.0f) == 0) goto stop;
flagon:
    stage_KillPlayBgAnimation(0xE4, 0, 0);
    _ACTWait(0x3C);
    D_004CC380[1] = (int)actSt04eWaterFlagOn;
    gobj->unkB4 = D_004CC380;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
    return;
stop:
    stage_KillPlayBgAnimation(0xE3, 0, 0);
    D_004CC3A0[1] = (int)actSt04eWaterStop;
    gobj->unkB4 = D_004CC3A0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWaterStop);


extern int scpKillSpiderGroup(int a0, int a1);
extern void actCreateSubThread(void *fn, int a1);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern int func_0012A958(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void func_00217458(volatile int a0);
extern void actSt04eWaterStop(int a0);
extern int D_004CC3E0[];
void actSt04eWaterFlagOn(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    struct SndBuf buf;
    while (scpKillSpiderGroup(a0, 0x2000000) != 0) { _ACTWait(1); }
    _ACTWait(0xF);
    actCreateSubThread(func_00217458, 0x15);
    stage_KillPlayBgAnimation(0xE4, 1, 0);
    buf = D_006148C0;
    soundSeDefPlayWithVolumeRate(0x4AC, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012A958(0xE4) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_004CC3E0[1] = (int)actSt04eWaterStop;
    obj->unkB4 = D_004CC3E0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


void func_00217198(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_002171A8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217288);

void func_00217368(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_006148D0[]; extern long long D_006148E0[];
void func_00217378(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006148D0[0]; long long v0b=D_006148E0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006148D0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006148E0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_006148E0[]; extern long long D_006148D0[];
void func_00217458(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006148E0[0]; long long v0b=D_006148D0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006148E0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006148D0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217538);

typedef struct { char pad[0xB0]; int *unkB0; } ActB0Obj;
extern int D_004CC400[];

void func_002175E0(volatile int a0) {
    ActB0Obj *gobj = *(ActB0Obj **)(a0 + 0x164);
    gobj->unkB0 = D_004CC400;
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217610);

#include "common.h"
extern void lt_fade_status(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void func_00217730();
extern void scpDispOnAllWithKind(void);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern void AddWayPointTop(int a0, int a1);
extern int D_0062A894;
void func_00217668(volatile int a0) {
    lt_fade_status(0x33);
    actCreateSubThread(func_00217730, 0x15);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0xE9, 1, 0);
    stage_KillPlayBgAnimation(0xE8, -1, -2);
    while (func_0012A958(0xE9) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x495) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x494) + 0x16C) = 0;
    D_0062A894 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
    AddWayPointTop(5, 1);
}

extern int D_00271240[];
extern int func_0025F4F0(int a0);
extern int func_0025EF78(int a0, long long a1);
extern int func_0025F5A8(int a0);
extern void func_00178DD8(int a0);
void func_00217730(volatile int a0) {
    int q = (0x3C - D_00271240[0] * 0xA) / D_00271240[1];
    int v = func_0025F4F0(q);
    v = func_0025EF78(v, 0x4026000000000000LL);
    v = func_0025F5A8(v);
    _ACTWait(v);
    func_00178DD8(0xCD);
}


extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);

void func_002177A8(void) {
    if (func_00178DB0(0xC0) == 0) stage_KillPlayBgAnimation(0xCD, 0, 0); else stage_KillPlayBgAnimation(0xCD, 0, -1);
    if (func_00178DB0(0xC1) == 0) stage_KillPlayBgAnimation(0xCE, 0, 0); else stage_KillPlayBgAnimation(0xCE, 0, -1);
    if (func_00178DB0(0xC2) == 0) stage_KillPlayBgAnimation(0xCF, 0, 0); else stage_KillPlayBgAnimation(0xCF, 0, -1);
    if (func_00178DB0(0xC3) == 0) stage_KillPlayBgAnimation(0xD0, 0, 0); else stage_KillPlayBgAnimation(0xD0, 0, -1);
    if (func_00178DB0(0xC4) == 0) stage_KillPlayBgAnimation(0xD1, 0, 0); else stage_KillPlayBgAnimation(0xD1, 0, -1);
    if (func_00178DB0(0xC5) == 0) stage_KillPlayBgAnimation(0xD2, 0, 0); else stage_KillPlayBgAnimation(0xD2, 0, -1);
    if (func_00178DB0(0xC6) == 0) stage_KillPlayBgAnimation(0xD3, 0, 0); else stage_KillPlayBgAnimation(0xD3, 0, -1);
    if (func_00178DB0(0xA9) == 0) AddWayPointTop(1, 0); else AddWayPointTop(1, 1);
    if (func_00178DB0(0xA3) == 0) stage_KillPlayBgAnimation(0xC3, 0, 0); else stage_KillPlayBgAnimation(0xC3, 0, -1);
    if (func_00178DB0(0xA4) == 0) stage_KillPlayBgAnimation(0xC4, 0, 0); else stage_KillPlayBgAnimation(0xC4, 0, -1);
}

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);

void func_00217990(void) {
    if (func_00178DB0(0xA1) == 0) {
        stage_KillPlayBgAnimation(0xC6, 0, 0);
        stage_KillPlayBgAnimation(0xE5, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xC6, 0, -1);
        stage_KillPlayBgAnimation(0xE5, 0, -1);
    }
    if (func_00178DB0(0xA3) == 0) {
        stage_KillPlayBgAnimation(0xC3, 0, 0);
        AddWayPointTop(3, 0);
    } else {
        stage_KillPlayBgAnimation(0xC3, 0, -1);
        AddWayPointTop(3, 1);
    }
    if (func_00178DB0(0xA4) == 0) {
        stage_KillPlayBgAnimation(0xC4, 0, 0);
        AddWayPointTop(4, 0);
    } else {
        stage_KillPlayBgAnimation(0xC4, 0, -1);
        AddWayPointTop(4, 1);
    }
    if (func_00178DB0(0xC0) == 0) stage_KillPlayBgAnimation(0xCD, 0, 0); else stage_KillPlayBgAnimation(0xCD, 0, -1);
    if (func_00178DB0(0xC1) == 0) stage_KillPlayBgAnimation(0xCE, 0, 0); else stage_KillPlayBgAnimation(0xCE, 0, -1);
    if (func_00178DB0(0xC2) == 0) stage_KillPlayBgAnimation(0xCF, 0, 0); else stage_KillPlayBgAnimation(0xCF, 0, -1);
    if (func_00178DB0(0xC3) == 0) stage_KillPlayBgAnimation(0xD0, 0, 0); else stage_KillPlayBgAnimation(0xD0, 0, -1);
    if (func_00178DB0(0xC4) == 0) stage_KillPlayBgAnimation(0xD1, 0, 0); else stage_KillPlayBgAnimation(0xD1, 0, -1);
    if (func_00178DB0(0xC5) == 0) stage_KillPlayBgAnimation(0xD2, 0, 0); else stage_KillPlayBgAnimation(0xD2, 0, -1);
    if (func_00178DB0(0xC6) == 0) stage_KillPlayBgAnimation(0xD3, 0, 0); else stage_KillPlayBgAnimation(0xD3, 0, -1);
    if (func_00178DB0(0x91) != 0 && func_00178DB0(0x9B) == 0) {
        stage_KillPlayBgAnimation(0xE0, 0, -1);
    }
    if (func_00178DB0(0x91) == 0 || func_00178DB0(0x9B) != 0) {
        stage_KillPlayBgAnimation(0xE0, 0, 0);
    }
    if (func_00178DB0(0xAB) != 0) {
        stage_KillPlayBgAnimation(0xC7, 0, 0xC8);
    } else {
        stage_KillPlayBgAnimation(0xC7, 0, 0);
    }
}

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_00217C58(void) {
    if (func_00178DB0(0xCD) == 0) {
        AddWayPointTop(5, 0);
    } else {
        AddWayPointTop(5, 1);
    }
    if (func_00178DB0(0xA3) == 0) {
        stage_KillPlayBgAnimation(0xC3, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xC3, 0, -1);
    }
    if (func_00178DB0(0xA4) == 0) {
        stage_KillPlayBgAnimation(0xC4, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xC4, 0, -1);
    }
}

extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BCC8;
extern int D_00271240[];
extern int D_0062A894;
void func_00217CF0(volatile int a0) {
    lt_fade_status(0x33);
    func_00178DD8(0x9E);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    scpPlayStart(0x50, (int)&D_0062BCC8, 1, 1, 1);
    while (D_0062BCC8 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0xB8, 1, 0);
    while (func_0012A958(0xB8) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x3FF) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x400) + 0x16C) = 1;
    _ACTWait((0x3C - D_00271240[0] * 0xA) / D_00271240[1] * 6);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BCCC;
extern int D_00271240[];
extern int D_0062A894;
void func_00217E18(volatile int a0) {
    lt_fade_status(0x33);
    func_00178DD8(0x9F);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    scpPlayStart(0x50, (int)&D_0062BCCC, 1, 1, 1);
    while (D_0062BCCC == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0xB9, 1, 0);
    while (func_0012A958(0xB9) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x451) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x452) + 0x16C) = 1;
    _ACTWait((0x3C - D_00271240[0] * 0xA) / D_00271240[1] * 6);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


#include "common.h"
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BCD0;
extern int D_0062A894;
void func_00217F40(volatile int a0) {
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_00178DD8(0xA0);
    _ACTWait(0x3C);
    scpPlayStart(0x50, (int)&D_0062BCD0, 1, 1, 1);
    while (D_0062BCD0 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0xBA, 1, 0);
    while (func_0012A958(0xBA) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x453) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x454) + 0x16C) = 1;
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}
