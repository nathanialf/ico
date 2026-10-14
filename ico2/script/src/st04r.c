#include "st04r.h"
#include "st04l.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "gobj_process.h"
#include "obj_manager.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act-game.h"
#include "act.h"
#include "commonact.h"
#include "girl_act.h"
#include "way_llf.h"
#include "camera-root.h"
#include "fightSound.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "item.h"
#include <libvu0.h>
#include "typedef.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt04rBrg1Sub(GObj *volatile self);
static void openGate(struct GObj *self);

static ActMail c1_ball_main_mes[2] = {{406, actSt04rC1BallSwitch}, {429}}; /* derived name */

static ActMail c1_ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c1_ball_switch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c2_ball_main_mes[2] = {{406, actSt04rC2BallSwitch}, {429}}; /* derived name */

static ActMail c2_ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c2_ball_switch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c3_ball_main_mes[2] = {{407, actSt04rC3BallSwitch}, {429}}; /* derived name */

static ActMail c3_ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c3_ball_switch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest01_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest03_mes[2] = {{430}, {429}}; /* derived name */

static ActMail solar_beam_mes[2] = {{430}, {429}}; /* derived name */

static ActMail solar_stage_change_mes[2] = {{430}, {429}}; /* derived name */

static ActMail stair_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1_chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope3_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope4_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2_chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1_way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2_way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou01_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou03_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou04_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou05_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou06_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou07_mes[2] = {{430}, {429}}; /* derived name */

static ActMail barricade_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_chara_chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch1_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch1_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch3_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch3_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_1xl_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_2xl_mes[2] = {{430}, {429}}; /* derived name */

/* .sbss: the pad actuator handle openGate holds, the demo's own end flag, the
   gate animation and voice clip openGate plays, and the flag the stair
   subthread raises once it is past its setup. */
static int padAct; /* derived name */

static int demoEnd;

static int gateAnim; /* derived name */

static int gateAdpcm; /* derived name */

static int subStarted; /* derived name */

/* The look-at point both characters face in the crest cutscene. */
static const ConstVec crestFacePos = {{0.0f, 0.0f, -5000.0f, 1.0f}}; /* derived name */

/* .sdata: the room's stream handles and shakes (the three balls and crest2_4r
   unused). */
SqEntry *solar4r = 0;

int ball1_4r = 0;

int ball2_4r = 0;

int ball3_4r = 0;

SqEntry *crest1_4r = 0;

int crest2_4r = 0;

SqEntry *crest3_4r = 0;

SqEntry *stair5d = 0;

SqEntry *sekizo5c = 0;

unsigned char st05d_hasi = 0;

int st04r_yure = 0;

unsigned char st04r_yure_vol = 0;

int sekizo_4r = 0;

void actSt05eEnd(void)
{
    if (solar4r != 0) {
        if (gflagChk(234) == 0) {
            scpAdpcmCloseFunc(&solar4r);
        }
    }
}

INCLUDE_ASM(actSt05cInit);

INCLUDE_ASM(actSt05dInit);

INCLUDE_ASM(actSt05eInit);

INCLUDE_ASM(actSt04rCrest02);

