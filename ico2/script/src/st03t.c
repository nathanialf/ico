#include "st03t.h"
#include "debug.h"
#include "layout_texture.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-ico2.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "box.h"
#include "motionManager2.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static ActMail switchL_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchLUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchLChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchR_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchRUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchRChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail girlCam_mes[2] = {{393}, {392}}; /* derived name */

static ActMail girlCamStartChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail girlCamEndChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wayOn_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wayOff_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wayOnChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wayOffChk_mes[2] = {{393}, {392}}; /* derived name */

void actSt03tSwitchL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(80) == 0) {
        stage_SetAnimation(328, 0, 0);
        stage_SetAnimation(330, 0, 0);

        switchL_mes[0].func = actSt03tSwitchLChk;
        act->mail = switchL_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(328, 0, 45);
        stage_SetAnimation(330, 0, -1);

        switchLUp_mes[0].func = actSt03tSwitchLUpChk;
        act->mail = switchLUp_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt03tSwitchLChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(328, 1, 0);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(328, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(80);

    stage_SetAnimation(330, 1, 0);

    gflagOn(82);

    while (stage_CheckAnimationFrame(330, 75, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1194, 0, 0, 1);

    while (stage_CheckAnimationFrame(330, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1195, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(330) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLChk_mes[0].func = actSt03tSwitchLUpChk;
    act->mail = switchLChk_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt03tSwitchLUpChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(60);

    gflagOff(80);

    stage_SetAnimation(328, 1, 46);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(328, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(331, 1, 0);

    soundSeDefPlay(1194, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1195, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(331, 120, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLUpChk_mes[0].func = actSt03tSwitchLChk;
    act->mail = switchLUpChk_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt03tSwitchR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(81) == 0) {
        stage_SetAnimation(329, 0, 0);
        stage_SetAnimation(332, 0, 0);

        switchR_mes[0].func = actSt03tSwitchRChk;
        act->mail = switchR_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(329, 0, 45);
        stage_SetAnimation(332, 0, -1);

        switchRUp_mes[0].func = actSt03tSwitchRUpChk;
        act->mail = switchRUp_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt03tSwitchRChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(329, 1, 0);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(329, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(332, 1, 0);

    SetWayGroupActive(5, 1);

    gflagOn(82);

    soundSeDefPlay(1194, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1195, 0, 0, 1);

    while (stage_CheckAnimationFinish(332) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(81);

    switchRChk_mes[0].func = actSt03tSwitchRUpChk;
    act->mail = switchRChk_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt03tSwitchRUpChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(((60 - systemStatus[0] * 10) / systemStatus[1]) * 10);

    gflagOff(81);

    stage_SetAnimation(329, 1, 46);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(329, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(333, 1, 0);

    SetWayGroupActive(5, 0);

    soundSeDefPlay(1194, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1195, 0, 0, 1);

    while (stage_CheckAnimationFinish(333) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchRUpChk_mes[0].func = actSt03tSwitchRChk;
    act->mail = switchRUpChk_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt03tBoxA(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(271) == 0) {
        scpSearchGobj(805)->active = 0;
    } else {
        scpSearchGobj(792)->active = 0;
        scpSearchGobj(803)->active = 0;
        scpSearchGobj(805)->active = 1;

        scpTransGObj(scpSearchGobj(805), 0.0f, -200.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(805));
    }
}

void actSt03tBoxB(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(272) == 0) {
        scpSearchGobj(806)->active = 0;
    } else {
        scpSearchGobj(793)->active = 0;
        scpSearchGobj(804)->active = 0;
        scpSearchGobj(806)->active = 1;

        gflagOn(89);

        scpTransGObj(scpSearchGobj(806), 0.0f, -400.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(806));
    }
}

void actSt03tInit(void)
{
    if (gflagChk(82) == 0) {
        SetWayGroupActive(7, 0);
    }

    if (gflagChk(83) != 0) {
        SetWayGroupActive(5, 1);
    } else {
        SetWayGroupActive(5, 0);
    }
}

INCLUDE_ASM(actSt03tGirlCam);

INCLUDE_ASM(actSt03tSekizo);

INCLUDE_ASM(actSt03tWay);

INCLUDE_ASM(actSt03tEne);

INCLUDE_ASM(actSt03tGene);

void actSt03tGirlCamEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt03tGirlCamStartChk);

INCLUDE_ASM(actSt03tGirlCamEndChk);

void actSt03tSekizoEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt03tEneChk);

INCLUDE_ASM(actSt03tWayOnChk);

INCLUDE_ASM(actSt03tWayOffChk);
