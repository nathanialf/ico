#include "st04c.h"
#include "layout_texture.h"
#include "thread.h"
#include "s_init.h"
#include "commonact.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "act.h"
#include "gobj_process.h"
#include "typedef.h"
#include "generator.h"
#include "script.h"
#include "main.h"

#ifdef VERSION_NTSC
void actSt04cEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(146) == 0) {
            gflagOn(358);
        }
    }
}
#else
#ifdef VERSION_AUG6
/* .sdata: the intro stream's handle, which actSt04cIntroChk fades out */
SqEntry *intro = 0;
#else
static void actSt04cIntroChkSub(GObj *volatile self);
#endif

void actSt04cEnd(void)
{
    if (girlGObj != 0) {
#ifdef VERSION_AUG6
        if (gflagChk(146) == 0) {
            gflagOn(357);
#else
        if (gflagChk(163) == 0) {
            gflagOn(391);
#endif
        }
    }
}
#endif

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const StVec doorDownChkPos = {{0.0f, 84.0f, -1359.0f, 0.0f}}; /* derived name */

static const ConstVec doorDownEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorDownEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorDownEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}}; /* derived name */

#ifdef VERSION_NTSC
void actSt04cDoorDownChk(GObj *volatile self)
{
    StVec pos;

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    _ACTWait(30);

    actCreateSubThread(actSt04cDoorDownEffect, 21);

    stage_SetAnimation(225, 1, 0);

    pos = doorDownChkPos;

    _ACTWait(30);
    soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(225) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(145);
}

void actSt04lDoorChk(GObj *volatile self)
{
    GObj *x = self;
    int h;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(179) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1010))) {
        case 0:
            _ACTWait(1);
            break;

        case 1:
            stage_SetAnimation(204, 1, 0);
            while (stage_CheckAnimationFinish(204) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;

        case 2:
            scpSearchGobj(1010)->active = 0;

            lt_switch_layout(51);

            scpBoyControlReadDisable = 1;
            scpSleepEnemyAll();

            gflagOn(179);

            stage_SetAnimation(203, 1, 0);

            h = soundSeDefPlay(1306, 0, 0, 1);

            _ACTWait(90);

            soundSeDefStop(h);

            soundSeDefPlay(1307, 0, 0, 1);

            scpWakeupEnemyAll();
            scpBoyControlReadDisable = 0;

            lt_switch_layout(50);
            break;
        }
    }
}

void actSt04cSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(124) == 0) {
        stage_SetAnimation(269, -1, -2);
    }
}

static ActMail doorDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st04lDoor_mes[2] = {{397}, {396}}; /* derived name */

void actSt04lDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(179) == 0) {
        stage_SetAnimation(203, 0, 0);
        st04lDoor_mes[0].func = actSt04lDoorChk;
        act->mail = st04lDoor_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(203, 0, -1);
        scpSearchGobj(1010)->active = 0;
    }
}

