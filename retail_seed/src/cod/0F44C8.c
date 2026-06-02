#include "ico/types.h"
void func_001F44C8(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    int val = *(int *)(sub + 0x74);
    char *q = *(char **)(p + 0x5C);
    *(int *)(q + 0x16C) = val;
}
