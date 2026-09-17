/* libc.a member stdio.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern void fiprintf();
extern void abort(void);
extern int strtok_r(int a0, int a1, int a2);
extern int __sread(Fil *a0, int a1, int a2);
extern long __swrite(Fil *a0, int a1, int a2);
extern long __sseek(Fil *a0, int a1, int a2);
extern int __sclose(Fil *a0);
extern void *_malloc_r(void *a0, int a1);
extern void _fwalk(int a0, void *a1);
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int _raise_r(int a0, int a1);
extern int __sigtramp_r(int a0, int a1);
extern int kill(int a0, void *a1);
extern int _read_r(int *self, int a1, int a2, int a3);

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

extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);

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

extern int _close_r(int *self, int a1);

int __sclose(Fil *a0)
{
    return _close_r((int *)a0->data, a0->file);
}

extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int fstat(void *a0, void *a1);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
