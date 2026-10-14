#include "st04l.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "obj_manager.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act-game.h"
#include "act.h"
#include "gobj_process.h"
#include "boyact.h"
#include "commonact.h"
#include "girl_act.h"
#include "way_llf.h"
#include "camera-root.h"
#include "fightSound.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "st04r.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "motionManager2.h"
#include "weapon.h"
#include <libvu0.h>
#include "typedef.h"
#include "st04r.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt04eSolarBeamChkSub(GObj *volatile self);

/* .sbss: the four arguments turnBall hands to the ball-turn actor through file
   scope, the demo's own end flag, the crest-2 animation the room selects, and
   the flag the stair subthread raises once it is past its setup. */
static int turnFlag; /* derived name */

static int turnAnim; /* derived name */

static int turnGobj1; /* derived name */

static int turnGobj2; /* derived name */

static int demoEnd;

static int crest2Anim; /* derived name */

static int subStarted; /* derived name */

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec stairSubPos = {{0.0f, 0.0f, -5000.0f, 1.0f}}; /* derived name */

/* .sdata: the room's stream handles and shakes (solar4l unused). */
SqEntry *ball1_4l = 0;

SqEntry *ball2_4l = 0;

SqEntry *ball3_4l = 0;

SqEntry *crest1 = 0;

SqEntry *crest2 = 0;

SqEntry *crest3 = 0;

int solar4l = 0;

SqEntry *stair4d = 0;

SqEntry *st04d_hasi = 0;

SqEntry *sekizo4c = 0;

unsigned int oriup4c = 0;

unsigned char oridown4c = 0;

unsigned int st04l_yure = 0;

unsigned char st04l_yure_vol = 0;

INCLUDE_ASM(actSt04cInit);

INCLUDE_ASM(actSt04dInit);

INCLUDE_ASM(actSt04eInit);

