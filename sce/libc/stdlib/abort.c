/* libc.a member abort.o */
#include <reent.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

void abort(void)
{
    for (;;) {
        raise(6);
        _exit(1);
    }
}
