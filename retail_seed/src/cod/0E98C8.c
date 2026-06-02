#include "ico/types.h"
extern int func_0010ECD8(int a0);
extern int func_0010ECA0(int a0);

void func_001E98C8(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010ECD8(a0);
        return func_0010ECA0((int)s0);
    }
}
