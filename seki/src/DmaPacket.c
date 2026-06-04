#include "common.h"

extern int D_0062C260;

void dpk_SwapBuffer(int a0) {
    if (a0 < 0) {
        D_0062C260 = 0;
    } else if (a0 >= 0xD) {
        D_0062C260 = 0xC;
    } else {
        D_0062C260 = a0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DmaPacket", dpk_Init);

extern int D_0062C260;

int dpk_CheckBufferSize(void) {
    return D_0062C260;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DmaPacket", func_001F87B0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DmaPacket", func_001F8848);
