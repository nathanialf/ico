#include "common.h"


extern int D_00633F70;
void dpk_SwapBuffer(int a0)
{
    if (a0 < 0) {
        D_00633F70 = 0;
    } else if (a0 >= 0xD) {
        D_00633F70 = 0xC;
    } else {
        D_00633F70 = a0;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/DmaPacket", dpk_Init);

int dpk_CheckBufferSize(void) {
    return D_00633F70;
}

INCLUDE_ASM("asm/nonmatchings/src/DmaPacket", func_001FBB48);

INCLUDE_ASM("asm/nonmatchings/src/DmaPacket", func_001FBBE0);

