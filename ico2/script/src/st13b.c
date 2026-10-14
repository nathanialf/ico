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

/* .sbss: the demo's own end flag, the conte-02 end flag, the pad actuator
   handle and volume byte the door-up subthread holds, and the flag
   actSt13bDoorUpSub raises when the door is up. */
static int demoEnd;

static int conte02End; /* derived name */

static int padAct; /* derived name */

static unsigned char padActVolume; /* derived name */

static int doorUpDone; /* derived name */

/* .data: actor mail packets. */
static ActMail floor_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail meetAgain_mes[2] = {{430}, {429}}; /* derived name */

static ActMail boss_mes[2] = {{430}, {429}}; /* derived name */

static ActMail bossAfter_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elevMain_mes[2] = {{406, actSt13bElevSwitch}, {429}}; /* derived name */

static ActMail elev_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elevSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elevUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorMain_mes[2] = {{407, actSt13bDoorSwitch}, {429}}; /* derived name */

static ActMail door_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorSwitch_mes[2] = {{430}, {429}}; /* derived name */

static float doorUpSubPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f}; /* derived name */

static ActMail elev2Chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elev2Chk2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elev2Chara_mes[2] = {{430}, {429}}; /* derived name */

static ActMail elev2CharaChk_mes[2] = {{430}, {429}}; /* derived name */

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

void actSt13bFloorChk(GObj *volatile self)
{
    int v = 32;

    gflagOn(5);
    actCreateSubThread(actSt13bConte02, 21);
    actCreateSubThread(actSt13bConte02Jimaku, 21);

    conte02End = 0;
    st13b_adpcm = 0;

    do {
        _ACTWait(1);
    } while (st13b_adpcm == 0);

    while (conte02End == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (conte02End == 0) {
        v = 64;
    }

    if (st13b_adpcm != 0) {
        scpAdpcmFadeCloseFunc(&st13b_adpcm, v);
    }

    RequestStageChange(4, boyGObj, 0, 0.025f, 2.0f);
}

INCLUDE_ASM(actSt13bConte02);

void actSt13bSekizoChk(GObj *volatile self);

INCLUDE_ASM(actSt13bSekizoChk);

void actSt13bSekizo2Chk(GObj *volatile self);

INCLUDE_ASM(actSt13bSekizo2Chk);

void actSt13bMeetAgain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(12) == 0) {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);

        meetAgain_mes[0].func = actSt13bMeetAgainChk;
        act->mail = meetAgain_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
    }
}

INCLUDE_ASM(actSt13bMeetAgainSub);

INCLUDE_ASM(actSt13bMeetAgainChk);

