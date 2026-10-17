#include "st02a.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "box.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "particleLayout.h"
#include "pool.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static void actSt02aFenceOpenSub(GObj *volatile self);
/* .data: one mail record per posting site. Word 0 of each entry is the mail id
 * the entry answers (430 the actor post, 429 the trailing entry); .func is
 * filled in at run time before the post, except in the two main-mail records,
 * which answer 406 and 407 with their switch threads. Each record is named for
 * the thread that owns and posts it; where one thread owns two, for the
 * watcher it installs. */
void actSt02aFenceSwitch(GObj *volatile self);
void actSt02aGondolaSwitch(GObj *volatile self);

static ActMail door_down_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail door_up_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail door_up_chk_mail[2] = {{377}, {376}}; /* derived name */

static ActMail door_down_chk_mail[2] = {{377}, {376}}; /* derived name */

static ActMail fence_main_mail[2] = {{356, actSt02aFenceSwitch}, {376}}; /* derived name */

static ActMail fence_mail[2] = {{377}, {376}}; /* derived name */

static ActMail fence_switch_mail[2] = {{377}, {376}}; /* derived name */

static ActMail waterfall_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_main_mail[2] = {{357, actSt02aGondolaSwitch}, {376}}; /* derived name */

static ActMail gondola_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_switch_down_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_switch_up_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_up_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_down_mail[2] = {{377}, {376}}; /* derived name */

static ActMail ene_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_off_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_on_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_on_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_off_mail[2] = {{377}, {376}}; /* derived name */

static ActMail taki_way_mail[2] = {{377}, {376}}; /* derived name */

/* The two-part door's SE position, copied into the local the sound call reads. */
static const ConstVec doorSePos = {{-1823.0f, -1174.0f, 2429.0f, 0.0f}}; /* derived name */

/* The door's two effect positions; the up sequence plays them in this order and
 * the down sequence in the other.  ico2/script/src/st08b.c carries the same two
 * points for its own door. */
static const ConstVec doorUpEffectPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect2Pos = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

/* The two boundary points the boy's splash check tests against. */
static const ConstVec boySplashPos[2] = {{{840.0f, 235.0f, 560.0f, 1.0f}},
                                         {{740.0f, 235.0f, 560.0f, 1.0f}}};

/* The waterfall's reflection mesh and the layout quad it is stretched over:
 * the quad drops from y 280 to y 0, the falling water.  This build has one
 * mesh and one quad (PAL adds the pool's).  The value at offset 0x1C is a
 * hardware field. */
static const PoolMesh fallReflactionMesh = {40, 20, 0, 0, 0, 0, 0, 0x60687080}; /* derived name */

static const PoolMeshQuad fallReflactionQuad = {{{650.0f, 280.0f, 550.0f, 1.0f},
                                                 {650.0f, 0.0f, 700.0f, 1.0f},
                                                 {900.0f, 280.0f, 550.0f, 1.0f},
                                                 {900.0f, 0.0f, 700.0f, 1.0f}}};

INCLUDE_ASM(actSt02aDoorUpChk);

INCLUDE_ASM(actSt02aDoorDownChk);

/* .sdata */
SqEntry *st02a_fence = 0;

/* No .sbss here in this build: no function of the demo addresses such a flag. */

void actSt02aFenceOpen(GObj *volatile self);

INCLUDE_ASM(actSt02WaterFallBoySplashCheck);

INCLUDE_ASM(actSt02aWaterFallChk);

SqEntry *gondola = 0;

INCLUDE_ASM(actSt02aGondolaUp);

SqEntry *gondola_test = 0;

INCLUDE_ASM(actSt02aGondolaDown);

INCLUDE_ASM(func_001FEBA8);

INCLUDE_ASM(actSt02aBox);

INCLUDE_ASM(actSt02aGondola);

INCLUDE_ASM(actSt02aFence);

INCLUDE_ASM(actSt02aObj1518);

INCLUDE_ASM(func_001FF110);

INCLUDE_ASM(actSt02aWaterFall);

INCLUDE_ASM(actSt02aBoxEvent2);

INCLUDE_ASM(actSt02aEne);

INCLUDE_ASM(actSt02aEnemy1);

INCLUDE_ASM(actSt02aEnemy2);

INCLUDE_ASM(actSt02aSekizo);

INCLUDE_ASM(actSt02aWay);

void actSt02aDoorEvent(int x)
{
    volatile int local = x;
}

void actSt02aDoorUpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorUpEffectPos.d[0];
    long long v0b = doorUpEffect2Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffectPos.d[1];
            scpEffectStart(b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorUpEffect2Pos.d[1];
            scpEffectStart(b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt02aDoorDownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorUpEffect2Pos.d[0];
    long long v0b = doorUpEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffect2Pos.d[1];
            scpEffectStart(b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorUpEffectPos.d[1];
            scpEffectStart(b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt02aFenceMain);

INCLUDE_ASM(actSt02aFenceSwitch);

INCLUDE_ASM(func_001FF790);

INCLUDE_ASM(func_001FF838);

INCLUDE_ASM(actSt02aWaterFallReflactionEffect);

INCLUDE_ASM(actSt02aGondolaMain);

INCLUDE_ASM(actSt02aGondolaSwitch);

INCLUDE_ASM(func_001FFA68);

INCLUDE_ASM(actSt02aEneChk);

INCLUDE_ASM(actSt02aSekizoEvent);

INCLUDE_ASM(actSt02aTakiWayOnChk);

INCLUDE_ASM(actSt02aTakiWayOffChk);
