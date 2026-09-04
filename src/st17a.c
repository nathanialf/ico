#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aDoor);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aDoorUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aDoorDownChk);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aHasiChk);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aHasiEffect);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aIntroCancel);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actLinkTest);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aSekizo);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aHasi);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aIntro);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aHint1);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aFall);
void actSt17aSekizoEvent(int x) {
    volatile int local = x;
}
extern int *D_00639EA4;
extern void _ACTWait();
extern void scpGetWallCollision(float a0, float a1, float a2, float a3, float a4, float a5);

void actLinkTestChk(volatile int a0)
{
    *(int *)(D_00639EA4[0x57] + 0x4E8) = 1;
    *(int *)(D_00639EA4[0x57] + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
}
void actSt17aDoorEvent(int x) {
    volatile int local = x;
}
extern long long D_00622F70[];
extern long long D_00622F80[];
extern void scpEffectStart(int *buf, int a1);

void actSt17aDoorUpEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622F70[0]; long long v0b=D_00622F80[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622F70[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622F80[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
extern long long D_00622F90[];

void actSt17aDoorDownEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622F80[0]; long long v0b=D_00622F90[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622F80[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622F90[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
void actSt17aHasiEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aIntroChk);
extern long long D_00623020[];
extern void *D_00639EA8;
extern void _SCPMoveCharactorByWay(void *a0, int a1, int *buf, int a3, float f);

void actSt17aGirlWay(volatile int a0)
{
    long long buf[2];
    buf[0] = D_00623020[0];
    buf[1] = D_00623020[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 2, 100.0f);
}
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aHint1Chk);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aFallChk);
