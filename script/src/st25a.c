#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenAppear);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenAppearChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actConte11);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenTalkChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actConte12);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actConte12Jimaku);

extern void isysGObjAddHead(void);

void actSt25aQueenDeadChk(void) {
    isysGObjAddHead();
    /* ROM keeps a non-tail frame here (stripped debug code); block the sibcall */
    __asm__ __volatile__("");
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actConte13Jimaku);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", BoySekikaTexScroll);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aGenerator);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenBefore);

extern int D_0062C030;

void actSt25aQueenTalk(void) {
    D_0062C030 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenDead);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actItouQueenAttack);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSwordEff);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSwordEffXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenBeforeChk);

extern int D_0062BA78;
extern float D_0062BA7C;
extern int D_0062BA80;

void actConte11Jimaku(float a0) {
    D_0062BA78 = 1;
    D_0062BA7C = -a0;
    D_0062BA80 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actSt25aQueenDeadEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", actItouQueenAttackChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BCC0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BCE0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BD00);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BD40);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BE60);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BF18);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st25a", func_0017BF50);
