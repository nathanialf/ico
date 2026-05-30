#include "matching.h"
#include "regpin.h"

extern unsigned int D_00633718;
extern unsigned int D_0063371C;

int func_001F1108(void)
{
    register unsigned int p;
    register unsigned int q REG("$3");
    register unsigned int end;
    p = D_00633718;
    q = D_0063371C;
    end = p + 0x1000;
    if (q < p) {
        q += 0x28000;
        if (q < p) return 1;
    }
    return !((int)q < (int)end);
}
