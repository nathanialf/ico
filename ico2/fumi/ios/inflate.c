#include "common.h"
#include "inflate.h"
#include "debug.h"
#include "mblock.h"
#include "memory.h"
#include <string.h>

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

/* .data, the first four objects of inflate.o's run (MAIN.MAP sizes the member
   0x14C, which is exactly these four plus the border table below, each one
   8-aligned).  The deflate code tables: copy length and extra-bit count per
   literal code 257..285, then copy offset and extra-bit count per distance
   code 0..29.  99 marks an invalid code. */
static unsigned short cplens[31] = {3,  4,   5,   6,   7,   8,   9,   10, 11, 13, 15,
                                    17, 19,  23,  27,  31,  35,  43,  51, 59, 67, 83,
                                    99, 115, 131, 163, 195, 227, 258, 0,  0};

static unsigned short cplext[31] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2,  2, 2,
                                    3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 99, 99};

static unsigned short cpdist[30] = {1,    2,    3,    4,    5,    7,    9,    13,    17,    25,
                                    33,   49,   65,   97,   129,  193,  257,  385,   513,   769,
                                    1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577};

static unsigned short cpdext[30] = {0, 0, 0, 0, 1, 1, 2, 2,  3,  3,  4,  4,  5,  5,  6,
                                    6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};

#define BMAX 16
#define N_MAX 288

extern int D_0063A464;

