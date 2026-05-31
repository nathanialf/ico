#include "matching.h"
#include "regpin.h"

int *func_0023F598(int *a0, long long a1, long long a2)
{
    register int *ret REG("$2");
    register int v1_const;
    __asm__ ("dsll32 %0, %0, 0" : "+r"(a1));
    __asm__ ("dsll32 %0, %0, 0" : "+r"(a2));
    __asm__ ("dsrl32 %0, %0, 0" : "+r"(a1));
    v1_const = 0x18;
    __asm__ ("or %0, %1, %0" : "+r"(a2) : "r"(a1));
    ret = a0 + 4;
    __asm__ ("dsll32 %0, %0, 0" : "+r"(a1));
    __asm__ volatile("dsra32 %0, %0, 0" : "+r"(a1));
    __asm__ volatile("dsra32 %0, %0, 0" : "+r"(a2));


    __asm__ volatile("sw %1, 0(%0)" : : "r"(a0), "r"(a1) : "memory");
    __asm__ volatile("sw %1, 4(%0)" : : "r"(a0), "r"(a2) : "memory");
    __asm__ volatile("sw %1, 8(%0)" : : "r"(a0), "r"(v1_const) : "memory");
    __asm__ volatile("sw $0, 0xC(%0)" : : "r"(a0) : "memory");
    return ret;
}
