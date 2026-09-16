/* libc.a member refill.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef struct PObjBlk {
    char pad0[4];
    unsigned int size; /* 0x4 */
} PObjBlk;

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

typedef struct {
    char *pos; /* 0x0 */
    int len;   /* 0x4 */
} StreamBuf;

extern int D_0054CEAC[];
extern void fiprintf();
extern void abort(void);
/* fflush is reached both with and without an argument in this member, exactly
   as the shipped code does; the declaration is left unprototyped. */
extern int fflush();

typedef struct {
    char pad0[0x38];
    int sdidinit; /* 0x38 */
} Reent;

typedef struct {
    char *_p;                                     /* 0x0 */
    int _r;                                       /* 0x4 */
    int _w;                                       /* 0x8 */
    short _flags;                                 /* 0xC */
    short _file;                                  /* 0xE */
    char *_bf_base;                               /* 0x10 */
    int _bf_size;                                 /* 0x14 */
    int _lbfsize;                                 /* 0x18 */
    void *_cookie;                                /* 0x1C */
    int (*_read)(void *cookie, char *buf, int n); /* 0x20 */
    int _write;                                   /* 0x24 */
    int _seek;                                    /* 0x28 */
    int _close;                                   /* 0x2C */
    char *_ub_base;                               /* 0x30 */
    int _ub_size;                                 /* 0x34 */
    char *_up;                                    /* 0x38 */
    int _ur;                                      /* 0x3C */
    unsigned char _ubuf[3];                       /* 0x40 */
    unsigned char _nbuf[1];                       /* 0x43 */
    char *_lb_base;                               /* 0x44 */
    int _lb_size;                                 /* 0x48 */
    int _blksize;                                 /* 0x4C */
    int _offset;                                  /* 0x50 */
    Reent *_data;                                 /* 0x54 */
} FileS;

extern void __sinit(Reent *r);
extern void _free_r(Reent *r, void *p);
extern void __smakebuf(FileS *fp);
extern void _fwalk(Reent *r, int (*f)());

int lflush(void)
{
    return fflush();
}

int __srefill(FileS *fp)
{
    /* newlib's CHECK_INIT(fp), a do-while-zero macro wrapper */
    do {
        if (fp->_data == 0)
            fp->_data = (Reent *)D_0054CEAC[0];
        if (!fp->_data->sdidinit)
            __sinit(fp->_data);
    } while (0);

    fp->_r = 0;

    if (fp->_flags & 0x20)
        return -1;

    if ((fp->_flags & 0x4) == 0) {
        if ((fp->_flags & 0x10) == 0)
            return -1;
        if (fp->_flags & 0x8) {
            if (fflush(fp))
                return -1;
            fp->_flags &= ~0x8;
            fp->_w = 0;
            fp->_lbfsize = 0;
        }
        fp->_flags |= 0x4;
    } else {
        if (fp->_ub_base != 0) {
            if (fp->_ub_base != (char *)fp->_ubuf)
                _free_r(fp->_data, fp->_ub_base);
            fp->_ub_base = 0;
            if ((fp->_r = fp->_ur) != 0) {
                fp->_p = fp->_up;
                return 0;
            }
        }
    }

    if (fp->_bf_base == 0)
        __smakebuf(fp);

    if (fp->_flags & 3)
        _fwalk(fp->_data, lflush);
    fp->_p = fp->_bf_base;
    fp->_r = (*fp->_read)(fp->_cookie, (char *)fp->_p, fp->_bf_size);
    fp->_flags &= ~0x2000;
    if (fp->_r <= 0) {
        if (fp->_r == 0)
            fp->_flags |= 0x20;
        else {
            fp->_r = 0;
            fp->_flags |= 0x40;
        }
        return -1;
    }
    return 0;
}
