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
#include "stageSEProc.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

/* .data: four 0x20-byte actor mail packets, one per thread hand-off. */

static ActMail water_mes[2] = {{397}, {396}}; /* derived name */

static ActMail waterSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail solar_mes[2] = {{397}, {396}}; /* derived name */

/* .sdata: the solar stream handle. */
struct SqEntry *solar = 0;

INCLUDE_ASM(func_00225B20);

INCLUDE_ASM(actSt05eWater);
