#include "matching.h"
#include "regpin.h"

extern int D_00274ED4[];
extern int D_00633F64;
extern int *D_006337BC;
extern void func_001F6D90(int *);

void func_001FAA58(void)
{
    register int *s0 REG("$16");
    D_00633F64 = 0;
    if (D_00274ED4[0] != 0) return;
    s0 = D_006337BC;
    D_006337BC = 0;
    if (s0 == 0) return;
loop:
    func_001F6D90(s0);
    s0 = (int *)s0[0x154 / 4];
    if (s0 != 0) goto loop;
}
