#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

typedef union ActStatus {
    unsigned long long ll;
    int i[2];
} ActStatus;

typedef struct Act {
    char unk00[0x20];  /* 0x00 */
    ActStatus flags20; /* 0x20 */
    char unk28[0xA8];  /* 0x28 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} Act;

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    int act;           /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObj;

extern void lt_switch_layout(int a0);
extern void gflagOn(int a0);
extern int gflagChk(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int D_00639EA4;
extern int D_00639EA8;
extern int D_0063AA08;
extern int enable_game_pause;
extern int D_0028F4C0[];
extern void stgmgrNextStagePreLoadForceStageSet(int val);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);

void actE3WarningChk(volatile int a0)
{
    int x = a0;
    int i;

    actInitialize(a0);
    _ACTWait(1);

    stgmgrNextStagePreLoadForceStageSet(0x5F);

    i = 0;
    while (i++ < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 5) {
        _ACTWait(1);
    }

    scpFadeOut(6.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    _ACTWait((int)(float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]));

    RequestStageChange(1, D_00639EA4, 0, 255.0f, 0.0f);
}

extern void gflagOff(int a0);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern void scpFadeIn(float t);
extern void actE3TitleChk(volatile int a0);
extern ActMail D_004F79D0[];
extern int D_0063B4D0;
extern int D_0063BDF4;

void actE3Title(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    enable_game_pause = 0;
    D_0063AA08 = 1;

    gflagOff(0x164);

    D_0063BDF4 = 0;
    scpAdpcmPlayRequestFunc(5, &D_0063BDF4, 0, 1, 0);

    while (D_0063B4D0 == 0) {
        _ACTWait(1);
    }

    D_0028F4C0[0xB] = 7;

    scpFadeOut(255.0f, 0, 0, 0);

    while (D_0063BDF4 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    if (D_00639EA4 != 0) {
        scpPlayMot(D_00639EA4, 0);
    }

    stage_SetAnimation(0x20, 0, 0);
    stage_SetAnimation(0x1A, 0, -1);
    stage_SetAnimation(0x23, 0, 0);
    stage_SetAnimation(0x21, 0, 0);
    stage_SetAnimation(0x24, 0, 0);
    stage_SetAnimation(0x26, 0, 0);
    stage_SetAnimation(0x2B, 0, 0);

    D_004F79D0[0].func = actE3TitleChk;
    sub->mail = D_004F79D0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

typedef struct PadState {
    int unk00; /* 0x00 */
    int flags; /* 0x04 */
} PadState;

extern PadState D_0028F8F0[];
extern char D_006224F0[];
extern int D_0063BDF4;
extern void gflagOn(int a0);
extern int actCreateSubThread(void *entry, int prio);
extern void actE3TitleFrameChk(volatile int a0);
extern void debug_StdPrintfDummy();
extern void AdpcmPlay(int handle);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);

void actE3TitleChk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    actCreateSubThread(actE3TitleFrameChk, 0x15);

    while (gflagChk(0x164) != 0 || (D_0028F8F0[0].flags & 0x840) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x165);
    debug_StdPrintfDummy(D_006224F0);

    AdpcmPlay(*(int *)(D_0063BDF4 + 0x2C));

    scpFadeOut(4.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, D_00639EA4, 0, 255.0f, 16.0f);
}

extern int NonLinearCameraMove;
extern void stage_SetLoopFlag(int key, int a1);
extern int stage_ContinueAnimation(int a0, int a1);
extern void scpAdpcmCloseFunc(int *h);
extern void stgmgrForceSwitchWithFade(int a0, float a1, float a2);
extern char D_00622500[];
extern int D_0063B5F0;
extern int mpegPlayReturnStage;

