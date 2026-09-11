#include "common.h"

extern void iosFree();
int huft_free(char *p);

struct huft {
    unsigned char e; /* 0x0 number of extra bits or operation */
    unsigned char b; /* 0x1 number of bits in this code or subcode */

    union {
        unsigned short n; /* 0x4 literal, length base or distance base */
        struct huft *t;   /* 0x4 pointer to the next level of table */
    } v;
};

typedef struct InflateWork {
    char unk00[0x48];
    int wp;                /* 0x48 window position */
    unsigned int insize;   /* 0x4C */
    unsigned int inptr;    /* 0x50 */
    struct huft *tl;       /* 0x54 */
    struct huft *td;       /* 0x58 */
    int bl;                /* 0x5C */
    int bd;                /* 0x60 */
    int unk64;             /* 0x64 */
    unsigned long long bb; /* 0x68 bit buffer */
    unsigned long long bk; /* 0x70 bits in buffer */
    int t;                 /* 0x78 block type, -1 = need a new header */
    int last;              /* 0x7C final block seen */
    int n;                 /* 0x80 bytes left in the current block */
    int copy_src;          /* 0x84 window read position of a running copy */
    struct huft *w_tl;     /* 0x88 also the "a huffman block is in progress" flag */
    struct huft *w_td;     /* 0x8C */
    int w_bl;              /* 0x90 */
    int w_bd;              /* 0x94 */
} InflateWork;

typedef struct InflateHandler {
    char unk00[0x8];
    unsigned char slide[0x10000]; /* 0x00008 sliding window */
    unsigned char inbuf[0x8000];  /* 0x10008 compressed input */
} InflateHandler;

#define IWORK(p) ((InflateWork *)((char *)(p) + 0x18000))
#define ISLIDE(p) (((InflateHandler *)(p))->slide)
#define IINBUF(p) (((InflateHandler *)(p))->inbuf)

static int fill_inbuf();

#define NEXTBYTE(w)                                                                                \
    (IWORK(w)->inptr < IWORK(w)->insize ? IINBUF(w)[IWORK(w)->inptr++] : fill_inbuf(w))
#define NEEDBITS(w, j)                                                                             \
    {                                                                                              \
        while (k < (j)) {                                                                          \
            b |= (unsigned long long)NEXTBYTE(w) << k;                                             \
            k += 8;                                                                                \
        }                                                                                          \
    }
#define MASKBITS(j) (((unsigned long long)1 << (j)) - 1)
#define DUMPBITS(j)                                                                                \
    {                                                                                              \
        b >>= (j);                                                                                 \
        k -= (j);                                                                                  \
    }

extern unsigned short D_0029B430[]; /* cplens */
extern unsigned short D_0029B470[]; /* cplext */
extern unsigned short D_0029B4B0[]; /* cpdist */
extern unsigned short D_0029B4F0[]; /* cpdext */
extern long long inflate_stored(void *w, unsigned char *out, long long outlen);
extern long long inflate_fixed(void *w, unsigned char *out, long long outlen);

#define BMAX 16
#define N_MAX 288

extern void *memset(void *s, int c, int n);
extern void *new_segment(void *mb, int size);
extern int iosMallocDebug(int a0, int a1, const char *file, int line);
extern int D_0063A464;
extern char D_00550FF0[];

INCLUDE_ASM("asm/nonmatchings/ios/inflate", huft_build);

extern int huft_build(unsigned int *b, unsigned int n, unsigned int s, unsigned short *d,
                      unsigned short *e, struct huft **t, int *m, void *mb);

/* huft_free sits at source lines 307-321, ahead of inflate_codes, yet the ROM
 * emits it LAST in the TU and inlines its body into inflate_fixed and
 * inflate_dynamic: it is an `inline` function, so gcc defers the out-of-line
 * copy to the end of the translation unit.  */
inline int huft_free(char *p)
{
    char *next;
    if (p == (char *)0)
        goto end;
    p -= 8;
    while (1) {
        next = *(char **)(p + 4);
        iosFree(p);
        p = next;
        if (p == (char *)0)
            break;
        p -= 8;
    }
end:
    return 0;
}

