#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0xD0];           /* 0x00 */
    ActMail *mainMail;          /* 0xD0 */
    ActMail *mail;              /* 0xD4 */
} Act;
typedef struct PObjGObj {
    char pad00[0x164];          /* 0x000 */
    int act;                    /* 0x164 */
    char pad168[0x4];           /* 0x168 */
    int f16C;                   /* 0x16C */
} PObjGObj;

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int D_0063AA08;
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void gflagOn(int a0);
extern void gflagOff(int a0);
extern PObjGObj *scpSearchGobj(int a0);
extern int scpTriggerBall(int a0, void *a1, float radius);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void soundSeDefStop(int handle);

extern void SetWayGroupActive(int a0, int a1);
extern int scpTriggerFloorAttr(void *obj, int attr);
extern void FinishHint(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void stage_SetLoopFlag(int a0, int a1);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int D_0063C558;
extern void debug_StdPrintfDummy(char *fmt);
extern void *D_00639EA4;
extern void *D_00639EA8;

void actSt06aInit(void)
{
    if (gflagChk(0x6A) == 0) {
        SetWayGroupActive(9, 0);
        SetWayGroupActive(0xA, 0);
    } else {
        SetWayGroupActive(9, 1);
        SetWayGroupActive(0xA, 1);
        FinishHint(0x13);
    }

    if (gflagChk(0x6B) == 0) {
        SetWayGroupActive(0xC, 0);
    } else {
        SetWayGroupActive(0xC, 1);
    }
}
extern void SetRotObjectLockFlag(PObjGObj *a0, int a1);
extern void ReInitBoxGeo(PObjGObj *a0);
extern void actSt06aSuimonChk(volatile int a0);
extern ActMail D_004F9920[];

void actSt06aSuimon(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6A) == 0) {
        stage_SetAnimation(0x6B, 0, 0);
        scpSearchGobj(0x6D7)->f16C = 0;
        stage_SetLoopFlag(0x6C, 1);
        stage_SetAnimation(0x6C, 1, 0);
        D_004F9920[0].func = actSt06aSuimonChk;
        self->mail = D_004F9920;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x6B, 0, -1);
        stage_SetAnimation(0x6D, 0, -1);
        scpSearchGobj(0x6D8)->f16C = 0;
        SetRotObjectLockFlag(scpSearchGobj(0x6EE), 1);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(0x6ED));
    }
}
typedef struct Pad {
    int unk00;                  /* 0x00 */
    int trg;                    /* 0x04 */
    char unk08[0x50];           /* 0x08 */
} Pad;
extern Pad D_0028F8F0[];
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyAll(void);
extern void WakeupHint(int a0);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
extern char *shutter;
extern void actSt06aShutterOpenSub(volatile int a0);
extern void scpWakeupEnemyAll(void);
extern int actCreateSubThread(void *entry, int prio);
extern void actSt06aJumpSub(volatile int a0);
extern int scpAdpcmPlayRequestNum(void);
extern void iosThreadSetPri(int a0, int a1);
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern void scpFadeIn(float f);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern void SetCameraFlag_LwsCutBack(void);extern int suimon;
extern int D_0063C55C;
extern float scpGetRotObjectRotCount(int a0);
extern void actSt06aSuimonFlagOn(volatile int a0);
extern void actSt06aSuimonEffect(volatile int a0);
extern void actSt06aSuimonSub(volatile int a0);
extern float D_004F9940[];

