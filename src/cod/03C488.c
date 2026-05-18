#include "matching.h"

void func_0013C488(int *out, unsigned short *q)
{
    unsigned int v3;
    out[0] = (int)q;
    KEEP_LIVE_MEM(out[0]);
    out[3] = (int)q + (unsigned int)q[5] * 4;
    out[1] = (int)q + (unsigned int)q[1] * 4;
    v3 = q[3];
    q = (unsigned short *)((char *)q + v3 * 4);
    out[2] = (int)q;
}
