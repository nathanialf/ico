#include "matching.h"

typedef struct {
    int _0;
    int flags;
    char _8[0x50];
} R58;

extern R58 D_00275250[];

int func_001B59D0(int idx)
{
    int v = D_00275250[idx].flags;
    if ((v & 0x40) != 0) goto one;
    if ((v & 0x10) == 0) goto zero;
one:
    return 1;
zero:
    return 0;
}