static void openGateSub(GObj *volatile self)
{
    stage_SetAnimation(gateAnim, 1, 0);

    while (stage_CheckAnimationFrame(gateAnim, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    padAct = iosPadActRequest(boyPad, 10);
    st05d_hasi = 128;
    iosPadActVolumeSet(padAct, 128);

    while (stage_CheckAnimationFrame(gateAnim, 190, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(padAct);

    while (stage_CheckAnimationFinish(gateAnim) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

INCLUDE_ASM(openGate);

INCLUDE_ASM(actSt04rCrest2Main);

INCLUDE_ASM(actSt04rCrest3Main);

INCLUDE_ASM(actSt04rSolarBeam);

INCLUDE_ASM(actSt04rSolarBeamChk);

INCLUDE_ASM(actSt04rStairSub);

INCLUDE_ASM(actSt04rStairChk);

INCLUDE_ASM(actSt04rSekizoChk);

INCLUDE_ASM(actSt04rRope1Chk);

INCLUDE_ASM(actSt04rRope2Chk);

INCLUDE_ASM(actSt04rBrgCommon);

INCLUDE_ASM(actSt04rRope3Chk);

INCLUDE_ASM(actSt04rRope4Chk);

INCLUDE_ASM(actSt04rMonyou01Chk);

INCLUDE_ASM(actSt04rMonyou02Chk);

INCLUDE_ASM(actSt04rMonyou03Chk);

INCLUDE_ASM(actSt04rMonyou04Chk);

INCLUDE_ASM(actSt04rMonyou05Chk);

INCLUDE_ASM(actSt04rMonyou06Chk);

INCLUDE_ASM(actSt04rMonyou07Chk);

INCLUDE_ASM(actSt04rBarricadeChk);

void actSt04rGondolaChk(GObj *volatile self);

INCLUDE_ASM(actSt04rGondolaChk);

void actSt04rSolarStageChange(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(234) == 0) {
        solar_stage_change_mes[0].func = actSt04rSolarStageChangeChk;
        act->mail = solar_stage_change_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt04rCrest01);

INCLUDE_ASM(actSt04rCrest03);

INCLUDE_ASM(actSt04rC1Ball);

INCLUDE_ASM(actSt04rC2Ball);

INCLUDE_ASM(actSt04rC3Ball);

INCLUDE_ASM(actSt04rStair);

void actSt04rBrg1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(259) == 0) {
        brg1_mes[0].func = actSt04rBrg1Chk;
        act->mail = brg1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04rBrg2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(260) == 0) {
        brg2_mes[0].func = actSt04rBrg2Chk;
        act->mail = brg2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04rBrg1Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(259) == 0) {
        brg1_way_mes[0].func = actSt04rBrg1WayChk;
        act->mail = brg1_way_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04rBrg2Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(260) == 0) {
        brg2_way_mes[0].func = actSt04rBrg2WayChk;
        act->mail = brg2_way_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt04rRope1);

INCLUDE_ASM(actSt04rRope2);

INCLUDE_ASM(actSt04rRope3);

INCLUDE_ASM(actSt04rRope4);

INCLUDE_ASM(actSt04rSekizo);

INCLUDE_ASM(actSt04rBarricade);

INCLUDE_ASM(actSt04rGondola);

INCLUDE_ASM(actSt04rCrest01XL);

INCLUDE_ASM(actSt04rCrest02XL);

INCLUDE_ASM(actSt04rCrest03XL);

INCLUDE_ASM(actSt04rC2BallXL);

INCLUDE_ASM(actSt04rC3BallXL);

INCLUDE_ASM(actSt04rTorch1_1);

INCLUDE_ASM(actSt04rTorch1_2);

void actSt04rTorch2_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(268) != 0 || gflagChk(270) != 0) {
        scpTorchLightOn(1487);
    } else {
        torch2_1_mes[0].func = actSt04rTorch2_1Chk;
        act->mail = torch2_1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04rTorch2_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(269) != 0 || gflagChk(271) != 0) {
        scpTorchLightOn(1488);
    } else {
        torch2_2_mes[0].func = actSt04rTorch2_2Chk;
        act->mail = torch2_2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04rTorch3_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(272) == 0) {
        torch3_1_mes[0].func = actSt04rTorch3_1Chk;
        act->mail = torch3_1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1489);
    }
}

void actSt04rTorch3_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(273) == 0) {
        torch3_2_mes[0].func = actSt04rTorch3_2Chk;
        act->mail = torch3_2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1490);
    }
}

INCLUDE_ASM(actSt04rTorch2_1XL);

INCLUDE_ASM(actSt04rTorch2_2XL);

void actSt04rTorch3_1XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(272) != 0) {
        scpTorchLightOn(1562);
    }
}

