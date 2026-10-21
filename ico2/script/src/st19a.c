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

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec hagurumaPos = {{-642.0f, 2132.0f, -2861.0f, 0.0f}}; /* derived name */

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
void actSt19aOriSwitch(GObj *volatile self);
void actSt19aOriDown(GObj *volatile self);
void actSt19aOriUp(GObj *volatile self);

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
void actSt19aChainSwitch(GObj *volatile self);
void actSt19aChainDown(GObj *volatile self);
void actSt19aChainUp(GObj *volatile self);

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
