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

#ifndef VERSION_AUG6
static void actSt10lEneKillChk(GObj *volatile self);
#endif

/* .rodata: the girl's way-point packet for actSt10lEneCam3Chk, a 16-byte
   constant vector template whose long long view the copy reads */

static const ConstVec eneCam3ChkPos = {{-33.0f, -72.0f, 470.0f, 0.0f}}; /* derived name */

/* .data: actor mail packets. */

#ifdef VERSION_NTSC
static ActMail floorMain_mes[2] = {{376, actSt10lFloorSwitch}, {396}}; /* derived name */

static ActMail floor_mes[2] = {{397}, {396}}; /* derived name */

static ActMail floorSwitchRight_mes[2] = {{397}, {396}}; /* derived name */

static ActMail floorSwitchLeft_mes[2] = {{397}, {396}}; /* derived name */

static ActMail floorLeft_mes[2] = {{397}, {396}}; /* derived name */

static ActMail floorRight_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaMain_mes[2] = {{377, actSt10lGondolaSwitch}, {396}}; /* derived name */

static ActMail gondola_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaSwitchDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaSwitchUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail eneCam1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box_mes[2] = {{397}, {396}}; /* derived name */

static ActMail eneCam2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail eneCam3_mes[2] = {{397}, {396}}; /* derived name */

static ActMail boxA_mes[2] = {{397}, {396}}; /* derived name */

static ActMail boxB_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainMain_mes[2] = {{378, actSt10lChainSwitch}, {396}}; /* derived name */

static ActMail chain_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail eneKill_mes[2] = {{397}, {396}}; /* derived name */
#else
#ifdef VERSION_AUG6
static ActMail floorMain_mes[2] = {{372, actSt10lFloorSwitch}, {392}}; /* derived name */

static ActMail floor_mes[2] = {{393}, {392}}; /* derived name */

static ActMail floorSwitchRight_mes[2] = {{393}, {392}}; /* derived name */

static ActMail floorSwitchLeft_mes[2] = {{393}, {392}}; /* derived name */

static ActMail floorLeft_mes[2] = {{393}, {392}}; /* derived name */

static ActMail floorRight_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondolaMain_mes[2] = {{373, actSt10lGondolaSwitch}, {392}}; /* derived name */

static ActMail gondola_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondolaSwitchDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondolaSwitchUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondolaUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondolaDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail eneCam1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail box_mes[2] = {{393}, {392}}; /* derived name */

static ActMail eneCam2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail eneCam3_mes[2] = {{393}, {392}}; /* derived name */

static ActMail boxA_mes[2] = {{393}, {392}}; /* derived name */

static ActMail boxB_mes[2] = {{393}, {392}}; /* derived name */

static ActMail chainMain_mes[2] = {{374, actSt10lChainSwitch}, {392}}; /* derived name */

static ActMail chain_mes[2] = {{393}, {392}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{393}, {392}}; /* derived name */
#else
static ActMail floorMain_mes[2] = {{406, actSt10lFloorSwitch}, {429}}; /* derived name */

static ActMail floor_mes[2] = {{430}, {429}}; /* derived name */

static ActMail floorSwitchRight_mes[2] = {{430}, {429}}; /* derived name */

static ActMail floorSwitchLeft_mes[2] = {{430}, {429}}; /* derived name */

static ActMail floorLeft_mes[2] = {{430}, {429}}; /* derived name */

static ActMail floorRight_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaMain_mes[2] = {{407, actSt10lGondolaSwitch}, {429}}; /* derived name */

static ActMail gondola_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaSwitchDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaSwitchUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail eneCam1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail box_mes[2] = {{430}, {429}}; /* derived name */

static ActMail eneCam2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail eneCam3_mes[2] = {{430}, {429}}; /* derived name */

static ActMail boxA_mes[2] = {{430}, {429}}; /* derived name */

static ActMail boxB_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainMain_mes[2] = {{408, actSt10lChainSwitch}, {429}}; /* derived name */

static ActMail chain_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail eneKill_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif

