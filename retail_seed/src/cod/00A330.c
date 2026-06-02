#include "ico/types.h"
extern float func_00168C18(int *p, int *q);

float func_0010A330(int *a, int *b)
{
    int *pa;
    int *pb;
    float r1;
    float r2;
    pa = (int *)((GObj *)(a))->p_15C;
    r1 = func_00168C18((int *)((char *)pa + 0x1D0), (int *)((char *)pa + 0xA0));
    pb = (int *)((GObj *)(b))->p_15C;
    r2 = func_00168C18((int *)((char *)pb + 0x1D0), (int *)((char *)pb + 0xA0));
    return r1 - r2;
}
