/* libc.a member findfp.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern int D_0054CEAC[];
extern void fiprintf();
extern void abort(void);
extern int strtok_r(int a0, int a1, int a2);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern int __sclose(void *a0);

void std(char *fp, int flags, int file, void *data)
{
    *(int *)(fp + 0x0) = 0;
    *(int *)(fp + 0x4) = 0;
    *(int *)(fp + 0x8) = 0;
    *(short *)(fp + 0xC) = flags;
    *(short *)(fp + 0xE) = file;
    *(int *)(fp + 0x10) = 0;
    *(int *)(fp + 0x18) = 0;
    *(char **)(fp + 0x1C) = fp;
    *(void **)(fp + 0x20) = (void *)__sread;
    *(void **)(fp + 0x24) = (void *)__swrite;
    *(void **)(fp + 0x28) = (void *)__sseek;
    *(void **)(fp + 0x2C) = (void *)__sclose;
    *(void **)(fp + 0x54) = data;
}

extern void *_malloc_r(void *a0, int a1);

void *__sfmoreglue(void *a0, int a1)
{
    int sz;
    char *p;
    char *body;
    sz = a1 * 0x58;
    p = (char *)_malloc_r(a0, sz + 0xC);
    if (p == 0) {
        return 0;
    }
    body = p + 0xC;
    *(int *)(p + 0x4) = a1;
    *(int *)(p + 0x0) = 0;
    *(int *)(p + 0x8) = (int)body;
    memset(body, 0, sz);
    return p;
}

Reent;

#define ENOMEM 12
#define NDYNAMIC 4

extern void __sinit(char *a0);

Fil *__sfp(Reent *d)
{
    Fil *fp;
    int n;
    Glue *g;

    if (!d->sdidinit) {
        __sinit((char *)d);
    }

    for (g = &d->glue;; g = g->next) {
        for (fp = g->iobs, n = g->niobs; --n >= 0; fp++) {
            if (fp->flags == 0) {
                goto found;
            }
        }
        if (g->next == 0 && (g->next = (Glue *)__sfmoreglue(d, NDYNAMIC)) == 0) {
            break;
        }
    }
    d->err = ENOMEM;
    return 0;

found:
    fp->flags = 1;
    fp->file = -1;
    fp->data = d;
    fp->p = 0;
    fp->w = 0;
    fp->r = 0;
    fp->bf.base = 0;
    fp->bf.size = 0;
    fp->lbfsize = 0;
    fp->ub.base = 0;
    fp->ub.size = 0;
    fp->lb.base = 0;
    fp->lb.size = 0;
    return fp;
}

extern void _fwalk(int a0, void *a1);
extern int fflush(void);

void _cleanup_r(int a0)
{
    _fwalk(a0, fflush);
}

extern void _cleanup_r(int a0);

void _cleanup(void)
{
    _cleanup_r(D_0054CEAC[0]);
}

extern void std();

void __sinit(char *a0)
{
    char *p = a0 + 0x1E4;
    *(void **)(a0 + 0x3C) = (void *)_cleanup_r;
    *(int *)(a0 + 0x38) = 1;
    std(p, 4, 0, (int)a0);
    std(a0 + 0x23C, 9, 1, (int)a0);
    std(a0 + 0x294, 0xA, 2, (int)a0);
    *(char **)(a0 + 0x1E0) = p;
    *(int *)(a0 + 0x1DC) = 3;
    *(int *)(a0 + 0x1D8) = 0;
}

extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int fflush(void);
extern int _raise_r(int a0, int a1);
extern int __sigtramp_r(int a0, int a1);
extern int kill(int a0, void *a1);
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int fstat(void *a0, void *a1);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
