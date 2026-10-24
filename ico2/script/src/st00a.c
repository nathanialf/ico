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

#ifdef VERSION_JUN26
#include "spider.h"
#endif

#include "typedef.h"
#include "main.h"
#include "script.h"

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

#ifdef VERSION_JUN26
/* The functions stand in the order of the stage's source (aug6's TRFILE
   numbers them so). The ones defined inline are output at the end of the
   file, in the order of their declarations (the entry points below
   first), which gives this build's .text order; the others are output
   where they stand. The mail records, each the usual pair (the 377 entry
   whose handler the sender fills in and the 376 terminator), are
   file-scope statics ahead of the actors that install them, except the
   first three door checks' records, static locals of their posters (gcc's
   local name.N symbol); .data keeps the source order. */

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

inline void actSt00aAtr2Chk(GObj *volatile self);

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
void actSt00aDoor2DownChk(GObj *volatile self);
inline void actSt00aDoor2UpEffect(GObj *volatile self);
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
#else
/* .data: eleven actor mail records, each the usual pair, the 430 entry whose
   handler the sender fills in and the 429 terminator, named for the actor that
   installs it. */
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#ifdef VERSION_AUG6
static ActMail atr2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

static ActMail stair_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door2Down_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door2Up_mes[2] = {{393}, {392}}; /* derived name */

/* the four door checks' records */
static ActMail door2Upchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door2Downchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door1Down_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door1Up_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door1Upchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door1Downchk_mes[2] = {{393}, {392}}; /* derived name */
#else
static ActMail atr2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

static ActMail stair_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door2Down_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door2Up_mes[2] = {{397}, {396}}; /* derived name */

/* the four door checks' records */
static ActMail door2Upchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door2Downchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door1Down_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door1Up_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door1Upchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door1Downchk_mes[2] = {{397}, {396}}; /* derived name */
#endif

void actSt00aInit(void)
{
    if (gflagChk(38) == 0) {
#ifdef VERSION_AUG6
        stage_SetAnimation(76, 0, 0);
        stage_SetAnimation(73, 0, 0);
    } else {
        stage_SetAnimation(74, 0, -1);
        stage_SetAnimation(73, 0, -1);
#else
        stage_SetAnimation(77, 0, 0);
        stage_SetAnimation(74, 0, 0);
    } else {
        stage_SetAnimation(75, 0, -1);
        stage_SetAnimation(74, 0, -1);
#endif
    }
}

void actSt00aEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(39) == 0) {
#ifdef VERSION_AUG6
            gflagOn(357);
#else
            gflagOn(358);
#endif
        }
    }
}

