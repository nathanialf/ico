/* libc.a member mprec.o.  MAIN.MAP member spans tile this run exactly and
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
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);
extern int _vfprintf_r(int *self, int subj, int b, void *args);
extern int strtok_r(int a0, int a1, int a2);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void *_malloc_r(void *a0, int a1);
extern void _fwalk(int a0, void *a1);
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);

/* newlib Bigint: _next, _k, _maxwds, _sign, _wds, then the word array. */
typedef struct _Bigint {
    struct _Bigint *next; /* 0x00 */
    int k;                /* 0x04 */
    int maxwds;           /* 0x08 */
    int sign;             /* 0x0C */
    int wds;              /* 0x10 */
    unsigned int x[1];    /* 0x14 */
} Bigint;

extern void *_calloc_r(void *ptr, int n, int size);

/* the _reent slot the Bigint free list hangs off, at 0x4C */
typedef struct {
    char pad0[0x48];
    Bigint *p5s;       /* 0x48 */
    Bigint **freelist; /* 0x4C */
} MpReent;

int *_Balloc(void *ptr, int k)
{
    MpReent *r = (MpReent *)ptr;
    Bigint *rv;
    int x;

    if (r->freelist == 0) {
        r->freelist = (Bigint **)_calloc_r(ptr, 4, 16);
        if (r->freelist == 0) {
            return 0;
        }
    }
    rv = r->freelist[k];
    if (rv != 0) {
        r->freelist[k] = rv->next;
    } else {
        x = 1 << k;
        rv = (Bigint *)_calloc_r(ptr, 1, sizeof(Bigint) + (x - 1) * sizeof(int));
        if (rv == 0) {
            return 0;
        }
        rv->k = k;
        rv->maxwds = x;
    }
    rv->sign = rv->wds = 0;
    return (int *)rv;
}

void _Bfree(char *a0, int *a1)
{
    if (a1) {
        int off = a1[1] * 4;
        int *slot;
        a0 = *(char **)(a0 + 0x4C);
        off += (int)a0;
        slot = (int *)off;
        a1[0] = slot[0];
        slot[0] = (int)a1;
    }
}

int *_multadd(void *ptr, Bigint *b, int m, int a)
{
    Bigint *b1;
    unsigned int *x;
    unsigned int xi, y, z;
    int i, wds;

    wds = b->wds;
    x = b->x;
    i = 0;
    do {
        xi = *x;
        y = (xi & 0xFFFF) * m + a;
        z = (xi >> 16) * m + (y >> 16);
        a = (int)(z >> 16);
        *x++ = (z << 16) + (y & 0xFFFF);
    } while (++i < wds);
    if (a != 0) {
        if (wds >= b->maxwds) {
            b1 = (Bigint *)_Balloc(ptr, b->k + 1);
            memcpy((char *)&b1->sign, (char *)&b->sign, b->wds * 4 + 8);
            _Bfree(ptr, (int *)b);
            b = b1;
        }
        b->x[wds++] = a;
        b->wds = wds;
    }
    return (int *)b;
}

extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, Bigint *a1, int a2, int a3);

int _s2b(void *a0, char *a1, int a2, int a3, int a4)
{
    int n3 = (a3 + 8) / 9;
    int p = 1;
    int five = 0;
    int i18;
    int *r5;
    int i17;

    if (p < n3) {
        do {
            p <<= 1;
            five++;
        } while (p < n3);
    }
    i18 = a2 < 10;
    r5 = _Balloc(a0, five);
    i17 = 9;
    r5[5] = a4;
    r5[4] = 1;
    if (i18 == 0) {
        a1 += 9;
        do {
            i17++;
            r5 = _multadd(a0, (Bigint *)r5, 10, a1[0] - 0x30);
            a1++;
        } while (i17 < a2);
        a1++;
    } else {
        a1 += 10;
    }
    if (i17 < a3) {
        i17 = a3 - i17;
        do {
            r5 = _multadd(a0, (Bigint *)r5, 10, a1[0] - 0x30);
            a1++;
            i17--;
        } while (i17 != 0);
    }
    return (int)r5;
}

int _hi0bits(unsigned int a0)
{
    int n = 0;
    if ((a0 & 0xFFFF0000) == 0) {
        n = 16;
        a0 <<= 16;
    }
    if ((a0 & 0xFF000000) == 0) {
        n += 8;
        a0 <<= 8;
    }
    if ((a0 & 0xF0000000) == 0) {
        n += 4;
        a0 <<= 4;
    }
    if ((a0 & 0xC0000000) == 0) {
        n += 2;
        a0 <<= 2;
    }
    if ((int)a0 >= 0) {
        n += 1;
        if ((a0 & 0x40000000) == 0) {
            return 0x20;
        }
    }
    return n;
}

