#include "common.h"
#include "st05e.h"
#include "layout_texture.h"
#include "thread.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "rotObject.h"
#include "typedef.h"

extern int D_0063AA08;

/* st05e.o's own .data run 0x4F98A0..0x4F9920 (0x80, no MAIN.MAP symbols):
   four 0x20-byte actor mail packets, one per thread hand-off. */

static ActMail waterMain_mes[2] = {{406, actSt05eWaterSwitch}, {429}};

static ActMail water_mes[2] = {{430}, {429}};

static ActMail waterSwitch_mes[2] = {{430}, {429}};

static ActMail solar_mes[2] = {{430}, {429}};

/* .sbss, owned by st05e.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for, and its complement, true when the
   player skipped the demo with START. */
static int demoEnd;

static int demoSkipped;

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
extern int D_0028F4C0[];
extern float D_0063C088;
extern int D_0028F8F4[];
extern int D_0028F8F0[];
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

/* listing lines 228-270 */
void actSt05eWaterStop(volatile int a0)
{
    int th;

    lt_switch_layout(55);

    demoEnd = 0;
    demoSkipped = 0;
    actCreateSubThread(actSt05eWaterFlagOn, 21);

    scpSleepEnemyAll();

    th = actCreateSubThread(actSt05eWaterStopSub, 21);
    while (demoEnd == 0 && (!(D_0028F8F4[0] & 0x800) || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    demoSkipped = demoEnd ^ 1;
    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(267, 0, -1);
        stage_SetAnimation(266, -1, -2);
        scpFadeIn(3.0f);
    }

    scpSearchGobj(1555)->f16C = 1;
    scpSearchGobj(1554)->f16C = 0;

    D_0063AA08 = 0;
    lt_switch_layout(54);

    scpWakeupEnemyAll();

    SetWayGroupActive(5, 1);
}

extern int solar;
/* kept local: this TU's uses of scpIsRotObjectZPlusDirInclude do not fit the prototype in script.h */
extern int scpIsRotObjectZPlusDirInclude(int a0, int a1, int a2);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *h, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *h, short a1);

/* listing lines 319-389 */
void actSt05eSolarChk(volatile int a0)
{
    while (scpIsRotObjectZPlusDirInclude(1556, 0x10D, 0x10F) == 0) {
        _ACTWait(1);
    }

    SetRotObjectLockFlag(scpSearchGobj(1556), 1);

    FinishHint(23);
    FinishHint(25);
    FinishHint(26);

    if (gflagChk(243) == 0 || gflagChk(244) == 0 || gflagChk(245) == 0) {
        lt_switch_layout(55);
        D_0063AA08 = 1;

        scpSleepEnemyAll();

        scpAdpcmPlayRequestFunc(54, &solar, 1, 1, 1);

        stage_SetAnimation(268, 1, 0);

        while (stage_CheckAnimationFinish(268) == 0) {
            if ((D_0028F8F0[1] & 0x800) && scpAdpcmPlayRequestNum() == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
                stage_SetAnimation(268, 0, -1);
                scpFadeIn(3.0f);
                break;
            }
            _ACTWait(1);
        }

        if (solar != 0) {
            scpAdpcmFadeCloseFunc(&solar, 80);
        }

        lt_switch_layout(54);

        D_0063AA08 = 0;
        scpWakeupEnemyAll();
    }

    gflagOff(246);
    gflagOff(247);
    gflagOff(248);
    gflagOff(249);
    gflagOn(233);

    gflagOn(232);
}

void actSt05eWater(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(231) == 0) {
        scpSearchGobj(1555)->f16C = 0;

        water_mes[0].func = actSt05eWaterMain;
        self->mail = water_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(1554)->f16C = 0;

        stage_SetAnimation(266, -1, -2);
    }
}

void actSt05eSolar(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    SetRotObjectArmRadius(scpSearchGobj(1556), 200.0f);

    if (gflagChk(232) == 0) {
        solar_mes[0].func = actSt05eSolarChk;
        self->mail = solar_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        SetRotObjectLockFlag(scpSearchGobj(1556), 1);

        FinishHint(23);
        FinishHint(25);
        FinishHint(26);
    }
}

void actSt05eWaterMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = waterMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt05eWaterSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;
    waterSwitch_mes[0].func = actSt05eWaterStop;
    sub->mail = waterSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt05eWaterFlagOn(volatile int a0)
{
    int i = (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 6.0;

    D_0063C088 = 0.005f;

    while (i-- > 0) {
        if (demoSkipped != 0) {
            D_0063C088 = 1000.0f;
            break;
        }
        _ACTWait(1);
    }
    gflagOn(231);
}

void actSt05eWaterStopSub(volatile int a0)
{
    _ACTWait(60);

    stage_SetAnimation(267, 1, 0);

    stage_SetAnimation(266, -1, -2);

    while (stage_CheckAnimationFinish(267) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}
