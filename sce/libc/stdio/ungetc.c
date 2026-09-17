/* libc.a member ungetc.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern int D_0054CEAC[];
extern void fiprintf();
extern void abort(void);
extern void *_malloc_r(void *r, int n);
extern void *_realloc_r(void *r, void *p, int n);

/* newlib's struct __sbuf / struct __sFILE, reconstructed from the ROM's own
   field offsets in this member (evidence rung: ROM bytes; the newlib member
   layout gives the names).  Only this member needs the typed form: the loop
   below copies fp->ubuf[i] and gcc hoists the address only when the field is a
   real array member of a struct type, which is what puts ROM's preheader copy
   of _ub._base in place of a load. */

int __submore(char *fp0)
{
    Fil *fp = (Fil *)fp0;
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

extern void __sinit(void *r);
extern int fflush();
extern int __submore(char *fp);

int ungetc(int c, Fil *fp)
{
    if (c == -1)
        return -1;
    /* newlib's CHECK_INIT(fp), a do-while-zero macro wrapper */
    do {
        if (fp->data == 0)
            fp->data = (char *)D_0054CEAC[0];
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
