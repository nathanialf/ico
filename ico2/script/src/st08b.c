#include "common.h"

typedef struct ActMail {
    int mail;          /* 0x00 */
    void (*func)(int); /* 0x04 */
    int unk08;         /* 0x08 */
    int unk0C;         /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD0];  /* 0x00 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} Act;

extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004FA210[];
extern int gflagChk(int a0);
extern ActMail D_004FA2D0[];
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern int D_00639EA8;
extern int D_0063AA08;
extern int D_004FA1F0[];
extern void scpPlayEnd(int a0);
extern void scpPlayStart(int a0);
extern void scpPlayMot(int a0, int mot);
extern void scpPlayWaitMotEnd(int a0);
extern long long D_00622D80[];
extern long long D_00622D90[];
extern void scpEffectStart(int *buf, int a1);
extern int scpTriggerFloorAttr(int a0, int a1);
extern void gflagOn(int a0);
extern int scpTriggerBall(int a0, int a1, float radius);
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern int actCreateSubThread(void *entry, int prio);
extern void lt_switch_layout(int a0);
extern void scpAdpcmPlayRequestFunc(int a0, int *h, int a2, int a3, int a4);
extern int scpAdpcmPlayRequestNum(void);
extern void scpAdpcmFadeCloseFunc(int *h, int a1);
extern void iosThreadSetPri(int th, int pri);
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern void scpFadeIn(float a0);
extern void HotInitCageGeo(void *g);
extern void SetDirectRootPosition(int obj, void *pos);
extern void GetRootPosition(void *dst, int obj);

typedef union Pos {
    long long ll[2];
    float f[4];
} Pos;

typedef struct PadState {
    int unk00;        /* 0x00 */
    int flags;        /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} PadState;

extern PadState D_0028F8F0[];
extern long long D_00622D50[];
extern long long D_00622D60[];
extern ActMail D_004FA230[];
void actSt08bKurenLeft(volatile int a0);
void actSt08bKurenRight(volatile int a0);
extern void scpWakeupItemWithBoundary(float a0, float a1, float a2, float a3);
extern int D_00639EA4;
extern long long D_00622D70[];
/* The door-boundary X/Z corners live in the -G8 gp float pool and are written
   by the stage's layout/script side, so their loads may not sink into the jal
   delay slot; ROM has a nop at both call sites. */
extern ActMail D_004FA250[];
extern ActMail D_004FA270[];
extern ActMail D_004FA290[];
void actSt08bDoorUpChk(volatile int a0);
void actSt08bDoorDownChk(volatile int a0);

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    int act;           /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObj;

