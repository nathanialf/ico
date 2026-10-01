/* libc.a member fiprintf.o */
#include <reent.h>
#include <stdio.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int fiprintf(void *fp, void *fmt, ...)
{
    void *args = (char *)__builtin_next_arg(fmt) - 0x30;
    return vfiprintf(fp, fmt, args);
}
