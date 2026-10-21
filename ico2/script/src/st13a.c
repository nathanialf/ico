#include "st13a.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "chain.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include <libvu0.h>
#include "typedef.h"
#include "main.h"

void actSt13aElevDownChk(GObj *volatile self);

/* .data: actor mail packets, each named for the actor that posts it
   (exit_mes is actSt13aExit's, check_mes actSt13aCheck's). */

static ActMail elevMain_mes[2] = {{356, actSt13aElevSwitch}, {376}}; /* derived name */

static ActMail elev_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elevDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail sekizo_mes[2] = {{377}, {376}}; /* derived name */

static ActMail exit_mes[2] = {{377}, {376}}; /* derived name */

static ActMail check_mes[2] = {{377}, {376}}; /* derived name */

/* .sdata: the lift stream handles, the lift's shake and volume, the statue's
   shake and volume (this build has no statue stream handle). */
SqEntry *st13a_up = 0;

SqEntry *st13a_down = 0;

unsigned int st13a_yure = 0;

unsigned char st13a_yure_vol = 0;

int sekizo_13a = 0;

unsigned char sekizo_13a_vol = 0;

void actSt13aElevUp(GObj *volatile self)
{
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(70, &st13a_up, 0, 1, 1);
    while (st13a_up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(138, 1, 0);
    stage_SetAnimation(139, 1, 0);

    while (stage_CheckAnimationFrame(138, 86, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(138, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure = iosPadActRequest(boyPad, 9);
    st13a_yure_vol = 128;
    iosPadActVolumeSet(st13a_yure, 128);

    while (stage_CheckAnimationFrame(138, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure_vol = 64;

    while (stage_CheckAnimationFrame(138, 380, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st13a_yure);
    gflagOn(282);
    RequestStageChange(15, boyGObj, 0, 16.0f, 16.0f);
}

void actSt13aElevDownChk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(73, &st13a_down, 1, 1, 1);
    while (st13a_down == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    stage_SetAnimation(138, 1, 451);
    stage_SetAnimation(140, 1, 0);

    scpPlayPosSet(boyGObj, -4871.0f, -2800.0f, 2699.0f);

    st13a_yure = iosPadActRequest(boyPad, 9);
    st13a_yure_vol = 128;
    iosPadActVolumeSet(st13a_yure, 128);

    while (stage_CheckAnimationFrame(138, 850, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    iosPadActStop(st13a_yure);

    while (stage_CheckAnimationFinish(138) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    gflagOff(15);
}

void actSt13aSekizoChk(GObj *volatile self)
{
    float d[4];

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 83) {
        _ACTWait(1);
    }

    scpSekizouCheckPoint();

    scpAdpcmPlayRequestFunc(21, 0, 1, 1, 1);

    scpBoyControlReadDisable = 1;
    lt_switch_layout(51);

    gflagOn(283);

    _ACTWait(60);

    stage_SetAnimation(141, 1, 0);

    sekizo_13a = iosPadActRequest(boyPad, 9);
    sekizo_13a_vol = 128;
    iosPadActVolumeSet(sekizo_13a, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet(boyGObj, -3688.0f, 3527.0f, 2502.0f);
    scpPlayMot(boyGObj, 0);
    _ACTWait(1);

    sceVu0SubVector(d, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, d);

    scpPlayMot(boyGObj, 253);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    while (stage_CheckAnimationFinish(141) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_13a);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt13aElev(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(282) == 0) {
        stage_SetAnimation(138, 0, 0);

        elev_mes[0].func = actSt13aElevMain;
        act->mail = elev_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt13aElevDown(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(15) != 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(138, 0, 0);
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpPlayStart(boyGObj);
        _ACTWait(10);
        stage_SetAnimation(138, 0, 451);

        elevDown_mes[0].func = actSt13aElevDownChk;
        act->mail = elevDown_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt13aSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(283) == 0) {
        stage_SetAnimation(141, 0, 0);

        sekizo_mes[0].func = actSt13aSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(141, 0, -1);
    }
}

void actSt13aExit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    exit_mes[0].func = actSt13aExitChk;
    act->mail = exit_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt13aCheck(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(284) == 0) {
        check_mes[0].func = actSt13aCheckChk;
        act->mail = check_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt13aElevMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = elevMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13aElevSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    elevSwitch_mes[0].func = actSt13aElevUp;
    sub->mail = elevSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt13aExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 || gflagChk(15) != 0) {
        _ACTWait(1);
    }

    gflagOn(282);
    RequestStageChange(15, boyGObj, 0, 16.0f, 16.0f);
}

void actSt13aCheckChk(GObj *volatile self)
{
    _ACTWait(1);

    CheckPoint();
    gflagOn(284);
}
