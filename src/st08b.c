#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bKurenSwitch);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bKurenLeft);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bKurenRight);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoor);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoorUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoorDownChk);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bKuren);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bEne);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bEnemy1);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bEnemy2);
INCLUDE_ASM("asm/nonmatchings/src/st08b", func_00241E00);
void actSt08bDoorEvent(int x) {
    volatile int local = x;
}
extern long long D_00622D80[];
extern long long D_00622D90[];
extern void _ACTWait(int a0);
extern void scpEffectStart(int *buf, int a1);

void actSt08bDoorUpEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622D80[0]; long long v0b=D_00622D90[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622D80[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622D90[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
void actSt08bDoorDownEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622D90[0]; long long v0b=D_00622D80[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622D90[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622D80[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bEneChk);