long long inflate_codes(void *w, unsigned char *out, long long outlen)
{
    unsigned int e;
    unsigned int n;
    unsigned int d;
    int wp;
    struct huft *t;
    struct huft *tl;
    struct huft *td;
    int bl;
    int bd;
    int nout;
    unsigned char *slide;
    unsigned long long b;
    unsigned long long k;

    b = IWORK(w)->bb;
    k = IWORK(w)->bk;
    if (outlen == 0)
        return 0;
    slide = ISLIDE(w);
    tl = IWORK(w)->w_tl;
    td = IWORK(w)->w_td;
    bl = IWORK(w)->w_bl;
    bd = IWORK(w)->w_bd;
    wp = IWORK(w)->wp;
    nout = 0;
    for (;;) {
        NEEDBITS(w, (unsigned int)bl)
        t = tl + (unsigned int)(b & MASKBITS(bl));
        e = t->e;
        if (e > 16) {
            do {
                if (e == 99)
                    return -1;
                DUMPBITS(t->b)
                e -= 16;
                NEEDBITS(w, e)
                t = t->v.t + (unsigned int)(b & MASKBITS(e));
                e = t->e;
            } while (e > 16);
        }
        DUMPBITS(t->b)
        if (e == 16) {
            wp &= 0x7fff;
            out[nout++] = slide[wp++] = (unsigned char)t->v.n;
            if (nout == outlen) {
                IWORK(w)->wp = wp;
                IWORK(w)->bb = b;
                IWORK(w)->bk = k;
                return outlen;
            }
        } else {
            if (e == 15)
                break;
            NEEDBITS(w, e)
            n = t->v.n + (unsigned int)(b & MASKBITS(e));
            DUMPBITS(e)
            NEEDBITS(w, (unsigned int)bd)
            t = td + (unsigned int)(b & MASKBITS(bd));
            e = t->e;
            if (e > 16) {
                do {
                    if (e == 99)
                        return -1;
                    DUMPBITS(t->b)
                    e -= 16;
                    NEEDBITS(w, e)
                    t = t->v.t + (unsigned int)(b & MASKBITS(e));
                    e = t->e;
                } while (e > 16);
            }
            DUMPBITS(t->b)
            NEEDBITS(w, e)
            d = wp - t->v.n - (unsigned int)(b & MASKBITS(e));
            DUMPBITS(e)
            while (n != 0 && nout < outlen) {
                n--;
                d &= 0x7fff;
                wp &= 0x7fff;
                out[nout++] = slide[wp++] = slide[d++];
            }
            if (nout == outlen) {
                IWORK(w)->n = n;
                IWORK(w)->wp = wp;
                IWORK(w)->copy_src = d;
                IWORK(w)->bb = b;
                IWORK(w)->bk = k;
                return outlen;
            }
        }
    }
    IWORK(w)->wp = wp;
    IWORK(w)->t = -1;
    IWORK(w)->bb = b;
    IWORK(w)->bk = k;
    return nout;
}

long long inflate_stored(void *w, unsigned char *out, long long outlen)
{
    unsigned int n;
    int wp;
    int cnt;
    unsigned int m;
    unsigned long long b;
    unsigned long long k;

    b = IWORK(w)->bb;
    k = IWORK(w)->bk;

    n = k & 7;
    DUMPBITS(n)

    NEEDBITS(w, 16)
    n = b & 0xffff;
    DUMPBITS(16)
    NEEDBITS(w, 16)
    m = ~b & 0xffff;
    if (n != m) {
        IWORK(w)->bb = b;
        IWORK(w)->bk = k;
        return -1;
    }
    DUMPBITS(16)

    IWORK(w)->n = n;

    n = 0;
    cnt = m;
    wp = IWORK(w)->wp;
    while (cnt != 0 && n < outlen) {
        cnt--;
        wp &= 0x7fff;
        NEEDBITS(w, 8)
        out[n++] = ISLIDE(w)[wp++] = (unsigned char)(b & 0xff);
        DUMPBITS(8)
    }
    if (cnt == 0)
        IWORK(w)->t = -1;
    IWORK(w)->n = cnt;
    IWORK(w)->wp = wp;
    IWORK(w)->bb = b;
    IWORK(w)->bk = k;
    return n;
}

