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

/* The functions stand in the order of the stage's source (aug6's TRFILE
   numbers them so). The ones defined inline are output at the end of the
   file, in the order of the declarations below, which gives this build's
   .text order; the others are output where they stand. The mail tables are
   file-scope statics ahead of the functions that post them, except
   actSt06aWayOnChk's, a static local of its poster as in the USA source
   (gcc's local name.N symbol); .data keeps the source order. */

inline void actSt06aSuimon(GObj *volatile self);
inline void actSt06aDoor(GObj *volatile self);
inline void actSt06aExit(GObj *volatile self);
inline void actSt06aBox(GObj *volatile self);
inline void actSt06aBox2(GObj *volatile self);
inline void actSt06aBox3(GObj *volatile self);
inline void actSt06aBoxEvent2(GObj *volatile self);
inline void actSt06aWay(GObj *volatile self);
inline void actSt06aWallWay(GObj *volatile self);
inline void actSt06aWallWay2(GObj *volatile self);
inline void actSt06aStatue(GObj *volatile self);
inline void actSt06aHead(GObj *volatile self);
inline void actSt06aTree(GObj *volatile self);
inline void actSt06aSuimonEvent(int x);
inline void actSt06aSuimonEffect(GObj *volatile self);
inline void actSt06aDoorEvent(int x);
inline void actSt06aDoorUpEffect(GObj *volatile self);
inline void actSt06aDoorDownEffect(GObj *volatile self);
inline void actSt06aShutterMain(GObj *volatile self);
inline void actSt06aShutterSwitch(GObj *volatile self);
inline void actSt06aExitChk(GObj *volatile self);
inline void actSt06aBox2Chk(GObj *volatile self);
inline void actSt06aBox3Chk(GObj *volatile self);
inline void actSt06aBoxEvent2InChk(GObj *volatile self);
inline void actSt06aBoxEvent2OutChk(GObj *volatile self);
inline void actSt06aWayOnChk(GObj *volatile self);
inline void actSt06aWayOffChk(GObj *volatile self);
inline void actSt06aWallWayOnChk(GObj *volatile self);
inline void actSt06aWallWayOffChk(GObj *volatile self);
inline void actSt06aWallWay2OnChk(GObj *volatile self);
inline void actSt06aWallWay2OffChk(GObj *volatile self);
inline void actSt06aTreeChk(GObj *volatile self);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copies read. */

static const ConstVec doorUpEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec suimonSubPos = {{-1869.0f, -1147.0f, -664.0f, 0.0f}}; /* derived name */

static const ConstVec jumpPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec jumpPos2 = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

/* No .sdata: this build's room plays its sluice, shutter and door streams
   with no handle. */

void actSt06aInit(void)
{
    if (gflagChk(92) == 0) {
        SetWayGroupActive(9, 0);
        SetWayGroupActive(10, 0);
    } else {
        SetWayGroupActive(9, 1);
        SetWayGroupActive(10, 1);
    }

    if (gflagChk(93) == 0) {
        SetWayGroupActive(12, 0);
    } else {
        SetWayGroupActive(12, 1);
    }
}

static ActMail suimon_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aSuimonEvent(int x)
{
    volatile int local = x;
}

inline void actSt06aSuimon(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(92) == 0) {
        stage_SetAnimation(82, 0, 0);
        scpSearchGobj(1545)->active = 0;
        suimon_mes[0].func = actSt06aSuimonChk;
        act->mail = suimon_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(82, 0, -1);
        scpSearchGobj(1546)->active = 0;
    }
}

