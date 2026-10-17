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

static ActMail sekizo_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ene1_mes[2] = {{377}, {376}}; /* derived name */

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{-10750.0f, -2122.0f, 0.0f, 0.0f}}; /* derived name */

static const ConstVec girlWay2Pos = {{-139.0f, -177.0f, 1670.0f, 0.0f}}; /* derived name */

/* .sdata: the stone statue's shake and the shake's volume (this build has no
   stream handle for the statue: actSt04bSekizoChk addresses these two). */
int sekizo_4b = 0;

unsigned char sekizo_4b_vol = 0;

INCLUDE_ASM(actSt04bSekizoChk);

void actSt04bEne1Chk(GObj *volatile self);

INCLUDE_ASM(actSt04bCrest01XL);

INCLUDE_ASM(actSt04bDoorXL);

INCLUDE_ASM(actSt04bMonyoDoorXL);

INCLUDE_ASM(actSt04bSekizo);

INCLUDE_ASM(actSt04bEne1);

INCLUDE_ASM(actSt04bEnemy1);

INCLUDE_ASM(actSt04bEnemy2);

INCLUDE_ASM(actSt04bBallXL);

INCLUDE_ASM(actSt04bSolarXL);

INCLUDE_ASM(actSt04bSekizoEvent);

INCLUDE_ASM(actSt04bGirlWay);