void actSt06aSuimonChk(volatile int a0)
{
    int he;
    int hs;

    while ((scpGetRotObjectRotCount(0x6EE) < -2.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    FinishHint(0x13);

    SetRotObjectLockFlag(scpSearchGobj(0x6EE), 1);

    stage_SetLoopFlag(0x6C, 0);
    stage_SetLoopFlag(0x71, 0);
    stage_SetAnimation(0x71, 0, 0);

    soundSeDefPlay(0x54F, 0, D_004F9940, 1);

    D_0063AA08 = 1;
    scpSleepEnemyAll();

    _ACTWait(0x1E);

    scpAdpcmPlayRequestFunc(0x44, &suimon, 1, 1, 1);

    while (suimon == 0) {
        _ACTWait(1);
    }

    D_0063C558 = 0;
    D_0063C55C = 0;

    actCreateSubThread(actSt06aSuimonFlagOn, 0x15);
    he = actCreateSubThread(actSt06aSuimonEffect, 0x15);
    hs = actCreateSubThread(actSt06aSuimonSub, 0x15);

    while (D_0063C558 == 0 &&
           ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    D_0063C55C = D_0063C558 ^ 1;

    iosThreadSetPri(hs + 0x24, 0x22);
    iosThreadSetPri(he + 0x24, 0x22);

    if (D_0063C558 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&suimon, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x6B, 0, -1);
        stage_SetAnimation(0x6D, 0, -1);
        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);

    scpSearchGobj(0x6D7)->f16C = 1;
    scpSearchGobj(0x6D8)->f16C = 0;

    SetWayGroupActive(9, 1);
    SetWayGroupActive(0xA, 1);
}
extern void actSt06aDoorDownChk(volatile int a0);
extern void actSt06aDoorUpChk(volatile int a0);
extern ActMail D_004F9950[];
extern ActMail D_004F9970[];

void actSt06aDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(0x70, 0, 0);
        _ACTWait(0x3C);
        D_004F9950[0].func = actSt06aDoorDownChk;
        self->mail = D_004F9950;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x6F, 0, 0);
        D_004F9970[0].func = actSt06aDoorUpChk;
        self->mail = D_004F9970;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
/* The four door-boundary X/Z corners and the exit-camera Z live in the -G8
   gp float pool and are written by the stage's layout/script side, so the
   compiler may not sink their loads into a jal delay slot; ROM has a nop at
   every one of these call sites. */
extern volatile float D_00639998;
extern volatile float D_0063999C;
extern volatile float D_006399A0;
extern volatile float D_006399A4;
extern volatile float D_006399AC;
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
extern void scpWakeupItemWithBoundary(float a0, float a1, float a2, float a3);
extern void actSt06aDoorUpEffect(volatile int a0);
extern void actSt06aDoorDownEffect(volatile int a0);
extern long long D_00622B90[];
extern ActMail D_004F9990[];
extern ActMail D_004F99B0[];

void actSt06aDoorUpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt06aDoorUpEffect, 0x15);

    scpWakeupItemWithBoundary(D_00639998, D_0063999C, -620.0f, 100.0f);

    stage_SetAnimation(0x6F, 1, 0);

    buf[0] = D_00622B90[0];
    buf[1] = D_00622B90[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x6F) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004F9990[0].func = actSt06aDoorDownChk;
    sub->mail = D_004F9990;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt06aDoorDownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt06aDoorDownEffect, 0x15);

    scpWakeupItemWithBoundary(D_006399A0, D_006399A4, -620.0f, 100.0f);

    stage_SetAnimation(0x70, 1, 0);

    buf[0] = D_00622B90[0];
    buf[1] = D_00622B90[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x70) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004F99B0[0].func = actSt06aDoorUpChk;
    sub->mail = D_004F99B0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt06aShutterOpen(volatile int a0)
{
    int h;

    lt_switch_layout(0x37);
    gflagOn(0x6B);
    WakeupHint(0x13);
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(0x53, (int *)&shutter, 1, 1, 0);

    h = actCreateSubThread(actSt06aShutterOpenSub, 0x15);

    D_0063C558 = 0;

    while (D_0063C558 == 0 &&
           ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C558 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (shutter == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc((int *)&shutter, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x6E, 0, -1);
        SetCameraFlag_LwsCutBack();
        scpFadeIn(3.0f);
    }

    scpSearchGobj(0x6CE)->f16C = 0;
    scpSearchGobj(0x6CF)->f16C = 1;
    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    SetWayGroupActive(0xC, 1);
}
extern void SetCameraFlag_GamecamCutBack(void);
extern void actSt06aBoxSub(volatile int a0);

void actSt06aBoxChk(volatile int a0)
{
    int h;

    while (scpTriggerBall(a0, scpSearchGobj(0x6ED), 300.0f) == 0 ||
           gflagChk(0x6A) != 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    gflagOn(0x6D);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    h = actCreateSubThread(actSt06aBoxSub, 0x15);

    D_0063C558 = 0;

    while (D_0063C558 == 0 &&
           ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C558 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        scpSearchGobj(0x6ED)->f16C = 0;
        stage_SetAnimation(0x73, 0, -1);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(8.0f);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}
extern void ReviveAllCarryableItemsWithRandomVelocity(float a0, float a1);

void actSt06aStatueChk(volatile int a0)
{
    int handle;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0xB000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0xB000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    scpSearchGobj(0x715)->f16C = 0;
    stage_SetAnimation(0x103, -1, -2);
    stage_SetAnimation(0x75, 1, 0);

    handle = soundSeDefPlay(0x54D, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x75, 0x32, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerBall(a0, scpSearchGobj(0x6EA), 150.0f) != 0) {
        ReviveAllCarryableItemsWithRandomVelocity(-50.0f, 0.0f);
    }

    while (stage_CheckAnimationFrame(0x75, 0x6D, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(handle);

    while (stage_CheckAnimationFinish(0x75) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);

    _ACTWait(0x78);

    gflagOn(0x71);
}
extern int toge;
extern int D_0063AA00;
extern int GetCharHeldItem(void *a0);
extern void scpPlayMot(void *a0, int a1);

void actSt06aHeadChk(volatile int a0)
{
    while (scpTriggerBall(a0, scpSearchGobj(0x6EA), 70.0f) == 0 ||
           gflagChk(0x71) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();
    gflagOn(0x72);

    _ACTWait(0x78);

    scpAdpcmPlayRequestFunc(0x37, &toge, 1, 1, 1);

    while (toge == 0) {
        _ACTWait(1);
    }

    if (D_0063AA00 == 0) {
        stage_SetAnimation(0x77, 1, 0);

        if (scpTriggerFloorAttr(D_00639EA4, 0x7000000) == 0 &&
            scpTriggerFloorAttr(D_00639EA4, 0xB000000) == 0) {
            SetCameraFlag_LwsCutBack();
        }

        while (stage_CheckAnimationFrame(0x77, 0x82, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(0x35B, 0, 0, 1);

        while (stage_CheckAnimationFrame(0x77, 0xD0, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        scpSearchGobj(0x6EB)->f16C = 1;

        while (stage_CheckAnimationFinish(0x77) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
    }

    if (D_0063AA00 != 0) {
        stage_SetAnimation(0x78, 1, 0);

        if (scpTriggerFloorAttr(D_00639EA4, 0x7000000) == 0 &&
            scpTriggerFloorAttr(D_00639EA4, 0xB000000) == 0) {
            SetCameraFlag_LwsCutBack();
        }

        while (stage_CheckAnimationFrame(0x78, 0x82, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(0x35B, 0, 0, 1);

        while (stage_CheckAnimationFrame(0x78, 0xD0, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        scpSearchGobj(0x6EC)->f16C = 1;

        while (stage_CheckAnimationFinish(0x78) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
    }

    if (GetCharHeldItem(D_00639EA4) == 6) {
        scpPlayMot(D_00639EA4, 0);
    }

    scpSearchGobj(0x6EA)->f16C = 0;

    if (toge != 0) {
        scpAdpcmFadeCloseFunc(&toge, 0x50);
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}
void actSt06aJumpMove(volatile int a0)
{
    int h;

    lt_switch_layout(0x37);
    scpSleepEnemyAll();

    h = actCreateSubThread(actSt06aJumpSub, 0x15);

    D_0063C558 = 0;

    while (D_0063C558 == 0 &&
           ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C558 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetLoopFlag(0x71, 1);
        stage_SetAnimation(0x71, 1, 0);
        gflagOn(0x74);
        stage_SetAnimation(0x72, 0, -1);
        SetCameraFlag_LwsCutBack();
        scpFadeIn(8.0f);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}
extern char D_00622C08[];
extern float D_004F9E70[];
extern void actSt06aPistonFlagOffChk(volatile int a0);
extern ActMail D_004F9E80[];

void actSt06aPistonFlagOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (gflagChk(0x74) == 0 || gflagChk(0x6A) != 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFrame(0x71, 0x7A, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(0x551, 0, D_004F9E70, 1);
    gflagOn(0x75);
    debug_StdPrintfDummy(D_00622C08);

    while (stage_CheckAnimationFrame(0x71, 0x7C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004F9E80[0].func = actSt06aPistonFlagOffChk;
    sub->mail = D_004F9E80;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void SleepHint(int a0);
extern void actSt06aShutterMain(volatile int a0);
extern ActMail D_004F99F0[];

void actSt06aShutter(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6B) == 0) {
        stage_SetAnimation(0x6E, 0, 0);
        scpSearchGobj(0x6CF)->f16C = 0;
        SleepHint(0x13);
        D_004F99F0[0].func = actSt06aShutterMain;
        self->mail = D_004F99F0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x6E, 0, -1);
        scpSearchGobj(0x6CE)->f16C = 0;
    }
}
extern void actSt06aExitChk(volatile int a0);
extern ActMail D_004F9A30[];

void actSt06aExit(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F9A30[0].func = actSt06aExitChk;
    self->mail = D_004F9A30;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void actSt06aExitGirlChk(volatile int a0);
extern ActMail D_004F9A50[];

void actSt06aExitGirl(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F9A50[0].func = actSt06aExitGirlChk;
    self->mail = D_004F9A50;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void actSt06aBoxChk(volatile int a0);
extern ActMail D_004F9A70[];

void actSt06aBox(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6C) == 0 && gflagChk(0x6D) == 0) {
        D_004F9A70[0].func = actSt06aBoxChk;
        self->mail = D_004F9A70;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x6ED)->f16C = 0;
    }
}
extern void actSt06aBox2Chk(volatile int a0);
extern ActMail D_004F9A90[];

void actSt06aBox2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6C) == 0 && gflagChk(0x6D) == 0) {
        D_004F9A90[0].func = actSt06aBox2Chk;
        self->mail = D_004F9A90;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void actSt06aBox3Chk(volatile int a0);
extern ActMail D_004F9AB0[];

void actSt06aBox3(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6C) == 0 && gflagChk(0x6D) == 0) {
        D_004F9AB0[0].func = actSt06aBox3Chk;
        self->mail = D_004F9AB0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void actSt06aBoxEvent2InChk(volatile int a0);
extern void actSt06aBoxEvent2OutChk(volatile int a0);
extern ActMail D_004F9AF0[];
extern ActMail D_004F9B10[];

void actSt06aBoxEvent2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6E) == 0) {
        D_004F9AF0[0].func = actSt06aBoxEvent2InChk;
        self->mail = D_004F9AF0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        D_004F9B10[0].func = actSt06aBoxEvent2OutChk;
        self->mail = D_004F9B10;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void actSt06aWayOnChk(volatile int a0);
extern ActMail D_004F9B70[];

void actSt06aWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F9B70[0].func = actSt06aWayOnChk;
    self->mail = D_004F9B70;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void actSt06aWallWayOnChk(volatile int a0);
extern void actSt06aWallWayOffChk(volatile int a0);
extern ActMail D_004F9BD0[];
extern ActMail D_004F9BF0[];

void actSt06aWallWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6F) == 0) {
        D_004F9BD0[0].func = actSt06aWallWayOnChk;
        self->mail = D_004F9BD0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        SetWayGroupActive(0x17, 1);
        SetWayGroupActive(0x18, 1);
        D_004F9BF0[0].func = actSt06aWallWayOffChk;
        self->mail = D_004F9BF0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void actSt06aWallWay2OnChk(volatile int a0);
extern void actSt06aWallWay2OffChk(volatile int a0);
extern ActMail D_004F9C50[];
extern ActMail D_004F9C70[];

void actSt06aWallWay2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x70) == 0) {
        D_004F9C50[0].func = actSt06aWallWay2OnChk;
        self->mail = D_004F9C50;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        SetWayGroupActive(0x17, 1);
        SetWayGroupActive(0x18, 1);
        D_004F9C70[0].func = actSt06aWallWay2OffChk;
        self->mail = D_004F9C70;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F9CD0[];
extern void actSt06aStatueChk(volatile int a0);

void actSt06aStatue(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x71) == 0) {
        stage_SetAnimation(0x75, 0, 0);
        D_004F9CD0[0].func = actSt06aStatueChk;
        self->mail = D_004F9CD0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x75, 0, -1);
        scpSearchGobj(0x715)->f16C = 0;
        stage_SetAnimation(0x103, -1, -2);
    }
}
extern void actSt06aHeadChk(volatile int a0);
extern ActMail D_004F9CF0[];

void actSt06aHead(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x72) == 0) {
        scpSearchGobj(0x6EB)->f16C = 0;
        scpSearchGobj(0x6EC)->f16C = 0;
        D_004F9CF0[0].func = actSt06aHeadChk;
        self->mail = D_004F9CF0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        if (D_0063AA00 == 0) {
            scpSearchGobj(0x6EC)->f16C = 0;
        }
        if (D_0063AA00 != 0) {
            scpSearchGobj(0x6EB)->f16C = 0;
        }
    }
}
extern void actSt06aTreeChk(volatile int a0);
extern ActMail D_004F9D10[];

void actSt06aTree(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x72) == 0) {
        scpSearchGobj(0x6EA)->f16C = 0;
        D_004F9D10[0].func = actSt06aTreeChk;
        self->mail = D_004F9D10;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x6EA)->f16C = 0;
    }
}
extern void actSt06aBallDeleteChk(volatile int a0);
extern ActMail D_004F9AD0[];

void actSt06aBallDelete(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F9AD0[0].func = actSt06aBallDeleteChk;
    self->mail = D_004F9AD0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void actSt06aKyomiOffChk(volatile int a0);
extern ActMail D_004F9D30[];

void actSt06aKyomi(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F9D30[0].func = actSt06aKyomiOffChk;
    self->mail = D_004F9D30;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void actSt06aJumpMain(volatile int a0);
extern ActMail D_004F9DB0[];

void actSt06aJump(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x74) == 0) {
        stage_SetAnimation(0x71, 0, 0);
        D_004F9DB0[0].func = actSt06aJumpMain;
        self->mail = D_004F9DB0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else if (gflagChk(0x6A) == 0) {
        stage_SetLoopFlag(0x71, 1);
        stage_SetAnimation(0x71, 1, 0);
    } else {
        stage_SetAnimation(0x71, 0, 0);
    }
}
extern void actSt06aPistonRideOnChk(volatile int a0);
extern ActMail D_004F9DF0[];

void actSt06aPiston(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F9DF0[0].func = actSt06aPistonRideOnChk;
    self->mail = D_004F9DF0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void actSt06aPistonFlagOnChk(volatile int a0);
extern ActMail D_004F9E50[];

void actSt06aPistonFlag(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F9E50[0].func = actSt06aPistonFlagOnChk;
    self->mail = D_004F9E50;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void actSt06aSoundChk(volatile int a0);
extern ActMail D_004F9EC0[];

void actSt06aSound(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6A) == 0) {
        D_004F9EC0[0].func = actSt06aSoundChk;
        self->mail = D_004F9EC0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void actSt06aSound2Chk(volatile int a0);
extern ActMail D_004F9EF0[];

void actSt06aSound2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x6A) == 0) {
        D_004F9EF0[0].func = actSt06aSound2Chk;
        self->mail = D_004F9EF0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt06aSuimonEvent(int x) {
    volatile int local = x;
}
extern long long D_00622B60[];
extern long long D_00622B70[];
extern long long D_00622B80[];
extern int scpEffectStart(int *buf, int a1);

void actSt06aSuimonEffect(volatile int a0){ long long b1[2]; long long b2[2]; long long b3[2];
 long long v0a=D_00622B60[0]; long long v0b=D_00622B70[0]; long long v0c=D_00622B80[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622B60[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622B70[1]; scpEffectStart((int*)b2,0);
             b3[0]=v0c; b3[1]=D_00622B80[1]; scpEffectStart((int*)b3,0); break;
  } _ACTWait(1); }
 _ACTWait(0); }
extern int D_0028F4C0[];
extern float D_006399A8;
extern float D_0063C088;

void actSt06aSuimonFlagOn(volatile int a0)
{
    int i = (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 7.0;

    D_0063C088 = D_006399A8;

    while (i-- > 0) {
        if (D_0063C55C != 0) {
            D_0063C088 = 1000.0f;
            break;
        }
        _ACTWait(1);
    }
    gflagOn(0x6A);
}

void actSt06aSuimonSub(volatile int a0)
{
    stage_SetAnimation(0x6B, 1, 0);
    stage_SetAnimation(0x6D, 1, 0);

    while (stage_CheckAnimationFinish(0x6B) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C558 = 1;
    _ACTWait(0);
}
void actSt06aDoorEvent(int x) {
    volatile int local = x;
}
extern long long D_00622BA0[];
extern long long D_00622BB0[];
extern void _ACTWait(int a0);
extern int scpEffectStart(int *buf, int a1);

void actSt06aDoorUpEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622BA0[0]; long long v0b=D_00622BB0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622BA0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622BB0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
void actSt06aDoorDownEffect(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00622BB0[0]; long long v0b=D_00622BA0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00622BB0[1]; scpEffectStart((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00622BA0[1]; scpEffectStart((int*)b2,0); break;
  } _ACTWait(1); } }
extern ActMail D_004F99D0[];

void actSt06aShutterMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = D_004F99D0;

    while (1) {
        _ACTWait(1);
    }
}
extern ActMail D_004F9A10[];
extern void actSt06aShutterOpen(volatile int a0);

void actSt06aShutterSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004F9A10[0].func = actSt06aShutterOpen;
    sub->mail = D_004F9A10;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void AdpcmPlay(int a0);

void actSt06aShutterOpenSub(volatile int a0)
{
    _ACTWait(0x3C);

    while (shutter == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(shutter + 0x2C));

    stage_SetAnimation(0x6E, 1, 0);

    while (stage_CheckAnimationFinish(0x6E) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C558 = 1;
    _ACTWait(0);
}
extern int RequestStageChange(int a0, void *a1, int a2, float a3, float a4);

void actSt06aExitChk(volatile int a0)
{
    while (gflagChk(0x6A) != 0 ||
           scpTriggerBall(a0, D_00639EA4, 400.0f) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 0;
    RequestStageChange(3, D_00639EA4, 0, 16.0f, 16.0f);
}
extern const long long D_00622BC0[];
extern const long long D_00622BD0[];
extern void RequestStageChangeDirect(void *a0, int a1, void *buf, int a3);
extern void SetDirectRootPosition(void *a0, void *a1);
extern void ScpCallCameraSetTarget(float x, float y, float z);

void actSt06aExitGirlChk(volatile int a0)
{
    long long buf1[2];
    long long buf2[2];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(0x6A) != 0 ||
           scpTriggerBall(a0, D_00639EA8, 400.0f) == 0) {
        _ACTWait(1);
    }

    buf1[0] = D_00622BC0[0];
    buf1[1] = D_00622BC0[1];
    RequestStageChangeDirect(D_00639EA8, 0x16, buf1, 0xB4);

    buf2[0] = D_00622BD0[0];
    buf2[1] = D_00622BD0[1];
    SetDirectRootPosition(D_00639EA8, buf2);

    ScpCallCameraSetTarget(-800.0f, -500.0f, D_006399AC);
}

void actSt06aBoxSub(volatile int a0)
{
    _ACTWait(0x3C);

    stage_SetAnimation(0x73, 1, 0);

    scpSearchGobj(0x6ED)->f16C = 0;

    while (stage_CheckAnimationFinish(0x73) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 7);

    D_0063C558 = 1;
    _ACTWait(0);
}
void actSt06aBox2Chk(volatile int a0)
{
    while (scpTriggerBall(a0, scpSearchGobj(0x6ED), 200.0f) == 0 ||
           gflagChk(0x6A) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x6C);
    scpSearchGobj(0x6ED)->f16C = 0;
}
void actSt06aBox3Chk(volatile int a0)
{
    while (scpTriggerBall(a0, scpSearchGobj(0x6ED), 200.0f) == 0 ||
           gflagChk(0x6A) != 0) {
        _ACTWait(1);
    }
}
void actSt06aBallDeleteChk(volatile int a0)
{
    while (scpTriggerBall(a0, scpSearchGobj(0x6EA), 200.0f) == 0 ||
           gflagChk(0x6A) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x6EA)->f16C = 0;
}
extern void actSt06aBoxEvent2OutChk(volatile int a0);
extern ActMail D_004F9B30[];

void actSt06aBoxEvent2InChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(scpSearchGobj(0x6ED), 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x6E);

    D_004F9B30[0].func = actSt06aBoxEvent2OutChk;
    sub->mail = D_004F9B30;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void actSt06aBoxEvent2InChk(volatile int a0);
extern ActMail D_004F9B50[];

void actSt06aBoxEvent2OutChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(scpSearchGobj(0x6ED), 0x2000000) != 0) {
        _ACTWait(1);
    }

    gflagOff(0x6E);

    D_004F9B50[0].func = actSt06aBoxEvent2InChk;
    sub->mail = D_004F9B50;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern int scpCheckExistAliveEnemy(void);
extern void actSt06aWayOffChk(volatile int a0);
extern ActMail D_004F9B90[];

void actSt06aWayOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpCheckExistAliveEnemy() != 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x16, 1);

    D_004F9B90[0].func = actSt06aWayOffChk;
    sub->mail = D_004F9B90;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void actSt06aWayOnChk(volatile int a0);
extern ActMail D_004F9BB0[];

void actSt06aWayOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpCheckExistAliveEnemy() == 0 &&
           scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x16, 0);

    D_004F9BB0[0].func = actSt06aWayOnChk;
    sub->mail = D_004F9BB0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern int scpIsRotObjectZPlusDirInclude(int a0, int a1, int a2);
extern void actSt06aWallWayOffChk(volatile int a0);
extern ActMail D_004F9C10[];

void actSt06aWallWayOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpIsRotObjectZPlusDirInclude(0x6EF, 0xF0, 0x12C) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x17, 1);
    SetWayGroupActive(0x18, 1);
    gflagOn(0x6F);

    D_004F9C10[0].func = actSt06aWallWayOffChk;
    sub->mail = D_004F9C10;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aWallWayOffChk);
extern void actSt06aWallWay2OffChk(volatile int a0);
extern ActMail D_004F9C90[];

void actSt06aWallWay2OnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpIsRotObjectZPlusDirInclude(0x6EF, 0x3C, 0x78) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x17, 1);
    SetWayGroupActive(0x18, 1);
    gflagOn(0x70);

    D_004F9C90[0].func = actSt06aWallWay2OffChk;
    sub->mail = D_004F9C90;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void actSt06aWallWay2OnChk(volatile int a0);
extern ActMail D_004F9CB0[];

void actSt06aWallWay2OffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpIsRotObjectZPlusDirInclude(0x6EF, 0x3C, 0x78) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x17, 0);
    SetWayGroupActive(0x18, 0);
    gflagOff(0x70);

    D_004F9CB0[0].func = actSt06aWallWay2OnChk;
    sub->mail = D_004F9CB0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern int ForMotionViewer_GetCurrentMotion(void *a0);
extern void ReviveAllCarryableItems(void);

void actSt06aTreeChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 150.0f) == 0 ||
           (ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x2F &&
            ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x30 &&
            ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x31 &&
            ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x3E)) {
        _ACTWait(1);
    }

    scpSearchGobj(0x6EA)->f16C = 1;
    ReviveAllCarryableItems();
}
extern void actSt06aKyomiOffChk(volatile int a0);
extern ActMail D_004F9D50[];

