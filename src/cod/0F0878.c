#include "regpin.h"

extern void func_00105F00(int p, int q);
extern char D_00275850[];

void func_001F0878(int *self)
{
    register int one REG("$17") = 1;
    register int *p REG("$2");
    volatile int pad;
    p = (int *)self[0x57];
    p[0x11C] = -1;
    p = (int *)self[0x57];
    p[0x198] = one;
    func_00105F00((int)((char *)((int *)self[0x57]) + 0x670), (int)D_00275850);
    p = (int *)self[0x57];
    p[0x154] = one;
}
