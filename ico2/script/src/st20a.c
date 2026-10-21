#include "st20a.h"
#include "gamesys.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "boyact.h"
#include "commonact.h"
#include "girl_act.h"
#include "way_llf.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"

/* This stage's actor mail records. Word 0 of each entry is the mail id the
   entry answers (377 = the actor's own wake-up post, 376 = the trailing
   entry); the handler in .func is installed at run time just before the
   record is posted. The two main-thread records answer their own ids and
   carry their switch handler from the start. Each record is named for the
   actor thread that owns and posts it.

   The functions stand in the order of the stage's source as this build has
   it (the layout of this build's st47a.c): the handlers of the bridge, the
   gondola, the exit and the fence first, the actors gathered after them,
   the enemy group last. The ones defined inline are output at the end of
   the file in the order of their first declarations (the entry points in
   st20a.h first); the others where they stand. The tables the actors
   install with actInitialize, the main-mail tables and the switch packets
   are file-scope statics; the ones the gondola and fence handlers install
   through GOBJ_ACT are static locals of their posters (gcc's local name.N
   symbol); .data keeps the source order. */

void actSt20aInit(void)
{
    if (gflagChk(275) == 0) {
        stage_SetAnimation(114, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(114, 0, -1);
        SetWayGroupActive(4, 1);
    }
}

/* .sdata: the gondola stream handles and the bridge's shake with its volume
   (actSt20aBridgeDown); this build has no bridge stream handle. */
SqEntry *gondola_up = 0;

SqEntry *gondola_down = 0;

unsigned int st20a_yure = 0;

unsigned char st20a_yure_vol = 0;

void actSt20aBridgeMain(GObj *volatile self);
void actSt20aBridgeSwitch(GObj *volatile self);
void actSt20aBridgeDown(GObj *volatile self);

static ActMail bridgeMain_mes[2] = {{356, actSt20aBridgeSwitch}, {376}}; /* derived name */

static ActMail bridge_mes[2] = {{377}, {376}}; /* derived name */

static ActMail bridgeSwitch_mes[2] = {{377}, {376}}; /* derived name */

/* the actor entry's parameter is its frame home: the thread switch writes it */
inline void actSt20aBridgeMain(GObj *volatile self)
{
    GOBJ_ACT(self)->mainMail = bridgeMain_mes;
    scpBoyControlReadDisable = 0;
    while (1) {
        _ACTWait(1);
    }
}

inline void actSt20aBridgeSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;
    bridgeSwitch_mes[0].func = actSt20aBridgeDown;
    sub->mainMail = 0;
    sub->mail = bridgeSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt20aBridgeDown(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(275);
    _ACTWait(30);
    scpAdpcmPlayRequestFunc(64, 0, 1, 1, 1);
    _ACTWait(30);
    stage_SetAnimation(114, 1, 0);
    st20a_yure = iosPadActRequest(boyPad, 9);
    st20a_yure_vol = 128;
    iosPadActVolumeSet(st20a_yure, 128);
    while (stage_CheckAnimationFinish(114) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(st20a_yure);
    SetWayGroupActive(4, 1);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt20aGondolaMain(GObj *volatile self);
void actSt20aGondolaSwitch(GObj *volatile self);
void actSt20aGondolaDown(GObj *volatile self);
void actSt20aGondolaUp(GObj *volatile self);

static ActMail gondolaMain_mes[2] = {{357, actSt20aGondolaSwitch}, {376}}; /* derived name */

static ActMail gondola_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondolaSwitchUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondolaSwitchDown_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt20aGondolaMain(GObj *volatile self)
{
    Act *p = GOBJ_ACT(self);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    p->mainMail = gondolaMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

inline void actSt20aGondolaSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    if (gflagChk(276) != 0) {
        gondolaSwitchUp_mes[0].func = actSt20aGondolaUp;
        sub->mail = gondolaSwitchUp_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
    gondolaSwitchDown_mes[0].func = actSt20aGondolaDown;
    sub->mail = gondolaSwitchDown_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt20aGondolaDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail gondolaDown_mes[2] = {{377}, {376}}; /* derived name */

    SetGirlDangerGObj(boyGObj);
    scpAdpcmPlayRequestFunc(62, &gondola_down, 1, 1, 1);
    while (gondola_down == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(113, 1, 0);
    gflagOn(276);
    while (stage_CheckAnimationFrame(113, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    while (stage_CheckAnimationFrame(113, 500, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    if (gondola_down != 0) {
        scpAdpcmFadeClose(gondola_down, 256);
    }
    while (scpAdpcmCloseChk(gondola_down) != 0) {
        _ACTWait(1);
    }
    ClearGirlDangerGObj();
    gondolaDown_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondolaDown_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt20aGondolaUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail gondolaUp_mes[2] = {{377}, {376}}; /* derived name */

    scpAdpcmPlayRequestFunc(63, &gondola_up, 1, 1, 1);
    while (gondola_up == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(113, 1, 500);
    gflagOff(276);
    while (stage_CheckAnimationFrame(113, 820, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    while (stage_CheckAnimationFrame(113, 1000, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    if (gondola_up != 0) {
        scpAdpcmFadeClose(gondola_up, 256);
    }
    while (scpAdpcmCloseChk(gondola_up) != 0) {
        _ACTWait(1);
    }
    gondolaUp_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondolaUp_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail exit_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt20aExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(277);
    gflagOff(270);
    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        RequestStageChange(4, boyGObj, girlGObj, 16.0f, 16.0f);
    }
    RequestStageChange(4, boyGObj, 0, 16.0f, 16.0f);
}

void actSt20aEneChk(GObj *volatile self);

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

void actSt20aFenceDownChk(GObj *volatile self);
void actSt20aFenceUpChk(GObj *volatile self);
void actSt20aFenceDownChk2(GObj *volatile self);
void actSt20aFenceUpChk2(GObj *volatile self);

static ActMail fence_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fence2_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt20aFenceDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail fenceDownChk_mes[2] = {{377}, {376}}; /* derived name */

    while (scpTriggerBall(self, scpSearchGobj(1764), 5.0f) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(115, 1, 0);
    while (stage_CheckAnimationFrame(115, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(19, 1);
    gflagOff(280);
    fenceDownChk_mes[0].func = actSt20aFenceUpChk;
    sub->mail = fenceDownChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt20aFenceUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail fenceUpChk_mes[2] = {{377}, {376}}; /* derived name */

    while (scpTriggerBall(self, scpSearchGobj(1764), 5.0f) != 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(19, 0);
    stage_SetAnimation(115, 1, 31);
    while (stage_CheckAnimationFinish(115) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(280);
    fenceUpChk_mes[0].func = actSt20aFenceDownChk;
    sub->mail = fenceUpChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt20aFenceDownChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail fenceDownChk2_mes[2] = {{377}, {376}}; /* derived name */

    while (scpTriggerBall(self, scpSearchGobj(1766), 5.0f) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(115, 1, 0);
    while (stage_CheckAnimationFrame(115, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(19, 1);
    gflagOff(280);
    fenceDownChk2_mes[0].func = actSt20aFenceUpChk2;
    sub->mail = fenceDownChk2_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt20aFenceUpChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail fenceUpChk2_mes[2] = {{377}, {376}}; /* derived name */

    while (scpTriggerBall(self, scpSearchGobj(1766), 5.0f) != 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(19, 0);
    stage_SetAnimation(115, 1, 31);
    while (stage_CheckAnimationFinish(115) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(280);
    fenceUpChk2_mes[0].func = actSt20aFenceDownChk2;
    sub->mail = fenceUpChk2_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt20aFence(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(270) == 0) {
        SetWayGroupActive(19, 1);

        scpSearchGobj(1766)->active = 0;
        scpSearchGobj(1767)->active = 0;

        scpLinkBGAtoLayoutedTarget(1764, 115);
        stage_SetAnimation(115, 0, 30);

        fence_mes[0].func = actSt20aFenceUpChk;
        sub->mail = fence_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        SetWayGroupActive(19, 0);

        scpSearchGobj(1764)->active = 0;
        scpSearchGobj(1765)->active = 0;

        gflagOff(270);

        scpLinkBGAtoLayoutedTarget(1766, 115);
        stage_SetAnimation(115, 0, 0);

        fence2_mes[0].func = actSt20aFenceDownChk2;
        sub->mail = fence2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt20aBridge(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(275) == 0) {
        bridge_mes[0].func = actSt20aBridgeMain;
        sub->mail = bridge_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt20aGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(276) != 0) {
        stage_SetAnimation(113, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(113, 0, 500);
    } else {
        stage_SetAnimation(113, 0, 0);
    }
    gondola_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondola_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt20aExit(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    exit_mes[0].func = actSt20aExitChk;
    sub->mail = exit_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt20aElv(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    if (gflagChk(270) != 0) {
        scpSearchGobj(1764)->active = 0;
        scpSearchGobj(1765)->active = 0;
        gflagOff(270);
    } else {
        scpSearchGobj(1766)->active = 0;
        scpSearchGobj(1767)->active = 0;
    }
}

inline void actSt20aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(278) == 0) {
        ene_mes[0].func = actSt20aEneChk;
        sub->mail = ene_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt20aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (gflagChk(275) == 0 || scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(278);
    gflagOn(279);
}

inline void actSt20aEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(279) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

inline void actSt20aEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(279) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}
