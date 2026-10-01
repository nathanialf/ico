/* libc.a member errno.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <reent.h>
#include <errno.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int __errno(void)
{
    return (int)_impure_ptr;
}
