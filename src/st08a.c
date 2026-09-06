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
    char pad00[0x15C];          /* 0x000 */
    char *f15C;                 /* 0x15C */
    char pad160[0x4];           /* 0x160 */
    Act *act;                   /* 0x164 */
    char pad168[0x4];           /* 0x168 */
    int f16C;                   /* 0x16C */
} PObjGObj;

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int D_0063AA08;
extern ActMail D_004FA060[];
extern ActMail D_004FA0A0[];
extern ActMail D_004FA130[];
extern ActMail D_004FA170[];
extern int scpTriggerBall(int a0, void *a1, float radius);
extern void *D_00639EA4;
extern void *D_00639EA8;
extern void WakeupHint(int a0);
extern void FinishHint(int a0);
extern int gflagChk(int a0);
extern void debug_StdPrintfDummy(char *fmt);
extern char D_00622D30[];
extern void lt_switch_layout(int a0);
extern void gflagOn(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern float D_004FA0C0[];
extern int D_0063C568;
extern int D_0063C564;
extern Act *actInitialize(int a0);
extern PObjGObj *scpSearchGobj(int a0);
extern void shadow_SetLength(char *a0, float f);
extern void SetWayGroupActive(int a0, int a1);
extern void SleepHint(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern void scpSetCageVelocityFriction(int id, float f);
extern float D_006399C0;
extern ActMail D_004FA020[];
extern ActMail D_004FA040[];
extern ActMail D_004FA080[];
extern ActMail D_004FA0D0[];
extern ActMail D_004FA0F0[];
extern ActMail D_004FA110[];
extern ActMail D_004FA150[];
extern ActMail D_004FA190[];
extern void actSt08aDoorUp(volatile int a0);
extern void actSt08aHasiUp(volatile int a0);
extern void actSt08aEne1Chk(volatile int a0);
extern void actSt08aEne2Chk(volatile int a0);
extern void actSt08aTorchOffChk(volatile int a0);
extern void actSt08aDoorMain(volatile int a0);
extern void actSt08aHasiMain(volatile int a0);
extern void actSt08aIntroChk(volatile int a0);
extern void actSt08aGirlPosChk(volatile int a0);
extern void actSt08aHint1Chk(volatile int a0);

INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aEnd);
INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aEne1Chk);
INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aEne2Chk);
INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aDoorUp);
INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aHasiUpSub);
INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aHasiUp);
INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aTorchOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aTorchOffChk);
void actSt08aDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x47) == 0) {
        stage_SetAnimation(0x69, 0, 0);
        D_004FA080[0].func = actSt08aDoorMain;
        self->mail = D_004FA080;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        SetWayGroupActive(0xB, 1);
        stage_SetAnimation(0x69, 0, -1);
    }
}
void actSt08aEne1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    shadow_SetLength(scpSearchGobj(0x16E)->f15C, 100.0f);
    shadow_SetLength(scpSearchGobj(0x16F)->f15C, 100.0f);
    shadow_SetLength(scpSearchGobj(0x170)->f15C, 100.0f);

    if (gflagChk(0x48) == 0) {

        D_004FA020[0].func = actSt08aEne1Chk;
        self->mail = D_004FA020;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt08aEne2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x49) == 0) {

        D_004FA040[0].func = actSt08aEne2Chk;
        self->mail = D_004FA040;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt08aEnemy1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x4A) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x74);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
void actSt08aEnemy2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x4A) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x64);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
void actSt08aEnemy3(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x4B) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
void actSt08aEnemy4(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x4B) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
void actSt08aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x4C) == 0) {
        D_004FA0D0[0].func = actSt08aIntroChk;
        self->mail = D_004FA0D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt08aHint1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x4D) == 0) {
        D_004FA110[0].func = actSt08aHint1Chk;
        self->mail = D_004FA110;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        FinishHint(2);
    }
}
void actSt08aGirlPos(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x4E) == 0) {

        SleepHint(2);
        D_004FA0F0[0].func = actSt08aGirlPosChk;
        self->mail = D_004FA0F0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt08aHasi(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x4F) == 0) {
        stage_SetAnimation(0x6A, 0, 0);
        D_004FA150[0].func = actSt08aHasiMain;
        self->mail = D_004FA150;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x6A, 0, -1);
        scpSearchGobj(0x171)->f16C = 0;
        SetWayGroupActive(0x1E, 1);
    }
}
void actSt08aTorch(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004FA190[0].func = actSt08aTorchOffChk;
    self->mail = D_004FA190;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt08aInit(void)
{
    float f = D_006399C0;

    scpSetCageVelocityFriction(0x16D, f);
    scpSetCageVelocityFriction(0x16C, f);

    if (gflagChk(0x50) != 0) {
        stage_SetAnimation(0x172, 0, 0x1FE);
        scpSearchGobj(0x16D)->f16C = 0;
    } else {
        stage_SetAnimation(0x172, 0, 0);
        scpSearchGobj(0x16C)->f16C = 0;
    }
}
void actSt08aDoorMain(volatile int a0)
{
    int sub = *(int *)(a0 + 0x164);

    D_0063AA08 = 0;

    *(int *)(sub + 0xD0) = (int)D_004FA060;
    while (1) {
        _ACTWait(1);
    }
}
void actSt08aDoorSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    D_004FA0A0[0].func = actSt08aDoorUp;
    sub->mail = D_004FA0A0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt08aDoorUpSub(volatile int a0)
{
    _ACTWait(0x3C);

    stage_SetAnimation(0x69, 1, 0);

    soundSeDefPlay(0x4C5, 0, D_004FA0C0, 1);
    _ACTWait(0x1E);
    D_0063C568 = 1;
    soundSeDefPlay(0x4C6, 0, D_004FA0C0, 1);

    while (stage_CheckAnimationFinish(0x69) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C564 = 1;
    _ACTWait(0);
}
void actSt08aIntroChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    gflagOn(0x4C);

    stage_SetAnimation(0x87, 1, 0);
    while (stage_CheckAnimationFinish(0x87) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}
void actSt08aGirlPosChk(volatile int a0)
{
    while (D_00639EA8 == 0 ||
           scpTriggerBall(a0, D_00639EA8, 200.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x4E);
    WakeupHint(2);
}
void actSt08aHint1Chk(volatile int a0)
{
    while (gflagChk(0x50) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00622D30);

    gflagOn(0x4D);
    FinishHint(2);
}
void actSt08aHasiMain(volatile int a0)
{
    int sub = *(int *)(a0 + 0x164);

    D_0063AA08 = 0;

    *(int *)(sub + 0xD0) = (int)D_004FA130;
    while (1) {
        _ACTWait(1);
    }
}
void actSt08aHasiSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    D_004FA170[0].func = actSt08aHasiUp;
    sub->mail = D_004FA170;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
