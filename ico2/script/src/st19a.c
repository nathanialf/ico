#include "st19a.h"
#include "layout_texture.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "camera-root.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "typedef.h"
#include "main.h"
#include "script.h"

#ifndef VERSION_JUN26
#ifdef VERSION_AUG6
/* .data: actor mail packets. */

static ActMail oriMain_mes[2] = {{373, actSt19aOriSwitch}, {392}}; /* derived name */

static ActMail ori_mes[2] = {{393}, {392}}; /* derived name */

static ActMail oriSwitch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail oriSwitch2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail oriDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail haguruma_mes[2] = {{393}, {392}}; /* derived name */

static ActMail pipe_mes[2] = {{393}, {392}}; /* derived name */

static ActMail chainMain_mes[2] = {{372, actSt19aChainSwitch}, {392}}; /* derived name */

static ActMail chain_mes[2] = {{393}, {392}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail chainSwitch2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail chainUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail intro_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_NTSC
/* .data: actor mail packets. */

static ActMail oriMain_mes[2] = {{377, actSt19aOriSwitch}, {396}}; /* derived name */

static ActMail ori_mes[2] = {{397}, {396}}; /* derived name */

static ActMail oriSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail oriSwitch2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail oriDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail haguruma_mes[2] = {{397}, {396}}; /* derived name */

static ActMail pipe_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainMain_mes[2] = {{376, actSt19aChainSwitch}, {396}}; /* derived name */

static ActMail chain_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainSwitch2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */
#else
static void actSt19aChainDownSub(GObj *volatile self);

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for. */
static int demoEnd;

/* .data: actor mail packets. */

static ActMail oriMain_mes[2] = {{407, actSt19aOriSwitch}, {429}}; /* derived name */

static ActMail ori_mes[2] = {{430}, {429}}; /* derived name */

static ActMail oriSwitch_mes[2] = {{430}, {429}}; /* derived name */

static float oriXLPos[4] = {-642.0f, 2132.0f, -2861.0f, 0.0f}; /* derived name */

static float haguruma2Pos[4] = {486.0f, 2386.0f, -2917.0f, 0.0f}; /* derived name */

static ActMail haguruma_mes[2] = {{430}, {429}}; /* derived name */

static ActMail pipe_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainMain_mes[2] = {{406, actSt19aChainSwitch}, {429}}; /* derived name */

static ActMail chain_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{430}, {429}}; /* derived name */
/* .sdata: the fence, horn and pipe stream handles. */
#endif
#endif

SqEntry *fence_up_19a = 0;

SqEntry *fence_down_19a = 0;

SqEntry *hgrm_19a = 0;

SqEntry *pipe19a = 0;

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
SqEntry *chain19a = 0;
#else
void actSt19aOriUp(GObj *volatile self)
{
    int skip = 0;
    int i;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(74, &fence_up_19a, 1, 1, 1);
    while (fence_up_19a == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(138, 1, 0);
#else
    stage_SetAnimation(142, 1, 0);
#endif
    gflagOn(310);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(138, 89, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(142, 89, 1) == 0) {
#endif
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
            scpFadeOut(16.0f, 0, 0, 0);
            scpAdpcmFadeCloseFunc(&fence_up_19a, 512);
            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(138, 0, 89);
#else
            stage_SetAnimation(142, 0, 89);
#endif
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }
    for (i = 120; i-- > 0 && skip == 0;) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
    }
    if (skip == 0) {
        scpAdpcmFadeCloseFunc(&fence_up_19a, 256);
    }
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}
#endif
#endif

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec hagurumaPos = {{-642.0f, 2132.0f, -2861.0f, 0.0f}}; /* derived name */

#ifdef VERSION_AUG6
static const ConstVec hagurumaChkPos = {{486.0f, 2386.0f, -2917.0f, 0.0f}}; /* derived name */

