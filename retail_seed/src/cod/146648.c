#include "matching.h"

int func_00246648(int *self)
{
    int *p = (int *)self[0];
    if (p == 0) goto ret0;
    if (self[1] != p[6]) goto ret0;
    if ((p[4] & 1) != 0) goto ret1;
ret0:
    return 0;
ret1:
    return 1;
}
