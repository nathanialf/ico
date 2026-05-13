#include "matching.h"
#include "regpin.h"

extern int D_00632D30;
extern char D_006D0680[];

void func_0018CF80(long long *a0, float *a1)
{
    register float f REG("$f0") = (float)D_00632D30;
    register char *base REG("$6") = D_006D0680;
    *a0 = *(long long *)&base[0];
    NOP();
    NOP();
    f /= 100.0f;
    *(a0 + 1) = *(long long *)&base[8];
    *(a0 + 2) = *(long long *)&base[16];
    *(a0 + 3) = *(long long *)&base[24];
    *a1 = f;
}
