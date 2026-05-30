#include "regpin.h"
#include "ico/types.h"
extern int D_00553BE0[];
extern float func_00168C18(int *a, int *b);
extern void func_001A6E28(int *a);

void func_00106D68(int *self)
{
    register char *p REG("$4");  /* a0 */
    register char *base_a0 REG("$16");  /* s0 */
    p = (char *)((GObj *)(self))->p_15C;
    base_a0 = p + 0xA0;
    *(float *)(base_a0 + 0x1B4) = func_00168C18((int *)(p + 0x1D0), (int *)(p + 0x250));
    func_001A6E28(D_00553BE0);
}
