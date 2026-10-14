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

static void actSt06aBoxSub(GObj *volatile self);
static void actSt06aExitGirlChk(GObj *volatile self);
static void actSt06aJumpMain(GObj *volatile self);
static void actSt06aJumpSub(GObj *volatile self);
static void actSt06aJumpSwitch(GObj *volatile self);
static void actSt06aKyomiOffChk(GObj *volatile self);
static void actSt06aPistonRideOnChk(GObj *volatile self);
static void actSt06aShutterOpenSub(GObj *volatile self);
static void actSt06aSuimonSub(GObj *volatile self);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copies read. */

static const ConstVec doorUpEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec suimonSubPos = {{-1869.0f, -1147.0f, -664.0f, 0.0f}}; /* derived name */

static const ConstVec jumpPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec jumpPos2 = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec kyomiPos = {{-985.0f, -177.0f, -696.0f, 0.0f}}; /* derived name */

static const ConstVec farPos = {{0.0f, 0.0f, -1000000.0f, 1.0f}}; /* derived name */

/* st06a.c's `inline` functions, in the order of their definitions'
   out-of-line copies at the end of the object (first-declaration order). */
static inline void actSt06aPistonRideOffChk(GObj *volatile self);
static inline void actSt06aPistonFlagOffChk(GObj *volatile self);
static inline void actSt06aSoundChk(GObj *volatile self);
static inline void actSt06aSound2Chk(GObj *volatile self);

static ActMail suimon_mes[2] = {{430}, {429}}; /* derived name */

static float suimon_sound_pos[4] = {810.0f, -346.0f, 381.0f, 0.0f}; /* derived name */

static ActMail door_down_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door_up_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door_upchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door_dnchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail shutter_main_mes[2] = {{406, actSt06aShutterSwitch}, {429}}; /* derived name */

static ActMail shutter_mes[2] = {{430}, {429}}; /* derived name */

static ActMail shutter_switch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail exit_mes[2] = {{430}, {429}}; /* derived name */

static ActMail exit_girl_mes[2] = {{430}, {429}}; /* derived name */

static ActMail box_mes[2] = {{430}, {429}}; /* derived name */

static ActMail box2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail box3_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ball_delete_mes[2] = {{430}, {429}}; /* derived name */

static ActMail box_event2_in_mes[2] = {{430}, {429}}; /* derived name */

static ActMail box_event2_out_mes[2] = {{430}, {429}}; /* derived name */

static ActMail box_event2_inchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail box_event2_out_chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_onchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_offchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wall_way_on_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wall_way_off_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wall_way_onchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wall_way_offchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wall_way2_on_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wall_way2_off_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wall_way2_onchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wall_way2_offchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail statue_mes[2] = {{430}, {429}}; /* derived name */

static ActMail head_mes[2] = {{430}, {429}}; /* derived name */

static ActMail tree_mes[2] = {{430}, {429}}; /* derived name */

static ActMail kyomi_mes[2] = {{430}, {429}}; /* derived name */

static ActMail kyomi_onchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail kyomi_off_chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail jump_main_mes[2] = {{407, actSt06aJumpSwitch}, {429}}; /* derived name */

static ActMail jump_mes[2] = {{430}, {429}}; /* derived name */

static ActMail jump_switch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail piston_mes[2] = {{430}, {429}}; /* derived name */

static ActMail piston_ride_onchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail piston_ride_offchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail piston_flag_mes[2] = {{430}, {429}}; /* derived name */

static float piston_flag_sound_pos[4] = {87.0f, -772.0f, 1135.0f, 0.0f}; /* derived name */

static ActMail piston_flag_onchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail piston_flag_offchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sound_mes[2] = {{430}, {429}}; /* derived name */

static float sound_chk_pos[4] = {810.0f, -346.0f, 381.0f, 0.0f}; /* derived name */

