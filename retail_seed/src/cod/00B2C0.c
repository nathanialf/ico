#include "ico/types.h"
extern void func_00105F00(int a0, int a1);

void func_0010B2C0(int a0, int a1)
{
    func_00105F00(a0, *(int *)((int)((GObj *)(a1))->p_15C + 0x800) + 0x10);
}
