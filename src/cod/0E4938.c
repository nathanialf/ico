#include "ico/types.h"
extern int D_00274ED4[];
extern void func_001D12C0(int a0, int a1);

int func_001E4938(int a0)
{
    if (D_00274ED4[0] != 0) {
        *(int *)((int)((GObj *)(a0))->p_15C + 0x628) = 0;
        func_001D12C0(a0, 1);
    }
    return 1;
}
