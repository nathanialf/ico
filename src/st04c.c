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
extern void ACTSendMailCorrect(int a0, int mail);
extern void _ACTWait(int a0);
extern int stage_CheckAnimationFinish(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);

extern char *D_00639EA8;
void actSt04cEnd(void) {
    if (D_00639EA8 != 0) {
        if (gflagChk(0xA3) == 0) {
            gflagOn(0x187);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cDoorDownChk);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04cIntroChk);
INCLUDE_ASM("asm/nonmatchings/src/st04c", actSt04lDoorChk);
void actSt04cSolarXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8A) == 0)
    {
        stage_SetAnimation(0x12E, -1, -2);
    }
}
extern ActMail D_004F8850[];
extern void actSt04lDoorChk(int a0);
extern int scpSearchGobj(int a0);
extern void FinishHint(int a0);

void actSt04lDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xC7) == 0)
    {
        stage_SetAnimation(0xE7, 0, 0);
        D_004F8850[0].func = actSt04lDoorChk;
        self->mail = D_004F8850;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
    else
    {
        stage_SetAnimation(0xE7, 0, -1);
        *(int *)(scpSearchGobj(0x44A) + 0x16C) = 0;
        FinishHint(0xF);
    }
}
extern ActMail D_004F8830[];
extern void actSt04cIntroChk(int a0);

void actSt04cIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xA1) == 0)
    {
        D_004F8830[0].func = actSt04cIntroChk;
        self->mail = D_004F8830;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F87F0[];
extern void actSt04cDoorDownChk(int a0);

void actSt04cDoorDown(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    if (gflagChk(0xA2) == 0)
    {
        D_004F87F0[0].func = actSt04cDoorDownChk;
        self->mail = D_004F87F0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F8810[];
extern void actSt04cEneChk(int a0);

void actSt04cEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xA3) == 0)
    {
        D_004F8810[0].func = actSt04cEneChk;
        self->mail = D_004F8810;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt04cEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);
    while (gflagChk(0xA4) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}
void actSt04cEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);
    while (gflagChk(0xA4) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}
void actSt04cWaterXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xE6) != 0)
    {
        *(int *)(scpSearchGobj(0x446) + 0x16C) = 0;
    }
}
void actSt04cDoorDownEvent(int x) {
    volatile int local = x;
}
/* Effect-parameter triples in .rodata; the `const` is the data model and is
   load-bearing: RTX_UNCHANGING_P is what keeps sched2 from ordering each
   b[0] store behind the b[1] load in the two remat'd-address switch arms. */
extern const long long D_00622A00[];
extern const long long D_00622A10[];
extern const long long D_00622A20[];

void actSt04cDoorDownEffect(volatile int a0){ long long b1[2]; long long b2[2]; long long b3[2];
 long long v0a=D_00622A00[0]; long long v0b=D_00622A10[0]; long long v0c=D_00622A20[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622A00[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622A10[1]; scpEffectStart((int*)b2,0);
             b3[0]=v0c; b3[1]=D_00622A20[1]; scpEffectStart((int*)b3,0); break;
  } _ACTWait(1); } }
extern char *D_00639EA8;
void actSt04cEneChk(volatile int a0) {
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0xB000000) == 0) {
        _ACTWait(1);
    }
    gflagOff(0x187);
    _ACTWait(1);
    gflagOn(0xA3);
    gflagOn(0xA4);
}
extern int D_0063C510;

void actSt04cIntroChkSub(volatile int a0)
{
    while (stage_CheckAnimationFinish(0x160) == 0) { _ACTWait(1); } _ACTWait(1);
    D_0063C510 = 1;
    _ACTWait(0);
}
void actSt04lDoorEvent(int x) {
    volatile int local = x;
}
