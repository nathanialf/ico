#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFloorChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rCageMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rTowerChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rTowerConte);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rChainMove);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFence);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFenceDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFenceUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFenceDownChk2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rFenceUpChk2);

void actSt10rFloor(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rCage);

extern int func_0025F4F0(int a0);
extern int func_0025EF78(int a0, long a1);
extern int func_0025F5A8(int a0);
extern void _ACTWait(int a0);
extern void func_00178DD8(int a0);
extern int D_00271240[];
void actSt10rTower(volatile int a0) {
    _ACTWait(func_0025F5A8(func_0025EF78(func_0025F4F0((0x3C - D_00271240[0] * 0xA) / D_00271240[1]), (long)0x8054 << 47)));
    func_00178DD8(0x5F);
}

void actSt10rExit(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rChain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10r", actSt10rEne);

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern int D_00629DE4;
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
void actSt10rEnemy1(volatile int a0) {
    while (func_00178DB0(0x5F) != 0 || scpSleepEnemyOne(a0, D_00629DE4, 400.0f) == 0) {
        _ACTWait(1);
    }
    actSt25aQueenDead(3, D_00629DE4, 0, 16.0f, 16.0f);
}

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
void actSt10rEnemy2(volatile int a0) {
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x65D), 200.0f) == 0 ||
           func_00178DB0(0x5F) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x61);
    *(int *)(actSt25aQueenDeadChk(0x65D) + 0x16C) = 0;
}

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern int func_00178DB0(int a0);

void actSt10rElv(volatile int a0) {
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x65D), 200.0f) == 0 ||
           func_00178DB0(0x5F) != 0) {
        _ACTWait(1);
    }
}

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern int func_00178DB0(int a0);
void actSt10rGateXL(volatile int a0) {
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x659), 200.0f) == 0 ||
           func_00178DB0(0x5F) != 0) {
        _ACTWait(1);
    }
    *(int *)(actSt25aQueenDeadChk(0x659) + 0x16C) = 0;
}
