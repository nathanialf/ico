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

static ActMail sword_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demoCam_mes[2] = {{397}, {396}}; /* derived name */

static const Vec16 swordChkPos = {{1685.0f, -1080.0f, -1000.0f, 1.0f}}; /* derived name */

/* .sdata: the sword's object. */
SqEntry *sword = 0;

INCLUDE_ASM(func_002394D8);

INCLUDE_ASM(actSt24aSword);

INCLUDE_ASM(actSt24aSaku);
