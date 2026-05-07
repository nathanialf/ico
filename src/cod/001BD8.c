#include "matching.h"

extern void func_00100950(int a0, int *a1);

void func_00101BD8(int a0, char a1)
{
    int locals[2];
    locals[0] = a0;
    locals[1] = a1;
    func_00100950(-7, locals);
    KEEP_LIVE(locals);
}
