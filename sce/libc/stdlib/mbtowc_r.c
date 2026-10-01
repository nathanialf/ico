/* libc.a member mbtowc_r.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int _mbtowc_r(int a0, int *a1, unsigned char *a2, int a3)
{
    int local;
    int *p = &local;
    if (a1 != 0)
        p = a1;
    if (a2 == 0)
        goto zero;
    if (a3 != 0)
        goto store;
    return -1;
zero:
    return 0;
store:
    *p = *a2;
    return *a2 != 0;
}
