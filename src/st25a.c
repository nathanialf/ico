#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenAppearChk);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte11);
ASM_LIT4_SLOT(D_006390D4, 0.99f);
ASM_LIT4_SLOT(D_006390D8, 0.1f);
ASM_LIT4_SLOT(D_006390DC, 0.8f);
ASM_LIT4_SLOT(D_006390E0, 0.45f);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenTalkChk);
ASM_LIT4_SLOT(D_006390E4, 625.0f);
ASM_LIT4_SLOT(D_006390E8, 1650.0f);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte12);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte12Jimaku);
ASM_LIT4_SLOT(D_006390EC, 4200.0f);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenDeadChk);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actConte13Jimaku);
ASM_LIT4_SLOT(D_006390F0, 3100.0f);
extern char D_005549D0[];
extern void tex_SetUVScroll(void *a0, float f12, float f13, float f14, float f15, float f16, float f17, int a1);

void BoySekikaTexScroll(void) {
    tex_SetUVScroll(D_005549D0, 0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.5f, 1);
}
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
ASM_LIT4_SLOT(D_006390F8, 1500.0f);
INCLUDE_ASM("asm/nonmatchings/src/st25a", actSt25aQueenDeadReadyChk);
void actSt25aQueenDeadEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st25a", func_00187DF0);
ASM_LIT4_SLOT(D_006390FC, 0.99f);
ASM_LIT4_SLOT(D_00639100, 0.001f);
ASM_LIT4_SLOT(D_00639104, 0.01f);
