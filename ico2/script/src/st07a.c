#include "st07a.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
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
#include "main.h"

void actSt07aInit(void)
{
    if (gflagChk(113) != 0) {
        if (gflagChk(114) != 0) {
            SetWayGroupActive(11, 0);
            SetWayGroupActive(12, 0);
            stage_SetAnimation(323, 0, -1);
        } else {
            SetWayGroupActive(13, 0);
            SetWayGroupActive(14, 0);
            SetWayGroupActive(15, 0);
            stage_SetAnimation(322, 0, -1);
        }
    } else {
        SetWayGroupActive(13, 0);
        SetWayGroupActive(14, 0);
        SetWayGroupActive(15, 0);

        stage_SetAnimation(322, 0, 0);
    }
}

void actSt07aEnd(void)
{
    if (girlGObj != 0 && gflagChk(117) == 0 && gflagChk(114) != 0) {
        gflagOn(358);
    }
    if (girlGObj != 0 && gflagChk(120) == 0 && gflagChk(155) != 0) {
        gflagOn(358);
    }
}

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for. */
static int demoEnd;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec chanChkPos = {{10000.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

/* .sdata: the bridge and statue stream handles, the statue's shake and the
   shake's volume. */
SqEntry *bridge = 0;

SqEntry *sekizo7a = 0;

int sekizo_7a = 0;

unsigned char sekizo_7a_vol = 0;

void actSt07aChanChk(GObj *volatile self)
{
    long long buf[2];
    float dir[4];
    SqEntry *chan = 0;
    GProc *hEffect;
    GProc *hMot;
    GProc *hFall;

    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    soundSeDefPlay(1289, 0, 0, 1);

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        actCreateSubThread(actSt07aChanWay1, 21);
    }
    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x5000000) != 0) {
        actCreateSubThread(actSt07aChanWay2, 21);
    }

    scpSleepEnemyAll();

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);

    gflagOn(113);

    _ACTWait(90);

    scpAdpcmPlayRequestFunc(57, &chan, 1, 1, 1);
    while (chan == 0) {
        _ACTWait(1);
    }

    hEffect = actCreateSubThread(actSt07aChanEffect, 21);

    hMot = actCreateSubThread(actSt07aChanMot, 21);

    hFall = actCreateSubThread(actSt07aChanFall, 21);

    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (demoEnd == 0) {
        scpAdpcmFadeClose(chan, 192);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        iosThreadSetPri(&hEffect->thread, 34);
        iosThreadSetPri(&hMot->thread, 34);
        iosThreadSetPri(&hFall->thread, 34);

        stage_SetAnimation(322, 1, -1);
        scpPlayMot(boyGObj, 465);

        DeleteLayoutedCandleParticleEffect();
        _ACTWait(1);

        scpTorchLightOn(394);
        scpTorchLightOn(395);

        scpFadeIn(3.0f);
    } else {
        iosThreadSetPri(&hEffect->thread, 34);
        iosThreadSetPri(&hMot->thread, 34);
        iosThreadSetPri(&hFall->thread, 34);
    }

    buf[0] = chanChkPos.d[0];
    buf[1] = chanChkPos.d[1];
    sceVu0SubVector(dir, buf, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpPlayMot(boyGObj, 0);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    scpWakeupEnemyAll();
}