void actSt00aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (gflagChk(39) == 0 || gflagChk(35) != 0) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(36);
#ifdef VERSION_AUG6
    scpSleepEnemyOne(3415);
    gflagOff(357);
    _ACTWait(60);
    gflagOn(37);
    stage_SetAnimation(155, 1, 0);
    _ACTWait(150);
    while (stage_CheckAnimationFinish(155) == 0) {
#else
    scpSleepEnemyOne(3453);
    gflagOff(358);
    _ACTWait(60);
    gflagOn(37);
    stage_SetAnimation(156, 1, 0);
    _ACTWait(150);
    while (stage_CheckAnimationFinish(156) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(50);
    _ACTWait(120);
    scpBoyControlReadDisable = 0;
    gflagOff(36);
#ifdef VERSION_AUG6
    scpWakeupEnemyOne(3415);
#else
    scpWakeupEnemyOne(3453);
#endif
}

void actSt00aStairChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpTriggerBall(self, scpSearchGobj(248), 90.0f) != 0 || gflagChk(36) != 0) {
#else
    while (scpTriggerBall(self, scpSearchGobj(249), 90.0f) != 0 || gflagChk(36) != 0) {
#endif
        _ACTWait(1);
    }
    gflagOn(35);
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(38);
    scpSleepEnemyAll();
    _ACTWait(60);
    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(20, &proto, 1, 1, 1);
    while (proto == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_AUG6
    stage_SetAnimation(73, 1, 0);
#else
    stage_SetAnimation(74, 1, 0);
#endif
    ReviveAllCarryableItemsWithNonSleepFrame(260);
    _ACTWait(90);
    iosPadActRequest(boyPad, 17);
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(73) == 0) {
#else
    while (stage_CheckAnimationFinish(74) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    stage_SetAnimation(75, 1, 0);
    stage_SetAnimation(76, 1, 0);
#else
    stage_SetAnimation(76, 1, 0);
    stage_SetAnimation(77, 1, 0);
#endif
    proto_yure = iosPadActRequest(boyPad, 9);
    proto_yure_vol = 128;
    iosPadActVolumeSet(proto_yure, 128);
    _ACTWait(500);
    iosPadActStop(proto_yure);
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(76) == 0) {
#else
    while (stage_CheckAnimationFinish(77) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    scpSearchGobj(245)->active = 0;
    scpSearchGobj(244)->active = 1;
#else
    scpSearchGobj(246)->active = 0;
    scpSearchGobj(245)->active = 1;
#endif
    lt_switch_layout(50);
    _ACTWait(120);
    ReviveAllCarryableItemsWithNonSleepFrame(60);
#ifdef VERSION_AUG6
    stage_SetAnimation(74, 0, -1);
    stage_SetAnimation(76, -1, -2);
#else
    stage_SetAnimation(75, 0, -1);
    stage_SetAnimation(77, -1, -2);
#endif
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    gflagOff(35);
    fightSoundProcessRequestStart();
}
#else
static ActMail atr2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail stair_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door2Down_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door2Up_mes[2] = {{430}, {429}}; /* derived name */

/* the four door checks' records */
static ActMail door2Upchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door2Downchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door1Down_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door1Up_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door1Upchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door1Downchk_mes[2] = {{430}, {429}}; /* derived name */

void actSt00aInit(void)
{
    if (gflagChk(41) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(86, 0, 0);
        stage_SetAnimation(83, 0, 0);
#else
        stage_SetAnimation(90, 0, 0);
        stage_SetAnimation(87, 0, 0);
#endif
        SetWayGroupActive(3, 0);
        SetWayGroupActive(13, 1);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(84, 0, -1);
        stage_SetAnimation(83, 0, -1);
#else
        stage_SetAnimation(88, 0, -1);
        stage_SetAnimation(87, 0, -1);
#endif
        FinishHint(1);
        SetWayGroupActive(3, 1);
        SetWayGroupActive(13, 0);
    }
    if (gflagChk(79) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(92, 0, 1);
#else
        stage_SetAnimation(96, 0, 1);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(92, 0, 2);
#else
        stage_SetAnimation(96, 0, 2);
#endif
    }
}

void actSt00aEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(42) == 0) {
            gflagOn(391);
        }
    }
}

void actSt00aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (gflagChk(42) == 0 || gflagChk(38) != 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    gflagOn(39);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSleepEnemyOne(3734);
#else
    scpSleepEnemyOne(3757);
#endif
    scpSleepEnemyAll();
    gflagOff(391);
    _ACTWait(60);
    gflagOn(40);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(173, 1, 0);
#else
    stage_SetAnimation(177, 1, 0);
#endif
    _ACTWait(150);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(173) == 0) {
#else
    while (stage_CheckAnimationFinish(177) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    _ACTWait(120);
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpWakeupEnemyOne(3734);
#else
    scpWakeupEnemyOne(3757);
#endif
    scpWakeupEnemyAll();
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1]);
    gflagOff(39);
}

/* .sbss: the flag the stair-check subthread raises when the demo is over,
   which the wait loop below spins for. */
static int demoEnd;

static void actSt00aStairChkSub(GObj *volatile self);

