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

static void actSt18aDoorChkSub(GObj *volatile a0);

static ActMail intro_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchL_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchR_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorDownChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene2_mes[2] = {{430}, {429}}; /* derived name */

void actSt18aEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(61) == 0) {
            gflagOn(391);
        }
    }
}

void actSt18aIntroChk(GObj *volatile a0)
{
    while (scpTriggerBall(a0, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    gflagOn(55);

    scpBoyControlReadDisable = 1;

    _ACTWait(1);

    stage_SetAnimation(354, 1, 0);

    while (stage_CheckAnimationFinish(354) == 0) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(354, 1, -1);
            SetCameraFlag_LwsCutBack();
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    lt_switch_layout(54);
    scpBoyControlReadDisable = 0;
}

void actSt18aSwitchLChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttr(scpSearchGobj(773), 0x1000000) != 0 ||
            scpTriggerFloorAttr(scpSearchGobj(774), 0x1000000) != 0 ||
            scpTriggerFloorAttr(boyGObj, 0x1000000) != 0 ||
            (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x1000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(121, 1, 0);

    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(121, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerFloorAttr(scpSearchGobj(773), 0x1000000) != 0 ||
        scpTriggerFloorAttr(scpSearchGobj(774), 0x1000000) != 0 ||
        scpTriggerFloorAttr(boyGObj, 0x1000000) != 0 ||
        (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x1000000) != 0)) {
        gflagOn(58);
        FinishHint(7);
    }

    switchLChk_mes[0].func = actSt18aSwitchLUpChk;
    sub->mail = switchLChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt18aSwitchLUpChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    gflagOff(58);

    stage_SetAnimation(121, 1, 46);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(121, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupItemWithBoundary(3054.0f, 1530.0f, -3061.0f, 100.0f);

    while (stage_CheckAnimationFrame(121, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLUpChk_mes[0].func = actSt18aSwitchLChk;
    sub->mail = switchLUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt18aSwitchRChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttr(scpSearchGobj(773), 0x2000000) != 0 ||
            scpTriggerFloorAttr(scpSearchGobj(774), 0x2000000) != 0 ||
            scpTriggerFloorAttr(boyGObj, 0x2000000) != 0 ||
            (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(122, 1, 0);

    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(122, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerFloorAttr(scpSearchGobj(773), 0x2000000) != 0 ||
        scpTriggerFloorAttr(scpSearchGobj(774), 0x2000000) != 0 ||
        scpTriggerFloorAttr(boyGObj, 0x2000000) != 0 ||
        (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0)) {
        gflagOn(59);
        FinishHint(7);
    }

    switchRChk_mes[0].func = actSt18aSwitchRUpChk;
    sub->mail = switchRChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt18aSwitchRUpChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    while (scpTriggerFloorAttrTargetMan(a0, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    gflagOff(59);

    stage_SetAnimation(122, 1, 46);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(122, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupItemWithBoundary(1451.0f, 1530.0f, -3039.0f, 100.0f);

    while (stage_CheckAnimationFrame(122, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchRUpChk_mes[0].func = actSt18aSwitchRChk;
    sub->mail = switchRUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for, and the flag actSt18aDoorChkSub raises when the door check is
   done. */
static int demoEnd;

static int doorChkDone; /* derived name */

void actSt18aDoorChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);
    GProc *th;

    while (gflagChk(58) == 0 || gflagChk(59) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(60);

    th = actCreateSubThread(actSt18aDoorChkSub, 21);
    demoEnd = 0;
    doorChkDone = 0;

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

        stage_SetAnimation(123, 0, -1);

        if (doorChkDone == 0) {
            soundSeDefPlay(1222, 0, 0, 1);
        }

        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    lt_switch_layout(54);

    doorChk_mes[0].func = actSt18aDoorDownChk;
    sub->mail = doorChk_mes;
    scpBoyControlReadDisable = 0;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt18aDoorDownChk(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    while (gflagChk(58) != 0 && gflagChk(59) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    gflagOff(60);

    stage_SetAnimation(124, 1, 0);

    soundSeDefPlay(1221, 0, 0, 1);
    _ACTWait(50);
    soundSeDefPlay(1222, 0, 0, 1);
    while (stage_CheckAnimationFinish(124) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    doorDownChk_mes[0].func = actSt18aDoorChk;
    sub->mail = doorDownChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt18aEnemy1_1(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask(scpSearchGobj(765));
    Generator_Mask(scpSearchGobj(766));

    while (gflagChk(62) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    Generator_Call(scpSearchGobj(765));
    Generator_Call(scpSearchGobj(766));
}

void actSt18aEnemy2_1(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask(scpSearchGobj(766));

    while (gflagChk(64) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_Call(scpSearchGobj(766));
}

void actSt18aIntro(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(55) == 0) {
        intro_mes[0].func = actSt18aIntroChk;
        self->mail = intro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aDoor(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(60) == 0) {
        stage_SetAnimation(123, 0, 0);

        door_mes[0].func = actSt18aDoorChk;
        self->mail = door_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(123, 0, -1);

        doorDown_mes[0].func = actSt18aDoorDownChk;
        self->mail = doorDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aSwitchL(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(58) == 0) {
        stage_SetAnimation(121, 0, 0);

        switchL_mes[0].func = actSt18aSwitchLChk;
        self->mail = switchL_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(121, 0, 45);

        switchLUp_mes[0].func = actSt18aSwitchLUpChk;
        self->mail = switchLUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aSwitchR(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(59) == 0) {
        stage_SetAnimation(122, 0, 0);

        switchR_mes[0].func = actSt18aSwitchRChk;
        self->mail = switchR_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(122, 0, 45);

        switchRUp_mes[0].func = actSt18aSwitchRUpChk;
        self->mail = switchRUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aEne(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(61) == 0) {
        ene_mes[0].func = actSt18aEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aEnemy1_2(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(62) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
}

void actSt18aEne2(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(63) == 0) {
        ene2_mes[0].func = actSt18aEne2Chk;
        self->mail = ene2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aEnemy2_2(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(64) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt18aCamera(int x)
{
    volatile int local = x;
}

static void actSt18aDoorChkSub(GObj *volatile a0)
{
    _ACTWait(60);

    stage_SetAnimation(123, 1, 0);

    if (scpTriggerFloorAttr(boyGObj, 0x5000000) != 0) {
        SetCameraFlag_LwsCutBack();
    }

    soundSeDefPlay(1221, 0, 0, 1);
    _ACTWait(50);
    doorChkDone = 1;
    soundSeDefPlay(1222, 0, 0, 1);
    while (stage_CheckAnimationFinish(123) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt18aEneChk(GObj *volatile a0)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOff(391);
    gflagOn(61);
    gflagOn(62);
}

void actSt18aEne2Chk(GObj *volatile a0)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (girlGObj == 0 || scpTriggerFloorAttr(scpSearchGobj(774), 0x4000000) == 0) {
        _ACTWait(1);
    }
    FinishHint(8);
    _ACTWait(300);
    gflagOn(63);
    gflagOn(64);
}
