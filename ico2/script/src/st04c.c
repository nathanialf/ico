#include "common.h"
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
#include "typedef.h"
#include "generator.h"

extern char *D_00639EA8;

void actSt04cEnd(void)
{
    if (D_00639EA8 != 0) {
        if (gflagChk(163) == 0) {
            gflagOn(391);
        }
    }
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const StVec doorDownChkPos = {{0.0f, 84.0f, -1359.0f, 0.0f}};

static const ConstVec doorDownEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}};

static const ConstVec doorDownEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}};

static const ConstVec doorDownEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}};

extern int D_00639EA4;
/* kept local: the declaration in script.h changes this TU codegen */
extern int scpTriggerBall(int a0, int gobj, float r);

/* listing lines 326-357 */
void actSt04cDoorDownChk(volatile int a0)
{
    StVec pos;

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0) {
        _ACTWait(1);
    }

    _ACTWait(30);

    actCreateSubThread(actSt04cDoorDownEffect, 21);

    stage_SetAnimation(253, 1, 0);

    pos = doorDownChkPos;

    _ACTWait(30);
    soundSeDefPlay(1221, 0, &pos, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, &pos, 1);

    while (stage_CheckAnimationFinish(253) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(162);
}

extern int D_0063AA08;

/* .sbss, owned by st04c.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for. */
static int demoEnd;

extern int D_0028F8F4[];
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float f, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);

/* listing lines 592-637 */
void actSt04cIntroChk(volatile int a0)
{
    int th;

    while (scpTriggerBall(a0, D_00639EA4, 1000.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    gflagOff(390);

    gflagOn(161);
    D_0063AA08 = 1;

    stage_SetAnimation(352, 1, 0);

    th = actCreateSubThread(actSt04cIntroChkSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && (!(D_0028F8F4[0] & 0x800) || scpAdpcmPlayRequestNum() != 0)) {
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
        stage_SetAnimation(352, 0, -1);
        scpFadeIn(3.0f);
    }

    lt_switch_layout(54);
    D_0063AA08 = 0;
}

extern int D_0028F8F0[];
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern int scpSearchGobj(int a0);
/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
/* kept local: this TU's uses of scpWakeupEnemyAll do not fit the prototype in script.h */
extern void scpWakeupEnemyAll(void);

/* listing lines 705-753 */
void actSt04lDoorChk(volatile int a0)
{
    int x = a0;
    int h;
    int i;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(199) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1098))) {
        case 0:
            _ACTWait(1);
            break;

        case 1:
            stage_SetAnimation(232, 1, 0);
            while (stage_CheckAnimationFinish(232) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;

        case 2:
            *(int *)(scpSearchGobj(1098) + 0x16C) = 0;
            FinishHint(15);

            lt_switch_layout(55);

            D_0063AA08 = 1;
            scpSleepEnemyAll();

            gflagOn(199);

            stage_SetAnimation(231, 1, 0);

            h = soundSeDefPlay(1330, 0, 0, 1);

            for (i = 90; i-- > 0;) {
                if ((D_0028F8F0[1] & 0x800) && scpAdpcmPlayRequestNum() == 0) {
                    scpFadeOut(16.0f, 0, 0, 0);
                    while (scpFadeChk() != 0) {
                        _ACTWait(1);
                    }
                    while (lt_fade_status() != 2) {
                        _ACTWait(1);
                    }
                    stage_SetAnimation(231, 0, -1);
                    scpFadeIn(3.0f);
                    break;
                }
                _ACTWait(1);
            }

            soundSeDefStop(h);

            soundSeDefPlay(1331, 0, 0, 1);

            scpWakeupEnemyAll();
            D_0063AA08 = 0;

            lt_switch_layout(54);
            break;
        }
    }
}

void actSt04cSolarXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(138) == 0) {
        stage_SetAnimation(302, -1, -2);
    }
}

static ActMail doorDown_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail intro_mes[2] = {{430}, {429}};

static ActMail st04lDoor_mes[2] = {{430}, {429}};

void actSt04lDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(199) == 0) {
        stage_SetAnimation(231, 0, 0);
        st04lDoor_mes[0].func = actSt04lDoorChk;
        self->mail = st04lDoor_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(231, 0, -1);
        *(int *)(scpSearchGobj(1098) + 0x16C) = 0;
        FinishHint(15);
    }
}

void actSt04cIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(161) == 0) {
        intro_mes[0].func = actSt04cIntroChk;
        self->mail = intro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04cDoorDown(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    if (gflagChk(162) == 0) {
        doorDown_mes[0].func = actSt04cDoorDownChk;
        self->mail = doorDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04cEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(163) == 0) {
        ene_mes[0].func = actSt04cEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04cEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);
    while (gflagChk(164) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt04cEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);
    while (gflagChk(164) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt04cWaterXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(230) != 0) {
        *(int *)(scpSearchGobj(1094) + 0x16C) = 0;
    }
}

void actSt04cDoorDownEvent(int x)
{
    volatile int local = x;
}

/* Effect-parameter triples in .rodata; the `const` is the data model and is
   load-bearing: RTX_UNCHANGING_P is what keeps sched2 from ordering each
   b[0] store behind the b[1] load in the two remat'd-address switch arms. */

void actSt04cDoorDownEffect(volatile int a0)
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
        case 0x1E:
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

void actSt04cEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0xB000000) == 0) {
        _ACTWait(1);
    }
    gflagOff(391);
    _ACTWait(1);
    gflagOn(163);
    gflagOn(164);
}

void actSt04cIntroChkSub(volatile int a0)
{
    while (stage_CheckAnimationFinish(352) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt04lDoorEvent(int x)
{
    volatile int local = x;
}
