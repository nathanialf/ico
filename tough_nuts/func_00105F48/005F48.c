/* src/cod/005F48.c — func_00105F48 */

#include "r5900.h"
#include "regpin.h"

void func_00105F48(int dst, void *src)
{
    register int pinned_a0 REG("$4") = dst | 0x20000000;
    (void)pinned_a0;
    QCOPY64_SERIAL("$a2");
}
