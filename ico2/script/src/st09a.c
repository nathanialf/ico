#include "common.h"
#include "st09a.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "typedef.h"

extern int D_00639EA4;
extern int D_00639EAC;

/* .sbss, owned by st09a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for. */
static int demoEnd;

/* st09a.o's own .rodata run 0x00622DA0..0x00622DE0 (no MAIN.MAP symbols):
   the two hint-finished debug strings. */
extern int D_0063AA08;

/* st09a.o's own .data run 0x004FA2F0..0x004FA480 (no MAIN.MAP symbols):
   actor mail packets. */

static ActMail elvMain_mes[2] = {{406, actSt09aElvSwitch}, {429}};

static ActMail elv_mes[2] = {{430}, {429}};

static ActMail elvSwitchUp_mes[2] = {{430}, {429}};

static ActMail elvSwitchDown_mes[2] = {{430}, {429}};

static ActMail elvDown_mes[2] = {{430}, {429}};

static ActMail elvUp_mes[2] = {{430}, {429}};

static float sekizoPos[4] = {1548.0f, -412.0f, -608.0f, 0.0f};

static ActMail intro_mes[2] = {{430}, {429}};

static ActMail brgMain_mes[2] = {{407, actSt09aBrgSwitch}, {429}};

static ActMail brg_mes[2] = {{430}, {429}};

static ActMail brgSwitch_mes[2] = {{430}, {429}};

static ActMail hint1_mes[2] = {{430}, {429}};

static ActMail hint2_mes[2] = {{430}, {429}};

extern int st09a_brg;
extern int D_0028F8F4[];

void actSt09aInit(void)
{
    if (gflagChk(86) == 0) {
        stage_SetAnimation(378, 0, 0);
    } else {
        stage_SetAnimation(378, 0, -1);
    }
}

void actSt09aElvDown(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;
    /* sound handle owned by the sound subsystem: ROM homes it at 4(sp)
       across the animation wait and reloads it for soundSeDefStop. */
    volatile int se;

    lt_switch_layout(55);
    LockForceGroundParent(D_00639EA4);

    stage_SetAnimation(375, 1, 0);

    se = soundSeDefPlay(1217, 0, 0, 1);

    gflagOn(83);

    while (stage_CheckAnimationFrame(375, 210, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    UnlockForceGroundParent(D_00639EA4);

    lt_switch_layout(54);

    elvDown_mes[0].func = actSt09aElvMain;
    self->mail = elvDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt09aBrgDown(volatile int a0)
{
    int th;

    lt_switch_layout(55);
    gflagOn(86);
    scpAdpcmPlayRequestFunc(90, &st09a_brg, 1, 1, 1);

    while (st09a_brg == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(actSt09aBrgDownSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st09a_brg, 0x100);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(378, 0, -1);
        scpFadeIn(5.0f);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    D_0063AA08 = 0;
    lt_switch_layout(54);
}

void actSt09aElv(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(83) != 0) {
        stage_SetAnimation(375, 0, 0xD2);
    } else {
        stage_SetAnimation(375, 0, 0);
    }

    elv_mes[0].func = actSt09aElvMain;
    self->mail = elv_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt09aSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    soundSeDefPlay(1346, 0, sekizoPos, 1);
    soundSeDefPlay(1347, 0, sekizoPos, 1);
    soundSeDefPlay(1348, 0, sekizoPos, 1);

    scpSekizou(a0, 0x54, 0x178, 0, 0x12, -1350.0f, -100.0f, 1515.0f, -1450.0f, -100.0f, 1515.0f);
}

void actSt09aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(85) == 0) {
        intro_mes[0].func = actSt09aIntroChk;
        self->mail = intro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt09aBrg(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(86) == 0) {
        brg_mes[0].func = actSt09aBrgMain;
        self->mail = brg_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt09aHint1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(87) == 0) {
        hint1_mes[0].func = actSt09aHint1Chk;
        self->mail = hint1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(10);
    }
}

void actSt09aHint2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(88) == 0) {
        hint2_mes[0].func = actSt09aHint2Chk;
        self->mail = hint2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(11);
    }
}

void actSt09aElvMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = elvMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt09aElvSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    if (gflagChk(83) != 0) {
        elvSwitchUp_mes[0].func = actSt09aElvUp;
        sub->mail = elvSwitchUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }

    elvSwitchDown_mes[0].func = actSt09aElvDown;
    sub->mail = elvSwitchDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt09aElvUp(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;
    /* sound handle owned by the sound subsystem: ROM homes it at 4(sp)
       across the animation wait and reloads it for soundSeDefStop. */
    volatile int se;

    lt_switch_layout(55);

    stage_SetAnimation(375, 1, 0xD3);

    se = soundSeDefPlay(1217, 0, 0, 1);

    gflagOff(83);

    while (stage_CheckAnimationFrame(375, 420, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    lt_switch_layout(54);

    elvUp_mes[0].func = actSt09aElvMain;
    self->mail = elvUp_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt09aSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt09aIntroChk(volatile int a0)
{
    lt_switch_layout(55);
    gflagOn(85);

    D_0063AA08 = 1;
    _ACTWait(1);

    stage_SetAnimation(377, 1, 0);

    while (stage_CheckAnimationFinish(377) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);

    D_0063AA08 = 0;
}

void actSt09aBrgMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    sub->mainMail = brgMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt09aBrgSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    brgSwitch_mes[0].func = actSt09aBrgDown;
    sub->mail = brgSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt09aBrgDownSub(volatile int a0)
{
    stage_SetAnimation(378, 1, 0);

    while (stage_CheckAnimationFrame(378, 115, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(378, 165, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFinish(378) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt09aHint1Chk(volatile int a0)
{
    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");

    gflagOn(87);
    FinishHint(10);
}

void actSt09aHint2Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 400.0f) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT2_FINISH!!!!!!!!!!!!!!!\n");

    gflagOn(88);
    FinishHint(11);
}