static void actSt04lBallTurnCommonSub(GObj *volatile self)
{
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(82, &ball1_4l, 1, 1, 1);

    while (ball1_4l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(turnAnim, 1, 0);

    while (stage_CheckAnimationFinish(turnAnim) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    demoEnd = 1;
    _ACTWait(0);
}

static void actSt04lBallTurnCommon(GObj *volatile self);

INCLUDE_ASM(actSt04lBallTurnCommon);

static ActMail c1BallMain_mes[2] = {{406, actSt04lC1BallSwitch}, {429}}; /* derived name */

static ActMail c1Ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c1BallSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c1BallTurn_mes[2] = {{430}, {429}}; /* derived name */

static ActMail turnBall_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c2BallMain_mes[2] = {{406, actSt04lC2BallSwitch}, {429}}; /* derived name */

static ActMail c2Ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c2BallSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c2BallTurn_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c3BallMain_mes[2] = {{407, actSt04lC3BallSwitch}, {429}}; /* derived name */

static ActMail c3Ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c3BallSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c3BallTurn_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest01_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest03_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st04eSolarBeam_mes[2] = {{430}, {429}}; /* derived name */

static ActMail stair_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1Chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope3_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope4_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2Chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1Way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2Way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail turi_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_chara[2] = {{430}, {429}}; /* derived name */

static ActMail monyou01_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou03_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou04_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou05_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou06_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou07_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ori_mes[2] = {{430}, {429}}; /* derived name */

static ActMail oriRopeCutR_mes[2] = {{430}, {429}}; /* derived name */

static ActMail oriRopeCutL_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ori2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sword_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch1_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch1_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch3_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch3_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_1XL_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_2XL_mes[2] = {{430}, {429}}; /* derived name */

void turnBall(GObj *self, int flag, int anim, int gobj1, int gobj2)
{
    Act *sub = GOBJ_ACT(self);

    turnFlag = flag;
    turnAnim = anim;
    turnGobj1 = gobj1;
    turnGobj2 = gobj2;

    turnBall_mes[0].func = actSt04lBallTurnCommon;
    sub->mail = turnBall_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt04lCrest02);

INCLUDE_ASM(actSt04lCrestSub);

INCLUDE_ASM(actSt04lCrestMain);

static void actSt04lCrest2Sub(GObj *volatile self)
{
    stage_SetAnimation(crest2Anim, 1, 0);

    while (stage_CheckAnimationFrame(crest2Anim, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    oriup4c = iosPadActRequest(boyPad, 10);
    oridown4c = 128;
    iosPadActVolumeSet(oriup4c, 128);

    while (stage_CheckAnimationFrame(crest2Anim, 190, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(oriup4c);
    oriup4c = 0xFFFFFFFF;

    while (stage_CheckAnimationFinish(crest2Anim) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    if (current_stage_no == 19) {
        scpSearchGobj(1122)->active = 1;
    }

    demoEnd = 1;
    _ACTWait(0);
}

INCLUDE_ASM(actSt04lCrest2Main);

INCLUDE_ASM(actSt04lCrest3Sub);

INCLUDE_ASM(actSt04lCrest3Main);

void actSt04eSolarBeamChk(GObj *volatile self);

INCLUDE_ASM(actSt04eSolarBeamChk);

INCLUDE_ASM(actSt04lStairSub);

INCLUDE_ASM(actSt04lStairChk);

INCLUDE_ASM(actSt04lRope1Chk);

INCLUDE_ASM(actSt04lRope2Chk);

INCLUDE_ASM(actSt04lRope3Chk);

INCLUDE_ASM(actSt04lRope4Chk);

INCLUDE_ASM(actSt04lSekizoChk);

void actSt04lGondolaChk(GObj *volatile self);

INCLUDE_ASM(actSt04lGondolaChk);

INCLUDE_ASM(actSt04lMonyou01Chk);

INCLUDE_ASM(actSt04lMonyou02Chk);

INCLUDE_ASM(actSt04lMonyou03Chk);

INCLUDE_ASM(actSt04lMonyou04Chk);

INCLUDE_ASM(actSt04lMonyou05Chk);

INCLUDE_ASM(actSt04lMonyou06Chk);

INCLUDE_ASM(actSt04lMonyou07Chk);

INCLUDE_ASM(actSt04lOriSub);

INCLUDE_ASM(actSt04lOriChk);

void actSt04lOriRopeCutRChk(GObj *volatile self);

INCLUDE_ASM(actSt04lOriRopeCutRChk);

void actSt04lOriRopeCutLChk(GObj *volatile self);

INCLUDE_ASM(actSt04lOriRopeCutLChk);

INCLUDE_ASM(actSt04lOri2);

INCLUDE_ASM(actSt04lOri2Sub);

INCLUDE_ASM(actSt04lOri2Chk);

INCLUDE_ASM(actSt04lCrest01);

INCLUDE_ASM(actSt04lCrest03);

INCLUDE_ASM(actSt04lC1Ball);

INCLUDE_ASM(actSt04lC2Ball);

INCLUDE_ASM(actSt04lC3Ball);

INCLUDE_ASM(actSt04lStair);

void actSt04lBrg1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(182) == 0) {
        brg1_mes[0].func = actSt04lBrg1Chk;
        act->mail = brg1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04lBrg2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(183) == 0) {
        SleepHint(16);

        brg2_mes[0].func = actSt04lBrg2Chk;
        act->mail = brg2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04lBrg1Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(182) == 0) {
        brg1Way_mes[0].func = actSt04lBrg1WayChk;
        act->mail = brg1Way_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04lBrg2Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(183) == 0) {
        brg2Way_mes[0].func = actSt04lBrg2WayChk;
        act->mail = brg2Way_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt04lRope1);

INCLUDE_ASM(actSt04lRope2);

INCLUDE_ASM(actSt04lRope3);

INCLUDE_ASM(actSt04lRope4);

INCLUDE_ASM(actSt04lSekizo);

INCLUDE_ASM(actSt04lTuri);

INCLUDE_ASM(actSt04lOri);

void actSt04lOriRopeCutR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(201) == 0) {
        oriRopeCutR_mes[0].func = actSt04lOriRopeCutRChk;
        act->mail = oriRopeCutR_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04lOriRopeCutL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(202) == 0) {
        oriRopeCutL_mes[0].func = actSt04lOriRopeCutLChk;
        act->mail = oriRopeCutL_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04lSword(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(175) == 0) {
        sword_mes[0].func = actSt04lSwordChk;
        act->mail = sword_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt04lGondola);

INCLUDE_ASM(actSt04lMonyou01);

INCLUDE_ASM(actSt04lMonyou02);

INCLUDE_ASM(actSt04lMonyou03);

INCLUDE_ASM(actSt04lMonyou04);

INCLUDE_ASM(actSt04lMonyou05);

INCLUDE_ASM(actSt04lMonyou06);

INCLUDE_ASM(actSt04lMonyou07);

INCLUDE_ASM(actSt04lCrest01XL);

INCLUDE_ASM(actSt04lCrest02XL);

INCLUDE_ASM(actSt04lCrest03XL);

INCLUDE_ASM(actSt04lC2BallXL);

INCLUDE_ASM(actSt04lC3BallXL);

INCLUDE_ASM(actSt04lTorch1_1);

INCLUDE_ASM(actSt04lTorch1_2);

INCLUDE_ASM(actSt04lTorch2_1);

INCLUDE_ASM(actSt04lTorch2_2);

INCLUDE_ASM(actSt04lTorch3_1);

INCLUDE_ASM(actSt04lTorch3_2);

INCLUDE_ASM(actSt04lTorch2_1XL);

INCLUDE_ASM(actSt04lTorch2_2XL);

void actSt04lTorch3_1XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(210) != 0) {
        scpTorchLightOn(1283);
    }
}

void actSt04lTorch3_2XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(211) != 0) {
        scpTorchLightOn(1284);
    }
}

INCLUDE_ASM(actSt04cDoorInit);

void actSt04dEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(220) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04dEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(220) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04dEnemy3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(220) == 0) {
        _ACTWait(1);
    }

    Generator_Call(self);
}