static ActMail sound2_mes[2] = {{430}, {429}}; /* derived name */

static float sound2_chk_pos[4] = {87.0f, -772.0f, 1135.0f, 0.0f}; /* derived name */

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for, and its complement, true when the player skipped the demo
   with START. */
static int demoEnd;

static int demoSkipped; /* derived name */

void actSt06aInit(void)
{
    if (gflagChk(106) == 0) {
        SetWayGroupActive(9, 0);
        SetWayGroupActive(10, 0);
    } else {
        SetWayGroupActive(9, 1);
        SetWayGroupActive(10, 1);
        FinishHint(19);
    }

    if (gflagChk(107) == 0) {
        SetWayGroupActive(12, 0);
    } else {
        SetWayGroupActive(12, 1);
    }
}

INCLUDE_ASM(actSt06aSuimon);

/* .sdata: the sluice, shutter and spike stream handles. */
SqEntry *suimon = 0;

SqEntry *shutter = 0;

SqEntry *toge = 0;

INCLUDE_ASM(actSt06aSuimonChk);

INCLUDE_ASM(actSt06aDoor);

INCLUDE_ASM(actSt06aDoorUpChk);

INCLUDE_ASM(actSt06aDoorDownChk);

void actSt06aShutterOpen(GObj *volatile self);

INCLUDE_ASM(actSt06aShutterOpen);

void actSt06aBoxChk(GObj *volatile self);

INCLUDE_ASM(actSt06aBoxChk);

INCLUDE_ASM(actSt06aStatueChk);

void actSt06aHeadChk(GObj *volatile self);

INCLUDE_ASM(actSt06aHeadChk);

static void actSt06aJumpMove(GObj *volatile self);

INCLUDE_ASM(actSt06aJumpMove);

static void actSt06aPistonFlagOnChk(GObj *volatile self);

INCLUDE_ASM(actSt06aPistonFlagOnChk);

INCLUDE_ASM(actSt06aShutter);

void actSt06aExit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    exit_mes[0].func = actSt06aExitChk;
    act->mail = exit_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aExitGirl(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    exit_girl_mes[0].func = actSt06aExitGirlChk;
    act->mail = exit_girl_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aBox(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(108) == 0 && gflagChk(109) == 0) {
        box_mes[0].func = actSt06aBoxChk;
        act->mail = box_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(1773)->active = 0;
    }
}

void actSt06aBox2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(108) == 0 && gflagChk(109) == 0) {
        box2_mes[0].func = actSt06aBox2Chk;
        act->mail = box2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt06aBox3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(108) == 0 && gflagChk(109) == 0) {
        box3_mes[0].func = actSt06aBox3Chk;
        act->mail = box3_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt06aBoxEvent2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(110) == 0) {
        box_event2_in_mes[0].func = actSt06aBoxEvent2InChk;
        act->mail = box_event2_in_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        box_event2_out_mes[0].func = actSt06aBoxEvent2OutChk;
        act->mail = box_event2_out_mes;
        ACTSendMailCorrect(self, 430);
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
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aWallWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(111) == 0) {
        wall_way_on_mes[0].func = actSt06aWallWayOnChk;
        act->mail = wall_way_on_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(23, 1);
        SetWayGroupActive(24, 1);
        wall_way_off_mes[0].func = actSt06aWallWayOffChk;
        act->mail = wall_way_off_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt06aWallWay2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(112) == 0) {
        wall_way2_on_mes[0].func = actSt06aWallWay2OnChk;
        act->mail = wall_way2_on_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(23, 1);
        SetWayGroupActive(24, 1);
        wall_way2_off_mes[0].func = actSt06aWallWay2OffChk;
        act->mail = wall_way2_off_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt06aStatue);

