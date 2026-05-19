#include "matching.h"
#include "regpin.h"

extern float D_0063183C;
extern float D_00631840;

int func_0023CA08(char *a0)
{
    float *v1 = *(float **)(a0 + 0x34);
    register int rv REG("$2") = 1;
    register float f3 __asm__("$f3");
    register float f2 __asm__("$f2");
    register float f0 __asm__("$f0");
    register float f1 __asm__("$f1");
    KEEP_LIVE(rv);
    f3 = 1800.0f;
    f2 = D_0063183C;
    f0 = D_00631840;
    f1 = 1.0f;
    KEEP_LIVE_FP(f3);
    KEEP_LIVE_FP(f2);
    KEEP_LIVE_FP(f0);
    KEEP_LIVE_FP(f1);
    __asm__ volatile("swc1 %1, 0x8(%0)" : : "r"(v1), "f"(f0) : "memory");
    __asm__ volatile("swc1 %1, 0x0(%0)" : : "r"(v1), "f"(f3) : "memory");
    __asm__ volatile("swc1 %1, 0x4(%0)" : : "r"(v1), "f"(f2) : "memory");
    __asm__ volatile("swc1 %1, 0x18(%0)" : : "r"(a0), "f"(f1) : "memory");
    return rv;
}
