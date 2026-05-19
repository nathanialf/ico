#include "matching.h"
#include "regpin.h"

extern int D_004C49A8[];
extern char D_00565060[];

void func_001D4E30(int target)
{
    register char *base REG("$2");
    register int *out REG("$3");
    register char *p REG("$6");
    register int i REG("$5");
    base = D_00565060;
    out = D_004C49A8;
    p = base + 0x134;
    i = 0x43D;
    KEEP_LIVE(base);
    do {
        if (*(int *)p == target) *out = 0;
        out++;
        i--;
        p += 0x190;
    } while (i >= 0);
}
