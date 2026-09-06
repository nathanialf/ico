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

extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern PObjGObj *scpSearchGobj(int a0);
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern void gflagOn(int a0);
extern void AdpcmPlay(int a0);
extern void SetCameraFlag_LwsCutBack(void);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int D_0063AA08;
extern char *pipe19a;
extern int D_0063C5A4;

extern void actSt19aOriUp(volatile int a0);
extern void actSt19aPipeChk(volatile int a0);
extern void actSt19aChainDown(volatile int a0);
extern void actSt19aChainMain(volatile int a0);
extern void actSt19aOriMain(volatile int a0);

/* st19a.o's own .data run (no MAIN.MAP symbols): actor mail packets. */
extern ActMail D_004FB250[];
extern ActMail D_004FB270[];
extern ActMail D_004FB290[];
extern float D_004FB2B0[];
extern ActMail D_004FB2F0[];
extern ActMail D_004FB310[];
extern ActMail D_004FB330[];
extern ActMail D_004FB350[];

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aOriUp);
INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aHaguruma);
INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aHagurumaChk);
ASM_LIT4_SLOT(D_00639AA8, 3933.0f);
INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aPipeChk);
INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aChainDown);
INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19bIntro);
void actSt19aOri(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    ScpCallCameraSetTarget(4298.0f, -2342.0f, 1331.0f);

    if (gflagChk(0x136) == 0) {
        stage_SetAnimation(0x8E, 0, 0);

        D_004FB270[0].func = actSt19aOriMain;
        self->mail = D_004FB270;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x8E, 0, 0x59);
    }
}
void actSt19aOriXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    soundSeDefPlay(0x545, 0, D_004FB2B0, 1);

    stage_SetAnimation(0x8E, 0, 0);
}
void actSt19aPipe(volatile int a0)
{
    int x = a0;

    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x138) == 0) {

        scpSearchGobj(0x7A7)->f16C = 0;
        stage_SetAnimation(0x8F, 0, 0);

        D_004FB2F0[0].func = actSt19aPipeChk;
        self->mail = D_004FB2F0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);

    } else {

        scpSearchGobj(0x7A6)->f16C = 0;
        stage_SetAnimation(0x8F, 0, -1);
    }
}
void actSt19aPipeXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x138) == 0) {
        stage_SetAnimation(0x8F, 0, 0);
    } else {
        stage_SetAnimation(0x8F, 0, -1);
    }
}
void actSt19aChain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x139) == 0) {
        scpSearchGobj(0x7AB)->f16C = 0;

        stage_SetAnimation(0x90, 0, 0);

        D_004FB330[0].func = actSt19aChainMain;
        self->mail = D_004FB330;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt19aOriMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = D_004FB250;

    while (1) {
        _ACTWait(1);
    }
}
void actSt19aOriSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;
    D_004FB290[0].func = actSt19aOriUp;
    sub->mail = D_004FB290;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt19aChainMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = D_004FB310;

    while (1) {
        _ACTWait(1);
    }
}
void actSt19aChainSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    if (gflagChk(0x139) == 0) {
        D_004FB350[0].func = actSt19aChainDown;
        sub->mail = D_004FB350;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt19aChainDownSub(volatile int a0)
{
    _ACTWait(0x3C);

    while (pipe19a == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(pipe19a + 0x2C));

    stage_SetAnimation(0x90, 1, 0);

    gflagOn(0x139);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(0x90, 0xF0, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C5A4 = 1;
    _ACTWait(0x3C);
}
