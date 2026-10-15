#include "st05b.h"
#include "layout_texture.h"
#include "pad.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "brain.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "item.h"
#include <libvu0.h>
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

INCLUDE_ASM(actSt05bCrest01XL);

/* .sdata: the stone statue's stream handle, its shake and the shake's volume. */
SqEntry *sekizo5b = 0;

int sekizo_5b = 0;

unsigned char sekizo_5b_vol = 0;

INCLUDE_ASM(actSt05bSekizoChk);

void actSt05bDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(218) != 0 && gflagChk(125) == 0) {
        stage_SetAnimation(312, 0, -1);
    } else {
        stage_SetAnimation(312, 0, 0);
    }
}

void actSt05bMonyoDoorXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(209) == 0) {
        stage_SetAnimation(223, 0, 0);
    } else {
        stage_SetAnimation(223, 0, -1);
    }
}

void actSt05bSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(143) == 0) {
        stage_SetAnimation(171, 0, 0);
        sekizo_mes[0].func = actSt05bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(171, 0, -1);
        if (gflagChk(218) == 0) {
            ScpCallCameraSetTarget(-10793.0f, 2122.0f, 0.0f);
        }
    }
}

void actSt05bBallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(125) == 0) {
        stage_SetAnimation(267, -1, -2);
    } else {
        stage_SetAnimation(265, -1, -2);
    }
}

void actSt05bSolarXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(125) == 0) {
        stage_SetAnimation(270, -1, -2);
        stage_SetAnimation(273, -1, -2);
    }
}

void actSt05bSekizoEvent(int x)
{
    volatile int local = x;
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{10750.0f, -2122.0f, 0.0f, 0.0f}}; /* derived name */

static const ConstVec girlWay2Pos = {{139.0f, -177.0f, 1670.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(actSt05bGirlWay);
