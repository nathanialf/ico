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
    Act *act;                   /* 0x164 */
} PObjGObj;

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void CheckPoint(void);
extern void gflagOn(int a0);
extern void gflagOff(int a0);
extern int scpSearchGobj(int a0);
extern int scpTriggerBall(int a0, int gobj, float r);
extern void EnableChainHang(char *a0);
extern void UnableChainHang(char *a0);
extern void lt_switch_layout(int a0);
extern int D_0063AA08;

extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void ScpCallCameraSetTarget(float x, float y, float z);

extern void actSt13aElevMain(volatile int a0);
extern void actSt13aElevUp(volatile int a0);
extern void actSt13aCheckChk(volatile int a0);
extern void actSt13aSekizoChk(volatile int a0);
extern void actSt13aChainOK(volatile int a0);
extern void actSt13aChainNG(volatile int a0);

/* st13a.o's own .data run (no MAIN.MAP symbols): actor mail packets. */
extern ActMail D_004FA9A0[];
extern ActMail D_004FA9C0[];
extern ActMail D_004FA9E0[];
extern ActMail D_004FAA20[];
extern ActMail D_004FAA40[];
extern ActMail D_004FAA60[];
extern ActMail D_004FAA80[];
extern ActMail D_004FAAA0[];
extern ActMail D_004FAAC0[];

INCLUDE_ASM("asm/nonmatchings/src/st13a", actSt13aElevUpSub);
ASM_LIT4_SLOT(D_00639A00, 0.025f);
INCLUDE_ASM("asm/nonmatchings/src/st13a", actSt13aElevUp);
INCLUDE_ASM("asm/nonmatchings/src/st13a", actSt13aElevDown);
ASM_LIT4_SLOT(D_00639A04, -4871.0f);
ASM_LIT4_SLOT(D_00639A08, 2699.0f);
INCLUDE_ASM("asm/nonmatchings/src/st13a", actSt13aElevDownSub);
ASM_LIT4_SLOT(D_00639A0C, 3527.0f);
ASM_LIT4_SLOT(D_00639A10, 2699.0f);
ASM_LIT4_SLOT(D_00639A14, -4871.0f);
INCLUDE_ASM("asm/nonmatchings/src/st13a", actSt13aElevDownChk);
ASM_LIT4_SLOT(D_00639A18, 3527.0f);
ASM_LIT4_SLOT(D_00639A1C, 2502.0f);
ASM_LIT4_SLOT(D_00639A20, -3688.0f);
INCLUDE_ASM("asm/nonmatchings/src/st13a", actSt13aSekizoChk);
void actSt13aElev(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    ScpCallCameraSetTarget(4729.0f, 2715.0f, -2504.0f);

    if (gflagChk(0x145) == 0) {
        stage_SetAnimation(0xAD, 0, 0);

        D_004FA9C0[0].func = actSt13aElevMain;
        self->mail = D_004FA9C0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt13aSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x146) == 0) {
        stage_SetAnimation(0xB0, 0, 0);

        D_004FAA20[0].func = actSt13aSekizoChk;
        self->mail = D_004FAA20;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xB0, 0, -1);
    }
}
void actSt13aCheck(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x147) == 0) {
        D_004FAA40[0].func = actSt13aCheckChk;
        self->mail = D_004FAA40;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt13aChain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x148) == 0) {
        D_004FAA60[0].func = actSt13aChainNG;
        self->mail = D_004FAA60;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        D_004FAA80[0].func = actSt13aChainOK;
        self->mail = D_004FAA80;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt13aElevMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004FA9A0;
    while (1) {
        _ACTWait(1);
    }
}
void actSt13aElevSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    D_004FA9E0[0].func = actSt13aElevUp;
    sub->mail = D_004FA9E0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt13aCheckChk(volatile int a0)
{
    _ACTWait(1);

    CheckPoint();
    gflagOn(0x147);
}
INCLUDE_ASM("asm/nonmatchings/src/st13a", actSt13aChainOK);
void actSt13aChainNG(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, scpSearchGobj(0x818), 200.0f) == 0) {
        _ACTWait(1);
    }

    UnableChainHang((char *)scpSearchGobj(0x817));
    gflagOn(0x148);

    D_004FAAC0[0].func = actSt13aChainOK;
    sub->mail = D_004FAAC0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
