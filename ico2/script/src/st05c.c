#include "st05c.h"
#include "layout_texture.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "st04c.h"
#include "typedef.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt04rDoor2Sub(GObj *volatile self);
static void actSt04rDoorSub(GObj *volatile self);

static const StVec doorDownChkPos = {{0.0f, 84.0f, -1359.0f, 0.0f}}; /* derived name */

static const StVec doorDownEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}}; /* derived name */

static const StVec doorDownEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}}; /* derived name */

static const StVec doorDownEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}}; /* derived name */

static ActMail doorDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st04rDoor_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st04rDoor2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crestHint_mes[2] = {{430}, {429}}; /* derived name */

INCLUDE_ASM(actSt05cDoorDownChk);

INCLUDE_ASM(actSt04rDoorChk);

INCLUDE_ASM(actSt04rDoor2Chk);

INCLUDE_ASM(actSt05cSolarXL);

INCLUDE_ASM(actSt05cWaterXL);

INCLUDE_ASM(actSt04rDoor);

INCLUDE_ASM(actSt04rDoor2);

INCLUDE_ASM(actSt05cDoorDown);

INCLUDE_ASM(actSt05cEne);

INCLUDE_ASM(actSt05cEnemy1);

INCLUDE_ASM(actSt05cEnemy2);

void actSt05cDoorDownEvent(int x)
{
    volatile int local = x;
}

void actSt05cDoorDownEffect(GObj *volatile self)
{
    StVec a;
    StVec b;
    StVec c;
    int i;

    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            a = doorDownEffectPos;
            scpEffectStart(&a, 0);
            break;
        case 30:
            b = doorDownEffect2Pos;
            scpEffectStart(&b, 0);
            c = doorDownEffect3Pos;
            scpEffectStart(&c, 0);
            break;
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt05cEneChk);
