#include "common.h"
#include "st03t.h"
#include "debug.h"
#include "layout_texture.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-ico2.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "box.h"
#include "motionManager2.h"
#include "typedef.h"

static ActMail switchLChk_mes[2] = {{430}, {429}};

static ActMail switchLUpchk_mes[2] = {{430}, {429}};

static ActMail switchLChk2_mes[2] = {{430}, {429}};

static ActMail switchLUpChk_mes[2] = {{430}, {429}};

static ActMail switchRChk_mes[2] = {{430}, {429}};

static ActMail switchRUpchk_mes[2] = {{430}, {429}};

static ActMail switchRChk2_mes[2] = {{430}, {429}};

static ActMail switchRUpChk_mes[2] = {{430}, {429}};

static ActMail girlCam_mes[2] = {{430}, {429}};

static ActMail girlCamStartChk_mes[2] = {{430}, {429}};

static ActMail girlCamEndChk_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail wayOnchk_mes[2] = {{430}, {429}};

static ActMail wayOffchk_mes[2] = {{430}, {429}};

static ActMail way_on_mes[2] = {{430}, {429}};

static ActMail way_off_mes[2] = {{430}, {429}};

static ActMail girlPos_mes[2] = {{430}, {429}};

static ActMail girlUp_mes[2] = {{430}, {429}};

static ActMail hint1Sleep_mes[2] = {{430}, {429}};

static ActMail hint1OffChk_mes[2] = {{430}, {429}};

static ActMail hint1OnChk_mes[2] = {{430}, {429}};

