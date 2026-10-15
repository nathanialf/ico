#include "st09a.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "typedef.h"
#include "main.h"
#include "include_asm.h"

/* .data: actor mail packets. */

static ActMail elvMain_mes[2] = {{376, actSt09aElvSwitch}, {396}}; /* derived name */

static ActMail elv_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elvSwitchUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elvSwitchDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elvDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elvUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brgMain_mes[2] = {{377, actSt09aBrgSwitch}, {396}}; /* derived name */

static ActMail brg_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brgSwitch_mes[2] = {{397}, {396}}; /* derived name */

/* .sdata: the bridge stream handle. */
SqEntry *st09a_brg = 0;

void actSt09aInit(void)
{
    if (gflagChk(79) == 0) {
        stage_SetAnimation(343, 0, 0);
    } else {
        stage_SetAnimation(343, 0, -1);
    }
}

void actSt09aElvDown(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    /* the sound handle, which the sound subsystem owns; it is kept across
       the animation wait and read again for soundSeDefStop */
    volatile int se;

    lt_switch_layout(51);
    LockForceGroundParent(boyGObj);

    stage_SetAnimation(340, 1, 0);

    se = soundSeDefPlay(1193, 0, 0, 1);

    gflagOn(76);

    while (stage_CheckAnimationFrame(340, 210, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    UnlockForceGroundParent(boyGObj);

    lt_switch_layout(50);

    elvDown_mes[0].func = actSt09aElvMain;
    act->mail = elvDown_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

INCLUDE_ASM(actSt09aProc_0022B9A8);

void actSt09aBrgDown(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(79);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(88, &st09a_brg, 1, 1, 1);

    while (st09a_brg == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(343, 1, 0);

    while (stage_CheckAnimationFrame(343, 115, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(343, 165, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(343) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

INCLUDE_ASM(actSt09aElv);

INCLUDE_ASM(actSt09aIntro);

INCLUDE_ASM(actSt09aBrg);

void actSt09aElvMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = elvMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt09aElvSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    if (gflagChk(76) != 0) {
        elvSwitchUp_mes[0].func = actSt09aElvUp;
        sub->mail = elvSwitchUp_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }

    elvSwitchDown_mes[0].func = actSt09aElvDown;
    sub->mail = elvSwitchDown_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt09aElvUp(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    /* the sound handle, which the sound subsystem owns; it is kept across
       the animation wait and read again for soundSeDefStop */
    volatile int se;

    lt_switch_layout(51);

    stage_SetAnimation(340, 1, 211);

    se = soundSeDefPlay(1193, 0, 0, 1);

    gflagOff(76);

    while (stage_CheckAnimationFrame(340, 420, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    lt_switch_layout(50);

    elvUp_mes[0].func = actSt09aElvMain;
    act->mail = elvUp_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt09aSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt09aIntroChk(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(78);

    scpBoyControlReadDisable = 1;
    _ACTWait(1);

    stage_SetAnimation(342, 1, 0);

    while (stage_CheckAnimationFinish(342) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
}

void actSt09aBrgMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = brgMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt09aBrgSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    brgSwitch_mes[0].func = actSt09aBrgDown;
    sub->mail = brgSwitch_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
