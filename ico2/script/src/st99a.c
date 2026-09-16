#include "common.h"
#include "st99a.h"
#include "act.h"
#include "commonact.h"
#include "script.h"
#include "StageAnimation.h"

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

static ActMail explode_mes[2] = {{430}, {429}};

static ActMail splash1_mes[2] = {{430}, {429}};

static ActMail splash2_mes[2] = {{430}, {429}};

static ActMail wave_mes[2] = {{430}, {429}};

static ActMail st27aWave_mes[2] = {{430}, {429}};

static ActMail spider_mes[2] = {{430}, {429}};

static ActMail st17aTest_mes[2] = {{430}, {429}};

void actExplode(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    explode_mes[0].func = actExplodeChk;
    self->mail = explode_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSplash1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    splash1_mes[0].func = actSplash1Chk;
    self->mail = splash1_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSplash2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    splash2_mes[0].func = actSplash2Chk;
    self->mail = splash2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actWave(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    wave_mes[0].func = actWaveChk;
    self->mail = wave_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSpider(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    stage_SetLoopFlag(0xA0, 1);
    stage_SetAnimation(0xA0, 1, 0);

    spider_mes[0].func = actSpiderChk;
    self->mail = spider_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actDevilLightning(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(0xDB9, 0, 0x22A, 0);
}

void actQueenLightning(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(0xDB8, 0, 0x22B, 0);
}

void actSt17aTest(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    stage_SetAnimation(0x84, 0, 0);

    st17aTest_mes[0].func = actSt17aTestChk;
    self->mail = st17aTest_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt27aWave(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    st27aWave_mes[0].func = actSt27aWaveChk;
    self->mail = st27aWave_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actExplodeChk(volatile int a0)
{
    *(int *)(*(int *)(scpSearchGobj(0xBC6) + 0x15C) + 0x4E8) = 1;
    *(int *)(*(int *)(scpSearchGobj(0xBC6) + 0x15C) + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
    stage_SetAnimation(0x1FF, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xBC6, 0x1FF);
    while (stage_CheckAnimationFinish(0x1FF) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSplash1Chk(volatile int a0)
{
    *(int *)(*(int *)(scpSearchGobj(0xBC7) + 0x15C) + 0x4E8) = 1;
    *(int *)(*(int *)(scpSearchGobj(0xBC7) + 0x15C) + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
    stage_SetAnimation(0x1F2, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xBC7, 0x1F2);
    while (stage_CheckAnimationFinish(0x1F2) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSplash2Chk(volatile int a0)
{
    *(int *)(*(int *)(scpSearchGobj(0xBC8) + 0x15C) + 0x4E8) = 1;
    *(int *)(*(int *)(scpSearchGobj(0xBC8) + 0x15C) + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
    stage_SetAnimation(0x1F3, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xBC8, 0x1F3);
    while (stage_CheckAnimationFinish(0x1F3) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actWaveChk(volatile int a0)
{
    actCreateSubThread(actWave1, 0x15);
}

void actWave1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    while (1) {
        stage_SetAnimation(0x207, 1, 0);
        _ACTWait(0xB3);
        stage_SetAnimation(0x208, 1, 0);
        _ACTWait(0xB3);
        stage_SetAnimation(0x209, 1, 0);
        _ACTWait(0xB3);
        stage_SetAnimation(0x20A, 1, 0);
        _ACTWait(0xB3);
    }
}

void actSt27aWaveChk(volatile int a0)
{
    actCreateSubThread(actSt27aWave1, 0x15);
}

void actSt27aWave1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    while (1) {
        stage_SetAnimation(0xC2, 1, 0);
        _ACTWait(0xC8);
        stage_SetAnimation(0xC3, 1, 0);
        _ACTWait(0xC8);
        stage_SetAnimation(0xC4, 1, 0);
        _ACTWait(0xC8);
        stage_SetAnimation(0xC5, 1, 0);
        _ACTWait(0xC8);
    }
}

extern int D_00639EA4;

void actSpiderChk(volatile int a0)
{
    while (1) {
        while ((*(int *)(*(int *)(D_00639EA4 + 0x164) + 0x2E4) & 0x400) == 0) {
            _ACTWait(1);
        }
        scpBornSpider(2, 0.0f, -500.0f, 0.0f, 500.0f);
        _ACTWait(1);
    }
}

typedef struct PadState {
    int unk00;        /* 0x00 */
    int flags;        /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} PadState;

extern PadState D_0028F8F0[];

void actSt17aTestChk(volatile int a0)
{
    while (1) {
        while ((D_0028F8F0[1].flags & 0x20) == 0) {
            _ACTWait(1);
        }
        stage_SetAnimation(0x54, 1, 0);
        _ACTWait(1);
    }
}
