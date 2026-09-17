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

typedef struct {
    unsigned char *_p; /* 0x00 */
    int _r;            /* 0x04 */
    int _w;            /* 0x08 */
    short _flags;      /* 0x0C */
    short _file;       /* 0x0E */

    struct {
        unsigned char *_base; /* 0x10 */
        int _size;            /* 0x14 */
    } _bf;

    int _lbfsize;                             /* 0x18 */
    void *_cookie;                            /* 0x1C */
    int (*_read)(void *, char *, int);        /* 0x20 */
    int (*_write)(void *, const char *, int); /* 0x24 */
} FILE;

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

extern int __swsetup(FILE *fp);
extern int fflush(FILE *fp);
extern void *memchr(const void *s, int c, int n);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define COPY(n) (void)memmove((void *)fp->_p, (void *)p, (int)(n))
#define GETIOV(extra_work)                                                                         \
    while (len == 0) {                                                                             \
        extra_work;                                                                                \
        p = iov->iov_base;                                                                         \
        len = iov->iov_len;                                                                        \
        iov++;                                                                                     \
    }

int __sfvwrite(FILE *fp, struct __suio *uio)
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
    if (((fp->_flags & __SWR) == 0 || fp->_bf._base == 0) && __swsetup(fp)) {
        return EOF;
    }

    iov = uio->uio_iov;
    len = 0;
    w = 0;
    if (fp->_flags & __SNBF) {
        do {
            GETIOV(;);
            w = (*fp->_write)(fp->_cookie, p, MIN(len, BUFSIZ));
            if (w <= 0) {
                goto err;
            }
            p += w;
            len -= w;
        } while ((uio->uio_resid -= w) != 0);
    } else if ((fp->_flags & __SLBF) == 0) {
        do {
            GETIOV(;);
            w = fp->_w;
            if (fp->_flags & __SSTR) {
                if (len < w) {
                    w = len;
                }
                COPY(w);
                fp->_w -= w;
                fp->_p += w;
                w = len;
            } else if (fp->_p > fp->_bf._base && len > w) {
                COPY(w);
                fp->_p += w;
                if (fflush(fp)) {
                    goto err;
                }
            } else if (len >= (w = fp->_bf._size)) {
                w = (*fp->_write)(fp->_cookie, p, w);
                if (w <= 0) {
                    goto err;
                }
            } else {
                w = len;
                COPY(w);
                fp->_w -= w;
                fp->_p += w;
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
            w = fp->_w + fp->_bf._size;
            if (fp->_p > fp->_bf._base && s > w) {
                COPY(w);
                fp->_p += w;
                if (fflush(fp)) {
                    goto err;
                }
            } else if (s >= (w = fp->_bf._size)) {
                w = (*fp->_write)(fp->_cookie, p, w);
                if (w <= 0) {
                    goto err;
                }
            } else {
                w = s;
                COPY(w);
                fp->_w -= w;
                fp->_p += w;
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
    fp->_flags |= __SERR;
    return EOF;
}
