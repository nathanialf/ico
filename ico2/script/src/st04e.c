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

static void actSt04eWaterStopSub(GObj *volatile self);

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for, and its complement, true when the player skipped the demo with
   START. */
static int demoEnd;

static int demoSkipped; /* derived name */

static ActMail waterMain_mes[2] = {{406, actSt04eWaterSwitch}, {429}}; /* derived name */

static ActMail water_mes[2] = {{430}, {429}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{430}, {429}}; /* derived name */

void actSt04eWaterStop(GObj *volatile self)
{
    GProc *th;

    lt_switch_layout(55);

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

        stage_SetAnimation(262, 0, -1);
        stage_SetAnimation(261, -1, -2);
        scpFadeIn(3.0f);
    }

    scpSearchGobj(1273)->active = 1;
    scpSearchGobj(1272)->active = 0;

    scpBoyControlReadDisable = 0;
    lt_switch_layout(54);

    scpWakeupEnemyAll();

    SetWayGroupActive(5, 1);
}

void actSt04eWater(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    SetRotObjectLockFlag(scpSearchGobj(1274), 1);

    if (gflagChk(230) == 0) {
        scpSearchGobj(1273)->active = 0;
        water_mes[0].func = actSt04eWaterMain;
        act->mail = water_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(1272)->active = 0;
        stage_SetAnimation(261, -1, -2);
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
