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
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F9720[];
extern void actSt05bSekizoChk(int a0);
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void scpTorchLightOn(int id);

void actSt05bCrest01XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    if (gflagChk(0xF3) == 0) {
        stage_SetAnimation(0xBB, 0, 0);
        stage_SetAnimation(0xBD, 0, 0);
    } else {
        stage_SetAnimation(0xBB, 0, -1);
        stage_SetAnimation(0xBD, 0, -1);
        scpTorchLightOn(0x53F);
        scpTorchLightOn(0x540);
    }
    if (gflagChk(0xF4) == 0) {
        stage_SetAnimation(0xBC, 0, 0);
    } else {
        stage_SetAnimation(0xBC, 0, -1);
        scpTorchLightOn(0x541);
        scpTorchLightOn(0x542);
    }
    if (gflagChk(0xFB) == 0) {
        stage_SetAnimation(0xBE, 0, 0);
    } else {
        stage_SetAnimation(0xBE, 0, -1);
    }
}

extern int sekizo5b;
extern int sekizo_5b;
extern unsigned char sekizo_5b_vol;
extern int D_00639EA4;
extern int D_00639EA8;
extern int D_00639EAC;
extern int D_0063AA08;
extern int scpTriggerBall(int a0, int gobj, float r);
extern void brainLockGirl(void);
extern void scpKillEnemyAll(void);
extern void scpMaskGeneratorAll(void);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern void gflagOn(int a0);
extern void ReviveAllCarryableItemsWithNonSleepFrame(int frames);
extern int iosPadActRequest(int port, int id);
extern int *iosPadActVolumeSet(int key, unsigned int val);
extern void iosPadActStop(int key);
extern int soundSeDefPlay(int se, int a1, void *pos, int a3);
extern void soundSeDefStop(int handle);
extern void scpPlayStart(int gobj);
extern void scpPlayMot(int gobj, int mot);
extern void scpPlayWaitMotEnd(int gobj);
extern void scpPlayEnd(int gobj);
extern void scpPlayPosSet(int gobj, float x, float y, float z);
extern void scpPlayMotDir(int gobj, float *dir);
extern void scpSekizouCheckPoint(void);
extern void *test_CURRENTROOT(int gobj);
extern void sceVu0SubVector(float *dst, void *a, void *b);
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern int actCreateSubThread(void *entry, int prio);
extern void lt_switch_layout(int a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern void actSt05bGirlWay(volatile int a0);

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
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    brainLockGirl();
    scpKillEnemyAll();
    scpMaskGeneratorAll();
    scpAdpcmPlayRequestFunc(0x12, &sekizo5b, 1, 1, 1);
    while (sekizo5b == 0) {
        _ACTWait(1);
    }
    gflagOn(0x186);
    stage_SetAnimation(0xC0, 1, 0);
    ReviveAllCarryableItemsWithNonSleepFrame(0xFA);
    sekizo_5b = iosPadActRequest(D_00639EAC, 9);
    sekizo_5b_vol = 0x80;
    iosPadActVolumeSet(sekizo_5b, 0x80);
    h = soundSeDefPlay(0x4C1, 0, 0, 1);
    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);
    scpPlayPosSet(D_00639EA8, 10350.0f, -2150.0f, 0.0f);
    scpPlayPosSet(D_00639EA4, 10350.0f, -2150.0f, -100.0f);
    _ACTWait(1);
    sceVu0SubVector(d, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, d);
    D_0063AA08 = 1;
    sceVu0SubVector(d, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, d);
    scpSekizouCheckPoint();
    scpPlayMot(D_00639EA8, 0x285);
    scpPlayWaitMotEnd(D_00639EA8);
    gflagOn(0xA0);
    soundSeDefStop(h);
    while (stage_CheckAnimationFrame(0xC0, 0x97, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_5b);
    scpPlayMot(D_00639EA8, 0x214);
    scpPlayEnd(D_00639EA8);
    actCreateSubThread(actSt05bGirlWay, 0x15);
    _ACTWait(0x1E);
    scpPlayMot(D_00639EA4, 0xFC);
    scpPlayWaitMotEnd(D_00639EA4);
    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    ScpCallCameraSetTarget(-10793.0f, 2122.0f, 0.0f);
    while (stage_CheckAnimationFinish(0xC0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

void actSt05bDoorXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xF3) != 0 && gflagChk(0x8B) == 0) {
        stage_SetAnimation(0x159, 0, -1);
    } else {
        stage_SetAnimation(0x159, 0, 0);
    }
}

void actSt05bMonyoDoorXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xEA) == 0) {
        stage_SetAnimation(0xFB, 0, 0);
    } else {
        stage_SetAnimation(0xFB, 0, -1);
    }
}

void actSt05bSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xA0) == 0) {
        stage_SetAnimation(0xC0, 0, 0);
        D_004F9720[0].func = actSt05bSekizoChk;
        self->mail = D_004F9720;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xC0, 0, -1);
        if (gflagChk(0xF3) == 0) {
            ScpCallCameraSetTarget(-10793.0f, 2122.0f, 0.0f);
        }
    }
}

void actSt05bBallXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8B) == 0) {
        stage_SetAnimation(0x12C, -1, -2);
    } else {
        stage_SetAnimation(0x12A, -1, -2);
    }
}

void actSt05bSolarXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8B) == 0) {
        stage_SetAnimation(0x12F, -1, -2);
        stage_SetAnimation(0x132, -1, -2);
    }
}

void actSt05bSekizoEvent(int x)
{
    volatile int local = x;
}

extern const long long D_00622AD0[];
extern const long long D_00622AE0[];
extern int D_00639EA8;
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
extern void RequestStageChangeDirect(int a0, int a1, int *buf, int a3);
extern void brainUnlockGirl(void);

INCLUDE_ASM("asm/nonmatchings/src/st05b", actSt05bGirlWay);
