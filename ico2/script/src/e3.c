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

#ifdef VERSION_JUN26
#include "e3.h"
#else
void actE3WarningChk(GObj *volatile self)
{
    GObj *x = self;
    int i;

    actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC) || defined(VERSION_AUG6)
    stgmgrNextStagePreLoadForceStageSet(93);
#else
    stgmgrNextStagePreLoadForceStageSet(95);
#endif

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

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
static inline void actE3St09aBrgSwitch(GObj *volatile self);
#endif
#endif

/* .sdata: the title stream's handle, the capsule's, the cage fall's, the
   first gate's, the stone statue's and its volume word, then the statue
   shake's volume. */
static SqEntry *e3title = 0; /* derived name */

SqEntry *e3capsule = 0;

static SqEntry *e3cage = 0; /* derived name */

SqEntry *e3gate1st = 0;

#ifdef VERSION_NTSC
unsigned int sekizo_e3 = 0;

unsigned char sekizo_e3_vol = 0;

static ActMail warning_mes[2] = {{397}, {396}}; /* derived name */

static ActMail title_mes[2] = {{397}, {396}}; /* derived name */

static ActMail inst1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail capsule_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorMain_mes[2] = {{376, actE3DoorSwitch}, {396}}; /* derived name */

static ActMail door_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{397}, {396}}; /* derived name */
#else
#ifdef VERSION_AUG6
int sekizo_e3 = 0;

unsigned char sekizo_e3_vol = 0;

/* actE3Warning's mail, the first object of the TU's .data */
static ActMail warning_mes[2] = {{393}, {392}}; /* derived name */

static ActMail title_mes[2] = {{393}, {392}}; /* derived name */

static ActMail inst1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail capsule_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorMain_mes[2] = {{372, actE3DoorSwitch}, {392}}; /* derived name */

static ActMail door_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_JUN26
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
#else
SqEntry *sekizo_e3 = 0;

int sekizo_e3_vol = 0;

static unsigned char e3sekizo_yure_vol = 0; /* derived name */

#if defined(VERSION_JPN) || defined(VERSION_KOR)
static ActMail warning_mes[2] = {{430}, {429}}; /* derived name */
#endif

static ActMail title_mes[2] = {{430}, {429}}; /* derived name */

static ActMail inst1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail capsule_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorMain_mes[2] = {{406, actE3DoorSwitch}, {429}}; /* derived name */

static ActMail door_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif
#endif

static float doorUpPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f}; /* derived name */

#ifdef VERSION_NTSC
static ActMail st13cIntro_mes[2] = {{397}, {396}}; /* derived name */

static ActMail cageFallReady_mes[2] = {{397}, {396}}; /* derived name */

static ActMail cageFall_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st01bEne_mes[2] = {{397}, {396}}; /* derived name */
#else
#ifdef VERSION_AUG6
static ActMail st13cIntro_mes[2] = {{393}, {392}}; /* derived name */

static ActMail cageFallReady_mes[2] = {{393}, {392}}; /* derived name */

static ActMail cageFall_mes[2] = {{393}, {392}}; /* derived name */

static ActMail st01bEne_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_JUN26
static ActMail st13cIntro_mes[2] = {{377}, {376}}; /* derived name */

static ActMail cageFallReady_mes[2] = {{377}, {376}}; /* derived name */

static ActMail cageFall_mes[2] = {{377}, {376}}; /* derived name */

static ActMail st01bEne_mes[2] = {{377}, {376}}; /* derived name */
#else
static ActMail st13cIntro_mes[2] = {{430}, {429}}; /* derived name */

static ActMail cageFallReady_mes[2] = {{430}, {429}}; /* derived name */

static ActMail cageFall_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st01bEne_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif
#endif

static float st09aSekizoPos[4] = {1548.0f, -412.0f, -608.0f, 0.0f}; /* derived name */

#ifdef VERSION_NTSC
static ActMail st09aSekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gate_mes[2] = {{397}, {396}}; /* derived name */
#else
#ifdef VERSION_AUG6
static ActMail st09aSekizo_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gate_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_JUN26
static ActMail st09aSekizo_mes[2] = {{377}, {376}}; /* derived name */

/* actE3Gate's (this build has no stage 9 bridge records) */
static ActMail gate_mes[2] = {{377}, {376}}; /* derived name */

/* main.c's: wakes the boot thread to hand the disc back to the menu (the
   stage scripts that include main.h keep a static flag of this name) */
void demoEnd(void);
#else
static ActMail st09aSekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gate_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st09aBrgMain_mes[2] = {{407, actE3St09aBrgSwitch}, {429}}; /* derived name */

static ActMail st09aBrg_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st09aBrgSwitch_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif
#endif

