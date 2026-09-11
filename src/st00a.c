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

typedef struct PObjGObj {
    /*0x00*/ char pad00[0x164];
    /*0x164*/ Act *act;
    /*0x168*/ char pad168[0x4];
    /*0x16C*/ int f16C;
} PObjGObj;

extern Act *actInitialize(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void SetWayGroupActive(int a0, int a1);
extern void FinishHint(int a0);

void actSt00aInit(void)
{
    if (gflagChk(0x29) == 0) {
        stage_SetAnimation(0x5A, 0, 0);
        stage_SetAnimation(0x57, 0, 0);
        SetWayGroupActive(3, 0);
        SetWayGroupActive(0xD, 1);
    } else {
        stage_SetAnimation(0x58, 0, -1);
        stage_SetAnimation(0x57, 0, -1);
        FinishHint(1);
        SetWayGroupActive(3, 1);
        SetWayGroupActive(0xD, 0);
    }
    if (gflagChk(0x4F) == 0) {
        stage_SetAnimation(0x60, 0, 1);
    } else {
        stage_SetAnimation(0x60, 0, 2);
    }
}

extern char *D_00639EA8;

void actSt00aEnd(void)
{
    if (D_00639EA8 != 0) {
        if (gflagChk(0x2A) == 0) {
            gflagOn(0x187);
        }
    }
}

extern int D_0028F4C0[];
extern int D_0063AA08;
extern void lt_switch_layout(int a0);
extern void gflagOn(int a0);
extern void gflagOff(int a0);
extern void scpSleepEnemyOne(int a0);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyOne(int a0);
extern void scpWakeupEnemyAll(void);

void actSt00aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (gflagChk(0x2A) == 0 || gflagChk(0x26) != 0) {
        _ACTWait(1);
    }
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    gflagOn(0x27);
    scpSleepEnemyOne(0xEAD);
    scpSleepEnemyAll();
    gflagOff(0x187);
    _ACTWait(0x3C);
    gflagOn(0x28);
    stage_SetAnimation(0xB1, 1, 0);
    _ACTWait(0x96);
    while (stage_CheckAnimationFinish(0xB1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(0x36);
    _ACTWait(0x78);
    D_0063AA08 = 0;
    scpWakeupEnemyOne(0xEAD);
    scpWakeupEnemyAll();
    _ACTWait((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    gflagOff(0x27);
}

extern PObjGObj *scpSearchGobj(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern int D_0063BE70;
extern unsigned int D_0063BE74;
extern int D_0063C4F8;
extern int D_0028F8F4[];
extern void fightSoundProcessRequestPause(void);
extern int fightSoundPlayChk(void);
extern void fightSoundProcessRequestStart(void);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern int scpAdpcmPlayRequestNum(void);
extern int scpAdpcmFadeCloseFunc(int *h, short fade);
extern int ReviveAllCarryableItemsWithNonSleepFrame(int nonSleepFrame);
extern void scpFadeOut(float f, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern void scpFadeIn(float f);
extern void iosThreadSetPri(int th, int pri);
extern void iosPadActStop(int a0);
void actSt00aStairChkSub(volatile int a0);

void actSt00aStairChk(volatile int a0)
{
    int th;
    int fade;

    while (scpTriggerBall(a0, (int)scpSearchGobj(0x114), 90.0f) != 0 || gflagChk(0x27) != 0) {
        _ACTWait(1);
    }
    gflagOn(0x26);
    FinishHint(1);
    SetWayGroupActive(3, 1);
    SetWayGroupActive(0xD, 0);
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    gflagOn(0x29);
    scpSleepEnemyAll();
    _ACTWait(0x3C);
    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(0x15, &D_0063BE70, 1, 1, 1);
    while (D_0063BE70 == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(0x57, 1, 0);
    ReviveAllCarryableItemsWithNonSleepFrame(0x104);
    D_0063BE74 = 0xFFFFFFFF;
    th = actCreateSubThread(actSt00aStairChkSub, 0x15);
    D_0063C4F8 = 0;
    while (D_0063C4F8 == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    fade = D_0063C4F8 ^ 1;
    if (fade) {
        scpAdpcmFadeCloseFunc(&D_0063BE70, 0x100);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    iosThreadSetPri(th + 0x24, 0x22);
    if (fade) {
        stage_SetAnimation(0x5A, 1, -1);
        stage_SetAnimation(0x57, 0, -1);
        scpFadeIn(3.0f);
    }
    iosPadActStop(D_0063BE74);
    while (stage_CheckAnimationFinish(0x5A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(0x111)->f16C = 0;
    scpSearchGobj(0x110)->f16C = 1;
    lt_switch_layout(0x36);
    _ACTWait(0x78);
    ReviveAllCarryableItemsWithNonSleepFrame(0x3C);
    stage_SetAnimation(0x58, 0, -1);
    stage_SetAnimation(0x5A, -1, -2);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    gflagOff(0x26);
    fightSoundProcessRequestStart();
}

extern int D_00639EA4;
extern ActMail D_004F7F10[];
extern ActMail D_004F7EB0[];
extern ActMail D_004F7ED0[];
extern int scpTriggerBall(int a0, int a1, float f);
void actSt00aDoor2DownChk(int a0);
void actSt00aDoor2UpChk(int a0);

void actSt00aDoor2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, (int)D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(0x5E, 0, 0);
        _ACTWait(0x3C);
        D_004F7EB0[0].func = actSt00aDoor2DownChk;
        self->mail = D_004F7EB0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x5D, 0, 0);
        D_004F7ED0[0].func = actSt00aDoor2UpChk;
        self->mail = D_004F7ED0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern long long D_006226A0[];
extern ActMail D_004F7EF0[];
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
extern int actCreateSubThread(void *func, int a1);
extern void scpWakeupItemWithBoundary(float x, float y, float z, float r);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void soundSeDefStop(int h);
extern int stage_CheckAnimationFinish(int a0);
void actSt00aDoor2UpEffect(volatile int a0);

void actSt00aDoor2UpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt00aDoor2UpEffect, 0x15);

    stage_SetAnimation(0x5D, 1, 0);

    scpWakeupItemWithBoundary(-6.0f, -221.0f, 1504.0f, 100.0f);

    _ACTWait(1);

    buf[0] = D_006226A0[0];
    buf[1] = D_006226A0[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    h = soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x3C);
    soundSeDefStop(h);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x5D) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004F7EF0[0].func = actSt00aDoor2DownChk;
    sub->mail = D_004F7EF0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt00aDoor2DownEffect(volatile int a0);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor2DownChk);

extern ActMail D_004F7F30[];
extern ActMail D_004F7F50[];
void actSt00aDoor1DownChk(int a0);
void actSt00aDoor1UpChk(int a0);

void actSt00aDoor1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, (int)D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(0x5C, 0, 0);
        _ACTWait(0x3C);
        D_004F7F30[0].func = actSt00aDoor1DownChk;
        self->mail = D_004F7F30;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x5B, 0, 0);
        D_004F7F50[0].func = actSt00aDoor1UpChk;
        self->mail = D_004F7F50;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern long long D_006226D0[];
extern ActMail D_004F7F70[];
void actSt00aDoor1UpEffect(volatile int a0);

INCLUDE_ASM("asm/nonmatchings/src/st00a", actSt00aDoor1UpChk);

extern ActMail D_004F7F90[];
void actSt00aDoor1DownEffect(volatile int a0);

void actSt00aDoor1DownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x4000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt00aDoor1DownEffect, 0x15);

    scpWakeupItemWithBoundary(-8.0f, -73.0f, 64.0f, 100.0f);

    stage_SetAnimation(0x5C, 1, 0);

    buf[0] = D_006226D0[0];
    buf[1] = D_006226D0[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    h = soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefStop(h);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x5C) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004F7F90[0].func = actSt00aDoor1UpChk;
    sub->mail = D_004F7F90;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern ActMail D_004F7E70[];
void actSt00aEneChk(int a0);

void actSt00aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x2A) == 0) {
        D_004F7E70[0].func = actSt00aEneChk;
        self->mail = D_004F7E70;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt00aEnemy1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x28) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x32);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x1E);
    Generator_Call(a0);
    _ACTWait(0x1E);
    Generator_Call(a0);
}

