#include "regpin.h"
extern int *func_0014A6B8(int a0);

int func_0017E620(int a0, int b)
{
    register int *p REG("$3");  /* v1 */
    register int b_save REG("$16");  /* s0 */
    register unsigned int v REG("$2");  /* v0 */
    b_save = b;
    p = func_0014A6B8(a0);
    v = 0;
    if (p == 0) goto out;
    v = (unsigned int)(p[0x8/4] ^ b_save) < 1;
out:
    return (int)v;
}
