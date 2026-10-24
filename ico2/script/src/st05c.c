#include "st05c.h"
#include "layout_texture.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "st04c.h"
#include "typedef.h"
#include "script.h"
#include "main.h"

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
static void actSt04rDoor2Sub(GObj *volatile self);
static void actSt04rDoorSub(GObj *volatile self);
static void actSt05cCrestHintChk(GObj *volatile self);

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for. */
static int demoEnd;
#endif

static const StVec doorDownChkPos = {{0.0f, 84.0f, -1359.0f, 0.0f}}; /* derived name */

static const StVec doorDownEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}}; /* derived name */

static const StVec doorDownEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}}; /* derived name */

static const StVec doorDownEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}}; /* derived name */

#ifdef VERSION_NTSC
static ActMail doorDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st04rDoor_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st04rDoor2_mes[2] = {{397}, {396}}; /* derived name */

void actSt05cDoorDownChk(GObj *volatile self)
{
    StVec pos;

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    _ACTWait(30);
    gflagOff(357);
    actCreateSubThread(actSt05cDoorDownEffect, 21);
    stage_SetAnimation(314, 1, 0);

    pos = doorDownChkPos;
    _ACTWait(30);
    soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(314) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    gflagOn(148);
    scpBoyControlReadDisable = 0;
}

void actSt04rDoorChk(GObj *volatile self)
{
    GObj *x = self;
    int se;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(230) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1280))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(301, 1, 0);
            while (stage_CheckAnimationFinish(301) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1280)->active = 0;
            lt_switch_layout(51);
            scpBoyControlReadDisable = 1;
            scpSleepEnemyAll();
            gflagOn(230);
            stage_SetAnimation(299, 1, 0);
            se = soundSeDefPlay(1306, 0, 0, 1);
            _ACTWait(90);
            soundSeDefStop(se);
            soundSeDefPlay(1307, 0, 0, 1);
            scpWakeupEnemyAll();
            scpBoyControlReadDisable = 0;
            lt_switch_layout(50);
            break;
        }
    }
}

void actSt04rDoor2Chk(GObj *volatile self)
{
    GObj *x = self;
    int se;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(231) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1281))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(302, 1, 0);
            while (stage_CheckAnimationFinish(302) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1281)->active = 0;
            lt_switch_layout(51);
            scpBoyControlReadDisable = 1;
            scpSleepEnemyAll();
            gflagOn(231);
            stage_SetAnimation(300, 1, 0);
            se = soundSeDefPlay(1306, 0, 0, 1);
            _ACTWait(90);
            soundSeDefStop(se);
            soundSeDefPlay(1307, 0, 0, 1);
            scpWakeupEnemyAll();
            scpBoyControlReadDisable = 0;
            lt_switch_layout(50);
            break;
        }
    }
}

void actSt05cSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(125) == 0) {
        stage_SetAnimation(271, -1, -2);
    }
}

void actSt05cWaterXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(206) != 0) {
        scpSearchGobj(1276)->active = 0;
    }
}

void actSt04rDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(230) == 0) {
        stage_SetAnimation(299, 0, 0);
        st04rDoor_mes[0].func = actSt04rDoorChk;
        act->mail = st04rDoor_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(299, 0, -1);
        scpSearchGobj(1280)->active = 0;
    }
}

void actSt04rDoor2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(231) == 0) {
        stage_SetAnimation(300, 0, 0);
        st04rDoor2_mes[0].func = actSt04rDoor2Chk;
        act->mail = st04rDoor2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(300, 0, -1);
        scpSearchGobj(1281)->active = 0;
    }
}

