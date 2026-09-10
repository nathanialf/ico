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
    char pad00[0x50];         /* 0x000 */
    int f50;                  /* 0x050 */
    char pad54[0x164 - 0x54]; /* 0x054 */
    int act;                  /* 0x164 */
    char pad168[0x4];         /* 0x168 */
    int f16C;                 /* 0x16C */
} PObjGObj;

extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void scpTorchLightOff(int a0);
extern void DeleteLayoutedCandleParticleEffect(void);
extern PObjGObj *scpSearchGobj(int a0);
extern void gflagOn(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern void FinishHint(int a0);
extern void SetWayGroupActive(int a0, int a1);
extern void scpLinkBGAtoLayoutedTarget(int a0, int a1);

void actSt07aInit(void)
{
    if (gflagChk(0x7E) != 0) {
        scpSearchGobj(0x18D)->f16C = 0;

        stage_SetAnimation(0x168, -1, -2);

        FinishHint(3);

        if (gflagChk(0x80) != 0) {
            SetWayGroupActive(0xB, 0);
            SetWayGroupActive(0xC, 0);
            stage_SetAnimation(0x165, 0, -1);
        } else {
            SetWayGroupActive(0xD, 0);
            SetWayGroupActive(0xE, 0);
            SetWayGroupActive(0xF, 0);
            stage_SetAnimation(0x164, 0, -1);
        }
    } else {
        scpLinkBGAtoLayoutedTarget(0x18D, 0x168);

        SetWayGroupActive(0xD, 0);
        SetWayGroupActive(0xE, 0);
        SetWayGroupActive(0xF, 0);

        stage_SetAnimation(0x164, 0, 0);
        stage_SetAnimation(0x163, 0, 0);
    }
}

extern int D_00639EA8;

void actSt07aEnd(void)
{
    if (D_00639EA8 != 0 && gflagChk(0x83) == 0 && gflagChk(0x80) != 0) {
        gflagOn(0x187);
    }
    if (D_00639EA8 != 0 && gflagChk(0x86) == 0 && gflagChk(0xAE) != 0) {
        gflagOn(0x187);
    }
}

typedef struct Pad {
    int unk00;        /* 0x00 */
    int trg;          /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} Pad;

extern Pad D_0028F8F0[];
extern int D_00639EA4;
extern int D_0063AA08;
extern int D_0063C560;
extern int scpTriggerFloorAttr(int a0, int a1);
extern int actCreateSubThread(void *entry, int prio);
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern int scpAdpcmPlayRequestNum(void);
extern void scpAdpcmFadeCloseFunc(int *a0, int a1);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern void scpFadeIn(float t);
extern int scpFadeChk(void);
extern void iosThreadSetPri(int th, int pri);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void scpPlayStart(int a0);
extern void scpPlayEnd(int a0);
extern void scpPlayMot(int a0, int mot);
extern void scpPlayMotDir(int a0, void *dir);
extern void *test_CURRENTROOT(int a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void SetCameraFlag_GamecamCutBack(void);
extern int iosPadActRequest(int port, int id);
extern int ReviveAllCarryableItemsWithRandomVelocity(float a0, float a1);
extern int D_00639EAC;
extern int D_0028F4C0[];
extern void actSt07aChanWay1(volatile unsigned int a0);
extern void actSt07aChanWay2(volatile unsigned int a0);
extern void actSt07aChanEffect(volatile int a0);
extern void actSt07aChanMot(volatile int a0);
extern void actSt07aChanFall(volatile int a0);
extern void AdpcmPlay(int handle);
extern void scpTorchLightOn(int a0);
extern long long D_00622C60[];
extern int bridge;

void actSt07aChanChk(volatile int a0)
{
    long long buf[2];
    float dir[4];
    int hEffect;
    int hMot;
    int hFall;

    while (gflagChk(0x7F) == 0) {
        _ACTWait(1);
    }

    soundSeDefPlay(0x521, 0, 0, 1);

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        actCreateSubThread(actSt07aChanWay1, 0x15);
    }
    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x5000000) != 0) {
        actCreateSubThread(actSt07aChanWay2, 0x15);
    }

    scpSleepEnemyAll();
    FinishHint(3);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    stage_SetAnimation(0x163, 1, 0);

    _ACTWait(1);

    scpSearchGobj(0x18D)->f16C = 0;
    stage_SetAnimation(0x168, -1, -2);

    while (stage_CheckAnimationFinish(0x163) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayStart(D_00639EA4);

    if (D_00639EA8 != 0) {
        scpPlayStart(D_00639EA8);
    }

    gflagOn(0x7E);

    while (bridge == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(*(int *)(bridge + 0x2C));

    hEffect = actCreateSubThread(actSt07aChanEffect, 0x15);

    hMot = actCreateSubThread(actSt07aChanMot, 0x15);

    hFall = actCreateSubThread(actSt07aChanFall, 0x15);

    D_0063C560 = 0;

    while (D_0063C560 == 0 && ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (D_0063C560 == 0) {
        scpAdpcmFadeCloseFunc(&bridge, 0xC0);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        iosThreadSetPri(hEffect + 0x24, 0x22);
        iosThreadSetPri(hMot + 0x24, 0x22);
        iosThreadSetPri(hFall + 0x24, 0x22);

        stage_SetAnimation(0x164, 1, -1);
        scpPlayMot(D_00639EA4, 0x1DB);

        DeleteLayoutedCandleParticleEffect();
        _ACTWait(1);

        scpTorchLightOn(0x1AF);
        scpTorchLightOn(0x1B0);

        SetCameraFlag_GamecamCutBack();
        scpFadeIn(3.0f);
    } else {
        iosThreadSetPri(hEffect + 0x24, 0x22);
        iosThreadSetPri(hMot + 0x24, 0x22);
        iosThreadSetPri(hFall + 0x24, 0x22);
    }

    buf[0] = D_00622C60[0];
    buf[1] = D_00622C60[1];
    sceVu0SubVector(dir, buf, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpPlayMot(D_00639EA4, 0);

    scpPlayEnd(D_00639EA4);

    if (D_00639EA8 != 0) {
        scpPlayEnd(D_00639EA8);
    }

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    scpWakeupEnemyAll();
}

void actSt07aChanEffect(volatile int a0)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 154:
            iosPadActRequest(D_00639EAC, 15);
            ReviveAllCarryableItemsWithRandomVelocity(-5.0f, 0.0f);
            break;
        case 84:
        case 210:
            iosPadActRequest(D_00639EAC, 17);
            break;
        case 420:
            iosPadActRequest(D_00639EAC, 15);
            break;
        case 434:
            iosPadActRequest(D_00639EAC, 16);
            break;
        case 574:
            iosPadActRequest(D_00639EAC, 17);
            break;
        case 0:
        case 112:
        case 300:
            break;
        }

        n = (int)t;
        tn = t + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 1600.0f);
    _ACTWait(0);
}

