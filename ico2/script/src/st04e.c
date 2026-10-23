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
#include "main.h"
#include "script.h"

static ActMail waterMain_mes[2] = {{372, actSt04eWaterSwitch}, {392}}; /* derived name */

static ActMail water_mes[2] = {{393}, {392}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{393}, {392}}; /* derived name */

void actSt04eWater(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(205) == 0) {
        scpSearchGobj(1173)->active = 0;
        water_mes[0].func = actSt04eWaterMain;
        act->mail = water_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpSearchGobj(1172)->active = 0;
        stage_SetAnimation(232, -1, -2);
    }
}

void actSt04eWaterMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = waterMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04eWaterSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    waterSwitch_mes[0].func = actSt04eWaterStop;
    sub->mail = waterSwitch_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt04eWaterStop(GObj *volatile self)
{
    lt_switch_layout(51);

    actCreateSubThread(actSt04eWaterFlagOn, 21);

    scpSleepEnemyAll();

    _ACTWait(60);

    stage_SetAnimation(233, 1, 0);

    stage_SetAnimation(232, -1, -2);

    while (stage_CheckAnimationFinish(233) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1173)->active = 1;
    scpSearchGobj(1172)->active = 0;

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
