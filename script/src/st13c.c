#include "common.h"

typedef struct ActB4Obj { char pad[0xB0]; int *unkB0; int *unkB4; } ActB4Obj;

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

extern int D_0062A894;
extern int D_00629DE8;
extern void func_001790E8(int a0);
extern int D_004CD710[];

void actSt13cBmg1(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    if (D_00629DE8 != 0) {
        func_001790E8(D_00629DE8);
    }
    *(int *)(gobj + 0xB0) = (int)D_004CD710;
    for (;;) {
        _ACTWait(1);
    }
}

extern int D_00629DE8;
extern void func_001790A8(int a0);
extern void gflagOff(int a0, int a1);
extern void actSt25aQueenBefore(int a0);
void func_00227FA0(volatile int a0){
 func_001790A8(D_00629DE8);
 gflagOff(D_00629DE8, 0x293);
 actSt25aQueenBefore(D_00629DE8);
 gflagOff(D_00629DE8, 0x23A);
 actSt25aQueenBefore(D_00629DE8);
 _ACTWait(0);
}


void actSt13cBmg1Chk(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void scpEffectStart(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614B90[]; extern long long D_00614BA0[];
void actSt13cConte04(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614B90[0]; long long v0b=D_00614BA0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614B90[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614BA0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }

extern void scpEffectStart(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614BA0[]; extern long long D_00614B90[];
void actSt13cConte04Jimaku(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614BA0[0]; long long v0b=D_00614B90[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614BA0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614B90[1]; scpEffectStart((int*)b2,0); break;
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

extern void lt_fade_status(int a0);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern void iosPadDevRead(int a0, int a1);
extern int func_0012A958(int a0);
extern int D_0062BD6C;
extern int D_00629DEC;
extern int D_0062A894;
void actSt13cConte05(volatile int a0){
    lt_fade_status(0x33);
    func_00178DD8(0x4F);
    _ACTWait(0x3C);
    scpPlayStart(0x58, &D_0062BD6C, 1, 1, 1);
    while (D_0062BD6C == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x156, 1, 0);
    while (func_0012AA28(0x156, 0x73, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    while (func_0012AA28(0x156, 0xA5, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x10);
    while (func_0012A958(0x156) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CD830[];
extern void actSt13cHandChk(volatile int a0);
void actSt13cConte05Jimaku(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x4C)!=0){
  stage_KillPlayBgAnimation(0x153,0,0xD2);
 }else{
  stage_KillPlayBgAnimation(0x153,0,0);
 }
 D_004CD830[1]=(int)actSt13cHandChk;
 gobj->unkB4=D_004CD830;
 BoxBarSoundOn((int)a0,0x189);
 _ACTWait(0);
}


extern int D_004CD8D0[];
extern void actSt13cCageDown(volatile int a0);
void actSt13cCageFallEffect(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x4E)==0){
  D_004CD8D0[1]=(int)actSt13cCageDown;
  gobj->unkB4=D_004CD8D0;
  BoxBarSoundOn((int)a0,0x189);
  _ACTWait(0);
 }
}


extern int D_004CD910[];
extern void actSt13cCageFallReady(volatile int a0);
void actSt13cGirlCarryChk(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x4F)==0){
  D_004CD910[1]=(int)actSt13cCageFallReady;
  gobj->unkB4=D_004CD910;
  BoxBarSoundOn((int)a0,0x189);
  _ACTWait(0);
 }
}


extern int D_004CD810[];

void actSt13cHandChk(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CD810;
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", func_00228710);

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

extern int D_004CD8F0[];

void actSt13cCageFallReady(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CD8F0;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct { char pad[0xB0]; void *f_B0; void *unkB4; } BoxObj_st13c;
extern int *D_004CD930[];
extern void actSt13cConte05(volatile int a0);
void func_00228950(volatile int a0) {
    BoxObj_st13c *obj = *(BoxObj_st13c **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CD930[1] = (int *)actSt13cConte05;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004CD930;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

extern void SetWayGroupActive(int a0, int a1);

void actSt13cEnemy(void) {
    if (func_00178DB0(0x107) != 0) {
        SetWayGroupActive(0x16, 1);
        SetWayGroupActive(0x17, 1);
        stage_KillPlayBgAnimation(0x157, 0, 0x59);
    } else {
        SetWayGroupActive(0x14, 1);
        SetWayGroupActive(0x15, 1);
        stage_KillPlayBgAnimation(0x157, 0, 0);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13c", actSt13cEnemyNull);


extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_001790A8(int a0);
extern void gflagOff(int a0, int a1);
extern void scpPlayPosSet(int a0, float f0, float f1, float f2);
extern void func_00178E08(int a0);
extern int D_0062BD70;
extern int D_00271240[];
extern int D_004CD9F0[];
extern void actSt17aDoorUpChk(volatile int a0);
void actSt13cSekizo(volatile int a0){
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    if (func_00178DB0(0x108) == 0) goto B00;
    if (D_00629DE8 == 0) goto B00;
    if (scpSleepSpiderGroupOne(D_00629DE8, 0x3000000) == 0) goto B00;
    scpPlayPosSet(D_00629DE8, -196.0f, -72.0f, 62.0f);
    func_001790A8(D_00629DE8);
    gflagOff(D_00629DE8, 0x202);
B00:
    scpPlayStart(0x59, &D_0062BD70, 1, 1, 1);
    while (D_0062BD70 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x157, 1, 0x5A);
    SetWayGroupActive(0x14, 1);
    SetWayGroupActive(0x15, 1);
    SetWayGroupActive(0x16, 0);
    SetWayGroupActive(0x17, 0);
    func_00178E08(0x107);
    while (func_0012AA28(0x157, 0xB4, 1) == 0) { _ACTWait(1); }
    _ACTWait(1);
    _ACTWait((0x3C - D_00271240[0] * 0xA) / D_00271240[1] * 0xB);
    D_004CD9F0[1] = (int)actSt17aDoorUpChk;
    obj->unkB4 = D_004CD9F0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

