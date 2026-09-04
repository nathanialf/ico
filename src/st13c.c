#include "common.h"

void actSt13cInit(void) {
    if (gflagChk(0x15)) {
        SetWayGroupActive(9, 0);
    }
}
extern char D_00622E10[];
void actSt13cEnd(void) {
    if (gflagChk(0x1F) == 0) {
        debug_StdPrintfDummy(D_00622E10);
        gflagOn(0x186);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cBmg1);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cBmg1Chk);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cConte04);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cConte04Jimaku);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCage1stDownDemoCancel);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCage1stDown);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageFall);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageFallChk);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cConte05);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cConte05Jimaku);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageFallEffect);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cSekizoChk);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cGirlCarryChk);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cHandChk);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cHandJimaku);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cSleep);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageDown);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageFallReady);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cEnemy);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cEnemyNull);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cSekizo);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cSekizoJimaku);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cHand);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cGirlCarry);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cRescue);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cBuki);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actE3St13cSekizo);
void actSt13cBmg1Event(int x) {
    volatile int local = x;
}
void actSt13cSleepEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cSleepChk);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageDownMain);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCage1stDownDemo);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageFallReadyChk);
void actSt13cCageFallEvent(int x) {
    volatile int local = x;
}
void actE3St13cSekizoEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cSekizoJimakuChk);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cSekizoJimakuEff);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cGirlCarryAgainChk);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cHandSub);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cRescueChk);
void actSt13cBukiEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cBukiChk);
