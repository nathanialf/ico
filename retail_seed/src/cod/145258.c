#include "matching.h"

void func_00245258(int *q)
{
    int *p = (int *)q[0];
    int new_p = (int)p + 0x10;
    __asm__ __volatile__("sq $5, 0(%0)" : : "r"(p) : "memory");
    q[0] = new_p;
    __asm__ __volatile__("" : : : "memory");
    q[5] = (int)p;
}