void actE3TitleFrameChk(volatile int a0)
{
    int intro = 0x3AF;
    int loop = 0x3AA;
    int outro = 0x3B4;
    int i;

    stage_SetAnimation(0x3A7, 1, 0);

    switch (NonLinearCameraMove) {
    case 3:
        intro = 0x3B0;
        break;
    case 4:
        intro = 0x3B1;
        break;
    case 6:
        intro = 0x3B3;
        break;
    case 5:
        intro = 0x3B2;
        break;
    }
    stage_SetAnimation(intro, 1, 0);

    while (stage_ContinueAnimation(0x3A7, 0x3A8) == 0) {
        _ACTWait(1);
    }

    stage_SetLoopFlag(0x3A8, 1);

    switch (NonLinearCameraMove) {
    case 3:
        loop = 0x3AB;
        break;
    case 4:
        loop = 0x3AC;
        break;
    case 6:
        loop = 0x3AE;
        break;
    case 5:
        loop = 0x3AD;
        break;
    }
    stage_SetLoopFlag(loop, 1);
    stage_SetAnimation(loop, 1, 0);

    i = 0;
    while (i++ < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x2D) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x3A9, 1, 0);

    switch (NonLinearCameraMove) {
    case 3:
        outro = 0x3B5;
        break;
    case 4:
        outro = 0x3B6;
        break;
    case 6:
        outro = 0x3B8;
        break;
    case 5:
        outro = 0x3B7;
        break;
    }
    stage_SetAnimation(outro, 1, 0);

    while (stage_CheckAnimationFinish(0x3A9) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(0x165) == 0) {
        debug_StdPrintfDummy(D_00622500);

        gflagOn(0x164);

        if (D_0063BDF4 != 0) {
            scpAdpcmCloseFunc(&D_0063BDF4);
        }

        mpegPlayReturnStage = 0x5F;
        D_0063B5F0 = 0x5F;

        stgmgrForceSwitchWithFade(0x67, 4.0f, 4.0f);
    }
}

extern int NonLinearCameraMove;
extern void stage_SetLoopFlag(int key, int a1);

void actE3Inst1Chk(volatile int a0)
{
    int x = a0;
    int anim;
    int i;

    actInitialize(a0);
    _ACTWait(1);

    anim = 0x3C0;
    switch (NonLinearCameraMove) {
    case 3:
        anim = 0x3C1;
        break;
    case 4:
        anim = 0x3C2;
        break;
    case 6:
        anim = 0x3C4;
        break;
    case 5:
        anim = 0x3C3;
        break;
    }

    stage_SetLoopFlag(anim, 1);
    stage_SetAnimation(anim, 1, 0);

    i = 0;
    while (i++ < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0xA &&
           (D_0028F8F0[0].flags & 0x840) == 0) {
        _ACTWait(1);
    }

    soundSeDefPlay(0x56E, 0, 0, 1);

    scpFadeOut(3.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, D_00639EA4, 0, 255.0f, 16.0f);
}

extern void ScpCallCameraOff(void);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern void actE3CapsuleChk(volatile int a0);
extern ActMail D_004F7A10[];

void actE3Capsule(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (D_00639EA8 == 0) {
        ScpCallCameraOff();
    }

    if (gflagChk(0x166) == 0) {
        if (D_00639EA4 != 0) {
            scpPlayMot(D_00639EA4, 0);
        }

        scpFadeOut(255.0f, 0, 0, 0);

        lt_switch_layout(0x37);

        stage_SetAnimation(0x20, 0, 0);
        stage_SetAnimation(0x1A, 0, -1);
        stage_SetAnimation(0x23, 0, 0);
        stage_SetAnimation(0x21, 0, 0);
        stage_SetAnimation(0x24, 0, 0);
        stage_SetAnimation(0x26, 0, 0);

        D_004F7A10[0].func = actE3CapsuleChk;
        sub->mail = D_004F7A10;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x20, 0, -1);
        stage_SetAnimation(0x1A, 0, -1);
        stage_SetAnimation(0x23, 0, 0);
        stage_SetAnimation(0x21, 0, 0);
        stage_SetAnimation(0x24, 0, 0);
        stage_SetAnimation(0x26, 0, 0);
    }
}

extern void iosThreadSetPri(int th, int pri);
extern void scpAdpcmCloseFunc(int *h);
extern void scpFadeIn(float t);
extern void actE3CapsuleDemoEnd(volatile int a0);
extern int D_0063C4E0;
extern int D_0063C4E4;
extern int D_0063BDF8;

