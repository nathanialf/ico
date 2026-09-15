/* libc.a member vfprintf.o.  MAIN.MAP member spans tile this run exactly and
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
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);
extern long long strtol(void *a0, int a1, int a2);
extern int _vfprintf_r(int *self, int subj, int b, void *args);
extern int vfprintf();
extern int strtok_r(int a0, int a1, int a2);
extern int __sfvwrite();

/* census __sprint, a file static (sce/libc/stdio/vfiprintf holds the global);
   _vfprintf_r's stub calls it and the same-object definition binds first. */
static int __sprint(int a0, int *a1)
{
    int ret;
    if (a1[2] == 0) {
        a1[1] = 0;
        return 0;
    }
    ret = __sfvwrite(a0, a1);
    a1[2] = 0;
    a1[1] = 0;
    return ret;
}

/* The stdio stream, as this libc lays it out: __sbprintf builds one on its own
   stack so a line-buffered stream is written through a full-size buffer. */
struct __sbuf {
    unsigned char *_base; /* 0x0 */
    int _size;            /* 0x4 */
};

typedef struct __sFILE {
    unsigned char *_p;      /* 0x00 */
    int _r;                 /* 0x04 */
    int _w;                 /* 0x08 */
    short _flags;           /* 0x0C */
    short _file;            /* 0x0E */
    struct __sbuf _bf;      /* 0x10 */
    int _lbfsize;           /* 0x18 */
    void *_cookie;          /* 0x1C */
    int (*_read)();         /* 0x20 */
    int (*_write)();        /* 0x24 */
    int (*_seek)();         /* 0x28 */
    int (*_close)();        /* 0x2C */
    struct __sbuf _ub;      /* 0x30 */
    unsigned char *_up;     /* 0x38 */
    int _ur;                /* 0x3C */
    unsigned char _ubuf[3]; /* 0x40 */
    unsigned char _nbuf[1]; /* 0x43 */
    struct __sbuf _lb;      /* 0x44 */
    int _blksize;           /* 0x4C */
    int _offset;            /* 0x50 */
    void *_data;            /* 0x54 */
} FILE;

#define __SNBF 0x0002
#define __SERR 0x0040
#define BUFSIZ 1024
#define EOF (-1)

extern int fflush(FILE *fp);

/* census __sbprintf, a file static (sce/libc/stdio/vfiprintf holds the global
   at 0x00280160); _vfprintf_r's stub calls it and the same-object definition
   binds first. */
static int __sbprintf(FILE *fp, const char *fmt, void *ap)
{
    int ret;
    FILE fake;
    unsigned char buf[BUFSIZ];

    /* copy the important variables */
    fake._data = fp->_data;
    fake._flags = fp->_flags & ~__SNBF;
    fake._file = fp->_file;
    fake._cookie = fp->_cookie;
    fake._write = fp->_write;

    /* set up the buffer */
    fake._bf._base = fake._p = buf;
    fake._bf._size = fake._w = sizeof(buf);
    fake._lbfsize = 0;

    /* do the work, then copy any error status */
    ret = vfprintf(&fake, fmt, ap);
    if (ret >= 0 && fflush(&fake))
        ret = EOF;
    if (fake._flags & __SERR)
        fp->_flags |= __SERR;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdio/vfprintf", vfprintf);
INCLUDE_ASM("asm/nonmatchings/sce/libc/stdio/vfprintf", _vfprintf_r);
INCLUDE_ASM("asm/nonmatchings/sce/libc/stdio/vfprintf", cvt);
INCLUDE_ASM("asm/nonmatchings/sce/libc/stdio/vfprintf", exponent);

extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void *_malloc_r(void *a0, int a1);
extern void memset(void *a0, int a1, int a2);
extern void _fwalk(int a0, void *a1);
extern int memcpy(char *a0, char *a1, int a2);
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
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
