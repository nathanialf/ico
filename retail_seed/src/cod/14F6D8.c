#include "matching.h"

extern int D_005523D0[];
extern void *func_0024F5A0(int a0, int a1, int a2, int a3);

void *func_0024F6D8(int a0, int a1, int a2)
{
    void *p = func_0024F5A0(a0, a1, a2, 0x40);
    if (p == 0) {
        D_005523D0[0] = 0xB;
    }
    return p;
}

TRAILING_PAD_NOP();
