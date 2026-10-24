#include "st04b.h"
#include "layout_texture.h"
#include "pad.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "brain.h"
#include "camera-root.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "item.h"
#include <libvu0.h>
#include "typedef.h"
#include "main.h"
#include "script.h"

#ifdef VERSION_NTSC
static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene1_mes[2] = {{397}, {396}}; /* derived name */
#else
#ifdef VERSION_AUG6
static ActMail sekizo_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene1_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_JUN26
static ActMail sekizo_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ene1_mes[2] = {{377}, {376}}; /* derived name */
#else
static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene1_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif
#endif

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{-10750.0f, -2122.0f, 0.0f, 0.0f}}; /* derived name */

static const ConstVec girlWay2Pos = {{-139.0f, -177.0f, 1670.0f, 0.0f}}; /* derived name */

#ifndef VERSION_JUN26
#ifdef VERSION_NTSC
void actSt04bEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(124) != 0) {
            if (gflagChk(140) == 0) {
                gflagOn(358);
            }
        }
    }
}
#else
void actSt04bEnd(void)
{
    if (girlGObj != 0) {
#ifdef VERSION_AUG6
        if (gflagChk(124) != 0) {
            if (gflagChk(140) == 0) {
                gflagOn(357);
#else
        if (gflagChk(138) != 0) {
            if (gflagChk(157) == 0) {
                gflagOn(391);
#endif
            }
        }
    }
}
#endif

/* .sdata: the stone statue's stream handle, its shake and the shake's volume. */
SqEntry *sekizo4b = 0;
#endif

int sekizo_4b = 0;

unsigned char sekizo_4b_vol = 0;

#ifdef VERSION_NTSC
void actSt04bSekizoChk(GObj *volatile self)
{
    /* soundSeDefPlay hands back a slot id the sound side keeps updating, so
       the handle is read again at the stop site */
    volatile int se;
    float v[4];
    int key;

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

    scpKillEnemyOne(3453);
    scpMaskGeneratorAll();

    scpAdpcmPlayRequestFunc(18, &sekizo4b, 1, 1, 1);
    while (sekizo4b == 0) {
        _ACTWait(1);
    }

    gflagOn(357);
    _ACTWait(60);

    stage_SetAnimation(170, 1, 0);

    ReviveAllCarryableItemsWithNonSleepFrame(250);

    key = iosPadActRequest(boyPad, 9);
    sekizo_4b_vol = 128;
    iosPadActVolumeSet(sekizo_4b = key, 128);

    se = soundSeDefPlay(1193, 0, 0, 1);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    scpPlayPosSet(girlGObj, -10325.0f, -2150.0f, 0.0f);
    scpPlayPosSet(boyGObj, -10325.0f, -2150.0f, -100.0f);
    _ACTWait(1);
    sceVu0SubVector(v, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, v);
    scpBoyControlReadDisable = 1;
    sceVu0SubVector(v, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, v);

    scpSekizouCheckPoint();

    scpPlayMot(girlGObj, 572);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(142);

    soundSeDefStop(se);

    while (stage_CheckAnimationFrame(170, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_4b);

    scpPlayMot(girlGObj, 514);
    scpPlayEnd(girlGObj);

    actCreateSubThread(actSt04bGirlWay, 21);

    _ACTWait(30);
    scpPlayMot(boyGObj, 247);
    scpPlayWaitMotEnd(boyGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    ScpCallCameraSetTarget(10793.0f, 2122.0f, 0.0f);
}

void actSt04bEne1Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(124) == 0 || scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpSleepEnemyOne(3453);

    gflagOff(358);

    _ACTWait(60);

    gflagOn(140);
    gflagOn(141);

    stage_SetAnimation(163, 1, 0);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFinish(163) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;

    scpWakeupEnemyOne(3453);
}

void actSt04bCrest01XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(155) == 0) {
        stage_SetAnimation(164, 0, 0);
        stage_SetAnimation(165, 0, 0);
    } else {
        stage_SetAnimation(164, 0, -1);
        stage_SetAnimation(165, 0, -1);
        scpTorchLightOn(968);
        scpTorchLightOn(969);
    }
}

void actSt04bDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    stage_SetAnimation(221, 0, 0);
}

