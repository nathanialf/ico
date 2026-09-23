#include "common.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "geometryManager.h"
#include "item.h"
#include "quaternion.h"
#include "typedef.h"

extern void *D_00639EA4;
extern char *D_00639EA8;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec door2UpChkPos = {{-702.0f, -1886.0f, -5680.0f, 0.0f}};

static const ConstVec door2UpEffectPos = {{-704.0f, -1700.0f, -5679.0f, 1.0f}};

static const ConstVec door2UpEffect2Pos = {{-704.0f, -1955.0f, -5679.0f, 1.0f}};

void actSt05dDoor2UpEffect(volatile int a0);
void actSt05dDoor2DownEffect(volatile int a0);
void actSt05dEneChk(volatile int a0);
void actSt05dCrestHintChk(volatile int a0);

static ActMail door2Down_mes[2] = {{430}, {429}};

static ActMail door2Up_mes[2] = {{430}, {429}};

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
        stage_SetAnimation(349, 0, 0);
        _ACTWait(60);
        door2Down_mes[0].func = actSt05dDoor2DownChk;
        self->mail = door2Down_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(348, 0, 0);
        door2Up_mes[0].func = actSt05dDoor2UpChk;
        self->mail = door2Up_mes;
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
    _ACTWait(15);

    actCreateSubThread(actSt05dDoor2UpEffect, 21);

    ReviveAllCarryableItemsWithNonSleepFrame(60);

    stage_SetAnimation(348, 1, 0);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(348) == 0) {
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
    _ACTWait(15);

    actCreateSubThread(actSt05dDoor2DownEffect, 21);

    ReviveAllCarryableItemsWithNonSleepFrame(60);

    stage_SetAnimation(349, 1, 0);

    buf[0] = door2UpChkPos.d[0];
    buf[1] = door2UpChkPos.d[1];
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(349) == 0) {
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

    g = scpSearchGobj(1458);
    rot = scpGetRotObjectCurrentRot(0x614);

    GetRootQuaternion(GetCurrentQuaternion(), g);
    RotQuaternionY(GetCurrentQuaternion(), rot);
    SetRootQuaternion(g, GetCurrentQuaternion());
    UpdateRootMatrix(g);

    if (gflagChk(171) == 0) {
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
    Generator_Mask(scpSearchGobj(1477));
    Generator_Mask(scpSearchGobj(1478));
    while (gflagChk(172) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_Call(scpSearchGobj(1477));
    Generator_Call(scpSearchGobj(1478));
}

void actSt05dEnemy2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(172) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt05dCrestHint(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(173) == 0) {
        SleepHint(25);
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

void actSt05dDoor2UpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door2UpEffectPos.d[0];
    long long v0b = door2UpEffect2Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
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
    for (i = 0; i < 50; i++) {
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
    while (D_00639EA8 == 0 || gflagChk(170) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(171);
    gflagOn(172);
}

void actSt05dCrestHintChk(volatile int a0)
{
    while (gflagChk(243) == 0 || gflagChk(244) == 0 || gflagChk(245) == 0 || gflagChk(232) != 0) {
        _ACTWait(1);
    }
    gflagOn(173);
    WakeupHint(25);
}