void actSt06aSuimonChk(GObj *volatile self)
{
    while ((scpGetRotObjectRotCount(1556) < -2.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    gflagOn(92);

    scpBoyControlReadDisable = 1;

    scpAdpcmPlayRequestFunc(61, 0, 1, 1, 1);

    _ACTWait(30);

    actCreateSubThread(actSt06aSuimonEffect, 21);

    stage_SetAnimation(82, 1, 0);

    while (stage_CheckAnimationFinish(82) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    scpSearchGobj(1545)->active = 1;
    scpSearchGobj(1546)->active = 0;

    SetWayGroupActive(9, 1);
    SetWayGroupActive(10, 1);
}

inline void actSt06aSuimonEffect(GObj *volatile self)
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

static ActMail door_down_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door_up_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door_upchk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door_downchk_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aDoorEvent(int x)
{
    volatile int local = x;
}

inline void actSt06aDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 200.0f) != 0) {
        stage_SetAnimation(85, 0, 0);
        _ACTWait(60);
        door_down_mes[0].func = actSt06aDoorDownChk;
        act->mail = door_down_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(84, 0, 0);
        door_up_mes[0].func = actSt06aDoorUpChk;
        act->mail = door_up_mes;
        ACTSendMailCorrect(self, 377);
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

    stage_SetAnimation(84, 1, 0);

    buf[0] = suimonSubPos.d[0];
    buf[1] = suimonSubPos.d[1];
    soundSeDefPlay(1170, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1171, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1172, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(84) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_upchk_mes[0].func = actSt06aDoorDownChk;
    sub->mail = door_upchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt06aDoorUpEffect(GObj *volatile self)
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

    stage_SetAnimation(85, 1, 0);

    buf[0] = suimonSubPos.d[0];
    buf[1] = suimonSubPos.d[1];
    soundSeDefPlay(1170, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1171, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1172, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(85) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_downchk_mes[0].func = actSt06aDoorUpChk;
    sub->mail = door_downchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt06aDoorDownEffect(GObj *volatile self)
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

static ActMail shutter_main_mes[2] = {{356, actSt06aShutterSwitch}, {376}}; /* derived name */

static ActMail shutter_mes[2] = {{377}, {376}}; /* derived name */

static ActMail shutter_switch_mes[2] = {{377}, {376}}; /* derived name */

void actSt06aShutter(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(93) == 0) {
        stage_SetAnimation(83, 0, 0);
        scpSearchGobj(1537)->active = 0;
        shutter_mes[0].func = actSt06aShutterMain;
        act->mail = shutter_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(351, -1, -2);
        stage_SetAnimation(352, 1, 0);
        stage_SetLoopFlag(352, 1);
        stage_SetAnimation(83, 0, -1);
        scpSearchGobj(1536)->active = 0;
    }
}

inline void actSt06aShutterMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = shutter_main_mes;

    while (1) {
        _ACTWait(1);
    }
}

inline void actSt06aShutterSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    shutter_switch_mes[0].func = actSt06aShutterOpen;
    sub->mail = shutter_switch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt06aShutterOpen(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(93);
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(76, 0, 1, 1, 1);

    stage_SetAnimation(351, -1, -2);
    stage_SetAnimation(352, 1, 0);
    stage_SetLoopFlag(352, 1);

    stage_SetAnimation(83, 1, 0);

    while (stage_CheckAnimationFinish(83) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1536)->active = 0;
    scpSearchGobj(1537)->active = 1;
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    SetWayGroupActive(12, 1);
}

static ActMail exit_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aExit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    exit_mes[0].func = actSt06aExitChk;
    act->mail = exit_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt06aExitChk(GObj *volatile self)
{
    while (gflagChk(92) != 0 || scpTriggerBall(self, boyGObj, 200.0f) == 0) {
        _ACTWait(1);
    }
    RequestStageChange(3, boyGObj, 0, 16.0f, 16.0f);
}

static ActMail box_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aBox(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(94) == 0 && gflagChk(95) == 0) {
        box_mes[0].func = actSt06aBoxChk;
        act->mail = box_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(1555)->active = 0;
    }
}

void actSt06aBoxChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1555), 300.0f) == 0 || gflagChk(92) != 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    gflagOn(95);
    scpBoyControlReadDisable = 1;
    _ACTWait(1);

    stage_SetAnimation(86, 1, 0);

    while (stage_CheckAnimationFinish(86) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 7);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

static ActMail box2_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aBox2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(94) == 0 && gflagChk(95) == 0) {
        box2_mes[0].func = actSt06aBox2Chk;
        act->mail = box2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt06aBox2Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1555), 200.0f) == 0 || gflagChk(92) == 0) {
        _ACTWait(1);
    }
    gflagOn(94);
    scpSearchGobj(1555)->active = 0;
}

static ActMail box3_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aBox3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(94) == 0 && gflagChk(95) == 0) {
        box3_mes[0].func = actSt06aBox3Chk;
        act->mail = box3_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt06aBox3Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1555), 200.0f) == 0 || gflagChk(92) != 0) {
        _ACTWait(1);
    }
    gflagOn(95);
    scpSearchGobj(1555)->active = 0;
}

static ActMail box_event2_in_mes[2] = {{377}, {376}}; /* derived name */

static ActMail box_event2_out_mes[2] = {{377}, {376}}; /* derived name */