void actE3CapsuleDemoCancel(volatile int a0)
{
    while (D_0063C4E4 == 0 || (D_0028F8F0[0].flags & 0x800) == 0) {
        _ACTWait(1);
    }

    iosThreadSetPri(D_0063C4E0 + 0x24, 0x22);

    scpFadeOut(8.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmCloseFunc(&D_0063BDF8);

    stage_SetAnimation(0x20, 0, -1);
    stage_SetAnimation(0x1A, 0, -1);
    stage_SetAnimation(0x252, -1, -2);
    stage_SetAnimation(0x257, -1, -2);
    stage_SetAnimation(0x259, -1, -2);
    stage_SetAnimation(0x25A, -1, -2);
    stage_SetAnimation(0x25B, -1, -2);
    stage_SetAnimation(0x25C, -1, -2);
    stage_SetAnimation(0x25D, -1, -2);
    stage_SetAnimation(0x25E, -1, -2);
    stage_SetAnimation(0x270, 1, 0);

    scpFadeIn(6.0f);

    actCreateSubThread(actE3CapsuleDemoEnd, 0x15);
}

extern void scpPlayStart(int a0);
extern int stage_ContinueAnimation(int a0, int a1);

void actE3CapsuleDemo(volatile int a0)
{
    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);

    D_0063C4E4 = 1;
    actCreateSubThread(actE3CapsuleDemoCancel, 0x15);

    stage_SetAnimation(0x252, 1, 0);
    _ACTWait(0x5F);
    stage_SetAnimation(0x20, 1, 0);

    while (stage_ContinueAnimation(0x252, 0x257) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x120);

    while (stage_ContinueAnimation(0x257, 0x259) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x120);

    while (stage_ContinueAnimation(0x259, 0x25A) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x124);

    _ACTWait(1);

    stage_SetAnimation(0x20, 1, 0xD0);

    while (stage_ContinueAnimation(0x25A, 0x25B) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x125);

    while (stage_ContinueAnimation(0x25B, 0x25C) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x126);

    while (stage_ContinueAnimation(0x25C, 0x25D) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x127);

    while (stage_ContinueAnimation(0x25D, 0x25E) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x128);

    while (stage_ContinueAnimation(0x25E, 0x270) == 0) {
        _ACTWait(1);
    }

    D_0063C4E4 = 0;
    actCreateSubThread(actE3CapsuleDemoEnd, 0x15);
}

extern void SetWayGroupActive(int a0, int a1);

void actE3St13cInit(void)
{
    SetWayGroupActive(7, 0);

    if (gflagChk(0x168) != 0) {
        SetWayGroupActive(9, 0);
    }
}

extern void scpPlayPosSet(int a0, float x, float y, float z);
extern void actE3CageFallChk(volatile int a0);
extern ActMail D_004F7AE0[];

void actE3CageFall(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x168) == 0) {
        stage_SetAnimation(0x4C, 0, 0);
        stage_SetAnimation(0x48, 0, -1);

        if (D_00639EA8 == 0) {
            _ACTWait(0);
        }

        scpPlayPosSet(D_00639EA8, -30.0f, -436.0f, -1.0f);

        D_004F7AE0[0].func = actE3CageFallChk;
        sub->mail = D_004F7AE0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x4C, 0, 0);
        stage_SetAnimation(0x4A, 0, -1);
        stage_SetAnimation(0x4B, 0, -1);
    }
}

extern int scpTriggerBall(int a0, int gobj, float r);
extern void fightSoundProcessRequestPause(void);
extern int fightSoundPlayChk(void);
extern void AdpcmPlay(int handle);
extern int actCreateSubThread(void *entry, int prio);
extern void actE3CageFallDemo(volatile int a0);
extern void actE3CageFallEffect(volatile int a0);
extern void SetWayGroupActive(int a0, int a1);
extern PObjGObj *scpSearchGobj(int id);
extern int D_0063BDFC;

