#include "common.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "fightSound.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "item.h"
#include "typedef.h"

/* st00a.o's whole .rodata run: six 16-byte constant vectors in ROM order, each
   named for the first actor that copies it. The float view carries the values,
   the long long view is the one the copies read, which is what makes gcc emit
   the ld/sd pairs the ROM has. */

static const ConstVec door2UpChkPos = {{0.0f, -422.0f, 1630.0f, 0.0f}};

static const ConstVec door2UpEffectPos = {{0.0f, -150.0f, 1640.0f, 1.0f}};

static const ConstVec door2UpEffect2Pos = {{0.0f, -450.0f, 1640.0f, 1.0f}};

static const ConstVec door1UpChkPos = {{-1.0f, -184.0f, -57.0f, 0.0f}};

static const ConstVec door1UpEffectPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}};

static const ConstVec door1UpEffect2Pos = {{-505.0f, -1447.0f, -5671.0f, 1.0f}};

/* st00a.o's whole .data run: eleven actor mail records in ROM order, each the
   usual pair, the 430 entry whose handler the sender fills in and the 429
   terminator, named for the actor that installs it. */
static ActMail atr2_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail stair_mes[2] = {{430}, {429}};

static ActMail door2Down_mes[2] = {{430}, {429}};

static ActMail door2Up_mes[2] = {{430}, {429}};

/* The four check records' names are ours and not settled. Each check actor hoists the
   record's %hi and its handler's %hi out of its trigger loop, and which of the two takes
   $20 falls to the order of their gcse hash buckets, i.e. to the record's NAME: st05d's
   spelling door2UpChk_mes (bucket 34 of 43, handler 30) gives actSt00aDoor2UpChk the
   other register order and door1UpChk_mes (37 of 41, handler 2) does the same to
   actSt00aDoor1UpChk, while the lower-case chk that st05d and st08b first carried fits
   all four. The bytes pin the buckets, not the text. */
static ActMail door2Upchk_mes[2] = {{430}, {429}};

static ActMail door2Downchk_mes[2] = {{430}, {429}};

static ActMail door1Down_mes[2] = {{430}, {429}};

static ActMail door1Up_mes[2] = {{430}, {429}};

static ActMail door1Upchk_mes[2] = {{430}, {429}};

static ActMail door1Downchk_mes[2] = {{430}, {429}};

void actSt00aInit(void)
{
    if (gflagChk(41) == 0) {
        stage_SetAnimation(90, 0, 0);
        stage_SetAnimation(87, 0, 0);
        SetWayGroupActive(3, 0);
        SetWayGroupActive(13, 1);
    } else {
        stage_SetAnimation(88, 0, -1);
        stage_SetAnimation(87, 0, -1);
        FinishHint(1);
        SetWayGroupActive(3, 1);
        SetWayGroupActive(13, 0);
    }
    if (gflagChk(79) == 0) {
        stage_SetAnimation(96, 0, 1);
    } else {
        stage_SetAnimation(96, 0, 2);
    }
}

extern char *D_00639EA8;

void actSt00aEnd(void)
{
    if (D_00639EA8 != 0) {
        if (gflagChk(42) == 0) {
            gflagOn(391);
        }
    }
}

extern int D_0028F4C0[];
extern int D_0063AA08;
/* kept local: this TU's uses of scpSleepEnemyOne do not fit the prototype in script.h */
extern void scpSleepEnemyOne(int a0);
/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
/* kept local: this TU's uses of scpWakeupEnemyOne do not fit the prototype in script.h */
extern void scpWakeupEnemyOne(int a0);
/* kept local: this TU's uses of scpWakeupEnemyAll do not fit the prototype in script.h */
extern void scpWakeupEnemyAll(void);

