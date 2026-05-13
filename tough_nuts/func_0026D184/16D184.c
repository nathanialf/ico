#include "matching.h"

extern int func_0026B548(int *self, int a1);

int func_0026D188(int *self)
{
    int *p;
    int i;
    if (self[117] != 0) return 0;
    p = (int *)func_0026B548(self, 0x80);
    self[117] = (int)p;
    if (p == 0) return -1;
    p = (int *)((char *)p + 0x7C);
    i = 0x1F;
    do {
        *p = 0;
        i--;
        p--;
        NOP();
    } while (i >= 0);
    return 0;
}
