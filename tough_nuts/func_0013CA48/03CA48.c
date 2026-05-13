#include "regpin.h"
extern int *D_00632190;

void func_0013CA48(int *a0, int *a1, int count)
{
    register int *p REG("$8");
    register int i REG("$7");
    if (a0 == 0) return;
    if (a1 == 0) return;
    p = a0;
    i = 0;
    p[1] = (int)a1;
    D_00632190 = p;
    if (count > 0) {
        p[0] = count;
        do {
            int *arr = (int *)p[1];
            arr[i] = 0;
            i++;
        } while (i < count);
    }
    p[2] = 0;
}
