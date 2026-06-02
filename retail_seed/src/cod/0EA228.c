#include "ico/types.h"
int func_001EA228(char *self, char *src) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    *(unsigned short *)(p + 0x20) = *(unsigned short *)(src + 0x30);
    *(int *)(p + 0x24) = *(short *)(src + 0x32);
    return 1;
}
