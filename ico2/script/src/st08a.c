#include "st08a.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"
#include "script.h"

static ActMail ene1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door_main_mes[2] = {{373, actSt08aDoorSwitch}, {392}}; /* derived name */

static ActMail door_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door_switch_mes[2] = {{393}, {392}}; /* derived name */

static float door_up_sound_pos[4] = {-3092.0f, -2727.0f, 3711.0f, 0.0f}; /* derived name */

static ActMail intro_mes[2] = {{393}, {392}}; /* derived name */

void actSt08aEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(69) == 0) {
            gflagOn(357);
        }
    }
}

void actSt08aEne1Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while ((scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 ||
            scpTriggerFloorAttr(boyGObj, 0x6000000) == 0) &&
           (scpTriggerFloorAttr(girlGObj, 0x1000000) &
            scpTriggerFloorAttr(scpSearchGobj(330), 0x1000000)) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyOne(3415);
    gflagOn(68);
    gflagOn(70);
    stage_SetAnimation(88, 1, 0);

    while (stage_CheckAnimationFinish(88) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    scpWakeupEnemyOne(3415);
}

void actSt08aEne2Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyOne(3415);
    gflagOff(357);
    gflagOn(69);
    gflagOn(71);
    _ACTWait(60);

    scpKillEnemyOne(303);
    scpKillEnemyOne(304);
    scpKillEnemyOne(305);
    scpKillSpiderGroup(306);

    stage_SetAnimation(89, 1, 0);

    while (stage_CheckAnimationFinish(89) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyOne(3415);
}

void actSt08aDoorUp(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(67);
    scpSleepEnemyAll();

    _ACTWait(60);

    stage_SetAnimation(90, 1, 0);

    soundSeDefPlay(1197, 0, door_up_sound_pos, 1);
    _ACTWait(30);
    soundSeDefPlay(1198, 0, door_up_sound_pos, 1);

    while (stage_CheckAnimationFinish(90) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(11, 1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt08aDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(67) == 0) {
        stage_SetAnimation(90, 0, 0);
        door_mes[0].func = actSt08aDoorMain;
        act->mail = door_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        SetWayGroupActive(11, 1);
        stage_SetAnimation(90, 0, -1);
    }
}

void actSt08aEne1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(68) == 0) {
        ene1_mes[0].func = actSt08aEne1Chk;
        act->mail = ene1_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt08aEne2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(69) == 0) {
        ene2_mes[0].func = actSt08aEne2Chk;
        act->mail = ene2_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt08aEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(70) == 0) {
        _ACTWait(1);
    }

    _ACTWait(116);

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt08aEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(70) == 0) {
        _ACTWait(1);
    }

    _ACTWait(100);

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt08aEnemy3(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(71) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt08aEnemy4(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(71) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt08aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(72) == 0) {
        intro_mes[0].func = actSt08aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt08aInit(void)
{
    float f = 0.95f;

    scpSetCageVelocityFriction(335, f);
    scpSetCageVelocityFriction(334, f);

    if (gflagChk(73) != 0) {
        stage_SetAnimation(334, 0, 510);
        scpSearchGobj(335)->active = 0;
    } else {
        stage_SetAnimation(334, 0, 0);
        scpSearchGobj(334)->active = 0;
    }
}

void actSt08aDoorMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = door_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt08aDoorSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    door_switch_mes[0].func = actSt08aDoorUp;
    sub->mail = door_switch_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt08aIntroChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    gflagOn(72);

    stage_SetAnimation(114, 1, 0);
    while (stage_CheckAnimationFinish(114) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}
