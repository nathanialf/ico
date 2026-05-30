#include "matching.h"

extern int *D_00631AE4;
extern int D_00633FAC;
extern void func_0017B3F8(int *p, int n);
extern void func_0017E2E8(int *p);
extern void func_00203AA0(int x);

void func_00229D30(volatile int unused)
{
    func_0017B3F8(D_00631AE4, 0x1D0);
    func_0017E2E8(D_00631AE4);
    func_0017B3F8(D_00631AE4, 0x1D1);
    func_0017E2E8(D_00631AE4);
    D_00633FAC = 1;
    func_00203AA0(0);

}
