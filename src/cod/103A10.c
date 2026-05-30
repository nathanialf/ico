#include "matching.h"
#include "regpin.h"
extern int func_0013FF88(int *self, int a, int b);
int func_00203A10(int *self, int a1, int a2)
{
    register int *a3_save REG("$7") = self;
    register int t0_save REG("$8") = a1;
    register int a1_arg REG("$5") = a2;
    int *p = (int *)a3_save[0x164 / 4];
    if (p[0x12C / 4] != 0) goto fail;
    *(volatile int *)&p[0x130 / 4] = a1_arg;
    *(volatile int *)&p[0x12C / 4] = (int)a3_save;
    func_0013FF88(a3_save, a1_arg, t0_save);
    return 1;
fail:
    return 0;
}
