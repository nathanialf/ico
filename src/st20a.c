#include "common.h"

typedef struct ActB4Obj { char pad[0xC0]; int *unkC0; int *unkC4; } ActB4Obj;

extern void *D_00631AE4;
extern int D_00633FC4;
extern void _ACTWait(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B528(void *a0);
extern void gflagOff(void *a0, int a1);
extern int stage_DispBgAnimation(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt20aInit(volatile int a0){
 func_0017B528(D_00631AE4);
 stage_KillPlayBgAnimation(0x22A,1,0);
 gflagOff(D_00631AE4,0x12E);
 while(stage_DispBgAnimation(0x22A,0x22B)==0){ _ACTWait(1); }
 gflagOff(D_00631AE4,0x12F);
 while(stage_DispBgAnimation(0x22B,0x22C)==0){ _ACTWait(1); }
 gflagOff(D_00631AE4,0x130);
 while(stage_DispBgAnimation(0x22C,0x22D)==0){ _ACTWait(1); }
 gflagOff(D_00631AE4,0x131);
 while(stage_DispBgAnimation(0x22D,0x22E)==0){ _ACTWait(1); }
 gflagOff(D_00631AE4,0x132);
 while(func_0012AA80(0x22E)==0){ _ACTWait(1); }
 _ACTWait(1);
 D_00633FC4=1;
 _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st20a", actSt20aEnd);

INCLUDE_ASM("asm/nonmatchings/src/st20a", actSt20aBridgeDown);

extern void BoySekikaTexScroll(void *a0, int a1);
extern void *D_00631AE8;
extern int D_00633ADC;
extern void actCreateSubThread(void *entry, int a1);
extern void actSt20aBridgeDown(volatile int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern void func_0017B568(void *a0);
extern void lt_fade_status(int a0);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void soundSeDefPitchSet(int a0);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);

void actSt20aGondolaDown(volatile int a0){
 int h;
 lt_fade_status(0x33);
 func_0017B258(0x13);
 scpPlayStart(0xE, &D_00633ADC, 1, 1, 1);
 while(D_00633ADC==0){ _ACTWait(1); }
 stage_KillPlayBgAnimation(0x3B,1,0);
 stage_KillPlayBgAnimation(0x3C,1,0);
 actCreateSubThread(actSt20aBridgeDown, 0x15);
 func_0017B528(D_00631AE8);
 while(func_0012AB50(0x3B,0xF,0)==0){ _ACTWait(1); }
 _ACTWait(1);
 BoySekikaTexScroll(D_00631AE8, 0xFE);
 while(func_0012AB50(0x3B,0x2D,0)==0){ _ACTWait(1); }
 _ACTWait(1);
 h = soundSeDefPlayWithVolumeRate(0x530,0,0,1);
 while(func_0012AA80(0x3B)==0){ _ACTWait(1); }
 _ACTWait(1);
 soundSeDefPitchSet(h);
 while(func_0012AA80(0x3B)==0){ _ACTWait(1); }
 _ACTWait(1);
 func_0017B568(D_00631AE8);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D35F0[];
extern int D_004D3610[];
extern void ReleaseWeapon(int a0);
extern int actInitialize(int a0);
extern void actSt20aFence(volatile int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int func_0017B230(int a0);

void actSt20aGondolaUp(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x13)==0){
  stage_KillPlayBgAnimation(0x3B,-1,-2);
  *(int*)(actSt25aQueenDeadChk(0x6F)+0x16C)=0;
  ReleaseWeapon(1);
  D_004D35F0[1]=(int)actSt20aFence;
  gobj->unkC4=D_004D35F0;
  BoxBarSoundOn((int)a0,0x18D);
  _ACTWait(0);
 } else {
  if(func_0017B230(0x15)==0){
   *(int*)(actSt25aQueenDeadChk(0x6F)+0x16C)=0;
   ReleaseWeapon(1);
   stage_KillPlayBgAnimation(0x3B,0,-1);
   stage_KillPlayBgAnimation(0x3F,0,0);
   D_004D3610[1]=(int)actSt20aFence;
   gobj->unkC4=D_004D3610;
   BoxBarSoundOn((int)a0,0x18D);
   _ACTWait(0);
  }
  *(int*)(actSt25aQueenDeadChk(0x7F)+0x16C)=0;
  stage_KillPlayBgAnimation(0x3F,0,-1);
  stage_KillPlayBgAnimation(0x3D,0,-1);
  stage_KillPlayBgAnimation(0x3E,0,-1);
 }
}

INCLUDE_ASM("asm/nonmatchings/src/st20a", actSt20aFence);

INCLUDE_ASM("asm/nonmatchings/src/st20a", actSt20aFenceDownChk);

INCLUDE_ASM("asm/nonmatchings/src/st20a", actSt20aFenceUpChk);

INCLUDE_ASM("asm/nonmatchings/src/st20a", actSt20aFenceDownChk2);

INCLUDE_ASM("asm/nonmatchings/src/st20a", actSt20aFenceUpChk2);

INCLUDE_ASM("asm/nonmatchings/src/st20a", actSt20aBridge);

INCLUDE_ASM("asm/nonmatchings/src/st20a", actSt20aGondola);

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D3550[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt22aIntroSub(volatile int a0);
extern int func_0017B230(int a0);

void actSt20aExit(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x12)==0){
  D_004D3550[1]=(int)actSt22aIntroSub;
  gobj->unkC4=D_004D3550;
  BoxBarSoundOn((int)a0,0x18D);
  _ACTWait(0);
 }
}

extern int D_004D3590[];
extern void func_002342C8();
extern void AddPluralCameraSet(int a0);

void actSt20aElv(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x13)==0){
  stage_KillPlayBgAnimation(0x3B,0,0);
  stage_KillPlayBgAnimation(0x3F,0,0);
  D_004D3590[1]=(int)func_002342C8;
  gobj->unkC4=D_004D3590;
  BoxBarSoundOn((int)a0,0x18D);
  _ACTWait(0);
 }
 if(func_0017B230(0x13)!=0){
  AddPluralCameraSet(0x25);
 }
}


