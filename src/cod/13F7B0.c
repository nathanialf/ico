#include "matching.h"
#include "regpin.h"

int *func_0023F7B0(int *a0, long long a1)
{
    register int *ret REG("$2");
    __asm__ ("dsll32 %0, %0, 0" : "+r"(a1));
    __asm__ ("dsrl32 %0, %0, 0" : "+r"(a1));
    a0[2] = 0x53;
    __asm__ ("dsll32 %0, %0, 0" : "+r"(a1));
    __asm__ volatile("dsra32 %0, %0, 0" : "+r"(a1));
    ret = a0 + 4;
    KEEP_LIVE(ret);
    __asm__ volatile("sw %1, 0(%0)" : : "r"(a0), "r"(a1) : "memory");
    __asm__ volatile("sw $0, 0x4(%0)" : : "r"(a0) : "memory");
    __asm__ volatile("sw $0, 0xC(%0)" : : "r"(a0) : "memory");
    return ret;
}

TRAILING_PAD_NOP();
