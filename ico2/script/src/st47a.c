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

INCLUDE_ASM(actSt47aInit);

INCLUDE_ASM(actSt47aEnd);

INCLUDE_ASM(actSt47aSekizo1Chk);

/* .sdata: the statue's shake and its volume; this build has no statue or
   wing stream handles (the statue and the wings play their streams with no
   handle). */
int sekizo_47a = 0;

unsigned char sekizo_47a_vol = 0;

INCLUDE_ASM(actSt47aHane1Up);

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4. */

/* the table of the process stubbed as actSt47aInit, first in this build's
   run (that process and the one stubbed as actSt47aEnd read as st24a.o's) */
static ActMail init_mes[2] = {{377}, {376}}; /* derived name */

static ActMail sekizo1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail hane1Main_mes[2] = {{356, actSt47aHane1Switch}, {376}}; /* derived name */

static ActMail hane1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail hane1SwitchUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail hane1SwitchDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail hane1Down_mes[2] = {{377}, {376}}; /* derived name */

static ActMail hane1Up_mes[2] = {{377}, {376}}; /* derived name */

static ActMail hane2Main_mes[2] = {{357, actSt47aHane2Switch}, {376}}; /* derived name */

static ActMail hane2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail hane2SwitchUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail hane2SwitchDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail hane2Down_mes[2] = {{377}, {376}}; /* derived name */

static ActMail hane2Up_mes[2] = {{377}, {376}}; /* derived name */

static ActMail rope_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ropeSwing_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ropeSwingDemo_mes[2] = {{377}, {376}}; /* derived name */

static ActMail barricade_mes[2] = {{377}, {376}}; /* derived name */

static ActMail exit_mes[2] = {{377}, {376}}; /* derived name */

static ActMail exit2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

INCLUDE_ASM(actSt47aHane2Up);

INCLUDE_ASM(actSt47aRopeChk);

INCLUDE_ASM(actSt47aEnemy1);

INCLUDE_ASM(actSt47aTorch);

INCLUDE_ASM(actSt47aSekizo1);

INCLUDE_ASM(actSt47aSekizo2);

INCLUDE_ASM(actSt47aSekizo3);

INCLUDE_ASM(actSt47aSekizo4);

INCLUDE_ASM(actSt47aHane1);

INCLUDE_ASM(actSt47aHane2);

INCLUDE_ASM(actSt47aRope);

INCLUDE_ASM(actSt47aBarricade);

void actSt47aRopeSwing(GObj *volatile self) /* derived name */
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(45) == 0) {
        ropeSwing_mes[0].func = actSt47aRopeSwingChk;
        act->mail = ropeSwing_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt47aExit2);

INCLUDE_ASM(actSt47aEne);

INCLUDE_ASM(actSt47aEnemy2);

INCLUDE_ASM(actSt47aEnemy3);

INCLUDE_ASM(actSt47aEnemy4);

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

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    brainUnlockGirl();
}

void actSt47aSekizo2Event(int x)
{
    volatile int local = x;
}

void actSt47aSekizo3Event(int x)
{
    volatile int local = x;
}

void actSt47aSekizo4Event(int x)
{
    volatile int local = x;
}

void actSt47aHane1Main(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    sub->mainMail = hane1Main_mes;
    while (1) {
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt47aHane1Switch);

INCLUDE_ASM(actSt47aHane1Down);

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

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    sub->mainMail = hane2Main_mes;
    while (1) {
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt47aHane2Switch);

void actSt47aHane2Down(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(59, 0, 1, 1, 1);

    stage_SetAnimation(132, 1, 0);

    SetWayGroupActive(34, 1);

    gflagOn(44);

    while (stage_CheckAnimationFinish(132) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    hane2Down_mes[0].func = actSt47aHane2Main;
    act->mail = hane2Down_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt47aHane2Girl(GObj *volatile self)
{
    long long buf[2];
    buf[0] = hane2GirlPos.d[0];
    buf[1] = hane2GirlPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
}

void actSt47aBarricadeEvent(int x)
{
    volatile int local = x;
}

/* The rope swings when the boy strikes it without the sword: the check
   threads the swing and the swing re-arms the check. */
void actSt47aRopeSwingChk(GObj *volatile self) /* derived name */
{
    while (1) {
        if (scpGameStat_BoyWeaponkind() != 4 && scpTriggerBall(self, boyGObj, 100.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(boyGObj) == 39 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 44 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 46 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 40 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 41 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 62)) {
            break;
        }
        _ACTWait(1);
    }

    actCreateSubThread(func_00221858, 21);
}

INCLUDE_ASM(func_00221858);

void actSt47aRopeSwingEvent(int x) /* derived name */
{
    volatile int local = x;
}

void actSt47aBarricadeChk(GObj *volatile self)
{
    GObj *n;

    while ((n = scpIsBombExplode(19)) == 0 || scpTriggerBall(self, n, 500.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    stage_SetAnimation(136, 1, 0);

    gflagOn(46);

    while (stage_CheckAnimationFinish(136) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt47aExitChk(GObj *volatile self)
{
    scpSearchGobj(420)->active = 0;

    while ((gflagChk(148) == 0) || (gflagChk(200) == 0)) {
        _ACTWait(1);
    }

    gflagOn(47);
    scpSearchGobj(419)->active = 0;
    scpSearchGobj(420)->active = 1;
}

void actSt47aExit2Chk(GObj *volatile self)
{
    scpSearchGobj(419)->active = 1;
    scpSearchGobj(420)->active = 0;
}

void actSt47aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    gflagOn(48);
    gflagOn(49);
}