void actSt00aStairChk(GObj *volatile self)
{
    GProc *th;
    int fade;

    while (scpTriggerBall(self, scpSearchGobj(276), 90.0f) != 0 || gflagChk(39) != 0) {
        _ACTWait(1);
    }
    gflagOn(38);
    FinishHint(1);
    SetWayGroupActive(3, 1);
    SetWayGroupActive(13, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    gflagOn(41);
    scpSleepEnemyAll();
    _ACTWait(60);
    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(21, &proto, 1, 1, 1);
    while (proto == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(83, 1, 0);
#else
    stage_SetAnimation(87, 1, 0);
#endif
    ReviveAllCarryableItemsWithNonSleepFrame(260);
    proto_yure = 0xFFFFFFFF;
    th = actCreateSubThread(actSt00aStairChkSub, 21);
    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    fade = demoEnd ^ 1;
    if (fade) {
        scpAdpcmFadeCloseFunc(&proto, 256);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    iosThreadSetPri(&th->thread, 34);
    if (fade) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(86, 1, -1);
        stage_SetAnimation(83, 0, -1);
#else
        stage_SetAnimation(90, 1, -1);
        stage_SetAnimation(87, 0, -1);
#endif
        scpFadeIn(3.0f);
    }
    iosPadActStop(proto_yure);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(86) == 0) {
#else
    while (stage_CheckAnimationFinish(90) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(273)->active = 0;
    scpSearchGobj(272)->active = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    _ACTWait(120);
    ReviveAllCarryableItemsWithNonSleepFrame(60);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(84, 0, -1);
    stage_SetAnimation(86, -1, -2);
#else
    stage_SetAnimation(88, 0, -1);
    stage_SetAnimation(90, -1, -2);
#endif
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    gflagOff(38);
    fightSoundProcessRequestStart();
}
#endif

void actSt00aDoor2DownChk(GObj *self);
void actSt00aDoor2UpChk(GObj *self);

void actSt00aDoor2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 200.0f) != 0 ||
        (girlGObj != 0 && scpTriggerBall(self, girlGObj, 400.0f) != 0)) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(90, 0, 0);
#else
#ifdef VERSION_NTSC
        stage_SetAnimation(81, 0, 0);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(80, 0, 0);
#else
        stage_SetAnimation(94, 0, 0);
#endif
#endif
#endif
        _ACTWait(60);
        door2Down_mes[0].func = actSt00aDoor2DownChk;
        act->mail = door2Down_mes;
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(80, 0, 0);
        door2Up_mes[0].func = actSt00aDoor2UpChk;
        act->mail = door2Up_mes;
        ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(79, 0, 0);
        door2Up_mes[0].func = actSt00aDoor2UpChk;
        act->mail = door2Up_mes;
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(89, 0, 0);
#else
        stage_SetAnimation(93, 0, 0);
#endif
        door2Up_mes[0].func = actSt00aDoor2UpChk;
        act->mail = door2Up_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt00aDoor2UpEffect(GObj *volatile self);

#ifdef VERSION_NTSC
void actSt00aDoor2UpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor2UpEffect, 21);

    stage_SetAnimation(80, 1, 0);

    scpWakeupItemWithBoundary(-6.0f, -221.0f, 1504.0f, 100.0f);

    _ACTWait(1);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(60);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(80) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2Upchk_mes[0].func = actSt00aDoor2DownChk;
    sub->mail = door2Upchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt00aDoor2DownEffect(GObj *volatile self);

