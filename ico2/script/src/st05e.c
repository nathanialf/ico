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

/* .data: four 0x20-byte actor mail packets, one per thread hand-off. */

static ActMail waterMain_mes[2] = {{376, actSt05eWaterSwitch}, {396}}; /* derived name */

static ActMail water_mes[2] = {{397}, {396}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail solar_mes[2] = {{397}, {396}}; /* derived name */

/* .sdata: the solar stream handle. */
struct SqEntry *solar = 0;

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

void actSt05eWaterMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = waterMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

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