static ActMail box_event2_inchk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail box_event2_outchk_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aBoxEvent2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(96) == 0) {
        box_event2_in_mes[0].func = actSt06aBoxEvent2InChk;
        act->mail = box_event2_in_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        box_event2_out_mes[0].func = actSt06aBoxEvent2OutChk;
        act->mail = box_event2_out_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt06aBoxEvent2InChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(scpSearchGobj(1555), 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(96);

    box_event2_inchk_mes[0].func = actSt06aBoxEvent2OutChk;
    sub->mail = box_event2_inchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt06aBoxEvent2OutChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(scpSearchGobj(1555), 0x2000000) != 0) {
        _ACTWait(1);
    }

    gflagOff(96);

    box_event2_outchk_mes[0].func = actSt06aBoxEvent2InChk;
    sub->mail = box_event2_outchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail way_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    way_mes[0].func = actSt06aWayOnChk;
    act->mail = way_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt06aWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail way_onchk_mes[2] = {{377}, {376}}; /* derived name */

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(19, 1);
    SetWayGroupActive(23, 1);
    SetWayGroupActive(24, 1);

    way_onchk_mes[0].func = actSt06aWayOffChk;
    sub->mail = way_onchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail way_off_chk_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(19, 0);
    SetWayGroupActive(23, 0);
    SetWayGroupActive(24, 0);

    way_off_chk_mes[0].func = actSt06aWayOnChk;
    sub->mail = way_off_chk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail wall_way_on_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wall_way_off_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wall_way_onchk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wall_way_offchk_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aWallWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(97) == 0) {
        wall_way_on_mes[0].func = actSt06aWallWayOnChk;
        act->mail = wall_way_on_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        SetWayGroupActive(25, 1);
        SetWayGroupActive(26, 1);
        wall_way_off_mes[0].func = actSt06aWallWayOffChk;
        act->mail = wall_way_off_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt06aWallWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpIsRotObjectZPlusDirInclude(1557, 240, 300) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(25, 1);
    SetWayGroupActive(26, 1);
    gflagOn(97);

    wall_way_onchk_mes[0].func = actSt06aWallWayOffChk;
    sub->mail = wall_way_onchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt06aWallWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpIsRotObjectZPlusDirInclude(1557, 240, 300) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(25, 0);
    SetWayGroupActive(26, 0);
    gflagOff(97);

    wall_way_offchk_mes[0].func = actSt06aWallWayOnChk;
    sub->mail = wall_way_offchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail wall_way2_on_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wall_way2_off_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wall_way2_onchk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wall_way2_offchk_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aWallWay2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(98) == 0) {
        wall_way2_on_mes[0].func = actSt06aWallWay2OnChk;
        act->mail = wall_way2_on_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        SetWayGroupActive(25, 1);
        SetWayGroupActive(26, 1);
        wall_way2_off_mes[0].func = actSt06aWallWay2OffChk;
        act->mail = wall_way2_off_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt06aWallWay2OnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpIsRotObjectZPlusDirInclude(1557, 60, 120) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(25, 1);
    SetWayGroupActive(26, 1);
    gflagOn(98);

    wall_way2_onchk_mes[0].func = actSt06aWallWay2OffChk;
    sub->mail = wall_way2_onchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt06aWallWay2OffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpIsRotObjectZPlusDirInclude(1557, 60, 120) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(25, 0);
    SetWayGroupActive(26, 0);
    gflagOff(98);

    wall_way2_offchk_mes[0].func = actSt06aWallWay2OnChk;
    sub->mail = wall_way2_offchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail statue_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aStatue(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(99) == 0) {
        stage_SetAnimation(88, 0, 0);
        statue_mes[0].func = actSt06aStatueChk;
        act->mail = statue_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(88, 0, -1);
        scpSearchGobj(1587)->active = 0;
        stage_SetAnimation(205, -1, -2);
    }
}

void actSt06aStatueChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0xB000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0xB000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpSearchGobj(1587)->active = 0;
    stage_SetAnimation(205, -1, -2);
    gflagOn(99);

    stage_SetAnimation(88, 1, 0);

    while (stage_CheckAnimationFinish(88) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

static ActMail head_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aHead(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(100) == 0) {
        scpSearchGobj(1552)->active = 0;
        head_mes[0].func = actSt06aHeadChk;
        act->mail = head_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(1552)->active = 1;
        stage_SetAnimation(89, 0, -1);
        stage_SetAnimation(90, 0, -1);
    }
}

void actSt06aHeadChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1551), 50.0f) == 0 || gflagChk(99) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(100);

    _ACTWait(120);

    stage_SetAnimation(90, 1, 0);

    while (stage_CheckAnimationFrame(90, 210, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1552)->active = 1;
    stage_SetAnimation(90, 0, -1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

static ActMail tree_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt06aTree(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(101) == 0) {
        scpSearchGobj(1551)->active = 0;
        tree_mes[0].func = actSt06aTreeChk;
        act->mail = tree_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt06aTreeChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0 ||
           (ForMotionViewer_GetCurrentMotion(boyGObj) != 48 &&
            ForMotionViewer_GetCurrentMotion(boyGObj) != 49 &&
            ForMotionViewer_GetCurrentMotion(boyGObj) != 50)) {
        _ACTWait(1);
    }

    scpSearchGobj(1551)->active = 1;
    ReviveAllCarryableItems();
}
