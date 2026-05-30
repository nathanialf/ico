#include "ico/types.h"
void func_001CEB08(char *self, int val) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    *(int *)(p + 0x38) = val;
}
