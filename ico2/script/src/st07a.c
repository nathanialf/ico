#include "common.h"
#include "st07a.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "brain.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "candle.h"
#include "geometryManager.h"
#include "item.h"
#include "staticBlur.h"
#include <libvu0.h>
#include "typedef.h"
#include "e3.h"

void actSt07aInit(void)
{
    if (gflagChk(126) != 0) {
        ((PObjGObj *)scpSearchGobj(397))->f16C = 0;

        stage_SetAnimation(360, -1, -2);

        FinishHint(3);

        if (gflagChk(128) != 0) {
            SetWayGroupActive(11, 0);
            SetWayGroupActive(12, 0);
            stage_SetAnimation(357, 0, -1);
        } else {
            SetWayGroupActive(13, 0);
            SetWayGroupActive(14, 0);
            SetWayGroupActive(15, 0);
            stage_SetAnimation(356, 0, -1);
        }
    } else {
        scpLinkBGAtoLayoutedTarget(0x18D, 0x168);

        SetWayGroupActive(13, 0);
        SetWayGroupActive(14, 0);
        SetWayGroupActive(15, 0);

        stage_SetAnimation(356, 0, 0);
        stage_SetAnimation(355, 0, 0);
    }
}

extern int D_00639EA8;

void actSt07aEnd(void)
{
    if (D_00639EA8 != 0 && gflagChk(131) == 0 && gflagChk(128) != 0) {
        gflagOn(391);
    }
    if (D_00639EA8 != 0 && gflagChk(134) == 0 && gflagChk(174) != 0) {
        gflagOn(391);
    }
}

extern Pad D_0028F8F0[];
extern int D_00639EA4;
extern int D_0063AA08;

/* .sbss, owned by st07a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthreads the wait loops below spin for. */
static int demoEnd;

extern int D_00639EAC;
extern int D_0028F4C0[];

/* A 16-byte constant vector: the float view carries the values, the long
   long view is the one the whole-object copy reads. */

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec chanChkPos = {{10000.0f, 0.0f, 0.0f, 1.0f}};

static const ConstVec chanWay1Pos = {{-875.0f, 77.0f, -958.0f, 0.0f}};

static const ConstVec chanWay2Pos = {{-264.0f, 1277.0f, -292.0f, 0.0f}};

static const ConstVec tsuroChkPos = {{-123.0f, -72.0f, -945.0f, 0.0f}};

static const EffectArg tsuroEffectPos = {{-1793.0f, 132.0f, -942.0f, 1.0f}};

static const EffectArg tsuroEffect2Pos = {{-2406.0f, 182.0f, -975.0f, 1.0f}};

static const EffectArg tsuroEffect3Pos = {{-1005.0f, 1349.0f, -493.0f, 1.0f}};

static const EffectArg tsuroEffect4Pos = {{-1320.0f, 1346.0f, -806.0f, 1.0f}};

static const EffectArg tsuroEffect5Pos = {{-1885.0f, 1360.0f, -842.0f, 1.0f}};

static const EffectArg tsuroEffect6Pos = {{-1864.0f, 1360.0f, -1106.0f, 1.0f}};

static const EffectArg tsuroEffect7Pos = {{-1327.0f, 1327.0f, -1141.0f, 1.0f}};

static const EffectArg tsuroEffect8Pos = {{-1223.0f, 1325.0f, -1101.0f, 1.0f}};

static const EffectArg tsuroEffect9Pos = {{-1273.0f, 1325.0f, -873.0f, 1.0f}};

extern int bridge;

