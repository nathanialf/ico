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

static ActMail switchL_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchR_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlCam_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlCamStartChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlCamEndChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wayOn_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wayOff_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wayOnChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wayOffChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlPos_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1Sleep_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1OffChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1OnChk_mes[2] = {{430}, {429}}; /* derived name */

void actSt03tSwitchL(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(89) == 0) {
        stage_SetAnimation(364, 0, 0);
        stage_SetAnimation(366, 0, 0);

        switchL_mes[0].func = actSt03tSwitchLChk;
        self->mail = switchL_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(364, 0, 45);
        stage_SetAnimation(366, 0, -1);

        switchLUp_mes[0].func = actSt03tSwitchLUpChk;
        self->mail = switchLUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt03tSwitchLChk(GObj *volatile a0)
{
    Act *self = GOBJ_ACT(a0);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    gflagOn(102);

    stage_SetAnimation(364, 1, 0);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(364, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(89);

    stage_SetAnimation(366, 1, 0);

    SetWayGroupActive(7, 1);

    gflagOn(91);

    while (stage_CheckAnimationFrame(366, 75, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1218, 0, 0, 1);

    while (stage_CheckAnimationFrame(366, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1219, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(366) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLChk_mes[0].func = actSt03tSwitchLUpChk;
    self->mail = switchLChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tSwitchLUpChk(GObj *volatile a0)
{
    Act *self = GOBJ_ACT(a0);

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(60);

    gflagOff(89);

    stage_SetAnimation(364, 1, 46);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(364, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(367, 1, 0);

    if (girlGObj != 0) {
        scpCheckDisconnectWallStart(girlGObj);
    }

    SetWayGroupActive(7, 0);

    soundSeDefPlay(1218, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1219, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(367, 120, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (girlGObj != 0) {
        scpCheckDisconnectWallEnd(girlGObj);
    }

    switchLUpChk_mes[0].func = actSt03tSwitchLChk;
    self->mail = switchLUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tSwitchR(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(90) == 0) {
        stage_SetAnimation(365, 0, 0);
        stage_SetAnimation(368, 0, 0);

        switchR_mes[0].func = actSt03tSwitchRChk;
        self->mail = switchR_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(365, 0, 45);
        stage_SetAnimation(368, 0, -1);

        switchRUp_mes[0].func = actSt03tSwitchRUpChk;
        self->mail = switchRUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt03tSwitchRChk(GObj *volatile a0)
{
    Act *self = GOBJ_ACT(a0);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttrTargetMan(a0, 0x2000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    gflagOn(102);

    stage_SetAnimation(365, 1, 0);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(365, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(368, 1, 0);

    SetWayGroupActive(5, 1);

    gflagOn(91);

    soundSeDefPlay(1218, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1219, 0, 0, 1);

    while (stage_CheckAnimationFinish(368) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(90);

    switchRChk_mes[0].func = actSt03tSwitchRUpChk;
    self->mail = switchRChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tSwitchRUpChk(GObj *volatile a0)
{
    Act *self = GOBJ_ACT(a0);

    while (scpTriggerFloorAttrTargetMan(a0, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(((60 - systemStatus[0] * 10) / systemStatus[1]) * 10);

    gflagOff(90);

    stage_SetAnimation(365, 1, 46);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(365, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(369, 1, 0);

    SetWayGroupActive(5, 0);

    soundSeDefPlay(1218, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1219, 0, 0, 1);

    while (stage_CheckAnimationFinish(369) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchRUpChk_mes[0].func = actSt03tSwitchRChk;
    self->mail = switchRUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tGene(GObj *volatile a0)
{
    GObj *x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask(scpSearchGobj(877));
    Generator_Mask(scpSearchGobj(878));

    while (gflagChk(105) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(20);
    Generator_Call(a0);

    Generator_Call(scpSearchGobj(877));
    Generator_Call(scpSearchGobj(878));
}

void actSt03tBoxA(GObj *volatile a0)
{
    GObj *x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(298) == 0) {
        scpSearchGobj(865)->active = 0;
    } else {
        scpSearchGobj(852)->active = 0;
        scpSearchGobj(863)->active = 0;
        scpSearchGobj(865)->active = 1;

        scpTransGObj(scpSearchGobj(865), 0.0f, -200.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(865));
    }
}

void actSt03tBoxB(GObj *volatile a0)
{
    GObj *x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(299) == 0) {
        scpSearchGobj(866)->active = 0;
    } else {
        scpSearchGobj(853)->active = 0;
        scpSearchGobj(864)->active = 0;
        scpSearchGobj(866)->active = 1;

        gflagOn(98);

        scpTransGObj(scpSearchGobj(866), 0.0f, -400.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(866));
    }
}

void actSt03tInit(void)
{
    if (gflagChk(91) != 0) {
        SetWayGroupActive(7, 1);
    } else {
        SetWayGroupActive(7, 0);
    }

    if (gflagChk(92) != 0) {
        SetWayGroupActive(5, 1);
    } else {
        SetWayGroupActive(5, 0);
    }
}

void actSt03tGirlUp(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(93) == 0) {
        girlUp_mes[0].func = actSt03tGirlUpChk;
        self->mail = girlUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(12);
    }
}

void actSt03tGirlCam(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    girlCam_mes[0].func = actSt03tGirlCamStartChk;
    self->mail = girlCam_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tSekizo(GObj *volatile a0)
{
    GObj *x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 95, 80, 0, 18, -913.0f, -400.0f, 605.0f, -1000.0f, -400.0f, 550.0f);
}

void actSt03tWay(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(100) == 0) {
        wayOn_mes[0].func = actSt03tWayOnChk;
        self->mail = wayOn_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        wayOff_mes[0].func = actSt03tWayOffChk;
        self->mail = wayOff_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt03tEne(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(104) == 0) {
        ene_mes[0].func = actSt03tEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt03tGirlPos(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(101) == 0) {
        SleepHint(12);

        girlPos_mes[0].func = actSt03tGirlPosChk;
        self->mail = girlPos_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt03tHint1Sleep(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    hint1Sleep_mes[0].func = actSt03tHint1OffChk;
    self->mail = hint1Sleep_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tGirlCamEvent(int x)
{
    volatile int local = x;
}

void actSt03tGirlCamStartChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    while (scpTriggerBall(a0, boyGObj, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) != 202) {
        _ACTWait(1);
    }

    CameraGetTarget();
    Camctrl_SetTarget(girlGObj, 0, 3);
    _ACTWait(15);
    CameraSetCameraSet(48);

    girlCamStartChk_mes[0].func = actSt03tGirlCamEndChk;
    sub->mail = girlCamStartChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tGirlCamEndChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    while (scpTriggerBall(a0, boyGObj, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 202) {
        _ACTWait(1);
    }

    CameraGetTarget();
    _ACTWait(90);
    CameraSetCameraSet_Default();
    Camctrl_ExitEveRock();

    girlCamEndChk_mes[0].func = actSt03tGirlCamStartChk;
    sub->mail = girlCamEndChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt03tEneChk(GObj *volatile a0)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerBall(a0, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyOne(3757);
    gflagOn(104);
    gflagOn(105);
    stage_SetAnimation(81, 1, 0);

    while (stage_CheckAnimationFinish(81) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyOne(3757);
}

void actSt03tWayOnChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(17, 1);
    gflagOn(100);

    wayOnChk_mes[0].func = actSt03tWayOffChk;
    sub->mail = wayOnChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tWayOffChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(17, 0);
    gflagOff(100);

    wayOffChk_mes[0].func = actSt03tWayOnChk;
    sub->mail = wayOffChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tGirlPosChk(GObj *volatile a0)
{
    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(101);
    WakeupHint(12);
}

void actSt03tGirlUpChk(GObj *volatile a0)
{
    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");
    gflagOn(93);
    FinishHint(12);
}

void actSt03tHint1OnChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 60);
    WakeupHint(12);

    hint1OnChk_mes[0].func = actSt03tHint1OffChk;
    sub->mail = hint1OnChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tHint1OffChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    while (gflagChk(102) == 0) {
        _ACTWait(1);
    }

    SleepHint(12);
    gflagOff(102);

    hint1OffChk_mes[0].func = actSt03tHint1OnChk;
    sub->mail = hint1OffChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
