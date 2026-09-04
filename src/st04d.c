#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1UpChk);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1DownChk);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2UpChk);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2DownChk);
void actSt04dDoor1Event(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1UpEffect);
INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1DownEffect);
void actSt04dDoor2Event(int x) {
    volatile int local = x;
}
extern long long D_00622A70[];
extern long long D_00622A80[];
extern void _ACTWait(int a0);
extern void scpEffectStart(int *buf, int a1);

void actSt04dDoor2UpEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622A70[0]; long long v0b=D_00622A80[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622A70[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622A80[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
void actSt04dDoor2DownEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622A80[0]; long long v0b=D_00622A70[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622A80[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622A70[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
