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
#include "include_asm.h"

/* This stage's actor mail records. Word 0 of each entry is the mail id the
   entry answers (393 = the actor's own wake-up post, 392 = the trailing
   entry); the handler in .func is installed at run time just before the
   record is posted. The two main-thread records answer their own ids and
   carry their switch handler from the start. Each record is named for the
   actor thread that owns and posts it. */
static ActMail bridgeMain_mes[2] = {{372, actSt20aBridgeSwitch}, {392}}; /* derived name */

static ActMail bridge_mes[2] = {{393}, {392}}; /* derived name */

static ActMail bridgeSwitch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondolaMain_mes[2] = {{373, actSt20aGondolaSwitch}, {392}}; /* derived name */

static ActMail gondola_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondolaSwitchUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondolaSwitchDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondolaDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondolaUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail exit_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fence_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fence2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fenceDownChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fenceUpChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fenceDownChk2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fenceUpChk2_mes[2] = {{393}, {392}}; /* derived name */

void actSt20aInit(void)
{
    if (gflagChk(287) == 0) {
        stage_SetAnimation(127, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(127, 0, -1);
        SetWayGroupActive(4, 1);
    }
}

void actSt20aEnd(void)
{
    if (girlGObj != 0 && gflagChk(287) != 0 && gflagChk(290) == 0) {
        gflagOn(357);
    }
}

void actSt20aBridgeDown(GObj *volatile self)
{
    lt_switch_layout(51);
    scpSleepEnemyAll();
    gflagOn(287);
    gflagOff(357);
    _ACTWait(30);
    scpAdpcmPlayRequestFunc(69, &brg20a, 1, 1, 1);
    while (brg20a == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(127, 1, 0);
    st20a_yure = iosPadActRequest(boyPad, 9);
    st20a_yure_vol = 128;
    iosPadActVolumeSet(st20a_yure, 128);
    while (stage_CheckAnimationFinish(127) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(st20a_yure);
    SetWayGroupActive(4, 1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

/* .sdata: the bridge and gondola stream handles and the shake. */
SqEntry *brg20a = 0;

SqEntry *gondola_up = 0;

SqEntry *gondola_down = 0;

unsigned int st20a_yure = 0;

unsigned char st20a_yure_vol = 0;

void actSt20aGondolaDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    SetGirlDangerGObj(boyGObj);
    scpAdpcmPlayRequestFunc(67, &gondola_down, 1, 1, 1);
    while (gondola_down == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(126, 1, 0);
    gflagOn(288);
    while (stage_CheckAnimationFrame(126, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    while (stage_CheckAnimationFrame(126, 500, 1) == 0) {
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
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt20aGondolaUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(68, &gondola_up, 1, 1, 1);
    while (gondola_up == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(126, 1, 500);
    gflagOff(288);
    while (stage_CheckAnimationFrame(126, 820, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    while (stage_CheckAnimationFrame(126, 1000, 1) == 0) {
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
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt20aFence(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(281) == 0) {
        SetWayGroupActive(19, 1);

        scpSearchGobj(1840)->active = 0;
        scpSearchGobj(1841)->active = 0;

        scpLinkBGAtoLayoutedTarget(1838, 128);
        stage_SetAnimation(128, 0, 30);

        fence_mes[0].func = actSt20aFenceUpChk;
        sub->mail = fence_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        SetWayGroupActive(19, 0);

        scpSearchGobj(1838)->active = 0;
        scpSearchGobj(1839)->active = 0;

        gflagOff(281);

        scpLinkBGAtoLayoutedTarget(1840, 128);
        stage_SetAnimation(128, 0, 0);

        fence2_mes[0].func = actSt20aFenceDownChk2;
        sub->mail = fence2_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt20aFenceDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1838), 5.0f) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(128, 1, 0);
    while (stage_CheckAnimationFrame(128, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(1314, 0, 0, 1);
    while (stage_CheckAnimationFrame(128, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(19, 1);
    gflagOff(292);
    fenceDownChk_mes[0].func = actSt20aFenceUpChk;
    sub->mail = fenceDownChk_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt20aFenceUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1838), 5.0f) != 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(19, 0);
    stage_SetAnimation(128, 1, 31);
    while (stage_CheckAnimationFrame(128, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(1314, 0, 0, 1);
    while (stage_CheckAnimationFinish(128) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(292);
    fenceUpChk_mes[0].func = actSt20aFenceDownChk;
    sub->mail = fenceUpChk_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

INCLUDE_ASM(actSt20aFenceDownChk2);

void actSt20aFenceUpChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1840), 5.0f) != 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(19, 0);
    stage_SetAnimation(128, 1, 31);
    while (stage_CheckAnimationFrame(128, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(1314, 0, 0, 1);
    while (stage_CheckAnimationFinish(128) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(292);
    fenceUpChk2_mes[0].func = actSt20aFenceDownChk2;
    sub->mail = fenceUpChk2_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt20aBridge(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(287) == 0) {
        bridge_mes[0].func = actSt20aBridgeMain;
        sub->mail = bridge_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt20aGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(288) != 0) {
        stage_SetAnimation(126, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(126, 0, 500);
    } else {
        stage_SetAnimation(126, 0, 0);
    }
    gondola_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondola_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt20aExit(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    exit_mes[0].func = actSt20aExitChk;
    sub->mail = exit_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt20aElv(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    if (gflagChk(281) != 0) {
        scpSearchGobj(1838)->active = 0;
        scpSearchGobj(1839)->active = 0;
        gflagOff(281);
    } else {
        scpSearchGobj(1840)->active = 0;
        scpSearchGobj(1841)->active = 0;
    }
}

void actSt20aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(290) == 0) {
        ene_mes[0].func = actSt20aEneChk;
        sub->mail = ene_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt20aEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(291) == 0) {
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

void actSt20aEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(291) == 0) {
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

void actSt20aEnemy3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(291) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
}

/* the actor entry's parameter is its frame home: the thread switch writes it */
void actSt20aBridgeMain(GObj *volatile self)
{
    GOBJ_ACT(self)->mainMail = bridgeMain_mes;
    scpBoyControlReadDisable = 0;
    while (1) {
        _ACTWait(1);
    }
}

void actSt20aBridgeSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;
    bridgeSwitch_mes[0].func = actSt20aBridgeDown;
    sub->mainMail = 0;
    sub->mail = bridgeSwitch_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt20aGondolaMain(GObj *volatile self)
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

void actSt20aGondolaSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    if (gflagChk(288) != 0) {
        gondolaSwitchUp_mes[0].func = actSt20aGondolaUp;
        sub->mail = gondolaSwitchUp_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
    gondolaSwitchDown_mes[0].func = actSt20aGondolaDown;
    sub->mail = gondolaSwitchDown_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt20aExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(289);
    gflagOff(281);
    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        OnGirlEscortFlag();
        RequestStageChange(4, boyGObj, girlGObj, 2.0f, 8.0f);
    }
    RequestStageChange(4, boyGObj, 0, 2.0f, 8.0f);
}

void actSt20aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (gflagChk(287) == 0 || scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(290);
    gflagOn(291);
}