void actE3CageFallChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 160.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);

    D_0063AA08 = 1;

    ((Act *)scpSearchGobj(0xC9D)->act)->flags20.ll |= 0x20000;
    ((Act *)scpSearchGobj(0xC9E)->act)->flags20.ll |= 0x20000;

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    gflagOn(0x168);

    while (D_0063BDFC == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(D_0063BDFC + 0x2C));

    actCreateSubThread(actE3CageFallDemo, 0x15);

    stage_SetAnimation(0x4A, 1, 0);
    stage_SetAnimation(0x4B, 1, 0);

    actCreateSubThread(actE3CageFallEffect, 0x15);

    while (stage_CheckAnimationFinish(0x4A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(9, 0);
}

extern void SetHandCameraLimitInDemo(int a0, int a1);
extern void ResetHandCameraLimitInDemo(void);
extern void fightSoundProcessRequestStart(void);
extern void *test_CURRENTROOT(int a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void scpPlayMotDir(int a0, void *dir);
extern void scpPlayEnd(int a0);
extern void scpPlayStart(int a0);
extern int stage_CheckAnimationFrame(int anim, int frame, int a2);
extern int gamesysObjInfoPosSetStage(int w, int a1, int a2, int stage);
extern void CheckPoint(void);
extern int stage_no;

void actE3CageFallDemo(volatile int a0)
{
    float dir[4];

    lt_switch_layout(0x37);

    D_0063AA08 = 1;

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    stage_SetAnimation(0x276, 1, 0);

    scpPlayMot(D_00639EA4, 0x13B);

    while (stage_ContinueAnimation(0x276, 0x277) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(0, 0);

    while (stage_ContinueAnimation(0x277, 0x278) == 0) {
        _ACTWait(1);
    }

    ResetHandCameraLimitInDemo();

    scpPlayMot(D_00639EA8, 0x2D6);

    while (stage_ContinueAnimation(0x278, 0x279) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA8, 0x2D7);

    while (stage_ContinueAnimation(0x279, 0x27A) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x13C);

    while (stage_ContinueAnimation(0x27A, 0x27B) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x145);

    while (stage_ContinueAnimation(0x27B, 0x27C) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA8, 0x2D8);

    while (stage_ContinueAnimation(0x27C, 0x27D) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA8, 0x2D9);

    _ACTWait(0xF0);

    gflagOn(0x16C);

    fightSoundProcessRequestStart();

    while (stage_ContinueAnimation(0x27D, 0x3BB) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x143);

    while (stage_ContinueAnimation(0x3BB, 0x3BC) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA8, 0x146);

    while (stage_CheckAnimationFrame(0x3BC, 0x96, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA4, 0x144);

    while (stage_CheckAnimationFinish(0x3BC) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA4, 0);

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;

    lt_switch_layout(0x36);

    scpPlayMot(D_00639EA8, 0x214);
    {
        int self = D_00639EA8;

        *(int *)(*(int *)((char *)self + 0x15C) + 0x514) =
            (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 30.0f);

        scpPlayEnd(self);
    }

    gflagOn(0x17D);

    gamesysObjInfoPosSetStage(D_00639EA4, *(int *)(*(int *)(D_00639EA4 + 0x164) + 0x444), 0,
                              stage_no);

    CheckPoint();

    gflagOff(0x17D);
}

typedef struct EffectArg {
    long long lo; /* 0x00 */
    long long hi; /* 0x08 */
} EffectArg;

/* e3.o's own .rodata: the cage-fall effect templates, one per scpEffectStart. */
extern const EffectArg D_00622520;
extern const EffectArg D_00622530;
extern const EffectArg D_00622540;
extern const EffectArg D_00622550;
extern const EffectArg D_00622560;
extern const EffectArg D_00622570;
extern const EffectArg D_00622580;
extern const EffectArg D_00622590;
extern const EffectArg D_006225A0;
/* no prototype in the dev's TU: the C89 implicit-int return is what makes
   ee-gcc treat $v0 as clobbered at every call site. The definition in
   src/script.c is void. */
extern int scpEffectStart(void *a0, int a1);
extern int iosPadActRequest(int port, int id);
extern int D_00639EAC;

void actE3CageFallEffect(volatile int a0)
{
    EffectArg b1;
    EffectArg b2;
    EffectArg b3;
    EffectArg b4;
    EffectArg b5;
    EffectArg b6;
    EffectArg b7;
    EffectArg b8;
    EffectArg b9;
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 0:
            gflagOn(0x16);
            break;
        case 0x40:
            iosPadActRequest(D_00639EAC, 0x11);
            b1 = D_00622520;
            scpEffectStart(&b1, 0);
            b2 = D_00622530;
            scpEffectStart(&b2, 0);
            break;
        case 0x44:
            b3 = D_00622540;
            scpEffectStart(&b3, 0);
            b4 = D_00622550;
            scpEffectStart(&b4, 0);
            break;
        case 0x60:
            b5 = D_00622560;
            scpEffectStart(&b5, 0);
            b6 = D_00622570;
            scpEffectStart(&b6, 0);
            b7 = D_00622580;
            scpEffectStart(&b7, 0);
            break;
        case 0xB4:
            iosPadActRequest(D_00639EAC, 0xF);
            break;
        case 0x12C:
            b8 = D_00622590;
            scpEffectStart(&b8, 0);
            b9 = D_006225A0;
            scpEffectStart(&b9, 0);
            break;
        case 0x17C:
            iosPadActRequest(D_00639EAC, 0x10);
            break;
        }

        n = (int)t;
        tn = t + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 400.0f);
}

extern void ScpCallCameraSetTarget(float x, float y, float z);
extern void actE3St09aSekizoChk(volatile int a0);
/* e3.o's own .data run (no MAIN.MAP symbol): the sekizou's SE position. */
extern float D_004F7B20[];
extern ActMail D_004F7B30[];

void actE3St09aSekizo(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    soundSeDefPlay(0x542, 0, D_004F7B20, 1);
    soundSeDefPlay(0x543, 0, D_004F7B20, 1);
    soundSeDefPlay(0x544, 0, D_004F7B20, 1);

    if (gflagChk(0x16E) == 0) {
        stage_SetAnimation(0x178, 0, 0);

        D_004F7B30[0].func = actE3St09aSekizoChk;
        sub->mail = D_004F7B30;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        ScpCallCameraSetTarget(1421.0f, 97.0f, -1885.0f);
        stage_SetAnimation(0x178, 0, -1);
    }
}

extern int ForMotionViewer_GetCurrentMotion(int a0);
extern void scpSekizouCheckPoint(void);
extern void scpKillEnemyAll(void);
extern void scpMaskGeneratorAll(void);
extern void brainLockGirl(void);
extern int iosPadActRequest(int port, int id);
extern int *iosPadActVolumeSet(int key, unsigned int val);
extern void iosPadActStop(int a0);
extern void *test_CURRENTROOT(int a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void scpPlayMotDir(int a0, void *dir);
extern void scpPlayWaitMotEnd(int a0);
extern void scpPlayEnd(int a0);
extern int stage_CheckAnimationFrame(int anim, int frame, int a2);
extern void actE3St09aGirlWay(volatile int a0);
extern int D_00639EAC;
extern int D_0063BE08;
extern unsigned char D_0063BE0C;

void actE3St09aSekizoChk(volatile int a0)
{
    float dir[4];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 ||
           scpTriggerBall(a0, D_00639EA8, 200.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x4B) {
        _ACTWait(1);
    }

    scpSekizouCheckPoint();

    scpAdpcmPlayRequestFunc(0x12, 0, 1, 1, 1);

    scpKillEnemyAll();
    scpMaskGeneratorAll();

    lt_switch_layout(0x37);

    D_0063AA08 = 1;
    brainLockGirl();

    gflagOn(0x16E);

    _ACTWait(0x3C);

    stage_SetAnimation(0x178, 1, 0);

    D_0063BE08 = iosPadActRequest(D_00639EAC, 9);
    D_0063BE0C = 0x80;
    iosPadActVolumeSet(D_0063BE08, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpPlayPosSet(D_00639EA8, -1410.0f, -100.0f, 1515.0f);
    scpPlayPosSet(D_00639EA4, -1330.0f, -100.0f, 1515.0f);

    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    D_0063AA08 = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpPlayMot(D_00639EA8, 0x285);
    scpPlayWaitMotEnd(D_00639EA8);

    while (stage_CheckAnimationFrame(0x178, 0x97, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(D_0063BE08);

    scpPlayMot(D_00639EA8, 0x214);
    scpPlayEnd(D_00639EA8);

    actCreateSubThread(actE3St09aGirlWay, 0x15);

    _ACTWait(0x1E);

    scpPlayMot(D_00639EA4, 0xFC);
    scpPlayWaitMotEnd(D_00639EA4);

    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    ScpCallCameraSetTarget(1421.0f, 97.0f, -1885.0f);
}

extern char D_00618F00[];
extern char D_006225C0[];
extern void StandbyStreamMotion(char *a0);
extern int CheckReadyStreamMotion(void);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern void SetWindManager(float a, float b, float c, float d, float e, float f, float g, float h);
extern void scpPlayStart(int a0);
extern void reg_SetScissorSw(int val);
extern void SetStaticBlur(int x);
extern void actE3GateDemo(volatile int a0);
extern void actE3GateJimaku(volatile int a0);
extern int D_0063BE00;

void actE3GateChk(volatile int a0)
{
    int i;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 3000.0f) == 0) {
        _ACTWait(1);
    }

    StandbyStreamMotion(D_00618F00);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(D_006225C0, i);
        _ACTWait(1);
    }

    lt_switch_layout(0x37);

    SetWindManager(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 5.0f, 0.0f);

    scpPlayStart(D_00639EA8);

    reg_SetScissorSw(1);
    SetStaticBlur(0);

    scpAdpcmPlayRequestFunc(4, &D_0063BE00, 1, 1, 0);
    while (D_0063BE00 == 0) {
        _ACTWait(1);
    }

    gflagOn(0x169);
    _ACTWait(1);

    actCreateSubThread(actE3GateDemo, 0x15);
    actCreateSubThread(actE3GateJimaku, 0x15);

    stage_SetAnimation(0x10D, 1, 0);
}

extern int EntryStreamMotion(int a0);
extern void PlayStreamMotion(void);
extern void SetAuraInspireParam(float a0);
extern void ReinitWindManager(void);
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
extern void stgmgrForceSwitchWithFadeColor(int id, float speed, float wait, int r, int gr, int b);
extern float D_0063AA0C;

void actE3GateDemo(volatile int a0)
{
    scpSearchGobj(0xD36)->f16C = 1;

    EntryStreamMotion(D_00639EA4);
    EntryStreamMotion(D_00639EA8);
    EntryStreamMotion((int)scpSearchGobj(0xD36));

    PlayStreamMotion();

    scpFadeIn(6.0f);

    stage_SetAnimation(0x288, 1, 0);

    while (stage_CheckAnimationFrame(0x288, 0xA, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    AdpcmPlay(*(int *)(D_0063BE00 + 0x2C));

    while (stage_ContinueAnimation(0x288, 0x289) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x289, 0x28A) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x28A, 0x28B) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x28B, 0x28C) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x28C, 0x28D) == 0) {
        _ACTWait(1);
    }

    reg_SetScissorSw(0);

    while (stage_ContinueAnimation(0x28D, 0x28E) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x28E, 0x28F) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x28F, 0x290) == 0) {
        _ACTWait(1);
    }

    SetStaticBlur(8);
    SetAuraInspireParam(100.0f);

    stage_SetAnimation(0x1DB, 1, 0);

    iosPadActRequest(D_00639EAC, 0xF);

    soundSeDefPlay(0x591, 0, 0, 0);

    while (stage_CheckAnimationFrame(0x290, 0x2D, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (D_0063BE00 != 0) {
        scpAdpcmFadeCloseFunc(&D_0063BE00, 0x50);
    }

    ReinitWindManager();

    lt_switch_layout(0x36);

    enable_game_pause = 0;

    scpFadeOut(4.0f, 0xFF, 0xFF, 0xFF);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (D_0063AA0C > 0.0f) {
        D_0063AA0C -= 0.012f;
        _ACTWait(1);
    }

    mpegPlayReturnStage = 0x5F;

    stgmgrForceSwitchWithFadeColor(0x68, 255.0f, 4.0f, 0, 0, 0);
}

typedef struct JimakuSub {
    char unk00[0x2C]; /* 0x0C */
    int unk2C;        /* 0x38 */
    int n;            /* 0x3C */
    int unk34;        /* 0x40 */
    int unk38;        /* 0x44 */
    void *unk3C;      /* 0x48 */
    void *unk40;      /* 0x4C */
} JimakuSub;

typedef struct JimakuArg {
    int cmd;       /* 0x00 */
    int unk04;     /* 0x04 */
    int done;      /* 0x08 */
    JimakuSub sub; /* 0x0C */
} JimakuArg;

extern JimakuArg jimaku_msg;
extern int jimakuOn;
extern void jimakuBegin(int a0);
extern void jimakuJump(int a0);

void actE3GateJimaku(volatile int a0)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin((int)&jimaku_msg);
            break;
        case 0x12C:
            jimaku_msg.sub.unk2C = 0x19;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x58C:
            jimaku_msg.sub.unk2C = 0x1A;
            jimaku_msg.sub.unk38 = 0x1E;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 7300.0f);
}

