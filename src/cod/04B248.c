#include "matching.h"

int func_0014B248(char *self, int bit) {
    char *sub = *(char **)(self + 0x164);
    return (*(int *)(sub + 0x90) >> bit) & 1;
}

TRAILING_PAD_NOP();
