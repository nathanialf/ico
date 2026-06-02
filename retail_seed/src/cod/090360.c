#include "ico/types.h"
void func_00190360(char *self, float *src) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    *(float *)(p + 0x20) = src[0];
    *(float *)(p + 0x24) = src[1];
    *(float *)(p + 0x28) = src[2];
}
