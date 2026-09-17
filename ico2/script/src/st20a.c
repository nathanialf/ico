#include "common.h"
#include "st20a.h"
#include "gamesys.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
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

/* This stage's actor mail records. Word 0 of each entry is the mail id the
   entry answers (430 = the actor's own wake-up post, 429 = the trailing
   entry); the handler in .func is installed at run time just before the
   record is posted. The two main-thread records answer their own ids and
   carry their switch handler from the start. Each record is named for the
   actor thread that owns and posts it. */
static ActMail bridgeMain_mes[2] = {{406, actSt20aBridgeSwitch}, {429}};

static ActMail bridge_mes[2] = {{430}, {429}};

static ActMail bridgeSwitch_mes[2] = {{430}, {429}};

static ActMail gondolaMain_mes[2] = {{407, actSt20aGondolaSwitch}, {429}};

static ActMail gondola_mes[2] = {{430}, {429}};

static ActMail gondolaSwitchUp_mes[2] = {{430}, {429}};

static ActMail gondolaSwitchDown_mes[2] = {{430}, {429}};

static ActMail gondolaDown_mes[2] = {{430}, {429}};

static ActMail gondolaUp_mes[2] = {{430}, {429}};

static ActMail exit_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail fence_mes[2] = {{430}, {429}};

static ActMail fence2_mes[2] = {{430}, {429}};

static ActMail fenceDownChk_mes[2] = {{430}, {429}};

static ActMail fenceUpChk_mes[2] = {{430}, {429}};

static ActMail fenceDownChk2_mes[2] = {{430}, {429}};

static ActMail fenceUpChk2_mes[2] = {{430}, {429}};

static ActMail girlPos_mes[2] = {{430}, {429}};

static ActMail hint1_mes[2] = {{430}, {429}};

extern int D_00639EA8;
extern int D_00639EA4;
extern int D_0063AA08;

