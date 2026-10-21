#include "st10l.h"
#include "layout_texture.h"
#include "pad.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "girl_act.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "layout_action.h"
#include "script.h"
#include "main.h"

/* .rodata: the girl's way-point packet for actSt10lEneCam3Chk, a 16-byte
   constant vector template whose long long view the copy reads */

static const ConstVec eneCam3ChkPos = {{-33.0f, -72.0f, 470.0f, 0.0f}}; /* derived name */

/* .data: actor mail packets. */

static ActMail floorMain_mes[2] = {{356, actSt10lFloorSwitch}, {376}}; /* derived name */

static ActMail floor_mes[2] = {{377}, {376}}; /* derived name */

static ActMail floorSwitchRight_mes[2] = {{377}, {376}}; /* derived name */

static ActMail floorSwitchLeft_mes[2] = {{377}, {376}}; /* derived name */

static ActMail floorLeft_mes[2] = {{377}, {376}}; /* derived name */

static ActMail floorRight_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondolaMain_mes[2] = {{357, actSt10lGondolaSwitch}, {376}}; /* derived name */

static ActMail gondola_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondolaSwitchDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondolaSwitchUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondolaUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondolaDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail box_mes[2] = {{377}, {376}}; /* derived name */

static ActMail eneCam2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail eneCam3_mes[2] = {{377}, {376}}; /* derived name */

static ActMail boxA_mes[2] = {{377}, {376}}; /* derived name */

static ActMail boxB_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chainMain_mes[2] = {{358, actSt10lChainSwitch}, {376}}; /* derived name */

static ActMail chain_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{377}, {376}}; /* derived name */

/* .sdata: the gondola stream handles (actSt10lGondolaUp's and
   actSt10lGondolaDown's); this build has no floor or chain handle. */
SqEntry *st10l_gondola_up = 0;

SqEntry *st10l_gondola_down = 0;

void actSt10lInit(void)
{
    if (gflagChk(254) != 0) {
        stage_SetAnimation(310, 0, 89);
    } else {
        stage_SetAnimation(310, 0, 0);
    }
}

void actSt10lFloorLeft(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (gflagChk(255) == 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        gflagOn(255);
    }

    scpAdpcmPlayRequestFunc(84, 0, 1, 1, 1);

    stage_SetAnimation(310, 1, 0);

    gflagOn(254);

    while (stage_CheckAnimationFrame(310, 89, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(255) != 0) {
        gflagOn(260);
    }

    _ACTWait(60);
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 9);

    floorLeft_mes[0].func = actSt10lFloorMain;
    sub->mail = floorLeft_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10lFloorRight(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(84, 0, 1, 1, 1);

    stage_SetAnimation(310, 1, 90);

    gflagOff(254);

    while (stage_CheckAnimationFrame(310, 180, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 11);

    floorRight_mes[0].func = actSt10lFloorMain;
    sub->mail = floorRight_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10lGondolaUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(81, &st10l_gondola_up, 1, 1, 1);

    while (st10l_gondola_up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(311, 1, 0);

    while (stage_CheckAnimationFrame(311, 169, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFrame(311, 179, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(256);

    if (st10l_gondola_up != 0) {
        scpAdpcmFadeClose(st10l_gondola_up, 256);
    }

    while (scpAdpcmCloseChk(st10l_gondola_up) != 0) {
        _ACTWait(1);
    }

    gondolaUp_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaUp_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10lGondolaDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    SetGirlDangerGObj(boyGObj);

    scpAdpcmPlayRequestFunc(82, &st10l_gondola_down, 1, 1, 1);

    while (st10l_gondola_down == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(311, 1, 180);

    while (stage_CheckAnimationFrame(311, 340, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(311, 360, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(256);

    if (st10l_gondola_down != 0) {
        scpAdpcmFadeClose(st10l_gondola_down, 256);
    }

    while (scpAdpcmCloseChk(st10l_gondola_down) != 0) {
        _ACTWait(1);
    }

    ClearGirlDangerGObj();

    gondolaDown_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaDown_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10lEneCam3Chk(GObj *volatile self)
{
    long long buf[2];

    while (gflagChk(260) == 0) {
        _ACTWait(1);
    }

    gflagOn(259);

    stage_SetAnimation(313, 1, 0);

    buf[0] = eneCam3ChkPos.d[0];
    buf[1] = eneCam3ChkPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);

    while (stage_CheckAnimationFinish(313) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(259);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 3);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
}

void actSt10lChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(252) == 0) {
        stage_SetAnimation(315, 0, 0);

        scpSearchGobj(861)->active = 0;

        chain_mes[0].func = actSt10lChainMain;
        act->mail = chain_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(315, 0, -1);
    }
}

void actSt10lFloor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    floor_mes[0].func = actSt10lFloorMain;
    act->mail = floor_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10lGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(256) != 0) {
        stage_SetAnimation(311, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(311, 0, 179);
    } else {
        stage_SetAnimation(311, 0, 0);
    }

    gondola_mes[0].func = actSt10lGondolaMain;
    act->mail = gondola_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10lSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpSekizou(self, 253, 314, 0, 21, 0.0f, -72.0f, 1274.0f, 76.0f, -72.0f, 1274.0f);
}

void actSt10lBox(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    box_mes[0].func = actSt10lBoxChk;
    act->mail = box_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10lEnemy1_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 || gflagChk(257) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt10lEnemy2_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(258) == 0) {
        _ACTWait(1);
    }

    _ACTWait(116);
    Generator_Call(self);
}

void actSt10lEnemy2_2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(258) == 0) {
        _ACTWait(1);
    }

    _ACTWait(100);
    Generator_Call(self);
}

void actSt10lEnemy2_3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(258) == 0) {
        _ACTWait(1);
    }

    _ACTWait(130);
    Generator_Call(self);
}

void actSt10lEneCam2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(258) == 0) {
        eneCam2_mes[0].func = actSt10lEneCam2Chk;
        act->mail = eneCam2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt10lEnemy3_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(259) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_Call(self);
}

void actSt10lEnemy3_2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(259) == 0) {
        _ACTWait(1);
    }

    _ACTWait(320);
    Generator_Call(self);
}

