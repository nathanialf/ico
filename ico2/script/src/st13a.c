#include "st13a.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "chain.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"

#ifdef VERSION_JUN26
#include "motionManager2.h"
#endif

#include <libvu0.h>
#include "typedef.h"
#include "main.h"

#ifdef VERSION_AUG6
/* The functions stand in the order of the stage's source (aug6's TRFILE
   numbers them so). The ones defined inline are output at the end of the
   file, in the order of the declarations below, which gives this build's
   .text order; the others are output where they stand. */
inline void actSt13aElev(GObj *volatile self);
inline void actSt13aElevDown(GObj *volatile self);
inline void actSt13aSekizo(GObj *volatile self);
inline void actSt13aExit(GObj *volatile self);
inline void actSt13aCheck(GObj *volatile self);
inline void actSt13aChain(GObj *volatile self);
inline void actSt13aElevMain(GObj *volatile self);
inline void actSt13aElevSwitch(GObj *volatile self);
inline void actSt13aExitChk(GObj *volatile self);
inline void actSt13aCheckChk(GObj *volatile self);
inline void actSt13aChainOK(GObj *volatile self);
inline void actSt13aChainNG(GObj *volatile self);
void actSt13aElevDownChk(GObj *volatile self);

/* .data: actor mail packets. The main-thread record answers its own id and
   carries its switch handler from the start; every other record is a static
   of the actor thread that owns and posts it. Word 0 of each entry is the
   mail id the entry answers (393 the actor post, 392 the trailing entry);
   .func is filled in at run time. */
static ActMail elevMain_mes[2] = {{372, actSt13aElevSwitch}, {392}}; /* derived name */
#else
#ifdef VERSION_JUN26
void actSt13aElevDownChk(GObj *volatile self);

/* .data: actor mail packets, each named for the actor that posts it
   (exit_mes is actSt13aExit's, check_mes actSt13aCheck's). */

static ActMail elevMain_mes[2] = {{356, actSt13aElevSwitch}, {376}}; /* derived name */

static ActMail elev_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elevDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail sekizo_mes[2] = {{377}, {376}}; /* derived name */

static ActMail exit_mes[2] = {{377}, {376}}; /* derived name */

static ActMail check_mes[2] = {{377}, {376}}; /* derived name */
#else
#ifndef VERSION_NTSC
/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for. */
static int demoEnd;

static void actSt13aElevUpSub(GObj *volatile self);
static void actSt13aElevDownSub(GObj *volatile self);
#endif

void actSt13aElevDownChk(GObj *volatile self);

/* .data: actor mail packets. */

/* The chain-OK watcher's mail record: it installs actSt13aChainNG here and
   posts it to hand the chain back to the NG (hang-disabled) watcher. Word 0
   of each entry is the mail id the entry answers (430 the actor post,
   429 the trailing entry); .func is filled in at run time. Named for the
   thread that owns and posts it. */

#ifdef VERSION_NTSC
static ActMail elevMain_mes[2] = {{376, actSt13aElevSwitch}, {396}}; /* derived name */

static ActMail elev_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elevDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail check_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainNg_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainOk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainOK_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainNG_mes[2] = {{397}, {396}}; /* derived name */
#else
static ActMail elevMain_mes[2] = {{406, actSt13aElevSwitch}, {429}}; /* derived name */

static ActMail elev_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elevDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail check_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainNg_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainOk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainOK_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainNG_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif
#endif

/* .sdata: the lift and statue stream handles and shakes. */
SqEntry *st13a_up = 0;

SqEntry *st13a_down = 0;

#ifndef VERSION_JUN26
SqEntry *sekizo13a = 0;
#endif

unsigned int st13a_yure = 0;

unsigned char st13a_yure_vol = 0;

int sekizo_13a = 0;

unsigned char sekizo_13a_vol = 0;

