#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Init);

int dl_Clear(void) {
    return 0x14;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Swap);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_PushPriority);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_PopPriority);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Debug);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_CloseDma);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_Out);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_SetDLPriority);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_OpenDma);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", dl_GetPri);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayList", func_001F8660);
