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

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt07aInit(void)
{
    if (gflagChk(113) != 0) {
        if (gflagChk(114) != 0) {
            SetWayGroupActive(11, 0);
            SetWayGroupActive(12, 0);
#ifdef VERSION_AUG6
            stage_SetAnimation(322, 0, -1);
#else
            stage_SetAnimation(323, 0, -1);
#endif
        } else {
            SetWayGroupActive(13, 0);
            SetWayGroupActive(14, 0);
            SetWayGroupActive(15, 0);
#ifdef VERSION_AUG6
            stage_SetAnimation(321, 0, -1);
#else
            stage_SetAnimation(322, 0, -1);
#endif
        }
    } else {
        SetWayGroupActive(13, 0);
        SetWayGroupActive(14, 0);
        SetWayGroupActive(15, 0);

#ifdef VERSION_AUG6
        stage_SetAnimation(321, 0, 0);
#else
        stage_SetAnimation(322, 0, 0);
#endif
    }
}

void actSt07aEnd(void)
{
    if (girlGObj != 0 && gflagChk(117) == 0 && gflagChk(114) != 0) {
#ifdef VERSION_AUG6
        gflagOn(357);
    }
    if (girlGObj != 0 && gflagChk(120) == 0 && gflagChk(155) != 0) {
        gflagOn(357);
#else
        gflagOn(358);
    }
    if (girlGObj != 0 && gflagChk(120) == 0 && gflagChk(155) != 0) {
        gflagOn(358);
#endif
    }
}
#else
#ifdef VERSION_JUN26
void actSt07aInit(void)
{
    if (gflagChk(109) != 0) {
        if (gflagChk(110) != 0) {
            SetWayGroupActive(11, 0);
            SetWayGroupActive(12, 0);
            stage_SetAnimation(290, 0, -1);
        } else {
            SetWayGroupActive(13, 0);
            SetWayGroupActive(14, 0);
            SetWayGroupActive(15, 0);
            stage_SetAnimation(289, 0, -1);
        }
    } else {
        SetWayGroupActive(13, 0);
        SetWayGroupActive(14, 0);
        SetWayGroupActive(15, 0);

        stage_SetAnimation(289, 0, 0);
    }
}
#else
static void actSt07aChanChainChk(GObj *volatile self);
static void actSt07aChanReadyChk(GObj *volatile self);

