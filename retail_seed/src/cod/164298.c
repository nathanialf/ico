#include "matching.h"

extern int func_002669E8(int *self, int subj, int b, void *args);

int func_00264298(int *self, int b, ...)
{
    void *args = (char *)__builtin_next_arg(b) - 0x30;
    return func_002669E8(self, self[2], b, args);
}