void actSt04bMonyoDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(155) == 0) {
        stage_SetAnimation(222, 0, 0);
    } else {
        stage_SetAnimation(222, 0, -1);
    }
}

void actSt04bSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(142) == 0) {
        stage_SetAnimation(170, 0, 0);
        sekizo_mes[0].func = actSt04bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(170, 0, -1);
        if (gflagChk(155) == 0) {
            ScpCallCameraSetTarget(10793.0f, 2122.0f, 0.0f);
        }
    }
}

void actSt04bEne1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(140) == 0) {
        ene1_mes[0].func = actSt04bEne1Chk;
        act->mail = ene1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04bEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);
    while (gflagChk(141) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04bEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);
    while (gflagChk(141) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04bBallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(124) == 0) {
        stage_SetAnimation(266, -1, -2);
    } else {
        stage_SetAnimation(264, -1, -2);
    }
}

void actSt04bSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(124) == 0) {
        stage_SetAnimation(268, -1, -2);
        stage_SetAnimation(272, -1, -2);
    }
}
#else
#ifdef VERSION_JUN26
void actSt04bSekizoChk(GObj *volatile self)
{
    /* soundSeDefPlay hands back a slot id the sound side keeps updating, so
       the handle is read again at the stop site */
    volatile int se;
    float v[4];
    int key;

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

    gflagOn(135);
    _ACTWait(60);

    stage_SetAnimation(153, 1, 0);

    key = iosPadActRequest(boyPad, 9);
    sekizo_4b_vol = 128;
    iosPadActVolumeSet(sekizo_4b = key, 128);

    se = soundSeDefPlay(1167, 0, 0, 1);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 521);

    scpPlayPosSet(girlGObj, -10325.0f, -2150.0f, 0.0f);
    scpPlayPosSet(boyGObj, -10325.0f, -2150.0f, 100.0f);
    _ACTWait(1);
    sceVu0SubVector(v, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, v);
    scpBoyControlReadDisable = 1;
    sceVu0SubVector(v, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, v);

    scpPlayMot(girlGObj, 584);
    scpPlayWaitMotEnd(girlGObj);

    soundSeDefStop(se);

    while (stage_CheckAnimationFrame(153, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_4b);

    scpPlayMot(girlGObj, 521);
    scpPlayEnd(girlGObj);

    actCreateSubThread(actSt04bGirlWay, 21);

    _ACTWait(30);
    scpPlayMot(boyGObj, 254);
    scpPlayWaitMotEnd(boyGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
}

inline void actSt04bEne1Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(117) == 0 || scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }
}
#else
void actSt04bSekizoChk(GObj *volatile self)
{
    /* soundSeDefPlay hands back a slot id the sound side keeps updating, so
       the handle is read again at the stop site */
    volatile int se;
    float v[4];
    int key;

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

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    scpKillEnemyOne(3734);
#else
    scpKillEnemyOne(3757);
#endif
    scpMaskGeneratorAll();
#endif

    scpAdpcmPlayRequestFunc(18, &sekizo4b, 1, 1, 1);
    while (sekizo4b == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpKillEnemyOne(3415);
    scpMaskGeneratorAll();

    gflagOn(356);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    brainLockGirl();

    _ACTWait(60);

    stage_SetAnimation(169, 1, 0);
#else
    gflagOn(390);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(187, 1, 0);
#else
    stage_SetAnimation(191, 1, 0);
#endif
#endif

    ReviveAllCarryableItemsWithNonSleepFrame(250);

    key = iosPadActRequest(boyPad, 9);
    sekizo_4b_vol = 128;
    iosPadActVolumeSet(sekizo_4b = key, 128);

#ifdef VERSION_AUG6
    se = soundSeDefPlay(1193, 0, 0, 1);
#else
    se = soundSeDefPlay(1217, 0, 0, 1);
#endif

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpPlayMot(boyGObj, 0);
#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 514);

    scpPlayPosSet(girlGObj, -10325.0f, -2150.0f, 0.0f);
    scpPlayPosSet(boyGObj, -10325.0f, -2150.0f, 100.0f);
#else
    scpPlayMot(girlGObj, 532);

    scpPlayPosSet(girlGObj, -10325.0f, -2150.0f, 0.0f);
    scpPlayPosSet(boyGObj, -10325.0f, -2150.0f, -100.0f);
#endif
    _ACTWait(1);
    sceVu0SubVector(v, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, v);
    scpBoyControlReadDisable = 1;
    sceVu0SubVector(v, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, v);

    scpSekizouCheckPoint();

#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 573);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(142);
#else
    scpPlayMot(girlGObj, 645);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(159);
#endif

    soundSeDefStop(se);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(187, 151, 0) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(169, 151, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(191, 151, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_4b);

#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 514);
#else
    scpPlayMot(girlGObj, 532);
#endif
    scpPlayEnd(girlGObj);

    actCreateSubThread(actSt04bGirlWay, 21);

    _ACTWait(30);
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 247);
#else
    scpPlayMot(boyGObj, 252);
#endif
    scpPlayWaitMotEnd(boyGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    ScpCallCameraSetTarget(10793.0f, 2122.0f, 0.0f);

#ifndef VERSION_AUG6
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(187) == 0) {
#else
    while (stage_CheckAnimationFinish(191) == 0) {
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

void actSt04bEne1Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

#ifdef VERSION_AUG6
    while (gflagChk(124) == 0 || scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
#else
    while (gflagChk(138) == 0 || (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 &&
                                  scpTriggerFloorAttr(boyGObj, 0x2000000) == 0)) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpSleepEnemyOne(3415);

    gflagOff(357);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    scpSleepEnemyOne(3734);
#else
    scpSleepEnemyOne(3757);
#endif

    gflagOff(391);
#endif

    _ACTWait(60);

#ifdef VERSION_AUG6
    gflagOn(140);
    gflagOn(141);

    stage_SetAnimation(162, 1, 0);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFinish(162) == 0) {
#else
    gflagOn(157);
    gflagOn(158);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(180, 1, 0);
#else
    stage_SetAnimation(184, 1, 0);
#endif
    SetCameraFlag_LwsCutBack();
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(180) == 0) {
#else
    while (stage_CheckAnimationFinish(184) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;

    scpWakeupEnemyOne(3415);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    scpWakeupEnemyOne(3734);
#else
    scpWakeupEnemyOne(3757);
#endif
#endif
}
#endif

void actSt04bCrest01XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(155) == 0) {
        stage_SetAnimation(163, 0, 0);
        stage_SetAnimation(164, 0, 0);
    } else {
        stage_SetAnimation(163, 0, -1);
        stage_SetAnimation(164, 0, -1);
        scpTorchLightOn(966);
        scpTorchLightOn(967);
#else
#ifdef VERSION_JUN26
    if (gflagChk(148) == 0) {
        stage_SetAnimation(149, 0, 0);
        stage_SetAnimation(150, 0, 0);
    } else {
        stage_SetAnimation(149, 0, -1);
        stage_SetAnimation(150, 0, -1);
        scpTorchLightOn(919);
        scpTorchLightOn(920);
#else
    if (gflagChk(174) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(181, 0, 0);
        stage_SetAnimation(182, 0, 0);
#else
        stage_SetAnimation(185, 0, 0);
        stage_SetAnimation(186, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(181, 0, -1);
        stage_SetAnimation(182, 0, -1);
#else
        stage_SetAnimation(185, 0, -1);
        stage_SetAnimation(186, 0, -1);
#endif
        scpTorchLightOn(1056);
        scpTorchLightOn(1057);
#endif
#endif
    }
}

void actSt04bDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(245, 0, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(220, 0, 0);
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(195, 0, 0);
#else
    stage_SetAnimation(249, 0, 0);
#endif
#endif
#endif
}

void actSt04bMonyoDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(155) == 0) {
        stage_SetAnimation(221, 0, 0);
    } else {
        stage_SetAnimation(221, 0, -1);
#else
#ifdef VERSION_JUN26
    if (gflagChk(148) == 0) {
        stage_SetAnimation(196, 0, 0);
    } else {
        stage_SetAnimation(196, 0, -1);
#else
    if (gflagChk(174) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(246, 0, 0);
#else
        stage_SetAnimation(250, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(246, 0, -1);
#else
        stage_SetAnimation(250, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04bSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_JUN26
    if (gflagChk(135) == 0) {
        stage_SetAnimation(153, 0, 0);
        sekizo_mes[0].func = actSt04bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(153, 0, -1);
#else
#ifdef VERSION_AUG6
    if (gflagChk(142) == 0) {
        stage_SetAnimation(169, 0, 0);
        sekizo_mes[0].func = actSt04bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(169, 0, -1);
        if (gflagChk(155) == 0) {
#else
    if (gflagChk(159) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(187, 0, 0);
#else
        stage_SetAnimation(191, 0, 0);
#endif
        sekizo_mes[0].func = actSt04bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(187, 0, -1);
#else
        stage_SetAnimation(191, 0, -1);
#endif
        if (gflagChk(174) == 0) {
#endif
            ScpCallCameraSetTarget(10793.0f, 2122.0f, 0.0f);
        }
#endif
    }
}

void actSt04bEne1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(140) == 0) {
        ene1_mes[0].func = actSt04bEne1Chk;
        act->mail = ene1_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(133) == 0) {
        ene1_mes[0].func = actSt04bEne1Chk;
        act->mail = ene1_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(157) == 0) {
        ene1_mes[0].func = actSt04bEne1Chk;
        act->mail = ene1_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04bEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);
#ifdef VERSION_AUG6
    while (gflagChk(141) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(134) == 0) {
#else
    while (gflagChk(158) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04bEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);
#ifdef VERSION_AUG6
    while (gflagChk(141) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(134) == 0) {
#else
    while (gflagChk(158) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04bBallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(124) == 0) {
        stage_SetAnimation(265, -1, -2);
    } else {
        stage_SetAnimation(263, -1, -2);
#else
#ifdef VERSION_JUN26
    if (gflagChk(117) == 0) {
        stage_SetAnimation(239, -1, -2);
    } else {
        stage_SetAnimation(237, -1, -2);
#else
    if (gflagChk(138) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(295, -1, -2);
#else
        stage_SetAnimation(299, -1, -2);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(293, -1, -2);
#else
        stage_SetAnimation(297, -1, -2);
#endif
#endif
#endif
    }
}

void actSt04bSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(124) == 0) {
        stage_SetAnimation(267, -1, -2);
        stage_SetAnimation(271, -1, -2);
#else
#ifdef VERSION_JUN26
    if (gflagChk(117) == 0) {
        stage_SetAnimation(241, -1, -2);
        stage_SetAnimation(245, -1, -2);
#else
    if (gflagChk(138) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(297, -1, -2);
#endif
        stage_SetAnimation(301, -1, -2);
#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_CN)
        stage_SetAnimation(305, -1, -2);
#endif
#endif
#endif
    }
}
#endif

void actSt04bSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt04bGirlWay(GObj *volatile self)
{
    long long buf[2];
    long long way[2];

    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);

    way[0] = girlWay2Pos.d[0];
    way[1] = girlWay2Pos.d[1];
    RequestStageChangeDirect(girlGObj, 19, way, 180);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
#endif
    brainUnlockGirl();
}
