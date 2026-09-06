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

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3WarningChk);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Title);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3TitleChk);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3TitleFrameChk);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Inst1Chk);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Capsule);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CapsuleDemoCancel);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CapsuleDemo);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St13cInit);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CageFall);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CageFallChk);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CageFallDemo);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CageFallEffect);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St09aSekizo);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St09aSekizoChk);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3GateChk);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3GateDemo);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3GateJimaku);
void actE3St01bInit(void) {
    stage_SetAnimation(0xB7, 0, -1);
}
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St09aBrgDown);
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
typedef struct { unsigned char _0[0xA0]; short ent[0x18]; unsigned char _d0[0xC4]; } StgPre;
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
void actE3St13cGene1(volatile int a0) {
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
void actE3St13cGene2(volatile int a0) {
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

void actE3Floor(volatile int a0) {
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
void actE3St01bGene1(volatile int a0) {
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
void actE3St01bGene2(volatile int a0) {
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
void actE3St01bGene3(volatile int a0) {
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
    while (D_0063BDF8 == 0) { _ACTWait(1); }

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

void actE3CageFallReadyChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    D_0063BDFC = 0;
    _ACTWait(1);
    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0) { _ACTWait(1); }
    scpAdpcmPlayRequestFunc(3, &D_0063BDFC, 1, 1, 0);
}
extern int D_00639EA8;

void actE3St01bEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) { _ACTWait(0); }

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
