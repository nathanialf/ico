#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aInit);
extern char *D_00639EA8;
void actSt00aEnd(void) {
    if (D_00639EA8 != 0) {
        if (gflagChk(0x2A) == 0) {
            gflagOn(0x187);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aStairChk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2UpChk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2DownChk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1UpChk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1DownChk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEne);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEnemy1);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aEnemy2);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aStair);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aAtr2);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aAtr2Chk);
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aStairChkSub);
void actSt00aDoor2Event(int x) {
    volatile int local = x;
}
extern long long D_006226B0[];
extern long long D_006226C0[];
extern void _ACTWait(int a0);
extern void scpEffectStart(int *buf, int a1);

void actSt00aDoor2UpEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006226B0[0]; long long v0b=D_006226C0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006226B0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006226C0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
void actSt00aDoor2DownEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006226C0[0]; long long v0b=D_006226B0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006226C0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006226B0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
void actSt00aDoor1Event(int x) {
    volatile int local = x;
}
extern long long D_006226E0[];
extern long long D_006226F0[];

void actSt00aDoor1UpEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006226E0[0]; long long v0b=D_006226F0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006226E0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006226F0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1DownEffect);
