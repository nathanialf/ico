#include "matching.h"

extern void func_0014BD88(int *self);
extern void func_00145638(int *self);
extern void func_0014BC30(int *a, int b, int c);

void func_0014B1D0(int *self)
{
    int *q = (int *)self[0x59];
    int *p;
    func_0014BD88(self);
    func_00145638(self);
    p = (int *)self[0x59];
    func_0014BC30((int *)p[0x19E], q[0x24], 0);
    q[0x25] = q[0x24];
}
