#include "matching.h"
#include "regpin.h"

extern float D_0063184C;
extern float D_00631850;

int func_0023CCB8(char *a0)
{
    float *v1 = *(float **)(a0 + 0x34);
    register int rv REG("$2") = 1;
    register float f1 __asm__("$f1");
    register float f2 __asm__("$f2");
    register float f0 __asm__("$f0");
    KEEP_LIVE(rv);
    f1 = -133.0f;
    f2 = D_0063184C;
    f0 = D_00631850;
    KEEP_LIVE_FP(f1);
    KEEP_LIVE_FP(f2);
    KEEP_LIVE_FP(f0);
    __asm__ volatile("swc1 %1, 0x0(%0)" : : "r"(v1), "f"(f1) : "memory");
    __asm__ volatile("swc1 %1, 0x8(%0)" : : "r"(v1), "f"(f0) : "memory");
    __asm__ volatile("swc1 %1, 0x4(%0)" : : "r"(v1), "f"(f2) : "memory");
    return rv;
}