long long inflate_fixed(void *w, unsigned char *out, long long outlen)
{
    int i;
    unsigned int l[288];

    if (IWORK(w)->tl == (struct huft *)0) {
        for (i = 0; i < 144; i++)
            l[i] = 8;
        for (i = 144; i < 256; i++)
            l[i] = 9;
        for (; i < 280; i++)
            l[i] = 7;
        for (; i < 288; i++)
            l[i] = 8;
        IWORK(w)->bl = 7;
        if ((i = huft_build(l, 288, 257, D_0029B430, D_0029B470, &IWORK(w)->tl, &IWORK(w)->bl,
                            (void *)0)) != 0) {
            IWORK(w)->tl = (struct huft *)0;
            return -1;
        }
        for (i = 0; i < 30; i++)
            l[i] = 5;
        IWORK(w)->bd = 5;
        if (huft_build(l, 30, 0, D_0029B4B0, D_0029B4F0, &IWORK(w)->td, &IWORK(w)->bd, (void *)0) >
            1) {
            huft_free((char *)IWORK(w)->tl);
            IWORK(w)->tl = (struct huft *)0;
            return -1;
        }
    }
    IWORK(w)->w_tl = IWORK(w)->tl;
    IWORK(w)->w_td = IWORK(w)->td;
    IWORK(w)->w_bl = IWORK(w)->bl;
    IWORK(w)->w_bd = IWORK(w)->bd;
    return inflate_codes(w, out, outlen);
}

INCLUDE_ASM("asm/nonmatchings/ios/inflate", inflate_dynamic);

extern void init_mblock(int *self);

void inflate_start(void *a0)
{
    int *w = (int *)((char *)a0 + 0x18000);
    w[0x78 / 4] = -1;
    w[0x48 / 4] = 0;
    *(long long *)((char *)w + 0x68) = 0;
    *(long long *)((char *)w + 0x70) = 0;
    w[0x50 / 4] = 0;
    w[0x4C / 4] = 0;
    w[0x54 / 4] = 0;
    w[0x58 / 4] = 0;
    w[0x7C / 4] = 0;
    w[0x84 / 4] = 0;
    w[0x80 / 4] = 0;
    w[0x88 / 4] = 0;
    init_mblock((char *)a0 + 0x18098);
}

extern int D_0063A464;
extern void iosMallocResetPartition(int a0);
extern void reuse_mblock(void *p);

void close_inflate_handler(void *a0)
{
    char *p;
    if (*(int *)((char *)a0 + 0x18054) != 0) {
        p = *(char **)((char *)a0 + 0x18058);
        if (p != 0) {
            p -= 8;
            for (;;) {
                char *node = p;
                p = *(char **)(p + 4);
                iosFree(node);
                if (p == 0)
                    break;
                p -= 8;
            }
        }
        p = *(char **)((char *)a0 + 0x18054);
        if (p != 0) {
            p -= 8;
            for (;;) {
                char *node = p;
                p = *(char **)(p + 4);
                iosFree(node);
                if (p == 0)
                    break;
                p -= 8;
            }
        }
        *(int *)((char *)a0 + 0x18054) = 0;
        *(int *)((char *)a0 + 0x18058) = 0;
    }
    reuse_mblock((char *)a0 + 0x18098);
    iosFree(a0);
    iosMallocResetPartition(D_0063A464);
}

extern int inflate_dynamic(void *w, unsigned char *out, long long outlen);