static const EffectArg chanEffectPos = {{-1617.0f, -958.0f, -957.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect2Pos = {{-1641.0f, 80.0f, -848.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect3Pos = {{-1669.0f, 73.0f, -765.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect4Pos = {{-1689.0f, 191.0f, -624.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect5Pos = {{-1700.0f, 180.0f, -524.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect6Pos = {{-1745.0f, 106.0f, -632.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect7Pos = {{-1352.0f, 1344.0f, -561.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect8Pos = {{-1411.0f, 1327.0f, -459.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect9Pos = {{-1562.0f, 1630.0f, 451.15f, 1.0f}}; /* derived name */

void actSt07aChanEffect(GObj *volatile self)
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
        case 250:
            b1 = chanEffectPos;
            scpEffectStart(&b1, 16);
            b2 = chanEffectPos;
            scpEffectStart(&b2, 11);
            break;
        case 300:
            iosPadActRequest(boyPad, 17);
            break;
        case 354:
            b3 = chanEffect2Pos;
            scpEffectStart(&b3, 14);
            b4 = chanEffect3Pos;
            scpEffectStart(&b4, 15);
            iosPadActRequest(boyPad, 15);
            ReviveAllCarryableItemsWithRandomVelocity(-5.0f, 0.0f);
            break;
        case 500:
            b5 = chanEffect4Pos;
            scpEffectStart(&b5, 16);
            b6 = chanEffect5Pos;
            scpEffectStart(&b6, 15);
            b7 = chanEffect6Pos;
            scpEffectStart(&b7, 14);
            break;
        case 598:
            b8 = chanEffect7Pos;
            scpEffectStart(&b8, 15);
            b9 = chanEffect8Pos;
            scpEffectStart(&b9, 14);
            break;
        case 628:
            b10 = chanEffect9Pos;
            scpEffectStart(&b10, 15);
            iosPadActRequest(boyPad, 16);
            break;
        /* frames with nothing to do.  Cases 1 and 410 are pinned by their
           compares; the case tree's split points (410 at the root, 300 and
           628 below it) pin at least one more empty case between 354 and
           410 and two above 628, and aug6's TRFILE puts no code on this
           function's lines 575..613, where the block sits.  The values
           leave no code, so 400, 700 and 800 are not pinned. */
        case 1:
        case 400:
        case 410:
        case 700:
        case 800:
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 1600.0f);
    _ACTWait(0);
}

static const ConstVec chanWay1Pos = {{-875.0f, 77.0f, -958.0f, 0.0f}}; /* derived name */

static const ConstVec chanWay2Pos = {{-264.0f, 1277.0f, -292.0f, 0.0f}}; /* derived name */

static const ConstVec tsuroChkPos = {{-123.0f, -72.0f, -945.0f, 0.0f}}; /* derived name */

static const EffectArg tsuroEffectPos = {{-1793.0f, 132.0f, -942.0f, 1.0f}}; /* derived name */

static const EffectArg tsuroEffect2Pos = {{-2406.0f, 182.0f, -975.0f, 1.0f}}; /* derived name */

static const EffectArg tsuroEffect3Pos = {{-1005.0f, 1349.0f, -493.0f, 1.0f}}; /* derived name */

static const EffectArg tsuroEffect4Pos = {{-1320.0f, 1346.0f, -806.0f, 1.0f}}; /* derived name */

static const EffectArg tsuroEffect5Pos = {{-1885.0f, 1360.0f, -842.0f, 1.0f}}; /* derived name */

static const EffectArg tsuroEffect6Pos = {{-1864.0f, 1360.0f, -1106.0f, 1.0f}}; /* derived name */

static const EffectArg tsuroEffect7Pos = {{-1327.0f, 1327.0f, -1141.0f, 1.0f}}; /* derived name */

static const EffectArg tsuroEffect8Pos = {{-1223.0f, 1325.0f, -1101.0f, 1.0f}}; /* derived name */

static const EffectArg tsuroEffect9Pos = {{-1273.0f, 1325.0f, -873.0f, 1.0f}}; /* derived name */

void actSt07aTsuroChk(GObj *volatile self)
{
    long long buf[2];
    GObj *obj;
    int wk;
    GProc *hGirl;
    GProc *hEffect;
    GProc *hConte;

    hGirl = 0;

    while ((obj = scpIsBombExplode(19)) == 0 || scpTriggerBall(self, obj, 200.0f) == 0) {
        _ACTWait(1);
    }

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        hGirl = actCreateSubThread(actSt07aGirlWay, 21);
    }

    gflagOn(114);

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    brainLockGirl();

    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(58, &bridge, 1, 1, 1);
    while (bridge == 0) {
        _ACTWait(1);
    }

    hEffect = actCreateSubThread(actSt07aTsuroEffect, 21);
    hConte = actCreateSubThread(actSt07aTsuroConte, 21);

    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    wk = demoEnd ^ 1;

    if (wk != 0) {
        scpAdpcmFadeClose(bridge, 192);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosPadActStopAll();
    iosThreadSetPri(&hConte->thread, 34);
    iosThreadSetPri(&hEffect->thread, 34);
    if (hGirl != 0) {
        iosThreadSetPri(&hGirl->thread, 34);
        _ACTWait(2);
        _SCPMoveCharactorByWay_Cancel(girlGObj);
    }

    if (wk != 0) {
        stage_SetAnimation(323, 0, -1);
        stage_SetAnimation(324, 0, -1);
        ReviveAllCarryableItemsWithRandomVelocity(-5.0f, 0.0f);
        _ACTWait(2);

        if (hGirl != 0) {
            buf[0] = tsuroChkPos.d[0];
            buf[1] = tsuroChkPos.d[1];
            SetDirectRootPosition(girlGObj, buf);
        }

        SetCameraFlag_GamecamCutBack();
        scpFadeIn(3.0f);
    }

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
    brainUnlockGirl();

    gflagOn(119);

    scpWakeupEnemyAll();

    SetWayGroupActive(11, 0);
    SetWayGroupActive(12, 0);
    SetWayGroupActive(13, 1);
    SetWayGroupActive(14, 1);
    SetWayGroupActive(15, 1);

    scpTorchLightOff(394);
    scpTorchLightOff(395);
}

void actSt07aTsuroEffect(GObj *volatile self)
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
            iosPadActRequest(boyPad, 16);
            break;
        case 100:
        case 180:
        case 480:
            iosPadActRequest(boyPad, 17);
            break;
        case 505:
            ReviveAllCarryableItemsWithRandomVelocity(-5.0f, 0.0f);
            b4 = tsuroEffect3Pos;
            scpEffectStart(&b4, 15);
            iosPadActRequest(boyPad, 15);
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
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 600.0f);
    _ACTWait(0);
}

void actSt07aSekizoChk(GObj *volatile self)
{
    /* the SE handle, which the sound subsystem owns (st13c's
       actSt13cSekizoChk keeps one the same way) */
    volatile int se;
    float dir[4];

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 ||
           scpTriggerBall(self, girlGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(18, &sekizo7a, 1, 1, 1);
    while (sekizo7a == 0) {
        _ACTWait(1);
    }

    _ACTWait(60);

    scpKillEnemyOne(363);
    scpKillEnemyOne(364);
    scpKillEnemyOne(365);
    scpKillEnemyOne(366);
    scpKillEnemyOne(367);
    scpKillEnemyOne(368);
    scpKillEnemyOne(3453);
    scpKillSpiderGroup(369);

    scpMaskGeneratorAll();

    stage_SetAnimation(327, 1, 0);

    ReviveAllCarryableItemsWithNonSleepFrame(250);

    sekizo_7a = iosPadActRequest(boyPad, 9);
    sekizo_7a_vol = 128;
    iosPadActVolumeSet(sekizo_7a, 128);

    se = soundSeDefPlay(1193, 0, 0, 1);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    scpPlayPosSet(boyGObj, -3300.0f, 977.0f, -1050.0f);
    scpPlayPosSet(girlGObj, -3300.0f, 977.0f, -950.0f);

    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpBoyControlReadDisable = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpSekizouCheckPoint();

    scpPlayMot(girlGObj, 572);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(116);

    soundSeDefStop(se);

    while (stage_CheckAnimationFrame(327, 180, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_7a);

    while (stage_CheckAnimationFinish(327) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(girlGObj, 514);
    scpPlayEnd(girlGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

static ActMail chan_mes[2] = {{397}, {396}}; /* derived name */

static ActMail tsuro_mes[2] = {{397}, {396}}; /* derived name */

static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene2_mes[2] = {{397}, {396}}; /* derived name */

void actSt07aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    ((GObj *)scpSearchGobj(361))->active = 0;

    ((GObj *)scpSearchGobj(372))->drawMask = 0;
    ((GObj *)scpSearchGobj(373))->drawMask = 0;

    if (gflagChk(117) == 0) {
        ((GObj *)scpSearchGobj(374))->active = 0;
        ((GObj *)scpSearchGobj(375))->active = 0;
        ((GObj *)scpSearchGobj(376))->active = 0;
        ((GObj *)scpSearchGobj(377))->active = 0;
        ((GObj *)scpSearchGobj(378))->active = 0;
        ((GObj *)scpSearchGobj(379))->active = 0;

        ene_mes[0].func = actSt07aEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt07aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(119) == 0 || scpTriggerBall(self, girlGObj, 400.0f) == 0) {
        _ACTWait(1);
    }

    ((GObj *)scpSearchGobj(361))->active = 1;

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpSleepEnemyOne(3453);

    gflagOff(358);

    gflagOn(117);
    gflagOn(118);

    stage_SetAnimation(325, 1, 0);
    SetCameraFlag_LwsCutBack();

    reg_SetScissorSw(1);

    SetStaticBlur(0);

    scpSleepEnemyOne(364);
    scpSleepSpiderGroupOne(369);

    while (stage_CheckAnimationFinish(325) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    reg_SetScissorSw(0);

    SetStaticBlur(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;

    ((GObj *)scpSearchGobj(361))->active = 0;

    _ACTWait(30);

    scpWakeupEnemyOne(3453);
    scpWakeupEnemyOne(364);
    scpWakeupSpiderGroupOne(369);
}

void actSt07aChan(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(113) != 0) {
        DeleteLayoutedCandleParticleEffect();
        if (gflagChk(114) != 0) {
            scpTorchLightOff(394);
            scpTorchLightOff(395);
        }
    } else {
        scpTorchLightOff(394);
        scpTorchLightOff(395);
        chan_mes[0].func = actSt07aChanChk;
        act->mail = chan_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt07aTsuro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(114) == 0) {
        tsuro_mes[0].func = actSt07aTsuroChk;
        act->mail = tsuro_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        gflagOn(119);
    }
}

void actSt07aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(115) == 0) {
        intro_mes[0].func = actSt07aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt07aSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(116) == 0) {
        stage_SetAnimation(327, 0, 0);
        sekizo_mes[0].func = actSt07aSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(327, 0, -1);
    }
}

void actSt07aGene1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(118) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt07aGene2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(118) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt07aGene3(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(118) == 0) {
        _ACTWait(1);
    }
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt07aEne2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(120) == 0) {
        ene2_mes[0].func = actSt07aEne2Chk;
        act->mail = ene2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt07aGene2_1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(121) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt07aGene2_2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(121) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt07aGene2_3(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(121) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
}

void actSt07ChanEvent(int x)
{
    volatile int local = x;
}

void actSt07aChanFall(GObj *volatile self)
{
    stage_SetAnimation(322, 1, 0);

    while (stage_CheckAnimationFinish(322) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    DeleteLayoutedCandleParticleEffect();
    _ACTWait(120);
    scpTorchLightOn(394);
    scpTorchLightOn(395);
    _ACTWait(0);
}

void actSt07aChanMot(GObj *volatile self)
{
    scpPlayMot(boyGObj, 464);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 465);
    scpPlayWaitMotEnd(boyGObj);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt07aChanWay1(volatile unsigned int self)
{
    long long buf[2];
    buf[0] = chanWay1Pos.d[0];
    buf[1] = chanWay1Pos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
    _ACTWait(0);
}

void actSt07aChanWay2(volatile unsigned int self)
{
    long long buf[2];
    buf[0] = chanWay2Pos.d[0];
    buf[1] = chanWay2Pos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
    _ACTWait(0);
}

void actSt07TsuroEvent(int x)
{
    volatile int local = x;
}

void actSt07aTsuroConte(GObj *volatile self)
{
    stage_SetAnimation(323, 1, 0);
    stage_SetAnimation(324, 1, 0);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(324) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt07aGirlWay(volatile unsigned int self)
{
    long long buf[2];
    buf[0] = tsuroChkPos.d[0];
    buf[1] = tsuroChkPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
    _ACTWait(0);
}

void actSt07aCamera2(int x)
{
    volatile int local = x;
}

void actSt07aIntroChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    gflagOn(115);

    scpBoyControlReadDisable = 1;
    _ACTWait(1);

    stage_SetAnimation(320, 1, 0);
    while (stage_CheckAnimationFinish(320) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt07aSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt07aEne2Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(155) == 0 || scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    gflagOff(358);
    gflagOn(120);
    gflagOn(121);
}
