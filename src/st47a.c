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
    char pad168[0x4];           /* 0x168 */
    int f16C;                   /* 0x16C */
} PObjGObj;

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void gflagOn(int a0);
extern void gflagOff(int a0);
extern PObjGObj *scpSearchGobj(int a0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aInit);
extern int D_00639EA8;
void actSt47aEnd(void) {
    if (D_00639EA8 != 0) {
        if (gflagChk(0x34) == 0) {
            gflagOn(0x187);
        }
    }
}
ASM_LIT4_SLOT(D_00639AFC, 1750.0f);
ASM_LIT4_SLOT(D_00639B00, -3000.0f);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aSekizo1Chk);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane1Down);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane1Up);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane2Down);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane2Up);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aRope);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aRopeChk);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aBarricadeChk);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aEnemy1);
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aTorch);
extern Act *actInitialize(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern ActMail D_004FB630[];
extern void actSt47aSekizo1Chk(volatile int a0);

void actSt47aSekizo1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x2B) == 0) {
        stage_SetAnimation(0xA3, 0, 0);
        D_004FB630[0].func = actSt47aSekizo1Chk;
        self->mail = D_004FB630;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xA3, 0, -1);
        if (gflagChk(0x89) == 0) {
            ScpCallCameraSetTarget(-3000.0f, 272.0f, 0.0f);
        }
    }
}
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4,
                       float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt47aSekizo2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x2C, 0xA4, 0, 0x12,
               -2450.0f, -1372.0f, -1150.0f,
               -2450.0f, -1372.0f, -1250.0f);
}
extern ActMail D_004FB670[];
extern void actSt47aHane1Main(volatile int a0);

void actSt47aHane1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    gflagChk(0x2F);

    D_004FB670[0].func = actSt47aHane1Main;
    self->mail = D_004FB670;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern ActMail D_004FB730[];
extern void actSt47aHane2Main(volatile int a0);

void actSt47aHane2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004FB730[0].func = actSt47aHane2Main;
    self->mail = D_004FB730;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern void FinishHint(int a0);
extern ActMail D_004FB7F0[];
extern void actSt47aBarricadeChk(volatile int a0);

void actSt47aBarricade(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x32) == 0) {
        stage_SetAnimation(0xAB, 0, 0);
        D_004FB7F0[0].func = actSt47aBarricadeChk;
        self->mail = D_004FB7F0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        FinishHint(4);
        FinishHint(6);
        stage_SetAnimation(0xAB, 0, -1);
    }
}
extern ActMail D_004FB810[];
extern void actSt47aExitChk(volatile int a0);

void actSt47aExit(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004FB810[0].func = actSt47aExitChk;
    self->mail = D_004FB810;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern ActMail D_004FB830[];
extern void actSt47aExit2Chk(volatile int a0);

void actSt47aExit2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x90) != 0) {
        D_004FB830[0].func = actSt47aExit2Chk;
        self->mail = D_004FB830;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004FB850[];
extern void actSt47aEneChk(volatile int a0);

void actSt47aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x34) == 0) {
        D_004FB850[0].func = actSt47aEneChk;
        self->mail = D_004FB850;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt47aEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x35) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xB4);

    Generator_MaskOff(a0);
    Generator_Call(a0);

    _ACTWait(0x3C);

    Generator_Call(a0);
}

void actSt47aEnemy3(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x35) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xB4);

    Generator_MaskOff(a0);
    Generator_Call(a0);

    _ACTWait(0x3C);

    Generator_Call(a0);
}
void actSt47aEnemy4(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x35) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);
}
extern void SleepHint(int a0);
extern ActMail D_004FB870[];
extern void actSt47aHint2OnChk(volatile int a0);

