/* libc.a member vfiprintf.o.  MAIN.MAP member spans tile this run exactly and
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
extern int strtok_r(int a0, int a1, int a2);
extern int __sfvwrite();

int __sprint(int a0, int *a1)
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

/* newlib's struct __sFILE for this build; the tail padding is what puts
   __sbprintf's 0x400-byte buffer at sp+0x60 behind the fake FILE at sp+0. */
typedef struct {
    char *_p;               /* 0x0 */
    int _r;                 /* 0x4 */
    int _w;                 /* 0x8 */
    short _flags;           /* 0xC */
    short _file;            /* 0xE */
    char *_bf_base;         /* 0x10 */
    int _bf_size;           /* 0x14 */
    int _lbfsize;           /* 0x18 */
    void *_cookie;          /* 0x1C */
    int _read;              /* 0x20 */
    int _write;             /* 0x24 */
    int _seek;              /* 0x28 */
    int _close;             /* 0x2C */
    char *_ub_base;         /* 0x30 */
    int _ub_size;           /* 0x34 */
    char *_up;              /* 0x38 */
    int _ur;                /* 0x3C */
    unsigned char _ubuf[3]; /* 0x40 */
    unsigned char _nbuf[1]; /* 0x43 */
    char *_lb_base;         /* 0x44 */
    int _lb_size;           /* 0x48 */
    int _blksize;           /* 0x4C */
    int _offset;            /* 0x50 */
    void *_data;            /* 0x54 */
} FileS;

extern int fflush();
extern int vfiprintf(char *fp, char *fmt, void *ap);

int __sbprintf(FileS *fp, char *fmt, void *ap)
{
    FileS fake;
    unsigned char buf[0x400];
    int ret;

    /* copy the important variables */
    fake._data = fp->_data;
    fake._flags = fp->_flags & ~2;
    fake._file = fp->_file;
    fake._cookie = fp->_cookie;
    fake._write = fp->_write;

    /* set up the buffer */
    fake._bf_base = fake._p = (char *)buf;
    fake._bf_size = fake._w = sizeof(buf);
    fake._lbfsize = 0;

    /* do the work, then copy any error status */
    ret = vfiprintf((char *)&fake, fmt, ap);
    if (ret >= 0 && fflush(&fake)) {
        ret = -1;
    }
    if (fake._flags & 0x40) {
        fp->_flags |= 0x40;
    }
    return ret;
}

extern void __sinit(void *r);
extern int _vfiprintf_r(void *r, char *fp, char *fmt, void *ap);

int vfiprintf(char *fp, char *fmt0, void *ap)
{
    /* newlib's CHECK_INIT(fp), a do-while-zero macro wrapper */
    do {
        if (*(char **)(fp + 0x54) == 0)
            *(char **)(fp + 0x54) = (char *)D_0054CEAC[0];
        if (*(int *)(*(char **)(fp + 0x54) + 0x38) == 0)
            __sinit(*(char **)(fp + 0x54));
    } while (0);
    return _vfiprintf_r(*(char **)(fp + 0x54), fp, fmt0, ap);
}

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdio/vfiprintf", _vfiprintf_r);

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
