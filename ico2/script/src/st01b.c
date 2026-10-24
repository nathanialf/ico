#include "st01b.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "chain.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"

#ifdef VERSION_JUN26
#include "spider.h"
#endif

#include "typedef.h"
#include "main.h"
#include "script.h"

#ifdef VERSION_NTSC
/* This stage's actor mail records are static locals of the function that
   posts each one (.data holds the five in the order of their posters, and
   each takes gcc's local name.N symbol). Word 0 of each entry is the
   mail id the entry answers (397 = the actor's own wake-up post, 396 = the
   trailing entry); the handler in .func is installed at run time just
   before the record is posted. */

void actSt01bInit(void)
{
    if (gflagChk(66) == 0) {
        SetWayGroupActive(2, 0);
        stage_SetAnimation(162, 0, 0);
        return stage_SetAnimation(159, 0, 0);
    }
    SetWayGroupActive(2, 1);
    stage_SetAnimation(162, 0, -1);
    return stage_SetAnimation(159, 0, -1);
}

void actSt01bEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (gflagChk(66) == 0 || scpTriggerFloorAttr(boyGObj, 0x1000000) == 0 ||
           (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 &&
            scpTriggerFloorAttr(girlGObj, 0x2000000) == 0)) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyOne(3453);
    _ACTWait(30);
    gflagOn(64);
    gflagOn(65);
    stage_SetAnimation(161, 1, 0);
    while (stage_CheckAnimationFrame(161, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    while (stage_CheckAnimationFinish(161) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyOne(3453);
}
#else
#ifndef VERSION_AUG6
/* This stage's actor mail records. Word 0 of each entry is the mail id the
   entry answers (430 = the actor's own wake-up post, 429 = the trailing
   entry); the handler in .func is installed at run time just before the
   record is posted. Each record is named for the actor thread that owns
   and posts it. */
#ifdef VERSION_JUN26
static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

static ActMail floor_mes[2] = {{377}, {376}}; /* derived name */
#else
static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail floor_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_on_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_off_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif

void actSt01bInit(void)
{
#ifdef VERSION_AUG6
    if (gflagChk(66) == 0) {
        SetWayGroupActive(2, 0);
        stage_SetAnimation(161, 0, 0);
        return stage_SetAnimation(158, 0, 0);
    }
    SetWayGroupActive(2, 1);
    stage_SetAnimation(161, 0, -1);
    return stage_SetAnimation(158, 0, -1);
#else
#ifdef VERSION_JUN26
    if (gflagChk(65) == 0) {
        stage_SetAnimation(147, 0, 0);
        return stage_SetAnimation(145, 0, 0);
    }
    stage_SetAnimation(147, 0, -1);
    return stage_SetAnimation(145, 0, -1);
#else
    if (gflagChk(70) == 0) {
        SetWayGroupActive(2, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(179, 0, 0);
        return stage_SetAnimation(176, 0, 0);
#else
        stage_SetAnimation(183, 0, 0);
        return stage_SetAnimation(180, 0, 0);
#endif
    }
    SetWayGroupActive(2, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(179, 0, -1);
    stage_SetAnimation(176, 0, -1);
#else
    stage_SetAnimation(183, 0, -1);
    stage_SetAnimation(180, 0, -1);
#endif
    return FinishHint(9);
#endif
#endif
}

void actSt01bEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
#ifdef VERSION_AUG6
    while (gflagChk(66) == 0 || scpTriggerFloorAttr(boyGObj, 0x1000000) == 0 ||
           (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 &&
            scpTriggerFloorAttr(girlGObj, 0x2000000) == 0)) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyOne(3415);
    _ACTWait(30);
    gflagOn(64);
    gflagOn(65);
    stage_SetAnimation(160, 1, 0);
    while (stage_CheckAnimationFrame(160, 90, 0) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(65) == 0 || scpTriggerFloorAttr(boyGObj, 0x1000000) == 0 ||
           (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 &&
            scpTriggerFloorAttr(girlGObj, 0x2000000) == 0)) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    _ACTWait(30);
    gflagOn(63);
    gflagOn(64);
    stage_SetAnimation(146, 1, 0);
    while (stage_CheckAnimationFrame(146, 90, 0) == 0) {
#else
    while (gflagChk(70) == 0 || scpTriggerFloorAttr(boyGObj, 0x1000000) == 0 ||
           (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 &&
            scpTriggerFloorAttr(girlGObj, 0x2000000) == 0)) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSleepEnemyOne(3734);
#else
    scpSleepEnemyOne(3757);
#endif
    _ACTWait(30);
    gflagOn(68);
    gflagOn(69);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(178, 1, 0);
    while (stage_CheckAnimationFrame(178, 90, 0) == 0) {
#else
    stage_SetAnimation(182, 1, 0);
    while (stage_CheckAnimationFrame(182, 90, 0) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(178) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(160) == 0) {
#else
#ifdef VERSION_JUN26
    WakeUpSpidersFromGenerator(scpSearchGobj(749));
    WakeUpSpidersFromGenerator(scpSearchGobj(750));
    while (stage_CheckAnimationFinish(146) == 0) {
#else
    while (stage_CheckAnimationFinish(182) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_AUG6
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyOne(3415);
#else
#ifdef VERSION_JUN26
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpWakeupEnemyOne(3734);
#else
    scpWakeupEnemyOne(3757);
#endif
#endif
#endif
}
#endif

/* .sdata */
SqEntry *st01b_floor = 0;

unsigned int st01b_yure = 0;

unsigned char st01b_yure_vol = 0;

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for, and the handle of the looping sound effect the demo starts. */
static int demoEnd;

static int seHandle; /* derived name */
#endif

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec floorChkSubPos = {{-101.0f, -381.0f, -398.0f, 0.0f}}; /* derived name */

#ifdef VERSION_NTSC
void actSt01bFloorChk(GObj *volatile self)
{
    ConstVec pos;
    int se;

    while (scpIsHangChainOptional(boyGObj, 747) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(66);
    SetWayGroupActive(2, 1);
    if (girlGObj != 0) {
        scpPlayPosSet(girlGObj, -200.0f, 900.0f, -200.0f);
    }
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(79, &st01b_floor, 1, 1, 1);
    while (st01b_floor == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(159, 1, 0);
    stage_SetAnimation(160, 1, 0);
    pos = floorChkSubPos;
    se = soundSeDefPlay(1301, 0, pos.f, 1);
    _ACTWait(90);
    soundSeDefStop(se);
    soundSeDefPlay(1264, 0, 0, 1);
    stage_SetAnimation(162, 1, 0);
    st01b_yure = iosPadActRequest(boyPad, 9);
    st01b_yure_vol = 128;
    iosPadActVolumeSet(st01b_yure, 128);
    while (stage_CheckAnimationFrame(162, 180, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(st01b_yure);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt01bSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpSekizou(self, 61, 157, 0, 18, 1000.0f, 528.0f, -150.0f, 1000.0f, 528.0f, -100.0f);
}

void actSt01bEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(64) == 0) {
        static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

        ene_mes[0].func = actSt01bEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt01bEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(65) == 0) {
        _ACTWait(1);
    }

    _ACTWait(116);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt01bEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(65) == 0) {
        _ACTWait(1);
    }

    _ACTWait(100);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt01bEnemy3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(65) == 0) {
        _ACTWait(1);
    }

    _ACTWait(130);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt01bEnemy4(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(65) == 0) {
        _ACTWait(1);
    }

    _ACTWait(115);
    Generator_Call(self);
}

void actSt01bEnemy5(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(65) == 0) {
        _ACTWait(1);
    }

    _ACTWait(125);
    Generator_Call(self);
}

void actSt01bEnemy6(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(65) == 0) {
        _ACTWait(1);
    }

    _ACTWait(110);
    Generator_Call(self);
}

void actSt01bFloor(GObj *volatile self)
{
    GObj *x = self;
    static ActMail floor_mes[2] = {{397}, {396}}; /* derived name */
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(66) == 0) {
        floor_mes[0].func = actSt01bFloorChk;
        act->mail = floor_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
void actSt01bFloorChk(GObj *volatile self)
{
    ConstVec pos;
    int se;

#ifdef VERSION_JUN26
    while (scpIsHangChainOptional(boyGObj, 724) == 0) {
#else
    while (scpIsHangChainOptional(boyGObj, 746) == 0) {
#endif
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
#ifdef VERSION_JUN26
    gflagOn(65);
#else
    scpSleepEnemyAll();
    gflagOn(66);
    SetWayGroupActive(2, 1);
#endif
    if (girlGObj != 0) {
        scpPlayPosSet(girlGObj, -200.0f, 900.0f, -200.0f);
    }
    _ACTWait(60);
#ifdef VERSION_JUN26
    scpAdpcmPlayRequestFunc(74, &st01b_floor, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(79, &st01b_floor, 1, 1, 1);
#endif
    while (st01b_floor == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_JUN26
    stage_SetAnimation(145, 1, 0);
    pos = floorChkSubPos;
    se = soundSeDefPlay(1270, 0, pos.f, 1);
    _ACTWait(90);
    soundSeDefStop(se);
    soundSeDefPlay(1238, 0, 0, 1);
    stage_SetAnimation(147, 1, 0);
#else
    stage_SetAnimation(158, 1, 0);
    stage_SetAnimation(159, 1, 0);
    pos = floorChkSubPos;
    se = soundSeDefPlay(1301, 0, pos.f, 1);
    _ACTWait(90);
    soundSeDefStop(se);
    soundSeDefPlay(1264, 0, 0, 1);
    stage_SetAnimation(161, 1, 0);
#endif
    st01b_yure = iosPadActRequest(boyPad, 9);
    st01b_yure_vol = 128;
    iosPadActVolumeSet(st01b_yure, 128);
#ifdef VERSION_JUN26
    while (stage_CheckAnimationFinish(147) == 0) {
#else
    while (stage_CheckAnimationFrame(161, 180, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(st01b_yure);
#ifndef VERSION_JUN26
    scpWakeupEnemyAll();
#endif
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
#else
static void actSt01bFloorChkSub(GObj *volatile self)
{
    ConstVec pos;

    while (st01b_floor == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(st01b_floor->stream);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(176, 1, 0);
    stage_SetAnimation(177, 1, 0);
#else
    stage_SetAnimation(180, 1, 0);
    stage_SetAnimation(181, 1, 0);
#endif
    pos = floorChkSubPos;
    seHandle = soundSeDefPlay(1325, 0, pos.f, 1);
    _ACTWait(90);
    soundSeDefStop(seHandle);
    seHandle = -1;
    soundSeDefPlay(1288, 0, 0, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(179, 1, 0);
#else
    stage_SetAnimation(183, 1, 0);
#endif
    st01b_yure = iosPadActRequest(boyPad, 9);
    st01b_yure_vol = 128;
    iosPadActVolumeSet(st01b_yure, 128);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(179, 180, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(183, 180, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt01bFloorChk(GObj *volatile self)
{
    GProc *th;
    int notdone;

    while (scpIsHangChainOptional(boyGObj, 805) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(70);
    FinishHint(9);
    SetWayGroupActive(2, 1);
    if (girlGObj != 0) {
        scpPlayPosSet(girlGObj, -200.0f, 900.0f, -200.0f);
    }
    scpAdpcmPlayRequestFunc(81, &st01b_floor, 1, 1, 0);
    th = actCreateSubThread(actSt01bFloorChkSub, 21);
    seHandle = -1;
    st01b_yure = 0xFFFFFFFF;
    demoEnd = 0;
    st01b_floor = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    notdone = demoEnd ^ 1;
    if (notdone) {
        while (st01b_floor == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc(&st01b_floor, 256);
        scpFadeOut(16.0f, 0, 0, 0);
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosThreadSetPri(&th->thread, 34);

    if (notdone) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(177, 1, -1);
        stage_SetAnimation(176, 1, -1);
        stage_SetAnimation(179, 0, 180);
#else
        stage_SetAnimation(181, 1, -1);
        stage_SetAnimation(180, 1, -1);
        stage_SetAnimation(183, 0, 180);
#endif
        if (seHandle >= 0) {
            soundSeDefStop(seHandle);
            soundSeDefPlay(1288, 0, 0, 1);
        }
        _ACTWait(1);
        ChainPositionReset(scpSearchGobj(805));
        _ACTWait(1);
        scpFadeIn(3.0f);
    }

    iosPadActStop(st01b_yure);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}
#endif

void actSt01bSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSekizou(self, 65, 174, 0, 18, 1000.0f, 528.0f, -150.0f, 1000.0f, 528.0f, -100.0f);
#else
#ifdef VERSION_AUG6
    scpSekizou(self, 61, 156, 0, 18, 1000.0f, 528.0f, -150.0f, 1000.0f, 528.0f, -100.0f);
#else
#ifdef VERSION_JUN26
    scpSekizou(self, 60, 143, 0, 21, 1000.0f, 528.0f, -150.0f, 1000.0f, 528.0f, -100.0f);
#else
    scpSekizou(self, 65, 178, 0, 18, 1000.0f, 528.0f, -150.0f, 1000.0f, 528.0f, -100.0f);
#endif
#endif
#endif
}

void actSt01bEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(64) == 0) {
        static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

        ene_mes[0].func = actSt01bEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(63) == 0) {
        ene_mes[0].func = actSt01bEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(68) == 0) {
        ene_mes[0].func = actSt01bEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt01bEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(65) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(64) == 0) {
#else
    while (gflagChk(69) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(116);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
#ifndef VERSION_JUN26
    Generator_MaskOff(self);
#endif
}

void actSt01bEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(65) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(64) == 0) {
#else
    while (gflagChk(69) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(100);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
#ifndef VERSION_JUN26
    Generator_MaskOff(self);
#endif
}

void actSt01bEnemy3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(65) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(64) == 0) {
#else
    while (gflagChk(69) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(130);
    Generator_Call(self);
#ifndef VERSION_JUN26
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
#endif
}

void actSt01bEnemy4(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(65) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(64) == 0) {
#else
    while (gflagChk(69) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(115);
    Generator_Call(self);
}

void actSt01bEnemy5(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(65) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(64) == 0) {
#else
    while (gflagChk(69) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(125);
    Generator_Call(self);
}

void actSt01bEnemy6(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(65) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(64) == 0) {
#else
    while (gflagChk(69) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(110);
    Generator_Call(self);
}

void actSt01bFloor(GObj *volatile self)
{
    GObj *x = self;
#ifdef VERSION_AUG6
    static ActMail floor_mes[2] = {{393}, {392}}; /* derived name */
#endif
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(66) == 0) {
        floor_mes[0].func = actSt01bFloorChk;
        act->mail = floor_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(65) == 0) {
        floor_mes[0].func = actSt01bFloorChk;
        act->mail = floor_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(70) == 0) {
        floor_mes[0].func = actSt01bFloorChk;
        act->mail = floor_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}
#endif

#ifndef VERSION_JUN26
void actSt01bWay(GObj *volatile self)
{
    GObj *x = self;
#ifdef VERSION_NTSC
    static ActMail way_mes[2] = {{397}, {396}}; /* derived name */
#endif
#ifdef VERSION_AUG6
    static ActMail way_mes[2] = {{393}, {392}}; /* derived name */
#endif
    Act *act = actInitialize(self);

    _ACTWait(1);

    way_mes[0].func = actSt01bWayOnChk;
    act->mail = way_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actSt01bEnd(void) {}
#endif

void actSt01bSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt01bFloorEvent(int x)
{
    volatile int local = x;
}

#ifdef VERSION_NTSC
void actSt01bWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail way_on_mes[2] = {{397}, {396}}; /* derived name */

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 || gflagChk(66) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);

    way_on_mes[0].func = actSt01bWayOffChk;
    sub->mail = way_on_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt01bWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail way_off_mes[2] = {{397}, {396}}; /* derived name */

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x2000000) == 0 || gflagChk(66) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 0);

    way_off_mes[0].func = actSt01bWayOnChk;
    sub->mail = way_off_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
#else
#ifndef VERSION_JUN26
void actSt01bWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    static ActMail way_on_mes[2] = {{393}, {392}}; /* derived name */
#endif

    if (girlGObj == 0) {
        _ACTWait(0);
    }
#ifdef VERSION_AUG6
    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 || gflagChk(66) == 0) {
#else
    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 || gflagChk(70) == 0) {
#endif
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);

    way_on_mes[0].func = actSt01bWayOffChk;
    sub->mail = way_on_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt01bWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    static ActMail way_off_mes[2] = {{393}, {392}}; /* derived name */
#endif

    if (girlGObj == 0) {
        _ACTWait(0);
    }
#ifdef VERSION_AUG6
    while (scpTriggerFloorAttr(girlGObj, 0x2000000) == 0 || gflagChk(66) == 0) {
#else
    while (scpTriggerFloorAttr(girlGObj, 0x2000000) == 0 || gflagChk(70) == 0) {
#endif
        _ACTWait(1);
    }

    SetWayGroupActive(4, 0);

    way_off_mes[0].func = actSt01bWayOnChk;
    sub->mail = way_off_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}
#endif
#endif
