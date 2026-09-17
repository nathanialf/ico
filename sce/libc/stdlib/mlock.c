/* libc.a member mlock.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern void fiprintf();
extern void abort(void);
extern void __malloc_lock(void);
extern void __malloc_unlock();

void __malloc_lock(void) {}

void __malloc_unlock() {}
