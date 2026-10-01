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

/* kept local: agrees with script.h, which this TU does not include (RequestStageChangeDirect, _SCPMoveCharactorByWay differ) */
extern void ScpCallCameraSetTarget(float x, float y, float z);
/* kept local: agrees with script.h, which this TU does not include (RequestStageChangeDirect, _SCPMoveCharactorByWay differ) */
extern void scpTorchLightOn(int a0);
/* kept local: int here, GObj * in main.h */
extern int girlGObj;
/* kept local: int (int, int, int *, int, float) here, int (char *, int, int, float, int) in script.h */
extern int _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
/* kept local: void (int, int, int *, int) here, void (int *) in script.h */
extern void RequestStageChangeDirect(int a0, int a1, int *buf, int a3);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec girlWayPos = {{-10750.0f, -2122.0f, 0.0f, 0.0f}};

static const ConstVec girlWay2Pos = {{-139.0f, -177.0f, 1670.0f, 0.0f}};

void actSt04bEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(138) != 0) {
            if (gflagChk(157) == 0) {
                gflagOn(391);
            }
        }
    }
}

/* kept local: int here, GObj * in main.h */
extern int boyGObj;
/* kept local: agrees with main.h, which this TU does not include (boyGObj, girlGObj differ) */
extern int boyPad;
/* kept local: agrees with script.h, which this TU does not include (RequestStageChangeDirect, _SCPMoveCharactorByWay differ) */
extern int scpBoyControlReadDisable;
/* kept local: int (int, int, float) here, int (char *, char *, float) in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
/* kept local: agrees with script.h, which this TU does not include (RequestStageChangeDirect, _SCPMoveCharactorByWay differ) */
extern void scpKillEnemyOne(int a0);
/* kept local: agrees with script.h, which this TU does not include (RequestStageChangeDirect, _SCPMoveCharactorByWay differ) */
extern void scpMaskGeneratorAll(void);
/* kept local: void (int, int *, int, int, int) here, void (int, char **, int, int, int) in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: agrees with script.h, which this TU does not include (RequestStageChangeDirect, _SCPMoveCharactorByWay differ) */
extern void scpPlayStart(int a0);
/* kept local: void (int, int) here, void (char *, int) in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: void (int, float, float, float) here, void (void *, float, float, float) in script.h */
extern void scpPlayPosSet(int a0, float x, float y, float z);
/* kept local: void (int, void *) here, void (char *, float *) in script.h */
extern void scpPlayMotDir(int a0, void *dir);
/* kept local: agrees with script.h, which this TU does not include (RequestStageChangeDirect, _SCPMoveCharactorByWay differ) */
extern void scpSekizouCheckPoint(void);
/* kept local: void (int) here, void (char *) in script.h */
extern void scpPlayWaitMotEnd(int a0);
/* kept local: agrees with script.h, which this TU does not include (RequestStageChangeDirect, _SCPMoveCharactorByWay differ) */
extern void scpPlayEnd(int a0);

/* .sdata, owned by st04b.o, in the ROM's order: the stone statue's stream handle, its shake and the shake's volume. */
int sekizo4b = 0;

int sekizo_4b = 0;

unsigned char sekizo_4b_vol = 0;

void actSt04bSekizoChk(volatile int a0)
{
    /* the SE handle is memory-resident in ROM: soundSeDefPlay hands back a slot
       id the sound side keeps updating, so it is re-read at the stop site rather
       than carried in a callee-saved register */
    volatile int se;
    float v[4];
    int key;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, boyGObj, 200.0f) == 0 || scpTriggerBall(a0, girlGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
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

    key = iosPadActRequest(boyPad, 9);
    sekizo_4b_vol = 128;
    iosPadActVolumeSet(sekizo_4b = key, 128);

    se = soundSeDefPlay(1217, 0, 0, 1);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 532);

    scpPlayPosSet(girlGObj, -10325.0f, -2150.0f, 0.0f);
    scpPlayPosSet(boyGObj, -10325.0f, -2150.0f, -100.0f);
    _ACTWait(1);
    sceVu0SubVector(v, test_CURRENTROOT(a0), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, v);
    scpBoyControlReadDisable = 1;
    sceVu0SubVector(v, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, v);

    scpSekizouCheckPoint();

    scpPlayMot(girlGObj, 645);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(159);

    soundSeDefStop(se);

    while (stage_CheckAnimationFrame(191, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_4b);

    scpPlayMot(girlGObj, 532);
    scpPlayEnd(girlGObj);

    actCreateSubThread(actSt04bGirlWay, 21);

    _ACTWait(30);
    scpPlayMot(boyGObj, 252);
    scpPlayWaitMotEnd(boyGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    ScpCallCameraSetTarget(10793.0f, 2122.0f, 0.0f);

    while (stage_CheckAnimationFinish(191) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);
    scpBoyControlReadDisable = 0;
}

/* kept local: int (int, int) here, int (char *, int) in script.h */
extern int scpTriggerFloorAttr(int a0, int attr);
/* kept local: agrees with script.h, which this TU does not include (RequestStageChangeDirect, _SCPMoveCharactorByWay differ) */
extern void scpSleepEnemyOne(int a0);
/* kept local: agrees with script.h, which this TU does not include (RequestStageChangeDirect, _SCPMoveCharactorByWay differ) */
extern void scpWakeupEnemyOne(int a0);

void actSt04bEne1Chk(volatile int a0)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(138) == 0 || (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 &&
                                  scpTriggerFloorAttr(boyGObj, 0x2000000) == 0)) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;

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
    scpBoyControlReadDisable = 0;

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
    _SCPMoveCharactorByWay(girlGObj, 0, (int *)buf, 0, 100.0f);

    way[0] = girlWay2Pos.d[0];
    way[1] = girlWay2Pos.d[1];
    RequestStageChangeDirect(girlGObj, 0x13, (int *)way, 0xB4);

    brainUnlockGirl();
}
