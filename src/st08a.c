#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aEnd);

INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aEne1Chk);

INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aEne2Chk);

INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aDoorUp);

INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aDoor);

INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aEne1);

INCLUDE_ASM("asm/nonmatchings/src/st08a", actSt08aEne2);

extern int D_00631AE4;
extern int D_00631AE8;
extern void _ACTWait(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float a3, float a4);
extern int func_0017B230(int a0);

void actSt08aEnemy1(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_0017B230(0xDA) == 0 || func_0017B230(0xDB) == 0 ||
           func_0017B230(0xDC) == 0 || func_0017B230(0xCF) == 0) {
        _ACTWait(1);
    }
    actSt25aQueenDead(8, D_00631AE4, D_00631AE8, 2.0f, 8.0f);
}

void actSt08aEnemy2(int x) {
    volatile int local = x;
}

void actSt08aEnemy3(int x) {
    volatile int local = x;
}

void actSt08aEnemy4(int x) {
    volatile int local = x;
}

void actSt08aIntro(int x) {
    volatile int local = x;
}

void actSt08aInit(int x) {
    volatile int local = x;
}

void actSt08aDoorMain(int x) {
    volatile int local = x;
}

void actSt08aDoorSwitch(int x) {
    volatile int local = x;
}

extern void AddWayPointTop(int a0, int a1);

void actSt08aIntroChk(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_0017B230(0xEA) == 0) {
        _ACTWait(1);
    }
    AddWayPointTop(3, 1);
}

INCLUDE_ASM("asm/nonmatchings/src/st08a", func_00223E98);

void func_00223EF0(int x) {
    volatile int local = x;
}

void func_00223F00(int x) {
    volatile int local = x;
}

void func_00223F10(int x) {
    volatile int local = x;
}

void func_00223F20(int x) {
    volatile int local = x;
}

void func_00223F30(int x) {
    volatile int local = x;
}

