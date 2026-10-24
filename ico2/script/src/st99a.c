#include "st99a.h"
#include "act.h"
#include "commonact.h"
#include "script.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"

#ifdef VERSION_AUG6
static ActMail explode_mes[2] = {{393}, {392}}; /* derived name */

static ActMail splash1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail splash2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wave_mes[2] = {{393}, {392}}; /* derived name */

static ActMail st27aWave_mes[2] = {{393}, {392}}; /* derived name */

static ActMail spider_mes[2] = {{393}, {392}}; /* derived name */
#else
static void actSt17aTestChk(GObj *volatile self);

#ifdef VERSION_NTSC
static ActMail explode_mes[2] = {{397}, {396}}; /* derived name */

static ActMail splash1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail splash2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wave_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st27aWave_mes[2] = {{397}, {396}}; /* derived name */

static ActMail spider_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st17aTest_mes[2] = {{397}, {396}}; /* derived name */
#else
static ActMail explode_mes[2] = {{430}, {429}}; /* derived name */

static ActMail splash1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail splash2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wave_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st27aWave_mes[2] = {{430}, {429}}; /* derived name */

static ActMail spider_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st17aTest_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif

void actExplode(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    explode_mes[0].func = actExplodeChk;
    act->mail = explode_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actSplash1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    splash1_mes[0].func = actSplash1Chk;
    act->mail = splash1_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actSplash2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    splash2_mes[0].func = actSplash2Chk;
    act->mail = splash2_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actWave(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    wave_mes[0].func = actWaveChk;
    act->mail = wave_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actSpider(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetLoopFlag(156, 1);
    stage_SetAnimation(156, 1, 0);
#else
#ifdef VERSION_NTSC
    stage_SetLoopFlag(139, 1);
    stage_SetAnimation(139, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetLoopFlag(138, 1);
    stage_SetAnimation(138, 1, 0);
#else
    stage_SetLoopFlag(160, 1);
    stage_SetAnimation(160, 1, 0);
#endif
#endif
#endif

    spider_mes[0].func = actSpiderChk;
    act->mail = spider_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actDevilLightning(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(3490, 0, 550, 0);
#else
#ifdef VERSION_NTSC
    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(3242, 0, 483, 0);
#else
#ifdef VERSION_AUG6
    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(3212, 0, 482, 0);
#else
    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(3513, 0, 554, 0);
#endif
#endif
#endif
}

void actQueenLightning(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(3211, 0, 483, 0);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(3489, 0, 551, 0);
#else
#ifdef VERSION_NTSC
    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(3241, 0, 484, 0);
#else
    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(3512, 0, 555, 0);
#endif
#endif
}

void actSt17aTest(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(128, 0, 0);
#else
#ifdef VERSION_NTSC
    stage_SetAnimation(112, 0, 0);
#else
    stage_SetAnimation(132, 0, 0);
#endif
#endif

    st17aTest_mes[0].func = actSt17aTestChk;
    act->mail = st17aTest_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
#endif
}

void actSt27aWave(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    st27aWave_mes[0].func = actSt27aWaveChk;
    act->mail = st27aWave_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

#ifdef VERSION_NTSC
void actExplodeChk(GObj *volatile self)
{
    GOBJ_SUB(scpSearchGobj(2791))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(2791))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(440, 1, 0);
    scpLinkBGAtoLayoutedTarget(2791, 440);
    while (stage_CheckAnimationFinish(440) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSplash1Chk(GObj *volatile self)
{
    GOBJ_SUB(scpSearchGobj(2792))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(2792))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(428, 1, 0);
    scpLinkBGAtoLayoutedTarget(2792, 428);
    while (stage_CheckAnimationFinish(428) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSplash2Chk(GObj *volatile self)
{
    GOBJ_SUB(scpSearchGobj(2793))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(2793))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(429, 1, 0);
    scpLinkBGAtoLayoutedTarget(2793, 429);
    while (stage_CheckAnimationFinish(429) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}
#else
void actExplodeChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    GOBJ_SUB(scpSearchGobj(2761))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(2761))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(439, 1, 0);
    scpLinkBGAtoLayoutedTarget(2761, 439);
    while (stage_CheckAnimationFinish(439) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    GOBJ_SUB(scpSearchGobj(3010))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(3010))->ctrl.noStand = 0;
#else
    GOBJ_SUB(scpSearchGobj(3014))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(3014))->ctrl.noStand = 0;
#endif
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(507, 1, 0);
    scpLinkBGAtoLayoutedTarget(3010, 507);
    while (stage_CheckAnimationFinish(507) == 0) {
#else
    stage_SetAnimation(511, 1, 0);
    scpLinkBGAtoLayoutedTarget(3014, 511);
    while (stage_CheckAnimationFinish(511) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSplash1Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    GOBJ_SUB(scpSearchGobj(2762))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(2762))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(427, 1, 0);
    scpLinkBGAtoLayoutedTarget(2762, 427);
    while (stage_CheckAnimationFinish(427) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    GOBJ_SUB(scpSearchGobj(3011))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(3011))->ctrl.noStand = 0;
#else
    GOBJ_SUB(scpSearchGobj(3015))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(3015))->ctrl.noStand = 0;
#endif
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(494, 1, 0);
    scpLinkBGAtoLayoutedTarget(3011, 494);
    while (stage_CheckAnimationFinish(494) == 0) {
#else
    stage_SetAnimation(498, 1, 0);
    scpLinkBGAtoLayoutedTarget(3015, 498);
    while (stage_CheckAnimationFinish(498) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSplash2Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    GOBJ_SUB(scpSearchGobj(2763))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(2763))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(428, 1, 0);
    scpLinkBGAtoLayoutedTarget(2763, 428);
    while (stage_CheckAnimationFinish(428) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    GOBJ_SUB(scpSearchGobj(3012))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(3012))->ctrl.noStand = 0;
#else
    GOBJ_SUB(scpSearchGobj(3016))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(3016))->ctrl.noStand = 0;
#endif
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(495, 1, 0);
    scpLinkBGAtoLayoutedTarget(3012, 495);
    while (stage_CheckAnimationFinish(495) == 0) {
#else
    stage_SetAnimation(499, 1, 0);
    scpLinkBGAtoLayoutedTarget(3016, 499);
    while (stage_CheckAnimationFinish(499) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
}
#endif

void actWaveChk(GObj *volatile self)
{
    actCreateSubThread(actWave1, 21);
}

void actWave1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    while (1) {
#ifdef VERSION_NTSC
        stage_SetAnimation(448, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(449, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(450, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(451, 1, 0);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(447, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(448, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(449, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(450, 1, 0);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(515, 1, 0);
#else
        stage_SetAnimation(519, 1, 0);
#endif
        _ACTWait(179);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(516, 1, 0);
#else
        stage_SetAnimation(520, 1, 0);
#endif
        _ACTWait(179);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(517, 1, 0);
#else
        stage_SetAnimation(521, 1, 0);
#endif
        _ACTWait(179);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(518, 1, 0);
#else
        stage_SetAnimation(522, 1, 0);
#endif
#endif
#endif
        _ACTWait(179);
    }
}

void actSt27aWaveChk(GObj *volatile self)
{
    actCreateSubThread(actSt27aWave1, 21);
}

void actSt27aWave1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    while (1) {
#ifdef VERSION_NTSC
        stage_SetAnimation(173, 1, 0);
        _ACTWait(200);
        stage_SetAnimation(174, 1, 0);
        _ACTWait(200);
        stage_SetAnimation(175, 1, 0);
        _ACTWait(200);
        stage_SetAnimation(176, 1, 0);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(172, 1, 0);
        _ACTWait(200);
        stage_SetAnimation(173, 1, 0);
        _ACTWait(200);
        stage_SetAnimation(174, 1, 0);
        _ACTWait(200);
        stage_SetAnimation(175, 1, 0);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(190, 1, 0);
#else
        stage_SetAnimation(194, 1, 0);
#endif
        _ACTWait(200);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(191, 1, 0);
#else
        stage_SetAnimation(195, 1, 0);
#endif
        _ACTWait(200);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(192, 1, 0);
#else
        stage_SetAnimation(196, 1, 0);
#endif
        _ACTWait(200);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(193, 1, 0);
#else
        stage_SetAnimation(197, 1, 0);
#endif
#endif
#endif
        _ACTWait(200);
    }
}

void actSpiderChk(GObj *volatile self)
{
    while (1) {
        while ((GOBJ_ACT(boyGObj)->pad.trg & 0x400) == 0) {
            _ACTWait(1);
        }
        scpBornSpider(2, 0.0f, -500.0f, 0.0f, 500.0f);
        _ACTWait(1);
    }
}

#ifndef VERSION_AUG6
static void actSt17aTestChk(GObj *volatile self)
{
    while (1) {
        while ((pad[1].flags & 0x20) == 0) {
            _ACTWait(1);
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(80, 1, 0);
#else
#ifdef VERSION_NTSC
        stage_SetAnimation(71, 1, 0);
#else
        stage_SetAnimation(84, 1, 0);
#endif
#endif
        _ACTWait(1);
    }
}
#endif
