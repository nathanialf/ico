#include "matching.h"

extern int D_00552370[];
extern void func_0024DD30(int a0, int a1, int a2, int a3, int t0);

void func_0024D9E8(int a0, int a1)
{
    D_00552370[0] = 1;
    func_0024DD30(a0, 0, 0, 1, a1);
    DEFEAT_TCO();
}
