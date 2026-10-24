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

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
static void actSt20aBridgeDownSub(GObj *volatile self);
static void actSt20aGirlPosChk(GObj *volatile self);
static void actSt20aHint1Chk(GObj *volatile self);
#endif

/* This stage's actor mail records. Word 0 of each entry is the mail id the
   entry answers (430 = the actor's own wake-up post, 429 = the trailing
   entry); the handler in .func is installed at run time just before the
   record is posted. The two main-thread records answer their own ids and
   carry their switch handler from the start. Each record is named for the
   actor thread that owns and posts it. */
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#ifdef VERSION_AUG6
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
#else
static ActMail bridgeMain_mes[2] = {{376, actSt20aBridgeSwitch}, {396}}; /* derived name */

static ActMail bridge_mes[2] = {{397}, {396}}; /* derived name */

static ActMail bridgeSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaMain_mes[2] = {{377, actSt20aGondolaSwitch}, {396}}; /* derived name */

static ActMail gondola_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaSwitchUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaSwitchDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail exit_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fenceDownChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fenceUpChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fenceDownChk2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fenceUpChk2_mes[2] = {{397}, {396}}; /* derived name */
#endif

void actSt20aInit(void)
{
#ifdef VERSION_AUG6
    if (gflagChk(287) == 0) {
        stage_SetAnimation(127, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(127, 0, -1);
#else
    if (gflagChk(288) == 0) {
        stage_SetAnimation(128, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(128, 0, -1);
#endif
        SetWayGroupActive(4, 1);
    }
}

void actSt20aEnd(void)
{
#ifdef VERSION_AUG6
    if (girlGObj != 0 && gflagChk(287) != 0 && gflagChk(290) == 0) {
        gflagOn(357);
#else
    if (girlGObj != 0 && gflagChk(288) != 0 && gflagChk(291) == 0) {
        gflagOn(358);
#endif
    }
}

void actSt20aBridgeDown(GObj *volatile self)
{
    lt_switch_layout(51);
    scpSleepEnemyAll();
#ifdef VERSION_AUG6
    gflagOn(287);
    gflagOff(357);
#else
    gflagOn(288);
    gflagOff(358);
#endif
    _ACTWait(30);
    scpAdpcmPlayRequestFunc(69, &brg20a, 1, 1, 1);
    while (brg20a == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_AUG6
    stage_SetAnimation(127, 1, 0);
#else
    stage_SetAnimation(128, 1, 0);
#endif
    st20a_yure = iosPadActRequest(boyPad, 9);
    st20a_yure_vol = 128;
    iosPadActVolumeSet(st20a_yure, 128);
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(127) == 0) {
#else
    while (stage_CheckAnimationFinish(128) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(st20a_yure);
    SetWayGroupActive(4, 1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
#else
static ActMail bridgeMain_mes[2] = {{406, actSt20aBridgeSwitch}, {429}}; /* derived name */

static ActMail bridge_mes[2] = {{430}, {429}}; /* derived name */

static ActMail bridgeSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaMain_mes[2] = {{407, actSt20aGondolaSwitch}, {429}}; /* derived name */

static ActMail gondola_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaSwitchUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaSwitchDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail exit_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fence_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fence2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fenceDownChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fenceUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fenceDownChk2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fenceUpChk2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlPos_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1_mes[2] = {{430}, {429}}; /* derived name */

void actSt20aInit(void)
{
    if (gflagChk(315) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(144, 0, 0);
#else
        stage_SetAnimation(148, 0, 0);
#endif
        SetWayGroupActive(4, 0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(144, 0, -1);
#else
        stage_SetAnimation(148, 0, -1);
#endif
        SetWayGroupActive(4, 1);
    }
}

void actSt20aEnd(void)
{
    if (girlGObj != 0 && gflagChk(315) != 0 && gflagChk(318) == 0) {
        gflagOn(391);
    }
    gamesysObjInfoCls(scpSearchGobj(2025)->kind, scpSearchGobj(2025)->labelId);
    gamesysObjInfoCls(scpSearchGobj(2023)->kind, scpSearchGobj(2023)->labelId);
}

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for. */
static int demoEnd;
#endif

/* .sdata: the bridge and gondola stream handles and the shake. */
SqEntry *brg20a = 0;

SqEntry *gondola_up = 0;

SqEntry *gondola_down = 0;

unsigned int st20a_yure = 0;

unsigned char st20a_yure_vol = 0;

#ifdef VERSION_NTSC
void actSt20aGondolaDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    SetGirlDangerGObj(boyGObj);
    scpAdpcmPlayRequestFunc(67, &gondola_down, 1, 1, 1);
    while (gondola_down == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(127, 1, 0);
    gflagOn(289);
    while (stage_CheckAnimationFrame(127, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    while (stage_CheckAnimationFrame(127, 500, 1) == 0) {
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
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt20aGondolaUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(68, &gondola_up, 1, 1, 1);
    while (gondola_up == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(127, 1, 500);
    gflagOff(289);
    while (stage_CheckAnimationFrame(127, 820, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    while (stage_CheckAnimationFrame(127, 1000, 1) == 0) {
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
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt20aFence(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(282) == 0) {
        SetWayGroupActive(19, 1);

        scpSearchGobj(1856)->active = 0;
        scpSearchGobj(1857)->active = 0;

        scpSearchGobj(1862)->active = 0;
        scpSearchGobj(1863)->active = 0;
        scpSearchGobj(1864)->active = 0;
        scpSearchGobj(1865)->active = 0;

        scpSearchGobj(1858)->active = 0;
        scpSearchGobj(1859)->active = 0;
        scpSearchGobj(1860)->active = 0;
        scpSearchGobj(1861)->active = 0;

        scpLinkBGAtoLayoutedTarget(1854, 129);
        stage_SetAnimation(129, 0, 30);

        fence_mes[0].func = actSt20aFenceUpChk;
        sub->mail = fence_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        SetWayGroupActive(19, 0);

        scpSearchGobj(1854)->active = 0;
        scpSearchGobj(1855)->active = 0;

        scpSearchGobj(1858)->active = 0;
        scpSearchGobj(1859)->active = 0;
        scpSearchGobj(1860)->active = 0;
        scpSearchGobj(1861)->active = 0;

        gflagOff(282);

        scpLinkBGAtoLayoutedTarget(1856, 129);
        stage_SetAnimation(129, 0, 0);

        fence2_mes[0].func = actSt20aFenceDownChk2;
        sub->mail = fence2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt20aFenceDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1854), 5.0f) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(129, 1, 0);
    while (stage_CheckAnimationFrame(129, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(1314, 0, 0, 1);
    while (stage_CheckAnimationFrame(129, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(19, 1);
    scpSearchGobj(1858)->active = 0;
    scpSearchGobj(1859)->active = 0;
    scpSearchGobj(1860)->active = 0;
    scpSearchGobj(1861)->active = 0;
    gflagOff(293);
    fenceDownChk_mes[0].func = actSt20aFenceUpChk;
    sub->mail = fenceDownChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt20aFenceUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1854), 5.0f) != 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(19, 0);
    stage_SetAnimation(129, 1, 31);
    while (stage_CheckAnimationFrame(129, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(1314, 0, 0, 1);
    while (stage_CheckAnimationFinish(129) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(1858)->active = 1;
    scpSearchGobj(1859)->active = 1;
    scpSearchGobj(1860)->active = 1;
    scpSearchGobj(1861)->active = 1;
    gflagOn(293);
    fenceUpChk_mes[0].func = actSt20aFenceDownChk;
    sub->mail = fenceUpChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt20aFenceDownChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1856), 5.0f) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(129, 1, 0);
    while (stage_CheckAnimationFrame(129, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(1314, 0, 0, 1);
    while (stage_CheckAnimationFrame(129, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(1862)->active = 0;
    scpSearchGobj(1863)->active = 0;
    scpSearchGobj(1864)->active = 0;
    scpSearchGobj(1865)->active = 0;
    SetWayGroupActive(19, 1);
    gflagOff(293);
    fenceDownChk2_mes[0].func = actSt20aFenceUpChk2;
    sub->mail = fenceDownChk2_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt20aFenceUpChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1856), 5.0f) != 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(19, 0);
    stage_SetAnimation(129, 1, 31);
    while (stage_CheckAnimationFrame(129, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(1314, 0, 0, 1);
    while (stage_CheckAnimationFinish(129) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(1862)->active = 1;
    scpSearchGobj(1863)->active = 1;
    scpSearchGobj(1864)->active = 1;
    scpSearchGobj(1865)->active = 1;
    gflagOn(293);
    fenceUpChk2_mes[0].func = actSt20aFenceDownChk2;
    sub->mail = fenceUpChk2_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt20aBridge(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(288) == 0) {
        bridge_mes[0].func = actSt20aBridgeMain;
        sub->mail = bridge_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt20aGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(289) != 0) {
        stage_SetAnimation(127, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(127, 0, 500);
    } else {
        stage_SetAnimation(127, 0, 0);
    }
    gondola_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondola_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
#else
#ifndef VERSION_AUG6
void actSt20aBridgeDown(GObj *volatile self)
{
    GProc *th;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpSleepEnemyAll();
    gflagOn(315);
    gflagOff(391);
    st20a_yure = 0xFFFFFFFF;
    demoEnd = 0;
    scpAdpcmPlayRequestFunc(71, &brg20a, 1, 1, 0);
    th = actCreateSubThread(actSt20aBridgeDownSub, 21);
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    iosThreadSetPri(&th->thread, 34);
    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (brg20a == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc(&brg20a, 512);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(144, 0, -1);
#else
        stage_SetAnimation(148, 0, -1);
#endif
        scpFadeIn(3.0f);
    }
    iosPadActStop(st20a_yure);
    SetWayGroupActive(4, 1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}
#endif

void actSt20aGondolaDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    SetGirlDangerGObj(boyGObj);
#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(67, &gondola_down, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(69, &gondola_down, 1, 1, 1);
#endif
    while (gondola_down == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_AUG6
    stage_SetAnimation(126, 1, 0);
    gflagOn(288);
    while (stage_CheckAnimationFrame(126, 150, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(143, 1, 0);
#else
    stage_SetAnimation(147, 1, 0);
#endif
    gflagOn(316);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(143, 150, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(147, 150, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(143, 500, 1) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(126, 500, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(147, 500, 1) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    if (gondola_down != 0) {
#ifdef VERSION_AUG6
        scpAdpcmFadeClose(gondola_down, 256);
    }
    while (scpAdpcmCloseChk(gondola_down) != 0) {
#else
        scpAdpcmFadeCloseFunc(&gondola_down, 256);
    }
    while (scpAdpcmCloseChkFunc(&gondola_down) != 0) {
#endif
        _ACTWait(1);
    }
    ClearGirlDangerGObj();
    gondolaDown_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondolaDown_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt20aGondolaUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(68, &gondola_up, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(70, &gondola_up, 1, 1, 1);
#endif
    while (gondola_up == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_AUG6
    stage_SetAnimation(126, 1, 500);
    gflagOff(288);
    while (stage_CheckAnimationFrame(126, 820, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(143, 1, 500);
#else
    stage_SetAnimation(147, 1, 500);
#endif
    gflagOff(316);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(143, 820, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(147, 820, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(143, 1000, 1) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(126, 1000, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(147, 1000, 1) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    if (gondola_up != 0) {
#ifdef VERSION_AUG6
        scpAdpcmFadeClose(gondola_up, 256);
    }
    while (scpAdpcmCloseChk(gondola_up) != 0) {
#else
        scpAdpcmFadeCloseFunc(&gondola_up, 256);
    }
    while (scpAdpcmCloseChkFunc(&gondola_up) != 0) {
#endif
        _ACTWait(1);
    }
    gondolaUp_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondolaUp_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt20aFence(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
#ifdef VERSION_AUG6
    if (gflagChk(281) == 0) {
        SetWayGroupActive(19, 1);

        scpSearchGobj(1840)->active = 0;
        scpSearchGobj(1841)->active = 0;

        scpLinkBGAtoLayoutedTarget(1838, 128);
        stage_SetAnimation(128, 0, 30);
#else
    if (gflagChk(309) == 0) {
        SetWayGroupActive(19, 1);

        scpSearchGobj(2024)->active = 0;
        scpSearchGobj(2025)->active = 0;

        scpSearchGobj(2030)->active = 0;
        scpSearchGobj(2031)->active = 0;
        scpSearchGobj(2032)->active = 0;
        scpSearchGobj(2033)->active = 0;

        scpSearchGobj(2026)->active = 0;
        scpSearchGobj(2027)->active = 0;
        scpSearchGobj(2028)->active = 0;
        scpSearchGobj(2029)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        scpLinkBGAtoLayoutedTarget(2022, 145);
        stage_SetAnimation(145, 0, 30);
#else
        scpLinkBGAtoLayoutedTarget(2022, 149);
        stage_SetAnimation(149, 0, 30);
#endif
#endif

        fence_mes[0].func = actSt20aFenceUpChk;
        sub->mail = fence_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    } else {
        SetWayGroupActive(19, 0);

#ifdef VERSION_AUG6
        scpSearchGobj(1838)->active = 0;
        scpSearchGobj(1839)->active = 0;

        gflagOff(281);

        scpLinkBGAtoLayoutedTarget(1840, 128);
        stage_SetAnimation(128, 0, 0);
#else
        scpSearchGobj(2022)->active = 0;
        scpSearchGobj(2023)->active = 0;

        scpSearchGobj(2026)->active = 0;
        scpSearchGobj(2027)->active = 0;
        scpSearchGobj(2028)->active = 0;
        scpSearchGobj(2029)->active = 0;

        gflagOff(309);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        scpLinkBGAtoLayoutedTarget(2024, 145);
        stage_SetAnimation(145, 0, 0);
#else
        scpLinkBGAtoLayoutedTarget(2024, 149);
        stage_SetAnimation(149, 0, 0);
#endif

        if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
            scpPlayPosSet(girlGObj, 3973.0f, -1100.0f, -1169.0f);
        }
#endif

        fence2_mes[0].func = actSt20aFenceDownChk2;
        sub->mail = fence2_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt20aFenceDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    while (scpTriggerBall(self, scpSearchGobj(1838), 5.0f) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(128, 1, 0);
    while (stage_CheckAnimationFrame(128, 10, 0) == 0) {
#else
    while (scpTriggerBall(self, scpSearchGobj(2022), 5.0f) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(145, 1, 0);
    while (stage_CheckAnimationFrame(145, 10, 0) == 0) {
#else
    stage_SetAnimation(149, 1, 0);
    while (stage_CheckAnimationFrame(149, 10, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    soundSeDefPlay(1314, 0, 0, 1);
    while (stage_CheckAnimationFrame(128, 30, 1) == 0) {
#else
    soundSeDefPlay(1339, 0, 0, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(145, 30, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(149, 30, 1) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(19, 1);
#ifdef VERSION_AUG6
    gflagOff(292);
    fenceDownChk_mes[0].func = actSt20aFenceUpChk;
    sub->mail = fenceDownChk_mes;
    ACTSendMailCorrect(self, 393);
#else
    scpSearchGobj(2026)->active = 0;
    scpSearchGobj(2027)->active = 0;
    scpSearchGobj(2028)->active = 0;
    scpSearchGobj(2029)->active = 0;
    gflagOff(320);
    fenceDownChk_mes[0].func = actSt20aFenceUpChk;
    sub->mail = fenceDownChk_mes;
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt20aFenceUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    while (scpTriggerBall(self, scpSearchGobj(1838), 5.0f) != 0) {
#else
    while (scpTriggerBall(self, scpSearchGobj(2022), 5.0f) != 0) {
#endif
        _ACTWait(1);
    }
    SetWayGroupActive(19, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(145, 1, 31);
    while (stage_CheckAnimationFrame(145, 40, 0) == 0) {
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(128, 1, 31);
    while (stage_CheckAnimationFrame(128, 40, 0) == 0) {
#else
    stage_SetAnimation(149, 1, 31);
    while (stage_CheckAnimationFrame(149, 40, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    soundSeDefPlay(1314, 0, 0, 1);
    while (stage_CheckAnimationFinish(128) == 0) {
#else
    soundSeDefPlay(1339, 0, 0, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(145) == 0) {
#else
    while (stage_CheckAnimationFinish(149) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    gflagOn(292);
    fenceUpChk_mes[0].func = actSt20aFenceDownChk;
    sub->mail = fenceUpChk_mes;
    ACTSendMailCorrect(self, 393);
#else
    scpSearchGobj(2026)->active = 1;
    scpSearchGobj(2027)->active = 1;
    scpSearchGobj(2028)->active = 1;
    scpSearchGobj(2029)->active = 1;
    gflagOn(320);
    fenceUpChk_mes[0].func = actSt20aFenceDownChk;
    sub->mail = fenceUpChk_mes;
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt20aFenceDownChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    /* pinned: two to five instructions at gcse that later passes delete
       (the hash table is 35 buckets, not the 33 the literal text gives, so
       the record's %hi takes s1 and the callee's s2), from values that
       cross a label cse1 cannot follow; the trigger target and the
       animation number are this check's two such parameters, and gcse
       folds them into their uses.  The two map lines after `sub` (aug6
       853/854, PAL 948/949) carry no code.  Not pinned: the text (the
       other three checks and the later builds spell both as literals). */
    int ball = 1840;
    int anim = 128;
    while (scpTriggerBall(self, scpSearchGobj(ball), 5.0f) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(anim, 1, 0);
    while (stage_CheckAnimationFrame(anim, 10, 0) == 0) {
#else
    while (scpTriggerBall(self, scpSearchGobj(2024), 5.0f) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(145, 1, 0);
    while (stage_CheckAnimationFrame(145, 10, 0) == 0) {
#else
    stage_SetAnimation(149, 1, 0);
    while (stage_CheckAnimationFrame(149, 10, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    soundSeDefPlay(1314, 0, 0, 1);
    while (stage_CheckAnimationFrame(anim, 30, 1) == 0) {
#else
    soundSeDefPlay(1339, 0, 0, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(145, 30, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(149, 30, 1) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    SetWayGroupActive(19, 1);
    gflagOff(292);
    fenceDownChk2_mes[0].func = actSt20aFenceUpChk2;
    sub->mail = fenceDownChk2_mes;
    ACTSendMailCorrect(self, 393);
#else
    scpSearchGobj(2030)->active = 0;
    scpSearchGobj(2031)->active = 0;
    scpSearchGobj(2032)->active = 0;
    scpSearchGobj(2033)->active = 0;
    SetWayGroupActive(19, 1);
    gflagOff(320);
    fenceDownChk2_mes[0].func = actSt20aFenceUpChk2;
    sub->mail = fenceDownChk2_mes;
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt20aFenceUpChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    while (scpTriggerBall(self, scpSearchGobj(1840), 5.0f) != 0) {
#else
    while (scpTriggerBall(self, scpSearchGobj(2024), 5.0f) != 0) {
#endif
        _ACTWait(1);
    }
    SetWayGroupActive(19, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(145, 1, 31);
    while (stage_CheckAnimationFrame(145, 40, 0) == 0) {
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(128, 1, 31);
    while (stage_CheckAnimationFrame(128, 40, 0) == 0) {
#else
    stage_SetAnimation(149, 1, 31);
    while (stage_CheckAnimationFrame(149, 40, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    soundSeDefPlay(1314, 0, 0, 1);
    while (stage_CheckAnimationFinish(128) == 0) {
#else
    soundSeDefPlay(1339, 0, 0, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(145) == 0) {
#else
    while (stage_CheckAnimationFinish(149) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    gflagOn(292);
    fenceUpChk2_mes[0].func = actSt20aFenceDownChk2;
    sub->mail = fenceUpChk2_mes;
    ACTSendMailCorrect(self, 393);
#else
    scpSearchGobj(2030)->active = 1;
    scpSearchGobj(2031)->active = 1;
    scpSearchGobj(2032)->active = 1;
    scpSearchGobj(2033)->active = 1;
    gflagOn(320);
    fenceUpChk2_mes[0].func = actSt20aFenceDownChk2;
    sub->mail = fenceUpChk2_mes;
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt20aBridge(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
#ifdef VERSION_AUG6
    if (gflagChk(287) == 0) {
        bridge_mes[0].func = actSt20aBridgeMain;
        sub->mail = bridge_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(315) == 0) {
        bridge_mes[0].func = actSt20aBridgeMain;
        sub->mail = bridge_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt20aGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
#ifdef VERSION_AUG6
    if (gflagChk(288) != 0) {
        stage_SetAnimation(126, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(126, 0, 500);
    } else {
        stage_SetAnimation(126, 0, 0);
#else
    if (gflagChk(316) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(143, 0, 0);
#else
        stage_SetAnimation(147, 0, 0);
#endif
        _ACTWait(10);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(143, 0, 500);
#else
        stage_SetAnimation(147, 0, 500);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(143, 0, 0);
#else
        stage_SetAnimation(147, 0, 0);
#endif
#endif
    }
    gondola_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondola_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}
#endif

void actSt20aExit(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    exit_mes[0].func = actSt20aExitChk;
    sub->mail = exit_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

#ifdef VERSION_NTSC
void actSt20aElv(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    if (gflagChk(282) != 0) {
        scpSearchGobj(1854)->active = 0;
        scpSearchGobj(1855)->active = 0;
        gflagOff(282);
    } else {
        scpSearchGobj(1856)->active = 0;
        scpSearchGobj(1857)->active = 0;
    }
}

void actSt20aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(291) == 0) {
        ene_mes[0].func = actSt20aEneChk;
        sub->mail = ene_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt20aEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(292) == 0) {
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
    while (gflagChk(292) == 0) {
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
    while (gflagChk(292) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
}
#else
void actSt20aElv(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
#ifdef VERSION_AUG6
    if (gflagChk(281) != 0) {
        scpSearchGobj(1838)->active = 0;
        scpSearchGobj(1839)->active = 0;
        gflagOff(281);
    } else {
        scpSearchGobj(1840)->active = 0;
        scpSearchGobj(1841)->active = 0;
#else
    if (gflagChk(309) != 0) {
        scpSearchGobj(2022)->active = 0;
        scpSearchGobj(2023)->active = 0;
        gflagOff(309);
    } else {
        scpSearchGobj(2024)->active = 0;
        scpSearchGobj(2025)->active = 0;
#endif
    }
}

void actSt20aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
#ifdef VERSION_AUG6
    if (gflagChk(290) == 0) {
        ene_mes[0].func = actSt20aEneChk;
        sub->mail = ene_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(318) == 0) {
        ene_mes[0].func = actSt20aEneChk;
        sub->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt20aEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
#ifdef VERSION_AUG6
    while (gflagChk(291) == 0) {
#else
    while (gflagChk(319) == 0) {
#endif
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
#ifdef VERSION_AUG6
    while (gflagChk(291) == 0) {
#else
    while (gflagChk(319) == 0) {
#endif
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
#ifdef VERSION_AUG6
    while (gflagChk(291) == 0) {
#else
    while (gflagChk(319) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
#ifndef VERSION_AUG6
}

void actSt20aHint1(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(321) == 0) {
        hint1_mes[0].func = actSt20aHint1Chk;
        sub->mail = hint1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        FinishHint(20);
    }
}

void actSt20aGirlPos(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(322) == 0) {
        SleepHint(20);
        girlPos_mes[0].func = actSt20aGirlPosChk;
        sub->mail = girlPos_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
#endif
}
#endif

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
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt20aBridgeDownSub(GObj *volatile self)
{
    _ACTWait(30);
    while (brg20a == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(brg20a->stream);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(144, 1, 0);
#else
    stage_SetAnimation(148, 1, 0);
#endif
    st20a_yure = iosPadActRequest(boyPad, 9);
    st20a_yure_vol = 128;
    iosPadActVolumeSet(st20a_yure, 128);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(144) == 0) {
#else
    while (stage_CheckAnimationFinish(148) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
#endif
#endif
    _ACTWait(0);
}

void actSt20aGondolaMain(GObj *volatile self)
{
    Act *p = GOBJ_ACT(self);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    p->mainMail = gondolaMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
void actSt20aGondolaSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    if (gflagChk(289) != 0) {
        gondolaSwitchUp_mes[0].func = actSt20aGondolaUp;
        sub->mail = gondolaSwitchUp_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
    gondolaSwitchDown_mes[0].func = actSt20aGondolaDown;
    sub->mail = gondolaSwitchDown_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
#else
void actSt20aGondolaSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    if (gflagChk(288) != 0) {
        gondolaSwitchUp_mes[0].func = actSt20aGondolaUp;
        sub->mail = gondolaSwitchUp_mes;
        ACTSendMailCorrect(self, 393);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    if (gflagChk(316) != 0) {
        gondolaSwitchUp_mes[0].func = actSt20aGondolaUp;
        sub->mail = gondolaSwitchUp_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
    gondolaSwitchDown_mes[0].func = actSt20aGondolaDown;
    sub->mail = gondolaSwitchDown_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}
#endif

void actSt20aExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_NTSC
    gflagOn(290);
    gflagOff(282);
#else
#ifdef VERSION_AUG6
    gflagOn(289);
    gflagOff(281);
#else
    gflagOn(317);
    gflagOff(309);
#endif
#endif
    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        OnGirlEscortFlag();
        RequestStageChange(4, boyGObj, girlGObj, 2.0f, 8.0f);
    }
    RequestStageChange(4, boyGObj, 0, 2.0f, 8.0f);
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt20aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
#ifdef VERSION_AUG6
    while (gflagChk(287) == 0 || scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
#else
    while (gflagChk(288) == 0 || scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    gflagOn(290);
    gflagOn(291);
#else
    gflagOn(291);
    gflagOn(292);
#endif
}
#else
void actSt20aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (gflagChk(315) == 0 || scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(318);
    gflagOn(319);
}

static void actSt20aGirlPosChk(GObj *volatile self)
{
    while (girlGObj == 0 || scpTriggerBall(self, girlGObj, 200.0f) == 0) {
        _ACTWait(1);
    }
    gflagOn(322);
    WakeupHint(20);
}

static void actSt20aHint1Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0 &&
           scpTriggerFloorAttr(boyGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");
    gflagOn(321);
    FinishHint(20);
}
#endif
