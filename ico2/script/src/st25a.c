#include "st25a.h"
#include "StageManager.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "gobj_process.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "boyact.h"
#include "commonact.h"
#include "queen.h"
#include "camera-ico2.h"
#include "camera-root.h"
#include "fightSound.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "Texture.h"
#include "boy.h"
#include "geometryManager.h"
#include "motionManager2.h"
#include "streamMotionManager.h"
#include <libvu0.h>
#include <string.h>
#include "e3.h"
#include "typedef.h"
#include "layout_action.h"
#include "main.h"
#include "script.h"
#include "jimaku.h"

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
static void actSt25aElevCharaChk(GObj *volatile self);
#endif

/* .sdata: the ADPCM request slots the scenes hand scpAdpcmPlayRequestFunc
   and wait on, and conte12's flag. */
static SqEntry *conte11 = 0; /* derived name */

SqEntry *conte12 = 0;

SqEntry *sd2 = 0;

static int conte12Flag = 0; /* derived name */

SqEntry *dead = 0;

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
static SqEntry *elevAgain = 0; /* derived name */

static SqEntry *elevFirst = 0; /* derived name */
#endif

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

/* this file's own view of Vec4 (the shared one is in typedef.h) */
typedef union Vec4St25A { /* derived name */ /* field names derived */
    float f[4];
    long long d[2];
} __attribute__((aligned(16))) Vec4St25A; /* derived name */

typedef struct AnimSet18 { /* field names derived */
    int anim[18];          /* 0x00 */
} AnimSet18;               /* derived name */

#ifdef VERSION_NTSC
/* the two face-shadow textures actSt25aQueenAppear and actConte11
   scroll the UVs of. */
static const char faceShadowTex[] = "face_sadow_sd"; /* derived name */

static const char faceShadowTex00[] = "face_sadow_sd_00"; /* derived name */
#else
/* the two face-shadow textures ConteQueenDead scrolls the UVs of. */
const char faceShadowTex[] = "face_sadow_sd"; /* script.c scrolls it too */

const char faceShadowTex00[] = "face_sadow_sd_00";
#endif

/* The offset the sekika boy is dropped by. */
static const Vec4St25A sekikaOfs = {{2000.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

static const char streamWaitFmt[] =
    "Now waiting for standby stream motion system... %d\n"; /* derived name */

#ifdef VERSION_NTSC
/* The eighteen stage animations the cancelled ending restores. */
static const AnimSet18 cancelAnimSet = {
    /* derived name */
    {710, 711, 712, 713, 714, 715, 716, 717, 718, 719, 720, 721, 722, 723, 724, 725, 726, 727}};
#else
#ifdef VERSION_AUG6
/* The eighteen stage animations the cancelled ending restores. */
static const AnimSet18 cancelAnimSet = {
    /* derived name */
    {709, 710, 711, 712, 713, 714, 715, 716, 717, 718, 719, 720, 721, 722, 723, 724, 725, 726}};
#else
/* The eighteen stage animations the cancelled ending restores. */
static const AnimSet18 cancelAnimSet = {
/* derived name */
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    {780, 781, 782, 783, 784, 785, 786, 787, 788, 789, 790, 791, 792, 793, 794, 795, 796, 797}};

#else
    {784, 785, 786, 787, 788, 789, 790, 791, 792, 793, 794, 795, 796, 797, 798, 799, 800, 801}};
#endif
#endif

#endif

/* Where the boy is put back when the ending is cancelled. */
static const Vec4St25A cancelBoyPos = {
    {-1472.7711f, 928.20026f, -18.074427f, 0.0f}}; /* derived name */

static const char queenBallScrTexture[] = "queen_ball_scr"; /* derived name */

static const char sekikaBoyTexture[] = "sekika_boy"; /* derived name */

#ifdef VERSION_AUG6
/* .data: ten actor mail records.  Each is
   the usual pair, the 393 entry whose handler the sender fills in and the 392
   terminator.  queen_appear_mes is the only one another TU sends, so it is the
   only global of the ten. */
static ActMail queen_before_mes[2] = {{393}, {392}}; /* derived name */

ActMail queen_appear_mes[2] = {{393}, {392}}; /* derived name */

static ActMail queen_talk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail queen_dead_mes[2] = {{393}, {392}}; /* derived name */

static ActMail queen_attack_mes[2] = {{393}, {392}}; /* derived name */

void actSt25aQueenBeforeChk(GObj *volatile self);
#else
#ifdef VERSION_NTSC
/* .data: six actor mail records.  Each is
   the usual pair, the 397 entry whose handler the sender fills in and the 396
   terminator. */
static ActMail queen_before_mes[2] = {{397}, {396}}; /* derived name */

static ActMail queen_appear_mes[2] = {{397}, {396}}; /* derived name */

static ActMail queen_talk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail queen_dead_ready_mes[2] = {{397}, {396}}; /* derived name */

static ActMail queen_dead_mes[2] = {{397}, {396}}; /* derived name */

static ActMail queen_attack_mes[2] = {{397}, {396}}; /* derived name */
#else
/* .data: ten actor mail records.  Each is
   the usual pair, the 430 entry whose handler the sender fills in and the 429
   terminator.  queen_appear_mes is the only one another TU sends, so it is the
   only global of the ten. */
static ActMail queen_before_mes[2] = {{430}, {429}}; /* derived name */

ActMail queen_appear_mes[2] = {{430}, {429}};

static ActMail queen_talk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail queen_dead_ready_mes[2] = {{430}, {429}}; /* derived name */

static ActMail queen_dead_mes[2] = {{430}, {429}}; /* derived name */

static ActMail queen_attack_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elev_up_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elev_down_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elev_chara_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elev_end_mes[2] = {{430}, {429}}; /* derived name */
#endif

void actSt25aQueenBeforeChk(GObj *volatile self);
static void actSt25aQueenDeadReadyChk(GObj *volatile self);
#endif

void actItouQueenAttackChk(GObj *volatile self);
void actConte11(GObj *volatile self);
void actConte11Jimaku(GObj *volatile self);

#ifdef VERSION_NTSC
/* Before flag 302 this hands the actor queen_appear_mes and posts it; after
 * it, it shows object 1966, plays its motion and starts the face shadow
 * scrolls and the stage animations. */
void actSt25aQueenAppear(GObj *volatile self)
{
    GObj *x = self;
    Act *act = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(302) == 0) {
        ScpCallCameraSetTarget(3834.0f, -888.0f, 0.0f);
        scpSearchGobj(1966)->active = 0;
        stage_SetLoopFlag(484, 0);
        queen_appear_mes[0].func = actSt25aQueenAppearChk;
        act->mail = queen_appear_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
        return;
    }
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(46, 0, 484, 0);
    scpSearchGobj(1966)->active = 1;
    scpPlayMot(scpSearchGobj(1966), 1043);
    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);
    ScpCallCameraSetTarget(3834.0f, -888.0f, 0.0f);
    stage_SetAnimation(135, 0, -1);
    stage_SetAnimation(138, 1, 0);
}

