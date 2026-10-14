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

static ActMail demo04_mes[2] = {{397}, {396}}; /* derived name */

static ActMail D_004D0BF0[2] = {{397}, {396}}; /* derived name */

static ActMail demo05_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo06_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo07_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo10_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo11_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo12_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo13_mes[2] = {{397}, {396}}; /* derived name */

static ActMail staff2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail staff3_mes[2] = {{397}, {396}}; /* derived name */

static ActMail D_004D0D30[2] = {{397}, {396}}; /* derived name */

static ActMail ed_demo14_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st27aEnd_mes[2] = {{397}, {396}}; /* derived name */

static ActMail logo_mes[2] = {{397}, {396}}; /* derived name */

INCLUDE_ASM(actEndDemo01);

INCLUDE_ASM(actConte14_1);

INCLUDE_ASM(actEndDemo02);

INCLUDE_ASM(actConte14_2);

INCLUDE_ASM(actEndDemo06);

INCLUDE_ASM(actConte14_6);

INCLUDE_ASM(actEndDemo07);

/* 16-byte constant vector templates: the float view carries the values, the
   long long view is the one the copy reads. */

static const ConstVec conte14_7Pos = {{-4743.0f, -661.0f, 2503.0f, 1.0f}}; /* derived name */

static const ConstVec staff3DemoPos = {{-800.0f, 0.0f, -1000.0f, 1.0f}}; /* derived name */

static const ConstVec conte14_14Pos = {{16975.0f, 71.0f, -4332.0f, 1.0f}}; /* derived name */

INCLUDE_ASM(actConte14_7);

INCLUDE_ASM(actEndDemo10);

INCLUDE_ASM(actConte14_10);

INCLUDE_ASM(actConte14_13);

void actStaff1Demo(GObj *volatile self);

INCLUDE_ASM(actStaff1Demo);

void actStaff2Demo(GObj *volatile self);

INCLUDE_ASM(actStaff2Demo);

INCLUDE_ASM(actStaff3Demo);

INCLUDE_ASM(actEndDemo14);

INCLUDE_ASM(actConte14_14);

INCLUDE_ASM(actSt27aEndChk);

INCLUDE_ASM(func_0020C748);

INCLUDE_ASM(actEndDemo04);

INCLUDE_ASM(func_0020C910);

INCLUDE_ASM(actEndDemo05);

INCLUDE_ASM(actEndDemo11);

INCLUDE_ASM(actEndDemo12);

INCLUDE_ASM(actEndDemo13);

INCLUDE_ASM(actStaff2);

INCLUDE_ASM(actStaff3);

INCLUDE_ASM(func_0020CD60);

INCLUDE_ASM(func_0020CE00);

INCLUDE_ASM(actEndLogo);

INCLUDE_ASM(actEndDemo01Chk);

INCLUDE_ASM(actEndDemo02Chk);

INCLUDE_ASM(actEndDemo03Chk);

INCLUDE_ASM(actConte14_3);

INCLUDE_ASM(actEndDemo04Chk);

INCLUDE_ASM(actConte14_4);

INCLUDE_ASM(actEndDemo05Chk);

INCLUDE_ASM(actConte14_5);

INCLUDE_ASM(func_0020D2B8);

INCLUDE_ASM(actEndDemo07Chk);

INCLUDE_ASM(actEndDemo10Chk);

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

INCLUDE_ASM(actEndDemo11Chk);

INCLUDE_ASM(actConte14_11);

INCLUDE_ASM(actEndDemo12Chk);

INCLUDE_ASM(actConte14_12);

INCLUDE_ASM(actEndDemo13Chk);

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

INCLUDE_ASM(actStaff3Chk);

INCLUDE_ASM(actStaff3RollChk);

INCLUDE_ASM(actEndDemo14Chk);

INCLUDE_ASM(actEndingSave);
