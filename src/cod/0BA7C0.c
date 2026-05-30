#include "ico/types.h"
extern int D_004BEA50[];

int func_001BA7C0(void *a0)
{
    int *p = ((GObj *)((char *)a0))->p_15C;
    int *q = ((Sub15C *)((char *)p))->p_800;
    return D_004BEA50[q[0x8 / 4]];
}
