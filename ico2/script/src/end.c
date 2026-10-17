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

/* .sdata: two stream handles in this build, the ending demo's and the staff
   roll's (PAL has eleven words here: ed2..ed6, sea, happy_end, the fourteenth
   demo's and the st27a ending's are not in the demo's .sdata). */
SqEntry *ed1 = 0;

static SqEntry *staff3 = 0; /* derived name */

static ActMail demo01_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo02_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo03_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo04_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo05_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo06_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo07_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo10_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo11_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo12_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo13_mes[2] = {{377}, {376}}; /* derived name */

static ActMail staff1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail staff2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail staff3_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ed_demo14_mes[2] = {{377}, {376}}; /* derived name */

static ActMail st27aEnd_mes[2] = {{377}, {376}}; /* derived name */

static ActMail logo_mes[2] = {{377}, {376}}; /* derived name */

INCLUDE_ASM(actConte14_1);

INCLUDE_ASM(actConte14_2);

void actConte14_6(GObj *volatile self);

INCLUDE_ASM(actEndDemo07);

/* 16-byte constant vector templates: the float view carries the values, the
   long long view is the one the copy reads. */

static const ConstVec conte14_7Pos = {{-4743.0f, -661.0f, 2503.0f, 1.0f}}; /* derived name */

static const ConstVec staff3DemoPos = {{-800.0f, 0.0f, -1000.0f, 1.0f}}; /* derived name */

/* this build's position (actStaff2Demo reads it) */
static const ConstVec conte14_14Pos = {{17430.0f, 3.0f, -4384.0f, 1.0f}}; /* derived name */

INCLUDE_ASM(actConte14_7);

INCLUDE_ASM(actConte14_10);

INCLUDE_ASM(func_001F9200);

void actConte14_13(GObj *volatile self);

INCLUDE_ASM(actStaff1Demo);

INCLUDE_ASM(actStaff2Demo);

INCLUDE_ASM(func_001F9950);

void actStaff3Demo(GObj *volatile self);

INCLUDE_ASM(actEndDemo14);

INCLUDE_ASM(actEndObj2368);

INCLUDE_ASM(actEndObj2242);

INCLUDE_ASM(actEndObj2361);

INCLUDE_ASM(actEndObj2354);

void actConte14_14(GObj *volatile self);

INCLUDE_ASM(actEndDemo03);

INCLUDE_ASM(actEndDemo04);

INCLUDE_ASM(actEndDemo05);

INCLUDE_ASM(actEndDemo11);

INCLUDE_ASM(actEndObj2383);

INCLUDE_ASM(actEndDemo12);

INCLUDE_ASM(actEndDemo13);

INCLUDE_ASM(actStaff1);

INCLUDE_ASM(actStaff2);

INCLUDE_ASM(actStaff3);

INCLUDE_ASM(actSt27aEnd);

INCLUDE_ASM(actEndLogo);

INCLUDE_ASM(actEndDemo01Chk);

INCLUDE_ASM(func_001FA3C0);

INCLUDE_ASM(func_001FA3F0);

INCLUDE_ASM(actConte14_3);

INCLUDE_ASM(func_001FA498);

INCLUDE_ASM(actConte14_4);

INCLUDE_ASM(actEndDemo05Chk);

INCLUDE_ASM(actConte14_5);

INCLUDE_ASM(func_001FA5E8);

INCLUDE_ASM(actEndDemo06Chk);

INCLUDE_ASM(func_001FA640);

INCLUDE_ASM(actEndDemo10Chk);

INCLUDE_ASM(func_001FA720);

INCLUDE_ASM(actConte14_10_Jimaku);

INCLUDE_ASM(actEndDemo11Chk);

INCLUDE_ASM(actConte14_11);

INCLUDE_ASM(actEndDemo12Chk);

INCLUDE_ASM(actConte14_12);

INCLUDE_ASM(actEndDemo13Chk);

INCLUDE_ASM(func_001FAAA8);

INCLUDE_ASM(actStaff1Chk);

INCLUDE_ASM(actStaff3Chk);

INCLUDE_ASM(actStaff3RollChk);

INCLUDE_ASM(actEndDemo14Chk);

INCLUDE_ASM(actEndLogoChk);
