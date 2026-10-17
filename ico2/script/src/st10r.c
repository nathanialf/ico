#include "st10r.h"
#include "gamesys.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "gobj_process.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "boyact.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "cage.h"
#include "motionManager2.h"
#include "rotObject.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static void actSt10rCageSub(GObj *volatile self);
static void actSt10rChainMoveSub(GObj *volatile self);
static void actSt10rFloorSub(GObj *volatile self);
static void actSt10rTowerResqueChk(GObj *volatile self);
static void actSt10rWayOffChk(GObj *volatile self);
static void actSt10rWayOnChk(GObj *volatile self);

static ActMail floor_hit_mes[2] = {{377}, {376}}; /* derived name */

static ActMail cage_mes[2] = {{377}, {376}}; /* derived name */

static ActMail tower_mes[2] = {{377}, {376}}; /* derived name */

static ActMail exit_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chain_main_mes[2] = {{358, actSt10rChainSwitch}, {376}}; /* derived name */

static ActMail chain_mes[2] = {{377}, {376}}; /* derived name */

static ActMail chain_switch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fence_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fence2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fence_down1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fence_up1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail fence_down2_mes[2] = {{377}, {376}}; /* derived name */

/* No .sbss here in this build: no function of the demo addresses such a flag. */

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

/* PAL's girlWayPos is not in this build's .rodata */
/* .sdata: the cage stream handle (actSt10rCageMain's) and the scene stream
   (actSt10rTowerChk's); this build has no floor or chain handle. */
SqEntry *cage10r = 0;

static SqEntry *st10r_adpcm = 0; /* derived name */

INCLUDE_ASM(actSt10rInit);

INCLUDE_ASM(actSt10rFloorChk);

INCLUDE_ASM(actSt10rCageMain);

INCLUDE_ASM(actSt10rTowerChk);

INCLUDE_ASM(actSt10rChainMove);

INCLUDE_ASM(actSt10rFence);

INCLUDE_ASM(actSt10rFloor);

INCLUDE_ASM(actSt10rCage);

INCLUDE_ASM(actSt10rTower);

INCLUDE_ASM(actSt10rExit);

INCLUDE_ASM(actSt10rChain);

INCLUDE_ASM(actSt10rSekizo);

INCLUDE_ASM(actSt10rEnemy1);

INCLUDE_ASM(actSt10rElv);

INCLUDE_ASM(actSt10rGateXL);

INCLUDE_ASM(func_002167D0);

INCLUDE_ASM(actSt10rExitChk);

INCLUDE_ASM(actSt10rChainMain);

INCLUDE_ASM(actSt10rChainSwitch);

void actSt10rSekizoEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(func_00216A00);

INCLUDE_ASM(func_00216AE0);

INCLUDE_ASM(func_00216BB8);

INCLUDE_ASM(actSt10rEneChk);
