#include "ico/types.h"
int func_001D40A0(int *a0)
{
    int *sub = (int *)((int *)((GObj *)(a0))->p_15C)[0x800 / 4];
    return (sub[0] == 1) || (a0[0x16C / 4] == 0);
}
