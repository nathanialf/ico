#include "matching.h"

extern void func_00118FD8(int *p, int n);

void func_0011BF60(int *a0, int size)
{
    int count;
    int *p;
    size >>= 4;
    if (size <= 0) return;
    p = a0;
    count = size;
    do {
        func_00118FD8(p, 4);
        p += 4;
        count--;
    } while (count != 0);
}
