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
#include "windManager.h"
#include "streamMotionManager.h"
#include <libvu0.h>
#include "e3.h"
#include "typedef.h"
#include "Matrix.h"
#include "script.h"
#include "jimaku.h"
#include "main.h"

static void finishCallBackFunc(struct GObj *obj);

/* this file's own view of Act (the shared one is in typedef.h) */
typedef struct ActSt04A { /* field names derived */
    char pad0[32];        /* 0x00 */
    ActStatus flags20;    /* 0x20 */
    char pad28[8];        /* 0x28 */
    int actMode;          /* 0x30, the current action mode */
    char pad34[124];      /* 0x34 */
    ActMail *mainMail;    /* 0xB0 */
    ActMail *mail;        /* 0xB4 */
    char padB8[936];      /* 0xB8 */
    int torchAnim;        /* 0x460, the stage animation the lit torch plays */
    GObj *torchObj;       /* 0x464, the torch the ball must reach */
    int torchFlag;        /* 0x468, the game flag raised once it is lit */
} ActSt04A;               /* derived name */

/* .data: each action's mail pair, the check handler stored into its first
   entry at run time, and the matrix finishCallBackFunc writes into every
   joint. */
static ActMail gate_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gate_open_mail[2] = {{393}, {392}}; /* derived name */

static Mtx44 jointMtxInit = {{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                              1.0f, 0.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

static ActMail gate_open2_ready_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gate_open2_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gate_open3_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gate_l_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gate_r_mail[2] = {{393}, {392}}; /* derived name */

static ActMail torch1_mail[2] = {{393}, {392}}; /* derived name */

static ActMail girl_sit_mail[2] = {{393}, {392}}; /* derived name */

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

    scpSearchGobj(548)->active = 0;

    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(521), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(522), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(523), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(524), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(525), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(526), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(527), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(528), 10.0f, 0.01f, 1.0f);

    if (gflagChk(123) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetLoopFlag(483, 0);

        stage_SetAnimation(237, 0, 0);
        stage_SetAnimation(240, 0, 0);

        gflagOff(356);

        gate_mail[0].func = actSt04aGateChk;
        act->mail = gate_mail;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetLoopFlag(483, 0);

        stage_SetAnimation(237, 0, -1);
        stage_SetAnimation(240, 0, 0);
    }
}

void actSt04aGateChk(GObj *volatile self)
{
    GProc *th0;
    GProc *th1;
    GProc *th2;
    int i;
    int n;

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

    stage_SetAnimation(237, 1, 0);

    scpSearchGobj(548)->active = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion(scpSearchGobj(548));

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
                {576, 577, 578, 579, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589,
                 590, 591, 592, 593, 594, 595, 596, 597, 598, 599, 600, 601}}; /* derived name */
            AnimList26 anim;
            unsigned int j;

            anim = gateOpenAnims;
            for (j = 0; j < 26; j++) {
                stage_SetAnimation(anim.v[j], 1, -1);
                _ACTWait(1);
            }
        }

        jimakuUndisp(&jimaku_msg);

        stage_SetAnimation(237, 0, -1);
        stage_SetAnimation(601, 1, -1);
        stage_SetAnimation(410, -1, -2);
        stage_SetAnimation(412, -1, -2);

        scpSearchGobj(548)->active = 0;

        stage_SetLoopFlag(483, 0);
        stage_SetAnimation(483, -1, -2);

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

    iosOmSendMail(girlGObj, 59, boyGObj);

    scpBoyControlReadDisable = 0;

    ReinitWindManager();

    lt_switch_layout(50);

    SetStaticBlur(1);
}

