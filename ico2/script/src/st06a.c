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
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt06aBoxSub(GObj *volatile self);
static void actSt06aShutterOpenSub(GObj *volatile self);
static void actSt06aSuimonSub(GObj *volatile self);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copies read. */

static const ConstVec doorUpEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec suimonSubPos = {{-1869.0f, -1147.0f, -664.0f, 0.0f}}; /* derived name */

static const ConstVec jumpPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec jumpPos2 = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

static ActMail suimon_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door_down_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door_up_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door_upchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail door_dnchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail shutter_main_mes[2] = {{372, actSt06aShutterSwitch}, {392}}; /* derived name */

static ActMail shutter_mes[2] = {{393}, {392}}; /* derived name */

static ActMail shutter_switch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail exit_mes[2] = {{393}, {392}}; /* derived name */

static ActMail box_mes[2] = {{393}, {392}}; /* derived name */

static ActMail box2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail box3_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ball_delete_mes[2] = {{393}, {392}}; /* derived name */

static ActMail box_event2_in_mes[2] = {{393}, {392}}; /* derived name */

static ActMail box_event2_out_mes[2] = {{393}, {392}}; /* derived name */

static ActMail box_event2_inchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail box_event2_out_chk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail way_mes[2] = {{393}, {392}}; /* derived name */

static ActMail way_onchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail way_offchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wall_way_on_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wall_way_off_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wall_way_onchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wall_way_offchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wall_way2_on_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wall_way2_off_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wall_way2_onchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wall_way2_offchk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail statue_mes[2] = {{393}, {392}}; /* derived name */

static ActMail head_mes[2] = {{393}, {392}}; /* derived name */

static ActMail tree_mes[2] = {{393}, {392}}; /* derived name */

INCLUDE_ASM(actSt06aInit);

INCLUDE_ASM(actSt06aSuimon);

/* .sdata: the sluice, shutter and spike stream handles. */
SqEntry *suimon = 0;

SqEntry *shutter = 0;

SqEntry *toge = 0;

INCLUDE_ASM(actSt06aSuimonChk);

INCLUDE_ASM(actSt06aDoor);

INCLUDE_ASM(actSt06aDoorUpChk);

INCLUDE_ASM(actSt06aDoorDownChk);

INCLUDE_ASM(actSt06aShutterOpen);

INCLUDE_ASM(actSt06aBoxChk);

INCLUDE_ASM(actSt06aStatueChk);

INCLUDE_ASM(actSt06aHeadChk);

INCLUDE_ASM(actSt06aShutter);

INCLUDE_ASM(actSt06aExit);

INCLUDE_ASM(actSt06aBox);

INCLUDE_ASM(actSt06aBox2);

INCLUDE_ASM(actSt06aBox3);

INCLUDE_ASM(actSt06aBoxEvent2);

INCLUDE_ASM(actSt06aWay);

INCLUDE_ASM(actSt06aWallWay);

INCLUDE_ASM(actSt06aWallWay2);

INCLUDE_ASM(actSt06aStatue);

INCLUDE_ASM(actSt06aHead);

INCLUDE_ASM(actSt06aTree);

INCLUDE_ASM(actSt06aBallDelete);

void actSt06aSuimonEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt06aSuimonEffect);

INCLUDE_ASM(actSt06aSuimonFlagOn);

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

INCLUDE_ASM(actSt06aShutterMain);

INCLUDE_ASM(actSt06aShutterSwitch);

INCLUDE_ASM(actSt06aExitChk);

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
