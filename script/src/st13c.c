#include "common.h"

extern int actInitialize(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void actSt13cInit(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_00178DB0(0x4B)==0){ _ACTWait(1); }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

void actSt13cEnd(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_00178DB0(0x4B)==0){ _ACTWait(1); }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cBmg1);

void actSt13cBmg1Chk(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614B90[]; extern long long D_00614BA0[];
void actSt13cConte04(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614B90[0]; long long v0b=D_00614BA0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614B90[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614BA0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614BA0[]; extern long long D_00614B90[];
void actSt13cConte04Jimaku(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614BA0[0]; long long v0b=D_00614B90[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614BA0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614B90[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);
void actSt13cCage1stDownDemoCancel(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178DD8(0x4A);
    func_00178DD8(0x4B);
}

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt13cCage1stDown(void) {
    if (func_00178DB0(0x4F) == 0) {
        stage_KillPlayBgAnimation(0x156, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x156, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cCageFall);

#include "common.h"
struct CFS { long long a, b; };
extern struct CFS D_00614BB0;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern void func_00179710(int a0, int a1, int a2, int a3, int a4, float f0, float f1, float f2, float f3, float f4, float f5);
extern float D_0062992C, D_00629928, D_00629930;
void actSt13cCageFallChk(volatile int a0) {
    struct CFS buf;
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    buf = D_00614BB0;
    soundSeDefPlayWithVolumeRate(0x527, 0, &buf, 1);
    soundSeDefPlayWithVolumeRate(0x528, 0, &buf, 1);
    soundSeDefPlayWithVolumeRate(0x529, 0, &buf, 1);
    func_00179710(a0, 0x4D, 0x154, 0, 0x12, D_0062992C, -100.0f, D_00629928, D_00629930, -100.0f, D_00629928);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cConte05);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cConte05Jimaku);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cCageFallEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cGirlCarryChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cHandChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cHandJimaku);

void actSt13cSleep(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void lt_fade_status(int a0);
extern int func_0012A958(int a0);
extern int D_0062A894;
void actSt13cCageDown(volatile int a0){
 lt_fade_status(0x33); func_00178DD8(0x4E); D_0062A894=1; _ACTWait(1);
 stage_KillPlayBgAnimation(0x155,1,0);
 while(func_0012A958(0x155)==0) _ACTWait(1); _ACTWait(1); lt_fade_status(0x32); D_0062A894=0; }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cCageFallReady);

extern void AddWayPointTop(int a0, int a1);

void actSt13cEnemy(void) {
    if (func_00178DB0(0x107) != 0) {
        AddWayPointTop(0x16, 1);
        AddWayPointTop(0x17, 1);
        stage_KillPlayBgAnimation(0x157, 0, 0x59);
    } else {
        AddWayPointTop(0x14, 1);
        AddWayPointTop(0x15, 1);
        stage_KillPlayBgAnimation(0x157, 0, 0);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cEnemyNull);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cSekizo);