long long inflate(void *w, unsigned char *out, long long outlen)
{
    long long total;
    long long ret;
    int cnt;
    int wp;
    int src;

    total = 0;
    while (total < outlen) {
        if (IWORK(w)->last != 0 && IWORK(w)->t == -1)
            return total;

        if (IWORK(w)->n != 0) {
            cnt = IWORK(w)->n;
            wp = IWORK(w)->wp;
            if (IWORK(w)->t != 0) {
                src = IWORK(w)->copy_src;
                while (cnt != 0 && total < outlen) {
                    cnt--;
                    src &= 0x7fff;
                    wp &= 0x7fff;
                    out[total++] = ISLIDE(w)[wp++] = ISLIDE(w)[src++];
                }
                IWORK(w)->copy_src = src;
            } else {
                unsigned long long b;
                unsigned long long k;

                b = IWORK(w)->bb;
                k = IWORK(w)->bk;
                while (cnt != 0 && total < outlen) {
                    cnt--;
                    wp &= 0x7fff;
                    NEEDBITS(w, 8)
                    out[total++] = ISLIDE(w)[wp++] = (unsigned char)(b & 0xff);
                    DUMPBITS(8)
                }
                IWORK(w)->bb = b;
                IWORK(w)->bk = k;
                if (cnt == 0)
                    IWORK(w)->t = -1;
            }
            IWORK(w)->n = cnt;
            IWORK(w)->wp = wp;
            if (total == outlen)
                return total;
        }

        if (IWORK(w)->t == -1) {
            unsigned long long k;
            unsigned long long b;

            b = IWORK(w)->bb;
            k = IWORK(w)->bk;
            if (IWORK(w)->last != 0)
                return total;
            NEEDBITS(w, 1)
            if (b & 1)
                IWORK(w)->last = 1;
            DUMPBITS(1)
            NEEDBITS(w, 2)
            IWORK(w)->t = b & 3;
            DUMPBITS(2)
            IWORK(w)->w_tl = (struct huft *)0;
            IWORK(w)->n = 0;
            IWORK(w)->bb = b;
            IWORK(w)->bk = k;
        }

        switch (IWORK(w)->t) {
        case 0:
            ret = inflate_stored(w, out + total, outlen - total);
            break;
        case 1:
            if (IWORK(w)->w_tl != (struct huft *)0)
                ret = inflate_codes(w, out + total, outlen - total);
            else
                ret = inflate_fixed(w, out + total, outlen - total);
            break;
        case 2:
            if (IWORK(w)->w_tl != (struct huft *)0)
                ret = inflate_codes(w, out + total, outlen - total);
            else
                ret = inflate_dynamic(w, out + total, outlen - total);
            break;
        default:
            ret = -1;
            break;
        }

        if (ret == -1) {
            if (IWORK(w)->last != 0)
                return 0;
            return -1;
        }
        total += ret;
    }
    return total;
}

extern char D_00550FF0[];
extern char D_00551040[];
extern int D_0063A450;
extern int D_0063A470;
extern void debug_StdPrintfDummy();

int open_inflate_handler(int a0, int a1)
{
    int g = D_0063A450;
    int *s1;
    D_0063A464 = g;
    D_0063A470 = 0;
    s1 = (int *)iosMallocDebug(g, 0x180A8, D_00550FF0, 0x2E3);
    inflate_start(s1);
    s1[0] = a1;
    if (a0 == 0) {
        debug_StdPrintfDummy(D_00551040);
    } else {
        s1[0x4 / 4] = a0;
    }
    return (int)s1;
}

/* The inflate handler block carries the gzip-style input buffer at +0x10008
 * and the decoder state at +0x18000 (insize at +0x4C, inptr at +0x50); the
 * read callback and the handle it is given live at +0x4 and +0x0.  The
 * callback's 64-bit size/return are the ones inflate_cd_read_func uses.  */
#define INFLATE_INBUF(p) ((unsigned char *)(p) + 0x10008)
#define INFLATE_STATE(p) ((unsigned int *)((char *)(p) + 0x18000))

typedef long long (*InflateReadFn)(void *buf, long long size, void *handle);

static int fill_inbuf(void *a0)
{
    int len;

    INFLATE_STATE(a0)[0x4C / 4] = 0;
    do {
        len = (*(InflateReadFn *)((char *)a0 + 4))(INFLATE_INBUF(a0) + INFLATE_STATE(a0)[0x4C / 4],
                                                   0x8000 - INFLATE_STATE(a0)[0x4C / 4],
                                                   *(void **)a0);
        if (len == 0 || len == -1)
            break;
        INFLATE_STATE(a0)[0x4C / 4] += len;
    } while (INFLATE_STATE(a0)[0x4C / 4] < 0x8000);
    if (INFLATE_STATE(a0)[0x4C / 4] == 0)
        return -1;
    INFLATE_STATE(a0)[0x50 / 4] = 1;
    return INFLATE_INBUF(a0)[0];
}
