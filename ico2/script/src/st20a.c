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

extern void actSt20aBridgeSwitch(volatile int a0);
extern void actSt20aGondolaSwitch(volatile int a0);

/* This stage's actor mail records. Word 0 of each entry is the mail id the
   entry answers (430 = the actor's own wake-up post, 429 = the trailing
   entry); the handler in .func is installed at run time just before the
   record is posted. The two main-thread records answer their own ids and
   carry their switch handler from the start. Each record is named for the
   actor thread that owns and posts it. */
static ActMail bridgeMain_mes[2] = {{406, actSt20aBridgeSwitch}, {429}};

static ActMail bridge_mes[2] = {{430}, {429}};

static ActMail bridgeSwitch_mes[2] = {{430}, {429}};

static ActMail gondolaMain_mes[2] = {{407, actSt20aGondolaSwitch}, {429}};

static ActMail gondola_mes[2] = {{430}, {429}};

static ActMail gondolaSwitchUp_mes[2] = {{430}, {429}};

static ActMail gondolaSwitchDown_mes[2] = {{430}, {429}};

static ActMail gondolaDown_mes[2] = {{430}, {429}};

static ActMail gondolaUp_mes[2] = {{430}, {429}};

static ActMail exit_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail fence_mes[2] = {{430}, {429}};

static ActMail fence2_mes[2] = {{430}, {429}};

static ActMail fenceDownChk_mes[2] = {{430}, {429}};

static ActMail fenceUpChk_mes[2] = {{430}, {429}};

static ActMail fenceDownChk2_mes[2] = {{430}, {429}};

static ActMail fenceUpChk2_mes[2] = {{430}, {429}};

static ActMail girlPos_mes[2] = {{430}, {429}};

static ActMail hint1_mes[2] = {{430}, {429}};

extern int gflagChk(int id);
extern void gflagOn(int id);
extern void gflagOff(int id);
extern int actInitialize(int a0);
extern void _ACTWait(int n);
extern void ACTSendMailCorrect(int a0, int mail);
extern void SleepHint(int id);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern int scpSearchGobj(int id);
extern void FinishHint(int id);
extern void Generator_Call(int a0);
extern void gamesysObjInfoCls(int a, int b);
extern int D_00639EA8;
extern int D_00639EA4;
extern int scpTriggerBall(int a0, int obj, float r);
extern int scpTriggerFloorAttr(int obj, int attr);
extern int D_0063AA08;
extern void stage_SetAnimation(int a, int b, int c);
extern void SetWayGroupActive(int g, int on);

