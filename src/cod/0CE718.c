#include "matching.h"
#include "regpin.h"

void func_001CE718(int *self, float v)
{
    register float *p REG("$2");
    register float *q REG("$3");
    int **base = (int **)self;
    p = (float *)((int *)base[0x15C / 4])[0x840 / 4];
    q = p;
    p[0x30 / 4] = v;
    if (v < 0.0f) p[0x30 / 4] = 0.0f;
    KEEP_LIVE(q);
    if (1.0f < q[0x30 / 4]) q[0x30 / 4] = 1.0f;
}
