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

INCLUDE_ASM(actSt05eEnd);

INCLUDE_ASM(actSt05cInit);

INCLUDE_ASM(actSt05dInit);

INCLUDE_ASM(actSt05eInit);

INCLUDE_ASM(actSt04rC1BallTurn);

INCLUDE_ASM(actSt04rC2BallTurn);

INCLUDE_ASM(actSt04rC3BallTurn);

INCLUDE_ASM(actSt04rCrest02);

INCLUDE_ASM(actSt04rCrestMain);

INCLUDE_ASM(actSt04rCrest2Main);

INCLUDE_ASM(actSt04rCrest3Main);

INCLUDE_ASM(actSt04rSolarBeam);

INCLUDE_ASM(actSt04rSolarBeamChk);

static void actSt04rStairSub(GObj *volatile self);

INCLUDE_ASM(actSt04rStairChk);

INCLUDE_ASM(actSt04rSekizoChk);

INCLUDE_ASM(actSt04rRope1Chk);

INCLUDE_ASM(actSt04rRope2Chk);

void actSt04rBrgCommon(GObj *volatile self);

INCLUDE_ASM(actSt04rBrg1Chk);

INCLUDE_ASM(actSt04rRope3Chk);

INCLUDE_ASM(actSt04rRope4Chk);

INCLUDE_ASM(actSt04rBrg2Chk);

INCLUDE_ASM(actSt04rMonyou01Chk);

INCLUDE_ASM(actSt04rMonyou02Chk);

INCLUDE_ASM(actSt04rMonyou03Chk);

INCLUDE_ASM(actSt04rMonyou04Chk);

INCLUDE_ASM(actSt04rMonyou05Chk);

INCLUDE_ASM(actSt04rMonyou06Chk);

INCLUDE_ASM(actSt04rMonyou07Chk);

INCLUDE_ASM(actSt04rGondolaChk);

INCLUDE_ASM(actSt04rSolarStageChange);

INCLUDE_ASM(actSt04rCrest01);

INCLUDE_ASM(actSt04rCrest03);

INCLUDE_ASM(actSt04rC1Ball);

INCLUDE_ASM(actSt04rC2Ball);

INCLUDE_ASM(actSt04rC3Ball);

INCLUDE_ASM(actSt04rStair);

INCLUDE_ASM(actSt04rBrg1);

INCLUDE_ASM(actSt04rBrg2);

INCLUDE_ASM(actSt04rBrg1Way);

INCLUDE_ASM(actSt04rBrg2Way);

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

INCLUDE_ASM(actSt04rTorch2_1);

INCLUDE_ASM(actSt04rTorch2_2);

INCLUDE_ASM(actSt04rTorch3_1);

INCLUDE_ASM(actSt04rTorch3_2);

INCLUDE_ASM(actSt04rTorch2_1XL);

INCLUDE_ASM(actSt04rTorch2_2XL);

INCLUDE_ASM(actSt04rTorch3_1XL);

INCLUDE_ASM(actSt04rTorch3_2XL);

INCLUDE_ASM(actSt04rMonyou01);

INCLUDE_ASM(actSt04rMonyou02);

INCLUDE_ASM(actSt04rMonyou03);

INCLUDE_ASM(actSt04rMonyou04);

INCLUDE_ASM(actSt04rMonyou05);

INCLUDE_ASM(actSt04rMonyou06);

INCLUDE_ASM(actSt04rMonyou07);

INCLUDE_ASM(actSt05cDoorInit);

INCLUDE_ASM(actSt04rC1BallMain);

INCLUDE_ASM(actSt04rC1BallSwitch);

INCLUDE_ASM(actSt04rC2BallMain);

INCLUDE_ASM(actSt04rC2BallSwitch);

INCLUDE_ASM(actSt04rC3BallMain);

INCLUDE_ASM(actSt04rC3BallSwitch);

INCLUDE_ASM(actSt04rSolarStageChangeChk);

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

INCLUDE_ASM(actSt04rBrg1WayChk);

INCLUDE_ASM(actSt04rBrg2WayChk);

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

INCLUDE_ASM(actSt04rBarricadeChk);

INCLUDE_ASM(actSt04rGondolaCharaChk);

INCLUDE_ASM(actSt04rTorch1_1Chk);

INCLUDE_ASM(actSt04rTorch1_2Chk);

INCLUDE_ASM(actSt04rTorch2_1Chk);

INCLUDE_ASM(actSt04rTorch2_2Chk);

INCLUDE_ASM(actSt04rTorch3_1Chk);

INCLUDE_ASM(actSt04rTorch3_2Chk);

INCLUDE_ASM(actSt04rTorch2_1XLChk);

INCLUDE_ASM(actSt04rTorch2_2XLChk);
