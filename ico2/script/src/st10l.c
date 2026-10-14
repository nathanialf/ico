#include "st10l.h"
#include "layout_texture.h"
#include "pad.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "girl_act.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "layout_action.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt10lEneKillChk(GObj *volatile self);

/* .rodata: the girl's way-point packet for actSt10lEneCam3Chk, a 16-byte
   constant vector template whose long long view the copy reads */

static const ConstVec eneCam3ChkPos = {{-33.0f, -72.0f, 470.0f, 0.0f}}; /* derived name */

/* .data: actor mail packets. */

static ActMail floorMain_mes[2] = {{376, actSt10lFloorSwitch}, {396}}; /* derived name */

static ActMail floor_mes[2] = {{397}, {396}}; /* derived name */

static ActMail floorSwitchRight_mes[2] = {{397}, {396}}; /* derived name */

static ActMail floorSwitchLeft_mes[2] = {{397}, {396}}; /* derived name */

static ActMail floorLeft_mes[2] = {{397}, {396}}; /* derived name */

static ActMail floorRight_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaMain_mes[2] = {{377, actSt10lGondolaSwitch}, {396}}; /* derived name */

static ActMail gondola_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaSwitchDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaSwitchUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail eneCam1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail box_mes[2] = {{397}, {396}}; /* derived name */

static ActMail eneCam2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail eneCam3_mes[2] = {{397}, {396}}; /* derived name */

static ActMail boxA_mes[2] = {{397}, {396}}; /* derived name */

static ActMail boxB_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainMain_mes[2] = {{378, actSt10lChainSwitch}, {396}}; /* derived name */

static ActMail chain_mes[2] = {{397}, {396}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail eneKill_mes[2] = {{397}, {396}}; /* derived name */

/* .sdata: the floor, gondola and chain stream handles. */
SqEntry *floor10l = 0;

SqEntry *st10l_gondola_up = 0;

SqEntry *st10l_gondola_down = 0;

SqEntry *chain10l = 0;

INCLUDE_ASM(actSt10lInit);

INCLUDE_ASM(actSt10lFloorLeft);

INCLUDE_ASM(actSt10lFloorRight);

INCLUDE_ASM(actSt10lGondolaUp);

INCLUDE_ASM(actSt10lGondolaDown);

INCLUDE_ASM(actSt10lEneCam2Chk);

INCLUDE_ASM(actSt10lEneCam3Chk);

INCLUDE_ASM(func_0022C9F0);

INCLUDE_ASM(actSt10lChain);

INCLUDE_ASM(actSt10lFloor);

INCLUDE_ASM(actSt10lGondola);

INCLUDE_ASM(actSt10lSekizo);

INCLUDE_ASM(actSt10lBox);

INCLUDE_ASM(actSt10lEnemy1_1);

INCLUDE_ASM(actSt10lEnemy1_2);

INCLUDE_ASM(actSt10lEnemy2_1);

INCLUDE_ASM(actSt10lEnemy2_2);

INCLUDE_ASM(actSt10lEnemy2_3);

INCLUDE_ASM(actSt10lEnemy3_1);

INCLUDE_ASM(actSt10lEnemy3_2);

INCLUDE_ASM(actSt10lEneCam1);

INCLUDE_ASM(actSt10lEneCam2);

INCLUDE_ASM(actSt10lEneCam3);

INCLUDE_ASM(actSt10lEneKill);

INCLUDE_ASM(actSt10lBoxA);

INCLUDE_ASM(actSt10lBoxB);

INCLUDE_ASM(actSt10lGateXL);

INCLUDE_ASM(actSt10lFloorMain);

INCLUDE_ASM(actSt10lFloorSwitch);

INCLUDE_ASM(actSt10lGondolaMain);

INCLUDE_ASM(actSt10lGondolaSwitch);

INCLUDE_ASM(actSt10lEneCam1Chk);

INCLUDE_ASM(actSt10lBoxChk);

void actSt10lSekizoEvent(int x)
{
    volatile int local = x;
}

INCLUDE_ASM(actSt10lBoxAChk);

INCLUDE_ASM(actSt10lBoxBChk);

INCLUDE_ASM(actSt10lChainMain);

INCLUDE_ASM(actSt10lChainSwitch);

INCLUDE_ASM(actSt10lEneKillChk);