void actSt19aOriDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    lt_switch_layout(51);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(73, &fence_down_19a, 1, 1, 1);
    while (fence_down_19a == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(121, 1, 90);
    gflagOff(282);
    while (stage_CheckAnimationFrame(121, 180, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(120);
    if (fence_down_19a != 0) {
        scpAdpcmFadeClose(fence_down_19a, 256);
    }
    lt_switch_layout(50);
    _ACTWait(60);

    oriDown_mes[0].func = actSt19aOriMain;
    sub->mail = oriDown_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}
#endif

#ifdef VERSION_JUN26
static const ConstVec hagurumaChkPos = {{486.0f, 2386.0f, -2917.0f, 0.0f}}; /* derived name */

/* The functions stand in the order of the stage's source as this build has
   it (the layout of this build's st47a.c and st20a.c): the handlers of each
   gimmick in aug6's order, the actors gathered after them (actSt19aHaguruma,
   not inline, stands before its check as the object's text has it). The
   ones defined inline are output at the end of the file in the order of
   their first declarations (the entry points in st19a.h first); the others
   where they stand. The tables the actors install with actInitialize, the
   main-mail tables and the switch packets are file-scope statics; the ones
   the toggle handlers install through GOBJ_ACT are static locals of their
   posters (gcc's local name.N symbol); .data keeps the source order. The
   two switch packets' mail ids are 356 and 357 (the reverse of PAL's
   order). */

void actSt19aOriMain(GObj *volatile self);
inline void actSt19aOriSwitch(GObj *volatile self);
inline void actSt19aOriDown(GObj *volatile self);
inline void actSt19aOriUp(GObj *volatile self);

static ActMail oriMain_mes[2] = {{356, actSt19aOriSwitch}, {376}}; /* derived name */

static ActMail ori_mes[2] = {{377}, {376}}; /* derived name */

static ActMail oriSwitch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail oriSwitch2_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt19aOriMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = oriMain_mes;

    while (1) {
        _ACTWait(1);
    }
}
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#ifndef VERSION_AUG6
static const ConstVec hagurumaChkPos = {{486.0f, 2386.0f, -2917.0f, 0.0f}}; /* derived name */

void actSt19aOriDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    lt_switch_layout(51);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(73, &fence_down_19a, 1, 1, 1);
    while (fence_down_19a == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(122, 1, 90);
    gflagOff(283);
    while (stage_CheckAnimationFrame(122, 180, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(120);
    if (fence_down_19a != 0) {
        scpAdpcmFadeClose(fence_down_19a, 256);
    }
    lt_switch_layout(50);
    _ACTWait(60);

    oriDown_mes[0].func = actSt19aOriMain;
    sub->mail = oriDown_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
#endif

void actSt19aHaguruma(GObj *volatile self)
{
    long long pos[2];
    long long pos2[2];
    Act *sub;
    GObj *x = self;

    sub = actInitialize(self);
    _ACTWait(1);
    pos[0] = hagurumaPos.d[0];
    pos[1] = hagurumaPos.d[1];
    soundSeDefPlay(1322, 0, (float *)pos, 1);
#ifdef VERSION_AUG6
    if (gflagChk(283) == 0) {
        scpSearchGobj(1777)->active = 0;
        stage_SetAnimation(118, 0, 0);
        haguruma_mes[0].func = actSt19aHagurumaChk;
        sub->mail = haguruma_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(284) == 0) {
        scpSearchGobj(1793)->active = 0;
        stage_SetAnimation(119, 0, 0);
        haguruma_mes[0].func = actSt19aHagurumaChk;
        sub->mail = haguruma_mes;
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);
    } else {
        pos2[0] = hagurumaChkPos.d[0];
        pos2[1] = hagurumaChkPos.d[1];
        soundSeDefPlay(1323, 0, (float *)pos2, 1);
        soundSeDefPlay(1324, 0, (float *)pos2, 1);
        soundSeDefPlay(1325, 0, (float *)pos2, 1);
#ifdef VERSION_AUG6
        scpSearchGobj(1778)->active = 0;
        stage_SetAnimation(118, 1, 0);
        stage_SetLoopFlag(118, 1);
        stage_SetLoopFlag(119, 1);
#else
        scpSearchGobj(1794)->active = 0;
        stage_SetAnimation(119, 1, 0);
        stage_SetLoopFlag(119, 1);
        stage_SetLoopFlag(120, 1);
#endif
    }
}

void actSt19aHagurumaChk(GObj *volatile self)
{
    long long pos[2];

#ifdef VERSION_AUG6
    while (scpTriggerBall(self, scpSearchGobj(1778), 220.0f) == 0) {
#else
    while (scpTriggerBall(self, scpSearchGobj(1794), 220.0f) == 0) {
#endif
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
#ifdef VERSION_AUG6
    gflagOn(283);
#else
    gflagOn(284);
#endif
    scpAdpcmPlayRequestFunc(74, &hgrm_19a, 1, 1, 1);
    while (hgrm_19a == 0) {
        _ACTWait(1);
    }
    _ACTWait(60);
#ifdef VERSION_AUG6
    stage_SetAnimation(120, 1, 0);
    _ACTWait(90);
    stage_SetAnimation(118, 1, 0);
    stage_SetAnimation(119, 1, 0);
    scpSearchGobj(1778)->active = 0;
    scpSearchGobj(1777)->active = 1;
    stage_SetLoopFlag(118, 1);
    stage_SetLoopFlag(119, 1);
#else
    stage_SetAnimation(121, 1, 0);
    _ACTWait(90);
    stage_SetAnimation(119, 1, 0);
    stage_SetAnimation(120, 1, 0);
    scpSearchGobj(1794)->active = 0;
    scpSearchGobj(1793)->active = 1;
    stage_SetLoopFlag(119, 1);
    stage_SetLoopFlag(120, 1);
#endif
    pos[0] = hagurumaChkPos.d[0];
    pos[1] = hagurumaChkPos.d[1];
    soundSeDefPlay(1323, 0, (float *)pos, 1);
    soundSeDefPlay(1324, 0, (float *)pos, 1);
    soundSeDefPlay(1325, 0, (float *)pos, 1);
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(120) == 0) {
#else
    while (stage_CheckAnimationFinish(121) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt19aPipeChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 50.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
#ifdef VERSION_AUG6
    gflagOn(284);
    scpSearchGobj(1775)->active = 0;
#else
    gflagOn(285);
    scpSearchGobj(1791)->active = 0;
#endif
    _ACTWait(1);
    scpAdpcmPlayRequestFunc(82, &pipe19a, 1, 1, 1);
    while (pipe19a == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_AUG6
    stage_SetAnimation(122, 1, 0);
#else
    stage_SetAnimation(123, 1, 0);
#endif
    FeedbackWallWorkInfoToBrainSystem(boyGObj);
    scpPlayMot(boyGObj, 78);
    _ACTWait(300);
#ifdef VERSION_AUG6
    scpSearchGobj(1776)->active = 1;
#else
    scpSearchGobj(1792)->active = 1;
#endif
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt19aChainDown(GObj *volatile self)
{
    lt_switch_layout(51);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(95, &chain19a, 1, 1, 1);
    while (chain19a == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_AUG6
    stage_SetAnimation(123, 1, 0);
    gflagOn(285);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFrame(123, 240, 1) == 0) {
#else
    stage_SetAnimation(124, 1, 0);
    gflagOn(286);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFrame(124, 240, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    scpSearchGobj(1780)->active = 1;
    stage_SetAnimation(123, 0, 361);
#else
    scpSearchGobj(1796)->active = 1;
    stage_SetAnimation(124, 0, 361);
#endif
    if (chain19a != 0) {
        scpAdpcmFadeClose(chain19a, 256);
    }
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt19aChainUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    lt_switch_layout(51);
    _ACTWait(60);
#ifdef VERSION_AUG6
    scpSearchGobj(1780)->active = 0;
    stage_SetAnimation(123, 1, 240);
    gflagOff(285);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFrame(123, 359, 1) == 0) {
#else
    scpSearchGobj(1796)->active = 0;
    stage_SetAnimation(124, 1, 240);
    gflagOff(286);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFrame(124, 359, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    if (chain19a != 0) {
        scpAdpcmFadeClose(chain19a, 256);
    }
    _ACTWait(60);
    lt_switch_layout(50);

    chainUp_mes[0].func = actSt19aChainMain;
    sub->mail = chainUp_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

void actSt19aOri(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    ScpCallCameraSetTarget(4298.0f, -2342.0f, 1331.0f);

#ifdef VERSION_AUG6
    if (gflagChk(282) != 0) {
        stage_SetAnimation(121, 0, 89);
    } else {
        stage_SetAnimation(121, 0, 0);
#else
    if (gflagChk(283) != 0) {
        stage_SetAnimation(122, 0, 89);
    } else {
        stage_SetAnimation(122, 0, 0);
#endif
    }

    ori_mes[0].func = actSt19aOriMain;
    act->mail = ori_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

void actSt19aOriXL(GObj *volatile self)
{
    long long pos[2];
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    pos[0] = hagurumaPos.d[0];
    pos[1] = hagurumaPos.d[1];
    soundSeDefPlay(1322, 0, (float *)pos, 1);

#ifdef VERSION_AUG6
    stage_SetAnimation(121, 0, 0);
#else
    stage_SetAnimation(122, 0, 0);
#endif
}

void actSt19aPipe(GObj *volatile self)
{
    GObj *x = self;

    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(284) == 0) {
        scpSearchGobj(1776)->active = 0;
        stage_SetAnimation(122, 0, 0);
#else
    if (gflagChk(285) == 0) {
        scpSearchGobj(1792)->active = 0;
        stage_SetAnimation(123, 0, 0);
#endif

        pipe_mes[0].func = actSt19aPipeChk;
        act->mail = pipe_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);

    } else {
#ifdef VERSION_AUG6
        scpSearchGobj(1775)->active = 0;
        stage_SetAnimation(122, 0, -1);
#else
        scpSearchGobj(1791)->active = 0;
        stage_SetAnimation(123, 0, -1);
#endif
    }
}

void actSt19aPipeXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(284) == 0) {
        stage_SetAnimation(122, 0, 0);
    } else {
        stage_SetAnimation(122, 0, -1);
#else
    if (gflagChk(285) == 0) {
        stage_SetAnimation(123, 0, 0);
    } else {
        stage_SetAnimation(123, 0, -1);
#endif
    }
}

void actSt19aChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(285) == 0) {
        scpSearchGobj(1780)->active = 0;

        stage_SetAnimation(123, 0, 0);
#else
    if (gflagChk(286) == 0) {
        scpSearchGobj(1796)->active = 0;

        stage_SetAnimation(124, 0, 0);
#endif
    }

    chain_mes[0].func = actSt19aChainMain;
    act->mail = chain_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

void actSt19bIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(286) == 0) {
        intro_mes[0].func = actSt19bIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(287) == 0) {
        intro_mes[0].func = actSt19bIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);
    }
}
#else
void actSt19aHaguruma(GObj *volatile self)
{
    long long pos[2];
    Act *sub;
    GObj *x = self;

    sub = actInitialize(self);
    _ACTWait(1);
    pos[0] = hagurumaPos.d[0];
    pos[1] = hagurumaPos.d[1];
    soundSeDefPlay(1349, 0, (float *)pos, 1);
    if (gflagChk(311) == 0) {
        scpSearchGobj(1960)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(135, 0, 0);
        stage_SetAnimation(136, -1, -2);
#else
        stage_SetAnimation(139, 0, 0);
        stage_SetAnimation(140, -1, -2);
#endif
        haguruma_mes[0].func = actSt19aHagurumaChk;
        sub->mail = haguruma_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        soundSeDefPlay(1350, 0, haguruma2Pos, 1);
        soundSeDefPlay(1351, 0, haguruma2Pos, 1);
        soundSeDefPlay(1352, 0, haguruma2Pos, 1);
        scpSearchGobj(1961)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(135, 1, 0);
        stage_SetLoopFlag(135, 1);
        stage_SetLoopFlag(136, 1);
#else
        stage_SetAnimation(139, 1, 0);
        stage_SetLoopFlag(139, 1);
        stage_SetLoopFlag(140, 1);
#endif
    }
}

void actSt19aHagurumaChk(GObj *volatile self)
{
    int skip = 0;
    int i;

    while (scpTriggerBall(self, scpSearchGobj(1961), 220.0f) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    gflagOn(311);
    scpAdpcmPlayRequestFunc(76, &fence_down_19a, 1, 1, 1);
    while (fence_down_19a == 0) {
        _ACTWait(1);
    }
    for (i = 60; i-- > 0 && skip == 0;) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(137, 1, 0);
#else
    stage_SetAnimation(141, 1, 0);
#endif
    for (i = 90; i-- > 0 && skip == 0;) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
    }
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(135, 1, 0);
    stage_SetAnimation(136, 1, 0);
#else
    stage_SetAnimation(139, 1, 0);
    stage_SetAnimation(140, 1, 0);
#endif
    scpSearchGobj(1961)->active = 0;
    scpSearchGobj(1960)->active = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetLoopFlag(135, 1);
    stage_SetLoopFlag(136, 1);
#else
    stage_SetLoopFlag(139, 1);
    stage_SetLoopFlag(140, 1);
#endif
    soundSeDefPlay(1350, 0, haguruma2Pos, 1);
    soundSeDefPlay(1351, 0, haguruma2Pos, 1);
    soundSeDefPlay(1352, 0, haguruma2Pos, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(137) == 0) {
#else
    while (stage_CheckAnimationFinish(141) == 0) {
#endif
        if (((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) || skip != 0) {
            scpFadeOut(16.0f, 0, 0, 0);
            scpAdpcmFadeCloseFunc(&fence_down_19a, 512);
            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(137, 0, -1);
#else
            stage_SetAnimation(141, 0, -1);
#endif
            scpFadeIn(3.0f);
            scpBoyControlReadDisable = 0;
            goto done;
        }
        _ACTWait(1);
    }
    scpBoyControlReadDisable = 0;
done:
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}

void actSt19aPipeChk(GObj *volatile self)
{
    int i;

    while (scpTriggerBall(self, boyGObj, 50.0f) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    gflagOn(312);
    scpSearchGobj(1958)->active = 0;
    _ACTWait(1);
    scpAdpcmPlayRequestFunc(84, &hgrm_19a, 1, 1, 1);
    while (hgrm_19a == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(139, 1, 0);
#else
    stage_SetAnimation(143, 1, 0);
#endif
    FeedbackWallWorkInfoToBrainSystem(boyGObj);
    scpPlayMot(boyGObj, 78);
    for (i = 300; i-- > 0;) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);
            scpAdpcmFadeCloseFunc(&hgrm_19a, 512);
            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(139, 0, -1);
#else
            stage_SetAnimation(143, 0, -1);
#endif
            scpPlayPosSet(boyGObj, 336.0f, 3933.0f, -402.0f);
            _ACTWait(4);
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }
    scpSearchGobj(1959)->active = 1;
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}

void actSt19aChainDown(GObj *volatile self)
{
    GProc *th;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpAdpcmPlayRequestFunc(97, &pipe19a, 1, 1, 0);
    th = actCreateSubThread(actSt19aChainDownSub, 21);
    demoEnd = 0;
    while (demoEnd == 0) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            break;
        }
        _ACTWait(1);
    }
    iosThreadSetPri(&th->thread, 34);
    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        SetCameraFlag_LwsCutBack();
        scpFadeIn(3.0f);
    }
    scpSearchGobj(1963)->active = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(140, 0, 361);
#else
    stage_SetAnimation(144, 0, 361);
#endif
    if (pipe19a != 0) {
        scpAdpcmFadeCloseFunc(&pipe19a, 256);
    }
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}

void actSt19bIntro(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    if (gflagChk(314) == 0) {
        while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
            _ACTWait(1);
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        lt_switch_layout(52);
#else
        lt_switch_layout(55);
#endif
        scpBoyControlReadDisable = 1;
        gflagOn(314);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(133, 1, 0);
        while (stage_CheckAnimationFinish(133) == 0) {
#else
        stage_SetAnimation(137, 1, 0);
        while (stage_CheckAnimationFinish(137) == 0) {
#endif
            if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                stage_SetAnimation(133, 0, -1);
#else
                stage_SetAnimation(137, 0, -1);
#endif
                scpFadeIn(3.0f);
                break;
            }
            _ACTWait(1);
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        lt_switch_layout(51);
#else
        lt_switch_layout(54);
#endif
        scpBoyControlReadDisable = 0;
    }
}

void actSt19aOri(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    ScpCallCameraSetTarget(4298.0f, -2342.0f, 1331.0f);

    if (gflagChk(310) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(138, 0, 0);
#else
        stage_SetAnimation(142, 0, 0);
#endif

        ori_mes[0].func = actSt19aOriMain;
        act->mail = ori_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(138, 0, 89);
#else
        stage_SetAnimation(142, 0, 89);
#endif
    }
}

void actSt19aOriXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    soundSeDefPlay(1349, 0, oriXLPos, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(138, 0, 0);
#else
    stage_SetAnimation(142, 0, 0);
#endif
}

void actSt19aPipe(GObj *volatile self)
{
    GObj *x = self;

    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(312) == 0) {
        scpSearchGobj(1959)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(139, 0, 0);
#else
        stage_SetAnimation(143, 0, 0);
#endif

        pipe_mes[0].func = actSt19aPipeChk;
        act->mail = pipe_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);

    } else {
        scpSearchGobj(1958)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(139, 0, -1);
#else
        stage_SetAnimation(143, 0, -1);
#endif
    }
}

void actSt19aPipeXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(312) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(139, 0, 0);
#else
        stage_SetAnimation(143, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(139, 0, -1);
#else
        stage_SetAnimation(143, 0, -1);
#endif
    }
}

void actSt19aChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(313) == 0) {
        scpSearchGobj(1963)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(140, 0, 0);
#else
        stage_SetAnimation(144, 0, 0);
#endif

        chain_mes[0].func = actSt19aChainMain;
        act->mail = chain_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}
#endif

void actSt19aOriMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = oriMain_mes;

    while (1) {
        _ACTWait(1);
    }
}
#endif

#ifdef VERSION_JUN26
inline void actSt19aOriSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    if (gflagChk(271) != 0) {
        oriSwitch_mes[0].func = actSt19aOriDown;
        sub->mail = oriSwitch_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }

    oriSwitch2_mes[0].func = actSt19aOriUp;
    sub->mail = oriSwitch2_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}
#else
void actSt19aOriSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)

#ifdef VERSION_AUG6
    if (gflagChk(282) != 0) {
        oriSwitch_mes[0].func = actSt19aOriDown;
        sub->mail = oriSwitch_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
#else
    if (gflagChk(283) != 0) {
        oriSwitch_mes[0].func = actSt19aOriDown;
        sub->mail = oriSwitch_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
#endif

#ifdef VERSION_AUG6
    oriSwitch2_mes[0].func = actSt19aOriUp;
    sub->mail = oriSwitch2_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt19aOriUp(GObj *volatile self)
{
    lt_switch_layout(51);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(72, &fence_up_19a, 1, 1, 1);
    while (fence_up_19a == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(121, 1, 0);
    gflagOn(282);
    while (stage_CheckAnimationFrame(121, 89, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(120);
    if (fence_up_19a != 0) {
        scpAdpcmFadeClose(fence_up_19a, 256);
    }
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
#else
    oriSwitch2_mes[0].func = actSt19aOriUp;
    sub->mail = oriSwitch2_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt19aOriUp(GObj *volatile self)
{
    lt_switch_layout(51);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(72, &fence_up_19a, 1, 1, 1);
    while (fence_up_19a == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(122, 1, 0);
    gflagOn(283);
    while (stage_CheckAnimationFrame(122, 89, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(120);
    if (fence_up_19a != 0) {
        scpAdpcmFadeClose(fence_up_19a, 256);
    }
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
#endif
#else
    oriSwitch_mes[0].func = actSt19aOriUp;
    sub->mail = oriSwitch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
#endif
}
#endif

#ifdef VERSION_JUN26
inline void actSt19aOriDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail oriDown_mes[2] = {{377}, {376}}; /* derived name */

    lt_switch_layout(51);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(68, 0, 1, 1, 1);
    stage_SetAnimation(108, 1, 90);
    gflagOff(271);
    while (stage_CheckAnimationFrame(108, 180, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(60);
    lt_switch_layout(50);

    oriDown_mes[0].func = actSt19aOriMain;
    sub->mail = oriDown_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt19aOriUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail oriUp_mes[2] = {{377}, {376}}; /* derived name */

    lt_switch_layout(51);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(67, 0, 1, 1, 1);
    stage_SetAnimation(108, 1, 0);
    gflagOn(271);
    while (stage_CheckAnimationFrame(108, 89, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(60);
    lt_switch_layout(50);

    oriUp_mes[0].func = actSt19aOriMain;
    sub->mail = oriUp_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt19aHagurumaChk(GObj *volatile self);

static ActMail haguruma_mes[2] = {{377}, {376}}; /* derived name */

void actSt19aHaguruma(GObj *volatile self)
{
    long long pos[2];
    long long pos2[2];
    Act *sub;
    GObj *x = self;

    sub = actInitialize(self);
    _ACTWait(1);
    pos[0] = hagurumaPos.d[0];
    pos[1] = hagurumaPos.d[1];
    soundSeDefPlay(1293, 0, (float *)pos, 1);
    if (gflagChk(272) == 0) {
        scpSearchGobj(1705)->active = 0;
        stage_SetAnimation(105, 0, 0);
        haguruma_mes[0].func = actSt19aHagurumaChk;
        sub->mail = haguruma_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        pos2[0] = hagurumaChkPos.d[0];
        pos2[1] = hagurumaChkPos.d[1];
        soundSeDefPlay(1294, 0, (float *)pos2, 1);
        soundSeDefPlay(1295, 0, (float *)pos2, 1);
        soundSeDefPlay(1296, 0, (float *)pos2, 1);
        scpSearchGobj(1706)->active = 0;
        stage_SetAnimation(105, 1, 0);
        stage_SetLoopFlag(105, 1);
        stage_SetLoopFlag(106, 1);
    }
}

void actSt19aHagurumaChk(GObj *volatile self)
{
    long long pos[2];

    while (scpTriggerBall(self, scpSearchGobj(1706), 50.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(272);
    scpAdpcmPlayRequestFunc(69, 0, 1, 1, 1);
    _ACTWait(60);
    stage_SetAnimation(107, 1, 0);
    _ACTWait(90);
    stage_SetAnimation(105, 1, 0);
    stage_SetAnimation(106, 1, 0);
    scpSearchGobj(1706)->active = 0;
    scpSearchGobj(1705)->active = 1;
    stage_SetLoopFlag(105, 1);
    stage_SetLoopFlag(106, 1);
    pos[0] = hagurumaChkPos.d[0];
    pos[1] = hagurumaChkPos.d[1];
    soundSeDefPlay(1294, 0, (float *)pos, 1);
    soundSeDefPlay(1295, 0, (float *)pos, 1);
    soundSeDefPlay(1296, 0, (float *)pos, 1);
    while (stage_CheckAnimationFinish(107) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

static ActMail pipe_mes[2] = {{377}, {376}}; /* derived name */

void actSt19aPipeChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 50.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    gflagOn(273);
    scpSearchGobj(1703)->active = 0;
    _ACTWait(1);
    scpAdpcmPlayRequestFunc(77, 0, 1, 1, 1);
    stage_SetAnimation(109, 1, 0);
    FeedbackWallWorkInfoToBrainSystem(boyGObj);
    scpPlayMot(boyGObj, 86);
    _ACTWait(300);
    scpSearchGobj(1704)->active = 1;
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt19aChainMain(GObj *volatile self);
inline void actSt19aChainSwitch(GObj *volatile self);
void actSt19aChainDown(GObj *volatile self);
inline void actSt19aChainUp(GObj *volatile self);

static ActMail chainMain_mes[2] = {{357, actSt19aChainSwitch}, {376}}; /* derived name */

static ActMail chain_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chainSwitch2_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt19aChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = chainMain_mes;

    while (1) {
        _ACTWait(1);
    }
}
#else
void actSt19aChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = chainMain_mes;

    while (1) {
        _ACTWait(1);
    }
}
#endif

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt19aChainSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

#ifdef VERSION_AUG6
    if (gflagChk(285) == 0) {
        chainSwitch_mes[0].func = actSt19aChainDown;
        sub->mail = chainSwitch_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(286) == 0) {
        chainSwitch_mes[0].func = actSt19aChainDown;
        sub->mail = chainSwitch_mes;
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);
    } else {
        chainSwitch2_mes[0].func = actSt19aChainUp;
        sub->mail = chainSwitch2_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);
    }
}

void actSt19bIntroChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
#ifdef VERSION_AUG6
    gflagOn(286);
    stage_SetAnimation(116, 1, 0);
    while (stage_CheckAnimationFinish(116) == 0) {
#else
    gflagOn(287);
    stage_SetAnimation(117, 1, 0);
    while (stage_CheckAnimationFinish(117) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}
#else
#ifdef VERSION_JUN26
inline void actSt19aChainSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    if (gflagChk(274) == 0) {
        chainSwitch_mes[0].func = actSt19aChainDown;
        sub->mail = chainSwitch_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        chainSwitch2_mes[0].func = actSt19aChainUp;
        sub->mail = chainSwitch2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt19aChainDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail chainDown_mes[2] = {{377}, {376}}; /* derived name */

    lt_switch_layout(51);
    _ACTWait(60);
    stage_SetAnimation(110, 1, 0);
    gflagOn(274);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFrame(110, 240, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(1708)->active = 1;
    stage_SetAnimation(110, 0, 361);
    _ACTWait(60);
    lt_switch_layout(50);

    chainDown_mes[0].func = actSt19aChainMain;
    sub->mail = chainDown_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}
#else
void actSt19aChainSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    if (gflagChk(313) == 0) {
        chainSwitch_mes[0].func = actSt19aChainDown;
        sub->mail = chainSwitch_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

static void actSt19aChainDownSub(GObj *volatile self)
{
    _ACTWait(60);

    while (pipe19a == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(pipe19a->stream);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(140, 1, 0);
#else
    stage_SetAnimation(144, 1, 0);
#endif

    gflagOn(313);

    SetCameraFlag_LwsCutBack();

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(140, 240, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(144, 240, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(60);
}
#endif
#endif

#ifdef VERSION_JUN26
inline void actSt19aChainUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail chainUp_mes[2] = {{377}, {376}}; /* derived name */

    lt_switch_layout(51);
    _ACTWait(60);
    scpSearchGobj(1708)->active = 0;
    stage_SetAnimation(110, 1, 240);
    gflagOff(274);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFrame(110, 359, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(60);
    lt_switch_layout(50);

    chainUp_mes[0].func = actSt19aChainMain;
    sub->mail = chainUp_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt19aOri(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(271) != 0) {
        stage_SetAnimation(108, 0, 89);
    } else {
        stage_SetAnimation(108, 0, 0);
    }

    ori_mes[0].func = actSt19aOriMain;
    act->mail = ori_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt19aOriXL(GObj *volatile self)
{
    long long pos[2];
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    pos[0] = hagurumaPos.d[0];
    pos[1] = hagurumaPos.d[1];
    soundSeDefPlay(1293, 0, (float *)pos, 1);

    stage_SetAnimation(108, 0, 0);
}

inline void actSt19aPipe(GObj *volatile self)
{
    GObj *x = self;

    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(273) == 0) {
        scpSearchGobj(1704)->active = 0;
        stage_SetAnimation(109, 0, 0);

        pipe_mes[0].func = actSt19aPipeChk;
        act->mail = pipe_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);

    } else {
        scpSearchGobj(1703)->active = 0;
        stage_SetAnimation(109, 0, -1);
    }
}

inline void actSt19aPipeXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(273) == 0) {
        stage_SetAnimation(109, 0, 0);
    } else {
        stage_SetAnimation(109, 0, -1);
    }
}

inline void actSt19aChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(274) == 0) {
        scpSearchGobj(1708)->active = 0;

        stage_SetAnimation(110, 0, 0);
    }

    chain_mes[0].func = actSt19aChainMain;
    act->mail = chain_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}
#endif
