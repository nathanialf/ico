#include "matching.h"

extern void func_001CE768(int self, int flag);

void func_0015F650(int self)
{
    volatile int s = self;
    char *sub;
    char *sub2;
    sub = *(char **)((char *)s + 0x164);
    *(long long *)(sub + 0x20) |= 1LL;
    func_001CE768(s, 1);
    sub2 = *(char **)((char *)s + 0x15C);
    *(int *)(sub2 + 0x654) = 0;
}
