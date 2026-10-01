/* libc.a member refill.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <reent.h>
#include <libc_internal.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

/* fflush is reached both with and without an argument in this member, exactly
   as the shipped code does; the declaration is left unprototyped. */
/* kept local: not yet moved to stdio.h */
extern int fflush();
/* kept local: stdlib.h declares it as `void _free_r(int *self, void *mem)` */
extern void _free_r(Reent *r, void *p);

int lflush(void)
{
    return fflush();
}

int __srefill(Fil *fp)
{
    /* newlib's CHECK_INIT(fp), a do-while-zero macro wrapper */
    do {
        if (fp->data == 0)
            fp->data = _impure_ptr;
        if (!fp->data->sdidinit)
            __sinit(fp->data);
    } while (0);

    fp->r = 0;

    if (fp->flags & 0x20)
        return -1;

    if ((fp->flags & 0x4) == 0) {
        if ((fp->flags & 0x10) == 0)
            return -1;
        if (fp->flags & 0x8) {
            if (fflush(fp))
                return -1;
            fp->flags &= ~0x8;
            fp->w = 0;
            fp->lbfsize = 0;
        }
        fp->flags |= 0x4;
    } else {
        if (fp->ub.base != 0) {
            if (fp->ub.base != (char *)fp->ubuf)
                _free_r(fp->data, fp->ub.base);
            fp->ub.base = 0;
            if ((fp->r = fp->ur) != 0) {
                fp->p = fp->up;
                return 0;
            }
        }
    }

    if (fp->bf.base == 0)
        __smakebuf(fp);

    if (fp->flags & 3)
        _fwalk(fp->data, lflush);
    fp->p = fp->bf.base;
    fp->r = (*fp->read)(fp->cookie, (char *)fp->p, fp->bf.size);
    fp->flags &= ~0x2000;
    if (fp->r <= 0) {
        if (fp->r == 0)
            fp->flags |= 0x20;
        else {
            fp->r = 0;
            fp->flags |= 0x40;
        }
        return -1;
    }
    return 0;
}
