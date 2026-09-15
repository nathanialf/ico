/* libgraph.a member graph021.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

void sceGsSetHalfOffset(void *a0, short a1, short a2, short a3)
{
    unsigned long long v = *(unsigned long long *)((char *)a0 + 0x30);
    long long a, b, ta, t, hi;
    b = (short)a2;
    b -= (unsigned long long)((int)((v >> 48) & 0x7FF) + 1) >> 1;
    t = b << 4;
    a = (short)a1;
    a -= (unsigned long long)((int)((v >> 16) & 0x7FF) + 1) >> 1;
    ta = a << 4;
    if (a3 != 0)
        hi = (t + 8) << 32;
    else
        hi = b << 36;
    *(long long *)((char *)a0 + 0x20) = ta | hi;
}
