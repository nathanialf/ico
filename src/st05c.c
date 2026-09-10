#include "common.h"

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

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    Act *act;          /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObj;

typedef union StVec {
    float f[4];
    long long ll[2];
} StVec;

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void gflagOn(int a0);
extern void gflagOff(int a0);
extern void SleepHint(int a0);
extern void WakeupHint(int a0);
extern void FinishHint(int a0);
extern PObjGObj *scpSearchGobj(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int scpTriggerBall(int a0, int gobj, float r);
extern int soundSeDefPlay(int se, int a1, void *pos, int a3);
extern void soundSeDefStop(int handle);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern int actCreateSubThread(void *entry, int prio);
extern void iosThreadSetPri(int th, int pri);
extern int GetAttackCheckBoundaryManagerStatus(PObjGObj *gobj);
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern int scpAdpcmPlayRequestNum(void);
extern void scpFadeOut(float f, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern void scpFadeIn(float f);
extern int lt_fade_status(void);

typedef struct Pad {
    int on;  /* 0x00 */
    int trg; /* 0x04 */
} Pad;

extern Pad D_0028F8F0[];
extern void actSt04rDoorSub(volatile int a0);
extern void actSt04rDoor2Sub(volatile int a0);
extern int scpEffectStart(StVec *a0, int a1);
extern int D_00639EA4;
extern int D_00639EA8;
extern int D_0063AA08;
extern int D_0063C54C;
extern StVec D_00622AF0;
extern const StVec D_00622B00;
extern const StVec D_00622B10;
extern const StVec D_00622B20;
extern ActMail D_004F9740[];
extern ActMail D_004F9760[];
extern ActMail D_004F9780[];
extern ActMail D_004F97A0[];
extern ActMail D_004F97C0[];
extern void actSt05cDoorDownChk(volatile int a0);
extern void actSt05cDoorDownEffect(volatile int a0);
extern void actSt05cEneChk(volatile int a0);
extern void actSt05cCrestHintChk(volatile int a0);
extern void actSt04rDoorChk(volatile int a0);
extern void actSt04rDoor2Chk(volatile int a0);

void actSt05cDoorDownChk(volatile int a0)
{
    StVec pos;

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    _ACTWait(0x1E);
    gflagOff(0x186);
    actCreateSubThread(actSt05cDoorDownEffect, 0x15);
    stage_SetAnimation(0x15B, 1, 0);

    pos = D_00622AF0;
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, &pos, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, &pos, 1);

    while (stage_CheckAnimationFinish(0x15B) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    gflagOn(0xA5);
    D_0063AA08 = 0;
}

void actSt04rDoorChk(volatile int a0)
{
    int x = a0;
    int th;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0xFF) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x564))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(0x14E, 1, 0);
            while (stage_CheckAnimationFinish(0x14E) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x564)->f16C = 0;
            lt_switch_layout(0x37);
            D_0063AA08 = 1;
            scpSleepEnemyAll();
            gflagOn(0xFF);
            D_0063C54C = 0;
            th = actCreateSubThread(actSt04rDoorSub, 0x15);

            while (D_0063C54C == 0 &&
                   ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
                _ACTWait(1);
            }

            iosThreadSetPri(th + 0x24, 0x22);

            if (D_0063C54C == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
                stage_SetAnimation(0x14C, 0, -1);
                scpFadeIn(3.0f);
            }

            soundSeDefPlay(0x533, 0, 0, 1);
            scpWakeupEnemyAll();
            D_0063AA08 = 0;
            lt_switch_layout(0x36);
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

    while (gflagChk(0x100) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x565))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(0x14F, 1, 0);
            while (stage_CheckAnimationFinish(0x14F) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x565)->f16C = 0;
            lt_switch_layout(0x37);
            D_0063AA08 = 1;
            scpSleepEnemyAll();
            gflagOn(0x100);
            D_0063C54C = 0;
            th = actCreateSubThread(actSt04rDoor2Sub, 0x15);

            while (D_0063C54C == 0 &&
                   ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
                _ACTWait(1);
            }

            iosThreadSetPri(th + 0x24, 0x22);

            if (D_0063C54C == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
                stage_SetAnimation(0x14D, 0, -1);
                scpFadeIn(3.0f);
            }

            soundSeDefPlay(0x533, 0, 0, 1);
            scpWakeupEnemyAll();
            D_0063AA08 = 0;
            lt_switch_layout(0x36);
            break;
        }
    }
}

void actSt05cSolarXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8B) == 0) {
        stage_SetAnimation(0x130, -1, -2);
    }
}

void actSt05cWaterXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xE7) != 0) {
        scpSearchGobj(0x560)->f16C = 0;
    }
}

void actSt04rDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xFF) == 0) {
        stage_SetAnimation(0x14C, 0, 0);
        D_004F9780[0].func = actSt04rDoorChk;
        self->mail = D_004F9780;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x14C, 0, -1);
        scpSearchGobj(0x564)->f16C = 0;
    }
}

void actSt04rDoor2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x100) == 0) {
        stage_SetAnimation(0x14D, 0, 0);
        D_004F97A0[0].func = actSt04rDoor2Chk;
        self->mail = D_004F97A0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x14D, 0, -1);
        scpSearchGobj(0x565)->f16C = 0;
    }
}

void actSt05cDoorDown(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    if (gflagChk(0xA5) == 0) {
        D_004F9740[0].func = actSt05cDoorDownChk;
        self->mail = D_004F9740;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt05cEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xA7) == 0) {
        D_004F9760[0].func = actSt05cEneChk;
        self->mail = D_004F9760;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt05cEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0xA8) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_MaskOff(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void actSt05cEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0xA8) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void actSt05cCrestHint(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xA9) == 0) {
        SleepHint(0x17);
        D_004F97C0[0].func = actSt05cCrestHintChk;
        self->mail = D_004F97C0;
        ACTSendMailCorrect(a0, 0x1AE);
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

    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            a = D_00622B00;
            scpEffectStart(&a, 0);
            break;
        case 0x1E:
            b = D_00622B10;
            scpEffectStart(&b, 0);
            c = D_00622B20;
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

    while (D_00639EA8 == 0 || gflagChk(0xFF) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x258);
    gflagOn(0xA7);
    gflagOn(0xA8);
}

void actSt04rDoorSub(volatile int a0)
{
    int h;

    stage_SetAnimation(0x14C, 1, 0);
    h = soundSeDefPlay(0x532, 0, 0, 1);
    _ACTWait(0x5A);
    soundSeDefStop(h);
    D_0063C54C = 1;
    _ACTWait(0);
}

void actSt04rDoor2Sub(volatile int a0)
{
    int h;

    stage_SetAnimation(0x14D, 1, 0);
    h = soundSeDefPlay(0x532, 0, 0, 1);
    _ACTWait(0x5A);
    soundSeDefStop(h);
    D_0063C54C = 1;
    _ACTWait(0);
}

void actSt05cCrestHintChk(volatile int a0)
{
    while (gflagChk(0xF3) == 0 || gflagChk(0xF4) == 0 || gflagChk(0xF5) == 0 ||
           gflagChk(0xE8) != 0) {
        _ACTWait(1);
    }

    gflagOn(0xA9);
    WakeupHint(0x17);
}
