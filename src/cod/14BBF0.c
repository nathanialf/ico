#include "regpin.h"
extern char D_00717764[];
extern char D_0071776C[];

void func_0024BBF0(int a0)
{
    register int idx_off REG("$3");
    register char *base REG("$4");
    idx_off = a0 * 8;
    if (a0 < 0) {
        base = *(char **)D_00717764;
    } else {
        base = *(char **)D_0071776C;
    }
    *(int *)(base + idx_off) = 0;
}
