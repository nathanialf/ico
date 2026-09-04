#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aInit);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aSuimon);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aSuimonChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aDoor);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aDoorUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aDoorDownChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aShutterOpen);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBoxChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aStatueChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aHeadChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aJumpMove);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aPistonFlagOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aShutter);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aExit);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aExitGirl);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBox);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBox2);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBox3);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBoxEvent2);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aWay);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aWallWay);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aWallWay2);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aStatue);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aHead);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aTree);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBallDelete);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aKyomi);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aJump);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aPiston);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aPistonFlag);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aSound);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aSound2);
void actSt06aSuimonEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aSuimonEffect);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aSuimonFlagOn);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aSuimonSub);
void actSt06aDoorEvent(int x) {
    volatile int local = x;
}
extern long long D_00622BA0[];
extern long long D_00622BB0[];
extern void _ACTWait(int a0);
extern void scpEffectStart(int *buf, int a1);

void actSt06aDoorUpEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622BA0[0]; long long v0b=D_00622BB0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622BA0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622BB0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
void actSt06aDoorDownEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622BB0[0]; long long v0b=D_00622BA0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622BB0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622BA0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aShutterMain);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aShutterOpenSub);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aExitChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aExitGirlChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBoxSub);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBox2Chk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBox3Chk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBallDeleteChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBoxEvent2InChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aBoxEvent2OutChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aWayOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aWayOffChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aWallWayOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aWallWayOffChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aWallWay2OnChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aWallWay2OffChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aTreeChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aKyomiOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aKyomiOffChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aJumpMain);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aJumpSub);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aPistonRideOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aPistonRideOffChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aPistonFlagOffChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aSoundChk);
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aSound2Chk);
