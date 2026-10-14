#include "st04e.h"
#include "debug.h"
#include "layout_texture.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "rotObject.h"
#include "typedef.h"
#include "stageSEProc.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static void actSt04eWaterStopSub(GObj *volatile self);

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for, and its complement, true when the player skipped the demo with
   START. */
static int demoEnd;

static int demoSkipped; /* derived name */

static ActMail waterMain_mes[2] = {{372, actSt04eWaterSwitch}, {392}}; /* derived name */

static ActMail water_mes[2] = {{393}, {392}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{393}, {392}}; /* derived name */

INCLUDE_ASM(actSt04eWater);

INCLUDE_ASM(actSt04eWaterMain);

INCLUDE_ASM(actSt04eWaterSwitch);

INCLUDE_ASM(actSt04eWaterStop);

INCLUDE_ASM(actSt04eWaterFlagOn);