void actE3St01bInit(void)
{
    stage_SetAnimation(0xB7, 0, -1);
}

extern int stage_CheckAnimationFrame(int anim, int frame, int a2);
extern int iosPadActRequest(int port, int id);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern int D_0063BE04;
extern int D_00639EAC;

void actE3St09aBrgDown(volatile int a0)
{
    lt_switch_layout(0x37);
    gflagOn(0x56);

    scpAdpcmPlayRequestFunc(0x5A, &D_0063BE04, 1, 1, 1);
    while (D_0063BE04 == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x17A, 1, 0);

    while (stage_CheckAnimationFrame(0x17A, 0x73, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x17A, 0xA5, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFinish(0x17A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063AA08 = 0;

    lt_switch_layout(0x36);
}

extern void scpFadeOut(float t, int a1, int a2, int a3);
extern void InitStageLight(int stage);
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int stage_no;

void actE3Warning(volatile int a0)
{
    int x = a0;
    actInitialize(a0);

    scpFadeOut(255.0f, 0, 0, 0);

    enable_game_pause = 0;

    _ACTWait(1);

    D_0063AA08 = 1;
    InitStageLight(stage_no);

    RequestStageChange(1, D_00639EA4, 0, 255.0f, 0.0f);
}

extern void stgmgrNextStagePreLoadForceStageSet(int val);

typedef struct {
    unsigned char _0[0xA0];
    short ent[0x18];
    unsigned char _d0[0xC4];
} StgPre;

extern StgPre D_005F5D50[];
extern int D_0055C518[][10];
extern void actE3Inst1Chk(volatile int a0);
extern ActMail D_004F79F0[];

void actE3Inst1(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);
    StgPre *pre;

    _ACTWait(1);

    D_0063AA08 = 1;
    if (D_00639EA4 != 0) {
        scpPlayMot(D_00639EA4, 0);
    }

    pre = &D_005F5D50[stage_no];
    stgmgrNextStagePreLoadForceStageSet(D_0055C518[pre->ent[0]][9]);

    D_004F79F0[0].func = actE3Inst1Chk;
    sub->mail = D_004F79F0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void actE3DoorMain(volatile int a0);
extern ActMail D_004F7A50[];

void actE3Door(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x167) == 0) {
        stage_SetAnimation(0x3B9, 0, 0);

        D_004F7A50[0].func = actE3DoorMain;
        sub->mail = D_004F7A50;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x3B9, 0, -1);
    }
}

