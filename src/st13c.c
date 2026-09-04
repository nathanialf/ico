#include "common.h"

extern int D_004D2D60[];

typedef struct { char pad[0xC0]; void *f_B0; void *unkB4; } BoxObj_st13c;

struct CFS { long long a, b; };

typedef struct ActB4Obj { char pad[0xC0]; int *unkB0; int *unkB4; } ActB4Obj;


extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation();
extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);

void actSt13cInit(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_0017B230(0x4B)==0){ _ACTWait(1); }
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
 while(func_0017B230(0x4B)==0){ _ACTWait(1); }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

extern int D_004D2B80[];
extern int D_00631AE8;
extern int D_006325B4;
extern void func_0017B568(int a0);

void actSt13cBmg1(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_006325B4 = 0;
    if (D_00631AE8 != 0) {
        func_0017B568(D_00631AE8);
    }
    *(int *)(gobj + 0xC0) = (int)D_004D2B80;
    for (;;) {
        _ACTWait(1);
    }
}

extern void func_0017B528(int a0);
extern void gflagOff(int a0, int a1);
extern void actSt25aQueenBefore(int a0);
extern int D_00631AE8;

void func_0022B5E8(volatile int a0) {
    func_0017B528(D_00631AE8);
    gflagOff(D_00631AE8, 0x291);
    actSt25aQueenBefore(D_00631AE8);
    gflagOff(D_00631AE8, 0x239);
    actSt25aQueenBefore(D_00631AE8);
    _ACTWait(0);
}

void actSt13cBmg1Chk(int x) {
    volatile int local = x;
}

extern long long D_0061C070[];
extern long long D_0061C080[];
extern void scpEffectStart(int *buf, int a1);

void actSt13cConte04(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061C070[0]; long long v0b=D_0061C080[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061C070[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061C080[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }

void actSt13cConte04Jimaku(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061C080[0]; long long v0b=D_0061C070[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061C080[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061C070[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }

extern int D_00631AE8;
extern void _ACTWait(int a0);
extern void func_0017B258(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actSt13cCage1stDownDemoCancel(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00631AE8, 0x2000000) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_0017B258(0x4A);
    func_0017B258(0x4B);
}

void actSt13cCage1stDown(void) {
    if (func_0017B230(0x4F) == 0) {
        stage_KillPlayBgAnimation(0x157, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x157, 0, -1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageFall);

extern struct CFS D_0061C090;
extern void func_0017BF78(int a0, int a1, int a2, int a3, int a4, float f0, float f1, float f2, float f3, float f4, float f5);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);

void actSt13cCageFallChk(volatile int a0) {
    struct CFS buf;
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    buf = D_0061C090;
    soundSeDefPlayWithVolumeRate(0x527, 0, &buf, 1);
    soundSeDefPlayWithVolumeRate(0x528, 0, &buf, 1);
    soundSeDefPlayWithVolumeRate(0x529, 0, &buf, 1);
    func_0017BF78(a0, 0x4D, 0x155, 0, 0x12, -1350.0f, -100.0f, 1515.0f, -1450.0f, -100.0f, 1515.0f);
}

extern int D_00631AEC;
extern int D_006325B4;
extern int D_00633A64;
extern int func_0012AA80(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void iosPadDevRead(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt13cConte05(volatile int a0){
    lt_fade_status(0x33);
    func_0017B258(0x4F);
    _ACTWait(0x3C);
    scpPlayStart(0x58, &D_00633A64, 1, 1, 1);
    while (D_00633A64 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x157, 1, 0);
    while (func_0012AB50(0x157, 0x73, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x11);
    while (func_0012AB50(0x157, 0xA5, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x10);
    while (func_0012AA80(0x157) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D2CA0[];
extern void actSt13cHandChk(volatile int a0);

void actSt13cConte05Jimaku(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x4C)!=0){
  stage_KillPlayBgAnimation(0x154,0,0xD2);
 }else{
  stage_KillPlayBgAnimation(0x154,0,0);
 }
 D_004D2CA0[1]=(int)actSt13cHandChk;
 gobj->unkB4=D_004D2CA0;
 BoxBarSoundOn((int)a0,0x18D);
 _ACTWait(0);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D2D40[];
extern void func_0022BEE0(volatile int a0);

void actSt13cCageFallEffect(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x4E)==0){
  D_004D2D40[1]=(int)func_0022BEE0;
  gobj->unkB4=D_004D2D40;
  BoxBarSoundOn((int)a0,0x18D);
  _ACTWait(0);
 }
}

extern int D_004D2D80[];
extern void func_0022BF60(volatile int a0);

void actSt13cGirlCarryChk(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x4F)==0){
  D_004D2D80[1]=(int)func_0022BF60;
  gobj->unkB4=D_004D2D80;
  BoxBarSoundOn((int)a0,0x18D);
  _ACTWait(0);
 }
}

extern int D_004D2C80[];

void actSt13cHandChk(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_006325B4 = 0;
    *(int *)(gobj + 0xC0) = (int)D_004D2C80;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct St13cBox { char pad[0xC0]; void *field_B0; void *field_B4; } St13cBox;
extern int *D_004D2CC0[];
extern int *D_004D2CE0[];
extern void actSt13cHandJimaku(void);
extern void actSt13cCageFall(void);
extern int func_0017B230(int a0);
extern int D_006325B4;

void func_0022BD58(volatile int a0) {
    St13cBox *gobj = (St13cBox *)*(int *)(a0 + 0x164);
    D_006325B4 = 1;
    gobj->field_B0 = 0;
    if (func_0017B230(0x4C) != 0) {
        D_004D2CC0[1] = (int *)actSt13cHandJimaku;
        gobj->field_B4 = D_004D2CC0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
    D_004D2CE0[1] = (int *)actSt13cCageFall;
    gobj->field_B4 = D_004D2CE0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cHandJimaku);

void actSt13cSleep(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022BEE0);

typedef struct KSub_bf60 { char pad[0xC0]; int unkC0; } KSub_bf60;


void func_0022BF60(volatile int a0) {
    KSub_bf60 *s = *(KSub_bf60 **)(a0 + 0x164);
    s->unkC0 = (int)D_004D2D60;
    for (;;) {
        _ACTWait(1);
    }
}

extern int *D_004D2DA0[];

void func_0022BF90(volatile int a0) {
    BoxObj_st13c *obj = *(BoxObj_st13c **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D2DA0[1] = (int *)actSt13cConte05;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004D2DA0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022BFE8);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022C060);
ASM_LIT4_SLOT(D_00631648, -705.0f);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022C2D0);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022C4C0);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022C638);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022C7C0);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022C8D8);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022C9F0);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022CAC8);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022CB70);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022CBD8);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022CC88);
ASM_LIT4_SLOT(D_0063164C, 1274.0f);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022CCF0);

