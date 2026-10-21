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

/* The functions stand in the order of the stage's source (aug6's TRFILE and the
   PAL listing number them so). The ones defined inline are output at
   the end of the file, in the order of the declarations below, which gives
   this build's .text order; the others are output where they stand. The mail
   tables are file-scope statics ahead of the functions that post them, but
   for actSt18aDoorChk's own table (doorChk_mes), a static local, so .data
   keeps the source order and the table takes gcc's local name.N symbol. */

inline void actSt18aIntro(GObj *volatile self);
inline void actSt18aDoor(GObj *volatile self);
inline void actSt18aSwitchL(GObj *volatile self);
inline void actSt18aSwitchR(GObj *volatile self);
inline void actSt18aEne(GObj *volatile self);
inline void actSt18aEnemy1_2(GObj *volatile self);
inline void actSt18aEne2(GObj *volatile self);
inline void actSt18aEnemy2_2(GObj *volatile self);
inline void actSt18aCamera(int x);
inline void actSt18aIntroChk(GObj *volatile self);
inline void actSt18aSwitchLUpChk(GObj *volatile self);
inline void actSt18aSwitchRUpChk(GObj *volatile self);
inline void actSt18aEneChk(GObj *volatile self);
inline void actSt18aEne2Chk(GObj *volatile self);

inline void actSt18aCamera(int x)
{
    volatile int local = x;
}

static ActMail intro_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt18aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(50) == 0) {
        intro_mes[0].func = actSt18aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt18aIntroChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    gflagOn(50);

    scpBoyControlReadDisable = 1;

    _ACTWait(1);

    stage_SetAnimation(288, 1, 0);

    while (stage_CheckAnimationFinish(288) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

static ActMail switchL_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchLUp_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt18aSwitchL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(53) == 0) {
        stage_SetAnimation(91, 0, 0);

        switchL_mes[0].func = actSt18aSwitchLChk;
        act->mail = switchL_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(91, 0, 45);

        switchLUp_mes[0].func = actSt18aSwitchLUpChk;
        act->mail = switchLUp_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

static ActMail switchLChk_mes[2] = {{377}, {376}}; /* derived name */

void actSt18aSwitchLChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(91, 1, 0);

    soundSeDefPlay(1170, 0, 0, 1);

    while (stage_CheckAnimationFrame(91, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
        gflagOn(53);
    }

    switchLChk_mes[0].func = actSt18aSwitchLUpChk;
    sub->mail = switchLChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail switchLUpChk_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt18aSwitchLUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    gflagOff(53);

    stage_SetAnimation(91, 1, 46);
    soundSeDefPlay(1170, 0, 0, 1);

    while (stage_CheckAnimationFrame(91, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLUpChk_mes[0].func = actSt18aSwitchLChk;
    sub->mail = switchLUpChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail switchR_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchRUp_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt18aSwitchR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(54) == 0) {
        stage_SetAnimation(92, 0, 0);

        switchR_mes[0].func = actSt18aSwitchRChk;
        act->mail = switchR_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(92, 0, 45);

        switchRUp_mes[0].func = actSt18aSwitchRUpChk;
        act->mail = switchRUp_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

static ActMail switchRChk_mes[2] = {{377}, {376}}; /* derived name */

void actSt18aSwitchRChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(92, 1, 0);

    soundSeDefPlay(1170, 0, 0, 1);

    while (stage_CheckAnimationFrame(92, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
        gflagOn(54);
    }

    switchRChk_mes[0].func = actSt18aSwitchRUpChk;
    sub->mail = switchRChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail switchRUpChk_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt18aSwitchRUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    gflagOff(54);

    stage_SetAnimation(92, 1, 46);
    soundSeDefPlay(1170, 0, 0, 1);

    while (stage_CheckAnimationFrame(92, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchRUpChk_mes[0].func = actSt18aSwitchRChk;
    sub->mail = switchRUpChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail door_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorDown_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt18aDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(55) == 0) {
        stage_SetAnimation(93, 0, 0);

        door_mes[0].func = actSt18aDoorChk;
        act->mail = door_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(93, 0, -1);

        doorDown_mes[0].func = actSt18aDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt18aDoorChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail doorChk_mes[2] = {{377}, {376}}; /* derived name */

    while (gflagChk(53) == 0 || gflagChk(54) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(55);

    _ACTWait(60);

    stage_SetAnimation(93, 1, 0);

    soundSeDefPlay(1171, 0, 0, 1);
    _ACTWait(60);
    soundSeDefPlay(1172, 0, 0, 1);
    while (stage_CheckAnimationFinish(93) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();
    lt_switch_layout(50);

    doorChk_mes[0].func = actSt18aDoorDownChk;
    sub->mail = doorChk_mes;
    scpBoyControlReadDisable = 0;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail doorDownChk_mes[2] = {{377}, {376}}; /* derived name */

INCLUDE_ASM(actSt18aDoorDownChk);

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt18aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(56) == 0) {
        ene_mes[0].func = actSt18aEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt18aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(56);
    gflagOn(57);
}

void actSt18aEnemy1_1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(690));

    while (gflagChk(57) == 0) {
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
    Generator_Call(scpSearchGobj(690));
}

inline void actSt18aEnemy1_2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(57) == 0) {
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

static ActMail ene2_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt18aEne2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(58) == 0) {
        ene2_mes[0].func = actSt18aEne2Chk;
        act->mail = ene2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt18aEne2Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (girlGObj == 0 || scpTriggerFloorAttr(scpSearchGobj(701), 0x4000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(600);
    gflagOn(58);
    gflagOn(59);
}

void actSt18aEnemy2_1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(691));

    while (gflagChk(59) == 0) {
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
    Generator_Call(scpSearchGobj(691));
}

inline void actSt18aEnemy2_2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(59) == 0) {
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
