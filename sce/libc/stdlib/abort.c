/* libc.a member abort.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
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
