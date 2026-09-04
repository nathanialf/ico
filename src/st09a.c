#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aInit);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aElvDown);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aBrgDown);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aElv);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aSekizo);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aIntro);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aBrg);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aHint1);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aHint2);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aElvSwitch);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aElvUp);
void actSt09aSekizoEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aIntroChk);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aBrgMain);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aBrgDownSub);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aHint1Chk);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aHint2Chk);
