#include "ico/types.h"
extern int D_00632D98;
extern float D_00630F88;

void func_00190330(void *a0)
{
    void *p = ((GObj *)((char *)a0))->p_15C;
    void *q = *(void **)((char *)p + 0x800);
    *(float *)((char *)q + 0x44) = (float)D_00632D98 * 0.5f * D_00630F88;
}
