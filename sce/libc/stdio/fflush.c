/* libc.a member fflush.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);

#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SWR 0x0008
#define __SERR 0x0040
#define EOF (-1)

extern int _fwalk(Reent *r, int (*func)());
extern void __sinit(Reent *r);
extern int fflush(Fil *fp);

int fflush(Fil *fp)
{
    register unsigned char *p;
    register int n, t;

    if (fp == 0) {
        return _fwalk((Reent *)D_0054CEAC[0], fflush);
    }
    /* newlib's CHECK_INIT(fp), a do-while-zero macro wrapper */
    do {
        if (fp->data == 0)
            fp->data = (Reent *)D_0054CEAC[0];
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