extern void actE3CageFallReadyChk(volatile int a0);
extern ActMail D_004F7AC0[];

void actE3CageFallReady(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x168) == 0) {
        D_004F7AC0[0].func = actE3CageFallReadyChk;
        sub->mail = D_004F7AC0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void actE3St13cIntroChk(volatile int a0);
extern ActMail D_004F7AA0[];

void actE3St13cIntro(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x16B) == 0) {
        D_004F7AA0[0].func = actE3St13cIntroChk;
        sub->mail = D_004F7AA0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actE3St13cGene1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x16C) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x190);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actE3St13cGene2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x16C) == 0) {
        _ACTWait(1);
    }
    Generator_Call(a0);
    _ACTWait(0x78);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern void _ACTWait(int a0);
extern int actInitialize(int a0);

void actE3Floor(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

extern void actE3St01bEneChk(volatile int a0);
extern ActMail D_004F7B00[];

void actE3St01bEne(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x16A) == 0) {
        D_004F7B00[0].func = actE3St01bEneChk;
        sub->mail = D_004F7B00;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actE3St01bGene1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x16A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x1E);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actE3St01bGene2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x16A) == 0) {
        _ACTWait(1);
    }
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actE3St01bGene3(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x16A) == 0) {
        _ACTWait(1);
    }
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern void actE3St09aBrgMain(volatile int a0);
extern ActMail D_004F7B90[];

