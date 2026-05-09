#include "matching.h"

void func_001A9D90(int a0)
{
    *(volatile int *)0x10000800 = 0;
    *(volatile int *)0x10000810 = a0 | 0x80;
    NOP();
}
