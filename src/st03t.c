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

extern Act *actInitialize(int a0);

typedef struct PObjGObj {
    char pad00[0x164];          /* 0x000 */
    int act;                    /* 0x164 */
} PObjGObj;

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchL);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchLChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchLUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchR);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchRChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchRUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGene);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tBoxA);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tBoxB);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tInit);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGirlUp);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8430[];
extern void actSt03tGirlCamStartChk(volatile int a0);

void actSt03tGirlCam(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F8430[0].func = actSt03tGirlCamStartChk;
    self->mail = D_004F8430;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void _ACTWait(int a0);
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4,
                       float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt03tSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x5F, 0x50, 0, 0x12,
               -913.0f, -400.0f, 605.0f,
               -1000.0f, -400.0f, 550.0f);
}
extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F84B0[];
extern ActMail D_004F84D0[];
extern void actSt03tWayOnChk(volatile int a0);
extern void actSt03tWayOffChk(volatile int a0);

void actSt03tWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x64) == 0) {
        D_004F84B0[0].func = actSt03tWayOnChk;
        self->mail = D_004F84B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        D_004F84D0[0].func = actSt03tWayOffChk;
        self->mail = D_004F84D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8490[];
extern void actSt03tEneChk(volatile int a0);

void actSt03tEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x68) == 0) {
        D_004F8490[0].func = actSt03tEneChk;
        self->mail = D_004F8490;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void SleepHint(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8530[];
extern void actSt03tGirlPosChk(volatile int a0);

void actSt03tGirlPos(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x65) == 0) {
        SleepHint(0xC);

        D_004F8530[0].func = actSt03tGirlPosChk;
        self->mail = D_004F8530;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8570[];
extern void actSt03tHint1OffChk(volatile int a0);

void actSt03tHint1Sleep(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F8570[0].func = actSt03tHint1OffChk;
    self->mail = D_004F8570;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt03tGirlCamEvent(int x) {
    volatile int local = x;
}
extern int D_00639EA4;
extern int D_00639EA8;
extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int a1, float radius);
extern int ForMotionViewer_GetCurrentMotion(int a0);
extern int CameraGetTarget(void);
extern void Camctrl_SetTarget(int a0, int a1, int a2);
extern void CameraSetCameraSet(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8450[];
extern void actSt03tGirlCamEndChk(volatile int a0);

void actSt03tGirlCamStartChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0xCA) {
        _ACTWait(1);
    }

    CameraGetTarget();
    Camctrl_SetTarget(D_00639EA8, 0, 3);
    _ACTWait(0xF);
    CameraSetCameraSet(0x30);

    D_004F8450[0].func = actSt03tGirlCamEndChk;
    sub->mail = D_004F8450;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern int D_00639EA4;
extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int a1, float radius);
extern int ForMotionViewer_GetCurrentMotion(int a0);
extern int CameraGetTarget(void);
extern void CameraSetCameraSet_Default(void);
extern void Camctrl_ExitEveRock(void);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8470[];
extern void actSt03tGirlCamStartChk(volatile int a0);

void actSt03tGirlCamEndChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0xCA) {
        _ACTWait(1);
    }

    CameraGetTarget();
    _ACTWait(0x5A);
    CameraSetCameraSet_Default();
    Camctrl_ExitEveRock();

    D_004F8470[0].func = actSt03tGirlCamStartChk;
    sub->mail = D_004F8470;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt03tSekizoEvent(int x) {
    volatile int local = x;
}
extern int D_00639EA4;
extern int D_00639EA8;
extern int D_0063AA08;
extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int a1, float radius);
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyOne(int a0);
extern void scpWakeupEnemyOne(int a0);
extern void gflagOn(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);

void actSt03tEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyOne(0xEAD);
    gflagOn(0x68);
    gflagOn(0x69);
    stage_SetAnimation(0x51, 1, 0);

    while (stage_CheckAnimationFinish(0x51) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
    scpWakeupEnemyOne(0xEAD);
}
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tWayOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tWayOffChk);
extern int D_00639EA8;
extern void _ACTWait(int a0);
extern int scpTriggerFloorAttr(int a0, int a1);
extern void gflagOn(int a0);
extern void WakeupHint(int a0);

void actSt03tGirlPosChk(volatile int a0)
{
    while (D_00639EA8 == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x65);
    WakeupHint(0xC);
}
extern char D_00622820[];
extern void debug_StdPrintfDummy();
extern void FinishHint(int a0);

void actSt03tGirlUpChk(volatile int a0)
{
    while (D_00639EA8 == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00622820);
    gflagOn(0x5D);
    FinishHint(0xC);
}
extern int D_0028F4C0[];
extern void _ACTWait(int a0);
extern void WakeupHint(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F85B0[];
extern void actSt03tHint1OffChk(volatile int a0);

void actSt03tHint1OnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x3C);
    WakeupHint(0xC);

    D_004F85B0[0].func = actSt03tHint1OffChk;
    sub->mail = D_004F85B0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void SleepHint(int a0);
extern void gflagOff(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8590[];
extern void actSt03tHint1OnChk(volatile int a0);

void actSt03tHint1OffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (gflagChk(0x66) == 0) {
        _ACTWait(1);
    }

    SleepHint(0xC);
    gflagOff(0x66);

    D_004F8590[0].func = actSt03tHint1OnChk;
    sub->mail = D_004F8590;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
