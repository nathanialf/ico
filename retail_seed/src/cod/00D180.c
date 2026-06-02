#include "matching.h"
#include "ico/types.h"

int func_0010D180(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    return *(int *)(p + 0x30) != 0;
}

TRAILING_PAD_NOP();
