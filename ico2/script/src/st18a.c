#include "st18a.h"
#include "layout_texture.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "st04r.h"
#include "typedef.h"
#include "main.h"
#include "include_asm.h"

static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchL_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchR_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorDownChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene2_mes[2] = {{397}, {396}}; /* derived name */

void actSt18aEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(57) == 0) {
            gflagOn(358);
        }
    }
}

void actSt18aSwitchLChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttr(scpSearchGobj(723), 0x1000000) != 0 ||
            scpTriggerFloorAttr(scpSearchGobj(724), 0x1000000) != 0 ||
            scpTriggerFloorAttr(boyGObj, 0x1000000) != 0 ||
            (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x1000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(101, 1, 0);

    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(101, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerFloorAttr(scpSearchGobj(723), 0x1000000) != 0 ||
        scpTriggerFloorAttr(scpSearchGobj(724), 0x1000000) != 0 ||
        scpTriggerFloorAttr(boyGObj, 0x1000000) != 0 ||
        scpTriggerFloorAttr(girlGObj, 0x1000000) != 0) {
        gflagOn(54);
    }

    switchLChk_mes[0].func = actSt18aSwitchLUpChk;
    sub->mail = switchLChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt18aSwitchLUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    gflagOff(54);

    stage_SetAnimation(101, 1, 46);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(101, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupItemWithBoundary(3054.0f, 1530.0f, -3061.0f, 100.0f);

    while (stage_CheckAnimationFrame(101, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLUpChk_mes[0].func = actSt18aSwitchLChk;
    sub->mail = switchLUpChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt18aSwitchRChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttr(scpSearchGobj(723), 0x2000000) != 0 ||
            scpTriggerFloorAttr(scpSearchGobj(724), 0x2000000) != 0 ||
            scpTriggerFloorAttr(boyGObj, 0x2000000) != 0 ||
            (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(102, 1, 0);

    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(102, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerFloorAttr(scpSearchGobj(723), 0x2000000) != 0 ||
        scpTriggerFloorAttr(scpSearchGobj(724), 0x2000000) != 0 ||
        scpTriggerFloorAttr(boyGObj, 0x2000000) != 0 ||
        scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        gflagOn(55);
    }

    switchRChk_mes[0].func = actSt18aSwitchRUpChk;
    sub->mail = switchRChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt18aSwitchRUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    gflagOff(55);

    stage_SetAnimation(102, 1, 46);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(102, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupItemWithBoundary(1451.0f, 1530.0f, -3039.0f, 100.0f);

    while (stage_CheckAnimationFrame(102, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchRUpChk_mes[0].func = actSt18aSwitchRChk;
    sub->mail = switchRUpChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt18aDoorChk(GObj *volatile self);

INCLUDE_ASM(actSt18aDoorChk);

void actSt18aDoorDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (gflagChk(54) != 0 && gflagChk(55) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    gflagOff(56);

    stage_SetAnimation(104, 1, 0);

    soundSeDefPlay(1197, 0, 0, 1);
    _ACTWait(50);
    soundSeDefPlay(1198, 0, 0, 1);
    while (stage_CheckAnimationFinish(104) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    doorDownChk_mes[0].func = actSt18aDoorChk;
    sub->mail = doorDownChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt18aEnemy1_1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(715));

    while (gflagChk(58) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
    Generator_Call(scpSearchGobj(715));
}

void actSt18aEnemy2_1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(716));

    while (gflagChk(60) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_Call(scpSearchGobj(716));
}

void actSt18aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(51) == 0) {
        intro_mes[0].func = actSt18aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt18aDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(56) == 0) {
        stage_SetAnimation(103, 0, 0);

        door_mes[0].func = actSt18aDoorChk;
        act->mail = door_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(103, 0, -1);

        doorDown_mes[0].func = actSt18aDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt18aSwitchL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(54) == 0) {
        stage_SetAnimation(101, 0, 0);

        switchL_mes[0].func = actSt18aSwitchLChk;
        act->mail = switchL_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(101, 0, 45);

        switchLUp_mes[0].func = actSt18aSwitchLUpChk;
        act->mail = switchLUp_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt18aSwitchR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(55) == 0) {
        stage_SetAnimation(102, 0, 0);

        switchR_mes[0].func = actSt18aSwitchRChk;
        act->mail = switchR_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(102, 0, 45);

        switchRUp_mes[0].func = actSt18aSwitchRUpChk;
        act->mail = switchRUp_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt18aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(57) == 0) {
        ene_mes[0].func = actSt18aEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt18aEnemy1_2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(58) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
}

void actSt18aEne2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(59) == 0) {
        ene2_mes[0].func = actSt18aEne2Chk;
        act->mail = ene2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt18aEnemy2_2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(60) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt18aCamera(int x)
{
    volatile int local = x;
}

void actSt18aIntroChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    gflagOn(51);

    scpBoyControlReadDisable = 1;

    _ACTWait(1);

    stage_SetAnimation(321, 1, 0);

    while (stage_CheckAnimationFinish(321) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt18aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOff(358);
    gflagOn(57);
    gflagOn(58);
}

void actSt18aEne2Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (girlGObj == 0 || scpTriggerFloorAttr(scpSearchGobj(724), 0x4000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(300);
    gflagOn(59);
    gflagOn(60);
}