void actSt06aHead(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(114) == 0) {
        scpSearchGobj(1771)->active = 0;
        scpSearchGobj(1772)->active = 0;
        head_mes[0].func = actSt06aHeadChk;
        act->mail = head_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        if (gFlagGameClear == 0) {
            scpSearchGobj(1772)->active = 0;
        }
        if (gFlagGameClear != 0) {
            scpSearchGobj(1771)->active = 0;
        }
    }
}

void actSt06aTree(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(114) == 0) {
        scpSearchGobj(1770)->active = 0;
        tree_mes[0].func = actSt06aTreeChk;
        act->mail = tree_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(1770)->active = 0;
    }
}

void actSt06aBallDelete(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    ball_delete_mes[0].func = actSt06aBallDeleteChk;
    act->mail = ball_delete_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aKyomi(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    kyomi_mes[0].func = actSt06aKyomiOffChk;
    act->mail = kyomi_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt06aJump);

void actSt06aPiston(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    piston_mes[0].func = actSt06aPistonRideOnChk;
    act->mail = piston_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aPistonFlag(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    piston_flag_mes[0].func = actSt06aPistonFlagOnChk;
    act->mail = piston_flag_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aSound(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(106) == 0) {
        sound_mes[0].func = actSt06aSoundChk;
        act->mail = sound_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt06aSound2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(106) == 0) {
        sound2_mes[0].func = actSt06aSound2Chk;
        act->mail = sound2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
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
    _ACTWait(0);
}

void actSt06aSuimonFlagOn(GObj *volatile self)
{
    int i = (60 - systemStatus[0] * 10) / systemStatus[1] * 7.0;

    riverFadeSpeed = 0.005f;

    while (i-- > 0) {
        if (demoSkipped != 0) {
            riverFadeSpeed = 1000.0f;
            break;
        }
        _ACTWait(1);
    }
    gflagOn(106);
}

INCLUDE_ASM(actSt06aSuimonSub);

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
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt06aShutterOpenSub);

void actSt06aExitChk(GObj *volatile self)
{
    while (gflagChk(106) != 0 || scpTriggerBall(self, boyGObj, 400.0f) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 0;
    RequestStageChange(3, boyGObj, 0, 16.0f, 16.0f);
}

static void actSt06aExitGirlChk(GObj *volatile self)
{
    long long buf1[2];
    long long buf2[2];

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(106) != 0 || scpTriggerBall(self, girlGObj, 400.0f) == 0) {
        _ACTWait(1);
    }

    buf1[0] = kyomiPos.d[0];
    buf1[1] = kyomiPos.d[1];
    RequestStageChangeDirect(girlGObj, 22, buf1, 180);

    buf2[0] = farPos.d[0];
    buf2[1] = farPos.d[1];
    SetDirectRootPosition(girlGObj, buf2);

    ScpCallCameraSetTarget(-800.0f, -500.0f, 2200.0f);
}

INCLUDE_ASM(actSt06aBoxSub);

void actSt06aBox2Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1773), 200.0f) == 0 || gflagChk(106) == 0) {
        _ACTWait(1);
    }

    gflagOn(108);
    scpSearchGobj(1773)->active = 0;
}

void actSt06aBox3Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1773), 200.0f) == 0 || gflagChk(106) != 0) {
        _ACTWait(1);
    }
}

void actSt06aBallDeleteChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(1770), 200.0f) == 0 || gflagChk(106) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1770)->active = 0;
}

