#include "matching.h"

void func_0013F810(int *p)
{
    int *cur = (int *)p[0x2C/4];
    if (cur != 0) {
        do {
            cur[0x18/4] = 0;
            cur = (int *)cur[0x8/4];
        } while (cur != 0);
    }
}

TRAILING_PAD_NOP();
