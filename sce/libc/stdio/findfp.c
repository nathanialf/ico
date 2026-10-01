/* libc.a member findfp.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <stdio.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

/* kept local: libc_internal.h declares it as `int __sread(Fil *a0, int a1, int a2)` */
extern int __sread(void *a0, int a1, int a2);
/* kept local: libc_internal.h declares it as `long __swrite(Fil *a0, int a1, int a2)` */
extern long __swrite(void *a0, int a1, int a2);
/* kept local: libc_internal.h declares it as `long __sseek(Fil *a0, int a1, int a2)` */
extern long __sseek(void *a0, int a1, int a2);
/* kept local: libc_internal.h declares it as `int __sclose(Fil *a0)` */
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

/* kept local: this member cannot include libc_internal.h, whose __sclose, __sread, __sseek,
   __swrite, _fwalk conflict with its own */
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

/* kept local: libc_internal.h declares it as `int _fwalk(Reent *ptr, int (*function)())` */
extern void _fwalk(int a0, void *a1);

void _cleanup_r(int a0)
{
    _fwalk(a0, fflush);
}

/* kept local: this member cannot include libc_internal.h, whose __sclose, __sread, __sseek,
   __swrite, _fwalk conflict with its own */
extern void _cleanup_r(int a0);

void _cleanup(void)
{
    _cleanup_r((int)_impure_ptr);
}

/* kept local: this member cannot include libc_internal.h, whose __sclose, __sread, __sseek,
   __swrite, _fwalk conflict with its own */
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
