#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aEne1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aEne2Chk);

void actSt08aDoorUp(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x94) != 0 && func_00178DB0(0xD1) == 0) {
        stage_KillPlayBgAnimation(0x139, 0, -1);
    }
    if (func_00178DB0(0x94) == 0 || func_00178DB0(0xD1) != 0) {
        stage_KillPlayBgAnimation(0x139, 0, 0);
    }
}

extern int D_0062A894;
extern int D_004CCA60[];

void actSt08aDoor(volatile int a0) {
    int s = *(int*)(a0 + 0x164);
    D_0062A894 = 0;
    *(int*)(s + 0xB0) = (int)D_004CCA60;
    while (1) {
        _ACTWait(1);
    }
}

typedef struct DoorSub {
    char pad[0xB0];
    void *field_B0;
    void *field_B4;
} DoorSub;

extern int D_004CCAA0[];
extern void actSt05eSolar(void);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", func_00220918);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aEne1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aEne2);

extern int D_00629DE4;
extern int D_00629DE8;
extern void actSt25aQueenDead(int a0, int a1, int a2, float a3, float a4);

void actSt08aEnemy1(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_00178DB0(0xDA) == 0 || func_00178DB0(0xDB) == 0 ||
           func_00178DB0(0xDC) == 0 || func_00178DB0(0xCF) == 0) {
        _ACTWait(1);
    }
    actSt25aQueenDead(8, D_00629DE4, D_00629DE8, 2.0f, 8.0f);
}

void actSt08aEnemy2(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aEnemy3(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aEnemy4(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aIntro(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aInit(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aDoorMain(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aDoorSwitch(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt08aIntroChk(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_00178DB0(0xEA) == 0) {
        _ACTWait(1);
    }
    AddWayPointTop(3, 1);
}

void func_00220BD0(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_00178DB0(0xEA) == 0 || func_00178DB0(0xEB) == 0) {
        _ACTWait(1);
    }
    AddWayPointTop(4, 1);
}

void func_00220C28(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00220C38(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00220C48(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00220C58(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00220C68(int a0) {
    int buf[4];
    buf[0] = a0;
}
