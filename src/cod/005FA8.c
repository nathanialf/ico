#include "matching.h"
#include "r5900.h"
#include "regpin.h"

extern void func_00243BD8(void *a0);

void func_00105FA8(char *a0)
{
    register char *p REG("$16") = a0 + 0x30;
    char backup[16];
    LQ16_FROM(p);
    SQ16_TO(backup);
    NOP();
    func_00243BD8(a0);
    LQ16_FROM(backup);
    SQ16_TO(p);
}
