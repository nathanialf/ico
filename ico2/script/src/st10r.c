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

static ActMail floor_mes[2] = {{397}, {396}}; /* derived name */

static ActMail cage_mes[2] = {{397}, {396}}; /* derived name */

static ActMail tower_mes[2] = {{397}, {396}}; /* derived name */

static ActMail exit_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chain_main_mes[2] = {{378, actSt10rChainSwitch}, {396}}; /* derived name */

static ActMail chain_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chain_switch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_down1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_up1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_down2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_up2_mes[2] = {{397}, {396}}; /* derived name */

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for. */
static int demoEnd;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{-296.0f, 327.0f, 2125.0f, 0.0f}}; /* derived name */

/* .sdata: the floor and cage stream handles, the scene stream, the chain's. */
SqEntry *st10r_floor = 0;

SqEntry *cage10r = 0;

static SqEntry *st10r_adpcm = 0; /* derived name */

SqEntry *chain10r = 0;

void actSt10rInit(void)
{
    if (gflagChk(274) != 0) {
        stage_SetAnimation(350, 0, -1);
        SetWayGroupActive(15, 1);
    } else {
        stage_SetAnimation(350, 0, 0);
    }

    if (gflagChk(276) == 0) {
        SetWayGroupActive(23, 0);
        stage_SetAnimation(353, 0, 0);
    } else {
        SetWayGroupActive(23, 1);
        stage_SetAnimation(353, 0, -1);
    }

    if (gflagChk(275) == 0) {
        stage_SetAnimation(352, 0, 0);
    } else {
        stage_SetAnimation(352, 0, -1);
    }
}

