#include "regpin.h"

extern void func_001E3FC8(int *self);

void func_001CE6F0(int *self)
{
    register int *copy REG("$5");
    int *p;
    copy = self;
    p = (int *)copy[0x15C / 4];
    *(int *)((char *)p + 0x2B0) = 0;
    p = (int *)copy[0x15C / 4];
    *(int *)((char *)p + 0x310) = 0;
    p = (int *)copy[0x15C / 4];
    *(int *)((char *)p + 0x3B8) = 0;
    p = (int *)copy[0x15C / 4];
    *(int *)((char *)p + 0x3BC) = 0;
    func_001E3FC8(self);
}
