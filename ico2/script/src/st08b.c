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

static ActMail kurenMain_mes[2] = {{372, actSt08bKurenSwitch}, {392}}; /* derived name */

static ActMail kuren_mes[2] = {{393}, {392}}; /* derived name */

static ActMail kurenSwitch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorUpChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorDownChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec kurenSwitchPos = {{248.0f, -2626.0f, 705.0f, 1.0f}}; /* derived name */

static const ConstVec kurenSwitch2Pos = {{280.0f, -3748.0f, 2416.0f, 1.0f}}; /* derived name */

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

void actSt08bKurenSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    Pos p1;
    Pos p2;
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

    if (gflagChk(73) != 0) {
        scpAdpcmPlayRequestFunc(56, &h, 1, 1, 1);
        while (h == 0) {
            _ACTWait(1);
        }
        thread = actCreateSubThread(actSt08bKurenRight, 21);
        frame = 1020;
    } else {
        scpAdpcmPlayRequestFunc(55, &h, 1, 1, 1);
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
        stage_SetAnimation(334, 1, frame - 60);
        _ACTWait(1);
        HotInitCageGeo(scpSearchGobj(335));
        HotInitCageGeo(scpSearchGobj(334));
        _ACTWait(1);
        if (th != 0) {
            scpPlayMot(girlGObj, 514);
            if (gflagChk(73) != 0) {
                p1.ll[0] = kurenSwitchPos.d[0];
                p1.ll[1] = kurenSwitchPos.d[1];
                SetDirectRootPosition(girlGObj, &p1);
            } else {
                p2.ll[0] = kurenSwitch2Pos.d[0];
                p2.ll[1] = kurenSwitch2Pos.d[1];
                p2.f[1] += GOBJ_SUB(girlGObj)->skel->pos[1];
                SetDirectRootPosition(girlGObj, &p2);
            }
        }
        scpFadeIn(3.0f);
    }

    while (stage_CheckAnimationFrame(334, frame, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);

    if (gflagChk(73) != 0) {
        scpSearchGobj(335)->active = 1;
        scpSearchGobj(334)->active = 0;
        _ACTWait(1);
        gflagOff(73);
    } else {
        gflagOn(73);
    }

    kurenSwitch_mes[0].func = actSt08bKurenMain;
    sub->mail = kurenSwitch_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt08bKurenLeft(GObj *volatile self)
{
    ReviveAllCarryableItemsWithNonSleepFrame(300);

    stage_SetAnimation(334, 1, 0);

    scpSearchGobj(335)->active = 0;
    scpSearchGobj(334)->active = 1;

    while (stage_CheckAnimationFrame(334, 5, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFrame(334, 215, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(334, 465, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt08bKurenRight(GObj *volatile self)
{
    ReviveAllCarryableItemsWithNonSleepFrame(300);

    stage_SetAnimation(334, 1, 511);

    while (stage_CheckAnimationFrame(334, 732, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(334, 822, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(334, 995, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt08bDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 200.0f) != 0 ||
        (girlGObj != 0 && scpTriggerBall(self, girlGObj, 400.0f) != 0)) {
        stage_SetAnimation(336, 0, 0);
        _ACTWait(60);
        doorDown_mes[0].func = actSt08bDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(335, 0, 0);
        doorUp_mes[0].func = actSt08bDoorUpChk;
        act->mail = doorUp_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt08bDoorUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x4000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt08bDoorUpEffect, 21);

    scpWakeupItemWithBoundary(-1189.0f, -2326.0f, -408.0f, 100.0f);

    stage_SetAnimation(335, 1, 0);

    buf[0] = doorUpChkPos.d[0];
    buf[1] = doorUpChkPos.d[1];
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(335) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    doorUpChk_mes[0].func = actSt08bDoorDownChk;
    sub->mail = doorUpChk_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt08bDoorDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x4000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt08bDoorDownEffect, 21);

    scpWakeupItemWithBoundary(-1189.0f, -2326.0f, -408.0f, 100.0f);

    stage_SetAnimation(336, 1, 0);

    buf[0] = doorUpChkPos.d[0];
    buf[1] = doorUpChkPos.d[1];
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(336) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    doorDownChk_mes[0].func = actSt08bDoorUpChk;
    sub->mail = doorDownChk_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt08bKuren(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    kuren_mes[0].func = actSt08bKurenMain;
    act->mail = kuren_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt08bEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(74) == 0) {
        ene_mes[0].func = actSt08bEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

inline void actSt08bEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(75) == 0) {
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
    while (gflagChk(75) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

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

inline void actSt08aGirlYoro(GObj *volatile self)
{
    scpPlayStart(girlGObj);
    scpPlayMot(girlGObj, 659);
    scpPlayWaitMotEnd(girlGObj);
    scpPlayMot(girlGObj, 570);
    scpPlayWaitMotEnd(girlGObj);
    _ACTWait(0);
}

inline void actSt08bDoorEvent(int x)
{
    volatile int local = x;
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

inline void actSt08bEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(74);
    gflagOn(75);
}
