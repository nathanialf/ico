#include "matching.h"

extern void func_00143948(int x, int *p);
extern void func_00144308(int x);
extern void func_00141F58(int x, int y);
extern void func_001434B0(int *a, int *b);

void func_00144780(int *a, int *b)
{
    func_00143948(1, a);
    func_00143948(2, a);
    func_00144308(1);
    func_00141F58(1, 0);
    func_001434B0(a, b);
}
