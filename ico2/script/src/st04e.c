#include "common.h"
#include "st04e.h"
#include "debug.h"
#include "layout_texture.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "rotObject.h"
#include "typedef.h"

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);
/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
/* kept local: this TU's uses of scpWakeupEnemyAll do not fit the prototype in script.h */
extern void scpWakeupEnemyAll(void);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float f, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
extern int D_0028F4C0[];
extern int D_0028F8F4[];
extern int D_00639EA4;
extern int D_0063AA08;
extern float D_0063C088;

/* .sbss, owned by st04e.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for, and its complement, true when the
   player skipped the demo with START. */
static int demoEnd;

static int demoSkipped;

static ActMail waterMain_mes[2] = {{406, actSt04eWaterSwitch}, {429}};

static ActMail water_mes[2] = {{430}, {429}};

static ActMail waterSwitch_mes[2] = {{430}, {429}};

static ActMail hint1_mes[2] = {{430}, {429}};

static ActMail fuchi1_mes[2] = {{430}, {429}};

static ActMail fuchi2_mes[2] = {{430}, {429}};

static ActMail fuchi3_mes[2] = {{430}, {429}};

static ActMail se_mes[2] = {{430}, {429}};

static float seChkPos[4] = {0.0f, -171.0f, -8000.0f, 0.0f};

static ActMail hint1WakeUp_mes[2] = {{430}, {429}};

void actSt04eWaterStop(volatile int a0)
{
    int th;

    lt_switch_layout(55);

    demoEnd = 0;
    demoSkipped = 0;
    actCreateSubThread(actSt04eWaterFlagOn, 21);

    scpSleepEnemyAll();

    th = actCreateSubThread(actSt04eWaterStopSub, 21);

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    demoSkipped = demoEnd ^ 1;
    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(262, 0, -1);
        stage_SetAnimation(261, -1, -2);
        scpFadeIn(3.0f);
    }

    scpSearchGobj(1273)->f16C = 1;
    scpSearchGobj(1272)->f16C = 0;

    D_0063AA08 = 0;
    lt_switch_layout(54);

    scpWakeupEnemyAll();

    SetWayGroupActive(5, 1);
}

void actSt04eHint1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(225) == 0) {
        hint1_mes[0].func = actSt04eHint1Chk;
        self->mail = hint1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(18);
    }
}

void actSt04eHint1WakeUp(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(226) == 0) {
        SleepHint(18);
        hint1WakeUp_mes[0].func = actSt04eHint1WakeUpChk;
        self->mail = hint1WakeUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04eFuchi1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(227) == 0) {
        stage_SetAnimation(263, 0, 0);
        fuchi1_mes[0].func = actSt04eFuchi1Chk;
        self->mail = fuchi1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(263, 0, -1);
    }
}

void actSt04eFuchi2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(228) == 0) {
        stage_SetAnimation(264, 0, 0);
        fuchi2_mes[0].func = actSt04eFuchi2Chk;
        self->mail = fuchi2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(264, 0, -1);
    }
}

void actSt04eFuchi3(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(229) == 0) {
        stage_SetAnimation(265, 0, 0);
        fuchi3_mes[0].func = actSt04eFuchi3Chk;
        self->mail = fuchi3_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(265, 0, -1);
    }
}

void actSt04eSe(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    se_mes[0].func = actSt04eSeChk;
    self->mail = se_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04eWater(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    SetRotObjectLockFlag(scpSearchGobj(1274), 1);

    if (gflagChk(230) == 0) {
        scpSearchGobj(1273)->f16C = 0;
        water_mes[0].func = actSt04eWaterMain;
        self->mail = water_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(1272)->f16C = 0;
        stage_SetAnimation(261, -1, -2);
    }
}

void actSt04eWaterMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = waterMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04eWaterSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    waterSwitch_mes[0].func = actSt04eWaterStop;
    sub->mail = waterSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04eWaterFlagOn(volatile int a0)
{
    int t = (0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 6.0;

    D_0063C088 = 0.005f;

    while (t-- > 0) {
        if (demoSkipped != 0) {
            D_0063C088 = 1000.0f;
            break;
        }
        _ACTWait(1);
    }

    gflagOn(230);
}

void actSt04eWaterStopSub(volatile int a0)
{
    _ACTWait(60);

    stage_SetAnimation(262, 1, 0);
    stage_SetAnimation(261, -1, -2);

    while (stage_CheckAnimationFinish(262) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt04eHint1Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 1000.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x91) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");
    gflagOn(225);
    FinishHint(18);
}

void actSt04eFuchi1Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(227);
    _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    stage_SetAnimation(263, 1, 0);
    soundSeDefPlay(1342, 0, 0, 1);

    while (stage_CheckAnimationFinish(263) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
}

void actSt04eFuchi2Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(228);
    _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    stage_SetAnimation(264, 1, 0);
    soundSeDefPlay(1342, 0, 0, 1);

    while (stage_CheckAnimationFinish(264) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
}

void actSt04eFuchi3Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(229);
    _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    stage_SetAnimation(265, 1, 0);
    soundSeDefPlay(1342, 0, 0, 1);

    while (stage_CheckAnimationFinish(265) == 0) {
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

        h = soundSeDefPlay(1340, 0, seChkPos, 1);
        _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 0.5);
        soundSeDefStop(h);

        soundSeDefPlay(1341, 0, seChkPos, 1);

        _ACTWait(1);
    }
}

void actSt04eHint1WakeUpChk(volatile int a0)
{
    while (scpTriggerFloorAttr(D_00639EA4, 0x3000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(226);
    WakeupHint(18);
}
