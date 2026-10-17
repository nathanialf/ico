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
static void actSt08aGirlPosChk(GObj *volatile self);
static void actSt08aHasiMain(GObj *volatile self);
static void actSt08aHint1Chk(GObj *volatile self);
static void actSt08aTorchOffChk(GObj *volatile self);

static ActMail ene1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ene2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door_main_mes[2] = {{357, actSt08aDoorSwitch}, {376}}; /* derived name */

static ActMail door_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door_switch_mes[2] = {{377}, {376}}; /* derived name */

static float door_up_sound_pos[4] = {-3092.0f, -2727.0f, 3711.0f, 0.0f}; /* derived name */

/* No .sbss here in this build: no function of the demo addresses these flags. */

void actSt08aEne1Chk(GObj *volatile self);
void actSt08aEne2Chk(GObj *volatile self);
void actSt08aDoorUp(GObj *volatile self);

/* No .sdata: this build's scene has no stream handle of its own (no function
   of the demo addresses one). */

INCLUDE_ASM(actSt08aDoor);

INCLUDE_ASM(actSt08aEne1);

INCLUDE_ASM(actSt08aEne2);

INCLUDE_ASM(actSt08aEnemy1);

INCLUDE_ASM(actSt08aEnemy2);

INCLUDE_ASM(actSt08aEnemy3);

INCLUDE_ASM(actSt08aEnemy4);

INCLUDE_ASM(actSt08aIntro);

INCLUDE_ASM(actSt08aInit);

INCLUDE_ASM(func_002131E0);

INCLUDE_ASM(actSt08aDoorMain);

INCLUDE_ASM(actSt08aDoorSwitch);

INCLUDE_ASM(actSt08aIntroChk);
