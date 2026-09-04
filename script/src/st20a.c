#include "common.h"

typedef struct ActB4Obj { char pad[0xB0]; int *unkB0; int *unkB4; } ActB4Obj;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);

extern void *D_00629DE4;
extern int D_0062C2C4;
extern void func_001790A8(void *a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void gflagOff(void *a0, int a1);
extern int stage_DispBgAnimation(int a0, int a1);
extern int func_0012A958(int a0);
void actSt20aInit(volatile int a0){
 func_001790A8(D_00629DE4);
 stage_KillPlayBgAnimation(0x229,1,0);
 gflagOff(D_00629DE4,0x12E);
 while(stage_DispBgAnimation(0x229,0x22A)==0){ _ACTWait(1); }
 gflagOff(D_00629DE4,0x12F);
 while(stage_DispBgAnimation(0x22A,0x22B)==0){ _ACTWait(1); }
 gflagOff(D_00629DE4,0x130);
 while(stage_DispBgAnimation(0x22B,0x22C)==0){ _ACTWait(1); }
 gflagOff(D_00629DE4,0x131);
 while(stage_DispBgAnimation(0x22C,0x22D)==0){ _ACTWait(1); }
 gflagOff(D_00629DE4,0x132);
 while(func_0012A958(0x22D)==0){ _ACTWait(1); }
 _ACTWait(1);
 D_0062C2C4=1;
 _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aBridgeDown);

extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern int D_0062BDE4;
extern void actCreateSubThread(void *entry, int a1);
extern void actSt20aBridgeDown(volatile int a0);
extern void *D_00629DE8;
extern int func_0012AA28(int a0, int a1, int a2);
extern void BoySekikaTexScroll(void *a0, int a1);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern void soundSeDefPitchSet(int a0);
extern void func_001790E8(void *a0);
void actSt20aGondolaDown(volatile int a0){
 int h;
 lt_fade_status(0x33);
 func_00178DD8(0x13);
 scpPlayStart(0xE, &D_0062BDE4, 1, 1, 1);
 while(D_0062BDE4==0){ _ACTWait(1); }
 stage_KillPlayBgAnimation(0x3B,1,0);
 stage_KillPlayBgAnimation(0x3C,1,0);
 actCreateSubThread(actSt20aBridgeDown, 0x15);
 func_001790A8(D_00629DE8);
 while(func_0012AA28(0x3B,0xF,0)==0){ _ACTWait(1); }
 _ACTWait(1);
 BoySekikaTexScroll(D_00629DE8, 0xFC);
 while(func_0012AA28(0x3B,0x2D,0)==0){ _ACTWait(1); }
 _ACTWait(1);
 h = soundSeDefPlayWithVolumeRate(0x530,0,0,1);
 while(func_0012A958(0x3B)==0){ _ACTWait(1); }
 _ACTWait(1);
 soundSeDefPitchSet(h);
 while(func_0012A958(0x3B)==0){ _ACTWait(1); }
 _ACTWait(1);
 func_001790E8(D_00629DE8);
}


extern int actSt25aQueenDeadChk(int a0);
extern void ReleaseWeapon(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CE1A0[];
extern int D_004CE1C0[];
extern void actSt20aFence(volatile int a0);
void actSt20aGondolaUp(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x13)==0){
  stage_KillPlayBgAnimation(0x3B,-1,-2);
  *(int*)(actSt25aQueenDeadChk(0x6E)+0x16C)=0;
  ReleaseWeapon(1);
  D_004CE1A0[1]=(int)actSt20aFence;
  gobj->unkB4=D_004CE1A0;
  BoxBarSoundOn((int)a0,0x189);
  _ACTWait(0);
 } else {
  if(func_00178DB0(0x15)==0){
   *(int*)(actSt25aQueenDeadChk(0x6E)+0x16C)=0;
   ReleaseWeapon(1);
   stage_KillPlayBgAnimation(0x3B,0,-1);
   stage_KillPlayBgAnimation(0x3F,0,0);
   D_004CE1C0[1]=(int)actSt20aFence;
   gobj->unkB4=D_004CE1C0;
   BoxBarSoundOn((int)a0,0x189);
   _ACTWait(0);
  }
  *(int*)(actSt25aQueenDeadChk(0x7E)+0x16C)=0;
  stage_KillPlayBgAnimation(0x3F,0,-1);
  stage_KillPlayBgAnimation(0x3D,0,-1);
  stage_KillPlayBgAnimation(0x3E,0,-1);
 }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFence);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceDownChk2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceUpChk2);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aBridge);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aGondola);


