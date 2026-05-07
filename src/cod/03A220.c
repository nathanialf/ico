#include "regpin.h"
extern int func_00100540(int a0, int *a1);

void func_0013A220(int *a0)
{
    register int *v1 REG("$3") = a0;
    register int *a1 REG("$5") = (int *)v1[0x10 / 4];
    int v0;
    int new_a0;
    if (a1 == 0) {
        return;
    }
    v0 = a1[0x44 / 4];
    new_a0 = v1[0x2C / 4];
    v1[0x10 / 4] = v0;
    a1[0x44 / 4] = 0;
    return func_00100540(new_a0, a1);
}
