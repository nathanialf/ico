#include "matching.h"

extern void (*D_006323F0)(int a0, int a1);
extern int D_00633D34;

void func_00168510(int a0, int a1)
{
    D_00633D34 = a1;
    D_006323F0(a0, 9);
    DEFEAT_TCO();
}
