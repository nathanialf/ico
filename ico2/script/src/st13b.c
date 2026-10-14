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
static void actSt13bElevUpSub(GObj *volatile self);

/* .sbss: the demo's own end flag, the conte-02 end flag, the pad actuator
   handle and volume byte the door-up subthread holds, and the flag
   actSt13bDoorUpSub raises when the door is up. */
static int demoEnd;

static int conte02End; /* derived name */

static int padAct; /* derived name */

static unsigned char padActVolume; /* derived name */

static int doorUpDone; /* derived name */

/* .data: actor mail packets. */
static ActMail floor_mes[2] = {{393}, {392}}; /* derived name */

static ActMail sekizo_mes[2] = {{393}, {392}}; /* derived name */

static ActMail sekizo2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail meetAgain_mes[2] = {{393}, {392}}; /* derived name */

static ActMail boss_mes[2] = {{393}, {392}}; /* derived name */

static ActMail bossAfter_mes[2] = {{393}, {392}}; /* derived name */

static ActMail exit_mes[2] = {{393}, {392}}; /* derived name */

static ActMail elevMain_mes[2] = {{372, actSt13bElevSwitch}, {392}}; /* derived name */

static ActMail elev_mes[2] = {{393}, {392}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail elevUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorMain_mes[2] = {{373, actSt13bDoorSwitch}, {392}}; /* derived name */

static ActMail door_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{393}, {392}}; /* derived name */

static float doorUpSubPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f}; /* derived name */

/* .sdata: the scene stream, the stream handles and shakes, then a further
   shake and volume. */
static SqEntry *st13b_adpcm = 0; /* derived name */

SqEntry *sekizo13b = 0;

SqEntry *sekizo13b2 = 0;

SqEntry *meets_again = 0;

SqEntry *boss = 0;

SqEntry *sd = 0;

SqEntry *boss_dead = 0;

SqEntry *st13b_up = 0;

SqEntry *st13b_down = 0;

SqEntry *sekizo_13b = 0;

SqEntry *sekizo_13b_vol = 0;

int st13b_yure = 0;

unsigned char st13b_yure_vol = 0;

static int st13b_boss_yure = 0; /* derived name */

static unsigned char st13b_boss_yure_vol = 0; /* derived name */

INCLUDE_ASM(actSt13bFloor);

INCLUDE_ASM(actSt13bFloorChk);

INCLUDE_ASM(actSt13bConte02);

INCLUDE_ASM(actSt13bSekizoChk);

INCLUDE_ASM(actSt13bSekizo2Chk);

INCLUDE_ASM(actSt13bMeetAgain);

static void actSt13bMeetAgainSub(GObj *volatile self);

INCLUDE_ASM(actSt13bBoss);

static void actSt13bElevDownSub(GObj *volatile self);

INCLUDE_ASM(actConte10b);

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
