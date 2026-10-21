#include "st13b.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "jimaku.h"
#include "itou_boss.h"
#include "camera-root.h"
#include "fightSound.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include <libvu0.h>
#include "e3.h"
#include "typedef.h"
#include "main.h"
#include "script.h"

/* The functions stand in the order of the stage's source (aug6's TRFILE
   numbers them so). The ones defined inline are output at the end of the
   file, in the order of the declarations below, which gives this build's
   .text order; the others are output where they stand. */
inline void actSt13bSekizo(GObj *volatile self);
inline void actSt13bSekizo2(GObj *volatile self);
inline void actSt13bBossAfter(GObj *volatile self);
inline void actSt13bStoneGirl(GObj *volatile self);
inline void actSt13bExit(GObj *volatile self);
inline void actSt13bElev(GObj *volatile self);
inline void actSt13bDoor(GObj *volatile self);
inline void actBossTest(GObj *volatile self);
inline void actSt13bConte02Jimaku(GObj *volatile self);
inline void actSt13bSekizo2Event(int x);
inline void actSt13bMeetAgainChk(GObj *volatile self);
inline void actConte10a(GObj *volatile self);
inline void actSt13bBossChk(GObj *volatile self);
inline void actSt13bBossAfterChk(GObj *volatile self);
inline void actConte10c(GObj *volatile self);
inline void actSt13bExitChk(GObj *volatile self);
inline void actSt13bElevMain(GObj *volatile self);
inline void actSt13bElevSwitch(GObj *volatile self);
inline void actSt13bDoorMain(GObj *volatile self);
inline void actSt13bDoorSwitch(GObj *volatile self);
inline void actSt13bDoorUp(GObj *volatile self);

/* .sbss: the demo's own end flag and the pad actuator handle and volume byte
   actSt13bConte02 holds (this build has no conte-02 end flag and no door-up
   flag). */
static int demoEnd;

static int padAct; /* derived name */

static unsigned char padActVolume; /* derived name */

/* .data: actor mail packets. */
static ActMail floor_mes[2] = {{377}, {376}}; /* derived name */

static ActMail sekizo_mes[2] = {{377}, {376}}; /* derived name */

static ActMail sekizo2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail meetAgain_mes[2] = {{377}, {376}}; /* derived name */

static ActMail boss_mes[2] = {{377}, {376}}; /* derived name */

static ActMail bossAfter_mes[2] = {{377}, {376}}; /* derived name */

/* actSt13bExit's */
static ActMail exit_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elevMain_mes[2] = {{356, actSt13bElevSwitch}, {376}}; /* derived name */

static ActMail elev_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elevUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorMain_mes[2] = {{357, actSt13bDoorSwitch}, {376}}; /* derived name */

static ActMail door_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{377}, {376}}; /* derived name */

static float doorUpSubPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f}; /* derived name */

/* .sdata: the scene stream (actSt13bFloorChk, actSt13bConte02), the boss's
   stream handle, the lift's two handles, the statues' shake and volume, the
   lift's shake and volume. This build has no statue, reunion, sound or
   boss-death handle and no boss shake (no function of the demo addresses
   one). */
static SqEntry *st13b_adpcm = 0; /* derived name */

SqEntry *boss = 0;

SqEntry *st13b_up = 0;

SqEntry *st13b_down = 0;

int sekizo_13b = 0;

unsigned char sekizo_13b_vol = 0;

int st13b_yure = 0;

unsigned char st13b_yure_vol = 0;

void actSt13bFloor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(5) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        lt_switch_layout(51);

        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(21, 0, 0);
        stage_SetAnimation(28, 0, 0);
        stage_SetAnimation(29, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(35, 0, 235);
        stage_SetAnimation(36, 0, 0);

        floor_mes[0].func = actSt13bFloorChk;
        act->mail = floor_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(27, 0, -1);
        stage_SetAnimation(21, 0, -1);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
    }
}

void actSt13bFloorChk(GObj *volatile self)
{
    int v = 32;

    gflagOn(5);
    actCreateSubThread(actSt13bConte02, 21);
    actCreateSubThread(actSt13bConte02Jimaku, 21);

    demoEnd = 0;
    st13b_adpcm = 0;

    do {
        _ACTWait(1);
    } while (st13b_adpcm == 0);

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (demoEnd == 0) {
        v = 64;
    }

    if (st13b_adpcm != 0) {
        scpAdpcmFadeClose(st13b_adpcm, v);
    }

    RequestStageChange(4, boyGObj, 0, 0.025f, 2.0f);
}