extern PObjGObj *scpSearchGobj(int a0);
extern void ReviveAllCarryableItemsWithNonSleepFrame(int a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int iosPadActRequest(int a0, int a1);
extern int D_00639EAC;
extern int D_0063C56C;
/* prototypes: their order is the inline tail's emission order */
void actSt08bKuren(volatile int a0);
void actSt08bEne(volatile int a0);
void actSt08bEnemy1(volatile int a0);
void actSt08bEnemy2(volatile int a0);
void actSt08bKurenMain(volatile int a0);
void actSt08aGirlYoro(volatile int a0);
void actSt08bDoorEvent(int x);
void actSt08bDoorUpEffect(volatile int a0);
void actSt08bDoorDownEffect(volatile int a0);
void actSt08bEneChk(volatile int a0);

inline void actSt08bKuren(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004FA210[0].func = actSt08bKurenMain;
    self->mail = D_004FA210;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

inline void actSt08bKurenMain(volatile int a0)
{
    int sub = *(int *)(a0 + 0x164);

    D_0063AA08 = 0;
    if (D_00639EA8 != 0) {
        scpPlayEnd(D_00639EA8);
    }
    *(int *)(sub + 0xD0) = (int)D_004FA1F0;
    while (1) {
        _ACTWait(1);
    }
}

void actSt08bKurenSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    Pos p1;
    Pos p2;
    int h;
    int th = 0;
    int thread;
    int frame;

    D_0063AA08 = 1;
    sub->mainMail = 0;

    if (D_00639EA8 != 0) {
        if (scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
            th = actCreateSubThread(actSt08aGirlYoro, 0x15);
        }
    }

    lt_switch_layout(0x37);

    if (gflagChk(0x50) != 0) {
        scpAdpcmPlayRequestFunc(0x3A, &h, 1, 1, 1);
        while (h == 0) {
            _ACTWait(1);
        }
        thread = actCreateSubThread(actSt08bKurenRight, 0x15);
        frame = 0x3FC;
    } else {
        scpAdpcmPlayRequestFunc(0x39, &h, 1, 1, 1);
        while (h == 0) {
            _ACTWait(1);
        }
        thread = actCreateSubThread(actSt08bKurenLeft, 0x15);
        frame = 0x1FE;
    }

    _ACTWait(3);

    D_0063C56C = 0;
    while (D_0063C56C == 0 &&
           ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(thread + 0x24, 0x22);
    if (th != 0) {
        iosThreadSetPri(th + 0x24, 0x22);
    }

    if (D_0063C56C == 0) {
        scpAdpcmFadeCloseFunc(&h, 0x80);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        stage_SetAnimation(0x172, 1, frame - 0x3C);
        _ACTWait(1);
        HotInitCageGeo(scpSearchGobj(0x16D));
        HotInitCageGeo(scpSearchGobj(0x16C));
        _ACTWait(1);
        if (th != 0) {
            scpPlayMot(D_00639EA8, 0x214);
            if (gflagChk(0x50) != 0) {
                p1.ll[0] = D_00622D50[0];
                p1.ll[1] = D_00622D50[1];
                SetDirectRootPosition(D_00639EA8, &p1);
            } else {
                p2.ll[0] = D_00622D60[0];
                p2.ll[1] = D_00622D60[1];
                p2.f[1] += *(float *)(*(int *)(*(int *)(D_00639EA8 + 0x15C) + 0x8C) + 0x14);
                SetDirectRootPosition(D_00639EA8, &p2);
            }
        }
        scpFadeIn(3.0f);
    }

    if (D_00639EA8 != 0) {
        GetRootPosition(&p1, D_00639EA8);
        *(float *)(*(int *)(D_00639EA8 + 0x15C) + 0x254) = p1.f[1];
    }

    while (stage_CheckAnimationFrame(0x172, frame, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);

    if (gflagChk(0x50) != 0) {
        scpSearchGobj(0x16D)->f16C = 1;
        scpSearchGobj(0x16C)->f16C = 0;
        _ACTWait(1);
        gflagOff(0x50);
    } else {
        gflagOn(0x50);
    }

    D_004FA230[0].func = actSt08bKurenMain;
    sub->mail = D_004FA230;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt08bKurenLeft(volatile int a0)
{
    ReviveAllCarryableItemsWithNonSleepFrame(0x12C);

    stage_SetAnimation(0x172, 1, 0);

    scpSearchGobj(0x16D)->f16C = 0;
    scpSearchGobj(0x16C)->f16C = 1;

    while (stage_CheckAnimationFrame(0x172, 0x5, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFrame(0x172, 0xD7, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x172, 0x1D1, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    D_0063C56C = 1;
    _ACTWait(0);
}

void actSt08bKurenRight(volatile int a0)
{
    ReviveAllCarryableItemsWithNonSleepFrame(0x12C);

    stage_SetAnimation(0x172, 1, 0x1FF);

    while (stage_CheckAnimationFrame(0x172, 0x2DC, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x172, 0x336, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x172, 0x3E3, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    D_0063C56C = 1;
    _ACTWait(0);
}

inline void actSt08aGirlYoro(volatile int a0)
{
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x222);
    scpPlayWaitMotEnd(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x253);
    scpPlayWaitMotEnd(D_00639EA8);
    _ACTWait(0);
}

inline void actSt08bDoorEvent(int x)
{
    volatile int local = x;
}

void actSt08bDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(0x174, 0, 0);
        _ACTWait(0x3C);
        D_004FA250[0].func = actSt08bDoorDownChk;
        self->mail = D_004FA250;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x173, 0, 0);
        D_004FA270[0].func = actSt08bDoorUpChk;
        self->mail = D_004FA270;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt08bDoorUpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x4000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt08bDoorUpEffect, 0x15);

    scpWakeupItemWithBoundary(-1189.0f, -2326.0f, -408.0f, 100.0f);

    stage_SetAnimation(0x173, 1, 0);

    buf[0] = D_00622D70[0];
    buf[1] = D_00622D70[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x173) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004FA290[0].func = actSt08bDoorDownChk;
    sub->mail = D_004FA290;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

inline void actSt08bDoorUpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_00622D80[0];
    long long v0b = D_00622D90[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622D80[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622D90[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

inline void actSt08bDoorDownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_00622D90[0];
    long long v0b = D_00622D80[0];
    int i;
    for (i = 0; i < 0x32; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622D90[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622D80[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

/* TU-owned mail record: role-named file static per the 2026-09-07 ruling,
   same shape as st17a's door_mes / st18a's switch_l_mes. */
static ActMail door_down_mes[2] = {{0x1AE}, {0x1AD}};

void actSt08bDoorDownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x4000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);

    actCreateSubThread(actSt08bDoorDownEffect, 0x15);

    scpWakeupItemWithBoundary(-1189.0f, -2326.0f, -408.0f, 100.0f);

    stage_SetAnimation(0x174, 1, 0);

    buf[0] = D_00622D70[0];
    buf[1] = D_00622D70[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x174) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_down_mes[0].func = actSt08bDoorUpChk;
    sub->mail = door_down_mes;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

inline void actSt08bEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x51) == 0) {
        D_004FA2D0[0].func = actSt08bEneChk;
        self->mail = D_004FA2D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

inline void actSt08bEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(0x51);
    gflagOn(0x52);
}

inline void actSt08bEnemy1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x52) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

inline void actSt08bEnemy2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x52) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
