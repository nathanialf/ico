#include "common.h"
#include "st04d.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "script.h"
#include "StageAnimation.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD4]; /* 0x00 */
    ActMail *mail;    /* 0xD4 */
} Act;

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    int act;           /* 0x164 */
} PObjGObj;

extern void *D_00639EA4;
extern void *D_00639EA8;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */
typedef union {
    float f[4];
    long long d[2];
} ConstVec;

/* prototypes: their order is the inline tail's emission order */
inline void actSt04dDoor1Event(int x)
{
    volatile int local = x;
}

static ActMail door1_down_mes[2] = {{430}, {429}};

static ActMail door1_up_mes[2] = {{430}, {429}};

void actSt04dDoor1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 400.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(0xFF, 0, 0);
        _ACTWait(0x3C);
        door1_down_mes[0].func = actSt04dDoor1DownChk;
        self->mail = door1_down_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xFE, 0, 0);
        door1_up_mes[0].func = actSt04dDoor1UpChk;
        self->mail = door1_up_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

inline void actSt04dDoor1UpEffect(volatile int a0);

static const ConstVec door1SoundPos = {{-498.0f, -1418.0f, -5663.0f, 0.0f}};

static const ConstVec door1UpEffectPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}};

static const ConstVec door1DownEffectPos = {{-505.0f, -1447.0f, -5671.0f, 1.0f}};

static ActMail door1_up_chk_mes[2] = {{430}, {429}};

void actSt04dDoor1UpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt04dDoor1UpEffect, 0x15);

    stage_SetAnimation(0xFE, 1, 0);

    buf[0] = door1SoundPos.d[0];
    buf[1] = door1SoundPos.d[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0xFE) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door1_up_chk_mes[0].func = actSt04dDoor1DownChk;
    sub->mail = door1_up_chk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

inline void actSt04dDoor1UpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door1UpEffectPos.d[0];
    long long v0b = door1DownEffectPos.d[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door1UpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = door1DownEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

inline void actSt04dDoor1DownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door1DownEffectPos.d[0];
    long long v0b = door1UpEffectPos.d[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door1DownEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = door1UpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

static ActMail door1_down_chk_mes[2] = {{430}, {429}};

void actSt04dDoor1DownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt04dDoor1DownEffect, 0x15);

    stage_SetAnimation(0xFF, 1, 0);

    buf[0] = door1SoundPos.d[0];
    buf[1] = door1SoundPos.d[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0xFF) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door1_down_chk_mes[0].func = actSt04dDoor1UpChk;
    sub->mail = door1_down_chk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

inline void actSt04dDoor2Event(int x)
{
    volatile int local = x;
}

static ActMail door2_down_mes[2] = {{430}, {429}};

static ActMail door2_up_mes[2] = {{430}, {429}};

void actSt04dDoor2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 400.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(0x101, 0, 0);
        _ACTWait(0x3C);
        door2_down_mes[0].func = actSt04dDoor2DownChk;
        self->mail = door2_down_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x100, 0, 0);
        door2_up_mes[0].func = actSt04dDoor2UpChk;
        self->mail = door2_up_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

inline void actSt04dDoor2UpEffect(volatile int a0);

static const ConstVec door2SoundPos = {{702.0f, -1886.0f, -5680.0f, 0.0f}};

static const ConstVec door2UpEffectPos = {{704.0f, -1700.0f, -5679.0f, 1.0f}};

static const ConstVec door2DownEffectPos = {{704.0f, -1955.0f, -5679.0f, 1.0f}};

static ActMail door2_up_chk_mes[2] = {{430}, {429}};

void actSt04dDoor2UpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x2000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt04dDoor2UpEffect, 0x15);

    stage_SetAnimation(0x100, 1, 0);

    buf[0] = door2SoundPos.d[0];
    buf[1] = door2SoundPos.d[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x100) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2_up_chk_mes[0].func = actSt04dDoor2DownChk;
    sub->mail = door2_up_chk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

inline void actSt04dDoor2UpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door2UpEffectPos.d[0];
    long long v0b = door2DownEffectPos.d[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door2UpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = door2DownEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

inline void actSt04dDoor2DownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door2DownEffectPos.d[0];
    long long v0b = door2UpEffectPos.d[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door2DownEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = door2UpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

static ActMail door2_down_chk_mes[2] = {{430}, {429}};

void actSt04dDoor2DownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x2000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt04dDoor2DownEffect, 0x15);

    stage_SetAnimation(0x101, 1, 0);

    buf[0] = door2SoundPos.d[0];
    buf[1] = door2SoundPos.d[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x101) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2_down_chk_mes[0].func = actSt04dDoor2UpChk;
    sub->mail = door2_down_chk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
