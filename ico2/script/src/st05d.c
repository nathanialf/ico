#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "geometryManager.h"
#include "item.h"
#include "quaternion.h"
#include "typedef.h"
#include "main.h"

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec door2UpChkPos = {{-702.0f, -1886.0f, -5680.0f, 0.0f}}; /* derived name */

static const ConstVec door2UpEffectPos = {{-704.0f, -1700.0f, -5679.0f, 1.0f}}; /* derived name */

static const ConstVec door2UpEffect2Pos = {{-704.0f, -1955.0f, -5679.0f, 1.0f}}; /* derived name */

#ifdef VERSION_JUN26
/* The functions stand in the order of the stage's source (aug6's TRFILE
   numbers them so), with actSt05dDoor2 after the two checks as this
   build's .text has it. The ones defined inline are output at the end of
   the file, in the order of their declarations. door2Up_mes is a
   file-scope static; the checks' tables are static locals of their
   posters (gcc's local name.N symbol); .data keeps the source order. */

inline void actSt05dDoor2Event(int x)
{
    volatile int local = x;
}

inline void actSt05dDoor2UpEffect(GObj *volatile self);
void actSt05dDoor2DownEffect(GObj *volatile self);
inline void actSt05dEneChk(GObj *volatile self);

static ActMail door2Up_mes[2] = {{377}, {376}}; /* derived name */
#else
void actSt05dDoor2UpEffect(GObj *volatile self);
void actSt05dDoor2DownEffect(GObj *volatile self);
void actSt05dEneChk(GObj *volatile self);

#ifdef VERSION_NTSC
static ActMail door2Down_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door2Up_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door2UpChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door2DownChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */
#else
#ifdef VERSION_AUG6
static ActMail door2Down_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door2Up_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door2UpChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door2DownChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */
#else
static void actSt05dCrestHintChk(GObj *volatile self);

static ActMail door2Down_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door2Up_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door2UpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door2DownChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crestHint_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif
#endif

void actSt05dDoor2DownChk(GObj *volatile self);
void actSt05dDoor2UpChk(GObj *volatile self);

#ifndef VERSION_JUN26
void actSt05dDoor2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 400.0f) != 0 ||
        (girlGObj != 0 && scpTriggerBall(self, girlGObj, 400.0f) != 0)) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(345, 0, 0);
#else
#ifdef VERSION_NTSC
        stage_SetAnimation(316, 0, 0);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(315, 0, 0);
#else
        stage_SetAnimation(349, 0, 0);
#endif
#endif
#endif
        _ACTWait(60);
        door2Down_mes[0].func = actSt05dDoor2DownChk;
        act->mail = door2Down_mes;
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(315, 0, 0);
        door2Up_mes[0].func = actSt05dDoor2UpChk;
        act->mail = door2Up_mes;
        ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(314, 0, 0);
        door2Up_mes[0].func = actSt05dDoor2UpChk;
        act->mail = door2Up_mes;
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(344, 0, 0);
#else
        stage_SetAnimation(348, 0, 0);
#endif
        door2Up_mes[0].func = actSt05dDoor2UpChk;
        act->mail = door2Up_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}
#endif

#ifdef VERSION_JUN26
void actSt05dDoor2UpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail door2UpChk_mes[2] = {{377}, {376}}; /* derived name */
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt05dDoor2UpEffect, 21);

    scpWakeupItemWithBoundary(-603.0f, -1773.0f, -5680.0f, 100.0f);
    scpWakeupItemWithBoundary(-815.0f, -1773.0f, -5676.0f, 100.0f);

    stage_SetAnimation(282, 1, 0);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
    soundSeDefPlay(1170, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1171, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1172, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(282) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2UpChk_mes[0].func = actSt05dDoor2DownChk;
    sub->mail = door2UpChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt05dDoor2UpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door2UpEffectPos.d[0];
    long long v0b = door2UpEffect2Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door2UpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door2UpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}
