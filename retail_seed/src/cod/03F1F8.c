#include "matching.h"

extern void func_001A6E28(char *fmt, ...);
extern char D_00557A58[];
extern int D_00281AD0[];

void func_0013F1F8(int *self, int *a1, int a2, int *a3)
{
    int *t0;
    int v34, v44;
    if (a1 == 0) return;
    t0 = self;
    if (a3 == 0) {
        func_001A6E28(D_00557A58);
        return;
    }
    t0[0x14] = a2;
    t0[0x12] = (int)a1;
    *((unsigned char *)t0 + 0x40) = *((unsigned char *)a3 + 0x40);
    t0[0xE] = (int)a3;
    v34 = a3[0xD];
    v44 = a3[0x11];
    t0[0xD] = v34;
    a3[0xD] = (int)t0;
    t0[0x11] = v44;
    if (t0[0xD] == 0) {
        D_00281AD0[*((unsigned char *)t0 + 0x40)] = (int)t0;
    }
}
