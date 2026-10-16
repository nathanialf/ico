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

void actE3WarningChk(GObj *volatile self)
{
    GObj *x = self;
    int i;

    actInitialize(self);
    _ACTWait(1);

    stgmgrNextStagePreLoadForceStageSet(93);

    i = 0;
    while (i++ < (60 - systemStatus[0] * 10) / systemStatus[1] * 5) {
        _ACTWait(1);
    }

    scpFadeOut(6.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    _ACTWait((int)(float)((60 - systemStatus[0] * 10) / systemStatus[1]));

    RequestStageChange(1, boyGObj, 0, 255.0f, 0.0f);
}

#include "e3.h"

/* .sdata: the title stream's handle, the capsule's, the cage fall's, the
   first gate's, and the stone statue's and its volume word. */
static SqEntry *e3title = 0; /* derived name */

SqEntry *e3capsule = 0;

static SqEntry *e3cage = 0; /* derived name */

SqEntry *e3gate1st = 0;

unsigned int sekizo_e3 = 0;

unsigned char sekizo_e3_vol = 0;

static ActMail warning_mes[2] = {{397}, {396}}; /* derived name */

static ActMail title_mes[2] = {{397}, {396}}; /* derived name */

static ActMail inst1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail capsule_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorMain_mes[2] = {{376, actE3DoorSwitch}, {396}}; /* derived name */

static ActMail door_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{397}, {396}}; /* derived name */

static float doorUpPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f}; /* derived name */

static ActMail st13cIntro_mes[2] = {{397}, {396}}; /* derived name */

static ActMail cageFallReady_mes[2] = {{397}, {396}}; /* derived name */

static ActMail cageFall_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st01bEne_mes[2] = {{397}, {396}}; /* derived name */

static float st09aSekizoPos[4] = {1548.0f, -412.0f, -608.0f, 0.0f}; /* derived name */

static ActMail st09aSekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gate_mes[2] = {{397}, {396}}; /* derived name */

void actE3Title(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    enable_game_pause = 0;
    scpBoyControlReadDisable = 1;

    gflagOff(324);

    e3title = 0;
    scpAdpcmPlayRequestFunc(5, &e3title, 0, 1, 0);

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

    stage_SetAnimation(31, 0, 0);
    stage_SetAnimation(25, 0, -1);
    stage_SetAnimation(34, 0, 0);
    stage_SetAnimation(32, 0, 0);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(37, 0, 0);

    title_mes[0].func = actE3TitleChk;
    sub->mail = title_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actE3TitleChk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    actCreateSubThread(actE3TitleFrameChk, 21);

    while (gflagChk(324) != 0 || (pad[0].flags & 0x840) == 0) {
        _ACTWait(1);
    }

    gflagOn(325);
    debug_StdPrintfDummy("game_start\n");

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

    stage_SetAnimation(797, 1, 0);

    while (stage_ContinueAnimation(797, 798) == 0) {
        _ACTWait(1);
    }

    stage_SetLoopFlag(798, 1);

    i = 0;
    while (i++ < (60 - systemStatus[0] * 10) / systemStatus[1] * 45) {
        _ACTWait(1);
    }

    stage_SetAnimation(799, 1, 0);

    while (stage_CheckAnimationFinish(799) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(325) == 0) {
        debug_StdPrintfDummy("mpeg_start\n");

        gflagOn(324);

        if (e3title != 0) {
            soundDataClose(e3title);
        }

        mpegPlayReturnStage = 93;
        stage_after_skipping_demo = 93;

        stgmgrForceSwitchWithFade(101, 4.0f, 4.0f);
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

    soundSeDefPlay(1353, 0, 0, 1);

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

    if ((int)girlGObj == 0) {
        ScpCallCameraOff();
    }

    if (gflagChk(326) == 0) {
        if ((int)boyGObj != 0) {
            scpPlayMot(boyGObj, 0);
        }

        scpFadeOut(255.0f, 0, 0, 0);

        lt_switch_layout(51);

        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(25, 0, -1);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);

        capsule_mes[0].func = actE3CapsuleChk;
        sub->mail = capsule_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, -1);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
    }
}

