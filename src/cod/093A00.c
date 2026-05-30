#include "matching.h"
#include "ico/types.h"

extern void func_0013FF88(int *self, int x, int *self2);

int func_00193A00(int *self, short *p)
{
    Sub15C *q = ((int *)((GObj *)(self))->p_15C)[0x800/4];
    short v = p[0x30/2];
    q->f_50 = v;
    q->f_8 = p[0x32/2];
    if (v == 1) {
        q->f_54 = 2;
        func_0013FF88(self, 1, self);
    }
    return 1;
}

TRAILING_PAD_NOP();
