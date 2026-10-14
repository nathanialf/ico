#include "st01b.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "chain.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

/* This stage's actor mail records. Word 0 of each entry is the mail id the
   entry answers (430 = the actor's own wake-up post, 429 = the trailing
   entry); the handler in .func is installed at run time just before the
   record is posted. Each record is named for the actor thread that owns
   and posts it. */
static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail floor_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_on_mes[2] = {{430}, {429}}; /* derived name */

static ActMail way_off_mes[2] = {{430}, {429}}; /* derived name */

INCLUDE_ASM(actSt01bInit);

INCLUDE_ASM(actSt01bEneChk);

INCLUDE_ASM(func_00210F20);

/* .sdata */
SqEntry *st01b_floor = 0;

unsigned int st01b_yure = 0;

unsigned char st01b_yure_vol = 0;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec floorChkSubPos = {{-101.0f, -381.0f, -398.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(actSt01bSekizo);

INCLUDE_ASM(actSt01bEne);

INCLUDE_ASM(actSt01bEnemy1);

INCLUDE_ASM(actSt01bEnemy2);

INCLUDE_ASM(actSt01bEnemy3);

INCLUDE_ASM(actSt01bEnemy4);

INCLUDE_ASM(actSt01bEnemy5);

INCLUDE_ASM(actSt01bEnemy6);

INCLUDE_ASM(actSt01bFloor);

INCLUDE_ASM(actSt01bWay);

void actSt01bEnd(void) {}

void actSt01bSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt01bFloorEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt01bWayOnChk);

INCLUDE_ASM(actSt01bWayOffChk);
