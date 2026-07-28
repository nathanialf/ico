#include "common.h"



extern void debug_assertMessage(char *fmt, ...);
extern int D_0061ABF0[];
extern int D_00710D10[];
extern int D_00633F70;
extern int D_00631C5C;
INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_Init);

int dl_Clear(void)
{
    return 0x14;
}

int dl_Swap(void) {
    return (0x3200 / D_00631C5C) / 2;
}

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_PushPriority);

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_PopPriority);

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_Debug);

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_CloseDma);

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_Out);

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_SetDLPriority);

void dl_OpenDma(void)
{
    int *entry = &D_00710D10[D_00633F70 * 10];
    unsigned int end = entry[9];
    unsigned int start = entry[1];
    unsigned int count = (end - start) >> 4;
    return debug_assertMessage(D_0061ABF0, count - 1);
}

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", dl_GetPri);

INCLUDE_ASM("asm/nonmatchings/src/DisplayList", func_001FB9F8);

