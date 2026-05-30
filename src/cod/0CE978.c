#include "ico/types.h"
void func_001CE978(char *self, int idx) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = *(char **)(sub + 0x800);
    int *arr = *(int **)(p + 0x14);
    arr[idx] = 0;
}
