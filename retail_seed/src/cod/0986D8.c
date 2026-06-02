#include "matching.h"

extern void func_002439B0(int *buf);
extern int func_00198438(int a0, int *buf);

int func_001986D8(int a0)
{
    int buf[16];
    func_002439B0(buf);
    return func_00198438(a0, buf);
}

TRAILING_PAD_NOP();