/* .sdata: the floor, gondola and chain stream handles. */
SqEntry *floor10l = 0;

SqEntry *st10l_gondola_up = 0;

SqEntry *st10l_gondola_down = 0;

SqEntry *chain10l = 0;

#ifdef VERSION_NTSC
void actSt10lInit(void)
{
    if (gflagChk(263) != 0) {
        SetWayGroupActive(22, 1);
        SetWayGroupActive(23, 1);
        stage_SetAnimation(344, 0, 89);
    } else {
        SetWayGroupActive(20, 1);
        SetWayGroupActive(21, 1);
        stage_SetAnimation(344, 0, 0);
    }
}

void actSt10lFloorLeft(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (gflagChk(264) == 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        gflagOn(264);
    }

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        scpPlayStart(girlGObj);
        scpPlayMot(girlGObj, 514);
    }

    if (gflagChk(264) != 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        scpPlayPosSet(girlGObj, -167.0f, -72.0f, -705.0f);
        scpPlayStart(girlGObj);
        scpPlayMot(girlGObj, 514);
    }

    scpAdpcmPlayRequestFunc(89, &floor10l, 1, 1, 1);

    while (floor10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(344, 1, 0);

    SetWayGroupActive(20, 0);
    SetWayGroupActive(21, 0);
    SetWayGroupActive(22, 1);
    SetWayGroupActive(23, 1);

    gflagOn(263);

    while (stage_CheckAnimationFrame(344, 89, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(264) != 0) {
        gflagOn(270);
    }

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 10);

    if (gflagChk(269) == 0) {
        scpBoyControlReadDisable = 0;
        lt_switch_layout(50);
        scpWakeupEnemyAll();

        if (girlGObj != 0) {
            scpPlayEnd(girlGObj);
        }
    }

    floorLeft_mes[0].func = actSt10lFloorMain;
    sub->mail = floorLeft_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10lFloorRight(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (gflagChk(264) != 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        scpPlayPosSet(girlGObj, -196.0f, -72.0f, 62.0f);
        scpPlayStart(girlGObj);
        scpPlayMot(girlGObj, 514);
    }

    scpAdpcmPlayRequestFunc(89, &floor10l, 1, 1, 1);

    while (floor10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(344, 1, 90);

    SetWayGroupActive(20, 1);
    SetWayGroupActive(21, 1);
    SetWayGroupActive(22, 0);
    SetWayGroupActive(23, 0);

    gflagOff(263);

    while (stage_CheckAnimationFrame(344, 180, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 11);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    scpWakeupEnemyAll();

    if (girlGObj != 0) {
        scpPlayEnd(girlGObj);
    }

    floorRight_mes[0].func = actSt10lFloorMain;
    sub->mail = floorRight_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10lGondolaUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(86, &st10l_gondola_up, 1, 1, 1);

    while (st10l_gondola_up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(345, 1, 0);

    while (stage_CheckAnimationFrame(345, 169, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFrame(345, 179, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(265);

    if (st10l_gondola_up != 0) {
        scpAdpcmFadeClose(st10l_gondola_up, 256);
    }

    while (scpAdpcmCloseChk(st10l_gondola_up) != 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(50);

    gondolaUp_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaUp_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10lGondolaDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    SetGirlDangerGObj(boyGObj);

    scpAdpcmPlayRequestFunc(87, &st10l_gondola_down, 1, 1, 1);

    while (st10l_gondola_down == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(345, 1, 180);

    while (stage_CheckAnimationFrame(345, 340, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(345, 360, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(265);

    if (st10l_gondola_down != 0) {
        scpAdpcmFadeClose(st10l_gondola_down, 256);
    }

    while (scpAdpcmCloseChk(st10l_gondola_down) != 0) {
        _ACTWait(1);
    }

    ClearGirlDangerGObj();

    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(50);

    gondolaDown_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaDown_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10lEneCam2Chk(GObj *volatile self)
{
    while (girlGObj == 0 || scpTriggerFloorAttr(boyGObj, 0x4000000) == 0 || gflagChk(261) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpSleepEnemyOne(3453);
    scpSleepEnemyOne(903);
    scpSleepEnemyOne(906);
    scpSleepEnemyOne(907);
    scpSleepSpiderGroupOne(908);

    _ACTWait(30);

    gflagOn(268);

    stage_SetAnimation(346, 1, 0);

    while (stage_CheckAnimationFinish(346) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait(60);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;

    scpWakeupEnemyOne(3453);
    scpWakeupEnemyOne(903);
    scpWakeupEnemyOne(906);
    scpWakeupEnemyOne(907);
    scpWakeupSpiderGroupOne(908);
}

void actSt10lEneCam3Chk(GObj *volatile self)
{
    long long buf[2];

    while (gflagChk(270) == 0) {
        _ACTWait(1);
    }

    gflagOn(269);

    stage_SetAnimation(347, 1, 0);

    buf[0] = eneCam3ChkPos.d[0];
    buf[1] = eneCam3ChkPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);

    while (stage_CheckAnimationFinish(347) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(269);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 3);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
}

void actSt10lChainMove(GObj *volatile self)
{
    lt_switch_layout(51);
    scpSleepEnemyAll();

    gflagOn(261);

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(95, &chain10l, 1, 1, 1);

    while (chain10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(349, 1, 0);
    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(349, 240, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(899)->active = 1;

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt10lChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(261) == 0) {
        stage_SetAnimation(349, 0, 0);

        scpSearchGobj(899)->active = 0;

        chain_mes[0].func = actSt10lChainMain;
        act->mail = chain_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(349, 0, -1);
    }
}
#else
void actSt10lInit(void)
{
#ifdef VERSION_AUG6
    if (gflagChk(263) != 0) {
        SetWayGroupActive(22, 1);
        SetWayGroupActive(23, 1);
        stage_SetAnimation(343, 0, 89);
#else
    if (gflagChk(289) != 0) {
        SetWayGroupActive(22, 1);
        SetWayGroupActive(23, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(375, 0, 89);
#else
        stage_SetAnimation(379, 0, 89);
#endif
#endif
    } else {
        SetWayGroupActive(20, 1);
        SetWayGroupActive(21, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(375, 0, 0);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(343, 0, 0);
#else
        stage_SetAnimation(379, 0, 0);
#endif
#endif
    }
}

void actSt10lFloorLeft(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    if (gflagChk(264) == 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        gflagOn(264);
#else
    if (gflagChk(290) == 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        gflagOn(290);
#endif
    }

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        scpPlayStart(girlGObj);
#ifdef VERSION_AUG6
        scpPlayMot(girlGObj, 514);
    }

    if (gflagChk(264) != 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        scpPlayPosSet(girlGObj, -167.0f, -72.0f, -705.0f);
        scpPlayStart(girlGObj);
        scpPlayMot(girlGObj, 514);
    }

    scpAdpcmPlayRequestFunc(89, &floor10l, 1, 1, 1);
#else
        scpPlayMot(girlGObj, 532);
    }

    if (gflagChk(290) != 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        scpPlayPosSet(girlGObj, -167.0f, -72.0f, -705.0f);
        scpPlayStart(girlGObj);
        scpPlayMot(girlGObj, 532);
    }

    scpAdpcmPlayRequestFunc(91, &floor10l, 1, 1, 1);
#endif

    while (floor10l == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(375, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(343, 1, 0);
#else
    stage_SetAnimation(379, 1, 0);
#endif
#endif

    SetWayGroupActive(20, 0);
    SetWayGroupActive(21, 0);
    SetWayGroupActive(22, 1);
    SetWayGroupActive(23, 1);

#ifdef VERSION_AUG6
    gflagOn(263);

    while (stage_CheckAnimationFrame(343, 89, 1) == 0) {
#else
    gflagOn(289);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(375, 89, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(379, 89, 1) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(264) != 0) {
        gflagOn(270);
    }

    _ACTWait(60);
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 9);
#else
    if (gflagChk(290) != 0) {
        gflagOn(296);
    }

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 10);

    if (gflagChk(295) == 0) {
        scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        lt_switch_layout(51);
#else
        lt_switch_layout(54);
#endif
        scpWakeupEnemyAll();

        if (girlGObj != 0) {
            scpPlayEnd(girlGObj);
        }
    }
#endif

    floorLeft_mes[0].func = actSt10lFloorMain;
    sub->mail = floorLeft_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt10lFloorRight(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    if (gflagChk(264) != 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        scpPlayPosSet(girlGObj, -196.0f, -72.0f, 62.0f);
        scpPlayStart(girlGObj);
        scpPlayMot(girlGObj, 514);
    }

    scpAdpcmPlayRequestFunc(89, &floor10l, 1, 1, 1);
#else
    if (gflagChk(290) != 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        scpPlayPosSet(girlGObj, -196.0f, -72.0f, 62.0f);
        scpPlayStart(girlGObj);
        scpPlayMot(girlGObj, 532);
    }

    scpAdpcmPlayRequestFunc(91, &floor10l, 1, 1, 1);
#endif

    while (floor10l == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(375, 1, 90);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(343, 1, 90);
#else
    stage_SetAnimation(379, 1, 90);
#endif
#endif

    SetWayGroupActive(20, 1);
    SetWayGroupActive(21, 1);
    SetWayGroupActive(22, 0);
    SetWayGroupActive(23, 0);

#ifdef VERSION_AUG6
    gflagOff(263);

    while (stage_CheckAnimationFrame(343, 180, 1) == 0) {
#else
    gflagOff(289);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(375, 180, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(379, 180, 1) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 11);

#ifdef VERSION_AUG6
    floorRight_mes[0].func = actSt10lFloorMain;
    sub->mail = floorRight_mes;
    ACTSendMailCorrect(self, 393);
#else
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpWakeupEnemyAll();

    if (girlGObj != 0) {
        scpPlayEnd(girlGObj);
    }

    floorRight_mes[0].func = actSt10lFloorMain;
    sub->mail = floorRight_mes;
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt10lGondolaUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(86, &st10l_gondola_up, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(88, &st10l_gondola_up, 1, 1, 1);
#endif

    while (st10l_gondola_up == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(344, 1, 0);

    while (stage_CheckAnimationFrame(344, 169, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(376, 1, 0);
#else
    stage_SetAnimation(380, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(376, 169, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(380, 169, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(376, 179, 1) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(344, 179, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(380, 179, 1) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    gflagOn(265);

    if (st10l_gondola_up != 0) {
        scpAdpcmFadeClose(st10l_gondola_up, 256);
    }

    while (scpAdpcmCloseChk(st10l_gondola_up) != 0) {
#else
    gflagOn(291);

    if (st10l_gondola_up != 0) {
        scpAdpcmFadeCloseFunc(&st10l_gondola_up, 256);
    }

    while (scpAdpcmCloseChkFunc(&st10l_gondola_up) != 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gondolaUp_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaUp_mes;
    ACTSendMailCorrect(self, 393);
#else
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    gondolaUp_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaUp_mes;
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt10lGondolaDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    SetGirlDangerGObj(boyGObj);

#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(87, &st10l_gondola_down, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(89, &st10l_gondola_down, 1, 1, 1);
#endif

    while (st10l_gondola_down == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(344, 1, 180);

    while (stage_CheckAnimationFrame(344, 340, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(376, 1, 180);
#else
    stage_SetAnimation(380, 1, 180);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(376, 340, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(380, 340, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(376, 360, 1) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(344, 360, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(380, 360, 1) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    gflagOff(265);

    if (st10l_gondola_down != 0) {
        scpAdpcmFadeClose(st10l_gondola_down, 256);
    }

    while (scpAdpcmCloseChk(st10l_gondola_down) != 0) {
#else
    gflagOff(291);

    if (st10l_gondola_down != 0) {
        scpAdpcmFadeCloseFunc(&st10l_gondola_down, 256);
    }

    while (scpAdpcmCloseChkFunc(&st10l_gondola_down) != 0) {
#endif
        _ACTWait(1);
    }

    ClearGirlDangerGObj();

#ifdef VERSION_AUG6
    gondolaDown_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaDown_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
#else
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    gondolaDown_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaDown_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10lEneCam2Chk(GObj *volatile self)
{
    int save;

    while (girlGObj == 0 || scpTriggerFloorAttr(boyGObj, 0x4000000) == 0 || gflagChk(287) == 0 ||
           GOBJ_ACT(girlGObj)->actMode == 111) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

    save = iosPadActRequestEnable;
    iosPadActRequestEnable = 0;

    scpKillEnemyOne(992);
    scpKillEnemyOne(993);
    scpKillSpiderGroup(994);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSleepEnemyOne(3734);
#else
    scpSleepEnemyOne(3757);
#endif
    scpSleepEnemyOne(991);
    scpSleepEnemyOne(1006);
    scpSleepSpiderGroupOne(1007);

    _ACTWait(30);

    gflagOn(294);

    iosPadActRequestEnable = save;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(377, 1, 0);
#else
    stage_SetAnimation(381, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(377) == 0) {
#else
    while (stage_CheckAnimationFinish(381) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 3);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpWakeupEnemyOne(3734);
#else
    scpWakeupEnemyOne(3757);
#endif
    scpWakeupEnemyOne(992);
    scpWakeupEnemyOne(993);
    scpWakeupSpiderGroupOne(994);
    scpWakeupEnemyOne(991);
    scpWakeupEnemyOne(1006);
    scpWakeupSpiderGroupOne(1007);
#endif
}

void actSt10lEneCam3Chk(GObj *volatile self)
{
    long long buf[2];

#ifdef VERSION_AUG6
    while (gflagChk(270) == 0) {
#else
    while (gflagChk(296) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(269);

    stage_SetAnimation(346, 1, 0);
#else
    gflagOn(295);
    FinishHint(14);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(378, 1, 0);
#else
    stage_SetAnimation(382, 1, 0);
#endif
#endif

    buf[0] = eneCam3ChkPos.d[0];
    buf[1] = eneCam3ChkPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(378) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(346) == 0) {
#else
    while (stage_CheckAnimationFinish(382) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    gflagOff(269);
#else
    gflagOff(295);
#endif

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 3);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
}

void actSt10lChainMove(GObj *volatile self)
{
#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpSleepEnemyAll();

    gflagOn(261);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpSleepEnemyAll();

    gflagOn(287);
    FinishHint(13);
#endif

    _ACTWait(30);

#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(95, &chain10l, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(97, &chain10l, 1, 1, 1);
#endif

    while (chain10l == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(348, 1, 0);
    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(348, 240, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(898)->active = 1;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(380, 1, 0);
#else
    stage_SetAnimation(384, 1, 0);
#endif
    SetCameraFlag_LwsCutBack();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(380, 240, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(384, 240, 0) == 0) {
#endif
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);
            scpAdpcmFadeCloseFunc(&chain10l, 512);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(380, 1, 239);
#else
            stage_SetAnimation(384, 1, 239);
#endif
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }
#endif

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
#ifdef VERSION_AUG6
    lt_switch_layout(50);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1]);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(380, 0, 0);
#else
    stage_SetAnimation(384, 0, 0);
#endif

    scpSearchGobj(985)->active = 1;
#endif
}

void actSt10lChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(261) == 0) {
        stage_SetAnimation(348, 0, 0);

        scpSearchGobj(898)->active = 0;
#else
    if (gflagChk(287) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(380, 0, 0);
#else
        stage_SetAnimation(384, 0, 0);
#endif

        scpSearchGobj(985)->active = 0;
#endif

        chain_mes[0].func = actSt10lChainMain;
        act->mail = chain_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(348, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(380, 0, 0);
#else
        stage_SetAnimation(384, 0, 0);
#endif
        FinishHint(13);
#endif
    }
}
#endif

void actSt10lFloor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    floor_mes[0].func = actSt10lFloorMain;
    act->mail = floor_mes;
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
void actSt10lGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(265) != 0) {
        stage_SetAnimation(345, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(345, 0, 179);
    } else {
        stage_SetAnimation(345, 0, 0);
    }

    gondola_mes[0].func = actSt10lGondolaMain;
    act->mail = gondola_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
#else
void actSt10lGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(265) != 0) {
        stage_SetAnimation(344, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(344, 0, 179);
    } else {
        stage_SetAnimation(344, 0, 0);
#else
    if (gflagChk(291) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(376, 0, 0);
#else
        stage_SetAnimation(380, 0, 0);
#endif
        _ACTWait(10);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(376, 0, 179);
#else
        stage_SetAnimation(380, 0, 179);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(376, 0, 0);
#else
        stage_SetAnimation(380, 0, 0);
#endif
#endif
    }

    gondola_mes[0].func = actSt10lGondolaMain;
    act->mail = gondola_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}
#endif

void actSt10lSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSekizou(self, 288, 379, 0, 19, 0.0f, -72.0f, 1274.0f, 76.0f, -72.0f, 1274.0f);
#else
#ifdef VERSION_NTSC
    scpSekizou(self, 262, 348, 0, 18, 0.0f, -72.0f, 1274.0f, 76.0f, -72.0f, 1274.0f);
#else
#ifdef VERSION_AUG6
    scpSekizou(self, 262, 347, 0, 18, 0.0f, -72.0f, 1274.0f, 76.0f, -72.0f, 1274.0f);
#else
    scpSekizou(self, 288, 383, 0, 19, 0.0f, -72.0f, 1274.0f, 76.0f, -72.0f, 1274.0f);
#endif
#endif
#endif
}

void actSt10lBox(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    box_mes[0].func = actSt10lBoxChk;
    act->mail = box_mes;
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
void actSt10lEnemy1_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(267) == 0) {
        _ACTWait(1);
    }
    _ACTWait(116);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy1_2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(267) == 0) {
        _ACTWait(1);
    }
    _ACTWait(100);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy2_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(268) == 0) {
        _ACTWait(1);
    }
    _ACTWait(116);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy2_2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(268) == 0) {
        _ACTWait(1);
    }
    _ACTWait(100);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy2_3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(268) == 0) {
        _ACTWait(1);
    }
    _ACTWait(130);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy3_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(269) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy3_2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(269) == 0) {
        _ACTWait(1);
    }
    _ACTWait(320);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEneCam1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(267) == 0) {
        eneCam1_mes[0].func = actSt10lEneCam1Chk;
        act->mail = eneCam1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10lEneCam2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(268) == 0) {
        eneCam2_mes[0].func = actSt10lEneCam2Chk;
        act->mail = eneCam2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10lEneCam3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(270) == 0) {
        eneCam3_mes[0].func = actSt10lEneCam3Chk;
        act->mail = eneCam3_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10lEneKill(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(271) == 0) {
        eneKill_mes[0].func = actSt10lEneKillChk;
        act->mail = eneKill_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10lBoxA(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(272) == 0) {
        boxA_mes[0].func = actSt10lBoxAChk;
        act->mail = boxA_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpSearchGobj(891)->active = 0;
    }
}

void actSt10lBoxB(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(273) == 0) {
        boxB_mes[0].func = actSt10lBoxBChk;
        act->mail = boxB_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpSearchGobj(892)->active = 0;
    }
}

void actSt10lGateXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(155) == 0) {
        scpSearchGobj(885)->active = 0;
    } else {
        scpSearchGobj(884)->active = 0;
    }
}
#else
void actSt10lEnemy1_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);
#ifdef VERSION_AUG6

    while (gflagChk(267) == 0) {
#else
    Generator_Mask(scpSearchGobj(997));

    while (gflagChk(293) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(116);

    Generator_Call(self);
    Generator_MaskOff(self);
#ifndef VERSION_AUG6
    Generator_Call(scpSearchGobj(997));
#endif
}

void actSt10lEnemy1_2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(267) == 0) {
#else
    while (gflagChk(293) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(100);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy2_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(268) == 0) {
#else
    while (gflagChk(294) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(116);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy2_2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(268) == 0) {
#else
    while (gflagChk(294) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(100);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy2_3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(268) == 0) {
#else
    while (gflagChk(294) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(130);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy3_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(269) == 0) {
#else
    while (gflagChk(295) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy3_2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(269) == 0) {
#else
    while (gflagChk(295) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(320);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEneCam1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(267) == 0) {
        eneCam1_mes[0].func = actSt10lEneCam1Chk;
        act->mail = eneCam1_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(293) == 0) {
        eneCam1_mes[0].func = actSt10lEneCam1Chk;
        act->mail = eneCam1_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt10lEneCam2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(268) == 0) {
        eneCam2_mes[0].func = actSt10lEneCam2Chk;
        act->mail = eneCam2_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(294) == 0) {
        eneCam2_mes[0].func = actSt10lEneCam2Chk;
        act->mail = eneCam2_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt10lEneCam3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(270) == 0) {
        eneCam3_mes[0].func = actSt10lEneCam3Chk;
        act->mail = eneCam3_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(296) == 0) {
        eneCam3_mes[0].func = actSt10lEneCam3Chk;
        act->mail = eneCam3_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        FinishHint(14);
    }
}

void actSt10lEneKill(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(297) == 0) {
        eneKill_mes[0].func = actSt10lEneKillChk;
        act->mail = eneKill_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt10lBoxA(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(271) == 0) {
        boxA_mes[0].func = actSt10lBoxAChk;
        act->mail = boxA_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpSearchGobj(890)->active = 0;
#else
    if (gflagChk(298) == 0) {
        boxA_mes[0].func = actSt10lBoxAChk;
        act->mail = boxA_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(977)->active = 0;
#endif
    }
}

void actSt10lBoxB(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(272) == 0) {
        boxB_mes[0].func = actSt10lBoxBChk;
        act->mail = boxB_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpSearchGobj(891)->active = 0;
#else
    if (gflagChk(299) == 0) {
        boxB_mes[0].func = actSt10lBoxBChk;
        act->mail = boxB_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(978)->active = 0;
#endif
    }
}

void actSt10lGateXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(155) == 0) {
        scpSearchGobj(884)->active = 0;
    } else {
        scpSearchGobj(883)->active = 0;
#else
    if (gflagChk(174) == 0) {
        scpSearchGobj(971)->active = 0;
    } else {
        scpSearchGobj(970)->active = 0;
#endif
    }
}
#endif

void actSt10lFloorMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    if (gflagChk(269) == 0) {
        scpBoyControlReadDisable = 0;
        lt_switch_layout(50);
        scpWakeupEnemyAll();

        if (girlGObj != 0) {
            scpPlayEnd(girlGObj);
        }
    }
#endif

    sub->mainMail = floorMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
void actSt10lFloorSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    if (gflagChk(263) != 0) {
        floorSwitchRight_mes[0].func = actSt10lFloorRight;
        sub->mail = floorSwitchRight_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }

    floorSwitchLeft_mes[0].func = actSt10lFloorLeft;
    sub->mail = floorSwitchLeft_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
#else
void actSt10lFloorSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

#ifdef VERSION_AUG6
    if (gflagChk(263) != 0) {
        floorSwitchRight_mes[0].func = actSt10lFloorRight;
        sub->mail = floorSwitchRight_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(289) != 0) {
        floorSwitchRight_mes[0].func = actSt10lFloorRight;
        sub->mail = floorSwitchRight_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }

    floorSwitchLeft_mes[0].func = actSt10lFloorLeft;
    sub->mail = floorSwitchLeft_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}
#endif

void actSt10lGondolaMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(50);
#endif

    sub->mainMail = gondolaMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
void actSt10lGondolaSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    if (gflagChk(265) != 0) {
        gondolaSwitchDown_mes[0].func = actSt10lGondolaDown;
        sub->mail = gondolaSwitchDown_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }

    gondolaSwitchUp_mes[0].func = actSt10lGondolaUp;
    sub->mail = gondolaSwitchUp_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10lEneCam1Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while ((scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 || gflagChk(266) == 0) &&
           (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 ||
            scpTriggerFloorAttr(girlGObj, 0x2000000) == 0)) {
        _ACTWait(1);
    }

    gflagOn(267);
}

void actSt10lBoxChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(scpSearchGobj(902), 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(266);
}
#else
void actSt10lGondolaSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

#ifdef VERSION_AUG6
    if (gflagChk(265) != 0) {
        gondolaSwitchDown_mes[0].func = actSt10lGondolaDown;
        sub->mail = gondolaSwitchDown_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(291) != 0) {
        gondolaSwitchDown_mes[0].func = actSt10lGondolaDown;
        sub->mail = gondolaSwitchDown_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }

    gondolaSwitchUp_mes[0].func = actSt10lGondolaUp;
    sub->mail = gondolaSwitchUp_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt10lEneCam1Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

#ifdef VERSION_AUG6
    while ((scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 || gflagChk(266) == 0) &&
           (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 ||
            scpTriggerFloorAttr(girlGObj, 0x2000000) == 0)) {
#else
    while ((girlGObj == 0 || gflagChk(292) == 0) &&
           (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 ||
            scpTriggerFloorAttr(girlGObj, 0x2000000) == 0)) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(267);
#else
    gflagOn(293);
#endif
}

void actSt10lBoxChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

#ifdef VERSION_AUG6
    while (scpTriggerFloorAttr(scpSearchGobj(901), 0x1000000) == 0) {
#else
    while (scpTriggerFloorAttr(scpSearchGobj(988), 0x1000000) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(266);
}

void actSt10lEneCam2Chk(GObj *volatile self)
{
    while (girlGObj == 0 || scpTriggerFloorAttr(boyGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    _ACTWait(30);

    gflagOn(268);

    stage_SetAnimation(345, 1, 0);

    while (stage_CheckAnimationFinish(345) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
#else
    gflagOn(292);
#endif
}
#endif

void actSt10lSekizoEvent(int x)
{
    volatile int local = x;
}

#ifdef VERSION_NTSC
void actSt10lBoxAChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(891), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(272);
    scpSearchGobj(891)->active = 0;
    _ACTWait(30);
    soundSeDefPlay(1246, 0, 0, 1);
}

void actSt10lBoxBChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(892), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(273);
    scpSearchGobj(892)->active = 0;
    _ACTWait(30);
    soundSeDefPlay(1247, 0, 0, 1);
}
#else
void actSt10lBoxAChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpTriggerBall(self, scpSearchGobj(890), 100.0f) == 0) {
#else
    while (scpTriggerBall(self, scpSearchGobj(977), 100.0f) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(271);
    scpSearchGobj(890)->active = 0;
#else
    gflagOn(298);
    scpSearchGobj(977)->active = 0;
    _ACTWait(30);
    soundSeDefPlay(1270, 0, 0, 1);
#endif
}

void actSt10lBoxBChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpTriggerBall(self, scpSearchGobj(891), 100.0f) == 0) {
#else
    while (scpTriggerBall(self, scpSearchGobj(978), 100.0f) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(272);
    scpSearchGobj(891)->active = 0;
#else
    gflagOn(299);
    scpSearchGobj(978)->active = 0;
    _ACTWait(30);
    soundSeDefPlay(1271, 0, 0, 1);
#endif
}
#endif

void actSt10lChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    scpBoyControlReadDisable = 0;
#endif
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

#ifndef VERSION_AUG6
static void actSt10lEneKillChk(GObj *volatile self)
{
    int save;

    while (scpTriggerBall(self, boyGObj, 500.0f) == 0) {
        _ACTWait(1);
    }

    enable_game_pause = 0;
    _ACTWait(1);

    save = iosPadActRequestEnable;
    iosPadActRequestEnable = 0;
    _ACTWait(30);

#ifdef VERSION_NTSC
    gflagOn(271);
    scpKillEnemyOne(904);
    scpKillEnemyOne(913);
    scpKillEnemyOne(914);
    scpKillSpiderGroup(915);
#else
    gflagOn(297);
    scpKillEnemyOne(1000);
    scpKillEnemyOne(1001);
    scpKillSpiderGroup(1002);
#endif
    _ACTWait(30);

    iosPadActRequestEnable = save;
    _ACTWait(1);
    enable_game_pause = 1;
}
#endif
