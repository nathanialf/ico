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
#include "include_asm.h"

static void actSt04eFuchi1Chk(GObj *volatile self);
static void actSt04eFuchi2Chk(GObj *volatile self);
static void actSt04eFuchi3Chk(GObj *volatile self);
static void actSt04eHint1Chk(GObj *volatile self);
static void actSt04eHint1WakeUpChk(GObj *volatile self);
static void actSt04eSeChk(GObj *volatile self);
static void actSt04eWaterStopSub(GObj *volatile self);

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for, and its complement, true when the player skipped the demo with
   START. */
static int demoEnd;

static int demoSkipped; /* derived name */

static ActMail waterMain_mes[2] = {{406, actSt04eWaterSwitch}, {429}}; /* derived name */

static ActMail water_mes[2] = {{430}, {429}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fuchi1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fuchi2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fuchi3_mes[2] = {{430}, {429}}; /* derived name */

static ActMail se_mes[2] = {{430}, {429}}; /* derived name */

static float seChkPos[4] = {0.0f, -171.0f, -8000.0f, 0.0f}; /* derived name */

static ActMail hint1WakeUp_mes[2] = {{430}, {429}}; /* derived name */

void actSt04eWaterStop(GObj *volatile self);

INCLUDE_ASM(actSt04eWaterStop);

void actSt04eHint1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(225) == 0) {
        hint1_mes[0].func = actSt04eHint1Chk;
        act->mail = hint1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        FinishHint(18);
    }
}

void actSt04eHint1WakeUp(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(226) == 0) {
        SleepHint(18);
        hint1WakeUp_mes[0].func = actSt04eHint1WakeUpChk;
        act->mail = hint1WakeUp_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt04eFuchi1);

INCLUDE_ASM(actSt04eFuchi2);

INCLUDE_ASM(actSt04eFuchi3);

void actSt04eSe(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    se_mes[0].func = actSt04eSeChk;
    act->mail = se_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt04eWater);

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

INCLUDE_ASM(actSt04eWaterStopSub);

static void actSt04eHint1Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 1000.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) != 145) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");
    gflagOn(225);
    FinishHint(18);
}

INCLUDE_ASM(actSt04eFuchi1Chk);

INCLUDE_ASM(actSt04eFuchi2Chk);

INCLUDE_ASM(actSt04eFuchi3Chk);

static void actSt04eSeChk(GObj *volatile self)
{
    int h;

    while (1) {
        while (ForMotionViewer_GetCurrentMotion(boyGObj) != 173 &&
               ForMotionViewer_GetCurrentMotion(boyGObj) != 177) {
            _ACTWait(1);
        }

        h = soundSeDefPlay(1340, 0, seChkPos, 1);
        _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 0.5);
        soundSeDefStop(h);

        soundSeDefPlay(1341, 0, seChkPos, 1);

        _ACTWait(1);
    }
}

static void actSt04eHint1WakeUpChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(226);
    WakeupHint(18);
}
