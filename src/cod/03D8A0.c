#include "regpin.h"
extern int *D_006A6F30[];
extern int func_00100410(void);

int func_0013D8A0(int *a0)
{
    register int **base REG("$16");  /* s0 */
    if (a0 == 0) {
        int idx;
        base = D_006A6F30;
        idx = func_00100410();
        a0 = base[idx];
    }
    return a0[0x18 / 4];
}
