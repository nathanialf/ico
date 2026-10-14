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

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for. */
static int demoEnd;

/* .data: actor mail packets. */

static ActMail oriMain_mes[2] = {{373, actSt19aOriSwitch}, {392}}; /* derived name */

static ActMail ori_mes[2] = {{393}, {392}}; /* derived name */

static ActMail oriSwitch_mes[2] = {{393}, {392}}; /* derived name */

static float oriXLPos[4] = {-642.0f, 2132.0f, -2861.0f, 0.0f}; /* derived name */

static float haguruma2Pos[4] = {486.0f, 2386.0f, -2917.0f, 0.0f}; /* derived name */

static ActMail haguruma_mes[2] = {{393}, {392}}; /* derived name */

static ActMail pipe_mes[2] = {{393}, {392}}; /* derived name */

static ActMail chainMain_mes[2] = {{372, actSt19aChainSwitch}, {392}}; /* derived name */

static ActMail chain_mes[2] = {{393}, {392}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{393}, {392}}; /* derived name */

/* .sdata: the fence, horn and pipe stream handles. */
SqEntry *fence_up_19a = 0;

SqEntry *fence_down_19a = 0;

SqEntry *hgrm_19a = 0;

SqEntry *pipe19a = 0;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec hagurumaPos = {{-642.0f, 2132.0f, -2861.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(actSt19aOriDown);

INCLUDE_ASM(actSt19aHaguruma);

INCLUDE_ASM(actSt19aHagurumaChk);

INCLUDE_ASM(actSt19aPipeChk);

INCLUDE_ASM(actSt19aChainDown);

INCLUDE_ASM(actSt19aChainUp);

INCLUDE_ASM(actSt19aOri);

INCLUDE_ASM(actSt19aOriXL);

INCLUDE_ASM(actSt19aPipe);

INCLUDE_ASM(actSt19aPipeXL);

INCLUDE_ASM(actSt19aChain);

INCLUDE_ASM(actSt19bIntro);

INCLUDE_ASM(actSt19aOriMain);

INCLUDE_ASM(actSt19aOriSwitch);

INCLUDE_ASM(actSt19aOriUp);

INCLUDE_ASM(actSt19aChainMain);

INCLUDE_ASM(actSt19aChainSwitch);

INCLUDE_ASM(actSt19bIntroChk);
