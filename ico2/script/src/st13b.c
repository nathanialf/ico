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
   the conte-02 cutscene holds. */
static int demoEnd; /* derived name */

static int padAct; /* derived name */

static unsigned char padActVolume; /* derived name */

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

static float doorUpSubPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f}; /* derived name */

/* .sdata: the scene stream and the stream handles, then the two shakes' pad
   actuator handles and volumes. */
static SqEntry *st13b_adpcm = 0; /* derived name */

SqEntry *sekizo13b = 0;

SqEntry *sekizo13b2 = 0;

SqEntry *meets_again = 0;

SqEntry *boss = 0;

SqEntry *sd = 0;

SqEntry *boss_dead = 0;

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
        scpBoyControlReadDisable = 1;

        stage_SetAnimation(29, 0, 0);
        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
        stage_SetAnimation(39, 0, 235);
        stage_SetAnimation(40, 0, 0);

        floor_mes[0].func = actSt13bFloorChk;
        act->mail = floor_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, -1);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
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
    scpPlayStart(boyGObj);
    stgmgrNextStagePreLoadForceStageSet(0);
    scpAdpcmPlayRequestFunc(11, &st13b_adpcm, 0, 1, 0);

    while (st13b_adpcm == 0) {
        _ACTWait(1);
    }

    scpFadeIn(8.0f);

    stgmgrNextStagePreLoadForceStageSet(exitData[(&stageData[stage_no])->ent[3]].nextStage);
    stgmgrNextStagePreLoadForceNoCancel(1);

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

    AdpcmPlay(st13b_adpcm->stream);

    while (stage_ContinueAnimation(514, 515) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 277);
    scpPlayMot(scpSearchGobj(2172), 943);
    scpPlayMot(scpSearchGobj(2173), 965);
    scpPlayMot(scpSearchGobj(2174), 989);
    _ACTWait(1);

    stage_SetAnimation(26, 1, 0);
    stage_SetAnimation(21, 1, 0);

    while (stage_ContinueAnimation(515, 516) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    stage_SetAnimation(27, 1, 0);

    while (stage_ContinueAnimation(516, 517) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 278);
    scpPlayMot(scpSearchGobj(2172), 944);
    scpPlayMot(scpSearchGobj(2173), 966);
    scpPlayMot(scpSearchGobj(2174), 990);
    _ACTWait(1);

    stage_SetAnimation(28, 1, 0);
    stage_SetAnimation(22, 1, 0);

    while (stage_ContinueAnimation(517, 518) == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    scpPlayMot((void *)boyGObj, 279);
    scpPlayMot(scpSearchGobj(2173), 967);
    _ACTWait(1);

    stage_SetAnimation(29, 1, 0);

    while (stage_ContinueAnimation(518, 519) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 280);
    scpPlayMot(scpSearchGobj(2172), 943);
    scpPlayMot(scpSearchGobj(2173), 965);
    scpPlayMot(scpSearchGobj(2174), 989);
    _ACTWait(1);

    stage_SetAnimation(30, 1, 0);

    while (stage_ContinueAnimation(519, 520) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2172), 945);
    scpPlayMot(scpSearchGobj(2173), 968);
    scpPlayMot(scpSearchGobj(2174), 991);
    _ACTWait(1);

    stage_SetAnimation(23, 1, 0);

    while (stage_ContinueAnimation(520, 521) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 281);
    scpSearchGobj(2172)->active = 0;
    scpSearchGobj(2173)->active = 0;
    scpSearchGobj(2174)->active = 0;

    stage_SetAnimation(33, 0, 0);

    while (stage_CheckAnimationFrame(521, 200, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpFadeOut(3.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }

    stage_SetAnimation(521, -1, -2);
    scpFadeIn(3.0f);
    stage_SetAnimation(522, 1, 0);

    while (stage_ContinueAnimation(522, 523) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 282);
    _ACTWait(1);

    stage_SetAnimation(25, 1, 0);
    _ACTWait(60);

    padAct = iosPadActRequest(boyPad, 9);
    padActVolume = 128;
    iosPadActVolumeSet(padAct, 128);

    while (stage_ContinueAnimation(523, 524) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(524, 525) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(24, 1, 0);

    while (stage_ContinueAnimation(525, 526) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 283);
    _ACTWait(130);

    stage_SetAnimation(31, 1, 0);

    while (stage_ContinueAnimation(526, 527) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(527, 528) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(padAct);
    scpPlayMot((void *)boyGObj, 284);

    while (stage_ContinueAnimation(528, 529) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 282);

    while (stage_ContinueAnimation(529, 530) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 286);
    while (stage_ContinueAnimation(530, 531) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 287);
    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(531, 532) == 0) {
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

    while (stage_ContinueAnimation(532, 533) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 289);

    while (stage_ContinueAnimation(533, 534) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 290);

    while (stage_ContinueAnimation(534, 535) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)boyGObj, 291);

    while (stage_CheckAnimationFrame(535, 150, 0) == 0) {
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
        stage_SetAnimation(32, 0, 0);

        sekizo_mes[0].func = actSt13bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
    }
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
        stage_SetAnimation(33, 0, 0);

        sekizo2_mes[0].func = actSt13bSekizo2Chk;
        act->mail = sekizo2_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(33, 0, -1);
    }
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
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
    }
}

inline void actSt13bMeetAgainChk(GObj *volatile self)
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

inline void actConte10a(GObj *volatile self)
{
    stage_SetAnimation(685, 1, 0);

    while (stage_ContinueAnimation(685, 686) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 393);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(686) == 0) {
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

    ScpCallCameraSetTarget(-1886.0f, 651.0f, -4.0f);
    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    if (gflagChk(13) == 0) {
        boss_mes[0].func = actSt13bBossChk;
        act->mail = boss_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else if (gflagChk(14) == 0) {
        scpAdpcmPlayRequestFunc(36, &boss, 1, 0, 1);
        scpSeEnvMasterVolRate = 0.5f;
    }
}

inline void actSt13bBossChk(GObj *volatile self)
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

    while (boss == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(boss->stream);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

inline void actSt13bStoneGirl(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (current_stage_no == 46) {
        scpPlayMot(scpSearchGobj(2231), 765);
        scpSearchGobj(2231)->active = 1;
    }
}

inline void actSt13bBossAfter(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(14) == 0) {
        stage_SetAnimation(34, 0, 0);

        bossAfter_mes[0].func = actSt13bBossAfterChk;
        act->mail = bossAfter_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(34, 0, -1);
    }
}

inline void actSt13bBossAfterChk(GObj *volatile self)
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

inline void actConte10c(GObj *volatile self)
{
    stage_SetAnimation(688, 1, 0);

    while (stage_CheckAnimationFrame(688, 300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(34, 1, 0);

    while (stage_CheckAnimationFinish(688) == 0) {
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
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt13bExitChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0 || gflagChk(295) != 0) {
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
    ACTSendMailCorrect(self, 393);
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
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt13bElevDown(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(15);
    scpAdpcmPlayRequestFunc(77, &st13b_down, 0, 1, 1);

    while (st13b_down == 0) {
        _ACTWait(1);
    }

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
    gflagOff(295);
}

inline void actBossTest(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    stage_SetAnimation(31, 0, -1);
    stage_SetAnimation(25, 0, 0);
    stage_SetAnimation(34, 0, 0);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(37, 0, 0);
}

inline void actSt13bDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(16) == 0) {
        stage_SetAnimation(40, 0, 0);

        door_mes[0].func = actSt13bDoorMain;
        act->mail = door_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(40, 0, -1);
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
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt13bDoorUp(GObj *volatile self)
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
