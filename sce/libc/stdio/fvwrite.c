/* libc.a member fvwrite.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern void fiprintf();
extern void abort(void);

struct __siov {
    const char *iov_base; /* 0x0 */
    int iov_len;          /* 0x4 */
};

struct __suio {
    struct __siov *uio_iov; /* 0x0 */
    int uio_iovcnt;         /* 0x4 */
    int uio_resid;          /* 0x8 */
};

#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SWR 0x0008
#define __SSTR 0x0200
#define __SERR 0x0040
#define EOF (-1)
#define BUFSIZ 1024

extern int __swsetup(Fil *fp);
extern int fflush(Fil *fp);
extern void *memchr(const void *s, int c, int n);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define COPY(n) (void)memmove((void *)fp->p, (void *)p, (int)(n))
#define GETIOV(extra_work)                                                                         \
    while (len == 0) {                                                                             \
        extra_work;                                                                                \
        p = iov->iov_base;                                                                         \
        len = iov->iov_len;                                                                        \
        iov++;                                                                                     \
    }

int __sfvwrite(Fil *fp, struct __suio *uio)
{
    unsigned int len;
    const char *p;
    struct __siov *iov;
    int w, s;
    char *nl;
    int nlknown, nldist;

    if ((len = uio->uio_resid) == 0) {
        return 0;
    }
    if (((fp->flags & __SWR) == 0 || fp->bf.base == 0) && __swsetup(fp)) {
        return EOF;
    }

    iov = uio->uio_iov;
    len = 0;
    w = 0;
    if (fp->flags & __SNBF) {
        do {
            GETIOV(;);
            w = (*fp->write)(fp->cookie, p, MIN(len, BUFSIZ));
            if (w <= 0) {
                goto err;
            }
            p += w;
            len -= w;
        } while ((uio->uio_resid -= w) != 0);
    } else if ((fp->flags & __SLBF) == 0) {
        do {
            GETIOV(;);
            w = fp->w;
            if (fp->flags & __SSTR) {
                if (len < w) {
                    w = len;
                }
                COPY(w);
                fp->w -= w;
                fp->p += w;
                w = len;
            } else if (fp->p > fp->bf.base && len > w) {
                COPY(w);
                fp->p += w;
                if (fflush(fp)) {
                    goto err;
                }
            } else if (len >= (w = fp->bf.size)) {
                w = (*fp->write)(fp->cookie, p, w);
                if (w <= 0) {
                    goto err;
                }
            } else {
                w = len;
                COPY(w);
                fp->w -= w;
                fp->p += w;
            }
            p += w;
            len -= w;
        } while ((uio->uio_resid -= w) != 0);
    } else {
        nlknown = 0;
        do {
            GETIOV(nlknown = 0);
            if (!nlknown) {
                nl = memchr((void *)p, '\n', len);
                nldist = nl ? nl + 1 - p : len + 1;
                nlknown = 1;
            }
            s = MIN(len, nldist);
            w = fp->w + fp->bf.size;
            if (fp->p > fp->bf.base && s > w) {
                COPY(w);
                fp->p += w;
                if (fflush(fp)) {
                    goto err;
                }
            } else if (s >= (w = fp->bf.size)) {
                w = (*fp->write)(fp->cookie, p, w);
                if (w <= 0) {
                    goto err;
                }
            } else {
                w = s;
                COPY(w);
                fp->w -= w;
                fp->p += w;
            }
            if ((nldist -= w) == 0) {
                if (fflush(fp)) {
                    goto err;
                }
                nlknown = 0;
            }
            p += w;
            len -= w;
        } while ((uio->uio_resid -= w) != 0);
    }
    return 0;

err:
    fp->flags |= __SERR;
    return EOF;
}
