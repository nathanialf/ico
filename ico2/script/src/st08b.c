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

#ifdef VERSION_NTSC
static ActMail kurenMain_mes[2] = {{376, actSt08bKurenSwitch}, {396}}; /* derived name */

static ActMail kuren_mes[2] = {{397}, {396}}; /* derived name */

static ActMail kurenSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorUpChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorDownChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */
#else
#ifdef VERSION_AUG6
static ActMail kurenMain_mes[2] = {{372, actSt08bKurenSwitch}, {392}}; /* derived name */

static ActMail kuren_mes[2] = {{393}, {392}}; /* derived name */

static ActMail kurenSwitch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorUpChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorDownChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_JUN26
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
#else
static ActMail kurenMain_mes[2] = {{406, actSt08bKurenSwitch}, {429}}; /* derived name */

static ActMail kuren_mes[2] = {{430}, {429}}; /* derived name */

static ActMail kurenSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorDownChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif
#endif

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec kurenSwitchPos = {{248.0f, -2626.0f, 705.0f, 1.0f}}; /* derived name */

#ifndef VERSION_JUN26
static const ConstVec kurenSwitch2Pos = {{280.0f, -3748.0f, 2416.0f, 1.0f}}; /* derived name */
#endif

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

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
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
#ifdef VERSION_AUG6
        stage_SetAnimation(334, 1, frame - 60);
        _ACTWait(1);
        HotInitCageGeo(scpSearchGobj(335));
        HotInitCageGeo(scpSearchGobj(334));
#else
        stage_SetAnimation(335, 1, frame - 60);
        _ACTWait(1);
        HotInitCageGeo(scpSearchGobj(336));
        HotInitCageGeo(scpSearchGobj(335));
