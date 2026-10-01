/* libc.a member ungetc.o */
#include <string.h>
#include <reent.h>
#include <libc_internal.h>
#include <stdio.h>
#include <stdlib.h>

/* newlib's struct __sbuf / struct __sFILE, laid out from this member's own
   field offsets, with the newlib member names.  Only this member needs the
   typed form: the loop below copies fp->ubuf[i] through the real array
   member. */

int __submore(Fil *fp)
{
    int i;
    unsigned char *p;

    if (fp->ub.base == fp->ubuf) {
        p = (unsigned char *)_malloc_r(fp->data, 0x400);
        if (p == 0)
            return -1;
        fp->ub.base = p;
        fp->ub.size = 0x400;
        p += 0x400 - 3;
        for (i = 3; --i >= 0;)
            p[i] = fp->ubuf[i];
        fp->p = p;
        return 0;
    }
    i = fp->ub.size;
    p = (unsigned char *)_realloc_r(fp->data, fp->ub.base, i << 1);
    if (p == 0)
        return -1;
    memcpy(p + i, p, i);
    fp->p = p + i;
    fp->ub.base = p;
    fp->ub.size = i << 1;
    return 0;
}

int ungetc(int c, Fil *fp)
{
    if (c == -1)
        return -1;
    /* newlib's CHECK_INIT(fp), a do-while-zero macro wrapper */
    do {
        if (fp->data == 0)
            fp->data = _impure_ptr;
        if (fp->data->sdidinit == 0)
            __sinit(fp->data);
    } while (0);
    fp->flags &= ~0x20;
    if ((fp->flags & 4) == 0) {
        if ((fp->flags & 0x10) == 0)
            return -1;
        if (fp->flags & 8) {
            if (fflush(fp))
                return -1;
            fp->flags &= ~8;
            fp->w = 0;
            fp->lbfsize = 0;
        }
        fp->flags |= 4;
    }
    c = (unsigned char)c;
    if (fp->ub.base != 0) {
        if (fp->r >= fp->ub.size && __submore(fp))
            return -1;
        *--fp->p = c;
        fp->r += 1;
        return c;
    }
    if (fp->bf.base != 0 && fp->p > fp->bf.base && fp->p[-1] == c) {
        fp->p -= 1;
        fp->r += 1;
        return c;
    }
    fp->ur = fp->r;
    fp->up = fp->p;
    fp->ub.base = fp->ubuf;
    fp->ub.size = 3;
    fp->ubuf[2] = c;
    fp->p = &fp->ubuf[2];
    fp->r = 1;
    return c;
}
