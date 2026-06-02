#include "r5900.h"

void func_00105F48(void *dst, void *src)
{
    MAP_A0_TO_SPR();
    QCOPY64_SERIAL("$a2");
}
