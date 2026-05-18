#include "matching.h"

extern void func_0013CD30(void);
extern void func_0013CD70(void);
extern void func_0013D098(void);
extern int D_006321A8;

void func_0013CF38(int *a0)
{
    void (*fn1)(void) = func_0013CD30;
    void (*fn2)(void) = func_0013CD70;
    a0[0] = 0;
    if (fn1 != 0) {
        a0[1] = (int)fn1;
    } else {
        a0[1] = (int)func_0013D098;
    }
    a0[2] = (int)fn2;
    a0[3] = (int)&D_006321A8;
}

TRAILING_PAD_NOP();