extern int scpIsBombExplode(int a0);
extern int scpTriggerBall(int a0, int a1, float radius);
extern int scpTriggerFloorAttr(int a0, int a1);
extern int actCreateSubThread(void *entry, int prio);
extern void actSt07aGirlWay(volatile unsigned int a0);
extern void actSt07aTsuroEffect(volatile int a0);
extern void actSt07aTsuroConte(volatile int a0);
extern void lt_switch_layout(int a0);
extern void brainLockGirl(void);
extern void brainUnlockGirl(void);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern int scpAdpcmPlayRequestNum(void);
extern void scpAdpcmFadeCloseFunc(int *a0, int a1);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern void scpFadeIn(float t);
extern int scpFadeChk(void);
extern void iosPadActStopAll(void);
extern void iosThreadSetPri(int th, int pri);
extern void _SCPMoveCharactorByWay_Cancel(int a0);
extern void SetDirectRootPosition(int obj, void *pos);
extern void SetCameraFlag_GamecamCutBack(void);
extern int ReviveAllCarryableItemsWithRandomVelocity(float a0, float a1);
extern int sekizo7a;
extern int D_0063C560;
extern int D_0063AA08;
extern long long D_00622C90[];

void actSt07aTsuroChk(volatile int a0)
{
    long long buf[2];
    int obj;
    int wk;
    int hGirl;
    int hEffect;
    int hConte;

    hGirl = 0;

    while ((obj = scpIsBombExplode(0x13)) == 0 || scpTriggerBall(a0, obj, 200.0f) == 0) {
        _ACTWait(1);
    }

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        hGirl = actCreateSubThread(actSt07aGirlWay, 0x15);
    }

    gflagOn(0x80);

    lt_switch_layout(0x37);

    D_0063AA08 = 1;
    brainLockGirl();

    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(0x3C, &sekizo7a, 1, 1, 1);
    while (sekizo7a == 0) {
        _ACTWait(1);
    }

    hEffect = actCreateSubThread(actSt07aTsuroEffect, 0x15);
    hConte = actCreateSubThread(actSt07aTsuroConte, 0x15);

    D_0063C560 = 0;
    while (D_0063C560 == 0 && ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    wk = D_0063C560 ^ 1;

    if (wk != 0) {
        scpAdpcmFadeCloseFunc(&sekizo7a, 0xC0);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosPadActStopAll();
    iosThreadSetPri(hConte + 0x24, 0x22);
    iosThreadSetPri(hEffect + 0x24, 0x22);
    if (hGirl != 0) {
        iosThreadSetPri(hGirl + 0x24, 0x22);
        _ACTWait(2);
        _SCPMoveCharactorByWay_Cancel(D_00639EA8);
    }

    if (wk != 0) {
        stage_SetAnimation(0x165, 0, -1);
        stage_SetAnimation(0x166, 0, -1);
        ReviveAllCarryableItemsWithRandomVelocity(-5.0f, 0.0f);
        _ACTWait(2);

        if (hGirl != 0) {
            buf[0] = D_00622C90[0];
            buf[1] = D_00622C90[1];
            SetDirectRootPosition(D_00639EA8, buf);
        }

        SetCameraFlag_GamecamCutBack();
        scpFadeIn(8.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    lt_switch_layout(0x36);

    D_0063AA08 = 0;
    brainUnlockGirl();

    gflagOn(0x85);

    scpWakeupEnemyAll();

    SetWayGroupActive(0xB, 0);
    SetWayGroupActive(0xC, 0);
    SetWayGroupActive(0xD, 1);
    SetWayGroupActive(0xE, 1);
    SetWayGroupActive(0xF, 1);

    scpTorchLightOff(0x1AF);
    scpTorchLightOff(0x1B0);
}

typedef struct EffectArg {
    long long lo; /* 0x00 */
    long long hi; /* 0x08 */
} EffectArg;

extern const EffectArg D_00622CA0;
extern const EffectArg D_00622CB0;
extern const EffectArg D_00622CC0;
extern const EffectArg D_00622CD0;
extern const EffectArg D_00622CE0;
extern const EffectArg D_00622CF0;
extern const EffectArg D_00622D00;
extern const EffectArg D_00622D10;
extern const EffectArg D_00622D20;
extern int D_0028F4C0[];
extern int scpEffectStart(void *a0, int a1);
extern int iosPadActRequest(int port, int id);
extern int ReviveAllCarryableItemsWithRandomVelocity(float a0, float a1);
extern int D_00639EAC;

void actSt07aTsuroEffect(volatile int a0)
{
    EffectArg b1;
    EffectArg b2;
    EffectArg b3;
    EffectArg b4;
    EffectArg b5;
    EffectArg b6;
    EffectArg b7;
    EffectArg b8;
    EffectArg b9;
    EffectArg b10;
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 212:
            b1 = D_00622CA0;
            scpEffectStart(&b1, 13);
            b2 = D_00622CA0;
            scpEffectStart(&b2, 15);
            break;
        case 438:
            b3 = D_00622CB0;
            scpEffectStart(&b3, 13);
            break;
        case 465:
            iosPadActRequest(D_00639EAC, 16);
            break;
        case 100:
        case 180:
        case 480:
            iosPadActRequest(D_00639EAC, 17);
            break;
        case 505:
            ReviveAllCarryableItemsWithRandomVelocity(-5.0f, 0.0f);
            b4 = D_00622CC0;
            scpEffectStart(&b4, 15);
            iosPadActRequest(D_00639EAC, 15);
            break;
        case 510:
            b5 = D_00622CD0;
            scpEffectStart(&b5, 11);
            b6 = D_00622CE0;
            scpEffectStart(&b6, 15);
            b7 = D_00622CF0;
            scpEffectStart(&b7, 15);
            b8 = D_00622D00;
            scpEffectStart(&b8, 11);
            break;
        case 560:
            b9 = D_00622D10;
            scpEffectStart(&b9, 15);
            b10 = D_00622D20;
            scpEffectStart(&b10, 15);
            break;
        }

        n = (int)t;
        tn = t + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 600.0f);
    _ACTWait(0);
}

extern int D_00639EA4;
extern int D_00639EAC;
extern int sekizo_7a;
extern int sekizo_7a_vol;
extern unsigned char D_0063BF78;
extern void scpKillEnemyOne(int a0);
extern void scpKillSpiderGroup(int a0);
extern void scpMaskGeneratorAll(void);
extern void ReviveAllCarryableItemsWithNonSleepFrame(int frames);
extern int iosPadActRequest(int port, int id);
extern void iosPadActVolumeSet(int h, int vol);
extern void iosPadActStop(int h);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void soundSeDefStop(int handle);
extern void scpPlayStart(int a0);
extern void scpPlayEnd(int a0);
extern void scpPlayPosSet(int a0, float x, float y, float z);
extern void *test_CURRENTROOT(int a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void scpPlayMotDir(int a0, void *dir);
extern void scpSekizouCheckPoint(void);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern void scpPlayWaitMotEnd(int a0);

void actSt07aSekizoChk(volatile int a0)
{
    /* the family's SE-handle slot at 4(sp): sound-subsystem owned (st13c
       actSt13cSekizoChk uses the same slot) */
    volatile int se;
    float dir[4];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 ||
           scpTriggerBall(a0, D_00639EA8, 200.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(0x13, &sekizo_7a, 1, 1, 1);
    while (sekizo_7a == 0) {
        _ACTWait(1);
    }

    scpKillEnemyOne(0x18F);
    scpKillEnemyOne(0x190);
    scpKillEnemyOne(0x191);
    scpKillEnemyOne(0x192);
    scpKillEnemyOne(0x193);
    scpKillEnemyOne(0x194);
    scpKillEnemyOne(0xEAD);
    scpKillSpiderGroup(0x195);

    scpMaskGeneratorAll();

    stage_SetAnimation(0x16A, 1, 0);

    ReviveAllCarryableItemsWithNonSleepFrame(0xFA);

    sekizo_7a_vol = iosPadActRequest(D_00639EAC, 9);
    D_0063BF78 = 0x80;
    iosPadActVolumeSet(sekizo_7a_vol, 0x80);

    se = soundSeDefPlay(0x4C1, 0, 0, 1);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);

    scpPlayPosSet(D_00639EA4, -3300.0f, 977.0f, -1050.0f);
    scpPlayPosSet(D_00639EA8, -3300.0f, 977.0f, -950.0f);

    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    D_0063AA08 = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpSekizouCheckPoint();

    scpPlayMot(D_00639EA8, 0x285);
    scpPlayWaitMotEnd(D_00639EA8);

    gflagOn(0x82);

    soundSeDefStop(se);

    while (stage_CheckAnimationFrame(0x16A, 0xB4, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_7a_vol);

    while (stage_CheckAnimationFinish(0x16A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA8, 0x214);
    scpPlayEnd(D_00639EA8);
    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    scpWakeupEnemyAll();

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

extern void actSt07aEneChk(volatile int a0);
extern ActMail D_004F9FE0[];

void actSt07aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    scpSearchGobj(0x18C)->f16C = 0;

    scpSearchGobj(0x198)->f50 = 0;
    scpSearchGobj(0x199)->f50 = 0;

    if (gflagChk(0x83) == 0) {
        scpSearchGobj(0x19B)->f16C = 0;
        scpSearchGobj(0x19C)->f16C = 0;
        scpSearchGobj(0x19D)->f16C = 0;
        scpSearchGobj(0x19E)->f16C = 0;
        scpSearchGobj(0x19F)->f16C = 0;
        scpSearchGobj(0x1A0)->f16C = 0;

        D_004F9FE0[0].func = actSt07aEneChk;
        self->mail = D_004F9FE0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern int scpTriggerBall(int a0, int a1, float radius);
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyOne(int a0);
extern void gflagOff(int a0);
extern void SetCameraFlag_LwsCutBack(void);
extern void reg_SetScissorSw(int a0);
extern void SetStaticBlur(int a0);
extern void scpSleepSpiderGroupOne(int a0);
extern void scpWakeupEnemyOne(int a0);
extern void scpWakeupSpiderGroupOne(int a0);
extern int D_0063AA08;

void actSt07aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(0x85) == 0 || scpTriggerBall(a0, D_00639EA8, 400.0f) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x18C)->f16C = 1;

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    scpSleepEnemyOne(0xEAD);

    gflagOff(0x187);

    gflagOn(0x83);
    gflagOn(0x84);

    stage_SetAnimation(0x167, 1, 0);
    SetCameraFlag_LwsCutBack();

    reg_SetScissorSw(1);

    SetStaticBlur(0);

    scpSleepEnemyOne(0x190);
    scpSleepSpiderGroupOne(0x195);

    while (stage_CheckAnimationFinish(0x167) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    reg_SetScissorSw(0);

    SetStaticBlur(1);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;

    scpSearchGobj(0x18C)->f16C = 0;

    _ACTWait(0x1E);

    scpWakeupEnemyOne(0xEAD);
    scpWakeupEnemyOne(0x190);
    scpWakeupSpiderGroupOne(0x195);
}

extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt07aGene1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask((int)scpSearchGobj(0x19A));

    while (gflagChk(0x84) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_Call((int)scpSearchGobj(0x19A));
}

extern void actSt07aChanChk(volatile int a0);
extern ActMail D_004F9F60[];

void actSt07aChan(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x7E) != 0) {
        DeleteLayoutedCandleParticleEffect();
        if (gflagChk(0x80) != 0) {
            scpTorchLightOff(0x1AF);
            scpTorchLightOff(0x1B0);
        }
    } else {
        scpTorchLightOff(0x1AF);
        scpTorchLightOff(0x1B0);
        D_004F9F60[0].func = actSt07aChanChk;
        self->mail = D_004F9F60;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void actSt07aChanReadyChk(volatile int a0);
extern ActMail D_004F9F20[];

void actSt07aChanReady(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x7E) == 0) {
        D_004F9F20[0].func = actSt07aChanReadyChk;
        self->mail = D_004F9F20;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void actSt07aChanChainChk(volatile int a0);
extern ActMail D_004F9F40[];

void actSt07aChanChain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x7F) == 0) {
        D_004F9F40[0].func = actSt07aChanChainChk;
        self->mail = D_004F9F40;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x1C6)->f16C = 0;
    }
}

extern void actSt07aTsuroChk(volatile int a0);
extern ActMail D_004F9F80[];

void actSt07aTsuro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x80) == 0) {
        D_004F9F80[0].func = actSt07aTsuroChk;
        self->mail = D_004F9F80;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        gflagOn(0x85);
    }
}