void actSt00aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (gflagChk(42) == 0 || gflagChk(38) != 0) {
        _ACTWait(1);
    }
    lt_switch_layout(55);
    D_0063AA08 = 1;
    gflagOn(39);
    scpSleepEnemyOne(3757);
    scpSleepEnemyAll();
    gflagOff(391);
    _ACTWait(60);
    gflagOn(40);
    stage_SetAnimation(177, 1, 0);
    _ACTWait(150);
    while (stage_CheckAnimationFinish(177) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(54);
    _ACTWait(120);
    D_0063AA08 = 0;
    scpWakeupEnemyOne(3757);
    scpWakeupEnemyAll();
    _ACTWait((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    gflagOff(39);
}

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int a1, float f);
extern int D_0063BE70;
extern unsigned int D_0063BE74;

/* .sbss, owned by st00a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the flag the stair-check subthread raises when the demo
   is over, which the wait loop below spins for. */
static int demoEnd;

extern int D_0028F8F4[];
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern int scpAdpcmFadeCloseFunc(int *h, short fade);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float f, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
void actSt00aStairChkSub(volatile int a0);

void actSt00aStairChk(volatile int a0)
{
    int th;
    int fade;

    while (scpTriggerBall(a0, (int)scpSearchGobj(276), 90.0f) != 0 || gflagChk(39) != 0) {
        _ACTWait(1);
    }
    gflagOn(38);
    FinishHint(1);
    SetWayGroupActive(3, 1);
    SetWayGroupActive(13, 0);
    lt_switch_layout(55);
    D_0063AA08 = 1;
    gflagOn(41);
    scpSleepEnemyAll();
    _ACTWait(60);
    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(21, &D_0063BE70, 1, 1, 1);
    while (D_0063BE70 == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(87, 1, 0);
    ReviveAllCarryableItemsWithNonSleepFrame(260);
    D_0063BE74 = 0xFFFFFFFF;
    th = actCreateSubThread(actSt00aStairChkSub, 21);
    demoEnd = 0;
    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    fade = demoEnd ^ 1;
    if (fade) {
        scpAdpcmFadeCloseFunc(&D_0063BE70, 0x100);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    iosThreadSetPri(th + 0x24, 34);
    if (fade) {
        stage_SetAnimation(90, 1, -1);
        stage_SetAnimation(87, 0, -1);
        scpFadeIn(3.0f);
    }
    iosPadActStop(D_0063BE74);
    while (stage_CheckAnimationFinish(90) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(273)->f16C = 0;
    scpSearchGobj(272)->f16C = 1;
    lt_switch_layout(54);
    _ACTWait(120);
    ReviveAllCarryableItemsWithNonSleepFrame(60);
    stage_SetAnimation(88, 0, -1);
    stage_SetAnimation(90, -1, -2);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    gflagOff(38);
    fightSoundProcessRequestStart();
}

extern int D_00639EA4;
void actSt00aDoor2DownChk(int a0);
void actSt00aDoor2UpChk(int a0);

void actSt00aDoor2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, (int)D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(94, 0, 0);
        _ACTWait(60);
        door2Down_mes[0].func = actSt00aDoor2DownChk;
        self->mail = door2Down_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(93, 0, 0);
        door2Up_mes[0].func = actSt00aDoor2UpChk;
        self->mail = door2Up_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* kept local: this TU's uses of scpTriggerFloorAttrTargetMan do not fit the prototype in script.h */
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
/* kept local: this TU's uses of scpWakeupItemWithBoundary do not fit the prototype in script.h */
extern void scpWakeupItemWithBoundary(float x, float y, float z, float r);
void actSt00aDoor2UpEffect(volatile int a0);

void actSt00aDoor2UpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor2UpEffect, 21);

    stage_SetAnimation(93, 1, 0);

    scpWakeupItemWithBoundary(-6.0f, -221.0f, 1504.0f, 100.0f);

    _ACTWait(1);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(60);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(93) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2Upchk_mes[0].func = actSt00aDoor2DownChk;
    sub->mail = door2Upchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt00aDoor2DownEffect(volatile int a0);

void actSt00aDoor2DownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    ConstVec pos;
    int h;

    while (1) {
        if (scpTriggerFloorAttrTargetMan(a0, 0x3000000) == 0)
            break;
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor2DownEffect, 21);

    stage_SetAnimation(94, 1, 0);

    scpWakeupItemWithBoundary(-6.0f, -221.0f, 1504.0f, 100.0f);

    _ACTWait(1);

    pos = door2UpChkPos;
    soundSeDefPlay(1220, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, pos.f, 1);
    _ACTWait(37);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(94) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2Downchk_mes[0].func = actSt00aDoor2UpChk;
    sub->mail = door2Downchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt00aDoor1DownChk(int a0);
void actSt00aDoor1UpChk(int a0);

void actSt00aDoor1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, (int)D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(92, 0, 0);
        _ACTWait(60);
        door1Down_mes[0].func = actSt00aDoor1DownChk;
        self->mail = door1Down_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(91, 0, 0);
        door1Up_mes[0].func = actSt00aDoor1UpChk;
        self->mail = door1Up_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt00aDoor1UpEffect(volatile int a0);

void actSt00aDoor1UpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    ConstVec pos;
    int h;

    while (1) {
        if (scpTriggerFloorAttrTargetMan(a0, 0x4000000) != 0)
            break;
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor1UpEffect, 21);

    scpWakeupItemWithBoundary(-8.0f, -73.0f, 64.0f, 100.0f);

    stage_SetAnimation(91, 1, 0);

    pos = door1UpChkPos;
    soundSeDefPlay(1220, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, pos.f, 1);

    while (stage_CheckAnimationFinish(91) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door1Upchk_mes[0].func = actSt00aDoor1DownChk;
    sub->mail = door1Upchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt00aDoor1DownEffect(volatile int a0);

void actSt00aDoor1DownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x4000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt00aDoor1DownEffect, 21);

    scpWakeupItemWithBoundary(-8.0f, -73.0f, 64.0f, 100.0f);

    stage_SetAnimation(92, 1, 0);

    buf[0] = door1UpChkPos.d[0];
    buf[1] = door1UpChkPos.d[1];
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(92) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door1Downchk_mes[0].func = actSt00aDoor1UpChk;
    sub->mail = door1Downchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt00aEneChk(int a0);

void actSt00aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(42) == 0) {
        ene_mes[0].func = actSt00aEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt00aEnemy1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(40) == 0) {
        _ACTWait(1);
    }
    _ACTWait(50);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
}

void actSt00aEnemy2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(40) == 0) {
        _ACTWait(1);
    }
    _ACTWait(160);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
}