void actSt47aHint2On(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x36) == 0) {
        SleepHint(5);

        D_004FB870[0].func = actSt47aHint2OnChk;
        self->mail = D_004FB870;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt47aSekizo1Event(int x) {
    volatile int local = x;
}
extern long long D_006230B0[];
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
extern void RequestStageChangeDirect(int a0, int a1, int *buf, int a3);
extern void brainUnlockGirl(void);
extern void memset(void *dst, int c, int n);

void actSt47aGirlWay(volatile int a0)
{
    long long buf[2];
    long long way[2];

    buf[0] = D_006230B0[0];
    buf[1] = D_006230B0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);

    memset(way, 0, 0x10);
    RequestStageChangeDirect(D_00639EA8, 0xB, (int *)way, 0xB4);
    brainUnlockGirl();
}
void actSt47aSekizo2Event(int x) {
    volatile int local = x;
}
extern ActMail D_004FB650[];

void actSt47aHane1Main(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004FB650;
    while (1) {
        _ACTWait(1);
    }
}
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyAll(void);
extern int D_0063AA08;
extern ActMail D_004FB690[];
extern ActMail D_004FB6B0[];
extern void actSt47aHane1Up(volatile int a0);
extern void actSt47aHane1Down(volatile int a0);

void actSt47aHane1Switch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(0x2F) != 0) {
        D_004FB690[0].func = actSt47aHane1Up;
        sub->mail = D_004FB690;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }

    D_004FB6B0[0].func = actSt47aHane1Down;
    sub->mail = D_004FB6B0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern long long D_006230C0[];
extern int D_00639EA8;
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);

void actSt47aHane1_1Girl(volatile int a0)
{
    long long buf[2];
    buf[0] = D_006230C0[0];
    buf[1] = D_006230C0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
}
extern long long D_006230D0[];

void actSt47aHane1_2Girl(volatile int a0)
{
    long long buf[2];
    buf[0] = D_006230D0[0];
    buf[1] = D_006230D0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
}
extern ActMail D_004FB710[];

void actSt47aHane2Main(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004FB710;
    while (1) {
        _ACTWait(1);
    }
}
extern ActMail D_004FB750[];
extern ActMail D_004FB770[];
extern void actSt47aHane2Up(volatile int a0);
extern void actSt47aHane2Down(volatile int a0);

void actSt47aHane2Switch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(0x30) != 0) {
        D_004FB750[0].func = actSt47aHane2Up;
        sub->mail = D_004FB750;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }

    D_004FB770[0].func = actSt47aHane2Down;
    sub->mail = D_004FB770;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern long long D_006230E0[];

void actSt47aHane2Girl(volatile int a0)
{
    long long buf[2];
    buf[0] = D_006230E0[0];
    buf[1] = D_006230E0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
}
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int D_0063C5B4;

void actSt47aRopeSub(volatile int a0)
{
    _ACTWait(0xF);

    stage_SetAnimation(0xAA, 1, 0);

    while (stage_CheckAnimationFrame(0xAA, 0x94, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(0x1F7)->f16C = 1;

    while (stage_CheckAnimationFinish(0xAA) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C5B4 = 1;
    _ACTWait(0);
}
void actSt47aBarricadeEvent(int x) {
    volatile int local = x;
}
void actSt47aExitChk(volatile int a0)
{
    scpSearchGobj(0x1E1)->f16C = 0;

    while ((gflagChk(0xAE) == 0) || (gflagChk(0xEA) == 0)) {
        _ACTWait(1);
    }

    gflagOn(0x33);
    scpSearchGobj(0x1E0)->f16C = 0;
    scpSearchGobj(0x1E1)->f16C = 1;
}
void actSt47aExit2Chk(volatile int a0) {
    scpSearchGobj(0x1E0)->f16C = 1;
    scpSearchGobj(0x1E1)->f16C = 0;
}
extern int scpTriggerFloorAttr(int a0, int a1);

void actSt47aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOff(0x187);
    _ACTWait(1);
    gflagOn(0x34);
    gflagOn(0x35);
}
extern void WakeupHint(int a0);

void actSt47aHint2OnChk(volatile int a0)
{
    while (gflagChk(0x2F) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x36);
    WakeupHint(5);
}
