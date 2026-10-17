#include "st19a.h"
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
#include "motionManager2.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static void actSt19aChainDownSub(GObj *volatile self);

/* No .sbss here in this build: no function of the demo addresses such a flag. */

/* .data: actor mail packets. */

/* this build's run: fourteen packets, the two switch packets' mail ids
   356 and 357 (the reverse of PAL's order) */
static ActMail oriMain_mes[2] = {{356, actSt19aOriSwitch}, {376}}; /* derived name */

static ActMail ori_mes[2] = {{377}, {376}}; /* derived name */

static ActMail oriSwitch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail oriSwitch2_mes[2] = {{377}, {376}}; /* derived name */

/* func_0021EB40's and func_0021EC28's */
static ActMail st19a_mes080[2] = {{377}, {376}}; /* derived name */

static ActMail st19a_mes0A0[2] = {{377}, {376}}; /* derived name */

static ActMail haguruma_mes[2] = {{377}, {376}}; /* derived name */

static ActMail pipe_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chainMain_mes[2] = {{357, actSt19aChainSwitch}, {376}}; /* derived name */

static ActMail chain_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chainSwitch2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chainDown_mes[2] = {{377}, {376}}; /* derived name */

/* actSt19bIntroChk's */
static ActMail st19bIntro_mes[2] = {{377}, {376}}; /* derived name */

/* No .sdata: this build's room has no fence, horn or pipe stream handle
   (no function of the demo addresses one). */

void actSt19aOriUp(GObj *volatile self);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec hagurumaPos = {{-642.0f, 2132.0f, -2861.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(actSt19aHaguruma);

INCLUDE_ASM(actSt19aHagurumaChk);

INCLUDE_ASM(actSt19aPipeChk);

INCLUDE_ASM(actSt19aChainDown);

INCLUDE_ASM(actSt19aOri);

INCLUDE_ASM(actSt19aOriXL);

INCLUDE_ASM(actSt19aPipe);

INCLUDE_ASM(actSt19aPipeXL);

INCLUDE_ASM(actSt19aChain);

INCLUDE_ASM(actSt19aOriMain);

INCLUDE_ASM(actSt19aOriSwitch);

INCLUDE_ASM(func_0021EB40);

INCLUDE_ASM(func_0021EC28);

INCLUDE_ASM(actSt19aChainMain);

INCLUDE_ASM(actSt19aChainSwitch);

INCLUDE_ASM(actSt19bIntroChk);
