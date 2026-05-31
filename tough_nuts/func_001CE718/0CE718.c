#include "matching.h"
#include "ico/types.h"
#include "regpin.h"
void func_001CE718(int *self, float v)
{
    register float *p REG("$2");
    register float *q REG("$3");
    float qv;
    p = (float *)(int *)((GObj *)self)->p_15C;
    p = (float *)((int *)p)[0x840 / 4];
    q = p;
    p[0x30 / 4] = v;
    if (v < 0.0f) p[0x30 / 4] = 0.0f;
    qv = q[0x30 / 4];
    KEEP_LIVE(q);
    if (qv > 1.0f) q[0x30 / 4] = 1.0f;
}
