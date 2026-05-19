#include "matching.h"
#include "regpin.h"

int func_00187950(int *self, int n)
{
    register int t0 REG("$8") = 0;
    register int sum REG("$6") = 0;
    int lower, upper;
    KEEP_LIVE(t0);
    KEEP_LIVE(sum);
    if (n > 0) {
        upper = self[0x3C / 4];
        lower = self[0x38 / 4];
        MATERIALIZE(lower);
        MATERIALIZE(upper);
        do {
            int v1;
            __asm__ volatile("subu %0, %1, %2" : "=r"(v1) : "r"(upper), "r"(lower));
            t0++;
            sum += v1;
        } while (t0 < n);
    }
    return sum;
}

TRAILING_PAD_NOP();
