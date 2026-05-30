#include "ico/types.h"
extern void func_001CE028(int a0, int a1, int a2, int a3);

void func_001F3368(int a0, int a1)
{
    int base = *(int *)((int)((GObj *)(a0))->p_15C + 0x800);
    func_001CE028(a1, base + 0x20, base + 0x30, base + 0x40);
}
