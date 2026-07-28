#include "common.h"


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

INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cBmg1);

void actSt13cBmg1Chk(int x) {
    volatile int local = x;
}

extern long long D_0061C070[];
extern long long D_0061C080[];
extern void scpDispOffAllWithKind(int *buf, int a1);

void actSt13cConte04(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061C070[0]; long long v0b=D_0061C080[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061C070[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061C080[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

void actSt13cConte04Jimaku(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061C080[0]; long long v0b=D_0061C070[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061C080[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061C070[1]; scpDispOffAllWithKind((int*)b2,0); break;
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

INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageFallChk);

INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cConte05);

INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cConte05Jimaku);

INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageFallEffect);

INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cGirlCarryChk);

INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cHandChk);

INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cHandJimaku);

void actSt13cSleep(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022BEE0);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022BF60);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022BFE8);

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022C060);

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

INCLUDE_ASM("asm/nonmatchings/src/st13c", func_0022CCF0);

