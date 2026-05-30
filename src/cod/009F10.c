#include "matching.h"
#include "ico/types.h"

char func_00109F10(char *self, int idx) {
    char *sub = ((GObj *)(self))->p_15C;
    char *table = *(char **)(sub + 0x810);
    return table[idx];
}

TRAILING_PAD_NOP();
