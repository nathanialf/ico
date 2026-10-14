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

static void actSt03tGirlPosChk(GObj *volatile self);
static void actSt03tGirlUpChk(GObj *volatile self);
static void actSt03tHint1OffChk(GObj *volatile self);

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

INCLUDE_ASM(actSt03tSwitchL);

INCLUDE_ASM(actSt03tSwitchLChk);

INCLUDE_ASM(actSt03tSwitchLUpChk);

INCLUDE_ASM(actSt03tSwitchR);

INCLUDE_ASM(actSt03tSwitchRChk);

INCLUDE_ASM(actSt03tSwitchRUpChk);

void actSt03tGene(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(877));
    Generator_Mask(scpSearchGobj(878));

    while (gflagChk(105) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(20);
    Generator_Call(self);

    Generator_Call(scpSearchGobj(877));
    Generator_Call(scpSearchGobj(878));
}

void actSt03tBoxA(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
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

void actSt03tBoxB(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
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

void actSt03tGirlUp(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(93) == 0) {
        girlUp_mes[0].func = actSt03tGirlUpChk;
        act->mail = girlUp_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        FinishHint(12);
    }
}

void actSt03tGirlCam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    girlCam_mes[0].func = actSt03tGirlCamStartChk;
    act->mail = girlCam_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt03tSekizo);

void actSt03tWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(100) == 0) {
        wayOn_mes[0].func = actSt03tWayOnChk;
        act->mail = wayOn_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        wayOff_mes[0].func = actSt03tWayOffChk;
        act->mail = wayOff_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt03tEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(104) == 0) {
        ene_mes[0].func = actSt03tEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt03tGirlPos(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(101) == 0) {
        SleepHint(12);

        girlPos_mes[0].func = actSt03tGirlPosChk;
        act->mail = girlPos_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt03tHint1Sleep(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    hint1Sleep_mes[0].func = actSt03tHint1OffChk;
    act->mail = hint1Sleep_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tGirlCamEvent(int x)
{
    volatile int local = x;
}

void actSt03tGirlCamStartChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, boyGObj, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) != 202) {
        _ACTWait(1);
    }

    CameraGetTarget();
    Camctrl_SetTarget(girlGObj, 0, 3);
    _ACTWait(15);
    CameraSetCameraSet(48);

    girlCamStartChk_mes[0].func = actSt03tGirlCamEndChk;
    sub->mail = girlCamStartChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tGirlCamEndChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, boyGObj, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 202) {
        _ACTWait(1);
    }

    CameraGetTarget();
    _ACTWait(90);
    CameraSetCameraSet_Default();
    Camctrl_ExitEveRock();

    girlCamEndChk_mes[0].func = actSt03tGirlCamStartChk;
    sub->mail = girlCamEndChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tSekizoEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt03tEneChk);

void actSt03tWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

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
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

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
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt03tGirlPosChk(GObj *volatile self)
{
    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(101);
    WakeupHint(12);
}

static void actSt03tGirlUpChk(GObj *volatile self)
{
    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");
    gflagOn(93);
    FinishHint(12);
}

static void actSt03tHint1OnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 60);
    WakeupHint(12);

    hint1OnChk_mes[0].func = actSt03tHint1OffChk;
    sub->mail = hint1OnChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt03tHint1OffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (gflagChk(102) == 0) {
        _ACTWait(1);
    }

    SleepHint(12);
    gflagOff(102);

    hint1OffChk_mes[0].func = actSt03tHint1OnChk;
    sub->mail = hint1OffChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
