#include "st04a.h"
#include "StageManager.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "obj_manager.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act-game.h"
#include "act.h"
#include "gobj_process.h"
#include "boyact.h"
#include "commonact.h"
#include "way_llf.h"
#include "brain.h"
#include "camera-root.h"
#include "fightSound.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include "Texture.h"
#include "geometryManager.h"
#include "girl.h"
#include "matrixDrive.h"
#include "staticBlur.h"

#ifdef VERSION_NTSC
#include "windManager.h"
#endif

#ifdef VERSION_AUG6
#include "windManager.h"
#endif

#ifdef VERSION_JUN26
#include "windManager.h"
#endif

#include "streamMotionManager.h"
#include <libvu0.h>
#include "e3.h"
#include "typedef.h"
#include "Matrix.h"
#include "script.h"
#include "jimaku.h"
#include "main.h"

#ifdef VERSION_JUN26
/* this file's own view of Act (the shared one is in typedef.h): the torch
   watcher's three words */
typedef struct ActSt04A { /* field names derived */
    char pad0[1128];      /* 0x000 */
    int torchAnim;        /* 0x468, the stage animation the lit torch plays */
    GObj *torchObj;       /* 0x46C, the torch the ball must reach */
    int torchFlag;        /* 0x470, the game flag raised once it is lit */
} ActSt04A;               /* derived name */

/* .data: each action's mail pair and the check handler stored into its first
   entry at run time. */
static ActMail gate_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open2_ready_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open2_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open3_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_l_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_r_mail[2] = {{377}, {376}}; /* derived name */

static ActMail torch1_mail[2] = {{377}, {376}}; /* derived name */

static ActMail girl_sit_mail[2] = {{377}, {376}}; /* derived name */

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

/* .sdata: the first gate's stream handle */
SqEntry *gate1st = 0;

void actSt04aGate(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    scpSearchGobj(528)->active = 0;

    if (gflagChk(116) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(212, 0, 0);
        stage_SetAnimation(215, 0, 0);

        gate_mail[0].func = actSt04aGateChk;
        act->mail = gate_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(212, 0, -1);
        stage_SetAnimation(215, 0, 0);
    }
}

void actSt04aGateChk(GObj *volatile self)
{
    int i;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, boyGObj, 3000.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);

    scpPlayMot(boyGObj, 0);

    StandbyStreamMotion(streamMotion[1].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", ++i);
        _ACTWait(1);
    }

    SetWindManager(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 5.0f, 0.0f);

    scpPlayStart(girlGObj);

    reg_SetScissorSw(1);

    SetStaticBlur(0);

    scpAdpcmPlayRequestFunc(25, &gate1st, 1, 1, 1);
    while (gate1st == 0) {
        _ACTWait(1);
    }

    gflagOn(116);

    _ACTWait(1);

    actCreateSubThread(actSt04aConte06, 21);
    actCreateSubThread(actSt04aConte06Jimaku, 21);

    stage_SetAnimation(212, 1, 0);
}

void actSt04aConte06(GObj *volatile self)
{
    float dir[4];

    scpSearchGobj(528)->active = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion(scpSearchGobj(528));

    PlayStreamMotion();

    scpFadeIn(6.0f);

    stage_SetAnimation(527, 1, 0);

    while (stage_ContinueAnimation(527, 528) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(528, 529) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(529, 530) == 0) {
        _ACTWait(1);
    }

    _ACTWait(240);

    gate_yure_low = iosPadActRequest(boyPad, 9);
    gate_yure_low_vol = 64;
    iosPadActVolumeSet(gate_yure_low, 64);

    while (stage_ContinueAnimation(530, 531) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(531, 532) == 0) {
        _ACTWait(1);
    }

    reg_SetScissorSw(0);

    while (stage_ContinueAnimation(532, 533) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(533, 534) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(534, 535) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(375, 1, 0);

    iosPadActRequest(boyPad, 15);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    while (stage_ContinueAnimation(535, 536) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(536, 537) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(gate_yure_low);

    while (stage_CheckAnimationFrame(537, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    while (stage_ContinueAnimation(537, 538) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(538, 539) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(539, 540) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(540, 541) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(541, 542) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(542, 543) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(543, 544) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(544, 545) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(545, 546) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(546, 547) == 0) {
        _ACTWait(1);
    }

    _ACTWait(120);

    stage_SetAnimation(377, 1, 0);

    iosPadActRequest(boyPad, 15);

    while (stage_ContinueAnimation(547, 548) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(528)->active = 0;

    while (stage_ContinueAnimation(548, 549) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(549, 550) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(550, 551) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(551, 552) == 0) {
        _ACTWait(1);
    }

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(552) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 521);

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    sceVu0SubVector(dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    _ACTWait(1);

    iosOmSendMail(girlGObj, 58, boyGObj);

    scpBoyControlReadDisable = 0;

    ReinitWindManager();

    lt_switch_layout(50);

    SetStaticBlur(1);
}

/* .sdata: the other gate and torch stream handles, then the pad shakes and
   their volumes (declared in st04a.h for actSt04aConte06). */
static SqEntry *gate_open = 0; /* derived name */
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
static void finishCallBackFunc(struct GObj *obj);

/* this file's own view of Act (the shared one is in typedef.h) */
typedef struct ActSt04A { /* field names derived */
    char pad0[32];        /* 0x00 */
    ActStatus flags20;    /* 0x20 */
    char pad28[8];        /* 0x28 */
    int actMode;          /* 0x30, the current action mode */
#ifdef VERSION_AUG6
    char pad34[124];   /* 0x34 */
    ActMail *mainMail; /* 0xB0 */
    ActMail *mail;     /* 0xB4 */
    char padB8[936];   /* 0xB8 */
#else
    char pad34[140];   /* 0x34 */
    ActMail *mainMail; /* 0xC0 */
    ActMail *mail;     /* 0xC4 */
    char padC8[920];   /* 0xC8 */
#endif
    int torchAnim;  /* 0x460, the stage animation the lit torch plays */
    GObj *torchObj; /* 0x464, the torch the ball must reach */
    int torchFlag;  /* 0x468, the game flag raised once it is lit */
} ActSt04A;         /* derived name */

/* .data: each action's mail pair, the check handler stored into its first
   entry at run time, and the matrix finishCallBackFunc writes into every
   joint. */
#ifdef VERSION_AUG6
static ActMail gate_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gate_open_mail[2] = {{393}, {392}}; /* derived name */
#else
static ActMail gate_mail[2] = {{397}, {396}}; /* derived name */

static ActMail gate_open_mail[2] = {{397}, {396}}; /* derived name */
#endif
#else
static void actConte09_3_demoCancel(GObj *volatile self);
static void actSt04aGateLSub(GObj *volatile self);
static void actSt04aGateRSub(GObj *volatile self);
static void actSt04aModelOffChk(GObj *volatile self);
static void actSt04aModelOnChk(GObj *volatile self);
static void finishCallBackFunc(struct GObj *obj);

/* this file's own view of Act (the shared one is in typedef.h) */
typedef struct ActSt04A { /* field names derived */
    char pad0[32];        /* 0x00 */
    ActStatus flags20;    /* 0x20 */
    char pad28[12];       /* 0x28 */
    int actMode;          /* 0x34, the current action mode */
    char pad38[152];      /* 0x38 */
    ActMail *mainMail;    /* 0xD0 */
    ActMail *mail;        /* 0xD4 */
    char padD8[920];      /* 0xD8 */
    int torchAnim;        /* 0x470, the stage animation the lit torch plays */
    GObj *torchObj;       /* 0x474, the torch the ball must reach */
    int torchFlag;        /* 0x478, the game flag raised once it is lit */
} ActSt04A;               /* derived name */

/* this file's own view of GObj (the shared one is in typedef.h) */
typedef struct PObjGObjSt04A { /* field names derived */
    char pad00[348];           /* 0x000 */
    Sub15C *dobj;              /* 0x15C */
    char pad160[4];            /* 0x160 */
    ActSt04A *act;             /* 0x164 */
    char pad168[4];            /* 0x168 */
    int active;                /* 0x16C */
} PObjGObjSt04A;               /* derived name */

/* .data, ahead of model_on and model_off: each action's mail pair, the check
   handler stored into its first entry at run time, and the matrix
   finishCallBackFunc writes into every joint. */
static ActMail gate_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_open_mail[2] = {{430}, {429}}; /* derived name */
#endif

static Mtx44 jointMtxInit = {{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                              1.0f, 0.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#ifdef VERSION_AUG6
static ActMail gate_open2_ready_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gate_open2_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gate_open3_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gate_l_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gate_r_mail[2] = {{393}, {392}}; /* derived name */

static ActMail torch1_mail[2] = {{393}, {392}}; /* derived name */

static ActMail girl_sit_mail[2] = {{393}, {392}}; /* derived name */
#else
static ActMail gate_open2_ready_mail[2] = {{397}, {396}}; /* derived name */

static ActMail gate_open2_mail[2] = {{397}, {396}}; /* derived name */

static ActMail gate_open3_mail[2] = {{397}, {396}}; /* derived name */

static ActMail gate_l_mail[2] = {{397}, {396}}; /* derived name */

static ActMail gate_r_mail[2] = {{397}, {396}}; /* derived name */

static ActMail torch1_mail[2] = {{397}, {396}}; /* derived name */

static ActMail girl_sit_mail[2] = {{397}, {396}}; /* derived name */
#endif

typedef struct AnimList26 { /* field names derived */
    int v[26];
} AnimList26; /* derived name */

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

/* .sdata: the first and the second gate's stream handles */
SqEntry *gate1st = 0;

SqEntry *gate1 = 0;

/* .sbss: the demo's own end flag, raised by the subthread the wait loops below
   spin for. */
static int demoEnd;

void actSt04aGate(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    scpSearchGobj(548)->active = 0;

    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(521), 10.0f, 0.01f, 1.0f);
#else
    MallocStreamMotionBuffer();

    scpSearchGobj(549)->active = 0;

#endif
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(522), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(523), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(524), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(525), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(526), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(527), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(528), 10.0f, 0.01f, 1.0f);
#ifndef VERSION_AUG6
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(529), 10.0f, 0.01f, 1.0f);
#endif

    if (gflagChk(123) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);

#ifdef VERSION_AUG6
        stage_SetLoopFlag(483, 0);

        stage_SetAnimation(237, 0, 0);
        stage_SetAnimation(240, 0, 0);

        gflagOff(356);
#else
        stage_SetLoopFlag(484, 0);

        stage_SetAnimation(238, 0, 0);
        stage_SetAnimation(241, 0, 0);

        gflagOff(357);
#endif

        gate_mail[0].func = actSt04aGateChk;
        act->mail = gate_mail;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetLoopFlag(483, 0);

        stage_SetAnimation(237, 0, -1);
        stage_SetAnimation(240, 0, 0);
#else
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetLoopFlag(484, 0);

        stage_SetAnimation(238, 0, -1);
        stage_SetAnimation(241, 0, 0);
#endif
    }
}

void actSt04aGateChk(GObj *volatile self)
{
    GProc *th0;
    GProc *th1;
    GProc *th2;
    int i;
    int n;

#ifndef VERSION_AUG6
    stgmgrNextStagePreLoadForceStageSet(0);
#endif

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, boyGObj, 3000.0f) == 0) {
        _ACTWait(1);
    }

    th0 = actCreateSubThread(actSt04aEnvSe, 21);

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);

    scpDispOffAllWithKind(19);

    scpPlayMot(boyGObj, 0);

    StandbyStreamMotion(streamMotion[1].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", ++i);
        _ACTWait(1);
    }

#ifndef VERSION_AUG6
    DisableStreamMotionManagerAutomaticDelete();
#endif

    SetWindManager(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 5.0f, 0.0f);

    scpPlayStart(girlGObj);

    reg_SetScissorSw(1);

    SetStaticBlur(0);

    scpAdpcmPlayRequestFunc(22, &gate1st, 1, 1, 0);
    while (gate1st == 0) {
        _ACTWait(1);
    }

    gflagOn(123);

    _ACTWait(1);

    th1 = actCreateSubThread(actSt04aConte06, 21);
    th2 = actCreateSubThread(actSt04aConte06Jimaku, 21);

#ifdef VERSION_AUG6
    stage_SetAnimation(237, 1, 0);

    scpSearchGobj(548)->active = 1;
#else
    stage_SetAnimation(238, 1, 0);

    scpSearchGobj(549)->active = 1;
#endif

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
#ifdef VERSION_AUG6
    EntryStreamMotion(scpSearchGobj(548));
#else
    EntryStreamMotion(scpSearchGobj(549));
#endif

    PlayStreamMotion();

    scpFadeIn(6.0f);

    _ACTWait((int)((60 - systemStatus[0] * 10) / systemStatus[1] * 2.5));

    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    n = demoEnd ^ 1;

    if (n != 0) {
        scpAdpcmFadeClose(gate1st, 192);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    DeleteStreamMotionManager();

    iosPadActStopAll();

    iosThreadSetPri(&th1->thread, 34);
    iosThreadSetPri(&th2->thread, 34);
    iosThreadSetPri(&th0->thread, 34);

    if (n != 0) {
        {
            /* the gate-open animations, in the order they start */
            static const AnimList26 gateOpenAnims = {
#ifdef VERSION_AUG6
                {576, 577, 578, 579, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589,
                 590, 591, 592, 593, 594, 595, 596, 597, 598, 599, 600, 601}}; /* derived name */
#else
                {577, 578, 579, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589, 590,
                 591, 592, 593, 594, 595, 596, 597, 598, 599, 600, 601, 602}}; /* derived name */
#endif
            AnimList26 anim;
            unsigned int j;

            anim = gateOpenAnims;
            for (j = 0; j < 26; j++) {
                stage_SetAnimation(anim.v[j], 1, -1);
                _ACTWait(1);
            }
        }

        jimakuUndisp(&jimaku_msg);

#ifdef VERSION_AUG6
        stage_SetAnimation(237, 0, -1);
        stage_SetAnimation(601, 1, -1);
        stage_SetAnimation(410, -1, -2);
        stage_SetAnimation(412, -1, -2);

        scpSearchGobj(548)->active = 0;

        stage_SetLoopFlag(483, 0);
        stage_SetAnimation(483, -1, -2);
#else
        stage_SetAnimation(238, 0, -1);
        stage_SetAnimation(602, 1, -1);
        stage_SetAnimation(411, -1, -2);
        stage_SetAnimation(413, -1, -2);

        scpSearchGobj(549)->active = 0;

        stage_SetLoopFlag(484, 0);
        stage_SetAnimation(484, -1, -2);
#endif

        reg_SetScissorSw(0);

        {
            /* the boy's and the girl's root positions after the gate opens */
            static const ConstVec boyRootPos = {
                {1.635725f, -72.36407f, -1233.2648f, 0.0f}}; /* derived name */
            static const ConstVec girlRootPos = {
                {7.660961f, -88.9936f, -1293.0424f, 0.0f}}; /* derived name */
            long long p1[2];
            long long p2[2];

            p1[0] = boyRootPos.d[0];
            p1[1] = boyRootPos.d[1];
            SetDirectRootPosition(boyGObj, p1);

            p2[0] = girlRootPos.d[0];
            p2[1] = girlRootPos.d[1];
            SetDirectRootPosition(girlGObj, p2);
        }

        _ACTWait(1);

        SetCameraFlag_GamecamCutBack();

        scpFadeIn(3.0f);
    }

    {
        float dir[4];

        scpSeEnvMasterVolRate = 1.0f;

        scpPlayMot(boyGObj, 0);
        scpPlayMot(girlGObj, 514);

        sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
        scpPlayMotDir(boyGObj, dir);

        sceVu0SubVector(dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj));
        scpPlayMotDir(girlGObj, dir);
    }

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    _ACTWait(1);

