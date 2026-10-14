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

static void actSt04eHint1Chk(GObj *volatile self);

static ActMail waterMain_mes[2] = {{376, actSt04eWaterSwitch}, {396}}; /* derived name */

static ActMail water_mes[2] = {{397}, {396}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{397}, {396}}; /* derived name */

INCLUDE_ASM(actSt04eWater);

INCLUDE_ASM(actSt04eWaterMain);

INCLUDE_ASM(actSt04eWaterSwitch);

INCLUDE_ASM(func_0021A390);

INCLUDE_ASM(actSt04eHint1Chk);
