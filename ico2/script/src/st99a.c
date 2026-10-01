#include "st99a.h"
#include "act.h"
#include "commonact.h"
#include "script.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"

static ActMail explode_mes[2] = {{430}, {429}}; /* derived name */

static ActMail splash1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail splash2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wave_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st27aWave_mes[2] = {{430}, {429}}; /* derived name */

static ActMail spider_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st17aTest_mes[2] = {{430}, {429}}; /* derived name */

void actExplode(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    explode_mes[0].func = actExplodeChk;
    self->mail = explode_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSplash1(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    splash1_mes[0].func = actSplash1Chk;
    self->mail = splash1_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSplash2(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    splash2_mes[0].func = actSplash2Chk;
    self->mail = splash2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actWave(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    wave_mes[0].func = actWaveChk;
    self->mail = wave_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSpider(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    stage_SetLoopFlag(160, 1);
    stage_SetAnimation(160, 1, 0);

    spider_mes[0].func = actSpiderChk;
    self->mail = spider_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actDevilLightning(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    _ACTWait(1);

    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(0xDB9, 0, 0x22A, 0);
}

void actQueenLightning(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    _ACTWait(1);

    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(0xDB8, 0, 0x22B, 0);
}

void actSt17aTest(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    stage_SetAnimation(132, 0, 0);

    st17aTest_mes[0].func = actSt17aTestChk;
    self->mail = st17aTest_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt27aWave(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    st27aWave_mes[0].func = actSt27aWaveChk;
    self->mail = st27aWave_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actExplodeChk(GObj *volatile a0)
{
    GOBJ_SUB(scpSearchGobj(3014))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(3014))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(511, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xBC6, 0x1FF);
    while (stage_CheckAnimationFinish(511) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSplash1Chk(GObj *volatile a0)
{
    GOBJ_SUB(scpSearchGobj(3015))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(3015))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(498, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xBC7, 0x1F2);
    while (stage_CheckAnimationFinish(498) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSplash2Chk(GObj *volatile a0)
{
    GOBJ_SUB(scpSearchGobj(3016))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(3016))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(499, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xBC8, 0x1F3);
    while (stage_CheckAnimationFinish(499) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actWaveChk(GObj *volatile a0)
{
    actCreateSubThread(actWave1, 21);
}

void actWave1(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    while (1) {
        stage_SetAnimation(519, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(520, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(521, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(522, 1, 0);
        _ACTWait(179);
    }
}

void actSt27aWaveChk(GObj *volatile a0)
{
    actCreateSubThread(actSt27aWave1, 21);
}

void actSt27aWave1(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    while (1) {
        stage_SetAnimation(194, 1, 0);
        _ACTWait(200);
        stage_SetAnimation(195, 1, 0);
        _ACTWait(200);
        stage_SetAnimation(196, 1, 0);
        _ACTWait(200);
        stage_SetAnimation(197, 1, 0);
        _ACTWait(200);
    }
}

void actSpiderChk(GObj *volatile a0)
{
    while (1) {
        while ((GOBJ_ACT(boyGObj)->padTrg & 0x400) == 0) {
            _ACTWait(1);
        }
        scpBornSpider(2, 0.0f, -500.0f, 0.0f, 500.0f);
        _ACTWait(1);
    }
}

void actSt17aTestChk(GObj *volatile a0)
{
    while (1) {
        while ((pad[1].flags & 0x20) == 0) {
            _ACTWait(1);
        }
        stage_SetAnimation(84, 1, 0);
        _ACTWait(1);
    }
}
