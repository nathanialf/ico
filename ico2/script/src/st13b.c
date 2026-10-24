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

#ifdef VERSION_AUG6
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
   the conte-02 cutscene holds. */
static int demoEnd; /* derived name */
#else
#ifndef VERSION_NTSC
#ifdef VERSION_JUN26
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
#else
static void actSt13bDoorUpSub(GObj *volatile self);
static void actSt13bElev2CharaChk(GObj *volatile self);
static void actSt13bElevUpSub(GObj *volatile self);
#endif

/* .sbss: the demo's own end flag, the conte-02 end flag, the pad actuator
   handle and volume byte the door-up subthread holds, and the flag
   actSt13bDoorUpSub raises when the door is up. */
static int demoEnd;
#endif

#ifndef VERSION_JUN26
static int conte02End; /* derived name */
#endif
#endif

static int padAct; /* derived name */

static unsigned char padActVolume; /* derived name */

#ifdef VERSION_NTSC
/* .data: actor mail packets. */
static ActMail floor_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sekizo2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail meetAgain_mes[2] = {{397}, {396}}; /* derived name */

static ActMail boss_mes[2] = {{397}, {396}}; /* derived name */

static ActMail bossAfter_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elevMain_mes[2] = {{376, actSt13bElevSwitch}, {396}}; /* derived name */

static ActMail elev_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elevUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorMain_mes[2] = {{377, actSt13bDoorSwitch}, {396}}; /* derived name */

static ActMail door_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{397}, {396}}; /* derived name */
#else
#ifdef VERSION_AUG6
/* .data: actor mail packets. */
static ActMail floor_mes[2] = {{393}, {392}}; /* derived name */

static ActMail sekizo_mes[2] = {{393}, {392}}; /* derived name */

static ActMail sekizo2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail meetAgain_mes[2] = {{393}, {392}}; /* derived name */

static ActMail boss_mes[2] = {{393}, {392}}; /* derived name */

static ActMail bossAfter_mes[2] = {{393}, {392}}; /* derived name */

static ActMail exit_mes[2] = {{393}, {392}}; /* derived name */

static ActMail elevMain_mes[2] = {{372, actSt13bElevSwitch}, {392}}; /* derived name */

static ActMail elev_mes[2] = {{393}, {392}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail elevUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorMain_mes[2] = {{373, actSt13bDoorSwitch}, {392}}; /* derived name */

static ActMail door_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_JUN26
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
#else
static int doorUpDone; /* derived name */

/* .data: actor mail packets. */
static ActMail floor_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail meetAgain_mes[2] = {{430}, {429}}; /* derived name */

static ActMail boss_mes[2] = {{430}, {429}}; /* derived name */

static ActMail bossAfter_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elevMain_mes[2] = {{406, actSt13bElevSwitch}, {429}}; /* derived name */

static ActMail elev_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elevUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorMain_mes[2] = {{407, actSt13bDoorSwitch}, {429}}; /* derived name */

static ActMail door_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif
#endif

static float doorUpSubPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f}; /* derived name */

#ifdef VERSION_JUN26
/* .sdata: the scene stream (actSt13bFloorChk, actSt13bConte02), the boss's
   stream handle, the lift's two handles, the statues' shake and volume, the
   lift's shake and volume. This build has no statue, reunion, sound or
   boss-death handle and no boss shake (no function of the demo addresses
   one). */
static SqEntry *st13b_adpcm = 0; /* derived name */

SqEntry *boss = 0;
#else
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
static ActMail elev2Chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elev2Chk2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elev2Chara_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elev2CharaChk_mes[2] = {{430}, {429}}; /* derived name */
#endif

/* .sdata: the scene stream, the stream handles and shakes, then a further
   shake and volume. */
static SqEntry *st13b_adpcm = 0; /* derived name */

SqEntry *sekizo13b = 0;

SqEntry *sekizo13b2 = 0;

SqEntry *meets_again = 0;

SqEntry *boss = 0;

SqEntry *sd = 0;

SqEntry *boss_dead = 0;
#endif

SqEntry *st13b_up = 0;

SqEntry *st13b_down = 0;

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
int sekizo_13b = 0;

unsigned char sekizo_13b_vol = 0;
#else
SqEntry *sekizo_13b = 0;

SqEntry *sekizo_13b_vol = 0;
#endif

int st13b_yure = 0;

unsigned char st13b_yure_vol = 0;

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
static int st13b_boss_yure = 0; /* derived name */

static unsigned char st13b_boss_yure_vol = 0; /* derived name */
#endif

void actSt13bFloor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(5) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;

        stage_SetAnimation(29, 0, 0);
        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
        stage_SetAnimation(39, 0, 235);
        stage_SetAnimation(40, 0, 0);
#else
#ifdef VERSION_JUN26
        lt_switch_layout(51);

        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(21, 0, 0);
        stage_SetAnimation(28, 0, 0);
        stage_SetAnimation(29, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(35, 0, 235);
        stage_SetAnimation(36, 0, 0);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        lt_switch_layout(52);
#else
        lt_switch_layout(55);
#endif
        scpBoyControlReadDisable = 1;

        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
        stage_SetAnimation(40, 0, 235);
        stage_SetAnimation(43, 0, 0);
        stage_SetAnimation(35, 0, 0);
#endif
#endif

        floor_mes[0].func = actSt13bFloorChk;
        act->mail = floor_mes;
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);
    } else {
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, -1);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(27, 0, -1);
        stage_SetAnimation(21, 0, -1);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, -1);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
#endif
#endif
    }
}

void actSt13bFloorChk(GObj *volatile self)
{
    int v = 32;

    gflagOn(5);
    actCreateSubThread(actSt13bConte02, 21);
    actCreateSubThread(actSt13bConte02Jimaku, 21);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    demoEnd = 0;
#else
    conte02End = 0;
#endif
    st13b_adpcm = 0;

    do {
        _ACTWait(1);
    } while (st13b_adpcm == 0);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
#else
    while (conte02End == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
#endif
        _ACTWait(1);
    }

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    if (demoEnd == 0) {
#else
    if (conte02End == 0) {
#endif
        v = 64;
    }

    if (st13b_adpcm != 0) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        scpAdpcmFadeClose(st13b_adpcm, v);
#else
        scpAdpcmFadeCloseFunc(&st13b_adpcm, v);
#endif
    }

    RequestStageChange(4, boyGObj, 0, 0.025f, 2.0f);
}

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
void actSt13bConte02(GObj *volatile self)
{
#ifdef VERSION_JUN26
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    stgmgrNextStagePreLoadForceStageSet(0);
    scpAdpcmPlayRequestFunc(14, &st13b_adpcm, 0, 1, 0);
#else
    scpPlayStart(boyGObj);
    stgmgrNextStagePreLoadForceStageSet(0);
    scpAdpcmPlayRequestFunc(11, &st13b_adpcm, 0, 1, 0);
#endif

    while (st13b_adpcm == 0) {
        _ACTWait(1);
    }

    scpFadeIn(8.0f);

    stgmgrNextStagePreLoadForceStageSet(exitData[(&stageData[stage_no])->ent[3]].nextStage);
    stgmgrNextStagePreLoadForceNoCancel(1);

#ifdef VERSION_JUN26
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
#else
    stage_SetAnimation(514, 1, 0);
    scpPlayMot((void *)boyGObj, 276);
    scpPlayMot(scpSearchGobj(2172), 942);
    scpSearchGobj(2172)->active = 1;
    scpPlayMot(scpSearchGobj(2173), 964);
    scpSearchGobj(2173)->active = 1;
    scpPlayMot(scpSearchGobj(2174), 988);
    scpSearchGobj(2174)->active = 1;
    _ACTWait(1);

    stage_SetAnimation(33, 1, 0);
    stage_SetAnimation(20, 1, 0);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 0.15);
