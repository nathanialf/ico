#include "st05b.h"
#include "layout_texture.h"
#include "pad.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "brain.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "item.h"
#include <libvu0.h>
#include "typedef.h"
#include "main.h"
#include "script.h"

static ActMail sekizo_mes[2] = {{377}, {376}}; /* derived name */

/* .sdata: the stone statue's shake and the shake's volume (actSt05bSekizoChk
   addresses them; this build has no stream handle for the statue). */
int sekizo_5b = 0;

unsigned char sekizo_5b_vol = 0;

void actSt05bSekizoChk(GObj *volatile self)
{
    volatile int h;
    float d[4];

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 ||
           scpTriggerBall(self, girlGObj, 200.0f) == 0) {
        _ACTWait(1);
    }
    scpSekizouCheckPoint();
    scpAdpcmPlayRequestFunc(21, 0, 1, 1, 1);
    scpKillEnemyAll();
    scpMaskGeneratorAll();
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    brainLockGirl();
    gflagOn(136);
    _ACTWait(60);
    stage_SetAnimation(154, 1, 0);
    sekizo_5b = iosPadActRequest(boyPad, 9);
    sekizo_5b_vol = 128;
    iosPadActVolumeSet(sekizo_5b, 128);
    h = soundSeDefPlay(1167, 0, 0, 1);
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 521);
    scpPlayPosSet(girlGObj, 10350.0f, -2150.0f, 0.0f);
    scpPlayPosSet(boyGObj, 10350.0f, -2150.0f, 100.0f);
    _ACTWait(1);
    sceVu0SubVector(d, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, d);
    scpBoyControlReadDisable = 1;
    sceVu0SubVector(d, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, d);
    scpPlayMot(girlGObj, 584);
    scpPlayWaitMotEnd(girlGObj);
    soundSeDefStop(h);
    while (stage_CheckAnimationFrame(154, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_5b);
    scpPlayMot(girlGObj, 521);
    scpPlayEnd(girlGObj);
    actCreateSubThread(actSt05bGirlWay, 21);
    _ACTWait(30);
    scpPlayMot(boyGObj, 254);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
}

void actSt05bCrest01XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    if (gflagChk(209) == 0) {
        stage_SetAnimation(151, 0, 0);
        stage_SetAnimation(152, 0, 0);
    } else {
        stage_SetAnimation(151, 0, -1);
        stage_SetAnimation(152, 0, -1);
        scpTorchLightOn(1185);
        scpTorchLightOn(1186);
    }
}

void actSt05bDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(209) != 0 && gflagChk(118) == 0) {
        stage_SetAnimation(279, 0, -1);
    } else {
        stage_SetAnimation(279, 0, 0);
    }
}

void actSt05bMonyoDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(200) == 0) {
        stage_SetAnimation(197, 0, 0);
    } else {
        stage_SetAnimation(197, 0, -1);
    }
}

void actSt05bSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(136) == 0) {
        stage_SetAnimation(154, 0, 0);
        sekizo_mes[0].func = actSt05bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(154, 0, -1);
    }
}

void actSt05bBallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(118) == 0) {
        stage_SetAnimation(240, -1, -2);
    } else {
        stage_SetAnimation(238, -1, -2);
    }
}

void actSt05bSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(118) == 0) {
        stage_SetAnimation(243, -1, -2);
        stage_SetAnimation(246, -1, -2);
    }
}

void actSt05bSekizoEvent(int x)
{
    volatile int local = x;
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{10750.0f, -2122.0f, 0.0f, 0.0f}}; /* derived name */

static const ConstVec girlWay2Pos = {{139.0f, -177.0f, 1670.0f, 0.0f}}; /* derived name */

void actSt05bGirlWay(GObj *volatile self)
{
    long long buf[2];
    long long way[2];

    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);

    way[0] = girlWay2Pos.d[0];
    way[1] = girlWay2Pos.d[1];
    RequestStageChangeDirect(girlGObj, 28, way, 180);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    brainUnlockGirl();
}
