#include "regpin.h"
#include "ico/types.h"
#include "matching.h"

extern void func_001BF2C8(int *self);
extern void func_00102858(int *self);
extern void func_001AE460(int *self);

void func_001C0538(int *self)
{
    int *p;
    register int v_load;
    register int v_copy REG("$3");
    int next;

    p = (int *)((int *)((GObj *)(self))->p_15C)[0x800 / 4];
    func_001BF2C8(self);
    func_00102858(self);
    v_load = p[0];
    next = v_load + 1;
    v_copy = v_load;
    KEEP_LIVE(v_copy);
    p[0] = next;
    if (v_copy < 0x1F) return;
    p[0] = 0;
    func_001AE460(self);
}
