#include "common.h"

typedef struct ActMail {
    int mail;          /* 0x00 */
    void (*func)(int); /* 0x04 */
    int unk08;         /* 0x08 */
    int unk0C;         /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD4]; /* 0x00 */
    ActMail *mail;    /* 0xD4 */
} Act;

extern Act *actInitialize(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void _ACTWait(int a0);
extern int stage_CheckAnimationFinish(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern char *D_00639EA8;

void actSt04cEnd(void)
{
    if (D_00639EA8 != 0) {
        if (gflagChk(0xA3) == 0) {
            gflagOn(0x187);
        }
    }
}

typedef union StVec {
    float f[4];
    long long ll[2];
} StVec;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */
typedef union {
    float f[4];
    long long d[2];
} ConstVec;

static const StVec doorDownChkPos = {{0.0f, 84.0f, -1359.0f, 0.0f}};

static const ConstVec doorDownEffectPos = {{0.0f, 50.0f, -1450.0f, 1.0f}};

static const ConstVec doorDownEffect2Pos = {{-2.0f, 250.0f, -1450.0f, 1.0f}};

static const ConstVec doorDownEffect3Pos = {{5.0f, 260.0f, -1450.0f, 1.0f}};

extern int D_00639EA4;
extern int scpTriggerBall(int a0, int gobj, float r);
extern int actCreateSubThread(void *entry, int prio);
extern void actSt04cDoorDownEffect(volatile int a0);
extern int soundSeDefPlay(int se, int a1, void *pos, int a3);
extern void gflagOn(int a0);

/* listing lines 326-357 */
void actSt04cDoorDownChk(volatile int a0)
{
    StVec pos;

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0) {
        _ACTWait(1);
    }

    _ACTWait(30);

    actCreateSubThread(actSt04cDoorDownEffect, 0x15);

    stage_SetAnimation(0xFD, 1, 0);

    pos = doorDownChkPos;

    _ACTWait(30);
    soundSeDefPlay(0x4C5, 0, &pos, 1);
    _ACTWait(30);
    soundSeDefPlay(0x4C6, 0, &pos, 1);

    while (stage_CheckAnimationFinish(0xFD) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(0xA2);
}

extern int D_0063AA08;
extern int D_0063C510;
extern int D_0028F8F4[];
extern void lt_switch_layout(int a0);
extern void gflagOff(int a0);
extern void iosThreadSetPri(int th, int pri);
extern int scpAdpcmPlayRequestNum(void);
extern void scpFadeOut(float f, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern void scpFadeIn(float f);
extern int lt_fade_status(void);
extern void actSt04cIntroChkSub(volatile int a0);

/* listing lines 592-637 */
void actSt04cIntroChk(volatile int a0)
{
    int th;

    while (scpTriggerBall(a0, D_00639EA4, 1000.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);

    gflagOff(0x186);

    gflagOn(0xA1);
    D_0063AA08 = 1;

    stage_SetAnimation(0x160, 1, 0);

    th = actCreateSubThread(actSt04cIntroChkSub, 0x15);
    D_0063C510 = 0;

    while (D_0063C510 == 0 && (!(D_0028F8F4[0] & 0x800) || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C510 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(0x160, 0, -1);
        scpFadeIn(3.0f);
    }

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

extern int D_0028F8F0[];
extern int scpSearchGobj(int a0);
extern int GetAttackCheckBoundaryManagerStatus(int g);
extern void FinishHint(int no);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern void soundSeDefStop(int h);

/* listing lines 705-753 */
void actSt04lDoorChk(volatile int a0)
{
    int x = a0;
    int h;
    int i;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0xC7) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x44A))) {
        case 0:
            _ACTWait(1);
            break;

        case 1:
            stage_SetAnimation(0xE8, 1, 0);
            while (stage_CheckAnimationFinish(0xE8) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;

        case 2:
            *(int *)(scpSearchGobj(0x44A) + 0x16C) = 0;
            FinishHint(15);

            lt_switch_layout(0x37);

            D_0063AA08 = 1;
            scpSleepEnemyAll();

            gflagOn(0xC7);

            stage_SetAnimation(0xE7, 1, 0);

            h = soundSeDefPlay(0x532, 0, 0, 1);

            for (i = 90; i-- > 0;) {
                if ((D_0028F8F0[1] & 0x800) && scpAdpcmPlayRequestNum() == 0) {
                    scpFadeOut(16.0f, 0, 0, 0);
                    while (scpFadeChk() != 0) {
                        _ACTWait(1);
                    }
                    while (lt_fade_status() != 2) {
                        _ACTWait(1);
                    }
                    stage_SetAnimation(0xE7, 0, -1);
                    scpFadeIn(3.0f);
                    break;
                }
                _ACTWait(1);
            }

            soundSeDefStop(h);

            soundSeDefPlay(0x533, 0, 0, 1);

            scpWakeupEnemyAll();
            D_0063AA08 = 0;

            lt_switch_layout(0x36);
            break;
        }
    }
}

void actSt04cSolarXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8A) == 0) {
        stage_SetAnimation(0x12E, -1, -2);
    }
}

static ActMail doorDown_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail intro_mes[2] = {{430}, {429}};

static ActMail st04lDoor_mes[2] = {{430}, {429}};

extern void actSt04lDoorChk(int a0);
extern int scpSearchGobj(int a0);
extern void FinishHint(int a0);

void actSt04lDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xC7) == 0) {
        stage_SetAnimation(0xE7, 0, 0);
        st04lDoor_mes[0].func = actSt04lDoorChk;
        self->mail = st04lDoor_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xE7, 0, -1);
        *(int *)(scpSearchGobj(0x44A) + 0x16C) = 0;
        FinishHint(0xF);
    }
}

extern void actSt04cIntroChk(int a0);

void actSt04cIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xA1) == 0) {
        intro_mes[0].func = actSt04cIntroChk;
        self->mail = intro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern void actSt04cDoorDownChk(int a0);

void actSt04cDoorDown(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    if (gflagChk(0xA2) == 0) {
        doorDown_mes[0].func = actSt04cDoorDownChk;
        self->mail = doorDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern void actSt04cEneChk(int a0);

void actSt04cEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xA3) == 0) {
        ene_mes[0].func = actSt04cEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt04cEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);
    while (gflagChk(0xA4) == 0) {
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
    while (gflagChk(0xA4) == 0) {
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

    if (gflagChk(0xE6) != 0) {
        *(int *)(scpSearchGobj(0x446) + 0x16C) = 0;
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
    for (i = 0; i < 0x32; i++) {
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

extern char *D_00639EA8;

void actSt04cEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0xB000000) == 0) {
        _ACTWait(1);
    }
    gflagOff(0x187);
    _ACTWait(1);
    gflagOn(0xA3);
    gflagOn(0xA4);
}

extern int D_0063C510;

void actSt04cIntroChkSub(volatile int a0)
{
    while (stage_CheckAnimationFinish(0x160) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C510 = 1;
    _ACTWait(0);
}

void actSt04lDoorEvent(int x)
{
    volatile int local = x;
}
