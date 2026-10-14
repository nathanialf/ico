#include "st47a.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "brain.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "item.h"
#include "motionManager2.h"
#include <libvu0.h>
#include <string.h>
#include "typedef.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt47aHint2OnChk(GObj *volatile self);
static void actSt47aRopeSub(GObj *volatile self);

INCLUDE_ASM(actSt47aInit);

void actSt47aEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(52) == 0) {
            gflagOn(391);
        }
    }
}

/* .sdata: the statue and wing stream handles and the statue's shake. */
SqEntry *sekizo47a = 0;

SqEntry *hane1up = 0;

SqEntry *hane2up = 0;

SqEntry *hane1down = 0;

SqEntry *hane2down = 0;

int sekizo_47a = 0;

unsigned char sekizo_47a_vol = 0;

INCLUDE_ASM(actSt47aSekizo1Chk);

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4. */

static ActMail sekizo1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hane1Main_mes[2] = {{406, actSt47aHane1Switch}, {429}}; /* derived name */

static ActMail hane1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hane1SwitchUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hane1SwitchDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hane1Down_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hane1Up_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hane2Main_mes[2] = {{407, actSt47aHane2Switch}, {429}}; /* derived name */

static ActMail hane2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hane2SwitchUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hane2SwitchDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hane2Down_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hane2Up_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope_mes[2] = {{430}, {429}}; /* derived name */

static ActMail barricade_mes[2] = {{430}, {429}}; /* derived name */

static ActMail exit_mes[2] = {{430}, {429}}; /* derived name */

static ActMail exit2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint2On_mes[2] = {{430}, {429}}; /* derived name */

INCLUDE_ASM(actSt47aHane1Down);

INCLUDE_ASM(actSt47aHane1Up);

INCLUDE_ASM(actSt47aHane2Down);

INCLUDE_ASM(actSt47aHane2Up);

INCLUDE_ASM(actSt47aRope);

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for. */
static int demoEnd;

INCLUDE_ASM(actSt47aRopeChk);

INCLUDE_ASM(actSt47aBarricadeChk);

void actSt47aEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(513));

    while (gflagChk(53) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);

    Generator_Call(scpSearchGobj(513));
}

void actSt47aTorch(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(153) != 0) {
        scpTorchLightOn(489);
        scpTorchLightOn(490);
        scpTorchLightOn(491);
        scpTorchLightOn(492);
        scpTorchLightOn(493);
        scpTorchLightOn(494);
        scpTorchLightOn(495);
        scpTorchLightOn(496);
        scpTorchLightOn(497);
        scpTorchLightOn(498);
        scpTorchLightOn(499);
        scpTorchLightOn(500);
        scpTorchLightOn(501);
        scpTorchLightOn(502);
    }
}

INCLUDE_ASM(actSt47aSekizo1);

INCLUDE_ASM(actSt47aSekizo2);

void actSt47aHane1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    gflagChk(47);

    hane1_mes[0].func = actSt47aHane1Main;
    act->mail = hane1_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt47aHane2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    hane2_mes[0].func = actSt47aHane2Main;
    act->mail = hane2_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

INCLUDE_ASM(actSt47aBarricade);

void actSt47aExit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    exit_mes[0].func = actSt47aExitChk;
    act->mail = exit_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt47aExit2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(144) != 0) {
        exit2_mes[0].func = actSt47aExit2Chk;
        act->mail = exit2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt47aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(52) == 0) {
        ene_mes[0].func = actSt47aEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt47aEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(53) == 0) {
        _ACTWait(1);
    }
    _ACTWait(180);

    Generator_MaskOff(self);
    Generator_Call(self);

    _ACTWait(60);

    Generator_Call(self);
}

void actSt47aEnemy3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(53) == 0) {
        _ACTWait(1);
    }
    _ACTWait(180);

    Generator_MaskOff(self);
    Generator_Call(self);

    _ACTWait(60);

    Generator_Call(self);
}

void actSt47aEnemy4(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(53) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);
}

void actSt47aHint2On(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(54) == 0) {
        SleepHint(5);

        hint2On_mes[0].func = actSt47aHint2OnChk;
        act->mail = hint2On_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt47aSekizo1Event(int x)
{
    volatile int local = x;
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{2266.0f, -272.0f, 0.0f, 0.0f}}; /* derived name */

static const ConstVec hane1_1GirlPos = {{-1076.0f, -1972.0f, 755.0f, 0.0f}}; /* derived name */

static const ConstVec hane1_2GirlPos = {{1028.0f, -1972.0f, 744.0f, 0.0f}}; /* derived name */

static const ConstVec hane2GirlPos = {{-1031.0f, -1972.0f, -747.0f, 0.0f}}; /* derived name */

void actSt47aGirlWay(GObj *volatile self)
{
    long long buf[2];
    long long way[2];

    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);

    memset(way, 0, 16);
    RequestStageChangeDirect(girlGObj, 11, way, 180);
    brainUnlockGirl();
}

void actSt47aSekizo2Event(int x)
{
    volatile int local = x;
}

void actSt47aHane1Main(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = hane1Main_mes;
    while (1) {
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt47aHane1Switch);

void actSt47aHane1_1Girl(GObj *volatile self)
{
    long long buf[2];
    buf[0] = hane1_1GirlPos.d[0];
    buf[1] = hane1_1GirlPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
}

void actSt47aHane1_2Girl(GObj *volatile self)
{
    long long buf[2];
    buf[0] = hane1_2GirlPos.d[0];
    buf[1] = hane1_2GirlPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
}

void actSt47aHane2Main(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = hane2Main_mes;
    while (1) {
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt47aHane2Switch);

void actSt47aHane2Girl(GObj *volatile self)
{
    long long buf[2];
    buf[0] = hane2GirlPos.d[0];
    buf[1] = hane2GirlPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
}

INCLUDE_ASM(actSt47aRopeSub);

void actSt47aBarricadeEvent(int x)
{
    volatile int local = x;
}

void actSt47aExitChk(GObj *volatile self)
{
    scpSearchGobj(481)->active = 0;

    while ((gflagChk(174) == 0) || (gflagChk(234) == 0)) {
        _ACTWait(1);
    }

    gflagOn(51);
    scpSearchGobj(480)->active = 0;
    scpSearchGobj(481)->active = 1;
}

void actSt47aExit2Chk(GObj *volatile self)
{
    scpSearchGobj(480)->active = 1;
    scpSearchGobj(481)->active = 0;
}

void actSt47aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOff(391);
    _ACTWait(1);
    gflagOn(52);
    gflagOn(53);
}

static void actSt47aHint2OnChk(GObj *volatile self)
{
    while (gflagChk(47) == 0) {
        _ACTWait(1);
    }

    gflagOn(54);
    WakeupHint(5);
}