void actSt07aInit(void)
{
    if (gflagChk(126) != 0) {
        ((GObj *)scpSearchGobj(397))->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(356, -1, -2);
#else
        stage_SetAnimation(360, -1, -2);
#endif

        FinishHint(3);

        if (gflagChk(128) != 0) {
            SetWayGroupActive(11, 0);
            SetWayGroupActive(12, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(353, 0, -1);
#else
            stage_SetAnimation(357, 0, -1);
#endif
        } else {
            SetWayGroupActive(13, 0);
            SetWayGroupActive(14, 0);
            SetWayGroupActive(15, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(352, 0, -1);
#else
            stage_SetAnimation(356, 0, -1);
#endif
        }
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        scpLinkBGAtoLayoutedTarget(397, 356);
#else
        scpLinkBGAtoLayoutedTarget(397, 360);
#endif

        SetWayGroupActive(13, 0);
        SetWayGroupActive(14, 0);
        SetWayGroupActive(15, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(352, 0, 0);
        stage_SetAnimation(351, 0, 0);
#else
        stage_SetAnimation(356, 0, 0);
        stage_SetAnimation(355, 0, 0);
#endif
    }
}

void actSt07aEnd(void)
{
    if (girlGObj != 0 && gflagChk(131) == 0 && gflagChk(128) != 0) {
        gflagOn(391);
    }
    if (girlGObj != 0 && gflagChk(134) == 0 && gflagChk(174) != 0) {
        gflagOn(391);
    }
}
#endif
#endif

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for. */
static int demoEnd;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec chanChkPos = {{10000.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

#ifdef VERSION_NTSC
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
#endif

#ifdef VERSION_JUN26
/* .sdata: the bridge stream handle (this build has no statue handle or
   shake). */
SqEntry *bridge = 0;

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

    soundSeDefPlay(1260, 0, 0, 1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);

    gflagOn(109);

    _ACTWait(90);

    scpAdpcmPlayRequestFunc(54, &chan, 1, 1, 1);
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
        scpAdpcmFadeClose(chan, 128);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        iosThreadSetPri(&hEffect->thread, 34);
        iosThreadSetPri(&hMot->thread, 34);
        iosThreadSetPri(&hFall->thread, 34);

        stage_SetAnimation(289, 1, -1);
        scpPlayMot(boyGObj, 476);

        DeleteLayoutedCandleParticleEffect();
        _ACTWait(1);

        scpTorchLightOn(378);
        scpTorchLightOn(379);

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
        /* frames with nothing to do.  1 and 410 are the object's own
           compares; its case tree (410 at the root, 300 and 628 below it)
           holds one more value between 354 and 410 and two above 628, and
           aug6's TRFILE puts no code on the block's lines 575..613.  400,
           700 and 800 leave no code: derived values. */
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
#else
#ifdef VERSION_AUG6
/* the nine points actSt07aChanEffect sets its effects at */
static const EffectArg chanEffectPos = {{-1617.0f, -958.0f, -957.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect2Pos = {{-1641.0f, 80.0f, -848.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect3Pos = {{-1669.0f, 73.0f, -765.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect4Pos = {{-1689.0f, 191.0f, -624.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect5Pos = {{-1700.0f, 180.0f, -524.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect6Pos = {{-1745.0f, 106.0f, -632.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect7Pos = {{-1352.0f, 1344.0f, -561.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect8Pos = {{-1411.0f, 1327.0f, -459.15f, 1.0f}}; /* derived name */

static const EffectArg chanEffect9Pos = {{-1562.0f, 1630.0f, 451.15f, 1.0f}}; /* derived name */
#endif

static const ConstVec chanWay1Pos = {{-875.0f, 77.0f, -958.0f, 0.0f}}; /* derived name */

static const ConstVec chanWay2Pos = {{-264.0f, 1277.0f, -292.0f, 0.0f}}; /* derived name */
#endif

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

#ifdef VERSION_JUN26
void actSt07aTsuroChk(GObj *volatile self)
{
    GObj *obj;

    while ((obj = scpIsBombExplode(19)) == 0 || scpTriggerBall(self, obj, 200.0f) == 0) {
        _ACTWait(1);
    }

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        actCreateSubThread(actSt07aGirlWay, 21);
    }

    gflagOn(110);

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    brainLockGirl();

    scpAdpcmPlayRequestFunc(55, &bridge, 1, 1, 1);
    while (bridge == 0) {
        _ACTWait(1);
    }

    actCreateSubThread(actSt07aTsuroEffect, 21);

    stage_SetAnimation(290, 1, 0);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(290) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
    brainUnlockGirl();

    SetWayGroupActive(11, 0);
    SetWayGroupActive(12, 0);
    SetWayGroupActive(13, 1);
    SetWayGroupActive(14, 1);
    SetWayGroupActive(15, 1);

    scpTorchLightOff(378);
    scpTorchLightOff(379);
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

    for (t = 0.0f; t < 600.0f;) {
        switch ((int)t) {
        /* cases in time order, derived: 100 and 180 repeat 480's body,
           which jump2 cross-jumps into one copy (the maps' code-less lines
           between the switch and case 212) */
        case 100:
            iosPadActRequest(boyPad, 17);
            break;
        case 180:
            iosPadActRequest(boyPad, 17);
            break;
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
    }
}

void actSt07aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(110) == 0 || scpTriggerBall(self, girlGObj, 400.0f) == 0) {
        _ACTWait(1);
    }

    ((GObj *)scpSearchGobj(350))->active = 1;

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    gflagOn(113);
    gflagOn(114);

    stage_SetAnimation(291, 1, 0);

    while (stage_CheckAnimationFinish(291) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;

    ((GObj *)scpSearchGobj(350))->active = 0;
}

static ActMail chan_mes[2] = {{377}, {376}}; /* derived name */

static ActMail tsuro_mes[2] = {{377}, {376}}; /* derived name */

static ActMail intro_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

void actSt07aChan(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(109) != 0) {
        DeleteLayoutedCandleParticleEffect();
        if (gflagChk(110) != 0) {
            scpTorchLightOff(378);
            scpTorchLightOff(379);
        }
    } else {
        scpTorchLightOff(378);
        scpTorchLightOff(379);
        chan_mes[0].func = actSt07aChanChk;
        act->mail = chan_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt07aTsuro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(110) == 0) {
        tsuro_mes[0].func = actSt07aTsuroChk;
        act->mail = tsuro_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt07aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(111) == 0) {
        intro_mes[0].func = actSt07aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt07aSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpSekizou(self, 112, 293, 0, 21, -3300.0f, 977.0f, -1050.0f, -3300.0f, 977.0f, -950.0f);
}

void actSt07aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    ((GObj *)scpSearchGobj(350))->active = 0;

    if (gflagChk(113) == 0) {
        ene_mes[0].func = actSt07aEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt07aGene1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(114) == 0) {
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
    while (gflagChk(114) == 0) {
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
    while (gflagChk(114) == 0) {
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
#else
#ifdef VERSION_NTSC
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
#else
/* .sdata: the bridge and statue stream handles and the statue's shake, then
   the shake's volume. */
SqEntry *bridge = 0;

SqEntry *sekizo7a = 0;

#ifdef VERSION_AUG6
int sekizo_7a = 0;

unsigned char sekizo_7a_vol = 0;
#else
SqEntry *sekizo_7a = 0;

int sekizo_7a_vol = 0;

static unsigned char st07a_yure_vol = 0; /* derived name */
#endif

void actSt07aChanChk(GObj *volatile self)
{
    long long buf[2];
    float dir[4];
#ifdef VERSION_AUG6
    SqEntry *chan = 0;
#endif
    GProc *hEffect;
    GProc *hMot;
    GProc *hFall;

#ifdef VERSION_AUG6
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
#else
    while (gflagChk(127) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    soundSeDefPlay(1289, 0, 0, 1);
#else
    soundSeDefPlay(1313, 0, 0, 1);
#endif

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        actCreateSubThread(actSt07aChanWay1, 21);
    }
    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x5000000) != 0) {
        actCreateSubThread(actSt07aChanWay2, 21);
    }

    scpSleepEnemyAll();
#ifdef VERSION_AUG6

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
#else
    FinishHint(3);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(351, 1, 0);
#else
    stage_SetAnimation(355, 1, 0);
#endif

    _ACTWait(1);

    ((GObj *)scpSearchGobj(397))->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(356, -1, -2);
#else
    stage_SetAnimation(360, -1, -2);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(351) == 0) {
#else
    while (stage_CheckAnimationFinish(355) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#endif

    scpPlayStart(boyGObj);

#ifdef VERSION_AUG6
    gflagOn(113);

    _ACTWait(90);

    scpAdpcmPlayRequestFunc(57, &chan, 1, 1, 1);
    while (chan == 0) {
        _ACTWait(1);
    }
#else
    if (girlGObj != 0) {
        scpPlayStart(girlGObj);
    }

    gflagOn(126);

    while (bridge == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(bridge->stream);
#endif

    hEffect = actCreateSubThread(actSt07aChanEffect, 21);

    hMot = actCreateSubThread(actSt07aChanMot, 21);

    hFall = actCreateSubThread(actSt07aChanFall, 21);

    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (demoEnd == 0) {
#ifdef VERSION_AUG6
        scpAdpcmFadeClose(chan, 192);
#else
        scpAdpcmFadeCloseFunc(&bridge, 192);
#endif
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        iosThreadSetPri(&hEffect->thread, 34);
        iosThreadSetPri(&hMot->thread, 34);
        iosThreadSetPri(&hFall->thread, 34);

#ifdef VERSION_AUG6
        stage_SetAnimation(321, 1, -1);
        scpPlayMot(boyGObj, 465);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(352, 1, -1);
#else
        stage_SetAnimation(356, 1, -1);
#endif
        scpPlayMot(boyGObj, 475);
#endif

        DeleteLayoutedCandleParticleEffect();
        _ACTWait(1);

#ifdef VERSION_AUG6
        scpTorchLightOn(393);
        scpTorchLightOn(394);

#else
        scpTorchLightOn(431);
        scpTorchLightOn(432);

        SetCameraFlag_GamecamCutBack();
#endif
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

#ifdef VERSION_AUG6
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
#else
    if (girlGObj != 0) {
        scpPlayEnd(girlGObj);
    }

    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
#endif
    scpWakeupEnemyAll();
}

void actSt07aChanEffect(GObj *volatile self)
{
#ifdef VERSION_AUG6
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
#endif
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
#ifdef VERSION_AUG6
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
#else
        case 154:
#endif
            iosPadActRequest(boyPad, 15);
            ReviveAllCarryableItemsWithRandomVelocity(-5.0f, 0.0f);
            break;
#ifdef VERSION_AUG6
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
        /* frames with nothing to do.  1 and 410 are the object's own
           compares; its case tree (410 at the root, 300 and 628 below it)
           holds one more value between 354 and 410 and two above 628, and
           aug6's TRFILE puts no code on the block's lines 575..613.  400,
           700 and 800 leave no code: derived values. */
        case 1:
        case 400:
        case 410:
        case 700:
        case 800:
#else
        case 84:
        case 210:
            iosPadActRequest(boyPad, 17);
            break;
        case 420:
            iosPadActRequest(boyPad, 15);
            break;
        case 434:
            iosPadActRequest(boyPad, 16);
            break;
        case 574:
            iosPadActRequest(boyPad, 17);
            break;
        case 0:
        case 112:
        case 300:
#endif
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

#ifdef VERSION_AUG6
    gflagOn(114);

    lt_switch_layout(51);
#else
    gflagOn(128);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
#endif

    scpBoyControlReadDisable = 1;
    brainLockGirl();

    scpSleepEnemyAll();

#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(58, &bridge, 1, 1, 1);
    while (bridge == 0) {
#else
    scpAdpcmPlayRequestFunc(60, &sekizo7a, 1, 1, 1);
    while (sekizo7a == 0) {
#endif
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
#ifdef VERSION_AUG6
        scpAdpcmFadeClose(bridge, 192);
#else
        scpAdpcmFadeCloseFunc(&sekizo7a, 192);
#endif
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(353, 0, -1);
        stage_SetAnimation(354, 0, -1);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(322, 0, -1);
        stage_SetAnimation(323, 0, -1);
#else
        stage_SetAnimation(357, 0, -1);
        stage_SetAnimation(358, 0, -1);
#endif
#endif
        ReviveAllCarryableItemsWithRandomVelocity(-5.0f, 0.0f);
        _ACTWait(2);

        if (hGirl != 0) {
            buf[0] = tsuroChkPos.d[0];
            buf[1] = tsuroChkPos.d[1];
            SetDirectRootPosition(girlGObj, buf);
        }

        SetCameraFlag_GamecamCutBack();
#ifdef VERSION_AUG6
        scpFadeIn(3.0f);
    }

    lt_switch_layout(50);
#else
        scpFadeIn(8.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
#endif

    scpBoyControlReadDisable = 0;
    brainUnlockGirl();

#ifdef VERSION_AUG6
    gflagOn(119);
#else
    gflagOn(133);
#endif

    scpWakeupEnemyAll();

    SetWayGroupActive(11, 0);
    SetWayGroupActive(12, 0);
    SetWayGroupActive(13, 1);
    SetWayGroupActive(14, 1);
    SetWayGroupActive(15, 1);

#ifdef VERSION_AUG6
    scpTorchLightOff(393);
    scpTorchLightOff(394);
#else
    scpTorchLightOff(431);
    scpTorchLightOff(432);
#endif
}
#endif

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

#ifdef VERSION_NTSC
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
#else
#ifdef VERSION_AUG6
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

    scpAdpcmPlayRequestFunc(18, &sekizo7a, 1, 1, 1);
    while (sekizo7a == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    _ACTWait(60);

    scpKillEnemyOne(362);
    scpKillEnemyOne(363);
    scpKillEnemyOne(364);
    scpKillEnemyOne(365);
    scpKillEnemyOne(366);
    scpKillEnemyOne(367);
    scpKillEnemyOne(3415);
    scpKillSpiderGroup(368);

    scpMaskGeneratorAll();

    stage_SetAnimation(326, 1, 0);

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

    scpPlayMot(girlGObj, 573);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(116);

    soundSeDefStop(se);

    while (stage_CheckAnimationFrame(326, 180, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_7a);

    while (stage_CheckAnimationFinish(326) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(girlGObj, 514);
    scpPlayEnd(girlGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

static ActMail chan_mes[2] = {{393}, {392}}; /* derived name */

static ActMail tsuro_mes[2] = {{393}, {392}}; /* derived name */

static ActMail intro_mes[2] = {{393}, {392}}; /* derived name */

static ActMail sekizo_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene2_mes[2] = {{393}, {392}}; /* derived name */
#else
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

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    scpKillEnemyOne(3734);
#else
    scpKillEnemyOne(3757);
#endif
    scpKillSpiderGroup(405);

    scpMaskGeneratorAll();

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(358, 1, 0);
#else
    stage_SetAnimation(362, 1, 0);
#endif

    ReviveAllCarryableItemsWithNonSleepFrame(250);

    sekizo_7a_vol = iosPadActRequest(boyPad, 9);
    st07a_yure_vol = 128;
    iosPadActVolumeSet(sekizo_7a_vol, 128);

    se = soundSeDefPlay(1217, 0, 0, 1);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 532);

    scpPlayPosSet(boyGObj, -3300.0f, 977.0f, -1050.0f);
    scpPlayPosSet(girlGObj, -3300.0f, 977.0f, -950.0f);

    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpBoyControlReadDisable = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpSekizouCheckPoint();

    scpPlayMot(girlGObj, 645);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(130);

    soundSeDefStop(se);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(358, 180, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(362, 180, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_7a_vol);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(358) == 0) {
#else
    while (stage_CheckAnimationFinish(362) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(girlGObj, 532);
    scpPlayEnd(girlGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}

static ActMail chanReady_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chanChain_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chan_mes[2] = {{430}, {429}}; /* derived name */

static ActMail tsuro_mes[2] = {{430}, {429}}; /* derived name */

static ActMail intro_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene2_mes[2] = {{430}, {429}}; /* derived name */
#endif

void actSt07aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    ((GObj *)scpSearchGobj(360))->active = 0;

    if (gflagChk(117) == 0) {
        ((GObj *)scpSearchGobj(373))->active = 0;
        ((GObj *)scpSearchGobj(374))->active = 0;
        ((GObj *)scpSearchGobj(375))->active = 0;
        ((GObj *)scpSearchGobj(376))->active = 0;
        ((GObj *)scpSearchGobj(377))->active = 0;
        ((GObj *)scpSearchGobj(378))->active = 0;
#else
    ((GObj *)scpSearchGobj(396))->active = 0;

    ((GObj *)scpSearchGobj(408))->drawMask = 0;
    ((GObj *)scpSearchGobj(409))->drawMask = 0;

    if (gflagChk(131) == 0) {
        ((GObj *)scpSearchGobj(411))->active = 0;
        ((GObj *)scpSearchGobj(412))->active = 0;
        ((GObj *)scpSearchGobj(413))->active = 0;
        ((GObj *)scpSearchGobj(414))->active = 0;
        ((GObj *)scpSearchGobj(415))->active = 0;
        ((GObj *)scpSearchGobj(416))->active = 0;
#endif

        ene_mes[0].func = actSt07aEneChk;
        act->mail = ene_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt07aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

#ifdef VERSION_AUG6
    while (gflagChk(119) == 0 || scpTriggerBall(self, girlGObj, 400.0f) == 0) {
#else
    while (gflagChk(133) == 0 || scpTriggerBall(self, girlGObj, 400.0f) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    ((GObj *)scpSearchGobj(360))->active = 1;

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpSleepEnemyOne(3415);

    gflagOff(357);

    gflagOn(117);
    gflagOn(118);

    stage_SetAnimation(324, 1, 0);
#else
    ((GObj *)scpSearchGobj(396))->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    scpSleepEnemyOne(3734);
#else
    scpSleepEnemyOne(3757);
#endif

    gflagOff(391);

    gflagOn(131);
    gflagOn(132);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(355, 1, 0);
#else
    stage_SetAnimation(359, 1, 0);
#endif
#endif
    SetCameraFlag_LwsCutBack();

    reg_SetScissorSw(1);

    SetStaticBlur(0);

#ifdef VERSION_AUG6
    scpSleepEnemyOne(363);
    scpSleepSpiderGroupOne(368);

    while (stage_CheckAnimationFinish(324) == 0) {
#else
    scpSleepEnemyOne(400);
    scpSleepSpiderGroupOne(405);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(355) == 0) {
#else
    while (stage_CheckAnimationFinish(359) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    reg_SetScissorSw(0);

    SetStaticBlur(1);

#ifdef VERSION_AUG6
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;

    ((GObj *)scpSearchGobj(360))->active = 0;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;

    ((GObj *)scpSearchGobj(396))->active = 0;
#endif

    _ACTWait(30);

#ifdef VERSION_AUG6
    scpWakeupEnemyOne(3415);
    scpWakeupEnemyOne(363);
    scpWakeupSpiderGroupOne(368);
}

void actSt07aChan(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(113) != 0) {
        DeleteLayoutedCandleParticleEffect();
        if (gflagChk(114) != 0) {
            scpTorchLightOff(393);
            scpTorchLightOff(394);
        }
    } else {
        scpTorchLightOff(393);
        scpTorchLightOff(394);
        chan_mes[0].func = actSt07aChanChk;
        act->mail = chan_mes;
        ACTSendMailCorrect(self, 393);
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
        ACTSendMailCorrect(self, 393);
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
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt07aSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(116) == 0) {
        stage_SetAnimation(326, 0, 0);
        sekizo_mes[0].func = actSt07aSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(326, 0, -1);
    }
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    scpWakeupEnemyOne(3734);
#else
    scpWakeupEnemyOne(3757);
#endif
    scpWakeupEnemyOne(400);
    scpWakeupSpiderGroupOne(405);
#endif
}

void actSt07aGene1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(118) == 0) {
#else
    Generator_Mask(scpSearchGobj(410));

    while (gflagChk(132) == 0) {
#endif
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
#ifndef VERSION_AUG6
    Generator_Call(scpSearchGobj(410));
}

void actSt07aChan(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

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
        act->mail = chan_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt07aChanReady(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(126) == 0) {
        chanReady_mes[0].func = actSt07aChanReadyChk;
        act->mail = chanReady_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt07aChanChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(127) == 0) {
        chanChain_mes[0].func = actSt07aChanChainChk;
        act->mail = chanChain_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        ((GObj *)scpSearchGobj(454))->active = 0;
    }
}

void actSt07aTsuro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(128) == 0) {
        tsuro_mes[0].func = actSt07aTsuroChk;
        act->mail = tsuro_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        gflagOn(133);
    }
}

void actSt07aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(129) == 0) {
        intro_mes[0].func = actSt07aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt07aSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(130) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(358, 0, 0);
#else
        stage_SetAnimation(362, 0, 0);
#endif
        sekizo_mes[0].func = actSt07aSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(358, 0, -1);
#else
        stage_SetAnimation(362, 0, -1);
#endif
    }
#endif
}

void actSt07aGene2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
#ifdef VERSION_AUG6
    while (gflagChk(118) == 0) {
#else
    while (gflagChk(132) == 0) {
#endif
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
#ifdef VERSION_AUG6
    while (gflagChk(118) == 0) {
#else
    while (gflagChk(132) == 0) {
#endif
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

#ifdef VERSION_AUG6
    if (gflagChk(120) == 0) {
        ene2_mes[0].func = actSt07aEne2Chk;
        act->mail = ene2_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(134) == 0) {
        ene2_mes[0].func = actSt07aEne2Chk;
        act->mail = ene2_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt07aGene2_1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
#ifdef VERSION_AUG6
    while (gflagChk(121) == 0) {
#else
    while (gflagChk(135) == 0) {
#endif
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
#ifdef VERSION_AUG6
    while (gflagChk(121) == 0) {
#else
    while (gflagChk(135) == 0) {
#endif
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
#ifdef VERSION_AUG6
    while (gflagChk(121) == 0) {
#else
    while (gflagChk(135) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
#ifndef VERSION_AUG6
}

static void actSt07aChanReadyChk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(59, &bridge, 1, 1, 0);
}

static void actSt07aChanChainChk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(127) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(454))) {
        case 1:
            if (scpGameStat_BoyWeaponkind() != 0) {
                gflagOn(127);
                soundSeDefPlay(878, 0, 0, 1);
                _ACTWait(30);
                ((GObj *)scpSearchGobj(454))->active = 0;
            }
        case 0:
            _ACTWait(1);
            break;
        case 2:
            ((GObj *)scpSearchGobj(454))->active = 0;
            gflagOn(127);
            break;
        }
    }
#endif
}
#endif
#endif

void actSt07ChanEvent(int x)
{
    volatile int local = x;
}

#ifdef VERSION_JUN26
void actSt07aChanFall(GObj *volatile self)
{
    stage_SetAnimation(289, 1, 0);

    while (stage_CheckAnimationFinish(289) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    DeleteLayoutedCandleParticleEffect();
    _ACTWait(120);
    scpTorchLightOn(378);
    scpTorchLightOn(379);
    _ACTWait(0);
}

void actSt07aChanMot(GObj *volatile self)
{
    scpPlayMot(boyGObj, 475);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 476);
    scpPlayWaitMotEnd(boyGObj);

    demoEnd = 1;
    _ACTWait(0);
}
#else
#ifdef VERSION_NTSC
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
#else
void actSt07aChanFall(GObj *volatile self)
{
#ifdef VERSION_AUG6
    stage_SetAnimation(321, 1, 0);

    while (stage_CheckAnimationFinish(321) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(352, 1, 0);
#else
    stage_SetAnimation(356, 1, 0);
#endif
    _ACTWait(5);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(351, -1, -2);
#else
    stage_SetAnimation(355, -1, -2);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(352) == 0) {
#else
    while (stage_CheckAnimationFinish(356) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    DeleteLayoutedCandleParticleEffect();
    _ACTWait(120);
#ifdef VERSION_AUG6
    scpTorchLightOn(393);
    scpTorchLightOn(394);
#else
    scpTorchLightOn(431);
    scpTorchLightOn(432);
#endif
    _ACTWait(0);
}

void actSt07aChanMot(GObj *volatile self)
{
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 464);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 465);
#else
    scpPlayMot(boyGObj, 474);
    scpPlayWaitMotEnd(boyGObj);
    scpPlayMot(boyGObj, 475);
#endif
    scpPlayWaitMotEnd(boyGObj);

    demoEnd = 1;
    _ACTWait(0);
}
#endif

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
#endif

void actSt07TsuroEvent(int x)
{
    volatile int local = x;
}

#ifdef VERSION_NTSC
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
#else
#ifndef VERSION_JUN26
void actSt07aTsuroConte(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(353, 1, 0);
    stage_SetAnimation(354, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(322, 1, 0);
    stage_SetAnimation(323, 1, 0);
#else
    stage_SetAnimation(357, 1, 0);
    stage_SetAnimation(358, 1, 0);
#endif
#endif

    SetCameraFlag_LwsCutBack();

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(354) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(323) == 0) {
#else
    while (stage_CheckAnimationFinish(358) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}
#endif
#endif

void actSt07aGirlWay(volatile unsigned int self)
{
    long long buf[2];
    buf[0] = tsuroChkPos.d[0];
    buf[1] = tsuroChkPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
#ifndef VERSION_JUN26
    _ACTWait(0);
#endif
}

void actSt07aCamera2(int x)
{
    volatile int local = x;
}

#ifdef VERSION_NTSC
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
#else
void actSt07aIntroChk(GObj *volatile self)
{
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    lt_switch_layout(51);
    gflagOn(115);
#else
#ifdef VERSION_JUN26
    lt_switch_layout(51);
    gflagOn(111);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    gflagOn(129);
#endif
#endif

    scpBoyControlReadDisable = 1;
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(349, 1, 0);
    while (stage_CheckAnimationFinish(349) == 0) {
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(319, 1, 0);
    while (stage_CheckAnimationFinish(319) == 0) {
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(287, 1, 0);
    while (stage_CheckAnimationFinish(287) == 0) {
#else
    stage_SetAnimation(353, 1, 0);
    while (stage_CheckAnimationFinish(353) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif
    scpBoyControlReadDisable = 0;
}
#endif

void actSt07aSekizoEvent(int x)
{
    volatile int local = x;
}

#ifdef VERSION_NTSC
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
#else
#ifndef VERSION_JUN26
void actSt07aEne2Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

#ifdef VERSION_AUG6
    while (gflagChk(155) == 0 || scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
#else
    while (gflagChk(174) == 0 || scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOff(357);
    gflagOn(120);
    gflagOn(121);
#else
    gflagOff(391);
    gflagOn(134);
    gflagOn(135);
#endif
}
#endif
#endif
