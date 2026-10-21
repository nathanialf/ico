#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "fightSound.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "item.h"
#include "spider.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

/* .sdata: the prototype stair's stream handle, its shake and the shake's
   volume. */
SqEntry *proto = 0;

unsigned int proto_yure = 0;

unsigned char proto_yure_vol = 0;

/* .rodata: six 16-byte constant vectors, each named for the first actor that
   copies it.  The float view carries the values, the long long view is the
   one the copies read. */

static const ConstVec door2UpChkPos = {{0.0f, -422.0f, 1630.0f, 0.0f}}; /* derived name */

static const ConstVec door2UpEffectPos = {{0.0f, -150.0f, 1640.0f, 1.0f}}; /* derived name */

static const ConstVec door2UpEffect2Pos = {{0.0f, -450.0f, 1640.0f, 1.0f}}; /* derived name */

static const ConstVec door1UpChkPos = {{-1.0f, -184.0f, -57.0f, 0.0f}}; /* derived name */

static const ConstVec door1UpEffectPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec door1UpEffect2Pos = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

/* The functions stand in the order of the stage's source (aug6's TRFILE
   numbers them so). The ones defined inline are output at the end of the
   file, in the order of their declarations (the entry points below
   first), which gives this build's .text order; the others are output
   where they stand. The mail records, each the usual pair (the 377 entry
   whose handler the sender fills in and the 376 terminator), are
   file-scope statics ahead of the actors that install them, except the
   door checks' records, static locals of their posters (gcc's local name.N
   symbol); .data keeps the source order. */

void actSt00aEne(GObj *volatile self);
void actSt00aEnemy1(GObj *volatile self);
void actSt00aEnemy2(GObj *volatile self);
void actSt00aStair(GObj *volatile self);
void actSt00aDoor1(GObj *volatile self);
void actSt00aDoor2(GObj *volatile self);
void actSt00aAtr2(GObj *volatile self);

void actSt00aInit(void)
{
    if (gflagChk(37) == 0) {
        stage_SetAnimation(68, 0, 0);
        stage_SetAnimation(67, 0, 0);
    } else {
        stage_SetAnimation(68, 0, -1);
        stage_SetAnimation(67, 0, -1);
    }
}

void actSt00aAtr2Chk(GObj *volatile self);

static ActMail atr2_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt00aAtr2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(38) == 0) {
        atr2_mes[0].func = actSt00aAtr2Chk;
        act->mail = atr2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt00aAtr2Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(38);
}

void actSt00aEneChk(GObj *volatile self);

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt00aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(38) == 0) {
        ene_mes[0].func = actSt00aEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt00aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (gflagChk(38) == 0 || gflagChk(34) != 0) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(35);
    _ACTWait(60);
    gflagOn(36);
    stage_SetAnimation(142, 1, 0);
    _ACTWait(150);
    WakeUpSpidersFromGenerator(scpSearchGobj(248));
    WakeUpSpidersFromGenerator(scpSearchGobj(249));
    while (stage_CheckAnimationFinish(142) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(50);
    _ACTWait(120);
    scpBoyControlReadDisable = 0;
    gflagOff(35);
}

inline void actSt00aEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(36) == 0) {
        _ACTWait(1);
    }
    _ACTWait(50);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
}

inline void actSt00aEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(36) == 0) {
        _ACTWait(1);
    }
    _ACTWait(160);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
}

/* No .sbss here in this build: no function of the demo addresses such a flag. */

void actSt00aStairChk(GObj *volatile self);

static ActMail stair_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt00aStair(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(37) == 0) {
        stair_mes[0].func = actSt00aStairChk;
        act->mail = stair_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(235)->active = 0;
    }
}

