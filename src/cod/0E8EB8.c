#include "matching.h"

extern int D_00632010;
extern char D_00619EC0[];
extern int *func_0013A0F8(int x, int n, char *t, int line);
extern int func_001E8B48(int x, int *p, char *q);

int *func_001E8EB8(int *self, int *other)
{
    int *r;
    int *p_15c;
    r = func_0013A0F8(D_00632010, 0x4, D_00619EC0, 0xC);
    p_15c = (int *)self[0x15C/4];
    *r = func_001E8B48(other[0x30/4], other, (char *)p_15c + 0x60);
    return r;
}

TRAILING_PAD_NOP();
