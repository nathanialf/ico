#include "matching.h"

extern void (*D_006323F4)(int a0, int a1);
extern int D_00633D34;

void func_001685B8(int a0, int a1)
{
    D_00633D34 = a1;
    D_006323F4(a0, 0x10);
    DEFEAT_TCO();
}
