#include "ico/types.h"
int func_0010D338(int *a0, void *a1)
{
    void *p = ((GObj *)((char *)a1))->p_15C;
    void *q = *(void **)((char *)a0[0] + 0x15C);
    void *r = ((Sub15C *)((char *)q))->p_800;
    *(float *)((char *)p + 0x644) = *(float *)((char *)p + 0xA4) - *(float *)((char *)r + 0x4);
    return 1;
}
