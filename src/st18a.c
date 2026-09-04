#include "common.h"

extern char *D_00639EA8;
void actSt18aEnd(void) {
    if (D_00639EA8 != 0) {
        if (gflagChk(0x3D) == 0) {
            gflagOn(0x187);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aIntroChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchLChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchLUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchRChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchRUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aDoorChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aDoorDownChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aEnemy1_1);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aEnemy2_1);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aIntro);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aDoor);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchL);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchR);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aEne);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aEnemy1_2);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aEne2);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aEnemy2_2);
void actSt18aCamera(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aDoorChkSub);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aEneChk);
INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aEne2Chk);
