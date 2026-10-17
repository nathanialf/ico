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

/* .sdata: the fence, gear, pipe and chain stream handles. */
SqEntry *fence_up_19a = 0;

SqEntry *fence_down_19a = 0;

SqEntry *hgrm_19a = 0;

SqEntry *pipe19a = 0;

SqEntry *chain19a = 0;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec hagurumaPos = {{-642.0f, 2132.0f, -2861.0f, 0.0f}}; /* derived name */

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
    if (gflagChk(284) == 0) {
        scpSearchGobj(1793)->active = 0;
        stage_SetAnimation(119, 0, 0);
        haguruma_mes[0].func = actSt19aHagurumaChk;
        sub->mail = haguruma_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        pos2[0] = hagurumaChkPos.d[0];
        pos2[1] = hagurumaChkPos.d[1];
        soundSeDefPlay(1323, 0, (float *)pos2, 1);
        soundSeDefPlay(1324, 0, (float *)pos2, 1);
        soundSeDefPlay(1325, 0, (float *)pos2, 1);
        scpSearchGobj(1794)->active = 0;
        stage_SetAnimation(119, 1, 0);
        stage_SetLoopFlag(119, 1);
        stage_SetLoopFlag(120, 1);
    }
}

void actSt19aHagurumaChk(GObj *volatile self)
{
    long long pos[2];

    while (scpTriggerBall(self, scpSearchGobj(1794), 220.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(284);
    scpAdpcmPlayRequestFunc(74, &hgrm_19a, 1, 1, 1);
    while (hgrm_19a == 0) {
        _ACTWait(1);
    }
    _ACTWait(60);
    stage_SetAnimation(121, 1, 0);
    _ACTWait(90);
    stage_SetAnimation(119, 1, 0);
    stage_SetAnimation(120, 1, 0);
    scpSearchGobj(1794)->active = 0;
    scpSearchGobj(1793)->active = 1;
    stage_SetLoopFlag(119, 1);
    stage_SetLoopFlag(120, 1);
    pos[0] = hagurumaChkPos.d[0];
    pos[1] = hagurumaChkPos.d[1];
    soundSeDefPlay(1323, 0, (float *)pos, 1);
    soundSeDefPlay(1324, 0, (float *)pos, 1);
    soundSeDefPlay(1325, 0, (float *)pos, 1);
    while (stage_CheckAnimationFinish(121) == 0) {
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
    gflagOn(285);
    scpSearchGobj(1791)->active = 0;
    _ACTWait(1);
    scpAdpcmPlayRequestFunc(82, &pipe19a, 1, 1, 1);
    while (pipe19a == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(123, 1, 0);
    FeedbackWallWorkInfoToBrainSystem(boyGObj);
    scpPlayMot(boyGObj, 78);
    _ACTWait(300);
    scpSearchGobj(1792)->active = 1;
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
    stage_SetAnimation(124, 1, 0);
    gflagOn(286);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFrame(124, 240, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(1796)->active = 1;
    stage_SetAnimation(124, 0, 361);
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
    scpSearchGobj(1796)->active = 0;
    stage_SetAnimation(124, 1, 240);
    gflagOff(286);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFrame(124, 359, 1) == 0) {
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
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt19aOri(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    ScpCallCameraSetTarget(4298.0f, -2342.0f, 1331.0f);

    if (gflagChk(283) != 0) {
        stage_SetAnimation(122, 0, 89);
    } else {
        stage_SetAnimation(122, 0, 0);
    }

    ori_mes[0].func = actSt19aOriMain;
    act->mail = ori_mes;
    ACTSendMailCorrect(self, 397);
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

    stage_SetAnimation(122, 0, 0);
}

void actSt19aPipe(GObj *volatile self)
{
    GObj *x = self;

    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(285) == 0) {
        scpSearchGobj(1792)->active = 0;
        stage_SetAnimation(123, 0, 0);

        pipe_mes[0].func = actSt19aPipeChk;
        act->mail = pipe_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);

    } else {
        scpSearchGobj(1791)->active = 0;
        stage_SetAnimation(123, 0, -1);
    }
}

void actSt19aPipeXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(285) == 0) {
        stage_SetAnimation(123, 0, 0);
    } else {
        stage_SetAnimation(123, 0, -1);
    }
}

void actSt19aChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(286) == 0) {
        scpSearchGobj(1796)->active = 0;

        stage_SetAnimation(124, 0, 0);
    }

    chain_mes[0].func = actSt19aChainMain;
    act->mail = chain_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt19bIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(287) == 0) {
        intro_mes[0].func = actSt19bIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt19aOriMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = oriMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt19aOriSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    if (gflagChk(283) != 0) {
        oriSwitch_mes[0].func = actSt19aOriDown;
        sub->mail = oriSwitch_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }

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
}

void actSt19aChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = chainMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt19aChainSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    if (gflagChk(286) == 0) {
        chainSwitch_mes[0].func = actSt19aChainDown;
        sub->mail = chainSwitch_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        chainSwitch2_mes[0].func = actSt19aChainUp;
        sub->mail = chainSwitch2_mes;
        ACTSendMailCorrect(self, 397);
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
    gflagOn(287);
    stage_SetAnimation(117, 1, 0);
    while (stage_CheckAnimationFinish(117) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}
