/* libc.a member findfp.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern int D_0054CEAC[];
extern void fiprintf();
extern void abort(void);
extern int strtok_r(int a0, int a1, int a2);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
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

extern void *_malloc_r(void *a0, int a1);

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

struct _reent;

struct __sbuf {
    unsigned char *_base; /* 0x0 */
    int _size;            /* 0x4 */
};

typedef struct __sFILE {
    unsigned char *_p;    /* 0x00 */
    int _r;               /* 0x04 */
    int _w;               /* 0x08 */
    short _flags;         /* 0x0C */
    short _file;          /* 0x0E */
    struct __sbuf _bf;    /* 0x10 */
    int _lbfsize;         /* 0x18 */
    char pad1C[0x14];     /* 0x1C */
    struct __sbuf _ub;    /* 0x30 */
    char pad38[0xC];      /* 0x38 */
    struct __sbuf _lb;    /* 0x44 */
    char pad4C[0x8];      /* 0x4C */
    struct _reent *_data; /* 0x54 */
} __FILE;

struct _glue {
    struct _glue *_next; /* 0x0 */
    int _niobs;          /* 0x4 */
    __FILE *_iobs;       /* 0x8 */
};

struct _reent {
    int _errno;           /* 0x000 */
    char pad004[0x34];    /* 0x004 */
    int __sdidinit;       /* 0x038 */
    char pad03C[0x19C];   /* 0x03C */
    struct _glue __sglue; /* 0x1D8 */
};

#define ENOMEM 12
#define NDYNAMIC 4

extern void __sinit(char *a0);

__FILE *__sfp(struct _reent *d)
{
    __FILE *fp;
    int n;
    struct _glue *g;

    if (!d->__sdidinit) {
        __sinit((char *)d);
    }

    for (g = &d->__sglue;; g = g->_next) {
        for (fp = g->_iobs, n = g->_niobs; --n >= 0; fp++) {
            if (fp->_flags == 0) {
                goto found;
            }
        }
        if (g->_next == 0 && (g->_next = (struct _glue *)__sfmoreglue(d, NDYNAMIC)) == 0) {
            break;
        }
    }
    d->_errno = ENOMEM;
    return 0;

found:
    fp->_flags = 1;
    fp->_file = -1;
    fp->_data = d;
    fp->_p = 0;
    fp->_w = 0;
    fp->_r = 0;
    fp->_bf._base = 0;
    fp->_bf._size = 0;
    fp->_lbfsize = 0;
    fp->_ub._base = 0;
    fp->_ub._size = 0;
    fp->_lb._base = 0;
    fp->_lb._size = 0;
    return fp;
}

extern void _fwalk(int a0, void *a1);
extern int fflush(void);

void _cleanup_r(int a0)
{
    _fwalk(a0, fflush);
}

extern void _cleanup_r(int a0);

void _cleanup(void)
{
    _cleanup_r(D_0054CEAC[0]);
}

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

extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int fflush(void);
extern int _raise_r(int a0, int a1);
extern int __sigtramp_r(int a0, int a1);
extern int kill(int a0, void *a1);
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int fstat(void *a0, void *a1);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
