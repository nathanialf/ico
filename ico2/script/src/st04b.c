#include "st04b.h"
#include "layout_texture.h"
#include "pad.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "brain.h"
#include "camera-root.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "item.h"
#include <libvu0.h>
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene1_mes[2] = {{397}, {396}}; /* derived name */

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{-10750.0f, -2122.0f, 0.0f, 0.0f}}; /* derived name */

static const ConstVec girlWay2Pos = {{-139.0f, -177.0f, 1670.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(actSt04bEnd);

/* .sdata: the stone statue's stream handle, its shake and the shake's volume. */
SqEntry *sekizo4b = 0;

int sekizo_4b = 0;

unsigned char sekizo_4b_vol = 0;

INCLUDE_ASM(actSt04bSekizoChk);

INCLUDE_ASM(actSt04bEne1Chk);

INCLUDE_ASM(actSt04bCrest01XL);

void actSt04bDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    stage_SetAnimation(221, 0, 0);
}

INCLUDE_ASM(actSt04bMonyoDoorXL);

INCLUDE_ASM(actSt04bSekizo);

INCLUDE_ASM(actSt04bEne1);

void actSt04bEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);
    while (gflagChk(141) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04bEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);
    while (gflagChk(141) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

INCLUDE_ASM(actSt04bBallXL);

INCLUDE_ASM(actSt04bSolarXL);

void actSt04bSekizoEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt04bGirlWay);