void actSt00aEnemy2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x28) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xA0);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x1E);
    Generator_Call(a0);
}

extern PObjGObj *scpSearchGobj(int a0);
extern ActMail D_004F7E90[];
void actSt00aStairChk(int a0);

void actSt00aStair(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x29) == 0) {
        scpSearchGobj(0x110)->f16C = 0;
        D_004F7E90[0].func = actSt00aStairChk;
        self->mail = D_004F7E90;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x111)->f16C = 0;
    }
}

extern ActMail D_004F7E50[];
void actSt00aAtr2Chk(volatile int a0);

void actSt00aAtr2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x2A) == 0) {
        D_004F7E50[0].func = actSt00aAtr2Chk;
        self->mail = D_004F7E50;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern int scpTriggerFloorAttr(int a0, int a1);

void actSt00aAtr2Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(0x2A);
}

extern int D_00639EAC;
extern unsigned int D_0063BE74;
extern unsigned char D_0063BE78;
extern int D_0063C4F8;
extern int iosPadActRequest(int port, int id);
extern int *iosPadActVolumeSet(int key, unsigned int val);
extern int stage_CheckAnimationFinish(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);

void actSt00aStairChkSub(volatile int a0)
{
    _ACTWait(0x5A);
    iosPadActRequest(D_00639EAC, 0x11);
    while (stage_CheckAnimationFinish(0x57) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    stage_SetAnimation(0x59, 1, 0);
    stage_SetAnimation(0x5A, 1, 0);
    D_0063BE74 = iosPadActRequest(D_00639EAC, 9);
    D_0063BE78 = 0x80;
    iosPadActVolumeSet(D_0063BE74, 0x80);
    _ACTWait(0x1F4);
    D_0063C4F8 = 1;
    _ACTWait(0);
}

void actSt00aDoor2Event(int x)
{
    volatile int local = x;
}

extern long long D_006226B0[];
extern long long D_006226C0[];
extern void _ACTWait(int a0);
extern void scpEffectStart(int *buf, int a1);

void actSt00aDoor2UpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_006226B0[0];
    long long v0b = D_006226C0[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_006226B0[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_006226C0[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt00aDoor2DownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_006226C0[0];
    long long v0b = D_006226B0[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_006226C0[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_006226B0[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt00aDoor1Event(int x)
{
    volatile int local = x;
}

extern long long D_006226E0[];
extern long long D_006226F0[];

void actSt00aDoor1UpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_006226E0[0];
    long long v0b = D_006226F0[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_006226E0[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_006226F0[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt00aDoor1DownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_006226F0[0];
    long long v0b = D_006226E0[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_006226F0[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_006226E0[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}
