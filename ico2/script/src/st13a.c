#include "st13a.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "chain.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include <libvu0.h>
#include "typedef.h"
#include "main.h"
#include "include_asm.h"

static void actSt13aElevDownSub(GObj *volatile self);
void actSt13aElevDownChk(GObj *volatile self);

/* .data: actor mail packets. */

/* The chain-OK watcher's mail record: it installs actSt13aChainNG here and
   posts it to hand the chain back to the NG (hang-disabled) watcher. Word 0
   of each entry is the mail id the entry answers (397 the actor post,
   396 the trailing entry); .func is filled in at run time. Named for the
   thread that owns and posts it. */

static ActMail elevMain_mes[2] = {{376, actSt13aElevSwitch}, {396}}; /* derived name */

static ActMail elev_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elevDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail check_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainNg_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainOk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainOK_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainNG_mes[2] = {{397}, {396}}; /* derived name */

/* .sdata: the lift and statue stream handles and shakes. */
SqEntry *st13a_up = 0;

SqEntry *st13a_down = 0;

SqEntry *sekizo13a = 0;

unsigned int st13a_yure = 0;

unsigned char st13a_yure_vol = 0;

int sekizo_13a = 0;

unsigned char sekizo_13a_vol = 0;

INCLUDE_ASM(func_0022EF78);

INCLUDE_ASM(actSt13aElevDown);

INCLUDE_ASM(actSt13aElevDownSub);

INCLUDE_ASM(actSt13aSekizoChk);

INCLUDE_ASM(actSt13aElev);

INCLUDE_ASM(actSt13aSekizo);

INCLUDE_ASM(actSt13aCheck);

INCLUDE_ASM(actSt13aChain);

INCLUDE_ASM(actSt13aElevMain);

INCLUDE_ASM(actSt13aElevSwitch);

INCLUDE_ASM(actSt13aCheckChk);

INCLUDE_ASM(actSt13aChainOK);

INCLUDE_ASM(actSt13aChainNG);
