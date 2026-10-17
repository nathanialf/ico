#include "st24a.h"
#include "layout_texture.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "camera-root.h"
#include "gflag.h"
#include "StageAnimation.h"
#include <libvu0.h>
#include "typedef.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt24aSwordSub(GObj *volatile self);

static ActMail sword_mes[2] = {{377}, {376}}; /* derived name */

/* No .sbss here in this build: no function of the demo addresses such a flag. */

static const Vec16 swordChkPos = {{1685.0f, -1080.0f, -1000.0f, 1.0f}}; /* derived name */

/* .sdata: the sword's stream handle and the fence's (actSt24aSaku's). */
SqEntry *sword = 0;

SqEntry *saku = 0; /* derived name */

INCLUDE_ASM(actSt24aSwordChk);

INCLUDE_ASM(actSt24aSword);

INCLUDE_ASM(actSt24aSaku);
