#include "st10r.h"

#ifndef VERSION_NTSC
#include "gamesys.h"
#endif

#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "gobj_process.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "boyact.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "cage.h"
#include "motionManager2.h"

#ifndef VERSION_NTSC
#include "rotObject.h"
#endif

#include "typedef.h"
#include "main.h"
#include "script.h"

#ifdef VERSION_NTSC
static ActMail floor_mes[2] = {{397}, {396}}; /* derived name */

static ActMail cage_mes[2] = {{397}, {396}}; /* derived name */

static ActMail tower_mes[2] = {{397}, {396}}; /* derived name */

static ActMail exit_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chain_main_mes[2] = {{378, actSt10rChainSwitch}, {396}}; /* derived name */

static ActMail chain_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chain_switch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_down1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_up1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_down2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fence_up2_mes[2] = {{397}, {396}}; /* derived name */
#else
static void actSt10rCageSub(GObj *volatile self);
static void actSt10rChainMoveSub(GObj *volatile self);
static void actSt10rFloorSub(GObj *volatile self);
static void actSt10rTowerResqueChk(GObj *volatile self);
static void actSt10rWayOffChk(GObj *volatile self);
static void actSt10rWayOnChk(GObj *volatile self);

static ActMail floor_mes[2] = {{430}, {429}}; /* derived name */

static ActMail floor_hit_mes[2] = {{430}, {429}}; /* derived name */

static ActMail cage_mes[2] = {{430}, {429}}; /* derived name */

static ActMail tower_mes[2] = {{430}, {429}}; /* derived name */

static ActMail exit_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chain_main_mes[2] = {{408, actSt10rChainSwitch}, {429}}; /* derived name */

static ActMail chain_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chain_switch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fence_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fence2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fence_down1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fence_up1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fence_down2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fence_up2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_onchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_offchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail tower_resque_mes[2] = {{430}, {429}}; /* derived name */
#endif

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for. */
static int demoEnd;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{-296.0f, 327.0f, 2125.0f, 0.0f}}; /* derived name */

/* .sdata: the floor and cage stream handles, the scene stream, the chain's. */
SqEntry *st10r_floor = 0;

SqEntry *cage10r = 0;

static SqEntry *st10r_adpcm = 0; /* derived name */

SqEntry *chain10r = 0;

#ifdef VERSION_NTSC
void actSt10rInit(void)
{
    if (gflagChk(274) != 0) {
        stage_SetAnimation(350, 0, -1);
        SetWayGroupActive(15, 1);
    } else {
        stage_SetAnimation(350, 0, 0);
    }

    if (gflagChk(276) == 0) {
        SetWayGroupActive(23, 0);
        stage_SetAnimation(353, 0, 0);
    } else {
        SetWayGroupActive(23, 1);
        stage_SetAnimation(353, 0, -1);
    }

    if (gflagChk(275) == 0) {
        stage_SetAnimation(352, 0, 0);
    } else {
        stage_SetAnimation(352, 0, -1);
    }
}

