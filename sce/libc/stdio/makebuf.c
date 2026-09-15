/* libc.a member makebuf.o.  MAIN.MAP member spans tile this run exactly and
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

struct _reent {
    char pad000[0x3C]; /* 0x00 */
    void *__cleanup;   /* 0x3C */
};

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
    void *_read;            /* 0x20 */
    void *_write;           /* 0x24 */
    void *_seek;            /* 0x28 */
    void *_close;           /* 0x2C */
    struct __sbuf _ub;      /* 0x30 */
    unsigned char *_up;     /* 0x38 */
    int _ur;                /* 0x3C */
    unsigned char _ubuf[3]; /* 0x40 */
    unsigned char _nbuf[1]; /* 0x43 */
    struct __sbuf _lb;      /* 0x44 */
    int _blksize;           /* 0x4C */
    int _offset;            /* 0x50 */
    struct _reent *_data;   /* 0x54 */
} __FILE;

/* Only st_mode is reached here, at 0x04; the 0x70 size is what the ROM's
   0xB0 frame proves (locals 0x00..0x70, callee-saved homes above it).  The
   trailing bytes are padding, not an attested field layout. */
struct stat {
    short st_dev;          /* 0x00 */
    unsigned short st_ino; /* 0x02 */
    unsigned int st_mode;  /* 0x04 */
    char pad008[0x68];     /* 0x08 */
};

#define __SLBF 0x0001
#define __SNBF 0x0002
#define __SOPT 0x0400
#define __SNPT 0x0800
#define __SMOD 0x0080
#define S_IFMT 0xF000
#define S_IFCHR 0x2000
#define S_IFREG 0x8000
#define BUFSIZ 1024

extern int _fstat_r(struct _reent *ptr, int fd, struct stat *st);
extern void *_malloc_r(struct _reent *ptr, unsigned int size);
extern int isatty(int fd);
extern long __sseek(void *a0, int a1, int a2);
extern void _cleanup_r(struct _reent *ptr);

void __smakebuf(__FILE *fp)
{
    unsigned int size;
    int couldbetty;
    void *p;
    struct stat st;

    if (fp->_flags & __SNBF) {
        fp->_bf._base = fp->_p = fp->_nbuf;
        fp->_bf._size = 1;
        return;
    }
    if (fp->_file < 0 || _fstat_r(fp->_data, fp->_file, &st) < 0) {
        couldbetty = 0;
        size = BUFSIZ;
        fp->_flags |= __SNPT;
    } else {
        couldbetty = (st.st_mode & S_IFMT) == S_IFCHR;
        size = BUFSIZ;
        if ((st.st_mode & S_IFMT) == S_IFREG && fp->_seek == (void *)__sseek) {
            fp->_blksize = size;
            fp->_flags |= __SOPT;
        } else {
            fp->_flags |= __SNPT;
        }
    }
    if ((p = _malloc_r(fp->_data, size)) == 0) {
        fp->_flags |= __SNBF;
        fp->_bf._base = fp->_p = fp->_nbuf;
        fp->_bf._size = 1;
        return;
    }
    fp->_data->__cleanup = (void *)_cleanup_r;
    fp->_flags |= __SMOD;
    fp->_bf._base = fp->_p = (unsigned char *)p;
    fp->_bf._size = size;
    if (couldbetty && isatty(fp->_file)) {
        fp->_flags |= __SLBF;
    }
}
