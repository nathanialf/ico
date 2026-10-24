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

#ifdef VERSION_JUN26
static ActMail sekizo_mes[2] = {{377}, {376}}; /* derived name */
#else
#ifdef VERSION_NTSC
static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

void actSt05bCrest01XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    if (gflagChk(218) == 0) {
        stage_SetAnimation(166, 0, 0);
        stage_SetAnimation(168, 0, 0);
    } else {
        stage_SetAnimation(166, 0, -1);
        stage_SetAnimation(168, 0, -1);
        scpTorchLightOn(1243);
        scpTorchLightOn(1244);
    }
    if (gflagChk(219) == 0) {
        stage_SetAnimation(167, 0, 0);
    } else {
        stage_SetAnimation(167, 0, -1);
        scpTorchLightOn(1245);
        scpTorchLightOn(1246);
    }
    if (gflagChk(226) == 0) {
        stage_SetAnimation(169, 0, 0);
    } else {
        stage_SetAnimation(169, 0, -1);
    }
}
#else
#ifdef VERSION_AUG6
static ActMail sekizo_mes[2] = {{393}, {392}}; /* derived name */
#else
static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */
#endif

void actSt05bCrest01XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
#ifdef VERSION_AUG6
    if (gflagChk(218) == 0) {
        stage_SetAnimation(165, 0, 0);
        stage_SetAnimation(167, 0, 0);
    } else {
        stage_SetAnimation(165, 0, -1);
        stage_SetAnimation(167, 0, -1);
        scpTorchLightOn(1239);
        scpTorchLightOn(1240);
    }
    if (gflagChk(219) == 0) {
        stage_SetAnimation(166, 0, 0);
    } else {
        stage_SetAnimation(166, 0, -1);
        scpTorchLightOn(1241);
        scpTorchLightOn(1242);
    }
    if (gflagChk(226) == 0) {
        stage_SetAnimation(168, 0, 0);
    } else {
        stage_SetAnimation(168, 0, -1);
#else
    if (gflagChk(243) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(183, 0, 0);
        stage_SetAnimation(185, 0, 0);
#else
        stage_SetAnimation(187, 0, 0);
        stage_SetAnimation(189, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(183, 0, -1);
        stage_SetAnimation(185, 0, -1);
#else
        stage_SetAnimation(187, 0, -1);
        stage_SetAnimation(189, 0, -1);
#endif
        scpTorchLightOn(1343);
        scpTorchLightOn(1344);
    }
    if (gflagChk(244) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(184, 0, 0);
#else
        stage_SetAnimation(188, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(184, 0, -1);
#else
        stage_SetAnimation(188, 0, -1);
#endif
        scpTorchLightOn(1345);
        scpTorchLightOn(1346);
    }
    if (gflagChk(251) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(186, 0, 0);
#else
        stage_SetAnimation(190, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(186, 0, -1);
#else
        stage_SetAnimation(190, 0, -1);
#endif
#endif
    }
}
#endif

/* .sdata: the stone statue's stream handle, its shake and the shake's volume. */
SqEntry *sekizo5b = 0;
#endif

int sekizo_5b = 0;

unsigned char sekizo_5b_vol = 0;

#ifdef VERSION_NTSC
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
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    brainLockGirl();
    scpKillEnemyAll();
    scpMaskGeneratorAll();
    scpAdpcmPlayRequestFunc(18, &sekizo5b, 1, 1, 1);
    while (sekizo5b == 0) {
        _ACTWait(1);
    }
    gflagOn(357);
    _ACTWait(60);
    stage_SetAnimation(171, 1, 0);
    ReviveAllCarryableItemsWithNonSleepFrame(250);
    sekizo_5b = iosPadActRequest(boyPad, 9);
    sekizo_5b_vol = 128;
    iosPadActVolumeSet(sekizo_5b, 128);
    h = soundSeDefPlay(1193, 0, 0, 1);
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);
    scpPlayPosSet(girlGObj, 10350.0f, -2150.0f, 0.0f);
    scpPlayPosSet(boyGObj, 10350.0f, -2150.0f, -100.0f);
    _ACTWait(1);
    sceVu0SubVector(d, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, d);
    scpBoyControlReadDisable = 1;
    sceVu0SubVector(d, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, d);
    scpSekizouCheckPoint();
    scpPlayMot(girlGObj, 572);
    scpPlayWaitMotEnd(girlGObj);
    gflagOn(143);
    soundSeDefStop(h);
    while (stage_CheckAnimationFrame(171, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_5b);
    scpPlayMot(girlGObj, 514);
    scpPlayEnd(girlGObj);
    actCreateSubThread(actSt05bGirlWay, 21);
    _ACTWait(30);
    scpPlayMot(boyGObj, 247);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    ScpCallCameraSetTarget(-10793.0f, 2122.0f, 0.0f);
}

void actSt05bDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(218) != 0 && gflagChk(125) == 0) {
        stage_SetAnimation(312, 0, -1);
    } else {
        stage_SetAnimation(312, 0, 0);
    }
}

