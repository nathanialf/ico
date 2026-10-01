/* libc.a member atoi.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int atoi(void *a0)
{
    return (int)strtol(a0, 0, 0xA);
}