void actSt25aQueenAppearChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 || gflagChk(301) == 0) {
        _ACTWait(1);
    }
    enable_game_pause = 0;
    gflagOn(302);
    actCreateSubThread(actConte11Jimaku, 21);
    while (conte11 == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(conte11->stream);
    scpBoyControlReadDisable = 1;
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 3);
    actCreateSubThread(actConte11, 21);
}

void actConte11(GObj *volatile self)
{
    Vec4St25A ofs;
    float dir[4];

    lt_switch_layout(51);
    scpPlayStart(boyGObj);

    stage_SetAnimation(690, 1, 0);

    scpPlayMot(boyGObj, 394);
    scpSearchGobj(1966)->active = 1;
    scpPlayMot(scpSearchGobj(1966), 1043);

    _ACTWait(1);
    stage_SetAnimation(135, 1, 0);

    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(46, 0, 484, 0);

    stage_SetLoopFlag(484, 1);
    stage_SetAnimation(484, 1, 0);

    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    while (stage_ContinueAnimation(690, 691) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(691, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    scpPlayMot(scpSearchGobj(1966), 1044);

    scpPlayMot(boyGObj, 0);
    ofs = sekikaOfs;
    sceVu0SubVector(dir, &ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFinish(691) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSekizouCheckPoint();

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    enable_game_pause = 1;
}
#else
#ifdef VERSION_AUG6
void actSt25aQueenAppear(GObj *volatile self)
{
    GObj *x = self;
    Act *act = (Act *)actInitialize(self);

    _ACTWait(1);
    if (gflagChk(301) == 0) {
        ScpCallCameraSetTarget(3834.0f, -888.0f, 0.0f);
        scpSearchGobj(1942)->active = 0;
        stage_SetLoopFlag(483, 0);
        queen_appear_mes[0].func = actSt25aQueenAppearChk;
        act->mail = queen_appear_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
        return;
    }
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(46, 0, 483, 0);
    scpSearchGobj(1942)->active = 1;
    scpPlayMot(scpSearchGobj(1942), 1045);
    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);
    ScpCallCameraSetTarget(3834.0f, -888.0f, 0.0f);
    stage_SetAnimation(134, 0, -1);
    stage_SetAnimation(137, 1, 0);
}

void actSt25aQueenAppearChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 || gflagChk(300) == 0) {
        _ACTWait(1);
    }
    gflagOn(301);
    actCreateSubThread(actConte11Jimaku, 21);
    while (conte11 == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(conte11->stream);
    scpBoyControlReadDisable = 1;
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 3);
    actCreateSubThread(actConte11, 21);
}
#else
void actSt25aQueenAppearChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 || gflagChk(331) == 0) {
        _ACTWait(1);
    }
    enable_game_pause = 0;
    gflagOn(332);
    actCreateSubThread(actConte11Jimaku, 21);
    while (conte11 == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(conte11->stream);
    scpBoyControlReadDisable = 1;
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 3);
    actCreateSubThread(actConte11, 21);
}
#endif

