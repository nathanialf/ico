#include "ico/types.h"
extern int func_0010ECB8(int a0);
extern void func_0010ECA0(int a0);

void func_001C2DF8(int a0)
{
    int s0 = *(int *)((int)((GObj *)(a0))->p_15C + 0x800);
    func_0010ECB8(a0);
    func_0010ECA0(*(int *)s0);
}
