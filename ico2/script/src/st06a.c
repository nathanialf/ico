#include "st06a.h"
#include "debug.h"
#include "layout_texture.h"
#include "thread.h"
#include "obj_manager.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "box.h"
#include "geometryManager.h"
#include "item.h"
#include "motionManager2.h"
#include "rotObject.h"
#include "typedef.h"
#include "stageSEProc.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt06aExitGirlChk(GObj *volatile self);
static void actSt06aKyomiOffChk(GObj *volatile self);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copies read. */

static const ConstVec doorUpEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec suimonSubPos = {{-1869.0f, -1147.0f, -664.0f, 0.0f}}; /* derived name */

static const ConstVec jumpPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec jumpPos2 = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec kyomiPos = {{-985.0f, -177.0f, -696.0f, 0.0f}}; /* derived name */

static ActMail suimon_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door_down_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door_up_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door_upchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door_downchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail shutter_main_mes[2] = {{376, actSt06aShutterSwitch}, {396}}; /* derived name */

static ActMail shutter_mes[2] = {{397}, {396}}; /* derived name */

static ActMail shutter_switch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail exit_mes[2] = {{397}, {396}}; /* derived name */

static ActMail exit_girl_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box3_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ball_delete_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box_event2_in_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box_event2_out_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box_event2_inchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box_event2_outchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail way_mes[2] = {{397}, {396}}; /* derived name */

static ActMail way_onchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail way_offchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way_on_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way_off_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way_onchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way_offchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way2_on_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way2_off_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way2_onchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way2_offchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail statue_mes[2] = {{397}, {396}}; /* derived name */

static ActMail head_mes[2] = {{397}, {396}}; /* derived name */

static ActMail tree_mes[2] = {{397}, {396}}; /* derived name */

static ActMail kyomi_mes[2] = {{397}, {396}}; /* derived name */

static ActMail kyomi_onchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail kyomi_off_chk_mes[2] = {{397}, {396}}; /* derived name */

/* .sdata: the sluice, shutter and spike stream handles. */
SqEntry *suimon = 0;

SqEntry *shutter = 0;

SqEntry *toge = 0;

void actSt06aInit(void)
{
    if (gflagChk(95) == 0) {
        SetWayGroupActive(9, 0);
        SetWayGroupActive(10, 0);
    } else {
        SetWayGroupActive(9, 1);
        SetWayGroupActive(10, 1);
    }

    if (gflagChk(96) == 0) {
        SetWayGroupActive(12, 0);
    } else {
        SetWayGroupActive(12, 1);
    }
}

void actSt06aSuimon(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(95) == 0) {
        stage_SetAnimation(92, 0, 0);
        scpSearchGobj(1629)->active = 0;
        suimon_mes[0].func = actSt06aSuimonChk;
        act->mail = suimon_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(92, 0, -1);
        scpSearchGobj(1630)->active = 0;
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(1643));
    }
}