void actE3St09aBrg(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x56) == 0) {
        stage_SetAnimation(0x17A, 0, 0);

        D_004F7B90[0].func = actE3St09aBrgMain;
        sub->mail = D_004F7B90;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x17A, 0, -1);
    }
}

extern void MallocStreamMotionBuffer(void);
extern PObjGObj *scpSearchGobj(int id);
extern void scpPlayStart(int a0);
extern void actE3GateChk(volatile int a0);
extern ActMail D_004F7B50[];

void actE3Gate(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    MallocStreamMotionBuffer();

    scpSearchGobj(0xD36)->f16C = 0;

    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    scpPlayMot(D_00639EA4, 0);

    scpFadeOut(255.0f, 0, 0, 0);

    stage_SetAnimation(0x10D, 0, 0);
    stage_SetAnimation(0x110, 0, 0);

    D_004F7B50[0].func = actE3GateChk;
    sub->mail = D_004F7B50;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void scpSekizouCheckPoint(void);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern void scpFadeIn(float f);
extern int actCreateSubThread(void *entry, int prio);
extern void actE3CapsuleDemo(volatile int a0);
extern int D_0063BDF8;
extern int D_0063C4E0;

void actE3CapsuleChk(volatile int a0)
{
    scpSekizouCheckPoint();

    gflagOn(0x166);

    scpAdpcmPlayRequestFunc(2, &D_0063BDF8, 1, 1, 1);
    while (D_0063BDF8 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    D_0063C4E0 = actCreateSubThread(actE3CapsuleDemo, 0x15);
}

extern void scpPlayMot(int a0, int mot);
extern void scpPlayMotDir(int a0, void *dir);
extern void scpPlayEnd(int a0);
extern void *test_CURRENTROOT(int a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern int D_00639EA4;
extern int enable_game_pause;
/* e3.o's own .rodata: the capsule demo's exit direction vector. */
extern long long D_00622510[];

void actE3CapsuleDemoEnd(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    scpPlayMot(D_00639EA4, 0x133);

    while (stage_CheckAnimationFinish(0x270) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA4, 0);

    ofs[0] = D_00622510[0];
    ofs[1] = D_00622510[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;

    lt_switch_layout(0x36);

    enable_game_pause = 1;
}

extern int D_0063AA08;
/* e3.o's own .data run (no MAIN.MAP symbol): actor mail packets. */
extern ActMail D_004F7A30[];

void actE3DoorMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = D_004F7A30;

    while (1) {
        _ACTWait(1);
    }
}

extern void ACTSendMailCorrect(int a0, int mail);
extern void actE3DoorUp(volatile int a0);
extern ActMail D_004F7A70[];

void actE3DoorSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004F7A70[0].func = actE3DoorUp;
    sub->mail = D_004F7A70;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

/* e3.o's own .data run (no MAIN.MAP symbol): the door's SE position. */
extern float D_004F7A90[];

void actE3DoorUp(volatile int a0)
{
    lt_switch_layout(0x37);
    gflagOn(0x167);

    _ACTWait(0x3C);

    stage_SetAnimation(0x3B9, 1, 0);

    soundSeDefPlay(0x4C5, 0, D_004F7A90, 1);

    _ACTWait(0x1E);

    soundSeDefPlay(0x4C6, 0, D_004F7A90, 1);

    while (stage_CheckAnimationFinish(0x3B9) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063AA08 = 0;

    lt_switch_layout(0x36);
}

void actE3St13cIntroChk(volatile int a0)
{
    lt_switch_layout(0x37);
    gflagOn(0x16B);

    D_0063AA08 = 1;
    _ACTWait(0x78);

    stage_SetAnimation(0x3BA, 1, 0);

    while (stage_CheckAnimationFinish(0x3BA) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);

    D_0063AA08 = 0;
}

extern int D_00639EA4;
extern int D_0063BDFC;
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern int scpTriggerFloorAttr(int a0, int a1);

void actE3CageFallReadyChk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    D_0063BDFC = 0;
    _ACTWait(1);
    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0) {
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(3, &D_0063BDFC, 1, 1, 0);
}

extern int D_00639EA8;

void actE3St01bEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);

    D_0063AA08 = 1;
    _ACTWait(0x1E);

    gflagOn(0x16A);

    stage_SetAnimation(0xB6, 1, 0);

    while (stage_CheckAnimationFinish(0xB6) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);

    D_0063AA08 = 0;
}

/* e3.o's own .rodata: the girl's way-point vector. */
extern long long D_006225B0[];
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
extern void RequestStageChangeDirect(int a0, int a1, int *buf, int a3);
extern void brainUnlockGirl(void);
extern void memset(void *dst, int c, int n);

void actE3St09aGirlWay(volatile int a0)
{
    long long buf[2];
    long long way[2];

    buf[0] = D_006225B0[0];
    buf[1] = D_006225B0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);

    memset(way, 0, 0x10);
    RequestStageChangeDirect(D_00639EA8, 0x66, (int *)way, 0xB4);

    lt_switch_layout(0x36);

    D_0063AA08 = 0;
    brainUnlockGirl();
}

extern ActMail D_004F7B70[];

void actE3St09aBrgMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    sub->mainMail = D_004F7B70;

    while (1) {
        _ACTWait(1);
    }
}

extern void actE3St09aBrgDown(volatile int a0);
extern ActMail D_004F7BB0[];

void actE3St09aBrgSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004F7BB0[0].func = actE3St09aBrgDown;
    sub->mail = D_004F7BB0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
