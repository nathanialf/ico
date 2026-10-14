#include "st18a.h"
#include "layout_texture.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "st04r.h"
#include "typedef.h"
#include "main.h"
#include "include_asm.h"

static void actSt18aDoorChkSub(GObj *volatile self);

static ActMail intro_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchL_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchR_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail door_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorDownChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene2_mes[2] = {{430}, {429}}; /* derived name */

void actSt18aEnd(void)
{
    if (girlGObj != 0) {
        if (gflagChk(61) == 0) {
            gflagOn(391);
        }
    }
}

void actSt18aIntroChk(GObj *volatile self);

INCLUDE_ASM(actSt18aIntroChk);

INCLUDE_ASM(actSt18aSwitchLChk);

INCLUDE_ASM(actSt18aSwitchLUpChk);

INCLUDE_ASM(actSt18aSwitchRChk);

INCLUDE_ASM(actSt18aSwitchRUpChk);

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for, and the flag actSt18aDoorChkSub raises when the door check is
   done. */
static int demoEnd;

static int doorChkDone; /* derived name */

INCLUDE_ASM(actSt18aDoorChk);

INCLUDE_ASM(actSt18aDoorDownChk);

void actSt18aEnemy1_1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(765));
    Generator_Mask(scpSearchGobj(766));

    while (gflagChk(62) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
    Generator_Call(scpSearchGobj(765));
    Generator_Call(scpSearchGobj(766));
}

void actSt18aEnemy2_1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(766));

    while (gflagChk(64) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_Call(scpSearchGobj(766));
}

void actSt18aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(55) == 0) {
        intro_mes[0].func = actSt18aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt18aDoor);

INCLUDE_ASM(actSt18aSwitchL);

INCLUDE_ASM(actSt18aSwitchR);

void actSt18aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(61) == 0) {
        ene_mes[0].func = actSt18aEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt18aEnemy1_2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(62) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
    _ACTWait(30);
    Generator_Call(self);
}

void actSt18aEne2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(63) == 0) {
        ene2_mes[0].func = actSt18aEne2Chk;
        act->mail = ene2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt18aEnemy2_2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(64) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt18aCamera(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt18aDoorChkSub);

void actSt18aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOff(391);
    gflagOn(61);
    gflagOn(62);
}

void actSt18aEne2Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (girlGObj == 0 || scpTriggerFloorAttr(scpSearchGobj(774), 0x4000000) == 0) {
        _ACTWait(1);
    }
    FinishHint(8);
    _ACTWait(300);
    gflagOn(63);
    gflagOn(64);
}
