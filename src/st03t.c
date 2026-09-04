#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchL);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchLChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchLUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchR);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchRChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSwitchRUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGene);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tBoxA);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tBoxB);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tInit);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGirlUp);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGirlCam);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tSekizo);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tWay);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tEne);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGirlPos);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tHint1Sleep);
void actSt03tGirlCamEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGirlCamStartChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGirlCamEndChk);
void actSt03tSekizoEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tWayOnChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tWayOffChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGirlPosChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tGirlUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tHint1OnChk);
INCLUDE_ASM("asm/nonmatchings/src/st03t", actSt03tHint1OffChk);
