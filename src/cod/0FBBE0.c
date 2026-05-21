#include "matching.h"
#include "regpin.h"

extern int D_004C7710[];

void func_001FBBE0(void)
{
    register int *full REG("$5") = D_004C7710;
    register int flag REG("$3");
    register int offset REG("$2");
    int next;
    flag = D_004C7710[0];
    flag ^= 1;
    D_004C7710[0] = flag;
    offset = flag * 4;
    KEEP_LIVE(full);
    __asm__("addu %0, %1, %2" : "+r"(offset) : "r"(full));
    next = *(int *)((char *)offset + 4);
    full[5] = 0;
    full[6] = 0;
    full[4] = next;
    full[7] = 0;
}
