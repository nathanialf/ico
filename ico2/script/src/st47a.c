#include "st47a.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "brain.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "item.h"
#include "motionManager2.h"
#include <libvu0.h>
#include <string.h>
#include "typedef.h"
#include "script.h"
#include "main.h"

/* The functions stand in the order this build's TRFILE numbers them: each
   actor before the handlers it posts, the enemy group last. The ones defined
   inline are output at the end of the file in the order of their first
   declarations (the entry points in st47a.h first); the others where they
   stand. */

void actSt47aInit(void)
{
    if (gflagChk(44) != 0) {
        stage_SetAnimation(144, 0, 0);
        SetWayGroupActive(33, 1);
    } else {
        stage_SetAnimation(143, 0, 0);
        SetWayGroupActive(33, 0);
    }

    if (gflagChk(45) != 0) {
        stage_SetAnimation(146, 0, 0);
        SetWayGroupActive(34, 1);
    } else {
        stage_SetAnimation(145, 0, 0);
        SetWayGroupActive(34, 0);
    }
}

void actSt47aEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(49) == 0) {
            gflagOn(357);
        }
    }
}

/* .sdata: the statue and wing stream handles and the statue's shake. */
SqEntry *sekizo47a = 0;

SqEntry *hane1up = 0;

SqEntry *hane2up = 0;

SqEntry *hane1down = 0;

SqEntry *hane2down = 0;

int sekizo_47a = 0;

unsigned char sekizo_47a_vol = 0;

inline void actSt47aSekizo1Event(int x);
inline void actSt47aGirlWay(GObj *volatile self);
inline void actSt47aSekizo2Event(int x);
inline void actSt47aSekizo3Event(int x);
inline void actSt47aSekizo4Event(int x);
inline void actSt47aHane1Main(GObj *volatile self);
inline void actSt47aHane1Switch(GObj *volatile self);
inline void actSt47aHane1Down(GObj *volatile self);
inline void actSt47aHane1_1Girl(GObj *volatile self);
inline void actSt47aHane1_2Girl(GObj *volatile self);
inline void actSt47aHane2Main(GObj *volatile self);
inline void actSt47aHane2Switch(GObj *volatile self);
inline void actSt47aHane2Down(GObj *volatile self);
inline void actSt47aHane2Girl(GObj *volatile self);
inline void actSt47aBarricadeEvent(int x);
inline void actSt47aBarricadeChk(GObj *volatile self);
inline void actSt47aExitChk(GObj *volatile self);
inline void actSt47aExit2Chk(GObj *volatile self);
inline void actSt47aEneChk(GObj *volatile self);
void actSt47aSekizo1Chk(GObj *volatile self);
void actSt47aHane1Up(GObj *volatile self);
void actSt47aHane2Up(GObj *volatile self);
void actSt47aRopeChk(GObj *volatile self);

static ActMail sekizo1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail hane1Main_mes[2] = {{372, actSt47aHane1Switch}, {392}}; /* derived name */

static ActMail hane1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail hane1SwitchUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail hane1SwitchDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail hane1Down_mes[2] = {{393}, {392}}; /* derived name */

static ActMail hane1Up_mes[2] = {{393}, {392}}; /* derived name */

static ActMail hane2Main_mes[2] = {{373, actSt47aHane2Switch}, {392}}; /* derived name */

static ActMail hane2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail hane2SwitchUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail hane2SwitchDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail hane2Down_mes[2] = {{393}, {392}}; /* derived name */

static ActMail hane2Up_mes[2] = {{393}, {392}}; /* derived name */

static ActMail rope_mes[2] = {{393}, {392}}; /* derived name */

static ActMail barricade_mes[2] = {{393}, {392}}; /* derived name */

static ActMail exit_mes[2] = {{393}, {392}}; /* derived name */

static ActMail exit2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

inline void actSt47aSekizo1Event(int x)
{
    volatile int local = x;
}