void actSt04eSolarBeam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(224) != 0) {
        if (boyGObj != 0) {
            scpPlayMot(boyGObj, 0);

            if (ACTGame_NoWeapon(boyGObj) == 0) {
                LightTorchOffOfWeapon(GetBoyWeaponGObj());
            }
        }

        gflagOn(389);

        scpSeEnvMasterVolRate = 0.0f;
        scpFadeOut(255.0f, 0, 0, 0);

        st04eSolarBeam_mes[0].func = actSt04eSolarBeamChk;
        act->mail = st04eSolarBeam_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04lC1BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = c1BallMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04lC1BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c1BallSwitch_mes[0].func = actSt04lC1BallTurn;
    sub->mail = c1BallSwitch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt04lC1BallTurn);

void actSt04lC2BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = c2BallMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04lC2BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c2BallSwitch_mes[0].func = actSt04lC2BallTurn;
    sub->mail = c2BallSwitch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt04lC2BallTurn);

void actSt04lC3BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = c3BallMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04lC3BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c3BallSwitch_mes[0].func = actSt04lC3BallTurn;
    sub->mail = c3BallSwitch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt04lC3BallTurn);

INCLUDE_ASM(actSt04eSolarBeamChkSub);

void actSt04lRope1Event(int x)
{
    volatile int local = x;
}

void actSt04lRope2Event(int x)
{
    volatile int local = x;
}

void actSt04lBrg1Event(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt04lBrg1Chk);

void actSt04lRope3Event(int x)
{
    volatile int local = x;
}

void actSt04lRope4Event(int x)
{
    volatile int local = x;
}

void actSt04lBrg2Event(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt04lBrg2Chk);

void actSt04lBrg1WayChk(GObj *volatile self)
{
    while (gflagChk(182) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(3, 1);
}

void actSt04lBrg2WayChk(GObj *volatile self)
{
    while (gflagChk(182) == 0 || gflagChk(183) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);
}

void actSt04lTuriEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt04lTuriChk);

void actSt04lGondolaCharaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0xA000000)) {
        if (gflagChk(194) && scpTriggerFloorAttr(girlGObj, 0xA000000)) {
            break;
        }
        _ACTWait(1);
    }

    gondola_chara[0].func = actSt04lGondolaChk;
    sub->mail = gondola_chara;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04lMonyou01Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou02Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou03Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou04Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou05Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou06Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou07Event(int x)
{
    volatile int local = x;
}

void actSt04lOriEvent(int x)
{
    volatile int local = x;
}

void actSt04lOri2Event(int x)
{
    volatile int local = x;
}

void actSt04lSwordChk(GObj *volatile self)
{
    scpSearchGobj(1122)->active = 0;
}

INCLUDE_ASM(actSt04lTorch1_1Chk);

INCLUDE_ASM(actSt04lTorch1_2Chk);

INCLUDE_ASM(actSt04lTorch2_1Chk);

INCLUDE_ASM(actSt04lTorch2_2Chk);

INCLUDE_ASM(actSt04lTorch3_1Chk);

INCLUDE_ASM(actSt04lTorch3_2Chk);

INCLUDE_ASM(actSt04lTorch2_1XLChk);

INCLUDE_ASM(actSt04lTorch2_2XLChk);
