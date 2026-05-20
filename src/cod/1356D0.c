#include "regpin.h"

extern int D_00631AE4;
extern void func_0017CD18(float, float, float, float, float, float);
extern void func_00203AA0(int x);

void func_002356D0(volatile int unused)
{
    register int a1 REG("$5");
    register int *v0 REG("$2");
    register int one_v REG("$3");

    a1 = D_00631AE4;
    one_v = 1;
    v0 = *(int * volatile *)(a1 + 0x15C);
    v0[0x4E8 / 4] = one_v;
    v0 = *(int * volatile *)(a1 + 0x15C);
    v0[0x4E8 / 4] = 0;
    func_0017CD18(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    func_00203AA0(60);
}