inline void actSt47aSekizo1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(40) == 0) {
        stage_SetAnimation(139, 0, 0);
        sekizo1_mes[0].func = actSt47aSekizo1Chk;
        act->mail = sekizo1_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(139, 0, -1);
        if (gflagChk(123) == 0) {
            ScpCallCameraSetTarget(-3000.0f, 272.0f, 0.0f);
        }
    }
}

void actSt47aSekizo1Chk(GObj *volatile self)
{
    /* the sound handle, which the sound subsystem owns; it is kept across
       the whole cutscene and read again for soundSeDefStop */
    volatile int se;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 ||
           scpTriggerBall(self, girlGObj, 200.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 75) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(18, &sekizo47a, 1, 1, 1);
    while (sekizo47a == 0) {
        _ACTWait(1);
    }

    scpKillEnemyAll();
    scpMaskGeneratorAll();

    gflagOn(356);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    brainLockGirl();

    _ACTWait(60);

    stage_SetAnimation(139, 1, 0);

    ReviveAllCarryableItemsWithNonSleepFrame(300);

    sekizo_47a = iosPadActRequest(boyPad, 9);
    sekizo_47a_vol = 128;
    iosPadActVolumeSet(sekizo_47a, 128);

    se = soundSeDefPlay(1193, 0, 0, 1);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    scpPlayPosSet(girlGObj, 1750.0f, -272.0f, 0.0f);
    scpPlayPosSet(boyGObj, 1750.0f, -272.0f, 50.0f);

    _ACTWait(1);
    {
        Vec16 v;

        sceVu0SubVector(v.f, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
        scpPlayMotDir(girlGObj, v.f);
        scpBoyControlReadDisable = 1;
        sceVu0SubVector(v.f, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
        scpPlayMotDir(boyGObj, v.f);

        scpSekizouCheckPoint();

        scpPlayMot(girlGObj, 573);
        scpPlayWaitMotEnd(girlGObj);

        gflagOn(40);

        soundSeDefStop(se);
    }

    while (stage_CheckAnimationFrame(139, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_47a);

    scpPlayMot(girlGObj, 514);
    scpPlayEnd(girlGObj);

    actCreateSubThread(actSt47aGirlWay, 21);

    _ACTWait(30);

    scpPlayMot(boyGObj, 247);
    scpPlayWaitMotEnd(boyGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    ScpCallCameraSetTarget(-3000.0f, 272.0f, 0.0f);
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{2266.0f, -272.0f, 0.0f, 0.0f}}; /* derived name */

static const ConstVec hane1_1GirlPos = {{-1076.0f, -1972.0f, 755.0f, 0.0f}}; /* derived name */

static const ConstVec hane1_2GirlPos = {{1028.0f, -1972.0f, 744.0f, 0.0f}}; /* derived name */

static const ConstVec hane2GirlPos = {{-1031.0f, -1972.0f, -747.0f, 0.0f}}; /* derived name */

inline void actSt47aGirlWay(GObj *volatile self)
{
    long long buf[2];
    long long way[2];

    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);

    memset(way, 0, 16);
    RequestStageChangeDirect(girlGObj, 11, way, 180);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    brainUnlockGirl();
}

inline void actSt47aSekizo2Event(int x)
{
    volatile int local = x;
}

inline void actSt47aSekizo2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpSekizou(self, 41, 140, 0, 18, -2450.0f, -1372.0f, -1150.0f, -2450.0f, -1372.0f, -1250.0f);
}

inline void actSt47aSekizo3Event(int x)
{
    volatile int local = x;
}

inline void actSt47aSekizo3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpSekizou(self, 42, 141, 0, 18, 1700.0f, -1972.0f, 650.0f, 1700.0f, -1972.0f, 750.0f);
}

inline void actSt47aSekizo4Event(int x)
{
    volatile int local = x;
}

inline void actSt47aSekizo4(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpSekizou(self, 43, 142, 0, 18, 1700.0f, -1972.0f, -650.0f, 1700.0f, -1972.0f, -750.0f);
}

inline void actSt47aHane1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    gflagChk(44);

    hane1_mes[0].func = actSt47aHane1Main;
    act->mail = hane1_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt47aHane1Main(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    scpWakeupEnemyAll();

    sub->mainMail = hane1Main_mes;
    while (1) {
        _ACTWait(1);
    }
}

inline void actSt47aHane1Switch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    if (gflagChk(44) != 0) {
        hane1SwitchUp_mes[0].func = actSt47aHane1Up;
        sub->mail = hane1SwitchUp_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }

    hane1SwitchDown_mes[0].func = actSt47aHane1Down;
    sub->mail = hane1SwitchDown_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt47aHane1Down(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(62, &hane1down, 1, 1, 1);

    while (hane1down == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(143, 1, 0);

    SetWayGroupActive(33, 1);

    gflagOn(44);

    while (stage_CheckAnimationFinish(143) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    hane1Down_mes[0].func = actSt47aHane1Main;
    act->mail = hane1Down_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt47aHane1Up(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    if (girlGObj != 0) {
        if (scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
            actCreateSubThread(actSt47aHane1_1Girl, 21);
        }
        if (scpTriggerFloorAttr(girlGObj, 0x4000000) != 0) {
            actCreateSubThread(actSt47aHane1_2Girl, 21);
        }
    }

    scpAdpcmPlayRequestFunc(64, &hane1up, 1, 1, 1);

    while (hane1up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(144, 1, 0);

    SetWayGroupActive(33, 0);

    gflagOff(44);

    while (stage_CheckAnimationFinish(144) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    hane1Up_mes[0].func = actSt47aHane1Main;
    act->mail = hane1Up_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt47aHane1_1Girl(GObj *volatile self)
{
    long long buf[2];
    buf[0] = hane1_1GirlPos.d[0];
    buf[1] = hane1_1GirlPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
}

inline void actSt47aHane1_2Girl(GObj *volatile self)
{
    long long buf[2];
    buf[0] = hane1_2GirlPos.d[0];
    buf[1] = hane1_2GirlPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
}

inline void actSt47aHane2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    hane2_mes[0].func = actSt47aHane2Main;
    act->mail = hane2_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt47aHane2Main(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    scpWakeupEnemyAll();

    sub->mainMail = hane2Main_mes;
    while (1) {
        _ACTWait(1);
    }
}

inline void actSt47aHane2Switch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    if (gflagChk(45) != 0) {
        hane2SwitchUp_mes[0].func = actSt47aHane2Up;
        sub->mail = hane2SwitchUp_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }

    hane2SwitchDown_mes[0].func = actSt47aHane2Down;
    sub->mail = hane2SwitchDown_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt47aHane2Down(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(63, &hane2down, 1, 1, 1);

    while (hane2down == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(145, 1, 0);

    SetWayGroupActive(34, 1);

    gflagOn(45);

    while (stage_CheckAnimationFinish(145) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    hane2Down_mes[0].func = actSt47aHane2Main;
    act->mail = hane2Down_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

void actSt47aHane2Up(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        actCreateSubThread(actSt47aHane2Girl, 21);
    }

    scpAdpcmPlayRequestFunc(65, &hane2up, 1, 1, 1);

    while (hane2up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(146, 1, 0);

    SetWayGroupActive(34, 0);

    gflagOff(45);

    while (stage_CheckAnimationFinish(146) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    hane2Up_mes[0].func = actSt47aHane2Main;
    act->mail = hane2Up_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt47aHane2Girl(GObj *volatile self)
{
    long long buf[2];
    buf[0] = hane2GirlPos.d[0];
    buf[1] = hane2GirlPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
}

inline void actSt47aRope(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(46) == 0) {
        stage_SetAnimation(147, 0, 0);
        scpSearchGobj(459)->active = 0;
        rope_mes[0].func = actSt47aRopeChk;
        act->mail = rope_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(148, 0, -1);
        scpSearchGobj(459)->active = 1;
    }
}

void actSt47aRopeChk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(46) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(438))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(147, 1, 0);
            while (stage_CheckAnimationFinish(147) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(438)->active = 0;

            lt_switch_layout(51);
            scpBoyControlReadDisable = 1;

            gflagOn(46);

            scpSleepEnemyAll();

            _ACTWait(15);

            stage_SetAnimation(148, 1, 0);

            while (stage_CheckAnimationFrame(148, 148, 0) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);

            scpSearchGobj(459)->active = 1;

            while (stage_CheckAnimationFinish(148) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);

            scpWakeupEnemyAll();
            scpBoyControlReadDisable = 0;
            lt_switch_layout(50);
            break;
        }
    }
}

inline void actSt47aBarricadeEvent(int x)
{
    volatile int local = x;
}

inline void actSt47aBarricade(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(47) == 0) {
        stage_SetAnimation(149, 0, 0);
        barricade_mes[0].func = actSt47aBarricadeChk;
        act->mail = barricade_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(149, 0, -1);
    }
}

inline void actSt47aBarricadeChk(GObj *volatile self)
{
    GObj *n;

    while ((n = scpIsBombExplode(19)) == 0 || scpTriggerBall(self, n, 350.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    stage_SetAnimation(149, 1, 0);

    gflagOn(47);

    while (stage_CheckAnimationFinish(149) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    scpWakeupEnemyAll();
}

inline void actSt47aExit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    exit_mes[0].func = actSt47aExitChk;
    act->mail = exit_mes;
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
}

inline void actSt47aExitChk(GObj *volatile self)
{
    scpSearchGobj(437)->active = 0;

    while ((gflagChk(155) == 0) || (gflagChk(209) == 0)) {
        _ACTWait(1);
    }

    gflagOn(48);
    scpSearchGobj(436)->active = 0;
    scpSearchGobj(437)->active = 1;
}

inline void actSt47aExit2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(130) != 0) {
        exit2_mes[0].func = actSt47aExit2Chk;
        act->mail = exit2_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

inline void actSt47aExit2Chk(GObj *volatile self)
{
    scpSearchGobj(436)->active = 1;
    scpSearchGobj(437)->active = 0;
}

inline void actSt47aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(49) == 0) {
        ene_mes[0].func = actSt47aEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

inline void actSt47aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOff(357);
    _ACTWait(1);
    gflagOn(49);
    gflagOn(50);
}

void actSt47aEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(469));

    while (gflagChk(50) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);

    Generator_Call(scpSearchGobj(469));
}

inline void actSt47aEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(50) == 0) {
        _ACTWait(1);
    }

    _ACTWait(180);

    Generator_MaskOff(self);
    Generator_Call(self);

    _ACTWait(60);

    Generator_Call(self);
}

inline void actSt47aEnemy3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(50) == 0) {
        _ACTWait(1);
    }

    _ACTWait(180);

    Generator_MaskOff(self);
    Generator_Call(self);

    _ACTWait(60);

    Generator_Call(self);
}

inline void actSt47aEnemy4(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(50) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);
}

void actSt47aTorch(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(139) != 0) {
        scpTorchLightOn(445);
        scpTorchLightOn(446);
        scpTorchLightOn(447);
        scpTorchLightOn(448);
        scpTorchLightOn(449);
        scpTorchLightOn(450);
        scpTorchLightOn(451);
        scpTorchLightOn(452);
        scpTorchLightOn(453);
        scpTorchLightOn(454);
        scpTorchLightOn(455);
        scpTorchLightOn(456);
        scpTorchLightOn(457);
        scpTorchLightOn(458);
    }
}
