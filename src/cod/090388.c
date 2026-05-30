#include "ico/types.h"
int func_00190388(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    return *(int *)(p + 0x68) == *(int *)(p + 0x74) - 1;
}
