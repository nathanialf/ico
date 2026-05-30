#include "ico/types.h"
void func_00190430(char *self, int val) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = *(char **)(sub + 0x800);
    *(int *)p = val;
}
