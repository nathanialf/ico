#include "ico/types.h"
float func_00190658(int *self)
{
    int *p = (int *)((GObj *)(self))->p_15C;
    int *q = (int *)p[0x800/4];
    int n = q[0x74/4] - 1;
    return (float)n * 50.0f;
}