void actSt04cIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(144) == 0) {
        intro_mes[0].func = actSt04cIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04cDoorDown(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    if (gflagChk(145) == 0) {
        doorDown_mes[0].func = actSt04cDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04cEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(146) == 0) {
        ene_mes[0].func = actSt04cEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04cEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);
    while (gflagChk(147) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04cEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);
    while (gflagChk(147) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04cWaterXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(205) != 0) {
        scpSearchGobj(1006)->active = 0;
    }
}
#else
void actSt04cDoorDownChk(GObj *volatile self)
{
    StVec pos;

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    _ACTWait(30);

    actCreateSubThread(actSt04cDoorDownEffect, 21);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(249, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(224, 1, 0);
#else
    stage_SetAnimation(253, 1, 0);
#endif
#endif

    pos = doorDownChkPos;

    _ACTWait(30);
#ifdef VERSION_AUG6
    soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(224) == 0) {
#else
    soundSeDefPlay(1221, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, pos.f, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(249) == 0) {
#else
    while (stage_CheckAnimationFinish(253) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    gflagOn(145);
#else
    gflagOn(162);
}

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for. */
static int demoEnd;

void actSt04cIntroChk(GObj *volatile self)
{
    GProc *th;

    while (scpTriggerBall(self, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    gflagOff(390);

    gflagOn(161);
    scpBoyControlReadDisable = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(348, 1, 0);
#else
    stage_SetAnimation(352, 1, 0);
#endif

    th = actCreateSubThread(actSt04cIntroChkSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && (!(pad[0].flags & 0x800) || scpAdpcmPlayRequestNum() != 0)) {
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
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(348, 0, -1);
#else
        stage_SetAnimation(352, 0, -1);
#endif
        scpFadeIn(3.0f);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
#endif
}

void actSt04lDoorChk(GObj *volatile self)
{
    GObj *x = self;
    int h;
#ifndef VERSION_AUG6
    int i;
#endif

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    while (gflagChk(179) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1007))) {
#else
    while (gflagChk(199) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1098))) {
#endif
        case 0:
            _ACTWait(1);
            break;

        case 1:
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(228, 1, 0);
            while (stage_CheckAnimationFinish(228) == 0) {
#else
#ifdef VERSION_AUG6
            stage_SetAnimation(203, 1, 0);
            while (stage_CheckAnimationFinish(203) == 0) {
#else
            stage_SetAnimation(232, 1, 0);
            while (stage_CheckAnimationFinish(232) == 0) {
#endif
#endif
                _ACTWait(1);
            }
            _ACTWait(1);
            break;

        case 2:
#ifdef VERSION_AUG6
            scpSearchGobj(1007)->active = 0;

            lt_switch_layout(51);
#else
            scpSearchGobj(1098)->active = 0;
            FinishHint(15);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            lt_switch_layout(52);
#else
            lt_switch_layout(55);
#endif
#endif

            scpBoyControlReadDisable = 1;
            scpSleepEnemyAll();

#ifdef VERSION_AUG6
            gflagOn(179);

            stage_SetAnimation(202, 1, 0);

            h = soundSeDefPlay(1306, 0, 0, 1);

            _ACTWait(90);
#else
            gflagOn(199);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(227, 1, 0);
#else
            stage_SetAnimation(231, 1, 0);
#endif

            h = soundSeDefPlay(1330, 0, 0, 1);

            for (i = 90; i-- > 0;) {
                if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
                    scpFadeOut(16.0f, 0, 0, 0);
                    while (scpFadeChk() != 0) {
                        _ACTWait(1);
                    }
                    while (lt_fade_status() != 2) {
                        _ACTWait(1);
                    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
                    stage_SetAnimation(227, 0, -1);
#else
                    stage_SetAnimation(231, 0, -1);
#endif
                    scpFadeIn(3.0f);
                    break;
                }
                _ACTWait(1);
            }
#endif

            soundSeDefStop(h);

#ifdef VERSION_AUG6
            soundSeDefPlay(1307, 0, 0, 1);
#else
            soundSeDefPlay(1331, 0, 0, 1);
#endif

            scpWakeupEnemyAll();
            scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            lt_switch_layout(51);
#else
#ifdef VERSION_AUG6
            lt_switch_layout(50);
#else
            lt_switch_layout(54);
#endif
#endif
            break;
        }
    }
}

void actSt04cSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(124) == 0) {
        stage_SetAnimation(268, -1, -2);
#else
    if (gflagChk(138) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(298, -1, -2);
#else
        stage_SetAnimation(302, -1, -2);
#endif
#endif
    }
}

#ifdef VERSION_AUG6
static ActMail doorDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

static ActMail intro_mes[2] = {{393}, {392}}; /* derived name */

static ActMail st04lDoor_mes[2] = {{393}, {392}}; /* derived name */
#else
static ActMail doorDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail intro_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st04lDoor_mes[2] = {{430}, {429}}; /* derived name */
#endif

void actSt04lDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(179) == 0) {
        stage_SetAnimation(202, 0, 0);
        st04lDoor_mes[0].func = actSt04lDoorChk;
        act->mail = st04lDoor_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(202, 0, -1);
        scpSearchGobj(1007)->active = 0;
#else
    if (gflagChk(199) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(227, 0, 0);
#else
        stage_SetAnimation(231, 0, 0);
#endif
        st04lDoor_mes[0].func = actSt04lDoorChk;
        act->mail = st04lDoor_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(227, 0, -1);
#else
        stage_SetAnimation(231, 0, -1);
#endif
        scpSearchGobj(1098)->active = 0;
        FinishHint(15);
#endif
    }
}

void actSt04cIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(144) == 0) {
        intro_mes[0].func = actSt04cIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(161) == 0) {
        intro_mes[0].func = actSt04cIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04cDoorDown(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

#ifdef VERSION_AUG6
    if (gflagChk(145) == 0) {
        doorDown_mes[0].func = actSt04cDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(162) == 0) {
        doorDown_mes[0].func = actSt04cDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04cEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(146) == 0) {
        ene_mes[0].func = actSt04cEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(163) == 0) {
        ene_mes[0].func = actSt04cEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04cEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);
#ifdef VERSION_AUG6
    while (gflagChk(147) == 0) {
#else
    while (gflagChk(164) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04cEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);
#ifdef VERSION_AUG6
    while (gflagChk(147) == 0) {
#else
    while (gflagChk(164) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04cWaterXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(205) != 0) {
        scpSearchGobj(1003)->active = 0;
#else
    if (gflagChk(230) != 0) {
        scpSearchGobj(1094)->active = 0;
#endif
    }
}
#endif

void actSt04cDoorDownEvent(int x)
{
    volatile int local = x;
}

void actSt04cDoorDownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long b3[2];
    long long v0a = doorDownEffectPos.d[0];
    long long v0b = doorDownEffect2Pos.d[0];
    long long v0c = doorDownEffect3Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorDownEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorDownEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            b3[0] = v0c;
            b3[1] = doorDownEffect3Pos.d[1];
            scpEffectStart((int *)b3, 0);
            break;
        }
        _ACTWait(1);
    }
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt04cEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0xB000000) == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_AUG6
    gflagOff(357);
#else
    gflagOff(358);
#endif
    _ACTWait(1);
    gflagOn(146);
    gflagOn(147);
}

#ifndef VERSION_AUG6
/* .sdata: the stream handle actSt04cIntroChk fades out when the intro ends */
SqEntry *intro = 0;
#endif

void actSt04cIntroChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

#ifdef VERSION_AUG6
    gflagOff(356);
#else
    gflagOff(357);
#endif

    gflagOn(144);
    scpBoyControlReadDisable = 1;

#ifdef VERSION_AUG6
    stage_SetAnimation(318, 1, 0);

    while (stage_CheckAnimationFinish(318) == 0) {
#else
    stage_SetAnimation(319, 1, 0);

    while (stage_CheckAnimationFinish(319) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    if (intro != 0) {
        scpAdpcmFadeClose(intro, 80);
    }

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}
#else
void actSt04cEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0xB000000) == 0) {
        _ACTWait(1);
    }
    gflagOff(391);
    _ACTWait(1);
    gflagOn(163);
    gflagOn(164);
}

static void actSt04cIntroChkSub(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(348) == 0) {
#else
    while (stage_CheckAnimationFinish(352) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}
#endif

void actSt04lDoorEvent(int x)
{
    volatile int local = x;
}