void actSt06aSuimonChk(GObj *volatile self)
{
    while ((scpGetRotObjectRotCount(1644) < -2.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    actCreateSubThread(actSt06aSuimonFlagOn, 21);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(66, &suimon, 1, 1, 1);

    while (suimon == 0) {
        _ACTWait(1);
    }

    actCreateSubThread(actSt06aSuimonEffect, 21);

    stage_SetAnimation(92, 1, 0);

    while (stage_CheckAnimationFinish(92) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait(1);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    scpSearchGobj(1629)->active = 1;
    scpSearchGobj(1630)->active = 0;

    SetWayGroupActive(9, 1);
    SetWayGroupActive(10, 1);
}

void actSt06aDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 200.0f) != 0 ||
        (girlGObj != 0 && scpTriggerBall(self, girlGObj, 400.0f) != 0)) {
        stage_SetAnimation(95, 0, 0);
        _ACTWait(60);
        door_down_mes[0].func = actSt06aDoorDownChk;
        act->mail = door_down_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(94, 0, 0);
        door_up_mes[0].func = actSt06aDoorUpChk;
        act->mail = door_up_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt06aDoorUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt06aDoorUpEffect, 21);

    scpWakeupItemWithBoundary(-1879.0f, -1047.0f, -620.0f, 100.0f);

    stage_SetAnimation(94, 1, 0);

    buf[0] = suimonSubPos.d[0];
    buf[1] = suimonSubPos.d[1];
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(94) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_upchk_mes[0].func = actSt06aDoorDownChk;
    sub->mail = door_upchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt06aDoorDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt06aDoorDownEffect, 21);

    scpWakeupItemWithBoundary(-1879.0f, -1047.0f, -620.0f, 100.0f);

    stage_SetAnimation(95, 1, 0);

    buf[0] = suimonSubPos.d[0];
    buf[1] = suimonSubPos.d[1];
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(95) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_downchk_mes[0].func = actSt06aDoorUpChk;
    sub->mail = door_downchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt06aShutterOpen(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(96);
    scpSleepEnemyAll();
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(81, &shutter, 1, 1, 1);

    while (shutter == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(93, 1, 0);

    while (stage_CheckAnimationFinish(93) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1620)->active = 0;
    scpSearchGobj(1621)->active = 1;
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    SetWayGroupActive(12, 1);
}

void actSt06aBoxChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1643), 300.0f) == 0 || gflagChk(95) != 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    gflagOn(98);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    _ACTWait(60);

    stage_SetAnimation(96, 1, 0);

    scpSearchGobj(1643)->active = 0;

    while (stage_CheckAnimationFinish(96) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 7);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt06aStatueChk(GObj *volatile self)
{
    int handle;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0xB000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0xB000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpSearchGobj(1678)->active = 0;
    stage_SetAnimation(231, -1, -2);
    stage_SetAnimation(98, 1, 0);

    handle = soundSeDefPlay(1330, 0, 0, 1);

    while (stage_CheckAnimationFrame(98, 70, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupItemWithBoundary(-3855.0f, -470.0f, 1392.0f, 200.0f);

    while (stage_CheckAnimationFinish(98) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(handle);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    _ACTWait(120);

    gflagOn(102);
}

void actSt06aHeadChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1639), 70.0f) == 0 || gflagChk(102) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(103);

    _ACTWait(120);

    scpAdpcmPlayRequestFunc(53, &toge, 1, 1, 1);

    while (toge == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(100, 1, 0);

    while (stage_CheckAnimationFrame(100, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(847, 0, 0, 1);

    while (stage_CheckAnimationFrame(100, 210, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1640)->active = 1;
    stage_SetAnimation(100, 0, -1);

    scpSearchGobj(1639)->active = 0;

    if (toge != 0) {
        scpAdpcmFadeCloseFunc(toge, 80);
    }

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt06aShutter(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(96) == 0) {
        stage_SetAnimation(93, 0, 0);
        scpSearchGobj(1621)->active = 0;
        shutter_mes[0].func = actSt06aShutterMain;
        act->mail = shutter_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(93, 0, -1);
        scpSearchGobj(1620)->active = 0;
    }
}

void actSt06aExit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    exit_mes[0].func = actSt06aExitChk;
    act->mail = exit_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt06aExitGirl(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    exit_girl_mes[0].func = actSt06aExitGirlChk;
    act->mail = exit_girl_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt06aBox(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(97) == 0 && gflagChk(98) == 0) {
        box_mes[0].func = actSt06aBoxChk;
        act->mail = box_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpSearchGobj(1643)->active = 0;
    }
}

void actSt06aBox2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(97) == 0 && gflagChk(98) == 0) {
        box2_mes[0].func = actSt06aBox2Chk;
        act->mail = box2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt06aBox3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(97) == 0 && gflagChk(98) == 0) {
        box3_mes[0].func = actSt06aBox3Chk;
        act->mail = box3_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt06aBoxEvent2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(99) == 0) {
        box_event2_in_mes[0].func = actSt06aBoxEvent2InChk;
        act->mail = box_event2_in_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        box_event2_out_mes[0].func = actSt06aBoxEvent2OutChk;
        act->mail = box_event2_out_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt06aWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    way_mes[0].func = actSt06aWayOnChk;
    act->mail = way_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt06aWallWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(100) == 0) {
        wall_way_on_mes[0].func = actSt06aWallWayOnChk;
        act->mail = wall_way_on_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        SetWayGroupActive(25, 1);
        SetWayGroupActive(26, 1);
        wall_way_off_mes[0].func = actSt06aWallWayOffChk;
        act->mail = wall_way_off_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt06aWallWay2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(101) == 0) {
        wall_way2_on_mes[0].func = actSt06aWallWay2OnChk;
        act->mail = wall_way2_on_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        SetWayGroupActive(25, 1);
        SetWayGroupActive(26, 1);
        wall_way2_off_mes[0].func = actSt06aWallWay2OffChk;
        act->mail = wall_way2_off_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt06aStatue(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(102) == 0) {
        stage_SetAnimation(98, 0, 0);
        statue_mes[0].func = actSt06aStatueChk;
        act->mail = statue_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(98, 0, -1);
        scpSearchGobj(1678)->active = 0;
        stage_SetAnimation(231, -1, -2);
    }
}

void actSt06aHead(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(103) == 0) {
        scpSearchGobj(1640)->active = 0;
        head_mes[0].func = actSt06aHeadChk;
        act->mail = head_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt06aTree(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(103) == 0) {
        scpSearchGobj(1639)->active = 0;
        tree_mes[0].func = actSt06aTreeChk;
        act->mail = tree_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpSearchGobj(1639)->active = 0;
    }
}

void actSt06aBallDelete(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    ball_delete_mes[0].func = actSt06aBallDeleteChk;
    act->mail = ball_delete_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt06aKyomi(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    kyomi_mes[0].func = actSt06aKyomiOffChk;
    act->mail = kyomi_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt06aSuimonEvent(int x)
{
    volatile int local = x;
}

void actSt06aSuimonEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long b3[2];
    long long v0a = doorUpEffectPos.d[0];
    long long v0b = doorUpEffect2Pos.d[0];
    long long v0c = doorUpEffect3Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorUpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            b3[0] = v0c;
            b3[1] = doorUpEffect3Pos.d[1];
            scpEffectStart((int *)b3, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt06aSuimonFlagOn(GObj *volatile self)
{
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 13.0);
    gflagOn(95);
}

void actSt06aDoorEvent(int x)
{
    volatile int local = x;
}

void actSt06aDoorUpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = jumpPos.d[0];
    long long v0b = jumpPos2.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = jumpPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = jumpPos2.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt06aDoorDownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = jumpPos2.d[0];
    long long v0b = jumpPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = jumpPos2.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = jumpPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt06aShutterMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = shutter_main_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt06aShutterSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    shutter_switch_mes[0].func = actSt06aShutterOpen;
    sub->mail = shutter_switch_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt06aExitChk(GObj *volatile self)
{
    while (gflagChk(95) != 0 || scpTriggerBall(self, boyGObj, 400.0f) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(3, boyGObj, 0, 16.0f, 16.0f);
}

static void actSt06aExitGirlChk(GObj *volatile self)
{
    long long buf[2];

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(95) != 0 || scpTriggerBall(self, girlGObj, 400.0f) == 0) {
        _ACTWait(1);
    }

    buf[0] = kyomiPos.d[0];
    buf[1] = kyomiPos.d[1];
    RequestStageChangeDirect(girlGObj, 22, buf, 180);
}

void actSt06aBox2Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1643), 200.0f) == 0 || gflagChk(95) == 0) {
        _ACTWait(1);
    }

    gflagOn(97);
    scpSearchGobj(1643)->active = 0;
}

void actSt06aBox3Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1643), 200.0f) == 0 || gflagChk(95) != 0) {
        _ACTWait(1);
    }
}