extern void actSt07aIntroChk(volatile int a0);
extern ActMail D_004F9FA0[];

void actSt07aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x81) == 0) {
        D_004F9FA0[0].func = actSt07aIntroChk;
        self->mail = D_004F9FA0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void actSt07aSekizoChk(volatile int a0);
extern ActMail D_004F9FC0[];

void actSt07aSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x82) == 0) {
        stage_SetAnimation(0x16A, 0, 0);
        D_004F9FC0[0].func = actSt07aSekizoChk;
        self->mail = D_004F9FC0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x16A, 0, -1);
    }
}

extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt07aGene2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x84) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt07aGene3(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x84) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern void actSt07aEne2Chk(volatile int a0);
extern ActMail D_004FA000[];

void actSt07aEne2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x86) == 0) {
        D_004FA000[0].func = actSt07aEne2Chk;
        self->mail = D_004FA000;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt07aGene2_1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x87) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void actSt07aGene2_2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x87) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt07aGene2_3(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x87) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
}

extern int D_00639EA4;
extern int bridge;
extern int scpTriggerFloorAttr(int a0, int a1);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);

void actSt07aChanReadyChk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(0x3B, &bridge, 1, 1, 0);
}

extern int GetAttackCheckBoundaryManagerStatus(PObjGObj *a0);
extern int scpGameStat_BoyWeaponkind(void);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);

