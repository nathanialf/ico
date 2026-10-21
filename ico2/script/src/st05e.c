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

static ActMail waterMain_mes[2] = {{356, actSt05eWaterSwitch}, {376}}; /* derived name */

static ActMail water_mes[2] = {{377}, {376}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail solar_mes[2] = {{377}, {376}}; /* derived name */

/* No .sbss here in this build: no function of the demo addresses these flags. */

/* .sdata: the solar stream handle. */
struct SqEntry *solar = 0;

void actSt05eSolarChk(GObj *volatile self)
{
    while (scpIsRotObjectZPlusDirInclude(1380, 265, 275) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1380)->active = 0;
    scpSearchGobj(1381)->active = 1;

    if (gflagChk(209) == 0 || gflagChk(210) == 0 || gflagChk(211) == 0) {
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;

        scpAdpcmPlayRequestFunc(2, &solar, 1, 1, 1);

        stage_SetAnimation(211, 1, 0);

        while (stage_CheckAnimationFinish(211) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        if (solar != 0) {
            scpAdpcmFadeClose(solar, 80);
        }

        lt_switch_layout(50);

        scpBoyControlReadDisable = 0;
    }

    gflagOn(198);
    gflagOff(212);
    gflagOff(213);
    gflagOff(215);

    gflagOn(199);
}

void actSt05eWater(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(197) == 0) {
        scpSearchGobj(1379)->active = 0;

        water_mes[0].func = actSt05eWaterMain;
        act->mail = water_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(1378)->active = 0;

        stage_SetAnimation(209, -1, -2);
    }
}

void actSt05eSolar(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(198) == 0) {
        scpSearchGobj(1381)->active = 0;

        solar_mes[0].func = actSt05eSolarChk;
        act->mail = solar_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(1380)->active = 0;
    }
}

void actSt05eWaterMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

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
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt05eWaterStop(GObj *volatile self)
{
    lt_switch_layout(51);

    gflagOn(197);

    _ACTWait(60);

    stage_SetAnimation(210, 1, 0);

    stage_SetAnimation(209, -1, -2);

    while (stage_CheckAnimationFinish(210) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1379)->active = 1;
    scpSearchGobj(1378)->active = 0;

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    SetWayGroupActive(5, 1);
}
