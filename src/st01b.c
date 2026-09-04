#include "common.h"

typedef struct { long long a, b; } WpData16;

typedef struct ActB4Obj {
    char pad[0xC4];
    int *unkC4;
} ActB4Obj;

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0E90[];
extern WpData16 D_0061B9A0;
extern void _ACTWait(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt01bEneChk(volatile int a0);
extern void actSt01bWay(volatile int a0);
extern int func_0012AA80(int a0);
extern void scpWakeupItemWithBoundary(float a0, float a1, float a2, float a3);
extern int scpKillSpiderGroup(int a0, int a1);
extern void soundSeDefPitchSet(int a0);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt01bInit(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    WpData16 buf;
    int r;
    while (scpKillSpiderGroup(a0, 0x3000000) == 0) { _ACTWait(1); }
    _ACTWait(0xF);
    actCreateSubThread((void *)actSt01bWay, 0x15);
    stage_KillPlayBgAnimation(0x50, 1, 0);
    scpWakeupItemWithBoundary(-6.0f, -221.0f, 1504.0f, 100.0f);
    _ACTWait(1);
    buf = D_0061B9A0;
    soundSeDefPlayWithVolumeRate(0x4AC, 0, &buf, 1);
    _ACTWait(0x1E);
    r = soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x3C);
    soundSeDefPitchSet(r);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012AA80(0x50) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_004D0E90[1] = (int)actSt01bEneChk;
    obj->unkC4 = D_004D0E90;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEneChk);

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0ED0[];
extern int D_004D0EF0[];
extern int D_00631AE4;
extern int D_00631AE8;
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt01bEne(volatile int a0);
extern void actSt01bSekizo(volatile int a0);
extern int scpTriggerBall(int a0, int a1, float f0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt01bFloorChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (scpTriggerBall(a0, D_00631AE4, 200.0f) != 0) goto ene;
    if (D_00631AE8 == 0) goto sekizo;
    if (scpTriggerBall(a0, D_00631AE8, 400.0f) == 0) goto sekizo;
ene:
    stage_KillPlayBgAnimation(0x4F, 0, 0);
    _ACTWait(0x3C);
    D_004D0ED0[1] = (int)actSt01bEne;
    gobj->unkC4 = D_004D0ED0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
    return;
sekizo:
    stage_KillPlayBgAnimation(0x4E, 0, 0);
    D_004D0EF0[1] = (int)actSt01bSekizo;
    gobj->unkC4 = D_004D0EF0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bSekizo);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEne);

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0E10[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt00aDoor1Event(volatile int a0);
extern int func_0017B230(int a0);

void actSt01bEnemy1(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x27) == 0) {
        D_004D0E10[1] = (int)actSt00aDoor1Event;
        gobj->unkC4 = D_004D0E10;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);

void actSt01bEnemy2(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x25)==0){ _ACTWait(1); }
 _ACTWait(0x32); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); }

void actSt01bEnemy3(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_0017B230(0x25)==0){ _ACTWait(1); }
 _ACTWait(0xA0);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x1E);
 Generator_Call(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy4);

extern int D_004D0DF0[];
extern void actSt01bEnemy6(volatile int a0);

void actSt01bEnemy5(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x27) == 0) {
        D_004D0DF0[1] = (int)actSt01bEnemy6;
        gobj->unkC4 = D_004D0DF0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_00631AE8;
extern void func_0017B258(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actSt01bEnemy6(volatile int a0) {
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00631AE8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0x27);
}

void actSt01bFloor(int x) {
    volatile int local = x;
}

extern long long D_0061B9B0[];
extern long long D_0061B9C0[];
extern void scpEffectStart(int *buf, int a1);

void actSt01bWay(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061B9B0[0]; long long v0b=D_0061B9C0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061B9B0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061B9C0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }

void actSt01bEnd(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061B9C0[0]; long long v0b=D_0061B9B0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061B9C0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061B9B0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }

void actSt01bSekizoEvent(int x) {
    volatile int local = x;
}

extern long long D_0061B9E0[];
extern long long D_0061B9F0[];

void actSt01bFloorEvent(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061B9E0[0]; long long v0b=D_0061B9F0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061B9E0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061B9F0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }

void actSt01bWayOnChk(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061B9F0[0]; long long v0b=D_0061B9E0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061B9F0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061B9E0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }

extern void SetWayGroupActive(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt01bWayOffChk(void) {
    if (func_0017B230(0x42) == 0) {
        SetWayGroupActive(0x2, 0);
        stage_KillPlayBgAnimation(0xA2, 0, 0);
        stage_KillPlayBgAnimation(0x9F, 0, 0);
    } else {
        SetWayGroupActive(0x2, 1);
        stage_KillPlayBgAnimation(0xA2, 0, -1);
        stage_KillPlayBgAnimation(0x9F, 0, -1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st01b", func_00210DF0);

INCLUDE_ASM("asm/nonmatchings/src/st01b", func_00210F20);

INCLUDE_ASM("asm/nonmatchings/src/st01b", func_002110F0);

