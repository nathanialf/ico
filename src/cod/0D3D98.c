#include "ico/types.h"
int func_001D3D98(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    return *(int *)(p + 0x48) == 2;
}