void actSt00aDoor2DownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    ConstVec pos;
    int h;

    while (1) {
        if (scpTriggerFloorAttrTargetMan(self, 0x3000000) == 0)
            break;
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor2DownEffect, 21);

    stage_SetAnimation(81, 1, 0);

    scpWakeupItemWithBoundary(-6.0f, -221.0f, 1504.0f, 100.0f);

    _ACTWait(1);

    pos = door2UpChkPos;
    soundSeDefPlay(1196, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(37);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(81) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2Downchk_mes[0].func = actSt00aDoor2UpChk;
    sub->mail = door2Downchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
#else
void actSt00aDoor2UpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor2UpEffect, 21);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(89, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(79, 1, 0);
#else
    stage_SetAnimation(93, 1, 0);
#endif
#endif

    scpWakeupItemWithBoundary(-6.0f, -221.0f, 1504.0f, 100.0f);

    _ACTWait(1);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
#ifdef VERSION_AUG6
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(60);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(79) == 0) {
#else
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(60);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(89) == 0) {
#else
    while (stage_CheckAnimationFinish(93) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    door2Upchk_mes[0].func = actSt00aDoor2DownChk;
    sub->mail = door2Upchk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt00aDoor2DownEffect(GObj *volatile self);

void actSt00aDoor2DownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    ConstVec pos;
    int h;

    while (1) {
        if (scpTriggerFloorAttrTargetMan(self, 0x3000000) == 0)
            break;
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor2DownEffect, 21);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(90, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(80, 1, 0);
#else
    stage_SetAnimation(94, 1, 0);
#endif
#endif

    scpWakeupItemWithBoundary(-6.0f, -221.0f, 1504.0f, 100.0f);

    _ACTWait(1);

    pos = door2UpChkPos;
#ifdef VERSION_AUG6
    soundSeDefPlay(1196, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(45);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(80) == 0) {
#else
    soundSeDefPlay(1220, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, pos.f, 1);
    _ACTWait(37);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, pos.f, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(90) == 0) {
#else
    while (stage_CheckAnimationFinish(94) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    door2Downchk_mes[0].func = actSt00aDoor2UpChk;
    sub->mail = door2Downchk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}
#endif

void actSt00aDoor1DownChk(GObj *self);
void actSt00aDoor1UpChk(GObj *self);

void actSt00aDoor1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 200.0f) != 0 ||
        (girlGObj != 0 && scpTriggerBall(self, girlGObj, 400.0f) != 0)) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(88, 0, 0);
#else
#ifdef VERSION_NTSC
        stage_SetAnimation(79, 0, 0);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(78, 0, 0);
#else
        stage_SetAnimation(92, 0, 0);
#endif
#endif
#endif
        _ACTWait(60);
        door1Down_mes[0].func = actSt00aDoor1DownChk;
        act->mail = door1Down_mes;
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(78, 0, 0);
        door1Up_mes[0].func = actSt00aDoor1UpChk;
        act->mail = door1Up_mes;
        ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(77, 0, 0);
        door1Up_mes[0].func = actSt00aDoor1UpChk;
        act->mail = door1Up_mes;
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(87, 0, 0);
#else
        stage_SetAnimation(91, 0, 0);
#endif
        door1Up_mes[0].func = actSt00aDoor1UpChk;
        act->mail = door1Up_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt00aDoor1UpEffect(GObj *volatile self);

#ifdef VERSION_NTSC
void actSt00aDoor1UpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
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

    stage_SetAnimation(78, 1, 0);

    pos = door1UpChkPos;
    soundSeDefPlay(1196, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(78) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door1Upchk_mes[0].func = actSt00aDoor1DownChk;
    sub->mail = door1Upchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt00aDoor1DownEffect(GObj *volatile self);

void actSt00aDoor1DownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x4000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor1DownEffect, 21);

    scpWakeupItemWithBoundary(-8.0f, -73.0f, 64.0f, 100.0f);

    stage_SetAnimation(79, 1, 0);

    buf[0] = door1UpChkPos.d[0];
    buf[1] = door1UpChkPos.d[1];
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(79) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door1Downchk_mes[0].func = actSt00aDoor1UpChk;
    sub->mail = door1Downchk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt00aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(39) == 0) {
        ene_mes[0].func = actSt00aEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt00aEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(37) == 0) {
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

void actSt00aEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(37) == 0) {
        _ACTWait(1);
    }
    _ACTWait(160);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
}

void actSt00aStair(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(38) == 0) {
        scpSearchGobj(245)->active = 0;
        stair_mes[0].func = actSt00aStairChk;
        act->mail = stair_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpSearchGobj(246)->active = 0;
    }
}

void actSt00aAtr2Chk(GObj *volatile self);

void actSt00aAtr2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(39) == 0) {
        atr2_mes[0].func = actSt00aAtr2Chk;
        act->mail = atr2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}
#else
void actSt00aDoor1UpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
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

