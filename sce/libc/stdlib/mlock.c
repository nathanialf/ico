/* libc.a member mlock.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <reent.h>
#include <libc_internal.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

void __malloc_lock(void) {}

void __malloc_unlock() {}
