#include "StageManager.h"
#include "debug.h"
#include "gamesys.h"
#include "layout_texture.h"
#include "sceneManager.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "jimaku.h"
#include "way_llf.h"
#include "brain.h"
#include "generator.h"
#include "camera-root.h"
#include "fightSound.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "staticBlur.h"
#include "windManager.h"
#include <libvu0.h>
#include <string.h>
#include "act.h"
#include "gobj_process.h"
#include "typedef.h"
#include "commonact.h"
#include "streamMotionManager.h"
#include "kanbanBoot.h"
#include "layout_action.h"
#include "script.h"
#include "main.h"
#include "e3.h"

/* .sdata: the title stream's handle, the capsule's, the cage fall's, the
   first gate's, and the stone statue's and its volume byte. */
static SqEntry *e3title = 0; /* derived name */

SqEntry *e3capsule = 0;

static SqEntry *e3cage = 0; /* derived name */

SqEntry *e3gate1st = 0;

unsigned int sekizo_e3 = 0;

unsigned char sekizo_e3_vol = 0;

/* actE3Warning's, first in this build's run */
static ActMail warning_mes[2] = {{377}, {376}}; /* derived name */

static ActMail title_mes[2] = {{377}, {376}}; /* derived name */

static ActMail inst1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail capsule_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorMain_mes[2] = {{356, actE3DoorSwitch}, {376}}; /* derived name */

static ActMail door_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{377}, {376}}; /* derived name */

static float doorUpPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f}; /* derived name */

static ActMail st13cIntro_mes[2] = {{377}, {376}}; /* derived name */

static ActMail cageFallReady_mes[2] = {{377}, {376}}; /* derived name */

static ActMail cageFall_mes[2] = {{377}, {376}}; /* derived name */

static ActMail st01bEne_mes[2] = {{377}, {376}}; /* derived name */

static float st09aSekizoPos[4] = {1548.0f, -412.0f, -608.0f, 0.0f}; /* derived name */

static ActMail st09aSekizo_mes[2] = {{377}, {376}}; /* derived name */

/* actE3Gate's (this build has no stage 9 bridge records) */
static ActMail gate_mes[2] = {{377}, {376}}; /* derived name */

/* main.c's: wakes the boot thread to hand the disc back to the menu (the
   stage scripts that include main.h keep a static flag of this name) */
void demoEnd(void);

