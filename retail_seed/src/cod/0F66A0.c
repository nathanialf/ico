#include "ico/types.h"
extern void func_00243AE8(int *self, int q);
extern void func_00243978(int *p, int *q);
extern void func_00243B18(int *p, int *q, float f);

void func_001F66A0(int *self, int *other, float f)
{
    func_00243AE8(self, (int)((char *)((GObj *)(other))->p_15C + 0x50));
    func_00243978(self, self);
    func_00243B18(self, self, f);
}
