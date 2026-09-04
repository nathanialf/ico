#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", initLineTraceTable);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", traceLine);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", dispSource);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", display);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugEEExceptionMain);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugIOPExceptionMain);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugExceptionInit);
void debugIOPExceptionInit(void) {}
void debug_assertMessage(char *file, int line, char *mes) {
    for (;;)
        ;
}
void debug_assert(char *file, int line) {
    for (;;)
        ;
}
extern void sceVif1PkInit();
extern void sceVif1PkReset();
extern void sceVif1PkCnt();
extern void sceVif1PkOpenDirectCode();
extern int D_0063B370;

void OpenVif1DirectPacket(void *packet) {
    sceVif1PkInit(packet, (D_0063B370 << 13) | 0x70000000);
    sceVif1PkReset(packet);
    sceVif1PkCnt(packet, 0);
    sceVif1PkOpenDirectCode(packet, 0);
    D_0063B370 = (D_0063B370 + 1) & 1;
}
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", SetPrimColor);
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", SetPrimColorTex);
