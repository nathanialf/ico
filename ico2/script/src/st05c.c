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

static const StVec doorDownChkPos = {{0.0f, 84.0f, -1359.0f, 0.0f}}; /* derived name */

static const StVec doorDownEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}}; /* derived name */

static const StVec doorDownEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}}; /* derived name */

static const StVec doorDownEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}}; /* derived name */

static ActMail doorDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

static ActMail st04rDoor_mes[2] = {{393}, {392}}; /* derived name */

static ActMail st04rDoor2_mes[2] = {{393}, {392}}; /* derived name */

void actSt05cDoorDownChk(GObj *volatile self)
{
    StVec pos;

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    _ACTWait(30);
    gflagOff(356);
    actCreateSubThread(actSt05cDoorDownEffect, 21);
    stage_SetAnimation(313, 1, 0);

    pos = doorDownChkPos;
    _ACTWait(30);
    soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(313) == 0) {
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
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1276))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(300, 1, 0);
            while (stage_CheckAnimationFinish(300) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1276)->active = 0;
            lt_switch_layout(51);
            scpBoyControlReadDisable = 1;
            scpSleepEnemyAll();
            gflagOn(230);
            stage_SetAnimation(298, 1, 0);
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
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1277))) {
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
            scpSearchGobj(1277)->active = 0;
            lt_switch_layout(51);
            scpBoyControlReadDisable = 1;
            scpSleepEnemyAll();
            gflagOn(231);
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

void actSt05cSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(125) == 0) {
        stage_SetAnimation(270, -1, -2);
    }
}

void actSt05cWaterXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(206) != 0) {
        scpSearchGobj(1272)->active = 0;
    }
}

void actSt04rDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(230) == 0) {
        stage_SetAnimation(298, 0, 0);
        st04rDoor_mes[0].func = actSt04rDoorChk;
        act->mail = st04rDoor_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(298, 0, -1);
        scpSearchGobj(1276)->active = 0;
    }
}

void actSt04rDoor2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(231) == 0) {
        stage_SetAnimation(299, 0, 0);
        st04rDoor2_mes[0].func = actSt04rDoor2Chk;
        act->mail = st04rDoor2_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(299, 0, -1);
        scpSearchGobj(1277)->active = 0;
    }
}

void actSt05cDoorDown(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    if (gflagChk(148) == 0) {
        doorDown_mes[0].func = actSt05cDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 393);
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
        ACTSendMailCorrect(self, 393);
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

void actSt05cEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (girlGObj == 0 || gflagChk(230) == 0) {
        _ACTWait(1);
    }

    _ACTWait(600);
    gflagOn(150);
    gflagOn(151);
}
