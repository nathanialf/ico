#include "matching.h"
#include "regpin.h"

int func_00187950(int *a0, int a1)
{
    register int sum REG("$6") = 0;
    register int i REG("$8") = 0;
    if (a1 > 0) {
        register int lo REG("$7") = a0[0xE];
        register int hi REG("$4") = a0[0xF];
        NOP();
        do {
            sum += hi - lo;
            i++;
            NOP();
        } while (i < a1);
    }
    return sum;
}
