#include "regpin.h"
extern int D_00632C80;
extern void sceClose(int a0);

int debugSceCloseFdNew(void)
{
    register int rv REG("$2") = 0;
    int s0 = D_00632C80;
    int sentinel = -1;
    if (s0 != sentinel) {
        D_00632C80 = sentinel;
        sceClose(s0);
        D_00632C80 = sentinel;
    }
    return rv;
}
