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
extern void actSt17aDoorUpChk(volatile int a0);
extern void actSt17aDoorDownChk(volatile int a0);
extern ActMail D_004FAF30[];
extern ActMail D_004FAF50[];
extern ActMail D_004FAF70[];
extern int *D_00639EA4;
extern void *D_00639EA8;
extern int scpTriggerBall(int a0, void *a1, float radius);
extern void stage_SetLoopFlag(int anim, int flag);

void actSt17aDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x20) == 0) {
        stage_SetLoopFlag(0x83, 1);
        stage_SetAnimation(0x83, 1, 0);

        D_004FAF30[0].func = actSt17aDoorUpChk;
        self->mail = D_004FAF30;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else if (scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 ||
               (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetLoopFlag(0x83, 1);
        stage_SetAnimation(0x83, 1, 0);

        _ACTWait(0x3C);
        D_004FAF50[0].func = actSt17aDoorDownChk;
        self->mail = D_004FAF50;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x81, 0, 0);
        D_004FAF70[0].func = actSt17aDoorUpChk;
        self->mail = D_004FAF70;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    int act;           /* 0x164 */
} PObjGObj;

extern long long D_00622F60[];
extern void actSt17aDoorDownEffect(volatile int a0);
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
extern int actCreateSubThread(void *entry, int prio);
extern void scpWakeupItemWithBoundary(float a0, float a1, float a2, float a3);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void soundSeDefStop(int h);
extern int stage_CheckAnimationFinish(int a0);
extern ActMail D_004FAF90[];
extern void actSt17aDoorUpEffect(volatile int a0);

void actSt17aDoorUpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x3000000) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0xF);

    actCreateSubThread(actSt17aDoorUpEffect, 0x15);

    scpWakeupItemWithBoundary(6573.0f, -2077.0f, 1089.0f, 100.0f);

    stage_SetAnimation(0x81, 1, 0);

    buf[0] = D_00622F60[0];
    buf[1] = D_00622F60[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);

    h = soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x3C);
    soundSeDefStop(h);

    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x81) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetLoopFlag(0x83, 1);
    stage_SetAnimation(0x83, 1, 0);

    D_004FAF90[0].func = actSt17aDoorDownChk;
    sub->mail = D_004FAF90;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

/* TU-owned .data record (VMA 0x004FAFB0..0x004FAFCF, ROM 0x3FAFB0): the mail
   table actSt17aDoorDownChk hands to the door actor. Role-named file static per
   the 2026-09-07 ruling, same shape as st13a's chain_ok_mes / st10r's
   fence_up2_mes. Needs the carve row [0x3FAFB0, .data, src/st17a]. */
static ActMail door_mes[2] = {{0x1AE}, {0x1AD}};

void actSt17aDoorDownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x3000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(0xF);

    actCreateSubThread(actSt17aDoorDownEffect, 0x15);

    scpWakeupItemWithBoundary(6573.0f, -2077.0f, 1089.0f, 100.0f);

    stage_SetLoopFlag(0x83, 0);

    stage_SetAnimation(0x82, 1, 0);

    buf[0] = D_00622F60[0];
    buf[1] = D_00622F60[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);

    h = soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x26);
    soundSeDefStop(h);

    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x82) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_mes[0].func = actSt17aDoorUpChk;
    sub->mail = door_mes;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern int scpTriggerFloorAttr(void *obj, int attr);
extern void SetCameraFlag_LwsCutBack(void);
extern void SetWayGroupActive(int a0, int a1);
extern int scpSearchGobj(int a0);
extern int D_0063AA08;
extern void gflagOn(int flag);
extern void iosPadActRequest(void *pad, int a1);
extern void *D_00639EAC;
extern int D_0028F4C0[];
extern long long D_00622FA0[];
extern void actSt17aHasiEffect(volatile int a0);
extern int ACTGame_FLAG_TETSUNAGI(void);
extern void scpPlayStart(void *o);
extern void scpPlayMot(void *o, int mot);
extern void scpPlayWaitMotEnd(void *o);
extern void scpPlayEnd(void *o);

