#include "common.h"
#include "st05b.h"
#include "layout_texture.h"
#include "pad.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "brain.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "item.h"
#include <libvu0.h>
#include "typedef.h"

static ActMail sekizo_mes[2] = {{430}, {429}};

/* kept local: this TU's uses of ScpCallCameraSetTarget do not fit the prototype in script.h */
extern void ScpCallCameraSetTarget(float x, float y, float z);
/* kept local: this TU's uses of scpTorchLightOn do not fit the prototype in script.h */
extern void scpTorchLightOn(int id);

void actSt05bCrest01XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    if (gflagChk(243) == 0) {
        stage_SetAnimation(187, 0, 0);
        stage_SetAnimation(189, 0, 0);
    } else {
        stage_SetAnimation(187, 0, -1);
        stage_SetAnimation(189, 0, -1);
        scpTorchLightOn(1343);
        scpTorchLightOn(1344);
    }
    if (gflagChk(244) == 0) {
        stage_SetAnimation(188, 0, 0);
    } else {
        stage_SetAnimation(188, 0, -1);
        scpTorchLightOn(1345);
        scpTorchLightOn(1346);
    }
    if (gflagChk(251) == 0) {
        stage_SetAnimation(190, 0, 0);
    } else {
        stage_SetAnimation(190, 0, -1);
    }
}

extern int sekizo5b;
extern int sekizo_5b;
extern unsigned char sekizo_5b_vol;
extern int D_00639EA4;
extern int D_00639EA8;
extern int D_00639EAC;
extern int D_0063AA08;
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
/* kept local: this TU's uses of scpKillEnemyAll do not fit the prototype in script.h */
extern void scpKillEnemyAll(void);
/* kept local: this TU's uses of scpMaskGeneratorAll do not fit the prototype in script.h */
extern void scpMaskGeneratorAll(void);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int gobj);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int gobj, int mot);
/* kept local: this TU's uses of scpPlayWaitMotEnd do not fit the prototype in script.h */
extern void scpPlayWaitMotEnd(int gobj);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int gobj);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int gobj, float x, float y, float z);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int gobj, float *dir);
/* kept local: this TU's uses of scpSekizouCheckPoint do not fit the prototype in script.h */
extern void scpSekizouCheckPoint(void);

void actSt05bSekizoChk(volatile int a0)
{
    volatile int h;
    float d[4];

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
    scpKillEnemyAll();
    scpMaskGeneratorAll();
    scpAdpcmPlayRequestFunc(18, &sekizo5b, 1, 1, 1);
    while (sekizo5b == 0) {
        _ACTWait(1);
    }
    gflagOn(390);
    stage_SetAnimation(192, 1, 0);
    ReviveAllCarryableItemsWithNonSleepFrame(250);
    sekizo_5b = iosPadActRequest(D_00639EAC, 9);
    sekizo_5b_vol = 0x80;
    iosPadActVolumeSet(sekizo_5b, 0x80);
    h = soundSeDefPlay(1217, 0, 0, 1);
    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 532);
    scpPlayPosSet(D_00639EA8, 10350.0f, -2150.0f, 0.0f);
    scpPlayPosSet(D_00639EA4, 10350.0f, -2150.0f, -100.0f);
    _ACTWait(1);
    sceVu0SubVector(d, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, d);
    D_0063AA08 = 1;
    sceVu0SubVector(d, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, d);
    scpSekizouCheckPoint();
    scpPlayMot(D_00639EA8, 645);
    scpPlayWaitMotEnd(D_00639EA8);
    gflagOn(160);
    soundSeDefStop(h);
    while (stage_CheckAnimationFrame(192, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_5b);
    scpPlayMot(D_00639EA8, 532);
    scpPlayEnd(D_00639EA8);
    actCreateSubThread(actSt05bGirlWay, 21);
    _ACTWait(30);
    scpPlayMot(D_00639EA4, 252);
    scpPlayWaitMotEnd(D_00639EA4);
    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    ScpCallCameraSetTarget(-10793.0f, 2122.0f, 0.0f);
    while (stage_CheckAnimationFinish(192) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(54);
    D_0063AA08 = 0;
}

void actSt05bDoorXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(243) != 0 && gflagChk(139) == 0) {
        stage_SetAnimation(345, 0, -1);
    } else {
        stage_SetAnimation(345, 0, 0);
    }
}

void actSt05bMonyoDoorXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(234) == 0) {
        stage_SetAnimation(251, 0, 0);
    } else {
        stage_SetAnimation(251, 0, -1);
    }
}

void actSt05bSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(160) == 0) {
        stage_SetAnimation(192, 0, 0);
        sekizo_mes[0].func = actSt05bSekizoChk;
        self->mail = sekizo_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(192, 0, -1);
        if (gflagChk(243) == 0) {
            ScpCallCameraSetTarget(-10793.0f, 2122.0f, 0.0f);
        }
    }
}

void actSt05bBallXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(139) == 0) {
        stage_SetAnimation(300, -1, -2);
    } else {
        stage_SetAnimation(298, -1, -2);
    }
}

void actSt05bSolarXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(139) == 0) {
        stage_SetAnimation(303, -1, -2);
        stage_SetAnimation(306, -1, -2);
    }
}

void actSt05bSekizoEvent(int x)
{
    volatile int local = x;
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec girlWayPos = {{10750.0f, -2122.0f, 0.0f, 0.0f}};

static const ConstVec girlWay2Pos = {{139.0f, -177.0f, 1670.0f, 0.0f}};

/* Returns int: st04b.c carries the same prototype, and the live $2 at the
 * call boundary is what puts the second way record's %hi in $3. */
/* kept local: this TU's uses of _SCPMoveCharactorByWay do not fit the prototype in script.h */
extern int _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
/* kept local: this TU's uses of RequestStageChangeDirect do not fit the prototype in script.h */
extern void RequestStageChangeDirect(int a0, int a1, int *buf, int a3);

void actSt05bGirlWay(volatile int a0)
{
    long long buf[2];
    long long way[2];

    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);

    way[0] = girlWay2Pos.d[0];
    way[1] = girlWay2Pos.d[1];
    RequestStageChangeDirect(D_00639EA8, 0x1C, (int *)way, 0xB4);
    brainUnlockGirl();
}
