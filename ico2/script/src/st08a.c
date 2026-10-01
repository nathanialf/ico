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

static ActMail ene1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door_main_mes[2] = {{407, actSt08aDoorSwitch}, {429}}; /* derived name */

static ActMail door_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door_switch_mes[2] = {{430}, {429}}; /* derived name */

static float door_up_sound_pos[4] = {-3092.0f, -2727.0f, 3711.0f, 0.0f}; /* derived name */

static ActMail intro_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girl_pos_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hasi_main_mes[2] = {{408, actSt08aHasiSwitch}, {429}}; /* derived name */

static ActMail hasi_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hasi_switch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch_on_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch_off_mes[2] = {{430}, {429}}; /* derived name */

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

void actSt08aEne1Chk(GObj *volatile a0)
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

void actSt08aEne2Chk(GObj *volatile a0)
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

void actSt08aDoorUp(GObj *volatile a0)
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

/* .sdata: the scene's stream handle. */
static char *st08a_adpcm = 0; /* derived name */

void actSt08aHasiUpSub(GObj *volatile a0)
{
    _ACTWait(60);

    while (st08a_adpcm == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(106, 1, 0);

    while (stage_CheckAnimationFrame(106, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    AdpcmPlay(((AdpcmObj *)st08a_adpcm)->stream);

    while (stage_CheckAnimationFrame(106, 180, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 0x11);

    while (stage_CheckAnimationFinish(106) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt08aHasiUp(GObj *volatile a0)
{
    GProc *th;

    lt_switch_layout(55);
    gflagOn(79);
    SetWayGroupActive(30, 1);
    scpSleepEnemyAll();

    demoEnd = 0;
    scpAdpcmPlayRequestFunc(98, &st08a_adpcm, 1, 1, 0);

    th = actCreateSubThread(actSt08aHasiUpSub, 21);

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (st08a_adpcm == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc(&st08a_adpcm, 0x200);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(106, 0, -1);
        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    scpSearchGobj(369)->active = 0;
    scpBoyControlReadDisable = 0;
    lt_switch_layout(54);
}

void actSt08aTorchOnChk(GObj *volatile a0)
{
    Act *self = GOBJ_ACT(a0);

    while (scpTriggerFloorAttr(boyGObj, 0x5000000) != 0 ||
           scpTriggerFloorAttr(boyGObj, 0x7000000) != 0 ||
           scpTriggerFloorAttr(boyGObj, 0xA000000) != 0) {
        _ACTWait(1);
    }

    ((unsigned int *)scpSearchGobj(350))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(351))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(352))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(353))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(354))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(355))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(356))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(357))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(358))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(359))[0x50 / 4] = 0xFFFFFFFF;
    ((unsigned int *)scpSearchGobj(348))[0x50 / 4] = 0xFFFFFFFF;

    torch_on_mes[0].func = actSt08aTorchOffChk;
    self->mail = torch_on_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt08aTorchOffChk(GObj *volatile a0)
{
    Act *self = GOBJ_ACT(a0);

    while (scpTriggerFloorAttr(boyGObj, 0x5000000) == 0 &&
           scpTriggerFloorAttr(boyGObj, 0x7000000) == 0 &&
           scpTriggerFloorAttr(boyGObj, 0xA000000) == 0) {
        _ACTWait(1);
    }

    ((int *)scpSearchGobj(350))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(351))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(352))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(353))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(354))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(355))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(356))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(357))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(358))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(359))[0x50 / 4] = 0;
    ((int *)scpSearchGobj(348))[0x50 / 4] = 0;

    torch_off_mes[0].func = actSt08aTorchOnChk;
    self->mail = torch_off_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt08aDoor(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(71) == 0) {
        stage_SetAnimation(105, 0, 0);
        door_mes[0].func = actSt08aDoorMain;
        self->mail = door_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(11, 1);
        stage_SetAnimation(105, 0, -1);
    }
}

void actSt08aEne1(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    shadow_SetLength(scpSearchGobj(366)->dobj, 100.0f);
    shadow_SetLength(scpSearchGobj(367)->dobj, 100.0f);
    shadow_SetLength(scpSearchGobj(368)->dobj, 100.0f);

    if (gflagChk(72) == 0) {
        ene1_mes[0].func = actSt08aEne1Chk;
        self->mail = ene1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt08aEne2(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(73) == 0) {
        ene2_mes[0].func = actSt08aEne2Chk;
        self->mail = ene2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt08aEnemy1(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(74) == 0) {
        _ACTWait(1);
    }

    _ACTWait(116);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt08aEnemy2(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(74) == 0) {
        _ACTWait(1);
    }

    _ACTWait(100);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt08aEnemy3(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(75) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt08aEnemy4(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(75) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt08aIntro(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(76) == 0) {
        intro_mes[0].func = actSt08aIntroChk;
        self->mail = intro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt08aHint1(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(77) == 0) {
        hint1_mes[0].func = actSt08aHint1Chk;
        self->mail = hint1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(2);
    }
}

void actSt08aGirlPos(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(78) == 0) {
        SleepHint(2);
        girl_pos_mes[0].func = actSt08aGirlPosChk;
        self->mail = girl_pos_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt08aHasi(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(79) == 0) {
        stage_SetAnimation(106, 0, 0);
        hasi_mes[0].func = actSt08aHasiMain;
        self->mail = hasi_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(106, 0, -1);
        scpSearchGobj(369)->active = 0;
        SetWayGroupActive(30, 1);
    }
}

void actSt08aTorch(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    torch_mes[0].func = actSt08aTorchOffChk;
    self->mail = torch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt08aInit(void)
{
    float f = 0.95f;

    scpSetCageVelocityFriction(0x16D, f);
    scpSetCageVelocityFriction(0x16C, f);

    if (gflagChk(80) != 0) {
        stage_SetAnimation(370, 0, 0x1FE);
        scpSearchGobj(365)->active = 0;
    } else {
        stage_SetAnimation(370, 0, 0);
        scpSearchGobj(364)->active = 0;
    }
}

void actSt08aDoorMain(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    scpBoyControlReadDisable = 0;

    sub->mainMail = door_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt08aDoorSwitch(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    door_switch_mes[0].func = actSt08aDoorUp;
    sub->mail = door_switch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt08aDoorUpSub(GObj *volatile a0)
{
    _ACTWait(60);

    stage_SetAnimation(105, 1, 0);

    soundSeDefPlay(1221, 0, door_up_sound_pos, 1);
    _ACTWait(30);
    doorUpDone = 1;
    soundSeDefPlay(1222, 0, door_up_sound_pos, 1);

    while (stage_CheckAnimationFinish(105) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt08aIntroChk(GObj *volatile a0)
{
    while (scpTriggerBall(a0, boyGObj, 100.0f) == 0) {
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

void actSt08aGirlPosChk(GObj *volatile a0)
{
    while (girlGObj == 0 || scpTriggerBall(a0, girlGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(78);
    WakeupHint(2);
}

void actSt08aHint1Chk(GObj *volatile a0)
{
    while (gflagChk(80) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");

    gflagOn(77);
    FinishHint(2);
}

void actSt08aHasiMain(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    scpBoyControlReadDisable = 0;

    sub->mainMail = hasi_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt08aHasiSwitch(GObj *volatile a0)
{
    Act *sub = GOBJ_ACT(a0);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    hasi_switch_mes[0].func = actSt08aHasiUp;
    sub->mail = hasi_switch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
