#include "matching.h"

extern void func_0010D530(int *p);

void func_0010A3A0(int *a0, int count)
{
    int *p;
    int i;
    if (count <= 0) return;
    p = a0;
    i = count;
    p[0] = 0;
    do {
        int *call_arg = p + 4;
        p += 8;
        func_0010D530(call_arg);
        --i;
        if (i != 0) p[0] = 0;
    } while (i != 0);
}