void actSt05bMonyoDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(209) == 0) {
        stage_SetAnimation(223, 0, 0);
    } else {
        stage_SetAnimation(223, 0, -1);
    }
}

void actSt05bSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(143) == 0) {
        stage_SetAnimation(171, 0, 0);
        sekizo_mes[0].func = actSt05bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(171, 0, -1);
        if (gflagChk(218) == 0) {
            ScpCallCameraSetTarget(-10793.0f, 2122.0f, 0.0f);
        }
    }
}

void actSt05bBallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(125) == 0) {
        stage_SetAnimation(267, -1, -2);
    } else {
        stage_SetAnimation(265, -1, -2);
    }
}

void actSt05bSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(125) == 0) {
        stage_SetAnimation(270, -1, -2);
        stage_SetAnimation(273, -1, -2);
    }
}
#else
#ifdef VERSION_JUN26
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
#else
void actSt05bSekizoChk(GObj *volatile self)
{
    volatile int h;
    float d[4];
#ifdef VERSION_AUG6
    int key;
#endif

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 ||
           scpTriggerBall(self, girlGObj, 200.0f) == 0) {
        _ACTWait(1);
    }
#ifndef VERSION_AUG6
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    brainLockGirl();
    scpKillEnemyAll();
    scpMaskGeneratorAll();
#endif
    scpAdpcmPlayRequestFunc(18, &sekizo5b, 1, 1, 1);
    while (sekizo5b == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_AUG6
    scpKillEnemyAll();
    scpMaskGeneratorAll();
    gflagOn(356);
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    brainLockGirl();
    _ACTWait(60);
    stage_SetAnimation(170, 1, 0);
    ReviveAllCarryableItemsWithNonSleepFrame(250);
    key = iosPadActRequest(boyPad, 9);
    sekizo_5b_vol = 128;
    iosPadActVolumeSet(sekizo_5b = key, 128);
    h = soundSeDefPlay(1193, 0, 0, 1);
#else
    gflagOn(390);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(188, 1, 0);
#else
    stage_SetAnimation(192, 1, 0);
#endif
    ReviveAllCarryableItemsWithNonSleepFrame(250);
    sekizo_5b = iosPadActRequest(boyPad, 9);
    sekizo_5b_vol = 128;
    iosPadActVolumeSet(sekizo_5b, 128);
    h = soundSeDefPlay(1217, 0, 0, 1);
#endif
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);
    scpPlayMot(boyGObj, 0);
#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 514);
    scpPlayPosSet(girlGObj, 10350.0f, -2150.0f, 0.0f);
    scpPlayPosSet(boyGObj, 10350.0f, -2150.0f, 100.0f);
#else
    scpPlayMot(girlGObj, 532);
    scpPlayPosSet(girlGObj, 10350.0f, -2150.0f, 0.0f);
    scpPlayPosSet(boyGObj, 10350.0f, -2150.0f, -100.0f);
#endif
    _ACTWait(1);
    sceVu0SubVector(d, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, d);
    scpBoyControlReadDisable = 1;
    sceVu0SubVector(d, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, d);
    scpSekizouCheckPoint();
