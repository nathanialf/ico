#include "common.h"
#include "st05c.h"
#include "layout_texture.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "st04c.h"
#include "typedef.h"

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
/* kept local: this TU's uses of scpWakeupEnemyAll do not fit the prototype in script.h */
extern void scpWakeupEnemyAll(void);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float f, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
extern Pad D_0028F8F0[];
/* kept local: this TU's uses of scpEffectStart do not fit the prototype in script.h */
extern int scpEffectStart(StVec *a0, int a1);
extern int D_00639EA4;
extern int D_00639EA8;
extern int D_0063AA08;

/* .sbss, owned by st05c.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthreads the wait loops below spin for. */
static int demoEnd;

static const StVec doorDownChkPos = {{0.0f, 84.0f, -1359.0f, 0.0f}};

static const StVec doorDownEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}};

static const StVec doorDownEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}};

static const StVec doorDownEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}};

static ActMail doorDown_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail st04rDoor_mes[2] = {{430}, {429}};

static ActMail st04rDoor2_mes[2] = {{430}, {429}};

static ActMail crestHint_mes[2] = {{430}, {429}};

void actSt05cDoorDownChk(volatile int a0)
{
    StVec pos;

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    _ACTWait(30);
    gflagOff(390);
    actCreateSubThread(actSt05cDoorDownEffect, 21);
    stage_SetAnimation(347, 1, 0);

    pos = doorDownChkPos;
    _ACTWait(30);
    soundSeDefPlay(1221, 0, &pos, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, &pos, 1);

    while (stage_CheckAnimationFinish(347) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    gflagOn(165);
    D_0063AA08 = 0;
}

void actSt04rDoorChk(volatile int a0)
{
    int x = a0;
    int th;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(255) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1380))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(334, 1, 0);
            while (stage_CheckAnimationFinish(334) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1380)->f16C = 0;
            lt_switch_layout(55);
            D_0063AA08 = 1;
            scpSleepEnemyAll();
            gflagOn(255);
            demoEnd = 0;
            th = actCreateSubThread(actSt04rDoorSub, 21);

            while (demoEnd == 0 &&
                   ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
                _ACTWait(1);
            }

            iosThreadSetPri(th + 0x24, 34);

            if (demoEnd == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
                stage_SetAnimation(332, 0, -1);
                scpFadeIn(3.0f);
            }

            soundSeDefPlay(1331, 0, 0, 1);
            scpWakeupEnemyAll();
            D_0063AA08 = 0;
            lt_switch_layout(54);
            break;
        }
    }
}

void actSt04rDoor2Chk(volatile int a0)
{
    int x = a0;
    int th;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(256) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1381))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(335, 1, 0);
            while (stage_CheckAnimationFinish(335) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1381)->f16C = 0;
            lt_switch_layout(55);
            D_0063AA08 = 1;
            scpSleepEnemyAll();
            gflagOn(256);
            demoEnd = 0;
            th = actCreateSubThread(actSt04rDoor2Sub, 21);

            while (demoEnd == 0 &&
                   ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
                _ACTWait(1);
            }

            iosThreadSetPri(th + 0x24, 34);

            if (demoEnd == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
                stage_SetAnimation(333, 0, -1);
                scpFadeIn(3.0f);
            }

            soundSeDefPlay(1331, 0, 0, 1);
            scpWakeupEnemyAll();
            D_0063AA08 = 0;
            lt_switch_layout(54);
            break;
        }
    }
}

void actSt05cSolarXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(139) == 0) {
        stage_SetAnimation(304, -1, -2);
    }
}

void actSt05cWaterXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(231) != 0) {
        scpSearchGobj(1376)->f16C = 0;
    }
}

void actSt04rDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(255) == 0) {
        stage_SetAnimation(332, 0, 0);
        st04rDoor_mes[0].func = actSt04rDoorChk;
        self->mail = st04rDoor_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(332, 0, -1);
        scpSearchGobj(1380)->f16C = 0;
    }
}

void actSt04rDoor2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(256) == 0) {
        stage_SetAnimation(333, 0, 0);
        st04rDoor2_mes[0].func = actSt04rDoor2Chk;
        self->mail = st04rDoor2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(333, 0, -1);
        scpSearchGobj(1381)->f16C = 0;
    }
}

void actSt05cDoorDown(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    if (gflagChk(165) == 0) {
        doorDown_mes[0].func = actSt05cDoorDownChk;
        self->mail = doorDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt05cEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(167) == 0) {
        ene_mes[0].func = actSt05cEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt05cEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(168) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_MaskOff(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt05cEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(168) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt05cCrestHint(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(169) == 0) {
        SleepHint(23);
        crestHint_mes[0].func = actSt05cCrestHintChk;
        self->mail = crestHint_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt05cDoorDownEvent(int x)
{
    volatile int local = x;
}

void actSt05cDoorDownEffect(volatile int a0)
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
        case 0x1E:
            b = doorDownEffect2Pos;
            scpEffectStart(&b, 0);
            c = doorDownEffect3Pos;
            scpEffectStart(&c, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt05cEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (D_00639EA8 == 0 || gflagChk(255) == 0) {
        _ACTWait(1);
    }

    _ACTWait(600);
    gflagOn(167);
    gflagOn(168);
}

void actSt04rDoorSub(volatile int a0)
{
    int h;

    stage_SetAnimation(332, 1, 0);
    h = soundSeDefPlay(1330, 0, 0, 1);
    _ACTWait(90);
    soundSeDefStop(h);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt04rDoor2Sub(volatile int a0)
{
    int h;

    stage_SetAnimation(333, 1, 0);
    h = soundSeDefPlay(1330, 0, 0, 1);
    _ACTWait(90);
    soundSeDefStop(h);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt05cCrestHintChk(volatile int a0)
{
    while (gflagChk(243) == 0 || gflagChk(244) == 0 || gflagChk(245) == 0 || gflagChk(232) != 0) {
        _ACTWait(1);
    }

    gflagOn(169);
    WakeupHint(23);
}