void actSt06aBoxEvent2InChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(scpSearchGobj(1773), 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(110);

    box_event2_inchk_mes[0].func = actSt06aBoxEvent2OutChk;
    sub->mail = box_event2_inchk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aBoxEvent2OutChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(scpSearchGobj(1773), 0x2000000) != 0) {
        _ACTWait(1);
    }

    gflagOff(110);

    box_event2_out_chk_mes[0].func = actSt06aBoxEvent2InChk;
    sub->mail = box_event2_out_chk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(22, 1);

    way_onchk_mes[0].func = actSt06aWayOffChk;
    sub->mail = way_onchk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(22, 0);

    way_offchk_mes[0].func = actSt06aWayOnChk;
    sub->mail = way_offchk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aWallWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpIsRotObjectZPlusDirInclude(1775, 240, 300) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(23, 1);
    SetWayGroupActive(24, 1);
    gflagOn(111);

    wall_way_onchk_mes[0].func = actSt06aWallWayOffChk;
    sub->mail = wall_way_onchk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aWallWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpIsRotObjectZPlusDirInclude(1775, 240, 300) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(23, 0);
    SetWayGroupActive(24, 0);
    gflagOff(111);

    wall_way_offchk_mes[0].func = actSt06aWallWayOnChk;
    sub->mail = wall_way_offchk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aWallWay2OnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpIsRotObjectZPlusDirInclude(1775, 60, 120) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(23, 1);
    SetWayGroupActive(24, 1);
    gflagOn(112);

    wall_way2_onchk_mes[0].func = actSt06aWallWay2OffChk;
    sub->mail = wall_way2_onchk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aWallWay2OffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpIsRotObjectZPlusDirInclude(1775, 60, 120) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(23, 0);
    SetWayGroupActive(24, 0);
    gflagOff(112);

    wall_way2_offchk_mes[0].func = actSt06aWallWay2OnChk;
    sub->mail = wall_way2_offchk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt06aTreeChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 150.0f) == 0 ||
           (ForMotionViewer_GetCurrentMotion(boyGObj) != 47 &&
            ForMotionViewer_GetCurrentMotion(boyGObj) != 48 &&
            ForMotionViewer_GetCurrentMotion(boyGObj) != 49 &&
            ForMotionViewer_GetCurrentMotion(boyGObj) != 62)) {
        _ACTWait(1);
    }

    scpSearchGobj(1770)->active = 1;
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

    scpSearchGobj(1766)->active = 1;
    scpSearchGobj(1767)->active = 1;
    scpSearchGobj(1768)->active = 1;
    scpSearchGobj(1769)->active = 1;

    kyomi_onchk_mes[0].func = actSt06aKyomiOffChk;
    sub->mail = kyomi_onchk_mes;
    ACTSendMailCorrect(self, 430);
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

    scpSearchGobj(1766)->active = 0;
    scpSearchGobj(1767)->active = 0;
    scpSearchGobj(1768)->active = 0;
    scpSearchGobj(1769)->active = 0;

    kyomi_off_chk_mes[0].func = actSt06aKyomiOnChk;
    sub->mail = kyomi_off_chk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt06aJumpMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = jump_main_mes;

    while (1) {
        _ACTWait(1);
    }
}

static void actSt06aJumpSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    jump_switch_mes[0].func = actSt06aJumpMove;
    sub->mail = jump_switch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt06aJumpSub);

static void actSt06aPistonRideOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (gflagChk(116) == 0 || scpTriggerFloorAttr(boyGObj, 0x6000000) == 0) {
        _ACTWait(1);
    }

    piston_ride_onchk_mes[0].func = actSt06aPistonRideOffChk;
    sub->mail = piston_ride_onchk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static inline void actSt06aSoundChk(GObj *volatile self)
{
    int handle = soundSeDefPlay(1358, 0, sound_chk_pos, 1);

    while (gflagChk(106) == 0) {
        _ACTWait(1);
    }

    soundSeDefStop(handle);
}

static inline void actSt06aSound2Chk(GObj *volatile self)
{
    int handle;

    while (gflagChk(116) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("PISTON_LOOP_SE!!!!!!!!!!!!\n");

    handle = soundSeDefPlay(1360, 0, sound2_chk_pos, 1);

    while (gflagChk(106) == 0) {
        _ACTWait(1);
    }

    soundSeDefStop(handle);
}

INCLUDE_ASM(actSt06aPistonRideOffChk);

INCLUDE_ASM(actSt06aPistonFlagOffChk);
