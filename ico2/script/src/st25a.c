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

/* .sdata: the ADPCM request slots the scenes hand scpAdpcmPlayRequestFunc
   and wait on, and conte12's flag. */
static SqEntry *conte11 = 0; /* derived name */

SqEntry *conte12 = 0;

SqEntry *sd2 = 0;

static int conte12Flag = 0; /* derived name */

SqEntry *dead = 0;

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

/* the two face-shadow textures ConteQueenDead scrolls the UVs of. */
const char faceShadowTex[] = "face_sadow_sd"; /* script.c scrolls it too */

const char faceShadowTex00[] = "face_sadow_sd_00";

/* The offset the sekika boy is dropped by. */
static const Vec4St25A sekikaOfs = {{2000.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

static const char streamWaitFmt[] =
    "Now waiting for standby stream motion system... %d\n"; /* derived name */

/* The eighteen stage animations the cancelled ending restores. */
static const AnimSet18 cancelAnimSet = {
    /* derived name */
    {709, 710, 711, 712, 713, 714, 715, 716, 717, 718, 719, 720, 721, 722, 723, 724, 725, 726}};

/* Where the boy is put back when the ending is cancelled. */
static const Vec4St25A cancelBoyPos = {
    {-1472.7711f, 928.20026f, -18.074427f, 0.0f}}; /* derived name */

static const char queenBallScrTexture[] = "queen_ball_scr"; /* derived name */

static const char sekikaBoyTexture[] = "sekika_boy"; /* derived name */

/* .data: ten actor mail records.  Each is
   the usual pair, the 393 entry whose handler the sender fills in and the 392
   terminator.  queen_appear_mes is the only one another TU sends, so it is the
   only global of the ten. */
static ActMail queen_before_mes[2] = {{393}, {392}}; /* derived name */

ActMail queen_appear_mes[2] = {{393}, {392}};

static ActMail queen_talk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail queen_dead_mes[2] = {{393}, {392}}; /* derived name */

static ActMail queen_attack_mes[2] = {{393}, {392}}; /* derived name */

void actSt25aQueenBeforeChk(GObj *volatile self);
void actItouQueenAttackChk(GObj *volatile self);
void actConte11(GObj *volatile self);
void actConte11Jimaku(GObj *volatile self);

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

void actConte11(GObj *volatile self)
{
    Vec4St25A ofs;
    float dir[4];

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

    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    while (stage_ContinueAnimation(689, 690) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(690, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    scpPlayMot(scpSearchGobj(1942), 1046);

    scpPlayMot(boyGObj, 0);
    ofs = sekikaOfs;
    sceVu0SubVector(dir, &ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFinish(690) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSekizouCheckPoint();

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

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

void actSt25aQueenTalkChk(GObj *volatile self)
{
    TalkWork w;
    unsigned int i;
    unsigned int n;
    int cancel;
    GProc *th1;
    GProc *th2;

    conte12 = sd2 = 0;

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0 || gflagChk(301) == 0) {
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

    gflagOn(302);

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
        scpAdpcmFadeClose(conte12, 192);

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
        scpLinkBGAtoLayoutedTarget(1951, 422);

        scpSearchGobj(1951)->active = 1;
        stage_SetAnimation(135, -1, -2);
        SelectBoyCrown(boyGObj, 1);

        stage_SetAnimation(484, 0, -1);
        stage_SetAnimation(488, 0, -1);
        stage_SetAnimation(489, 0, -1);

        stage_SetAnimation(726, 1, -1);
        jimakuUndisp(&jimaku_msg);

        w.v[0] = cancelBoyPos;
        SetDirectRootPosition(boyGObj, &w.v[0]);

        if (eventDone == 0) {
            QueenStartAttack();
            gflagOn(303);
        }

        _ACTWait(1);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(3.0f);
    }

    gflagOn(304);

    scpPlayMot(scpSearchGobj(1942), 1013);
    scpPlayPosSet(scpSearchGobj(1942), 1650.0f, 625.0f, 0.0f);

    memset(w.v[1].f, 0, 16);
    w.v[1].f[3] = 1.0f;
    sceVu0SubVector(w.v[2].f, w.v[1].f, test_CURRENTROOT(scpSearchGobj(1942)));
    scpPlayMotDir(scpSearchGobj(1942), w.v[2].f);
    scpPlayEnd(scpSearchGobj(1942));

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    CameraSetCameraSet(51);

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(40, &sd2, 1, 0, 1);

    stage_SetAnimation(137, -1, -2);

    stage_SetLoopFlag(138, 1);

    stage_SetAnimation(138, 1, 0);
}

void actConte12(GObj *volatile self)
{
    conte12Flag = 0;

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
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(719, 720) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(409, 1, 0);

    while (stage_ContinueAnimation(720, 721) == 0) {
        _ACTWait(1);
    }

    DeleteBoyWeapon();
    SelectBoyCrown(boyGObj, 1);
    stage_SetAnimation(135, 1, 0);
    stage_SetAnimation(484, 1, 0);

    iosPadActRequest(boyPad, 15);
    while (stage_CheckAnimationFrame(721, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    while (stage_CheckAnimationFrame(721, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    while (stage_CheckAnimationFrame(721, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    while (stage_CheckAnimationFrame(721, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(721, 722) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(488, 1, 0);

    while (stage_ContinueAnimation(722, 723) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(489, 1, 0);

    scpLinkBGAtoLayoutedTarget(1951, 422);

    scpSearchGobj(1951)->active = 1;

    stage_SetAnimation(135, -1, -2);

    while (stage_ContinueAnimation(723, 724) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(724, 725) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(725, 726) == 0) {
        _ACTWait(1);
    }

    eventDone = 1;
    QueenStartAttack();
    gflagOn(303);

    ScpCallCameraTargetOff();

    while (stage_CheckAnimationFinish(726) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

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

void actSt25aQueenDeadChk(GObj *volatile self)
{
    unsigned int i;

    dead = 0;
    while (QueenInqDead() == 0) {
        _ACTWait(1);
    }

    iosPadActRequest(boyPad, 16);

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
    }

    scpKillEnemyAll();

    gflagOn(306);
    gflagOn(5);

    scpAdpcmPlayRequestFunc(41, &dead, 0, 1, 1);
    while (dead == 0) {
        _ACTWait(1);
    }

    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[3]].nextStage);
    stgmgrNextStagePreLoadForceNoCancel(1);

    scpSearchGobj(1942)->active = 1;
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(scpSearchGobj(1942));
    PlayStreamMotion();

    actCreateSubThread(actConte13Jimaku, 21);

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
        _ACTWait(1);
    }

    GOBJ_SUB(scpSearchGobj(1942))->streamScale = 1;
    while (stage_ContinueAnimation(731, 732) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(732, 733) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(413, 1, 0);
    iosPadActRequest(boyPad, 15);
    DeleteBoyWeapon();
    stage_SetAnimation(422, -1, -2);
    stage_SetAnimation(136, 1, 0);

    while (stage_ContinueAnimation(733, 734) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(734, 735) == 0) {
        _ACTWait(1);
    }

    SelectBoyCrown(boyGObj, 2);
    stage_SetAnimation(485, 1, 0);

    while (stage_CheckAnimationFrame(735, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_ContinueAnimation(735, 736) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(486, 1, 0);

    while (stage_CheckAnimationFrame(736, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    scpSearchGobj(1942)->active = 0;
    stage_SetLoopFlag(483, 0);

    while (stage_ContinueAnimation(736, 738) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFrame(738, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    DeleteStreamMotionManager();

    while (stage_CheckAnimationFinish(738) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(4, boyGObj, 0, 1.0f, 8.0f);
}

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

void actSt25aGenerator(GObj *volatile self)
{
    Generator_Mask(self);
}

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

void actSt25aQueenDead(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    queen_dead_mes[0].func = actSt25aQueenDeadChk;
    sub->mail = queen_dead_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actItouQueenAttack(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    queen_attack_mes[0].func = actItouQueenAttackChk;
    sub->mail = queen_attack_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSwordEff(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpLinkBGAtoLayoutedTarget(1902, 422);
}

void actSwordEffXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (scpGameStat_BoyWeaponkind() == 5) {
        scpLinkBGAtoLayoutedTarget(1902, 422);
    } else {
        stage_SetAnimation(422, -1, -2);
    }
}

void actSt25aQueenBeforeChk(GObj *volatile self)
{
    conte11 = 0;
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(300);
    jimakuBegin(&jimaku_msg);
    scpAdpcmPlayRequestFunc(38, &conte11, 1, 1, 0);
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

void actSt25aQueenDeadEvent(int x)
{
    volatile int local = x;
}

void actItouQueenAttackChk(GObj *volatile self)
{
    while (1) {
        while (ForMotionViewer_GetCurrentMotion(scpSearchGobj(3225)) != 1019) {
            _ACTWait(1);
        }
        tex_SetUVScroll(queenBallScrTexture, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 1);
        _ACTWait(1);
    }
}