void actSt06aBallDeleteChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1639), 200.0f) == 0 || gflagChk(95) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1639)->active = 0;
}

void actSt06aBoxEvent2InChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(scpSearchGobj(1643), 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(99);

    box_event2_inchk_mes[0].func = actSt06aBoxEvent2OutChk;
    sub->mail = box_event2_inchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt06aBoxEvent2OutChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(scpSearchGobj(1643), 0x2000000) != 0) {
        _ACTWait(1);
    }

    gflagOff(99);

    box_event2_outchk_mes[0].func = actSt06aBoxEvent2InChk;
    sub->mail = box_event2_outchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

INCLUDE_ASM(actSt06aWayOnChk);

INCLUDE_ASM(actSt06aWayOffChk);

void actSt06aWallWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpIsRotObjectZPlusDirInclude(1645, 240, 300) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(25, 1);
    SetWayGroupActive(26, 1);
    gflagOn(100);

    wall_way_onchk_mes[0].func = actSt06aWallWayOffChk;
    sub->mail = wall_way_onchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

INCLUDE_ASM(actSt06aWallWayOffChk);

void actSt06aWallWay2OnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpIsRotObjectZPlusDirInclude(1645, 60, 120) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(25, 1);
    SetWayGroupActive(26, 1);
    gflagOn(101);

    wall_way2_onchk_mes[0].func = actSt06aWallWay2OffChk;
    sub->mail = wall_way2_onchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt06aWallWay2OffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpIsRotObjectZPlusDirInclude(1645, 60, 120) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(25, 0);
    SetWayGroupActive(26, 0);
    gflagOff(101);

    wall_way2_offchk_mes[0].func = actSt06aWallWay2OnChk;
    sub->mail = wall_way2_offchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt06aTreeChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 150.0f) == 0 ||
           (ForMotionViewer_GetCurrentMotion(boyGObj) != 46 &&
            ForMotionViewer_GetCurrentMotion(boyGObj) != 47 &&
            ForMotionViewer_GetCurrentMotion(boyGObj) != 48 &&
            ForMotionViewer_GetCurrentMotion(boyGObj) != 62)) {
        _ACTWait(1);
    }

    scpSearchGobj(1639)->active = 1;
    ReviveAllCarryableItems();
}

static void actSt06aKyomiOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x5000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1635)->active = 1;
    scpSearchGobj(1636)->active = 1;
    scpSearchGobj(1637)->active = 1;
    scpSearchGobj(1638)->active = 1;

    kyomi_onchk_mes[0].func = actSt06aKyomiOffChk;
    sub->mail = kyomi_onchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

static void actSt06aKyomiOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x5000000) != 0 &&
           scpTriggerFloorAttr(girlGObj, 0x5000000) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1635)->active = 0;
    scpSearchGobj(1636)->active = 0;
    scpSearchGobj(1637)->active = 0;
    scpSearchGobj(1638)->active = 0;

    kyomi_off_chk_mes[0].func = actSt06aKyomiOnChk;
    sub->mail = kyomi_off_chk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
