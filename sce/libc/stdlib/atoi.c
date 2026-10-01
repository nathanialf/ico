/* libc.a member atoi.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
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
