#include "matching.h"

extern void *D_00631AE8;

long func_0014A0D8(void)
{
    void *a = D_00631AE8;
    if (a == 0) {
        return 0;
    }
    {
        unsigned long *b = *(unsigned long **)((char *)a + 0x164);
        return (b[3] >> 36) & 1;
    }
}

TRAILING_PAD_NOP();