#ifdef VERSION_AUG6
    iosOmSendMail(girlGObj, 59, boyGObj);
#else
    iosOmSendMail(girlGObj, 60, boyGObj);
#endif

    scpBoyControlReadDisable = 0;

    ReinitWindManager();

    lt_switch_layout(50);

    SetStaticBlur(1);

#ifndef VERSION_AUG6
    stgmgrNextStagePreLoadDistBoyMode();
#endif
}

void actSt04aConte06(GObj *volatile self)
{
#ifdef VERSION_AUG6
    stage_SetAnimation(576, 1, 0);
#else
    stage_SetAnimation(577, 1, 0);
#endif

    AdpcmPlay(gate1st->stream);

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(576, 577) == 0) {
        _ACTWait(1);
    }
#endif
    while (stage_ContinueAnimation(577, 578) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(578, 579) == 0) {
#ifndef VERSION_AUG6
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(579, 580) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(240);

    gate_yure_low = iosPadActRequest(boyPad, 9);
    gate_yure_low_vol = 64;
    iosPadActVolumeSet(gate_yure_low, 64);

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(579, 580) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(580, 581) == 0) {
#else
    while (stage_ContinueAnimation(580, 581) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(581, 582) == 0) {
#endif
        _ACTWait(1);
    }

    reg_SetScissorSw(0);

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(581, 582) == 0) {
        _ACTWait(1);
    }