void actSt17aHasiChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (1) {
        if ((*(int *)(*(int *)((char *)D_00639EA8 + 0x164) + 0x34) != 0x6F && D_00639EA8 != 0 &&
             scpTriggerFloorAttr(D_00639EA8, 0x1000000) != 0 &&
             scpTriggerFloorAttr(D_00639EA4, 0x2000000) != 0) ||
            (*(int *)(*(int *)((char *)D_00639EA8 + 0x164) + 0x34) != 0x6F && D_00639EA8 != 0 &&
             scpTriggerFloorAttr(D_00639EA8, 0x4000000) != 0 &&
             scpTriggerFloorAttr(D_00639EA4, 0x2000000) != 0)) {
            break;
        }
        _ACTWait(1);
    }

    gflagOn(0x21);

    iosPadActRequest(D_00639EAC, 0xF);
    SetWayGroupActive(3, 0);

    *(int *)(scpSearchGobj(0xF3) + 0x16C) = 0;
    *(int *)(scpSearchGobj(0xF4) + 0x16C) = 1;

    stage_SetAnimation(0x85, 1, 0);
    SetCameraFlag_LwsCutBack();

    actCreateSubThread(actSt17aHasiEffect, 0x15);

    if (ACTGame_FLAG_TETSUNAGI() == 0) {
        long long buf[2];

        scpPlayStart(D_00639EA8);

        stage_SetAnimation(0x84, 1, 0);

        buf[0] = D_00622FA0[0];
        buf[1] = D_00622FA0[1];
        soundSeDefPlay(0x50A, 0, (float *)buf, 1);

        scpPlayMot(D_00639EA8, 0x2D3);
        scpPlayWaitMotEnd(D_00639EA8);

        scpPlayMot(D_00639EA8, 0x214);
        *(int *)(*(int *)((char *)D_00639EA8 + 0x15C) + 0x514) =
            (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 0.0f);

        scpPlayEnd(D_00639EA8);

        D_0063AA08 = 0;
    } else {
        long long buf2[2];

        scpPlayStart(D_00639EA4);
        scpPlayStart(D_00639EA8);

        stage_SetAnimation(0x84, 1, 0);

        buf2[0] = D_00622FA0[0];
        buf2[1] = D_00622FA0[1];
        soundSeDefPlay(0x50A, 0, (float *)buf2, 1);

        scpPlayMot(D_00639EA4, 0x106);
        scpPlayMot(D_00639EA8, 0x2D2);
        scpPlayWaitMotEnd(D_00639EA4);

        scpPlayEnd(D_00639EA4);
        scpPlayEnd(D_00639EA8);

        scpPlayMot(D_00639EA4, 0);
        scpPlayMot(D_00639EA8, 0x214);
        *(int *)(*(int *)((char *)D_00639EA8 + 0x15C) + 0x514) =
            (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 0.0f);
    }

    while (stage_CheckAnimationFinish(0x84) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

INCLUDE_ASM("asm/nonmatchings/src/st17a", actSt17aHasiEffect);

typedef struct PadState {
    int unk00;        /* 0x00 */
    int flags;        /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} PadState;

extern PadState D_0028F8F0[];
extern int lt_fade_status(void);
extern int scpAdpcmPlayRequestNum(void);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern void scpFadeIn(float f);
extern void lt_switch_layout(int a0);
extern void SetCameraFlag_LwsCutBack(void);
extern int D_0063AA08;
extern int D_0063C598;

/* a0 is the actor entry parameter: its stack home is the actor-thread frame
   slot the scheduler reads, so it is volatile like every other stage actor. */
void actSt17aIntroCancel(volatile int a0)
{
    D_0063C598 = 0;

    while (lt_fade_status() != 2) {
        _ACTWait(1);
    }

    while (D_0063C598 == 0 &&
           ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (D_0063C598 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x53, 1, -1);
        SetCameraFlag_LwsCutBack();
        scpFadeIn(3.0f);
    }

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

extern ActMail D_004FAF10[];
extern void actLinkTestChk(int a0);

void actLinkTest(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004FAF10[0].func = actLinkTestChk;
    self->mail = D_004FAF10;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt17aSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x20, 0x52, 0x82, 0x12, 6450.0f, -2100.0f, 1000.0f, 6450.0f, -2100.0f, 1100.0f);
}

extern ActMail D_004FAFD0[];
extern void actSt17aHasiChk(int a0);
extern int scpSearchGobj(int a0);
extern void SetWayGroupActive(int a0, int a1);

void actSt17aHasi(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x21) == 0) {
        *(int *)(scpSearchGobj(0xF4) + 0x16C) = 0;
        stage_SetAnimation(0x84, 0, 0);
        SetWayGroupActive(3, 1);
        D_004FAFD0[0].func = actSt17aHasiChk;
        self->mail = D_004FAFD0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        *(int *)(scpSearchGobj(0xF3) + 0x16C) = 0;
        stage_SetAnimation(0x84, 0, -1);
    }
}