void actSt06aKyomiOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x5000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x6E6)->f16C = 1;
    scpSearchGobj(0x6E7)->f16C = 1;
    scpSearchGobj(0x6E8)->f16C = 1;
    scpSearchGobj(0x6E9)->f16C = 1;

    D_004F9D50[0].func = actSt06aKyomiOffChk;
    sub->mail = D_004F9D50;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void actSt06aKyomiOnChk(volatile int a0);
extern ActMail D_004F9D70[];

void actSt06aKyomiOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x5000000) != 0 &&
           scpTriggerFloorAttr(D_00639EA8, 0x5000000) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x6E6)->f16C = 0;
    scpSearchGobj(0x6E7)->f16C = 0;
    scpSearchGobj(0x6E8)->f16C = 0;
    scpSearchGobj(0x6E9)->f16C = 0;

    D_004F9D70[0].func = actSt06aKyomiOnChk;
    sub->mail = D_004F9D70;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern ActMail D_004F9D90[];

void actSt06aJumpMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = D_004F9D90;

    while (1) {
        _ACTWait(1);
    }
}
extern ActMail D_004F9DD0[];
extern void actSt06aJumpMove(volatile int a0);

void actSt06aJumpSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004F9DD0[0].func = actSt06aJumpMove;
    sub->mail = D_004F9DD0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void SetCameraFlag_LwsCutBack(void);