void actSt05cDoorDown(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    if (gflagChk(148) == 0) {
        doorDown_mes[0].func = actSt05cDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt05cEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(150) == 0) {
        ene_mes[0].func = actSt05cEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt05cEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(151) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_MaskOff(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt05cEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(151) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}
#else
#ifdef VERSION_AUG6
static ActMail doorDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

static ActMail st04rDoor_mes[2] = {{393}, {392}}; /* derived name */

static ActMail st04rDoor2_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_JUN26
static ActMail doorDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

static ActMail st04rDoor_mes[2] = {{377}, {376}}; /* derived name */

static ActMail st04rDoor2_mes[2] = {{377}, {376}}; /* derived name */
#else
static ActMail doorDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st04rDoor_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st04rDoor2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crestHint_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif

void actSt05cDoorDownChk(GObj *volatile self)
{
    StVec pos;

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    _ACTWait(30);
#ifdef VERSION_AUG6
    gflagOff(356);
    actCreateSubThread(actSt05cDoorDownEffect, 21);
    stage_SetAnimation(313, 1, 0);
#else
#ifdef VERSION_JUN26
    actCreateSubThread(actSt05cDoorDownEffect, 21);
    stage_SetAnimation(281, 1, 0);
#else
    gflagOff(390);
    actCreateSubThread(actSt05cDoorDownEffect, 21);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(343, 1, 0);
#else
    stage_SetAnimation(347, 1, 0);
#endif
#endif
#endif

    pos = doorDownChkPos;
    _ACTWait(30);
#ifdef VERSION_AUG6
    soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(313) == 0) {
#else
#ifdef VERSION_JUN26
    soundSeDefPlay(1171, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefPlay(1172, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(281) == 0) {
#else
    soundSeDefPlay(1221, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, pos.f, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(343) == 0) {
#else
    while (stage_CheckAnimationFinish(347) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
#ifdef VERSION_AUG6
    gflagOn(148);
#else
#ifdef VERSION_JUN26
    gflagOn(141);
#else
    gflagOn(165);
#endif
#endif
    scpBoyControlReadDisable = 0;
}

void actSt04rDoorChk(GObj *volatile self)
{
    GObj *x = self;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    int se;
#else
    GProc *th;
#endif

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    while (gflagChk(230) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1276))) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(221) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1216))) {
#else
    while (gflagChk(255) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1380))) {
#endif
#endif
        case 0:
            _ACTWait(1);
            break;
        case 1:
#ifndef VERSION_JUN26
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(330, 1, 0);
            while (stage_CheckAnimationFinish(330) == 0) {
#else
#ifdef VERSION_AUG6
            stage_SetAnimation(300, 1, 0);
            while (stage_CheckAnimationFinish(300) == 0) {
#else
            stage_SetAnimation(334, 1, 0);
            while (stage_CheckAnimationFinish(334) == 0) {
#endif
#endif
                _ACTWait(1);
            }
#endif
            _ACTWait(1);
            break;
        case 2:
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
            scpSearchGobj(1216)->active = 0;
#else
            scpSearchGobj(1276)->active = 0;
#endif
            lt_switch_layout(51);
            scpBoyControlReadDisable = 1;
            scpSleepEnemyAll();
#ifdef VERSION_JUN26
            gflagOn(221);
            stage_SetAnimation(268, 1, 0);
            se = soundSeDefPlay(1275, 0, 0, 1);
            _ACTWait(180);
            soundSeDefStop(se);
            soundSeDefPlay(1276, 0, 0, 1);
#else
            gflagOn(230);
            stage_SetAnimation(298, 1, 0);
            se = soundSeDefPlay(1306, 0, 0, 1);
            _ACTWait(90);
            soundSeDefStop(se);
            soundSeDefPlay(1307, 0, 0, 1);
#endif
            scpWakeupEnemyAll();
            scpBoyControlReadDisable = 0;
            lt_switch_layout(50);
#else
            scpSearchGobj(1380)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            lt_switch_layout(52);
#else
            lt_switch_layout(55);
#endif
            scpBoyControlReadDisable = 1;
            scpSleepEnemyAll();
            gflagOn(255);
            demoEnd = 0;
            th = actCreateSubThread(actSt04rDoorSub, 21);

            while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
                _ACTWait(1);
            }

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
                stage_SetAnimation(328, 0, -1);
#else
                stage_SetAnimation(332, 0, -1);
#endif
                scpFadeIn(3.0f);
            }

            soundSeDefPlay(1331, 0, 0, 1);
            scpWakeupEnemyAll();
            scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            lt_switch_layout(51);
#else
            lt_switch_layout(54);
#endif
#endif
            break;
        }
    }
}

