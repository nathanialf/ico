#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(int);          /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0xD4];           /* 0x00 */
    ActMail *mail;              /* 0xD4 */
} Act;
extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004FA210[];
extern int gflagChk(int a0);
extern ActMail D_004FA2D0[];
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern int D_00639EA8;
extern int D_0063AA08;
extern int D_004FA1F0[];
extern void scpPlayEnd(int a0);
extern void scpPlayStart(int a0);
extern void scpPlayMot(int a0, int mot);
extern void scpPlayWaitMotEnd(int a0);
extern long long D_00622D80[];
extern long long D_00622D90[];
extern void scpEffectStart(int *buf, int a1);
extern int scpTriggerFloorAttr(int a0, int a1);
extern void gflagOn(int a0);
/* prototypes: their order is the inline tail's emission order */
void actSt08bKuren(volatile int a0);
void actSt08bEne(volatile int a0);
void actSt08bEnemy1(volatile int a0);
void actSt08bEnemy2(volatile int a0);
void actSt08bKurenMain(volatile int a0);
void actSt08aGirlYoro(volatile int a0);
void actSt08bDoorEvent(int x);
void actSt08bDoorUpEffect(volatile int a0);
void actSt08bDoorDownEffect(volatile int a0);
void actSt08bEneChk(volatile int a0);
inline void actSt08bKuren(volatile int a0) {
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004FA210[0].func = actSt08bKurenMain;
    self->mail = D_004FA210;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
inline void actSt08bKurenMain(volatile int a0)
{
    int sub = *(int *)(a0 + 0x164);

    D_0063AA08 = 0;
    if (D_00639EA8 != 0) {
        scpPlayEnd(D_00639EA8);
    }
    *(int *)(sub + 0xD0) = (int)D_004FA1F0;
    while (1) {
        _ACTWait(1);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bKurenSwitch);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bKurenLeft);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bKurenRight);
inline void actSt08aGirlYoro(volatile int a0)
{
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x222);
    scpPlayWaitMotEnd(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x253);
    scpPlayWaitMotEnd(D_00639EA8);
    _ACTWait(0);
}
inline void actSt08bDoorEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoor);
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoorUpChk);
inline void actSt08bDoorUpEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622D80[0]; long long v0b=D_00622D90[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622D80[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622D90[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
inline void actSt08bDoorDownEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622D90[0]; long long v0b=D_00622D80[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622D90[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622D80[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
INCLUDE_ASM("asm/nonmatchings/src/st08b", actSt08bDoorDownChk);
inline void actSt08bEne(volatile int a0) {
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x51) == 0) {
        D_004FA2D0[0].func = actSt08bEneChk;
        self->mail = D_004FA2D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
inline void actSt08bEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(0x51);
    gflagOn(0x52);
}
inline void actSt08bEnemy1(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x52) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
inline void actSt08bEnemy2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x52) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