void actSt20aInit(void)
{
    if (gflagChk(0x13B) == 0) {
        stage_SetAnimation(0x94, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(0x94, 0, -1);
        SetWayGroupActive(4, 1);
    }
}

void actSt20aEnd(void)
{
    if (D_00639EA8 != 0 && gflagChk(0x13B) != 0 && gflagChk(0x13E) == 0) {
        gflagOn(0x187);
    }
    gamesysObjInfoCls(*(int *)(scpSearchGobj(0x7E9) + 0xC), *(int *)(scpSearchGobj(0x7E9) + 8));
    gamesysObjInfoCls(*(int *)(scpSearchGobj(0x7E7) + 0xC), *(int *)(scpSearchGobj(0x7E7) + 8));
}

extern int brg20a;
extern int gondola_up;
extern int gondola_down;
extern unsigned int st20a_yure;
extern int D_00639EAC;
extern int D_0063C5A8;
extern int D_0028F8F4[];
extern void lt_switch_layout(int id);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern void SetGirlDangerGObj(int a0);
extern void ClearGirlDangerGObj(void);
extern void scpAdpcmPlayRequestFunc(int no, int *h, int a2, int a3, int a4);
extern void scpAdpcmFadeCloseFunc(int *h, short rate);
extern int scpAdpcmCloseChkFunc(int *h);
extern int scpAdpcmPlayRequestNum(void);
extern int actCreateSubThread(void *entry, int prio);
extern void iosThreadSetPri(int th, int pri);
extern void scpFadeOut(float f, int a1, int a2, int a3);
extern void scpFadeIn(float f);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern void iosPadActStop(int key);
extern int stage_CheckAnimationFrame(int a, int b, int c);
extern int iosPadActRequest(int a0, int a1);
extern void actSt20aBridgeDownSub(volatile int a0);
extern void actSt20aGondolaMain(volatile int a0);

void actSt20aBridgeDown(volatile int a0)
{
    int th;

    lt_switch_layout(0x37);
    scpSleepEnemyAll();
    gflagOn(0x13B);
    gflagOff(0x187);
    st20a_yure = 0xFFFFFFFF;
    D_0063C5A8 = 0;
    scpAdpcmPlayRequestFunc(0x47, &brg20a, 1, 1, 0);
    th = actCreateSubThread(actSt20aBridgeDownSub, 0x15);
    while (D_0063C5A8 == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    iosThreadSetPri(th + 0x24, 0x22);
    if (D_0063C5A8 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (brg20a == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc(&brg20a, 0x200);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(0x94, 0, -1);
        scpFadeIn(3.0f);
    }
    iosPadActStop(st20a_yure);
    SetWayGroupActive(4, 1);
    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

void actSt20aGondolaDown(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    SetGirlDangerGObj(D_00639EA4);
    scpAdpcmPlayRequestFunc(0x45, &gondola_down, 1, 1, 1);
    while (gondola_down == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(0x93, 1, 0);
    gflagOn(0x13C);
    while (stage_CheckAnimationFrame(0x93, 0x96, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);
    while (stage_CheckAnimationFrame(0x93, 0x1F4, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x10);
    if (gondola_down != 0) {
        scpAdpcmFadeCloseFunc(&gondola_down, 0x100);
    }
    while (scpAdpcmCloseChkFunc(&gondola_down) != 0) {
        _ACTWait(1);
    }
    ClearGirlDangerGObj();
    gondolaDown_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondolaDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt20aGondolaUp(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    scpAdpcmPlayRequestFunc(0x46, &gondola_up, 1, 1, 1);
    while (gondola_up == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(0x93, 1, 0x1F4);
    gflagOff(0x13C);
    while (stage_CheckAnimationFrame(0x93, 0x334, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);
    while (stage_CheckAnimationFrame(0x93, 0x3E8, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x10);
    if (gondola_up != 0) {
        scpAdpcmFadeCloseFunc(&gondola_up, 0x100);
    }
    while (scpAdpcmCloseChkFunc(&gondola_up) != 0) {
        _ACTWait(1);
    }
    gondolaUp_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondolaUp_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void scpLinkBGAtoLayoutedTarget(int a0, int a1);
extern void scpPlayPosSet(int gobj, float x, float y, float z);
extern void actSt20aFenceUpChk(volatile int a0);
extern void actSt20aFenceDownChk2(volatile int a0);

void actSt20aFence(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(0x135) == 0) {
        SetWayGroupActive(0x13, 1);

        *(int *)(scpSearchGobj(0x7E8) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7E9) + 0x16C) = 0;

        *(int *)(scpSearchGobj(0x7EE) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7EF) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7F0) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7F1) + 0x16C) = 0;

        *(int *)(scpSearchGobj(0x7EA) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7EB) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7EC) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7ED) + 0x16C) = 0;

        scpLinkBGAtoLayoutedTarget(0x7E6, 0x95);
        stage_SetAnimation(0x95, 0, 0x1E);

        fence_mes[0].func = actSt20aFenceUpChk;
        sub->mail = fence_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(0x13, 0);

        *(int *)(scpSearchGobj(0x7E6) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7E7) + 0x16C) = 0;

        *(int *)(scpSearchGobj(0x7EA) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7EB) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7EC) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7ED) + 0x16C) = 0;

        gflagOff(0x135);

        scpLinkBGAtoLayoutedTarget(0x7E8, 0x95);
        stage_SetAnimation(0x95, 0, 0);

        if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0) {
            scpPlayPosSet(D_00639EA8, 3973.0f, -1100.0f, -1169.0f);
        }

        fence2_mes[0].func = actSt20aFenceDownChk2;
        sub->mail = fence2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern void actSt20aFenceUpChk(volatile int a0);
extern int stage_CheckAnimationFrame(int a, int b, int c);
extern int soundSeDefPlay(int se, int a1, int a2, int a3);

void actSt20aFenceDownChk(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    while (scpTriggerBall(a0, scpSearchGobj(0x7E6), 5.0f) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(0x95, 1, 0);
    while (stage_CheckAnimationFrame(0x95, 0xA, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(0x53B, 0, 0, 1);
    while (stage_CheckAnimationFrame(0x95, 0x1E, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(0x13, 1);
    *(int *)(scpSearchGobj(0x7EA) + 0x16C) = 0;
    *(int *)(scpSearchGobj(0x7EB) + 0x16C) = 0;
    *(int *)(scpSearchGobj(0x7EC) + 0x16C) = 0;
    *(int *)(scpSearchGobj(0x7ED) + 0x16C) = 0;
    gflagOff(0x140);
    fenceDownChk_mes[0].func = actSt20aFenceUpChk;
    sub->mail = fenceDownChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt20aFenceDownChk(volatile int a0);

void actSt20aFenceUpChk(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    while (scpTriggerBall(a0, scpSearchGobj(0x7E6), 5.0f) != 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(0x13, 0);
    stage_SetAnimation(0x95, 1, 0x1F);
    while (stage_CheckAnimationFrame(0x95, 0x28, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(0x53B, 0, 0, 1);
    while (stage_CheckAnimationFinish(0x95) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    *(int *)(scpSearchGobj(0x7EA) + 0x16C) = 1;
    *(int *)(scpSearchGobj(0x7EB) + 0x16C) = 1;
    *(int *)(scpSearchGobj(0x7EC) + 0x16C) = 1;
    *(int *)(scpSearchGobj(0x7ED) + 0x16C) = 1;
    gflagOn(0x140);
    fenceUpChk_mes[0].func = actSt20aFenceDownChk;
    sub->mail = fenceUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt20aFenceUpChk2(volatile int a0);

void actSt20aFenceDownChk2(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    while (scpTriggerBall(a0, scpSearchGobj(0x7E8), 5.0f) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(0x95, 1, 0);
    while (stage_CheckAnimationFrame(0x95, 0xA, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(0x53B, 0, 0, 1);
    while (stage_CheckAnimationFrame(0x95, 0x1E, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    *(int *)(scpSearchGobj(0x7EE) + 0x16C) = 0;
    *(int *)(scpSearchGobj(0x7EF) + 0x16C) = 0;
    *(int *)(scpSearchGobj(0x7F0) + 0x16C) = 0;
    *(int *)(scpSearchGobj(0x7F1) + 0x16C) = 0;
    SetWayGroupActive(0x13, 1);
    gflagOff(0x140);
    fenceDownChk2_mes[0].func = actSt20aFenceUpChk2;
    sub->mail = fenceDownChk2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt20aFenceDownChk2(volatile int a0);

void actSt20aFenceUpChk2(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    while (scpTriggerBall(a0, scpSearchGobj(0x7E8), 5.0f) != 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(0x13, 0);
    stage_SetAnimation(0x95, 1, 0x1F);
    while (stage_CheckAnimationFrame(0x95, 0x28, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlay(0x53B, 0, 0, 1);
    while (stage_CheckAnimationFinish(0x95) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    *(int *)(scpSearchGobj(0x7EE) + 0x16C) = 1;
    *(int *)(scpSearchGobj(0x7EF) + 0x16C) = 1;
    *(int *)(scpSearchGobj(0x7F0) + 0x16C) = 1;
    *(int *)(scpSearchGobj(0x7F1) + 0x16C) = 1;
    gflagOn(0x140);
    fenceUpChk2_mes[0].func = actSt20aFenceDownChk2;
    sub->mail = fenceUpChk2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt20aBridgeMain(volatile int a0);

void actSt20aBridge(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(0x13B) == 0) {
        bridge_mes[0].func = actSt20aBridgeMain;
        sub->mail = bridge_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern void actSt20aGondolaMain(volatile int a0);

void actSt20aGondola(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(0x13C) != 0) {
        stage_SetAnimation(0x93, 0, 0);
        _ACTWait(0xA);
        stage_SetAnimation(0x93, 0, 0x1F4);
    } else {
        stage_SetAnimation(0x93, 0, 0);
    }
    gondola_mes[0].func = actSt20aGondolaMain;
    sub->mail = gondola_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void actSt20aExitChk(volatile int a0);

void actSt20aExit(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    exit_mes[0].func = actSt20aExitChk;
    sub->mail = exit_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt20aElv(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    if (gflagChk(0x135) != 0) {
        *(int *)(scpSearchGobj(0x7E6) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7E7) + 0x16C) = 0;
        gflagOff(0x135);
    } else {
        *(int *)(scpSearchGobj(0x7E8) + 0x16C) = 0;
        *(int *)(scpSearchGobj(0x7E9) + 0x16C) = 0;
    }
}

extern void actSt20aEneChk(volatile int a0);

void actSt20aEne(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(0x13E) == 0) {
        ene_mes[0].func = actSt20aEneChk;
        sub->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt20aEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x13F) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void actSt20aEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x13F) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void actSt20aEnemy3(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x13F) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
}

extern void actSt20aHint1Chk(volatile int a0);

void actSt20aHint1(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(0x141) == 0) {
        hint1_mes[0].func = actSt20aHint1Chk;
        sub->mail = hint1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(0x14);
    }
}

extern void actSt20aGirlPosChk(volatile int a0);

void actSt20aGirlPos(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);
    if (gflagChk(0x142) == 0) {
        SleepHint(0x14);
        girlPos_mes[0].func = actSt20aGirlPosChk;
        sub->mail = girlPos_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* the actor entry's parameter is its frame home: the thread switch writes it */
void actSt20aBridgeMain(volatile int a0)
{
    *(char **)(*(int *)(a0 + 0x164) + 0xD0) = (char *)bridgeMain_mes;
    D_0063AA08 = 0;
    while (1) {
        _ACTWait(1);
    }
}

extern void actSt20aBridgeDown(volatile int a0);

void actSt20aBridgeSwitch(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    D_0063AA08 = 1;
    bridgeSwitch_mes[0].func = actSt20aBridgeDown;
    sub->mainMail = 0;
    sub->mail = bridgeSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int brg20a;
extern unsigned int st20a_yure;
extern unsigned char st20a_yure_vol;
extern int D_00639EAC;
extern int D_0063C5A8;
extern void AdpcmPlay(int a0);
extern int iosPadActRequest(int a0, int a1);
extern void iosPadActVolumeSet(int h, int v);
extern int stage_CheckAnimationFinish(int a0);

void actSt20aBridgeDownSub(volatile int a0)
{
    _ACTWait(0x1E);
    while (brg20a == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(*(int *)(brg20a + 0x2C));
    stage_SetAnimation(0x94, 1, 0);
    st20a_yure = iosPadActRequest(D_00639EAC, 9);
    st20a_yure_vol = 0x80;
    iosPadActVolumeSet(st20a_yure, 0x80);
    while (stage_CheckAnimationFinish(0x94) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C5A8 = 1;
    _ACTWait(0);
}

extern void lt_switch_layout(int id);
extern void scpWakeupEnemyAll(void);

void actSt20aGondolaMain(volatile int a0)
{
    char *p = *(char **)(a0 + 0x164);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    *(char **)(p + 0xD0) = (char *)gondolaMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

extern void actSt20aGondolaUp(volatile int a0);
extern void actSt20aGondolaDown(volatile int a0);
extern void scpSleepEnemyAll(void);

void actSt20aGondolaSwitch(volatile int a0)
{
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();
    if (gflagChk(0x13C) != 0) {
        gondolaSwitchUp_mes[0].func = actSt20aGondolaUp;
        sub->mail = gondolaSwitchUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
    gondolaSwitchDown_mes[0].func = actSt20aGondolaDown;
    sub->mail = gondolaSwitchDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern void OnGirlEscortFlag();
extern void RequestStageChange(int a0, int a1, int a2, float a3, float a4);

void actSt20aExitChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 400.0f) == 0 ||
           scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(0x13D);
    gflagOff(0x135);
    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0) {
        OnGirlEscortFlag();
        RequestStageChange(4, D_00639EA4, D_00639EA8, 2.0f, 8.0f);
    }
    RequestStageChange(4, D_00639EA4, 0, 2.0f, 8.0f);
}

void actSt20aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (gflagChk(0x13B) == 0 || scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(0x13E);
    gflagOn(0x13F);
}

extern void WakeupHint(int id);

void actSt20aGirlPosChk(volatile int a0)
{
    while (D_00639EA8 == 0 || scpTriggerBall(a0, D_00639EA8, 200.0f) == 0) {
        _ACTWait(1);
    }
    gflagOn(0x142);
    WakeupHint(0x14);
}

extern char D_00623070[];

void actSt20aHint1Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0 &&
           scpTriggerFloorAttr(D_00639EA4, 0x4000000) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy(D_00623070);
    gflagOn(0x141);
    FinishHint(0x14);
}
