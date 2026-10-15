#include "st06a.h"
#include "debug.h"
#include "layout_texture.h"
#include "thread.h"
#include "obj_manager.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "box.h"
#include "geometryManager.h"
#include "item.h"
#include "motionManager2.h"
#include "rotObject.h"
#include "typedef.h"
#include "stageSEProc.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt06aJumpMain(GObj *volatile self);
static void actSt06aJumpSwitch(GObj *volatile self);
static void actSt06aKyomiOffChk(GObj *volatile self);
static void actSt06aPistonRideOnChk(GObj *volatile self);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copies read. */

static const ConstVec doorUpEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec suimonSubPos = {{-1869.0f, -1147.0f, -664.0f, 0.0f}}; /* derived name */

static const ConstVec jumpPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec jumpPos2 = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec kyomiPos = {{-985.0f, -177.0f, -696.0f, 0.0f}}; /* derived name */

/* st06a.c's `inline` functions, in the order of their definitions'
   out-of-line copies at the end of the object (first-declaration order). */
static inline void actSt06aSoundChk(GObj *volatile self);
static inline void actSt06aSound2Chk(GObj *volatile self);

static ActMail suimon_mes[2] = {{397}, {396}}; /* derived name */

static ActMail tree_mes[2] = {{397}, {396}}; /* derived name */

static ActMail jump_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door_down_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door_up_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door_upchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door_dnchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail shutter_main_mes[2] = {{376, actSt06aShutterSwitch}, {396}}; /* derived name */

static ActMail shutter_mes[2] = {{397}, {396}}; /* derived name */

static ActMail shutter_switch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail piston_mes[2] = {{397}, {396}}; /* derived name */

static ActMail piston_flag_mes[2] = {{397}, {396}}; /* derived name */

static ActMail piston_flag_onchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail piston_flag_offchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sound_mes[2] = {{397}, {396}}; /* derived name */

static ActMail D_004D2730[2] = {{397}, {396}}; /* derived name */

static ActMail box_event2_in_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box_event2_out_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box_event2_inchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box_event2_out_chk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail way_mes[2] = {{397}, {396}}; /* derived name */

static ActMail way_onchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail way_offchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way_on_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way_off_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way_onchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way_offchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way2_on_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way2_off_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way2_onchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wall_way2_offchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail D_004D2930[2] = {{397}, {396}}; /* derived name */

static ActMail sound2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail D_004D2970[2] = {{397}, {396}}; /* derived name */

static ActMail kyomi_mes[2] = {{397}, {396}}; /* derived name */

static ActMail kyomi_onchk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail kyomi_off_chk_mes[2] = {{397}, {396}}; /* derived name */

/* .sdata: the sluice, shutter and spike stream handles. */
SqEntry *suimon = 0;

SqEntry *shutter = 0;

SqEntry *toge = 0;

INCLUDE_ASM(actSt06aTree);

INCLUDE_ASM(func_00225DA0);

INCLUDE_ASM(func_00225DD0);

INCLUDE_ASM(func_00225E28);

INCLUDE_ASM(func_00225EF0);

INCLUDE_ASM(actSt06aInit);

INCLUDE_ASM(actSt06aJump);

INCLUDE_ASM(func_002260A8);

INCLUDE_ASM(actSt06aDoor);

INCLUDE_ASM(func_00226300);

INCLUDE_ASM(func_00226478);

INCLUDE_ASM(func_002265F0);

INCLUDE_ASM(func_002266D0);

INCLUDE_ASM(func_002267E8);

INCLUDE_ASM(func_00226958);

INCLUDE_ASM(actSt06aShutter);

INCLUDE_ASM(actSt06aPiston);

INCLUDE_ASM(actSt06aPistonFlag);

INCLUDE_ASM(actSt06aPistonFlagOnChk);

INCLUDE_ASM(actSt06aPistonFlagOffChk);

INCLUDE_ASM(actSt06aSound);

INCLUDE_ASM(actSt06aBoxEvent2);

INCLUDE_ASM(actSt06aWay);

INCLUDE_ASM(actSt06aWallWay);

INCLUDE_ASM(actSt06aWallWay2);

INCLUDE_ASM(actSt06aProc_002270A8);

INCLUDE_ASM(actSt06aSound2);

INCLUDE_ASM(actSt06aProc_002271E8);

INCLUDE_ASM(actSt06aProc_00227280);

INCLUDE_ASM(actSt06aKyomi);

void actSt06aSuimonEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt06aSuimonEffect);

INCLUDE_ASM(func_00227478);

void actSt06aDoorEvent(int x)
{
    volatile int local = x;
}

void actSt06aDoorUpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = jumpPos.d[0];
    long long v0b = jumpPos2.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = jumpPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = jumpPos2.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt06aDoorDownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = jumpPos2.d[0];
    long long v0b = jumpPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = jumpPos2.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = jumpPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt06aShutterMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = shutter_main_mes;

    while (1) {
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt06aShutterSwitch);

INCLUDE_ASM(actSt06aExitChk);

INCLUDE_ASM(func_002277C0);

INCLUDE_ASM(actSt06aBox2Chk);

INCLUDE_ASM(actSt06aBox3Chk);

INCLUDE_ASM(actSt06aBallDeleteChk);

INCLUDE_ASM(actSt06aBoxEvent2InChk);

INCLUDE_ASM(actSt06aBoxEvent2OutChk);

INCLUDE_ASM(actSt06aWayOnChk);

INCLUDE_ASM(actSt06aWayOffChk);

INCLUDE_ASM(actSt06aWallWayOnChk);

INCLUDE_ASM(actSt06aWallWayOffChk);

INCLUDE_ASM(actSt06aWallWay2OnChk);

INCLUDE_ASM(actSt06aWallWay2OffChk);

INCLUDE_ASM(actSt06aTreeChk);

INCLUDE_ASM(actSt06aKyomiOnChk);

INCLUDE_ASM(actSt06aKyomiOffChk);

INCLUDE_ASM(actSt07aInit);
