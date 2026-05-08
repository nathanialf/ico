#include "matching.h"

extern void func_00251ED0(int self);

void func_00251B80(int *self, unsigned int a1, int a2, int a3)
{
    int *p = (int *)self[0x40 / 4];
    int prod = a2 * a3;
    p[0xE0 / 4] = a3 << 4;
    p[0xD8 / 4] = (a1 & 0x0FFFFFFF) | 0x20000000;
    p[0xE4 / 4] = prod;
    p[0xDC / 4] = a2 << 4;
    p[0xB0 / 4] = 0;
    func_00251ED0((int)self);
    DEFEAT_TCO();
}
