#include "common.h"

#include "debug_exception_screen.c.inc"

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