void actSt07aChanChk(volatile int a0)
{
    long long buf[2];
    float dir[4];
    int hEffect;
    int hMot;
    int hFall;

    while (gflagChk(127) == 0) {
        _ACTWait(1);
    }

    soundSeDefPlay(1313, 0, 0, 1);

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        actCreateSubThread(actSt07aChanWay1, 21);
    }
    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x5000000) != 0) {
        actCreateSubThread(actSt07aChanWay2, 21);
    }

    scpSleepEnemyAll();
    FinishHint(3);

    lt_switch_layout(55);
    D_0063AA08 = 1;

    stage_SetAnimation(355, 1, 0);

    _ACTWait(1);

    ((PObjGObj *)scpSearchGobj(397))->f16C = 0;
    stage_SetAnimation(360, -1, -2);

    while (stage_CheckAnimationFinish(355) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayStart(D_00639EA4);

    if (D_00639EA8 != 0) {
        scpPlayStart(D_00639EA8);
    }

    gflagOn(126);

    while (bridge == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(*(int *)(bridge + 0x2C));

    hEffect = actCreateSubThread(actSt07aChanEffect, 21);

    hMot = actCreateSubThread(actSt07aChanMot, 21);

    hFall = actCreateSubThread(actSt07aChanFall, 21);

    demoEnd = 0;

    while (demoEnd == 0 && ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (demoEnd == 0) {
        scpAdpcmFadeCloseFunc(&bridge, 0xC0);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        iosThreadSetPri(hEffect + 0x24, 34);
        iosThreadSetPri(hMot + 0x24, 34);
        iosThreadSetPri(hFall + 0x24, 34);

        stage_SetAnimation(356, 1, -1);
        scpPlayMot(D_00639EA4, 475);

        DeleteLayoutedCandleParticleEffect();
        _ACTWait(1);

        scpTorchLightOn(431);
        scpTorchLightOn(432);

        SetCameraFlag_GamecamCutBack();
        scpFadeIn(3.0f);
    } else {
        iosThreadSetPri(hEffect + 0x24, 34);
        iosThreadSetPri(hMot + 0x24, 34);
        iosThreadSetPri(hFall + 0x24, 34);
    }

    buf[0] = chanChkPos.d[0];
    buf[1] = chanChkPos.d[1];
    sceVu0SubVector(dir, buf, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpPlayMot(D_00639EA4, 0);

    scpPlayEnd(D_00639EA4);

    if (D_00639EA8 != 0) {
        scpPlayEnd(D_00639EA8);
    }

    D_0063AA08 = 0;
    lt_switch_layout(54);
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

extern int sekizo7a;

void actSt07aTsuroChk(volatile int a0)
{
    long long buf[2];
    int obj;
    int wk;
    int hGirl;
    int hEffect;
    int hConte;

    hGirl = 0;

    while ((obj = scpIsBombExplode(19)) == 0 || scpTriggerBall(a0, obj, 200.0f) == 0) {
        _ACTWait(1);
    }

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        hGirl = actCreateSubThread(actSt07aGirlWay, 21);
    }

    gflagOn(128);

    lt_switch_layout(55);

    D_0063AA08 = 1;
    brainLockGirl();

    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(60, &sekizo7a, 1, 1, 1);
    while (sekizo7a == 0) {
        _ACTWait(1);
    }

    hEffect = actCreateSubThread(actSt07aTsuroEffect, 21);
    hConte = actCreateSubThread(actSt07aTsuroConte, 21);

    demoEnd = 0;
    while (demoEnd == 0 && ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    wk = demoEnd ^ 1;

    if (wk != 0) {
        scpAdpcmFadeCloseFunc(&sekizo7a, 0xC0);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosPadActStopAll();
    iosThreadSetPri(hConte + 0x24, 34);
    iosThreadSetPri(hEffect + 0x24, 34);
    if (hGirl != 0) {
        iosThreadSetPri(hGirl + 0x24, 34);
        _ACTWait(2);
        _SCPMoveCharactorByWay_Cancel(D_00639EA8);
    }

    if (wk != 0) {
        stage_SetAnimation(357, 0, -1);
        stage_SetAnimation(358, 0, -1);
        ReviveAllCarryableItemsWithRandomVelocity(-5.0f, 0.0f);
        _ACTWait(2);

        if (hGirl != 0) {
            buf[0] = tsuroChkPos.d[0];
            buf[1] = tsuroChkPos.d[1];
            SetDirectRootPosition(D_00639EA8, buf);
        }

        SetCameraFlag_GamecamCutBack();
        scpFadeIn(8.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    lt_switch_layout(54);

    D_0063AA08 = 0;
    brainUnlockGirl();

    gflagOn(133);

    scpWakeupEnemyAll();

    SetWayGroupActive(11, 0);
    SetWayGroupActive(12, 0);
    SetWayGroupActive(13, 1);
    SetWayGroupActive(14, 1);
    SetWayGroupActive(15, 1);

    scpTorchLightOff(431);
    scpTorchLightOff(432);
}

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
            b1 = tsuroEffectPos;
            scpEffectStart(&b1, 13);
            b2 = tsuroEffectPos;
            scpEffectStart(&b2, 15);
            break;
        case 438:
            b3 = tsuroEffect2Pos;
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
            b4 = tsuroEffect3Pos;
            scpEffectStart(&b4, 15);
            iosPadActRequest(D_00639EAC, 15);
            break;
        case 510:
            b5 = tsuroEffect4Pos;
            scpEffectStart(&b5, 11);
            b6 = tsuroEffect5Pos;
            scpEffectStart(&b6, 15);
            b7 = tsuroEffect6Pos;
            scpEffectStart(&b7, 15);
            b8 = tsuroEffect7Pos;
            scpEffectStart(&b8, 11);
            break;
        case 560:
            b9 = tsuroEffect8Pos;
            scpEffectStart(&b9, 15);
            b10 = tsuroEffect9Pos;
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

extern int sekizo_7a;
extern int sekizo_7a_vol;
extern unsigned char D_0063BF78;

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

    lt_switch_layout(55);
    D_0063AA08 = 1;

    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(19, &sekizo_7a, 1, 1, 1);
    while (sekizo_7a == 0) {
        _ACTWait(1);
    }

    scpKillEnemyOne(399);
    scpKillEnemyOne(400);
    scpKillEnemyOne(401);
    scpKillEnemyOne(402);
    scpKillEnemyOne(403);
    scpKillEnemyOne(404);
    scpKillEnemyOne(3757);
    scpKillSpiderGroup(405);

    scpMaskGeneratorAll();

    stage_SetAnimation(362, 1, 0);

    ReviveAllCarryableItemsWithNonSleepFrame(250);

    sekizo_7a_vol = iosPadActRequest(D_00639EAC, 9);
    D_0063BF78 = 0x80;
    iosPadActVolumeSet(sekizo_7a_vol, 0x80);

    se = soundSeDefPlay(1217, 0, 0, 1);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 532);

    scpPlayPosSet(D_00639EA4, -3300.0f, 977.0f, -1050.0f);
    scpPlayPosSet(D_00639EA8, -3300.0f, 977.0f, -950.0f);

    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    D_0063AA08 = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpSekizouCheckPoint();

    scpPlayMot(D_00639EA8, 645);
    scpPlayWaitMotEnd(D_00639EA8);

    gflagOn(130);

    soundSeDefStop(se);

    while (stage_CheckAnimationFrame(362, 180, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_7a_vol);

    while (stage_CheckAnimationFinish(362) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA8, 532);
    scpPlayEnd(D_00639EA8);
    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    scpWakeupEnemyAll();

    D_0063AA08 = 0;
    lt_switch_layout(54);
}

static ActMail chanReady_mes[2] = {{430}, {429}};

static ActMail chanChain_mes[2] = {{430}, {429}};

static ActMail chan_mes[2] = {{430}, {429}};

static ActMail tsuro_mes[2] = {{430}, {429}};

static ActMail intro_mes[2] = {{430}, {429}};

static ActMail sekizo_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail ene2_mes[2] = {{430}, {429}};

void actSt07aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    ((PObjGObj *)scpSearchGobj(396))->f16C = 0;

    ((PObjGObj *)scpSearchGobj(408))->f50 = 0;
    ((PObjGObj *)scpSearchGobj(409))->f50 = 0;

    if (gflagChk(131) == 0) {
        ((PObjGObj *)scpSearchGobj(411))->f16C = 0;
        ((PObjGObj *)scpSearchGobj(412))->f16C = 0;
        ((PObjGObj *)scpSearchGobj(413))->f16C = 0;
        ((PObjGObj *)scpSearchGobj(414))->f16C = 0;
        ((PObjGObj *)scpSearchGobj(415))->f16C = 0;
        ((PObjGObj *)scpSearchGobj(416))->f16C = 0;

        ene_mes[0].func = actSt07aEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt07aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(133) == 0 || scpTriggerBall(a0, D_00639EA8, 400.0f) == 0) {
        _ACTWait(1);
    }

    ((PObjGObj *)scpSearchGobj(396))->f16C = 1;

    lt_switch_layout(55);
    D_0063AA08 = 1;

    scpSleepEnemyOne(3757);

    gflagOff(391);

    gflagOn(131);
    gflagOn(132);

    stage_SetAnimation(359, 1, 0);
    SetCameraFlag_LwsCutBack();

    reg_SetScissorSw(1);

    SetStaticBlur(0);

    scpSleepEnemyOne(400);
    scpSleepSpiderGroupOne(0x195);

    while (stage_CheckAnimationFinish(359) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    reg_SetScissorSw(0);

    SetStaticBlur(1);

    lt_switch_layout(54);
    D_0063AA08 = 0;

    ((PObjGObj *)scpSearchGobj(396))->f16C = 0;

    _ACTWait(30);

    scpWakeupEnemyOne(3757);
    scpWakeupEnemyOne(400);
    scpWakeupSpiderGroupOne(0x195);
}

void actSt07aGene1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask((int)scpSearchGobj(410));

    while (gflagChk(132) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_Call((int)scpSearchGobj(410));
}

void actSt07aChan(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(126) != 0) {
        DeleteLayoutedCandleParticleEffect();
        if (gflagChk(128) != 0) {
            scpTorchLightOff(431);
            scpTorchLightOff(432);
        }
    } else {
        scpTorchLightOff(431);
        scpTorchLightOff(432);
        chan_mes[0].func = actSt07aChanChk;
        self->mail = chan_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt07aChanReady(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(126) == 0) {
        chanReady_mes[0].func = actSt07aChanReadyChk;
        self->mail = chanReady_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt07aChanChain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(127) == 0) {
        chanChain_mes[0].func = actSt07aChanChainChk;
        self->mail = chanChain_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        ((PObjGObj *)scpSearchGobj(454))->f16C = 0;
    }
}

void actSt07aTsuro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(128) == 0) {
        tsuro_mes[0].func = actSt07aTsuroChk;
        self->mail = tsuro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        gflagOn(133);
    }
}

void actSt07aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(129) == 0) {
        intro_mes[0].func = actSt07aIntroChk;
        self->mail = intro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt07aSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(130) == 0) {
        stage_SetAnimation(362, 0, 0);
        sekizo_mes[0].func = actSt07aSekizoChk;
        self->mail = sekizo_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(362, 0, -1);
    }
}

void actSt07aGene2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(132) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt07aGene3(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(132) == 0) {
        _ACTWait(1);
    }
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt07aEne2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(134) == 0) {
        ene2_mes[0].func = actSt07aEne2Chk;
        self->mail = ene2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt07aGene2_1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(135) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt07aGene2_2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(135) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt07aGene2_3(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(135) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
}

void actSt07aChanReadyChk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(59, &bridge, 1, 1, 0);
}

void actSt07aChanChainChk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(127) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(454))) {
        case 1:
            if (scpGameStat_BoyWeaponkind() != 0) {
                gflagOn(127);
                soundSeDefPlay(878, 0, 0, 1);
                _ACTWait(30);
                ((PObjGObj *)scpSearchGobj(454))->f16C = 0;
            }
        case 0:
            _ACTWait(1);
            break;
        case 2:
            ((PObjGObj *)scpSearchGobj(454))->f16C = 0;
            gflagOn(127);
            break;
        }
    }
}