#ifdef VERSION_JUN26
void actSt13aElevUp(GObj *volatile self)
{
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(70, &st13a_up, 0, 1, 1);
    while (st13a_up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(138, 1, 0);
    stage_SetAnimation(139, 1, 0);

    while (stage_CheckAnimationFrame(138, 86, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(138, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure = iosPadActRequest(boyPad, 9);
    st13a_yure_vol = 128;
    iosPadActVolumeSet(st13a_yure, 128);

    while (stage_CheckAnimationFrame(138, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure_vol = 64;

    while (stage_CheckAnimationFrame(138, 380, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st13a_yure);
    gflagOn(282);
    RequestStageChange(15, boyGObj, 0, 16.0f, 16.0f);
}

void actSt13aElevDownChk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(73, &st13a_down, 1, 1, 1);
    while (st13a_down == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    stage_SetAnimation(138, 1, 451);
    stage_SetAnimation(140, 1, 0);

    scpPlayPosSet(boyGObj, -4871.0f, -2800.0f, 2699.0f);

    st13a_yure = iosPadActRequest(boyPad, 9);
    st13a_yure_vol = 128;
    iosPadActVolumeSet(st13a_yure, 128);

    while (stage_CheckAnimationFrame(138, 850, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    iosPadActStop(st13a_yure);

    while (stage_CheckAnimationFinish(138) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    gflagOff(15);
}

void actSt13aSekizoChk(GObj *volatile self)
{
    float d[4];

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 83) {
        _ACTWait(1);
    }

    scpSekizouCheckPoint();

    scpAdpcmPlayRequestFunc(21, 0, 1, 1, 1);

    scpBoyControlReadDisable = 1;
    lt_switch_layout(51);

    gflagOn(283);

    _ACTWait(60);

    stage_SetAnimation(141, 1, 0);

    sekizo_13a = iosPadActRequest(boyPad, 9);
    sekizo_13a_vol = 128;
    iosPadActVolumeSet(sekizo_13a, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet(boyGObj, -3688.0f, 3527.0f, 2502.0f);
    scpPlayMot(boyGObj, 0);
    _ACTWait(1);

    sceVu0SubVector(d, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, d);

    scpPlayMot(boyGObj, 253);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    while (stage_CheckAnimationFinish(141) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_13a);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt13aElev(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(282) == 0) {
        stage_SetAnimation(138, 0, 0);

        elev_mes[0].func = actSt13aElevMain;
        act->mail = elev_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt13aElevDown(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(15) != 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(138, 0, 0);
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpPlayStart(boyGObj);
        _ACTWait(10);
        stage_SetAnimation(138, 0, 451);

        elevDown_mes[0].func = actSt13aElevDownChk;
        act->mail = elevDown_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt13aSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(283) == 0) {
        stage_SetAnimation(141, 0, 0);

        sekizo_mes[0].func = actSt13aSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(141, 0, -1);
    }
}

void actSt13aExit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    exit_mes[0].func = actSt13aExitChk;
    act->mail = exit_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt13aCheck(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(284) == 0) {
        check_mes[0].func = actSt13aCheckChk;
        act->mail = check_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt13aElevMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = elevMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13aElevSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    elevSwitch_mes[0].func = actSt13aElevUp;
    sub->mail = elevSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt13aExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 || gflagChk(15) != 0) {
        _ACTWait(1);
    }

    gflagOn(282);
    RequestStageChange(15, boyGObj, 0, 16.0f, 16.0f);
}

void actSt13aCheckChk(GObj *volatile self)
{
    _ACTWait(1);

    CheckPoint();
    gflagOn(284);
}
#else
#ifdef VERSION_AUG6
inline void actSt13aElev(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    static ActMail elev_mes[2] = {{393}, {392}}; /* derived name */

    _ACTWait(1);

    ScpCallCameraSetTarget(4729.0f, 2715.0f, -2504.0f);

    if (gflagChk(295) == 0) {
        stage_SetAnimation(151, 0, 0);

        elev_mes[0].func = actSt13aElevMain;
        act->mail = elev_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

inline void actSt13aElevMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = elevMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

inline void actSt13aElevSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail elevSwitch_mes[2] = {{393}, {392}}; /* derived name */

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    elevSwitch_mes[0].func = actSt13aElevUp;
    sub->mail = elevSwitch_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt13aElevUp(GObj *volatile self)
{
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(75, &st13a_up, 0, 1, 1);
    while (st13a_up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(151, 1, 0);
    stage_SetAnimation(152, 1, 0);

    while (stage_CheckAnimationFrame(151, 86, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(151, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure = iosPadActRequest(boyPad, 9);
    st13a_yure_vol = 128;
    iosPadActVolumeSet(st13a_yure, 128);

    while (stage_CheckAnimationFrame(151, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure_vol = 64;

    while (stage_CheckAnimationFrame(151, 380, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st13a_yure);
    gflagOn(295);
    RequestStageChange(15, boyGObj, 0, 16.0f, 16.0f);
}

inline void actSt13aElevDown(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    static ActMail elevDown_mes[2] = {{393}, {392}}; /* derived name */

    _ACTWait(1);

    if (gflagChk(15) != 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(151, 0, 0);
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpPlayStart(boyGObj);
        _ACTWait(10);
        stage_SetAnimation(151, 0, 451);

        elevDown_mes[0].func = actSt13aElevDownChk;
        act->mail = elevDown_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}
#else
#ifdef VERSION_NTSC
void actSt13aElevUp(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(75, &st13a_up, 0, 1, 0);

    preload(15);

    _ACTWait(60);
    while (st13a_up == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(st13a_up->stream);

    stage_SetAnimation(152, 1, 0);
    stage_SetAnimation(153, 1, 0);

    while (stage_CheckAnimationFrame(152, 86, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(152, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure = iosPadActRequest(boyPad, 9);
    st13a_yure_vol = 128;
    iosPadActVolumeSet(st13a_yure, 128);

    while (stage_CheckAnimationFrame(152, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure_vol = 64;

    while (stage_CheckAnimationFrame(152, 380, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st13a_yure);
    gflagOn(296);
    RequestStageChange(15, boyGObj, 0, 0.025f, 8.0f);
}
#else
static void actSt13aElevUpSub(GObj *volatile self)
{
    AdpcmPlay(st13a_up->stream);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(169, 1, 0);
    stage_SetAnimation(170, 1, 0);
#else
    stage_SetAnimation(173, 1, 0);
    stage_SetAnimation(174, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(169, 86, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(173, 86, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(169, 140, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(173, 140, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure = iosPadActRequest(boyPad, 9);
    st13a_yure_vol = 128;
    iosPadActVolumeSet(st13a_yure, 128);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(169, 200, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(173, 200, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure_vol = 64;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(169, 380, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(173, 380, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt13aElevUp(GObj *volatile self)
{
    GProc *th;

    scpAdpcmPlayRequestFunc(77, &st13a_up, 0, 1, 0);
    while (st13a_up == 0) {
        _ACTWait(1);
    }

    preload(15);

    st13a_yure = -1;
    th = actCreateSubThread(actSt13aElevUpSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st13a_up, 512);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
    }

    iosPadActStop(st13a_yure);
    gflagOn(325);
    RequestStageChange(15, boyGObj, 0, 0.025f, 8.0f);
}
#endif

void actSt13aElevDown(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(15) != 0) {
        scpFadeOut(255.0f, 0, 0, 0);
#ifdef VERSION_NTSC
        stage_SetAnimation(152, 0, 0);
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpPlayStart(boyGObj);
        scpAdpcmPlayRequestFunc(78, &st13a_down, 1, 1, 0);
        _ACTWait(10);
        stage_SetAnimation(152, 0, 451);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(169, 0, 0);
        lt_switch_layout(52);
#else
        stage_SetAnimation(173, 0, 0);
        lt_switch_layout(55);
#endif
        scpBoyControlReadDisable = 1;
        scpPlayStart(boyGObj);
        scpAdpcmPlayRequestFunc(80, &st13a_down, 1, 1, 0);
        _ACTWait(10);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(169, 0, 451);
#else
        stage_SetAnimation(173, 0, 451);
#endif
#endif

        elevDown_mes[0].func = actSt13aElevDownChk;
        act->mail = elevDown_mes;
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 397);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}
#endif

#ifdef VERSION_AUG6
void actSt13aElevDownChk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(78, &st13a_down, 1, 1, 1);
    while (st13a_down == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    stage_SetAnimation(151, 1, 451);
    stage_SetAnimation(153, 1, 0);

    scpPlayPosSet(boyGObj, -4871.0f, -2800.0f, 2699.0f);

    st13a_yure = iosPadActRequest(boyPad, 9);
    st13a_yure_vol = 128;
    iosPadActVolumeSet(st13a_yure, 128);

    while (stage_CheckAnimationFrame(151, 850, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    iosPadActStop(st13a_yure);

    while (stage_CheckAnimationFinish(151) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    gflagOff(15);
}

inline void actSt13aSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    static ActMail sekizo_mes[2] = {{393}, {392}}; /* derived name */

    _ACTWait(1);

    if (gflagChk(296) == 0) {
        stage_SetAnimation(154, 0, 0);

        sekizo_mes[0].func = actSt13aSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(154, 0, -1);
    }
}

void actSt13aSekizoChk(GObj *volatile self)
{
    float d[4];

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           scpActStatusDeathFall(boyGObj) != 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpAdpcmPlayRequestFunc(18, &sekizo13a, 1, 1, 1);
    while (sekizo13a == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(154, 1, 0);

    sekizo_13a = iosPadActRequest(boyPad, 9);
    sekizo_13a_vol = 128;
    iosPadActVolumeSet(sekizo_13a, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet(boyGObj, -3688.0f, 3527.0f, 2502.0f);
    scpPlayMot(boyGObj, 0);
    _ACTWait(1);

    sceVu0SubVector(d, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, d);

    scpSekizouCheckPoint();

    scpPlayMot(boyGObj, 246);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    gflagOn(296);

    while (stage_CheckAnimationFrame(154, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_13a);

    while (stage_CheckAnimationFinish(154) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

inline void actSt13aExit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    static ActMail exit_mes[2] = {{393}, {392}}; /* derived name */

    _ACTWait(1);

    exit_mes[0].func = actSt13aExitChk;
    act->mail = exit_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt13aExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 || gflagChk(15) != 0) {
        _ACTWait(1);
    }

    gflagOn(295);
    RequestStageChange(15, boyGObj, 0, 16.0f, 16.0f);
}

inline void actSt13aCheck(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    static ActMail check_mes[2] = {{393}, {392}}; /* derived name */

    _ACTWait(1);

    if (gflagChk(297) == 0) {
        check_mes[0].func = actSt13aCheckChk;
        act->mail = check_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

inline void actSt13aCheckChk(GObj *volatile self)
{
    _ACTWait(1);

    CheckPoint();
    gflagOn(297);
}

inline void actSt13aChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    static ActMail chainNg_mes[2] = {{393}, {392}}; /* derived name */
    static ActMail chainOk_mes[2] = {{393}, {392}}; /* derived name */

    _ACTWait(1);

    if (gflagChk(298) == 0) {
        chainNg_mes[0].func = actSt13aChainNG;
        act->mail = chainNg_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        chainOk_mes[0].func = actSt13aChainOK;
        act->mail = chainOk_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

inline void actSt13aChainOK(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail chainOK_mes[2] = {{393}, {392}}; /* derived name */

    while (scpTriggerBall(self, scpSearchGobj(1876), 200.0f) != 0) {
        _ACTWait(1);
    }

    EnableChainHang(scpSearchGobj(1875));
    gflagOff(298);

    chainOK_mes[0].func = actSt13aChainNG;
    sub->mail = chainOK_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}
#else
#ifdef VERSION_NTSC
void actSt13aElevDownChk(GObj *volatile self)
{
    while (st13a_down == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(st13a_down->stream);
    scpFadeIn(6.0f);

    stage_SetAnimation(152, 1, 451);
    stage_SetAnimation(154, 1, 0);

    scpPlayPosSet(boyGObj, -4871.0f, -2800.0f, 2699.0f);

    st13a_yure = iosPadActRequest(boyPad, 9);
    st13a_yure_vol = 128;
    iosPadActVolumeSet(st13a_yure, 128);

    while (stage_CheckAnimationFrame(152, 850, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    iosPadActStop(st13a_yure);

    while (stage_CheckAnimationFinish(152) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    gflagOff(15);
}

void actSt13aSekizoChk(GObj *volatile self)
{
    float d[4];

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           scpActStatusDeathFall(boyGObj) != 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpAdpcmPlayRequestFunc(18, &sekizo13a, 1, 1, 1);
    while (sekizo13a == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(155, 1, 0);

    sekizo_13a = iosPadActRequest(boyPad, 9);
    sekizo_13a_vol = 128;
    iosPadActVolumeSet(sekizo_13a, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet(boyGObj, -3688.0f, 3527.0f, 2502.0f);
    scpPlayMot(boyGObj, 0);
    _ACTWait(1);

    sceVu0SubVector(d, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, d);

    scpSekizouCheckPoint();

    scpPlayMot(boyGObj, 246);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    gflagOn(297);

    while (stage_CheckAnimationFrame(155, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_13a);

    while (stage_CheckAnimationFinish(155) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt13aElev(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    ScpCallCameraSetTarget(4729.0f, 2715.0f, -2504.0f);

    if (gflagChk(296) == 0) {
        stage_SetAnimation(152, 0, 0);

        elev_mes[0].func = actSt13aElevMain;
        act->mail = elev_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt13aSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(297) == 0) {
        stage_SetAnimation(155, 0, 0);

        sekizo_mes[0].func = actSt13aSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(155, 0, -1);
    }
}

void actSt13aCheck(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(298) == 0) {
        check_mes[0].func = actSt13aCheckChk;
        act->mail = check_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt13aChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(299) == 0) {
        chainNg_mes[0].func = actSt13aChainNG;
        act->mail = chainNg_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        chainOk_mes[0].func = actSt13aChainOK;
        act->mail = chainOk_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}
#else
static void actSt13aElevDownSub(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(169, 1, 451);
    stage_SetAnimation(171, 1, 0);
#else
    stage_SetAnimation(173, 1, 451);
    stage_SetAnimation(175, 1, 0);
#endif

    scpPlayPosSet(boyGObj, -4871.0f, -2800.0f, 2699.0f);

    st13a_yure = iosPadActRequest(boyPad, 9);
    st13a_yure_vol = 128;
    iosPadActVolumeSet(st13a_yure, 128);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(169, 850, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(173, 850, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    iosPadActStop(st13a_yure);
    st13a_yure = -1;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(169) == 0) {
#else
    while (stage_CheckAnimationFinish(173) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt13aElevDownChk(GObj *volatile self)
{
    GProc *th;

    while (st13a_down == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(st13a_down->stream);
    scpFadeIn(6.0f);

    th = actCreateSubThread(actSt13aElevDownSub, 21);
    demoEnd = 0;
    st13a_yure = -1;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st13a_down, 512);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(171, 0, -1);
        stage_SetAnimation(169, 0, -1);
#else
        stage_SetAnimation(175, 0, -1);
        stage_SetAnimation(173, 0, -1);
#endif
        _ACTWait(2);
        scpPlayPosSet(boyGObj, -4871.0f, 3527.0f, 2699.0f);
        iosPadActStop(st13a_yure);
        scpFadeIn(3.0f);
    }

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
    gflagOff(15);
}

void actSt13aSekizoChk(GObj *volatile self)
{
    float d[4];

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           scpActStatusDeathFall(boyGObj) != 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

    scpAdpcmPlayRequestFunc(18, &sekizo13a, 1, 1, 1);
    while (sekizo13a == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(172, 1, 0);
#else
    stage_SetAnimation(176, 1, 0);
#endif

    sekizo_13a = iosPadActRequest(boyPad, 9);
    sekizo_13a_vol = 128;
    iosPadActVolumeSet(sekizo_13a, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet(boyGObj, -3688.0f, 3527.0f, 2502.0f);
    scpPlayMot(boyGObj, 0);
    _ACTWait(1);

    sceVu0SubVector(d, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, d);

    scpSekizouCheckPoint();

    scpPlayMot(boyGObj, 251);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    gflagOn(326);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(172, 151, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(176, 151, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_13a);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(172) == 0) {
#else
    while (stage_CheckAnimationFinish(176) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
}

void actSt13aElev(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    ScpCallCameraSetTarget(4729.0f, 2715.0f, -2504.0f);

    if (gflagChk(325) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(169, 0, 0);
#else
        stage_SetAnimation(173, 0, 0);
#endif

        elev_mes[0].func = actSt13aElevMain;
        act->mail = elev_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13aSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(326) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(172, 0, 0);
#else
        stage_SetAnimation(176, 0, 0);
#endif

        sekizo_mes[0].func = actSt13aSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(172, 0, -1);
#else
        stage_SetAnimation(176, 0, -1);
#endif
    }
}

void actSt13aCheck(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(327) == 0) {
        check_mes[0].func = actSt13aCheckChk;
        act->mail = check_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13aChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(328) == 0) {
        chainNg_mes[0].func = actSt13aChainNG;
        act->mail = chainNg_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        chainOk_mes[0].func = actSt13aChainOK;
        act->mail = chainOk_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}
#endif

void actSt13aElevMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = elevMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13aElevSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
#ifdef VERSION_NTSC
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;

    elevSwitch_mes[0].func = actSt13aElevUp;
    sub->mail = elevSwitch_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}
#endif

#ifdef VERSION_NTSC
void actSt13aCheckChk(GObj *volatile self)
{
    _ACTWait(1);

    CheckPoint();
    gflagOn(298);
}

void actSt13aChainOK(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1900), 200.0f) != 0) {
        _ACTWait(1);
    }

    EnableChainHang(scpSearchGobj(1899));
    gflagOff(299);

    chainOK_mes[0].func = actSt13aChainNG;
    sub->mail = chainOK_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt13aChainNG(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1900), 200.0f) == 0) {
        _ACTWait(1);
    }

    UnableChainHang(scpSearchGobj(1899));
    gflagOn(299);

    chainNG_mes[0].func = actSt13aChainOK;
    sub->mail = chainNG_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
#else
#ifdef VERSION_AUG6
inline void actSt13aChainNG(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail chainNG_mes[2] = {{393}, {392}}; /* derived name */

    while (scpTriggerBall(self, scpSearchGobj(1876), 200.0f) == 0) {
        _ACTWait(1);
    }

    UnableChainHang(scpSearchGobj(1875));
    gflagOn(298);

    chainNG_mes[0].func = actSt13aChainOK;
    sub->mail = chainNG_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}
#else
void actSt13aCheckChk(GObj *volatile self)
{
    _ACTWait(1);

    CheckPoint();
    gflagOn(327);
}

void actSt13aChainOK(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(2072), 200.0f) != 0) {
        _ACTWait(1);
    }

    EnableChainHang(scpSearchGobj(2071));
    gflagOff(328);

    chainOK_mes[0].func = actSt13aChainNG;
    sub->mail = chainOK_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt13aChainNG(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(2072), 200.0f) == 0) {
        _ACTWait(1);
    }

    UnableChainHang(scpSearchGobj(2071));
    gflagOn(328);

    chainNG_mes[0].func = actSt13aChainOK;
    sub->mail = chainNG_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif
#endif
#endif
