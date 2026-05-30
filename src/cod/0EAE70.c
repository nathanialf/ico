#include "ico/types.h"
int func_001EAE70(char *self, int idx) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    int *arr = *(int **)(p + 0x24);
    int prev = arr[idx];
    arr[idx] = 0;
    return prev;
}
