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

static ActMail intro_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchL_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchLUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchLChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchR_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchRUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchRChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorDownChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ene2_mes[2] = {{377}, {376}}; /* derived name */

void actSt18aSwitchLChk(GObj *volatile self);

INCLUDE_ASM(actSt18aSwitchLUpChk);

void actSt18aSwitchRChk(GObj *volatile self);

INCLUDE_ASM(actSt18aSwitchRUpChk);

/* No .sbss here in this build: no function of the demo addresses these flags. */

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

INCLUDE_ASM(actSt18aCamera);

INCLUDE_ASM(actSt18aIntroChk);

INCLUDE_ASM(func_0021E040);

INCLUDE_ASM(func_0021E130);

INCLUDE_ASM(actSt18aEneChk);

INCLUDE_ASM(actSt18aEne2Chk);