void actSt10lEneCam3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(260) == 0) {
        eneCam3_mes[0].func = actSt10lEneCam3Chk;
        act->mail = eneCam3_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt10lBoxA(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(261) == 0) {
        boxA_mes[0].func = actSt10lBoxAChk;
        act->mail = boxA_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(853)->active = 0;
    }
}

void actSt10lBoxB(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(262) == 0) {
        boxB_mes[0].func = actSt10lBoxBChk;
        act->mail = boxB_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(854)->active = 0;
    }
}

void actSt10lGateXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(148) == 0) {
        scpSearchGobj(847)->active = 0;
    } else {
        scpSearchGobj(846)->active = 0;
    }
}

void actSt10lFloorMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (gflagChk(259) == 0) {
        scpBoyControlReadDisable = 0;
        lt_switch_layout(50);
        scpWakeupEnemyAll();
    }

    sub->mainMail = floorMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lFloorSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    if (gflagChk(254) != 0) {
        floorSwitchRight_mes[0].func = actSt10lFloorRight;
        sub->mail = floorSwitchRight_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }

    floorSwitchLeft_mes[0].func = actSt10lFloorLeft;
    sub->mail = floorSwitchLeft_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10lGondolaMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(50);

    sub->mainMail = gondolaMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lGondolaSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    if (gflagChk(256) != 0) {
        gondolaSwitchDown_mes[0].func = actSt10lGondolaDown;
        sub->mail = gondolaSwitchDown_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }

    gondolaSwitchUp_mes[0].func = actSt10lGondolaUp;
    sub->mail = gondolaSwitchUp_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10lBoxChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(scpSearchGobj(864), 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(257);
}

void actSt10lEneCam2Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    _ACTWait(30);

    gflagOn(258);

    stage_SetAnimation(312, 1, 0);

    while (stage_CheckAnimationFinish(312) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt10lSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt10lBoxAChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(853), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(261);
    scpSearchGobj(853)->active = 0;
}

void actSt10lBoxBChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(854), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(262);
    scpSearchGobj(854)->active = 0;
}

void actSt10lChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;
    sub->mainMail = chainMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lChainSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    chainSwitch_mes[0].func = actSt10lChainMove;
    sub->mail = chainSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt10lChainMove(GObj *volatile self)
{
    lt_switch_layout(51);

    gflagOn(252);

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(86, 0, 1, 1, 1);

    stage_SetAnimation(315, 1, 0);
    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(315, 240, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(861)->active = 1;

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
