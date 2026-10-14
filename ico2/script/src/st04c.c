#include "st04c.h"
#include "layout_texture.h"
#include "thread.h"
#include "s_init.h"
#include "commonact.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "act.h"
#include "gobj_process.h"
#include "typedef.h"
#include "generator.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt04cIntroChkSub(GObj *volatile self);

INCLUDE_ASM(actSt04cEnd);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const StVec doorDownChkPos = {{0.0f, 84.0f, -1359.0f, 0.0f}}; /* derived name */

static const ConstVec doorDownEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorDownEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}}; /* derived name */

static const ConstVec doorDownEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}}; /* derived name */

INCLUDE_ASM(actSt04cDoorDownChk);

INCLUDE_ASM(func_00218F98);

INCLUDE_ASM(actSt04cSolarXL);

static ActMail doorDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail intro_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st04lDoor_mes[2] = {{430}, {429}}; /* derived name */

INCLUDE_ASM(actSt04lDoor);

INCLUDE_ASM(actSt04cIntro);

INCLUDE_ASM(actSt04cDoorDown);

INCLUDE_ASM(actSt04cEne);

INCLUDE_ASM(actSt04cEnemy1);

INCLUDE_ASM(actSt04cEnemy2);

INCLUDE_ASM(actSt04cWaterXL);

void actSt04cDoorDownEvent(int x)
{
    volatile int local = x;
}

void actSt04cDoorDownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long b3[2];
    long long v0a = doorDownEffectPos.d[0];
    long long v0b = doorDownEffect2Pos.d[0];
    long long v0c = doorDownEffect3Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorDownEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorDownEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            b3[0] = v0c;
            b3[1] = doorDownEffect3Pos.d[1];
            scpEffectStart((int *)b3, 0);
            break;
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt04cEneChk);

INCLUDE_ASM(actSt04cIntroChkSub);

void actSt04lDoorEvent(int x)
{
    volatile int local = x;
}