extern int D_004D35D0[];
extern void func_002343B8(volatile int a0);

void actSt20aEne(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x15)==0){
  D_004D35D0[1]=(int)func_002343B8;
  gobj->unkC4=D_004D35D0;
  BoxBarSoundOn((int)a0,0x18D);
  _ACTWait(0);
 }
}

extern int D_00633FC8;
extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void func_0017B288(int a0);
extern void scpDispOnAllWithKind(void);

void actSt20aEnemy1(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    D_00633FC8 = a0;
    Generator_Mask(a0);
    while (func_0017B230(0x16) == 0) {
        _ACTWait(1);
    }
    Generator_Call(actSt25aQueenDeadChk(0x87));
    _ACTWait(0xB4);
    Generator_Call(a0);
    scpDispOnAllWithKind();
    func_0017B288(0x16);
}

extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);

void actSt20aEnemy2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x18) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);
}

extern void SetWayGroupActive(int a0, int a1);
extern void func_0017BF78(int a0, int a1, int a2, int a3, int a4, float f0, float f1, float f2, float f3, float f4, float f5);

void actSt20aEnemy3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_0017BF78(a0, 0x1D, 0x40, 0, 0x11, -300.0f, -100.0f, 100.0f, -300.0f, -100.0f, 0.0f);
    if (func_0017B230(0x1D) == 0) {
        SetWayGroupActive(2, 0);
    } else {
        SetWayGroupActive(2, 1);
    }
}

extern int D_004D3630[];
extern void func_00234458(volatile int a0);

void actSt20aBridgeMain(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x1D)==0){
  D_004D3630[1]=(int)func_00234458;
  gobj->unkC4=D_004D3630;
  BoxBarSoundOn((int)a0,0x18D);
  _ACTWait(0);
 }
}

extern int D_004D36B0[];
extern void actSt20aBridge(volatile int a0);

void actSt20aBridgeSwitch(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x1A)==0){
  D_004D36B0[1]=(int)actSt20aBridge;
  gobj->unkC4=D_004D36B0;
  BoxBarSoundOn((int)a0,0x18D);
  _ACTWait(0);
 }
}

extern int D_004D3650[];
extern void actSt20aFenceUpChk2(volatile int a0);

void actSt20aGondolaMain(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x1A)==0){
  D_004D3650[1]=(int)actSt20aFenceUpChk2;
  gobj->unkC4=D_004D3650;
  BoxBarSoundOn((int)a0,0x18D);
  _ACTWait(0);
 }
}

extern int D_004D36D0[];
extern void func_00234720(volatile int a0);

void actSt20aGondolaSwitch(volatile int a0){
 int x=a0;
 ActB4Obj *gobj=(ActB4Obj*)actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0x1C)==0){
  if(func_0017B230(0x1A)==0){
   D_004D36D0[1]=(int)func_00234720;
   gobj->unkC4=D_004D36D0;
   BoxBarSoundOn((int)a0,0x18D);
   _ACTWait(0);
  }
 }
}

