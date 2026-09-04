#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dDoor2);
INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dDoor2UpChk);
INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dDoor2DownChk);
INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dEne);
INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dEnemy1);
INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dEnemy2);
INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dCrestHint);
void actSt05dDoor2Event(int x) {
    volatile int local = x;
}
extern long long D_00622B40[];
extern long long D_00622B50[];
extern void _ACTWait(int a0);
extern void scpEffectStart(int *buf, int a1);

void actSt05dDoor2UpEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622B40[0]; long long v0b=D_00622B50[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622B40[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622B50[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
void actSt05dDoor2DownEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622B50[0]; long long v0b=D_00622B40[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622B50[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622B40[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dCrestHintChk);
