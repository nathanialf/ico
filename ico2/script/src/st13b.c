#include "st13b.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "jimaku.h"
#include "itou_boss.h"
#include "camera-root.h"
#include "fightSound.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include <libvu0.h>
#include "e3.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static void actSt13bDoorUpSub(GObj *volatile self);
static void actSt13bElev2CharaChk(GObj *volatile self);
static void actSt13bElevUpSub(GObj *volatile self);

/* .sbss: the demo's own end flag and the pad actuator handle and volume byte
   actSt13bConte02 holds (this build has no conte-02 end flag and no door-up
   flag). */
static int demoEnd;

static int padAct; /* derived name */

static unsigned char padActVolume; /* derived name */

/* .data: actor mail packets. */
static ActMail floor_mes[2] = {{377}, {376}}; /* derived name */

static ActMail sekizo_mes[2] = {{377}, {376}}; /* derived name */

static ActMail sekizo2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail meetAgain_mes[2] = {{377}, {376}}; /* derived name */

static ActMail boss_mes[2] = {{377}, {376}}; /* derived name */

static ActMail bossAfter_mes[2] = {{377}, {376}}; /* derived name */

/* actSt13bExit's */
static ActMail exit_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elevMain_mes[2] = {{356, actSt13bElevSwitch}, {376}}; /* derived name */

static ActMail elev_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail elevUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorMain_mes[2] = {{357, actSt13bDoorSwitch}, {376}}; /* derived name */

static ActMail door_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{377}, {376}}; /* derived name */

static float doorUpSubPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f}; /* derived name */

/* .sdata: the scene stream (actSt13bFloorChk, actSt13bConte02), the boss's
   stream handle, the lift's two handles, the statues' shake and volume, the
   lift's shake and volume. This build has no statue, reunion, sound or
   boss-death handle and no boss shake (no function of the demo addresses
   one). */
static SqEntry *st13b_adpcm = 0; /* derived name */

SqEntry *boss = 0;

SqEntry *st13b_up = 0;

SqEntry *st13b_down = 0;

int sekizo_13b = 0;

unsigned char sekizo_13b_vol = 0;

int st13b_yure = 0;

unsigned char st13b_yure_vol = 0;

INCLUDE_ASM(actSt13bFloor);

INCLUDE_ASM(actSt13bFloorChk);

INCLUDE_ASM(actSt13bConte02);

INCLUDE_ASM(actSt13bSekizoChk);

INCLUDE_ASM(actSt13bSekizo2Chk);

INCLUDE_ASM(actSt13bMeetAgain);

static void actSt13bMeetAgainSub(GObj *volatile self);

INCLUDE_ASM(actSt13bBoss);

INCLUDE_ASM(actConte10b);

static void actSt13bElevDownSub(GObj *volatile self);

INCLUDE_ASM(actSt13bElevDown);

INCLUDE_ASM(actSt13bElevUp);

INCLUDE_ASM(actSt13bElevUpChk);

INCLUDE_ASM(actSt13bSekizo);

INCLUDE_ASM(actSt13bSekizo2);

INCLUDE_ASM(actSt13bBossAfter);

INCLUDE_ASM(actSt13bStoneGirl);

INCLUDE_ASM(actSt13bExit);

INCLUDE_ASM(actSt13bElev);

INCLUDE_ASM(actSt13bDoor);

INCLUDE_ASM(actBossTest);

void actSt13bConte02Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 1800:
            jimaku_msg.sub.block = 1;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 2500.0f);
}

void actSt13bSekizo2Event(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt13bMeetAgainChk);

INCLUDE_ASM(actConte10a);

INCLUDE_ASM(actSt13bBossChk);

INCLUDE_ASM(actSt13bBossAfterChk);

INCLUDE_ASM(actConte10c);

INCLUDE_ASM(actSt13bExitChk);

INCLUDE_ASM(actSt13bElevMain);

INCLUDE_ASM(actSt13bElevSwitch);

INCLUDE_ASM(actSt13bDoorMain);

INCLUDE_ASM(actSt13bDoorSwitch);

INCLUDE_ASM(actSt13bDoorUp);