void actSt04rDoor2Chk(GObj *volatile self)
{
    GObj *x = self;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    int se;
#else
    GProc *th;
#endif

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    while (gflagChk(231) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1277))) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(222) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1217))) {
#else
    while (gflagChk(256) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1381))) {
#endif
#endif
        case 0:
            _ACTWait(1);
            break;
        case 1:
#ifndef VERSION_JUN26
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(331, 1, 0);
            while (stage_CheckAnimationFinish(331) == 0) {
#else
#ifdef VERSION_AUG6
            stage_SetAnimation(301, 1, 0);
            while (stage_CheckAnimationFinish(301) == 0) {
#else
            stage_SetAnimation(335, 1, 0);
            while (stage_CheckAnimationFinish(335) == 0) {
#endif
#endif
                _ACTWait(1);
            }
#endif
            _ACTWait(1);
            break;
        case 2:
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
            scpSearchGobj(1217)->active = 0;
#else
            scpSearchGobj(1277)->active = 0;
#endif
            lt_switch_layout(51);
            scpBoyControlReadDisable = 1;
            scpSleepEnemyAll();
#ifdef VERSION_JUN26
            gflagOn(222);
            stage_SetAnimation(269, 1, 0);
            se = soundSeDefPlay(1275, 0, 0, 1);
            _ACTWait(180);
            soundSeDefStop(se);
            soundSeDefPlay(1276, 0, 0, 1);
#else
            gflagOn(231);
            stage_SetAnimation(299, 1, 0);
            se = soundSeDefPlay(1306, 0, 0, 1);
            _ACTWait(90);
            soundSeDefStop(se);
            soundSeDefPlay(1307, 0, 0, 1);
#endif
            scpWakeupEnemyAll();
            scpBoyControlReadDisable = 0;
            lt_switch_layout(50);
#else
            scpSearchGobj(1381)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            lt_switch_layout(52);
#else
            lt_switch_layout(55);
#endif
            scpBoyControlReadDisable = 1;
            scpSleepEnemyAll();
            gflagOn(256);
            demoEnd = 0;
            th = actCreateSubThread(actSt04rDoor2Sub, 21);

            while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
                _ACTWait(1);
            }

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
                stage_SetAnimation(329, 0, -1);
#else
                stage_SetAnimation(333, 0, -1);
#endif
                scpFadeIn(3.0f);
            }

            soundSeDefPlay(1331, 0, 0, 1);
            scpWakeupEnemyAll();
            scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            lt_switch_layout(51);
#else
            lt_switch_layout(54);
#endif
#endif
            break;
        }
    }
}

