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

static ActMail oriMain_mes[2] = {{407, actSt19aOriSwitch}, {429}}; /* derived name */

static ActMail ori_mes[2] = {{430}, {429}}; /* derived name */

static ActMail oriSwitch_mes[2] = {{430}, {429}}; /* derived name */

static float oriXLPos[4] = {-642.0f, 2132.0f, -2861.0f, 0.0f}; /* derived name */

static float haguruma2Pos[4] = {486.0f, 2386.0f, -2917.0f, 0.0f}; /* derived name */

static ActMail haguruma_mes[2] = {{430}, {429}}; /* derived name */

static ActMail pipe_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainMain_mes[2] = {{406, actSt19aChainSwitch}, {429}}; /* derived name */

static ActMail chain_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{430}, {429}}; /* derived name */

/* .sdata: the fence, horn and pipe stream handles. */
SqEntry *fence_up_19a = 0;

SqEntry *fence_down_19a = 0;

SqEntry *hgrm_19a = 0;

SqEntry *pipe19a = 0;

void actSt19aOriUp(GObj *volatile self);

INCLUDE_ASM(actSt19aOriUp);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec hagurumaPos = {{-642.0f, 2132.0f, -2861.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(actSt19aHaguruma);

INCLUDE_ASM(actSt19aHagurumaChk);

INCLUDE_ASM(actSt19aPipeChk);

void actSt19aChainDown(GObj *volatile self);

INCLUDE_ASM(actSt19aChainDown);

INCLUDE_ASM(actSt19bIntro);

INCLUDE_ASM(actSt19aOri);

INCLUDE_ASM(actSt19aOriXL);

INCLUDE_ASM(actSt19aPipe);

INCLUDE_ASM(actSt19aPipeXL);

INCLUDE_ASM(actSt19aChain);

void actSt19aOriMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = oriMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt19aOriSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;
    oriSwitch_mes[0].func = actSt19aOriUp;
    sub->mail = oriSwitch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt19aChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = chainMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt19aChainSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    if (gflagChk(313) == 0) {
        chainSwitch_mes[0].func = actSt19aChainDown;
        sub->mail = chainSwitch_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt19aChainDownSub);
