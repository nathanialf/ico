#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/staffroll", staffRollStart);
INCLUDE_ASM("asm/nonmatchings/src/staffroll", staffRollScroll);
INCLUDE_ASM("asm/nonmatchings/src/staffroll", staffRollNameOut);
INCLUDE_ASM("asm/nonmatchings/src/staffroll", staffRollMain);
extern int D_004E4600[];
extern int staffRollAlpha;
extern int D_0063C42C;
extern float D_0063C430;
extern float D_0063C434;
extern int D_0063C438;

void staffRollWide(void)
{
    D_0063C438 = 1;
    D_0063C430 = (float)((D_004E4600[0] + 0x1400) / 30);
    D_0063C434 = (float)((D_0063C42C - 0x280) / 30);
    staffRollAlpha = 0xFF;
}
