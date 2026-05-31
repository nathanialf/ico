#include "regpin.h"
#include "ico/types.h"

extern void func_00102E08(int *a0);

typedef struct __attribute__((packed)) { long long w; } UB8;

void func_0019F4E8(int *a0, int *a1)
{
    register int *src;
    register int *self REG("$16");
    src = a1;
    self = a0;
    func_00102E08(self);
    *(UB8 *)((char *)((GObj *)(self))->p_15C) = *(UB8 *)src;
}
