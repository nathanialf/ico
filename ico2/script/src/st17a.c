#include "st17a.h"
#include "layout_texture.h"
#include "pad.h"
#include "debug.h"
#include "obj_manager.h"
#include "lws_kyomi.h"
#include "s_init.h"
#include "act-game.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "act.h"
#include "e3.h"
#include "typedef.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static ActMail linkTest_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorInit_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorUpChk_mes[2] = {{397}, {396}}; /* derived name */

/* actSt17aDoorDownChk's record */
static ActMail door_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hasi_mes[2] = {{397}, {396}}; /* derived name */

static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */

static const ConstVec doorChkSePos = {{6646.0f, -2157.0f, 1102.0f, 0.0f}}; /* derived name */

static const ConstVec doorUpEffectPos = {{6690.0f, -2000.0f, 1100.0f, 1.0f}}; /* derived name */

static const ConstVec doorDownEffectPos = {{6690.0f, -2300.0f, 1100.0f, 1.0f}}; /* derived name */

static const ConstVec doorDownEffect2Pos = {{6600.0f, -2000.0f, 1100.0f, 1.0f}}; /* derived name */

static const ConstVec hasiChkSePos = {{3587.0f, -2072.0f, 1124.0f, 0.0f}}; /* derived name */

static const ConstVec hasiChkGirlDir = {{10000.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

static const ConstVec hasiChkGirlWay = {{3830.0f, -2072.0f, 1113.0f, 0.0f}}; /* derived name */

void actSt17aDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(30) == 0) {
        stage_SetLoopFlag(111, 1);
        stage_SetAnimation(111, 1, 0);

        doorInit_mes[0].func = actSt17aDoorUpChk;
        act->mail = doorInit_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else if (scpTriggerBall(self, boyGObj, 200.0f) != 0 ||
               ((void *)girlGObj != 0 && scpTriggerBall(self, (void *)girlGObj, 400.0f) != 0)) {
        stage_SetLoopFlag(111, 1);
        stage_SetAnimation(111, 1, 0);

        _ACTWait(60);
        doorDown_mes[0].func = actSt17aDoorDownChk;
        act->mail = doorDown_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(109, 0, 0);
        doorUp_mes[0].func = actSt17aDoorUpChk;
        act->mail = doorUp_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt17aDoorUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x3000000) == 0) {
        _ACTWait(1);
    }

    _ACTWait(15);

    actCreateSubThread(actSt17aDoorUpEffect, 21);

    scpWakeupItemWithBoundary(6573.0f, -2077.0f, 1089.0f, 100.0f);

    stage_SetAnimation(109, 1, 0);

    buf[0] = doorChkSePos.d[0];
    buf[1] = doorChkSePos.d[1];
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);

    h = soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(60);
    soundSeDefStop(h);

    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(109) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetLoopFlag(111, 1);
    stage_SetAnimation(111, 1, 0);

    doorUpChk_mes[0].func = actSt17aDoorDownChk;
    sub->mail = doorUpChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt17aDoorDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x3000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);

    actCreateSubThread(actSt17aDoorDownEffect, 21);

    scpWakeupItemWithBoundary(6573.0f, -2077.0f, 1089.0f, 100.0f);

    stage_SetLoopFlag(111, 0);

    stage_SetAnimation(110, 1, 0);

    buf[0] = doorChkSePos.d[0];
    buf[1] = doorChkSePos.d[1];
    soundSeDefPlay(1196, 0, (float *)buf, 1);
    _ACTWait(30);

    h = soundSeDefPlay(1197, 0, (float *)buf, 1);
    _ACTWait(38);
    soundSeDefStop(h);

    soundSeDefPlay(1198, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(110) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_mes[0].func = actSt17aDoorUpChk;
    sub->mail = door_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt17aHasiChk(GObj *volatile self)
{
    long long buf[2];
    ConstVec pos;
    float dir[4];

    if ((void *)girlGObj == 0) {
        _ACTWait(0);
    }

    while (1) {
        if ((GOBJ_ACT(girlGObj)->actMode != 107 && (void *)girlGObj != 0 &&
             scpTriggerFloorAttr((void *)girlGObj, 0x1000000) != 0 &&
             scpTriggerFloorAttr(boyGObj, 0x2000000) != 0) ||
            (GOBJ_ACT(girlGObj)->actMode != 107 && (void *)girlGObj != 0 &&
             scpTriggerFloorAttr((void *)girlGObj, 0x4000000) != 0 &&
             scpTriggerFloorAttr(boyGObj, 0x2000000) != 0)) {
            break;
        }
        _ACTWait(1);
    }

    iosPadActRequest(boyPad, 15);
    gflagOn(31);
    SetWayGroupActive(3, 0);

    scpSearchGobj(220)->active = 0;
    scpSearchGobj(221)->active = 1;

    stage_SetAnimation(113, 1, 0);
    SetCameraFlag_LwsCutBack();

    actCreateSubThread(actSt17aHasiEffect, 21);

    if (ACTGame_FLAG_TETSUNAGI() == 0) {
        stage_SetAnimation(112, 1, 0);

        buf[0] = hasiChkSePos.d[0];
        buf[1] = hasiChkSePos.d[1];
        soundSeDefPlay(1266, 0, (float *)buf, 1);

        scpPlayMot((void *)girlGObj, 514);
        _ACTWait(10);
        pos = hasiChkGirlDir;
        sceVu0SubVector(dir, pos.f, test_CURRENTROOT((void *)girlGObj));
        scpPlayMotDir((void *)girlGObj, dir);
        _ACTWait(10);
        scpPlayJump((void *)girlGObj, 272);
        _ACTWait(330);
        pos = hasiChkGirlWay;
        _SCPMoveCharactorByWay((void *)girlGObj, 0, pos.f, 100.0f, 2);
    } else {
        _SCPBoySupportGirl(-3713.0f, 1907.0f, -1095.0f, -4713.0f, 1907.0f, -1095.0f);

        stage_SetAnimation(112, 1, 0);

        pos = hasiChkSePos;
        soundSeDefPlay(1266, 0, pos.f, 1);
    }

    while (stage_CheckAnimationFinish(112) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

/* The seven spawn positions are initialised block locals, as in e3.c's
 * actE3CageFallEffect. */
void actSt17aHasiEffect(GObj *volatile self)
{
    float t;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 0: {
            EffectArg b1 = {{3645.0f, -1966.0f, 1122.0f, 1.0f}};
            scpEffectStart(&b1, 15);
        } break;
        case 15: {
            EffectArg b2 = {{3753.0f, -1936.0f, 1090.0f, 1.0f}};
            scpEffectStart(&b2, 0);
        }
            {
                EffectArg b3 = {{3605.0f, -1866.0f, 1150.0f, 1.0f}};
                scpEffectStart(&b3, 15);
            }
            break;
        case 60: {
            EffectArg b4 = {{3759.0f, -1666.0f, 1152.0f, 1.0f}};
            scpEffectStart(&b4, 15);
        }
            {
                EffectArg b5 = {{3305.0f, -1566.0f, 1082.0f, 1.0f}};
                scpEffectStart(&b5, 0);
            }
            break;
        case 120: {
            EffectArg b6 = {{3545.0f, -1466.0f, 1120.0f, 1.0f}};
            scpEffectStart(&b6, 0);
        }
            {
                EffectArg b7 = {{3655.0f, -1066.0f, 1477.0f, 1.0f}};
                scpEffectStart(&b7, 0);
            }
            break;
        }
        n = (int)t;
        t += (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)t) {
            _ACTWait(1);
        } else {
            t += 1.0f;
        }
    } while (t < 1000.0f);
}

