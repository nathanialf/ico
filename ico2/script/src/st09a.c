#include "st09a.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "typedef.h"
#include "main.h"
#include "include_asm.h"

static void actSt09aBrgDownSub(GObj *volatile self);

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for. */
static int demoEnd;

/* .data: actor mail packets. */

static ActMail elvMain_mes[2] = {{406, actSt09aElvSwitch}, {429}}; /* derived name */

static ActMail elv_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elvSwitchUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elvSwitchDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elvDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elvUp_mes[2] = {{430}, {429}}; /* derived name */

static float sekizoPos[4] = {1548.0f, -412.0f, -608.0f, 0.0f}; /* derived name */

static ActMail intro_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brgMain_mes[2] = {{407, actSt09aBrgSwitch}, {429}}; /* derived name */

static ActMail brg_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brgSwitch_mes[2] = {{430}, {429}}; /* derived name */

/* .sdata: the bridge stream handle. */
SqEntry *st09a_brg = 0;

INCLUDE_ASM(actSt09aInit);

INCLUDE_ASM(actSt09aElvDown);

INCLUDE_ASM(actSt09aSekizo);

INCLUDE_ASM(actSt09aBrgDown);

INCLUDE_ASM(actSt09aElv);

INCLUDE_ASM(actSt09aIntro);

INCLUDE_ASM(actSt09aBrg);

INCLUDE_ASM(actSt09aElvMain);

INCLUDE_ASM(actSt09aElvSwitch);

INCLUDE_ASM(actSt09aElvUp);

void actSt09aSekizoEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt09aIntroChk);

INCLUDE_ASM(actSt09aBrgMain);

INCLUDE_ASM(actSt09aBrgSwitch);
