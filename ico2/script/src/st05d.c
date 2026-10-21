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
#include "main.h"
#include "include_asm.h"

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec door2UpChkPos = {{-702.0f, -1886.0f, -5680.0f, 0.0f}}; /* derived name */

static const ConstVec door2UpEffectPos = {{-704.0f, -1700.0f, -5679.0f, 1.0f}}; /* derived name */

static const ConstVec door2UpEffect2Pos = {{-704.0f, -1955.0f, -5679.0f, 1.0f}}; /* derived name */

void actSt05dDoor2UpEffect(GObj *volatile self);
void actSt05dDoor2DownEffect(GObj *volatile self);
void actSt05dEneChk(GObj *volatile self);

static ActMail door2Up_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door2UpChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door2DownChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

void actSt05dDoor2DownChk(GObj *volatile self);
void actSt05dDoor2UpChk(GObj *volatile self);

INCLUDE_ASM(actSt05dDoor2UpChk);

INCLUDE_ASM(actSt05dDoor2DownChk);

void actSt05dDoor2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    stage_SetAnimation(282, 0, 0);
    door2Up_mes[0].func = actSt05dDoor2UpChk;
    act->mail = door2Up_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt05dEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(146) == 0) {
        ene_mes[0].func = actSt05dEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt05dEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(147) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_MaskOff(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt05dEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    while (gflagChk(147) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt05dDoor2Event(int x)
{
    volatile int local = x;
}

void actSt05dDoor2UpEffect(GObj *volatile self)
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
        case 30:
            b2[0] = v0b;
            b2[1] = door2UpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt05dDoor2DownEffect(GObj *volatile self)
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
        case 30:
            b2[0] = v0b;
            b2[1] = door2UpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt05dEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (girlGObj == 0 || gflagChk(145) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(146);
    gflagOn(147);
}
