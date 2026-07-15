#include "common.h"

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
typedef struct { long long a, b; } WpData16;

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int scpKillSpiderGroup(int a0, int a1);
extern void actCreateSubThread(void *fn, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void func_0017BF50(float a0, float a1, float a2, float a3);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern void soundSeDefPitchSet(int a0);
extern int func_0012A958(int a0);
extern WpData16 D_00614530;
extern int D_004CBAA0[];
extern void actSt01bWay(volatile int a0);
extern void actSt01bEneChk(volatile int a0);

void actSt01bInit(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    WpData16 buf;
    int r;
    while (scpKillSpiderGroup(a0, 0x3000000) == 0) { _ACTWait(1); }
    _ACTWait(0xF);
    actCreateSubThread((void *)actSt01bWay, 0x15);
    stage_KillPlayBgAnimation(0x4F, 1, 0);
    func_0017BF50(-6.0f, -221.0f, 1504.0f, 100.0f);
    _ACTWait(1);
    buf = D_00614530;
    soundSeDefPlayWithVolumeRate(0x4AC, 0, &buf, 1);
    _ACTWait(0x1E);
    r = soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x3C);
    soundSeDefPitchSet(r);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012A958(0x4F) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_004CBAA0[1] = (int)actSt01bEneChk;
    obj->unkB4 = D_004CBAA0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int D_004CBAC0[];
extern void actSt01bEnd(volatile int a0);
extern void actSt01bInit(volatile int a0);
INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bEneChk);


extern int scpSleepEnemyOne(int a0, int a1, float f0);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_004CBAE0[];
extern int D_004CBB00[];
extern void actSt01bEne(volatile int a0);
extern void actSt01bSekizo(volatile int a0);
void actSt01bFloorChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne(a0, D_00629DE4, 200.0f) != 0) goto ene;
    if (D_00629DE8 == 0) goto sekizo;
    if (scpSleepEnemyOne(a0, D_00629DE8, 400.0f) == 0) goto sekizo;
ene:
    stage_KillPlayBgAnimation(0x4E, 0, 0);
    _ACTWait(0x3C);
    D_004CBAE0[1] = (int)actSt01bEne;
    gobj->unkB4 = D_004CBAE0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
    return;
sekizo:
    stage_KillPlayBgAnimation(0x4D, 0, 0);
    D_004CBB00[1] = (int)actSt01bSekizo;
    gobj->unkB4 = D_004CBB00;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bEne);


extern int func_00178DB0(int a0);
extern int D_004CBA20[];
extern void actSt00aDoor1Event(volatile int a0);
void actSt01bEnemy1(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x27) == 0) {
        D_004CBA20[1] = (int)actSt00aDoor1Event;
        gobj->unkB4 = D_004CBA20;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


void actSt01bEnemy2(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x25)==0){ _ACTWait(1); }
 _ACTWait(0x32); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); }

extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void actSt01bEnemy3(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_00178DB0(0x25)==0){ _ACTWait(1); }
 _ACTWait(0xA0);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x1E);
 Generator_Call(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bEnemy4);


extern int D_004CBA00[];
extern void actSt01bEnemy6(volatile int a0);
void actSt01bEnemy5(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x27) == 0) {
        D_004CBA00[1] = (int)actSt01bEnemy6;
        gobj->unkB4 = D_004CBA00;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern void _ACTWait(int a0);
extern int D_00629DE8;
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);

void actSt01bEnemy6(volatile int a0) {
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x27);
}

void actSt01bFloor(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614540[]; extern long long D_00614550[];
void actSt01bWay(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614540[0]; long long v0b=D_00614550[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614540[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614550[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614550[]; extern long long D_00614540[];
void actSt01bEnd(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614550[0]; long long v0b=D_00614540[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614550[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614540[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

void actSt01bSekizoEvent(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614570[]; extern long long D_00614580[];
void actSt01bFloorEvent(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614570[0]; long long v0b=D_00614580[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614570[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614580[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614580[]; extern long long D_00614570[];
void actSt01bWayOnChk(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614580[0]; long long v0b=D_00614570[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614580[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614570[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt01bWayOffChk(void) {
    if (func_00178DB0(0x42) == 0) {
        AddWayPointTop(0x2, 0);
        stage_KillPlayBgAnimation(0xA1, 0, 0);
        stage_KillPlayBgAnimation(0x9E, 0, 0);
    } else {
        AddWayPointTop(0x2, 1);
        stage_KillPlayBgAnimation(0xA1, 0, -1);
        stage_KillPlayBgAnimation(0x9E, 0, -1);
    }
}

extern void lt_fade_status(int a0);
extern int func_0017A040(int a0);
extern void func_0017A008(int a0);
extern int func_0012AA28(int a0, int a1, int a2);
extern int D_0062A894;
void func_0020E210(volatile int a0) {
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    goto test;
loop:
    _ACTWait(1);
test:
    if (func_00178DB0(0x42) == 0) goto loop;
    if (scpSleepSpiderGroupOne(D_00629DE4, 0x1000000) == 0) goto loop;
    if (scpSleepSpiderGroupOne(D_00629DE8, 0x1000000) != 0) goto done;
    if (scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) == 0) goto loop;
done:
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_0017A040(0xD57);
    _ACTWait(0x1E);
    func_00178DD8(0x40);
    func_00178DD8(0x41);
    stage_KillPlayBgAnimation(0xA0, 1, 0);
    while (func_0012AA28(0xA0, 0x5A, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    while (func_0012A958(0xA0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    func_0017A008(0xD57);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", func_0020E340);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
void func_0020E510(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1);
    func_00179710(a0, 0x3D, 0x9C, 0, 0x12, 1000.0f, 528.0f, -150.0f, 1000.0f, 528.0f, -100.0f);
}
