#include "regpin.h"
void func_00251D70(int *self, long long a1)
{
    char *p = (char *)self[0x10];
    register int one = 1;
    *(int *)(p + 0x70) = one;
    *(long long *)(p + 0x78) = a1;
}
