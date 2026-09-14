#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD4]; /* 0x00 */
    ActMail *mail;    /* 0xD4 */
} Act;

extern char *D_00639EA8;
extern void gflagOn(int a0);

void actSt18aEnd(void)
{
    if (D_00639EA8 != 0) {
        if (gflagChk(0x3D) == 0) {
            gflagOn(0x187);
        }
    }
}

/* the shared pad-state array (op.c's PadState): 0x58 per pad, trg at 0x4 */
typedef struct PadState {
    int unk00;        /* 0x00 */
    int trg;          /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} PadState;

extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int a1, float radius);
extern void lt_switch_layout(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int scpAdpcmPlayRequestNum(void);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern void SetCameraFlag_LwsCutBack(void);
extern void scpFadeIn(float f);
extern PadState D_0028F8F0[];
extern int D_00639EA4;
extern int D_0063AA08;

void actSt18aIntroChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 1000.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);

    gflagOn(0x37);

    D_0063AA08 = 1;

    _ACTWait(1);

    stage_SetAnimation(0x162, 1, 0);

    while (stage_CheckAnimationFinish(0x162) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(0x162, 1, -1);
            SetCameraFlag_LwsCutBack();
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    int act;           /* 0x164 */
} PObjGObj;

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int scpSearchGobj(int a0);
extern int scpTriggerFloorAttr(int a0, int a1);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFrame(int anim, int frame, int a2);
extern int soundSeDefPlay(int se, int a1, int a2, int a3);
extern void FinishHint(int a0);
extern void actSt18aSwitchLUpChk(volatile int a0);
extern int D_0028F4C0[];
extern int D_00639EA4;
extern ActMail D_004FB0D0[];

