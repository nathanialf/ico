#include "regpin.h"
#include "ico/types.h"
extern void func_00144240(int a0);

void func_001D12C0(int a0, int a1)
{
    register int p;
    p = (int)((GObj *)(a0))->p_15C;
    p += a1 * 4;
    func_00144240(*(int *)(p + 0x61C));
}
