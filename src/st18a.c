#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0xD4];           /* 0x00 */
    ActMail *mail;              /* 0xD4 */
} Act;

extern char *D_00639EA8;
void actSt18aEnd(void) {
    if (D_00639EA8 != 0) {
        if (gflagChk(0x3D) == 0) {
            gflagOn(0x187);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aIntroChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchLChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchLUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchRChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchRUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aDoorChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aDoorDownChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aEnemy1_1);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aEnemy2_1);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void actSt18aIntroChk(volatile int a0);
extern ActMail D_004FB070[];

void actSt18aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x37) == 0) {
        D_004FB070[0].func = actSt18aIntroChk;
        self->mail = D_004FB070;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void actSt18aDoorChk(volatile int a0);
extern void actSt18aDoorDownChk(volatile int a0);
extern ActMail D_004FB190[];
extern ActMail D_004FB1B0[];

void actSt18aDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x3C) == 0) {
        stage_SetAnimation(0x7B, 0, 0);

        D_004FB190[0].func = actSt18aDoorChk;
        self->mail = D_004FB190;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x7B, 0, -1);

        D_004FB1B0[0].func = actSt18aDoorDownChk;
        self->mail = D_004FB1B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void actSt18aSwitchLChk(volatile int a0);
extern void actSt18aSwitchLUpChk(volatile int a0);
extern ActMail D_004FB090[];
extern ActMail D_004FB0B0[];

void actSt18aSwitchL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x3A) == 0) {
        stage_SetAnimation(0x79, 0, 0);

        D_004FB090[0].func = actSt18aSwitchLChk;
        self->mail = D_004FB090;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x79, 0, 0x2D);

        D_004FB0B0[0].func = actSt18aSwitchLUpChk;
        self->mail = D_004FB0B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void actSt18aSwitchRChk(volatile int a0);
extern void actSt18aSwitchRUpChk(volatile int a0);
extern ActMail D_004FB110[];
extern ActMail D_004FB130[];

void actSt18aSwitchR(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x3B) == 0) {
        stage_SetAnimation(0x7A, 0, 0);

        D_004FB110[0].func = actSt18aSwitchRChk;
        self->mail = D_004FB110;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x7A, 0, 0x2D);

        D_004FB130[0].func = actSt18aSwitchRUpChk;
        self->mail = D_004FB130;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void actSt18aEneChk(volatile int a0);
extern ActMail D_004FB210[];

void actSt18aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x3D) == 0) {
        D_004FB210[0].func = actSt18aEneChk;
        self->mail = D_004FB210;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void _ACTWait(int a0);
extern Act *actInitialize(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt18aEnemy1_2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x3E) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
}
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void actSt18aEne2Chk(volatile int a0);
extern ActMail D_004FB230[];

void actSt18aEne2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x3F) == 0) {
        D_004FB230[0].func = actSt18aEne2Chk;
        self->mail = D_004FB230;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void _ACTWait(int a0);
extern Act *actInitialize(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt18aEnemy2_2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x40) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}
void actSt18aCamera(int x) {
    volatile int local = x;
}
extern void _ACTWait(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int scpTriggerFloorAttr(int a0, int a1);
extern void SetCameraFlag_LwsCutBack(void);
extern int soundSeDefPlay(int se, int a1, int a2, int a3);
extern int D_00639EA4;
extern int D_0063C59C;
extern int D_0063C5A0;

void actSt18aDoorChkSub(volatile int a0)
{
    _ACTWait(60);

    stage_SetAnimation(123, 1, 0);

    if (scpTriggerFloorAttr(D_00639EA4, 0x5000000) != 0) {
        SetCameraFlag_LwsCutBack();
    }

    soundSeDefPlay(0x4C5, 0, 0, 1);
    _ACTWait(50);
    D_0063C5A0 = 1;
    soundSeDefPlay(0x4C6, 0, 0, 1);
    while (stage_CheckAnimationFinish(123) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C59C = 1;
    _ACTWait(0);
}
extern void _ACTWait(int a0);
extern int scpTriggerFloorAttr(int a0, int a1);

void actSt18aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOff(0x187);
    gflagOn(0x3D);
    gflagOn(0x3E);
}
extern void _ACTWait(int a0);
extern int scpTriggerFloorAttr(int a0, int a1);
extern int scpSearchGobj(int a0);
extern void FinishHint(int a0);

void actSt18aEne2Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (D_00639EA8 == 0 ||
           scpTriggerFloorAttr(scpSearchGobj(0x306), 0x4000000) == 0) {
        _ACTWait(1);
    }
    FinishHint(8);
    _ACTWait(300);
    gflagOn(0x3F);
    gflagOn(0x40);
}
