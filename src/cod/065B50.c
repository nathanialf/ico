#include "regpin.h"

extern int D_00632390;

void func_00165B50(char *a0, int a1, int *a2)
{
    char *first;
    register char *second REG("$3");
    register int new_a0 REG("$4");
    first = *(char * volatile *)(a0 + 0x164);
    second = *(char **)(first + 0x670);
    *(int *)(second + 0x200) = a1;
    if (a2 != 0) {
        first = *(char * volatile *)(a0 + 0x164);
        new_a0 = *a2;
    } else {
        first = *(char * volatile *)(a0 + 0x164);
        new_a0 = D_00632390;
    }
    second = *(char **)(first + 0x670);
    *(int *)(second + 0x20C) = new_a0;
}
