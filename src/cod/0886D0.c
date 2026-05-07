#include "regpin.h"
extern char D_006D04B4[];
extern void func_0018CFE0(int a0);

void func_001886D0(int a0)
{
    register char *p REG("$2") = D_006D04B4;
    register int one REG("$3") = 1;
    int masked = a0 & 0xFF;
    *p = (char)one;
    if (masked == 0) {
        return;
    }
    return func_0018CFE0(masked);
}
