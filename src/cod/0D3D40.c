#include "ico/types.h"
int func_001D3D40(int *self)
{
    int *p = (int *)((GObj *)(self))->p_15C;
    int *q = (int *)((Sub15C *)(p))->p_800;
    int ret = 0;
    if (self[0x16C / 4] != 0) {
        if (*(long long *)((char *)q + 0x8) == 0) {
            ret = *(int *)((char *)q + 0x48) < 2;
        }
    }
    return ret;
}
