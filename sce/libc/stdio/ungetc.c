/* libc.a member ungetc.o.  MAIN.MAP member spans tile this run exactly and
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
extern void *_malloc_r(void *r, int n);
extern void *_realloc_r(void *r, void *p, int n);
extern void *memcpy(void *d, const void *s, unsigned int n);

/* newlib's struct __sbuf / struct __sFILE, reconstructed from the ROM's own
   field offsets in this member (evidence rung: ROM bytes; the newlib member
   layout gives the names).  Only this member needs the typed form: the loop
   below copies fp->ubuf[i] and gcc hoists the address only when the field is a
   real array member of a struct type, which is what puts ROM's preheader copy
   of _ub._base in place of a load. */
typedef struct {
    unsigned char *base; /* 0x0 */
    int size;            /* 0x4 */
} Sbuf;

typedef struct Fil {
    unsigned char *p;      /* 0x00 */
    int r;                 /* 0x04 */
    int w;                 /* 0x08 */
    short flags;           /* 0x0C */
    short file;            /* 0x0E */
    Sbuf bf;               /* 0x10 */
    int lbfsize;           /* 0x18 */
    char pad1C[0x14];      /* 0x1C */
    Sbuf ub;               /* 0x30 */
    unsigned char *up;     /* 0x38 */
    int ur;                /* 0x3C */
    unsigned char ubuf[3]; /* 0x40 */
    unsigned char nbuf[1]; /* 0x43 */
    Sbuf lb;               /* 0x44 */
    int blksize;           /* 0x4C */
    int offset;            /* 0x50 */
    void *data;            /* 0x54 */
} Fil;

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

int ungetc(int c, char *fp)
{
    if (c == -1)
        return -1;
    /* newlib's CHECK_INIT(fp), a do-while-zero macro wrapper */
    do {
        if (*(char **)(fp + 0x54) == 0)
            *(char **)(fp + 0x54) = (char *)D_0054CEAC[0];
        if (*(int *)(*(char **)(fp + 0x54) + 0x38) == 0)
            __sinit(*(char **)(fp + 0x54));
    } while (0);
    *(short *)(fp + 0xC) = *(unsigned short *)(fp + 0xC) & ~0x20;
    if ((*(unsigned short *)(fp + 0xC) & 4) == 0) {
        if ((*(unsigned short *)(fp + 0xC) & 0x10) == 0)
            return -1;
        if (*(unsigned short *)(fp + 0xC) & 8) {
            if (fflush(fp))
                return -1;
            *(short *)(fp + 0xC) = *(unsigned short *)(fp + 0xC) & ~8;
            *(int *)(fp + 0x8) = 0;
            *(int *)(fp + 0x18) = 0;
        }
        *(short *)(fp + 0xC) = *(unsigned short *)(fp + 0xC) | 4;
    }
    c = (unsigned char)c;
    if (*(char **)(fp + 0x30) != 0) {
        if (*(int *)(fp + 0x4) >= *(int *)(fp + 0x34) && __submore(fp))
            return -1;
        *--*(unsigned char **)(fp + 0x0) = c;
        *(int *)(fp + 0x4) += 1;
        return c;
    }
    if (*(char **)(fp + 0x10) != 0 &&
        *(unsigned char **)(fp + 0x0) > *(unsigned char **)(fp + 0x10) &&
        (*(unsigned char **)(fp + 0x0))[-1] == c) {
        *(unsigned char **)(fp + 0x0) -= 1;
        *(int *)(fp + 0x4) += 1;
        return c;
    }
    *(int *)(fp + 0x3C) = *(int *)(fp + 0x4);
    *(char **)(fp + 0x38) = *(char **)(fp + 0x0);
    *(char **)(fp + 0x30) = fp + 0x40;
    *(int *)(fp + 0x34) = 3;
    *(char *)(fp + 0x42) = c;
    *(char **)(fp + 0x0) = fp + 0x42;
    *(int *)(fp + 0x4) = 1;
    return c;
}
