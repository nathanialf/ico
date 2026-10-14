#include "st05e.h"
#include "layout_texture.h"
#include "thread.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "rotObject.h"
#include "typedef.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt05eWaterStopSub(GObj *volatile self);

/* .data: four 0x20-byte actor mail packets, one per thread hand-off. */

static ActMail waterMain_mes[2] = {{372, actSt05eWaterSwitch}, {392}}; /* derived name */

static ActMail water_mes[2] = {{393}, {392}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail solar_mes[2] = {{393}, {392}}; /* derived name */

/* .sdata: the solar stream handle. */
struct SqEntry *solar = 0;

INCLUDE_ASM(actSt05eSolarChk);

INCLUDE_ASM(actSt05eWater);

INCLUDE_ASM(actSt05eSolar);

INCLUDE_ASM(actSt05eWaterMain);

INCLUDE_ASM(actSt05eWaterSwitch);

INCLUDE_ASM(actSt05eWaterStop);

INCLUDE_ASM(actSt05eWaterFlagOn);
