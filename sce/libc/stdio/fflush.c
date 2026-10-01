/* libc.a member fflush.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <reent.h>
#include <stdio.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SWR 0x0008
#define __SERR 0x0040
#define EOF (-1)

/* kept local: libc_internal.h declares it as `int _fwalk(Reent *ptr, int (*function)())` */
extern int _fwalk(Reent *r, int (*func)());
/* kept local: libc_internal.h declares it as `void __sinit(char *a0)` */
extern void __sinit(Reent *r);

int fflush(Fil *fp)
{
    register unsigned char *p;
    register int n, t;

    if (fp == 0) {
        return _fwalk(_impure_ptr, fflush);
    }
    /* newlib's CHECK_INIT(fp), a do-while-zero macro wrapper */
    do {
        if (fp->data == 0)
            fp->data = _impure_ptr;
        if (fp->data->sdidinit == 0)
            __sinit(fp->data);
    } while (0);
    /* newlib spells the flags word and the write count with one variable t,
       which is what keeps ROM's copy of the write result out of $2. */
    t = fp->flags;
    if ((t & __SWR) == 0) {
        return 0;
    }
    if ((p = fp->bf.base) == 0) {
        return 0;
    }
    n = fp->p - p;
    fp->p = p;
    fp->w = (t & (__SLBF | __SNBF)) ? 0 : fp->bf.size;
    for (; n > 0; n -= t, p += t) {
        if ((t = (*fp->write)(fp->cookie, (char *)p, n)) <= 0) {
            fp->flags |= __SERR;
            return EOF;
        }
    }
    return 0;
}
