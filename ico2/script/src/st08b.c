#include "st08b.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "cage.h"
#include "geometryManager.h"
#include "item.h"
#include "typedef.h"
#include "main.h"
#include "script.h"

/* The functions stand in the order of the stage's source (aug6's TRFILE
   numbers them so), with actSt08bKuren and actSt08bDoor after the door
   checks as this build's .text has them. The ones defined inline are
   output at the end of the file in the order st08b.h declares them. The
   tables the actors install with actInitialize are file-scope statics;
   the ones the handlers install through GOBJ_ACT are static locals of
   their posters (gcc's local name.N symbol); .data keeps the source
   order. */

static ActMail kurenMain_mes[2] = {{356, actSt08bKurenSwitch}, {376}}; /* derived name */

static ActMail kuren_mes[2] = {{377}, {376}}; /* derived name */

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec kurenSwitchPos = {{248.0f, -2626.0f, 705.0f, 1.0f}}; /* derived name */

/* PAL's kurenSwitch2Pos is not in this build's .rodata */
static const ConstVec doorUpChkPos = {{-1319.0f, -2429.0f, -405.0f, 0.0f}}; /* derived name */

static const ConstVec doorUpEffectPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect2Pos = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

typedef union Pos { /* field names derived */
    long long ll[2];
    float f[4];
} Pos; /* derived name */

void actSt08bKurenLeft(GObj *volatile self);
void actSt08bKurenRight(GObj *volatile self);
void actSt08bDoorUpChk(GObj *volatile self);
void actSt08bDoorDownChk(GObj *volatile self);

/* .sbss: the demo's own end flag, raised by the subthreads the wait loop below
   spins for. */
static int demoEnd;

inline void actSt08bKurenMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;
    if (girlGObj != 0) {
        scpPlayEnd(girlGObj);
    }
    sub->mainMail = kurenMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt08bKurenSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail kurenSwitch_mes[2] = {{377}, {376}}; /* derived name */
    Pos p1;
    SqEntry *h;
    GProc *th = 0;
    GProc *thread;
    int frame;

    scpBoyControlReadDisable = 1;
    sub->mainMail = 0;

    if (girlGObj != 0) {
        if (scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
            th = actCreateSubThread(actSt08aGirlYoro, 21);
        }
    }

    lt_switch_layout(51);

    if (gflagChk(71) != 0) {
        scpAdpcmPlayRequestFunc(53, &h, 1, 1, 1);
        while (h == 0) {
            _ACTWait(1);
        }
        thread = actCreateSubThread(actSt08bKurenRight, 21);
        frame = 1020;
    } else {
        scpAdpcmPlayRequestFunc(52, &h, 1, 1, 1);
        while (h == 0) {
            _ACTWait(1);
        }
        thread = actCreateSubThread(actSt08bKurenLeft, 21);
        frame = 510;
    }

    _ACTWait(3);

    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&thread->thread, 34);
    if (th != 0) {
        iosThreadSetPri(&th->thread, 34);
    }

    if (demoEnd == 0) {
        scpAdpcmFadeClose(h, 128);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        stage_SetAnimation(301, 1, frame - 60);
        _ACTWait(1);
        HotInitCageGeo(scpSearchGobj(327));
        HotInitCageGeo(scpSearchGobj(326));
        _ACTWait(1);
        if (th != 0) {
            scpPlayMot(girlGObj, 521);
            if (gflagChk(71) != 0) {
                p1.ll[0] = kurenSwitchPos.d[0];
                p1.ll[1] = kurenSwitchPos.d[1];
                SetDirectRootPosition(girlGObj, &p1);
            }
        }
        scpFadeIn(3.0f);
    }

    while (stage_CheckAnimationFrame(301, frame, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);

    if (gflagChk(71) != 0) {
        scpSearchGobj(327)->active = 1;
        scpSearchGobj(326)->active = 0;
        _ACTWait(1);
        scpWakeupItemWithBoundary(244.0f, -2325.0f, 707.0f, 300.0f);
        gflagOff(71);
    } else {
        gflagOn(71);
    }

    kurenSwitch_mes[0].func = actSt08bKurenMain;
    sub->mail = kurenSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt08bKurenLeft(GObj *volatile self)
{
    stage_SetAnimation(301, 1, 0);

    scpSearchGobj(327)->active = 0;
    scpSearchGobj(326)->active = 1;
    _ACTWait(1);
    scpWakeupItemWithBoundary(244.0f, -2325.0f, 707.0f, 300.0f);

    while (stage_CheckAnimationFrame(301, 5, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFrame(301, 215, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(301, 465, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt08bKurenRight(GObj *volatile self)
{
    stage_SetAnimation(301, 1, 511);
    scpWakeupItemWithBoundary(323.0f, -3749.0f, 2453.0f, 300.0f);

    while (stage_CheckAnimationFrame(301, 732, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(301, 822, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(301, 995, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    demoEnd = 1;
    _ACTWait(0);
}

inline void actSt08aGirlYoro(GObj *volatile self)
{
    scpPlayStart(girlGObj);
    scpPlayMot(girlGObj, 680);
    scpPlayWaitMotEnd(girlGObj);
    scpPlayMot(girlGObj, 581);
    scpPlayWaitMotEnd(girlGObj);
    _ACTWait(0);
}

inline void actSt08bDoorEvent(int x)
{
    volatile int local = x;
}

static ActMail doorDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorUp_mes[2] = {{377}, {376}}; /* derived name */

void actSt08bDoorUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail doorUpChk_mes[2] = {{377}, {376}}; /* derived name */
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x4000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt08bDoorUpEffect, 21);

    scpWakeupItemWithBoundary(-1189.0f, -2326.0f, -408.0f, 100.0f);

    stage_SetAnimation(302, 1, 0);

    buf[0] = doorUpChkPos.d[0];
    buf[1] = doorUpChkPos.d[1];
    soundSeDefPlay(1170, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1171, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1172, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(302) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    doorUpChk_mes[0].func = actSt08bDoorDownChk;
    sub->mail = doorUpChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt08bDoorUpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorUpEffectPos.d[0];
    long long v0b = doorUpEffect2Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorUpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

inline void actSt08bDoorDownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorUpEffect2Pos.d[0];
    long long v0b = doorUpEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffect2Pos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorUpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt08bDoorDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail doorDownChk_mes[2] = {{377}, {376}}; /* derived name */
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x4000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt08bDoorDownEffect, 21);

    scpWakeupItemWithBoundary(-1189.0f, -2326.0f, -408.0f, 100.0f);

    stage_SetAnimation(303, 1, 0);

    buf[0] = doorUpChkPos.d[0];
    buf[1] = doorUpChkPos.d[1];
    soundSeDefPlay(1170, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1171, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1172, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(303) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    doorDownChk_mes[0].func = actSt08bDoorUpChk;
    sub->mail = doorDownChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt08bKuren(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    kuren_mes[0].func = actSt08bKurenMain;
    act->mail = kuren_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt08bDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 200.0f) != 0) {
        stage_SetAnimation(303, 0, 0);
        _ACTWait(60);
        doorDown_mes[0].func = actSt08bDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(302, 0, 0);
        doorUp_mes[0].func = actSt08bDoorUpChk;
        act->mail = doorUp_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt08bEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(72) == 0) {
        ene_mes[0].func = actSt08bEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt08bEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(72);
    gflagOn(73);
}

inline void actSt08bEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(73) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

inline void actSt08bEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(73) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}
