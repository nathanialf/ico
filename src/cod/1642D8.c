#include "matching.h"

extern int *D_00553244[];
extern int func_00266970(int *target, int *caller, void *args);

int func_002642D8(int *a0, ...)
{
    int *p = (int *)D_00553244[0];
    void *args = (char *)__builtin_next_arg(a0) - 0x38;
    ((int *)p[2])[0x15] = (int)p;
    return func_00266970((int *)p[2], a0, args);
}
