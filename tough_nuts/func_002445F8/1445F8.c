#include "matching.h"
#include "regpin.h"

void func_002445F8(char *p, int n)
{
    register int i REG("$2");
    register int neg1;
    if (n == 0) return;
    i = n - 1;
    neg1 = -1;
    NOP();
    do {
        *p = 0;
        i--;
        p++;
        NOP();
        NOP();
    } while (i != neg1);
}

TRAILING_PAD_NOP();