#else
#ifdef VERSION_NTSC
void actSt05dDoor2UpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt05dDoor2UpEffect, 21);

    ReviveAllCarryableItemsWithNonSleepFrame(60);

    stage_SetAnimation(315, 1, 0);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(315) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2UpChk_mes[0].func = actSt05dDoor2DownChk;
    sub->mail = door2UpChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt05dDoor2DownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt05dDoor2DownEffect, 21);

    ReviveAllCarryableItemsWithNonSleepFrame(60);

    stage_SetAnimation(316, 1, 0);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(316) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2DownChk_mes[0].func = actSt05dDoor2UpChk;
    sub->mail = door2DownChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt05dEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(153) == 0) {
        ene_mes[0].func = actSt05dEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt05dEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(154) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_MaskOff(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt05dEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(154) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}
#else
void actSt05dDoor2UpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt05dDoor2UpEffect, 21);

    ReviveAllCarryableItemsWithNonSleepFrame(60);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(344, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(314, 1, 0);
#else
    stage_SetAnimation(348, 1, 0);
#endif
#endif

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
#ifdef VERSION_AUG6
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(314) == 0) {
#else
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(344) == 0) {
#else
    while (stage_CheckAnimationFinish(348) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    door2UpChk_mes[0].func = actSt05dDoor2DownChk;
    sub->mail = door2UpChk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt05dDoor2DownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt05dDoor2DownEffect, 21);

    ReviveAllCarryableItemsWithNonSleepFrame(60);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(345, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(315, 1, 0);
#else
    stage_SetAnimation(349, 1, 0);
#endif
#endif

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
#ifdef VERSION_AUG6
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(315) == 0) {
#else
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(345) == 0) {
#else
    while (stage_CheckAnimationFinish(349) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    door2DownChk_mes[0].func = actSt05dDoor2UpChk;
    sub->mail = door2DownChk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt05dEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
#ifdef VERSION_AUG6
    _ACTWait(1);

    if (gflagChk(153) == 0) {
        ene_mes[0].func = actSt05dEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 393);
#else
    GObj *g;
    short rot;

    _ACTWait(1);

    g = scpSearchGobj(1458);
    rot = scpGetRotObjectCurrentRot(1556);

    GetRootQuaternion(GetCurrentQuaternion(), g);
    RotQuaternionY(GetCurrentQuaternion(), rot);
    SetRootQuaternion(g, GetCurrentQuaternion());
    UpdateRootMatrix(g);

    if (gflagChk(171) == 0) {
        ene_mes[0].func = actSt05dEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt05dEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
#ifdef VERSION_AUG6

    while (gflagChk(154) == 0) {
#else
    Generator_Mask(scpSearchGobj(1477));
    Generator_Mask(scpSearchGobj(1478));
    while (gflagChk(172) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
#ifndef VERSION_AUG6
    Generator_Call(scpSearchGobj(1477));
    Generator_Call(scpSearchGobj(1478));
#endif
}

void actSt05dEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
#ifdef VERSION_AUG6
    while (gflagChk(154) == 0) {
#else
    while (gflagChk(172) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
#ifndef VERSION_AUG6
}

void actSt05dCrestHint(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(173) == 0) {
        SleepHint(25);
        crestHint_mes[0].func = actSt05dCrestHintChk;
        act->mail = crestHint_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
#endif
}
#endif

void actSt05dDoor2Event(int x)
{
    volatile int local = x;
}

void actSt05dDoor2UpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door2UpEffectPos.d[0];
    long long v0b = door2UpEffect2Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door2UpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door2UpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}
#endif

#ifdef VERSION_JUN26
inline void actSt05dDoor2DownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door2UpEffect2Pos.d[0];
    long long v0b = door2UpEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door2UpEffect2Pos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door2UpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}
#else
void actSt05dDoor2DownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door2UpEffect2Pos.d[0];
    long long v0b = door2UpEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door2UpEffect2Pos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door2UpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}
#endif

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt05dEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (girlGObj == 0 || gflagChk(152) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(153);
    gflagOn(154);
}
#else
#ifdef VERSION_JUN26
void actSt05dDoor2DownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail door2DownChk_mes[2] = {{377}, {376}}; /* derived name */
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt05dDoor2DownEffect, 21);

    scpWakeupItemWithBoundary(-603.0f, -1773.0f, -5680.0f, 100.0f);
    scpWakeupItemWithBoundary(-815.0f, -1773.0f, -5676.0f, 100.0f);

    stage_SetAnimation(283, 1, 0);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
    soundSeDefPlay(1170, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1171, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1172, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(283) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2DownChk_mes[0].func = actSt05dDoor2UpChk;
    sub->mail = door2DownChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt05dDoor2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    stage_SetAnimation(282, 0, 0);
    door2Up_mes[0].func = actSt05dDoor2UpChk;
    act->mail = door2Up_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

void actSt05dEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(146) == 0) {
        ene_mes[0].func = actSt05dEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt05dEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (girlGObj == 0 || gflagChk(145) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(146);
    gflagOn(147);
}

void actSt05dEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(147) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_MaskOff(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}
#else
void actSt05dEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (girlGObj == 0 || gflagChk(170) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(171);
    gflagOn(172);
}

static void actSt05dCrestHintChk(GObj *volatile self)
{
    while (gflagChk(243) == 0 || gflagChk(244) == 0 || gflagChk(245) == 0 || gflagChk(232) != 0) {
        _ACTWait(1);
    }
    gflagOn(173);
    WakeupHint(25);
}
#endif
#endif

#ifdef VERSION_JUN26
void actSt05dEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(147) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}
#endif
