#include "regpin.h"

extern int D_00632108;
extern int D_00631950;
extern void func_00100F18(int x, int *p);

int func_0013A820(int a0)
{
    if (a0 == 2) {
        register unsigned long long v REG("$3") = *(volatile unsigned long long *)0x12001000;
        register int *p REG("$5") = (int *)D_00632108;
        D_00631950 = ((v >> 13) & 1) ^ 1;
        func_00100F18(p[0xC], p);
    }
    return 0;
}
