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

/* the stream the rope checks (actSt04lRope1Chk, func_0021BD80) open */
static SqEntry *ropeChk4l = 0; /* derived name */

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

INCLUDE_ASM(func_0021AA18);

INCLUDE_ASM(func_0021AB40);

INCLUDE_ASM(func_0021AC68);

static ActMail c1BallMain_mes[2] = {{376, actSt04lC1BallSwitch}, {396}}; /* derived name */

static ActMail c1Ball_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c1BallSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c2BallMain_mes[2] = {{376, actSt04lC2BallSwitch}, {396}}; /* derived name */

static ActMail c2Ball_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c2BallSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c3BallMain_mes[2] = {{377, actSt04lC3BallSwitch}, {396}}; /* derived name */

static ActMail c3Ball_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c3BallSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail crest01_mes[2] = {{397}, {396}}; /* derived name */

static ActMail crest02_mes[2] = {{397}, {396}}; /* derived name */

static ActMail crest03_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st04eSolarBeam_mes[2] = {{397}, {396}}; /* derived name */

static ActMail stair_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope3_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope4_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg1Way_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg2Way_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail turi_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondola2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_chara[2] = {{397}, {396}}; /* derived name */

static ActMail monyou01_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou02_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou03_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou04_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou05_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou06_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou07_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ori_mes[2] = {{397}, {396}}; /* derived name */

static ActMail oriRopeCutR_mes[2] = {{397}, {396}}; /* derived name */

static ActMail oriRopeCutL_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ori2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sword_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch1_1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch1_2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch3_1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch3_2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_1XL_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_2XL_mes[2] = {{397}, {396}}; /* derived name */

INCLUDE_ASM(actSt04lCrest02);

INCLUDE_ASM(func_0021AE20);

INCLUDE_ASM(func_0021B010);

INCLUDE_ASM(func_0021B2E8);

INCLUDE_ASM(func_0021B478);

INCLUDE_ASM(func_0021B750);

INCLUDE_ASM(func_0021B890);

INCLUDE_ASM(func_0021B9D0);

INCLUDE_ASM(actSt04lRope2Chk);

INCLUDE_ASM(actSt04lRope3Chk);

INCLUDE_ASM(func_0021BD80);

INCLUDE_ASM(actSt04lSekizoChk);

INCLUDE_ASM(actSt04lGondolaChk);

INCLUDE_ASM(actSt04lMonyou01Chk);

INCLUDE_ASM(actSt04lMonyou02Chk);

INCLUDE_ASM(actSt04lMonyou03Chk);

INCLUDE_ASM(actSt04lMonyou04Chk);

INCLUDE_ASM(actSt04lMonyou05Chk);

INCLUDE_ASM(actSt04lMonyou06Chk);

INCLUDE_ASM(actSt04lMonyou07Chk);

INCLUDE_ASM(func_0021CE30);

INCLUDE_ASM(actSt04lOriRopeCutRChk);

INCLUDE_ASM(actSt04lOriRopeCutLChk);

INCLUDE_ASM(actSt04lOri2);

INCLUDE_ASM(func_0021D420);

INCLUDE_ASM(actSt04lCrest01);

INCLUDE_ASM(actSt04lCrest03);

INCLUDE_ASM(actSt04lC1Ball);

INCLUDE_ASM(actSt04lC2Ball);

INCLUDE_ASM(actSt04lC3Ball);

INCLUDE_ASM(actSt04lStair);

INCLUDE_ASM(actSt04lBrg1);

INCLUDE_ASM(actSt04lBrg2);

INCLUDE_ASM(actSt04lBrg1Way);

INCLUDE_ASM(actSt04lBrg2Way);

INCLUDE_ASM(actSt04lRope1);

INCLUDE_ASM(actSt04lRope2);

INCLUDE_ASM(actSt04lRope3);

INCLUDE_ASM(actSt04lRope4);

INCLUDE_ASM(actSt04lSekizo);

INCLUDE_ASM(actSt04lTuri);

INCLUDE_ASM(actSt04lOri);

INCLUDE_ASM(actSt04lOriRopeCutR);

INCLUDE_ASM(actSt04lOriRopeCutL);

INCLUDE_ASM(actSt04lSword);

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

INCLUDE_ASM(actSt04lTorch3_1XL);

INCLUDE_ASM(actSt04lTorch3_2XL);

INCLUDE_ASM(actSt04cDoorInit);

INCLUDE_ASM(actSt04dEnemy1);

INCLUDE_ASM(actSt04dEnemy2);

INCLUDE_ASM(actSt04dEnemy3);

INCLUDE_ASM(actSt04eSolarBeam);

INCLUDE_ASM(actSt04lC1BallMain);

INCLUDE_ASM(actSt04lC1BallSwitch);

INCLUDE_ASM(actSt04lC2BallMain);

INCLUDE_ASM(actSt04lC2BallSwitch);

INCLUDE_ASM(actSt04lC3BallMain);

INCLUDE_ASM(actSt04lC3BallSwitch);

INCLUDE_ASM(func_0021F1C8);

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

INCLUDE_ASM(actSt04lBrg1WayChk);

INCLUDE_ASM(actSt04lBrg2WayChk);

void actSt04lTuriEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt04lTuriChk);

INCLUDE_ASM(actSt04lGondolaCharaChk);

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

INCLUDE_ASM(actSt04lSwordChk);

INCLUDE_ASM(actSt04lTorch1_1Chk);

INCLUDE_ASM(actSt04lTorch1_2Chk);

INCLUDE_ASM(actSt04lTorch2_1Chk);

INCLUDE_ASM(actSt04lTorch2_2Chk);

INCLUDE_ASM(actSt04lTorch3_1Chk);

INCLUDE_ASM(actSt04lTorch3_2Chk);

INCLUDE_ASM(actSt04lTorch2_1XLChk);

INCLUDE_ASM(actSt04lTorch2_2XLChk);
