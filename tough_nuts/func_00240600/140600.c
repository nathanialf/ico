#include "regpin.h"

extern void WaitSema(int x);
extern void SignalSema(int x);

void func_00240600(int *self)
{
    register int v;
    register int neg1 REG("$2");
    int adjusted;
    int rounded;

    WaitSema(self[0x40 / 4]);
    v = self[0x14 / 4];
    neg1 = -1;
    adjusted = v + 0x7FF;
    if (neg1 < adjusted) {
        rounded = adjusted;
    } else {
        rounded = v + 0xFFE;
    }
    self[0x14 / 4] = (rounded >> 11) << 11;
    SignalSema(self[0x40 / 4]);
}
