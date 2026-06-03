#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Init);

int dl_Clear(void) {
    return 0x14;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Swap);

extern int D_0062BAE0, D_0062BAE4, D_0062BAE8, D_0062BAEC, D_0062BAF0;

void dl_PushPriority(void) {
    D_0062BAE0 = 0;
    D_0062BAF0 = 0x80;
    D_0062BAEC = 0x80;
    D_0062BAE8 = 0x80;
    D_0062BAE4 = 0x80;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_PopPriority);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Debug);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_CloseDma);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Out);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_SetDLPriority);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_OpenDma);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_GetPri);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", func_001F8660);
