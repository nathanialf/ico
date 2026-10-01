/* libc.a member findfp.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <libc_internal.h>
#include <stdio.h>

void std(Fil *fp, int flags, int file, Reent *data)
{
    fp->p = 0;
    fp->r = 0;
    fp->w = 0;
    fp->flags = flags;
    fp->file = file;
    fp->bf.base = 0;
    fp->lbfsize = 0;
    fp->cookie = fp;
    fp->read = __sread;
    fp->write = __swrite;
    fp->seek = __sseek;
    fp->close = __sclose;
    fp->data = data;
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

#define ENOMEM 12
#define NDYNAMIC 4

void __sinit(Reent *s);

Fil *__sfp(Reent *d)
{
    Fil *fp;
    int n;
    Glue *g;

    if (!d->sdidinit) {
        __sinit(d);
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

int _fwalk(Reent *ptr, int (*function)());

void _cleanup_r(Reent *ptr)
{
    _fwalk(ptr, fflush);
}

void _cleanup(void)
{
    _cleanup_r(_impure_ptr);
}

void __sinit(Reent *s)
{
    s->cleanup = _cleanup_r;
    s->sdidinit = 1;
    std(&s->sf[0], 4, 0, s);
    std(&s->sf[1], 9, 1, s);
    std(&s->sf[2], 10, 2, s);
    s->glue.iobs = &s->sf[0];
    s->glue.niobs = 3;
    s->glue.next = 0;
}
