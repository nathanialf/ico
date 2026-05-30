#include "ico/types.h"
void func_001C2EB8(char *self, float val) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = *(char **)(sub + 0x800);
    *(float *)(p + 0x3C) = val;
}