/* .sbss: the capsule demo's sub-thread and the flag that thread raises when
   the demo has finished. */
static GProc *capsuleDemoThread; /* derived name */

static int demoEnd;

void actE3CapsuleDemoCancel(GObj *volatile self)
{
    while (demoEnd == 0 || (pad[0].flags & 0x800) == 0) {
        _ACTWait(1);
    }

    iosThreadSetPri(&capsuleDemoThread->thread, 34);

    scpFadeOut(8.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    soundDataClose(e3capsule);

    stage_SetAnimation(31, 0, -1);
    stage_SetAnimation(25, 0, -1);
    stage_SetAnimation(523, -1, -2);
    stage_SetAnimation(528, -1, -2);
    stage_SetAnimation(530, -1, -2);
    stage_SetAnimation(531, -1, -2);
    stage_SetAnimation(532, -1, -2);
    stage_SetAnimation(533, -1, -2);
    stage_SetAnimation(534, -1, -2);
    stage_SetAnimation(535, -1, -2);
    stage_SetAnimation(553, 1, 0);

    scpFadeIn(6.0f);

    actCreateSubThread(actE3CapsuleDemoEnd, 21);
}

void actE3CapsuleDemo(GObj *volatile self)
{
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);

    demoEnd = 1;
    actCreateSubThread(actE3CapsuleDemoCancel, 21);

    stage_SetAnimation(523, 1, 0);
    _ACTWait(95);
    stage_SetAnimation(31, 1, 0);

    while (stage_ContinueAnimation(523, 528) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 282);

    while (stage_ContinueAnimation(528, 530) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 282);

    while (stage_ContinueAnimation(530, 531) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 286);

    while (stage_ContinueAnimation(531, 532) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 287);

    while (stage_ContinueAnimation(532, 533) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 288);

    while (stage_ContinueAnimation(533, 534) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 289);

    while (stage_ContinueAnimation(534, 535) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 290);

    while (stage_ContinueAnimation(535, 553) == 0) {
        _ACTWait(1);
    }

    demoEnd = 0;
    actCreateSubThread(actE3CapsuleDemoEnd, 21);
}

void actE3St13cInit(void)
{
    SetWayGroupActive(7, 0);

    if (gflagChk(328) != 0) {
        SetWayGroupActive(9, 0);
    }
}

