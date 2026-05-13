#include "matching.h"
#include "regpin.h"

extern void func_001F2320(void);
extern int *func_00203B40(void (*fn)(void), int x);

void func_001F22E0(int *self)
{
    register int *q REG("$3") = func_00203B40(func_001F2320, 0x15);
    KEEP_LIVE(q);
    *self = 0;
    q[8] = (int)self;
}
