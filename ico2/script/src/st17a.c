#include "st17a.h"
#include "layout_texture.h"
#include "pad.h"
#include "debug.h"
#include "obj_manager.h"
#include "lws_kyomi.h"
#include "s_init.h"
#include "act-game.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "act.h"
#include "e3.h"
#include "typedef.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt17aFallChk(GObj *volatile self);

static ActMail linkTest_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorInit_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorUpChk_mes[2] = {{397}, {396}}; /* derived name */

/* actSt17aDoorDownChk's record */
static ActMail door_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hasi_mes[2] = {{397}, {396}}; /* derived name */

static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */

static ActMail hint1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail fall_mes[2] = {{397}, {396}}; /* derived name */

static const ConstVec doorChkSePos = {{6646.0f, -2157.0f, 1102.0f, 0.0f}}; /* derived name */

static const ConstVec doorUpEffectPos = {{6690.0f, -2000.0f, 1100.0f, 1.0f}}; /* derived name */

static const ConstVec doorDownEffectPos = {{6690.0f, -2300.0f, 1100.0f, 1.0f}}; /* derived name */

static const ConstVec doorDownEffect2Pos = {{6600.0f, -2000.0f, 1100.0f, 1.0f}}; /* derived name */

static const ConstVec hasiChkSePos = {{3587.0f, -2072.0f, 1124.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(actSt17aDoor);

INCLUDE_ASM(actSt17aDoorUpChk);

INCLUDE_ASM(actSt17aDoorDownChk);

INCLUDE_ASM(actSt17aHasiChk);

/* The seven spawn positions are initialised block locals, as in e3.c's
 * actE3CageFallEffect. */
void actSt17aHasiEffect(GObj *volatile self)
{
    float t;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 0: {
            EffectArg b1 = {{3645.0f, -1966.0f, 1122.0f, 1.0f}};
            scpEffectStart(&b1, 15);
        } break;
        case 15: {
            EffectArg b2 = {{3753.0f, -1936.0f, 1090.0f, 1.0f}};
            scpEffectStart(&b2, 0);
        }
            {
                EffectArg b3 = {{3605.0f, -1866.0f, 1150.0f, 1.0f}};
                scpEffectStart(&b3, 15);
            }
            break;
        case 60: {
            EffectArg b4 = {{3759.0f, -1666.0f, 1152.0f, 1.0f}};
            scpEffectStart(&b4, 15);
        }
            {
                EffectArg b5 = {{3305.0f, -1566.0f, 1082.0f, 1.0f}};
                scpEffectStart(&b5, 0);
            }
            break;
        case 120: {
            EffectArg b6 = {{3545.0f, -1466.0f, 1120.0f, 1.0f}};
            scpEffectStart(&b6, 0);
        }
            {
                EffectArg b7 = {{3655.0f, -1066.0f, 1477.0f, 1.0f}};
                scpEffectStart(&b7, 0);
            }
            break;
        }
        n = (int)t;
        t += (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)t) {
            _ACTWait(1);
        } else {
            t += 1.0f;
        }
    } while (t < 1000.0f);
}

INCLUDE_ASM(actLinkTest);

INCLUDE_ASM(actSt17aSekizo);

INCLUDE_ASM(actSt17aHasi);

INCLUDE_ASM(actSt17aFall);

void actSt17aSekizoEvent(int x)
{
    volatile int local = x;
}

void actLinkTestChk(GObj *volatile self)
{
    *(int *)(((int *)boyGObj)[87] + 1256) = 1;
    *(int *)(((int *)boyGObj)[87] + 1256) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
}

void actSt17aDoorEvent(int x)
{
    volatile int local = x;
}

void actSt17aDoorUpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorUpEffectPos.d[0];
    long long v0b = doorDownEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorDownEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt17aDoorDownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorDownEffectPos.d[0];
    long long v0b = doorDownEffect2Pos.d[0];
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
            break;
        }
        _ACTWait(1);
    }
}

void actSt17aHasiEvent(int x)
{
    volatile int local = x;
}

/* .sdata: the camera stream handle. */
SqEntry *cam = 0;

INCLUDE_ASM(actSt17aIntroChk);

void actSt17aGirlWay(GObj *volatile self)
{
    EffectArg buf = {{1547.0f, -2070.0f, 1495.0f, 0.0f}};

    _SCPMoveCharactorByWay((void *)girlGObj, 0, buf.f, 100.0f, 2);
}