#ifdef VERSION_AUG6
    stage_SetAnimation(77, 1, 0);

    pos = door1UpChkPos;
    soundSeDefPlay(1196, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(77) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(87, 1, 0);
#else
    stage_SetAnimation(91, 1, 0);
#endif

    pos = door1UpChkPos;
    soundSeDefPlay(1220, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, pos.f, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(87) == 0) {
#else
    while (stage_CheckAnimationFinish(91) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    door1Upchk_mes[0].func = actSt00aDoor1DownChk;
    sub->mail = door1Upchk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt00aDoor1DownEffect(GObj *volatile self);

void actSt00aDoor1DownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x4000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor1DownEffect, 21);

    scpWakeupItemWithBoundary(-8.0f, -73.0f, 64.0f, 100.0f);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(88, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(78, 1, 0);
#else
    stage_SetAnimation(92, 1, 0);
#endif
#endif

    buf[0] = door1UpChkPos.d[0];
    buf[1] = door1UpChkPos.d[1];
#ifdef VERSION_AUG6
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(78) == 0) {
#else
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(88) == 0) {
#else
    while (stage_CheckAnimationFinish(92) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    door1Downchk_mes[0].func = actSt00aDoor1UpChk;
    sub->mail = door1Downchk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt00aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(39) == 0) {
        ene_mes[0].func = actSt00aEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(42) == 0) {
        ene_mes[0].func = actSt00aEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt00aEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
#ifdef VERSION_AUG6
    while (gflagChk(37) == 0) {
#else
    while (gflagChk(40) == 0) {
#endif
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

void actSt00aEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
#ifdef VERSION_AUG6
    while (gflagChk(37) == 0) {
#else
    while (gflagChk(40) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(160);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
}

void actSt00aStair(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(38) == 0) {
        scpSearchGobj(244)->active = 0;
        stair_mes[0].func = actSt00aStairChk;
        act->mail = stair_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpSearchGobj(245)->active = 0;
#else
    if (gflagChk(41) == 0) {
        scpSearchGobj(272)->active = 0;
        stair_mes[0].func = actSt00aStairChk;
        act->mail = stair_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(273)->active = 0;
#endif
    }
}

void actSt00aAtr2Chk(GObj *volatile self);

void actSt00aAtr2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(39) == 0) {
        atr2_mes[0].func = actSt00aAtr2Chk;
        act->mail = atr2_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(42) == 0) {
        atr2_mes[0].func = actSt00aAtr2Chk;
        act->mail = atr2_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}
#endif
#endif

#ifdef VERSION_JUN26
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
#else
void actSt00aAtr2Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    gflagOn(39);
#else
    gflagOn(42);
}

static void actSt00aStairChkSub(GObj *volatile self)
{
    _ACTWait(90);
    iosPadActRequest(boyPad, 17);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(83) == 0) {
#else
    while (stage_CheckAnimationFinish(87) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(85, 1, 0);
    stage_SetAnimation(86, 1, 0);
#else
    stage_SetAnimation(89, 1, 0);
    stage_SetAnimation(90, 1, 0);
#endif
    proto_yure = iosPadActRequest(boyPad, 9);
    proto_yure_vol = 128;
    iosPadActVolumeSet(proto_yure, 128);
    _ACTWait(500);
    demoEnd = 1;
    _ACTWait(0);
#endif
}
#endif

#ifdef VERSION_JUN26
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
#else
void actSt00aDoor2Event(int x)
{
    volatile int local = x;
}

void actSt00aDoor2UpEffect(GObj *volatile self)
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
#else
void actSt00aDoor2DownEffect(GObj *volatile self)
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

#ifdef VERSION_JUN26
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
#else
void actSt00aDoor1Event(int x)
{
    volatile int local = x;
}
#endif

#ifdef VERSION_JUN26
void actSt00aDoor1UpChk(GObj *volatile self);
void actSt00aDoor1DownChk(GObj *volatile self);
inline void actSt00aDoor1UpEffect(GObj *volatile self);
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
#else
void actSt00aDoor1UpEffect(GObj *volatile self)
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
#endif

#ifdef VERSION_JUN26
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
#else
void actSt00aDoor1DownEffect(GObj *volatile self)
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
#endif

#ifdef VERSION_JUN26
/* file-scope, as in the later builds: the gcse expression hash table of
   43 buckets below puts its %hi after the callee's, which the demo's
   registers show (s5 table, s4 callee) */
static ActMail door1Downchk_mes[2] = {{377}, {376}}; /* derived name */

void actSt00aDoor1DownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];
    int h;
    /* pinned: two to five instructions at gcse that later passes delete
       (the hash table is 43 buckets, not the 41 the August text gives),
       from values that cross a label cse1 cannot follow; the trigger
       attribute and the animation number are the only two such values,
       and gcse folds them into their uses.  Not pinned: the text (aug6 and
       the later builds spell both as literals). */
    int attr = 0x4000000;
    int anim = 70;

    while (scpTriggerFloorAttrTargetMan(self, attr) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor1DownEffect, 21);

    scpWakeupItemWithBoundary(-8.0f, -73.0f, 64.0f, 100.0f);

    stage_SetAnimation(anim, 1, 0);

    buf[0] = door1UpChkPos.d[0];
    buf[1] = door1UpChkPos.d[1];
    soundSeDefPlay(1170, 0, (float *)buf, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1171, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1172, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(anim) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door1Downchk_mes[0].func = actSt00aDoor1UpChk;
    sub->mail = door1Downchk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}
#endif
