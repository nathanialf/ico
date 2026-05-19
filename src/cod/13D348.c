#include "matching.h"
#include "regpin.h"

extern float D_006318A4;
extern float D_006318A8;

int func_0023D348(char *a0)
{
    float *v1 = *(float **)(a0 + 0x34);
    register int rv REG("$2") = 1;
    register float f2 __asm__("$f2");
    register float f0 __asm__("$f0");
    register float f1 __asm__("$f1");
    KEEP_LIVE(rv);
    f2 = D_006318A4;
    f0 = D_006318A8;
    f1 = 0.5f;
    KEEP_LIVE_FP(f2);
    KEEP_LIVE_FP(f0);
    KEEP_LIVE_FP(f1);
    __asm__ volatile("swc1 %1, 0x8(%0)" : : "r"(v1), "f"(f0) : "memory");
    __asm__ volatile("swc1 %1, 0x0(%0)" : : "r"(v1), "f"(f2) : "memory");
    __asm__ volatile("swc1 %1, 0x1C(%0)" : : "r"(a0), "f"(f1) : "memory");
    return rv;
}
