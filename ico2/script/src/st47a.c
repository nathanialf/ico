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

INCLUDE_ASM(actSt47aInit);

INCLUDE_ASM(actSt47aEnd);

/* .sdata: the statue and wing stream handles and the statue's shake. */
SqEntry *sekizo47a = 0;

SqEntry *hane1up = 0;

SqEntry *hane2up = 0;

SqEntry *hane1down = 0;

SqEntry *hane2down = 0;

int sekizo_47a = 0;

unsigned char sekizo_47a_vol = 0;

INCLUDE_ASM(actSt47aSekizo1Chk);

INCLUDE_ASM(func_00239B50);

INCLUDE_ASM(func_00239C58);

INCLUDE_ASM(func_00239DA8);

INCLUDE_ASM(func_00239EB0);

INCLUDE_ASM(func_00239FE0);

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4. */

static ActMail sekizo1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hane1Main_mes[2] = {{376, actSt47aHane1Switch}, {396}}; /* derived name */

static ActMail hane1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hane1SwitchUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hane1SwitchDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hane1Down_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hane1Up_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hane2Main_mes[2] = {{377, actSt47aHane2Switch}, {396}}; /* derived name */

static ActMail hane2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hane2SwitchUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hane2SwitchDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hane2Down_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hane2Up_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope_mes[2] = {{397}, {396}}; /* derived name */

static ActMail barricade_mes[2] = {{397}, {396}}; /* derived name */

static ActMail exit_mes[2] = {{397}, {396}}; /* derived name */

static ActMail exit2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

INCLUDE_ASM(actSt47aEnemy1);

INCLUDE_ASM(actSt47aTorch);

INCLUDE_ASM(actSt47aSekizo1);

INCLUDE_ASM(actSt47aSekizo2);

INCLUDE_ASM(actSt47aProc_0023A418);

INCLUDE_ASM(actSt47aProc_0023A478);

INCLUDE_ASM(actSt47aHane1);

INCLUDE_ASM(actSt47aHane2);

INCLUDE_ASM(actSt47aRope);

INCLUDE_ASM(actSt47aBarricade);

INCLUDE_ASM(actSt47aExit);

INCLUDE_ASM(actSt47aExit2);

INCLUDE_ASM(actSt47aEne);

INCLUDE_ASM(actSt47aEnemy2);

INCLUDE_ASM(actSt47aEnemy3);

INCLUDE_ASM(actSt47aEnemy4);

INCLUDE_ASM(actSt47aSekizo1Event);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec girlWayPos = {{2266.0f, -272.0f, 0.0f, 0.0f}}; /* derived name */

static const ConstVec hane1_1GirlPos = {{-1076.0f, -1972.0f, 755.0f, 0.0f}}; /* derived name */

static const ConstVec hane1_2GirlPos = {{1028.0f, -1972.0f, 744.0f, 0.0f}}; /* derived name */

static const ConstVec hane2GirlPos = {{-1031.0f, -1972.0f, -747.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(actSt47aGirlWay);

INCLUDE_ASM(func_0023AA88);

INCLUDE_ASM(func_0023AA98);

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

void actSt47aBarricadeEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt47aExitChk);

INCLUDE_ASM(actSt47aExit2Chk);

INCLUDE_ASM(actSt47aEneChk);

INCLUDE_ASM(actSt47aHint2OnChk);
