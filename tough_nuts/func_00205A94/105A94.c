#include "regpin.h"

extern int D_004CAEC0[];

int func_00205A98(int *self)
{
    register int r REG("$4") = 0;
    int *p = (int *)((char *)D_004CAEC0 + self[8] * 0x34);
    if (self != 0) {
        r = self[3];
        if (r == p[2]) r = 0;
    }
    return r;
}