void actE3Title(GObj *volatile self)
{
    GObj *x = self;
#ifdef VERSION_JUN26
    Act *sub;

    if (InterStageSwitchLock != 0) {
        demoEnd();
        _ACTWait(0);
    }

    sub = (Act *)actInitialize(self);
#else
    Act *sub = (Act *)actInitialize(self);
#endif

    _ACTWait(1);

    enable_game_pause = 0;
    scpBoyControlReadDisable = 1;

#ifdef VERSION_JUN26
    e3title = 0;
    scpAdpcmPlayRequestFunc(8, &e3title, 0, 1, 0);
#else
#ifdef VERSION_NTSC
    gflagOff(324);
#else
#ifdef VERSION_AUG6
    gflagOff(323);
#else
    gflagOff(356);
#endif
#endif

    e3title = 0;
    scpAdpcmPlayRequestFunc(5, &e3title, 0, 1, 0);
#endif

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

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    stage_SetAnimation(31, 0, 0);
    stage_SetAnimation(25, 0, -1);
    stage_SetAnimation(34, 0, 0);
    stage_SetAnimation(32, 0, 0);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(37, 0, 0);
#else
#ifdef VERSION_JUN26
    ACTGame_StageChangeGObjID(47, 1, 39);
    ACTGame_StageChangeGObjID(124, 2, 40);

    stage_SetAnimation(27, 0, 0);
    stage_SetAnimation(21, 0, -1);
    stage_SetAnimation(30, 0, 0);
    stage_SetAnimation(28, 0, 0);
    stage_SetAnimation(31, 0, 0);
    stage_SetAnimation(33, 0, 0);
#else
    stage_SetAnimation(32, 0, 0);
    stage_SetAnimation(26, 0, -1);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(33, 0, 0);
    stage_SetAnimation(36, 0, 0);
    stage_SetAnimation(38, 0, 0);
    stage_SetAnimation(43, 0, 0);
#endif
#endif

    title_mes[0].func = actE3TitleChk;
    sub->mail = title_mes;
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

#ifdef VERSION_NTSC
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
#else
void actE3TitleChk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    actCreateSubThread(actE3TitleFrameChk, 21);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (gflagChk(356) != 0 || (pad[0].flags & 0x820) == 0) {
#else
#ifdef VERSION_AUG6
    while (gflagChk(323) != 0 || (pad[0].flags & 0x840) == 0) {
#else
#ifdef VERSION_JUN26
    while ((pad[0].flags & 0x840) == 0) {
#else
    while (gflagChk(356) != 0 || (pad[0].flags & 0x840) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    gflagOn(309);
#else
#ifdef VERSION_AUG6
    gflagOn(324);
#else
    gflagOn(357);
#endif
    debug_StdPrintfDummy("game_start\n");
#endif

    AdpcmPlay(e3title->stream);

    scpFadeOut(4.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, boyGObj, 0, 255.0f, 16.0f);
}

#if defined(VERSION_JPN) || defined(VERSION_KOR)
void actE3TitleFrameChk(GObj *volatile self)
{
    int i;

    stage_SetAnimation(931, 1, 0);

    while (stage_ContinueAnimation(931, 932) == 0) {
        _ACTWait(1);
    }

    stage_SetLoopFlag(932, 1);

    i = 0;
    while (i++ < (60 - systemStatus[0] * 10) / systemStatus[1] * 45) {
        _ACTWait(1);
    }

    stage_SetAnimation(933, 1, 0);

    while (stage_CheckAnimationFinish(933) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(357) == 0) {
        debug_StdPrintfDummy("mpeg_start\n");

        gflagOn(356);

        if (e3title != 0) {
            scpAdpcmCloseFunc(&e3title);
        }

        mpegPlayReturnStage = 93;
        stage_after_skipping_demo = 93;

        stgmgrForceSwitchWithFade(101, 4.0f, 4.0f);
    }
}
#else
void actE3TitleFrameChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    int i;

    stage_SetAnimation(796, 1, 0);

    while (stage_ContinueAnimation(796, 797) == 0) {
#else
#ifdef VERSION_JUN26
    int i;

    stage_SetAnimation(745, 1, 0);

    while (stage_ContinueAnimation(745, 746) == 0) {
#else
    int intro = 943;
    int loop = 938;
    int outro = 948;
    int i;

    stage_SetAnimation(935, 1, 0);

    switch (NonLinearCameraMove) {
    case 3:
        intro = 944;
        break;
    case 4:
        intro = 945;
        break;
    case 6:
        intro = 947;
        break;
    case 5:
        intro = 946;
        break;
    }
    stage_SetAnimation(intro, 1, 0);

    while (stage_ContinueAnimation(935, 936) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetLoopFlag(797, 1);
#else
#ifdef VERSION_JUN26
    stage_SetLoopFlag(746, 1);
#else
    stage_SetLoopFlag(936, 1);

    switch (NonLinearCameraMove) {
    case 3:
        loop = 939;
        break;
    case 4:
        loop = 940;
        break;
    case 6:
        loop = 942;
        break;
    case 5:
        loop = 941;
        break;
    }
    stage_SetLoopFlag(loop, 1);
    stage_SetAnimation(loop, 1, 0);
#endif
#endif

    i = 0;
    while (i++ < (60 - systemStatus[0] * 10) / systemStatus[1] * 45) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(798, 1, 0);

    while (stage_CheckAnimationFinish(798) == 0) {
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(747, 1, 0);

    while (stage_CheckAnimationFinish(747) == 0) {
#else
    stage_SetAnimation(937, 1, 0);

    switch (NonLinearCameraMove) {
    case 3:
        outro = 949;
        break;
    case 4:
        outro = 950;
        break;
    case 6:
        outro = 952;
        break;
    case 5:
        outro = 951;
        break;
    }
    stage_SetAnimation(outro, 1, 0);

    while (stage_CheckAnimationFinish(937) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(324) == 0) {
        debug_StdPrintfDummy("mpeg_start\n");

        gflagOn(323);

        if (e3title != 0) {
            soundDataClose(e3title);
        }

        mpegPlayReturnStage = 93;
        stage_after_skipping_demo = 93;

        stgmgrForceSwitchWithFade(101, 4.0f, 4.0f);
#else
#ifdef VERSION_JUN26
    if (gflagChk(309) == 0) {
        debug_StdPrintfDummy("mpeg_start\n");

        if (e3title != 0) {
            soundDataClose(e3title);
        }

        mpegPlayReturnStage = 92;
        stage_after_skipping_demo = 92;

        stgmgrForceSwitchWithFade(100, 4.0f, 4.0f);
#else
    if (gflagChk(357) == 0) {
        debug_StdPrintfDummy("mpeg_start\n");

        gflagOn(356);

        if (e3title != 0) {
            scpAdpcmCloseFunc(&e3title);
        }

        mpegPlayReturnStage = 95;
        stage_after_skipping_demo = 95;

        stgmgrForceSwitchWithFade(103, 4.0f, 4.0f);
#endif
#endif
    }
}
#endif
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
void actE3Inst1Chk(GObj *volatile self)
{
    GObj *x = self;
    int i;

    actInitialize(self);
    _ACTWait(1);

    i = 0;
    while (i++ < (60 - systemStatus[0] * 10) / systemStatus[1] * 10 &&
           (pad[0].flags & 0x820) == 0) {
        _ACTWait(1);
    }

    soundSeDefPlay(1390, 0, 0, 1);

    scpFadeOut(3.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, boyGObj, 0, 255.0f, 16.0f);
}
#else
void actE3Inst1Chk(GObj *volatile self)
{
    GObj *x = self;
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
    int anim;
#endif
    int i;

    actInitialize(self);
    _ACTWait(1);

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
    anim = 960;
    switch (NonLinearCameraMove) {
    case 3:
        anim = 961;
        break;
    case 4:
        anim = 962;
        break;
    case 6:
        anim = 964;
        break;
    case 5:
        anim = 963;
        break;
    }

    stage_SetLoopFlag(anim, 1);
    stage_SetAnimation(anim, 1, 0);
#endif

    i = 0;
    while (i++ < (60 - systemStatus[0] * 10) / systemStatus[1] * 10 &&
           (pad[0].flags & 0x840) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    soundSeDefPlay(1353, 0, 0, 1);
#else
#ifdef VERSION_JUN26
    soundSeDefPlay(1302, 0, 0, 1);
#else
    soundSeDefPlay(1390, 0, 0, 1);
#endif
#endif

    scpFadeOut(3.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, boyGObj, 0, 255.0f, 16.0f);
}
#endif

#ifdef VERSION_NTSC
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
#else
void actE3Capsule(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_JUN26
    if (gflagChk(310) == 0) {
#else
    if ((int)girlGObj == 0) {
        ScpCallCameraOff();
    }

#ifdef VERSION_AUG6
    if (gflagChk(325) == 0) {
#else
    if (gflagChk(358) == 0) {
#endif
#endif
        if ((int)boyGObj != 0) {
            scpPlayMot(boyGObj, 0);
        }

        scpFadeOut(255.0f, 0, 0, 0);

#ifdef VERSION_AUG6
        lt_switch_layout(51);

        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(25, 0, -1);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
#else
#ifdef VERSION_JUN26
        lt_switch_layout(51);

        stage_SetAnimation(27, 0, 0);
        stage_SetAnimation(21, 0, -1);
        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(28, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        lt_switch_layout(52);
#else
        lt_switch_layout(55);
#endif

        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(26, 0, -1);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
#endif
#endif

        capsule_mes[0].func = actE3CapsuleChk;
        sub->mail = capsule_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, -1);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(27, 0, -1);
        stage_SetAnimation(21, 0, -1);
        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(28, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, -1);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
#endif
#endif
    }
}
#endif

/* .sbss: the capsule demo's sub-thread and the flag that thread raises when
   the demo has finished. */
static GProc *capsuleDemoThread; /* derived name */

#ifdef VERSION_JUN26
static int demoEndFlag; /* derived name */
#else
static int demoEnd;
#endif

void actE3CapsuleDemoCancel(GObj *volatile self)
{
#ifdef VERSION_JUN26
    while (demoEndFlag == 0 || (pad[0].flags & 0x800) == 0) {
#else
    while (demoEnd == 0 || (pad[0].flags & 0x800) == 0) {
#endif
        _ACTWait(1);
    }

    iosThreadSetPri(&capsuleDemoThread->thread, 34);

    scpFadeOut(8.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    soundDataClose(e3capsule);

    stage_SetAnimation(31, 0, -1);
    stage_SetAnimation(25, 0, -1);
#ifdef VERSION_AUG6
    stage_SetAnimation(522, -1, -2);
    stage_SetAnimation(527, -1, -2);
    stage_SetAnimation(529, -1, -2);
#else
    stage_SetAnimation(523, -1, -2);
    stage_SetAnimation(528, -1, -2);
#endif
    stage_SetAnimation(530, -1, -2);
    stage_SetAnimation(531, -1, -2);
    stage_SetAnimation(532, -1, -2);
    stage_SetAnimation(533, -1, -2);
    stage_SetAnimation(534, -1, -2);
#ifdef VERSION_AUG6
    stage_SetAnimation(552, 1, 0);
#else
    stage_SetAnimation(535, -1, -2);
    stage_SetAnimation(553, 1, 0);
#endif
#else
#ifdef VERSION_JUN26
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
#else
    scpAdpcmCloseFunc(&e3capsule);

    stage_SetAnimation(32, 0, -1);
    stage_SetAnimation(26, 0, -1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(590, -1, -2);
    stage_SetAnimation(595, -1, -2);
    stage_SetAnimation(597, -1, -2);
    stage_SetAnimation(598, -1, -2);
#else
    stage_SetAnimation(594, -1, -2);
#endif
    stage_SetAnimation(599, -1, -2);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(600, -1, -2);
#endif
    stage_SetAnimation(601, -1, -2);
    stage_SetAnimation(602, -1, -2);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(620, 1, 0);
#else
    stage_SetAnimation(603, -1, -2);
    stage_SetAnimation(604, -1, -2);
    stage_SetAnimation(605, -1, -2);
    stage_SetAnimation(606, -1, -2);
    stage_SetAnimation(624, 1, 0);
#endif
#endif
#endif

    scpFadeIn(6.0f);

    actCreateSubThread(actE3CapsuleDemoEnd, 21);
}

#ifdef VERSION_NTSC
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
#else
void actE3CapsuleDemo(GObj *volatile self)
{
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);

#ifdef VERSION_JUN26
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
#else
    demoEnd = 1;
    actCreateSubThread(actE3CapsuleDemoCancel, 21);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    stage_SetAnimation(522, 1, 0);
    _ACTWait(95);
    stage_SetAnimation(31, 1, 0);

    while (stage_ContinueAnimation(522, 527) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 282);

    while (stage_ContinueAnimation(527, 529) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 282);

    while (stage_ContinueAnimation(529, 530) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 286);

    while (stage_ContinueAnimation(530, 531) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 287);

    while (stage_ContinueAnimation(531, 532) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(590, 1, 0);
#else
    stage_SetAnimation(594, 1, 0);
#endif
    _ACTWait(95);
    stage_SetAnimation(32, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(590, 595) == 0) {
#else
    while (stage_ContinueAnimation(594, 599) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 288);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    while (stage_ContinueAnimation(532, 533) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 289);

    while (stage_ContinueAnimation(533, 534) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 290);

    while (stage_ContinueAnimation(534, 552) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(595, 597) == 0) {
#else
    while (stage_ContinueAnimation(599, 601) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 288);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(597, 598) == 0) {
#else
    while (stage_ContinueAnimation(601, 602) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 292);

    _ACTWait(1);

    stage_SetAnimation(32, 1, 208);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(598, 599) == 0) {
#else
    while (stage_ContinueAnimation(602, 603) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 293);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(599, 600) == 0) {
#else
    while (stage_ContinueAnimation(603, 604) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 294);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(600, 601) == 0) {
#else
    while (stage_ContinueAnimation(604, 605) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 295);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(601, 602) == 0) {
#else
    while (stage_ContinueAnimation(605, 606) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 296);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(602, 620) == 0) {
#else
    while (stage_ContinueAnimation(606, 624) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    demoEndFlag = 0;
#else
    demoEnd = 0;
#endif
    actCreateSubThread(actE3CapsuleDemoEnd, 21);
}

void actE3St13cInit(void)
{
    SetWayGroupActive(7, 0);

#ifdef VERSION_AUG6
    if (gflagChk(327) != 0) {
#else
#ifdef VERSION_JUN26
    if (gflagChk(312) != 0) {
#else
    if (gflagChk(360) != 0) {
#endif
#endif
        SetWayGroupActive(9, 0);
    }
}

void actE3CageFall(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(327) == 0) {
        stage_SetAnimation(63, 0, 0);
        stage_SetAnimation(59, 0, -1);
#else
#ifdef VERSION_JUN26
    if (gflagChk(312) == 0) {
        stage_SetAnimation(57, 0, 0);
        stage_SetAnimation(53, 0, -1);
#else
    if (gflagChk(360) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(72, 0, 0);
        stage_SetAnimation(68, 0, -1);
#else
        stage_SetAnimation(76, 0, 0);
        stage_SetAnimation(72, 0, -1);
#endif
#endif
#endif

        if ((int)girlGObj == 0) {
            _ACTWait(0);
        }

        scpPlayPosSet(girlGObj, -30.0f, -436.0f, -1.0f);

        cageFall_mes[0].func = actE3CageFallChk;
        sub->mail = cageFall_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(63, 0, 0);
        stage_SetAnimation(61, 0, -1);
        stage_SetAnimation(62, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(57, 0, 0);
        stage_SetAnimation(55, 0, -1);
        stage_SetAnimation(56, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(72, 0, 0);
        stage_SetAnimation(70, 0, -1);
        stage_SetAnimation(71, 0, -1);
#else
        stage_SetAnimation(76, 0, 0);
        stage_SetAnimation(74, 0, -1);
        stage_SetAnimation(75, 0, -1);
#endif
#endif
#endif
    }
}

void actE3CageFallChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 160.0f) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    scpBoyControlReadDisable = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    ((Act *)scpSearchGobj(3206)->act)->flags20.ll |= 0x20000;
    ((Act *)scpSearchGobj(3207)->act)->flags20.ll |= 0x20000;
#else
    ((Act *)scpSearchGobj(3229)->act)->flags20.ll |= 0x20000;
    ((Act *)scpSearchGobj(3230)->act)->flags20.ll |= 0x20000;
#endif
#endif

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(327);
#else
#ifdef VERSION_JUN26
    gflagOn(312);
#else
    gflagOn(360);
#endif
#endif

    while (e3cage == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(e3cage->stream);

    actCreateSubThread(actE3CageFallDemo, 21);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(70, 1, 0);
    stage_SetAnimation(71, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(61, 1, 0);
    stage_SetAnimation(62, 1, 0);
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(55, 1, 0);
    stage_SetAnimation(56, 1, 0);
#else
    stage_SetAnimation(74, 1, 0);
    stage_SetAnimation(75, 1, 0);
#endif
#endif
#endif

    actCreateSubThread(actE3CageFallEffect, 21);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(70) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(61) == 0) {
#else
#ifdef VERSION_JUN26
    while (stage_CheckAnimationFinish(55) == 0) {
#else
    while (stage_CheckAnimationFinish(74) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(9, 0);
}

void actE3CageFallDemo(GObj *volatile self)
{
    float dir[4];

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif

    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

#ifdef VERSION_AUG6
    stage_SetAnimation(558, 1, 0);

    scpPlayMot(boyGObj, 309);

    while (stage_ContinueAnimation(558, 559) == 0) {
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(509, 1, 0);

    scpPlayMot(boyGObj, 318);

    while (stage_ContinueAnimation(509, 510) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(626, 1, 0);
#else
    stage_SetAnimation(630, 1, 0);
#endif

    scpPlayMot(boyGObj, 315);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(626, 627) == 0) {
#else
    while (stage_ContinueAnimation(630, 631) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(559, 560) == 0) {
#else
#ifdef VERSION_JUN26
    while (stage_ContinueAnimation(510, 511) == 0) {
#else
    SetHandCameraLimitInDemo(0, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(627, 628) == 0) {
#else
    while (stage_ContinueAnimation(631, 632) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 683);

    while (stage_ContinueAnimation(560, 561) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 684);

    while (stage_ContinueAnimation(561, 562) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 310);

    while (stage_ContinueAnimation(562, 563) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 319);

    while (stage_ContinueAnimation(563, 564) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 685);

    while (stage_ContinueAnimation(564, 565) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 686);
#else
#ifdef VERSION_JUN26
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
#else
    ResetHandCameraLimitInDemo();

    scpPlayMot(girlGObj, 726);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(628, 629) == 0) {
#else
    while (stage_ContinueAnimation(632, 633) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 727);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(629, 630) == 0) {
#else
    while (stage_ContinueAnimation(633, 634) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 316);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(630, 631) == 0) {
#else
    while (stage_ContinueAnimation(634, 635) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 325);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(631, 632) == 0) {
#else
    while (stage_ContinueAnimation(635, 636) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 728);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(632, 633) == 0) {
#else
    while (stage_ContinueAnimation(636, 637) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 729);
#endif
#endif

    _ACTWait(240);

#ifdef VERSION_AUG6
    gflagOn(331);
#else
#ifdef VERSION_JUN26
    gflagOn(316);
#else
    gflagOn(364);
#endif
#endif

    fightSoundProcessRequestStart();

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(565, 801) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 317);

    while (stage_ContinueAnimation(801, 802) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 320);

    while (stage_CheckAnimationFrame(802, 150, 0) == 0) {
#else
#ifdef VERSION_JUN26
    while (stage_ContinueAnimation(516, 750) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 326);

    while (stage_ContinueAnimation(750, 751) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 329);

    while (stage_CheckAnimationFrame(751, 150, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(633, 936) == 0) {
#else
    while (stage_ContinueAnimation(637, 955) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 323);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(936, 937) == 0) {
#else
    while (stage_ContinueAnimation(955, 956) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(girlGObj, 326);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(937, 150, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(956, 150, 0) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 318);

    while (stage_CheckAnimationFinish(802) == 0) {
#else
#ifdef VERSION_JUN26
    scpPlayMot(boyGObj, 327);

    while (stage_CheckAnimationFinish(751) == 0) {
#else
    scpPlayMot(boyGObj, 324);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(937) == 0) {
#else
    while (stage_CheckAnimationFinish(956) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

#ifdef VERSION_AUG6
    lt_switch_layout(50);

    gflagOn(347);
#else
#ifdef VERSION_JUN26
    lt_switch_layout(50);

    gflagOn(332);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    scpPlayMot(girlGObj, 532);
    {
        GObj *obj = girlGObj;

        GOBJ_SUB(obj)->ctrl.blendFrames =
            (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f * 30.0f);

        scpPlayEnd(obj);
    }

    gflagOn(381);
#endif
#endif

    gamesysObjInfoPosSetStage(boyGObj, GOBJ_ACT(boyGObj)->infoPos, 0, stage_no);

    CheckPoint();

#ifdef VERSION_AUG6
    gflagOff(347);
#else
#ifdef VERSION_JUN26
    gflagOff(332);
#else
    gflagOff(381);
#endif
#endif
}

inline void actE3CapsuleDemoEnd(GObj *volatile self)
{
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 301);

    while (stage_CheckAnimationFinish(552) == 0) {
#else
#ifdef VERSION_JUN26
    scpPlayMot(boyGObj, 310);

    while (stage_CheckAnimationFinish(503) == 0) {
#else
    scpPlayMot(boyGObj, 307);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(620) == 0) {
#else
    while (stage_CheckAnimationFinish(624) == 0) {
#endif
#endif
#endif
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

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif

    enable_game_pause = 1;
}
#endif

void actE3CageFallEffect(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 0:
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            gflagOn(21);
#else
            gflagOn(22);
#endif
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

#ifdef VERSION_NTSC
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
#else
void actE3St09aSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    soundSeDefPlay(1319, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1320, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1321, 0, st09aSekizoPos, 1);

    if (gflagChk(332) == 0) {
        if ((int)girlGObj == 0) {
            ScpCallCameraOff();
        }
        stage_SetAnimation(340, 0, 0);
#else
#ifdef VERSION_JUN26
    soundSeDefPlay(1290, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1291, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1292, 0, st09aSekizoPos, 1);

    if (gflagChk(317) == 0) {
        stage_SetAnimation(307, 0, 0);
#else
    soundSeDefPlay(1346, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1347, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1348, 0, st09aSekizoPos, 1);

    if (gflagChk(366) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(372, 0, 0);
#else
        stage_SetAnimation(376, 0, 0);
#endif
#endif
#endif

        st09aSekizo_mes[0].func = actE3St09aSekizoChk;
        sub->mail = st09aSekizo_mes;
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(307, 0, -1);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    } else {
        ScpCallCameraSetTarget(1421.0f, 97.0f, -1885.0f);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(372, 0, -1);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(340, 0, -1);
#else
        stage_SetAnimation(376, 0, -1);
#endif
#endif
#endif
    }
}
#endif

inline void actE3St09aGirlWay(GObj *volatile self)
{
    EffectArg buf = {{-1410.0f, -100.0f, 1950.0f, 0.0f}};
    long long way[2];

    _SCPMoveCharactorByWay(girlGObj, 0, buf.f, 100.0f, 0);

    memset(way, 0, 16);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    RequestStageChangeDirect(girlGObj, 100, way, 180);

    lt_switch_layout(50);
#else
#ifdef VERSION_JUN26
    RequestStageChangeDirect(girlGObj, 99, way, 180);

    lt_switch_layout(50);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    RequestStageChangeDirect(girlGObj, 100, way, 180);
#else
    RequestStageChangeDirect(girlGObj, 102, way, 180);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
#endif
#endif

    scpBoyControlReadDisable = 0;
    brainUnlockGirl();
}

#ifdef VERSION_NTSC
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
#else
void actE3St09aSekizoChk(GObj *volatile self)
{
    float dir[4];

    if ((int)girlGObj == 0) {
        _ACTWait(0);
    }

#ifdef VERSION_JUN26
    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 ||
           scpTriggerBall(self, girlGObj, 200.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 83) {
#else
    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 ||
           scpTriggerBall(self, girlGObj, 200.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 75) {
#endif
        _ACTWait(1);
    }

    scpSekizouCheckPoint();

#ifdef VERSION_JUN26
    scpAdpcmPlayRequestFunc(21, 0, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(18, 0, 1, 1, 1);
#endif

    scpKillEnemyAll();
    scpMaskGeneratorAll();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif

    scpBoyControlReadDisable = 1;
    brainLockGirl();

#ifdef VERSION_AUG6
    gflagOn(332);
#else
#ifdef VERSION_JUN26
    gflagOn(317);
#else
    gflagOn(366);
#endif
#endif

    _ACTWait(60);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    stage_SetAnimation(307, 1, 0);
#else
    stage_SetAnimation(340, 1, 0);
#endif

    sekizo_e3 = iosPadActRequest(boyPad, 9);
    sekizo_e3_vol = 128;
    iosPadActVolumeSet(sekizo_e3, 128);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(372, 1, 0);
#else
    stage_SetAnimation(376, 1, 0);
#endif

    sekizo_e3_vol = iosPadActRequest(boyPad, 9);
    e3sekizo_yure_vol = 128;
    iosPadActVolumeSet(sekizo_e3_vol, 128);
#endif

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

#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 573);
    scpPlayWaitMotEnd(girlGObj);

    while (stage_CheckAnimationFrame(340, 151, 0) == 0) {
#else
#ifdef VERSION_JUN26
    scpPlayMot(girlGObj, 584);
    scpPlayWaitMotEnd(girlGObj);

    while (stage_CheckAnimationFrame(307, 151, 0) == 0) {
#else
    scpPlayMot(girlGObj, 645);
    scpPlayWaitMotEnd(girlGObj);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(372, 151, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(376, 151, 0) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    iosPadActStop(sekizo_e3);

    scpPlayMot(girlGObj, 514);
#else
#ifdef VERSION_JUN26
    iosPadActStop(sekizo_e3);

    scpPlayMot(girlGObj, 521);
#else
    iosPadActStop(sekizo_e3_vol);

    scpPlayMot(girlGObj, 532);
#endif
#endif
    scpPlayEnd(girlGObj);

    actCreateSubThread(actE3St09aGirlWay, 21);

    _ACTWait(30);

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 247);
#else
#ifdef VERSION_JUN26
    scpPlayMot(boyGObj, 254);
#else
    scpPlayMot(boyGObj, 252);
#endif
#endif
    scpPlayWaitMotEnd(boyGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

#ifndef VERSION_JUN26
    ScpCallCameraSetTarget(1421.0f, 97.0f, -1885.0f);
#endif
}
#endif

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

#ifdef VERSION_NTSC
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
        scpAdpcmFadeClose(e3gate1st, 80);
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
#else
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

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif

    SetWindManager(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 5.0f, 0.0f);

    scpPlayStart(girlGObj);

    reg_SetScissorSw(1);
    SetStaticBlur(0);

#ifdef VERSION_JUN26
    scpAdpcmPlayRequestFunc(7, &e3gate1st, 1, 1, 0);
#else
    scpAdpcmPlayRequestFunc(4, &e3gate1st, 1, 1, 0);
#endif
    while (e3gate1st == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(328);
#else
#ifdef VERSION_JUN26
    gflagOn(313);
#else
    gflagOn(361);
#endif
#endif
    _ACTWait(1);

    actCreateSubThread(actE3GateDemo, 21);
    actCreateSubThread(actE3GateJimaku, 21);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(265, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(237, 1, 0);
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(212, 1, 0);
#else
    stage_SetAnimation(269, 1, 0);
#endif
#endif
#endif
}

void actE3GateDemo(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSearchGobj(3359)->active = 1;
#else
#ifdef VERSION_AUG6
    scpSearchGobj(3097)->active = 1;
#else
#ifdef VERSION_JUN26
    scpSearchGobj(2942)->active = 1;
#else
    scpSearchGobj(3382)->active = 1;
#endif
#endif
#endif

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    EntryStreamMotion(scpSearchGobj(3359));
#else
#ifdef VERSION_AUG6
    EntryStreamMotion(scpSearchGobj(3097));
#else
#ifdef VERSION_JUN26
    EntryStreamMotion(scpSearchGobj(2942));
#else
    EntryStreamMotion(scpSearchGobj(3382));
#endif
#endif
#endif

    PlayStreamMotion();

    scpFadeIn(6.0f);

#ifdef VERSION_AUG6
    stage_SetAnimation(576, 1, 0);

    while (stage_CheckAnimationFrame(576, 10, 0) == 0) {
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(527, 1, 0);

    while (stage_CheckAnimationFrame(527, 10, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(644, 1, 0);
#else
    stage_SetAnimation(648, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(644, 10, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(648, 10, 0) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    AdpcmPlay(e3gate1st->stream);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(644, 645) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(645, 646) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(646, 647) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(647, 648) == 0) {
        _ACTWait(1);
    }
#endif
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(576, 577) == 0) {
        _ACTWait(1);
    }
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
#else
#ifdef VERSION_JUN26
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
#else
    while (stage_ContinueAnimation(648, 649) == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)

    reg_SetScissorSw(0);

#endif
    while (stage_ContinueAnimation(649, 650) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(650, 651) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(651, 652) == 0) {
        _ACTWait(1);
    }
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
    while (stage_ContinueAnimation(652, 653) == 0) {
        _ACTWait(1);
    }

    reg_SetScissorSw(0);

    while (stage_ContinueAnimation(653, 654) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(654, 655) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(655, 656) == 0) {
        _ACTWait(1);
    }
#endif
#endif
#endif

    SetStaticBlur(8);
    SetAuraInspireParam(100.0f);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(471, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(410, 1, 0);
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(375, 1, 0);
#else
    stage_SetAnimation(475, 1, 0);
#endif
#endif
#endif

    iosPadActRequest(boyPad, 15);

#ifdef VERSION_AUG6
    soundSeDefPlay(1388, 0, 0, 0);

    while (stage_CheckAnimationFrame(584, 45, 0) == 0) {
#else
#ifdef VERSION_JUN26
    soundSeDefPlay(1336, 0, 0, 0);

    while (stage_CheckAnimationFrame(535, 45, 0) == 0) {
#else
    soundSeDefPlay(1425, 0, 0, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(652, 45, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(656, 45, 0) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    if (e3gate1st != 0) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        scpAdpcmFadeClose(e3gate1st, 80);
#else
        scpAdpcmFadeCloseFunc(&e3gate1st, 80);
#endif
    }

    ReinitWindManager();

#ifdef VERSION_JUN26
    lt_switch_layout(50);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif

    enable_game_pause = 0;
#endif

    scpFadeOut(4.0f, 255, 255, 255);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (scpSeEnvMasterVolRate > 0.0f) {
        scpSeEnvMasterVolRate -= 0.012f;
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    InterStageSwitchLock++;
    mpegPlayReturnStage = 92;

    stgmgrForceSwitchWithFadeColor(101, 255.0f, 4.0f, 255, 255, 255);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_AUG6)
    mpegPlayReturnStage = 93;
#else
    mpegPlayReturnStage = 95;
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_AUG6)
    stgmgrForceSwitchWithFadeColor(102, 255.0f, 4.0f, 255, 255, 255);
#else
    stgmgrForceSwitchWithFadeColor(104, 255.0f, 4.0f, 0, 0, 0);
#endif
#endif
}
#endif

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
#ifdef VERSION_NTSC
    stage_SetAnimation(162, 0, -1);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(161, 0, -1);
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(147, 0, -1);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(179, 0, -1);
#else
    stage_SetAnimation(183, 0, -1);
#endif
}

static void actE3St09aBrgDown(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    gflagOn(86);

    scpAdpcmPlayRequestFunc(90, &sekizo_e3, 1, 1, 1);
    while (sekizo_e3 == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(374, 1, 0);
#else
    stage_SetAnimation(378, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(374, 115, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(378, 115, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(374, 165, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(378, 165, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(374) == 0) {
#else
    while (stage_CheckAnimationFinish(378) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
#endif
#endif
#endif
}

void actE3Warning(GObj *volatile self)
{
    GObj *x = self;
#ifdef VERSION_JUN26
    Act *sub = (Act *)actInitialize(self);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC) || defined(VERSION_AUG6)
    Act *sub = (Act *)actInitialize(self);
#else
    actInitialize(self);
#endif

    scpFadeOut(255.0f, 0, 0, 0);

    enable_game_pause = 0;
#endif

    _ACTWait(1);

#ifdef VERSION_JUN26
    enable_game_pause = 0;
    scpBoyControlReadDisable = 1;

    if ((int)boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

    warning_mes[0].func = actE3WarningChk;
    sub->mail = warning_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
#else
    scpBoyControlReadDisable = 1;
    InitStageLight(stage_no);
#ifdef VERSION_JPN
    GlobalStageSetting.viewScale = 150;
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpFadeIn(6.0f);

    if ((int)boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

    warning_mes[0].func = actE3WarningChk;
    sub->mail = warning_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    scpFadeIn(6.0f);

    if ((int)boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

    warning_mes[0].func = actE3WarningChk;
    sub->mail = warning_mes;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
#else
    RequestStageChange(1, boyGObj, 0, 255.0f, 0.0f);
#endif
#endif
#endif
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

#ifdef VERSION_NTSC
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
#else
void actE3Door(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(326) == 0) {
        stage_SetAnimation(799, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(311) == 0) {
        stage_SetAnimation(748, 0, 0);
#else
    if (gflagChk(359) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(934, 0, 0);
#else
        stage_SetAnimation(953, 0, 0);
#endif
#endif
#endif

        door_mes[0].func = actE3DoorMain;
        sub->mail = door_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(799, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(748, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(934, 0, -1);
#else
        stage_SetAnimation(953, 0, -1);
#endif
#endif
#endif
    }
}

void actE3CageFallReady(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(327) == 0) {
        cageFallReady_mes[0].func = actE3CageFallReadyChk;
        sub->mail = cageFallReady_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(312) == 0) {
        cageFallReady_mes[0].func = actE3CageFallReadyChk;
        sub->mail = cageFallReady_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(360) == 0) {
        cageFallReady_mes[0].func = actE3CageFallReadyChk;
        sub->mail = cageFallReady_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actE3St13cIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if ((int)girlGObj == 0) {
        ScpCallCameraOff();
    }

    if (gflagChk(330) == 0) {
        st13cIntro_mes[0].func = actE3St13cIntroChk;
        sub->mail = st13cIntro_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(315) == 0) {
        st13cIntro_mes[0].func = actE3St13cIntroChk;
        sub->mail = st13cIntro_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(363) == 0) {
        st13cIntro_mes[0].func = actE3St13cIntroChk;
        sub->mail = st13cIntro_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actE3St13cGene1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
#ifdef VERSION_AUG6
    while (gflagChk(331) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(316) == 0) {
#else
    while (gflagChk(364) == 0) {
#endif
#endif
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
#ifdef VERSION_AUG6
    while (gflagChk(331) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(316) == 0) {
#else
    while (gflagChk(364) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    Generator_Call(self);
    _ACTWait(120);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}
#endif

void actE3Floor(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
void actE3St01bEne(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_JUN26
    if (gflagChk(314) == 0) {
        st01bEne_mes[0].func = actE3St01bEneChk;
        sub->mail = st01bEne_mes;
        ACTSendMailCorrect(self, 377);
#else
    if ((int)girlGObj == 0) {
        ScpCallCameraOff();
    }

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    if (gflagChk(329) == 0) {
        st01bEne_mes[0].func = actE3St01bEneChk;
        sub->mail = st01bEne_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(330) == 0) {
        st01bEne_mes[0].func = actE3St01bEneChk;
        sub->mail = st01bEne_mes;
        ACTSendMailCorrect(self, 397);
#endif
#endif
        _ACTWait(0);
    }
}

void actE3St01bGene1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    while (gflagChk(314) == 0) {
#else
    while (gflagChk(329) == 0) {
#endif
#else
    while (gflagChk(330) == 0) {
#endif
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
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    while (gflagChk(314) == 0) {
#else
    while (gflagChk(329) == 0) {
#endif
#else
    while (gflagChk(330) == 0) {
#endif
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
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    while (gflagChk(314) == 0) {
#else
    while (gflagChk(329) == 0) {
#endif
#else
    while (gflagChk(330) == 0) {
#endif
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
#else
void actE3St01bEne(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if (gflagChk(362) == 0) {
        st01bEne_mes[0].func = actE3St01bEneChk;
        sub->mail = st01bEne_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actE3St01bGene1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(362) == 0) {
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
    while (gflagChk(362) == 0) {
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
    while (gflagChk(362) == 0) {
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

void actE3St09aBrg(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

    if (gflagChk(86) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(374, 0, 0);
#else
        stage_SetAnimation(378, 0, 0);
#endif

        st09aBrg_mes[0].func = actE3St09aBrgMain;
        sub->mail = st09aBrg_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(374, 0, -1);
#else
        stage_SetAnimation(378, 0, -1);
#endif
    }
}
#endif

void actE3Gate(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = (Act *)actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    scpSearchGobj(3097)->active = 0;
#else
#ifdef VERSION_JUN26
    scpSearchGobj(2942)->active = 0;
#else
    MallocStreamMotionBuffer();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSearchGobj(3359)->active = 0;
#else
#ifdef VERSION_NTSC
    scpSearchGobj(3127)->active = 0;
#else
    scpSearchGobj(3382)->active = 0;
#endif
#endif
#endif
#endif

    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 0);

    scpFadeOut(255.0f, 0, 0, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(265, 0, 0);
    stage_SetAnimation(268, 0, 0);
#else
#ifdef VERSION_NTSC
    stage_SetAnimation(238, 0, 0);
    stage_SetAnimation(241, 0, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(237, 0, 0);
    stage_SetAnimation(240, 0, 0);
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(212, 0, 0);
    stage_SetAnimation(215, 0, 0);
#else
    stage_SetAnimation(269, 0, 0);
    stage_SetAnimation(272, 0, 0);
#endif
#endif
#endif
#endif

    gate_mes[0].func = actE3GateChk;
    sub->mail = gate_mes;
#ifdef VERSION_JUN26
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
#else
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
#endif
}

void actE3CapsuleChk(GObj *volatile self)
{
    scpSekizouCheckPoint();

#ifdef VERSION_JUN26
    gflagOn(310);

    scpAdpcmPlayRequestFunc(5, &e3capsule, 1, 1, 1);
#else
#ifdef VERSION_NTSC
    gflagOn(326);
#else
#ifdef VERSION_AUG6
    gflagOn(325);
#else
    gflagOn(358);
#endif
#endif

    scpAdpcmPlayRequestFunc(2, &e3capsule, 1, 1, 1);
#endif
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

#ifdef VERSION_NTSC
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
#else
inline void actE3DoorUp(GObj *volatile self)
{
#ifdef VERSION_AUG6
    lt_switch_layout(51);
    gflagOn(326);
#else
#ifdef VERSION_JUN26
    lt_switch_layout(51);
    gflagOn(311);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    gflagOn(359);
#endif
#endif

    _ACTWait(60);

#ifdef VERSION_AUG6
    stage_SetAnimation(799, 1, 0);

    soundSeDefPlay(1197, 0, doorUpPos, 1);
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(748, 1, 0);

    soundSeDefPlay(1171, 0, doorUpPos, 1);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(934, 1, 0);
#else
    stage_SetAnimation(953, 1, 0);
#endif

    soundSeDefPlay(1221, 0, doorUpPos, 1);
#endif
#endif

    _ACTWait(30);

#ifdef VERSION_AUG6
    soundSeDefPlay(1198, 0, doorUpPos, 1);

    while (stage_CheckAnimationFinish(799) == 0) {
#else
#ifdef VERSION_JUN26
    soundSeDefPlay(1172, 0, doorUpPos, 1);

    while (stage_CheckAnimationFinish(748) == 0) {
#else
    soundSeDefPlay(1222, 0, doorUpPos, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(934) == 0) {
#else
    while (stage_CheckAnimationFinish(953) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif
}

inline void actE3St13cIntroChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    lt_switch_layout(51);
    gflagOn(330);
#else
#ifdef VERSION_JUN26
    lt_switch_layout(51);
    gflagOn(315);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    gflagOn(363);
#endif
#endif

    scpBoyControlReadDisable = 1;
    _ACTWait(120);

#ifdef VERSION_AUG6
    stage_SetAnimation(800, 1, 0);

    while (stage_CheckAnimationFinish(800) == 0) {
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(749, 1, 0);

    while (stage_CheckAnimationFinish(749) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(935, 1, 0);
#else
    stage_SetAnimation(954, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(935) == 0) {
#else
    while (stage_CheckAnimationFinish(954) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif

    scpBoyControlReadDisable = 0;
}
#endif

inline void actE3CageFallReadyChk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    e3cage = 0;
    _ACTWait(1);
    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_JUN26
    scpAdpcmPlayRequestFunc(6, &e3cage, 1, 1, 0);
#else
    scpAdpcmPlayRequestFunc(3, &e3cage, 1, 1, 0);
#endif
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
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

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    gflagOn(314);

    stage_SetAnimation(146, 1, 0);

    while (stage_CheckAnimationFinish(146) == 0) {
#else
    gflagOn(329);

    stage_SetAnimation(160, 1, 0);

    while (stage_CheckAnimationFinish(160) == 0) {
#endif
#else
    gflagOn(330);

    stage_SetAnimation(161, 1, 0);

    while (stage_CheckAnimationFinish(161) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
}
#else
inline void actE3St01bEneChk(GObj *volatile self)
{
    if ((int)girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    scpBoyControlReadDisable = 1;
    _ACTWait(30);

    gflagOn(362);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(178, 1, 0);
#else
    stage_SetAnimation(182, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(178) == 0) {
#else
    while (stage_CheckAnimationFinish(182) == 0) {
#endif
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

inline void actE3St09aBrgMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = st09aBrgMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

static inline void actE3St09aBrgSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    st09aBrgSwitch_mes[0].func = actE3St09aBrgDown;
    sub->mail = st09aBrgSwitch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif
