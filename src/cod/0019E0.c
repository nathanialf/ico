#include "matching.h"

extern unsigned int D_00274EB8[16];
extern int func_00101100();
extern int func_001013E0(char *fmt, void *args);

int func_001019E0(char *fmt, ...)
{
    void *args = (char *)__builtin_next_arg(fmt) - 0x38;
    unsigned int saved = D_00274EB8[0];
    int result;
    D_00274EB8[0] = (unsigned int)func_00101100;
    result = func_001013E0(fmt, args);
    D_00274EB8[0] = saved;
    return result;
}
