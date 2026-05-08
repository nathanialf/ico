#include "matching.h"

extern void func_00202208(unsigned int a0);
extern void func_00203AA0(int a0);
extern void func_001297A0(int a0, int a1, int a2);

void func_002189E0(volatile unsigned int a0)
{
    volatile int local;
    int x = a0;
    VOLATILE_RELOAD_CALL(a0, func_00202208);
    func_00203AA0(1);
    func_001297A0(0xDD, 0, 0);
}
