#include "matching.h"
#include "regpin.h"

extern void func_0013A5B8(char *p, int *self, int zero, int neg2);
extern char D_00280F88[];

void func_00138218(int *self)
{
    register int *p REG("$3");
    long long v;
    p = self;
    p[1] = 0xD;
    v = *(long long *)p;
    *(long long *)p = v & -2LL;
    func_0013A5B8(D_00280F88, p, 0, -2);
    DEFEAT_TCO();
}
