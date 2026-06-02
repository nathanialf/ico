#include "ico/types.h"
int func_00193A58(short *dst, char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    dst[0] = *(unsigned short *)(p + 0x50);
    dst[1] = *(unsigned short *)(p + 0x8);
    return 1;
}
