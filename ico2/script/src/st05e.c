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

extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int D_0063AA08;
/* st05e.o's own .data run 0x4F98A0..0x4F9920 (0x80, no MAIN.MAP symbols):
   four 0x20-byte actor mail packets, one per thread hand-off. */
extern ActMail D_004F98A0[];
extern ActMail D_004F98C0[];
extern ActMail D_004F98E0[];
extern ActMail D_004F9900[];
extern void actSt05eWaterStop(volatile int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int D_0063C550;
extern int gflagChk(int a0);

typedef struct PObjGObj {
    /*0x00*/ char pad00[0x164];
    /*0x164*/ Act *act;
    /*0x168*/ char pad168[0x4];
    /*0x16C*/ int f16C;
} PObjGObj;

extern PObjGObj *scpSearchGobj(int a0);
extern void actSt05eWaterMain(volatile int a0);
extern int D_0028F4C0[];
extern float D_0063C088;
extern int D_0063C554;
extern void gflagOn(int a0);
extern void SetRotObjectArmRadius(PObjGObj *a0, float f);
extern void SetRotObjectLockFlag(PObjGObj *a0, int a1);
extern void FinishHint(int no);
extern void actSt05eSolarChk(volatile int a0);
extern int D_0028F8F4[];
extern int D_0028F8F0[];
extern void lt_switch_layout(int no);
extern int actCreateSubThread(void *entry, int prio);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern int scpAdpcmPlayRequestNum(void);
extern void iosThreadSetPri(int th, int pri);
extern void scpFadeOut(float f, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern void scpFadeIn(float f);
extern int lt_fade_status(void);
extern void SetWayGroupActive(int group, int on);
extern void actSt05eWaterFlagOn(volatile int a0);
extern void actSt05eWaterStopSub(volatile int a0);

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
extern int scpIsRotObjectZPlusDirInclude(int a0, int a1, int a2);
extern void scpAdpcmPlayRequestFunc(int a0, int *h, int a2, int a3, int a4);
extern void scpAdpcmFadeCloseFunc(int *h, short a1);
extern void gflagOff(int a0);

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

        D_004F98C0[0].func = actSt05eWaterMain;
        self->mail = D_004F98C0;
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
        D_004F9900[0].func = actSt05eSolarChk;
        self->mail = D_004F9900;
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

    sub->mainMail = D_004F98A0;
    while (1) {
        _ACTWait(1);
    }
}

void actSt05eWaterSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;
    D_004F98E0[0].func = actSt05eWaterStop;
    sub->mail = D_004F98E0;
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
