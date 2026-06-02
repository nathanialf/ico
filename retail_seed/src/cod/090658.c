#include "ico/types.h"
float func_00190658(int *self)
{
    int *p = (int *)((GObj *)(self))->p_15C;
    int *q = (int *)((Sub15C *)(p))->p_800;
    int n = q[0x74/4] - 1;
    return (float)n * 50.0f;
}
