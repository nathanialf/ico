#include "common.h"
#include "st13a.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "act.h"
#include "commonact.h"
#include "chain.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include <libvu0.h>
#include "typedef.h"

extern int D_0063AA08;
extern int D_00639EA4;
extern int D_00639EAC;

/* .sbss, owned by st13a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthreads the wait loops below spin for. */
static int demoEnd;

extern PadState D_0028F8F0[];
/* st13a.o's own .sdata run; MAIN.MAP names all seven. */
extern int st13a_up;
extern int st13a_down;
extern int sekizo13a;
extern unsigned int st13a_yure;
extern unsigned char st13a_yure_vol;
extern int sekizo_13a;
extern unsigned char sekizo_13a_vol;
void actSt13aElevUpSub(volatile int a0);
void actSt13aElevDownSub(volatile int a0);
void actSt13aElevDownChk(volatile int a0);

/* st13a.o's own .data run (no MAIN.MAP symbols): actor mail packets. */

/* The chain-OK watcher's mail record: it installs actSt13aChainNG here and
   posts it to hand the chain back to the NG (hang-disabled) watcher. Word 0
   of each entry is the mail id the entry answers (430 the actor post,
   429 the trailing entry); .func is filled in at run time. Named for the
   thread that owns and posts it. */

static ActMail elevMain_mes[2] = {{406, actSt13aElevSwitch}, {429}};

static ActMail elev_mes[2] = {{430}, {429}};

static ActMail elevSwitch_mes[2] = {{430}, {429}};

static ActMail elevDown_mes[2] = {{430}, {429}};

static ActMail sekizo_mes[2] = {{430}, {429}};

static ActMail check_mes[2] = {{430}, {429}};

static ActMail chainNg_mes[2] = {{430}, {429}};

static ActMail chainOk_mes[2] = {{430}, {429}};

static ActMail chain_ok_mes[2] = {{430}, {429}};

static ActMail chainNG_mes[2] = {{430}, {429}};

