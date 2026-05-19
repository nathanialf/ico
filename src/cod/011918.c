#include "matching.h"
#include "regpin.h"

extern int D_004C7710[];

void func_00111918(long long a0, long long a1)
{
    register long long *p REG("$3");
    register long long a1_out REG("$5");
    p = (long long *)D_004C7710[4];
    *p = a1;
    p++;
    D_004C7710[4] = (int)p;
    a1_out = (long long)(unsigned long)(p + 1);
    KEEP_LIVE(a1_out);
    __asm__ volatile("sd %1, 0(%0)" : : "r"(p), "r"(a0) : "memory");
    NOREORDER_BARRIER();
}