void actSt07aChanChainChk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0x7F) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x1C6))) {
        case 1:
            if (scpGameStat_BoyWeaponkind() != 0) {
                gflagOn(0x7F);
                soundSeDefPlay(0x36E, 0, 0, 1);
                _ACTWait(0x1E);
                scpSearchGobj(0x1C6)->f16C = 0;
            }
        case 0:
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x1C6)->f16C = 0;
            gflagOn(0x7F);
            break;
        }
    }
}

void actSt07ChanEvent(int x)
{
    volatile int local = x;
}

extern void scpTorchLightOn(int a0);

void actSt07aChanFall(volatile int a0)
{
    stage_SetAnimation(0x164, 1, 0);
    _ACTWait(5);
    stage_SetAnimation(0x163, -1, -2);

    while (stage_CheckAnimationFinish(0x164) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    DeleteLayoutedCandleParticleEffect();
    _ACTWait(0x78);
    scpTorchLightOn(0x1AF);
    scpTorchLightOn(0x1B0);
    _ACTWait(0);
}

extern void scpPlayMot(int a0, int mot);
extern void scpPlayWaitMotEnd(int a0);
extern int D_0063C560;

void actSt07aChanMot(volatile int a0)
{
    scpPlayMot(D_00639EA4, 0x1DA);
    scpPlayWaitMotEnd(D_00639EA4);
    scpPlayMot(D_00639EA4, 0x1DB);
    scpPlayWaitMotEnd(D_00639EA4);

    D_0063C560 = 1;
    _ACTWait(0);
}

extern long long D_00622C70[];
extern int D_00639EA8;
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);

