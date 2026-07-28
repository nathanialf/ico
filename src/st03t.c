#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchL);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchLChk);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchLUpChk);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchR);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchRChk);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchRUpChk);

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);

void actSt03tBoxA(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_0017B230(0x6D)==0){
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
 while(func_0017B230(0x6D)==0){ _ACTWait(1); }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tInit);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGirlCam);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSekizo);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tWay);

void actSt03tEne(int x) {
    volatile int local = x;
}

extern long long D_0061BA20[];
extern long long D_0061BA30[];
extern void scpDispOffAllWithKind(int *buf, int a1);

void actSt03tGene(volatile int a0){
 long long b1[2]; long long b2[2];
 long long v0a=D_0061BA20[0]; long long v0b=D_0061BA30[0];
 int i;
 for(i=0;i<0x32;i++){
  switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BA20[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BA30[1]; scpDispOffAllWithKind((int*)b2,0); break;
  }
  _ACTWait(1);
 } }

void actSt03tGirlCamEvent(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061BA30[0]; long long v0b=D_0061BA20[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BA30[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BA20[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGirlCamStartChk);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGirlCamEndChk);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSekizoEvent);

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tEneChk);

void actSt03tWayOnChk(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tWayOffChk);