#endif

    AdpcmPlay(st13b_adpcm->stream);

#ifdef VERSION_JUN26
    while (stage_ContinueAnimation(465, 466) == 0) {
#else
    while (stage_ContinueAnimation(514, 515) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(22, 1, 0);
    stage_SetAnimation(17, 1, 0);
    scpPlayMot((void *)boyGObj, 286);
    scpPlayMot(scpSearchGobj(2080), 1021);
    scpPlayMot(scpSearchGobj(2081), 1043);
    scpPlayMot(scpSearchGobj(2082), 1067);

    while (stage_ContinueAnimation(466, 467) == 0) {
#else
    scpPlayMot((void *)boyGObj, 277);
    scpPlayMot(scpSearchGobj(2172), 943);
    scpPlayMot(scpSearchGobj(2173), 965);
    scpPlayMot(scpSearchGobj(2174), 989);
    _ACTWait(1);

    stage_SetAnimation(26, 1, 0);
    stage_SetAnimation(21, 1, 0);

    while (stage_ContinueAnimation(515, 516) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(23, 1, 0);

    while (stage_ContinueAnimation(467, 468) == 0) {
#else
    _ACTWait(1);
    stage_SetAnimation(27, 1, 0);

    while (stage_ContinueAnimation(516, 517) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(24, 1, 0);
    stage_SetAnimation(18, 1, 0);
    scpPlayMot((void *)boyGObj, 287);
    scpPlayMot(scpSearchGobj(2080), 1022);
    scpPlayMot(scpSearchGobj(2081), 1044);
    scpPlayMot(scpSearchGobj(2082), 1068);

    while (stage_ContinueAnimation(468, 469) == 0) {
#else
    scpPlayMot((void *)boyGObj, 278);
    scpPlayMot(scpSearchGobj(2172), 944);
    scpPlayMot(scpSearchGobj(2173), 966);
    scpPlayMot(scpSearchGobj(2174), 990);
    _ACTWait(1);

    stage_SetAnimation(28, 1, 0);
    stage_SetAnimation(22, 1, 0);

    while (stage_ContinueAnimation(517, 518) == 0) {
#endif
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

#ifdef VERSION_JUN26
    stage_SetAnimation(25, 1, 0);
    scpPlayMot((void *)boyGObj, 288);
    scpPlayMot(scpSearchGobj(2081), 1045);

    while (stage_ContinueAnimation(469, 470) == 0) {
#else
    scpPlayMot((void *)boyGObj, 279);
    scpPlayMot(scpSearchGobj(2173), 967);
    _ACTWait(1);

    stage_SetAnimation(29, 1, 0);

    while (stage_ContinueAnimation(518, 519) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(26, 1, 0);
    scpPlayMot((void *)boyGObj, 289);
    scpPlayMot(scpSearchGobj(2080), 1021);
    scpPlayMot(scpSearchGobj(2081), 1043);
    scpPlayMot(scpSearchGobj(2082), 1067);

    while (stage_ContinueAnimation(470, 471) == 0) {
#else
    scpPlayMot((void *)boyGObj, 280);
    scpPlayMot(scpSearchGobj(2172), 943);
    scpPlayMot(scpSearchGobj(2173), 965);
    scpPlayMot(scpSearchGobj(2174), 989);
    _ACTWait(1);

    stage_SetAnimation(30, 1, 0);

    while (stage_ContinueAnimation(519, 520) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(19, 1, 0);
    scpPlayMot(scpSearchGobj(2080), 1023);
    scpPlayMot(scpSearchGobj(2081), 1046);
    scpPlayMot(scpSearchGobj(2082), 1069);

    while (stage_ContinueAnimation(471, 472) == 0) {
#else
    scpPlayMot(scpSearchGobj(2172), 945);
    scpPlayMot(scpSearchGobj(2173), 968);
    scpPlayMot(scpSearchGobj(2174), 991);
    _ACTWait(1);

    stage_SetAnimation(23, 1, 0);

    while (stage_ContinueAnimation(520, 521) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 290);
    scpSearchGobj(2080)->active = 0;
    scpSearchGobj(2081)->active = 0;
    scpSearchGobj(2082)->active = 0;

    stage_SetAnimation(29, 0, 0);

    while (stage_CheckAnimationFrame(472, 200, 0) == 0) {
#else
    scpPlayMot((void *)boyGObj, 281);
    scpSearchGobj(2172)->active = 0;
    scpSearchGobj(2173)->active = 0;
    scpSearchGobj(2174)->active = 0;

    stage_SetAnimation(33, 0, 0);

    while (stage_CheckAnimationFrame(521, 200, 0) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    scpFadeOut(3.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(472, -1, -2);
    scpFadeIn(3.0f);
    stage_SetAnimation(473, 1, 0);

    while (stage_ContinueAnimation(473, 474) == 0) {
#else
    stage_SetAnimation(521, -1, -2);
    scpFadeIn(3.0f);
    stage_SetAnimation(522, 1, 0);

    while (stage_ContinueAnimation(522, 523) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(21, 1, 0);
    scpPlayMot((void *)boyGObj, 291);
#else
    scpPlayMot((void *)boyGObj, 282);
    _ACTWait(1);

    stage_SetAnimation(25, 1, 0);
#endif
    _ACTWait(60);

    padAct = iosPadActRequest(boyPad, 9);
    padActVolume = 128;
    iosPadActVolumeSet(padAct, 128);

#ifdef VERSION_JUN26
    while (stage_ContinueAnimation(474, 475) == 0) {
#else
    while (stage_ContinueAnimation(523, 524) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    while (stage_ContinueAnimation(475, 476) == 0) {
#else
    while (stage_ContinueAnimation(524, 525) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(20, 1, 0);

    while (stage_ContinueAnimation(476, 477) == 0) {
#else
    stage_SetAnimation(24, 1, 0);

    while (stage_ContinueAnimation(525, 526) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 292);
    _ACTWait(130);

    stage_SetAnimation(27, 1, 0);

    while (stage_ContinueAnimation(477, 478) == 0) {
#else
    scpPlayMot((void *)boyGObj, 283);
    _ACTWait(130);

    stage_SetAnimation(31, 1, 0);

    while (stage_ContinueAnimation(526, 527) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    while (stage_ContinueAnimation(478, 479) == 0) {
#else
    while (stage_ContinueAnimation(527, 528) == 0) {
#endif
        _ACTWait(1);
    }

    iosPadActStop(padAct);
#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 293);

    while (stage_ContinueAnimation(479, 480) == 0) {
#else
    scpPlayMot((void *)boyGObj, 284);

    while (stage_ContinueAnimation(528, 529) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 291);

    while (stage_ContinueAnimation(480, 481) == 0) {
#else
    scpPlayMot((void *)boyGObj, 282);

    while (stage_ContinueAnimation(529, 530) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 295);

    while (stage_ContinueAnimation(481, 482) == 0) {
#else
    scpPlayMot((void *)boyGObj, 286);
    while (stage_ContinueAnimation(530, 531) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 296);
    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(482, 483) == 0) {
#else
    scpPlayMot((void *)boyGObj, 287);
    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(531, 532) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 297);
#else
    scpPlayMot((void *)boyGObj, 288);
#endif

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

#ifdef VERSION_JUN26
    while (stage_ContinueAnimation(483, 484) == 0) {
#else
    while (stage_ContinueAnimation(532, 533) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 298);

    while (stage_ContinueAnimation(484, 485) == 0) {
#else
    scpPlayMot((void *)boyGObj, 289);

    while (stage_ContinueAnimation(533, 534) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 299);

    while (stage_ContinueAnimation(485, 486) == 0) {
#else
    scpPlayMot((void *)boyGObj, 290);

    while (stage_ContinueAnimation(534, 535) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 300);

    while (stage_CheckAnimationFrame(486, 150, 0) == 0) {
#else
    scpPlayMot((void *)boyGObj, 291);

    while (stage_CheckAnimationFrame(535, 150, 0) == 0) {
#endif
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
#else
#ifdef VERSION_NTSC
void actSt13bConte02(GObj *volatile self)
{
    scpPlayStart(boyGObj);
    stgmgrNextStagePreLoadForceStageSet(0);
    scpAdpcmPlayRequestFunc(11, &st13b_adpcm, 0, 1, 0);

    while (st13b_adpcm == 0) {
        _ACTWait(1);
    }

    scpFadeIn(8.0f);

    stgmgrNextStagePreLoadForceStageSet(exitData[(&stageData[stage_no])->ent[3]].nextStage);
    stgmgrNextStagePreLoadForceNoCancel(1);

    stage_SetAnimation(515, 1, 0);
    scpPlayMot((void *)boyGObj, 276);
    scpPlayMot(scpSearchGobj(2197), 940);
    scpSearchGobj(2197)->active = 1;
    scpPlayMot(scpSearchGobj(2198), 962);
    scpSearchGobj(2198)->active = 1;
    scpPlayMot(scpSearchGobj(2199), 986);
    scpSearchGobj(2199)->active = 1;
    _ACTWait(1);

    stage_SetAnimation(33, 1, 0);
    stage_SetAnimation(20, 1, 0);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 0.15);

    AdpcmPlay(st13b_adpcm->stream);

    while (stage_ContinueAnimation(515, 516) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 277);
    scpPlayMot(scpSearchGobj(2197), 941);
    scpPlayMot(scpSearchGobj(2198), 963);
    scpPlayMot(scpSearchGobj(2199), 987);
    _ACTWait(1);

    stage_SetAnimation(26, 1, 0);
    stage_SetAnimation(21, 1, 0);

    while (stage_ContinueAnimation(516, 517) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    stage_SetAnimation(27, 1, 0);

    while (stage_ContinueAnimation(517, 518) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 278);
    scpPlayMot(scpSearchGobj(2197), 942);
    scpPlayMot(scpSearchGobj(2198), 964);
    scpPlayMot(scpSearchGobj(2199), 988);
    _ACTWait(1);

    stage_SetAnimation(28, 1, 0);
    stage_SetAnimation(22, 1, 0);

    while (stage_ContinueAnimation(518, 519) == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    scpPlayMot((void *)boyGObj, 279);
    scpPlayMot(scpSearchGobj(2198), 965);
    _ACTWait(1);

    stage_SetAnimation(29, 1, 0);

    while (stage_ContinueAnimation(519, 520) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 280);
    scpPlayMot(scpSearchGobj(2197), 941);
    scpPlayMot(scpSearchGobj(2198), 963);
    scpPlayMot(scpSearchGobj(2199), 987);
    _ACTWait(1);

    stage_SetAnimation(30, 1, 0);

    while (stage_ContinueAnimation(520, 521) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2197), 943);
    scpPlayMot(scpSearchGobj(2198), 966);
    scpPlayMot(scpSearchGobj(2199), 989);
    _ACTWait(1);

    stage_SetAnimation(23, 1, 0);

    while (stage_ContinueAnimation(521, 522) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 281);
    scpSearchGobj(2197)->active = 0;
    scpSearchGobj(2198)->active = 0;
    scpSearchGobj(2199)->active = 0;

    stage_SetAnimation(33, 0, 0);

    while (stage_CheckAnimationFrame(522, 200, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpFadeOut(3.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }

    stage_SetAnimation(522, -1, -2);
    scpFadeIn(3.0f);
    stage_SetAnimation(523, 1, 0);

    while (stage_ContinueAnimation(523, 524) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 282);
    _ACTWait(1);

    stage_SetAnimation(25, 1, 0);
    _ACTWait(60);

    padAct = iosPadActRequest(boyPad, 9);
    padActVolume = 128;
    iosPadActVolumeSet(padAct, 128);

    while (stage_ContinueAnimation(524, 525) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(525, 526) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(24, 1, 0);

    while (stage_ContinueAnimation(526, 527) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 283);
    _ACTWait(130);

    stage_SetAnimation(31, 1, 0);

    while (stage_ContinueAnimation(527, 528) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(528, 529) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(padAct);
    scpPlayMot((void *)boyGObj, 284);

    while (stage_ContinueAnimation(529, 530) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 282);

    while (stage_ContinueAnimation(530, 531) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 286);
    while (stage_ContinueAnimation(531, 532) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 287);
    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(532, 533) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 288);

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

    while (stage_ContinueAnimation(533, 534) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 289);

    while (stage_ContinueAnimation(534, 535) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 290);

    while (stage_ContinueAnimation(535, 536) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 291);

    while (stage_CheckAnimationFrame(536, 150, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    conte02End = 1;
}

void actSt13bSekizoChk(GObj *volatile self)
{
    float dir[4];

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 75) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpAdpcmPlayRequestFunc(18, &sekizo13b, 1, 1, 1);

    while (sekizo13b == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(32, 1, 0);

    sekizo_13b = iosPadActRequest(boyPad, 9);
    sekizo_13b_vol = 128;
    iosPadActVolumeSet(sekizo_13b, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet((void *)boyGObj, 3085.0f, -1338.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
    scpSekizouCheckPoint();
    scpPlayMot((void *)boyGObj, 246);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot((void *)boyGObj, 0);
    scpPlayEnd(boyGObj);
    gflagOn(10);

    while (stage_CheckAnimationFrame(32, 151, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(sekizo_13b);

    while (stage_CheckAnimationFinish(32) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt13bSekizo2Chk(GObj *volatile self)
{
    float dir[4];

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 75) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpAdpcmPlayRequestFunc(18, &sekizo13b2, 1, 1, 1);

    while (sekizo13b2 == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(33, 1, 0);

    sekizo_13b = iosPadActRequest(boyPad, 9);
    sekizo_13b_vol = 128;
    iosPadActVolumeSet(sekizo_13b, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet((void *)boyGObj, -1563.0f, 527.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
    scpSekizouCheckPoint();
    scpPlayMot((void *)boyGObj, 246);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot((void *)boyGObj, 0);
    scpPlayEnd(boyGObj);
    gflagOn(11);

    while (stage_CheckAnimationFrame(33, 151, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(sekizo_13b);

    while (stage_CheckAnimationFinish(33) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt13bMeetAgain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(12) == 0) {
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);

        meetAgain_mes[0].func = actSt13bMeetAgainChk;
        act->mail = meetAgain_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
    }
}
#else
void actSt13bConte02(GObj *volatile self)
{
    scpPlayStart(boyGObj);
    stgmgrNextStagePreLoadForceStageSet(0);
    scpAdpcmPlayRequestFunc(11, &st13b_adpcm, 0, 1, 0);

    while (st13b_adpcm == 0) {
        _ACTWait(1);
    }

    scpFadeIn(8.0f);

    stgmgrNextStagePreLoadForceStageSet(exitData[(&stageData[stage_no])->ent[3]].nextStage);
    stgmgrNextStagePreLoadForceNoCancel(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(582, 1, 0);
#else
    stage_SetAnimation(586, 1, 0);
#endif
    scpPlayMot((void *)boyGObj, 282);
    scpPlayMot(scpSearchGobj(2403), 1001);
    scpSearchGobj(2403)->active = 1;
    scpPlayMot(scpSearchGobj(2404), 1023);
    scpSearchGobj(2404)->active = 1;
    scpPlayMot(scpSearchGobj(2405), 1047);
    scpSearchGobj(2405)->active = 1;
    _ACTWait(1);

    stage_SetAnimation(34, 1, 0);
    stage_SetAnimation(21, 1, 0);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 0.15);

#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
    if (systemStatus[0] != 0) {
        _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 1.0);
    }

#endif
    AdpcmPlay(st13b_adpcm->stream);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(582, 583) == 0) {
#else
    while (stage_ContinueAnimation(586, 587) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 283);
    scpPlayMot(scpSearchGobj(2403), 1002);
    scpPlayMot(scpSearchGobj(2404), 1024);
    scpPlayMot(scpSearchGobj(2405), 1048);
    _ACTWait(1);

    stage_SetAnimation(27, 1, 0);
    stage_SetAnimation(22, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(583, 584) == 0) {
#else
    while (stage_ContinueAnimation(587, 588) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    stage_SetAnimation(28, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(584, 585) == 0) {
#else
    while (stage_ContinueAnimation(588, 589) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 284);
    scpPlayMot(scpSearchGobj(2403), 1003);
    scpPlayMot(scpSearchGobj(2404), 1025);
    scpPlayMot(scpSearchGobj(2405), 1049);
    _ACTWait(1);

    stage_SetAnimation(29, 1, 0);
    stage_SetAnimation(23, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(585, 586) == 0) {
#else
    while (stage_ContinueAnimation(589, 590) == 0) {
#endif
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    scpPlayMot((void *)boyGObj, 285);
    scpPlayMot(scpSearchGobj(2404), 1026);
    _ACTWait(1);

    stage_SetAnimation(30, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(586, 587) == 0) {
#else
    while (stage_ContinueAnimation(590, 591) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 286);
    scpPlayMot(scpSearchGobj(2403), 1002);
    scpPlayMot(scpSearchGobj(2404), 1024);
    scpPlayMot(scpSearchGobj(2405), 1048);
    _ACTWait(1);

    stage_SetAnimation(31, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(587, 588) == 0) {
#else
    while (stage_ContinueAnimation(591, 592) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2403), 1004);
    scpPlayMot(scpSearchGobj(2404), 1027);
    scpPlayMot(scpSearchGobj(2405), 1050);
    _ACTWait(1);

    stage_SetAnimation(24, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(588, 589) == 0) {
#else
    while (stage_ContinueAnimation(592, 593) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 287);
    scpSearchGobj(2403)->active = 0;
    scpSearchGobj(2404)->active = 0;
    scpSearchGobj(2405)->active = 0;

    stage_SetAnimation(34, 0, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(589, 200, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(593, 200, 0) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    scpFadeOut(3.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(589, -1, -2);
#else
    stage_SetAnimation(593, -1, -2);
#endif
    scpFadeIn(3.0f);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(590, 1, 0);
#else
    stage_SetAnimation(594, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(590, 591) == 0) {
#else
    while (stage_ContinueAnimation(594, 595) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 288);
    _ACTWait(1);

    stage_SetAnimation(26, 1, 0);
    _ACTWait(60);

    padAct = iosPadActRequest(boyPad, 9);
    padActVolume = 128;
    iosPadActVolumeSet(padAct, 128);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(591, 592) == 0) {
#else
    while (stage_ContinueAnimation(595, 596) == 0) {
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(592, 593) == 0) {
#else
    while (stage_ContinueAnimation(596, 597) == 0) {
#endif
        _ACTWait(1);
    }

    stage_SetAnimation(25, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(593, 594) == 0) {
#else
    while (stage_ContinueAnimation(597, 598) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 289);
    _ACTWait(130);

    stage_SetAnimation(32, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(594, 595) == 0) {
#else
    while (stage_ContinueAnimation(598, 599) == 0) {
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(595, 596) == 0) {
#else
    while (stage_ContinueAnimation(599, 600) == 0) {
#endif
        _ACTWait(1);
    }

    iosPadActStop(padAct);
    scpPlayMot((void *)boyGObj, 290);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(596, 597) == 0) {
#else
    while (stage_ContinueAnimation(600, 601) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 288);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(597, 598) == 0) {
#else
    while (stage_ContinueAnimation(601, 602) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 292);
    _ACTWait(1);

    stage_SetAnimation(32, 1, 208);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(598, 599) == 0) {
#else
    while (stage_ContinueAnimation(602, 603) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 293);
    iosPadActRequest(boyPad, 16);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(599, 600) == 0) {
#else
    while (stage_ContinueAnimation(603, 604) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 294);

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

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(600, 601) == 0) {
#else
    while (stage_ContinueAnimation(604, 605) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 295);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(601, 602) == 0) {
#else
    while (stage_ContinueAnimation(605, 606) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 296);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(602, 603) == 0) {
#else
    while (stage_ContinueAnimation(606, 607) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 297);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(603, 150, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(607, 150, 0) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    conte02End = 1;
}

void actSt13bSekizoChk(GObj *volatile self)
{
    float dir[4];

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 75) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpAdpcmPlayRequestFunc(19, &sekizo13b, 1, 1, 1);

    while (sekizo13b == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(33, 1, 0);

    st13b_yure = iosPadActRequest(boyPad, 9);
    st13b_yure_vol = 128;
    iosPadActVolumeSet(st13b_yure, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet((void *)boyGObj, 3085.0f, -1338.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
    scpSekizouCheckPoint();
    scpPlayMot((void *)boyGObj, 251);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot((void *)boyGObj, 0);
    scpPlayEnd(boyGObj);
    gflagOn(10);

    while (stage_CheckAnimationFrame(33, 151, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st13b_yure);

    while (stage_CheckAnimationFinish(33) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
}

void actSt13bSekizo2Chk(GObj *volatile self)
{
    float dir[4];

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 75) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpAdpcmPlayRequestFunc(18, &sekizo13b2, 1, 1, 1);

    while (sekizo13b2 == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(34, 1, 0);

    st13b_yure = iosPadActRequest(boyPad, 9);
    st13b_yure_vol = 128;
    iosPadActVolumeSet(st13b_yure, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet((void *)boyGObj, -1563.0f, 527.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
    scpSekizouCheckPoint();
    scpPlayMot((void *)boyGObj, 251);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot((void *)boyGObj, 0);
    scpPlayEnd(boyGObj);
    gflagOn(11);

    while (stage_CheckAnimationFrame(34, 151, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st13b_yure);

    while (stage_CheckAnimationFinish(34) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
}

void actSt13bMeetAgain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(12) == 0) {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);

        meetAgain_mes[0].func = actSt13bMeetAgainChk;
        act->mail = meetAgain_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
    }
}

static void actSt13bMeetAgainSub(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(756, 1, 0);
#else
    stage_SetAnimation(760, 1, 0);
#endif

    scpPlayMot((void *)boyGObj, 2);
    scpPlayMot(scpSearchGobj(2464), 971);
    scpPlayMot(scpSearchGobj(2465), 972);
    scpPlayMot(scpSearchGobj(2466), 973);
    scpPlayMot(scpSearchGobj(2467), 974);
    scpPlayMot(scpSearchGobj(2468), 975);
    scpPlayMot(scpSearchGobj(2469), 976);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(756, 757) == 0) {
#else
    while (stage_ContinueAnimation(760, 761) == 0) {
#endif
        _ACTWait(1);
    }

    SetCameraFlag_LwsCutBack();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(757) == 0) {
#else
    while (stage_CheckAnimationFinish(761) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt13bMeetAgainChk(GObj *volatile self)
{
    GProc *th;

    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayMot((void *)boyGObj, 0);
    gflagOn(12);
    scpAdpcmPlayRequestFunc(35, &meets_again, 1, 1, 1);

    while (meets_again == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(actSt13bMeetAgainSub, 21);
    demoEnd = 0;

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

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(756, 0, -1);
#else
        stage_SetAnimation(760, 0, -1);
#endif
        scpFadeIn(3.0f);
    }

    scpPlayMot(scpSearchGobj(2464), 977);
    scpPlayMot(scpSearchGobj(2465), 978);
    scpPlayMot(scpSearchGobj(2466), 979);
    scpPlayMot(scpSearchGobj(2467), 980);
    scpPlayMot(scpSearchGobj(2468), 981);
    scpPlayMot(scpSearchGobj(2469), 982);

    scpPlayMot((void *)boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpAdpcmFadeCloseFunc(&meets_again, 128);
}
#endif

void actSt13bBoss(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    ScpCallCameraSetTarget(-1886.0f, 625.0f, -4.0f);
    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    if (gflagChk(13) == 0) {
#ifdef VERSION_NTSC
        boss_mes[0].func = actSt13bBossChk;
        act->mail = boss_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else if (gflagChk(14) == 0) {
        scpAdpcmPlayRequestFunc(36, &boss, 1, 0, 1);
#else
        scpSearchGobj(2470)->active = 0;
        boss_mes[0].func = actSt13bBossChk;
        act->mail = boss_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else if (gflagChk(14) == 0) {
        scpAdpcmPlayRequestFunc(37, &boss, 1, 0, 1);
#endif
        scpSeEnvMasterVolRate = 0.5f;
    }
}

#ifdef VERSION_NTSC
void actSt13bBossChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    gflagOn(13);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 0);

    scpAdpcmPlayRequestFunc(35, &sd, 1, 1, 1);

    while (sd == 0) {
        _ACTWait(1);
    }

    scpSeEnvMasterVolRate = 0.5f;
    actCreateSubThread(actConte10b, 21);

    while (scpAdpcmCloseChk(meets_again) == 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(36, &boss, 1, 0, 0);
}

void actConte10b(GObj *volatile self)
{
    stage_SetAnimation(688, 1, 0);

    while (stage_CheckAnimationFinish(688) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    CapsuleGhostBossStart();

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 2);

    while (boss == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(boss->stream);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt13bElevDown(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(15);
    scpAdpcmPlayRequestFunc(77, &st13b_down, 0, 1, 1);

    while (st13b_down == 0) {
        _ACTWait(1);
    }

    preload(3);

    stage_SetAnimation(39, 1, 235);

    while (stage_CheckAnimationFrame(39, 321, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(39, 350, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13b_yure = iosPadActRequest(boyPad, 9);
    st13b_yure_vol = 128;
    iosPadActVolumeSet(st13b_yure, 128);

    while (stage_CheckAnimationFrame(39, 450, 0) == 0) {
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

    if (gflagChk(296) != 0) {
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(39, 0, 235);
        _ACTWait(10);
        scpBoyControlReadDisable = 1;
        stage_SetAnimation(39, 0, 0);
        elevUp_mes[0].func = actSt13bElevUpChk;
        act->mail = elevUp_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(39, 0, 235);
    }
}

void actSt13bElevUpChk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(76, &st13b_up, 1, 1, 1);

    while (st13b_up == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    stage_SetAnimation(39, 1, 0);
    st13b_yure = iosPadActRequest(boyPad, 9);
    st13b_yure_vol = 128;
    iosPadActVolumeSet(st13b_yure, 128);
    while (stage_CheckAnimationFrame(39, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    iosPadActStop(st13b_yure);
    while (stage_CheckAnimationFrame(39, 234, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    gflagOff(296);
}
#else
void actSt13bBossChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(13);
    scpAdpcmPlayRequestFunc(36, &sd, 1, 1, 1);

    while (sd == 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(37, &boss, 1, 0, 0);
    scpSeEnvMasterVolRate = 0.5f;

    scpSearchGobj(2470)->active = 1;
    scpPlayPosSet(scpSearchGobj(2470), 0.0f, -100.0f, 0.0f);

    scpPlayMot(scpSearchGobj(2464), 834);
    scpPlayMot(scpSearchGobj(2465), 834);
    scpPlayMot(scpSearchGobj(2466), 834);
    scpPlayMot(scpSearchGobj(2467), 834);
    scpPlayMot(scpSearchGobj(2468), 834);
    scpPlayMot(scpSearchGobj(2469), 834);

    CapsuleGhostBossStart();

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    while (boss == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(boss->stream);
}

void actSt13bBossAfterChk(GObj *volatile self)
{
    GProc *th;

    while (InqCapsuleGhostBossEnd() == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    gflagOn(14);
    scpAdpcmFadeCloseFunc(&boss, 128);

    while (scpAdpcmCloseChkFunc(&boss) != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(38, &boss_dead, 1, 1, 1);

    while (boss_dead == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(actConte10c, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&boss_dead, 512);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(759, 0, -1);
#else
        stage_SetAnimation(763, 0, -1);
#endif
        stage_SetAnimation(35, 0, -1);
        scpFadeIn(3.0f);
    }

    scpPlayMot((void *)boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}

static void actSt13bElevDownSub(GObj *volatile self)
{
    stage_SetAnimation(40, 1, 235);

    while (stage_CheckAnimationFrame(40, 321, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(40, 350, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13b_boss_yure = iosPadActRequest(boyPad, 9);
    st13b_boss_yure_vol = 128;
    iosPadActVolumeSet(st13b_boss_yure, 128);

    while (stage_CheckAnimationFrame(40, 450, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt13bElevDown(GObj *volatile self)
{
    GProc *th;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    gflagOn(15);
    scpAdpcmPlayRequestFunc(79, &st13b_down, 0, 1, 1);

    while (st13b_down == 0) {
        _ACTWait(1);
    }

    preload(3);
    st13b_boss_yure = -1;
    th = actCreateSubThread(actSt13bElevDownSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st13b_down, 512);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
    }

    if (st13b_boss_yure >= 0) {
        iosPadActStop(st13b_boss_yure);
    }

    RequestStageChange(3, boyGObj, 0, 2.0f, 4.0f);
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}

void actSt13bElevUp(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(325) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        lt_switch_layout(52);
#else
        lt_switch_layout(55);
#endif
        scpBoyControlReadDisable = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(40, 0, 235);
        _ACTWait(10);
        scpBoyControlReadDisable = 1;
        stage_SetAnimation(40, 0, 0);
        elevUp_mes[0].func = actSt13bElevUpChk;
        act->mail = elevUp_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(40, 0, 235);
    }
}

void actSt13bElevUpChk(GObj *volatile self)
{
    GProc *th;

    scpAdpcmPlayRequestFunc(78, &st13b_up, 1, 1, 1);

    while (st13b_up == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);
    th = actCreateSubThread(actSt13bElevUpSub, 21);

    demoEnd = 0;
    st13b_boss_yure = -1;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st13b_up, 512);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(40, 0, 235);
        _ACTWait(2);
        scpPlayPosSet((void *)boyGObj, -772.0f, 527.0f, -226.0f);

        if (st13b_boss_yure >= 0) {
            iosPadActStop(st13b_boss_yure);
        }

        scpFadeIn(3.0f);
    }

    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    gflagOff(325);
}

void actSt13bDoorUp(GObj *volatile self)
{
    GProc *th;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    gflagOn(17);
    th = actCreateSubThread(actSt13bDoorUpSub, 21);

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

        stage_SetAnimation(43, 0, -1);
        scpFadeIn(3.0f);
    }

    if (doorUpDone == 0) {
        soundSeDefPlay(1222, 0, 0, 1);
    }

    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}

static void actSt13bElev2Chk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

    if (gflagChk(16) != 0) {
        scpAdpcmPlayRequestFunc(100, &sekizo_13b_vol, 1, 1, 1);

        while (sekizo_13b_vol == 0) {
            _ACTWait(1);
        }

        _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1]);
        stage_SetAnimation(42, 1, 0);

        while (stage_CheckAnimationFrame(42, 50, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        iosPadActRequest(boyPad, 16);

        while (stage_CheckAnimationFinish(42) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        gflagOff(16);
        scpBoyControlReadDisable = 0;
    } else {
        scpAdpcmPlayRequestFunc(99, &sekizo_13b, 0, 1, 1);

        while (sekizo_13b == 0) {
            _ACTWait(1);
        }

        _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 0.15);
        stage_SetAnimation(41, 1, 0);

        while (stage_CheckAnimationFinish(41) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        gflagOn(16);
        RequestStageChange(2, boyGObj, 0, 2.0f, 8.0f);
        scpBoyControlReadDisable = 0;
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    elev2Chara_mes[0].func = actSt13bElev2CharaChk;
    sub->mail = elev2Chara_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif

void actSt13bSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(10) == 0) {
#ifdef VERSION_NTSC
        stage_SetAnimation(32, 0, 0);
#else
        stage_SetAnimation(33, 0, 0);
#endif

        sekizo_mes[0].func = actSt13bSekizoChk;
        act->mail = sekizo_mes;
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(33, 0, -1);
#endif
    }
}

void actSt13bSekizo2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(11) == 0) {
#ifdef VERSION_NTSC
        stage_SetAnimation(33, 0, 0);
#else
        stage_SetAnimation(34, 0, 0);
#endif

        sekizo2_mes[0].func = actSt13bSekizo2Chk;
        act->mail = sekizo2_mes;
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(33, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(34, 0, -1);
#endif
    }
}

void actSt13bBossAfter(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(14) == 0) {
#ifdef VERSION_NTSC
        stage_SetAnimation(34, 0, 0);
#else
        stage_SetAnimation(35, 0, 0);
#endif

        bossAfter_mes[0].func = actSt13bBossAfterChk;
        act->mail = bossAfter_mes;
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(34, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(35, 0, -1);
#endif
    }
}

void actSt13bStoneGirl(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (current_stage_no == 46) {
#ifdef VERSION_NTSC
        scpPlayMot(scpSearchGobj(2256), 763);
        scpSearchGobj(2256)->active = 1;
#else
        scpPlayMot(scpSearchGobj(2462), 808);
        scpSearchGobj(2462)->active = 1;
#endif
    }
}

#ifdef VERSION_NTSC
void actSt13bElev(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    elev_mes[0].func = actSt13bElevMain;
    act->mail = elev_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt13bDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(16) == 0) {
        stage_SetAnimation(40, 0, 0);

        door_mes[0].func = actSt13bDoorMain;
        act->mail = door_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(40, 0, -1);
    }
}
#else
void actSt13bElev(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    elev_mes[0].func = actSt13bElevMain;
    act->mail = elev_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt13bElev2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(16) != 0) {
        stage_SetAnimation(42, 0, 0);

        elev2Chk_mes[0].func = actSt13bElev2Chk;
        act->mail = elev2Chk_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(41, 0, 0);

        elev2Chk2_mes[0].func = actSt13bElev2Chk;
        act->mail = elev2Chk2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13bDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(17) == 0) {
        stage_SetAnimation(43, 0, 0);

        door_mes[0].func = actSt13bDoorMain;
        act->mail = door_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(43, 0, -1);
    }
}
#endif

void actBossTest(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_NTSC
    stage_SetAnimation(31, 0, -1);
    stage_SetAnimation(25, 0, 0);
    stage_SetAnimation(34, 0, 0);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(37, 0, 0);
#else
    stage_SetAnimation(32, 0, -1);
    stage_SetAnimation(26, 0, 0);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(36, 0, 0);
    stage_SetAnimation(38, 0, 0);
#endif
}

void actSt13bConte02Jimaku(GObj *volatile self)
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
#endif

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline void actSt13bSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(10) == 0) {
#ifdef VERSION_JUN26
        stage_SetAnimation(28, 0, 0);
#else
        stage_SetAnimation(32, 0, 0);
#endif

        sekizo_mes[0].func = actSt13bSekizoChk;
        act->mail = sekizo_mes;
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(28, 0, -1);
#else
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
#endif
    }
}

void actSt13bSekizoChk(GObj *volatile self)
{
    float dir[4];

#ifdef VERSION_JUN26
    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 83) {
#else
    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 75) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpSekizouCheckPoint();
    scpAdpcmPlayRequestFunc(21, 0, 1, 1, 1);
    scpBoyControlReadDisable = 1;
    lt_switch_layout(51);
    gflagOn(10);
    _ACTWait(60);

    stage_SetAnimation(28, 1, 0);
#else
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpAdpcmPlayRequestFunc(18, &sekizo13b, 1, 1, 1);

    while (sekizo13b == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(32, 1, 0);
#endif

    sekizo_13b = iosPadActRequest(boyPad, 9);
    sekizo_13b_vol = 128;
    iosPadActVolumeSet(sekizo_13b, 128);

    scpPlayStart(boyGObj);
    scpPlayPosSet((void *)boyGObj, 3085.0f, -1338.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 253);
#else
    scpSekizouCheckPoint();
    scpPlayMot((void *)boyGObj, 246);
#endif
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot((void *)boyGObj, 0);
    scpPlayEnd(boyGObj);
#ifdef VERSION_JUN26

    while (stage_CheckAnimationFinish(28) == 0) {
#else
    gflagOn(10);

    while (stage_CheckAnimationFrame(32, 151, 0) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(sekizo_13b);

#ifndef VERSION_JUN26
    while (stage_CheckAnimationFinish(32) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
#endif
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

inline void actSt13bSekizo2Event(int x)
{
    volatile int local = x;
}
#else
void actSt13bSekizo2Event(int x)
{
    volatile int local = x;
}
#endif

#ifdef VERSION_NTSC
void actSt13bMeetAgainChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 0);
    gflagOn(12);

    scpAdpcmPlayRequestFunc(34, &meets_again, 1, 1, 1);

    while (meets_again == 0) {
        _ACTWait(1);
    }

    actCreateSubThread(actConte10a, 21);
}

void actConte10a(GObj *volatile self)
{
    stage_SetAnimation(686, 1, 0);

    while (stage_ContinueAnimation(686, 687) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 393);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(687) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    scpAdpcmFadeClose(meets_again, 128);
}

void actSt13bBossAfterChk(GObj *volatile self)
{
    while (InqCapsuleGhostBossEnd() == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 0);
    gflagOn(14);

    if (boss != 0) {
        soundDataClose(boss);
    }

    _ACTWait(120);

    scpAdpcmPlayRequestFunc(37, &boss_dead, 1, 1, 1);

    while (boss_dead == 0) {
        _ACTWait(1);
    }

    actCreateSubThread(actConte10c, 21);
}

void actConte10c(GObj *volatile self)
{
    stage_SetAnimation(689, 1, 0);

    while (stage_CheckAnimationFrame(689, 300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(34, 1, 0);

    while (stage_CheckAnimationFinish(689) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline void actSt13bSekizo2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(11) == 0) {
#ifdef VERSION_JUN26
        stage_SetAnimation(29, 0, 0);
#else
        stage_SetAnimation(33, 0, 0);
#endif

        sekizo2_mes[0].func = actSt13bSekizo2Chk;
        act->mail = sekizo2_mes;
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(29, 0, -1);
#else
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(33, 0, -1);
#endif
    }
}

void actSt13bSekizo2Chk(GObj *volatile self)
{
    float dir[4];

#ifdef VERSION_JUN26
    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 83) {
#else
    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 75) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpSekizouCheckPoint();
    scpAdpcmPlayRequestFunc(21, 0, 1, 1, 1);
    scpBoyControlReadDisable = 1;
    lt_switch_layout(51);
    gflagOn(11);
    _ACTWait(60);

    stage_SetAnimation(29, 1, 0);
#else
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpAdpcmPlayRequestFunc(18, &sekizo13b2, 1, 1, 1);

    while (sekizo13b2 == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(33, 1, 0);
#endif

    sekizo_13b = iosPadActRequest(boyPad, 9);
    sekizo_13b_vol = 128;
    iosPadActVolumeSet(sekizo_13b, 128);

    scpPlayStart(boyGObj);
#ifdef VERSION_JUN26
    scpPlayPosSet((void *)boyGObj, -1618.0f, 527.0f, 0.0f);
#else
    scpPlayPosSet((void *)boyGObj, -1563.0f, 527.0f, 0.0f);
#endif
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
#ifdef VERSION_JUN26
    scpPlayMot((void *)boyGObj, 253);
#else
    scpSekizouCheckPoint();
    scpPlayMot((void *)boyGObj, 246);
#endif
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot((void *)boyGObj, 0);
    scpPlayEnd(boyGObj);
#ifdef VERSION_JUN26

    while (stage_CheckAnimationFinish(29) == 0) {
#else
    gflagOn(11);

    while (stage_CheckAnimationFrame(33, 151, 0) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(sekizo_13b);

#ifndef VERSION_JUN26
    while (stage_CheckAnimationFinish(33) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
#endif
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt13bMeetAgain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(12) == 0) {
#ifdef VERSION_JUN26
        stage_SetAnimation(27, 0, -1);
        stage_SetAnimation(21, 0, 0);
        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
#else
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
#endif

        meetAgain_mes[0].func = actSt13bMeetAgainChk;
        act->mail = meetAgain_mes;
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(27, 0, -1);
        stage_SetAnimation(21, 0, 0);
        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
#else
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
#endif
    }
}

inline void actSt13bMeetAgainChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    gflagOn(12);
    scpBoyControlReadDisable = 1;
    scpAdpcmPlayRequestFunc(37, 0, 1, 1, 1);
#else
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 0);
    gflagOn(12);

    scpAdpcmPlayRequestFunc(34, &meets_again, 1, 1, 1);

    while (meets_again == 0) {
        _ACTWait(1);
    }

#endif
    actCreateSubThread(actConte10a, 21);
}

inline void actConte10a(GObj *volatile self)
{
#ifdef VERSION_JUN26
    lt_switch_layout(51);
    scpPlayStart(boyGObj);
    stage_SetAnimation(636, 1, 0);

    while (stage_ContinueAnimation(636, 637) == 0) {
#else
    stage_SetAnimation(685, 1, 0);

    while (stage_ContinueAnimation(685, 686) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpPlayMot(boyGObj, 402);
#else
    scpPlayMot(boyGObj, 393);
#endif

    SetCameraFlag_LwsCutBack();

#ifdef VERSION_JUN26
    while (stage_CheckAnimationFinish(637) == 0) {
#else
    while (stage_CheckAnimationFinish(686) == 0) {
#endif
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

#ifndef VERSION_JUN26
    ScpCallCameraSetTarget(-1886.0f, 651.0f, -4.0f);
#endif
    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    if (gflagChk(13) == 0) {
#ifdef VERSION_JUN26
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
#else
        boss_mes[0].func = actSt13bBossChk;
        act->mail = boss_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else if (gflagChk(14) == 0) {
        scpAdpcmPlayRequestFunc(36, &boss, 1, 0, 1);
        scpSeEnvMasterVolRate = 0.5f;
#endif
    }
}

inline void actSt13bBossChk(GObj *volatile self)
{
#ifdef VERSION_JUN26
    while (scpTriggerBall(self, boyGObj, 300.0f) == 0 || (GOBJ_ACT(boyGObj)->pad.trg & 8) == 0) {
#else
    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
#endif
        _ACTWait(1);
    }

    lt_switch_layout(51);
    gflagOn(13);
    scpBoyControlReadDisable = 1;
#ifdef VERSION_JUN26

    scpAdpcmPlayRequestFunc(38, &boss, 1, 0, 1);
#else
    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 0);

    scpAdpcmPlayRequestFunc(35, &sd, 1, 1, 1);

    while (sd == 0) {
        _ACTWait(1);
    }

    scpSeEnvMasterVolRate = 0.5f;
    actCreateSubThread(actConte10b, 21);

    scpAdpcmPlayRequestFunc(36, &boss, 1, 0, 0);
}

void actConte10b(GObj *volatile self)
{
    stage_SetAnimation(687, 1, 0);

    while (stage_CheckAnimationFinish(687) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    CapsuleGhostBossStart();

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 2);
#endif

    while (boss == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
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
#else
    AdpcmPlay(boss->stream);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
#endif
}

inline void actSt13bStoneGirl(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (current_stage_no == 46) {
#ifdef VERSION_JUN26
        scpPlayMot(scpSearchGobj(2138), 789);
        scpSearchGobj(2138)->active = 1;
#else
        scpPlayMot(scpSearchGobj(2231), 765);
        scpSearchGobj(2231)->active = 1;
#endif
    }
}

inline void actSt13bBossAfter(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(14) == 0) {
#ifdef VERSION_JUN26
        stage_SetAnimation(30, 0, 0);
#else
        stage_SetAnimation(34, 0, 0);
#endif

        bossAfter_mes[0].func = actSt13bBossAfterChk;
        act->mail = bossAfter_mes;
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(30, 0, -1);
#else
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(34, 0, -1);
#endif
    }
}

inline void actSt13bBossAfterChk(GObj *volatile self)
{
#ifdef VERSION_JUN26
    while (actEnemyFlagCheckDead(scpSearchGobj(2139)) == 0 ||
           actEnemyFlagCheckDead(scpSearchGobj(2140)) == 0) {
#else
    while (InqCapsuleGhostBossEnd() == 0) {
#endif
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
#ifndef VERSION_JUN26
    scpPlayMot(boyGObj, 0);
#endif
    gflagOn(14);

    if (boss != 0) {
        soundDataClose(boss);
    }

    _ACTWait(120);

#ifdef VERSION_JUN26
    CameraSetCameraSet(4);
    scpAdpcmPlayRequestFunc(40, 0, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(37, &boss_dead, 1, 1, 1);

    while (boss_dead == 0) {
        _ACTWait(1);
    }

#endif
    actCreateSubThread(actConte10c, 21);
}

inline void actConte10c(GObj *volatile self)
{
#ifdef VERSION_JUN26
    stage_SetAnimation(640, 1, 0);
    stage_SetAnimation(30, 1, 0);
    scpPlayMot(boyGObj, 404);

    while (stage_ContinueAnimation(640, 641) == 0) {
        _ACTWait(1);
    }

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(641) == 0) {
#else
    stage_SetAnimation(688, 1, 0);

    while (stage_CheckAnimationFrame(688, 300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(34, 1, 0);

    while (stage_CheckAnimationFinish(688) == 0) {
#endif
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
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 393);
#endif
    _ACTWait(0);
}
#else
void actConte10c(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(759, 1, 0);
#else
    stage_SetAnimation(763, 1, 0);
#endif

    SetCameraFlag_LwsCutBack();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(759, 300, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(763, 300, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(35, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(759) == 0) {
#else
    while (stage_CheckAnimationFinish(763) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}
#endif
#endif

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline void actSt13bExitChk(GObj *volatile self)
{
#ifdef VERSION_JUN26
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 || gflagChk(282) != 0) {
#else
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 || gflagChk(295) != 0) {
#endif
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
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 393);
#endif
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
#else
void actSt13bElevMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = elevMain_mes;
    while (1) {
        _ACTWait(1);
    }
}
#endif

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline void actSt13bElevSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    elevSwitch_mes[0].func = actSt13bElevDown;
    sub->mail = elevSwitch_mes;
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 393);
#endif
    _ACTWait(0);
}

void actSt13bElevDown(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(15);
#ifdef VERSION_JUN26
    scpAdpcmPlayRequestFunc(72, &st13b_down, 0, 1, 1);
#else
    scpAdpcmPlayRequestFunc(77, &st13b_down, 0, 1, 1);
#endif

    while (st13b_down == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(35, 1, 235);

    while (stage_CheckAnimationFrame(35, 321, 0) == 0) {
#else
    stage_SetAnimation(39, 1, 235);

    while (stage_CheckAnimationFrame(39, 321, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(35, 350, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(39, 350, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    st13b_yure = iosPadActRequest(boyPad, 9);
    st13b_yure_vol = 128;
    iosPadActVolumeSet(st13b_yure, 128);

#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(35, 450, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(39, 450, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st13b_yure);

    RequestStageChange(3, boyGObj, 0, 2.0f, 4.0f);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
#else
void actSt13bElevSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    elevSwitch_mes[0].func = actSt13bElevDown;
    sub->mail = elevSwitch_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt13bElevUpSub(GObj *volatile self)
{
    stage_SetAnimation(40, 1, 0);
    st13b_boss_yure = iosPadActRequest(boyPad, 9);
    st13b_boss_yure_vol = 128;
    iosPadActVolumeSet(st13b_boss_yure, 128);
    while (stage_CheckAnimationFrame(40, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    iosPadActStop(st13b_boss_yure);
    while (stage_CheckAnimationFrame(40, 234, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
#endif
    _ACTWait(0);
}
#endif

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
void actSt13bElevUp(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_JUN26
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
#else
    if (gflagChk(295) != 0) {
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(39, 0, 235);
        _ACTWait(10);
        scpBoyControlReadDisable = 1;
        stage_SetAnimation(39, 0, 0);
        elevUp_mes[0].func = actSt13bElevUpChk;
        act->mail = elevUp_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(39, 0, 235);
#endif
    }
}

void actSt13bElevUpChk(GObj *volatile self)
{
#ifdef VERSION_JUN26
    scpAdpcmPlayRequestFunc(71, &st13b_up, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(76, &st13b_up, 1, 1, 1);
#endif

    while (st13b_up == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

#ifdef VERSION_JUN26
    stage_SetAnimation(35, 1, 0);
#else
    stage_SetAnimation(39, 1, 0);
#endif
    st13b_yure = iosPadActRequest(boyPad, 9);
    st13b_yure_vol = 128;
    iosPadActVolumeSet(st13b_yure, 128);
#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(35, 200, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(39, 200, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    iosPadActStop(st13b_yure);
#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(35, 234, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(39, 234, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
#ifdef VERSION_JUN26
    gflagOff(282);
#else
    gflagOff(295);
#endif
}

inline void actBossTest(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_JUN26
    stage_SetAnimation(27, 0, -1);
    stage_SetAnimation(21, 0, 0);
    stage_SetAnimation(30, 0, 0);
    stage_SetAnimation(31, 0, 0);
    stage_SetAnimation(33, 0, 0);
#else
    stage_SetAnimation(31, 0, -1);
    stage_SetAnimation(25, 0, 0);
    stage_SetAnimation(34, 0, 0);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(37, 0, 0);
#endif
}

inline void actSt13bDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(16) == 0) {
#ifdef VERSION_JUN26
        stage_SetAnimation(36, 0, 0);
#else
        stage_SetAnimation(40, 0, 0);
#endif

        door_mes[0].func = actSt13bDoorMain;
        act->mail = door_mes;
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(36, 0, -1);
#else
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(40, 0, -1);
#endif
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
#else
void actSt13bDoorMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = doorMain_mes;
    while (1) {
        _ACTWait(1);
    }
}
#endif

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline void actSt13bDoorSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    doorSwitch_mes[0].func = actSt13bDoorUp;
    sub->mail = doorSwitch_mes;
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 393);
#endif
    _ACTWait(0);
}
#else
void actSt13bDoorSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    doorSwitch_mes[0].func = actSt13bDoorUp;
    sub->mail = doorSwitch_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}
#endif

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline void actSt13bDoorUp(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(16);

    _ACTWait(60);

#ifdef VERSION_JUN26
    stage_SetAnimation(36, 1, 0);

    soundSeDefPlay(1171, 0, doorUpSubPos, 1);
#else
    stage_SetAnimation(40, 1, 0);

    soundSeDefPlay(1197, 0, doorUpSubPos, 1);
#endif

    _ACTWait(30);

#ifdef VERSION_JUN26
    soundSeDefPlay(1172, 0, doorUpSubPos, 1);

    while (stage_CheckAnimationFinish(36) == 0) {
#else
    soundSeDefPlay(1198, 0, doorUpSubPos, 1);

    while (stage_CheckAnimationFinish(40) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
#else
void actSt13bDoorUp(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(16);

    _ACTWait(60);

    stage_SetAnimation(40, 1, 0);

    soundSeDefPlay(1197, 0, doorUpSubPos, 1);

    _ACTWait(30);

    soundSeDefPlay(1198, 0, doorUpSubPos, 1);

    while (stage_CheckAnimationFinish(40) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
#endif
#else
static void actSt13bDoorUpSub(GObj *volatile self)
{
    _ACTWait(60);

    stage_SetAnimation(43, 1, 0);

    _ACTWait(120);

    soundSeDefPlay(1221, 0, doorUpSubPos, 1);

    _ACTWait(30);

    doorUpDone = 1;
    soundSeDefPlay(1222, 0, doorUpSubPos, 1);

    while (stage_CheckAnimationFinish(43) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

static void actSt13bElev2CharaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0x4000000) != 0) {
        _ACTWait(1);
    }

    elev2CharaChk_mes[0].func = actSt13bElev2Chk;
    sub->mail = elev2CharaChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif
