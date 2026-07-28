#include "matching.h"

extern int func_00202208(int a0);
extern void func_00203AA0(int a0);

void func_00203EE8(volatile unsigned int a0)
{
    if (!a0) {
    }
    VOLATILE_RELOAD_CALL(a0, func_00202208);
    func_00203AA0(1);
}
