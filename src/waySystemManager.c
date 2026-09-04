#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", CreateWaySystemManagerGObj);
INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", RequestGetWayBegin);
extern int func_0017D5D0();

void actWaySystemCore(volatile unsigned int self)
{
    int *s = (int *)((int *)self)[0x20 / 4];
    int v;
    v = func_0017D5D0((int)((char *)s + 0x10), (int)((char *)s + 0x20), (int)((char *)s + 0xA0), 1);
    s[0x4 / 4] = v;
    s[0] = 1;
    s[0xB0 / 4] = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/waySystemManager", func_00200BA0);
