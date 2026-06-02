#include "ico/types.h"
void func_001903B8(float *dst, char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    dst[0] = *(float *)(p + 0xB0);
    dst[1] = *(float *)(p + 0xB4);
    dst[2] = *(float *)(p + 0xB8);
}
