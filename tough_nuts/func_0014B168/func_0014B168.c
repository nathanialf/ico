#include "matching.h"
#include "regpin.h"

int func_0014B168(char *self, int a1, float *a2, int a3, int a4)
{
    char *sub = *(char **)(self + 0x164);
    register int rv REG("$4") = 0;
    if (a3 == 6) {
        *(volatile int *)(sub + 0x9C) = 0;
        *(volatile int *)(sub + 0x98) = 0;
        *(volatile int *)(sub + 0xA0) = 0;
        goto end;
    }
    if (a3 < *(int *)(sub + 0x9C)) {
        goto end;
    }
    *(int *)(sub + 0x98) = a1;
    if (a2 != 0) {
        *(float *)(sub + 0xB0) = a2[0];
        *(float *)(sub + 0xB4) = a2[1];
        *(float *)(sub + 0xB8) = a2[2];
    }
    *(volatile int *)(sub + 0x9C) = a3;
    rv = 1;
    *(volatile int *)(sub + 0xA0) = a4;
end:
    return rv;
}