extern int D_004CE100[];
extern void actSt22aIntroSub(volatile int a0);
void actSt20aExit(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x12)==0){
  D_004CE100[1]=(int)actSt22aIntroSub;
  gobj->unkB4=D_004CE100;
  BoxBarSoundOn((int)a0,0x189);
  _ACTWait(0);
 }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int AddPluralCameraSet(int a0);
extern int D_004CE140[];
extern void func_00230A78(volatile int a0);
void actSt20aElv(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x13)==0){
  stage_KillPlayBgAnimation(0x3B,0,0);
  stage_KillPlayBgAnimation(0x3F,0,0);
  D_004CE140[1]=(int)func_00230A78;
  gobj->unkB4=D_004CE140;
  BoxBarSoundOn((int)a0,0x189);
  _ACTWait(0);
 }
 if(func_00178DB0(0x15)==0){
  if(func_00178DB0(0x13)!=0){
   AddPluralCameraSet(0x25);
  }
 }
}


extern int D_004CE180[];
extern void func_00230B70(volatile int a0);
void actSt20aEne(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x15)==0){
  D_004CE180[1]=(int)func_00230B70;
  gobj->unkB4=D_004CE180;
  BoxBarSoundOn((int)a0,0x189);
  _ACTWait(0);
 }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void Generator_Mask(int a0);
extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void Generator_Call(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178E08(int a0);
extern int D_0062C2C8;

void actSt20aEnemy1(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    D_0062C2C8 = a0;
    Generator_Mask(a0);
    while (func_00178DB0(0x16) == 0) {
        _ACTWait(1);
    }
    Generator_Call(actSt25aQueenDeadChk(0x86));
    _ACTWait(0xB4);
    Generator_Call(a0);
    scpDispOnAllWithKind();
    func_00178E08(0x16);
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);

void actSt20aEnemy2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_00178DB0(0x18) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);
}

#include "common.h"
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int a0, int a1, int a2, int a3, int a4, float f0, float f1, float f2, float f3, float f4, float f5);
extern int func_00178DB0(int a0);
extern void SetWayGroupActive(int a0, int a1);
void actSt20aEnemy3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x1D, 0x40, 0, 0x11, -300.0f, -100.0f, 100.0f, -300.0f, -100.0f, 0.0f);
    if (func_00178DB0(0x1D) == 0) {
        SetWayGroupActive(2, 0);
    } else {
        SetWayGroupActive(2, 1);
    }
}

extern int D_004CE1E0[];
extern void func_00230C10(volatile int a0);
void actSt20aBridgeMain(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x1D)==0){
  D_004CE1E0[1]=(int)func_00230C10;
  gobj->unkB4=D_004CE1E0;
  BoxBarSoundOn((int)a0,0x189);
  _ACTWait(0);
 }
}


extern int D_004CE260[];
extern void actSt20aBridge(volatile int a0);
void actSt20aBridgeSwitch(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x1A)==0){
  D_004CE260[1]=(int)actSt20aBridge;
  gobj->unkB4=D_004CE260;
  BoxBarSoundOn((int)a0,0x189);
  _ACTWait(0);
 }
}


extern int D_004CE200[];
extern void actSt20aFenceUpChk2(volatile int a0);
void actSt20aGondolaMain(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x1A)==0){
  D_004CE200[1]=(int)actSt20aFenceUpChk2;
  gobj->unkB4=D_004CE200;
  BoxBarSoundOn((int)a0,0x189);
  _ACTWait(0);
 }
}


extern int D_004CE280[];
extern void func_00230EC8(volatile int a0);
void actSt20aGondolaSwitch(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0x1C)==0){
  if(func_00178DB0(0x1A)==0){
   D_004CE280[1]=(int)func_00230EC8;
   gobj->unkB4=D_004CE280;
   BoxBarSoundOn((int)a0,0x189);
   _ACTWait(0);
  }
 }
}

