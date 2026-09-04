#include "common.h"

extern char D_00621D40[];
extern void debug_StdPrintfDummy();

void setMailTarget(int a0, int *a1, int *a2)
{
    int v = *a2;
    if (v >= 0x10) {
        debug_StdPrintfDummy(D_00621D40);
        return;
    }
    *a2 = v + 1;
    a1[v] = a0;
}
INCLUDE_ASM("asm/nonmatchings/src/seMail", seMail);
INCLUDE_ASM("asm/nonmatchings/src/seMail", seMailTargetDistCheck);
