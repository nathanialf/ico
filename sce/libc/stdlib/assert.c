/* libc.a member assert.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

/* this member's own declaration; stdio.h declares it as `int fiprintf(void *fp, void *fmt, ...)` */
extern void fiprintf();

void __assert(int a0, int a1, int a2)
{
    fiprintf(*(int *)((int)_impure_ptr + 0xC),
             (int)"assertion \"%s\" failed: file \"%s\", line %d\n", a2, a0, a1);
    abort();
}
