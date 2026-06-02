#include "ico/types.h"
int func_001CE998(char *self, int idx) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    int *arr = *(int **)(p + 0x14);
    return arr[idx] == 0;
}