void actSt13bBoss(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    ScpCallCameraSetTarget(-1886.0f, 625.0f, -4.0f);
    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    if (gflagChk(13) == 0) {
        scpSearchGobj(2470)->active = 0;
        boss_mes[0].func = actSt13bBossChk;
        act->mail = boss_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else if (gflagChk(14) == 0) {
        scpAdpcmPlayRequestFunc(37, &boss, 1, 0, 1);
        scpSeEnvMasterVolRate = 0.5f;
    }
}

void actSt13bBossChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(13);
    scpAdpcmPlayRequestFunc(36, &sd, 1, 1, 1);

    while (sd == 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(37, &boss, 1, 0, 0);
    scpSeEnvMasterVolRate = 0.5f;

    scpSearchGobj(2470)->active = 1;
    scpPlayPosSet(scpSearchGobj(2470), 0.0f, -100.0f, 0.0f);

    scpPlayMot(scpSearchGobj(2464), 834);
    scpPlayMot(scpSearchGobj(2465), 834);
    scpPlayMot(scpSearchGobj(2466), 834);
    scpPlayMot(scpSearchGobj(2467), 834);
    scpPlayMot(scpSearchGobj(2468), 834);
    scpPlayMot(scpSearchGobj(2469), 834);

    CapsuleGhostBossStart();

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    while (boss == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(boss->stream);
}

void actSt13bBossAfterChk(GObj *volatile self);

INCLUDE_ASM(actSt13bBossAfterChk);

static void actSt13bElevDownSub(GObj *volatile self)
{
    stage_SetAnimation(40, 1, 235);

    while (stage_CheckAnimationFrame(40, 321, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_CheckAnimationFrame(40, 350, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13b_boss_yure = iosPadActRequest(boyPad, 9);
    st13b_boss_yure_vol = 128;
    iosPadActVolumeSet(st13b_boss_yure, 128);

    while (stage_CheckAnimationFrame(40, 450, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt13bElevDown(GObj *volatile self);

INCLUDE_ASM(actSt13bElevDown);

INCLUDE_ASM(actSt13bElevUp);

INCLUDE_ASM(actSt13bElevUpChk);

void actSt13bDoorUp(GObj *volatile self);

INCLUDE_ASM(actSt13bDoorUp);

static void actSt13bElev2Chk(GObj *volatile self);

INCLUDE_ASM(actSt13bElev2Chk);

void actSt13bSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(10) == 0) {
        stage_SetAnimation(33, 0, 0);

        sekizo_mes[0].func = actSt13bSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(33, 0, -1);
    }
}

void actSt13bSekizo2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(11) == 0) {
        stage_SetAnimation(34, 0, 0);

        sekizo2_mes[0].func = actSt13bSekizo2Chk;
        act->mail = sekizo2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(34, 0, -1);
    }
}

void actSt13bBossAfter(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(14) == 0) {
        stage_SetAnimation(35, 0, 0);

        bossAfter_mes[0].func = actSt13bBossAfterChk;
        act->mail = bossAfter_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(35, 0, -1);
    }
}

void actSt13bStoneGirl(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (current_stage_no == 46) {
        scpPlayMot(scpSearchGobj(2462), 808);
        scpSearchGobj(2462)->active = 1;
    }
}

void actSt13bElev(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    elev_mes[0].func = actSt13bElevMain;
    act->mail = elev_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt13bElev2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(16) != 0) {
        stage_SetAnimation(42, 0, 0);

        elev2Chk_mes[0].func = actSt13bElev2Chk;
        act->mail = elev2Chk_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(41, 0, 0);

        elev2Chk2_mes[0].func = actSt13bElev2Chk;
        act->mail = elev2Chk2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt13bDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(17) == 0) {
        stage_SetAnimation(43, 0, 0);

        door_mes[0].func = actSt13bDoorMain;
        act->mail = door_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(43, 0, -1);
    }
}

void actBossTest(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    stage_SetAnimation(32, 0, -1);
    stage_SetAnimation(26, 0, 0);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(36, 0, 0);
    stage_SetAnimation(38, 0, 0);
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

INCLUDE_ASM(actConte10c);

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

    elevSwitch_mes[0].func = actSt13bElevDown;
    sub->mail = elevSwitch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt13bElevUpSub(GObj *volatile self)
{
    stage_SetAnimation(40, 1, 0);
    st13b_boss_yure = iosPadActRequest(boyPad, 9);
    st13b_boss_yure_vol = 128;
    iosPadActVolumeSet(st13b_boss_yure, 128);
    while (stage_CheckAnimationFrame(40, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    iosPadActStop(st13b_boss_yure);
    while (stage_CheckAnimationFrame(40, 234, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
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

    doorSwitch_mes[0].func = actSt13bDoorUp;
    sub->mail = doorSwitch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt13bDoorUpSub(GObj *volatile self)
{
    _ACTWait(60);

    stage_SetAnimation(43, 1, 0);

    _ACTWait(120);

    soundSeDefPlay(1221, 0, doorUpSubPos, 1);

    _ACTWait(30);

    doorUpDone = 1;
    soundSeDefPlay(1222, 0, doorUpSubPos, 1);

    while (stage_CheckAnimationFinish(43) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

static void actSt13bElev2CharaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0x4000000) != 0) {
        _ACTWait(1);
    }

    elev2CharaChk_mes[0].func = actSt13bElev2Chk;
    sub->mail = elev2CharaChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