extern ActMail D_004FAFF0[];
extern void actSt17aIntroChk(int a0);

void actSt17aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x22) == 0) {
        D_004FAFF0[0].func = actSt17aIntroChk;
        self->mail = D_004FAFF0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004FB010[];
extern void actSt17aHint1Chk(int a0);

void actSt17aHint1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x23) == 0) {
        D_004FB010[0].func = actSt17aHint1Chk;
        self->mail = D_004FB010;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        FinishHint(0);
    }
}

extern ActMail D_004FB030[];
extern void actSt17aFallChk(int a0);

void actSt17aFall(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x21) == 0) {
        D_004FB030[0].func = actSt17aFallChk;
        self->mail = D_004FB030;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt17aSekizoEvent(int x)
{
    volatile int local = x;
}

extern int *D_00639EA4;
extern void _ACTWait();
extern void scpGetWallCollision(float a0, float a1, float a2, float a3, float a4, float a5);

void actLinkTestChk(volatile int a0)
{
    *(int *)(D_00639EA4[0x57] + 0x4E8) = 1;
    *(int *)(D_00639EA4[0x57] + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
}

void actSt17aDoorEvent(int x)
{
    volatile int local = x;
}

extern long long D_00622F70[];
extern long long D_00622F80[];
extern void scpEffectStart(int *buf, int a1);

void actSt17aDoorUpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_00622F70[0];
    long long v0b = D_00622F80[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622F70[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622F80[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

extern long long D_00622F90[];

void actSt17aDoorDownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_00622F80[0];
    long long v0b = D_00622F90[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622F80[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622F90[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt17aHasiEvent(int x)
{
    volatile int local = x;
}

extern void lt_switch_layout(int a0);
extern int D_0063AA08;
extern int D_0063C598;
extern int cam;
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern void actSt17aIntroCancel(int a0);

void actSt17aIntroChk(volatile int a0)
{
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    gflagOn(0x22);
    scpAdpcmPlayRequestFunc(0x35, &cam, 1, 1, 1);
    _ACTWait(1);
    stage_SetAnimation(0x53, 1, 0);
    SetCameraFlag_LwsCutBack();
    actCreateSubThread(actSt17aIntroCancel, 0x15);

    while (stage_CheckAnimationFinish(0x53) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C598 = 1;
}

extern long long D_00623020[];
extern void *D_00639EA8;
extern void _SCPMoveCharactorByWay(void *a0, int a1, int *buf, int a3, float f);

void actSt17aGirlWay(volatile int a0)
{
    long long buf[2];
    buf[0] = D_00623020[0];
    buf[1] = D_00623020[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 2, 100.0f);
}

extern int scpTriggerBall(int a0, void *a1, float radius);
extern char D_00623030[];

void actSt17aHint1Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00623030);

    gflagOn(0x23);
    FinishHint(0);
}

extern char D_00623050[];

void actSt17aFallChk(volatile int a0)
{
    while (!(gflagChk(0x21) && scpTriggerBall(a0, D_00639EA4, 1800.0f))) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00623050);

    iosOmSendMail(D_00639EA4, 0xE2, D_00639EA4);
}
