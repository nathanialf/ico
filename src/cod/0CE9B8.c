#include "matching.h"
#include "ico/types.h"
#include "regpin.h"

int func_001CE9B8(int *self)
{
    int *sub = (int *)((GObj *)(self))->p_15C;
    register int n REG("$4");
    register int count_zero REG("$5") = 0;
    register int *p REG("$4");
    register int rem REG("$6");
    n = sub[0x88 / 4];
    if (n > 0) {
        rem = n;
        p = (int *)((int *)((Sub15C *)(sub))->p_800)[5];
        KEEP_LIVE(count_zero);
        KEEP_LIVE(rem);
        do {
            int v = *p;
            int next = count_zero + 1;
            p++;
            rem--;
            count_zero = (v == 0) ? next : count_zero;
        } while (rem != 0);
    }
    return count_zero;
}
