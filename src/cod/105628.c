#include "matching.h"

extern char D_004CAEC0[];
extern char D_004CC1E0[];

int func_00205628(int a0, int a1)
{
    int *ch = (int *)(D_004CAEC0 + a0 * 0x34);
    int *node = (int *)(D_004CC1E0 + (a1 << 6));
    int *old;
    int rv;
    rv = 0;
    node[2] = 0;
    old = (int *)ch[2];
    ch[2] = (int)node;
    node[3] = old[2];
    old[2] = (int)node;
    return rv;
}
