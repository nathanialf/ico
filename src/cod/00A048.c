#include "ico/types.h"
extern int func_00168A80(int);

int func_0010A048(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    return func_00168A80(*(int *)(sub + 0x5F8));
}
