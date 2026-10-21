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

/* .data: actor mail packets. */

static ActMail elvMain_mes[2] = {{356, actSt09aElvSwitch}, {376}}; /* derived name */

static ActMail elv_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elvSwitchUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elvSwitchDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elvDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elvUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail intro_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brgMain_mes[2] = {{357, actSt09aBrgSwitch}, {376}}; /* derived name */

static ActMail brg_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brgSwitch_mes[2] = {{377}, {376}}; /* derived name */

/* .sdata: the bridge stream handle. */
SqEntry *st09a_brg = 0;

/* The stone statue's sound position, a 16-byte constant vector template: the
   float view carries the values, the long long view is the one the copy reads. */
static const ConstVec sekizoPos = {{1548.0f, -412.0f, -608.0f, 0.0f}}; /* derived name */

void actSt09aInit(void)
{
    if (gflagChk(77) == 0) {
        stage_SetAnimation(309, 0, 0);
    } else {
        stage_SetAnimation(309, 0, -1);
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

    stage_SetAnimation(306, 1, 0);

    se = soundSeDefPlay(1167, 0, 0, 1);

    gflagOn(74);

    while (stage_CheckAnimationFrame(306, 210, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    UnlockForceGroundParent(boyGObj);

    lt_switch_layout(50);

    elvDown_mes[0].func = actSt09aElvMain;
    act->mail = elvDown_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt09aSekizo(GObj *volatile self)
{
    GObj *x = self;
    long long buf[2];

    actInitialize(self);
    _ACTWait(1);

    buf[0] = sekizoPos.d[0];
    buf[1] = sekizoPos.d[1];
    soundSeDefPlay(1290, 0, (float *)buf, 1);
    soundSeDefPlay(1291, 0, (float *)buf, 1);
    soundSeDefPlay(1292, 0, (float *)buf, 1);

    scpSekizou(self, 75, 307, 0, 21, -1350.0f, -100.0f, 1515.0f, -1450.0f, -100.0f, 1515.0f);
}

void actSt09aBrgDown(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(77);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(83, &st09a_brg, 1, 1, 1);

    while (st09a_brg == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(309, 1, 0);

    while (stage_CheckAnimationFrame(309, 115, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(309, 165, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(309) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt09aElv(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(74) != 0) {
        stage_SetAnimation(306, 0, 210);
    } else {
        stage_SetAnimation(306, 0, 0);
    }

    elv_mes[0].func = actSt09aElvMain;
    act->mail = elv_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt09aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(76) == 0) {
        intro_mes[0].func = actSt09aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt09aBrg(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(77) == 0) {
        brg_mes[0].func = actSt09aBrgMain;
        act->mail = brg_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

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

    if (gflagChk(74) != 0) {
        elvSwitchUp_mes[0].func = actSt09aElvUp;
        sub->mail = elvSwitchUp_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }

    elvSwitchDown_mes[0].func = actSt09aElvDown;
    sub->mail = elvSwitchDown_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt09aElvUp(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    /* the sound handle, which the sound subsystem owns; it is kept across
       the animation wait and read again for soundSeDefStop */
    volatile int se;

    lt_switch_layout(51);

    stage_SetAnimation(306, 1, 211);

    se = soundSeDefPlay(1167, 0, 0, 1);

    gflagOff(74);

    while (stage_CheckAnimationFrame(306, 420, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    lt_switch_layout(50);

    elvUp_mes[0].func = actSt09aElvMain;
    act->mail = elvUp_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt09aSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt09aIntroChk(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(76);

    scpBoyControlReadDisable = 1;
    _ACTWait(1);

    stage_SetAnimation(308, 1, 0);

    while (stage_CheckAnimationFinish(308) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
}

void actSt09aBrgMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

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
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}
