#include "regpin.h"
extern int D_00550864[];
extern int func_00100520(int *buf);

void func_00247088(void)
{
    register int *base;
    register int one REG("$2");
    int v;
    int buf[8];
    base = D_00550864;
    v = base[0];
    if (v != -1) return;
    one = 1;
    *(volatile int *)(buf + 5) = 0;
    *(volatile int *)(buf + 1) = one;
    *(volatile int *)(buf + 2) = one;
    base[0] = func_00100520(buf);
}
