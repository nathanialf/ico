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
extern void scpTorchLightOff(int a0);
extern void DeleteLayoutedCandleParticleEffect(void);
extern PObjGObj *scpSearchGobj(int a0);
extern void gflagOn(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);

INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aInit);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aEnd);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aChanChk);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aChanEffect);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aTsuroChk);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aTsuroEffect);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aSekizoChk);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aEne);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st07a", actSt07aGene1);
extern void actSt07aChanChk(volatile int a0);
extern ActMail D_004F9F60[];

void actSt07aChan(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x7E) != 0) {
        DeleteLayoutedCandleParticleEffect();
        if (gflagChk(0x80) != 0) {
            scpTorchLightOff(0x1AF);
            scpTorchLightOff(0x1B0);
        }
    } else {
        scpTorchLightOff(0x1AF);
        scpTorchLightOff(0x1B0);
        D_004F9F60[0].func = actSt07aChanChk;
        self->mail = D_004F9F60;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void actSt07aChanReadyChk(volatile int a0);
extern ActMail D_004F9F20[];

void actSt07aChanReady(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x7E) == 0) {
        D_004F9F20[0].func = actSt07aChanReadyChk;
        self->mail = D_004F9F20;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void actSt07aChanChainChk(volatile int a0);
extern ActMail D_004F9F40[];

void actSt07aChanChain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x7F) == 0) {
        D_004F9F40[0].func = actSt07aChanChainChk;
        self->mail = D_004F9F40;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x1C6)->f16C = 0;
    }
}
extern void actSt07aTsuroChk(volatile int a0);
extern ActMail D_004F9F80[];

void actSt07aTsuro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x80) == 0) {
        D_004F9F80[0].func = actSt07aTsuroChk;
        self->mail = D_004F9F80;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        gflagOn(0x85);
    }
}
extern void actSt07aIntroChk(volatile int a0);
extern ActMail D_004F9FA0[];

void actSt07aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x81) == 0) {
        D_004F9FA0[0].func = actSt07aIntroChk;
        self->mail = D_004F9FA0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void actSt07aSekizoChk(volatile int a0);
extern ActMail D_004F9FC0[];

void actSt07aSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x82) == 0) {
        stage_SetAnimation(0x16A, 0, 0);
        D_004F9FC0[0].func = actSt07aSekizoChk;
        self->mail = D_004F9FC0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x16A, 0, -1);
    }
}
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt07aGene2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x84) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actSt07aGene3(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x84) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}
extern void actSt07aEne2Chk(volatile int a0);
extern ActMail D_004FA000[];

void actSt07aEne2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x86) == 0) {
        D_004FA000[0].func = actSt07aEne2Chk;
        self->mail = D_004FA000;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt07aGene2_1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x87) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
void actSt07aGene2_2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x87) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actSt07aGene2_3(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x87) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
}
extern int D_00639EA4;
extern int bridge;
extern int scpTriggerFloorAttr(int a0, int a1);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);

void actSt07aChanReadyChk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) { _ACTWait(1); }
    scpAdpcmPlayRequestFunc(0x3B, &bridge, 1, 1, 0);
}
extern int GetAttackCheckBoundaryManagerStatus(PObjGObj *a0);
extern int scpGameStat_BoyWeaponkind(void);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);

void actSt07aChanChainChk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0x7F) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x1C6))) {
        case 1:
            if (scpGameStat_BoyWeaponkind() != 0) {
                gflagOn(0x7F);
                soundSeDefPlay(0x36E, 0, 0, 1);
                _ACTWait(0x1E);
                scpSearchGobj(0x1C6)->f16C = 0;
            }
        case 0:
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x1C6)->f16C = 0;
            gflagOn(0x7F);
            break;
        }
    }
}
void actSt07ChanEvent(int x) {
    volatile int local = x;
}
extern void scpTorchLightOn(int a0);

void actSt07aChanFall(volatile int a0)
{
    stage_SetAnimation(0x164, 1, 0);
    _ACTWait(5);
    stage_SetAnimation(0x163, -1, -2);

    while (stage_CheckAnimationFinish(0x164) == 0) { _ACTWait(1); }

    _ACTWait(1);
    DeleteLayoutedCandleParticleEffect();
    _ACTWait(0x78);
    scpTorchLightOn(0x1AF);
    scpTorchLightOn(0x1B0);
    _ACTWait(0);
}
extern void scpPlayMot(int a0, int mot);
extern void scpPlayWaitMotEnd(int a0);
extern int D_0063C560;

void actSt07aChanMot(volatile int a0)
{
    scpPlayMot(D_00639EA4, 0x1DA);
    scpPlayWaitMotEnd(D_00639EA4);
    scpPlayMot(D_00639EA4, 0x1DB);
    scpPlayWaitMotEnd(D_00639EA4);

    D_0063C560 = 1;
    _ACTWait(0);
}
extern long long D_00622C70[];
extern int D_00639EA8;
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);

void actSt07aChanWay1(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_00622C70[0];
    buf[1] = D_00622C70[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}
extern long long D_00622C80[];

void actSt07aChanWay2(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_00622C80[0];
    buf[1] = D_00622C80[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}
void actSt07TsuroEvent(int x) {
    volatile int local = x;
}
extern void SetCameraFlag_LwsCutBack(void);

void actSt07aTsuroConte(volatile int a0)
{
    stage_SetAnimation(0x165, 1, 0);
    stage_SetAnimation(0x166, 1, 0);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(0x166) == 0) { _ACTWait(1); }

    _ACTWait(1);

    D_0063C560 = 1;
    _ACTWait(0);
}
extern long long D_00622C90[];

void actSt07aGirlWay(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_00622C90[0];
    buf[1] = D_00622C90[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}
void actSt07aCamera2(int x) {
    volatile int local = x;
}
extern int scpTriggerBall(int a0, int a1, float radius);
extern void lt_switch_layout(int a0);
extern int D_0063AA08;

void actSt07aIntroChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) { _ACTWait(1); }

    lt_switch_layout(0x37);
    gflagOn(0x81);

    D_0063AA08 = 1;
    _ACTWait(1);

    stage_SetAnimation(0x161, 1, 0);
    while (stage_CheckAnimationFinish(0x161) == 0) { _ACTWait(1); }
    _ACTWait(1);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}
void actSt07aSekizoEvent(int x) {
    volatile int local = x;
}
extern void gflagOff(int a0);

void actSt07aEne2Chk(volatile int a0)
{
    if (D_00639EA8 == 0) { _ACTWait(0); }

    while (gflagChk(0xAE) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    gflagOff(0x187);
    gflagOn(0x86);
    gflagOn(0x87);
}