void actSt04rTorch3_2XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(273) != 0) {
        scpTorchLightOn(1563);
    }
}

INCLUDE_ASM(actSt04rMonyou01);

INCLUDE_ASM(actSt04rMonyou02);

INCLUDE_ASM(actSt04rMonyou03);

INCLUDE_ASM(actSt04rMonyou04);

INCLUDE_ASM(actSt04rMonyou05);

INCLUDE_ASM(actSt04rMonyou06);

INCLUDE_ASM(actSt04rMonyou07);

INCLUDE_ASM(actSt05cDoorInit);

void actSt04rC1BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = c1_ball_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04rC1BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c1_ball_switch_mes[0].func = actSt04rC1BallTurn;
    sub->mail = c1_ball_switch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt04rC1BallTurn);

void actSt04rC2BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = c2_ball_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04rC2BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c2_ball_switch_mes[0].func = actSt04rC2BallTurn;
    sub->mail = c2_ball_switch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt04rC2BallTurn);

void actSt04rC3BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = c3_ball_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04rC3BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c3_ball_switch_mes[0].func = actSt04rC3BallTurn;
    sub->mail = c3_ball_switch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt04rC3BallTurn);

INCLUDE_ASM(actSt04rCrestMain);

void actSt04rSolarStageChangeChk(GObj *volatile self)
{
    while (gflagChk(243) == 0 || gflagChk(244) == 0 || gflagChk(245) == 0 || gflagChk(232) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(8, boyGObj, 0, 2.0f, 8.0f);
}

void actSt04rStairEvent(int x)
{
    volatile int local = x;
}

void actSt04rRope1Event(int x)
{
    volatile int local = x;
}

void actSt04rRope2Event(int x)
{
    volatile int local = x;
}

void actSt04rBrg1Event(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt04rBrg1Chk);

static void actSt04rBrg1Sub(GObj *volatile self)
{
    _ACTWait(60);

    while (sekizo5c == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(sekizo5c->stream);

    stage_SetAnimation(sekizo_4r, 1, 0);

    while (stage_CheckAnimationFrame(sekizo_4r, 75, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(sekizo_4r) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt04rRope3Event(int x)
{
    volatile int local = x;
}

void actSt04rRope4Event(int x)
{
    volatile int local = x;
}

void actSt04rBrg2Event(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt04rBrg2Chk);

void actSt04rBrg1WayChk(GObj *volatile self)
{
    while (gflagChk(259) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(3, 1);
}

void actSt04rBrg2WayChk(GObj *volatile self)
{
    while (gflagChk(259) == 0 || gflagChk(260) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);
}

void actSt04rMonyou01Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou02Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou03Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou04Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou05Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou06Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou07Event(int x)
{
    volatile int local = x;
}

void actSt04rBarricadeEvent(int x)
{
    volatile int local = x;
}

void actSt04rGondolaCharaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0xA000000) != 0 &&
           (gflagChk(286) == 0 || scpTriggerFloorAttr(girlGObj, 0xA000000) == 0)) {
        _ACTWait(1);
    }

    gondola_chara_chk_mes[0].func = actSt04rGondolaChk;
    sub->mail = gondola_chara_chk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt04rTorch1_1Chk);

INCLUDE_ASM(actSt04rTorch1_2Chk);

void actSt04rTorch2_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1487) == 0) {
        _ACTWait(1);
    }

    gflagOn(268);
}

void actSt04rTorch2_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1488) == 0) {
        _ACTWait(1);
    }

    gflagOn(269);
}

void actSt04rTorch3_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1489) == 0) {
        _ACTWait(1);
    }

    gflagOn(272);
}

void actSt04rTorch3_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1490) == 0) {
        _ACTWait(1);
    }

    gflagOn(273);
}

INCLUDE_ASM(actSt04rTorch2_1XLChk);

INCLUDE_ASM(actSt04rTorch2_2XLChk);