void actSt13bConte02(GObj *volatile self)
{
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    stgmgrNextStagePreLoadForceStageSet(0);
    scpAdpcmPlayRequestFunc(14, &st13b_adpcm, 0, 1, 0);

    while (st13b_adpcm == 0) {
        _ACTWait(1);
    }

    scpFadeIn(8.0f);

    stgmgrNextStagePreLoadForceStageSet(exitData[(&stageData[stage_no])->ent[3]].nextStage);
    stgmgrNextStagePreLoadForceNoCancel(1);

    stage_SetAnimation(465, 1, 0);
    stage_SetAnimation(29, 1, 0);
    stage_SetAnimation(16, 1, 0);
    scpPlayMot((void *)boyGObj, 285);
    scpPlayMot(scpSearchGobj(2080), 1020);
    scpSearchGobj(2080)->active = 1;
    scpPlayMot(scpSearchGobj(2081), 1042);
    scpSearchGobj(2081)->active = 1;
    scpPlayMot(scpSearchGobj(2082), 1066);
    scpSearchGobj(2082)->active = 1;

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 2.7f);

    AdpcmPlay(st13b_adpcm->stream);

    while (stage_ContinueAnimation(465, 466) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(22, 1, 0);
    stage_SetAnimation(17, 1, 0);
    scpPlayMot((void *)boyGObj, 286);
    scpPlayMot(scpSearchGobj(2080), 1021);
    scpPlayMot(scpSearchGobj(2081), 1043);
    scpPlayMot(scpSearchGobj(2082), 1067);

    while (stage_ContinueAnimation(466, 467) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(23, 1, 0);

    while (stage_ContinueAnimation(467, 468) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(24, 1, 0);
    stage_SetAnimation(18, 1, 0);
    scpPlayMot((void *)boyGObj, 287);
    scpPlayMot(scpSearchGobj(2080), 1022);
    scpPlayMot(scpSearchGobj(2081), 1044);
    scpPlayMot(scpSearchGobj(2082), 1068);

    while (stage_ContinueAnimation(468, 469) == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    stage_SetAnimation(25, 1, 0);
    scpPlayMot((void *)boyGObj, 288);
    scpPlayMot(scpSearchGobj(2081), 1045);

    while (stage_ContinueAnimation(469, 470) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(26, 1, 0);
    scpPlayMot((void *)boyGObj, 289);
    scpPlayMot(scpSearchGobj(2080), 1021);
    scpPlayMot(scpSearchGobj(2081), 1043);
    scpPlayMot(scpSearchGobj(2082), 1067);

    while (stage_ContinueAnimation(470, 471) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(19, 1, 0);
    scpPlayMot(scpSearchGobj(2080), 1023);
    scpPlayMot(scpSearchGobj(2081), 1046);
    scpPlayMot(scpSearchGobj(2082), 1069);

    while (stage_ContinueAnimation(471, 472) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 290);
    scpSearchGobj(2080)->active = 0;
    scpSearchGobj(2081)->active = 0;
    scpSearchGobj(2082)->active = 0;

    stage_SetAnimation(29, 0, 0);

    while (stage_CheckAnimationFrame(472, 200, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpFadeOut(3.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }

    stage_SetAnimation(472, -1, -2);
    scpFadeIn(3.0f);
    stage_SetAnimation(473, 1, 0);

    while (stage_ContinueAnimation(473, 474) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(21, 1, 0);
    scpPlayMot((void *)boyGObj, 291);
    _ACTWait(60);

    padAct = iosPadActRequest(boyPad, 9);
    padActVolume = 128;
    iosPadActVolumeSet(padAct, 128);

    while (stage_ContinueAnimation(474, 475) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(475, 476) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(20, 1, 0);

    while (stage_ContinueAnimation(476, 477) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 292);
    _ACTWait(130);

    stage_SetAnimation(27, 1, 0);

    while (stage_ContinueAnimation(477, 478) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(478, 479) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(padAct);
    scpPlayMot((void *)boyGObj, 293);

    while (stage_ContinueAnimation(479, 480) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 291);

    while (stage_ContinueAnimation(480, 481) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 295);

    while (stage_ContinueAnimation(481, 482) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 296);
    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(482, 483) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 297);

    _ACTWait(30);
    iosPadActRequest(boyPad, 15);
    _ACTWait(30);
    iosPadActRequest(boyPad, 17);
    _ACTWait(15);
    iosPadActRequest(boyPad, 17);
    _ACTWait(5);
    iosPadActRequest(boyPad, 16);
    _ACTWait(15);
    iosPadActRequest(boyPad, 17);

    while (stage_ContinueAnimation(483, 484) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 298);

    while (stage_ContinueAnimation(484, 485) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 299);

    while (stage_ContinueAnimation(485, 486) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 300);

    while (stage_CheckAnimationFrame(486, 150, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    demoEnd = 1;
}

inline void actSt13bConte02Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 1800:
            jimaku_msg.sub.block = 1;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 2500.0f);
}

inline void actSt13bSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(10) == 0) {
        stage_SetAnimation(28, 0, 0);

        sekizo_mes[0].func = actSt13bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(28, 0, -1);
    }
}

void actSt13bSekizoChk(GObj *volatile self)
{
    float dir[4];

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 83) {
        _ACTWait(1);
    }

    scpSekizouCheckPoint();
    scpAdpcmPlayRequestFunc(21, 0, 1, 1, 1);
    scpBoyControlReadDisable = 1;
    lt_switch_layout(51);
    gflagOn(10);
    _ACTWait(60);

    stage_SetAnimation(28, 1, 0);

    sekizo_13b = iosPadActRequest(boyPad, 9);
    sekizo_13b_vol = 128;
    iosPadActVolumeSet(sekizo_13b, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet((void *)boyGObj, 3085.0f, -1338.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
    scpPlayMot((void *)boyGObj, 253);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot((void *)boyGObj, 0);
    scpPlayEnd(boyGObj);

    while (stage_CheckAnimationFinish(28) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(sekizo_13b);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

inline void actSt13bSekizo2Event(int x)
{
    volatile int local = x;
}

inline void actSt13bSekizo2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(11) == 0) {
        stage_SetAnimation(29, 0, 0);

        sekizo2_mes[0].func = actSt13bSekizo2Chk;
        act->mail = sekizo2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(29, 0, -1);
    }
}

void actSt13bSekizo2Chk(GObj *volatile self)
{
    float dir[4];

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 83) {
        _ACTWait(1);
    }

    scpSekizouCheckPoint();
    scpAdpcmPlayRequestFunc(21, 0, 1, 1, 1);
    scpBoyControlReadDisable = 1;
    lt_switch_layout(51);
    gflagOn(11);
    _ACTWait(60);

    stage_SetAnimation(29, 1, 0);

    sekizo_13b = iosPadActRequest(boyPad, 9);
    sekizo_13b_vol = 128;
    iosPadActVolumeSet(sekizo_13b, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet((void *)boyGObj, -1618.0f, 527.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
    scpPlayMot((void *)boyGObj, 253);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot((void *)boyGObj, 0);
    scpPlayEnd(boyGObj);

    while (stage_CheckAnimationFinish(29) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(sekizo_13b);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt13bMeetAgain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(12) == 0) {
        stage_SetAnimation(27, 0, -1);
        stage_SetAnimation(21, 0, 0);
        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);

        meetAgain_mes[0].func = actSt13bMeetAgainChk;
        act->mail = meetAgain_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(27, 0, -1);
        stage_SetAnimation(21, 0, 0);
        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
    }
}

inline void actSt13bMeetAgainChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(12);
    scpBoyControlReadDisable = 1;
    scpAdpcmPlayRequestFunc(37, 0, 1, 1, 1);
    actCreateSubThread(actConte10a, 21);
}

inline void actConte10a(GObj *volatile self)
{
    lt_switch_layout(51);
    scpPlayStart(boyGObj);
    stage_SetAnimation(636, 1, 0);

    while (stage_ContinueAnimation(636, 637) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 402);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(637) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt13bBoss(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    if (gflagChk(13) == 0) {
        scpSearchGobj(2139)->active = 0;
        scpSearchGobj(2140)->active = 0;
        scpSleepEnemyAll();

        boss_mes[0].func = actSt13bBossChk;
        act->mail = boss_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else if (gflagChk(14) == 0) {
        CameraSetCameraSet(5);
        scpAdpcmPlayRequestFunc(39, 0, 1, 0, 1);
    }
}

inline void actSt13bBossChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 300.0f) == 0 || (GOBJ_ACT(boyGObj)->pad.trg & 8) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    gflagOn(13);
    scpBoyControlReadDisable = 1;

    scpAdpcmPlayRequestFunc(38, &boss, 1, 0, 1);

    while (boss == 0) {
        _ACTWait(1);
    }

    actCreateSubThread(actConte10b, 21);
    CameraSetCameraSet(5);
}

void actConte10b(GObj *volatile self)
{
    scpPlayStart(boyGObj);
    stage_SetAnimation(638, 1, 0);
    scpPlayMot(boyGObj, 403);
    scpSearchGobj(2139)->active = 1;
    scpSearchGobj(2140)->active = 1;
    scpPlayStart(scpSearchGobj(2139));
    scpPlayStart(scpSearchGobj(2140));
    scpPlayMot(scpSearchGobj(2139), 999);
    scpPlayMot(scpSearchGobj(2140), 1000);

    while (stage_CheckAnimationFrame(638, 25, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(31, 1, 0);

    while (stage_CheckAnimationFrame(638, 130, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(33, 1, 0);

    while (stage_ContinueAnimation(638, 639) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(32, 1, 0);
    stage_SetAnimation(34, 1, 0);
    scpPlayMot(scpSearchGobj(2140), 1001);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(639) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(scpSearchGobj(2139), 821);
    scpPlayMot(scpSearchGobj(2140), 821);
    scpPlayEnd(boyGObj);
    scpPlayEnd(scpSearchGobj(2139));
    scpPlayEnd(scpSearchGobj(2140));
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    scpWakeupEnemyAll();
}

inline void actSt13bStoneGirl(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (current_stage_no == 46) {
        scpPlayMot(scpSearchGobj(2138), 789);
        scpSearchGobj(2138)->active = 1;
    }
}

inline void actSt13bBossAfter(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(14) == 0) {
        stage_SetAnimation(30, 0, 0);

        bossAfter_mes[0].func = actSt13bBossAfterChk;
        act->mail = bossAfter_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(30, 0, -1);
    }
}

inline void actSt13bBossAfterChk(GObj *volatile self)
{
    while (actEnemyFlagCheckDead(scpSearchGobj(2139)) == 0 ||
           actEnemyFlagCheckDead(scpSearchGobj(2140)) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    gflagOn(14);

    if (boss != 0) {
        soundDataClose(boss);
    }

    _ACTWait(120);

    CameraSetCameraSet(4);
    scpAdpcmPlayRequestFunc(40, 0, 1, 1, 1);
    actCreateSubThread(actConte10c, 21);
}

inline void actConte10c(GObj *volatile self)
{
    stage_SetAnimation(640, 1, 0);
    stage_SetAnimation(30, 1, 0);
    scpPlayMot(boyGObj, 404);

    while (stage_ContinueAnimation(640, 641) == 0) {
        _ACTWait(1);
    }

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(641) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

inline void actSt13bExit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    exit_mes[0].func = actSt13bExitChk;
    act->mail = exit_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt13bExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 || gflagChk(282) != 0) {
        _ACTWait(1);
    }

    RequestStageChange(3, boyGObj, 0, 2.0f, 4.0f);
}

inline void actSt13bElev(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    elev_mes[0].func = actSt13bElevMain;
    act->mail = elev_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt13bElevMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = elevMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

inline void actSt13bElevSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    elevSwitch_mes[0].func = actSt13bElevDown;
    sub->mail = elevSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt13bElevDown(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(15);
    scpAdpcmPlayRequestFunc(72, &st13b_down, 0, 1, 1);

    while (st13b_down == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(35, 1, 235);

    while (stage_CheckAnimationFrame(35, 321, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(35, 350, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13b_yure = iosPadActRequest(boyPad, 9);
    st13b_yure_vol = 128;
    iosPadActVolumeSet(st13b_yure, 128);

    while (stage_CheckAnimationFrame(35, 450, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st13b_yure);

    RequestStageChange(3, boyGObj, 0, 2.0f, 4.0f);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt13bElevUp(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(282) != 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(35, 0, 235);
        _ACTWait(10);
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        stage_SetAnimation(35, 0, 0);
        elevUp_mes[0].func = actSt13bElevUpChk;
        act->mail = elevUp_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(35, 0, 235);
    }
}

void actSt13bElevUpChk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(71, &st13b_up, 1, 1, 1);

    while (st13b_up == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    stage_SetAnimation(35, 1, 0);
    st13b_yure = iosPadActRequest(boyPad, 9);
    st13b_yure_vol = 128;
    iosPadActVolumeSet(st13b_yure, 128);
    while (stage_CheckAnimationFrame(35, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    iosPadActStop(st13b_yure);
    while (stage_CheckAnimationFrame(35, 234, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    gflagOff(282);
}

inline void actBossTest(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    stage_SetAnimation(27, 0, -1);
    stage_SetAnimation(21, 0, 0);
    stage_SetAnimation(30, 0, 0);
    stage_SetAnimation(31, 0, 0);
    stage_SetAnimation(33, 0, 0);
}

inline void actSt13bDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(16) == 0) {
        stage_SetAnimation(36, 0, 0);

        door_mes[0].func = actSt13bDoorMain;
        act->mail = door_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(36, 0, -1);
    }
}

inline void actSt13bDoorMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;
    sub->mainMail = doorMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

inline void actSt13bDoorSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    doorSwitch_mes[0].func = actSt13bDoorUp;
    sub->mail = doorSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt13bDoorUp(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(16);

    _ACTWait(60);

    stage_SetAnimation(36, 1, 0);

    soundSeDefPlay(1171, 0, doorUpSubPos, 1);

    _ACTWait(30);

    soundSeDefPlay(1172, 0, doorUpSubPos, 1);

    while (stage_CheckAnimationFinish(36) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
