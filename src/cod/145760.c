#include "matching.h"

void func_00245760(int *q)
{
    int count = q[1] - 1;
    char *rp = (char *)q[2] + 1;
    int cap = q[0];
    q[1] = count;
    cap += 0x10;
    {
        char *end = (char *)q + cap;
        q[2] = (int)rp;
        if (rp == end) {
            q[2] = (int)q + 0x10;
        }
    }
}
