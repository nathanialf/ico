#include "st20a.h"
#include "gamesys.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "boyact.h"
#include "commonact.h"
#include "girl_act.h"
#include "way_llf.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"
#include "include_asm.h"

static void actSt20aHint1Chk(GObj *volatile self);

/* This stage's actor mail records. Word 0 of each entry is the mail id the
   entry answers (430 = the actor's own wake-up post, 429 = the trailing
   entry); the handler in .func is installed at run time just before the
   record is posted. The two main-thread records answer their own ids and
   carry their switch handler from the start. Each record is named for the
   actor thread that owns and posts it. */
static ActMail bridgeMain_mes[2] = {{406, actSt20aBridgeSwitch}, {429}}; /* derived name */

static ActMail bridge_mes[2] = {{430}, {429}}; /* derived name */

static ActMail bridgeSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaMain_mes[2] = {{407, actSt20aGondolaSwitch}, {429}}; /* derived name */

static ActMail gondola_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaSwitchUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaSwitchDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail exit_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fence_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fence2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fenceDownChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fenceUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fenceDownChk2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail fenceUpChk2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlPos_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1_mes[2] = {{430}, {429}}; /* derived name */

INCLUDE_ASM(actSt20aInit);

INCLUDE_ASM(func_00237BD0);

INCLUDE_ASM(func_00237C18);

/* .sdata: the bridge and gondola stream handles and the shake. */
SqEntry *brg20a = 0;

SqEntry *gondola_up = 0;

SqEntry *gondola_down = 0;

unsigned int st20a_yure = 0;

unsigned char st20a_yure_vol = 0;

INCLUDE_ASM(actSt20aGondolaDown);

INCLUDE_ASM(actSt20aGondolaUp);

INCLUDE_ASM(actSt20aFence);

INCLUDE_ASM(actSt20aFenceDownChk);

INCLUDE_ASM(actSt20aFenceUpChk);

INCLUDE_ASM(actSt20aFenceDownChk2);

INCLUDE_ASM(actSt20aFenceUpChk2);

INCLUDE_ASM(actSt20aBridge);

INCLUDE_ASM(actSt20aGondola);

INCLUDE_ASM(actSt20aExit);

INCLUDE_ASM(actSt20aElv);

INCLUDE_ASM(actSt20aEne);

INCLUDE_ASM(actSt20aEnemy1);

INCLUDE_ASM(actSt20aEnemy2);

INCLUDE_ASM(actSt20aEnemy3);

/* the actor entry's parameter is its frame home: the thread switch writes it */
INCLUDE_ASM(actSt20aBridgeMain);

INCLUDE_ASM(actSt20aBridgeSwitch);

INCLUDE_ASM(actSt20aGondolaMain);

INCLUDE_ASM(actSt20aGondolaSwitch);

INCLUDE_ASM(actSt20aExitChk);

INCLUDE_ASM(actSt20aHint1Chk);
