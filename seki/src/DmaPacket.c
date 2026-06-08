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


int dpk_CheckBufferSize(void) {
    return D_0062C260;
}

extern int D_0062A314;
extern int D_004C3850[];
extern int iosFree(int handle, int size, char *file, int line);

extern char D_00613770[];

void func_001F87B0(void)
{
    D_004C3850[0] = 0;
    D_004C3850[1] = iosFree(D_0062A314, 0x80000, D_00613770, 0x86) | 0x30000000;
    D_004C3850[2] = iosFree(D_0062A314, 0x80000, D_00613770, 0x87) | 0x30000000;
    D_004C3850[4] = (D_004C3850 + D_004C3850[0])[1];
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DmaPacket", func_001F8848);
