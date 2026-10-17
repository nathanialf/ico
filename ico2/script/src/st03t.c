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

static void actSt03tGirlPosChk(GObj *volatile self);
static void actSt03tGirlUpChk(GObj *volatile self);
static void actSt03tHint1OffChk(GObj *volatile self);

static ActMail switchL_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchLUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchLChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchR_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchRUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchRChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail girlCam_mes[2] = {{377}, {376}}; /* derived name */

static ActMail girlCamStartChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail girlCamEndChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wayOn_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wayOff_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wayOnChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wayOffChk_mes[2] = {{377}, {376}}; /* derived name */

INCLUDE_ASM(actSt03tSwitchL);

INCLUDE_ASM(actSt03tSwitchLChk);

INCLUDE_ASM(actSt03tSwitchLUpChk);

INCLUDE_ASM(actSt03tSwitchR);

INCLUDE_ASM(actSt03tSwitchRChk);

INCLUDE_ASM(actSt03tSwitchRUpChk);

INCLUDE_ASM(actSt03tBoxB);

INCLUDE_ASM(actSt03tInit);

INCLUDE_ASM(actSt03tGirlCam);

INCLUDE_ASM(actSt03tSekizo);

INCLUDE_ASM(actSt03tObj776);

INCLUDE_ASM(actSt03tWay);

INCLUDE_ASM(actSt03tEne);

INCLUDE_ASM(actSt03tGene);

INCLUDE_ASM(actSt03tGirlCamEvent);

INCLUDE_ASM(actSt03tGirlCamStartChk);

INCLUDE_ASM(actSt03tGirlCamEndChk);

INCLUDE_ASM(actSt03tSekizoEvent);

INCLUDE_ASM(actSt03tEneChk);

INCLUDE_ASM(actSt03tWayOnChk);

INCLUDE_ASM(actSt03tWayOffChk);
