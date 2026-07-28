#include "regpin.h"

extern void func_00100560(int x);
extern void func_00100540(int x);

void func_00240600(int *self)
{
    register int v;
    register int neg1 REG("$2");
    int adjusted;
    int rounded;

    func_00100560(self[0x40 / 4]);
    v = self[0x14 / 4];
    neg1 = -1;
    adjusted = v + 0x7FF;
    if (neg1 < adjusted) {
        rounded = adjusted;
    } else {
        rounded = v + 0xFFE;
    }
    self[0x14 / 4] = (rounded >> 11) << 11;
    func_00100540(self[0x40 / 4]);
}
