/* libc.a member strtok.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int strtok(int a0, int a1)
{
    return strtok_r(a0, a1, (int)_impure_ptr + 0x5C);
}
