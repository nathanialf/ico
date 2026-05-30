#include "ico/types.h"
extern void func_0010ECD8(void);
extern void func_0010ECA0(int s);

void func_001C2FA0(int a0)
{
    int s0 = (int)((GObj *)(a0))->p_15C;
    if (*(int *)(s0 + 0x74)) {
        func_0010ECD8();
        func_0010ECA0(s0);
    }
}
