#include "matching.h"

void func_001BB800(char *self, int val) {
    *(int *)(*(char **)(self + 0x164) + 0x98) = val;
}

TRAILING_PAD_NOP();
