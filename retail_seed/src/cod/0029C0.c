#include "matching.h"

extern int func_00104F20(void);
extern int *func_00105278(void);
extern void func_00105F20(void *dst, void *src);
extern void func_0010DF70(void *p);
extern int *func_00105268(void);
extern void func_0010DDB8(void *p0, void *p1, void *p2);

void func_001029C0(int *self, int *other)
{
    func_00104F20();
    func_00105F20(func_00105278(), (char *)self + 0x20);
    func_0010DF70(other);
    func_00105F20((void *)self[0xC/4], func_00105278());
    func_00105268();
    func_0010DDB8((void *)self[0x10/4], (char *)self + 0x60, other);
}

TRAILING_PAD_NOP();
