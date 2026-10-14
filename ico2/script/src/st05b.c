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

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

INCLUDE_ASM(actSt05bCrest01XL);

/* .sdata: the stone statue's stream handle, its shake and the shake's volume. */
SqEntry *sekizo5b = 0;

int sekizo_5b = 0;

unsigned char sekizo_5b_vol = 0;

INCLUDE_ASM(actSt05bSekizoChk);

INCLUDE_ASM(actSt05bDoorXL);

INCLUDE_ASM(actSt05bMonyoDoorXL);

INCLUDE_ASM(actSt05bSekizo);

INCLUDE_ASM(actSt05bBallXL);

INCLUDE_ASM(actSt05bSolarXL);

void actSt05bSekizoEvent(int x)
{
    volatile int local = x;
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{10750.0f, -2122.0f, 0.0f, 0.0f}}; /* derived name */

static const ConstVec girlWay2Pos = {{139.0f, -177.0f, 1670.0f, 0.0f}}; /* derived name */

void actSt05bGirlWay(GObj *volatile self)
{
    long long buf[2];
    long long way[2];

    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);

    way[0] = girlWay2Pos.d[0];
    way[1] = girlWay2Pos.d[1];
    RequestStageChangeDirect(girlGObj, 28, way, 180);
    brainUnlockGirl();
}
