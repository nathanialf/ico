#include "regpin.h"

extern void func_00102E08(int *a0);

typedef struct __attribute__((packed)) { long long w; } UB8;

void func_0019F4E8(int *a0, int *a1)
{
    register int *src REG("$17");
    register int *self REG("$16");
    src = a1;
    self = a0;
    func_00102E08(self);
    *(UB8 *)((char *)self[0x15C / 4]) = *(UB8 *)src;
}
