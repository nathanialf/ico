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
#include "include_asm.h"

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

INCLUDE_ASM(actSt05bCrest01XL);

/* .sdata: the stone statue's stream handle, its shake and the shake's volume. */
SqEntry *sekizo5b = 0;

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
    lt_switch_layout(52);
    scpBoyControlReadDisable = 1;
    brainLockGirl();
    scpKillEnemyAll();
    scpMaskGeneratorAll();
    scpAdpcmPlayRequestFunc(18, &sekizo5b, 1, 1, 1);
    while (sekizo5b == 0) {
        _ACTWait(1);
    }
    gflagOn(390);
    stage_SetAnimation(188, 1, 0);
    ReviveAllCarryableItemsWithNonSleepFrame(250);
    sekizo_5b = iosPadActRequest(boyPad, 9);
    sekizo_5b_vol = 128;
    iosPadActVolumeSet(sekizo_5b, 128);
    h = soundSeDefPlay(1217, 0, 0, 1);
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 532);
    scpPlayPosSet(girlGObj, 10350.0f, -2150.0f, 0.0f);
    scpPlayPosSet(boyGObj, 10350.0f, -2150.0f, -100.0f);
    _ACTWait(1);
    sceVu0SubVector(d, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, d);
    scpBoyControlReadDisable = 1;
    sceVu0SubVector(d, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, d);
    scpSekizouCheckPoint();
    scpPlayMot(girlGObj, 645);
    scpPlayWaitMotEnd(girlGObj);
    gflagOn(160);
    soundSeDefStop(h);
    while (stage_CheckAnimationFrame(188, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_5b);
    scpPlayMot(girlGObj, 532);
    scpPlayEnd(girlGObj);
    actCreateSubThread(actSt05bGirlWay, 21);
    _ACTWait(30);
    scpPlayMot(boyGObj, 252);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    ScpCallCameraSetTarget(-10793.0f, 2122.0f, 0.0f);
    while (stage_CheckAnimationFinish(188) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(51);
    scpBoyControlReadDisable = 0;
}

INCLUDE_ASM(actSt05bDoorXL);

INCLUDE_ASM(actSt05bMonyoDoorXL);

INCLUDE_ASM(actSt05bSekizo);

void actSt05bBallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(139) == 0) {
        stage_SetAnimation(296, -1, -2);
    } else {
        stage_SetAnimation(294, -1, -2);
    }
}

void actSt05bSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(139) == 0) {
        stage_SetAnimation(299, -1, -2);
        stage_SetAnimation(302, -1, -2);
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
    brainUnlockGirl();
}
