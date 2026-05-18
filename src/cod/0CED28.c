#include "matching.h"

extern void func_00104508(void *dst, int *src);
extern void func_00102850(void *dst, int *src);
extern int func_001E8B48(int a, void *b, void *c);

void func_001CED28(int *self)
{
    int local[8];
    func_00104508(local, self);
    func_00102850(&local[4], self);
    func_001E8B48(0x31, local, &local[4]);
    self[0x16C / 4] = 0;
}
