#include "r5900.h"
#include "regpin.h"

void func_00105F48(char *dst, char *src)
{
    register char *d REG("$4") = dst;
    register int spr REG("$7");
    __asm__ volatile("lui %0, 0x2000" : "=r"(spr));
    __asm__ volatile("or %0, %0, %1" : "+r"(d) : "r"(spr));
    QCOPY64_SERIAL("$a2");
}
