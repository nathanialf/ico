#include "st05e.h"
#include "layout_texture.h"
#include "thread.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "rotObject.h"
#include "typedef.h"
#include "stageSEProc.h"
#include "script.h"
#include "main.h"

#ifdef VERSION_NTSC
/* .data: four 0x20-byte actor mail packets, one per thread hand-off. */

static ActMail waterMain_mes[2] = {{376, actSt05eWaterSwitch}, {396}}; /* derived name */

static ActMail water_mes[2] = {{397}, {396}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail solar_mes[2] = {{397}, {396}}; /* derived name */
#else
static void actSt05eWaterStopSub(GObj *volatile self);

/* .data: four 0x20-byte actor mail packets, one per thread hand-off. */

static ActMail waterMain_mes[2] = {{406, actSt05eWaterSwitch}, {429}}; /* derived name */

static ActMail water_mes[2] = {{430}, {429}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail solar_mes[2] = {{430}, {429}}; /* derived name */

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for, and its complement, true when the player skipped the demo with
   START. */
static int demoEnd;

static int demoSkipped; /* derived name */

void actSt05eWaterStop(GObj *volatile self)
{
    GProc *th;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    demoEnd = 0;
    demoSkipped = 0;
    actCreateSubThread(actSt05eWaterFlagOn, 21);

    scpSleepEnemyAll();

    th = actCreateSubThread(actSt05eWaterStopSub, 21);
    while (demoEnd == 0 && (!(pad[0].flags & 0x800) || scpAdpcmPlayRequestNum() != 0)) {
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
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(263, 0, -1);
        stage_SetAnimation(262, -1, -2);
#else
        stage_SetAnimation(267, 0, -1);
        stage_SetAnimation(266, -1, -2);
#endif
        scpFadeIn(3.0f);
    }

    scpSearchGobj(1555)->active = 1;
    scpSearchGobj(1554)->active = 0;

    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    scpWakeupEnemyAll();

    SetWayGroupActive(5, 1);
}
#endif

/* .sdata: the solar stream handle. */
struct SqEntry *solar = 0;

#ifdef VERSION_NTSC
void actSt05eSolarChk(GObj *volatile self)
{
    while (scpIsRotObjectZPlusDirInclude(1452, 265, 275) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1452)->active = 0;
    scpSearchGobj(1453)->active = 1;

    if (gflagChk(218) == 0 || gflagChk(219) == 0 || gflagChk(220) == 0) {
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;

        scpSleepEnemyAll();

        scpAdpcmPlayRequestFunc(52, &solar, 1, 1, 1);

        stage_SetAnimation(237, 1, 0);

        while (stage_CheckAnimationFinish(237) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        if (solar != 0) {
            scpAdpcmFadeClose(solar, 80);
        }

        lt_switch_layout(50);

        scpBoyControlReadDisable = 0;
        scpWakeupEnemyAll();
    }

    gflagOn(207);
    gflagOff(221);
    gflagOff(222);
    gflagOff(224);

    gflagOn(208);
}

void actSt05eWater(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(206) == 0) {
        scpSearchGobj(1451)->active = 0;

        water_mes[0].func = actSt05eWaterMain;
        act->mail = water_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpSearchGobj(1450)->active = 0;

        stage_SetAnimation(235, -1, -2);
    }
}

void actSt05eSolar(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(207) == 0) {
        scpSearchGobj(1453)->active = 0;

        solar_mes[0].func = actSt05eSolarChk;
        act->mail = solar_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpSearchGobj(1452)->active = 0;
    }
}
#else
void actSt05eSolarChk(GObj *volatile self)
{
    while (scpIsRotObjectZPlusDirInclude(1556, 269, 271) == 0) {
        _ACTWait(1);
    }

    SetRotObjectLockFlag(scpSearchGobj(1556), 1);

    FinishHint(23);
    FinishHint(25);
    FinishHint(26);

    if (gflagChk(243) == 0 || gflagChk(244) == 0 || gflagChk(245) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        lt_switch_layout(52);
#else
        lt_switch_layout(55);
#endif
        scpBoyControlReadDisable = 1;

        scpSleepEnemyAll();

        scpAdpcmPlayRequestFunc(54, &solar, 1, 1, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(264, 1, 0);
#else
        stage_SetAnimation(268, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFinish(264) == 0) {
#else
        while (stage_CheckAnimationFinish(268) == 0) {
#endif
            if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
                stage_SetAnimation(264, 0, -1);
#else
                stage_SetAnimation(268, 0, -1);
#endif
                scpFadeIn(3.0f);
                break;
            }
            _ACTWait(1);
        }

        if (solar != 0) {
            scpAdpcmFadeCloseFunc(&solar, 80);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        lt_switch_layout(51);
#else
        lt_switch_layout(54);
#endif

        scpBoyControlReadDisable = 0;
        scpWakeupEnemyAll();
    }

    gflagOff(246);
    gflagOff(247);
    gflagOff(248);
    gflagOff(249);
    gflagOn(233);

    gflagOn(232);
}

void actSt05eWater(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(231) == 0) {
        scpSearchGobj(1555)->active = 0;

        water_mes[0].func = actSt05eWaterMain;
        act->mail = water_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(1554)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(262, -1, -2);
#else
        stage_SetAnimation(266, -1, -2);
#endif
    }
}

void actSt05eSolar(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    SetRotObjectArmRadius(scpSearchGobj(1556), 200.0f);

    if (gflagChk(232) == 0) {
        solar_mes[0].func = actSt05eSolarChk;
        act->mail = solar_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        SetRotObjectLockFlag(scpSearchGobj(1556), 1);

        FinishHint(23);
        FinishHint(25);
        FinishHint(26);
    }
}
#endif

void actSt05eWaterMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = waterMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
void actSt05eWaterSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;
    waterSwitch_mes[0].func = actSt05eWaterStop;
    sub->mail = waterSwitch_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt05eWaterStop(GObj *volatile self)
{
    lt_switch_layout(51);

    actCreateSubThread(actSt05eWaterFlagOn, 21);

    scpSleepEnemyAll();

    _ACTWait(60);

    stage_SetAnimation(236, 1, 0);

    stage_SetAnimation(235, -1, -2);

    while (stage_CheckAnimationFinish(236) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1451)->active = 1;
    scpSearchGobj(1450)->active = 0;

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    scpWakeupEnemyAll();

    SetWayGroupActive(5, 1);
}

void actSt05eWaterFlagOn(GObj *volatile self)
{
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 11.0);
    gflagOn(206);
}
#else
void actSt05eWaterSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;
    waterSwitch_mes[0].func = actSt05eWaterStop;
    sub->mail = waterSwitch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt05eWaterFlagOn(GObj *volatile self)
{
    int i = (60 - systemStatus[0] * 10) / systemStatus[1] * 6.0;

    riverFadeSpeed = 0.005f;

    while (i-- > 0) {
        if (demoSkipped != 0) {
            riverFadeSpeed = 1000.0f;
            break;
        }
        _ACTWait(1);
    }
    gflagOn(231);
}

static void actSt05eWaterStopSub(GObj *volatile self)
{
    _ACTWait(60);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(263, 1, 0);
#else
    stage_SetAnimation(267, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(262, -1, -2);
#else
    stage_SetAnimation(266, -1, -2);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(263) == 0) {
#else
    while (stage_CheckAnimationFinish(267) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}
#endif
