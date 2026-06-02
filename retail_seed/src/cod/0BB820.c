#include "matching.h"

extern int D_00633248[];
extern int D_004BEF60[];

int *func_001BB820(int *self)
{
    int *p = (int *)self[0x164 / 4];
    int idx;
    if (p != 0) {
        idx = p[0x30 / 4];
        if ((unsigned)idx < 6) goto array_ret;
    }
    return (int *)D_00633248;
array_ret:
    return (int *)D_004BEF60[idx];
}