void actE3CageFall(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if (gflagChk(328) == 0) {
        stage_SetAnimation(63, 0, 0);
        stage_SetAnimation(59, 0, -1);

        if ((int)girlGObj == 0) {
            _ACTWait(0);
        }

        scpPlayPosSet(girlGObj, -30.0f, -436.0f, -1.0f);

        cageFall_mes[0].func = actE3CageFallChk;
        sub->mail = cageFall_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(63, 0, 0);
        stage_SetAnimation(61, 0, -1);
        stage_SetAnimation(62, 0, -1);
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

    gflagOn(328);

    while (e3cage == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(e3cage->stream);

    actCreateSubThread(actE3CageFallDemo, 21);

    stage_SetAnimation(61, 1, 0);
    stage_SetAnimation(62, 1, 0);

    actCreateSubThread(actE3CageFallEffect, 21);

    while (stage_CheckAnimationFinish(61) == 0) {
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

    stage_SetAnimation(559, 1, 0);

    scpPlayMot(boyGObj, 309);

    while (stage_ContinueAnimation(559, 560) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(560, 561) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(girlGObj, 681);

    while (stage_ContinueAnimation(561, 562) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 682);

    while (stage_ContinueAnimation(562, 563) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 310);

    while (stage_ContinueAnimation(563, 564) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 319);

    while (stage_ContinueAnimation(564, 565) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 683);

    while (stage_ContinueAnimation(565, 566) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 684);

    _ACTWait(240);

    gflagOn(332);

    fightSoundProcessRequestStart();

    while (stage_ContinueAnimation(566, 802) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 317);

    while (stage_ContinueAnimation(802, 803) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 320);

    while (stage_CheckAnimationFrame(803, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 318);

    while (stage_CheckAnimationFinish(803) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    gflagOn(348);

    gamesysObjInfoPosSetStage(boyGObj, GOBJ_ACT(boyGObj)->infoPos, 0, stage_no);

    CheckPoint();

    gflagOff(348);
}

inline void actE3CapsuleDemoEnd(GObj *volatile self)
{
    scpPlayMot(boyGObj, 301);

    while (stage_CheckAnimationFinish(553) == 0) {
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

    soundSeDefPlay(1319, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1320, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1321, 0, st09aSekizoPos, 1);

    if (gflagChk(333) == 0) {
        if ((int)girlGObj == 0) {
            ScpCallCameraOff();
        }
        stage_SetAnimation(341, 0, 0);

        st09aSekizo_mes[0].func = actE3St09aSekizoChk;
        sub->mail = st09aSekizo_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        ScpCallCameraSetTarget(1421.0f, 97.0f, -1885.0f);
        stage_SetAnimation(341, 0, -1);
    }
}

inline void actE3St09aGirlWay(GObj *volatile self)
{
    EffectArg buf = {{-1410.0f, -100.0f, 1950.0f, 0.0f}};
    long long way[2];

    _SCPMoveCharactorByWay(girlGObj, 0, buf.f, 100.0f, 0);

    memset(way, 0, 16);
    RequestStageChangeDirect(girlGObj, 100, way, 180);

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
           ForMotionViewer_GetCurrentMotion(boyGObj) == 75) {
        _ACTWait(1);
    }

    scpSekizouCheckPoint();

    scpAdpcmPlayRequestFunc(18, 0, 1, 1, 1);

    scpKillEnemyAll();
    scpMaskGeneratorAll();

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    brainLockGirl();

    gflagOn(333);

    _ACTWait(60);

    stage_SetAnimation(341, 1, 0);

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

    scpPlayMot(girlGObj, 572);
    scpPlayWaitMotEnd(girlGObj);

    while (stage_CheckAnimationFrame(341, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_e3);

    scpPlayMot(girlGObj, 514);
    scpPlayEnd(girlGObj);

    actCreateSubThread(actE3St09aGirlWay, 21);

    _ACTWait(30);

    scpPlayMot(boyGObj, 247);
    scpPlayWaitMotEnd(boyGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    ScpCallCameraSetTarget(1421.0f, 97.0f, -1885.0f);
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

    scpAdpcmPlayRequestFunc(4, &e3gate1st, 1, 1, 0);
    while (e3gate1st == 0) {
        _ACTWait(1);
    }

    gflagOn(329);
    _ACTWait(1);

    actCreateSubThread(actE3GateDemo, 21);
    actCreateSubThread(actE3GateJimaku, 21);

    stage_SetAnimation(238, 1, 0);
}

void actE3GateDemo(GObj *volatile self)
{
    scpSearchGobj(3127)->active = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion(scpSearchGobj(3127));

    PlayStreamMotion();

    scpFadeIn(6.0f);

    stage_SetAnimation(577, 1, 0);

    while (stage_CheckAnimationFrame(577, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    AdpcmPlay(e3gate1st->stream);

    while (stage_ContinueAnimation(577, 578) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(578, 579) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(579, 580) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(580, 581) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(581, 582) == 0) {
        _ACTWait(1);
    }

    reg_SetScissorSw(0);

    while (stage_ContinueAnimation(582, 583) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(583, 584) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(584, 585) == 0) {
        _ACTWait(1);
    }

    SetStaticBlur(8);
    SetAuraInspireParam(100.0f);

    stage_SetAnimation(411, 1, 0);

    iosPadActRequest(boyPad, 15);

    soundSeDefPlay(1388, 0, 0, 0);

    while (stage_CheckAnimationFrame(585, 45, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (e3gate1st != 0) {
        scpAdpcmFadeCloseFunc(e3gate1st, 80);
    }

    ReinitWindManager();

    lt_switch_layout(50);

    enable_game_pause = 0;

    scpFadeOut(4.0f, 255, 255, 255);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (scpSeEnvMasterVolRate > 0.0f) {
        scpSeEnvMasterVolRate -= 0.012f;
        _ACTWait(1);
    }

    mpegPlayReturnStage = 93;

    stgmgrForceSwitchWithFadeColor(102, 255.0f, 4.0f, 255, 255, 255);
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
    stage_SetAnimation(162, 0, -1);
}

void actE3Warning(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    scpFadeOut(255.0f, 0, 0, 0);

    enable_game_pause = 0;

    _ACTWait(1);

    scpBoyControlReadDisable = 1;
    InitStageLight(stage_no);

    scpFadeIn(6.0f);

    if ((int)boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

    warning_mes[0].func = actE3WarningChk;
    sub->mail = warning_mes;
    ACTSendMailCorrect(self, 397);
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
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actE3Door(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if (gflagChk(327) == 0) {
        stage_SetAnimation(800, 0, 0);

        door_mes[0].func = actE3DoorMain;
        sub->mail = door_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(800, 0, -1);
    }
}

void actE3CageFallReady(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if (gflagChk(328) == 0) {
        cageFallReady_mes[0].func = actE3CageFallReadyChk;
        sub->mail = cageFallReady_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actE3St13cIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if ((int)girlGObj == 0) {
        ScpCallCameraOff();
    }

    if (gflagChk(331) == 0) {
        st13cIntro_mes[0].func = actE3St13cIntroChk;
        sub->mail = st13cIntro_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actE3St13cGene1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(332) == 0) {
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
    while (gflagChk(332) == 0) {
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

    if ((int)girlGObj == 0) {
        ScpCallCameraOff();
    }

    if (gflagChk(330) == 0) {
        st01bEne_mes[0].func = actE3St01bEneChk;
        sub->mail = st01bEne_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actE3St01bGene1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(330) == 0) {
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
    while (gflagChk(330) == 0) {
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
    while (gflagChk(330) == 0) {
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

    MallocStreamMotionBuffer();

    scpSearchGobj(3127)->active = 0;

    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 0);

    scpFadeOut(255.0f, 0, 0, 0);

    stage_SetAnimation(238, 0, 0);
    stage_SetAnimation(241, 0, 0);

    gate_mes[0].func = actE3GateChk;
    sub->mail = gate_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actE3CapsuleChk(GObj *volatile self)
{
    scpSekizouCheckPoint();

    gflagOn(326);

    scpAdpcmPlayRequestFunc(2, &e3capsule, 1, 1, 1);
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
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

inline void actE3DoorUp(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(327);

    _ACTWait(60);

    stage_SetAnimation(800, 1, 0);

    soundSeDefPlay(1197, 0, doorUpPos, 1);

    _ACTWait(30);

    soundSeDefPlay(1198, 0, doorUpPos, 1);

    while (stage_CheckAnimationFinish(800) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

inline void actE3St13cIntroChk(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(331);

    scpBoyControlReadDisable = 1;
    _ACTWait(120);

    stage_SetAnimation(801, 1, 0);

    while (stage_CheckAnimationFinish(801) == 0) {
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
    scpAdpcmPlayRequestFunc(3, &e3cage, 1, 1, 0);
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

    gflagOn(330);

    stage_SetAnimation(161, 1, 0);

    while (stage_CheckAnimationFinish(161) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
}
