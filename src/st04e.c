#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD0];  /* 0x00 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} Act;

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    Act *act;          /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObj;

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern int actCreateSubThread(void *entry, int prio);
extern void iosThreadSetPri(int a0, int a1);
extern int gflagChk(int a0);
extern void gflagOn(int a0);
extern void FinishHint(int a0);
extern void SleepHint(int a0);
extern void WakeupHint(int a0);
extern PObjGObj *scpSearchGobj(int a0);
extern void SetRotObjectLockFlag(PObjGObj *a0, int a1);
extern void SetWayGroupActive(int a0, int a1);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int scpTriggerBall(int a0, int gobj, float r);
extern int scpTriggerFloorAttr(int a0, int a1);
extern int ForMotionViewer_GetCurrentMotion(int a0);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void soundSeDefStop(int handle);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern int scpAdpcmPlayRequestNum(void);
extern void scpFadeOut(float f, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern void scpFadeIn(float f);
extern int lt_fade_status(void);
extern void lt_switch_layout(int a0);
extern void debug_StdPrintfDummy();
extern char D_00622A90[];
extern int D_0028F4C0[];
extern int D_0028F8F4[];
extern int D_00639EA4;
extern int D_0063AA08;
extern float D_0063C088;
extern int D_0063C514;
extern int D_0063C518;
extern float D_004F8A70[];
extern void actSt04eWaterStop(volatile int a0);
extern void actSt04eWaterStopSub(volatile int a0);
extern void actSt04eWaterFlagOn(volatile int a0);
extern void actSt04eWaterMain(volatile int a0);
extern void actSt04eHint1Chk(volatile int a0);
extern void actSt04eHint1WakeUpChk(volatile int a0);
extern void actSt04eFuchi1Chk(volatile int a0);
extern void actSt04eFuchi2Chk(volatile int a0);
extern void actSt04eFuchi3Chk(volatile int a0);
extern void actSt04eSeChk(volatile int a0);
extern ActMail D_004F8970[];
extern ActMail D_004F8990[];
extern ActMail D_004F89B0[];
extern ActMail D_004F89D0[];
extern ActMail D_004F89F0[];
extern ActMail D_004F8A10[];
extern ActMail D_004F8A30[];
extern ActMail D_004F8A50[];
extern ActMail D_004F8A80[];

void actSt04eWaterStop(volatile int a0)
{
    int th;

    lt_switch_layout(0x37);

    D_0063C514 = 0;
    D_0063C518 = 0;
    actCreateSubThread(actSt04eWaterFlagOn, 0x15);

    scpSleepEnemyAll();

    th = actCreateSubThread(actSt04eWaterStopSub, 0x15);

    while (D_0063C514 == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    D_0063C518 = D_0063C514 ^ 1;
    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C514 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x106, 0, -1);
        stage_SetAnimation(0x105, -1, -2);
        scpFadeIn(3.0f);
    }

    scpSearchGobj(0x4F9)->f16C = 1;
    scpSearchGobj(0x4F8)->f16C = 0;

    D_0063AA08 = 0;
    lt_switch_layout(0x36);

    scpWakeupEnemyAll();

    SetWayGroupActive(5, 1);
}

void actSt04eHint1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xE1) == 0) {
        D_004F89D0[0].func = actSt04eHint1Chk;
        self->mail = D_004F89D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        FinishHint(0x12);
    }
}

void actSt04eHint1WakeUp(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xE2) == 0) {
        SleepHint(0x12);
        D_004F8A80[0].func = actSt04eHint1WakeUpChk;
        self->mail = D_004F8A80;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt04eFuchi1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xE3) == 0) {
        stage_SetAnimation(0x107, 0, 0);
        D_004F89F0[0].func = actSt04eFuchi1Chk;
        self->mail = D_004F89F0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x107, 0, -1);
    }
}

void actSt04eFuchi2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xE4) == 0) {
        stage_SetAnimation(0x108, 0, 0);
        D_004F8A10[0].func = actSt04eFuchi2Chk;
        self->mail = D_004F8A10;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x108, 0, -1);
    }
}

void actSt04eFuchi3(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xE5) == 0) {
        stage_SetAnimation(0x109, 0, 0);
        D_004F8A30[0].func = actSt04eFuchi3Chk;
        self->mail = D_004F8A30;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x109, 0, -1);
    }
}

void actSt04eSe(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004F8A50[0].func = actSt04eSeChk;
    self->mail = D_004F8A50;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt04eWater(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    SetRotObjectLockFlag(scpSearchGobj(0x4FA), 1);

    if (gflagChk(0xE6) == 0) {
        scpSearchGobj(0x4F9)->f16C = 0;
        D_004F8990[0].func = actSt04eWaterMain;
        self->mail = D_004F8990;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x4F8)->f16C = 0;
        stage_SetAnimation(0x105, -1, -2);
    }
}

void actSt04eWaterMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F8970;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04eWaterSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004F89B0[0].func = actSt04eWaterStop;
    sub->mail = D_004F89B0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt04eWaterFlagOn(volatile int a0)
{
    int t = (0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 6.0;

    D_0063C088 = 0.005f;

    while (t-- > 0) {
        if (D_0063C518 != 0) {
            D_0063C088 = 1000.0f;
            break;
        }
        _ACTWait(1);
    }

    gflagOn(0xE6);
}

void actSt04eWaterStopSub(volatile int a0)
{
    _ACTWait(0x3C);

    stage_SetAnimation(0x106, 1, 0);
    stage_SetAnimation(0x105, -1, -2);

    while (stage_CheckAnimationFinish(0x106) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    D_0063C514 = 1;
    _ACTWait(0);
}

void actSt04eHint1Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 1000.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x91) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00622A90);
    gflagOn(0xE1);
    FinishHint(0x12);
}

void actSt04eFuchi1Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xE3);
    _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    stage_SetAnimation(0x107, 1, 0);
    soundSeDefPlay(0x53E, 0, 0, 1);

    while (stage_CheckAnimationFinish(0x107) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
}

void actSt04eFuchi2Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xE4);
    _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    stage_SetAnimation(0x108, 1, 0);
    soundSeDefPlay(0x53E, 0, 0, 1);

    while (stage_CheckAnimationFinish(0x108) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
}

void actSt04eFuchi3Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xE5);
    _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    stage_SetAnimation(0x109, 1, 0);
    soundSeDefPlay(0x53E, 0, 0, 1);

    while (stage_CheckAnimationFinish(0x109) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
}

void actSt04eSeChk(volatile int a0)
{
    int h;

    while (1) {
        while (ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0xAD &&
               ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0xB1) {
            _ACTWait(1);
        }

        h = soundSeDefPlay(0x53C, 0, D_004F8A70, 1);
        _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 0.5);
        soundSeDefStop(h);

        soundSeDefPlay(0x53D, 0, D_004F8A70, 1);

        _ACTWait(1);
    }
}

void actSt04eHint1WakeUpChk(volatile int a0)
{
    while (scpTriggerFloorAttr(D_00639EA4, 0x3000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xE2);
    WakeupHint(0x12);
}
