#include "matching.h"

void func_0023EFB8(int x)
{
    *(volatile int *)0x1000A030 = x & 0x0FFFFFFF;
    *(volatile int *)0x1000A020 = 0;
    *(volatile int *)0x1000A000 = 0x105;
    NOP();
}
