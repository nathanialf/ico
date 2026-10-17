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
#include "include_asm.h"

static void actSt07aChanChainChk(GObj *volatile self);
static void actSt07aChanReadyChk(GObj *volatile self);

INCLUDE_ASM(actSt07aInit);

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for. */
static int demoEnd;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec chanChkPos = {{10000.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

/* actSt07aChanEffect's nine positions (the stub's row) stand between the two
   check positions in the demo's .rodata; PAL's two chan way positions are not
   in this build */
INCLUDE_ASM_LIT(actSt07aChanEffect);

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

/* .sdata: one stream handle, the one func_00211F40 plays (the Aug-6-2001
   build's first handle here, bridge; this build has no statue handles or
   shake). */
SqEntry *bridge = 0;

INCLUDE_ASM(actSt07aChanChk);

INCLUDE_ASM(actSt07aChanEffect);

INCLUDE_ASM(func_00211F40);

INCLUDE_ASM(func_002120C0);

INCLUDE_ASM(func_002124C0);

INCLUDE_ASM(actSt07aObj401);

INCLUDE_ASM(actSt07aObj402);

INCLUDE_ASM(func_002126E0);

INCLUDE_ASM(actSt07aObj404);

INCLUDE_ASM(actSt07aObj352);

INCLUDE_ASM(actSt07aObj365);

INCLUDE_ASM(actSt07aObj366);

INCLUDE_ASM(actSt07aObj367);

static ActMail chanReady_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chanChain_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chan_mes[2] = {{377}, {376}}; /* derived name */

static ActMail tsuro_mes[2] = {{377}, {376}}; /* derived name */

void actSt07ChanEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt07aChanFall);

INCLUDE_ASM(actSt07aChanWay2);

void actSt07TsuroEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(func_00212B90);

void actSt07aCamera2(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt07aIntroChk);

void actSt07aSekizoEvent(int x)
{
    volatile int local = x;
}
