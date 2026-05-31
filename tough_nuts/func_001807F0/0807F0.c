#include "matching.h"

extern void func_00202208(unsigned int a0);
extern void func_00203AA0(int a0);
extern void func_0017CB20(int a0, int a1);

void func_001807F0(volatile unsigned int a0)
{
    volatile int local;
    int x = a0;
    VOLATILE_RELOAD_CALL(a0, func_00202208);
    func_00203AA0(1);
    func_0017CB20(0x786, 0x1A7);
}

TRAILING_PAD_NOP();
