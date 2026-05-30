#include "matching.h"
#include "ico/types.h"
#include "regpin.h"

int func_001903E0(int *self)
{
    register int *p REG("$5");      /* a1 */
    register char *q REG("$4");     /* a0 */
    register int r REG("$2") = 0;   /* v0 */
    register int b REG("$3");       /* v1 */
    p = (int *)((GObj *)(self))->p_15C;
    q = (char *)p[0x800/4];
    b = *(unsigned char *)(q + 0xA0);
    if (b) {
        r = *(int *)(q + 0x68) < 3;
    }
    return r;
}

TRAILING_PAD_NOP();