void actSt00aStairChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(238), 90.0f) != 0 || gflagChk(35) != 0) {
        _ACTWait(1);
    }
    gflagOn(34);
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(37);
    scpSleepEnemyAll();
    _ACTWait(60);
    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(23, &proto, 1, 1, 1);
    while (proto == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(67, 1, 0);
    _ACTWait(90);
    iosPadActRequest(boyPad, 17);
    while (stage_CheckAnimationFinish(67) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    stage_SetAnimation(68, 1, 0);
    proto_yure = iosPadActRequest(boyPad, 9);
    proto_yure_vol = 128;
    iosPadActVolumeSet(proto_yure, 128);
    _ACTWait(500);
    iosPadActStop(proto_yure);
    while (stage_CheckAnimationFinish(68) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(235)->active = 0;
    lt_switch_layout(50);
    _ACTWait(120);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    gflagOff(34);
    fightSoundProcessRequestStart();
}

inline void actSt00aDoor2Event(int x)
{
    volatile int local = x;
}

void actSt00aDoor2UpChk(GObj *volatile self);
void actSt00aDoor2DownChk(GObj *self);
void actSt00aDoor2UpEffect(GObj *volatile self);
void actSt00aDoor2DownEffect(GObj *volatile self);

static ActMail door2Down_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door2Up_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt00aDoor2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 200.0f) != 0) {
        stage_SetAnimation(72, 0, 0);
        _ACTWait(60);
        door2Down_mes[0].func = actSt00aDoor2DownChk;
        act->mail = door2Down_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(71, 0, 0);
        door2Up_mes[0].func = actSt00aDoor2UpChk;
        act->mail = door2Up_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt00aDoor2UpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail door2Upchk_mes[2] = {{377}, {376}}; /* derived name */
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor2UpEffect, 21);

    stage_SetAnimation(71, 1, 0);

    scpWakeupItemWithBoundary(-6.0f, -221.0f, 1504.0f, 100.0f);

    _ACTWait(1);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
    soundSeDefPlay(1170, 0, (float *)buf, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1171, 0, (float *)buf, 1);
    _ACTWait(60);
    soundSeDefStop(h);
    soundSeDefPlay(1172, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(71) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2Upchk_mes[0].func = actSt00aDoor2DownChk;
    sub->mail = door2Upchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt00aDoor2UpEffect(GObj *volatile self)
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

inline void actSt00aDoor2DownEffect(GObj *volatile self)
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

void actSt00aDoor2DownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail door2Downchk_mes[2] = {{377}, {376}}; /* derived name */
    ConstVec pos;
    int h;

    while (1) {
        if (scpTriggerFloorAttrTargetMan(self, 0x3000000) == 0)
            break;
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor2DownEffect, 21);

    stage_SetAnimation(72, 1, 0);

    scpWakeupItemWithBoundary(-6.0f, -221.0f, 1504.0f, 100.0f);

    _ACTWait(1);

    pos = door2UpChkPos;
    soundSeDefPlay(1170, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1171, 0, pos.f, 1);
    _ACTWait(45);
    soundSeDefStop(h);
    soundSeDefPlay(1172, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(72) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2Downchk_mes[0].func = actSt00aDoor2UpChk;
    sub->mail = door2Downchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt00aDoor1Event(int x)
{
    volatile int local = x;
}

void actSt00aDoor1UpChk(GObj *volatile self);
void actSt00aDoor1DownChk(GObj *self);
void actSt00aDoor1UpEffect(GObj *volatile self);
void actSt00aDoor1DownEffect(GObj *volatile self);

static ActMail door1Down_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door1Up_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt00aDoor1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 200.0f) != 0) {
        stage_SetAnimation(70, 0, 0);
        _ACTWait(60);
        door1Down_mes[0].func = actSt00aDoor1DownChk;
        act->mail = door1Down_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(69, 0, 0);
        door1Up_mes[0].func = actSt00aDoor1UpChk;
        act->mail = door1Up_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt00aDoor1UpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail door1Upchk_mes[2] = {{377}, {376}}; /* derived name */
    ConstVec pos;
    int h;

    while (1) {
        if (scpTriggerFloorAttrTargetMan(self, 0x4000000) != 0)
            break;
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor1UpEffect, 21);

    scpWakeupItemWithBoundary(-8.0f, -73.0f, 64.0f, 100.0f);

    stage_SetAnimation(69, 1, 0);

    pos = door1UpChkPos;
    soundSeDefPlay(1170, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1171, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1172, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(69) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door1Upchk_mes[0].func = actSt00aDoor1DownChk;
    sub->mail = door1Upchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt00aDoor1UpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door1UpEffectPos.d[0];
    long long v0b = door1UpEffect2Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door1UpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door1UpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

inline void actSt00aDoor1DownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door1UpEffect2Pos.d[0];
    long long v0b = door1UpEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door1UpEffect2Pos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door1UpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

/* actSt00aDoor1DownChk's record, file-scope while that function is a stub
   (its static local's slot). */
static ActMail door1Downchk_mes[2] = {{377}, {376}}; /* derived name */

INCLUDE_ASM(actSt00aDoor1DownChk);
