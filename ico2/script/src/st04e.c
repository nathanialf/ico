#include "st04e.h"
#include "debug.h"
#include "layout_texture.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "rotObject.h"
#include "typedef.h"

#ifndef VERSION_AUG6
#include "stageSEProc.h"
#endif

#include "main.h"
#include "script.h"

#ifdef VERSION_NTSC
static ActMail waterMain_mes[2] = {{376, actSt04eWaterSwitch}, {396}}; /* derived name */

static ActMail water_mes[2] = {{397}, {396}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{397}, {396}}; /* derived name */

void actSt04eWater(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    SetRotObjectLockFlag(scpSearchGobj(1178), 1);

    if (gflagChk(205) == 0) {
        scpSearchGobj(1177)->active = 0;
        water_mes[0].func = actSt04eWaterMain;
        act->mail = water_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpSearchGobj(1176)->active = 0;
        stage_SetAnimation(233, -1, -2);
    }
}
#else
#ifdef VERSION_AUG6
static ActMail waterMain_mes[2] = {{372, actSt04eWaterSwitch}, {392}}; /* derived name */

static ActMail water_mes[2] = {{393}, {392}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_JUN26
static ActMail waterMain_mes[2] = {{356, actSt04eWaterSwitch}, {376}}; /* derived name */

static ActMail water_mes[2] = {{377}, {376}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{377}, {376}}; /* derived name */
#else
static void actSt04eFuchi1Chk(GObj *volatile self);
static void actSt04eFuchi2Chk(GObj *volatile self);
static void actSt04eFuchi3Chk(GObj *volatile self);
static void actSt04eHint1Chk(GObj *volatile self);
static void actSt04eHint1WakeUpChk(GObj *volatile self);
static void actSt04eSeChk(GObj *volatile self);
static void actSt04eWaterStopSub(GObj *volatile self);

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for, and its complement, true when the player skipped the demo with
   START. */
static int demoEnd;

static int demoSkipped; /* derived name */

static ActMail waterMain_mes[2] = {{406, actSt04eWaterSwitch}, {429}}; /* derived name */

static ActMail water_mes[2] = {{430}, {429}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fuchi1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fuchi2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fuchi3_mes[2] = {{430}, {429}}; /* derived name */

static ActMail se_mes[2] = {{430}, {429}}; /* derived name */

static float seChkPos[4] = {0.0f, -171.0f, -8000.0f, 0.0f}; /* derived name */

static ActMail hint1WakeUp_mes[2] = {{430}, {429}}; /* derived name */

void actSt04eWaterStop(GObj *volatile self)
{
    GProc *th;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    demoEnd = 0;
    demoSkipped = 0;
    actCreateSubThread(actSt04eWaterFlagOn, 21);

    scpSleepEnemyAll();

    th = actCreateSubThread(actSt04eWaterStopSub, 21);

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    demoSkipped = demoEnd ^ 1;
    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(258, 0, -1);
        stage_SetAnimation(257, -1, -2);
#else
        stage_SetAnimation(262, 0, -1);
        stage_SetAnimation(261, -1, -2);
#endif
        scpFadeIn(3.0f);
    }

    scpSearchGobj(1273)->active = 1;
    scpSearchGobj(1272)->active = 0;

    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    scpWakeupEnemyAll();

    SetWayGroupActive(5, 1);
}

void actSt04eHint1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(225) == 0) {
        hint1_mes[0].func = actSt04eHint1Chk;
        act->mail = hint1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        FinishHint(18);
    }
}

void actSt04eHint1WakeUp(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(226) == 0) {
        SleepHint(18);
        hint1WakeUp_mes[0].func = actSt04eHint1WakeUpChk;
        act->mail = hint1WakeUp_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

static void actSt04eFuchi1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(227) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(259, 0, 0);
#else
        stage_SetAnimation(263, 0, 0);
#endif
        fuchi1_mes[0].func = actSt04eFuchi1Chk;
        act->mail = fuchi1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(259, 0, -1);
#else
        stage_SetAnimation(263, 0, -1);
#endif
    }
}

static void actSt04eFuchi2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(228) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(260, 0, 0);
#else
        stage_SetAnimation(264, 0, 0);
#endif
        fuchi2_mes[0].func = actSt04eFuchi2Chk;
        act->mail = fuchi2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(260, 0, -1);
#else
        stage_SetAnimation(264, 0, -1);
#endif
    }
}

static void actSt04eFuchi3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(229) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(261, 0, 0);
#else
        stage_SetAnimation(265, 0, 0);
#endif
        fuchi3_mes[0].func = actSt04eFuchi3Chk;
        act->mail = fuchi3_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(261, 0, -1);
#else
        stage_SetAnimation(265, 0, -1);
#endif
    }
}

