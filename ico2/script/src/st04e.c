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
#include "stageSEProc.h"
#include "main.h"
#include "script.h"

static void actSt04eFuchi1Chk(GObj *volatile self);
static void actSt04eFuchi2Chk(GObj *volatile self);
static void actSt04eFuchi3Chk(GObj *volatile self);
static void actSt04eHint1Chk(GObj *volatile self);
static void actSt04eHint1WakeUpChk(GObj *volatile self);
static void actSt04eSeChk(GObj *volatile self);
static void actSt04eWaterStopSub(GObj *volatile self);

/* No .sbss here in this build: no function of the demo addresses these flags. */

static ActMail waterMain_mes[2] = {{356, actSt04eWaterSwitch}, {376}}; /* derived name */

static ActMail water_mes[2] = {{377}, {376}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{377}, {376}}; /* derived name */

void actSt04eWater(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(196) == 0) {
        scpSearchGobj(1118)->active = 0;
        water_mes[0].func = actSt04eWaterMain;
        act->mail = water_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(1117)->active = 0;
        stage_SetAnimation(207, -1, -2);
    }
}

void actSt04eWaterMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

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
