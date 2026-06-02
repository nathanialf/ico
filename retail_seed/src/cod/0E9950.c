#include "regpin.h"
#include "ico/types.h"
extern void func_001AE460(int *a0);

void func_001E9950(int *self)
{
    Sub15C *p = ((int *)((GObj *)(self))->p_15C)[0x800/4];
    register int v_old;  /* v0 */
    register int v_new;  /* v1 */
    v_new = p->f_30;
    v_old = v_new;
    v_new = v_new + 1;
    p->f_30 = v_new;
    if (v_old >= 0x1F) {
        p->f_30 = 0;
        func_001AE460(self);
    }
}
