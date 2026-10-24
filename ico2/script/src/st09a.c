#include "st09a.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "typedef.h"
#include "main.h"

#ifdef VERSION_NTSC
/* .data: actor mail packets. */

static ActMail elvMain_mes[2] = {{376, actSt09aElvSwitch}, {396}}; /* derived name */

static ActMail elv_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elvSwitchUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elvSwitchDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elvDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elvUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brgMain_mes[2] = {{377, actSt09aBrgSwitch}, {396}}; /* derived name */

static ActMail brg_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brgSwitch_mes[2] = {{397}, {396}}; /* derived name */
#else
#ifdef VERSION_AUG6
/* .data: actor mail packets. */

static ActMail elvMain_mes[2] = {{372, actSt09aElvSwitch}, {392}}; /* derived name */

static ActMail elv_mes[2] = {{393}, {392}}; /* derived name */

static ActMail elvSwitchUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail elvSwitchDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail elvDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail elvUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail intro_mes[2] = {{393}, {392}}; /* derived name */

static ActMail brgMain_mes[2] = {{373, actSt09aBrgSwitch}, {392}}; /* derived name */

static ActMail brg_mes[2] = {{393}, {392}}; /* derived name */

static ActMail brgSwitch_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_JUN26
/* .data: actor mail packets. */

static ActMail elvMain_mes[2] = {{356, actSt09aElvSwitch}, {376}}; /* derived name */

static ActMail elv_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elvSwitchUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elvSwitchDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elvDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elvUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail intro_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brgMain_mes[2] = {{357, actSt09aBrgSwitch}, {376}}; /* derived name */

static ActMail brg_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brgSwitch_mes[2] = {{377}, {376}}; /* derived name */
#else
static void actSt09aBrgDownSub(GObj *volatile self);
static void actSt09aHint1Chk(GObj *volatile self);
static void actSt09aHint2Chk(GObj *volatile self);

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for. */
static int demoEnd;

/* .data: actor mail packets. */

static ActMail elvMain_mes[2] = {{406, actSt09aElvSwitch}, {429}}; /* derived name */

static ActMail elv_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elvSwitchUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elvSwitchDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elvDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elvUp_mes[2] = {{430}, {429}}; /* derived name */

static float sekizoPos[4] = {1548.0f, -412.0f, -608.0f, 0.0f}; /* derived name */

static ActMail intro_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brgMain_mes[2] = {{407, actSt09aBrgSwitch}, {429}}; /* derived name */

static ActMail brg_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brgSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint2_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif
#endif

/* .sdata: the bridge stream handle. */
SqEntry *st09a_brg = 0;

#ifdef VERSION_NTSC
/* The stone statue's sound position, a 16-byte constant vector template: the
   float view carries the values, the long long view is the one the copy reads. */
static const ConstVec sekizoPos = {{1548.0f, -412.0f, -608.0f, 0.0f}}; /* derived name */

void actSt09aInit(void)
{
    if (gflagChk(79) == 0) {
        stage_SetAnimation(343, 0, 0);
    } else {
        stage_SetAnimation(343, 0, -1);
    }
}

