#include "matching.h"

#include "regpin.h"

extern float D_00631884;
extern float D_00631888;
extern float D_0063188C;

int func_0023D0C8(int *self)
{
    float *p = (float *)self[0xD];
    register float a REG("$f1") = D_00631884;
    register float b REG("$f2") = D_00631888;
    register float c REG("$f0") = D_0063188C;
    p[0] = a;
    p[1] = b;
    p[2] = c;
    return 1;
}

TRAILING_PAD_NOP();
