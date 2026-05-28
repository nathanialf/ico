#include "matching.h"
#include "regpin.h"

extern void func_00243AE8(void *dst, int a0, int a1);
extern void func_00243978(void *dst, void *src);
extern int func_00194508(void *buf, int a2);

int func_00194840(int a0, int a1, int a2, int a3)
{
    int buf[8];
    register int sa2 REG("$16") = a2;
    register int sa3 REG("$17") = a3;
    int r;
    func_00243AE8(&buf[4], a0, a1);
    buf[5] = 0;
    func_00243978(&buf[0], &buf[4]);
    r = func_00194508(&buf[0], sa2);
    return __builtin_abs(r) < sa3;
}
