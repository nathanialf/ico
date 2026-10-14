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

static ActMail bmg1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sleep_mes[2] = {{430}, {429}}; /* derived name */

static ActMail cageDownMain_mes[2] = {{406, actSt13cCageDownSwitch}, {429}}; /* derived name */

static ActMail cageDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail cageDownSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail cageFallReady_mes[2] = {{430}, {429}}; /* derived name */

static ActMail cageFall_mes[2] = {{430}, {429}}; /* derived name */

static ActMail cageFall2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizoJimaku_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlCarry_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlCarryChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlCarryAgainChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hand_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rescue_mes[2] = {{430}, {429}}; /* derived name */

static ActMail buki_mes[2] = {{430}, {429}}; /* derived name */

/* .sdata: bmg and hand around the two scene streams, then a word no code
   uses, a shake and its volume. */
SqEntry *bmg = 0;

static SqEntry *st13c_adpcm = 0; /* derived name */

static SqEntry *st13c_adpcm2 = 0; /* derived name */

SqEntry *hand = 0;

static SqEntry *st13c_reserved = 0; /* derived name */

static int st13c_yure = 0; /* derived name */

static unsigned char st13c_yure_vol = 0; /* derived name */

void actSt13cInit(void)
{
    if (gflagChk(21)) {
        SetWayGroupActive(9, 0);
    }
}

void actSt13cEnd(void)
{
    if (gflagChk(31) == 0) {
        debug_StdPrintfDummy("BackStageOff\n");
        gflagOn(390);
    }
}

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

void actSt13cBmg1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (girlGObj == 0) {
        return;
    }
    if (gflagChk(21) != 0) {
        return;
    }

    GOBJ_ACT(boyGObj)->flags |= 0x100000;

    if (gflagChk(20) != 0) {
        scpPlayPosSet(girlGObj, -30.0f, -436.0f, -1.0f);
        _ACTWait(60);
        scpPlayStart(girlGObj);
    } else if (gflagChk(18) == 0) {
        ScpCallCameraOff();
        scpPlayPosSet(girlGObj, -7.0f, -5725.0f, 18.0f);

        bmg1_mes[0].func = actSt13cBmg1Chk;
        act->mail = bmg1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpPlayPosSet(girlGObj, -7.0f, -5725.0f, 18.0f);
    }
}

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

void actSt13cCage1stDown(GObj *volatile self);

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
            gflagOn(22);
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

INCLUDE_ASM(actSt13cSekizoChk);

void actSt13cGirlCarryChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(25) == 0 || GOBJ_ACT(girlGObj)->actMode == 111 ||
           GOBJ_ACT(girlGObj)->actMode == 110 || gflagChk(29) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);

    scpPlayStart(girlGObj);
    scpPlayMot(girlGObj, 595);
    scpPlayWaitMotEnd(girlGObj);
    scpPlayMot(girlGObj, 596);

    GOBJ_SUB(girlGObj)->ctrl.blendFrames =
        (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f * 30.0f);

    gflagOn(26);

    girlCarryChk_mes[0].func = actSt13cGirlCarryAgainChk;
    act->mail = girlCarryChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);

    _ACTWait(1);
}

void actSt13cHandChk(GObj *volatile self);

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

void actSt13cSleep(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(19) == 0) {
        sleep_mes[0].func = actSt13cSleepChk;
        act->mail = sleep_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt13cCageDown);

void actSt13cCageFallReady(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(22) == 0) {
        cageFallReady_mes[0].func = actSt13cCageFallReadyChk;
        act->mail = cageFallReady_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13cEnemy(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    bossGenerator = self;
    Generator_Mask(self);

    while (gflagChk(23) == 0) {
        _ACTWait(1);
    }

    Generator_Call(scpSearchGobj(152));
    _ACTWait(180);

    Generator_Call(self);
    scpSleepEnemyAll();
    gflagOff(23);
}

void actSt13cEnemyNull(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(25) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);
}

INCLUDE_ASM(actSt13cSekizo);

void actSt13cSekizoJimaku(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(31) == 0) {
        sekizoJimaku_mes[0].func = actSt13cSekizoJimakuChk;
        act->mail = sekizoJimaku_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13cHand(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(27) == 0) {
        hand_mes[0].func = actSt13cHandChk;
        act->mail = hand_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13cGirlCarry(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(27) == 0) {
        girlCarry_mes[0].func = actSt13cGirlCarryChk;
        act->mail = girlCarry_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13cRescue(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(30) == 0 && gflagChk(27) == 0) {
        rescue_mes[0].func = actSt13cRescueChk;
        act->mail = rescue_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13cBuki(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    buki_mes[0].func = actSt13cBukiChk;
    act->mail = buki_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actE3St13cSekizo);

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

    scpPlayMotReq(girlGObj, 285);
}

void actSt13cCageDownMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = cageDownMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13cCageDownSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    if (gflagChk(20) == 0) {
        cageDownSwitch_mes[0].func = actSt13cCage1stDown;
        sub->mail = cageDownSwitch_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13cCage1stDownDemo(GObj *volatile self)
{
    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 313);
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

    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 || gflagChk(20) == 0) {
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

    while (gflagChk(31) == 0) {
        _ACTWait(1);
    }

    gflagOff(390);
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

void actSt13cGirlCarryAgainChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (GOBJ_ACT(girlGObj)->actMode != 111) {
        _ACTWait(1);
    }

    gflagOff(26);

    girlCarryAgainChk_mes[0].func = actSt13cGirlCarryChk;
    act->mail = girlCarryAgainChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);

    _ACTWait(1);
}

static void actSt13cHandSub(GObj *volatile self)
{
    _ACTWait(100);
    scpPlayWaitMotEnd(boyGObj);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt13cRescueChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (GOBJ_ACT(girlGObj)->actMode != 110) {
        _ACTWait(1);
    }

    gflagOn(29);
    scpBoyControlReadDisable = 1;
    _ACTWait(200);

    scpPlayStart(girlGObj);
    scpPlayMot(girlGObj, 596);
    _ACTWait(120);

    gflagOn(30);
}

void actSt13cBukiEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt13cBukiChk);
