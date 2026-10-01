/* libc.a member stdio.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <libc_internal.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

int __sread(Fil *a0, int a1, int a2)
{
    long v = _read_r((int *)a0->data, a0->file, a1, a2);
    if ((int)v >= 0) {
        a0->offset = a0->offset + (int)v;
    } else {
        a0->flags &= ~0x1000;
    }
    return (int)v;
}

long __swrite(Fil *a0, int a1, int a2)
{
    unsigned short flag = a0->flags;
    if (flag & 0x100) {
        _lseek_r((int *)a0->data, a0->file, 0, 2);
    }
    flag = a0->flags & ~0x1000;
    a0->flags = flag;
    {
        unsigned long r = (unsigned long)_write_r((int *)a0->data, a0->file, a1, a2);
        return (int)r;
    }
}

long __sseek(Fil *a0, int a1, int a2)
{
    unsigned long r = (unsigned long)_lseek_r((int *)a0->data, a0->file, a1, a2);
    if (r == -1) {
        a0->flags &= ~0x1000;
    } else {
        a0->offset = (int)r;
        a0->flags |= 0x1000;
    }
    return r;
}

int __sclose(Fil *a0)
{
    return _close_r((int *)a0->data, a0->file);
}
