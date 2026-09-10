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

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    Act *act;          /* 0x164 */
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
extern void AdpcmPlay(int a0);
extern int iosPadActRequest(int a0, int a1);
extern void iosPadActVolumeSet(int h, int vol);
extern void iosPadActStop(int h);
extern void iosThreadSetPri(int th, int pri);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int actCreateSubThread(void *entry, int prio);
extern void scpAdpcmPlayRequestFunc(int a0, int *h, int a2, int a3, int a4);
extern int scpAdpcmPlayRequestNum(void);
extern void scpAdpcmFadeCloseFunc(int *h, int a1);
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern void scpFadeIn(float a0);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern void preload(int a0);
extern void scpPlayStart(int a0);
extern void scpPlayEnd(int a0);
extern void scpPlayMot(int a0, int mot);
extern void scpPlayWaitMotEnd(int a0);
extern void scpPlayPosSet(int a0, float x, float y, float z);
extern void scpPlayMotDir(int a0, float *dir);
extern int scpGameStat_BoyWeaponkind(void);
extern int scpActStatusDeathFall(int a0);
extern void scpSekizouCheckPoint(void);
extern void *test_CURRENTROOT(int a0);
extern void sceVu0SubVector(float *d, void *a, void *b);
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;
extern int D_00639EAC;
extern int D_0063C578;

typedef struct PadState {
    int unk00;        /* 0x00 */
    int flags;        /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} PadState;

extern PadState D_0028F8F0[];
/* st13a.o's own .sdata run; MAIN.MAP names all seven. */
extern int st13a_up;
extern int st13a_down;
extern int sekizo13a;
extern unsigned int st13a_yure;
extern unsigned char st13a_yure_vol;
extern int sekizo_13a;
extern unsigned char sekizo_13a_vol;
extern ActMail D_004FAA00[];
void actSt13aElevUpSub(volatile int a0);
void actSt13aElevDownSub(volatile int a0);
void actSt13aElevDownChk(volatile int a0);
/* st13a.o's own .data run (no MAIN.MAP symbols): actor mail packets. */
extern ActMail D_004FA9A0[];
extern ActMail D_004FA9C0[];
extern ActMail D_004FA9E0[];
extern ActMail D_004FAA20[];
extern ActMail D_004FAA40[];
extern ActMail D_004FAA60[];
extern ActMail D_004FAA80[];

/* The chain-OK watcher's mail record: it installs actSt13aChainNG here and
   posts it to hand the chain back to the NG (hang-disabled) watcher. Word 0
   of each entry is the mail id the entry answers (0x1AE the actor post,
   0x1AD the trailing entry); .func is filled in at run time. Named for the
   thread that owns and posts it. */
static ActMail chain_ok_mes[2] = {{0x1AE}, {0x1AD}};

extern ActMail D_004FAAC0[];

void actSt13aElevUpSub(volatile int a0)
{
    AdpcmPlay(*(int *)(st13a_up + 0x2C));

    stage_SetAnimation(0xAD, 1, 0);
    stage_SetAnimation(0xAE, 1, 0);

    while (stage_CheckAnimationFrame(0xAD, 0x56, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0xAD, 0x8C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure = iosPadActRequest(D_00639EAC, 9);
    st13a_yure_vol = 0x80;
    iosPadActVolumeSet(st13a_yure, 0x80);

    while (stage_CheckAnimationFrame(0xAD, 0xC8, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    st13a_yure_vol = 0x40;

    while (stage_CheckAnimationFrame(0xAD, 0x17C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C578 = 1;
    _ACTWait(0);
}

/* NOT LANDED: byte-exact except that gcc hoists `%%hi(D_0028F8F4)` out of the
   pad-wait loop into a second callee-saved register (extra `sd`, duplicated
   `li $a0,0xF`, +1 insn here / +3 in ElevDownChk); ROM recomputes the `lui`
   inside the loop.  The identical source shape DOES match in
   src/st08b.c actSt08bKurenSwitch.  See the r1 ledger row and
   seeds/st13a.r1_ElevUp_plus1_ElevDownChk_plus3_TU.c. */
ASM_LIT4_SLOT(D_00639A00, 0.025f);
INCLUDE_ASM("asm/nonmatchings/src/st13a", actSt13aElevUp);

void actSt13aElevDown(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0xF) != 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(0xAD, 0, 0);
        lt_switch_layout(0x37);
        D_0063AA08 = 1;
        scpPlayStart(D_00639EA4);
        scpAdpcmPlayRequestFunc(0x50, &st13a_down, 1, 1, 0);
        _ACTWait(0xA);
        stage_SetAnimation(0xAD, 0, 0x1C3);

        D_004FAA00[0].func = actSt13aElevDownChk;
        self->mail = D_004FAA00;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt13aElevDownSub(volatile int a0)
{
    stage_SetAnimation(0xAD, 1, 0x1C3);
    stage_SetAnimation(0xAF, 1, 0);

    scpPlayPosSet(D_00639EA4, -4871.0f, -2800.0f, 2699.0f);

    st13a_yure = iosPadActRequest(D_00639EAC, 9);
    st13a_yure_vol = 0x80;
    iosPadActVolumeSet(st13a_yure, 0x80);

    while (stage_CheckAnimationFrame(0xAD, 0x352, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);
    iosPadActStop(st13a_yure);
    st13a_yure = -1;

    while (stage_CheckAnimationFinish(0xAD) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C578 = 1;
    _ACTWait(0);
}

/* NOT LANDED: byte-exact except that gcc hoists `%%hi(D_0028F8F4)` out of the
   pad-wait loop into a second callee-saved register (extra `sd`, duplicated
   `li $a0,0xF`, +1 insn here / +3 in ElevDownChk); ROM recomputes the `lui`
   inside the loop.  The identical source shape DOES match in
   src/st08b.c actSt08bKurenSwitch.  See the r1 ledger row and
   seeds/st13a.r1_ElevUp_plus1_ElevDownChk_plus3_TU.c. */
ASM_LIT4_SLOT(D_00639A0C, 3527.0f);
ASM_LIT4_SLOT(D_00639A10, 2699.0f);
ASM_LIT4_SLOT(D_00639A14, -4871.0f);
INCLUDE_ASM("asm/nonmatchings/src/st13a", actSt13aElevDownChk);

void actSt13aSekizoChk(volatile int a0)
{
    float d[4];

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           scpActStatusDeathFall(D_00639EA4) != 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    scpAdpcmPlayRequestFunc(0x12, &sekizo13a, 1, 1, 1);
    while (sekizo13a == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0xB0, 1, 0);

    sekizo_13a = iosPadActRequest(D_00639EAC, 9);
    sekizo_13a_vol = 0x80;
    iosPadActVolumeSet(sekizo_13a, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayPosSet(D_00639EA4, -3688.0f, 3527.0f, 2502.0f);
    scpPlayMot(D_00639EA4, 0);
    _ACTWait(1);

    sceVu0SubVector(d, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, d);

    scpSekizouCheckPoint();

    scpPlayMot(D_00639EA4, 0xFB);
    scpPlayWaitMotEnd(D_00639EA4);
    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    gflagOn(0x146);

    while (stage_CheckAnimationFrame(0xB0, 0x97, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_13a);

    while (stage_CheckAnimationFinish(0xB0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

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

void actSt13aChainOK(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, scpSearchGobj(0x818), 200.0f) != 0) {
        _ACTWait(1);
    }

    EnableChainHang((char *)scpSearchGobj(0x817));
    gflagOff(0x148);

    chain_ok_mes[0].func = actSt13aChainNG;
    sub->mail = chain_ok_mes;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

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
