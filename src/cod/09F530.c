#include "matching.h"
#include "ico/types.h"

extern void func_00103018(int *self);

void func_0019F530(int *self)
{
    long long *dst;
    func_00103018(self);
    dst = (long long *)(int)((GObj *)self)->p_15C;
    __asm__(
        "ldl $3, %%gp_rel(D_006323C7)($28)\n\t"
        "ldr $3, %%gp_rel(D_006323C0)($28)\n\t"
        "sdl $3, 7(%1)\n\t"
        "sdr $3, 0(%1)"
        : "=m"(*dst)
        : "r"(dst)
        : "$3");
}