void actSt18aSwitchLChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    int i;

    i = 0;
    while (i < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) {
        if (scpTriggerFloorAttr(scpSearchGobj(0x305), 0x1000000) != 0 ||
            scpTriggerFloorAttr(scpSearchGobj(0x306), 0x1000000) != 0 ||
            scpTriggerFloorAttr(D_00639EA4, 0x1000000) != 0 ||
            (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x1000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(0x79, 1, 0);

    soundSeDefPlay(0x4C4, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x79, 0x2D, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerFloorAttr(scpSearchGobj(0x305), 0x1000000) != 0 ||
        scpTriggerFloorAttr(scpSearchGobj(0x306), 0x1000000) != 0 ||
        scpTriggerFloorAttr(D_00639EA4, 0x1000000) != 0 ||
        (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x1000000) != 0)) {
        gflagOn(0x3A);
        FinishHint(7);
    }

    D_004FB0D0[0].func = actSt18aSwitchLUpChk;
    sub->mail = D_004FB0D0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFrame(int anim, int frame, int a2);
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
extern int soundSeDefPlay(int se, int a1, int a2, int a3);
extern void scpWakeupItemWithBoundary(float x, float y, float z, float r);
extern void actSt18aSwitchLChk(volatile int a0);

/* TU-owned .data record (VMA 0x004FB0F0..0x004FB10F, ROM 0x3FB0F0). */
static ActMail switch_l_mes[2] = {{0x1AE}, {0x1AD}};

void actSt18aSwitchLUpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(0xF);
    gflagOff(0x3A);

    stage_SetAnimation(0x79, 1, 0x2E);
    soundSeDefPlay(0x4C4, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x79, 0x32, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupItemWithBoundary(3054.0f, 1530.0f, -3061.0f, 100.0f);

    while (stage_CheckAnimationFrame(0x79, 0x5A, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switch_l_mes[0].func = actSt18aSwitchLChk;
    sub->mail = switch_l_mes;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int scpSearchGobj(int a0);
extern int scpTriggerFloorAttr(int a0, int a1);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFrame(int anim, int frame, int a2);
extern int soundSeDefPlay(int se, int a1, int a2, int a3);
extern void FinishHint(int a0);
extern void actSt18aSwitchRUpChk(volatile int a0);
extern int D_0028F4C0[];
extern int D_00639EA4;
extern ActMail D_004FB150[];

void actSt18aSwitchRChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    int i;

    i = 0;
    while (i < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) {
        if (scpTriggerFloorAttr(scpSearchGobj(0x305), 0x2000000) != 0 ||
            scpTriggerFloorAttr(scpSearchGobj(0x306), 0x2000000) != 0 ||
            scpTriggerFloorAttr(D_00639EA4, 0x2000000) != 0 ||
            (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(0x7A, 1, 0);

    soundSeDefPlay(0x4C4, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x7A, 0x2D, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerFloorAttr(scpSearchGobj(0x305), 0x2000000) != 0 ||
        scpTriggerFloorAttr(scpSearchGobj(0x306), 0x2000000) != 0 ||
        scpTriggerFloorAttr(D_00639EA4, 0x2000000) != 0 ||
        (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0)) {
        gflagOn(0x3B);
        FinishHint(7);
    }

    D_004FB150[0].func = actSt18aSwitchRUpChk;
    sub->mail = D_004FB150;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFrame(int anim, int frame, int a2);
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
extern int soundSeDefPlay(int se, int a1, int a2, int a3);
extern void scpWakeupItemWithBoundary(float x, float y, float z, float r);
extern void actSt18aSwitchRChk(volatile int a0);
extern ActMail D_004FB170[];

void actSt18aSwitchRUpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttrTargetMan(a0, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(0xF);
    gflagOff(0x3B);

    stage_SetAnimation(0x7A, 1, 0x2E);
    soundSeDefPlay(0x4C4, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x7A, 0x32, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupItemWithBoundary(1451.0f, 1530.0f, -3039.0f, 100.0f);

    while (stage_CheckAnimationFrame(0x7A, 0x5A, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004FB170[0].func = actSt18aSwitchRChk;
    sub->mail = D_004FB170;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern int actCreateSubThread(void *entry, int prio);
extern void iosThreadSetPri(int th, int pri);
extern int scpAdpcmPlayRequestNum(void);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern void scpFadeIn(float f);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int soundSeDefPlay(int se, int a1, int a2, int a3);
extern void actSt18aDoorChkSub(volatile int a0);
extern void actSt18aDoorDownChk(volatile int a0);
extern PadState D_0028F8F0[];
extern int D_0063AA08;
extern int D_0063C59C;
extern int D_0063C5A0;
extern ActMail D_004FB1D0[];

void actSt18aDoorChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    int th;

    while (gflagChk(0x3A) == 0 || gflagChk(0x3B) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    gflagOn(0x3C);

    th = actCreateSubThread(actSt18aDoorChkSub, 0x15);
    D_0063C59C = 0;
    D_0063C5A0 = 0;

    while (D_0063C59C == 0 && ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C59C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x7B, 0, -1);

        if (D_0063C5A0 == 0) {
            soundSeDefPlay(0x4C6, 0, 0, 1);
        }

        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    lt_switch_layout(0x36);

    D_004FB1D0[0].func = actSt18aDoorDownChk;
    sub->mail = D_004FB1D0;
    D_0063AA08 = 0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int soundSeDefPlay(int se, int a1, int a2, int a3);
extern void actSt18aDoorChk(volatile int a0);

/* TU-owned .data record (VMA 0x004FB1F0..0x004FB20F, ROM 0x3FB1F0): the mail
   table actSt18aDoorDownChk hands back to the door actor. Role-named file
   static per the 2026-09-07 ruling, same shape as st17a's door_mes. */
static ActMail door_mes[2] = {{0x1AE}, {0x1AD}};

void actSt18aDoorDownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (gflagChk(0x3A) != 0 && gflagChk(0x3B) != 0) {
        _ACTWait(1);
    }

    _ACTWait(0xF);
    gflagOff(0x3C);

    stage_SetAnimation(0x7C, 1, 0);

    soundSeDefPlay(0x4C5, 0, 0, 1);
    _ACTWait(0x32);
    soundSeDefPlay(0x4C6, 0, 0, 1);
    while (stage_CheckAnimationFinish(0x7C) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_mes[0].func = actSt18aDoorChk;
    sub->mail = door_mes;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern Act *actInitialize(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern int scpSearchGobj(int a0);

void actSt18aEnemy1_1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask(scpSearchGobj(0x2FD));
    Generator_Mask(scpSearchGobj(0x2FE));

    while (gflagChk(0x3E) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    Generator_Call(scpSearchGobj(0x2FD));
    Generator_Call(scpSearchGobj(0x2FE));
}

extern void _ACTWait(int a0);
extern Act *actInitialize(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern int scpSearchGobj(int a0);

void actSt18aEnemy2_1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask(scpSearchGobj(0x2FE));

    while (gflagChk(0x40) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_Call(scpSearchGobj(0x2FE));
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void actSt18aIntroChk(volatile int a0);
extern ActMail D_004FB070[];

void actSt18aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x37) == 0) {
        D_004FB070[0].func = actSt18aIntroChk;
        self->mail = D_004FB070;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void actSt18aDoorChk(volatile int a0);
extern void actSt18aDoorDownChk(volatile int a0);
extern ActMail D_004FB190[];
extern ActMail D_004FB1B0[];

void actSt18aDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x3C) == 0) {
        stage_SetAnimation(0x7B, 0, 0);

        D_004FB190[0].func = actSt18aDoorChk;
        self->mail = D_004FB190;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x7B, 0, -1);

        D_004FB1B0[0].func = actSt18aDoorDownChk;
        self->mail = D_004FB1B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void actSt18aSwitchLChk(volatile int a0);
extern void actSt18aSwitchLUpChk(volatile int a0);
extern ActMail D_004FB090[];
extern ActMail D_004FB0B0[];

void actSt18aSwitchL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x3A) == 0) {
        stage_SetAnimation(0x79, 0, 0);

        D_004FB090[0].func = actSt18aSwitchLChk;
        self->mail = D_004FB090;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x79, 0, 0x2D);

        D_004FB0B0[0].func = actSt18aSwitchLUpChk;
        self->mail = D_004FB0B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void actSt18aSwitchRChk(volatile int a0);
extern void actSt18aSwitchRUpChk(volatile int a0);
extern ActMail D_004FB110[];
extern ActMail D_004FB130[];

void actSt18aSwitchR(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x3B) == 0) {
        stage_SetAnimation(0x7A, 0, 0);

        D_004FB110[0].func = actSt18aSwitchRChk;
        self->mail = D_004FB110;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x7A, 0, 0x2D);

        D_004FB130[0].func = actSt18aSwitchRUpChk;
        self->mail = D_004FB130;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void actSt18aEneChk(volatile int a0);
extern ActMail D_004FB210[];

void actSt18aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x3D) == 0) {
        D_004FB210[0].func = actSt18aEneChk;
        self->mail = D_004FB210;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern Act *actInitialize(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt18aEnemy1_2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x3E) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern void actSt18aEne2Chk(volatile int a0);
extern ActMail D_004FB230[];

void actSt18aEne2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x3F) == 0) {
        D_004FB230[0].func = actSt18aEne2Chk;
        self->mail = D_004FB230;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern Act *actInitialize(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt18aEnemy2_2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x40) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt18aCamera(int x)
{
    volatile int local = x;
}

extern void _ACTWait(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int scpTriggerFloorAttr(int a0, int a1);
extern void SetCameraFlag_LwsCutBack(void);
extern int soundSeDefPlay(int se, int a1, int a2, int a3);
extern int D_00639EA4;
extern int D_0063C59C;
extern int D_0063C5A0;

void actSt18aDoorChkSub(volatile int a0)
{
    _ACTWait(60);

    stage_SetAnimation(123, 1, 0);

    if (scpTriggerFloorAttr(D_00639EA4, 0x5000000) != 0) {
        SetCameraFlag_LwsCutBack();
    }

    soundSeDefPlay(0x4C5, 0, 0, 1);
    _ACTWait(50);
    D_0063C5A0 = 1;
    soundSeDefPlay(0x4C6, 0, 0, 1);
    while (stage_CheckAnimationFinish(123) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C59C = 1;
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern int scpTriggerFloorAttr(int a0, int a1);

void actSt18aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOff(0x187);
    gflagOn(0x3D);
    gflagOn(0x3E);
}

extern void _ACTWait(int a0);
extern int scpTriggerFloorAttr(int a0, int a1);
extern int scpSearchGobj(int a0);
extern void FinishHint(int a0);

void actSt18aEne2Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (D_00639EA8 == 0 || scpTriggerFloorAttr(scpSearchGobj(0x306), 0x4000000) == 0) {
        _ACTWait(1);
    }
    FinishHint(8);
    _ACTWait(300);
    gflagOn(0x3F);
    gflagOn(0x40);
}