void actSt07ChanEvent(int x)
{
    volatile int local = x;
}

void actSt07aChanFall(volatile int a0)
{
    stage_SetAnimation(356, 1, 0);
    _ACTWait(5);
    stage_SetAnimation(355, -1, -2);

    while (stage_CheckAnimationFinish(356) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    DeleteLayoutedCandleParticleEffect();
    _ACTWait(120);
    scpTorchLightOn(431);
    scpTorchLightOn(432);
    _ACTWait(0);
}

void actSt07aChanMot(volatile int a0)
{
    scpPlayMot(D_00639EA4, 474);
    scpPlayWaitMotEnd(D_00639EA4);
    scpPlayMot(D_00639EA4, 475);
    scpPlayWaitMotEnd(D_00639EA4);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt07aChanWay1(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = chanWay1Pos.d[0];
    buf[1] = chanWay1Pos.d[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int)buf, 100.0f, 0);
    _ACTWait(0);
}

void actSt07aChanWay2(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = chanWay2Pos.d[0];
    buf[1] = chanWay2Pos.d[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int)buf, 100.0f, 0);
    _ACTWait(0);
}

void actSt07TsuroEvent(int x)
{
    volatile int local = x;
}

void actSt07aTsuroConte(volatile int a0)
{
    stage_SetAnimation(357, 1, 0);
    stage_SetAnimation(358, 1, 0);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(358) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt07aGirlWay(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = tsuroChkPos.d[0];
    buf[1] = tsuroChkPos.d[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int)buf, 100.0f, 0);
    _ACTWait(0);
}

void actSt07aCamera2(int x)
{
    volatile int local = x;
}

void actSt07aIntroChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    gflagOn(129);

    D_0063AA08 = 1;
    _ACTWait(1);

    stage_SetAnimation(353, 1, 0);
    while (stage_CheckAnimationFinish(353) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);
    D_0063AA08 = 0;
}

void actSt07aSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt07aEne2Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(174) == 0 || scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    gflagOff(391);
    gflagOn(134);
    gflagOn(135);
}
