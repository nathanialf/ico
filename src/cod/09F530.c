#include "matching.h"
#include "ico/types.h"

typedef struct __attribute__((packed)) { long long v; } pll;
extern pll D_006323C0;
extern void func_00103018(int *self);

void func_0019F530(int *self)
{
    func_00103018(self);
    *(pll *)(int)((GObj *)(self))->p_15C = D_006323C0;
}
