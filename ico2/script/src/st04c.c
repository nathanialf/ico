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

void actSt04cEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(146) == 0) {
            gflagOn(358);
        }
    }
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const StVec doorDownChkPos = {{0.0f, 84.0f, -1359.0f, 0.0f}}; /* derived name */

static const ConstVec doorDownEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorDownEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorDownEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}}; /* derived name */

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

void actSt04cEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0xB000000) == 0) {
        _ACTWait(1);
    }
    gflagOff(358);
    _ACTWait(1);
    gflagOn(146);
    gflagOn(147);
}

/* .sdata: the stream handle actSt04cIntroChk fades out when the intro ends */
static SqEntry *st04cIntro = 0; /* derived name */

void actSt04cIntroChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    gflagOff(357);

    gflagOn(144);
    scpBoyControlReadDisable = 1;

    stage_SetAnimation(319, 1, 0);

    while (stage_CheckAnimationFinish(319) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (st04cIntro != 0) {
        scpAdpcmFadeCloseFunc(st04cIntro, 80);
    }

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt04lDoorEvent(int x)
{
    volatile int local = x;
}
