/* libc.a member abort.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern void fiprintf();
extern void abort(void);
extern void _exit(int a0);
extern int raise(int a0);

void abort(void)
{
    for (;;) {
        raise(6);
        _exit(1);
    }
}
