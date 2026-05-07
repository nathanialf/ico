#include "regpin.h"
extern void func_0018D100(int a0);

int func_00190298(int a0)
{
    int s0 = *(int *)(*(int *)(a0 + 0x15C) + 0x800);
    func_0018D100(a0);
    {
        register int v REG("$2") = 1;
        *(signed char *)(s0 + 0x60) = v;
        return v;
    }
}
