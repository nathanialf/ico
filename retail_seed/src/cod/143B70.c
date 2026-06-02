#include "r5900.h"

void func_00243B70(void *dst, void *src)
{
    QCOPY64_PARALLEL_NO_NOP("$a2", "$a3", "$t0", "$t1");
}
