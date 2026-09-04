#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bInit);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bFloorChkSub);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bFloorChk);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bSekizo);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEne);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy1);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy2);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy3);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy4);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy5);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy6);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bFloor);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bWay);
void actSt01bEnd(void) {}
void actSt01bSekizoEvent(int x) {
    volatile int local = x;
}
void actSt01bFloorEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bWayOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bWayOffChk);