#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 573);
    scpPlayWaitMotEnd(girlGObj);
    gflagOn(143);
    soundSeDefStop(h);
    while (stage_CheckAnimationFrame(170, 151, 0) == 0) {
#else
    scpPlayMot(girlGObj, 645);
    scpPlayWaitMotEnd(girlGObj);
    gflagOn(160);
    soundSeDefStop(h);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(188, 151, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(192, 151, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_5b);
#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 514);
#else
    scpPlayMot(girlGObj, 532);
#endif
    scpPlayEnd(girlGObj);
    actCreateSubThread(actSt05bGirlWay, 21);
    _ACTWait(30);
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 247);
#else
    scpPlayMot(boyGObj, 252);
#endif
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    ScpCallCameraSetTarget(-10793.0f, 2122.0f, 0.0f);
#ifndef VERSION_AUG6
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(188) == 0) {
#else
    while (stage_CheckAnimationFinish(192) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
#endif
}
#endif

void actSt05bDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(218) != 0 && gflagChk(125) == 0) {
        stage_SetAnimation(311, 0, -1);
    } else {
        stage_SetAnimation(311, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(209) != 0 && gflagChk(118) == 0) {
        stage_SetAnimation(279, 0, -1);
    } else {
        stage_SetAnimation(279, 0, 0);
#else
    if (gflagChk(243) != 0 && gflagChk(139) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(341, 0, -1);
#else
        stage_SetAnimation(345, 0, -1);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(341, 0, 0);
#else
        stage_SetAnimation(345, 0, 0);
#endif
#endif
#endif
    }
}

void actSt05bMonyoDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(209) == 0) {
        stage_SetAnimation(222, 0, 0);
    } else {
        stage_SetAnimation(222, 0, -1);
#else
#ifdef VERSION_JUN26
    if (gflagChk(200) == 0) {
        stage_SetAnimation(197, 0, 0);
    } else {
        stage_SetAnimation(197, 0, -1);
#else
    if (gflagChk(234) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(247, 0, 0);
#else
        stage_SetAnimation(251, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(247, 0, -1);
#else
        stage_SetAnimation(251, 0, -1);
#endif
#endif
#endif
    }
}

void actSt05bSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_JUN26
    if (gflagChk(136) == 0) {
        stage_SetAnimation(154, 0, 0);
        sekizo_mes[0].func = actSt05bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(154, 0, -1);
#else
#ifdef VERSION_AUG6
    if (gflagChk(143) == 0) {
        stage_SetAnimation(170, 0, 0);
        sekizo_mes[0].func = actSt05bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(170, 0, -1);
        if (gflagChk(218) == 0) {
#else
    if (gflagChk(160) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(188, 0, 0);
#else
        stage_SetAnimation(192, 0, 0);
#endif
        sekizo_mes[0].func = actSt05bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(188, 0, -1);
#else
        stage_SetAnimation(192, 0, -1);
#endif
        if (gflagChk(243) == 0) {
#endif
            ScpCallCameraSetTarget(-10793.0f, 2122.0f, 0.0f);
        }
#endif
    }
}

void actSt05bBallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(125) == 0) {
        stage_SetAnimation(266, -1, -2);
    } else {
        stage_SetAnimation(264, -1, -2);
#else
#ifdef VERSION_JUN26
    if (gflagChk(118) == 0) {
        stage_SetAnimation(240, -1, -2);
    } else {
        stage_SetAnimation(238, -1, -2);
#else
    if (gflagChk(139) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(296, -1, -2);
#else
        stage_SetAnimation(300, -1, -2);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(294, -1, -2);
#else
        stage_SetAnimation(298, -1, -2);
#endif
#endif
#endif
    }
}

void actSt05bSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(125) == 0) {
        stage_SetAnimation(269, -1, -2);
        stage_SetAnimation(272, -1, -2);
#else
#ifdef VERSION_JUN26
    if (gflagChk(118) == 0) {
        stage_SetAnimation(243, -1, -2);
        stage_SetAnimation(246, -1, -2);
#else
    if (gflagChk(139) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(299, -1, -2);
        stage_SetAnimation(302, -1, -2);
#else
        stage_SetAnimation(303, -1, -2);
        stage_SetAnimation(306, -1, -2);
#endif
#endif
#endif
    }
}
#endif

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
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
#endif
    brainUnlockGirl();
}
