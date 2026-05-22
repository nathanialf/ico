#include "matching.h"
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
    {
        register float f1 REG("$f12") = 0.0f;
        register float f2 REG("$f13") = 0.0f;
        register float f3 REG("$f14") = 0.0f;
        register float f4 REG("$f15") = 0.0f;
        register float f5 REG("$f16") = 0.0f;
        register float f6 REG("$f17") = 100.0f;
        KEEP_LIVE_FP(f2);
        KEEP_LIVE_FP(f3);
        KEEP_LIVE_FP(f4);
        KEEP_LIVE_FP(f5);
        v0 = *(int * volatile *)(a1 + 0x15C);
        v0[0x4E8 / 4] = 0;
        func_0017CD18(f1, f2, f3, f4, f5, f6);
    }
    func_00203AA0(60);
}
