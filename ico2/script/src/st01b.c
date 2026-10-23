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
#include "typedef.h"
#include "main.h"
#include "script.h"

/* This stage's actor mail records are static locals of the function that
   posts each one (.data holds the five in the order of their posters, and
   each takes gcc's local name.N symbol). Word 0 of each entry is the
   mail id the entry answers (393 = the actor's own wake-up post, 392 = the
   trailing entry); the handler in .func is installed at run time just
   before the record is posted. */

void actSt01bInit(void)
{
    if (gflagChk(66) == 0) {
        SetWayGroupActive(2, 0);
        stage_SetAnimation(161, 0, 0);
        return stage_SetAnimation(158, 0, 0);
    }
    SetWayGroupActive(2, 1);
    stage_SetAnimation(161, 0, -1);
    return stage_SetAnimation(158, 0, -1);
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
    scpSleepEnemyOne(3415);
    _ACTWait(30);
    gflagOn(64);
    gflagOn(65);
    stage_SetAnimation(160, 1, 0);
    while (stage_CheckAnimationFrame(160, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    while (stage_CheckAnimationFinish(160) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyOne(3415);
}

/* .sdata */
SqEntry *st01b_floor = 0;

unsigned int st01b_yure = 0;

unsigned char st01b_yure_vol = 0;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec floorChkSubPos = {{-101.0f, -381.0f, -398.0f, 0.0f}}; /* derived name */

void actSt01bFloorChk(GObj *volatile self)
{
    ConstVec pos;
    int se;

    while (scpIsHangChainOptional(boyGObj, 746) == 0) {
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
    stage_SetAnimation(158, 1, 0);
    stage_SetAnimation(159, 1, 0);
    pos = floorChkSubPos;
    se = soundSeDefPlay(1301, 0, pos.f, 1);
    _ACTWait(90);
    soundSeDefStop(se);
    soundSeDefPlay(1264, 0, 0, 1);
    stage_SetAnimation(161, 1, 0);
    st01b_yure = iosPadActRequest(boyPad, 9);
    st01b_yure_vol = 128;
    iosPadActVolumeSet(st01b_yure, 128);
    while (stage_CheckAnimationFrame(161, 180, 0) == 0) {
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

    scpSekizou(self, 61, 156, 0, 18, 1000.0f, 528.0f, -150.0f, 1000.0f, 528.0f, -100.0f);
}

void actSt01bEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(64) == 0) {
        static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

        ene_mes[0].func = actSt01bEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 393);
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
    static ActMail floor_mes[2] = {{393}, {392}}; /* derived name */
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(66) == 0) {
        floor_mes[0].func = actSt01bFloorChk;
        act->mail = floor_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt01bWay(GObj *volatile self)
{
    GObj *x = self;
    static ActMail way_mes[2] = {{393}, {392}}; /* derived name */
    Act *act = actInitialize(self);

    _ACTWait(1);

    way_mes[0].func = actSt01bWayOnChk;
    act->mail = way_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt01bEnd(void) {}

void actSt01bSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt01bFloorEvent(int x)
{
    volatile int local = x;
}

void actSt01bWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail way_on_mes[2] = {{393}, {392}}; /* derived name */

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 || gflagChk(66) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);

    way_on_mes[0].func = actSt01bWayOffChk;
    sub->mail = way_on_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt01bWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail way_off_mes[2] = {{393}, {392}}; /* derived name */

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x2000000) == 0 || gflagChk(66) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 0);

    way_off_mes[0].func = actSt01bWayOnChk;
    sub->mail = way_off_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}
