#include "regpin.h"
#include "ico/types.h"
extern void func_001AE460(int *a0);

void func_001E9950(int *self)
{
    int *p = (int *)((int *)((GObj *)(self))->p_15C)[0x800/4];
    register int v_old REG("$2");  /* v0 */
    register int v_new REG("$3");  /* v1 */
    v_new = p[0x30/4];
    v_old = v_new;
    v_new = v_new + 1;
    p[0x30/4] = v_new;
    if (v_old >= 0x1F) {
        p[0x30/4] = 0;
        func_001AE460(self);
    }
}
