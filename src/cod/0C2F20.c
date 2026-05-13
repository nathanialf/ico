#include "matching.h"

extern void *func_0013EB50(int a0);
extern int func_00105278(void);
extern void func_00105F20(int a0, int a1);
extern void func_001C22F0(void *a0, int a1, int a2);

void func_001C2F20(int *self)
{
    void *s0 = func_0013EB50(0x2B);
    if (s0 != 0) {
        int *p;
        int v;
        v = func_00105278();
        p = (int *)self[0x57];
        func_00105F20(v, p[3]);
        v = func_00105278();
        p = (int *)self[0x57];
        func_001C22F0(s0, v + 0x30, p[4]);
    }
}

TRAILING_PAD_NOP();
