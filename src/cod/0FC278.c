#include "matching.h"
#include "regpin.h"

extern void func_001A6E28(char *fmt, ...);
extern char D_0061AC80[];
extern int *D_006321D8;

void func_001FC278(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 REG("$9") = self;
    int v34, v44;
    if (t0 == 0) {
        func_001A6E28(D_0061AC80);
        return;
    }
    MATERIALIZE(t1);
    t1[0x13] = a2;
    t1[0x14] = a3;
    t1[0x12] = a1;
    *((unsigned char *)t1 + 0x40) = *((unsigned char *)t0 + 0x40);
    t1[0xE] = (int)t0;
    v34 = t0[0xD];
    v44 = t0[0x11];
    t1[0xD] = v34;
    t0[0xD] = (int)t1;
    t1[0x11] = v44;
    if (t1[0xD] == 0) {
        D_006321D8 = t1;
    }
}