void actSt00aStairChk(int a0);

void actSt00aStair(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(41) == 0) {
        scpSearchGobj(272)->f16C = 0;
        stair_mes[0].func = actSt00aStairChk;
        self->mail = stair_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(273)->f16C = 0;
    }
}

void actSt00aAtr2Chk(volatile int a0);

void actSt00aAtr2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(42) == 0) {
        atr2_mes[0].func = actSt00aAtr2Chk;
        self->mail = atr2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);

void actSt00aAtr2Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(42);
}

extern int D_00639EAC;
extern unsigned char D_0063BE78;

void actSt00aStairChkSub(volatile int a0)
{
    _ACTWait(90);
    iosPadActRequest(D_00639EAC, 0x11);
    while (stage_CheckAnimationFinish(87) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    stage_SetAnimation(89, 1, 0);
    stage_SetAnimation(90, 1, 0);
    D_0063BE74 = iosPadActRequest(D_00639EAC, 9);
    D_0063BE78 = 0x80;
    iosPadActVolumeSet(D_0063BE74, 0x80);
    _ACTWait(500);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt00aDoor2Event(int x)
{
    volatile int local = x;
}

/* kept local: this TU's uses of scpEffectStart do not fit the prototype in script.h */
extern void scpEffectStart(int *buf, int a1);

void actSt00aDoor2UpEffect(volatile int a0)
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
        case 0x1E:
            b2[0] = v0b;
            b2[1] = door2UpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt00aDoor2DownEffect(volatile int a0)
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
        case 0x1E:
            b2[0] = v0b;
            b2[1] = door2UpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt00aDoor1Event(int x)
{
    volatile int local = x;
}

void actSt00aDoor1UpEffect(volatile int a0)
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
        case 0x1E:
            b2[0] = v0b;
            b2[1] = door1UpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt00aDoor1DownEffect(volatile int a0)
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
        case 0x1E:
            b2[0] = v0b;
            b2[1] = door1UpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}
