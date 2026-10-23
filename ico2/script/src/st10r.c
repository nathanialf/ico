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

static ActMail floor_mes[2] = {{393}, {392}}; /* derived name */

static ActMail cage_mes[2] = {{393}, {392}}; /* derived name */

static ActMail tower_mes[2] = {{393}, {392}}; /* derived name */

static ActMail exit_mes[2] = {{393}, {392}}; /* derived name */

static ActMail chain_main_mes[2] = {{374, actSt10rChainSwitch}, {392}}; /* derived name */

static ActMail chain_mes[2] = {{393}, {392}}; /* derived name */

static ActMail chain_switch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fence_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fence2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fence_down1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fence_up1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fence_down2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail fence_up2_mes[2] = {{393}, {392}}; /* derived name */

/* .sbss: the demo's own end flag, raised by the subthreads the wait loops
   below spin for. */
static int demoEnd;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{-296.0f, 327.0f, 2125.0f, 0.0f}}; /* derived name */

/* .sdata: the floor and cage stream handles, the scene stream, the chain's. */
SqEntry *st10r_floor = 0;

SqEntry *cage10r = 0;

static SqEntry *st10r_adpcm = 0; /* derived name */

SqEntry *chain10r = 0;

INCLUDE_ASM(actSt10rInit);

INCLUDE_ASM(actSt10rFloorChk);

INCLUDE_ASM(actSt10rCageMain);

INCLUDE_ASM(actSt10rTowerChk);

INCLUDE_ASM(actSt10rTowerConte);

INCLUDE_ASM(actSt10rChainMove);

INCLUDE_ASM(actSt10rFence);

INCLUDE_ASM(actSt10rFenceDownChk);

INCLUDE_ASM(actSt10rFenceUpChk);

INCLUDE_ASM(actSt10rFenceDownChk2);

INCLUDE_ASM(actSt10rFenceUpChk2);

INCLUDE_ASM(actSt10rFloor);

INCLUDE_ASM(actSt10rCage);

INCLUDE_ASM(actSt10rTower);

INCLUDE_ASM(actSt10rExit);

INCLUDE_ASM(actSt10rChain);

INCLUDE_ASM(actSt10rSekizo);

INCLUDE_ASM(actSt10rEne);

INCLUDE_ASM(actSt10rEnemy1);

INCLUDE_ASM(actSt10rEnemy2);

INCLUDE_ASM(actSt10rElv);

INCLUDE_ASM(actSt10rGateXL);

void actSt10rGirlWay(volatile unsigned int self)
{
    long long buf[2];
    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
    _ACTWait(0);
}

INCLUDE_ASM(actSt10rExitChk);

void actSt10rChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;
    sub->mainMail = chain_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt10rChainSwitch);

void actSt10rSekizoEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt10rEneChk);
