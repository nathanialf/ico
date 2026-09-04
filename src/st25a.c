#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenAppearChk);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte11);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenTalkChk);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte12);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte12Jimaku);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenDeadChk);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte13Jimaku);
INCLUDE_ASM("asm/nonmatchings/src/st25a", BoySekikaTexScroll);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aElevChk);
extern void Generator_Mask(char *self);

void actSt25aGenerator(volatile unsigned int a0)
{
    Generator_Mask(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenBefore);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenTalk);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenDeadReady);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenDead);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actItouQueenAttack);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aElev);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSwordEff);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSwordEffXL);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenBeforeChk);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte11Jimaku);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenDeadReadyChk);
void actSt25aQueenDeadEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st25a", func_00187DF0);
