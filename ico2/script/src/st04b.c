#include "common.h"

typedef struct ActMail {
    int mail;          /* 0x00 */
    void (*func)(int); /* 0x04 */
    int unk08;         /* 0x08 */
    int unk0C;         /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD4]; /* 0x00 */
    ActMail *mail;    /* 0xD4 */
} Act;

extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F87D0[];
extern ActMail D_004F87B0[];
extern void actSt04bEne1Chk(int a0);
extern void actSt04bSekizoChk(int a0);
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern void scpTorchLightOn(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern int D_00639EA8;
extern int _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
extern void RequestStageChangeDirect(int a0, int a1, int *buf, int a3);
extern void brainUnlockGirl(void);
extern const long long D_006229D0[];
extern const long long D_006229E0[];

void actSt04bEnd(void)
{
    if (D_00639EA8 != 0) {
        if (gflagChk(0x8A) != 0) {
            if (gflagChk(0x9D) == 0) {
                gflagOn(0x187);
            }
        }
    }
}

extern int D_00639EA4;
extern int D_00639EAC;
extern int D_0063AA08;
extern void lt_switch_layout(int a0);
extern int stage_CheckAnimationFinish(int a0);
extern int sekizo4b;
extern int sekizo_4b;
extern unsigned char sekizo_4b_vol;
extern int scpTriggerBall(int a0, int gobj, float r);
extern void brainLockGirl(void);
extern void scpKillEnemyOne(int a0);
extern void scpMaskGeneratorAll(void);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern void ReviveAllCarryableItemsWithNonSleepFrame(int a0);
extern int iosPadActRequest(int port, int id);
extern int *iosPadActVolumeSet(int key, unsigned int val);
extern void iosPadActStop(int key);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void soundSeDefStop(int handle);
extern void scpPlayStart(int a0);
extern void scpPlayMot(int a0, int mot);
extern void scpPlayPosSet(int a0, float x, float y, float z);
extern void *test_CURRENTROOT(int a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void scpPlayMotDir(int a0, void *dir);
extern void scpSekizouCheckPoint(void);
extern void scpPlayWaitMotEnd(int a0);
extern void scpPlayEnd(int a0);
extern int actCreateSubThread(void *entry, int prio);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern void actSt04bGirlWay(volatile int a0);

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

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    brainLockGirl();

    scpKillEnemyOne(0xEAD);
    scpMaskGeneratorAll();

    scpAdpcmPlayRequestFunc(0x12, &sekizo4b, 1, 1, 1);
    while (sekizo4b == 0) {
        _ACTWait(1);
    }

    gflagOn(0x186);

    stage_SetAnimation(0xBF, 1, 0);

    ReviveAllCarryableItemsWithNonSleepFrame(250);

    key = iosPadActRequest(D_00639EAC, 9);
    sekizo_4b_vol = 128;
    iosPadActVolumeSet(sekizo_4b = key, 128);

    se = soundSeDefPlay(0x4C1, 0, 0, 1);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);

    scpPlayPosSet(D_00639EA8, -10325.0f, -2150.0f, 0.0f);
    scpPlayPosSet(D_00639EA4, -10325.0f, -2150.0f, -100.0f);
    _ACTWait(1);
    sceVu0SubVector(v, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, v);
    D_0063AA08 = 1;
    sceVu0SubVector(v, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, v);

    scpSekizouCheckPoint();

    scpPlayMot(D_00639EA8, 0x285);
    scpPlayWaitMotEnd(D_00639EA8);

    gflagOn(0x9F);

    soundSeDefStop(se);

    while (stage_CheckAnimationFrame(0xBF, 0x97, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_4b);

    scpPlayMot(D_00639EA8, 0x214);
    scpPlayEnd(D_00639EA8);

    actCreateSubThread(actSt04bGirlWay, 21);

    _ACTWait(30);
    scpPlayMot(D_00639EA4, 252);
    scpPlayWaitMotEnd(D_00639EA4);

    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    ScpCallCameraSetTarget(10793.0f, 2122.0f, 0.0f);

    while (stage_CheckAnimationFinish(0xBF) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

extern int D_00639EA4;
extern int D_0063AA08;
extern int scpTriggerFloorAttr(int a0, int attr);
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyOne(int a0);
extern void scpWakeupEnemyOne(int a0);
extern void gflagOff(int a0);
extern void SetCameraFlag_LwsCutBack(void);
extern int stage_CheckAnimationFinish(int a0);

void actSt04bEne1Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(0x8A) == 0 || (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0 &&
                                   scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0)) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    scpSleepEnemyOne(0xEAD);

    gflagOff(0x187);

    _ACTWait(60);

    gflagOn(0x9D);
    gflagOn(0x9E);

    stage_SetAnimation(0xB8, 1, 0);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFinish(0xB8) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;

    scpWakeupEnemyOne(0xEAD);
}

void actSt04bCrest01XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xAE) == 0) {
        stage_SetAnimation(0xB9, 0, 0);
        stage_SetAnimation(0xBA, 0, 0);
    } else {
        stage_SetAnimation(0xB9, 0, -1);
        stage_SetAnimation(0xBA, 0, -1);
        scpTorchLightOn(0x420);
        scpTorchLightOn(0x421);
    }
}

void actSt04bDoorXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    stage_SetAnimation(0xF9, 0, 0);
}

void actSt04bMonyoDoorXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xAE) == 0) {
        stage_SetAnimation(0xFA, 0, 0);
    } else {
        stage_SetAnimation(0xFA, 0, -1);
    }
}

void actSt04bSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x9F) == 0) {
        stage_SetAnimation(0xBF, 0, 0);
        D_004F87B0[0].func = actSt04bSekizoChk;
        self->mail = D_004F87B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xBF, 0, -1);
        if (gflagChk(0xAE) == 0) {
            ScpCallCameraSetTarget(10793.0f, 2122.0f, 0.0f);
        }
    }
}

void actSt04bEne1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x9D) == 0) {
        D_004F87D0[0].func = actSt04bEne1Chk;
        self->mail = D_004F87D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt04bEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);
    while (gflagChk(0x9E) == 0) {
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
    while (gflagChk(0x9E) == 0) {
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

    if (gflagChk(0x8A) == 0) {
        stage_SetAnimation(0x12B, -1, -2);
    } else {
        stage_SetAnimation(0x129, -1, -2);
    }
}

void actSt04bSolarXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8A) == 0) {
        stage_SetAnimation(0x12D, -1, -2);
        stage_SetAnimation(0x131, -1, -2);
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

    buf[0] = D_006229D0[0];
    buf[1] = D_006229D0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);

    way[0] = D_006229E0[0];
    way[1] = D_006229E0[1];
    RequestStageChangeDirect(D_00639EA8, 0x13, (int *)way, 0xB4);

    brainUnlockGirl();
}
