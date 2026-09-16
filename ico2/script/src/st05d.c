#include "common.h"

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
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void SleepHint(int a0);
extern int scpTriggerBall(int a0, void *a1, float radius);
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern int actCreateSubThread(void *entry, int prio);
extern void ReviveAllCarryableItemsWithNonSleepFrame(int a0);
extern int scpSearchGobj(int a0);
extern int scpGetRotObjectCurrentRot(int a0);
extern void *GetCurrentQuaternion(void);
extern void GetRootQuaternion(void *dst, int gobj);
extern void RotQuaternionY(void *q, int ang);
extern void SetRootQuaternion(int obj, void *q);
extern void UpdateRootMatrix(int obj);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern void *D_00639EA4;
extern char *D_00639EA8;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */
typedef union {
    float f[4];
    long long d[2];
} ConstVec;

static const ConstVec door2UpChkPos = {{-702.0f, -1886.0f, -5680.0f, 0.0f}};

static const ConstVec door2UpEffectPos = {{-704.0f, -1700.0f, -5679.0f, 1.0f}};

static const ConstVec door2UpEffect2Pos = {{-704.0f, -1955.0f, -5679.0f, 1.0f}};

void actSt05dDoor2UpEffect(volatile int a0);
void actSt05dDoor2DownEffect(volatile int a0);
void actSt05dEneChk(volatile int a0);
void actSt05dCrestHintChk(volatile int a0);

static ActMail door2Downchk_mes[2] = {{430}, {429}};

static ActMail door2Upchk_mes[2] = {{430}, {429}};

static ActMail door2UpChk_mes[2] = {{430}, {429}};

static ActMail door2DownChk_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail crestHint_mes[2] = {{430}, {429}};

void actSt05dDoor2DownChk(volatile int a0);
void actSt05dDoor2UpChk(volatile int a0);

void actSt05dDoor2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 400.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(0x15D, 0, 0);
        _ACTWait(0x3C);
        door2Downchk_mes[0].func = actSt05dDoor2DownChk;
        self->mail = door2Downchk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x15C, 0, 0);
        door2Upchk_mes[0].func = actSt05dDoor2UpChk;
        self->mail = door2Upchk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt05dDoor2UpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x2000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt05dDoor2UpEffect, 0x15);

    ReviveAllCarryableItemsWithNonSleepFrame(0x3C);

    stage_SetAnimation(0x15C, 1, 0);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x15C) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2UpChk_mes[0].func = actSt05dDoor2DownChk;
    sub->mail = door2UpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt05dDoor2DownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x2000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt05dDoor2DownEffect, 0x15);

    ReviveAllCarryableItemsWithNonSleepFrame(0x3C);

    stage_SetAnimation(0x15D, 1, 0);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x15D) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door2DownChk_mes[0].func = actSt05dDoor2UpChk;
    sub->mail = door2DownChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt05dEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    int g;
    int rot;

    _ACTWait(1);

    g = scpSearchGobj(0x5B2);
    rot = scpGetRotObjectCurrentRot(0x614);

    GetRootQuaternion(GetCurrentQuaternion(), g);
    RotQuaternionY(GetCurrentQuaternion(), rot);
    SetRootQuaternion(g, GetCurrentQuaternion());
    UpdateRootMatrix(g);

    if (gflagChk(0xAB) == 0) {
        ene_mes[0].func = actSt05dEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt05dEnemy1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    Generator_Mask(scpSearchGobj(0x5C5));
    Generator_Mask(scpSearchGobj(0x5C6));
    while (gflagChk(0xAC) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_Call(scpSearchGobj(0x5C5));
    Generator_Call(scpSearchGobj(0x5C6));
}

void actSt05dEnemy2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0xAC) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void actSt05dCrestHint(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0xAD) == 0) {
        SleepHint(0x19);
        crestHint_mes[0].func = actSt05dCrestHintChk;
        self->mail = crestHint_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt05dDoor2Event(int x)
{
    volatile int local = x;
}

extern void _ACTWait(int a0);
extern void scpEffectStart(int *buf, int a1);

void actSt05dDoor2UpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door2UpEffectPos.d[0];
    long long v0b = door2UpEffect2Pos.d[0];
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
            b2[1] = door2UpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt05dDoor2DownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door2UpEffect2Pos.d[0];
    long long v0b = door2UpEffectPos.d[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door2UpEffect2Pos.d[1];
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

void actSt05dEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (D_00639EA8 == 0 || gflagChk(0xAA) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(0xAB);
    gflagOn(0xAC);
}

void actSt05dCrestHintChk(volatile int a0)
{
    while (gflagChk(0xF3) == 0 || gflagChk(0xF4) == 0 || gflagChk(0xF5) == 0 ||
           gflagChk(0xE8) != 0) {
        _ACTWait(1);
    }
    gflagOn(0xAD);
    WakeupHint(0x19);
}
