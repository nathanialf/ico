#include "st99a.h"
#include "act.h"
#include "commonact.h"
#include "script.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"
#include "include_asm.h"

static void actSt17aTestChk(GObj *volatile self);

static ActMail explode_mes[2] = {{397}, {396}}; /* derived name */

static ActMail splash1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail splash2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wave_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st27aWave_mes[2] = {{397}, {396}}; /* derived name */

static ActMail spider_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st17aTest_mes[2] = {{397}, {396}}; /* derived name */

void actExplode(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    explode_mes[0].func = actExplodeChk;
    act->mail = explode_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSplash1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    splash1_mes[0].func = actSplash1Chk;
    act->mail = splash1_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSplash2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    splash2_mes[0].func = actSplash2Chk;
    act->mail = splash2_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actWave(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    wave_mes[0].func = actWaveChk;
    act->mail = wave_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSpider(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    stage_SetLoopFlag(139, 1);
    stage_SetAnimation(139, 1, 0);

    spider_mes[0].func = actSpiderChk;
    act->mail = spider_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actDevilLightning(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(3242, 0, 483, 0);
}

void actQueenLightning(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(3241, 0, 484, 0);
}

void actSt17aTest(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    stage_SetAnimation(112, 0, 0);

    st17aTest_mes[0].func = actSt17aTestChk;
    act->mail = st17aTest_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt27aWave(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    st27aWave_mes[0].func = actSt27aWaveChk;
    act->mail = st27aWave_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

INCLUDE_ASM(actExplodeChk);

INCLUDE_ASM(actSplash1Chk);

INCLUDE_ASM(actSplash2Chk);

void actWaveChk(GObj *volatile self)
{
    actCreateSubThread(actWave1, 21);
}

INCLUDE_ASM(actWave1);

void actSt27aWaveChk(GObj *volatile self)
{
    actCreateSubThread(actSt27aWave1, 21);
}

INCLUDE_ASM(actSt27aWave1);

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

static void actSt17aTestChk(GObj *volatile self)
{
    while (1) {
        while ((pad[1].flags & 0x20) == 0) {
            _ACTWait(1);
        }
        stage_SetAnimation(71, 1, 0);
        _ACTWait(1);
    }
}