void actSt03tSwitchL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(89) == 0) {
        stage_SetAnimation(364, 0, 0);
        stage_SetAnimation(366, 0, 0);

        switchLChk_mes[0].func = actSt03tSwitchLChk;
        self->mail = switchLChk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(364, 0, 0x2D);
        stage_SetAnimation(366, 0, -1);

        switchLUpchk_mes[0].func = actSt03tSwitchLUpChk;
        self->mail = switchLUpchk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* kept local: this TU's uses of scpTriggerFloorAttrTargetMan do not fit the prototype in script.h */
extern int scpTriggerFloorAttrTargetMan(int a0, int a1);
extern int D_0028F4C0[];

void actSt03tSwitchLChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;
    int i;

    i = 0;
    while (i < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) {
        if (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    gflagOn(102);

    stage_SetAnimation(364, 1, 0);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(364, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(89);

    stage_SetAnimation(366, 1, 0);

    SetWayGroupActive(7, 1);

    gflagOn(91);

    while (stage_CheckAnimationFrame(366, 75, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1218, 0, 0, 1);

    while (stage_CheckAnimationFrame(366, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1219, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(366) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLChk2_mes[0].func = actSt03tSwitchLUpChk;
    self->mail = switchLChk2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* as script.h declares it; this TU does not include that header */
extern void scpCheckDisconnectWallStart(char *a0);
/* as script.h declares it; this TU does not include that header */
extern void scpCheckDisconnectWallEnd(char *a0);
extern int D_00639EA8;

void actSt03tSwitchLUpChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(60);

    gflagOff(89);

    stage_SetAnimation(364, 1, 0x2E);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(364, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(367, 1, 0);

    if (D_00639EA8 != 0) {
        scpCheckDisconnectWallStart((char *)D_00639EA8);
    }

    SetWayGroupActive(7, 0);

    soundSeDefPlay(1218, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1219, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(367, 120, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (D_00639EA8 != 0) {
        scpCheckDisconnectWallEnd((char *)D_00639EA8);
    }

    switchLUpChk_mes[0].func = actSt03tSwitchLChk;
    self->mail = switchLUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tSwitchR(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(90) == 0) {
        stage_SetAnimation(365, 0, 0);
        stage_SetAnimation(368, 0, 0);

        switchRChk_mes[0].func = actSt03tSwitchRChk;
        self->mail = switchRChk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(365, 0, 0x2D);
        stage_SetAnimation(368, 0, -1);

        switchRUpchk_mes[0].func = actSt03tSwitchRUpChk;
        self->mail = switchRUpchk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt03tSwitchRChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;
    int i;

    i = 0;
    while (i < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) {
        if (scpTriggerFloorAttrTargetMan(a0, 0x2000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    gflagOn(102);

    stage_SetAnimation(365, 1, 0);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(365, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(368, 1, 0);

    SetWayGroupActive(5, 1);

    gflagOn(91);

    soundSeDefPlay(1218, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1219, 0, 0, 1);

    while (stage_CheckAnimationFinish(368) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(90);

    switchRChk2_mes[0].func = actSt03tSwitchRUpChk;
    self->mail = switchRChk2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tSwitchRUpChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttrTargetMan(a0, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) * 0xA);

    gflagOff(90);

    stage_SetAnimation(365, 1, 0x2E);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(365, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(369, 1, 0);

    SetWayGroupActive(5, 0);

    soundSeDefPlay(1218, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1219, 0, 0, 1);

    while (stage_CheckAnimationFinish(369) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchRUpChk_mes[0].func = actSt03tSwitchRChk;
    self->mail = switchRUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);

void actSt03tGene(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask((int)scpSearchGobj(877));
    Generator_Mask((int)scpSearchGobj(878));

    while (gflagChk(105) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(20);
    Generator_Call(a0);

    Generator_Call((int)scpSearchGobj(877));
    Generator_Call((int)scpSearchGobj(878));
}

/* as script.h declares it; this TU does not include that header */
extern void scpTransGObj(void *a0, float x, float y, float z);

void actSt03tBoxA(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(298) == 0) {
        scpSearchGobj(865)->f16C = 0;
    } else {
        scpSearchGobj(852)->f16C = 0;
        scpSearchGobj(863)->f16C = 0;
        scpSearchGobj(865)->f16C = 1;

        scpTransGObj(scpSearchGobj(865), 0.0f, -200.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(865));
    }
}

void actSt03tBoxB(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(299) == 0) {
        scpSearchGobj(866)->f16C = 0;
    } else {
        scpSearchGobj(853)->f16C = 0;
        scpSearchGobj(864)->f16C = 0;
        scpSearchGobj(866)->f16C = 1;

        gflagOn(98);

        scpTransGObj(scpSearchGobj(866), 0.0f, -400.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(866));
    }
}

void actSt03tInit(void)
{
    if (gflagChk(91) != 0) {
        SetWayGroupActive(7, 1);
    } else {
        SetWayGroupActive(7, 0);
    }

    if (gflagChk(92) != 0) {
        SetWayGroupActive(5, 1);
    } else {
        SetWayGroupActive(5, 0);
    }
}

void actSt03tGirlUp(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(93) == 0) {
        girlUp_mes[0].func = actSt03tGirlUpChk;
        self->mail = girlUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(12);
    }
}

void actSt03tGirlCam(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    girlCam_mes[0].func = actSt03tGirlCamStartChk;
    self->mail = girlCam_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpSekizou do not fit the prototype in script.h */
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt03tSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x5F, 0x50, 0, 0x12, -913.0f, -400.0f, 605.0f, -1000.0f, -400.0f, 550.0f);
}

void actSt03tWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(100) == 0) {
        wayOnchk_mes[0].func = actSt03tWayOnChk;
        self->mail = wayOnchk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        wayOffchk_mes[0].func = actSt03tWayOffChk;
        self->mail = wayOffchk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt03tEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(104) == 0) {
        ene_mes[0].func = actSt03tEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt03tGirlPos(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(101) == 0) {
        SleepHint(12);

        girlPos_mes[0].func = actSt03tGirlPosChk;
        self->mail = girlPos_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt03tHint1Sleep(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    hint1Sleep_mes[0].func = actSt03tHint1OffChk;
    self->mail = hint1Sleep_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tGirlCamEvent(int x)
{
    volatile int local = x;
}

extern int D_00639EA4;
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int a1, float radius);

void actSt03tGirlCamStartChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0xCA) {
        _ACTWait(1);
    }

    CameraGetTarget();
    Camctrl_SetTarget(D_00639EA8, 0, 3);
    _ACTWait(15);
    CameraSetCameraSet(0x30);

    girlCamStartChk_mes[0].func = actSt03tGirlCamEndChk;
    sub->mail = girlCamStartChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tGirlCamEndChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0xCA) {
        _ACTWait(1);
    }

    CameraGetTarget();
    _ACTWait(90);
    CameraSetCameraSet_Default();
    Camctrl_ExitEveRock();

    girlCamEndChk_mes[0].func = actSt03tGirlCamStartChk;
    sub->mail = girlCamEndChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tSekizoEvent(int x)
{
    volatile int local = x;
}

extern int D_0063AA08;
/* as script.h declares it; this TU does not include that header */
extern void scpSleepEnemyOne(int a0);
/* as script.h declares it; this TU does not include that header */
extern void scpWakeupEnemyOne(int a0);

void actSt03tEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSleepEnemyOne(3757);
    gflagOn(104);
    gflagOn(105);
    stage_SetAnimation(81, 1, 0);

    while (stage_CheckAnimationFinish(81) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);
    D_0063AA08 = 0;
    scpWakeupEnemyOne(3757);
}

/* as script.h declares it; this TU does not include that header */
extern int scpCheckExistAliveEnemy(void);
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);

/* The way-on watcher's mail record: it installs actSt03tWayOffChk here and
   posts it. Word 0 of each entry is the mail id the entry answers (430 the
   actor post, 429 the trailing entry); .func is filled in at run time.
   Named for the thread that owns and posts it. */

void actSt03tWayOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(17, 1);
    gflagOn(100);

    way_on_mes[0].func = actSt03tWayOffChk;
    sub->mail = way_on_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* The way-off watcher's own mail record (installs actSt03tWayOnChk). */

void actSt03tWayOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(17, 0);
    gflagOff(100);

    way_off_mes[0].func = actSt03tWayOnChk;
    sub->mail = way_off_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tGirlPosChk(volatile int a0)
{
    while (D_00639EA8 == 0 || scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(101);
    WakeupHint(12);
}

void actSt03tGirlUpChk(volatile int a0)
{
    while (D_00639EA8 == 0 || scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");
    gflagOn(93);
    FinishHint(12);
}

void actSt03tHint1OnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x3C);
    WakeupHint(12);

    hint1OnChk_mes[0].func = actSt03tHint1OffChk;
    sub->mail = hint1OnChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt03tHint1OffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (gflagChk(102) == 0) {
        _ACTWait(1);
    }

    SleepHint(12);
    gflagOff(102);

    hint1OffChk_mes[0].func = actSt03tHint1OnChk;
    sub->mail = hint1OffChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
