#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0xD0];           /* 0x00 */
    ActMail *mainMail;          /* 0xD0 */
    ActMail *mail;              /* 0xD4 */
} Act;
typedef struct PObjGObj {
    char pad00[0x164];          /* 0x000 */
    Act *act;                   /* 0x164 */
    char pad168[0x4];           /* 0x168 */
    int f16C;                   /* 0x16C */
} PObjGObj;

extern PObjGObj *scpSearchGobj(int a0);


INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aInit);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aDoor);
ASM_LIT4_SLOT(D_006398B4, -1827.0f);
ASM_LIT4_SLOT(D_006398B8, 2285.0f);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aDoorUpChk);
ASM_LIT4_SLOT(D_006398BC, -1827.0f);
ASM_LIT4_SLOT(D_006398C0, 2285.0f);
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
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aWaterFallChk);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aGondolaUp);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aGondolaDown);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aBox);
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern ActMail D_004F8170[];
extern void actSt02aGondolaMain(volatile int a0);

void actSt02aGondola(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x77) != 0) {
        stage_SetAnimation(0x65, 0, 0);
        _ACTWait(0xA);
        stage_SetAnimation(0x65, 0, 0x95);
    } else {
        stage_SetAnimation(0x65, 0, 0x12C);
    }

    D_004F8170[0].func = actSt02aGondolaMain;
    self->mail = D_004F8170;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F80F0[];
extern void actSt02aFenceMain(volatile int a0);

void actSt02aFence(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x76) == 0) {
        D_004F80F0[0].func = actSt02aFenceMain;
        self->mail = D_004F80F0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void actCreateSubThread(void *entry, int prio);
extern ActMail D_004F8130[];
extern void actSt02aWaterFallChk(volatile int a0);
extern void actSt02aWaterFallReflactionEffect(volatile int a0);

void actSt02aWaterFall(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6A) != 0) {
        D_004F8130[0].func = actSt02aWaterFallChk;
        self->mail = D_004F8130;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }

    scpSearchGobj(0x6B1)->f16C = 0;

    actCreateSubThread(actSt02WaterFallBoySplashCheck, 0x15);
    actCreateSubThread(actSt02aWaterFallReflactionEffect, 0x15);
}
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);

void actSt02aBoxEvent2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6E) == 0) {
        scpSearchGobj(0x6AD)->f16C = 0;
    }
}
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8210[];
extern void actSt02aEneChk(volatile int a0);

void actSt02aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x79) == 0) {
        D_004F8210[0].func = actSt02aEneChk;
        self->mail = D_004F8210;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt02aEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x7A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt02aEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);
    Generator_Mask((int)scpSearchGobj(0x6A7));

    while (gflagChk(0x7A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_Call((int)scpSearchGobj(0x6A7));
}
extern Act *actInitialize(int a0);
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4,
                       float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt02aSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x7B, 0x66, 0, 0x12,
               900.0f, 1828.0f, 1150.0f,
               800.0f, 1828.0f, 1150.0f);
}
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8230[];
extern ActMail D_004F8250[];
extern void actSt02aWayOffChk(volatile int a0);
extern void actSt02aWayOnChk(volatile int a0);

void actSt02aWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x7C) == 0) {
        D_004F8230[0].func = actSt02aWayOffChk;
        self->mail = D_004F8230;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        D_004F8250[0].func = actSt02aWayOnChk;
        self->mail = D_004F8250;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F82B0[];
extern void actSt02aTakiWayOnChk(volatile int a0);

void actSt02aTakiWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6A) != 0) {
        D_004F82B0[0].func = actSt02aTakiWayOnChk;
        self->mail = D_004F82B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8310[];
extern void actSt02aSecretItemChk(volatile int a0);

void actSt02aSecretItem(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x72) == 0) {
        D_004F8310[0].func = actSt02aSecretItemChk;
        self->mail = D_004F8310;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
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
extern ActMail D_004F80D0[];

void actSt02aFenceMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F80D0;
    while (1) {
        _ACTWait(1);
    }
}
extern void lt_switch_layout(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int D_0063AA08;
extern ActMail D_004F8110[];
extern void actSt02aFenceOpen(volatile int a0);

void actSt02aFenceSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    D_004F8110[0].func = actSt02aFenceOpen;
    sub->mail = D_004F8110;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int st02a_fence;
extern int D_0063C504;

void actSt02aFenceOpenSub(volatile int a0)
{
    while (st02a_fence == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(0x63, 1, 0);
    stage_SetAnimation(0x64, 1, 0);
    while (stage_CheckAnimationFinish(0x64) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C504 = 1;
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aGondolaMain);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aGondolaSwitch);
extern int D_00639EA8;
extern int scpTriggerFloorAttr(int a0, int a1);
extern void gflagOn(int a0);

void actSt02aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(0x79);
    gflagOn(0x7A);
}
void actSt02aSekizoEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aWayOnChk);
extern int scpCheckExistAliveEnemy(void);
extern void SetWayGroupActive(int a0, int a1);
extern ActMail D_004F8290[];
extern void actSt02aWayOnChk(volatile int a0);

void actSt02aWayOffChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 &&
           scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x35, 0);
    SetWayGroupActive(0x37, 0);
    SetWayGroupActive(0x38, 0);
    SetWayGroupActive(0x39, 0);
    gflagOn(0x7C);

    D_004F8290[0].func = actSt02aWayOnChk;
    sub->mail = D_004F8290;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aTakiWayOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st02a", actSt02aTakiWayOffChk);
extern void scpExplodeSecretItem(void);

void actSt02aSecretItemChk(volatile int a0)
{
    while (scpSearchGobj(0x6EA) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x3C);

    scpExplodeSecretItem();
}