void actSt09aElvDown(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    /* the sound handle, which the sound subsystem owns; it is kept across
       the animation wait and read again for soundSeDefStop */
    volatile int se;

    lt_switch_layout(51);
    LockForceGroundParent(boyGObj);

    stage_SetAnimation(340, 1, 0);

    se = soundSeDefPlay(1193, 0, 0, 1);

    gflagOn(76);

    while (stage_CheckAnimationFrame(340, 210, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    UnlockForceGroundParent(boyGObj);

    lt_switch_layout(50);

    elvDown_mes[0].func = actSt09aElvMain;
    act->mail = elvDown_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt09aSekizo(GObj *volatile self)
{
    GObj *x = self;
    long long buf[2];

    actInitialize(self);
    _ACTWait(1);

    buf[0] = sekizoPos.d[0];
    buf[1] = sekizoPos.d[1];
    soundSeDefPlay(1319, 0, (float *)buf, 1);
    soundSeDefPlay(1320, 0, (float *)buf, 1);
    soundSeDefPlay(1321, 0, (float *)buf, 1);

    scpSekizou(self, 77, 341, 0, 18, -1350.0f, -100.0f, 1515.0f, -1450.0f, -100.0f, 1515.0f);
}

void actSt09aBrgDown(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(79);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(88, &st09a_brg, 1, 1, 1);

    while (st09a_brg == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(343, 1, 0);

    while (stage_CheckAnimationFrame(343, 115, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(343, 165, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(343) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt09aElv(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(76) != 0) {
        stage_SetAnimation(340, 0, 210);
    } else {
        stage_SetAnimation(340, 0, 0);
    }

    elv_mes[0].func = actSt09aElvMain;
    act->mail = elv_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt09aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(78) == 0) {
        intro_mes[0].func = actSt09aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt09aBrg(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(79) == 0) {
        brg_mes[0].func = actSt09aBrgMain;
        act->mail = brg_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
/* The stone statue's sound position, a 16-byte constant vector template: the
   float view carries the values, the long long view is the one the copy reads. */
static const ConstVec sekizoPos = {{1548.0f, -412.0f, -608.0f, 0.0f}}; /* derived name */

void actSt09aInit(void)
{
#ifdef VERSION_JUN26
    if (gflagChk(77) == 0) {
        stage_SetAnimation(309, 0, 0);
    } else {
        stage_SetAnimation(309, 0, -1);
#else
    if (gflagChk(79) == 0) {
        stage_SetAnimation(342, 0, 0);
    } else {
        stage_SetAnimation(342, 0, -1);
#endif
    }
}
#else
void actSt09aInit(void)
{
    if (gflagChk(86) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(374, 0, 0);
#else
        stage_SetAnimation(378, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(374, 0, -1);
#else
        stage_SetAnimation(378, 0, -1);
#endif
    }
}
#endif

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
void actSt09aElvDown(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    /* the sound handle, which the sound subsystem owns; it is kept across
       the animation wait and read again for soundSeDefStop */
    volatile int se;

    lt_switch_layout(51);
    LockForceGroundParent(boyGObj);

#ifdef VERSION_JUN26
    stage_SetAnimation(306, 1, 0);

    se = soundSeDefPlay(1167, 0, 0, 1);

    gflagOn(74);

    while (stage_CheckAnimationFrame(306, 210, 1) == 0) {
#else
    stage_SetAnimation(339, 1, 0);

    se = soundSeDefPlay(1193, 0, 0, 1);

    gflagOn(76);

    while (stage_CheckAnimationFrame(339, 210, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    UnlockForceGroundParent(boyGObj);

    lt_switch_layout(50);

    elvDown_mes[0].func = actSt09aElvMain;
    act->mail = elvDown_mes;
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 393);
#endif
    _ACTWait(0);
}

void actSt09aSekizo(GObj *volatile self)
{
    GObj *x = self;
    long long buf[2];

    actInitialize(self);
    _ACTWait(1);

    buf[0] = sekizoPos.d[0];
    buf[1] = sekizoPos.d[1];
#ifdef VERSION_JUN26
    soundSeDefPlay(1290, 0, (float *)buf, 1);
    soundSeDefPlay(1291, 0, (float *)buf, 1);
    soundSeDefPlay(1292, 0, (float *)buf, 1);

    scpSekizou(self, 75, 307, 0, 21, -1350.0f, -100.0f, 1515.0f, -1450.0f, -100.0f, 1515.0f);
#else
    soundSeDefPlay(1319, 0, (float *)buf, 1);
    soundSeDefPlay(1320, 0, (float *)buf, 1);
    soundSeDefPlay(1321, 0, (float *)buf, 1);

    scpSekizou(self, 77, 340, 0, 18, -1350.0f, -100.0f, 1515.0f, -1450.0f, -100.0f, 1515.0f);
#endif
}

void actSt09aBrgDown(GObj *volatile self)
{
    lt_switch_layout(51);
#ifdef VERSION_JUN26
    gflagOn(77);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(83, &st09a_brg, 1, 1, 1);
#else
    gflagOn(79);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(88, &st09a_brg, 1, 1, 1);
#endif

    while (st09a_brg == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(309, 1, 0);

    while (stage_CheckAnimationFrame(309, 115, 0) == 0) {
#else
    stage_SetAnimation(342, 1, 0);

    while (stage_CheckAnimationFrame(342, 115, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(309, 165, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(342, 165, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

#ifdef VERSION_JUN26
    while (stage_CheckAnimationFinish(309) == 0) {
#else
    while (stage_CheckAnimationFinish(342) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
#else
void actSt09aElvDown(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    /* the sound handle, which the sound subsystem owns; it is kept across
       the animation wait and read again for soundSeDefStop */
    volatile int se;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    LockForceGroundParent(boyGObj);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(371, 1, 0);
#else
    stage_SetAnimation(375, 1, 0);
#endif

    se = soundSeDefPlay(1217, 0, 0, 1);

    gflagOn(83);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(371, 210, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(375, 210, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    UnlockForceGroundParent(boyGObj);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    elvDown_mes[0].func = actSt09aElvMain;
    act->mail = elvDown_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt09aBrgDown(GObj *volatile self)
{
    GProc *th;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    gflagOn(86);
    scpAdpcmPlayRequestFunc(90, &st09a_brg, 1, 1, 1);

    while (st09a_brg == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(actSt09aBrgDownSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st09a_brg, 256);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(374, 0, -1);
#else
        stage_SetAnimation(378, 0, -1);
#endif
        scpFadeIn(5.0f);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}
#endif

void actSt09aElv(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(76) != 0) {
        stage_SetAnimation(339, 0, 210);
    } else {
        stage_SetAnimation(339, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(74) != 0) {
        stage_SetAnimation(306, 0, 210);
    } else {
        stage_SetAnimation(306, 0, 0);
#else
    if (gflagChk(83) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(371, 0, 210);
#else
        stage_SetAnimation(375, 0, 210);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(371, 0, 0);
#else
        stage_SetAnimation(375, 0, 0);
#endif
#endif
#endif
    }

    elv_mes[0].func = actSt09aElvMain;
    act->mail = elv_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
#else
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
#else
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt09aSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    soundSeDefPlay(1346, 0, sekizoPos, 1);
    soundSeDefPlay(1347, 0, sekizoPos, 1);
    soundSeDefPlay(1348, 0, sekizoPos, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    scpSekizou(self, 84, 372, 0, 18, -1350.0f, -100.0f, 1515.0f, -1450.0f, -100.0f, 1515.0f);
#else
    scpSekizou(self, 84, 376, 0, 18, -1350.0f, -100.0f, 1515.0f, -1450.0f, -100.0f, 1515.0f);
#endif
#endif
#endif
}

void actSt09aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(78) == 0) {
        intro_mes[0].func = actSt09aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(76) == 0) {
        intro_mes[0].func = actSt09aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(85) == 0) {
        intro_mes[0].func = actSt09aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt09aBrg(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    if (gflagChk(77) == 0) {
        brg_mes[0].func = actSt09aBrgMain;
        act->mail = brg_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
#else
    if (gflagChk(79) == 0) {
        brg_mes[0].func = actSt09aBrgMain;
        act->mail = brg_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
#endif
#else
    if (gflagChk(86) == 0) {
        brg_mes[0].func = actSt09aBrgMain;
        act->mail = brg_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt09aHint1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(87) == 0) {
        hint1_mes[0].func = actSt09aHint1Chk;
        act->mail = hint1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        FinishHint(10);
    }
}

void actSt09aHint2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(88) == 0) {
        hint2_mes[0].func = actSt09aHint2Chk;
        act->mail = hint2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        FinishHint(11);
#endif
    }
}
#endif

void actSt09aElvMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = elvMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
void actSt09aElvSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    if (gflagChk(76) != 0) {
        elvSwitchUp_mes[0].func = actSt09aElvUp;
        sub->mail = elvSwitchUp_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }

    elvSwitchDown_mes[0].func = actSt09aElvDown;
    sub->mail = elvSwitchDown_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt09aElvUp(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    /* the sound handle, which the sound subsystem owns; it is kept across
       the animation wait and read again for soundSeDefStop */
    volatile int se;

    lt_switch_layout(51);

    stage_SetAnimation(340, 1, 211);

    se = soundSeDefPlay(1193, 0, 0, 1);

    gflagOff(76);

    while (stage_CheckAnimationFrame(340, 420, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    lt_switch_layout(50);

    elvUp_mes[0].func = actSt09aElvMain;
    act->mail = elvUp_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
#else
void actSt09aElvSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

#ifdef VERSION_AUG6
    if (gflagChk(76) != 0) {
        elvSwitchUp_mes[0].func = actSt09aElvUp;
        sub->mail = elvSwitchUp_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(74) != 0) {
        elvSwitchUp_mes[0].func = actSt09aElvUp;
        sub->mail = elvSwitchUp_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(83) != 0) {
        elvSwitchUp_mes[0].func = actSt09aElvUp;
        sub->mail = elvSwitchUp_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }

    elvSwitchDown_mes[0].func = actSt09aElvDown;
    sub->mail = elvSwitchDown_mes;
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

void actSt09aElvUp(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    /* the sound handle, which the sound subsystem owns; it is kept across
       the animation wait and read again for soundSeDefStop */
    volatile int se;

#ifdef VERSION_AUG6
    lt_switch_layout(51);

    stage_SetAnimation(339, 1, 211);

    se = soundSeDefPlay(1193, 0, 0, 1);

    gflagOff(76);

    while (stage_CheckAnimationFrame(339, 420, 1) == 0) {
#else
#ifdef VERSION_JUN26
    lt_switch_layout(51);

    stage_SetAnimation(306, 1, 211);

    se = soundSeDefPlay(1167, 0, 0, 1);

    gflagOff(74);

    while (stage_CheckAnimationFrame(306, 420, 1) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(371, 1, 211);
#else
    stage_SetAnimation(375, 1, 211);
#endif

    se = soundSeDefPlay(1217, 0, 0, 1);

    gflagOff(83);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(371, 420, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(375, 420, 1) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif

    elvUp_mes[0].func = actSt09aElvMain;
    act->mail = elvUp_mes;
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
#endif

void actSt09aSekizoEvent(int x)
{
    volatile int local = x;
}

#ifdef VERSION_NTSC
void actSt09aIntroChk(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(78);

    scpBoyControlReadDisable = 1;
    _ACTWait(1);

    stage_SetAnimation(342, 1, 0);

    while (stage_CheckAnimationFinish(342) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
}
#else
void actSt09aIntroChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    lt_switch_layout(51);
    gflagOn(78);
#else
#ifdef VERSION_JUN26
    lt_switch_layout(51);
    gflagOn(76);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    gflagOn(85);
#endif
#endif

    scpBoyControlReadDisable = 1;
    _ACTWait(1);

#ifdef VERSION_AUG6
    stage_SetAnimation(341, 1, 0);

    while (stage_CheckAnimationFinish(341) == 0) {
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(308, 1, 0);

    while (stage_CheckAnimationFinish(308) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(373, 1, 0);
#else
    stage_SetAnimation(377, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(373) == 0) {
#else
    while (stage_CheckAnimationFinish(377) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
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

void actSt09aBrgMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    scpBoyControlReadDisable = 0;
#endif

    sub->mainMail = brgMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt09aBrgSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    brgSwitch_mes[0].func = actSt09aBrgDown;
    sub->mail = brgSwitch_mes;
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

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
static void actSt09aBrgDownSub(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(374, 1, 0);
#else
    stage_SetAnimation(378, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(374, 115, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(378, 115, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(374, 165, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(378, 165, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(374) == 0) {
#else
    while (stage_CheckAnimationFinish(378) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

static void actSt09aHint1Chk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");

    gflagOn(87);
    FinishHint(10);
}

static void actSt09aHint2Chk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 400.0f) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT2_FINISH!!!!!!!!!!!!!!!\n");

    gflagOn(88);
    FinishHint(11);
}
#endif
