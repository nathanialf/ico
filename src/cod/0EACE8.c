#include "ico/types.h"
extern int D_006335E0[];
extern void func_001AE460(int *self);
extern void func_001A6E28(int *a0, int a1);

void func_001EACE8(int *self) {
    Sub15C *p = ((int *)((GObj *)(self))->p_15C)[0x800/4];
    p->f_3C = 1;
    func_001AE460(self);
    func_001A6E28(D_006335E0, self[0x8/4]);
}
