#include "regpin.h"
extern int D_00559CC0[];
extern char D_004CC1E0[];
extern void func_001A6E28(int *p);
extern int func_00205498(int x);

void func_00178930(int *self)
{
    register int *self_save REG("$16");
    register int idx_a1 REG("$5");
    int idx;
    char *base;
    self_save = self;
    idx_a1 = self_save[0x64/4];
    if (idx_a1 < 0) return;
    func_001A6E28(D_00559CC0);
    idx = self_save[0x64/4];
    base = (char *)D_004CC1E0 + idx * 64;
    func_00205498(*(int *)(base + 0x20));
    self_save[0x64/4] = -1;
}