void actSt06aJumpSub(volatile int a0)
{
    stage_SetAnimation(0x72, 1, 0);

    while (stage_CheckAnimationFrame(0x72, 0x3C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetLoopFlag(0x71, 1);
    stage_SetAnimation(0x71, 1, 0);
    gflagOn(0x74);
    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(0x72) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C558 = 1;
    _ACTWait(1);
}
INCLUDE_ASM("asm/nonmatchings/src/st06a", actSt06aPistonRideOnChk);
extern void iosOmSendMail(void *a0, int a1, void *a2);
extern char D_00622BE0[];
extern void actSt06aPistonRideOnChk(volatile int a0);
extern ActMail D_004F9E30[];

void actSt06aPistonRideOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x6000000) != 0) {
        if (gflagChk(0x75) != 0) {
            debug_StdPrintfDummy(D_00622BE0);
            iosOmSendMail(D_00639EA4, 7, D_00639EA4);
        }
        _ACTWait(1);
    }

    D_004F9E30[0].func = actSt06aPistonRideOnChk;
    sub->mail = D_004F9E30;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern char D_00622C20[];
extern ActMail D_004F9EA0[];

void actSt06aPistonFlagOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (stage_CheckAnimationFrame(0x71, 0x7D, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(0x75);
    debug_StdPrintfDummy(D_00622C20);

    while (stage_CheckAnimationFrame(0x71, 0xC7, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004F9EA0[0].func = actSt06aPistonFlagOnChk;
    sub->mail = D_004F9EA0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern float D_004F9EE0[];

void actSt06aSoundChk(volatile int a0)
{
    int handle = soundSeDefPlay(0x54E, 0, D_004F9EE0, 1);

    while (gflagChk(0x6A) == 0) {
        _ACTWait(1);
    }

    soundSeDefStop(handle);
}
extern char D_00622C38[];
extern float D_004F9F10[];

void actSt06aSound2Chk(volatile int a0)
{
    int handle;

    while (gflagChk(0x74) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00622C38);

    handle = soundSeDefPlay(0x550, 0, D_004F9F10, 1);

    while (gflagChk(0x6A) == 0) {
        _ACTWait(1);
    }

    soundSeDefStop(handle);
}