int _lo0bits(int *p)
{
    unsigned int v = *p;
    int n;
    if (v & 7) {
        if (v & 1) {
            return 0;
        }
        if (v & 2) {
            *p = v >> 1;
            return 1;
        }
        *p = v >> 2;
        return 2;
    }
    n = 0;
    if ((v & 0xFFFF) == 0) {
        n = 0x10;
        v >>= 16;
    }
    if ((v & 0xFF) == 0) {
        n += 8;
        v >>= 8;
    }
    if ((v & 0xF) == 0) {
        n += 4;
        v >>= 4;
    }
    if ((v & 3) == 0) {
        n += 2;
        v >>= 2;
    }
    if (v & 1) {
        *p = v;
    } else {
        v >>= 1;
        n += 1;
        if (v == 0) {
            return 0x20;
        }
        *p = v;
    }
    return n;
}

void *_i2b(void *a0, int a1)
{
    int *r = _Balloc(a0, 1);
    r[5] = a1;
    r[4] = 1;
    return r;
}

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mprec", _multiply);

extern const int D_00638890[];
extern int *_multiply(void *ptr, Bigint *a, Bigint *b);

int *_pow5mult(void *ptr, Bigint *b, int k)
{
    MpReent *r = (MpReent *)ptr;
    Bigint *b1;
    Bigint *p5;
    Bigint *p51;
    int i;

    i = k & 3;
    if (i != 0) {
        b = (Bigint *)_multadd(ptr, b, D_00638890[i - 1], 0);
    }
    k >>= 2;
    if (k == 0) {
        return (int *)b;
    }
    p5 = r->p5s;
    if (p5 == 0) {
        p5 = r->p5s = (Bigint *)_i2b(ptr, 625);
        p5->next = 0;
    }
    for (;;) {
        if (k & 1) {
            b1 = (Bigint *)_multiply(ptr, b, p5);
            _Bfree(ptr, (int *)b);
            b = b1;
        }
        k >>= 1;
        if (k == 0) {
            break;
        }
        p51 = p5->next;
        if (p51 == 0) {
            p51 = p5->next = (Bigint *)_multiply(ptr, p5, p5);
            p51->next = 0;
        }
        p5 = p51;
    }
    return (int *)b;
}

int *_lshift(void *ptr, Bigint *b, int k)
{
    int i, k1, n, n1;
    Bigint *b1;
    unsigned int *x, *x1, *xe, z;

    n = k >> 5;
    k1 = b->k;
    n1 = n + b->wds + 1;
    for (i = b->maxwds; n1 > i; i <<= 1) {
        k1++;
    }
    b1 = (Bigint *)_Balloc(ptr, k1);
    x1 = b1->x;
    for (i = 0; i < n; i++) {
        *x1++ = 0;
    }
    x = b->x;
    xe = x + b->wds;
    if (k &= 0x1F) {
        k1 = 32 - k;
        z = 0;
        do {
            *x1++ = *x << k | z;
            z = *x++ >> k1;
        } while (x < xe);
        if ((*x1 = z) != 0) {
            ++n1;
        }
    } else {
        do {
            *x1++ = *x++;
        } while (x < xe);
    }
    b1->wds = n1 - 1;
    _Bfree(ptr, (int *)b);
    return (int *)b1;
}

int __mcmp(unsigned int *a, unsigned int *b)
{
    int n = a[4] - b[4];
    unsigned int *pa, *pb, *pae, *pbe;
    if (n != 0)
        return n;
    n = b[4];
    pa = a + 5;
    pb = b + 5;
    pae = pa + n;
    pbe = pb + n;
    do {
        --pae;
        --pbe;
        if (*pae != *pbe)
            return (*pae < *pbe) ? -1 : 1;
    } while (pa < pae);
    return 0;
}

/* newlib mprec.h Storeinc for a little-endian target: the two halves of the
   word go out as halfword stores. */
#define Storeinc(a, b, c)                                                                          \
    (((unsigned short *)(a))[1] = (unsigned short)(b),                                             \
     ((unsigned short *)(a))[0] = (unsigned short)(c), (a)++)

