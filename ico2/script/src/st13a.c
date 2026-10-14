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
#include "include_asm.h"

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for. */
static int demoEnd;

static void actSt13aElevUpSub(GObj *volatile self);
static void actSt13aElevDownSub(GObj *volatile self);
void actSt13aElevDownChk(GObj *volatile self);

/* .data: actor mail packets. */

/* The chain-OK watcher's mail record: it installs actSt13aChainNG here and
   posts it to hand the chain back to the NG (hang-disabled) watcher. Word 0
   of each entry is the mail id the entry answers (430 the actor post,
   429 the trailing entry); .func is filled in at run time. Named for the
   thread that owns and posts it. */

static ActMail elevMain_mes[2] = {{406, actSt13aElevSwitch}, {429}}; /* derived name */

static ActMail elev_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elevDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail check_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainNg_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainOk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainOK_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainNG_mes[2] = {{430}, {429}}; /* derived name */

/* .sdata: the lift and statue stream handles and shakes. */
SqEntry *st13a_up = 0;

SqEntry *st13a_down = 0;

SqEntry *sekizo13a = 0;

unsigned int st13a_yure = 0;

unsigned char st13a_yure_vol = 0;

int sekizo_13a = 0;

unsigned char sekizo_13a_vol = 0;

INCLUDE_ASM(actSt13aElevUpSub);

void actSt13aElevUp(GObj *volatile self)
{
    GProc *th;

    scpAdpcmPlayRequestFunc(77, &st13a_up, 0, 1, 0);
    while (st13a_up == 0) {
        _ACTWait(1);
    }

    preload(15);

    st13a_yure = -1;
    th = actCreateSubThread(actSt13aElevUpSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st13a_up, 512);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
    }

    iosPadActStop(st13a_yure);
    gflagOn(325);
    RequestStageChange(15, boyGObj, 0, 0.025f, 8.0f);
}

INCLUDE_ASM(actSt13aElevDown);

INCLUDE_ASM(actSt13aElevDownSub);

INCLUDE_ASM(actSt13aElevDownChk);

INCLUDE_ASM(actSt13aSekizoChk);

INCLUDE_ASM(actSt13aElev);

INCLUDE_ASM(actSt13aSekizo);

void actSt13aCheck(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(327) == 0) {
        check_mes[0].func = actSt13aCheckChk;
        act->mail = check_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13aChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(328) == 0) {
        chainNg_mes[0].func = actSt13aChainNG;
        act->mail = chainNg_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        chainOk_mes[0].func = actSt13aChainOK;
        act->mail = chainOk_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13aElevMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = elevMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt13aElevSwitch);

void actSt13aCheckChk(GObj *volatile self)
{
    _ACTWait(1);

    CheckPoint();
    gflagOn(327);
}

void actSt13aChainOK(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(2072), 200.0f) != 0) {
        _ACTWait(1);
    }

    EnableChainHang(scpSearchGobj(2071));
    gflagOff(328);

    chainOK_mes[0].func = actSt13aChainNG;
    sub->mail = chainOK_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt13aChainNG(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(2072), 200.0f) == 0) {
        _ACTWait(1);
    }

    UnableChainHang(scpSearchGobj(2071));
    gflagOn(328);

    chainNG_mes[0].func = actSt13aChainOK;
    sub->mail = chainNG_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
