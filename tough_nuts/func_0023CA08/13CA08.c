#include "regpin.h"

extern float D_0063183C;
extern float D_00631840;

int func_0023CA08(int *self)
{
    float *p = (float *)self[0xD];
    register float a REG("$f3") = 1800.0f;
    register float b REG("$f2") = D_0063183C;
    register float c REG("$f0") = D_00631840;
    register float one REG("$f1") = 1.0f;
    p[2] = c;
    p[0] = a;
    p[1] = b;
    *(float *)((char *)self + 0x18) = one;
    return 1;
}
