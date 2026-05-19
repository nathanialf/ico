#include "matching.h"

int func_001CFA20(char *self) {
    char *p = *(char **)(self + 0x4);
    *(int *)(p + 0x30) = 1;
    return 1;
}

TRAILING_PAD_NOP();