int huft_build(unsigned int *b, unsigned int n, unsigned int s, unsigned short *d,
               unsigned short *e, struct huft **t, int *m, void *mb)
{
    unsigned int a;           /* counter for codes of length k */
    unsigned int c[BMAX + 1]; /* bit length count table */
    unsigned int el;          /* length of EOB code (value 256) */
    unsigned int f;           /* i repeats in table every f entries */
    int g;                    /* maximum code length */
    int h;                    /* table level */
    register unsigned int i;  /* counter, current code */
    register unsigned int j;  /* counter */
    register int k;           /* number of bits in current code */
    int lx[BMAX + 1];         /* memory for l[-1..BMAX-1] */
    int *l = lx + 1;          /* stack of bits per table */
    register unsigned int *p; /* pointer into c[], b[], or v[] */
    register struct huft *q;  /* points to current table */
    struct huft r;            /* table entry for structure assignment */
    struct huft *u[BMAX];     /* table stack */
    unsigned int v[N_MAX];    /* values in order of bit length */
    register int w;           /* bits before this table == (l * h) */
    unsigned int x[BMAX + 1]; /* bit offsets, then code stack */
    unsigned int *xp;         /* pointer into x */
    int y;                    /* number of dummy codes added */
    unsigned int z;           /* number of entries in current table */

    /* Generate counts for each bit length */
    el = n > 256 ? b[256] : BMAX; /* set length of EOB code, if any */
    memset((char *)c, 0, sizeof(c));
    p = b;
    i = n;
    do {
        c[*p]++; /* assume all entries <= BMAX */
        p++;
    } while (--i);
    if (c[0] == n) { /* null input, all zero length codes */
        *t = (struct huft *)0;
        *m = 0;
        return 0;
    }

    /* Find minimum and maximum length, bound *m by those */
    for (j = 1; j <= BMAX; j++)
        if (c[j])
            break;
    k = j; /* minimum code length */
    if ((unsigned int)*m < j)
        *m = j;
    for (i = BMAX; i; i--)
        if (c[i])
            break;
    g = i; /* maximum code length */
    if ((unsigned int)*m > i)
        *m = i;

    /* Adjust last length count to fill out codes, if needed */
    for (y = 1 << j; j < i; j++, y <<= 1)
        if ((y -= c[j]) < 0)
            return 2; /* bad input: more codes than bits */
    if ((y -= c[i]) < 0)
        return 2;
    c[i] += y;

    /* Generate starting offsets into the value table for each length */
    x[1] = j = 0;
    p = c + 1;
    xp = x + 2;
    while (--i) { /* note that i == g from above */
        *xp++ = (j += *p++);
    }

    /* Make a table of values in order of bit lengths */
    memset((char *)v, 0, sizeof(v));
    p = b;
    i = 0;
    do {
        if ((j = *p++) != 0)
            v[x[j]++] = i;
    } while (++i < n);
    n = x[g]; /* set n to length of v */

    /* Generate the Huffman codes and for each, make the table entries */
    x[0] = i = 0;            /* first Huffman code is zero */
    p = v;                   /* grab values in bit order */
    h = -1;                  /* no tables yet, level -1 */
    w = l[-1] = 0;           /* no bits decoded yet */
    u[0] = (struct huft *)0; /* just to keep compilers happy */
    q = (struct huft *)0;    /* ditto */
    z = 0;                   /* ditto */

    /* go through the bit lengths (k already is bits in shortest code) */
    for (; k <= g; k++) {
        a = c[k];
        while (a--) {
            /* here i is the Huffman code of length k bits for value *p */
            /* make tables up to required level */
            while (k > w + l[h]) {
                w += l[h++]; /* add bits already decoded */

                /* compute minimum size table less than or equal to *m bits */
                z = (z = g - w) > (unsigned int)*m ? (unsigned int)*m : z;
                if ((f = 1 << (j = k - w)) > a + 1) { /* try a k-w bit table */
                    f -= a + 1;                       /* deduct codes from patterns left */
                    xp = c + k;
                    while (++j < z) { /* try smaller tables up to z bits */
                        if ((f <<= 1) <= *++xp)
                            break; /* enough codes to use up j bits */
                        f -= *xp;  /* else deduct codes from patterns */
                    }
                }
                if (w + j > el && w < el) /* here j == the table size in bits */
                    j = el - w;           /* make EOB code end at table */
                z = 1 << j;               /* table entries for j-bit table */
                l[h] = j;                 /* set table size in stack */

                /* allocate and link in new table */
                if (mb == 0)
                    q = (struct huft *)iosMallocDebug(D_0063A464, (z + 1) * sizeof(struct huft),
                                                      __FILE__, 241);
                else
                    q = (struct huft *)new_segment(mb, (z + 1) * sizeof(struct huft));
                if (q == (struct huft *)0) {
                    if (h && mb == 0)
                        huft_free((char *)u[0]);
                    return 3; /* not enough memory */
                }
                *t = q + 1; /* link to list for huft_free() */
                *(t = &(q->v.t)) = (struct huft *)0;
                u[h] = ++q; /* table starts after link */

                /* connect to last table, if there is one */
                if (h) {
                    x[h] = i;                      /* save pattern for backing up */
                    r.b = (unsigned char)l[h - 1]; /* bits to dump before this table */
                    r.e = (unsigned char)(16 + j); /* bits in this table */
                    r.v.t = q;                     /* pointer to this table */
                    j = (i & ((1 << w) - 1)) >> (w - l[h - 1]);
                    u[h - 1][j] = r; /* connect to last table */
                }
            }

            /* set up table entry in r */
            r.b = (unsigned char)(k - w);
            if (p >= v + n)
                r.e = 99; /* out of values, invalid code */
            else if (*p < s) {
                r.e = (unsigned char)(*p < 256 ? 16 : 15); /* 256 is end-of-block code */
                r.v.n = (unsigned short)*p;                /* simple code is just the value */
                p++;
            } else {
                r.e = (unsigned char)e[*p - s]; /* non-simple, look up in lists */
                r.v.n = d[*p++ - s];
            }

            /* fill code-like entries with r */
            f = 1 << (k - w);
            for (j = i >> w; j < z; j += f)
                q[j] = r;

            /* backwards increment the k-bit code i */
            for (j = 1 << (k - 1); i & j; j >>= 1)
                i ^= j;
            i ^= j;

            /* backup over finished tables */
            while ((i & ((1 << w) - 1)) != x[h]) {
                h--; /* don't need to update q */
                w -= l[h];
            }
        }
    }

    /* return actual size of base table */
    *m = l[0];

    /* Return true (1) if we were given an incomplete table */
    return y != 0 && g != 1;
}

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
        if ((i = huft_build(l, 288, 257, cplens, cplext, &IWORK(w)->tl, &IWORK(w)->bl,
                            (void *)0)) != 0) {
            IWORK(w)->tl = (struct huft *)0;
            return -1;
        }
        for (i = 0; i < 30; i++)
            l[i] = 5;
        IWORK(w)->bd = 5;
        if (huft_build(l, 30, 0, cpdist, cpdext, &IWORK(w)->td, &IWORK(w)->bd, (void *)0) > 1) {
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

/* .data, the last object of inflate.o's run: the order the bit length code
   lengths arrive in. */
static int border[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};

#define IMB(w) ((void *)((char *)(w) + 0x18098))

int inflate_dynamic(void *w, unsigned char *out, long long outlen)
{
    int i;
    unsigned int j;
    unsigned int l;
    unsigned int n;
    struct huft *tl;
    struct huft *td;
    int bl;
    int bd;
    unsigned int nb;
    unsigned int nl;
    unsigned int nd;
    unsigned int ll[286 + 30];
    unsigned long long k;
    unsigned long long b;

    b = IWORK(w)->bb;
    k = IWORK(w)->bk;
    reuse_mblock(IMB(w));

    NEEDBITS(w, 5)
    nl = 257 + (b & 0x1f);
    DUMPBITS(5)
    NEEDBITS(w, 5)
    nd = 1 + (b & 0x1f);
    DUMPBITS(5)
    NEEDBITS(w, 4)
    nb = 4 + (b & 0xf);
    DUMPBITS(4)
    if (nl > 286 || nd > 30) {
        IWORK(w)->bb = b;
        IWORK(w)->bk = k;
        return -1;
    }

    for (j = 0; j < nb; j++) {
        NEEDBITS(w, 3)
        ll[border[j]] = (unsigned int)(b & 7);
        DUMPBITS(3)
    }
    for (; j < 19; j++)
        ll[border[j]] = 0;

    bl = 7;
    if ((i = huft_build(ll, 19, 19, (unsigned short *)0, (unsigned short *)0, &tl, &bl, IMB(w))) !=
        0) {
        reuse_mblock(IMB(w));
        IWORK(w)->bb = b;
        IWORK(w)->bk = k;
        return -1;
    }

    n = nl + nd;
    i = l = 0;
    while ((unsigned int)i < n) {
        NEEDBITS(w, (unsigned int)bl)
        j = (td = tl + (unsigned int)(b & MASKBITS(bl)))->b;
        DUMPBITS(j)
        j = td->v.n;
        if (j < 16) {
            ll[i++] = l = j;
        } else if (j == 16) {
            NEEDBITS(w, 2)
            j = 3 + (b & 3);
            DUMPBITS(2)
            if ((unsigned int)i + j > n) {
                IWORK(w)->bb = b;
                IWORK(w)->bk = k;
                return -1;
            }
            while (j--)
                ll[i++] = l;
        } else if (j == 17) {
            NEEDBITS(w, 3)
            j = 3 + (b & 7);
            DUMPBITS(3)
            if ((unsigned int)i + j > n) {
                IWORK(w)->bb = b;
                IWORK(w)->bk = k;
                return -1;
            }
            while (j--)
                ll[i++] = 0;
            l = 0;
        } else {
            NEEDBITS(w, 7)
            j = 11 + (b & 0x7f);
            DUMPBITS(7)
            if ((unsigned int)i + j > n) {
                IWORK(w)->bb = b;
                IWORK(w)->bk = k;
                return -1;
            }
            while (j--)
                ll[i++] = 0;
            l = 0;
        }
    }

    IWORK(w)->bb = b;
    IWORK(w)->bk = k;
    reuse_mblock(IMB(w));

    bl = 9;
    i = huft_build(ll, nl, 257, cplens, cplext, &tl, &bl, IMB(w));
    if (bl == 0)
        i = 1;
    if (i != 0) {
        if (i == 1)
            debug_StdPrintfDummy(" incomplete literal tree\n");
        reuse_mblock(IMB(w));
        return -1;
    }

    bd = 6;
    i = huft_build(ll + nl, nd, 0, cpdist, cpdext, &td, &bd, IMB(w));
    if (bd == 0 && nl > 257) {
        debug_StdPrintfDummy(" incomplete distance tree\n");
        reuse_mblock(IMB(w));
        return -1;
    }
    if (i == 1)
        debug_StdPrintfDummy(" incomplete distance tree\n");
    if (i != 0) {
        reuse_mblock(IMB(w));
        return -1;
    }

    IWORK(w)->w_tl = tl;
    IWORK(w)->w_td = td;
    IWORK(w)->w_bl = bl;
    IWORK(w)->w_bd = bd;
    i = inflate_codes(w, out, outlen);
    if (i == -1) {
        reuse_mblock(IMB(w));
        return -1;
    }
    return i;
}

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

extern int D_0063A450;
extern int D_0063A470;

int open_inflate_handler(int a0, int a1)
{
    int g = D_0063A450;
    int *s1;
    D_0063A464 = g;
    D_0063A470 = 0;
    s1 = (int *)iosMallocDebug(g, 0x180A8, __FILE__, 739);
    inflate_start(s1);
    s1[0] = a1;
    if (a0 == 0) {
        debug_StdPrintfDummy("read func not entry\n");
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