#endif
    while (stage_ContinueAnimation(582, 583) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(583, 584) == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_AUG6

    stage_SetAnimation(410, 1, 0);
#else
    while (stage_ContinueAnimation(584, 585) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(411, 1, 0);
#endif

    iosPadActRequest(boyPad, 15);

#ifdef VERSION_AUG6
    stage_SetLoopFlag(483, 1);
    stage_SetAnimation(483, 1, 0);

    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(47, 0, 483, 0);
#else
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(47, 0, 484, 0);

    stage_SetLoopFlag(484, 1);
    stage_SetAnimation(484, 1, 0);
#endif

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(584, 585) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(585, 586) == 0) {
#else
    while (stage_ContinueAnimation(585, 586) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(586, 587) == 0) {
#endif
        _ACTWait(1);
    }

    iosPadActStop(gate_yure_low);

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(586, 150, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(587, 150, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(586, 587) == 0) {
        _ACTWait(1);
    }
#endif
    while (stage_ContinueAnimation(587, 588) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(588, 589) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(589, 590) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(590, 591) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(591, 592) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(592, 593) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(593, 594) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(594, 595) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(595, 596) == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_AUG6
    _ACTWait(120);

    stage_SetAnimation(412, 1, 0);

    iosPadActRequest(boyPad, 15);
#endif
    while (stage_ContinueAnimation(596, 597) == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpSearchGobj(548)->active = 0;

    stage_SetLoopFlag(483, 0);
    stage_SetAnimation(483, -1, -2);
#else
    _ACTWait(120);

    stage_SetAnimation(413, 1, 0);

    iosPadActRequest(boyPad, 15);
#endif

    while (stage_ContinueAnimation(597, 598) == 0) {
        _ACTWait(1);
    }

#ifndef VERSION_AUG6
    scpSearchGobj(549)->active = 0;

    stage_SetLoopFlag(484, 0);
    stage_SetAnimation(484, -1, -2);
#endif

    while (stage_ContinueAnimation(598, 599) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(599, 600) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(600, 601) == 0) {
        _ACTWait(1);
    }
#ifndef VERSION_AUG6
    while (stage_ContinueAnimation(601, 602) == 0) {
        _ACTWait(1);
    }
#endif

    SetCameraFlag_LwsCutBack();

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(601) == 0) {
#else
    while (stage_CheckAnimationFinish(602) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}
#else
static ActMail gate_open2_ready_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_open2_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_open3_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_l_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_r_mail[2] = {{430}, {429}}; /* derived name */

static ActMail torch1_mail[2] = {{430}, {429}}; /* derived name */

static ActMail girl_sit_mail[2] = {{430}, {429}}; /* derived name */

static ActMail torch_hint_mail[2] = {{430}, {429}}; /* derived name */

static ActMail model_mail[2] = {{430}, {429}}; /* derived name */

void actSt04aGate(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    MallocStreamMotionBuffer();

    scpSearchGobj(590)->active = 0;

    if (gflagChk(137) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetLoopFlag(551, 0);
#else
        stage_SetLoopFlag(555, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(265, 0, 0);
        stage_SetAnimation(268, 0, 0);
#else
        stage_SetAnimation(269, 0, 0);
        stage_SetAnimation(272, 0, 0);
#endif

        gflagOff(390);

        gate_mail[0].func = actSt04aGateChk;
        act->mail = gate_mail;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetLoopFlag(551, 0);
#else
        stage_SetLoopFlag(555, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(265, 0, -1);
        stage_SetAnimation(268, 0, 0);
#else
        stage_SetAnimation(269, 0, -1);
        stage_SetAnimation(272, 0, 0);
#endif
    }
}

typedef struct AnimList28 { /* field names derived */
    int v[28];
} AnimList28; /* derived name */

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

/* .sdata: the first gate's stream handle and gate1, which no code uses.
   actSt04aConte06's "!!\n" trace follows them. */
SqEntry *gate1st = 0;

int gate1 = 0;

/* .sbss: the demo's own end flag, raised by the subthread the wait loops below
   spin for, and a running flag set for the length of the conte09_3 cutscene
   that nothing reads back. */
static int demoEnd;

static int conte09_3Running; /* derived name */

void actSt04aGateChk(GObj *volatile self)
{
    GProc *th0;
    GProc *th1;
    GProc *th2;
    int i;
    int n;

    stgmgrNextStagePreLoadForceStageSet(0);

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, boyGObj, 3000.0f) == 0) {
        _ACTWait(1);
    }

    th0 = actCreateSubThread(actSt04aEnvSe, 21);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);

    scpDispOffAllWithKind(19);

    scpPlayMot(boyGObj, 0);

    StandbyStreamMotion(streamMotion[1].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", ++i);
        _ACTWait(1);
    }

    DisableStreamMotionManagerAutomaticDelete();

    scpPlayStart(girlGObj);

    reg_SetScissorSw(1);

    SetStaticBlur(0);

    scpAdpcmPlayRequestFunc(23, &gate1st, 1, 1, 0);
    while (gate1st == 0) {
        _ACTWait(1);
    }

    gflagOn(137);

    _ACTWait(1);

    th1 = actCreateSubThread(actSt04aConte06, 21);
    th2 = actCreateSubThread(actSt04aConte06Jimaku, 21);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(265, 1, 0);
#else
    stage_SetAnimation(269, 1, 0);
#endif

    scpSearchGobj(590)->active = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion(scpSearchGobj(590));

    PlayStreamMotion();

    scpFadeIn(6.0f);

    _ACTWait((int)((60 - systemStatus[0] * 10) / systemStatus[1] * 2.5));

    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    n = demoEnd ^ 1;

    if (n != 0) {
        scpAdpcmFadeCloseFunc(&gate1st, 192);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    DeleteStreamMotionManager();

    iosPadActStopAll();

    iosThreadSetPri(&th1->thread, 34);
    iosThreadSetPri(&th2->thread, 34);
    iosThreadSetPri(&th0->thread, 34);

    if (n != 0) {
        {
            /* the gate-open animations, in the order they start */
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            static const AnimList28 gateOpenAnims = {{551, 485, 644, 645, 646, 647, 648, 649,
                                                      650, 651, 652, 653, 654, 655, 656, 657,
                                                      658, 659, 660, 661, 662, 663, 664, 665,
                                                      666, 667, 668, 669}}; /* derived name */
#else
            static const AnimList28 gateOpenAnims = {{555, 489, 648, 649, 650, 651, 652, 653,
                                                      654, 655, 656, 657, 658, 659, 660, 661,
                                                      662, 663, 664, 665, 666, 667, 668, 669,
                                                      670, 671, 672, 673}}; /* derived name */
#endif
            AnimList28 anim;
            unsigned int j;

            anim = gateOpenAnims;
            for (j = 0; j < 28; j++) {
                stage_SetAnimation(anim.v[j], 1, -1);
                _ACTWait(1);
            }
        }

        jimakuUndisp(&jimaku_msg);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(265, 0, -1);
        stage_SetAnimation(669, 1, -1);
        stage_SetAnimation(471, -1, -2);
        stage_SetAnimation(473, -1, -2);
#else
        stage_SetAnimation(269, 0, -1);
        stage_SetAnimation(673, 1, -1);
        stage_SetAnimation(475, -1, -2);
        stage_SetAnimation(477, -1, -2);
#endif

        scpSearchGobj(590)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetLoopFlag(551, 0);
        stage_SetAnimation(551, -1, -2);
#else
        stage_SetLoopFlag(555, 0);
        stage_SetAnimation(555, -1, -2);
#endif

        reg_SetScissorSw(0);

        {
            /* the boy's and the girl's root positions after the gate opens */
            static const ConstVec boyRootPos = {
                {1.635725f, -72.36407f, -1233.2648f, 0.0f}}; /* derived name */
            static const ConstVec girlRootPos = {
                {7.660961f, -88.9936f, -1293.0424f, 0.0f}}; /* derived name */
            long long p1[2];
            long long p2[2];

            p1[0] = boyRootPos.d[0];
            p1[1] = boyRootPos.d[1];
            SetDirectRootPosition(boyGObj, p1);

            p2[0] = girlRootPos.d[0];
            p2[1] = girlRootPos.d[1];
            SetDirectRootPosition(girlGObj, p2);
        }

        _ACTWait(1);

        SetCameraFlag_GamecamCutBack();

        scpFadeIn(3.0f);
    }

    {
        float dir[4];

        scpSeEnvMasterVolRate = 1.0f;

        scpPlayMot(boyGObj, 0);
        scpPlayMot(girlGObj, 532);

        GOBJ_SUB(boyGObj)->ctrl.blendFrames =
            (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f * 0.0f);
        GOBJ_SUB(girlGObj)->ctrl.blendFrames =
            (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f * 0.0f);

        sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
        scpPlayMotDir(boyGObj, dir);

        sceVu0SubVector(dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj));
        scpPlayMotDir(girlGObj, dir);
    }

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    _ACTWait(1);

    iosOmSendMail(girlGObj, 63, boyGObj);

    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    SetStaticBlur(1);

    gflagOn(155);

    stgmgrNextStagePreLoadDistBoyMode();
}

void actSt04aConte06(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(644, 1, 0);
#else
    stage_SetAnimation(648, 1, 0);
#endif

    AdpcmPlay(gate1st->stream);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(644, 645) == 0) {
#else
    while (stage_ContinueAnimation(648, 649) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(645, 646) == 0) {
#else
    while (stage_ContinueAnimation(649, 650) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(646, 647) == 0) {
#else
    while (stage_ContinueAnimation(650, 651) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(240);

    gate_yure_low = iosPadActRequest(boyPad, 9);
    gate_yure_low_vol = 64;
    iosPadActVolumeSet(gate_yure_low, 64);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(647, 648) == 0) {
#else
    while (stage_ContinueAnimation(651, 652) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(648, 649) == 0) {
#else
    while (stage_ContinueAnimation(652, 653) == 0) {
#endif
        _ACTWait(1);
    }

    reg_SetScissorSw(0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(649, 650) == 0) {
#else
    while (stage_ContinueAnimation(653, 654) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(650, 651) == 0) {
#else
    while (stage_ContinueAnimation(654, 655) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(651, 652) == 0) {
#else
    while (stage_ContinueAnimation(655, 656) == 0) {
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(471, 1, 0);
#else
    stage_SetAnimation(475, 1, 0);
#endif

    iosPadActRequest(boyPad, 15);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(48, 0, 551, 0);
#else
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(48, 0, 555, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetLoopFlag(551, 1);
    stage_SetAnimation(551, 1, 0);
#else
    stage_SetLoopFlag(555, 1);
    stage_SetAnimation(555, 1, 0);
#endif

    debug_StdPrintfDummy("!!\n");

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(485, 1, 0);
#else
    stage_SetAnimation(489, 1, 0);
#endif

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(652, 653) == 0) {
#else
    while (stage_ContinueAnimation(656, 657) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(653, 654) == 0) {
#else
    while (stage_ContinueAnimation(657, 658) == 0) {
#endif
        _ACTWait(1);
    }

    iosPadActStop(gate_yure_low);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(654, 150, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(658, 150, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(654, 655) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(655, 656) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(656, 657) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(657, 658) == 0) {
        _ACTWait(1);
    }
#endif
    while (stage_ContinueAnimation(658, 659) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(659, 660) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(660, 661) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(661, 662) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(662, 663) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(663, 664) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)

    _ACTWait(120);

    stage_SetAnimation(473, 1, 0);

    iosPadActRequest(boyPad, 15);

#endif
    while (stage_ContinueAnimation(664, 665) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)

    scpSearchGobj(590)->active = 0;

    stage_SetLoopFlag(551, 0);
    stage_SetAnimation(551, -1, -2);

#endif
    while (stage_ContinueAnimation(665, 666) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(666, 667) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(667, 668) == 0) {
        _ACTWait(1);
    }
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)

    _ACTWait(120);

    stage_SetAnimation(477, 1, 0);

    iosPadActRequest(boyPad, 15);

#endif
    while (stage_ContinueAnimation(668, 669) == 0) {
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
        _ACTWait(1);
    }

    scpSearchGobj(590)->active = 0;

    stage_SetLoopFlag(555, 0);
    stage_SetAnimation(555, -1, -2);

    while (stage_ContinueAnimation(669, 670) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(670, 671) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(671, 672) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(672, 673) == 0) {
#endif
        _ACTWait(1);
    }

    SetCameraFlag_LwsCutBack();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(669) == 0) {
#else
    while (stage_CheckAnimationFinish(673) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

/* .sdata, after actSt04aConte06's trace: the gate and torch stream handles,
   then the pad shakes and their volumes (declared in st04a.h for
   actSt04aConte06). */
static SqEntry *gate_open = 0; /* derived name */
#endif
#endif

static SqEntry *gate_open2 = 0; /* derived name */

static SqEntry *conte09_2 = 0; /* derived name */

#ifndef VERSION_JUN26
SqEntry *gate_ready_l = 0;

SqEntry *gate_ready_r = 0;
#endif

SqEntry *torch = 0;

int gate_yure_low = 0;

unsigned char gate_yure_low_vol = 0;

int yure1 = 0;

unsigned char vol1 = 0;

#ifdef VERSION_JUN26
void actSt04aConte06Jimaku(GObj *volatile self)
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
        case 250:
            jimaku_msg.sub.block = 25;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1400:
            jimaku_msg.sub.block = 26;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2380:
            jimaku_msg.sub.block = 31;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2861:
            jimaku_msg.sub.block = 34;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3160:
            jimaku_msg.sub.block = 35;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3460:
            jimaku_msg.sub.block = 36;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3760:
            jimaku_msg.sub.block = 37;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 4180:
            jimaku_msg.sub.block = 38;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 4800:
            jimaku_msg.sub.block = 43;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 5576:
            jimaku_msg.sub.block = 27;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6080:
            jimaku_msg.sub.block = 29;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6740:
            jimaku_msg.sub.block = 48;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6980:
            jimaku_msg.sub.block = 49;
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
    } while (t < 7300.0f);
}

void actSt04aGateOpen(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(119) == 0) {
        stage_SetAnimation(213, 0, 0);

        scpSearchGobj(599)->active = 0;

        gate_open_mail[0].func = actSt04aGateOpenChk;
        act->mail = gate_open_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        SetWayGroupActive(2, 1);

        stage_SetAnimation(213, 0, -1);
        stage_SetAnimation(215, 0, -1);
        stage_SetAnimation(217, 0, -1);

        scpSearchGobj(599)->active = 0;
    }
}

void actSt04aGateOpenChk(GObj *volatile self)
{
    int i;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (1) {
        if ((scpTriggerBall(self, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(self, girlGObj, 200.0f) != 0 && gflagChk(148) != 0 &&
             gflagChk(209) != 0) ||
            (scpTriggerBall(self, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(self, girlGObj, 200.0f) != 0)) {
            break;
        }
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;

    StandbyStreamMotion(streamMotion[2].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(33, &gate_open, 1, 1, 1);
    while (gate_open == 0) {
        _ACTWait(1);
    }

    scpDispOffAllWithKind(19);

    actCreateSubThread(actConte09, 21);
    actCreateSubThread(actConte09Jimaku, 21);
}

static const ConstVec liftOfs1 = {{0.0f, 0.0f, 6000.0f, 1.0f}}; /* derived name */

static const ConstVec liftOfs2 = {{-5000.0f, 0.0f, 5300.0f, 1.0f}}; /* derived name */

void actConte09(GObj *volatile self)
{
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);

    PlayStreamMotion();

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    stage_SetAnimation(591, 1, 0);

    while (stage_ContinueAnimation(591, 592) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(592, 593) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(220, 1, 0);

    while (stage_ContinueAnimation(593, 594) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(594, 595) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(213, 1, 0);

    while (stage_ContinueAnimation(595, 596) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(596, 597) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(597, 598) == 0) {
        _ACTWait(1);
    }

    _ACTWait(300);

    stage_SetAnimation(217, 1, 0);

    _ACTWait(120);

    yure1 = iosPadActRequest(boyPad, 10);
    vol1 = 128;
    iosPadActVolumeSet(yure1, 128);

    while (stage_ContinueAnimation(598, 599) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(215, 1, 0);

    while (stage_ContinueAnimation(599, 600) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(yure1);

    while (stage_ContinueAnimation(600, 601) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(601, 602) == 0) {
        _ACTWait(1);
    }

    scpDispOnAllWithKind(19);

    gflagOn(119);

    while (stage_ContinueAnimation(602, 603) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFinish(603) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);

    _ACTWait(1);

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    SetWayGroupActive(2, 1);
}
#else
int yure2 = 0;

unsigned char vol2 = 0;

void actSt04aConte06Jimaku(GObj *volatile self)
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
        case 250:
            jimaku_msg.sub.block = 25;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1380:
            jimaku_msg.sub.block = 26;
            jimaku_msg.sub.jump = 60;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2380:
            jimaku_msg.sub.block = 31;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2861:
            jimaku_msg.sub.block = 34;
            jimaku_msg.sub.jump = 150;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3160:
            jimaku_msg.sub.block = 35;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3460:
            jimaku_msg.sub.block = 36;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3760:
            jimaku_msg.sub.block = 37;
            jimaku_msg.sub.jump = 174;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 4180:
            jimaku_msg.sub.block = 38;
            jimaku_msg.sub.jump = 174;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 4800:
            jimaku_msg.sub.block = 43;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 5580:
            jimaku_msg.sub.block = 27;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6050:
            jimaku_msg.sub.block = 29;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6740:
            jimaku_msg.sub.block = 48;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6980:
            jimaku_msg.sub.block = 49;
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
    } while (t < 7300.0f);
    _ACTWait(0);
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#ifdef VERSION_AUG6
void actSt04aGateOpen(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(126) == 0) {
        stage_SetAnimation(238, 0, 0);

        scpSearchGobj(624)->active = 0;

        gate_open_mail[0].func = actSt04aGateOpenChk;
        act->mail = gate_open_mail;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        SetWayGroupActive(2, 1);

        stage_SetAnimation(238, 0, -1);
        stage_SetAnimation(240, 0, -1);
        stage_SetAnimation(242, 0, -1);

        scpSearchGobj(624)->active = 0;
    }
}
#else
void actSt04aGateOpen(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    MallocStreamMotionBuffer();

    if (gflagChk(126) == 0) {
        stage_SetAnimation(239, 0, 0);

        scpSearchGobj(625)->active = 0;

        gate_open_mail[0].func = actSt04aGateOpenChk;
        act->mail = gate_open_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        SetWayGroupActive(2, 1);

        stage_SetAnimation(239, 0, -1);
        stage_SetAnimation(241, 0, -1);
        stage_SetAnimation(243, 0, -1);

        scpSearchGobj(625)->active = 0;
    }
}
#endif
#else
void actSt04aGateOpen(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    MallocStreamMotionBuffer();

    if (gflagChk(140) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(266, 0, 0);
#else
        stage_SetAnimation(270, 0, 0);
#endif

        scpSearchGobj(669)->active = 0;

        gate_open_mail[0].func = actSt04aGateOpenChk;
        act->mail = gate_open_mail;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(2, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(266, 0, -1);
        stage_SetAnimation(268, 0, -1);
        stage_SetAnimation(271, 0, -1);
#else
        stage_SetAnimation(270, 0, -1);
        stage_SetAnimation(272, 0, -1);
        stage_SetAnimation(275, 0, -1);
#endif

        scpSearchGobj(669)->active = 0;

        SetGirlHairDispSwitch(girlGObj, 1);
    }
}
#endif

typedef struct AnimList { /* field names derived */
    int v[13];
} AnimList; /* derived name */

/* .rodata, used here and by actConte09_2: the first lift offset, declared
   ahead and defined with the second after actSt04aGateOpenChk. */
static const ConstVec liftOfs1;

#ifdef VERSION_NTSC
void actSt04aGateOpenChk(GObj *volatile self)
{
    GProc *th1;
    GProc *th2;
    GProc *th3;
    int i;
    int n;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (1) {
        if ((GOBJ_ACT(girlGObj)->actMode != 107 && scpTriggerBall(self, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(self, girlGObj, 200.0f) != 0 && gflagChk(155) != 0 &&
             gflagChk(218) != 0) ||
            (GOBJ_ACT(girlGObj)->actMode != 107 && scpTriggerBall(self, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(self, girlGObj, 200.0f) != 0)) {
            break;
        }
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;

    scpSleepEnemyAll();

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpPlayMot(girlGObj, 514);

    StandbyStreamMotion(streamMotion[2].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(30, &gate1, 1, 1, 1);
    while (gate1 == 0) {
        _ACTWait(1);
    }

    scpDisActivateAllWithKind(19);

    th1 = actCreateSubThread(actConte09, 21);
    th2 = actCreateSubThread(actSt04aEnvSeWakare1, 21);
    th3 = actCreateSubThread(actConte09Jimaku, 21);

    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    n = demoEnd ^ 1;

    if (n != 0) {
        scpAdpcmFadeClose(gate1, 192);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    DeleteStreamMotionManager();

    iosPadActStopAll();

    iosThreadSetPri(&th1->thread, 34);
    iosThreadSetPri(&th3->thread, 34);
    iosThreadSetPri(&th2->thread, 34);

    if (n != 0) {
        {
            /* the second gate's animations, in the order they start */
            static const AnimList gateOpen2Anims = {{641, 642, 643, 644, 645, 646, 647, 648, 649,
                                                     650, 651, 652, 653}}; /* derived name */
            AnimList anim;
            unsigned int j;

            anim = gateOpen2Anims;
            for (j = 0; j < 13; j++) {
                stage_SetAnimation(anim.v[j], 1, -1);
                _ACTWait(1);
            }
        }

        jimakuUndisp(&jimaku_msg);

        stage_SetAnimation(653, 1, -1);
        stage_SetAnimation(243, 0, -1);
        stage_SetAnimation(241, 0, -1);
        stage_SetAnimation(247, 0, -1);
        stage_SetAnimation(239, 0, -1);

        scpKillEnemyAll();

        scpDispOnAllWithKind(19);

        gflagOn(126);

        {
            /* the boy's and the girl's root positions after the second gate */
            static const ConstVec boyRootPos2 = {
                {29.91216f, -71.98232f, -118.11676f, 0.0f}}; /* derived name */
            static const ConstVec girlRootPos2 = {
                {-49.44171f, -76.71414f, -142.27318f, 0.0f}}; /* derived name */
            long long p1[2];
            long long p2[2];

            p1[0] = boyRootPos2.d[0];
            p1[1] = boyRootPos2.d[1];
            SetDirectRootPosition(boyGObj, p1);

            p2[0] = girlRootPos2.d[0];
            p2[1] = girlRootPos2.d[1];
            SetDirectRootPosition(girlGObj, p2);
        }

        _ACTWait(1);

        SetCameraFlag_GamecamCutBack();

        scpFadeIn(3.0f);
    }

    {
        long long ofs[2];
        float dir[4];

        scpSeEnvMasterVolRate = 1.0f;

        scpPlayMot(boyGObj, 0);

        ofs[0] = liftOfs1.d[0];
        ofs[1] = liftOfs1.d[1];
        sceVu0SubVector(dir, ofs, test_CURRENTROOT(girlGObj));
        scpPlayMotDir(girlGObj, dir);
    }

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    SetWayGroupActive(2, 1);
}
#else
void actSt04aGateOpenChk(GObj *volatile self)
{
    GProc *th1;
    GProc *th2;
    GProc *th3;
    int i;
    int n;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (1) {
#ifdef VERSION_AUG6
        if ((GOBJ_ACT(girlGObj)->actMode != 107 && scpTriggerBall(self, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(self, girlGObj, 200.0f) != 0 && gflagChk(155) != 0 &&
             gflagChk(218) != 0) ||
            (GOBJ_ACT(girlGObj)->actMode != 107 && scpTriggerBall(self, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(self, girlGObj, 200.0f) != 0)) {
#else
        if ((GOBJ_ACT(girlGObj)->actMode != 111 && scpTriggerBall(self, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(self, girlGObj, 200.0f) != 0 && gflagChk(174) != 0 &&
             gflagChk(243) != 0) ||
            (GOBJ_ACT(girlGObj)->actMode != 111 && scpTriggerBall(self, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(self, girlGObj, 200.0f) != 0)) {
#endif
            break;
        }
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    scpBoyControlReadDisable = 1;

    scpPlayStart(girlGObj);
#endif

    scpSleepEnemyAll();

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 514);
#else
    scpPlayMot(girlGObj, 532);
#endif

    StandbyStreamMotion(streamMotion[2].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(30, &gate1, 1, 1, 1);
    while (gate1 == 0) {
#else
    scpAdpcmPlayRequestFunc(31, &gate_open, 1, 1, 1);
    while (gate_open == 0) {
#endif
        _ACTWait(1);
    }

    scpDisActivateAllWithKind(19);

    th1 = actCreateSubThread(actConte09, 21);
    th2 = actCreateSubThread(actSt04aEnvSeWakare1, 21);
    th3 = actCreateSubThread(actConte09Jimaku, 21);

    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    n = demoEnd ^ 1;

    if (n != 0) {
#ifdef VERSION_AUG6
        scpAdpcmFadeClose(gate1, 192);
#else
        scpAdpcmFadeCloseFunc(&gate_open, 192);
#endif

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    DeleteStreamMotionManager();

    iosPadActStopAll();

    iosThreadSetPri(&th1->thread, 34);
    iosThreadSetPri(&th3->thread, 34);
    iosThreadSetPri(&th2->thread, 34);

    if (n != 0) {
        {
            /* the second gate's animations, in the order they start */
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            static const AnimList gateOpen2Anims = {{708, 709, 710, 711, 712, 713, 714, 715, 716,
                                                     717, 718, 719, 720}}; /* derived name */
#else
#ifdef VERSION_AUG6
            static const AnimList gateOpen2Anims = {{640, 641, 642, 643, 644, 645, 646, 647, 648,
                                                     649, 650, 651, 652}}; /* derived name */
#else
            static const AnimList gateOpen2Anims = {{712, 713, 714, 715, 716, 717, 718, 719, 720,
                                                     721, 722, 723, 724}}; /* derived name */
#endif
#endif
            AnimList anim;
            unsigned int j;

            anim = gateOpen2Anims;
            for (j = 0; j < 13; j++) {
                stage_SetAnimation(anim.v[j], 1, -1);
                _ACTWait(1);
            }
        }

        jimakuUndisp(&jimaku_msg);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(720, 1, -1);
        stage_SetAnimation(271, 0, -1);
        stage_SetAnimation(268, 0, -1);
        stage_SetAnimation(276, 0, -1);
        stage_SetAnimation(266, 0, -1);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(652, 1, -1);
        stage_SetAnimation(242, 0, -1);
        stage_SetAnimation(240, 0, -1);
        stage_SetAnimation(246, 0, -1);
        stage_SetAnimation(238, 0, -1);
#else
        stage_SetAnimation(724, 1, -1);
        stage_SetAnimation(275, 0, -1);
        stage_SetAnimation(272, 0, -1);
        stage_SetAnimation(280, 0, -1);
        stage_SetAnimation(270, 0, -1);
#endif
#endif

        scpKillEnemyAll();

        scpDispOnAllWithKind(19);

#ifdef VERSION_AUG6
        gflagOn(126);
#else
        gflagOn(140);

        SetGirlHairDispSwitch(girlGObj, 1);
#endif

        {
            /* the boy's and the girl's root positions after the second gate */
            static const ConstVec boyRootPos2 = {
                {29.91216f, -71.98232f, -118.11676f, 0.0f}}; /* derived name */
            static const ConstVec girlRootPos2 = {
                {-49.44171f, -76.71414f, -142.27318f, 0.0f}}; /* derived name */
            long long p1[2];
            long long p2[2];

            p1[0] = boyRootPos2.d[0];
            p1[1] = boyRootPos2.d[1];
            SetDirectRootPosition(boyGObj, p1);

            p2[0] = girlRootPos2.d[0];
            p2[1] = girlRootPos2.d[1];
            SetDirectRootPosition(girlGObj, p2);
        }

        _ACTWait(1);

        SetCameraFlag_GamecamCutBack();

        scpFadeIn(3.0f);
    }

    {
        long long ofs[2];
        float dir[4];

        scpSeEnvMasterVolRate = 1.0f;

#ifndef VERSION_AUG6
        scpPlayStart(boyGObj);
#endif

        scpPlayMot(boyGObj, 0);

        ofs[0] = liftOfs1.d[0];
        ofs[1] = liftOfs1.d[1];
        sceVu0SubVector(dir, ofs, test_CURRENTROOT(girlGObj));
        scpPlayMotDir(girlGObj, dir);
    }

#ifndef VERSION_AUG6
    _ACTWait(1);
#endif

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    scpBoyControlReadDisable = 0;

#ifdef VERSION_AUG6
    lt_switch_layout(50);

    SetWayGroupActive(2, 1);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    SetWayGroupActive(2, 1);

    scpSearchGobj(648)->active = 0;
#endif
}
#endif

static const ConstVec liftOfs1 = {{0.0f, 0.0f, 6000.0f, 1.0f}}; /* derived name */

static const ConstVec liftOfs2 = {{-5000.0f, 0.0f, 5300.0f, 1.0f}}; /* derived name */

#ifdef VERSION_NTSC
void actConte09(GObj *volatile self)
{
    int th1;
    int th2;

    th1 = EntryStreamMotion(boyGObj);
    th2 = EntryStreamMotion(girlGObj);

    SetStreamMotionFinishCallBackFunc(th1, finishCallBackFunc);
    SetStreamMotionFinishCallBackFunc(th2, finishCallBackFunc);

    PlayStreamMotion();

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    stage_SetAnimation(641, 1, 0);

    while (stage_ContinueAnimation(641, 642) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(642, 643) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(247, 1, 0);

    while (stage_CheckAnimationFrame(643, 125, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 15);

    scpKillEnemyAll();

    while (stage_ContinueAnimation(643, 644) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(644, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(644, 645) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(239, 1, 0);

    while (stage_ContinueAnimation(645, 646) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(646, 647) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(647, 648) == 0) {
        _ACTWait(1);
    }

    _ACTWait(300);

    stage_SetAnimation(243, 1, 0);

    _ACTWait(120);

    yure1 = iosPadActRequest(boyPad, 10);
    vol1 = 128;
    iosPadActVolumeSet(yure1, 128);

    while (stage_ContinueAnimation(648, 649) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(241, 1, 0);

    while (stage_ContinueAnimation(649, 650) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(yure1);

    while (stage_ContinueAnimation(650, 651) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(651, 652) == 0) {
        _ACTWait(1);
    }

    scpDispOnAllWithKind(19);

    gflagOn(126);

    while (stage_ContinueAnimation(652, 653) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFinish(653) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    GOBJ_SUB(boyGObj)->ctrl.blendFrames =
        (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f * 0.0f);
    GOBJ_SUB(girlGObj)->ctrl.blendFrames =
        (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f * 0.0f);

    demoEnd = 1;

    _ACTWait(0);
}
#else
void actConte09(GObj *volatile self)
{
    int th1;
    int th2;

    th1 = EntryStreamMotion(boyGObj);
    th2 = EntryStreamMotion(girlGObj);

    SetStreamMotionFinishCallBackFunc(th1, finishCallBackFunc);
    SetStreamMotionFinishCallBackFunc(th2, finishCallBackFunc);

    PlayStreamMotion();

#ifdef VERSION_AUG6
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    stage_SetAnimation(640, 1, 0);

    while (stage_ContinueAnimation(640, 641) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(641, 642) == 0) {
#else
    scpPlayMot(boyGObj, 0);

    scpSearchGobj(648)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(708, 1, 0);
#else
    stage_SetAnimation(712, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(708, 709) == 0) {
#else
    while (stage_ContinueAnimation(712, 713) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(709, 710) == 0) {
#else
    while (stage_ContinueAnimation(713, 714) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(246, 1, 0);

    while (stage_CheckAnimationFrame(642, 125, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(276, 1, 0);
#else
    stage_SetAnimation(280, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(710, 125, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(714, 125, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 15);

    scpKillEnemyAll();

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(642, 643) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(643, 15, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(710, 711) == 0) {
#else
    while (stage_ContinueAnimation(714, 715) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(711, 15, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(715, 15, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(711, 712) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(643, 644) == 0) {
#else
    while (stage_ContinueAnimation(715, 716) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(238, 1, 0);

    while (stage_ContinueAnimation(644, 645) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(645, 646) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(646, 647) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(266, 1, 0);
#else
    stage_SetAnimation(270, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(712, 713) == 0) {
#else
    while (stage_ContinueAnimation(716, 717) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(713, 714) == 0) {
#else
    while (stage_ContinueAnimation(717, 718) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(714, 70, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(718, 70, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    SetGirlHairDispSwitch(girlGObj, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(714, 715) == 0) {
#else
    while (stage_ContinueAnimation(718, 719) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(300);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(271, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(242, 1, 0);
#else
    stage_SetAnimation(275, 1, 0);
#endif
#endif

    _ACTWait(120);

    yure1 = iosPadActRequest(boyPad, 10);
    vol1 = 128;
    iosPadActVolumeSet(yure1, 128);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(715, 716) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(647, 648) == 0) {
#else
    while (stage_ContinueAnimation(719, 720) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(240, 1, 0);

    while (stage_ContinueAnimation(648, 649) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(268, 1, 0);
#else
    stage_SetAnimation(272, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(716, 717) == 0) {
#else
    while (stage_ContinueAnimation(720, 721) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    iosPadActStop(yure1);

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(649, 650) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(650, 651) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(717, 718) == 0) {
#else
    while (stage_ContinueAnimation(721, 722) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(718, 719) == 0) {
#else
    while (stage_ContinueAnimation(722, 723) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    scpDispOnAllWithKind(19);

#ifdef VERSION_AUG6
    gflagOn(126);

    while (stage_ContinueAnimation(651, 652) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFinish(652) == 0) {
#else
    gflagOn(140);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(719, 720) == 0) {
#else
    while (stage_ContinueAnimation(723, 724) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(720) == 0) {
#else
    while (stage_CheckAnimationFinish(724) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    GOBJ_SUB(boyGObj)->ctrl.blendFrames =
        (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f * 0.0f);
    GOBJ_SUB(girlGObj)->ctrl.blendFrames =
        (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f * 0.0f);

    demoEnd = 1;

    _ACTWait(0);
}
#endif
#endif

#ifdef VERSION_JUN26
void actConte09Jimaku(GObj *volatile self)
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
        case 2161:
            jimaku_msg.sub.block = 88;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2550:
            jimaku_msg.sub.block = 86;
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
    } while (t < 2700.0f);
}

void actConte09_2(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];
    int i;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);

    PlayStreamMotion();

    stage_SetAnimation(604, 1, 0);
    stage_SetAnimation(221, 1, 0);

    while (stage_ContinueAnimation(604, 605) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(605, 606) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(606, 607) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(607, 608) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(608, 609) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(609, 610) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(610, 611) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(611, 612) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(612, 613) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(216, 1, 0);

    while (stage_ContinueAnimation(613, 614) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(614, 615) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(615, 616) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(616, 617) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(617, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMotReq(girlGObj, 270);

    scpPlayPosSet(girlGObj, -14.0f, 238.0f, 4843.0f);

    ofs[0] = liftOfs1.d[0];
    ofs[1] = liftOfs1.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    while (stage_CheckAnimationFinish(617) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    ofs[0] = liftOfs2.d[0];
    ofs[1] = liftOfs2.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    StandbyStreamMotion(streamMotion[4].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(35, &conte09_2, 1, 1, 0);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    gflagOn(120);
}

void actSt04aGateOpen3Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(120) == 0 || scpTriggerBall(self, boyGObj, 450.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(121);

    lt_switch_layout(51);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    if (gate_open2 != 0) {
        scpAdpcmFadeClose(gate_open2, 80);
    }

    while (conte09_2 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(conte09_2->stream);

    actCreateSubThread(actConte09_3, 21);
    actCreateSubThread(actConte09_3Jimaku, 21);
}

void actConte09_3(GObj *volatile self)
{
    scpSearchGobj(599)->active = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion(scpSearchGobj(599));

    PlayStreamMotion();

    stage_SetAnimation(618, 1, 0);

    stage_SetAnimation(216, 1, 501);

    while (stage_ContinueAnimation(618, 619) == 0) {
        _ACTWait(1);
    }

    if (scpGameStat_BoyWeaponkind() == 1) {
        stage_SetAnimation(218, 1, 0);
    }
    if (scpGameStat_BoyWeaponkind() == 4 || scpGameStat_BoyWeaponkind() == 5) {
        stage_SetAnimation(219, 1, 0);
    }

    DeleteBoyWeapon();

    while (stage_ContinueAnimation(619, 620) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(620, 621) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(621, 622) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(622, 623) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(623, 624) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(624, 625) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(625, 626) == 0) {
        _ACTWait(1);
    }

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.35f, 0.0f, -0.001f, 0.0f, -0.7f, 1);

    while (stage_ContinueAnimation(626, 627) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(627, 628) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(216, 1, 2101);

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.4f, 0.0f, -0.001f, 0.0f, -0.7f, 1);

    while (stage_ContinueAnimation(628, 629) == 0) {
        _ACTWait(1);
    }

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.5f, 0.0f, -0.001f, 0.0f, -0.7f, 1);

    while (stage_CheckAnimationFrame(629, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    while (stage_ContinueAnimation(629, 630) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(630, 631) == 0) {
        _ACTWait(1);
    }

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.55f, 0.0f, -0.001f, 0.0f, -0.7f, 1);

    while (stage_ContinueAnimation(631, 632) == 0) {
        _ACTWait(1);
    }

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.6f, 0.0f, -0.001f, 0.0f, -0.7f, 1);

    while (stage_ContinueAnimation(632, 633) == 0) {
        _ACTWait(1);
    }

    gflagOn(123);
    gflagOn(340);

    _ACTWait(120);

    RequestStageChange(3, boyGObj, 0, 16.0f, 16.0f);
}

void actSt04aGateRChk(GObj *volatile self)
{
    while (gflagChk(200) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    gflagOn(118);

    scpAdpcmPlayRequestFunc(32, 0, 1, 1, 1);

    stage_SetAnimation(235, 1, 0);
    while (stage_CheckAnimationFinish(235) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(212) != 0) {
        RequestStageChange(5, boyGObj, girlGObj, 16.0f, 16.0f);
    }
    if (gflagChk(213) != 0) {
        RequestStageChange(6, boyGObj, girlGObj, 16.0f, 16.0f);
    }
    if (gflagChk(214) != 0) {
        RequestStageChange(9, boyGObj, girlGObj, 16.0f, 16.0f);
    }
    if (gflagChk(215) != 0) {
        RequestStageChange(7, boyGObj, girlGObj, 16.0f, 16.0f);
    }
    if (gflagChk(199) != 0) {
        RequestStageChange(8, boyGObj, girlGObj, 16.0f, 16.0f);
    }
}

void actSt04aTorch1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(132) == 0) {
        if (gflagChk(124) != 0) {
            scpSearchGobj(501)->active = 0;
            stage_SetAnimation(223, 0, -1);
        }

        if (gflagChk(125) != 0) {
            scpSearchGobj(502)->active = 0;
            stage_SetAnimation(224, 0, -1);
        }

        if (gflagChk(126) != 0) {
            scpSearchGobj(503)->active = 0;
            stage_SetAnimation(225, 0, -1);
        }

        if (gflagChk(127) != 0) {
            scpSearchGobj(504)->active = 0;
            stage_SetAnimation(226, 0, -1);
        }

        if (gflagChk(128) != 0) {
            scpSearchGobj(505)->active = 0;
            stage_SetAnimation(227, 0, -1);
        }

        if (gflagChk(129) != 0) {
            scpSearchGobj(506)->active = 0;
            stage_SetAnimation(228, 0, -1);
        }

        if (gflagChk(130) != 0) {
            scpSearchGobj(507)->active = 0;
            stage_SetAnimation(229, 0, -1);
        }

        if (gflagChk(131) != 0) {
            scpSearchGobj(508)->active = 0;
            stage_SetAnimation(230, 0, -1);
        }

        torch1_mail[0].func = actSt04aTorch1Chk;
        act->mail = torch1_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(501)->active = 0;
        scpSearchGobj(502)->active = 0;
        scpSearchGobj(503)->active = 0;
        scpSearchGobj(504)->active = 0;
        scpSearchGobj(505)->active = 0;
        scpSearchGobj(506)->active = 0;
        scpSearchGobj(507)->active = 0;
        scpSearchGobj(508)->active = 0;

        stage_SetAnimation(223, 0, -1);
        stage_SetAnimation(224, 0, -1);
        stage_SetAnimation(225, 0, -1);
        stage_SetAnimation(226, 0, -1);
        stage_SetAnimation(227, 0, -1);
        stage_SetAnimation(228, 0, -1);
        stage_SetAnimation(229, 0, -1);
        stage_SetAnimation(230, 0, -1);

        scpTorchLightOn(509);
        scpTorchLightOn(510);
        scpTorchLightOn(511);
        scpTorchLightOn(512);
        scpTorchLightOn(513);
        scpTorchLightOn(514);
        scpTorchLightOn(515);
        scpTorchLightOn(516);
        scpTorchLightOn(517);
        scpTorchLightOn(518);
    }
}
#else
void actConte09Jimaku(GObj *volatile self)
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
        case 2161:
            jimaku_msg.sub.block = 88;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        case 2550:
#else
        case 2430:
#endif
            jimaku_msg.sub.block = 86;
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
    } while (t < 2700.0f);
    _ACTWait(0);
}

void actSt04aGateOpen2Chk(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 || ACTGame_FLAG_TETSUNAGI() == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_NTSC
    GOBJ_ACT(girlGObj)->flags20.ll &= ~0x40;
    scpPlayMotReq(girlGObj, 283);
#else
#ifdef VERSION_AUG6
    GOBJ_ACT(girlGObj)->flags20.ll &= ~0x8;
    scpPlayMotReq(girlGObj, 281);
#else
    GOBJ_ACT(girlGObj)->flags20.ll &= ~0x10000;
    scpPlayMotReq(girlGObj, 315);
#endif
#endif

    scpPlayMot(boyGObj, 0);

    ofs[0] = liftOfs2.d[0];
    ofs[1] = liftOfs2.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif

    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpDisActivateAllWithKind(19);

    while (gate_open2 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(gate_open2->stream);

    actCreateSubThread(actConte09_2, 21);
}

#ifdef VERSION_NTSC
void actConte09_2(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];
    int i;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);

    PlayStreamMotion();

    stage_SetAnimation(654, 1, 0);
    stage_SetAnimation(248, 1, 0);

    while (stage_ContinueAnimation(654, 655) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(655, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 15);

    while (stage_ContinueAnimation(655, 656) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(656, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(656, 657) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(657, 658) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(658, 659) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(659, 660) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(660, 661) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(661, 662) == 0) {
        _ACTWait(1);
    }

    yure2 = iosPadActRequest(boyPad, 10);
    vol2 = 128;
    iosPadActVolumeSet(yure2, 128);

    stage_SetAnimation(242, 1, 0);

    while (stage_ContinueAnimation(662, 663) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(663, 664) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(664, 665) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(665, 666) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(666, 667) == 0) {
        _ACTWait(1);
    }

    ClearStreamMotionEntry(girlGObj);

    scpPlayMotReq(girlGObj, 283);

    scpPlayPosSet(girlGObj, 14.8948f, 210.136f, 4858.48f);

    ofs[0] = liftOfs1.d[0];
    ofs[1] = liftOfs1.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    while (stage_CheckAnimationFinish(667) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(yure2);

    ofs[0] = liftOfs2.d[0];
    ofs[1] = liftOfs2.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    StandbyStreamMotion(streamMotion[4].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(32, &conte09_2, 1, 1, 0);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    gflagOn(127);
}

void actSt04aGateOpen3Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(127) == 0 || scpTriggerBall(self, boyGObj, 450.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(128);

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    if (gate_open2 != 0) {
        scpAdpcmFadeClose(gate_open2, 80);
    }

    while (conte09_2 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(conte09_2->stream);

    actCreateSubThread(actSt04aEnvSeWakare2, 21);
    actCreateSubThread(actConte09_3, 21);
    actCreateSubThread(actConte09_3Jimaku, 21);
}

void actConte09_3(GObj *volatile self)
{
    scpSearchGobj(625)->active = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion(scpSearchGobj(625));

    PlayStreamMotion();

    scpSetStreamMotionRootOffset(boyGObj, 0.0f, 0.0f, 1.0f);
    scpSetStreamMotionRootOffset(girlGObj, 0.0f, 0.0f, 1.0f);

    scpTorchLightOff(530);
    scpTorchLightOff(531);
    scpTorchLightOff(532);
    scpTorchLightOff(533);
    scpTorchLightOff(534);
    scpTorchLightOff(535);
    scpTorchLightOff(536);
    scpTorchLightOff(537);
    scpTorchLightOff(538);
    scpTorchLightOff(539);

    stage_SetAnimation(247, -1, -2);
    stage_SetAnimation(248, -1, -2);
    stage_SetAnimation(641, -1, -2);
    stage_SetAnimation(642, -1, -2);
    stage_SetAnimation(643, -1, -2);
    stage_SetAnimation(644, -1, -2);
    stage_SetAnimation(645, -1, -2);
    stage_SetAnimation(646, -1, -2);
    stage_SetAnimation(647, -1, -2);
    stage_SetAnimation(648, -1, -2);
    stage_SetAnimation(649, -1, -2);
    stage_SetAnimation(650, -1, -2);
    stage_SetAnimation(651, -1, -2);
    stage_SetAnimation(652, -1, -2);
    stage_SetAnimation(653, -1, -2);
    stage_SetAnimation(654, -1, -2);
    stage_SetAnimation(655, -1, -2);
    stage_SetAnimation(656, -1, -2);
    stage_SetAnimation(657, -1, -2);
    stage_SetAnimation(658, -1, -2);
    stage_SetAnimation(659, -1, -2);
    stage_SetAnimation(660, -1, -2);
    stage_SetAnimation(661, -1, -2);
    stage_SetAnimation(662, -1, -2);
    stage_SetAnimation(663, -1, -2);
    stage_SetAnimation(664, -1, -2);
    stage_SetAnimation(665, -1, -2);
    stage_SetAnimation(666, -1, -2);
    stage_SetAnimation(667, -1, -2);

    stage_SetAnimation(668, 1, 0);

    stage_SetAnimation(242, 1, 501);

    while (stage_ContinueAnimation(668, 669) == 0) {
        _ACTWait(1);
    }

    if (scpGameStat_BoyWeaponkind() == 1) {
        stage_SetAnimation(244, 1, 0);
    }
    if (scpGameStat_BoyWeaponkind() == 4 || scpGameStat_BoyWeaponkind() == 5) {
        stage_SetAnimation(245, 1, 0);
    }
    if (scpGameStat_BoyWeaponkind() == 6) {
        stage_SetAnimation(246, 1, 0);
    }

    DeleteBoyWeapon();

    while (stage_ContinueAnimation(669, 670) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(670, 671) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(244, -1, -2);
    stage_SetAnimation(245, -1, -2);
    stage_SetAnimation(246, -1, -2);

    while (stage_ContinueAnimation(671, 672) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(672, 673) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(673, 674) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(674, 675) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(675, 676) == 0) {
        _ACTWait(1);
    }

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.33f, 0.0f, -0.0004f, 0.0f, -0.42f, 1);

    while (stage_ContinueAnimation(676, 677) == 0) {
        _ACTWait(1);
    }

    shadow_SetLength(GOBJ_SUB(girlGObj), 20.0f);

    while (stage_ContinueAnimation(677, 678) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(242, 1, 2101);

    tex_SetUVScroll("bridge_shadow_hiro", 0.0f, -0.185f, 0.0f, -0.00025f, 0.0f, -0.22f, 1);

    while (stage_ContinueAnimation(678, 679) == 0) {
        _ACTWait(1);
    }

    shadow_DispCancel(66, 1);

    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(47, 0, 484, 0);

    stage_SetLoopFlag(484, 1);
    stage_SetAnimation(484, 1, 0);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    _ACTWait(1);

    scpSearchGobj(605)->active = 0;

    SetStaticBlur(0);

    tex_SetUVScroll("bridge_shadow_hiro", 0.0f, -0.24f, 0.0f, -0.00029f, 0.0f, -0.35f, 1);

    while (stage_CheckAnimationFrame(679, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    while (stage_ContinueAnimation(679, 680) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(605)->active = 1;

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.45f, 0.0f, -0.0004f, 0.0f, -0.7f, 1);

    while (stage_CheckAnimationFrame(680, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("bridge_shadow_hand", 0.0f, -0.35f, 0.0f, -0.0062f, 0.0f, -0.9f, 1);
    tex_SetUVScroll("bridge_shadow_hiro", 0.0f, -0.5f, 0.0f, -0.001f, 0.0f, -0.61f, 1);

    while (stage_ContinueAnimation(680, 681) == 0) {
        _ACTWait(1);
    }

    shadow_SetLength(GOBJ_SUB(girlGObj), 0.0f);

    while (stage_ContinueAnimation(681, 682) == 0) {
        _ACTWait(1);
    }

    tex_SetUVScroll("bridge_shadow_face", 0.0f, -0.3f, 0.0f, -0.002f, 0.0f, -0.9f, 1);

    SetGirlClothDispSwitch(girlGObj, 1, 0);
    SetGirlClothDispSwitch(girlGObj, 0, 0);
    SetGirlClothDispSwitch(girlGObj, 2, 0);

    _ACTWait(1);

    scpSearchGobj(51)->active = 0;
    scpSearchGobj(605)->active = 0;

    shadow_DispCancel(0, 1);
    shadow_DispCancel(2, 1);

    while (stage_ContinueAnimation(682, 683) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(51)->active = 1;
    scpSearchGobj(605)->active = 1;

    gflagOn(130);
    gflagOn(357);

    stage_SetLoopFlag(484, 0);

    shadow_DispCancel(66, 0);
    shadow_DispCancel(0, 0);
    shadow_DispCancel(2, 0);

    SetStaticBlur(1);

    while (stage_CheckAnimationFrame(683, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(3.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }

    RequestStageChange(3, boyGObj, 0, 16.0f, 16.0f);
}

void actSt04aGateLChk(GObj *volatile self)
{
    while (gflagChk(155) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    gflagOn(124);

    scpAdpcmPlayRequestFunc(28, &gate_ready_l, 1, 1, 1);
    while (gate_ready_l == 0) {
        _ACTWait(1);
    }

    preload(4);

    scpFadeIn(6.0f);

    stage_SetAnimation(260, 1, 0);
    while (stage_CheckAnimationFinish(260) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(4, boyGObj, 0, 1.0f, 8.0f);
}

void actSt04aGateRChk(GObj *volatile self)
{
    int stage;

    while (gflagChk(209) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    gflagOn(125);

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(29, &gate_ready_r, 1, 1, 1);
    while (gate_ready_r == 0) {
        _ACTWait(1);
    }

    if (gflagChk(221) != 0) {
        stage = 5;
    } else if (gflagChk(222) != 0) {
        stage = 6;
    } else if (gflagChk(223) != 0) {
        stage = 9;
    } else if (gflagChk(224) != 0) {
        stage = 7;
    } else if (gflagChk(208) != 0) {
        stage = 8;
    } else {
        stage = 0;
    }

    preload(stage);

    scpFadeIn(6.0f);

    stage_SetAnimation(262, 1, 0);
    while (stage_CheckAnimationFinish(262) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(stage, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actSt04aTorch1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(139) == 0) {
        if (gflagChk(131) != 0) {
            scpSearchGobj(522)->active = 0;
            stage_SetAnimation(250, 0, -1);
        }

        if (gflagChk(132) != 0) {
            scpSearchGobj(523)->active = 0;
            stage_SetAnimation(251, 0, -1);
        }

        if (gflagChk(133) != 0) {
            scpSearchGobj(524)->active = 0;
            stage_SetAnimation(252, 0, -1);
        }

        if (gflagChk(134) != 0) {
            scpSearchGobj(525)->active = 0;
            stage_SetAnimation(253, 0, -1);
        }

        if (gflagChk(135) != 0) {
            scpSearchGobj(526)->active = 0;
            stage_SetAnimation(254, 0, -1);
        }

        if (gflagChk(136) != 0) {
            scpSearchGobj(527)->active = 0;
            stage_SetAnimation(255, 0, -1);
        }

        if (gflagChk(137) != 0) {
            scpSearchGobj(528)->active = 0;
            stage_SetAnimation(256, 0, -1);
        }

        if (gflagChk(138) != 0) {
            scpSearchGobj(529)->active = 0;
            stage_SetAnimation(257, 0, -1);
        }

        torch1_mail[0].func = actSt04aTorch1Chk;
        act->mail = torch1_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpSearchGobj(522)->active = 0;
        scpSearchGobj(523)->active = 0;
        scpSearchGobj(524)->active = 0;
        scpSearchGobj(525)->active = 0;
        scpSearchGobj(526)->active = 0;
        scpSearchGobj(527)->active = 0;
        scpSearchGobj(528)->active = 0;
        scpSearchGobj(529)->active = 0;

        stage_SetAnimation(250, 0, -1);
        stage_SetAnimation(251, 0, -1);
        stage_SetAnimation(252, 0, -1);
        stage_SetAnimation(253, 0, -1);
        stage_SetAnimation(254, 0, -1);
        stage_SetAnimation(255, 0, -1);
        stage_SetAnimation(256, 0, -1);
        stage_SetAnimation(257, 0, -1);

        scpTorchLightOn(530);
        scpTorchLightOn(531);
        scpTorchLightOn(532);
        scpTorchLightOn(533);
        scpTorchLightOn(534);
        scpTorchLightOn(535);
        scpTorchLightOn(536);
        scpTorchLightOn(537);
        scpTorchLightOn(538);
        scpTorchLightOn(539);
    }
}
#else
#ifdef VERSION_AUG6
void actConte09_2(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];
    int i;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);

    PlayStreamMotion();

    stage_SetAnimation(653, 1, 0);
    stage_SetAnimation(247, 1, 0);

    while (stage_ContinueAnimation(653, 654) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(654, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 15);

    while (stage_ContinueAnimation(654, 655) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(655, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(655, 656) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(656, 657) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(657, 658) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(658, 659) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(659, 660) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(660, 661) == 0) {
        _ACTWait(1);
    }

    yure2 = iosPadActRequest(boyPad, 10);
    vol2 = 128;
    iosPadActVolumeSet(yure2, 128);

    stage_SetAnimation(241, 1, 0);

    while (stage_ContinueAnimation(661, 662) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(662, 663) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(663, 664) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(664, 665) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(665, 666) == 0) {
        _ACTWait(1);
    }

    ClearStreamMotionEntry(girlGObj);

    scpPlayMotReq(girlGObj, 281);

    scpPlayPosSet(girlGObj, 14.8948f, 210.136f, 4858.48f);

    ofs[0] = liftOfs1.d[0];
    ofs[1] = liftOfs1.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    while (stage_CheckAnimationFinish(666) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(yure2);

    ofs[0] = liftOfs2.d[0];
    ofs[1] = liftOfs2.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    StandbyStreamMotion(streamMotion[4].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(32, &conte09_2, 1, 1, 0);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    gflagOn(127);
}
#else
void actConte09_2(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];
    int i;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);

    PlayStreamMotion();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(724, 1, 0);
    stage_SetAnimation(277, 1, 0);
#else
    stage_SetAnimation(728, 1, 0);
    stage_SetAnimation(281, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(724, 725) == 0) {
#else
    while (stage_ContinueAnimation(728, 729) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(725, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(729, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 15);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(725, 726) == 0) {
#else
    while (stage_ContinueAnimation(729, 730) == 0) {
#endif
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(726, 15, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(730, 15, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(726, 727) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(727, 728) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(728, 729) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(729, 730) == 0) {
        _ACTWait(1);
    }
#endif
    while (stage_ContinueAnimation(730, 731) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(731, 732) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)

    yure2 = iosPadActRequest(boyPad, 10);
    vol2 = 128;
    iosPadActVolumeSet(yure2, 128);

    stage_SetAnimation(269, 1, 0);

#endif
    while (stage_ContinueAnimation(732, 733) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(733, 734) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(734, 735) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(735, 736) == 0) {
        _ACTWait(1);
    }
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)

    yure2 = iosPadActRequest(boyPad, 10);
    vol2 = 128;
    iosPadActVolumeSet(yure2, 128);

    stage_SetAnimation(273, 1, 0);

#endif
    while (stage_ContinueAnimation(736, 737) == 0) {
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(737, 738) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(738, 739) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(739, 740) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(740, 741) == 0) {
#endif
        _ACTWait(1);
    }

    ClearStreamMotionEntry(girlGObj);

    scpPlayMotReq(girlGObj, 315);

    scpPlayPosSet(girlGObj, 14.8948f, 210.136f, 4858.48f);

    ofs[0] = liftOfs1.d[0];
    ofs[1] = liftOfs1.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(737) == 0) {
#else
    while (stage_CheckAnimationFinish(741) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(yure2);

    ofs[0] = liftOfs2.d[0];
    ofs[1] = liftOfs2.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    StandbyStreamMotion(streamMotion[4].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(33, &conte09_2, 1, 1, 0);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

    gflagOn(141);
}

void actSt04aGateOpen3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(142) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetLoopFlag(551, 0);
#else
        stage_SetLoopFlag(555, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(551, 1, 1) == 0) {
#else
        while (stage_CheckAnimationFrame(555, 1, 1) == 0) {
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

        gate_open3_mail[0].func = actSt04aGateOpen3Chk;
        act->mail = gate_open3_mail;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetLoopFlag(551, 0);
#else
        stage_SetLoopFlag(555, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(551, 1, 1) == 0) {
#else
        while (stage_CheckAnimationFrame(555, 1, 1) == 0) {
#endif
            _ACTWait(1);
        }
        _ACTWait(1);
    }
}
#endif

void actSt04aGateOpen3Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

#ifdef VERSION_AUG6
    while (gflagChk(127) == 0 || scpTriggerBall(self, boyGObj, 450.0f) == 0) {
#else
    while (gflagChk(141) == 0 || scpTriggerBall(self, boyGObj, 450.0f) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(128);

    lt_switch_layout(51);
#else
    gflagOn(142);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
#endif

    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    if (gate_open2 != 0) {
#ifdef VERSION_AUG6
        scpAdpcmFadeClose(gate_open2, 80);
#else
        scpAdpcmFadeCloseFunc(&gate_open2, 80);
#endif
    }

    while (conte09_2 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(conte09_2->stream);

    actCreateSubThread(actSt04aEnvSeWakare2, 21);
    actCreateSubThread(actConte09_3, 21);
    actCreateSubThread(actConte09_3Jimaku, 21);
}

void actConte09_3(GObj *volatile self)
{
#ifdef VERSION_AUG6
    scpSearchGobj(624)->active = 1;
#else
    conte09_3Running = 1;

    actCreateSubThread(actConte09_3_demoCancel, 21);

    scpSearchGobj(669)->active = 1;
#endif

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
#ifdef VERSION_AUG6
    EntryStreamMotion(scpSearchGobj(624));
#else
    EntryStreamMotion(scpSearchGobj(669));
#endif

    PlayStreamMotion();

    scpSetStreamMotionRootOffset(boyGObj, 0.0f, 0.0f, 1.0f);
    scpSetStreamMotionRootOffset(girlGObj, 0.0f, 0.0f, 1.0f);

#ifdef VERSION_AUG6
    scpTorchLightOff(529);
    scpTorchLightOff(530);
    scpTorchLightOff(531);
    scpTorchLightOff(532);
    scpTorchLightOff(533);
    scpTorchLightOff(534);
    scpTorchLightOff(535);
    scpTorchLightOff(536);
    scpTorchLightOff(537);
    scpTorchLightOff(538);

    stage_SetAnimation(246, -1, -2);
    stage_SetAnimation(247, -1, -2);
    stage_SetAnimation(640, -1, -2);
    stage_SetAnimation(641, -1, -2);
    stage_SetAnimation(642, -1, -2);
    stage_SetAnimation(643, -1, -2);
    stage_SetAnimation(644, -1, -2);
    stage_SetAnimation(645, -1, -2);
    stage_SetAnimation(646, -1, -2);
    stage_SetAnimation(647, -1, -2);
    stage_SetAnimation(648, -1, -2);
    stage_SetAnimation(649, -1, -2);
    stage_SetAnimation(650, -1, -2);
    stage_SetAnimation(651, -1, -2);
    stage_SetAnimation(652, -1, -2);
    stage_SetAnimation(653, -1, -2);
    stage_SetAnimation(654, -1, -2);
    stage_SetAnimation(655, -1, -2);
    stage_SetAnimation(656, -1, -2);
    stage_SetAnimation(657, -1, -2);
    stage_SetAnimation(658, -1, -2);
    stage_SetAnimation(659, -1, -2);
    stage_SetAnimation(660, -1, -2);
    stage_SetAnimation(661, -1, -2);
    stage_SetAnimation(662, -1, -2);
    stage_SetAnimation(663, -1, -2);
    stage_SetAnimation(664, -1, -2);
    stage_SetAnimation(665, -1, -2);
    stage_SetAnimation(666, -1, -2);

    stage_SetAnimation(667, 1, 0);

    stage_SetAnimation(241, 1, 501);

    while (stage_ContinueAnimation(667, 668) == 0) {
#else
    scpTorchLightOff(571);
    scpTorchLightOff(572);
    scpTorchLightOff(573);
    scpTorchLightOff(574);
    scpTorchLightOff(575);
    scpTorchLightOff(576);
    scpTorchLightOff(577);
    scpTorchLightOff(578);
    scpTorchLightOff(579);
    scpTorchLightOff(580);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(276, -1, -2);
    stage_SetAnimation(277, -1, -2);
    stage_SetAnimation(708, -1, -2);
    stage_SetAnimation(709, -1, -2);
    stage_SetAnimation(710, -1, -2);
    stage_SetAnimation(711, -1, -2);
#else
    stage_SetAnimation(280, -1, -2);
    stage_SetAnimation(281, -1, -2);
#endif
    stage_SetAnimation(712, -1, -2);
    stage_SetAnimation(713, -1, -2);
    stage_SetAnimation(714, -1, -2);
    stage_SetAnimation(715, -1, -2);
    stage_SetAnimation(716, -1, -2);
    stage_SetAnimation(717, -1, -2);
    stage_SetAnimation(718, -1, -2);
    stage_SetAnimation(719, -1, -2);
    stage_SetAnimation(720, -1, -2);
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
    stage_SetAnimation(721, -1, -2);
    stage_SetAnimation(722, -1, -2);
    stage_SetAnimation(723, -1, -2);
#endif
    stage_SetAnimation(724, -1, -2);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(725, -1, -2);
    stage_SetAnimation(726, -1, -2);
    stage_SetAnimation(727, -1, -2);
#endif
    stage_SetAnimation(728, -1, -2);
    stage_SetAnimation(729, -1, -2);
    stage_SetAnimation(730, -1, -2);
    stage_SetAnimation(731, -1, -2);
    stage_SetAnimation(732, -1, -2);
    stage_SetAnimation(733, -1, -2);
    stage_SetAnimation(734, -1, -2);
    stage_SetAnimation(735, -1, -2);
    stage_SetAnimation(736, -1, -2);
    stage_SetAnimation(737, -1, -2);
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
    stage_SetAnimation(738, -1, -2);
    stage_SetAnimation(739, -1, -2);
    stage_SetAnimation(740, -1, -2);
    stage_SetAnimation(741, -1, -2);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(738, 1, 0);
    stage_SetAnimation(269, 1, 501);
#else
    stage_SetAnimation(742, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(738, 739) == 0) {
#else
    _ACTWait(1);

    stage_SetAnimation(273, 1, 502);

    while (stage_ContinueAnimation(742, 743) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    if (scpGameStat_BoyWeaponkind() == 1) {
#ifdef VERSION_AUG6
        stage_SetAnimation(243, 1, 0);
    }
    if (scpGameStat_BoyWeaponkind() == 4 || scpGameStat_BoyWeaponkind() == 5) {
        stage_SetAnimation(244, 1, 0);
    }
    if (scpGameStat_BoyWeaponkind() == 6) {
        stage_SetAnimation(245, 1, 0);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(272, 1, 0);
#else
        stage_SetAnimation(276, 1, 0);
#endif
    }
    if (scpGameStat_BoyWeaponkind() == 4 || scpGameStat_BoyWeaponkind() == 5) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(273, 1, 0);
#else
        stage_SetAnimation(277, 1, 0);
#endif
    }
    if (scpGameStat_BoyWeaponkind() == 6) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(274, 1, 0);
#else
        stage_SetAnimation(278, 1, 0);
#endif
    }
    if (scpGameStat_BoyWeaponkind() == 9) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(275, 1, 0);
#else
        stage_SetAnimation(279, 1, 0);
#endif
#endif
    }

    DeleteBoyWeapon();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(739, 740) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(740, 741) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(272, -1, -2);
    stage_SetAnimation(273, -1, -2);
    stage_SetAnimation(274, -1, -2);
    stage_SetAnimation(275, -1, -2);

    while (stage_ContinueAnimation(741, 742) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(742, 743) == 0) {
        _ACTWait(1);
    }
#endif
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(668, 669) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(669, 670) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(243, -1, -2);
    stage_SetAnimation(244, -1, -2);
    stage_SetAnimation(245, -1, -2);

    while (stage_ContinueAnimation(670, 671) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(671, 672) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(672, 673) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(673, 674) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(674, 675) == 0) {
#else
    while (stage_ContinueAnimation(743, 744) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(744, 745) == 0) {
        _ACTWait(1);
    }
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)

    stage_SetAnimation(276, -1, -2);
    stage_SetAnimation(277, -1, -2);
    stage_SetAnimation(278, -1, -2);
    stage_SetAnimation(279, -1, -2);

#endif
    while (stage_ContinueAnimation(745, 746) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)

    stage_SetAnimation(721, 1, 0);

#endif
    while (stage_ContinueAnimation(746, 747) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)

    shadow_SetLength(GOBJ_SUB(girlGObj), 20.0f);

#endif
    while (stage_ContinueAnimation(747, 748) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    tex_SetUVScroll("bridge_shadow", 0.0f, -0.33f, 0.0f, -0.0004f, 0.0f, -0.42f, 1);

    while (stage_ContinueAnimation(675, 676) == 0) {
        _ACTWait(1);
    }

    shadow_SetLength(GOBJ_SUB(girlGObj), 20.0f);

    while (stage_ContinueAnimation(676, 677) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(241, 1, 2101);

    tex_SetUVScroll("bridge_shadow_hiro", 0.0f, -0.185f, 0.0f, -0.00025f, 0.0f, -0.22f, 1);

    while (stage_ContinueAnimation(677, 678) == 0) {
        _ACTWait(1);
    }

    shadow_DispCancel(65, 1);

    stage_SetLoopFlag(483, 1);
    stage_SetAnimation(483, 1, 0);

    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(47, 0, 483, 0);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(269, 1, 2101);
    stage_SetAnimation(722, 1, 0);
#else
    stage_SetAnimation(273, 1, 881);
#endif

    while (stage_ContinueAnimation(748, 749) == 0) {
        _ACTWait(1);
    }
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
    while (stage_ContinueAnimation(749, 750) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(725, 1, 0);

    while (stage_ContinueAnimation(750, 751) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(273, 1, 1241);

    shadow_SetLength(GOBJ_SUB(girlGObj), 20.0f);

    while (stage_ContinueAnimation(751, 752) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(273, 1, 2101);
    stage_SetAnimation(725, -1, -2);
    stage_SetAnimation(726, 1, 0);

    while (stage_ContinueAnimation(752, 753) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(273, 1, 2221);
#endif

    shadow_DispCancel(71, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(48, 0, 551, 0);
#else
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(48, 0, 555, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetLoopFlag(551, 1);
    stage_SetAnimation(551, 1, 0);
#else
    stage_SetLoopFlag(555, 1);
    stage_SetAnimation(555, 1, 0);
#endif
#endif

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    _ACTWait(1);

#ifdef VERSION_AUG6
    scpSearchGobj(604)->active = 0;
#else
    scpSearchGobj(649)->active = 0;
#endif

    SetStaticBlur(0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(749, 150, 0) == 0) {
#else
#ifdef VERSION_AUG6
    tex_SetUVScroll("bridge_shadow_hiro", 0.0f, -0.24f, 0.0f, -0.00029f, 0.0f, -0.35f, 1);

    while (stage_CheckAnimationFrame(678, 150, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(753, 150, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(749, 750) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(678, 679) == 0) {
#else
    while (stage_ContinueAnimation(753, 754) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);

#ifdef VERSION_AUG6
    scpSearchGobj(604)->active = 1;

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.45f, 0.0f, -0.0004f, 0.0f, -0.7f, 1);

    while (stage_CheckAnimationFrame(679, 50, 0) == 0) {
#else
    scpSearchGobj(649)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(750, 50, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(754, 50, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(750, 751) == 0) {
#else
#ifdef VERSION_AUG6
    tex_SetUVScroll("bridge_shadow_hand", 0.0f, -0.35f, 0.0f, -0.0062f, 0.0f, -0.9f, 1);
    tex_SetUVScroll("bridge_shadow_hiro", 0.0f, -0.5f, 0.0f, -0.001f, 0.0f, -0.61f, 1);

    while (stage_ContinueAnimation(679, 680) == 0) {
#else
    while (stage_ContinueAnimation(754, 755) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    shadow_SetLength(GOBJ_SUB(girlGObj), 0.0f);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(751, 752) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(680, 681) == 0) {
#else
    while (stage_ContinueAnimation(755, 756) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(723, 1, 0);
#else
#ifdef VERSION_AUG6
    tex_SetUVScroll("bridge_shadow_face", 0.0f, -0.3f, 0.0f, -0.002f, 0.0f, -0.9f, 1);
#else
    stage_SetAnimation(726, -1, -2);
    stage_SetAnimation(727, 1, 0);
#endif
#endif

    SetGirlClothDispSwitch(girlGObj, 1, 0);
    SetGirlClothDispSwitch(girlGObj, 0, 0);
    SetGirlClothDispSwitch(girlGObj, 2, 0);

    _ACTWait(1);

#ifdef VERSION_AUG6
    scpSearchGobj(50)->active = 0;
    scpSearchGobj(604)->active = 0;

    shadow_DispCancel(0, 1);
    shadow_DispCancel(2, 1);

    while (stage_ContinueAnimation(681, 682) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(50)->active = 1;
    scpSearchGobj(604)->active = 1;

    gflagOn(130);
    gflagOn(356);

    stage_SetLoopFlag(483, 0);

    shadow_DispCancel(65, 0);
    shadow_DispCancel(0, 0);
    shadow_DispCancel(2, 0);
#else
    scpSearchGobj(54)->active = 0;
    scpSearchGobj(649)->active = 0;

    shadow_DispCancel(0, 1);
    shadow_DispCancel(4, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(752, 753) == 0) {
#else
    while (stage_ContinueAnimation(756, 757) == 0) {
#endif
        _ACTWait(1);
    }
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)

    stage_SetAnimation(727, -1, -2);
#endif

    conte09_3Running = 0;

    _ACTWait(1);

    scpSearchGobj(54)->active = 1;
    scpSearchGobj(649)->active = 1;

    gflagOn(144);
    gflagOn(390);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetLoopFlag(551, 0);
#else
    stage_SetLoopFlag(555, 0);
#endif

    shadow_DispCancel(71, 0);
    shadow_DispCancel(0, 0);
    shadow_DispCancel(4, 0);
#endif

    SetStaticBlur(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(753, 90, 0) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(682, 90, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(757, 90, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(3.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }

    RequestStageChange(3, boyGObj, 0, 16.0f, 16.0f);
}

void actSt04aGateLChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (gflagChk(155) == 0) {
#else
    GProc *th;

    while (gflagChk(174) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    gflagOn(124);

    scpAdpcmPlayRequestFunc(28, &gate_ready_l, 1, 1, 1);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    scpBoyControlReadDisable = 1;
    gflagOn(138);

    scpAdpcmPlayRequestFunc(29, &gate_ready_l, 1, 1, 1);
#endif
    while (gate_ready_l == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpFadeIn(6.0f);

    stage_SetAnimation(259, 1, 0);
    while (stage_CheckAnimationFinish(259) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(4, boyGObj, girlGObj, 1.0f, 8.0f);
#else
    preload(4);

    scpFadeIn(16.0f);

    th = actCreateSubThread(actSt04aGateLSub, 21);

    demoEnd = 0;

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&gate_ready_l, 256);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(289, 0, -1);
#else
        stage_SetAnimation(293, 0, -1);
#endif

        scpFadeIn(3.0f);
    }

    RequestStageChange(4, boyGObj, 0, 1.0f, 8.0f);
#endif
}

void actSt04aGateRChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (gflagChk(209) == 0) {
#else
    GProc *th;
    int stage;

    while (gflagChk(234) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    gflagOn(125);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    scpBoyControlReadDisable = 1;
    gflagOn(139);
#endif

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(29, &gate_ready_r, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(30, &gate_ready_r, 1, 1, 1);
#endif
    while (gate_ready_r == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpFadeIn(6.0f);

    stage_SetAnimation(261, 1, 0);
    while (stage_CheckAnimationFinish(261) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(221) != 0) {
        RequestStageChange(5, boyGObj, girlGObj, 1.0f, 8.0f);
    }
    if (gflagChk(222) != 0) {
        RequestStageChange(6, boyGObj, girlGObj, 1.0f, 8.0f);
    }
    if (gflagChk(223) != 0) {
        RequestStageChange(9, boyGObj, girlGObj, 1.0f, 8.0f);
    }
    if (gflagChk(224) != 0) {
        RequestStageChange(7, boyGObj, girlGObj, 1.0f, 8.0f);
    }
    if (gflagChk(208) != 0) {
        RequestStageChange(8, boyGObj, girlGObj, 1.0f, 8.0f);
    }
#else
    if (gflagChk(246) != 0) {
        stage = 5;
    } else if (gflagChk(247) != 0) {
        stage = 6;
    } else if (gflagChk(248) != 0) {
        stage = 9;
    } else if (gflagChk(249) != 0) {
        stage = 7;
    } else if (gflagChk(233) != 0) {
        stage = 8;
    } else {
        stage = 0;
    }

    preload(stage);

    scpFadeIn(16.0f);

    th = actCreateSubThread(actSt04aGateRSub, 21);

    demoEnd = 0;

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&gate_ready_r, 256);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(291, 0, -1);
#else
        stage_SetAnimation(295, 0, -1);
#endif

        scpFadeIn(3.0f);
    }

    RequestStageChange(stage, boyGObj, 0, 1.0f, 8.0f);
#endif
}

void actSt04aTorch1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(139) == 0) {
        if (gflagChk(131) != 0) {
            scpSearchGobj(521)->active = 0;
            stage_SetAnimation(249, 0, -1);
        }

        if (gflagChk(132) != 0) {
            scpSearchGobj(522)->active = 0;
            stage_SetAnimation(250, 0, -1);
        }

        if (gflagChk(133) != 0) {
            scpSearchGobj(523)->active = 0;
            stage_SetAnimation(251, 0, -1);
        }

        if (gflagChk(134) != 0) {
            scpSearchGobj(524)->active = 0;
            stage_SetAnimation(252, 0, -1);
        }

        if (gflagChk(135) != 0) {
            scpSearchGobj(525)->active = 0;
            stage_SetAnimation(253, 0, -1);
        }

        if (gflagChk(136) != 0) {
            scpSearchGobj(526)->active = 0;
            stage_SetAnimation(254, 0, -1);
        }

        if (gflagChk(137) != 0) {
            scpSearchGobj(527)->active = 0;
            stage_SetAnimation(255, 0, -1);
        }

        if (gflagChk(138) != 0) {
            scpSearchGobj(528)->active = 0;
            stage_SetAnimation(256, 0, -1);
#else
    if (gflagChk(153) == 0) {
        SleepHint(6);
        SleepHint(4);

        if (gflagChk(145) != 0) {
            scpSearchGobj(563)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(279, 0, -1);
#else
            stage_SetAnimation(283, 0, -1);
#endif
        }

        if (gflagChk(146) != 0) {
            scpSearchGobj(564)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(280, 0, -1);
#else
            stage_SetAnimation(284, 0, -1);
#endif
        }

        if (gflagChk(147) != 0) {
            scpSearchGobj(565)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(281, 0, -1);
#else
            stage_SetAnimation(285, 0, -1);
#endif
        }

        if (gflagChk(148) != 0) {
            scpSearchGobj(566)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(282, 0, -1);
#else
            stage_SetAnimation(286, 0, -1);
#endif
        }

        if (gflagChk(149) != 0) {
            scpSearchGobj(567)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(283, 0, -1);
#else
            stage_SetAnimation(287, 0, -1);
#endif
        }

        if (gflagChk(150) != 0) {
            scpSearchGobj(568)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(284, 0, -1);
#else
            stage_SetAnimation(288, 0, -1);
#endif
        }

        if (gflagChk(151) != 0) {
            scpSearchGobj(569)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(285, 0, -1);
#else
            stage_SetAnimation(289, 0, -1);
#endif
        }

        if (gflagChk(152) != 0) {
            scpSearchGobj(570)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(286, 0, -1);
#else
            stage_SetAnimation(290, 0, -1);
#endif
#endif
        }

        torch1_mail[0].func = actSt04aTorch1Chk;
        act->mail = torch1_mail;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpSearchGobj(521)->active = 0;
        scpSearchGobj(522)->active = 0;
        scpSearchGobj(523)->active = 0;
        scpSearchGobj(524)->active = 0;
        scpSearchGobj(525)->active = 0;
        scpSearchGobj(526)->active = 0;
        scpSearchGobj(527)->active = 0;
        scpSearchGobj(528)->active = 0;

        stage_SetAnimation(249, 0, -1);
        stage_SetAnimation(250, 0, -1);
        stage_SetAnimation(251, 0, -1);
        stage_SetAnimation(252, 0, -1);
        stage_SetAnimation(253, 0, -1);
        stage_SetAnimation(254, 0, -1);
        stage_SetAnimation(255, 0, -1);
        stage_SetAnimation(256, 0, -1);

        scpTorchLightOn(529);
        scpTorchLightOn(530);
        scpTorchLightOn(531);
        scpTorchLightOn(532);
        scpTorchLightOn(533);
        scpTorchLightOn(534);
        scpTorchLightOn(535);
        scpTorchLightOn(536);
        scpTorchLightOn(537);
        scpTorchLightOn(538);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(563)->active = 0;
        scpSearchGobj(564)->active = 0;
        scpSearchGobj(565)->active = 0;
        scpSearchGobj(566)->active = 0;
        scpSearchGobj(567)->active = 0;
        scpSearchGobj(568)->active = 0;
        scpSearchGobj(569)->active = 0;
        scpSearchGobj(570)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(279, 0, -1);
        stage_SetAnimation(280, 0, -1);
        stage_SetAnimation(281, 0, -1);
        stage_SetAnimation(282, 0, -1);
#endif
        stage_SetAnimation(283, 0, -1);
        stage_SetAnimation(284, 0, -1);
        stage_SetAnimation(285, 0, -1);
        stage_SetAnimation(286, 0, -1);
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
        stage_SetAnimation(287, 0, -1);
        stage_SetAnimation(288, 0, -1);
        stage_SetAnimation(289, 0, -1);
        stage_SetAnimation(290, 0, -1);
#endif

        scpTorchLightOn(571);
        scpTorchLightOn(572);
        scpTorchLightOn(573);
        scpTorchLightOn(574);
        scpTorchLightOn(575);
        scpTorchLightOn(576);
        scpTorchLightOn(577);
        scpTorchLightOn(578);
        scpTorchLightOn(579);
        scpTorchLightOn(580);
#endif
    }
}
#endif
#endif

void actSt04aTorch1Chk(GObj *volatile self)
{
    GObj *x = self;
    ActSt04A *act = (ActSt04A *)actInitialize(self);
    _ACTWait(1);

    switch (self->labelId) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#ifdef VERSION_AUG6
    case 513:
        act->torchFlag = 131;
        act->torchObj = scpSearchGobj(521);
        act->torchAnim = 249;
        actCreateSubThread(actSt04aTorchAllFlagfChk, 21);
        break;
    case 514:
        act->torchFlag = 132;
        act->torchObj = scpSearchGobj(522);
        act->torchAnim = 250;
        break;
    case 515:
        act->torchFlag = 133;
#else
    case 514:
        act->torchFlag = 131;
        act->torchObj = scpSearchGobj(522);
        act->torchAnim = 250;
        actCreateSubThread(actSt04aTorchAllFlagfChk, 21);
        break;
    case 515:
        act->torchFlag = 132;
#endif
        act->torchObj = scpSearchGobj(523);
        act->torchAnim = 251;
        break;
    case 516:
#ifdef VERSION_AUG6
        act->torchFlag = 134;
#else
        act->torchFlag = 133;
#endif
        act->torchObj = scpSearchGobj(524);
        act->torchAnim = 252;
        break;
    case 517:
#ifdef VERSION_AUG6
        act->torchFlag = 135;
#else
        act->torchFlag = 134;
#endif
        act->torchObj = scpSearchGobj(525);
        act->torchAnim = 253;
        break;
    case 518:
#ifdef VERSION_AUG6
        act->torchFlag = 136;
#else
        act->torchFlag = 135;
#endif
        act->torchObj = scpSearchGobj(526);
        act->torchAnim = 254;
        break;
    case 519:
#ifdef VERSION_AUG6
        act->torchFlag = 137;
#else
        act->torchFlag = 136;
#endif
        act->torchObj = scpSearchGobj(527);
        act->torchAnim = 255;
        break;
    case 520:
#ifdef VERSION_AUG6
        act->torchFlag = 138;
        act->torchObj = scpSearchGobj(528);
        act->torchAnim = 256;
#else
        act->torchFlag = 137;
        act->torchObj = scpSearchGobj(528);
        act->torchAnim = 256;
        break;
    case 521:
        act->torchFlag = 138;
        act->torchObj = scpSearchGobj(529);
        act->torchAnim = 257;
#endif
#else
#ifdef VERSION_JUN26
    case 493:
        act->torchFlag = 124;
        act->torchObj = scpSearchGobj(501);
        act->torchAnim = 223;
        actCreateSubThread(actSt04aTorchAllFlagfChk, 21);
        break;
    case 494:
        act->torchFlag = 125;
        act->torchObj = scpSearchGobj(502);
        act->torchAnim = 224;
        break;
    case 495:
        act->torchFlag = 126;
        act->torchObj = scpSearchGobj(503);
        act->torchAnim = 225;
        break;
    case 496:
        act->torchFlag = 127;
        act->torchObj = scpSearchGobj(504);
        act->torchAnim = 226;
        break;
    case 497:
        act->torchFlag = 128;
        act->torchObj = scpSearchGobj(505);
        act->torchAnim = 227;
        break;
    case 498:
        act->torchFlag = 129;
        act->torchObj = scpSearchGobj(506);
        act->torchAnim = 228;
        break;
    case 499:
        act->torchFlag = 130;
        act->torchObj = scpSearchGobj(507);
        act->torchAnim = 229;
        break;
    case 500:
        act->torchFlag = 131;
        act->torchObj = scpSearchGobj(508);
        act->torchAnim = 230;
#else
    case 555:
        act->torchFlag = 145;
        act->torchObj = scpSearchGobj(563);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        act->torchAnim = 279;
#else
        act->torchAnim = 283;
#endif
        actCreateSubThread(actSt04aTorchAllFlagfChk, 21);
        break;
    case 556:
        act->torchFlag = 146;
        act->torchObj = scpSearchGobj(564);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        act->torchAnim = 280;
#else
        act->torchAnim = 284;
#endif
        break;
    case 557:
        act->torchFlag = 147;
        act->torchObj = scpSearchGobj(565);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        act->torchAnim = 281;
#else
        act->torchAnim = 285;
#endif
        break;
    case 558:
        act->torchFlag = 148;
        act->torchObj = scpSearchGobj(566);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        act->torchAnim = 282;
#else
        act->torchAnim = 286;
#endif
        break;
    case 559:
        act->torchFlag = 149;
        act->torchObj = scpSearchGobj(567);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        act->torchAnim = 283;
#else
        act->torchAnim = 287;
#endif
        break;
    case 560:
        act->torchFlag = 150;
        act->torchObj = scpSearchGobj(568);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        act->torchAnim = 284;
#else
        act->torchAnim = 288;
#endif
        break;
    case 561:
        act->torchFlag = 151;
        act->torchObj = scpSearchGobj(569);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        act->torchAnim = 285;
#else
        act->torchAnim = 289;
#endif
        break;
    case 562:
        act->torchFlag = 152;
        act->torchObj = scpSearchGobj(570);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        act->torchAnim = 286;
#else
        act->torchAnim = 290;
#endif
#endif
#endif
        break;
    }

    while (1) {
        if (scpTriggerBall(self, act->torchObj, 5.0f) != 0) {
            scpBoyControlReadDisable = 1;

            act->torchObj->active = 0;

            stage_SetAnimation(act->torchAnim, 1, 0);

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
            while (stage_CheckAnimationFrame(act->torchAnim, 2, 0) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);

            soundSeDefPlay(1363, 0, 0, 1);
#endif

            while (stage_CheckAnimationFinish(act->torchAnim) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);

            gflagOn(act->torchFlag);

            scpBoyControlReadDisable = 0;
            break;
        }
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
void actSt04aTorchAllFlagfChk(GObj *volatile self)
{
    while (gflagChk(131) == 0 || gflagChk(132) == 0 || gflagChk(133) == 0 || gflagChk(134) == 0 ||
           gflagChk(135) == 0 || gflagChk(136) == 0 || gflagChk(137) == 0 || gflagChk(138) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(139);
    scpAdpcmPlayRequestFunc(83, &torch, 1, 1, 1);
    while (torch == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(249, 1, 0);
    while (stage_CheckAnimationFrame(249, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpTorchLightOn(530);
    scpTorchLightOn(531);
    scpTorchLightOn(532);
    scpTorchLightOn(533);
    scpTorchLightOn(534);
    scpTorchLightOn(535);
    scpTorchLightOn(536);
    scpTorchLightOn(537);
    scpTorchLightOn(538);
    scpTorchLightOn(539);

    while (stage_CheckAnimationFinish(249) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait(60);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    scpWakeupEnemyAll();
}

void actSt04aGateL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(124) == 0) {
        gflagOn(356);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(262, 0, 0);

        gate_l_mail[0].func = actSt04aGateLChk;
        act->mail = gate_l_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04aGateR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(125) == 0) {
        gflagOn(356);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(260, 0, -1);

        gate_r_mail[0].func = actSt04aGateRChk;
        act->mail = gate_r_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04aTorchXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    stage_SetAnimation(258, 0, 0);
}

void actSt04aGateOpen2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(127) == 0) {
        scpSearchGobj(625)->active = 0;

        gate_open2_mail[0].func = actSt04aGateOpen2Chk;
        act->mail = gate_open2_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04aGateOpen3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(128) == 0) {
        stage_SetAnimation(244, 0, -1);
        stage_SetAnimation(245, 0, -1);
        stage_SetAnimation(246, 0, -1);

        stage_SetLoopFlag(484, 0);

        gate_open3_mail[0].func = actSt04aGateOpen3Chk;
        act->mail = gate_open3_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetLoopFlag(484, 0);
    }
}
#else
void actSt04aTorchAllFlagfChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (gflagChk(131) == 0 || gflagChk(132) == 0 || gflagChk(133) == 0 || gflagChk(134) == 0 ||
           gflagChk(135) == 0 || gflagChk(136) == 0 || gflagChk(137) == 0 || gflagChk(138) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(124) == 0 || gflagChk(125) == 0 || gflagChk(126) == 0 || gflagChk(127) == 0 ||
           gflagChk(128) == 0 || gflagChk(129) == 0 || gflagChk(130) == 0 || gflagChk(131) == 0) {
#else
    int i;
    int skip = 0;

    while (gflagChk(145) == 0 || gflagChk(146) == 0 || gflagChk(147) == 0 || gflagChk(148) == 0 ||
           gflagChk(149) == 0 || gflagChk(150) == 0 || gflagChk(151) == 0 || gflagChk(152) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(139);
    scpAdpcmPlayRequestFunc(83, &torch, 1, 1, 1);
#else
#ifdef VERSION_JUN26
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(132);
    scpAdpcmPlayRequestFunc(78, &torch, 1, 1, 1);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(153);
    WakeupHint(6);
    WakeupHint(4);
    scpAdpcmPlayRequestFunc(85, &torch, 1, 1, 1);
#endif
#endif
    while (torch == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(248, 1, 0);
    while (stage_CheckAnimationFrame(248, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpTorchLightOn(529);
    scpTorchLightOn(530);
    scpTorchLightOn(531);
    scpTorchLightOn(532);
    scpTorchLightOn(533);
    scpTorchLightOn(534);
    scpTorchLightOn(535);
    scpTorchLightOn(536);
    scpTorchLightOn(537);
    scpTorchLightOn(538);

    while (stage_CheckAnimationFinish(248) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait(60);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    scpWakeupEnemyAll();
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(222, 1, 0);
    while (stage_CheckAnimationFrame(222, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpTorchLightOn(509);
    scpTorchLightOn(510);
    scpTorchLightOn(511);
    scpTorchLightOn(512);
    scpTorchLightOn(513);
    scpTorchLightOn(514);
    scpTorchLightOn(515);
    scpTorchLightOn(516);
    scpTorchLightOn(517);
    scpTorchLightOn(518);

    while (stage_CheckAnimationFinish(222) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait(60);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(278, 1, 0);
    while (stage_CheckAnimationFrame(278, 60, 0) == 0 && skip == 0) {
#else
    stage_SetAnimation(282, 1, 0);
    while (stage_CheckAnimationFrame(282, 60, 0) == 0 && skip == 0) {
#endif
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
        _ACTWait(1);
    }

    scpTorchLightOn(571);
    scpTorchLightOn(572);
    scpTorchLightOn(573);
    scpTorchLightOn(574);
    scpTorchLightOn(575);
    scpTorchLightOn(576);
    scpTorchLightOn(577);
    scpTorchLightOn(578);
    scpTorchLightOn(579);
    scpTorchLightOn(580);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(278) == 0 && skip == 0) {
#else
    while (stage_CheckAnimationFinish(282) == 0 && skip == 0) {
#endif
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
        _ACTWait(1);
    }

    for (i = 60; i-- > 0 && skip == 0;) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
        _ACTWait(1);
    }

    if (skip != 0) {
        scpAdpcmFadeCloseFunc(&torch, 192);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(278, 0, -1);
#else
        stage_SetAnimation(282, 0, -1);
#endif
        SetCameraFlag_LwsCutBack();
        scpFadeIn(3.0f);
    }
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpWakeupEnemyAll();
}

static void actSt04aTorchHintChk(GObj *volatile self)
{
    while (gflagChk(155) == 0) {
        _ACTWait(1);
    }

    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(563), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(564), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(565), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(566), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(567), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(568), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(569), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(570), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(591), 1.0f, 0.001f, 1.0f);

    if (gflagChk(156) == 0) {
        _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 20);
    }

    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(563), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(564), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(565), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(566), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(567), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(568), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(569), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(570), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(591), 2.0f, 0.01f, 1.0f);

    gflagOn(156);
#endif
#endif
}

void actSt04aGateL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_JUN26
    if (gflagChk(117) == 0) {
        stage_SetAnimation(235, 0, 0);
#else
#ifdef VERSION_AUG6
    if (gflagChk(124) == 0) {
        gflagOn(355);
#else
    if (gflagChk(138) == 0) {
        gflagOn(389);
#endif

        scpFadeOut(255.0f, 0, 0, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(291, 0, 0);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(261, 0, 0);
#else
        stage_SetAnimation(295, 0, 0);
#endif
#endif
#endif

        gate_l_mail[0].func = actSt04aGateLChk;
        act->mail = gate_l_mail;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
#else
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04aGateR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_JUN26
    if (gflagChk(118) == 0) {
        stage_SetAnimation(233, 0, -1);
#else
#ifdef VERSION_AUG6
    if (gflagChk(125) == 0) {
        gflagOn(355);
#else
    if (gflagChk(139) == 0) {
        gflagOn(389);
#endif

        scpFadeOut(255.0f, 0, 0, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(289, 0, -1);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(259, 0, -1);
#else
        stage_SetAnimation(293, 0, -1);
#endif
#endif
#endif

        gate_r_mail[0].func = actSt04aGateRChk;
        act->mail = gate_r_mail;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
#else
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04aTorchXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    stage_SetAnimation(257, 0, 0);
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(231, 0, 0);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(287, 0, 0);
#else
    stage_SetAnimation(291, 0, 0);
#endif
}

void actSt04aDeadCam(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(141) == 0 || scpTriggerBall(self, boyGObj, 600.0f) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(269, 1400, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(273, 1400, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(270, 1, 0);
#else
    stage_SetAnimation(274, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(270) == 0) {
#else
    while (stage_CheckAnimationFinish(274) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#endif
#endif
}

void actSt04aGateOpen2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(127) == 0) {
        scpSearchGobj(624)->active = 0;
#else
#ifdef VERSION_JUN26
    if (gflagChk(120) == 0) {
        scpSearchGobj(599)->active = 0;
#else
    if (gflagChk(141) == 0) {
        scpSearchGobj(669)->active = 0;
#endif
#endif

        gate_open2_mail[0].func = actSt04aGateOpen2Chk;
        act->mail = gate_open2_mail;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt04aGateOpen3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(128) == 0) {
        stage_SetAnimation(243, 0, -1);
        stage_SetAnimation(244, 0, -1);
        stage_SetAnimation(245, 0, -1);

        stage_SetLoopFlag(483, 0);

        gate_open3_mail[0].func = actSt04aGateOpen3Chk;
        act->mail = gate_open3_mail;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetLoopFlag(483, 0);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04aGateOpen3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(121) == 0) {
        stage_SetAnimation(218, 0, -1);
        stage_SetAnimation(219, 0, -1);

        gate_open3_mail[0].func = actSt04aGateOpen3Chk;
        act->mail = gate_open3_mail;
        ACTSendMailCorrect(self, 377);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
#endif
    }
}
#endif

void actSt04aGateOpen2Ready(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    gate_open2_ready_mail[0].func = actSt04aGateOpen2ReadyChk;
    act->mail = gate_open2_ready_mail;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
#endif
    _ACTWait(0);
}

#ifdef VERSION_JUN26
void actSt04aGirlSit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    girl_sit_mail[0].func = actSt04aGirlSitChk;
    act->mail = girl_sit_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt04aGateOpen2ReadyChk(GObj *volatile self)
{
    GObj *x = self;
    int i;

    actInitialize(self);
    _ACTWait(1);

    while (scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    StandbyStreamMotion(streamMotion[3].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(34, &gate_open2, 1, 1, 0);
}

void actSt04aGateOpen2Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 || ACTGame_FLAG_TETSUNAGI() == 0) {
        _ACTWait(1);
    }

    GOBJ_ACT(girlGObj)->flags20.ll &= ~2;
    scpPlayMotReq(girlGObj, 270);

    lt_switch_layout(51);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpDisActivateAllWithKind(19);

    while (gate_open2 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(gate_open2->stream);

    actCreateSubThread(actConte09_2, 21);
}
#else
void actSt04aGirlSit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    girl_sit_mail[0].func = actSt04aGirlSitChk;
    act->mail = girl_sit_mail;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04aTorchHint(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(153) == 0) {
        torch_hint_mail[0].func = actSt04aTorchHintChk;
        act->mail = torch_hint_mail;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04aModel(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    scpSearchGobj(648)->active = 0;

    model_mail[0].func = actSt04aModelOnChk;
    act->mail = model_mail;
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actSt04aEnvSe(GObj *volatile self)
{
    float f = 0.0f;

    scpSeEnvMasterVolRate = 0.0f;

    for (;;) {
        float nf = f + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 5401) {
            scpSeEnvMasterVolRate += 1.0f / 1800.0f;
            if (scpSeEnvMasterVolRate > 1.0f) {
                scpSeEnvMasterVolRate = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

void actSt04aEnvSeWakare1(GObj *volatile self)
{
    float f = 0.0f;

    scpSeEnvMasterVolRate = 0.0f;

    for (;;) {
        float nf = f + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2201) {
            scpSeEnvMasterVolRate += 1.0f / 3800.0f;
            if (scpSeEnvMasterVolRate > 1.0f) {
                scpSeEnvMasterVolRate = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

typedef struct { /* field names derived */
    float m[4];
} Vec4St04A; /* derived name */

static void finishCallBackFunc(GObj *obj)
{
    Vec4St04A v;
    int i;

    _ApplyMatrix(&v, (float *)GOBJ_SUB(obj)->nodeMtx, YUnitVector);
    v.m[1] = 0.0f;
    _NormalizeVector(GOBJ_SUB(obj)->ctrl.dir, &v);

    for (i = 0; i < GOBJ_SUB(obj)->skelNodeNum; i++) {
        *(Mtx44 *)&GOBJ_SUB(obj)->nodeRotElem[i] = jointMtxInit;
    }
}

void actSt04aGateOpen2ReadyChk(GObj *volatile self)
{
    GObj *x = self;
    int i;

    actInitialize(self);
    _ACTWait(1);

    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    StandbyStreamMotion(streamMotion[3].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    scpAdpcmPlayRequestFunc(31, &gate_open2, 1, 0, 0);
#else
    scpAdpcmPlayRequestFunc(32, &gate_open2, 1, 0, 0);
#endif
}

void actSt04aEnvSeWakare2(GObj *volatile self)
{
    float f = 0.0f;

    for (;;) {
        float nf = f + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2351) {
            scpSeEnvMasterVolRate -= 1.0f / 720.0f;
            if (scpSeEnvMasterVolRate < 0.0f) {
                scpSeEnvMasterVolRate = 0.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}
#endif

void actConte09_3Jimaku(GObj *volatile self)
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
#ifdef VERSION_JUN26
        case 2530:
#else
        case 2470:
#endif
            jimaku_msg.sub.block = 91;
            jimaku_msg.sub.jump = 300;
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
    } while (t < 3000.0f);
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt04aGirlSitChk(GObj *volatile self)
{
    int n;

    while (gflagChk(126) == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_AUG6
    GOBJ_ACT(girlGObj)->flags20.ll |= 0x8;
    n = 0;
    for (;;) {
        if ((int)(GOBJ_ACT(girlGObj)->flags20.ll >> 6) & 1) {
#else
    GOBJ_ACT(girlGObj)->flags20.ll |= 0x40;
    n = 0;
    for (;;) {
        if ((int)(GOBJ_ACT(girlGObj)->flags20.ll >> 9) & 1) {
#endif
            n++;
        } else {
            n = 0;
        }
        if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 3 < n) {
#ifdef VERSION_AUG6
            iosOmSendMail(girlGObj, 101, girlGObj);
#else
            iosOmSendMail(girlGObj, 102, girlGObj);
#endif
            n = 0;
        }
        _ACTWait(1);
    }
}
#else
#ifdef VERSION_JUN26
void actSt04aGateLChk(GObj *volatile self)
{
    while (gflagChk(148) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    gflagOn(117);

    scpAdpcmPlayRequestFunc(31, 0, 1, 1, 1);

    stage_SetAnimation(233, 1, 0);
    while (stage_CheckAnimationFinish(233) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(4, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actSt04aGirlSitChk(GObj *volatile self)
{
    int n;

    while (gflagChk(119) == 0) {
        _ACTWait(1);
    }
    GOBJ_ACT(girlGObj)->flags20.ll |= 2;
    n = 0;
    for (;;) {
        if ((int)(GOBJ_ACT(girlGObj)->flags20.ll >> 4) & 1) {
            n++;
        } else {
            n = 0;
        }
        if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 3 < n) {
            iosOmSendMail(girlGObj, 100, girlGObj);
            n = 0;
        }
        _ACTWait(1);
    }
}
#else
static void actConte09_3_demoCancel(GObj *volatile self)
{
    while (1) {
        _ACTWait(1);
    }
}

static void actSt04aGateLSub(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(289, 1, 0);
    while (stage_CheckAnimationFinish(289) == 0) {
#else
    stage_SetAnimation(293, 1, 0);
    while (stage_CheckAnimationFinish(293) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

static void actSt04aGateRSub(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(291, 1, 0);
    while (stage_CheckAnimationFinish(291) == 0) {
#else
    stage_SetAnimation(295, 1, 0);
    while (stage_CheckAnimationFinish(295) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt04aGirlSitChk(GObj *volatile self)
{
    int n;

    while (gflagChk(140) == 0) {
        _ACTWait(1);
    }
    GOBJ_ACT(girlGObj)->flags20.ll |= 0x10000;
    n = 0;
    for (;;) {
        if ((int)(GOBJ_ACT(girlGObj)->flags20.ll >> 20) & 1) {
            n++;
        } else {
            n = 0;
        }
        if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 3 < n) {
            iosOmSendMail(girlGObj, 109, girlGObj);
            n = 0;
        }
        _ACTWait(1);
    }
}

/* The model-on watcher's mail record: it installs actSt04aModelOffChk here
   and posts it. Word 0 of each entry is the mail id the entry answers (430
   the actor post, 429 the trailing entry); .func is filled in at run time.
   Named for the thread that owns and posts it. */
static ActMail model_on[2] = {{430}, {429}}; /* derived name */

static void actSt04aModelOnChk(GObj *volatile self)
{
    ActSt04A *sub = ((PObjGObjSt04A *)self)->act;

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(648)->active = 1;

    model_on[0].func = actSt04aModelOffChk;
    sub->mail = model_on;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

/* The model-off watcher's own mail record (installs actSt04aModelOnChk). */
static ActMail model_off[2] = {{430}, {429}}; /* derived name */

static void actSt04aModelOffChk(GObj *volatile self)
{
    ActSt04A *sub = ((PObjGObjSt04A *)self)->act;

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(648)->active = 0;

    model_off[0].func = actSt04aModelOnChk;
    sub->mail = model_off;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif
#endif