void actSt04eSe(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    se_mes[0].func = actSt04eSeChk;
    act->mail = se_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif
#endif

void actSt04eWater(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(205) == 0) {
        scpSearchGobj(1173)->active = 0;
        water_mes[0].func = actSt04eWaterMain;
        act->mail = water_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpSearchGobj(1172)->active = 0;
        stage_SetAnimation(232, -1, -2);
#else
#ifdef VERSION_JUN26
    if (gflagChk(196) == 0) {
        scpSearchGobj(1118)->active = 0;
        water_mes[0].func = actSt04eWaterMain;
        act->mail = water_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(1117)->active = 0;
        stage_SetAnimation(207, -1, -2);
#else
    SetRotObjectLockFlag(scpSearchGobj(1274), 1);

    if (gflagChk(230) == 0) {
        scpSearchGobj(1273)->active = 0;
        water_mes[0].func = actSt04eWaterMain;
        act->mail = water_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(1272)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(257, -1, -2);
#else
        stage_SetAnimation(261, -1, -2);
#endif
#endif
#endif
    }
}
#endif

void actSt04eWaterMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_JUN26
    scpBoyControlReadDisable = 0;
#endif

    sub->mainMail = waterMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt04eWaterSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    waterSwitch_mes[0].func = actSt04eWaterStop;
    sub->mail = waterSwitch_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

void actSt04eWaterStop(GObj *volatile self)
{
    lt_switch_layout(51);

    actCreateSubThread(actSt04eWaterFlagOn, 21);

    scpSleepEnemyAll();

    _ACTWait(60);

#ifdef VERSION_AUG6
    stage_SetAnimation(233, 1, 0);

    stage_SetAnimation(232, -1, -2);

    while (stage_CheckAnimationFinish(233) == 0) {
#else
    stage_SetAnimation(234, 1, 0);

    stage_SetAnimation(233, -1, -2);

    while (stage_CheckAnimationFinish(234) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    scpSearchGobj(1173)->active = 1;
    scpSearchGobj(1172)->active = 0;
#else
    scpSearchGobj(1177)->active = 1;
    scpSearchGobj(1176)->active = 0;
#endif

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    scpWakeupEnemyAll();

    SetWayGroupActive(5, 1);
}

void actSt04eWaterFlagOn(GObj *volatile self)
{
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 11.0);
    gflagOn(205);
}
#else
#ifdef VERSION_JUN26
void actSt04eWaterSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    waterSwitch_mes[0].func = actSt04eWaterStop;
    sub->mail = waterSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt04eWaterStop(GObj *volatile self)
{
    lt_switch_layout(51);

    gflagOn(196);

    _ACTWait(60);

    stage_SetAnimation(208, 1, 0);

    stage_SetAnimation(207, -1, -2);

    while (stage_CheckAnimationFinish(208) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1118)->active = 1;
    scpSearchGobj(1117)->active = 0;

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    SetWayGroupActive(5, 1);
}
#else
void actSt04eWaterSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    waterSwitch_mes[0].func = actSt04eWaterStop;
    sub->mail = waterSwitch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04eWaterFlagOn(GObj *volatile self)
{
    int t = (60 - systemStatus[0] * 10) / systemStatus[1] * 6.0;

    riverFadeSpeed = 0.005f;

    while (t-- > 0) {
        if (demoSkipped != 0) {
            riverFadeSpeed = 1000.0f;
            break;
        }
        _ACTWait(1);
    }

    gflagOn(230);
}

static void actSt04eWaterStopSub(GObj *volatile self)
{
    _ACTWait(60);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(258, 1, 0);
    stage_SetAnimation(257, -1, -2);
#else
    stage_SetAnimation(262, 1, 0);
    stage_SetAnimation(261, -1, -2);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(258) == 0) {
#else
    while (stage_CheckAnimationFinish(262) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

static void actSt04eHint1Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 1000.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) != 145) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");
    gflagOn(225);
    FinishHint(18);
}

static void actSt04eFuchi1Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(227);
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1]);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(259, 1, 0);
#else
    stage_SetAnimation(263, 1, 0);
#endif
    soundSeDefPlay(1342, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(259) == 0) {
#else
    while (stage_CheckAnimationFinish(263) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
}

static void actSt04eFuchi2Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(228);
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1]);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(260, 1, 0);
#else
    stage_SetAnimation(264, 1, 0);
#endif
    soundSeDefPlay(1342, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(260) == 0) {
#else
    while (stage_CheckAnimationFinish(264) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
}

static void actSt04eFuchi3Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(229);
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1]);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(261, 1, 0);
#else
    stage_SetAnimation(265, 1, 0);
#endif
    soundSeDefPlay(1342, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(261) == 0) {
#else
    while (stage_CheckAnimationFinish(265) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
}

static void actSt04eSeChk(GObj *volatile self)
{
    int h;

    while (1) {
        while (ForMotionViewer_GetCurrentMotion(boyGObj) != 173 &&
               ForMotionViewer_GetCurrentMotion(boyGObj) != 177) {
            _ACTWait(1);
        }

        h = soundSeDefPlay(1340, 0, seChkPos, 1);
        _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 0.5);
        soundSeDefStop(h);

        soundSeDefPlay(1341, 0, seChkPos, 1);

        _ACTWait(1);
    }
}

static void actSt04eHint1WakeUpChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(226);
    WakeupHint(18);
}
#endif
#endif
