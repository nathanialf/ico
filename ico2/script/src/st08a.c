#include "st08a.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static void actSt08aDoorUpSub(GObj *volatile self);

static ActMail ene1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door_main_mes[2] = {{407, actSt08aDoorSwitch}, {429}}; /* derived name */

static ActMail door_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door_switch_mes[2] = {{430}, {429}}; /* derived name */

static float door_up_sound_pos[4] = {-3092.0f, -2727.0f, 3711.0f, 0.0f}; /* derived name */

static ActMail intro_mes[2] = {{430}, {429}}; /* derived name */

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for, and the flag actSt08aDoorUpSub raises when the door is all
   the way up. */
static int demoEnd;

static int doorUpDone; /* derived name */

INCLUDE_ASM(actSt08aEnd);

INCLUDE_ASM(actSt08aEne1Chk);

INCLUDE_ASM(actSt08aEne2Chk);

INCLUDE_ASM(actSt08aDoorUp);

INCLUDE_ASM(actSt08aDoor);

INCLUDE_ASM(actSt08aEne1);

INCLUDE_ASM(actSt08aEne2);

INCLUDE_ASM(actSt08aEnemy1);

INCLUDE_ASM(actSt08aEnemy2);

INCLUDE_ASM(actSt08aEnemy3);

INCLUDE_ASM(actSt08aEnemy4);

INCLUDE_ASM(actSt08aIntro);

INCLUDE_ASM(actSt08aInit);

INCLUDE_ASM(actSt08aDoorMain);

INCLUDE_ASM(actSt08aDoorSwitch);

INCLUDE_ASM(actSt08aIntroChk);
