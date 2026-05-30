#include "ico/types.h"
extern void func_00105F00(int a, int b);

void func_001F3308(int *self, int a1, int a2, int a3)
{
    int *p = (int *)((int *)((GObj *)(self))->p_15C)[0x800 / 4];
    func_00105F00(a1, (int)((char *)p + 0x20));
    func_00105F00(a2, (int)((char *)p + 0x30));
    func_00105F00(a3, (int)((char *)p + 0x40));
}