void actConte11(GObj *volatile self)
{
    Vec4St25A ofs;
    float dir[4];

#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpPlayStart(boyGObj);

    stage_SetAnimation(689, 1, 0);

    scpPlayMot(boyGObj, 394);
    scpSearchGobj(1942)->active = 1;
    scpPlayMot(scpSearchGobj(1942), 1045);

    _ACTWait(1);
    stage_SetAnimation(134, 1, 0);

    stage_SetLoopFlag(483, 1);
    stage_SetAnimation(483, 1, 0);

    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(46, 0, 483, 0);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpPlayStart(boyGObj);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(760, 1, 0);
#else
    stage_SetAnimation(764, 1, 0);
#endif

    scpPlayMot(boyGObj, 400);
    scpSearchGobj(2149)->active = 1;
    scpPlayMot(scpSearchGobj(2149), 1104);

    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(152, 1, 0);
#else
    stage_SetAnimation(156, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(47, 0, 551, 0);
#else
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(47, 0, 555, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetLoopFlag(551, 1);
    stage_SetAnimation(551, 1, 0);
#else
    stage_SetLoopFlag(555, 1);
    stage_SetAnimation(555, 1, 0);
#endif
#endif

    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(689, 690) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(690, 10, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(760, 761) == 0) {
#else
    while (stage_ContinueAnimation(764, 765) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(761, 10, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(765, 10, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

#ifdef VERSION_AUG6
    scpPlayMot(scpSearchGobj(1942), 1046);
#else
    scpPlayMot(scpSearchGobj(2149), 1105);
#endif

    scpPlayMot(boyGObj, 0);
    ofs = sekikaOfs;
    sceVu0SubVector(dir, &ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    SetCameraFlag_LwsCutBack();
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(761) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(690) == 0) {
#else
    while (stage_CheckAnimationFinish(765) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSekizouCheckPoint();

#ifndef VERSION_AUG6
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    _ACTWait(60);
#endif

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;
#ifdef VERSION_AUG6
    lt_switch_layout(50);
#else
    enable_game_pause = 1;
#endif
}
#endif

/* actSt25aQueenTalkChk's work area: the stage animations the cancelled
   ending restores, or the boy's position and the direction vectors the
   scene's motions are played along */
typedef union TalkWork { /* derived name */ /* field names derived */
    AnimSet18 a;
    Vec4St25A v[3];
} TalkWork; /* derived name */

/* .sbss: the flag the demo raises when it is over, and the one its inner event
   raises when that has run. */
static int demoEnd;

static int eventDone; /* derived name */

#ifdef VERSION_NTSC
void actSt25aQueenTalkChk(GObj *volatile self)
{
    TalkWork w;
    unsigned int i;
    unsigned int n;
    int cancel;
    GProc *th1;
    GProc *th2;

    conte12 = sd2 = 0;

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0 || gflagChk(302) == 0) {
        _ACTWait(1);
    }

    iosPadActStopAll();

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpPlayMotReq(boyGObj, 1);

    StandbyStreamMotion(streamMotion[6].path);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(streamWaitFmt, i);
        _ACTWait(1);
    }

    gflagOn(303);

    scpAdpcmPlayRequestFunc(39, &conte12, 1, 1, 1);
    while (conte12 == 0) {
        _ACTWait(1);
    }

    th1 = actCreateSubThread(actConte12, 21);
    th2 = actCreateSubThread(actConte12Jimaku, 21);

    demoEnd = 0;
    eventDone = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    cancel = demoEnd ^ 1;

    if (cancel != 0) {
        scpAdpcmFadeClose(conte12, 256);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    DeleteStreamMotionManager();
    iosPadActStopAll();
    iosThreadSetPri(&((GProc *)th1)->thread, 34);
    iosThreadSetPri(&((GProc *)th2)->thread, 34);

    if (cancel != 0) {
        w.a = cancelAnimSet;
        for (n = 0; n < 18; n++) {
            stage_SetAnimation(w.a.anim[n], 1, -1);
            _ACTWait(1);
        }

        ScpCallCameraTargetOff();
        DeleteBoyWeapon();
        scpLinkBGAtoLayoutedTarget(1975, 423);

        scpSearchGobj(1975)->active = 1;
        stage_SetAnimation(136, -1, -2);
        SelectBoyCrown(boyGObj, 1);

        stage_SetAnimation(485, 0, -1);
        stage_SetAnimation(489, 0, -1);
        stage_SetAnimation(490, 0, -1);

        stage_SetAnimation(727, 1, -1);
        jimakuUndisp(&jimaku_msg);

        w.v[0] = cancelBoyPos;
        SetDirectRootPosition(boyGObj, &w.v[0]);

        if (eventDone == 0) {
            QueenStartAttack();
            gflagOn(304);
        }

        _ACTWait(1);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(3.0f);
    }

    gflagOn(305);

    scpPlayMot(scpSearchGobj(1966), 1011);
    scpPlayPosSet(scpSearchGobj(1966), 1650.0f, 625.0f, 0.0f);

    memset(w.v[1].f, 0, 16);
    w.v[1].f[3] = 1.0f;
    sceVu0SubVector(w.v[2].f, w.v[1].f, test_CURRENTROOT(scpSearchGobj(1966)));
    scpPlayMotDir(scpSearchGobj(1966), w.v[2].f);
    scpPlayEnd(scpSearchGobj(1966));

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    CameraSetCameraSet(51);

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(40, &sd2, 1, 0, 1);

    stage_SetAnimation(138, -1, -2);

    stage_SetLoopFlag(139, 1);

    stage_SetAnimation(139, 1, 0);
}

void actConte12(GObj *volatile self)
{
    conte12Flag = 0;

    scpSearchGobj(1966)->active = 1;
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(scpSearchGobj(1966));
    PlayStreamMotion();

    stage_SetAnimation(710, 1, 0);
    while (stage_ContinueAnimation(710, 711) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(711, 712) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(712, 713) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(713, 714) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(714, 715) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(715, 716) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(716, 717) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(717, 718) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(718, 719) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(719, 720) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(720, 721) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(410, 1, 0);

    while (stage_ContinueAnimation(721, 722) == 0) {
        _ACTWait(1);
    }

    DeleteBoyWeapon();
    SelectBoyCrown(boyGObj, 1);
    stage_SetAnimation(136, 1, 0);
    stage_SetAnimation(485, 1, 0);

    iosPadActRequest(boyPad, 15);
    while (stage_CheckAnimationFrame(722, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    while (stage_CheckAnimationFrame(722, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    while (stage_CheckAnimationFrame(722, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    while (stage_CheckAnimationFrame(722, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(722, 723) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(489, 1, 0);

    while (stage_ContinueAnimation(723, 724) == 0) {
        _ACTWait(1);
    }

    scpLinkBGAtoLayoutedTarget(1975, 423);

    scpSearchGobj(1975)->active = 1;

    _ACTWait(1);
    stage_SetAnimation(490, 1, 0);

    stage_SetAnimation(136, -1, -2);

    while (stage_ContinueAnimation(724, 725) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(725, 726) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(726, 727) == 0) {
        _ACTWait(1);
    }

    eventDone = 1;
    QueenStartAttack();
    gflagOn(304);

    ScpCallCameraTargetOff();

    while (stage_CheckAnimationFinish(727) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}
#else
void actSt25aQueenTalkChk(GObj *volatile self)
{
    TalkWork w;
    unsigned int i;
    unsigned int n;
    int cancel;
    GProc *th1;
    GProc *th2;

    conte12 = sd2 = 0;

#ifdef VERSION_AUG6
    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0 || gflagChk(301) == 0) {
#else
    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0 || gflagChk(332) == 0) {
#endif
        _ACTWait(1);
    }

    iosPadActStopAll();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;

    scpPlayMotReq(boyGObj, 1);

    StandbyStreamMotion(streamMotion[6].path);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(streamWaitFmt, i);
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(302);

    scpAdpcmPlayRequestFunc(39, &conte12, 1, 1, 1);
#else
    gflagOn(333);

    scpAdpcmPlayRequestFunc(40, &conte12, 1, 1, 1);
#endif
    while (conte12 == 0) {
        _ACTWait(1);
    }

    th1 = actCreateSubThread(actConte12, 21);
    th2 = actCreateSubThread(actConte12Jimaku, 21);

    demoEnd = 0;
    eventDone = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    cancel = demoEnd ^ 1;

    if (cancel != 0) {
#ifdef VERSION_AUG6
        scpAdpcmFadeClose(conte12, 192);
#else
        scpAdpcmFadeCloseFunc(&conte12, 256);
#endif

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    DeleteStreamMotionManager();
    iosPadActStopAll();
    iosThreadSetPri(&((GProc *)th1)->thread, 34);
    iosThreadSetPri(&((GProc *)th2)->thread, 34);

    if (cancel != 0) {
        w.a = cancelAnimSet;
        for (n = 0; n < 18; n++) {
            stage_SetAnimation(w.a.anim[n], 1, -1);
            _ACTWait(1);
        }

        ScpCallCameraTargetOff();
        DeleteBoyWeapon();
#ifdef VERSION_AUG6
        scpLinkBGAtoLayoutedTarget(1951, 422);

        scpSearchGobj(1951)->active = 1;
        stage_SetAnimation(135, -1, -2);
        SelectBoyCrown(boyGObj, 1);

        stage_SetAnimation(484, 0, -1);
        stage_SetAnimation(488, 0, -1);
        stage_SetAnimation(489, 0, -1);

        stage_SetAnimation(726, 1, -1);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        scpLinkBGAtoLayoutedTarget(2158, 483);
#else
        scpLinkBGAtoLayoutedTarget(2158, 487);
#endif

        scpSearchGobj(2158)->active = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(153, -1, -2);
#else
        stage_SetAnimation(157, -1, -2);
#endif
        SelectBoyCrown(boyGObj, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(552, 0, -1);
#endif
        stage_SetAnimation(556, 0, -1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(557, 0, -1);
#else
        stage_SetAnimation(560, 0, -1);
        stage_SetAnimation(561, 0, -1);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(797, 1, -1);
#else
        stage_SetAnimation(801, 1, -1);
#endif
#endif
        jimakuUndisp(&jimaku_msg);

        w.v[0] = cancelBoyPos;
        SetDirectRootPosition(boyGObj, &w.v[0]);

        if (eventDone == 0) {
            QueenStartAttack();
#ifdef VERSION_AUG6
            gflagOn(303);
#else
            gflagOn(334);
#endif
        }

        _ACTWait(1);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(3.0f);
    }

#ifdef VERSION_AUG6
    gflagOn(304);

    scpPlayMot(scpSearchGobj(1942), 1013);
    scpPlayPosSet(scpSearchGobj(1942), 1650.0f, 625.0f, 0.0f);
#else
    gflagOn(335);

    scpPlayMot(scpSearchGobj(2149), 1072);
    scpPlayPosSet(scpSearchGobj(2149), 1650.0f, 625.0f, 0.0f);
#endif

    memset(w.v[1].f, 0, 16);
    w.v[1].f[3] = 1.0f;
#ifdef VERSION_AUG6
    sceVu0SubVector(w.v[2].f, w.v[1].f, test_CURRENTROOT(scpSearchGobj(1942)));
    scpPlayMotDir(scpSearchGobj(1942), w.v[2].f);
    scpPlayEnd(scpSearchGobj(1942));
#else
    sceVu0SubVector(w.v[2].f, w.v[1].f, test_CURRENTROOT(scpSearchGobj(2149)));
    scpPlayMotDir(scpSearchGobj(2149), w.v[2].f);
    scpPlayEnd(scpSearchGobj(2149));
#endif

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif

    CameraSetCameraSet(51);

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(40, &sd2, 1, 0, 1);

    stage_SetAnimation(137, -1, -2);

    stage_SetLoopFlag(138, 1);

    stage_SetAnimation(138, 1, 0);
#else
    scpAdpcmPlayRequestFunc(41, &sd2, 1, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(155, -1, -2);
#else
    stage_SetAnimation(159, -1, -2);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetLoopFlag(156, 1);
#else
    stage_SetLoopFlag(160, 1);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(156, 1, 0);
#else
    stage_SetAnimation(160, 1, 0);
#endif
#endif
}

void actConte12(GObj *volatile self)
{
    conte12Flag = 0;

#ifdef VERSION_AUG6
    scpSearchGobj(1942)->active = 1;
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(scpSearchGobj(1942));
    PlayStreamMotion();

    stage_SetAnimation(709, 1, 0);
    while (stage_ContinueAnimation(709, 710) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(710, 711) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(711, 712) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(712, 713) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(713, 714) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(714, 715) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(715, 716) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(716, 717) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(717, 718) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(718, 719) == 0) {
#else
    scpSearchGobj(2149)->active = 1;
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(scpSearchGobj(2149));
    PlayStreamMotion();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(780, 1, 0);
    while (stage_ContinueAnimation(780, 781) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(781, 782) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(782, 783) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(783, 784) == 0) {
        _ACTWait(1);
    }
#else
    stage_SetAnimation(784, 1, 0);
#endif
    while (stage_ContinueAnimation(784, 785) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(785, 786) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(786, 787) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(787, 788) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(788, 789) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(789, 790) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(790, 791) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)

    stage_SetAnimation(470, 1, 0);

#endif
    while (stage_ContinueAnimation(791, 792) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)

    DeleteBoyWeapon();
    SelectBoyCrown(boyGObj, 1);
    stage_SetAnimation(153, 1, 0);
    stage_SetAnimation(552, 1, 0);

    scpLinkBGAtoLayoutedTarget(2152, 483);

    iosPadActRequest(boyPad, 15);
    while (stage_CheckAnimationFrame(792, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    while (stage_CheckAnimationFrame(792, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    while (stage_CheckAnimationFrame(792, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    while (stage_CheckAnimationFrame(792, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

#endif
    while (stage_ContinueAnimation(792, 793) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)

    stage_SetAnimation(556, 1, 0);

#endif
    while (stage_ContinueAnimation(793, 794) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)

    scpLinkBGAtoLayoutedTarget(2158, 483);

    scpSearchGobj(2158)->active = 1;

    _ACTWait(1);
    stage_SetAnimation(557, 1, 0);

    stage_SetAnimation(153, -1, -2);
#endif

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(719, 720) == 0) {
#else
    while (stage_ContinueAnimation(794, 795) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(409, 1, 0);

    while (stage_ContinueAnimation(720, 721) == 0) {
#else
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
    stage_SetAnimation(474, 1, 0);

#endif
    while (stage_ContinueAnimation(795, 796) == 0) {
#endif
        _ACTWait(1);
    }
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)

    DeleteBoyWeapon();
    SelectBoyCrown(boyGObj, 1);
#ifdef VERSION_AUG6
    stage_SetAnimation(135, 1, 0);
    stage_SetAnimation(484, 1, 0);

    iosPadActRequest(boyPad, 15);
    while (stage_CheckAnimationFrame(721, 15, 0) == 0) {
#else
    stage_SetAnimation(157, 1, 0);
    stage_SetAnimation(556, 1, 0);

    scpLinkBGAtoLayoutedTarget(2152, 487);

    iosPadActRequest(boyPad, 15);
    while (stage_CheckAnimationFrame(796, 15, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(721, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(796, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(721, 50, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(796, 50, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(721, 60, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(796, 60, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

#endif
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(721, 722) == 0) {
#else
    while (stage_ContinueAnimation(796, 797) == 0) {
#endif
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(488, 1, 0);

    while (stage_ContinueAnimation(722, 723) == 0) {
#else
    stage_SetAnimation(560, 1, 0);

    while (stage_ContinueAnimation(797, 798) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(489, 1, 0);

    scpLinkBGAtoLayoutedTarget(1951, 422);

    scpSearchGobj(1951)->active = 1;

    stage_SetAnimation(135, -1, -2);

    while (stage_ContinueAnimation(723, 724) == 0) {
#else
    scpLinkBGAtoLayoutedTarget(2158, 487);

    scpSearchGobj(2158)->active = 1;

    _ACTWait(1);
    stage_SetAnimation(561, 1, 0);

    stage_SetAnimation(157, -1, -2);

    while (stage_ContinueAnimation(798, 799) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(724, 725) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(725, 726) == 0) {
#else
    while (stage_ContinueAnimation(799, 800) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(800, 801) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    eventDone = 1;
    QueenStartAttack();
#ifdef VERSION_AUG6
    gflagOn(303);
#else
    gflagOn(334);
#endif

    ScpCallCameraTargetOff();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(797) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(726) == 0) {
#else
    while (stage_CheckAnimationFinish(801) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}
#endif

void actConte12Jimaku(GObj *volatile self)
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
        case 341:
            jimaku_msg.sub.block = 96;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 521:
            jimaku_msg.sub.block = 97;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 801:
            jimaku_msg.sub.block = 98;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1031:
            jimaku_msg.sub.block = 99;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1301:
            jimaku_msg.sub.block = 100;
            jimaku_msg.sub.jump = 200;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1781:
            jimaku_msg.sub.block = 104;
            jimaku_msg.sub.jump = 200;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2261:
            jimaku_msg.sub.block = 105;
            jimaku_msg.sub.jump = 150;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2561:
            jimaku_msg.sub.block = 106;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3780:
            jimaku_msg.sub.block = 109;
            jimaku_msg.sub.jump = 180;
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
    } while (t < 4200.0f);
    _ACTWait(0);
}

#ifdef VERSION_NTSC
void actSt25aQueenDeadChk(GObj *volatile self)
{
    while (QueenInqDead() == 0) {
        _ACTWait(1);
    }

    iosPadActRequest(boyPad, 16);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayStart(scpSearchGobj(1966));

    if (sd2 != 0) {
        scpAdpcmFadeClose(sd2, 256);
    }

    scpKillEnemyAll();

    gflagOn(307);
    gflagOn(5);

    while (dead == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(dead->stream);

    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[3]].nextStage);
    stgmgrNextStagePreLoadForceNoCancel(1);

    scpSearchGobj(1966)->active = 1;
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(scpSearchGobj(1966));
    PlayStreamMotion();

    actCreateSubThread(actConte13Jimaku, 21);

    stage_SetAnimation(728, 1, 0);

    scpSearchGobj(2042)->active = 0;
    scpSearchGobj(2043)->active = 0;

    while (stage_ContinueAnimation(728, 729) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(729, 730) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(730, 731) == 0) {
        _ACTWait(1);
    }

    GOBJ_SUB(scpSearchGobj(1966))->streamScale = 0;
    while (stage_ContinueAnimation(731, 732) == 0) {
        _ACTWait(1);
    }

    GOBJ_SUB(scpSearchGobj(1966))->streamScale = 1;
    while (stage_ContinueAnimation(732, 733) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(733, 734) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(414, 1, 0);
    iosPadActRequest(boyPad, 15);
    DeleteBoyWeapon();
    stage_SetAnimation(423, -1, -2);
    stage_SetAnimation(137, 1, 0);

    while (stage_ContinueAnimation(734, 735) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(735, 736) == 0) {
        _ACTWait(1);
    }

    SelectBoyCrown(boyGObj, 2);
    stage_SetAnimation(486, 1, 0);

    while (stage_CheckAnimationFrame(736, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_ContinueAnimation(736, 737) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(487, 1, 0);

    while (stage_CheckAnimationFrame(737, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    scpSearchGobj(1966)->active = 0;
    stage_SetLoopFlag(484, 0);

    while (stage_ContinueAnimation(737, 739) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFinish(739) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    DeleteStreamMotionManager();

    RequestStageChange(4, boyGObj, 0, 1.0f, 8.0f);
}
#else
void actSt25aQueenDeadChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    unsigned int i;

    dead = 0;
#endif
    while (QueenInqDead() == 0) {
        _ACTWait(1);
    }

    iosPadActRequest(boyPad, 16);

#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayStart(scpSearchGobj(1942));

    StandbyStreamMotion(streamMotion[8].path);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(streamWaitFmt, i);
        _ACTWait(1);
    }

    if (sd2 != 0) {
        scpAdpcmFadeClose(sd2, 256);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayStart(scpSearchGobj(2149));

    if (sd2 != 0) {
        scpAdpcmFadeCloseFunc(&sd2, 256);
#endif
    }

    scpKillEnemyAll();

#ifdef VERSION_AUG6
    gflagOn(306);
    gflagOn(5);

    scpAdpcmPlayRequestFunc(41, &dead, 0, 1, 1);
#else
    gflagOn(338);
    gflagOn(5);

#endif
    while (dead == 0) {
        _ACTWait(1);
    }
#ifndef VERSION_AUG6
    AdpcmPlay(dead->stream);
#endif

    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[3]].nextStage);
    stgmgrNextStagePreLoadForceNoCancel(1);

#ifdef VERSION_AUG6
    scpSearchGobj(1942)->active = 1;
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(scpSearchGobj(1942));
#else
    scpSearchGobj(2149)->active = 1;
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(scpSearchGobj(2149));
#endif
    PlayStreamMotion();

    actCreateSubThread(actConte13Jimaku, 21);

#ifdef VERSION_AUG6
    stage_SetAnimation(727, 1, 0);

    scpSearchGobj(2017)->active = 0;
    scpSearchGobj(2018)->active = 0;

    while (stage_ContinueAnimation(727, 728) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(728, 729) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(729, 730) == 0) {
        _ACTWait(1);
    }

    GOBJ_SUB(scpSearchGobj(1942))->streamScale = 0;
    while (stage_ContinueAnimation(730, 731) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(798, 1, 0);
#else
    stage_SetAnimation(802, 1, 0);
#endif

    scpSearchGobj(2227)->active = 0;
    scpSearchGobj(2228)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(798, 799) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(799, 800) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(800, 801) == 0) {
        _ACTWait(1);
    }

    GOBJ_SUB(scpSearchGobj(2149))->streamScale = 0;
    while (stage_ContinueAnimation(801, 802) == 0) {
        _ACTWait(1);
    }

    GOBJ_SUB(scpSearchGobj(2149))->streamScale = 1;
#endif
    while (stage_ContinueAnimation(802, 803) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(803, 804) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)

    stage_SetAnimation(474, 1, 0);
    iosPadActRequest(boyPad, 15);
    DeleteBoyWeapon();
    stage_SetAnimation(483, -1, -2);
    stage_SetAnimation(154, 1, 0);

#endif
    while (stage_ContinueAnimation(804, 805) == 0) {
        _ACTWait(1);
    }
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)

    GOBJ_SUB(scpSearchGobj(2149))->streamScale = 0;
#endif
    while (stage_ContinueAnimation(805, 806) == 0) {
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    SelectBoyCrown(boyGObj, 2);
    stage_SetAnimation(553, 1, 0);
#else
#ifdef VERSION_AUG6
    GOBJ_SUB(scpSearchGobj(1942))->streamScale = 1;
    while (stage_ContinueAnimation(731, 732) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(732, 733) == 0) {
#else
    GOBJ_SUB(scpSearchGobj(2149))->streamScale = 1;
    while (stage_ContinueAnimation(806, 807) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(807, 808) == 0) {
#endif
        _ACTWait(1);
    }
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(806, 15, 0) == 0) {
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(413, 1, 0);
    iosPadActRequest(boyPad, 15);
    DeleteBoyWeapon();
    stage_SetAnimation(422, -1, -2);
    stage_SetAnimation(136, 1, 0);

    while (stage_ContinueAnimation(733, 734) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(734, 735) == 0) {
#else
    stage_SetAnimation(478, 1, 0);
    iosPadActRequest(boyPad, 15);
    DeleteBoyWeapon();
    stage_SetAnimation(487, -1, -2);
    stage_SetAnimation(158, 1, 0);

    while (stage_ContinueAnimation(808, 809) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(809, 810) == 0) {
#endif
        _ACTWait(1);
    }

    SelectBoyCrown(boyGObj, 2);
#ifdef VERSION_AUG6
    stage_SetAnimation(485, 1, 0);

    while (stage_CheckAnimationFrame(735, 15, 0) == 0) {
#else
    stage_SetAnimation(557, 1, 0);

    while (stage_CheckAnimationFrame(810, 15, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(806, 807) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(735, 736) == 0) {
#else
    while (stage_ContinueAnimation(810, 811) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(486, 1, 0);

    while (stage_CheckAnimationFrame(736, 10, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(554, 1, 0);
#else
    stage_SetAnimation(558, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(807, 10, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(811, 10, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

#ifdef VERSION_AUG6
    scpSearchGobj(1942)->active = 0;
    stage_SetLoopFlag(483, 0);

    while (stage_ContinueAnimation(736, 738) == 0) {
#else
    scpSearchGobj(2149)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetLoopFlag(551, 0);
#else
    stage_SetLoopFlag(555, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(807, 809) == 0) {
#else
    while (stage_ContinueAnimation(811, 813) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(809) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(738, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFinish(813) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    DeleteStreamMotionManager();
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(738) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
#endif

    RequestStageChange(4, boyGObj, 0, 1.0f, 8.0f);
}
#endif

void actConte13Jimaku(GObj *volatile self)
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
        case 600:
            jimaku_msg.sub.block = 110;
            jimaku_msg.sub.jump = 400;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1320:
            jimaku_msg.sub.block = 111;
            jimaku_msg.sub.jump = 200;
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
    } while (t < 3100.0f);
}

void BoySekikaTexScroll(void)
{
    tex_SetUVScroll(sekikaBoyTexture, 0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.5f, 1);
}

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
static void actSt25aElevChk(GObj *volatile self)
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
    if (gflagChk(337) == 0) {
        scpAdpcmPlayRequestFunc(100, &elevFirst, 1, 1, 1);
        while (elevFirst == 0) {
            _ACTWait(1);
        }
        _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1]);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(157, 1, 0);
        while (stage_CheckAnimationFrame(157, 50, 0) == 0) {
#else
        stage_SetAnimation(161, 1, 0);
        while (stage_CheckAnimationFrame(161, 50, 0) == 0) {
#endif
            _ACTWait(1);
        }
        _ACTWait(1);
        iosPadActRequest(boyPad, 16);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFinish(157) == 0) {
#else
        while (stage_CheckAnimationFinish(161) == 0) {
#endif
            _ACTWait(1);
        }
        _ACTWait(1);
        gflagOn(337);
    } else {
        scpAdpcmPlayRequestFunc(99, &elevAgain, 0, 1, 1);
        while (elevAgain == 0) {
            _ACTWait(1);
        }
        _ACTWait((int)((60 - systemStatus[0] * 10) / systemStatus[1] * 0.15));
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(158, 1, 0);
        while (stage_CheckAnimationFinish(158) == 0) {
#else
        stage_SetAnimation(162, 1, 0);
        while (stage_CheckAnimationFinish(162) == 0) {
#endif
            _ACTWait(1);
        }
        _ACTWait(1);
        gflagOff(337);
        RequestStageChange(1, boyGObj, 0, 2.0f, 8.0f);
    }
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    elev_chara_mes[0].func = actSt25aElevCharaChk;
    sub->mail = elev_chara_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif

void actSt25aGenerator(GObj *volatile self)
{
    Generator_Mask(self);
}

#ifdef VERSION_AUG6
void actSt25aQueenBefore(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(300) == 0) {
        queen_before_mes[0].func = actSt25aQueenBeforeChk;
        sub->mail = queen_before_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt25aQueenTalk(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    fightSoundProcessRequestPause();

    if (gflagChk(302) == 0) {
        scpSearchGobj(1951)->active = 0;
        queen_talk_mes[0].func = actSt25aQueenTalkChk;
        sub->mail = queen_talk_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}
#else
#ifdef VERSION_NTSC
void actSt25aQueenBefore(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    MallocStreamMotionBuffer();

    if (gflagChk(301) == 0) {
        queen_before_mes[0].func = actSt25aQueenBeforeChk;
        sub->mail = queen_before_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt25aQueenTalk(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    fightSoundProcessRequestPause();

    if (gflagChk(303) == 0) {
        scpSearchGobj(1975)->active = 0;
        queen_talk_mes[0].func = actSt25aQueenTalkChk;
        sub->mail = queen_talk_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}
#else
void actSt25aQueenBefore(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    MallocStreamMotionBuffer();

    if (gflagChk(331) == 0) {
        queen_before_mes[0].func = actSt25aQueenBeforeChk;
        sub->mail = queen_before_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt25aQueenTalk(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    fightSoundProcessRequestPause();

    if (gflagChk(333) == 0) {
        scpSearchGobj(2158)->active = 0;
        queen_talk_mes[0].func = actSt25aQueenTalkChk;
        sub->mail = queen_talk_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}
#endif

void actSt25aQueenDeadReady(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    queen_dead_ready_mes[0].func = actSt25aQueenDeadReadyChk;
    sub->mail = queen_dead_ready_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}
#endif

void actSt25aQueenDead(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    queen_dead_mes[0].func = actSt25aQueenDeadChk;
    sub->mail = queen_dead_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actItouQueenAttack(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    queen_attack_mes[0].func = actItouQueenAttackChk;
    sub->mail = queen_attack_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
#else
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt25aElev(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(337) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(158, 0, 0);
#else
        stage_SetAnimation(162, 0, 0);
#endif
        elev_up_mes[0].func = actSt25aElevChk;
        sub->mail = elev_up_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(157, 0, 0);
#else
        stage_SetAnimation(161, 0, 0);
#endif
        elev_down_mes[0].func = actSt25aElevChk;
        sub->mail = elev_down_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
#endif
#endif
}

void actSwordEff(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpLinkBGAtoLayoutedTarget(2098, 483);
#else
#ifdef VERSION_NTSC
    scpLinkBGAtoLayoutedTarget(1926, 423);
#else
#ifdef VERSION_AUG6
    scpLinkBGAtoLayoutedTarget(1902, 422);
#else
    scpLinkBGAtoLayoutedTarget(2098, 487);
#endif
#endif
#endif
}

void actSwordEffXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (scpGameStat_BoyWeaponkind() == 5) {
#ifdef VERSION_NTSC
        scpLinkBGAtoLayoutedTarget(1926, 423);
    } else {
        stage_SetAnimation(423, -1, -2);
#else
#ifdef VERSION_AUG6
        scpLinkBGAtoLayoutedTarget(1902, 422);
    } else {
        stage_SetAnimation(422, -1, -2);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        scpLinkBGAtoLayoutedTarget(2098, 483);
#else
        scpLinkBGAtoLayoutedTarget(2098, 487);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(483, -1, -2);
#else
        stage_SetAnimation(487, -1, -2);
#endif
#endif
#endif
    }
}

void actSt25aQueenBeforeChk(GObj *volatile self)
{
    conte11 = 0;
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#ifdef VERSION_AUG6
    gflagOn(300);
#else
    gflagOn(301);
#endif
    jimakuBegin(&jimaku_msg);
    scpAdpcmPlayRequestFunc(38, &conte11, 1, 1, 0);
#else
    gflagOn(331);
    jimakuBegin(&jimaku_msg);
    scpAdpcmPlayRequestFunc(39, &conte11, 1, 1, 0);
#endif
}

void actConte11Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            break;
        case 10:
            jimaku_msg.sub.block = 93;
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
    } while (t < 1500.0f);
}

#ifdef VERSION_NTSC
static void actSt25aQueenDeadReadyChk(GObj *volatile self)
{
    int i;

    dead = 0;
    while (InqQueenBarrierExist() != 0 || gflagChk(304) == 0) {
        _ACTWait(1);
    }
    StandbyStreamMotion(streamMotion[8].path);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(streamWaitFmt, i);
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(41, &dead, 0, 1, 0);
}
#else
#ifndef VERSION_AUG6
static void actSt25aQueenDeadReadyChk(GObj *volatile self)
{
    int i;

    dead = 0;
    while (InqQueenBarrierExist() != 0 || gflagChk(334) == 0) {
        _ACTWait(1);
    }
    StandbyStreamMotion(streamMotion[8].path);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(streamWaitFmt, i);
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(42, &dead, 0, 1, 0);
}
#endif
#endif

void actSt25aQueenDeadEvent(int x)
{
    volatile int local = x;
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actItouQueenAttackChk(GObj *volatile self)
{
    while (1) {
#ifdef VERSION_AUG6
        while (ForMotionViewer_GetCurrentMotion(scpSearchGobj(3225)) != 1019) {
#else
        while (ForMotionViewer_GetCurrentMotion(scpSearchGobj(3255)) != 1017) {
#endif
            _ACTWait(1);
        }
        tex_SetUVScroll(queenBallScrTexture, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 1);
        _ACTWait(1);
    }
}
#else
void actItouQueenAttackChk(GObj *volatile self)
{
    while (1) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (ForMotionViewer_GetCurrentMotion(scpSearchGobj(3503)) != 1078) {
#else
        while (ForMotionViewer_GetCurrentMotion(scpSearchGobj(3526)) != 1078) {
#endif
            _ACTWait(1);
        }
        tex_SetUVScroll(queenBallScrTexture, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 1);
        _ACTWait(1);
    }
}

static void actSt25aElevCharaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0x4000000) != 0) {
        _ACTWait(1);
    }

    elev_end_mes[0].func = actSt25aElevChk;
    sub->mail = elev_end_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif
