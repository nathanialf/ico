#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD0];  /* 0x00 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} Act;

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    Act *act;          /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObj;

extern PObjGObj *scpSearchGobj(int a0);
extern int gflagChk(int a0);
extern void SetWayGroupActive(int grp, int on);
extern void stage_SetAnimation(int no, int a1, int a2);

void actSt02aInit(void)
{
    if (gflagChk(0x76) == 0) {
        SetWayGroupActive(0x1A, 0);
        stage_SetAnimation(0x63, 0, 0);
    } else {
        stage_SetAnimation(0x63, 0, -1);
    }
}

extern int scpTriggerBall(int a0, int gobj, float r);
extern char *D_00639EA4;
extern int D_00639EA8;
extern ActMail D_004F8050[];
extern ActMail D_004F8070[];
extern void actSt02aDoorUpChk(volatile int a0);
extern void actSt02aDoorDownChk(volatile int a0);
extern Act *actInitialize(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void _ACTWait(int a0);

void actSt02aDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);
    if (scpTriggerBall(a0, (int)D_00639EA4, 200.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(0x62, 0, 0);
        _ACTWait(0x3C);
        D_004F8050[0].func = actSt02aDoorDownChk;
        self->mail = D_004F8050;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x61, 0, 0);
        D_004F8070[0].func = actSt02aDoorUpChk;
        self->mail = D_004F8070;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern long long D_00622710[];
extern ActMail D_004F8090[];
extern void actSt02aDoorUpEffect(volatile int a0);
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
extern int actCreateSubThread(void *entry, int prio);
extern void scpWakeupItemWithBoundary(float x, float y, float z, float r);
extern int soundSeDefPlay(int se, int a1, void *pos, int a3);
extern void soundSeDefStop(int handle);
extern int stage_CheckAnimationFinish(int a0);

void actSt02aDoorUpChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;
    long long pos[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);
    actCreateSubThread(actSt02aDoorUpEffect, 0x15);
    scpWakeupItemWithBoundary(-1827.0f, -1072.0f, 2285.0f, 100.0f);
    stage_SetAnimation(0x61, 1, 0);
    pos[0] = D_00622710[0];
    pos[1] = D_00622710[1];
    soundSeDefPlay(0x4C4, 0, pos, 1);
    _ACTWait(0x1E);
    h = soundSeDefPlay(0x4C5, 0, pos, 1);
    _ACTWait(0x1E);
    soundSeDefStop(h);
    soundSeDefPlay(0x4C6, 0, pos, 1);
    while (stage_CheckAnimationFinish(0x61) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_004F8090[0].func = actSt02aDoorDownChk;
    sub->mail = D_004F8090;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern ActMail D_004F80B0[];
extern void actSt02aDoorDownEffect(volatile int a0);

void actSt02aDoorDownChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;
    long long pos[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);
    actCreateSubThread(actSt02aDoorDownEffect, 0x15);
    scpWakeupItemWithBoundary(-1827.0f, -1072.0f, 2285.0f, 100.0f);
    stage_SetAnimation(0x62, 1, 0);
    pos[0] = D_00622710[0];
    pos[1] = D_00622710[1];
    soundSeDefPlay(0x4C4, 0, pos, 1);
    _ACTWait(0x1E);
    h = soundSeDefPlay(0x4C5, 0, pos, 1);
    _ACTWait(0x1E);
    soundSeDefStop(h);
    soundSeDefPlay(0x4C6, 0, pos, 1);
    while (stage_CheckAnimationFinish(0x62) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_004F80B0[0].func = actSt02aDoorUpChk;
    sub->mail = D_004F80B0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern int D_0028F8F4[];
extern int D_0063AA08;
extern int st02a_fence;
extern int D_0063C504;
extern void actSt02aFenceOpenSub(volatile int a0);
extern void scpSleepEnemyAll(void);
extern int scpAdpcmPlayRequestNum(void);
extern int scpAdpcmFadeCloseFunc(int *h, int fade);
extern void iosThreadSetPri(int th, int pri);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern void scpFadeIn(float t);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern void SetCameraFlag_GamecamCutBack(void);
extern void SetWayGroupActive(int grp, int on);

void actSt02aFenceOpen(volatile int a0)
{
    int th;

    scpSleepEnemyAll();
    gflagOn(0x76);
    scpAdpcmPlayRequestFunc(0x60, &st02a_fence, 1, 1, 1);
    th = actCreateSubThread(actSt02aFenceOpenSub, 0x15);
    D_0063C504 = 0;

    while (D_0063C504 == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C504 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (st02a_fence == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc(&st02a_fence, 0x200);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(0x63, 0, -1);
        stage_SetAnimation(0x64, 0, -1);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(8.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    SetWayGroupActive(0x1A, 1);
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    scpWakeupEnemyAll();
}

extern void CopyVector(void *a0, float *a1);
extern long long D_00622740[];
extern char *D_00639EA4;
extern int GetSkeltonFocusNode(void *obj, int kind);
extern void _ACTWait(int a0);
extern void scpEffectStart(void *buf, int kind);
extern int scpTriggerPosBall(void *a, void *b, float f);

void actSt02WaterFallBoySplashCheck(volatile int a0)
{
    long long buf[4];
    long long buf2[2];
    int idx;
    if (D_00639EA4 == 0)
        return;
    buf[0] = D_00622740[0];
    buf[1] = D_00622740[1];
    buf[2] = D_00622740[2];
    buf[3] = D_00622740[3];
    for (;;) {
        idx = GetSkeltonFocusNode(D_00639EA4, 0x23);
        CopyVector(buf2,
                   (float *)(*(int *)(*(char **)(D_00639EA4 + 0x15C) + 0xC) + (idx << 6) + 0x30));
        if (scpTriggerPosBall(&buf[0], buf2, 100.0f))
            scpEffectStart(buf2, 0x2F);
        _ACTWait(0xA);
        idx = GetSkeltonFocusNode(D_00639EA4, 0x23);
        CopyVector(buf2,
                   (float *)(*(int *)(*(char **)(D_00639EA4 + 0x15C) + 0xC) + (idx << 6) + 0x30));
        if (scpTriggerPosBall(&buf[2], buf2, 100.0f))
            scpEffectStart(buf2, 0x2F);
        _ACTWait(0xA);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st02a", actSt02aWaterFallReflactionEffect);

extern void DeleteParticleLayout(PObjGObj *a0);
extern void scpTransGObj(void *a0, float x, float y, float z);
extern void ReInitBoxGeo(PObjGObj *a0);

void actSt02aWaterFallChk(volatile int a0)
{
    Act *act = ((PObjGObj *)D_00639EA4)->act;

    *(long long *)((char *)act + 0x20) &= ~0x80000000000LL;
    scpSearchGobj(0x6B1)->f16C = 1;
    scpSearchGobj(0x686)->f16C = 0;
    scpSearchGobj(0x697)->f16C = 0;
    scpSearchGobj(0x698)->f16C = 0;
    scpSearchGobj(0x69B)->f16C = 0;
    DeleteParticleLayout(scpSearchGobj(0x6BA));
    DeleteParticleLayout(scpSearchGobj(0x6BB));
    DeleteParticleLayout(scpSearchGobj(0x6BC));
    DeleteParticleLayout(scpSearchGobj(0x6BD));
    stage_SetAnimation(0x187, -1, -2);
    scpTransGObj(scpSearchGobj(0x6A9), 0.0f, -200.0f, 0.0f);
    scpTransGObj(scpSearchGobj(0x6AB), 0.0f, -200.0f, 0.0f);
    _ACTWait(5);
    ReInitBoxGeo(scpSearchGobj(0x6A9));
    ReInitBoxGeo(scpSearchGobj(0x6AB));
}

extern int gondola;
extern int D_00639EAC;
extern int D_0063AA08;
extern ActMail D_004F81D0[];
extern void actSt02aGondolaMain(volatile int a0);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern void scpAdpcmCloseFunc(int *a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int iosPadActRequest(int port, int id);
extern void gflagOn(int a0);
extern void lt_switch_layout(int a0);
extern void scpWakeupEnemyAll(void);

void actSt02aGondolaUp(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    scpAdpcmPlayRequestFunc(0x57, &gondola, 1, 1, 1);

    while (gondola == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x10);
    stage_SetAnimation(0x65, 1, 0);
    gflagOn(0x77);

    while (stage_CheckAnimationFrame(0x65, 0x8C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFrame(0x65, 0x95, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(0x78);

    if (gondola != 0) {
        scpAdpcmCloseFunc(&gondola);
    }

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();

    D_004F81D0[0].func = actSt02aGondolaMain;
    sub->mail = D_004F81D0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern int gondola_test;
extern ActMail D_004F81F0[];
extern void gflagOff(int a0);

void actSt02aGondolaDown(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    scpAdpcmPlayRequestFunc(0x57, &gondola_test, 1, 1, 1);

    while (gondola_test == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x65, 1, 0x96);
    gflagOff(0x77);

    while (stage_CheckAnimationFrame(0x65, 0x127, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFrame(0x65, 0x12C, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(0x78);

    if (gondola_test != 0) {
        scpAdpcmCloseFunc(&gondola_test);
    }

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();

    D_004F81F0[0].func = actSt02aGondolaMain;
    sub->mail = D_004F81F0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt02aBox(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    if (gflagChk(0x6D) != 0) {
        scpSearchGobj(0x6A9)->f16C = 0;
        if (gflagChk(0x6A) != 0) {
            scpSearchGobj(0x6A9)->f16C = 0;
            scpSearchGobj(0x6AA)->f16C = 0;
        } else {
            scpSearchGobj(0x6AB)->f16C = 0;
        }
    }
    if (gflagChk(0x6C) != 0) {
        scpSearchGobj(0x6AA)->f16C = 0;
        scpSearchGobj(0x6AB)->f16C = 0;
    }
    if (gflagChk(0x6C) == 0 && gflagChk(0x6D) == 0) {
        scpSearchGobj(0x6A9)->f16C = 0;
        scpSearchGobj(0x6AA)->f16C = 0;
        scpSearchGobj(0x6AB)->f16C = 0;
    }
}

extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern ActMail D_004F8170[];
extern void actSt02aGondolaMain(volatile int a0);

void actSt02aGondola(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x77) != 0) {
        stage_SetAnimation(0x65, 0, 0);
        _ACTWait(0xA);
        stage_SetAnimation(0x65, 0, 0x95);
    } else {
        stage_SetAnimation(0x65, 0, 0x12C);
    }

    D_004F8170[0].func = actSt02aGondolaMain;
    self->mail = D_004F8170;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F80F0[];
extern void actSt02aFenceMain(volatile int a0);

void actSt02aFence(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x76) == 0) {
        D_004F80F0[0].func = actSt02aFenceMain;
        self->mail = D_004F80F0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int actCreateSubThread(void *entry, int prio);
extern ActMail D_004F8130[];
extern void actSt02aWaterFallChk(volatile int a0);
extern void actSt02aWaterFallReflactionEffect(volatile int a0);

void actSt02aWaterFall(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6A) != 0) {
        D_004F8130[0].func = actSt02aWaterFallChk;
        self->mail = D_004F8130;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }

    scpSearchGobj(0x6B1)->f16C = 0;

    actCreateSubThread(actSt02WaterFallBoySplashCheck, 0x15);
    actCreateSubThread(actSt02aWaterFallReflactionEffect, 0x15);
}

extern Act *actInitialize(int a0);
extern int gflagChk(int a0);

void actSt02aBoxEvent2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6E) == 0) {
        scpSearchGobj(0x6AD)->f16C = 0;
    }
}

extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8210[];
extern void actSt02aEneChk(volatile int a0);

void actSt02aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x79) == 0) {
        D_004F8210[0].func = actSt02aEneChk;
        self->mail = D_004F8210;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt02aEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x7A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt02aEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);
    Generator_Mask((int)scpSearchGobj(0x6A7));

    while (gflagChk(0x7A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_Call((int)scpSearchGobj(0x6A7));
}

extern Act *actInitialize(int a0);
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt02aSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x7B, 0x66, 0, 0x12, 900.0f, 1828.0f, 1150.0f, 800.0f, 1828.0f, 1150.0f);
}

extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8230[];
extern ActMail D_004F8250[];
extern void actSt02aWayOffChk(volatile int a0);
extern void actSt02aWayOnChk(volatile int a0);

void actSt02aWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x7C) == 0) {
        D_004F8230[0].func = actSt02aWayOffChk;
        self->mail = D_004F8230;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        D_004F8250[0].func = actSt02aWayOnChk;
        self->mail = D_004F8250;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F82B0[];
extern void actSt02aTakiWayOnChk(volatile int a0);

void actSt02aTakiWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6A) != 0) {
        D_004F82B0[0].func = actSt02aTakiWayOnChk;
        self->mail = D_004F82B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8310[];
extern void actSt02aSecretItemChk(volatile int a0);

void actSt02aSecretItem(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x72) == 0) {
        D_004F8310[0].func = actSt02aSecretItemChk;
        self->mail = D_004F8310;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt02aDoorEvent(int x)
{
    volatile int local = x;
}

extern long long D_00622720[];
extern long long D_00622730[];
extern void scpEffectStart__pn(int *buf, int a1) __asm__("scpEffectStart");

void actSt02aDoorUpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_00622720[0];
    long long v0b = D_00622730[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622720[1];
            scpEffectStart__pn((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622730[1];
            scpEffectStart__pn((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt02aDoorDownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_00622730[0];
    long long v0b = D_00622720[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622730[1];
            scpEffectStart__pn((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622720[1];
            scpEffectStart__pn((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

extern ActMail D_004F80D0[];

void actSt02aFenceMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F80D0;
    while (1) {
        _ACTWait(1);
    }
}

extern void lt_switch_layout(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int D_0063AA08;
extern ActMail D_004F8110[];
extern void actSt02aFenceOpen(volatile int a0);

void actSt02aFenceSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    D_004F8110[0].func = actSt02aFenceOpen;
    sub->mail = D_004F8110;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int st02a_fence;
extern int D_0063C504;

void actSt02aFenceOpenSub(volatile int a0)
{
    while (st02a_fence == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(0x63, 1, 0);
    stage_SetAnimation(0x64, 1, 0);
    while (stage_CheckAnimationFinish(0x64) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C504 = 1;
    _ACTWait(0);
}

extern void scpSleepEnemyAll(void);
extern ActMail D_004F8150[];
extern ActMail D_004F8190[];
extern ActMail D_004F81B0[];
extern void actSt02aGondolaUp(volatile int a0);
extern void actSt02aGondolaDown(volatile int a0);

void actSt02aGondolaMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F8150;
    while (1) {
        _ACTWait(1);
    }
}

void actSt02aGondolaSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(0x77) != 0) {
        D_004F8190[0].func = actSt02aGondolaDown;
        sub->mail = D_004F8190;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }

    D_004F81B0[0].func = actSt02aGondolaUp;
    sub->mail = D_004F81B0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern int D_00639EA8;
extern int scpTriggerFloorAttr(int a0, int a1);
extern void gflagOn(int a0);

void actSt02aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(0x79);
    gflagOn(0x7A);
}

void actSt02aSekizoEvent(int x)
{
    volatile int local = x;
}

extern int scpCheckExistAliveEnemy(void);
extern void SetWayGroupActive(int a0, int a1);
extern void gflagOff(int a0);

/* The way-on watcher's mail record: it installs actSt02aWayOffChk here and
   posts it. Word 0 of each entry is the mail id the entry answers (0x1AE the
   actor post, 0x1AD the trailing entry); .func is filled in at run time.
   Named for the thread that owns and posts it. */
static ActMail way_on_mail[2] = {{0x1AE}, {0x1AD}};

extern void actSt02aWayOffChk(volatile int a0);

void actSt02aWayOnChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x35, 1);
    SetWayGroupActive(0x37, 1);
    SetWayGroupActive(0x38, 1);
    SetWayGroupActive(0x39, 1);
    gflagOff(0x7C);

    way_on_mail[0].func = actSt02aWayOffChk;
    sub->mail = way_on_mail;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern int scpCheckExistAliveEnemy(void);
extern void SetWayGroupActive(int a0, int a1);
extern ActMail D_004F8290[];
extern void actSt02aWayOnChk(volatile int a0);

void actSt02aWayOffChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x35, 0);
    SetWayGroupActive(0x37, 0);
    SetWayGroupActive(0x38, 0);
    SetWayGroupActive(0x39, 0);
    gflagOn(0x7C);

    D_004F8290[0].func = actSt02aWayOnChk;
    sub->mail = D_004F8290;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

/* The waterfall way-on watcher's own mail record (installs
   actSt02aTakiWayOffChk). */
static ActMail taki_on_mail[2] = {{0x1AE}, {0x1AD}};

extern void actSt02aTakiWayOffChk(volatile int a0);

void actSt02aTakiWayOnChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(D_00639EA8, 0x6000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x23, 1);
    SetWayGroupActive(0x3B, 1);

    taki_on_mail[0].func = actSt02aTakiWayOffChk;
    sub->mail = taki_on_mail;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

/* The waterfall way-off watcher's own mail record (installs
   actSt02aTakiWayOnChk). */
static ActMail taki_off_mail[2] = {{0x1AE}, {0x1AD}};

extern void actSt02aTakiWayOnChk(volatile int a0);

void actSt02aTakiWayOffChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x23, 0);
    SetWayGroupActive(0x3B, 0);

    taki_off_mail[0].func = actSt02aTakiWayOnChk;
    sub->mail = taki_off_mail;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void scpExplodeSecretItem(void);

void actSt02aSecretItemChk(volatile int a0)
{
    while (scpSearchGobj(0x6EA) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x3C);

    scpExplodeSecretItem();
}
