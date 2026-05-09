#include "matching.h"

extern void func_001B7FE8(int a, int b, int c, int d, int e, int f, int g, int h);
extern int D_00623468[];

void func_001BA770(int *self)
{
    int *entry = (int *)((char *)D_00623468 + (self[0x30 / 4] * 32));
    func_001B7FE8(0x3D, entry[0xC / 4], -1, 0, (int)self, -1, 7, 1);
    DEFEAT_TCO();
}
