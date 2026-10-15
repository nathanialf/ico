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

/* .sdata: bmg, the two scene streams, and the stream actSt13cHandChk
   waits on. */
SqEntry *bmg = 0;

static SqEntry *st13c_adpcm = 0; /* derived name */

static SqEntry *st13c_adpcm2 = 0; /* derived name */

static SqEntry *st13c_reserved = 0; /* derived name */

void actSt13cInit(void)
{
    if (gflagChk(20)) {
        SetWayGroupActive(9, 0);
    }
}

void actSt13cEnd(void)
{
    if (gflagChk(29) == 0) {
        debug_StdPrintfDummy("BackStageOff\n");
        gflagOn(357);
    }
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */
typedef union { /* field names derived */
    float f[4];
    long long d[2];
} __attribute__((aligned(16))) ConstVecSt13c; /* derived name */

/* The animations actSt13cConte04 steps through. */
static const AnimSet conte04Anims = {{554, 555, 556, 557, 558}}; /* derived name */

/* Where actSt13cSleepChk turns the sleeping girl to face. */
static const ConstVecSt13c sleepFacePos = {{-800.0f, 0.0f, -1000.0f, 1.0f}}; /* derived name */

/* The animations actSt13cConte05 steps through. */
static const AnimSet16 conte05Anims = {
    /* derived name */
    {559, 560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571, 572, 573, 574}};

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

void actSt13cCageFallEffect(GObj *volatile self)
{
    EffectArg b1;
    EffectArg b2;
    EffectArg b3;
    EffectArg b4;
    EffectArg b5;
    EffectArg b6;
    EffectArg b7;
    EffectArg b8;
    EffectArg b9;
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 0:
            gflagOn(21);
            break;
        case 64:
            iosPadActRequest(boyPad, 17);
            b1 = cageFallEffect1;
            scpEffectStart(&b1, 0);
            b2 = cageFallEffect2;
            scpEffectStart(&b2, 0);
            break;
        case 68:
            b3 = cageFallEffect3;
            scpEffectStart(&b3, 0);
            b4 = cageFallEffect4;
            scpEffectStart(&b4, 0);
            break;
        case 96:
            b5 = cageFallEffect5;
            scpEffectStart(&b5, 0);
            b6 = cageFallEffect6;
            scpEffectStart(&b6, 0);
            b7 = cageFallEffect7;
            scpEffectStart(&b7, 0);
            break;
        case 180:
            iosPadActRequest(boyPad, 15);
            break;
        case 300:
            b8 = cageFallEffect8;
            scpEffectStart(&b8, 0);
            b9 = cageFallEffect9;
            scpEffectStart(&b9, 0);
            break;
        case 380:
            iosPadActRequest(boyPad, 16);
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
    } while (t < 400.0f);
    _ACTWait(0);
}

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

void actSt13cEnemyNull(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(24) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);
}

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

void actSt13cSleepChk(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, girlGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    scpPlayStart(girlGObj);
    _ACTWait(1);

    ofs[0] = sleepFacePos.d[0];
    ofs[1] = sleepFacePos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpPlayMotReq(girlGObj, 253);
}

void actSt13cCageDownMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = cageDownMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt13cCageDownSwitch);

void actSt13cCage1stDownDemo(GObj *volatile self)
{
    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 307);
    scpPlayWaitMotEnd(boyGObj);
    _ACTWait(240);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt13cCageFallReadyChk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 || gflagChk(19) == 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(15, &st13c_adpcm2, 1, 1, 0);
}

void actSt13cCageFallEvent(int x)
{
    volatile int local = x;
}

static void actE3St13cSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt13cSekizoJimakuChk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    while (gflagChk(29) == 0) {
        _ACTWait(1);
    }

    gflagOff(357);
    actCreateSubThread(actSt13cSekizoJimakuEff, 21);
}

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

void actSt13cBukiChk(GObj *volatile self)
{
    while (ForMotionViewer_GetCurrentMotion(boyGObj) != 227) {
        _ACTWait(1);
    }
    stage_SetAnimation(63, -1, -2);
}