void actSt10rFloorChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 50.0f) == 0) {
        _ACTWait(1);
    }

    iosPadActRequest(boyPad, 16);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(274);

    scpAdpcmPlayRequestFunc(90, &st10r_floor, 1, 1, 1);
    while (st10r_floor == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(350, 1, 0);

    while (stage_CheckAnimationFinish(350) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    SetWayGroupActive(15, 1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt10rCageMain(GObj *volatile self)
{
    while (!(scpGetRotObjectRotCount(1499) < -2.0f)) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(275);

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(71, &cage10r, 1, 1, 1);
    while (cage10r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(352, 1, 0);

    while (stage_CheckAnimationFinish(352) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt10rTowerChk(GObj *volatile self)
{
    GProc *th;
    GObj *n;
    int f;

    while ((n = scpIsBombExplode(19)) == 0 || scpTriggerBall(self, n, 350.0f) == 0) {
        _ACTWait(1);
    }

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x4000000) != 0) {
        actCreateSubThread(actSt10rGirlWay, 21);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(276);

    reg_SetScissorSw(1);

    scpAdpcmPlayRequestFunc(70, &st10r_adpcm, 1, 1, 0);

    _ACTWait(60);
    while (st10r_adpcm == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(actSt10rTowerConte, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    f = demoEnd ^ 1;

    if (f) {
        scpAdpcmFadeClose(st10r_adpcm, 192);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosPadActStopAll();

    iosThreadSetPri(&((GProc *)th)->thread, 34);

    if (f) {
        stage_SetAnimation(353, 1, -1);
        SetCameraFlag_GamecamCutBack();
        scpPlayMot(boyGObj, 0);
        scpFadeIn(3.0f);
    }

    scpSearchGobj(1489)->active = 1;
    scpSearchGobj(1490)->active = 1;

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    reg_SetScissorSw(0);

    SetWayGroupActive(23, 1);
}

void actSt10rTowerConte(GObj *volatile self)
{
    stage_SetAnimation(353, 1, 0);

    AdpcmPlay(st10r_adpcm->stream);

    scpSearchGobj(1489)->active = 0;
    scpSearchGobj(1490)->active = 0;

    while (stage_CheckAnimationFrame(353, 215, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFrame(353, 270, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(353, 280, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFrame(353, 300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(353) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt10rChainMove(GObj *volatile self)
{
    int se;

    lt_switch_layout(51);

    scpSleepEnemyAll();

    gflagOn(277);

    scpSearchGobj(1516)->active = 1;

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(91, &chain10r, 1, 1, 1);

    while (chain10r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(351, 1, 0);

    se = soundSeDefPlay(1263, 0, 0, 1);

    _ACTWait(180);

    soundSeDefStop(se);

    soundSeDefPlay(1264, 0, 0, 1);

    iosPadActRequest(boyPad, 17);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt10rFence(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(290) == 0) {
        scpSearchGobj(1525)->active = 0;
        scpSearchGobj(1526)->active = 0;
        scpSearchGobj(1529)->active = 0;
        scpSearchGobj(1530)->active = 0;
        scpSearchGobj(1531)->active = 0;
        scpSearchGobj(1532)->active = 0;
        scpSearchGobj(1533)->active = 0;
        scpSearchGobj(1534)->active = 0;
        scpSearchGobj(1535)->active = 0;
        scpSearchGobj(1536)->active = 0;

        scpLinkBGAtoLayoutedTarget(1527, 129);

        stage_SetAnimation(129, 0, 30);

        SetWayGroupActive(37, 1);
        SetWayGroupActive(38, 1);

        fence_mes[0].func = actSt10rFenceUpChk;
        act->mail = fence_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpSearchGobj(1527)->active = 0;
        scpSearchGobj(1528)->active = 0;
        scpSearchGobj(1533)->active = 0;
        scpSearchGobj(1534)->active = 0;
        scpSearchGobj(1535)->active = 0;
        scpSearchGobj(1536)->active = 0;

        gflagOff(290);

        scpLinkBGAtoLayoutedTarget(1525, 129);

        stage_SetAnimation(129, 0, 0);

        fence2_mes[0].func = actSt10rFenceDownChk2;
        act->mail = fence2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10rFenceDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1527), 5.0f) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1533)->active = 0;
    scpSearchGobj(1534)->active = 0;
    scpSearchGobj(1535)->active = 0;
    scpSearchGobj(1536)->active = 0;

    stage_SetAnimation(129, 1, 0);

    while (stage_CheckAnimationFrame(129, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1314, 0, 0, 1);

    while (stage_CheckAnimationFrame(129, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 1);
    SetWayGroupActive(38, 1);

    gflagOff(281);

    fence_down1_mes[0].func = actSt10rFenceUpChk;
    sub->mail = fence_down1_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10rFenceUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1527), 5.0f) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1533)->active = 1;
    scpSearchGobj(1534)->active = 1;
    scpSearchGobj(1535)->active = 1;
    scpSearchGobj(1536)->active = 1;

    stage_SetAnimation(129, 1, 31);

    while (stage_CheckAnimationFrame(129, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1314, 0, 0, 1);

    while (stage_CheckAnimationFinish(129) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 0);
    SetWayGroupActive(38, 0);

    gflagOn(281);

    fence_up1_mes[0].func = actSt10rFenceDownChk;
    sub->mail = fence_up1_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10rFenceDownChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1525), 5.0f) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1529)->active = 0;
    scpSearchGobj(1530)->active = 0;
    scpSearchGobj(1531)->active = 0;
    scpSearchGobj(1532)->active = 0;

    stage_SetAnimation(129, 1, 0);

    while (stage_CheckAnimationFrame(129, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1314, 0, 0, 1);

    while (stage_CheckAnimationFrame(129, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 1);
    SetWayGroupActive(38, 1);

    gflagOff(281);

    fence_down2_mes[0].func = actSt10rFenceUpChk2;
    sub->mail = fence_down2_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10rFenceUpChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1525), 5.0f) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1529)->active = 1;
    scpSearchGobj(1530)->active = 1;
    scpSearchGobj(1531)->active = 1;
    scpSearchGobj(1532)->active = 1;

    stage_SetAnimation(129, 1, 31);

    while (stage_CheckAnimationFrame(129, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1314, 0, 0, 1);

    while (stage_CheckAnimationFinish(129) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 0);
    SetWayGroupActive(38, 0);

    gflagOn(281);

    fence_up2_mes[0].func = actSt10rFenceDownChk2;
    sub->mail = fence_up2_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt10rFloor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(274) == 0) {
        floor_mes[0].func = actSt10rFloorChk;
        act->mail = floor_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10rCage(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    scpSetCageVelocityFriction(1521, 0.95f);

    if (gflagChk(275) == 0) {
        cage_mes[0].func = actSt10rCageMain;
        act->mail = cage_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10rTower(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(276) == 0) {
        tower_mes[0].func = actSt10rTowerChk;
        act->mail = tower_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}
#else
void actSt10rInit(void)
{
    if (gflagChk(300) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(381, 0, -1);
#else
        stage_SetAnimation(385, 0, -1);
#endif
        SetWayGroupActive(15, 1);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(381, 0, 0);
#else
        stage_SetAnimation(385, 0, 0);
#endif
    }

    if (gflagChk(302) == 0) {
        SetWayGroupActive(23, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(385, 0, 0);
#else
        stage_SetAnimation(389, 0, 0);
#endif
    } else {
        SetWayGroupActive(23, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(385, 0, -1);
#else
        stage_SetAnimation(389, 0, -1);
#endif
        FinishHint(21);
    }

    if (gflagChk(301) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(384, 0, 0);
#else
        stage_SetAnimation(388, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(384, 0, -1);
#else
        stage_SetAnimation(388, 0, -1);
#endif
        FinishHint(22);
    }
}

void actSt10rEnd(void)
{
    gamesysObjInfoCls(scpSearchGobj(1634)->kind, scpSearchGobj(1634)->labelId);
    gamesysObjInfoCls(scpSearchGobj(1632)->kind, scpSearchGobj(1632)->labelId);
}

void actSt10rFloorChk(GObj *volatile self)
{
    GProc *th;

    while (scpTriggerBall(self, boyGObj, 50.0f) == 0) {
        _ACTWait(1);
    }

    iosPadActRequest(boyPad, 16);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(300);
    WakeupHint(21);

    scpAdpcmPlayRequestFunc(92, &st10r_floor, 1, 1, 1);
    while (st10r_floor == 0) {
        _ACTWait(1);
    }

    demoEnd = 0;
    th = actCreateSubThread(actSt10rFloorSub, 21);
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&((GProc *)th)->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st10r_floor, 512);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(381, 0, -1);
#else
        stage_SetAnimation(385, 0, -1);
#endif
        scpFadeIn(3.0f);
    }

    SetWayGroupActive(15, 1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}

static void actSt10rFloorHitChk(GObj *volatile self)
{
    for (;;) {
        while (scpTriggerBall(self, boyGObj, 100.0f) == 0 || gflagChk(300) != 0 ||
               (ForMotionViewer_GetCurrentMotion(boyGObj) != 47 &&
                ForMotionViewer_GetCurrentMotion(boyGObj) != 48 &&
                ForMotionViewer_GetCurrentMotion(boyGObj) != 49 &&
                ForMotionViewer_GetCurrentMotion(boyGObj) != 62)) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(382, 1, 0);
#else
        stage_SetAnimation(386, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(382, 12, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(386, 12, 0) == 0) {
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1335, 0, 0, 1);
        soundSeDefPlay(1335, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFinish(382) == 0) {
#else
        while (stage_CheckAnimationFinish(386) == 0) {
#endif
            _ACTWait(1);
        }
        _ACTWait(1);
    }
}

void actSt10rCageMain(GObj *volatile self)
{
    GProc *th;

    while (!(scpGetRotObjectRotCount(1605) < -2.0f)) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(301);
    FinishHint(22);

    SetRotObjectLockFlag(scpSearchGobj(1605), 1);

    demoEnd = 0;
    scpAdpcmPlayRequestFunc(73, &cage10r, 1, 1, 0);

    th = actCreateSubThread(actSt10rCageSub, 21);

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&((GProc *)th)->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (cage10r == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&cage10r, 512);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(384, 0, -1);
#else
        stage_SetAnimation(388, 0, -1);
#endif
        _ACTWait(1);

        HotInitCageGeo(scpSearchGobj(1627));
        _ACTWait(1);

        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}

void actSt10rTowerChk(GObj *volatile self)
{
    GProc *th;
    GObj *n;
    int f;

    while ((n = scpIsBombExplode(19)) == 0 || scpTriggerBall(self, n, 350.0f) == 0) {
        _ACTWait(1);
    }

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x4000000) != 0) {
        actCreateSubThread(actSt10rGirlWay, 21);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    FinishHint(21);

    reg_SetScissorSw(1);

    scpAdpcmPlayRequestFunc(72, &st10r_adpcm, 1, 1, 0);

    _ACTWait(60);
    while (st10r_adpcm == 0) {
        _ACTWait(1);
    }

    gflagOn(302);

    th = actCreateSubThread(actSt10rTowerConte, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    f = demoEnd ^ 1;

    if (f) {
        scpAdpcmFadeCloseFunc(&st10r_adpcm, 192);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosPadActStopAll();

    iosThreadSetPri(&((GProc *)th)->thread, 34);

    if (f) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(385, 1, -1);
#else
        stage_SetAnimation(389, 1, -1);
#endif
        SetCameraFlag_GamecamCutBack();
        scpPlayMot(boyGObj, 0);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(8.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    scpSearchGobj(1594)->active = 1;
    scpSearchGobj(1595)->active = 1;

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    reg_SetScissorSw(0);

    SetWayGroupActive(23, 1);

    gflagOn(303);
}

void actSt10rTowerConte(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(385, 1, 0);
#else
    stage_SetAnimation(389, 1, 0);
#endif

    AdpcmPlay(st10r_adpcm->stream);

    scpSearchGobj(1594)->active = 0;
    scpSearchGobj(1595)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(385, 215, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(389, 215, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(385, 270, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(389, 270, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(385, 280, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(389, 280, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(385, 300, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(389, 300, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(385) == 0) {
#else
    while (stage_CheckAnimationFinish(389) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt10rChainMove(GObj *volatile self)
{
    GProc *th;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    scpSleepEnemyAll();

    gflagOn(304);

    scpSearchGobj(1622)->active = 1;

    scpAdpcmPlayRequestFunc(93, &chain10r, 1, 1, 0);

    demoEnd = 0;

    th = actCreateSubThread(actSt10rChainMoveSub, 21);

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&((GProc *)th)->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (chain10r == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&chain10r, 512);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(383, 0, -1);
#else
        stage_SetAnimation(387, 0, -1);
#endif

        scpFadeIn(3.0f);
    }

    soundSeDefPlay(1288, 0, 0, 1);

    iosPadActRequest(boyPad, 17);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}

void actSt10rFence(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(317) == 0) {
        scpSearchGobj(1631)->active = 0;
        scpSearchGobj(1632)->active = 0;
        scpSearchGobj(1635)->active = 0;
        scpSearchGobj(1636)->active = 0;
        scpSearchGobj(1637)->active = 0;
        scpSearchGobj(1638)->active = 0;
        scpSearchGobj(1639)->active = 0;
        scpSearchGobj(1640)->active = 0;
        scpSearchGobj(1641)->active = 0;
        scpSearchGobj(1642)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        scpLinkBGAtoLayoutedTarget(1633, 145);
#else
        scpLinkBGAtoLayoutedTarget(1633, 149);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(145, 0, 30);
#else
        stage_SetAnimation(149, 0, 30);
#endif

        SetWayGroupActive(37, 1);
        SetWayGroupActive(38, 1);

        fence_mes[0].func = actSt10rFenceUpChk;
        act->mail = fence_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(1633)->active = 0;
        scpSearchGobj(1634)->active = 0;
        scpSearchGobj(1639)->active = 0;
        scpSearchGobj(1640)->active = 0;
        scpSearchGobj(1641)->active = 0;
        scpSearchGobj(1642)->active = 0;

        gflagOff(317);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        scpLinkBGAtoLayoutedTarget(1631, 145);
#else
        scpLinkBGAtoLayoutedTarget(1631, 149);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(145, 0, 0);
#else
        stage_SetAnimation(149, 0, 0);
#endif

        if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
            scpPlayPosSet(girlGObj, 417.0f, 900.0f, -1096.0f);
        }

        fence2_mes[0].func = actSt10rFenceDownChk2;
        act->mail = fence2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt10rFenceDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1633), 5.0f) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1639)->active = 0;
    scpSearchGobj(1640)->active = 0;
    scpSearchGobj(1641)->active = 0;
    scpSearchGobj(1642)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(145, 1, 0);
#else
    stage_SetAnimation(149, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(145, 10, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(149, 10, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1339, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(145, 30, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(149, 30, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 1);
    SetWayGroupActive(38, 1);

    gflagOff(308);

    fence_down1_mes[0].func = actSt10rFenceUpChk;
    sub->mail = fence_down1_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10rFenceUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1633), 5.0f) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1639)->active = 1;
    scpSearchGobj(1640)->active = 1;
    scpSearchGobj(1641)->active = 1;
    scpSearchGobj(1642)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(145, 1, 31);
#else
    stage_SetAnimation(149, 1, 31);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(145, 40, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(149, 40, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1339, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(145) == 0) {
#else
    while (stage_CheckAnimationFinish(149) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 0);
    SetWayGroupActive(38, 0);

    gflagOn(308);

    fence_up1_mes[0].func = actSt10rFenceDownChk;
    sub->mail = fence_up1_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10rFenceDownChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1631), 5.0f) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1635)->active = 0;
    scpSearchGobj(1636)->active = 0;
    scpSearchGobj(1637)->active = 0;
    scpSearchGobj(1638)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(145, 1, 0);
#else
    stage_SetAnimation(149, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(145, 10, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(149, 10, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1339, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(145, 30, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(149, 30, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 1);
    SetWayGroupActive(38, 1);

    gflagOff(308);

    fence_down2_mes[0].func = actSt10rFenceUpChk2;
    sub->mail = fence_down2_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10rFenceUpChk2(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, scpSearchGobj(1631), 5.0f) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1635)->active = 1;
    scpSearchGobj(1636)->active = 1;
    scpSearchGobj(1637)->active = 1;
    scpSearchGobj(1638)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(145, 1, 31);
#else
    stage_SetAnimation(149, 1, 31);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(145, 40, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(149, 40, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1339, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(145) == 0) {
#else
    while (stage_CheckAnimationFinish(149) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 0);
    SetWayGroupActive(38, 0);

    gflagOn(308);

    fence_up2_mes[0].func = actSt10rFenceDownChk2;
    sub->mail = fence_up2_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10rFloor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(300) == 0) {
        SleepHint(21);

        floor_mes[0].func = actSt10rFloorChk;
        act->mail = floor_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt10rFloorHit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(300) == 0) {
        floor_hit_mes[0].func = actSt10rFloorHitChk;
        act->mail = floor_hit_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt10rCage(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    scpSetCageVelocityFriction(1627, 0.95f);

    if (gflagChk(301) == 0) {
        cage_mes[0].func = actSt10rCageMain;
        act->mail = cage_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        SetRotObjectLockFlag(scpSearchGobj(1605), 1);
    }
}

void actSt10rTower(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(302) == 0) {
        tower_mes[0].func = actSt10rTowerChk;
        act->mail = tower_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt10rTowerResque(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(302) == 0) {
        tower_resque_mes[0].func = actSt10rTowerResqueChk;
        act->mail = tower_resque_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}
#endif

void actSt10rExit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    exit_mes[0].func = actSt10rExitChk;
    act->mail = exit_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

#ifdef VERSION_NTSC
void actSt10rChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(277) == 0) {
        stage_SetAnimation(351, 0, 0);
        scpSearchGobj(1516)->active = 0;

        chain_mes[0].func = actSt10rChainMain;
        act->mail = chain_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(351, 0, -1);
    }
}

void actSt10rSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpSekizou(self, 278, 354, 0, 18, 0.0f, 327.0f, 4649.0f, -75.0f, 327.0f, 4649.0f);
}

void actSt10rEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(279) == 0) {
        ene_mes[0].func = actSt10rEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt10rEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(280) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);

    Generator_MaskOff(self);
}

void actSt10rEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(280) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);
}

void actSt10rElv(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(290) != 0) {
        scpSearchGobj(1527)->active = 0;
        scpSearchGobj(1528)->active = 0;
        gflagOff(290);
    } else {
        scpSearchGobj(1525)->active = 0;
        scpSearchGobj(1526)->active = 0;
    }
}

void actSt10rGateXL(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(218) == 0) {
        scpSearchGobj(1493)->active = 0;
    } else {
        scpSearchGobj(1492)->active = 0;
    }
}
#else
void actSt10rChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(304) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(383, 0, 0);
#else
        stage_SetAnimation(387, 0, 0);
#endif
        scpSearchGobj(1622)->active = 0;

        chain_mes[0].func = actSt10rChainMain;
        act->mail = chain_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(383, 0, -1);
#else
        stage_SetAnimation(387, 0, -1);
#endif
    }
}

void actSt10rSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSekizou(self, 305, 386, 0, 18, 0.0f, 327.0f, 4649.0f, -75.0f, 327.0f, 4649.0f);
#else
    scpSekizou(self, 305, 390, 0, 18, 0.0f, 327.0f, 4649.0f, -75.0f, 327.0f, 4649.0f);
#endif
}

void actSt10rEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(306) == 0) {
        ene_mes[0].func = actSt10rEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt10rEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(307) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);

    Generator_MaskOff(self);
}

void actSt10rEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(307) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);
}

void actSt10rElv(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(317) != 0) {
        scpSearchGobj(1633)->active = 0;
        scpSearchGobj(1634)->active = 0;
        gflagOff(317);
    } else {
        scpSearchGobj(1631)->active = 0;
        scpSearchGobj(1632)->active = 0;
    }
}

void actSt10rGateXL(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(243) == 0) {
        scpSearchGobj(1598)->active = 0;
    } else {
        scpSearchGobj(1597)->active = 0;
    }
}

void actSt10rWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    way_mes[0].func = actSt10rWayOnChk;
    act->mail = way_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt10rFloorSub(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(381, 1, 0);
#else
    stage_SetAnimation(385, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(381, 67, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(385, 67, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(381, 80, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(385, 80, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(381) == 0) {
#else
    while (stage_CheckAnimationFinish(385) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

static void actSt10rCageSub(GObj *volatile self)
{
    _ACTWait(30);

    while (cage10r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(cage10r->stream);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(384, 1, 0);
#else
    stage_SetAnimation(388, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(384) == 0) {
#else
    while (stage_CheckAnimationFinish(388) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    demoEnd = 1;
    _ACTWait(0);
}
#endif

void actSt10rGirlWay(volatile unsigned int self)
{
    long long buf[2];
    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
    _ACTWait(0);
}

void actSt10rExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_NTSC
    gflagOn(282);
    gflagOff(290);
#else
    gflagOn(309);
    gflagOff(317);
#endif

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        OnGirlEscortFlag();
        RequestStageChange(1, boyGObj, girlGObj, 2.0f, 8.0f);
    }
    RequestStageChange(1, boyGObj, 0, 2.0f, 8.0f);
}

void actSt10rChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = chain_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10rChainSwitch(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;
    act->mainMail = 0;
    chain_switch_mes[0].func = actSt10rChainMove;
    act->mail = chain_switch_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt10rChainMoveSub(GObj *volatile self)
{
    int se;

    _ACTWait(30);

    while (chain10r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(chain10r->stream);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(383, 1, 0);
#else
    stage_SetAnimation(387, 1, 0);
#endif

    se = soundSeDefPlay(1287, 0, 0, 1);

    _ACTWait(180);

    soundSeDefStop(se);

    demoEnd = 1;
#endif
    _ACTWait(0);
}

void actSt10rSekizoEvent(int x)
{
    volatile int local = x;
}

#ifdef VERSION_NTSC
void actSt10rEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    gflagOn(279);
    gflagOn(280);
}
#else
void actSt10rEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    gflagOn(306);
    gflagOn(307);
}

static void actSt10rWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(20, 1);

    way_onchk_mes[0].func = actSt10rWayOffChk;
    sub->mail = way_onchk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt10rWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(girlGObj, 0x6000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(20, 0);

    way_offchk_mes[0].func = actSt10rWayOnChk;
    sub->mail = way_offchk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt10rTowerResqueChk(GObj *volatile self)
{
    while (gflagChk(303) != 0 || gflagChk(302) == 0 || scpTriggerBall(self, boyGObj, 500.0f) == 0 ||
           (ForMotionViewer_GetCurrentMotion(boyGObj) != 84 &&
            ForMotionViewer_GetCurrentMotion(boyGObj) != 85)) {
        _ACTWait(1);
    }

    scpPlayStart(boyGObj);
    scpPlayPosSet(boyGObj, 135.0f, 321.0f, 2101.0f);
    scpPlayMot(boyGObj, 0);
    _ACTWait(120);
    scpPlayEnd(boyGObj);
}
#endif
