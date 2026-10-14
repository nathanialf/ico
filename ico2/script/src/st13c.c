#include "st13c.h"
#include "StageManager.h"
#include "debug.h"
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
#include "enemy_act.h"
#include "way_llf.h"
#include "camera-ico2.h"
#include "camera-root.h"
#include "fightSound.h"
#include "generator.h"
#include "gflag.h"
#include "script.h"
#include "GsBase.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "weapon.h"
#include <libvu0.h>
#include <string.h>
#include "e3.h"
#include "typedef.h"
#include "main.h"
#include "jimaku.h"
#include "include_asm.h"

static void actSt13cHandSub(GObj *volatile self);

/* the stage-animation number sets the contes play; two functions keep one
   in their frame as the scratch vector they hand scpPlayMotDir or
   DirectCallEnemy. */
typedef struct AnimSet { /* field names derived */
    int anim[5];         /* 0x00 */
} AnimSet;               /* derived name */

typedef struct AnimSet16 { /* field names derived */
    int anim[16];          /* 0x00 */
} AnimSet16;               /* derived name */

/* .sbss: the flag each demo raises when it is over, and the generator the boss
   fight calls through. */
static int demoEnd;

static GObj *bossGenerator; /* derived name */

/* .data: actor mail packets. */

static ActMail bmg1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sleep_mes[2] = {{397}, {396}}; /* derived name */

static ActMail cageDownMain_mes[2] = {{376, actSt13cCageDownSwitch}, {396}}; /* derived name */

static ActMail cageDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail cageDownSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail cageFallReady_mes[2] = {{397}, {396}}; /* derived name */

static ActMail cageFall_mes[2] = {{397}, {396}}; /* derived name */

static ActMail cageFall2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail girlCarry_mes[2] = {{397}, {396}}; /* derived name */

static ActMail girlCarryChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail girlCarryAgainChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hand_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rescue_mes[2] = {{397}, {396}}; /* derived name */

static ActMail buki_mes[2] = {{397}, {396}}; /* derived name */

/* .sdata: bmg and hand around the two scene streams, then a word no code
   uses, a shake and its volume. */
SqEntry *bmg = 0;

static SqEntry *st13c_adpcm = 0; /* derived name */

static SqEntry *st13c_adpcm2 = 0; /* derived name */

SqEntry *hand = 0;

static SqEntry *st13c_reserved = 0; /* derived name */

static int st13c_yure = 0; /* derived name */

static unsigned char st13c_yure_vol = 0; /* derived name */

INCLUDE_ASM(actSt13cInit);

INCLUDE_ASM(actSt13cEnd);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */
typedef union { /* field names derived */
    float f[4];
    long long d[2];
} __attribute__((aligned(16))) ConstVecSt13c; /* derived name */

/* The animations actSt13cConte04 steps through. */
static const AnimSet conte04Anims = {{625, 626, 627, 628, 629}}; /* derived name */

/* Where actSt13cSleepChk turns the sleeping girl to face. */
static const ConstVecSt13c sleepFacePos = {{-800.0f, 0.0f, -1000.0f, 1.0f}}; /* derived name */

/* The animations actSt13cConte05 steps through. */
static const AnimSet16 conte05Anims = {
    /* derived name */
    {630, 631, 632, 633, 634, 635, 636, 637, 638, 639, 640, 641, 642, 643, 644, 645}};

/* actSt13cCageFallEffect's nine effect spawns, in the frame order it fires them. */
static const EffectArg cageFallEffect1 = {{-88.0f, -50.0f, -1.0f, 1.0f}}; /* derived name */

static const EffectArg cageFallEffect2 = {{-96.0f, -45.0f, 34.0f, 1.0f}}; /* derived name */

static const EffectArg cageFallEffect3 = {{72.0f, -50.0f, 8.0f, 1.0f}}; /* derived name */

static const EffectArg cageFallEffect4 = {{80.0f, -50.0f, 2.0f, 1.0f}}; /* derived name */

static const EffectArg cageFallEffect5 = {{-27.0f, -50.0f, 100.0f, 1.0f}}; /* derived name */

static const EffectArg cageFallEffect6 = {{-56.0f, -50.0f, 66.0f, 1.0f}}; /* derived name */

static const EffectArg cageFallEffect7 = {{-5.0f, -50.0f, 42.0f, 1.0f}}; /* derived name */

static const EffectArg cageFallEffect8 = {{-10.0f, 0.0f, 466.0f, 1.0f}}; /* derived name */

static const EffectArg cageFallEffect9 = {{-25.0f, 0.0f, 450.0f, 1.0f}}; /* derived name */

INCLUDE_ASM(actSt13cBmg1);

INCLUDE_ASM(actSt13cBmg1Chk);

INCLUDE_ASM(actSt13cConte04);

void actSt13cConte04Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 290:
            jimaku_msg.sub.block = 2;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 800:
            jimaku_msg.sub.block = 4;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1070:
            jimaku_msg.sub.block = 5;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 1400.0f);
    _ACTWait(0);
}

INCLUDE_ASM(actSt13cCage1stDownDemoCancel);

INCLUDE_ASM(actSt13cCage1stDown);

INCLUDE_ASM(actSt13cCageFall);

INCLUDE_ASM(actSt13cCageFallChk);

INCLUDE_ASM(actSt13cConte05);

void actSt13cConte05Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 1630:
            jimakuOn = 1;
            jimaku_msg.sub.block = 9;
            jimaku_msg.sub.jump = -1;
            jimakuJump(&jimaku_msg);
            break;
        case 2492:
            jimaku_msg.sub.block = 6;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2760:
            jimaku_msg.sub.block = 7;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3712:
            jimaku_msg.sub.block = 8;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 4000.0f);
    _ACTWait(0);
}

INCLUDE_ASM(actSt13cCageFallEffect);

INCLUDE_ASM(actSt13cGirlCarryChk);

INCLUDE_ASM(actSt13cHandChk);

void actSt13cHandJimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 110:
            jimaku_msg.sub.block = 11;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 340:
            jimaku_msg.sub.block = 12;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 580:
            jimaku_msg.sub.block = 13;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 800.0f);
}

INCLUDE_ASM(actSt13cSleep);

INCLUDE_ASM(actSt13cCageDown);

INCLUDE_ASM(actSt13cCageFallReady);

INCLUDE_ASM(actSt13cEnemy);

INCLUDE_ASM(actSt13cEnemyNull);

INCLUDE_ASM(actE3St13cSekizo);

INCLUDE_ASM(actSt13cSekizo);

INCLUDE_ASM(actSt13cHand);

INCLUDE_ASM(actSt13cGirlCarry);

INCLUDE_ASM(actSt13cRescue);

INCLUDE_ASM(actSt13cBuki);

void actSt13cBmg1Event(int x)
{
    volatile int local = x;
}

void actSt13cSleepEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt13cSleepChk);

INCLUDE_ASM(actSt13cCageDownMain);

INCLUDE_ASM(actSt13cCageDownSwitch);

INCLUDE_ASM(actSt13cCage1stDownDemo);

INCLUDE_ASM(actSt13cCageFallReadyChk);

void actSt13cCageFallEvent(int x)
{
    volatile int local = x;
}

static void actE3St13cSekizoEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt13cSekizoJimakuChk);

void actSt13cSekizoJimakuEff(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 45:
            jimaku_msg.sub.block = 19;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 500.0f);
}

INCLUDE_ASM(actSt13cGirlCarryAgainChk);

INCLUDE_ASM(actSt13cRescueChk);

void actSt13cBukiEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt13cBukiChk);
