#include "common.h"

extern long long D_00622A40[];
extern long long D_00622A50[];
extern long long D_00622A70[];
extern long long D_00622A80[];
extern void _ACTWait(int a0);
extern void scpEffectStart(int *buf, int a1);

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

extern Act *actInitialize(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int scpTriggerBall(int a0, void *a1, float radius);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern int actCreateSubThread(void *entry, int prio);
extern void *D_00639EA4;
extern void *D_00639EA8;

/* prototypes: their order is the inline tail's emission order */
inline void actSt04dDoor1Event(int x)
{
    volatile int local = x;
}

extern void actSt04dDoor1DownChk(volatile int a0);
extern void actSt04dDoor1UpChk(volatile int a0);
extern ActMail D_004F8870[];
extern ActMail D_004F8890[];

void actSt04dDoor1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 400.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(0xFF, 0, 0);
        _ACTWait(0x3C);
        D_004F8870[0].func = actSt04dDoor1DownChk;
        self->mail = D_004F8870;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xFE, 0, 0);
        D_004F8890[0].func = actSt04dDoor1UpChk;
        self->mail = D_004F8890;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

inline void actSt04dDoor1UpEffect(volatile int a0);
extern long long D_00622A30[];
extern ActMail D_004F88B0[];

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

    buf[0] = D_00622A30[0];
    buf[1] = D_00622A30[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0xFE) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004F88B0[0].func = actSt04dDoor1DownChk;
    sub->mail = D_004F88B0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

inline void actSt04dDoor1UpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_00622A40[0];
    long long v0b = D_00622A50[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622A40[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622A50[1];
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
    long long v0a = D_00622A50[0];
    long long v0b = D_00622A40[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622A50[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622A40[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

extern ActMail D_004F88D0[];

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

    buf[0] = D_00622A30[0];
    buf[1] = D_00622A30[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0xFF) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004F88D0[0].func = actSt04dDoor1UpChk;
    sub->mail = D_004F88D0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

inline void actSt04dDoor2Event(int x)
{
    volatile int local = x;
}

extern void actSt04dDoor2DownChk(volatile int a0);
extern void actSt04dDoor2UpChk(volatile int a0);
extern ActMail D_004F88F0[];
extern ActMail D_004F8910[];

void actSt04dDoor2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 400.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(0x101, 0, 0);
        _ACTWait(0x3C);
        D_004F88F0[0].func = actSt04dDoor2DownChk;
        self->mail = D_004F88F0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x100, 0, 0);
        D_004F8910[0].func = actSt04dDoor2UpChk;
        self->mail = D_004F8910;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

inline void actSt04dDoor2UpEffect(volatile int a0);
extern long long D_00622A60[];

/* TU-owned mail record: role-named file static per the 2026-09-07 ruling,
   same shape as st17a's door_mes / st18a's switch_l_mes. */
static ActMail door2_up_mes[2] = {{0x1AE}, {0x1AD}};

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

    buf[0] = D_00622A60[0];
    buf[1] = D_00622A60[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x100) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2_up_mes[0].func = actSt04dDoor2DownChk;
    sub->mail = door2_up_mes;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

inline void actSt04dDoor2UpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_00622A70[0];
    long long v0b = D_00622A80[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622A70[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622A80[1];
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
    long long v0a = D_00622A80[0];
    long long v0b = D_00622A70[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622A80[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622A70[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

extern ActMail D_004F8950[];

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

    buf[0] = D_00622A60[0];
    buf[1] = D_00622A60[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x101) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004F8950[0].func = actSt04dDoor2UpChk;
    sub->mail = D_004F8950;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