void actSt13aElevUpSub(volatile int a0)
{
    AdpcmPlay(*(int *)(st13a_up + 0x2C));

    stage_SetAnimation(173, 1, 0);
    stage_SetAnimation(174, 1, 0);

    while (stage_CheckAnimationFrame(173, 86, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(173, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure = iosPadActRequest(D_00639EAC, 9);
    st13a_yure_vol = 0x80;
    iosPadActVolumeSet(st13a_yure, 0x80);

    while (stage_CheckAnimationFrame(173, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure_vol = 0x40;

    while (stage_CheckAnimationFrame(173, 380, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt13aElevUp(volatile int a0)
{
    int th;

    scpAdpcmPlayRequestFunc(77, &st13a_up, 0, 1, 0);
    while (st13a_up == 0) {
        _ACTWait(1);
    }

    preload(0xF);

    st13a_yure = -1;
    th = actCreateSubThread(actSt13aElevUpSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st13a_up, 0x200);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
    }

    iosPadActStop(st13a_yure);
    gflagOn(325);
    RequestStageChange(0xF, D_00639EA4, 0, 0.025f, 8.0f);
}

void actSt13aElevDown(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(15) != 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(173, 0, 0);
        lt_switch_layout(55);
        D_0063AA08 = 1;
        scpPlayStart(D_00639EA4);
        scpAdpcmPlayRequestFunc(80, &st13a_down, 1, 1, 0);
        _ACTWait(10);
        stage_SetAnimation(173, 0, 0x1C3);

        elevDown_mes[0].func = actSt13aElevDownChk;
        self->mail = elevDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13aElevDownSub(volatile int a0)
{
    stage_SetAnimation(173, 1, 0x1C3);
    stage_SetAnimation(175, 1, 0);

    scpPlayPosSet(D_00639EA4, -4871.0f, -2800.0f, 2699.0f);

    st13a_yure = iosPadActRequest(D_00639EAC, 9);
    st13a_yure_vol = 0x80;
    iosPadActVolumeSet(st13a_yure, 0x80);

    while (stage_CheckAnimationFrame(173, 850, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);
    iosPadActStop(st13a_yure);
    st13a_yure = -1;

    while (stage_CheckAnimationFinish(173) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt13aElevDownChk(volatile int a0)
{
    int th;

    while (st13a_down == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(st13a_down + 0x2C));
    scpFadeIn(6.0f);

    th = actCreateSubThread(actSt13aElevDownSub, 21);
    demoEnd = 0;
    st13a_yure = -1;

    while (demoEnd == 0 && ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st13a_down, 0x200);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(175, 0, -1);
        stage_SetAnimation(173, 0, -1);
        _ACTWait(2);
        scpPlayPosSet(D_00639EA4, -4871.0f, 3527.0f, 2699.0f);
        iosPadActStop(st13a_yure);
        scpFadeIn(3.0f);
    }

    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    lt_switch_layout(54);
    D_0063AA08 = 0;
    gflagOff(15);
}

void actSt13aSekizoChk(volatile int a0)
{
    float d[4];

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           scpActStatusDeathFall(D_00639EA4) != 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;

    scpAdpcmPlayRequestFunc(18, &sekizo13a, 1, 1, 1);
    while (sekizo13a == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(176, 1, 0);

    sekizo_13a = iosPadActRequest(D_00639EAC, 9);
    sekizo_13a_vol = 0x80;
    iosPadActVolumeSet(sekizo_13a, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayPosSet(D_00639EA4, -3688.0f, 3527.0f, 2502.0f);
    scpPlayMot(D_00639EA4, 0);
    _ACTWait(1);

    sceVu0SubVector(d, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, d);

    scpSekizouCheckPoint();

    scpPlayMot(D_00639EA4, 251);
    scpPlayWaitMotEnd(D_00639EA4);
    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    gflagOn(326);

    while (stage_CheckAnimationFrame(176, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_13a);

    while (stage_CheckAnimationFinish(176) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);
    D_0063AA08 = 0;
}

void actSt13aElev(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    ScpCallCameraSetTarget(4729.0f, 2715.0f, -2504.0f);

    if (gflagChk(325) == 0) {
        stage_SetAnimation(173, 0, 0);

        elev_mes[0].func = actSt13aElevMain;
        self->mail = elev_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13aSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(326) == 0) {
        stage_SetAnimation(176, 0, 0);

        sekizo_mes[0].func = actSt13aSekizoChk;
        self->mail = sekizo_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(176, 0, -1);
    }
}

void actSt13aCheck(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(327) == 0) {
        check_mes[0].func = actSt13aCheckChk;
        self->mail = check_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13aChain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(328) == 0) {
        chainNg_mes[0].func = actSt13aChainNG;
        self->mail = chainNg_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        chainOk_mes[0].func = actSt13aChainOK;
        self->mail = chainOk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13aElevMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = elevMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13aElevSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(55);
    D_0063AA08 = 1;

    elevSwitch_mes[0].func = actSt13aElevUp;
    sub->mail = elevSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt13aCheckChk(volatile int a0)
{
    _ACTWait(1);

    CheckPoint();
    gflagOn(327);
}

void actSt13aChainOK(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, scpSearchGobj(2072), 200.0f) != 0) {
        _ACTWait(1);
    }

    EnableChainHang((char *)scpSearchGobj(2071));
    gflagOff(328);

    chain_ok_mes[0].func = actSt13aChainNG;
    sub->mail = chain_ok_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt13aChainNG(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, scpSearchGobj(2072), 200.0f) == 0) {
        _ACTWait(1);
    }

    UnableChainHang((char *)scpSearchGobj(2071));
    gflagOn(328);

    chainNG_mes[0].func = actSt13aChainOK;
    sub->mail = chainNG_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