void actSt04aConte06(GObj *volatile self)
{
    stage_SetAnimation(576, 1, 0);

    AdpcmPlay(gate1st->stream);

    while (stage_ContinueAnimation(576, 577) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(577, 578) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(578, 579) == 0) {
        _ACTWait(1);
    }

    _ACTWait(240);

    gate_yure_low = iosPadActRequest(boyPad, 9);
    gate_yure_low_vol = 64;
    iosPadActVolumeSet(gate_yure_low, 64);

    while (stage_ContinueAnimation(579, 580) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(580, 581) == 0) {
        _ACTWait(1);
    }

    reg_SetScissorSw(0);

    while (stage_ContinueAnimation(581, 582) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(582, 583) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(583, 584) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(410, 1, 0);

    iosPadActRequest(boyPad, 15);

    stage_SetLoopFlag(483, 1);
    stage_SetAnimation(483, 1, 0);

    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(47, 0, 483, 0);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    while (stage_ContinueAnimation(584, 585) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(585, 586) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(gate_yure_low);

    while (stage_CheckAnimationFrame(586, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    while (stage_ContinueAnimation(586, 587) == 0) {
        _ACTWait(1);
    }
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

    _ACTWait(120);

    stage_SetAnimation(412, 1, 0);

    iosPadActRequest(boyPad, 15);

    while (stage_ContinueAnimation(596, 597) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(548)->active = 0;

    stage_SetLoopFlag(483, 0);
    stage_SetAnimation(483, -1, -2);

    while (stage_ContinueAnimation(597, 598) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(598, 599) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(599, 600) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(600, 601) == 0) {
        _ACTWait(1);
    }

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(601) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

/* .sdata: the rest of the gate and torch stream handles,
   then the pad shakes and their volumes (declared in st04a.h for
   actSt04aConte06). */
static SqEntry *gate_open2 = 0; /* derived name */

static SqEntry *conte09_2 = 0; /* derived name */

SqEntry *gate_ready_l = 0;

SqEntry *gate_ready_r = 0;

SqEntry *torch = 0;

int gate_yure_low = 0;

unsigned char gate_yure_low_vol = 0;

int yure1 = 0;

unsigned char vol1 = 0;

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

typedef struct AnimList { /* field names derived */
    int v[13];
} AnimList; /* derived name */

/* .rodata, used here and by actConte09_2: the first lift offset, declared
   ahead and defined with the second after actSt04aGateOpenChk. */
static const ConstVec liftOfs1;

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
            static const AnimList gateOpen2Anims = {{640, 641, 642, 643, 644, 645, 646, 647, 648,
                                                     649, 650, 651, 652}}; /* derived name */
            AnimList anim;
            unsigned int j;

            anim = gateOpen2Anims;
            for (j = 0; j < 13; j++) {
                stage_SetAnimation(anim.v[j], 1, -1);
                _ACTWait(1);
            }
        }

        jimakuUndisp(&jimaku_msg);

        stage_SetAnimation(652, 1, -1);
        stage_SetAnimation(242, 0, -1);
        stage_SetAnimation(240, 0, -1);
        stage_SetAnimation(246, 0, -1);
        stage_SetAnimation(238, 0, -1);

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

static const ConstVec liftOfs1 = {{0.0f, 0.0f, 6000.0f, 1.0f}}; /* derived name */

static const ConstVec liftOfs2 = {{-5000.0f, 0.0f, 5300.0f, 1.0f}}; /* derived name */

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

    stage_SetAnimation(640, 1, 0);

    while (stage_ContinueAnimation(640, 641) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(641, 642) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(246, 1, 0);

    while (stage_CheckAnimationFrame(642, 125, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 15);

    scpKillEnemyAll();

    while (stage_ContinueAnimation(642, 643) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(643, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(643, 644) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(238, 1, 0);

    while (stage_ContinueAnimation(644, 645) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(645, 646) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(646, 647) == 0) {
        _ACTWait(1);
    }

    _ACTWait(300);

    stage_SetAnimation(242, 1, 0);

    _ACTWait(120);

    yure1 = iosPadActRequest(boyPad, 10);
    vol1 = 128;
    iosPadActVolumeSet(yure1, 128);

    while (stage_ContinueAnimation(647, 648) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(240, 1, 0);

    while (stage_ContinueAnimation(648, 649) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(yure1);

    while (stage_ContinueAnimation(649, 650) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(650, 651) == 0) {
        _ACTWait(1);
    }

    scpDispOnAllWithKind(19);

    gflagOn(126);

    while (stage_ContinueAnimation(651, 652) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFinish(652) == 0) {
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

    GOBJ_ACT(girlGObj)->flags20.ll &= ~0x8;
    scpPlayMotReq(girlGObj, 281);

    scpPlayMot(boyGObj, 0);

    ofs[0] = liftOfs2.d[0];
    ofs[1] = liftOfs2.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    lt_switch_layout(51);

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
    scpSearchGobj(624)->active = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion(scpSearchGobj(624));

    PlayStreamMotion();

    scpSetStreamMotionRootOffset(boyGObj, 0.0f, 0.0f, 1.0f);
    scpSetStreamMotionRootOffset(girlGObj, 0.0f, 0.0f, 1.0f);

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
        _ACTWait(1);
    }

    if (scpGameStat_BoyWeaponkind() == 1) {
        stage_SetAnimation(243, 1, 0);
    }
    if (scpGameStat_BoyWeaponkind() == 4 || scpGameStat_BoyWeaponkind() == 5) {
        stage_SetAnimation(244, 1, 0);
    }
    if (scpGameStat_BoyWeaponkind() == 6) {
        stage_SetAnimation(245, 1, 0);
    }

    DeleteBoyWeapon();

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
        _ACTWait(1);
    }

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

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    _ACTWait(1);

    scpSearchGobj(604)->active = 0;

    SetStaticBlur(0);

    tex_SetUVScroll("bridge_shadow_hiro", 0.0f, -0.24f, 0.0f, -0.00029f, 0.0f, -0.35f, 1);

    while (stage_CheckAnimationFrame(678, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    while (stage_ContinueAnimation(678, 679) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(604)->active = 1;

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.45f, 0.0f, -0.0004f, 0.0f, -0.7f, 1);

    while (stage_CheckAnimationFrame(679, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("bridge_shadow_hand", 0.0f, -0.35f, 0.0f, -0.0062f, 0.0f, -0.9f, 1);
    tex_SetUVScroll("bridge_shadow_hiro", 0.0f, -0.5f, 0.0f, -0.001f, 0.0f, -0.61f, 1);

    while (stage_ContinueAnimation(679, 680) == 0) {
        _ACTWait(1);
    }

    shadow_SetLength(GOBJ_SUB(girlGObj), 0.0f);

    while (stage_ContinueAnimation(680, 681) == 0) {
        _ACTWait(1);
    }

    tex_SetUVScroll("bridge_shadow_face", 0.0f, -0.3f, 0.0f, -0.002f, 0.0f, -0.9f, 1);

    SetGirlClothDispSwitch(girlGObj, 1, 0);
    SetGirlClothDispSwitch(girlGObj, 0, 0);
    SetGirlClothDispSwitch(girlGObj, 2, 0);

    _ACTWait(1);

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

    SetStaticBlur(1);

    while (stage_CheckAnimationFrame(682, 90, 0) == 0) {
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

    scpFadeIn(6.0f);

    stage_SetAnimation(259, 1, 0);
    while (stage_CheckAnimationFinish(259) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(4, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actSt04aGateRChk(GObj *volatile self)
{
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
}

void actSt04aTorch1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

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
        }

        torch1_mail[0].func = actSt04aTorch1Chk;
        act->mail = torch1_mail;
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
    }
}

void actSt04aTorch1Chk(GObj *volatile self)
{
    GObj *x = self;
    ActSt04A *act = (ActSt04A *)actInitialize(self);
    _ACTWait(1);

    switch (self->labelId) {
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
        act->torchObj = scpSearchGobj(523);
        act->torchAnim = 251;
        break;
    case 516:
        act->torchFlag = 134;
        act->torchObj = scpSearchGobj(524);
        act->torchAnim = 252;
        break;
    case 517:
        act->torchFlag = 135;
        act->torchObj = scpSearchGobj(525);
        act->torchAnim = 253;
        break;
    case 518:
        act->torchFlag = 136;
        act->torchObj = scpSearchGobj(526);
        act->torchAnim = 254;
        break;
    case 519:
        act->torchFlag = 137;
        act->torchObj = scpSearchGobj(527);
        act->torchAnim = 255;
        break;
    case 520:
        act->torchFlag = 138;
        act->torchObj = scpSearchGobj(528);
        act->torchAnim = 256;
        break;
    }

    while (1) {
        if (scpTriggerBall(self, act->torchObj, 5.0f) != 0) {
            scpBoyControlReadDisable = 1;

            act->torchObj->active = 0;

            stage_SetAnimation(act->torchAnim, 1, 0);

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
}

void actSt04aGateL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(124) == 0) {
        gflagOn(355);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(261, 0, 0);

        gate_l_mail[0].func = actSt04aGateLChk;
        act->mail = gate_l_mail;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt04aGateR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(125) == 0) {
        gflagOn(355);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(259, 0, -1);

        gate_r_mail[0].func = actSt04aGateRChk;
        act->mail = gate_r_mail;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt04aTorchXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    stage_SetAnimation(257, 0, 0);
}

void actSt04aGateOpen2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(127) == 0) {
        scpSearchGobj(624)->active = 0;

        gate_open2_mail[0].func = actSt04aGateOpen2Chk;
        act->mail = gate_open2_mail;
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
    }
}

void actSt04aGateOpen2Ready(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    gate_open2_ready_mail[0].func = actSt04aGateOpen2ReadyChk;
    act->mail = gate_open2_ready_mail;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt04aGirlSit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    girl_sit_mail[0].func = actSt04aGirlSitChk;
    act->mail = girl_sit_mail;
    ACTSendMailCorrect(self, 393);
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

    scpAdpcmPlayRequestFunc(31, &gate_open2, 1, 0, 0);
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
        case 2470:
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

void actSt04aGirlSitChk(GObj *volatile self)
{
    int n;

    while (gflagChk(126) == 0) {
        _ACTWait(1);
    }
    GOBJ_ACT(girlGObj)->flags20.ll |= 0x8;
    n = 0;
    for (;;) {
        if ((int)(GOBJ_ACT(girlGObj)->flags20.ll >> 6) & 1) {
            n++;
        } else {
            n = 0;
        }
        if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 3 < n) {
            iosOmSendMail(girlGObj, 101, girlGObj);
            n = 0;
        }
        _ACTWait(1);
    }
}