void actSt10rFloorChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 50.0f) == 0) {
        _ACTWait(1);
    }

    iosPadActRequest(boyPad, 16);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(274);

    scpAdpcmPlayRequestFunc(90, &st10r_floor, 1, 1, 1);
    while (st10r_floor == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(350, 1, 0);

    while (stage_CheckAnimationFinish(350) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    SetWayGroupActive(15, 1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt10rCageMain(GObj *volatile self)
{
    while (!(scpGetRotObjectRotCount(1499) < -2.0f)) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(275);

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(71, &cage10r, 1, 1, 1);
    while (cage10r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(352, 1, 0);

    while (stage_CheckAnimationFinish(352) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt10rTowerChk(GObj *volatile self)
{
    GProc *th;
    GObj *n;
    int f;

    while ((n = scpIsBombExplode(19)) == 0 || scpTriggerBall(self, n, 350.0f) == 0) {
        _ACTWait(1);
    }

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x4000000) != 0) {
        actCreateSubThread(actSt10rGirlWay, 21);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(276);

    reg_SetScissorSw(1);

    scpAdpcmPlayRequestFunc(70, &st10r_adpcm, 1, 1, 0);

    _ACTWait(60);
    while (st10r_adpcm == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(actSt10rTowerConte, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    f = demoEnd ^ 1;

    if (f) {
        scpAdpcmFadeCloseFunc(st10r_adpcm, 192);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosPadActStopAll();

    iosThreadSetPri(&((GProc *)th)->thread, 34);

    if (f) {
        stage_SetAnimation(353, 1, -1);
        SetCameraFlag_GamecamCutBack();
        scpPlayMot(boyGObj, 0);
        scpFadeIn(3.0f);
    }

    scpSearchGobj(1489)->active = 1;
    scpSearchGobj(1490)->active = 1;

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    reg_SetScissorSw(0);

    SetWayGroupActive(23, 1);
}

void actSt10rTowerConte(GObj *volatile self)
{
    stage_SetAnimation(353, 1, 0);

    AdpcmPlay(st10r_adpcm->stream);

    scpSearchGobj(1489)->active = 0;
    scpSearchGobj(1490)->active = 0;

    while (stage_CheckAnimationFrame(353, 215, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFrame(353, 270, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(353, 280, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFrame(353, 300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(353) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt10rChainMove(GObj *volatile self)
{
    int se;

    lt_switch_layout(51);

    scpSleepEnemyAll();

    gflagOn(277);

    scpSearchGobj(1516)->active = 1;

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(91, &chain10r, 1, 1, 1);

    while (chain10r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(351, 1, 0);

    se = soundSeDefPlay(1263, 0, 0, 1);

    _ACTWait(180);

    soundSeDefStop(se);

    soundSeDefPlay(1264, 0, 0, 1);

    iosPadActRequest(boyPad, 17);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt10rFence(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(290) == 0) {
        scpSearchGobj(1525)->active = 0;
        scpSearchGobj(1526)->active = 0;
        scpSearchGobj(1529)->active = 0;
        scpSearchGobj(1530)->active = 0;
        scpSearchGobj(1531)->active = 0;
        scpSearchGobj(1532)->active = 0;
        scpSearchGobj(1533)->active = 0;
        scpSearchGobj(1534)->active = 0;
        scpSearchGobj(1535)->active = 0;
        scpSearchGobj(1536)->active = 0;

        scpLinkBGAtoLayoutedTarget(1527, 129);

        stage_SetAnimation(129, 0, 30);

        SetWayGroupActive(37, 1);
        SetWayGroupActive(38, 1);

        fence_mes[0].func = actSt10rFenceUpChk;
        act->mail = fence_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpSearchGobj(1527)->active = 0;
        scpSearchGobj(1528)->active = 0;
        scpSearchGobj(1533)->active = 0;
        scpSearchGobj(1534)->active = 0;
        scpSearchGobj(1535)->active = 0;
        scpSearchGobj(1536)->active = 0;

        gflagOff(290);

        scpLinkBGAtoLayoutedTarget(1525, 129);

        stage_SetAnimation(129, 0, 0);

        fence2_mes[0].func = actSt10rFenceDownChk2;
        act->mail = fence2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10rFenceDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1527), 5.0f) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1533)->active = 0;
    scpSearchGobj(1534)->active = 0;
    scpSearchGobj(1535)->active = 0;
    scpSearchGobj(1536)->active = 0;

    stage_SetAnimation(129, 1, 0);

    while (stage_CheckAnimationFrame(129, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1314, 0, 0, 1);

    while (stage_CheckAnimationFrame(129, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 1);
    SetWayGroupActive(38, 1);

    gflagOff(281);

    fence_down1_mes[0].func = actSt10rFenceUpChk;
    sub->mail = fence_down1_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10rFenceUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1527), 5.0f) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1533)->active = 1;
    scpSearchGobj(1534)->active = 1;
    scpSearchGobj(1535)->active = 1;
    scpSearchGobj(1536)->active = 1;

    stage_SetAnimation(129, 1, 31);

    while (stage_CheckAnimationFrame(129, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1314, 0, 0, 1);

    while (stage_CheckAnimationFinish(129) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 0);
    SetWayGroupActive(38, 0);

    gflagOn(281);

    fence_up1_mes[0].func = actSt10rFenceDownChk;
    sub->mail = fence_up1_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10rFenceDownChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1525), 5.0f) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1529)->active = 0;
    scpSearchGobj(1530)->active = 0;
    scpSearchGobj(1531)->active = 0;
    scpSearchGobj(1532)->active = 0;

    stage_SetAnimation(129, 1, 0);

    while (stage_CheckAnimationFrame(129, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1314, 0, 0, 1);

    while (stage_CheckAnimationFrame(129, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 1);
    SetWayGroupActive(38, 1);

    gflagOff(281);

    fence_down2_mes[0].func = actSt10rFenceUpChk2;
    sub->mail = fence_down2_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10rFenceUpChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1525), 5.0f) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1529)->active = 1;
    scpSearchGobj(1530)->active = 1;
    scpSearchGobj(1531)->active = 1;
    scpSearchGobj(1532)->active = 1;

    stage_SetAnimation(129, 1, 31);

    while (stage_CheckAnimationFrame(129, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1314, 0, 0, 1);

    while (stage_CheckAnimationFinish(129) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 0);
    SetWayGroupActive(38, 0);

    gflagOn(281);

    fence_up2_mes[0].func = actSt10rFenceDownChk2;
    sub->mail = fence_up2_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10rFloor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(274) == 0) {
        floor_mes[0].func = actSt10rFloorChk;
        act->mail = floor_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10rCage(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    scpSetCageVelocityFriction(1521, 0.95f);

    if (gflagChk(275) == 0) {
        cage_mes[0].func = actSt10rCageMain;
        act->mail = cage_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10rTower(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(276) == 0) {
        tower_mes[0].func = actSt10rTowerChk;
        act->mail = tower_mes;
        ACTSendMailCorrect(self, 397);
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
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10rChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(277) == 0) {
        stage_SetAnimation(351, 0, 0);
        scpSearchGobj(1516)->active = 0;

        chain_mes[0].func = actSt10rChainMain;
        act->mail = chain_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(351, 0, -1);
    }
}

void actSt10rSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpSekizou(self, 278, 354, 0, 18, 0.0f, 327.0f, 4649.0f, -75.0f, 327.0f, 4649.0f);
}

void actSt10rEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(279) == 0) {
        ene_mes[0].func = actSt10rEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10rEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(280) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);

    Generator_MaskOff(self);
}

void actSt10rEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(280) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);
}

void actSt10rElv(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(290) != 0) {
        scpSearchGobj(1527)->active = 0;
        scpSearchGobj(1528)->active = 0;
        gflagOff(290);
    } else {
        scpSearchGobj(1525)->active = 0;
        scpSearchGobj(1526)->active = 0;
    }
}

void actSt10rGateXL(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(218) == 0) {
        scpSearchGobj(1493)->active = 0;
    } else {
        scpSearchGobj(1492)->active = 0;
    }
}

void actSt10rGirlWay(volatile unsigned int self)
{
    long long buf[2];
    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
    _ACTWait(0);
}

void actSt10rExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(282);
    gflagOff(290);

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        OnGirlEscortFlag();
        RequestStageChange(1, boyGObj, girlGObj, 2.0f, 8.0f);
    }
    RequestStageChange(1, boyGObj, 0, 2.0f, 8.0f);
}

void actSt10rChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

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
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10rSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt10rEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    gflagOn(279);
    gflagOn(280);
}
