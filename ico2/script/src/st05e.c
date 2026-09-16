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

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD0];  /* 0x00 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} Act;

extern int D_0063AA08;

/* st05e.o's own .data run 0x4F98A0..0x4F9920 (0x80, no MAIN.MAP symbols):
   four 0x20-byte actor mail packets, one per thread hand-off. */

static ActMail waterMain_mes[2] = {{406, actSt05eWaterSwitch}, {429}};

static ActMail water_mes[2] = {{430}, {429}};

static ActMail waterSwitch_mes[2] = {{430}, {429}};

static ActMail solar_mes[2] = {{430}, {429}};

extern int D_0063C550;

typedef struct PObjGObj {
    /*0x00*/ char pad00[0x164];
    /*0x164*/ Act *act;
    /*0x168*/ char pad168[0x4];
    /*0x16C*/ int f16C;
} PObjGObj;

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
extern int D_0028F4C0[];
extern float D_0063C088;
extern int D_0063C554;
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

    lt_switch_layout(0x37);

    D_0063C550 = 0;
    D_0063C554 = 0;
    actCreateSubThread(actSt05eWaterFlagOn, 0x15);

    scpSleepEnemyAll();

    th = actCreateSubThread(actSt05eWaterStopSub, 0x15);
    while (D_0063C550 == 0 && (!(D_0028F8F4[0] & 0x800) || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    D_0063C554 = D_0063C550 ^ 1;
    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C550 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(0x10B, 0, -1);
        stage_SetAnimation(0x10A, -1, -2);
        scpFadeIn(3.0f);
    }

    scpSearchGobj(0x613)->f16C = 1;
    scpSearchGobj(0x612)->f16C = 0;

    D_0063AA08 = 0;
    lt_switch_layout(0x36);

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
    while (scpIsRotObjectZPlusDirInclude(0x614, 0x10D, 0x10F) == 0) {
        _ACTWait(1);
    }

    SetRotObjectLockFlag(scpSearchGobj(0x614), 1);

    FinishHint(23);
    FinishHint(25);
    FinishHint(26);

    if (gflagChk(0xF3) == 0 || gflagChk(0xF4) == 0 || gflagChk(0xF5) == 0) {
        lt_switch_layout(0x37);
        D_0063AA08 = 1;

        scpSleepEnemyAll();

        scpAdpcmPlayRequestFunc(0x36, &solar, 1, 1, 1);

        stage_SetAnimation(0x10C, 1, 0);

        while (stage_CheckAnimationFinish(0x10C) == 0) {
            if ((D_0028F8F0[1] & 0x800) && scpAdpcmPlayRequestNum() == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
                stage_SetAnimation(0x10C, 0, -1);
                scpFadeIn(3.0f);
                break;
            }
            _ACTWait(1);
        }

        if (solar != 0) {
            scpAdpcmFadeCloseFunc(&solar, 80);
        }

        lt_switch_layout(0x36);

        D_0063AA08 = 0;
        scpWakeupEnemyAll();
    }

    gflagOff(0xF6);
    gflagOff(0xF7);
    gflagOff(0xF8);
    gflagOff(0xF9);
    gflagOn(0xE9);

    gflagOn(0xE8);
}

void actSt05eWater(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xE7) == 0) {
        scpSearchGobj(0x613)->f16C = 0;

        water_mes[0].func = actSt05eWaterMain;
        self->mail = water_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x612)->f16C = 0;

        stage_SetAnimation(0x10A, -1, -2);
    }
}

void actSt05eSolar(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    SetRotObjectArmRadius(scpSearchGobj(0x614), 200.0f);

    if (gflagChk(0xE8) == 0) {
        solar_mes[0].func = actSt05eSolarChk;
        self->mail = solar_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        SetRotObjectLockFlag(scpSearchGobj(0x614), 1);

        FinishHint(0x17);
        FinishHint(0x19);
        FinishHint(0x1A);
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
        if (D_0063C554 != 0) {
            D_0063C088 = 1000.0f;
            break;
        }
        _ACTWait(1);
    }
    gflagOn(0xE7);
}

void actSt05eWaterStopSub(volatile int a0)
{
    _ACTWait(0x3C);

    stage_SetAnimation(0x10B, 1, 0);

    stage_SetAnimation(0x10A, -1, -2);

    while (stage_CheckAnimationFinish(0x10B) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C550 = 1;
    _ACTWait(0);
}
