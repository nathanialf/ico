#include "st99a.h"
#include "act.h"
#include "commonact.h"
#include "script.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"

static ActMail explode_mes[2] = {{377}, {376}}; /* derived name */

static ActMail splash1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail splash2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wave_mes[2] = {{377}, {376}}; /* derived name */

static ActMail st27aWave_mes[2] = {{377}, {376}}; /* derived name */

static ActMail spider_mes[2] = {{377}, {376}}; /* derived name */

void actExplode(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    explode_mes[0].func = actExplodeChk;
    act->mail = explode_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSplash1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    splash1_mes[0].func = actSplash1Chk;
    act->mail = splash1_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSplash2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    splash2_mes[0].func = actSplash2Chk;
    act->mail = splash2_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actWave(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    wave_mes[0].func = actWaveChk;
    act->mail = wave_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSpider(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    stage_SetLoopFlag(125, 1);
    stage_SetAnimation(125, 1, 0);

    spider_mes[0].func = actSpiderChk;
    act->mail = spider_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt27aWave(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    st27aWave_mes[0].func = actSt27aWaveChk;
    act->mail = st27aWave_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actExplodeChk(GObj *volatile self)
{
    GOBJ_SUB(scpSearchGobj(2613))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(2613))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(403, 1, 0);
    scpLinkBGAtoLayoutedTarget(2613, 403);
    while (stage_CheckAnimationFinish(403) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSplash1Chk(GObj *volatile self)
{
    GOBJ_SUB(scpSearchGobj(2614))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(2614))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(391, 1, 0);
    scpLinkBGAtoLayoutedTarget(2614, 391);
    while (stage_CheckAnimationFinish(391) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSplash2Chk(GObj *volatile self)
{
    GOBJ_SUB(scpSearchGobj(2615))->ctrl.noStand = 1;
    GOBJ_SUB(scpSearchGobj(2615))->ctrl.noStand = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
    stage_SetAnimation(392, 1, 0);
    scpLinkBGAtoLayoutedTarget(2615, 392);
    while (stage_CheckAnimationFinish(392) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actWaveChk(GObj *volatile self)
{
    actCreateSubThread(actWave1, 21);
}

void actWave1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    while (1) {
        stage_SetAnimation(410, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(411, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(412, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(413, 1, 0);
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
        stage_SetAnimation(156, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(157, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(158, 1, 0);
        _ACTWait(179);
        stage_SetAnimation(159, 1, 0);
        _ACTWait(179);
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
