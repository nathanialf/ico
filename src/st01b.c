#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bInit);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEneChk);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bFloorChk);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bSekizo);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEne);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy1);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy2);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy3);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy4);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy5);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy6);

void actSt01bFloor(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bWay);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnd);

void actSt01bSekizoEvent(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bFloorEvent);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bWayOnChk);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bWayOffChk);

INCLUDE_ASM("asm/nonmatchings/src/st01b", func_00210DF0);

INCLUDE_ASM("asm/nonmatchings/src/st01b", func_00210F20);

INCLUDE_ASM("asm/nonmatchings/src/st01b", func_002110F0);

