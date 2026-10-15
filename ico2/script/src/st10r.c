#include "st10r.h"
#include "gamesys.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "gobj_process.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "boyact.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "cage.h"
#include "motionManager2.h"
#include "rotObject.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static void actSt10rTowerResqueChk(GObj *volatile self);

static ActMail floor_hit_mes[2] = {{397}, {396}}; /* derived name */

static ActMail tower_mes[2] = {{397}, {396}}; /* derived name */

static ActMail tower_resque_mes[2] = {{397}, {396}}; /* derived name */

static ActMail exit_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chain_main_mes[2] = {{378, actSt10rChainSwitch}, {396}}; /* derived name */

static ActMail chain_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chain_switch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_down1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_up1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_down2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_up2_mes[2] = {{397}, {396}}; /* derived name */

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for. */
static int demoEnd;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{-296.0f, 327.0f, 2125.0f, 0.0f}}; /* derived name */

/* .sdata: the floor and cage stream handles, the scene stream, the chain's. */
SqEntry *st10r_floor = 0;

SqEntry *cage10r = 0;

static SqEntry *st10r_adpcm = 0; /* derived name */

SqEntry *chain10r = 0;

INCLUDE_ASM(actSt10rInit);

INCLUDE_ASM(func_0022D9C0);

INCLUDE_ASM(func_0022DAC8);

INCLUDE_ASM(func_0022DBC8);

INCLUDE_ASM(actSt10rTowerConte);

void actSt10rChainMove(GObj *volatile self)
{
    int se;

    lt_switch_layout(51);

    scpSleepEnemyAll();

    gflagOn(277);

    scpSearchGobj(1516)->active = 1;

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(91, &chain10r, 1, 1, 1);

    while (chain10r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(351, 1, 0);

    se = soundSeDefPlay(1263, 0, 0, 1);

    _ACTWait(180);

    soundSeDefStop(se);

    soundSeDefPlay(1264, 0, 0, 1);

    iosPadActRequest(boyPad, 17);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

INCLUDE_ASM(actSt10rFence);

INCLUDE_ASM(actSt10rFenceDownChk);

INCLUDE_ASM(actSt10rFenceUpChk);

INCLUDE_ASM(actSt10rFenceDownChk2);

INCLUDE_ASM(actSt10rFenceUpChk2);

INCLUDE_ASM(actSt10rFloorHit);

INCLUDE_ASM(actSt10rTower);

INCLUDE_ASM(actSt10rTowerResque);

INCLUDE_ASM(actSt10rExit);

INCLUDE_ASM(actSt10rChain);

INCLUDE_ASM(actSt10rSekizo);

INCLUDE_ASM(actSt10rEne);

INCLUDE_ASM(actSt10rEnemy1);

INCLUDE_ASM(actSt10rEnemy2);

INCLUDE_ASM(actSt10rElv);

INCLUDE_ASM(actSt10rGateXL);

void actSt10rGirlWay(volatile unsigned int self)
{
    long long buf[2];
    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
    _ACTWait(0);
}

void actSt10rExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(282);
    gflagOff(290);

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        OnGirlEscortFlag();
        RequestStageChange(1, boyGObj, girlGObj, 2.0f, 8.0f);
    }
    RequestStageChange(1, boyGObj, 0, 2.0f, 8.0f);
}

void actSt10rChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = chain_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10rChainSwitch(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;
    act->mainMail = 0;
    chain_switch_mes[0].func = actSt10rChainMove;
    act->mail = chain_switch_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10rSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt10rEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    gflagOn(279);
    gflagOn(280);
}
