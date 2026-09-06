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
} PObjGObj;

extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bInit);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bFloorChkSub);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bFloorChk);
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4,
                       float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt01bSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x41, 0xB2, 0, 0x12,
               1000.0f, 528.0f, -150.0f,
               1000.0f, 528.0f, -100.0f);
}
extern void actSt01bEneChk(volatile int a0);
extern ActMail D_004F7FB0[];

void actSt01bEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x44) == 0) {
        D_004F7FB0[0].func = actSt01bEneChk;
        self->mail = D_004F7FB0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt01bEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x74);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actSt01bEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x64);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actSt01bEnemy3(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x82);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actSt01bEnemy4(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x73);
    Generator_Call(a0);
}
void actSt01bEnemy5(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x7D);
    Generator_Call(a0);
}
void actSt01bEnemy6(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x6E);
    Generator_Call(a0);
}
extern void actSt01bFloorChk(volatile int a0);
extern ActMail D_004F7FD0[];

void actSt01bFloor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x46) == 0) {
        D_004F7FD0[0].func = actSt01bFloorChk;
        self->mail = D_004F7FD0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern void actSt01bWayOnChk(volatile int a0);
extern ActMail D_004F7FF0[];

void actSt01bWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F7FF0[0].func = actSt01bWayOnChk;
    self->mail = D_004F7FF0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt01bEnd(void) {}
void actSt01bSekizoEvent(int x) {
    volatile int local = x;
}
void actSt01bFloorEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bWayOnChk);
extern int D_00639EA8;
extern int scpTriggerFloorAttr(int a0, int a1);
extern void SetWayGroupActive(int a0, int a1);
extern ActMail D_004F8030[];

void actSt01bWayOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0 ||
           gflagChk(0x46) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 0);

    D_004F8030[0].func = actSt01bWayOnChk;
    sub->mail = D_004F8030;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
