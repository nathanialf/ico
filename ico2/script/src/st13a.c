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
#include <libvu0.h>
#include "typedef.h"
#include "main.h"

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

/* .sdata: the lift and statue stream handles and shakes. */
SqEntry *st13a_up = 0;

SqEntry *st13a_down = 0;

SqEntry *sekizo13a = 0;

unsigned int st13a_yure = 0;

unsigned char st13a_yure_vol = 0;

int sekizo_13a = 0;

unsigned char sekizo_13a_vol = 0;

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
