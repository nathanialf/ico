#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aEne1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aEne2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aDoorUp);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aDoor);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aEne1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aEne2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st08a", actSt08aEnemy1);

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
