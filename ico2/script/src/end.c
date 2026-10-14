#include "end.h"
#include "mcard.h"
#include "layout_texture.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "boyact.h"
#include "commonact.h"
#include "jimaku.h"
#include "camera-root.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "boy.h"
#include "girl.h"
#include "item.h"
#include "staticBlur.h"
#include <libvu0.h>
#include "e3.h"
#include "typedef.h"
#include "layout_action.h"
#include "GsBase.h"
#include "main.h"
#include "script.h"
#include "staffroll.h"
#include "include_asm.h"

static void actEndingSave(GObj *volatile self);

/* .sdata: the ending scenes' stream handles (ed5 and happy_end unused), then
   the staff roll's, the fourteenth demo's and the st27a ending's. */
SqEntry *ed1 = 0;

SqEntry *ed2 = 0;

SqEntry *ed3 = 0;

SqEntry *ed4 = 0;

int ed5 = 0;

SqEntry *ed6 = 0;

SqEntry *sea = 0;

int happy_end = 0;

static SqEntry *staff3 = 0; /* derived name */

static SqEntry *endDemo14 = 0; /* derived name */

static SqEntry *st27aEnd = 0; /* derived name */

static ActMail demo01_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo03_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo04_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo05_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo06_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo07_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo10_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo11_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo12_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo13_mes[2] = {{430}, {429}}; /* derived name */

static ActMail staff1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail staff2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail staff3_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ed_demo14_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st27aEnd_mes[2] = {{430}, {429}}; /* derived name */

static ActMail logo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail end_mes[2] = {{430}, {429}}; /* derived name */

INCLUDE_ASM(actEndDemo01);

void actConte14_1(GObj *volatile self);

INCLUDE_ASM(actConte14_1);

INCLUDE_ASM(actEndDemo02);

void actConte14_2(GObj *volatile self);

INCLUDE_ASM(actConte14_2);

INCLUDE_ASM(actEndDemo06);

void actConte14_6(GObj *volatile self);

INCLUDE_ASM(actConte14_6);

INCLUDE_ASM(actEndDemo07);

/* 16-byte constant vector templates: the float view carries the values, the
   long long view is the one the copy reads. */

static const ConstVec conte14_7Pos = {{-4743.0f, -661.0f, 2503.0f, 1.0f}}; /* derived name */

static const ConstVec staff3DemoPos = {{-800.0f, 0.0f, -1000.0f, 1.0f}}; /* derived name */

static const ConstVec conte14_14Pos = {{16975.0f, 71.0f, -4332.0f, 1.0f}}; /* derived name */

void actConte14_7(GObj *volatile self);

INCLUDE_ASM(actConte14_7);

INCLUDE_ASM(actEndDemo10);

void actConte14_10(GObj *volatile self);

INCLUDE_ASM(actConte14_10);

void actConte14_13(GObj *volatile self);

INCLUDE_ASM(actConte14_13);

INCLUDE_ASM(actStaff1);

void actStaff1Demo(GObj *volatile self);

INCLUDE_ASM(actStaff1Demo);

void actStaff2Demo(GObj *volatile self);

INCLUDE_ASM(actStaff2Demo);

void actStaff3Demo(GObj *volatile self);

INCLUDE_ASM(actStaff3Demo);

INCLUDE_ASM(actEndDemo14);

void actConte14_14(GObj *volatile self);

INCLUDE_ASM(actConte14_14);

void actSt27aEnd(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gFlagGameClear == 0) {
        scpSearchGobj(2256)->active = 0;
        scpSearchGobj(2257)->active = 0;
        scpSearchGobj(2258)->active = 0;
        scpSearchGobj(2259)->active = 0;
        scpSearchGobj(2260)->active = 0;
        scpSearchGobj(2261)->active = 0;
        scpSearchGobj(2262)->active = 0;
        scpSearchGobj(2263)->active = 0;
    }

    if (gflagChk(355) == 0) {
        st27aEnd_mes[0].func = actSt27aEndChk;
        act->mail = st27aEnd_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt27aEndChk);

INCLUDE_ASM(actSt27aEndDemo);

void actEndLogoChk(GObj *volatile self);

INCLUDE_ASM(actEndLogoChk);

INCLUDE_ASM(actEndDemo03);

