#include "common.h"
#include "st04b.h"
#include "layout_texture.h"
#include "pad.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "brain.h"
#include "camera-root.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "item.h"
#include <libvu0.h>
#include "typedef.h"

static ActMail sekizo_mes[2] = {{430}, {429}};

static ActMail ene1_mes[2] = {{430}, {429}};

/* kept local: this TU's uses of ScpCallCameraSetTarget do not fit the prototype in script.h */
extern void ScpCallCameraSetTarget(float x, float y, float z);
/* kept local: this TU's uses of scpTorchLightOn do not fit the prototype in script.h */
extern void scpTorchLightOn(int a0);
extern int D_00639EA8;
/* kept local: this TU's uses of _SCPMoveCharactorByWay do not fit the prototype in script.h */
extern int _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
/* kept local: this TU's uses of RequestStageChangeDirect do not fit the prototype in script.h */
extern void RequestStageChangeDirect(int a0, int a1, int *buf, int a3);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec girlWayPos = {{-10750.0f, -2122.0f, 0.0f, 0.0f}};

static const ConstVec girlWay2Pos = {{-139.0f, -177.0f, 1670.0f, 0.0f}};

void actSt04bEnd(void)
{
    if (D_00639EA8 != 0) {
        if (gflagChk(138) != 0) {
            if (gflagChk(157) == 0) {
                gflagOn(391);
            }
        }
    }
}

extern int D_00639EA4;
extern int D_00639EAC;
extern int D_0063AA08;
extern int sekizo4b;
extern int sekizo_4b;
extern unsigned char sekizo_4b_vol;
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
/* kept local: this TU's uses of scpKillEnemyOne do not fit the prototype in script.h */
extern void scpKillEnemyOne(int a0);
/* kept local: this TU's uses of scpMaskGeneratorAll do not fit the prototype in script.h */
extern void scpMaskGeneratorAll(void);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float x, float y, float z);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int a0, void *dir);
/* kept local: this TU's uses of scpSekizouCheckPoint do not fit the prototype in script.h */
extern void scpSekizouCheckPoint(void);
/* kept local: this TU's uses of scpPlayWaitMotEnd do not fit the prototype in script.h */
extern void scpPlayWaitMotEnd(int a0);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);

void actSt04bSekizoChk(volatile int a0)
{
    /* the SE handle is memory-resident in ROM: soundSeDefPlay hands back a slot
       id the sound side keeps updating, so it is re-read at the stop site rather
       than carried in a callee-saved register */
    volatile int se;
    float v[4];
    int key;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 ||
           scpTriggerBall(a0, D_00639EA8, 200.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    brainLockGirl();

    scpKillEnemyOne(3757);
    scpMaskGeneratorAll();

    scpAdpcmPlayRequestFunc(18, &sekizo4b, 1, 1, 1);
    while (sekizo4b == 0) {
        _ACTWait(1);
    }

    gflagOn(390);

    stage_SetAnimation(191, 1, 0);

    ReviveAllCarryableItemsWithNonSleepFrame(250);

    key = iosPadActRequest(D_00639EAC, 9);
    sekizo_4b_vol = 128;
    iosPadActVolumeSet(sekizo_4b = key, 128);

    se = soundSeDefPlay(1217, 0, 0, 1);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 532);

    scpPlayPosSet(D_00639EA8, -10325.0f, -2150.0f, 0.0f);
    scpPlayPosSet(D_00639EA4, -10325.0f, -2150.0f, -100.0f);
    _ACTWait(1);
    sceVu0SubVector(v, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, v);
    D_0063AA08 = 1;
    sceVu0SubVector(v, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, v);

    scpSekizouCheckPoint();

    scpPlayMot(D_00639EA8, 645);
    scpPlayWaitMotEnd(D_00639EA8);

    gflagOn(159);

    soundSeDefStop(se);

    while (stage_CheckAnimationFrame(191, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_4b);

    scpPlayMot(D_00639EA8, 532);
    scpPlayEnd(D_00639EA8);

    actCreateSubThread(actSt04bGirlWay, 21);

    _ACTWait(30);
    scpPlayMot(D_00639EA4, 252);
    scpPlayWaitMotEnd(D_00639EA4);

    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    ScpCallCameraSetTarget(10793.0f, 2122.0f, 0.0f);

    while (stage_CheckAnimationFinish(191) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);
    D_0063AA08 = 0;
}

/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int attr);
/* kept local: this TU's uses of scpSleepEnemyOne do not fit the prototype in script.h */
extern void scpSleepEnemyOne(int a0);
/* kept local: this TU's uses of scpWakeupEnemyOne do not fit the prototype in script.h */
extern void scpWakeupEnemyOne(int a0);

void actSt04bEne1Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(138) == 0 || (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0 &&
                                  scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0)) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;

    scpSleepEnemyOne(3757);

    gflagOff(391);

    _ACTWait(60);

    gflagOn(157);
    gflagOn(158);

    stage_SetAnimation(184, 1, 0);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFinish(184) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);
    D_0063AA08 = 0;

    scpWakeupEnemyOne(3757);
}

void actSt04bCrest01XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(174) == 0) {
        stage_SetAnimation(185, 0, 0);
        stage_SetAnimation(186, 0, 0);
    } else {
        stage_SetAnimation(185, 0, -1);
        stage_SetAnimation(186, 0, -1);
        scpTorchLightOn(1056);
        scpTorchLightOn(1057);
    }
}

void actSt04bDoorXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    stage_SetAnimation(249, 0, 0);
}

void actSt04bMonyoDoorXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(174) == 0) {
        stage_SetAnimation(250, 0, 0);
    } else {
        stage_SetAnimation(250, 0, -1);
    }
}

void actSt04bSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(159) == 0) {
        stage_SetAnimation(191, 0, 0);
        sekizo_mes[0].func = actSt04bSekizoChk;
        self->mail = sekizo_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(191, 0, -1);
        if (gflagChk(174) == 0) {
            ScpCallCameraSetTarget(10793.0f, 2122.0f, 0.0f);
        }
    }
}

void actSt04bEne1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(157) == 0) {
        ene1_mes[0].func = actSt04bEne1Chk;
        self->mail = ene1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04bEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);
    while (gflagChk(158) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt04bEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);
    while (gflagChk(158) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt04bBallXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(138) == 0) {
        stage_SetAnimation(299, -1, -2);
    } else {
        stage_SetAnimation(297, -1, -2);
    }
}

void actSt04bSolarXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(138) == 0) {
        stage_SetAnimation(301, -1, -2);
        stage_SetAnimation(305, -1, -2);
    }
}

void actSt04bSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt04bGirlWay(volatile int a0)
{
    long long buf[2];
    long long way[2];

    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);

    way[0] = girlWay2Pos.d[0];
    way[1] = girlWay2Pos.d[1];
    RequestStageChangeDirect(D_00639EA8, 0x13, (int *)way, 0xB4);

    brainUnlockGirl();
}