void actSt20aInit(void)
{
    if (gflagChk(315) == 0) {
        stage_SetAnimation(148, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(148, 0, -1);
        SetWayGroupActive(4, 1);
    }
}

void actSt20aEnd(void)
{
    if (D_00639EA8 != 0 && gflagChk(315) != 0 && gflagChk(318) == 0) {
        gflagOn(391);
    }
    gamesysObjInfoCls(*(int *)(scpSearchGobj(2025) + 0xC), *(int *)(scpSearchGobj(2025) + 8));
    gamesysObjInfoCls(*(int *)(scpSearchGobj(2023) + 0xC), *(int *)(scpSearchGobj(2023) + 8));
}

extern int brg20a;
extern int gondola_up;
extern int gondola_down;
extern unsigned int st20a_yure;
extern int D_00639EAC;

/* .sbss, owned by st20a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for. */
static int demoEnd;

extern int D_0028F8F4[];

void actSt20aBridgeDown(volatile int a0)
{
    int th;

    lt_switch_layout(55);
    scpSleepEnemyAll();
    gflagOn(315);
    gflagOff(391);
    st20a_yure = 0xFFFFFFFF;
    demoEnd = 0;
    scpAdpcmPlayRequestFunc(71, &brg20a, 1, 1, 0);
    th = actCreateSubThread(actSt20aBridgeDownSub, 21);
    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    iosThreadSetPri(th + 0x24, 34);
    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (brg20a == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc(&brg20a, 0x200);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(148, 0, -1);
        scpFadeIn(3.0f);
    }
    iosPadActStop(st20a_yure);
    SetWayGroupActive(4, 1);
    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(54);
}

void actSt20aGondolaDown(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    SetGirlDangerGObj(D_00639EA4);
    scpAdpcmPlayRequestFunc(69, &gondola_down, 1, 1, 1);
    while (gondola_down == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(147, 1, 0);
    gflagOn(316);
    while (stage_CheckAnimationFrame(147, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);
    while (stage_CheckAnimationFrame(147, 500, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x10);
    if (gondola_down != 0) {
        scpAdpcmFadeCloseFunc(&gondola_down, 0x100);
    }
    while (scpAdpcmCloseChkFunc(&gondola_down) != 0) {
        _ACTWait(1);
    }
    ClearGirlDangerGObj();
    gondolaDown_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondolaDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt20aGondolaUp(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    scpAdpcmPlayRequestFunc(70, &gondola_up, 1, 1, 1);
    while (gondola_up == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(147, 1, 0x1F4);
    gflagOff(316);
    while (stage_CheckAnimationFrame(147, 820, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);
    while (stage_CheckAnimationFrame(147, 1000, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x10);
    if (gondola_up != 0) {
        scpAdpcmFadeCloseFunc(&gondola_up, 0x100);
    }
    while (scpAdpcmCloseChkFunc(&gondola_up) != 0) {
        _ACTWait(1);
    }
    gondolaUp_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondolaUp_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt20aFence(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(309) == 0) {
        SetWayGroupActive(19, 1);

        *(int *)(scpSearchGobj(2024) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2025) + 0x16C) = 0;

        *(int *)(scpSearchGobj(2030) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2031) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2032) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2033) + 0x16C) = 0;

        *(int *)(scpSearchGobj(2026) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2027) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2028) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2029) + 0x16C) = 0;

        scpLinkBGAtoLayoutedTarget(0x7E6, 0x95);
        stage_SetAnimation(149, 0, 0x1E);

        fence_mes[0].func = actSt20aFenceUpChk;
        sub->mail = fence_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(19, 0);

        *(int *)(scpSearchGobj(2022) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2023) + 0x16C) = 0;

        *(int *)(scpSearchGobj(2026) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2027) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2028) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2029) + 0x16C) = 0;

        gflagOff(309);

        scpLinkBGAtoLayoutedTarget(0x7E8, 0x95);
        stage_SetAnimation(149, 0, 0);

        if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0) {
            scpPlayPosSet(D_00639EA8, 3973.0f, -1100.0f, -1169.0f);
        }

        fence2_mes[0].func = actSt20aFenceDownChk2;
        sub->mail = fence2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt20aFenceDownChk(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    while (scpTriggerBall(a0, scpSearchGobj(2022), 5.0f) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(149, 1, 0);
    while (stage_CheckAnimationFrame(149, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(1339, 0, 0, 1);
    while (stage_CheckAnimationFrame(149, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(19, 1);
    *(int *)(scpSearchGobj(2026) + 0x16C) = 0;
    *(int *)(scpSearchGobj(2027) + 0x16C) = 0;
    *(int *)(scpSearchGobj(2028) + 0x16C) = 0;
    *(int *)(scpSearchGobj(2029) + 0x16C) = 0;
    gflagOff(320);
    fenceDownChk_mes[0].func = actSt20aFenceUpChk;
    sub->mail = fenceDownChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt20aFenceUpChk(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    while (scpTriggerBall(a0, scpSearchGobj(2022), 5.0f) != 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(19, 0);
    stage_SetAnimation(149, 1, 0x1F);
    while (stage_CheckAnimationFrame(149, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(1339, 0, 0, 1);
    while (stage_CheckAnimationFinish(149) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    *(int *)(scpSearchGobj(2026) + 0x16C) = 1;
    *(int *)(scpSearchGobj(2027) + 0x16C) = 1;
    *(int *)(scpSearchGobj(2028) + 0x16C) = 1;
    *(int *)(scpSearchGobj(2029) + 0x16C) = 1;
    gflagOn(320);
    fenceUpChk_mes[0].func = actSt20aFenceDownChk;
    sub->mail = fenceUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt20aFenceDownChk2(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    while (scpTriggerBall(a0, scpSearchGobj(2024), 5.0f) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(149, 1, 0);
    while (stage_CheckAnimationFrame(149, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(1339, 0, 0, 1);
    while (stage_CheckAnimationFrame(149, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    *(int *)(scpSearchGobj(2030) + 0x16C) = 0;
    *(int *)(scpSearchGobj(2031) + 0x16C) = 0;
    *(int *)(scpSearchGobj(2032) + 0x16C) = 0;
    *(int *)(scpSearchGobj(2033) + 0x16C) = 0;
    SetWayGroupActive(19, 1);
    gflagOff(320);
    fenceDownChk2_mes[0].func = actSt20aFenceUpChk2;
    sub->mail = fenceDownChk2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt20aFenceUpChk2(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    while (scpTriggerBall(a0, scpSearchGobj(2024), 5.0f) != 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(19, 0);
    stage_SetAnimation(149, 1, 0x1F);
    while (stage_CheckAnimationFrame(149, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(1339, 0, 0, 1);
    while (stage_CheckAnimationFinish(149) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    *(int *)(scpSearchGobj(2030) + 0x16C) = 1;
    *(int *)(scpSearchGobj(2031) + 0x16C) = 1;
    *(int *)(scpSearchGobj(2032) + 0x16C) = 1;
    *(int *)(scpSearchGobj(2033) + 0x16C) = 1;
    gflagOn(320);
    fenceUpChk2_mes[0].func = actSt20aFenceDownChk2;
    sub->mail = fenceUpChk2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt20aBridge(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(315) == 0) {
        bridge_mes[0].func = actSt20aBridgeMain;
        sub->mail = bridge_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt20aGondola(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(316) != 0) {
        stage_SetAnimation(147, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(147, 0, 0x1F4);
    } else {
        stage_SetAnimation(147, 0, 0);
    }
    gondola_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondola_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt20aExit(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    exit_mes[0].func = actSt20aExitChk;
    sub->mail = exit_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt20aElv(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    if (gflagChk(309) != 0) {
        *(int *)(scpSearchGobj(2022) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2023) + 0x16C) = 0;
        gflagOff(309);
    } else {
        *(int *)(scpSearchGobj(2024) + 0x16C) = 0;
        *(int *)(scpSearchGobj(2025) + 0x16C) = 0;
    }
}

void actSt20aEne(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(318) == 0) {
        ene_mes[0].func = actSt20aEneChk;
        sub->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt20aEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(319) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt20aEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(319) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt20aEnemy3(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(319) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
}

void actSt20aHint1(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(321) == 0) {
        hint1_mes[0].func = actSt20aHint1Chk;
        sub->mail = hint1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(20);
    }
}

void actSt20aGirlPos(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(322) == 0) {
        SleepHint(20);
        girlPos_mes[0].func = actSt20aGirlPosChk;
        sub->mail = girlPos_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* the actor entry's parameter is its frame home: the thread switch writes it */
void actSt20aBridgeMain(volatile int a0)
{
    *(char **)(*(int *)(a0 + 0x164) + 0xD0) = (char *)bridgeMain_mes;
    D_0063AA08 = 0;
    while (1) {
        _ACTWait(1);
    }
}

void actSt20aBridgeSwitch(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    D_0063AA08 = 1;
    bridgeSwitch_mes[0].func = actSt20aBridgeDown;
    sub->mainMail = 0;
    sub->mail = bridgeSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern unsigned char st20a_yure_vol;

void actSt20aBridgeDownSub(volatile int a0)
{
    _ACTWait(30);
    while (brg20a == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(*(int *)(brg20a + 0x2C));
    stage_SetAnimation(148, 1, 0);
    st20a_yure = iosPadActRequest(D_00639EAC, 9);
    st20a_yure_vol = 0x80;
    iosPadActVolumeSet(st20a_yure, 0x80);
    while (stage_CheckAnimationFinish(148) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt20aGondolaMain(volatile int a0)
{
    char *p = *(char **)(a0 + 0x164);

    lt_switch_layout(54);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    *(char **)(p + 0xD0) = (char *)gondolaMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt20aGondolaSwitch(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    sub->mainMail = 0;
    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSleepEnemyAll();
    if (gflagChk(316) != 0) {
        gondolaSwitchUp_mes[0].func = actSt20aGondolaUp;
        sub->mail = gondolaSwitchUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
    gondolaSwitchDown_mes[0].func = actSt20aGondolaDown;
    sub->mail = gondolaSwitchDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt20aExitChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 400.0f) == 0 ||
           scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(317);
    gflagOff(309);
    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0) {
        OnGirlEscortFlag();
        RequestStageChange(4, D_00639EA4, D_00639EA8, 2.0f, 8.0f);
    }
    RequestStageChange(4, D_00639EA4, 0, 2.0f, 8.0f);
}

void actSt20aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (gflagChk(315) == 0 || scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(318);
    gflagOn(319);
}

void actSt20aGirlPosChk(volatile int a0)
{
    while (D_00639EA8 == 0 || scpTriggerBall(a0, D_00639EA8, 200.0f) == 0) {
        _ACTWait(1);
    }
    gflagOn(322);
    WakeupHint(20);
}

void actSt20aHint1Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0 &&
           scpTriggerFloorAttr(D_00639EA4, 0x4000000) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");
    gflagOn(321);
    FinishHint(20);
}
