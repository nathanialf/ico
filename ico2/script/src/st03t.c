#include "st03t.h"
#include "debug.h"
#include "layout_texture.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-ico2.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "box.h"
#include "motionManager2.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static ActMail switchL_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchR_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail girlCam_mes[2] = {{397}, {396}}; /* derived name */

static ActMail girlCamStartChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail girlCamEndChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wayOn_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wayOff_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wayOnChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wayOffChk_mes[2] = {{397}, {396}}; /* derived name */

INCLUDE_ASM(actSt03tSwitchL);

INCLUDE_ASM(actSt03tSwitchLChk);

INCLUDE_ASM(actSt03tSwitchLUpChk);

INCLUDE_ASM(actSt03tSwitchR);

INCLUDE_ASM(actSt03tSwitchRChk);

INCLUDE_ASM(actSt03tSwitchRUpChk);

INCLUDE_ASM(actSt03tBoxA);

INCLUDE_ASM(actSt03tBoxB);

INCLUDE_ASM(actSt03tInit);

INCLUDE_ASM(actSt03tGirlCam);

INCLUDE_ASM(actSt03tSekizo);

INCLUDE_ASM(actSt03tWay);

INCLUDE_ASM(actSt03tEne);

INCLUDE_ASM(actSt03tGirlPos);

void actSt03tGirlCamEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt03tGirlCamStartChk);

INCLUDE_ASM(actSt03tGirlCamEndChk);

void actSt03tSekizoEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt03tEneChk);

void actSt03tWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(17, 1);
    gflagOn(91);

    wayOnChk_mes[0].func = actSt03tWayOffChk;
    sub->mail = wayOnChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt03tWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(17, 0);
    gflagOff(91);

    wayOffChk_mes[0].func = actSt03tWayOnChk;
    sub->mail = wayOffChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