INCLUDE_ASM(actEndDemo04);

INCLUDE_ASM(actEndDemo05);

INCLUDE_ASM(actEndDemo11);

INCLUDE_ASM(actEndDemo12);

INCLUDE_ASM(actEndDemo13);

INCLUDE_ASM(actStaff2);

INCLUDE_ASM(actStaff3);

void actEndLogo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    logo_mes[0].func = actEndLogoChk;
    act->mail = logo_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actEndDemo01Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(43, &ed1, 0, 1, 1);

    while (ed1 == 0) {
        _ACTWait(1);
    }

    preload(2);

    scpFadeIn(6.0f);

    gflagOn(2);

    gflagOn(3);

    gflagOn(4);

    gflagOn(339);

    actCreateSubThread(actConte14_1, 21);
}

void actEndDemo02Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(44, &ed2, 0, 1, 1);

    while (ed2 == 0) {
        _ACTWait(1);
    }

    preload(3);

    scpFadeIn(6.0f);

    gflagOn(340);

    actCreateSubThread(actConte14_2, 21);
}

void actEndDemo03Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(45, &ed3, 0, 1, 1);

    while (ed3 == 0) {
        _ACTWait(1);
    }

    preload(2);

    scpFadeIn(6.0f);

    gflagOn(341);

    actCreateSubThread(actConte14_3, 21);
}

INCLUDE_ASM(actConte14_3);

void actEndDemo04Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(46, &ed4, 0, 1, 1);

    while (ed4 == 0) {
        _ACTWait(1);
    }

    preload(5);

    scpFadeIn(6.0f);

    gflagOn(342);

    actCreateSubThread(actConte14_4, 21);
}

INCLUDE_ASM(actConte14_4);

void actEndDemo05Chk(GObj *volatile self)
{
    gflagOn(343);

    actCreateSubThread(actConte14_5, 21);
}

INCLUDE_ASM(actConte14_5);

void actEndDemo06Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(47, &sea, 0, 1, 1);

    while (sea == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    gflagOff(339);

    gflagOff(343);

    actCreateSubThread(actConte14_6, 21);
}

void actEndDemo07Chk(GObj *volatile self)
{
    _ACTWait(30);

    scpFadeIn(6.0f);

    gflagOn(345);

    actCreateSubThread(actConte14_7, 21);
}

void actEndDemo10Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(48, &ed6, 0, 1, 0);

    while (ed6 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    gflagOn(348);

    actCreateSubThread(actConte14_10, 21);

    actCreateSubThread(actConte14_10_Jimaku, 21);
}

void actConte14_10_Jimaku(GObj *volatile self)
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
        case 1500:
            jimaku_msg.sub.block = 112;
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
    } while (t < 1800.0f);
}

void actEndDemo11Chk(GObj *volatile self)
{
    gflagOn(349);

    actCreateSubThread(actConte14_11, 21);
}

INCLUDE_ASM(actConte14_11);

void actEndDemo12Chk(GObj *volatile self)
{
    gflagOn(350);

    actCreateSubThread(actConte14_12, 21);
}

INCLUDE_ASM(actConte14_12);

void actEndDemo13Chk(GObj *volatile self)
{
    gflagOn(351);

    actCreateSubThread(actConte14_13, 21);
}

void actStaff1Chk(GObj *volatile self)
{
    actCreateSubThread(actStaff1Demo, 21);
}

void actStaff2Chk(GObj *volatile self)
{
    reg_SetScissorSw(1);

    SetStaticBlur(0);

    actCreateSubThread(actStaff2Demo, 21);
}

void actStaff3Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(49, &staff3, 0, 1, 1);

    while (staff3 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    actCreateSubThread(actStaff3Demo, 21);

    actCreateSubThread(actStaff3RollChk, 21);
}

void actStaff3RollChk(GObj *volatile self)
{
    preload(1);

    while (staffRollStartFlag != 0) {
        _ACTWait(1);
    }

    if (ed6 != 0) {
        scpAdpcmFadeCloseFunc(&ed6, 80);
    }

    RequestStageChange(1, boyGObj, 0, 16.0f, 0.001f);
}

void actEndDemo14Chk(GObj *volatile self)
{
    gflagOn(352);

    actCreateSubThread(actConte14_14, 21);
}

INCLUDE_ASM(actEndingSave);