INCLUDE_ASM(actLinkTest);

INCLUDE_ASM(actSt17aSekizo);

INCLUDE_ASM(actSt17aHasi);

void actSt17aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(32) == 0) {
        intro_mes[0].func = actSt17aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt17aSekizoEvent(int x)
{
    volatile int local = x;
}

void actLinkTestChk(GObj *volatile self)
{
    *(int *)(((int *)boyGObj)[87] + 1256) = 1;
    *(int *)(((int *)boyGObj)[87] + 1256) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
}

void actSt17aDoorEvent(int x)
{
    volatile int local = x;
}

void actSt17aDoorUpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorUpEffectPos.d[0];
    long long v0b = doorDownEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorDownEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt17aDoorDownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorDownEffectPos.d[0];
    long long v0b = doorDownEffect2Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorDownEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorDownEffect2Pos.d[1];
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

/* .sdata: the camera stream handle. */
SqEntry *cam = 0;

void actSt17aIntroChk(GObj *volatile self)
{
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(32);
    if (girlGObj != 0) {
        iosOmSendMail(girlGObj, 59, boyGObj);
        actCreateSubThread(actSt17aGirlWay, 21);
    }
    scpAdpcmPlayRequestFunc(51, &cam, 1, 1, 1);
    _ACTWait(1);
    stage_SetAnimation(70, 1, 0);
    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(70) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt17aGirlWay(GObj *volatile self)
{
    EffectArg buf = {{1547.0f, -2070.0f, 1495.0f, 0.0f}};

    _SCPMoveCharactorByWay((void *)girlGObj, 0, buf.f, 100.0f, 2);
}