int *__mdiff(void *ptr, Bigint *a, Bigint *b)
{
    Bigint *c;
    int i, wa, wb;
    int borrow, y, z;
    unsigned int *xa, *xae, *xb, *xbe, *xc;

    i = __mcmp((unsigned int *)a, (unsigned int *)b);
    if (i == 0) {
        c = (Bigint *)_Balloc(ptr, 0);
        c->wds = 1;
        c->x[0] = 0;
        return (int *)c;
    }
    if (i < 0) {
        c = a;
        a = b;
        b = c;
        i = 1;
    } else {
        i = 0;
    }
    c = (Bigint *)_Balloc(ptr, a->k);
    c->sign = i;
    wa = a->wds;
    xa = a->x;
    xae = xa + wa;
    wb = b->wds;
    xb = b->x;
    xbe = xb + wb;
    xc = c->x;
    borrow = 0;
    do {
        y = (*xa & 0xFFFF) - (*xb & 0xFFFF) + borrow;
        borrow = y >> 16;
        z = (*xa++ >> 16) - (*xb++ >> 16) + borrow;
        borrow = z >> 16;
        Storeinc(xc, z, y);
    } while (xb < xbe);
    while (xa < xae) {
        y = (*xa & 0xFFFF) + borrow;
        borrow = y >> 16;
        z = (*xa++ >> 16) + borrow;
        borrow = z >> 16;
        Storeinc(xc, z, y);
    }
    while (*--xc == 0) {
        wa--;
    }
    c->wds = wa;
    return (int *)c;
}

/* newlib mprec.c ulp(): the double is one 64-bit register here, and the
   word0/word1 halves of the newlib source are a union, so gcc rewrites the
   halves as shifts and masks instead of a stack home. */
typedef union {
    double d;
    unsigned int i[2];
} MpDouble;

#define word0(x) ((x).i[1])
#define word1(x) ((x).i[0])

double _ulp(double xx)
{
    MpDouble x;
    MpDouble a;
    int L;

    x.d = xx;
    L = (word0(x) & 0x7FF00000) - 0x3400000;
    if (L > 0) {
        word0(a) = L;
        word1(a) = 0;
    } else {
        L = -L >> 20;
        if (L < 20) {
            word0(a) = 0x80000 >> L;
            word1(a) = 0;
        } else {
            word0(a) = 0;
            L -= 20;
            word1(a) = L >= 31 ? 1 : 1 << (31 - L);
        }
    }
    return a.d;
}

double _b2d(Bigint *a, int *e)
{
    unsigned int *xa, *xa0, w, y, z;
    int k;
    MpDouble d;

    xa0 = a->x;
    xa = xa0 + a->wds;
    y = *--xa;
    k = _hi0bits(y);
    *e = 32 - k;
    if (k < 11) {
        word0(d) = 0x3FF00000 | y >> (11 - k);
        w = xa > xa0 ? *--xa : 0;
        word1(d) = y << (21 + k) | w >> (11 - k);
    } else {
        z = xa > xa0 ? *--xa : 0;
        k -= 11;
        if (k != 0) {
            word0(d) = 0x3FF00000 | y << k | z >> (32 - k);
            y = xa > xa0 ? *--xa : 0;
            word1(d) = z << k | y >> (32 - k);
        } else {
            word0(d) = 0x3FF00000 | y;
            word1(d) = z;
        }
    }
    return d.d;
}

int *_d2b(void *ptr, double dd, int *e, int *bits)
{
    Bigint *b;
    int de, i, k;
    unsigned int *x, y, z;
    MpDouble d;

    d.d = dd;
    b = (Bigint *)_Balloc(ptr, 1);
    x = b->x;
    z = word0(d) & 0xFFFFF;
    word0(d) &= 0x7FFFFFFF;
    de = (int)(word0(d) >> 20);
    if (de != 0) {
        z |= 0x100000;
    }
    y = word1(d);
    if (y != 0) {
        k = _lo0bits((int *)&y);
        if (k != 0) {
            x[0] = y | z << (32 - k);
            z >>= k;
        } else {
            x[0] = y;
        }
        i = b->wds = (x[1] = z) ? 2 : 1;
    } else {
        k = _lo0bits((int *)&z);
        x[0] = z;
        i = b->wds = 1;
        k += 32;
    }
    if (de != 0) {
        *e = de - 1023 - 52 + k;
        *bits = 53 - k;
    } else {
        *e = de - 1023 - 52 + 1 + k;
        *bits = 32 * i - _hi0bits(x[i - 1]);
    }
    return (int *)b;
}

extern double _b2d(Bigint *a, int *e);

double _ratio(Bigint *a, Bigint *b)
{
    MpDouble da;
    MpDouble db;
    int k, ka, kb;

    da.d = _b2d(a, &ka);
    db.d = _b2d(b, &kb);
    k = ka - kb + 32 * (a->wds - b->wds);
    if (k > 0) {
        word0(da) += k * 0x100000;
    } else {
        k = -k;
        word0(db) += k * 0x100000;
    }
    return da.d / db.d;
}

extern const long D_006388A0[];
extern long dpmul(long a, long b);

long _mprec_log10(int n)
{
    long acc = (long)0xFFC0 << 46;
    if (n < 0x18) {
        return D_006388A0[n];
    }
    while (n > 0) {
        acc = dpmul(acc, (long)0x8048 << 47);
        n--;
    }
    return acc;
}

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