void actE3Title(GObj *volatile self)
{
    GObj *x = self;
    Act *sub;

    if (InterStageSwitchLock != 0) {
        demoEnd();
        _ACTWait(0);
    }

    sub = (Act *)actInitialize(self);

    _ACTWait(1);

    enable_game_pause = 0;
    scpBoyControlReadDisable = 1;

    e3title = 0;
    scpAdpcmPlayRequestFunc(8, &e3title, 0, 1, 0);

    while (kanbanBootEnd == 0) {
        _ACTWait(1);
    }

    systemStatus[11] = 7;

    scpFadeOut(255.0f, 0, 0, 0);

    while (e3title == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    if ((int)boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

    ACTGame_StageChangeGObjID(47, 1, 39);
    ACTGame_StageChangeGObjID(124, 2, 40);

    stage_SetAnimation(27, 0, 0);
    stage_SetAnimation(21, 0, -1);
    stage_SetAnimation(30, 0, 0);
    stage_SetAnimation(28, 0, 0);
    stage_SetAnimation(31, 0, 0);
    stage_SetAnimation(33, 0, 0);

    title_mes[0].func = actE3TitleChk;
    sub->mail = title_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actE3TitleChk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    actCreateSubThread(actE3TitleFrameChk, 21);

    while ((pad[0].flags & 0x840) == 0) {
        _ACTWait(1);
    }

    gflagOn(309);

    AdpcmPlay(e3title->stream);

    scpFadeOut(4.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, boyGObj, 0, 255.0f, 16.0f);
}

void actE3TitleFrameChk(GObj *volatile self)
{
    int i;

    stage_SetAnimation(745, 1, 0);

    while (stage_ContinueAnimation(745, 746) == 0) {
        _ACTWait(1);
    }

    stage_SetLoopFlag(746, 1);

    i = 0;
    while (i++ < (60 - systemStatus[0] * 10) / systemStatus[1] * 45) {
        _ACTWait(1);
    }

    stage_SetAnimation(747, 1, 0);

    while (stage_CheckAnimationFinish(747) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(309) == 0) {
        debug_StdPrintfDummy("mpeg_start\n");

        if (e3title != 0) {
            soundDataClose(e3title);
        }

        mpegPlayReturnStage = 92;
        stage_after_skipping_demo = 92;

        stgmgrForceSwitchWithFade(100, 4.0f, 4.0f);
    }
}

void actE3Inst1Chk(GObj *volatile self)
{
    GObj *x = self;
    int i;

    actInitialize(self);
    _ACTWait(1);

    i = 0;
    while (i++ < (60 - systemStatus[0] * 10) / systemStatus[1] * 10 &&
           (pad[0].flags & 0x840) == 0) {
        _ACTWait(1);
    }

    soundSeDefPlay(1302, 0, 0, 1);

    scpFadeOut(3.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, boyGObj, 0, 255.0f, 16.0f);
}

void actE3Capsule(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if (gflagChk(310) == 0) {
        if ((int)boyGObj != 0) {
            scpPlayMot(boyGObj, 0);
        }

        scpFadeOut(255.0f, 0, 0, 0);

        lt_switch_layout(51);

        stage_SetAnimation(27, 0, 0);
        stage_SetAnimation(21, 0, -1);
        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(28, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);

        capsule_mes[0].func = actE3CapsuleChk;
        sub->mail = capsule_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(27, 0, -1);
        stage_SetAnimation(21, 0, -1);
        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(28, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
    }
}

/* .sbss: the capsule demo's sub-thread and the flag that thread raises when
   the demo has finished. */
static GProc *capsuleDemoThread; /* derived name */

static int demoEndFlag; /* derived name */

void actE3CapsuleDemoCancel(GObj *volatile self)
{
    while (demoEndFlag == 0 || (pad[0].flags & 0x800) == 0) {
        _ACTWait(1);
    }

    iosThreadSetPri(&capsuleDemoThread->thread, 34);

    scpFadeOut(8.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    soundDataClose(e3capsule);

    stage_SetAnimation(27, 0, -1);
    stage_SetAnimation(21, 0, -1);
    stage_SetAnimation(473, -1, -2);
    stage_SetAnimation(478, -1, -2);
    stage_SetAnimation(480, -1, -2);
    stage_SetAnimation(481, -1, -2);
    stage_SetAnimation(482, -1, -2);
    stage_SetAnimation(483, -1, -2);
    stage_SetAnimation(484, -1, -2);
    stage_SetAnimation(485, -1, -2);
    stage_SetAnimation(503, 1, 0);

    scpFadeIn(6.0f);

    actCreateSubThread(actE3CapsuleDemoEnd, 21);
}

void actE3CapsuleDemo(GObj *volatile self)
{
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);

    demoEndFlag = 1;
    actCreateSubThread(actE3CapsuleDemoCancel, 21);

    stage_SetAnimation(473, 1, 0);
    _ACTWait(95);
    stage_SetAnimation(27, 1, 0);

    while (stage_ContinueAnimation(473, 478) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 291);

    while (stage_ContinueAnimation(478, 480) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 291);

    while (stage_ContinueAnimation(480, 481) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 295);

    while (stage_ContinueAnimation(481, 482) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 296);

    while (stage_ContinueAnimation(482, 483) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 297);

    while (stage_ContinueAnimation(483, 484) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 298);

    while (stage_ContinueAnimation(484, 485) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 299);

    while (stage_ContinueAnimation(485, 503) == 0) {
        _ACTWait(1);
    }

    demoEndFlag = 0;
    actCreateSubThread(actE3CapsuleDemoEnd, 21);
}

void actE3St13cInit(void)
{
    SetWayGroupActive(7, 0);

    if (gflagChk(312) != 0) {
        SetWayGroupActive(9, 0);
    }
}

void actE3CageFall(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if (gflagChk(312) == 0) {
        stage_SetAnimation(57, 0, 0);
        stage_SetAnimation(53, 0, -1);

        if ((int)girlGObj == 0) {
            _ACTWait(0);
        }

        scpPlayPosSet(girlGObj, -30.0f, -436.0f, -1.0f);

        cageFall_mes[0].func = actE3CageFallChk;
        sub->mail = cageFall_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(57, 0, 0);
        stage_SetAnimation(55, 0, -1);
        stage_SetAnimation(56, 0, -1);
    }
}

void actE3CageFallChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 160.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    gflagOn(312);

    while (e3cage == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(e3cage->stream);

    actCreateSubThread(actE3CageFallDemo, 21);

    stage_SetAnimation(55, 1, 0);
    stage_SetAnimation(56, 1, 0);

    actCreateSubThread(actE3CageFallEffect, 21);

    while (stage_CheckAnimationFinish(55) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(9, 0);
}

void actE3CageFallDemo(GObj *volatile self)
{
    float dir[4];

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    stage_SetAnimation(509, 1, 0);

    scpPlayMot(boyGObj, 318);

    while (stage_ContinueAnimation(509, 510) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(510, 511) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(girlGObj, 707);

    while (stage_ContinueAnimation(511, 512) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 708);

    while (stage_ContinueAnimation(512, 513) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 319);

    while (stage_ContinueAnimation(513, 514) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 328);

    while (stage_ContinueAnimation(514, 515) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 709);

    while (stage_ContinueAnimation(515, 516) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 710);

    _ACTWait(240);

    gflagOn(316);

    fightSoundProcessRequestStart();

    while (stage_ContinueAnimation(516, 750) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 326);

    while (stage_ContinueAnimation(750, 751) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 329);

    while (stage_CheckAnimationFrame(751, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 327);

    while (stage_CheckAnimationFinish(751) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    gflagOn(332);

    gamesysObjInfoPosSetStage(boyGObj, GOBJ_ACT(boyGObj)->infoPos, 0, stage_no);

    CheckPoint();

    gflagOff(332);
}

inline void actE3CapsuleDemoEnd(GObj *volatile self)
{
    scpPlayMot(boyGObj, 310);

    while (stage_CheckAnimationFinish(503) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);

    {
        EffectArg ofs = {{-1000.0f, 0.0f, -2200.0f, 1.0f}};
        float dir[4];

        sceVu0SubVector(dir, &ofs, test_CURRENTROOT(boyGObj));
        scpPlayMotDir(boyGObj, dir);
    }

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    enable_game_pause = 1;
}

void actE3CageFallEffect(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 0:
            gflagOn(21);
            break;
        case 64:
            iosPadActRequest(boyPad, 17);
            {
                EffectArg b1 = {{-88.0f, -50.0f, -1.0f, 1.0f}};
                scpEffectStart(&b1, 0);
            }
            {
                EffectArg b2 = {{-96.0f, -45.0f, 34.0f, 1.0f}};
                scpEffectStart(&b2, 0);
            }
            break;
        case 68: {
            EffectArg b3 = {{72.0f, -50.0f, 8.0f, 1.0f}};
            scpEffectStart(&b3, 0);
        }
            {
                EffectArg b4 = {{80.0f, -50.0f, 2.0f, 1.0f}};
                scpEffectStart(&b4, 0);
            }
            break;
        case 96: {
            EffectArg b5 = {{-27.0f, -50.0f, 100.0f, 1.0f}};
            scpEffectStart(&b5, 0);
        }
            {
                EffectArg b6 = {{-56.0f, -50.0f, 66.0f, 1.0f}};
                scpEffectStart(&b6, 0);
            }
            {
                EffectArg b7 = {{-5.0f, -50.0f, 42.0f, 1.0f}};
                scpEffectStart(&b7, 0);
            }
            break;
        case 180:
            iosPadActRequest(boyPad, 15);
            break;
        case 300: {
            EffectArg b8 = {{-10.0f, 0.0f, 466.0f, 1.0f}};
            scpEffectStart(&b8, 0);
        }
            {
                EffectArg b9 = {{-25.0f, 0.0f, 450.0f, 1.0f}};
                scpEffectStart(&b9, 0);
            }
            break;
        case 380:
            iosPadActRequest(boyPad, 16);
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
    } while (t < 400.0f);
}

void actE3St09aSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    soundSeDefPlay(1290, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1291, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1292, 0, st09aSekizoPos, 1);

    if (gflagChk(317) == 0) {
        stage_SetAnimation(307, 0, 0);

        st09aSekizo_mes[0].func = actE3St09aSekizoChk;
        sub->mail = st09aSekizo_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(307, 0, -1);
    }
}

inline void actE3St09aGirlWay(GObj *volatile self)
{
    EffectArg buf = {{-1410.0f, -100.0f, 1950.0f, 0.0f}};
    long long way[2];

    _SCPMoveCharactorByWay(girlGObj, 0, buf.f, 100.0f, 0);

    memset(way, 0, 16);
    RequestStageChangeDirect(girlGObj, 99, way, 180);

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
    brainUnlockGirl();
}

void actE3St09aSekizoChk(GObj *volatile self)
{
    float dir[4];

    if ((int)girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 ||
           scpTriggerBall(self, girlGObj, 200.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 83) {
        _ACTWait(1);
    }

    scpSekizouCheckPoint();

    scpAdpcmPlayRequestFunc(21, 0, 1, 1, 1);

    scpKillEnemyAll();
    scpMaskGeneratorAll();

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    brainLockGirl();

    gflagOn(317);

    _ACTWait(60);

    stage_SetAnimation(307, 1, 0);

    sekizo_e3 = iosPadActRequest(boyPad, 9);
    sekizo_e3_vol = 128;
    iosPadActVolumeSet(sekizo_e3, 128);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpPlayPosSet(girlGObj, -1410.0f, -100.0f, 1515.0f);
    scpPlayPosSet(boyGObj, -1330.0f, -100.0f, 1515.0f);

    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpBoyControlReadDisable = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpPlayMot(girlGObj, 584);
    scpPlayWaitMotEnd(girlGObj);

    while (stage_CheckAnimationFrame(307, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_e3);

    scpPlayMot(girlGObj, 521);
    scpPlayEnd(girlGObj);

    actCreateSubThread(actE3St09aGirlWay, 21);

    _ACTWait(30);

    scpPlayMot(boyGObj, 254);
    scpPlayWaitMotEnd(boyGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
}

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

void actE3GateChk(GObj *volatile self)
{
    int i;

    if ((int)girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, boyGObj, 3000.0f) == 0) {
        _ACTWait(1);
    }

    StandbyStreamMotion(streamMotion[9].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    lt_switch_layout(51);

    SetWindManager(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 5.0f, 0.0f);

    scpPlayStart(girlGObj);

    reg_SetScissorSw(1);
    SetStaticBlur(0);

    scpAdpcmPlayRequestFunc(7, &e3gate1st, 1, 1, 0);
    while (e3gate1st == 0) {
        _ACTWait(1);
    }

    gflagOn(313);
    _ACTWait(1);

    actCreateSubThread(actE3GateDemo, 21);
    actCreateSubThread(actE3GateJimaku, 21);

    stage_SetAnimation(212, 1, 0);
}

void actE3GateDemo(GObj *volatile self)
{
    scpSearchGobj(2942)->active = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion(scpSearchGobj(2942));

    PlayStreamMotion();

    scpFadeIn(6.0f);

    stage_SetAnimation(527, 1, 0);

    while (stage_CheckAnimationFrame(527, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    AdpcmPlay(e3gate1st->stream);

    while (stage_ContinueAnimation(527, 528) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(528, 529) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(529, 530) == 0) {
        _ACTWait(1);
    }
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

    SetStaticBlur(8);
    SetAuraInspireParam(100.0f);

    stage_SetAnimation(375, 1, 0);

    iosPadActRequest(boyPad, 15);

    soundSeDefPlay(1336, 0, 0, 0);

    while (stage_CheckAnimationFrame(535, 45, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (e3gate1st != 0) {
        scpAdpcmFadeClose(e3gate1st, 80);
    }

    ReinitWindManager();

    lt_switch_layout(50);

    scpFadeOut(4.0f, 255, 255, 255);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (scpSeEnvMasterVolRate > 0.0f) {
        scpSeEnvMasterVolRate -= 0.012f;
        _ACTWait(1);
    }

    InterStageSwitchLock++;
    mpegPlayReturnStage = 92;

    stgmgrForceSwitchWithFadeColor(101, 255.0f, 4.0f, 255, 255, 255);
}

void actE3GateJimaku(GObj *volatile self)
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
        case 300:
            jimaku_msg.sub.block = 25;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1420:
            jimaku_msg.sub.block = 26;
            jimaku_msg.sub.jump = 30;
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

void actE3St01bInit(void)
{
    stage_SetAnimation(147, 0, -1);
}

void actE3Warning(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    enable_game_pause = 0;
    scpBoyControlReadDisable = 1;

    if ((int)boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

    warning_mes[0].func = actE3WarningChk;
    sub->mail = warning_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actE3Inst1(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);
    const StgPre *pre;

    _ACTWait(1);

    scpBoyControlReadDisable = 1;
    if ((int)boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

    pre = &stageData[stage_no];
    stgmgrNextStagePreLoadForceStageSet(exitData[pre->ent[0]].nextStage);

    inst1_mes[0].func = actE3Inst1Chk;
    sub->mail = inst1_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actE3Door(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if (gflagChk(311) == 0) {
        stage_SetAnimation(748, 0, 0);

        door_mes[0].func = actE3DoorMain;
        sub->mail = door_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(748, 0, -1);
    }
}

void actE3CageFallReady(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if (gflagChk(312) == 0) {
        cageFallReady_mes[0].func = actE3CageFallReadyChk;
        sub->mail = cageFallReady_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actE3St13cIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if (gflagChk(315) == 0) {
        st13cIntro_mes[0].func = actE3St13cIntroChk;
        sub->mail = st13cIntro_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actE3St13cGene1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(316) == 0) {
        _ACTWait(1);
    }
    _ACTWait(400);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}

void actE3St13cGene2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(316) == 0) {
        _ACTWait(1);
    }
    Generator_Call(self);
    _ACTWait(120);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}

void actE3Floor(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
}

void actE3St01bEne(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if (gflagChk(314) == 0) {
        st01bEne_mes[0].func = actE3St01bEneChk;
        sub->mail = st01bEne_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actE3St01bGene1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(314) == 0) {
        _ACTWait(1);
    }
    _ACTWait(30);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}

void actE3St01bGene2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(314) == 0) {
        _ACTWait(1);
    }
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}

void actE3St01bGene3(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(314) == 0) {
        _ACTWait(1);
    }
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}

void actE3Gate(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    scpSearchGobj(2942)->active = 0;

    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 0);

    scpFadeOut(255.0f, 0, 0, 0);

    stage_SetAnimation(212, 0, 0);
    stage_SetAnimation(215, 0, 0);

    gate_mes[0].func = actE3GateChk;
    sub->mail = gate_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actE3WarningChk(GObj *volatile self)
{
    GObj *x = self;
    int i;

    actInitialize(self);
    _ACTWait(1);

    stgmgrNextStagePreLoadForceStageSet(92);

    i = 0;
    while (i++ < (60 - systemStatus[0] * 10) / systemStatus[1] * 5) {
        _ACTWait(1);
    }

    scpFadeOut(6.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, boyGObj, 0, 255.0f, 16.0f);
}

void actE3CapsuleChk(GObj *volatile self)
{
    scpSekizouCheckPoint();

    gflagOn(310);

    scpAdpcmPlayRequestFunc(5, &e3capsule, 1, 1, 1);
    while (e3capsule == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    capsuleDemoThread = actCreateSubThread(actE3CapsuleDemo, 21);
}

inline void actE3DoorMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = doorMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

inline void actE3DoorSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    doorSwitch_mes[0].func = actE3DoorUp;
    sub->mail = doorSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actE3DoorUp(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(311);

    _ACTWait(60);

    stage_SetAnimation(748, 1, 0);

    soundSeDefPlay(1171, 0, doorUpPos, 1);

    _ACTWait(30);

    soundSeDefPlay(1172, 0, doorUpPos, 1);

    while (stage_CheckAnimationFinish(748) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

inline void actE3St13cIntroChk(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(315);

    scpBoyControlReadDisable = 1;
    _ACTWait(120);

    stage_SetAnimation(749, 1, 0);

    while (stage_CheckAnimationFinish(749) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
}

inline void actE3CageFallReadyChk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    e3cage = 0;
    _ACTWait(1);
    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(6, &e3cage, 1, 1, 0);
}

inline void actE3St01bEneChk(GObj *volatile self)
{
    if ((int)girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    _ACTWait(30);

    gflagOn(314);

    stage_SetAnimation(146, 1, 0);

    while (stage_CheckAnimationFinish(146) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
}
