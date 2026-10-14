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

static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchL_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchR_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail door_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorDownChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ene2_mes[2] = {{397}, {396}}; /* derived name */

INCLUDE_ASM(actSt18aEnd);

INCLUDE_ASM(actSt18aSwitchLChk);

INCLUDE_ASM(actSt18aSwitchLUpChk);

INCLUDE_ASM(actSt18aSwitchRChk);

INCLUDE_ASM(actSt18aSwitchRUpChk);

INCLUDE_ASM(actSt18aDoorChk);

INCLUDE_ASM(actSt18aDoorDownChk);

INCLUDE_ASM(actSt18aEnemy1_1);

INCLUDE_ASM(actSt18aEnemy2_1);

INCLUDE_ASM(actSt18aIntro);

INCLUDE_ASM(actSt18aDoor);

INCLUDE_ASM(actSt18aSwitchL);

INCLUDE_ASM(actSt18aSwitchR);

INCLUDE_ASM(actSt18aEne);

INCLUDE_ASM(actSt18aEnemy1_2);

INCLUDE_ASM(actSt18aEne2);

INCLUDE_ASM(actSt18aEnemy2_2);

void actSt18aCamera(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(func_00236C70);

INCLUDE_ASM(actSt18aEneChk);

INCLUDE_ASM(actSt18aEne2Chk);
