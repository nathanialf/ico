#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "fightSound.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "item.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

/* .sdata: the prototype stair's stream handle, its shake and the shake's
   volume. */
SqEntry *proto = 0;

unsigned int proto_yure = 0;

unsigned char proto_yure_vol = 0;

/* .rodata: six 16-byte constant vectors, each named for the first actor that
   copies it.  The float view carries the values, the long long view is the
   one the copies read. */

static const ConstVec door2UpChkPos = {{0.0f, -422.0f, 1630.0f, 0.0f}}; /* derived name */

static const ConstVec door2UpEffectPos = {{0.0f, -150.0f, 1640.0f, 1.0f}}; /* derived name */

static const ConstVec door2UpEffect2Pos = {{0.0f, -450.0f, 1640.0f, 1.0f}}; /* derived name */

static const ConstVec door1UpChkPos = {{-1.0f, -184.0f, -57.0f, 0.0f}}; /* derived name */

static const ConstVec door1UpEffectPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec door1UpEffect2Pos = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

/* .data: eleven actor mail records, each the usual pair, the 430 entry whose
   handler the sender fills in and the 429 terminator, named for the actor that
   installs it. */
static ActMail atr2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail stair_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door2Down_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door2Up_mes[2] = {{430}, {429}}; /* derived name */

/* the four door checks' records */
static ActMail door2Upchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door2Downchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door1Down_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door1Up_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door1Upchk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door1Downchk_mes[2] = {{430}, {429}}; /* derived name */

INCLUDE_ASM(func_0020FA98);

INCLUDE_ASM(actSt00aEnd);

INCLUDE_ASM(actSt00aEneChk);

/* .sbss: the flag the stair-check subthread raises when the demo is over,
   which the wait loop below spins for. */
static int demoEnd;

static void actSt00aStairChkSub(GObj *volatile self);

INCLUDE_ASM(actSt00aStairChk);

void actSt00aDoor2DownChk(GObj *self);
void actSt00aDoor2UpChk(GObj *self);

INCLUDE_ASM(actSt00aDoor2);

void actSt00aDoor2UpEffect(GObj *volatile self);

INCLUDE_ASM(actSt00aDoor2UpChk);

void actSt00aDoor2DownEffect(GObj *volatile self);

INCLUDE_ASM(actSt00aDoor2DownChk);

void actSt00aDoor1DownChk(GObj *self);
void actSt00aDoor1UpChk(GObj *self);

INCLUDE_ASM(actSt00aDoor1);

void actSt00aDoor1UpEffect(GObj *volatile self);

INCLUDE_ASM(actSt00aDoor1UpChk);

void actSt00aDoor1DownEffect(GObj *volatile self);

INCLUDE_ASM(actSt00aDoor1DownChk);

INCLUDE_ASM(actSt00aEne);

INCLUDE_ASM(actSt00aEnemy1);

INCLUDE_ASM(actSt00aEnemy2);

INCLUDE_ASM(actSt00aStair);

void actSt00aAtr2Chk(GObj *volatile self);

INCLUDE_ASM(actSt00aAtr2);

INCLUDE_ASM(actSt00aAtr2Chk);

void actSt00aDoor2Event(int x)
{
    volatile int local = x;
}

void actSt00aDoor2UpEffect(GObj *volatile self)
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

void actSt00aDoor2DownEffect(GObj *volatile self)
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

void actSt00aDoor1Event(int x)
{
    volatile int local = x;
}

void actSt00aDoor1UpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door1UpEffectPos.d[0];
    long long v0b = door1UpEffect2Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door1UpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door1UpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt00aDoor1DownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door1UpEffect2Pos.d[0];
    long long v0b = door1UpEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door1UpEffect2Pos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door1UpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}
