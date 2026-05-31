extern int func_0017E188(int a0);
extern void func_0012AC70(int *a0, int *buf);

#include "regpin.h"

void func_0017CB20(int a0, int *a1)
{
    int v = func_0017E188(a0);
    if (v != 0) {
        int buf[2];
        register int *bufp REG("$5") = buf;
        buf[0] = v;
        buf[1] = 0;
        func_0012AC70(a1, bufp);
    }
}
