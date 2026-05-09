#include "regpin.h"
extern void func_001BC0A8(void);

void func_001C0870(int *self, int x)
{
    register int *t REG("$2");
    int *q;
    register int v REG("$3");
    t = (int *)self[0x15C/4];
    q = (int *)t[0x800/4];
    v = q[0x4/4];
    if (v != x) {
        func_001BC0A8();
    }
    q[0x4/4] = x;
}
