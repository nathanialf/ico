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

/* .sbss: the conte-02 end flag, and the pad actuator handle and volume byte
   the door-up subthread holds. */
static int conte02End; /* derived name */

static int padAct; /* derived name */

static unsigned char padActVolume; /* derived name */

/* the elevator-down and door-up threads the switches start */
void func_00230D18(GObj *volatile self);
void func_002319E0(GObj *volatile self);

/* .data: actor mail packets. */
static ActMail floor_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sekizo2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail meetAgain_mes[2] = {{397}, {396}}; /* derived name */

static ActMail boss_mes[2] = {{397}, {396}}; /* derived name */

static ActMail bossAfter_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elevMain_mes[2] = {{376, actSt13bElevSwitch}, {396}}; /* derived name */

static ActMail elev_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail elevUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorMain_mes[2] = {{377, actSt13bDoorSwitch}, {396}}; /* derived name */

static ActMail door_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{397}, {396}}; /* derived name */

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

INCLUDE_ASM(actSt13bBoss);

INCLUDE_ASM(func_00230B38);

INCLUDE_ASM(func_00230C38);

INCLUDE_ASM(func_00230D18);

INCLUDE_ASM(actSt13bElevUp);

INCLUDE_ASM(func_00230F78);

INCLUDE_ASM(actSt13bSekizo);

INCLUDE_ASM(actSt13bSekizo2);

INCLUDE_ASM(actSt13bBossAfter);

INCLUDE_ASM(actSt13bStoneGirl);

INCLUDE_ASM(actSt13bElev);

void actSt13bDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(16) == 0) {
        stage_SetAnimation(40, 0, 0);

        door_mes[0].func = actSt13bDoorMain;
        act->mail = door_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(40, 0, -1);
    }
}

void actBossTest(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    stage_SetAnimation(31, 0, -1);
    stage_SetAnimation(25, 0, 0);
    stage_SetAnimation(34, 0, 0);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(37, 0, 0);
}

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

INCLUDE_ASM(func_002315D8);

INCLUDE_ASM(func_00231690);

INCLUDE_ASM(func_00231748);

INCLUDE_ASM(func_00231818);

void actSt13bElevMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = elevMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13bElevSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    elevSwitch_mes[0].func = func_00230D18;
    sub->mail = elevSwitch_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt13bDoorMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = doorMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13bDoorSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    doorSwitch_mes[0].func = func_002319E0;
    sub->mail = doorSwitch_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

INCLUDE_ASM(func_002319E0);
