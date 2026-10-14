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

static void actSt08aDoorUpSub(GObj *volatile self);

static ActMail ene1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door_main_mes[2] = {{407, actSt08aDoorSwitch}, {429}}; /* derived name */

static ActMail door_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door_switch_mes[2] = {{430}, {429}}; /* derived name */

static float door_up_sound_pos[4] = {-3092.0f, -2727.0f, 3711.0f, 0.0f}; /* derived name */

static ActMail intro_mes[2] = {{430}, {429}}; /* derived name */

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for, and the flag actSt08aDoorUpSub raises when the door is all
   the way up. */
static int demoEnd;

static int doorUpDone; /* derived name */

void actSt08aEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(73) == 0) {
            gflagOn(391);
        }
    }
}

void actSt08aEne1Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(71) == 0 || (scpTriggerFloorAttr(boyGObj, 0x6000000) == 0 &&
                                 scpTriggerFloorAttr(girlGObj, 0x1000000) == 0)) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyOne(3757);
    gflagOn(72);
    gflagOn(74);
    stage_SetAnimation(103, 1, 0);

    if (scpTriggerFloorAttr(boyGObj, 0x6000000) == 0 &&
        scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        SetCameraFlag_LwsCutBack();
    }

    while (stage_CheckAnimationFinish(103) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(54);
    scpWakeupEnemyOne(3757);
}

void actSt08aEne2Chk(GObj *volatile self)
{
    int save;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(72) == 0 || scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyOne(3757);
    gflagOff(391);
    gflagOn(73);
    gflagOn(75);
    _ACTWait(60);

    save = iosPadActRequestEnable;
    iosPadActRequestEnable = 0;

    scpKillEnemyOne(334);
    scpKillEnemyOne(335);
    scpKillEnemyOne(336);
    scpKillSpiderGroup(337);
    Generator_Delete(scpSearchGobj(338));
    Generator_Delete(scpSearchGobj(339));

    stage_SetAnimation(104, 1, 0);

    if (scpTriggerFloorAttr(boyGObj, 0x5000000) == 0) {
        SetCameraFlag_LwsCutBack();
    }

    while (stage_CheckAnimationFinish(104) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequestEnable = save;
    scpPlayMot(boyGObj, 0);
    lt_switch_layout(54);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyOne(3757);
}

void actSt08aDoorUp(GObj *volatile self)
{
    GProc *th;

    lt_switch_layout(55);
    gflagOn(71);
    scpSleepEnemyAll();

    th = actCreateSubThread(actSt08aDoorUpSub, 21);
    demoEnd = 0;
    doorUpDone = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(105, 0, -1);
        scpFadeIn(3.0f);
        if (doorUpDone == 0) {
            soundSeDefPlay(1222, 0, 0, 1);
        }
    }

    SetWayGroupActive(11, 1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(54);
}

void actSt08aDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(71) == 0) {
        stage_SetAnimation(105, 0, 0);
        door_mes[0].func = actSt08aDoorMain;
        act->mail = door_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(11, 1);
        stage_SetAnimation(105, 0, -1);
    }
}

void actSt08aEne1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    shadow_SetLength(scpSearchGobj(366)->dobj, 100.0f);
    shadow_SetLength(scpSearchGobj(367)->dobj, 100.0f);
    shadow_SetLength(scpSearchGobj(368)->dobj, 100.0f);

    if (gflagChk(72) == 0) {
        ene1_mes[0].func = actSt08aEne1Chk;
        act->mail = ene1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt08aEne2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(73) == 0) {
        ene2_mes[0].func = actSt08aEne2Chk;
        act->mail = ene2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt08aEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(74) == 0) {
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

    while (gflagChk(74) == 0) {
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

    while (gflagChk(75) == 0) {
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

    while (gflagChk(75) == 0) {
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

    if (gflagChk(76) == 0) {
        intro_mes[0].func = actSt08aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt08aInit(void)
{
    float f = 0.95f;

    scpSetCageVelocityFriction(365, f);
    scpSetCageVelocityFriction(364, f);

    if (gflagChk(80) != 0) {
        stage_SetAnimation(370, 0, 510);
        scpSearchGobj(365)->active = 0;
    } else {
        stage_SetAnimation(370, 0, 0);
        scpSearchGobj(364)->active = 0;
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
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt08aIntroChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;

    gflagOn(76);

    stage_SetAnimation(135, 1, 0);
    while (stage_CheckAnimationFinish(135) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);
    scpBoyControlReadDisable = 0;
}