#endif
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

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(334, frame, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(335, frame, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);

    if (gflagChk(73) != 0) {
#ifdef VERSION_AUG6
        scpSearchGobj(335)->active = 1;
        scpSearchGobj(334)->active = 0;
#else
        scpSearchGobj(336)->active = 1;
        scpSearchGobj(335)->active = 0;
#endif
        _ACTWait(1);
        gflagOff(73);
    } else {
        gflagOn(73);
    }

    kurenSwitch_mes[0].func = actSt08bKurenMain;
    sub->mail = kurenSwitch_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

void actSt08bKurenLeft(GObj *volatile self)
{
    ReviveAllCarryableItemsWithNonSleepFrame(300);

#ifdef VERSION_AUG6
    stage_SetAnimation(334, 1, 0);

    scpSearchGobj(335)->active = 0;
    scpSearchGobj(334)->active = 1;

    while (stage_CheckAnimationFrame(334, 5, 0) == 0) {
#else
    stage_SetAnimation(335, 1, 0);

    scpSearchGobj(336)->active = 0;
    scpSearchGobj(335)->active = 1;

    while (stage_CheckAnimationFrame(335, 5, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(334, 215, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(335, 215, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(334, 465, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(335, 465, 0) == 0) {
#endif
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

#ifdef VERSION_AUG6
    stage_SetAnimation(334, 1, 511);

    while (stage_CheckAnimationFrame(334, 732, 0) == 0) {
#else
    stage_SetAnimation(335, 1, 511);

    while (stage_CheckAnimationFrame(335, 732, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(334, 822, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(335, 822, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(334, 995, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(335, 995, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    demoEnd = 1;
    _ACTWait(0);
}
#else
#ifndef VERSION_JUN26
inline void actSt08bKuren(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    kuren_mes[0].func = actSt08bKurenMain;
    act->mail = kuren_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif

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
#ifdef VERSION_JUN26
    static ActMail kurenSwitch_mes[2] = {{377}, {376}}; /* derived name */
    Pos p1;
#else
    Pos p1;
    Pos p2;
#endif
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

#ifdef VERSION_JUN26
    lt_switch_layout(51);

    if (gflagChk(71) != 0) {
        scpAdpcmPlayRequestFunc(53, &h, 1, 1, 1);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    if (gflagChk(80) != 0) {
        scpAdpcmPlayRequestFunc(58, &h, 1, 1, 1);
#endif
        while (h == 0) {
            _ACTWait(1);
        }
        thread = actCreateSubThread(actSt08bKurenRight, 21);
        frame = 1020;
    } else {
#ifdef VERSION_JUN26
        scpAdpcmPlayRequestFunc(52, &h, 1, 1, 1);
#else
        scpAdpcmPlayRequestFunc(57, &h, 1, 1, 1);
#endif
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
#ifdef VERSION_JUN26
        scpAdpcmFadeClose(h, 128);
#else
        scpAdpcmFadeCloseFunc(&h, 128);
#endif
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
#ifdef VERSION_JUN26
        stage_SetAnimation(301, 1, frame - 60);
        _ACTWait(1);
        HotInitCageGeo(scpSearchGobj(327));
        HotInitCageGeo(scpSearchGobj(326));
        _ACTWait(1);
        if (th != 0) {
            scpPlayMot(girlGObj, 521);
            if (gflagChk(71) != 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(366, 1, frame - 60);
#else
        stage_SetAnimation(370, 1, frame - 60);
#endif
        _ACTWait(1);
        HotInitCageGeo(scpSearchGobj(365));
        HotInitCageGeo(scpSearchGobj(364));
        _ACTWait(1);
        if (th != 0) {
            scpPlayMot(girlGObj, 532);
            if (gflagChk(80) != 0) {
#endif
                p1.ll[0] = kurenSwitchPos.d[0];
                p1.ll[1] = kurenSwitchPos.d[1];
                SetDirectRootPosition(girlGObj, &p1);
#ifndef VERSION_JUN26
            } else {
                p2.ll[0] = kurenSwitch2Pos.d[0];
                p2.ll[1] = kurenSwitch2Pos.d[1];
                p2.f[1] += GOBJ_SUB(girlGObj)->skel->pos[1];
                SetDirectRootPosition(girlGObj, &p2);
#endif
            }
        }
        scpFadeIn(3.0f);
    }

#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(301, frame, 1) == 0) {
#else
    if (girlGObj != 0) {
        GetRootPosition(&p1, girlGObj);
        GOBJ_SUB(girlGObj)->root.footPos[1] = p1.f[1];
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(366, frame, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(370, frame, 1) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_JUN26
    lt_switch_layout(50);

    if (gflagChk(71) != 0) {
        scpSearchGobj(327)->active = 1;
        scpSearchGobj(326)->active = 0;
        _ACTWait(1);
        scpWakeupItemWithBoundary(244.0f, -2325.0f, 707.0f, 300.0f);
        gflagOff(71);
    } else {
        gflagOn(71);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    if (gflagChk(80) != 0) {
        scpSearchGobj(365)->active = 1;
        scpSearchGobj(364)->active = 0;
        _ACTWait(1);
        gflagOff(80);
    } else {
        gflagOn(80);
#endif
    }

    kurenSwitch_mes[0].func = actSt08bKurenMain;
    sub->mail = kurenSwitch_mes;
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt08bKurenLeft(GObj *volatile self)
{
#ifdef VERSION_JUN26
    stage_SetAnimation(301, 1, 0);

    scpSearchGobj(327)->active = 0;
    scpSearchGobj(326)->active = 1;
    _ACTWait(1);
    scpWakeupItemWithBoundary(244.0f, -2325.0f, 707.0f, 300.0f);

    while (stage_CheckAnimationFrame(301, 5, 0) == 0) {
#else
    ReviveAllCarryableItemsWithNonSleepFrame(300);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(366, 1, 0);
#else
    stage_SetAnimation(370, 1, 0);
#endif

    scpSearchGobj(365)->active = 0;
    scpSearchGobj(364)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(366, 5, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(370, 5, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(366, 215, 0) == 0) {
#else
#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(301, 215, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(370, 215, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(366, 465, 0) == 0) {
#else
#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(301, 465, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(370, 465, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt08bKurenRight(GObj *volatile self)
{
#ifdef VERSION_JUN26
    stage_SetAnimation(301, 1, 511);
    scpWakeupItemWithBoundary(323.0f, -3749.0f, 2453.0f, 300.0f);

    while (stage_CheckAnimationFrame(301, 732, 0) == 0) {
#else
    ReviveAllCarryableItemsWithNonSleepFrame(300);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(366, 1, 511);
#else
    stage_SetAnimation(370, 1, 511);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(366, 732, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(370, 732, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(366, 822, 0) == 0) {
#else
#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(301, 822, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(370, 822, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(366, 995, 0) == 0) {
#else
#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(301, 995, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(370, 995, 0) == 0) {
#endif
#endif
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
#ifdef VERSION_JUN26
    scpPlayMot(girlGObj, 680);
    scpPlayWaitMotEnd(girlGObj);
    scpPlayMot(girlGObj, 581);
#else
    scpPlayMot(girlGObj, 546);
    scpPlayWaitMotEnd(girlGObj);
    scpPlayMot(girlGObj, 595);
#endif
    scpPlayWaitMotEnd(girlGObj);
    _ACTWait(0);
}

inline void actSt08bDoorEvent(int x)
{
    volatile int local = x;
}
#endif

#ifdef VERSION_JUN26
static ActMail doorDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorUp_mes[2] = {{377}, {376}}; /* derived name */
#else
void actSt08bDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 200.0f) != 0 ||
        (girlGObj != 0 && scpTriggerBall(self, girlGObj, 400.0f) != 0)) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(368, 0, 0);
#else
#ifdef VERSION_NTSC
        stage_SetAnimation(337, 0, 0);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(336, 0, 0);
#else
        stage_SetAnimation(372, 0, 0);
#endif
#endif
#endif
        _ACTWait(60);
        doorDown_mes[0].func = actSt08bDoorDownChk;
        act->mail = doorDown_mes;
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(336, 0, 0);
        doorUp_mes[0].func = actSt08bDoorUpChk;
        act->mail = doorUp_mes;
        ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(335, 0, 0);
        doorUp_mes[0].func = actSt08bDoorUpChk;
        act->mail = doorUp_mes;
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(367, 0, 0);
#else
        stage_SetAnimation(371, 0, 0);
#endif
        doorUp_mes[0].func = actSt08bDoorUpChk;
        act->mail = doorUp_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}
#endif

#ifdef VERSION_NTSC
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

    doorUpChk_mes[0].func = actSt08bDoorDownChk;
    sub->mail = doorUpChk_mes;
    ACTSendMailCorrect(self, 397);
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

    stage_SetAnimation(337, 1, 0);

    buf[0] = doorUpChkPos.d[0];
    buf[1] = doorUpChkPos.d[1];
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(337) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    doorDownChk_mes[0].func = actSt08bDoorUpChk;
    sub->mail = doorDownChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

inline void actSt08bKuren(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    kuren_mes[0].func = actSt08bKurenMain;
    act->mail = kuren_mes;
    ACTSendMailCorrect(self, 397);
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
        ACTSendMailCorrect(self, 397);
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
    scpPlayMot(girlGObj, 657);
    scpPlayWaitMotEnd(girlGObj);
    scpPlayMot(girlGObj, 569);
    scpPlayWaitMotEnd(girlGObj);
    _ACTWait(0);
}

inline void actSt08bDoorEvent(int x)
{
    volatile int local = x;
}
#else
void actSt08bDoorUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_JUN26
    static ActMail doorUpChk_mes[2] = {{377}, {376}}; /* derived name */
#endif
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x4000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt08bDoorUpEffect, 21);

    scpWakeupItemWithBoundary(-1189.0f, -2326.0f, -408.0f, 100.0f);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(367, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(335, 1, 0);
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(302, 1, 0);
#else
    stage_SetAnimation(371, 1, 0);
#endif
#endif
#endif

    buf[0] = doorUpChkPos.d[0];
    buf[1] = doorUpChkPos.d[1];
#ifdef VERSION_AUG6
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(335) == 0) {
#else
#ifdef VERSION_JUN26
    soundSeDefPlay(1170, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1171, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1172, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(302) == 0) {
#else
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(367) == 0) {
#else
    while (stage_CheckAnimationFinish(371) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    doorUpChk_mes[0].func = actSt08bDoorDownChk;
    sub->mail = doorUpChk_mes;
#ifdef VERSION_AUG6
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
#else
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
#endif
}
#endif

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

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
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
#else
#ifdef VERSION_JUN26
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
#else
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

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(368, 1, 0);
#else
    stage_SetAnimation(372, 1, 0);
#endif

    buf[0] = doorUpChkPos.d[0];
    buf[1] = doorUpChkPos.d[1];
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(368) == 0) {
#else
    while (stage_CheckAnimationFinish(372) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    doorDownChk_mes[0].func = actSt08bDoorUpChk;
    sub->mail = doorDownChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif

inline void actSt08bEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_JUN26
    if (gflagChk(72) == 0) {
        ene_mes[0].func = actSt08bEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(81) == 0) {
        ene_mes[0].func = actSt08bEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
#endif
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
#ifdef VERSION_JUN26
    gflagOn(72);
    gflagOn(73);
#else
    gflagOn(81);
    gflagOn(82);
#endif
}

inline void actSt08bEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
#ifdef VERSION_JUN26
    while (gflagChk(73) == 0) {
#else
    while (gflagChk(82) == 0) {
#endif
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
#ifdef VERSION_JUN26
    while (gflagChk(73) == 0) {
#else
    while (gflagChk(82) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}
#endif