void actSt05cSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(125) == 0) {
        stage_SetAnimation(270, -1, -2);
#else
#ifdef VERSION_JUN26
    if (gflagChk(118) == 0) {
        stage_SetAnimation(244, -1, -2);
#else
    if (gflagChk(139) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(300, -1, -2);
#else
        stage_SetAnimation(304, -1, -2);
#endif
#endif
#endif
    }
}

void actSt05cWaterXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(206) != 0) {
        scpSearchGobj(1272)->active = 0;
#else
#ifdef VERSION_JUN26
    if (gflagChk(197) != 0) {
        scpSearchGobj(1213)->active = 0;
#else
    if (gflagChk(231) != 0) {
        scpSearchGobj(1376)->active = 0;
#endif
#endif
    }
}

void actSt04rDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(230) == 0) {
        stage_SetAnimation(298, 0, 0);
        st04rDoor_mes[0].func = actSt04rDoorChk;
        act->mail = st04rDoor_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(298, 0, -1);
        scpSearchGobj(1276)->active = 0;
#else
#ifdef VERSION_JUN26
    if (gflagChk(221) == 0) {
        stage_SetAnimation(268, 0, 0);
        st04rDoor_mes[0].func = actSt04rDoorChk;
        act->mail = st04rDoor_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(268, 0, -1);
        scpSearchGobj(1216)->active = 0;
#else
    if (gflagChk(255) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(328, 0, 0);
#else
        stage_SetAnimation(332, 0, 0);
#endif
        st04rDoor_mes[0].func = actSt04rDoorChk;
        act->mail = st04rDoor_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(328, 0, -1);
#else
        stage_SetAnimation(332, 0, -1);
#endif
        scpSearchGobj(1380)->active = 0;
#endif
#endif
    }
}

void actSt04rDoor2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(231) == 0) {
        stage_SetAnimation(299, 0, 0);
        st04rDoor2_mes[0].func = actSt04rDoor2Chk;
        act->mail = st04rDoor2_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(299, 0, -1);
        scpSearchGobj(1277)->active = 0;
#else
#ifdef VERSION_JUN26
    if (gflagChk(222) == 0) {
        stage_SetAnimation(269, 0, 0);
        st04rDoor2_mes[0].func = actSt04rDoor2Chk;
        act->mail = st04rDoor2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(269, 0, -1);
        scpSearchGobj(1217)->active = 0;
#else
    if (gflagChk(256) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(329, 0, 0);
#else
        stage_SetAnimation(333, 0, 0);
#endif
        st04rDoor2_mes[0].func = actSt04rDoor2Chk;
        act->mail = st04rDoor2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(329, 0, -1);
#else
        stage_SetAnimation(333, 0, -1);
#endif
        scpSearchGobj(1381)->active = 0;
#endif
#endif
    }
}

void actSt05cDoorDown(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

#ifdef VERSION_AUG6
    if (gflagChk(148) == 0) {
        doorDown_mes[0].func = actSt05cDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(141) == 0) {
        doorDown_mes[0].func = actSt05cDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(165) == 0) {
        doorDown_mes[0].func = actSt05cDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt05cEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(150) == 0) {
        ene_mes[0].func = actSt05cEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(143) == 0) {
        ene_mes[0].func = actSt05cEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(167) == 0) {
        ene_mes[0].func = actSt05cEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt05cEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(151) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(144) == 0) {
#else
    while (gflagChk(168) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_MaskOff(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt05cEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(151) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(144) == 0) {
#else
    while (gflagChk(168) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
}

void actSt05cCrestHint(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(169) == 0) {
        SleepHint(23);
        crestHint_mes[0].func = actSt05cCrestHintChk;
        act->mail = crestHint_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
#endif
}
#endif

void actSt05cDoorDownEvent(int x)
{
    volatile int local = x;
}

void actSt05cDoorDownEffect(GObj *volatile self)
{
    StVec a;
    StVec b;
    StVec c;
    int i;

    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            a = doorDownEffectPos;
            scpEffectStart(&a, 0);
            break;
        case 30:
            b = doorDownEffect2Pos;
            scpEffectStart(&b, 0);
            c = doorDownEffect3Pos;
            scpEffectStart(&c, 0);
            break;
        }
        _ACTWait(1);
    }
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
void actSt05cEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

#ifdef VERSION_JUN26
    while (girlGObj == 0 || gflagChk(221) == 0) {
#else
    while (girlGObj == 0 || gflagChk(230) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(600);
#ifdef VERSION_JUN26
    gflagOn(143);
    gflagOn(144);
#else
    gflagOn(150);
    gflagOn(151);
#endif
}
#else
void actSt05cEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (girlGObj == 0 || gflagChk(255) == 0) {
        _ACTWait(1);
    }

    _ACTWait(600);
    gflagOn(167);
    gflagOn(168);
}

static void actSt04rDoorSub(GObj *volatile self)
{
    int h;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(328, 1, 0);
#else
    stage_SetAnimation(332, 1, 0);
#endif
    h = soundSeDefPlay(1330, 0, 0, 1);
    _ACTWait(90);
    soundSeDefStop(h);
    demoEnd = 1;
    _ACTWait(0);
}

static void actSt04rDoor2Sub(GObj *volatile self)
{
    int h;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(329, 1, 0);
#else
    stage_SetAnimation(333, 1, 0);
#endif
    h = soundSeDefPlay(1330, 0, 0, 1);
    _ACTWait(90);
    soundSeDefStop(h);
    demoEnd = 1;
    _ACTWait(0);
}

static void actSt05cCrestHintChk(GObj *volatile self)
{
    while (gflagChk(243) == 0 || gflagChk(244) == 0 || gflagChk(245) == 0 || gflagChk(232) != 0) {
        _ACTWait(1);
    }

    gflagOn(169);
    WakeupHint(23);
}
#endif
