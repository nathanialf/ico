#include "st10r.h"
#include "gamesys.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "gobj_process.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "boyact.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "cage.h"
#include "motionManager2.h"
#include "rotObject.h"
#include "typedef.h"
#include "main.h"
#include "script.h"

static ActMail floor_hit_mes[2] = {{377}, {376}}; /* derived name */

static ActMail cage_mes[2] = {{377}, {376}}; /* derived name */

static ActMail tower_mes[2] = {{377}, {376}}; /* derived name */

static ActMail exit_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chain_main_mes[2] = {{358, actSt10rChainSwitch}, {376}}; /* derived name */

static ActMail chain_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chain_switch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fence_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fence2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fenceDownChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fenceUpChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fenceDownChk2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fenceUpChk2_mes[2] = {{377}, {376}}; /* derived name */

/* .sdata: the floor stream handle (actSt10rFloorChk's) and the tower scene's
   (actSt10rTowerChk's); the cage and the chain play theirs with no handle. */
SqEntry *st10r_floor = 0;

static SqEntry *st10r_adpcm = 0; /* derived name */

void actSt10rInit(void)
{
    if (gflagChk(263) != 0) {
        stage_SetAnimation(316, 0, -1);
        SetWayGroupActive(15, 1);
    } else {
        stage_SetAnimation(316, 0, 0);
    }

    if (gflagChk(265) == 0) {
        SetWayGroupActive(23, 0);
        stage_SetAnimation(319, 0, 0);
    } else {
        SetWayGroupActive(23, 1);
        stage_SetAnimation(319, 0, -1);
    }

    if (gflagChk(264) == 0) {
        stage_SetAnimation(318, 0, 0);
    } else {
        stage_SetAnimation(318, 0, -1);
    }
}

void actSt10rFloorChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 98) {
        _ACTWait(1);
    }

    iosPadActRequest(boyPad, 16);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    gflagOn(263);

    scpAdpcmPlayRequestFunc(85, &st10r_floor, 1, 1, 1);
    while (st10r_floor == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(316, 1, 0);

    while (stage_CheckAnimationFinish(316) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    SetWayGroupActive(15, 1);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt10rTowerChk(GObj *volatile self)
{
    GObj *n;

    while ((n = scpIsBombExplode(19)) == 0 || scpTriggerBall(self, n, 350.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    gflagOn(265);

    scpAdpcmPlayRequestFunc(65, &st10r_adpcm, 1, 1, 0);

    _ACTWait(60);

    stage_SetAnimation(319, 1, 0);

    while (stage_CheckAnimationFrame(319, 130, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    while (st10r_adpcm == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(st10r_adpcm->stream);

    while (stage_CheckAnimationFrame(319, 215, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFrame(319, 270, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(319, 280, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFrame(319, 300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(319) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    SetWayGroupActive(23, 1);
}

void actSt10rChainMove(GObj *volatile self)
{
    int se;

    lt_switch_layout(51);

    gflagOn(266);

    scpSearchGobj(1436)->active = 1;

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(86, 0, 1, 1, 1);

    stage_SetAnimation(317, 1, 0);

    se = soundSeDefPlay(1237, 0, 0, 1);

    _ACTWait(180);

    soundSeDefStop(se);

    soundSeDefPlay(1238, 0, 0, 1);

    iosPadActRequest(boyPad, 17);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt10rFence(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(277) == 0) {
        scpSearchGobj(1447)->active = 0;
        scpSearchGobj(1448)->active = 0;

        scpLinkBGAtoLayoutedTarget(1449, 115);

        stage_SetAnimation(115, 0, 30);

        fence_mes[0].func = actSt10rFenceUpChk;
        act->mail = fence_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(1449)->active = 0;
        scpSearchGobj(1450)->active = 0;

        gflagOff(277);

        scpLinkBGAtoLayoutedTarget(1447, 115);

        stage_SetAnimation(115, 0, 0);

        fence2_mes[0].func = actSt10rFenceDownChk2;
        act->mail = fence2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt10rFloor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(263) == 0) {
        floor_hit_mes[0].func = actSt10rFloorChk;
        act->mail = floor_hit_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt10rCage(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    scpSetCageVelocityFriction(1441, 0.95f);

    if (gflagChk(264) == 0) {
        cage_mes[0].func = actSt10rCageMain;
        act->mail = cage_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt10rTower(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(265) == 0) {
        tower_mes[0].func = actSt10rTowerChk;
        act->mail = tower_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt10rExit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    exit_mes[0].func = actSt10rExitChk;
    act->mail = exit_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10rChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(266) == 0) {
        stage_SetAnimation(317, 0, 0);
        scpSearchGobj(1436)->active = 0;

        chain_mes[0].func = actSt10rChainMain;
        act->mail = chain_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(317, 0, -1);
    }
}

void actSt10rSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpSekizou(self, 267, 320, 0, 21, 0.0f, 327.0f, 4649.0f, -75.0f, 327.0f, 4649.0f);
}

void actSt10rEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);

    Generator_MaskOff(self);
}

void actSt10rElv(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(277) != 0) {
        scpSearchGobj(1449)->active = 0;
        scpSearchGobj(1450)->active = 0;
        gflagOff(277);
    } else {
        scpSearchGobj(1447)->active = 0;
        scpSearchGobj(1448)->active = 0;
    }
}

void actSt10rGateXL(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(209) == 0) {
        scpSearchGobj(1423)->active = 0;
    } else {
        scpSearchGobj(1422)->active = 0;
    }
}

void actSt10rCageMain(GObj *volatile self)
{
    while (!(scpGetRotObjectRotCount(1425) < -2.0f)) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    gflagOn(264);

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(66, 0, 1, 1, 1);

    stage_SetAnimation(318, 1, 0);

    while (stage_CheckAnimationFinish(318) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt10rExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(270);
    gflagOff(277);

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        RequestStageChange(1, boyGObj, girlGObj, 16.0f, 16.0f);
    }
    RequestStageChange(1, boyGObj, 0, 16.0f, 16.0f);
}

void actSt10rChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;
    sub->mainMail = chain_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10rChainSwitch(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;
    act->mainMail = 0;
    chain_switch_mes[0].func = actSt10rChainMove;
    act->mail = chain_switch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10rSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt10rFenceDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1449), 5.0f) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(115, 1, 0);

    while (stage_CheckAnimationFrame(115, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(269);

    fenceDownChk_mes[0].func = actSt10rFenceUpChk;
    sub->mail = fenceDownChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10rFenceUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1449), 5.0f) != 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(115, 1, 31);

    while (stage_CheckAnimationFinish(115) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(269);

    fenceUpChk_mes[0].func = actSt10rFenceDownChk;
    sub->mail = fenceUpChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10rFenceDownChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1447), 5.0f) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(115, 1, 0);

    while (stage_CheckAnimationFrame(115, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(269);

    fenceDownChk2_mes[0].func = actSt10rFenceUpChk2;
    sub->mail = fenceDownChk2_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10rFenceUpChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1447), 5.0f) != 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(115, 1, 31);

    while (stage_CheckAnimationFinish(115) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(269);

    fenceUpChk2_mes[0].func = actSt10rFenceDownChk2;
    sub->mail = fenceUpChk2_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}
