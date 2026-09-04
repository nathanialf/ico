#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aInit);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aDoor);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aDoorUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aDoorDownChk);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aFenceOpen);
extern void CopyVector(void *a0, float *a1);
extern long long D_00622740[];
extern char *D_00639EA4;
extern int GetSkeltonFocusNode(void *obj, int kind);
extern void _ACTWait(int a0);
extern void scpEffectStart(void *buf, int kind);
extern int scpTriggerPosBall(void *a, void *b, float f);

void actSt02WaterFallBoySplashCheck(volatile int a0){
 long long buf[4]; long long buf2[2]; int idx;
 if(D_00639EA4==0) return;
 buf[0]=D_00622740[0]; buf[1]=D_00622740[1]; buf[2]=D_00622740[2]; buf[3]=D_00622740[3];
 for(;;){
  idx=GetSkeltonFocusNode(D_00639EA4,0x23);
  CopyVector(buf2,(float*)(*(int*)(*(char**)(D_00639EA4+0x15C)+0xC)+(idx<<6)+0x30));
  if(scpTriggerPosBall(&buf[0],buf2,100.0f)) scpEffectStart(buf2,0x2F);
  _ACTWait(0xA);
  idx=GetSkeltonFocusNode(D_00639EA4,0x23);
  CopyVector(buf2,(float*)(*(int*)(*(char**)(D_00639EA4+0x15C)+0xC)+(idx<<6)+0x30));
  if(scpTriggerPosBall(&buf[2],buf2,100.0f)) scpEffectStart(buf2,0x2F);
  _ACTWait(0xA);
 } }
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aWaterFallReflactionEffect);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aGondolaUp);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aGondolaDown);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aBox);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aGondola);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aFence);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aWaterFall);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aBoxEvent2);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aEne);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aEnemy1);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aEnemy2);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aSekizo);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aWay);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aTakiWay);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aSecretItem);
void actSt02aDoorEvent(int x) {
    volatile int local = x;
}
extern long long D_00622720[];
extern long long D_00622730[];
extern void scpEffectStart__pn(int *buf, int a1) __asm__("scpEffectStart");

void actSt02aDoorUpEffect(volatile int a0){
 long long b1[2]; long long b2[2];
 long long v0a=D_00622720[0]; long long v0b=D_00622730[0];
 int i;
 for(i=0;i<0x32;i++){
  switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622720[1]; scpEffectStart__pn((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622730[1]; scpEffectStart__pn((int*)b2,0); break;
  }
  _ACTWait(1);
 } }
void actSt02aDoorDownEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622730[0]; long long v0b=D_00622720[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622730[1]; scpEffectStart__pn((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622720[1]; scpEffectStart__pn((int*)b2,0); break;
  } _ACTWait(1); } }
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aFenceMain);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aFenceOpenSub);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aGondolaSwitch);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aEneChk);
void actSt02aSekizoEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aWayOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aWayOffChk);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aTakiWayOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aTakiWayOffChk);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aSecretItemChk);
