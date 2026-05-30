#include "ico/types.h"
int func_001D3D98(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = *(char **)(sub + 0x800);
    return *(int *)(p + 0x48) == 2;
}
