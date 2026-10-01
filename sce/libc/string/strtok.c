/* libc.a member strtok.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
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
