#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", font_CheckAlign);
INCLUDE_ASM("asm/nonmatchings/src/DisplayFont", font_Print);
int font_GetWidth(void)
{
    return 0x14;
}
extern int D_0063A064;

int font_GetHeight(void) {
    return (0x3200 / D_0063A064) / 2;
}
extern int D_0063BD00;
extern int D_0063BD04;
extern int D_0063BD08;
extern int D_0063BD0C;
extern int D_0063BD10;

void font_Init(void) {
    D_0063BD00 = 0;
    D_0063BD10 = 0x80;
    D_0063BD0C = 0x80;
    D_0063BD08 = 0x80;
    D_0063BD04 = 0x80;
}
