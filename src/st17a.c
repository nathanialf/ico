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

INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aDoor);
ASM_LIT4_SLOT(D_00639A60, 6573.0f);
ASM_LIT4_SLOT(D_00639A64, -2077.0f);
ASM_LIT4_SLOT(D_00639A68, 1089.0f);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aDoorUpChk);
ASM_LIT4_SLOT(D_00639A6C, 6573.0f);
ASM_LIT4_SLOT(D_00639A70, -2077.0f);
ASM_LIT4_SLOT(D_00639A74, 1089.0f);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aDoorDownChk);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aHasiChk);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aHasiEffect);
INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aIntroCancel);
extern ActMail D_004FAF10[];
extern void actLinkTestChk(int a0);

void actLinkTest(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004FAF10[0].func = actLinkTestChk;
    self->mail = D_004FAF10;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4,
                       float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt17aSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x20, 0x52, 0x82, 0x12,
               6450.0f, -2100.0f, 1000.0f,
               6450.0f, -2100.0f, 1100.0f);
}
extern ActMail D_004FAFD0[];
extern void actSt17aHasiChk(int a0);
extern int scpSearchGobj(int a0);
extern void SetWayGroupActive(int a0, int a1);

void actSt17aHasi(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x21) == 0) {
        *(int *)(scpSearchGobj(0xF4) + 0x16C) = 0;
        stage_SetAnimation(0x84, 0, 0);
        SetWayGroupActive(3, 1);
        D_004FAFD0[0].func = actSt17aHasiChk;
        self->mail = D_004FAFD0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        *(int *)(scpSearchGobj(0xF3) + 0x16C) = 0;
        stage_SetAnimation(0x84, 0, -1);
    }
}
extern ActMail D_004FAFF0[];
extern void actSt17aIntroChk(int a0);

void actSt17aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x22) == 0) {
        D_004FAFF0[0].func = actSt17aIntroChk;
        self->mail = D_004FAFF0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004FB010[];
extern void actSt17aHint1Chk(int a0);

void actSt17aHint1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x23) == 0) {
        D_004FB010[0].func = actSt17aHint1Chk;
        self->mail = D_004FB010;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        FinishHint(0);
    }
}
extern ActMail D_004FB030[];
extern void actSt17aFallChk(int a0);

void actSt17aFall(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x21) == 0) {
        D_004FB030[0].func = actSt17aFallChk;
        self->mail = D_004FB030;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
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
extern void lt_switch_layout(int a0);
extern int D_0063AA08;
extern int D_0063C598;
extern int cam;
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern void actCreateSubThread(void *entry, int prio);
extern void actSt17aIntroCancel(int a0);

void actSt17aIntroChk(volatile int a0)
{
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    gflagOn(0x22);
    scpAdpcmPlayRequestFunc(0x35, &cam, 1, 1, 1);
    _ACTWait(1);
    stage_SetAnimation(0x53, 1, 0);
    SetCameraFlag_LwsCutBack();
    actCreateSubThread(actSt17aIntroCancel, 0x15);

    while (stage_CheckAnimationFinish(0x53) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C598 = 1;
}
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
extern int scpTriggerBall(int a0, void *a1, float radius);
extern char D_00623030[];

void actSt17aHint1Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00623030);

    gflagOn(0x23);
    FinishHint(0);
}
extern char D_00623050[];

void actSt17aFallChk(volatile int a0)
{
    while (!(gflagChk(0x21) && scpTriggerBall(a0, D_00639EA4, 1800.0f))) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00623050);

    iosOmSendMail(D_00639EA4, 0xE2, D_00639EA4);
}