void actSt07aChanWay1(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_00622C70[0];
    buf[1] = D_00622C70[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

extern long long D_00622C80[];

void actSt07aChanWay2(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_00622C80[0];
    buf[1] = D_00622C80[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

void actSt07TsuroEvent(int x)
{
    volatile int local = x;
}

extern void SetCameraFlag_LwsCutBack(void);

void actSt07aTsuroConte(volatile int a0)
{
    stage_SetAnimation(0x165, 1, 0);
    stage_SetAnimation(0x166, 1, 0);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(0x166) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    D_0063C560 = 1;
    _ACTWait(0);
}

extern long long D_00622C90[];

void actSt07aGirlWay(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_00622C90[0];
    buf[1] = D_00622C90[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

void actSt07aCamera2(int x)
{
    volatile int local = x;
}

extern int scpTriggerBall(int a0, int a1, float radius);
extern void lt_switch_layout(int a0);
extern int D_0063AA08;

void actSt07aIntroChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    gflagOn(0x81);

    D_0063AA08 = 1;
    _ACTWait(1);

    stage_SetAnimation(0x161, 1, 0);
    while (stage_CheckAnimationFinish(0x161) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

void actSt07aSekizoEvent(int x)
{
    volatile int local = x;
}

extern void gflagOff(int a0);

void actSt07aEne2Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(0xAE) == 0 || scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    gflagOff(0x187);
    gflagOn(0x86);
    gflagOn(0x87);
}
