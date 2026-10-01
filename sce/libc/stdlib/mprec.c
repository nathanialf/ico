/* libc.a member mprec.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <libc_internal.h>

_Bigint *_Balloc(Reent *ptr, int k)
{
    _Bigint *rv;
    int x;

    if (ptr->freelist == 0) {
        ptr->freelist = (_Bigint **)_calloc_r(ptr, 4, 16);
        if (ptr->freelist == 0) {
            return 0;
        }
    }
    rv = ptr->freelist[k];
    if (rv != 0) {
        ptr->freelist[k] = rv->_next;
    } else {
        x = 1 << k;
        rv = (_Bigint *)_calloc_r(ptr, 1, sizeof(_Bigint) + (x - 1) * sizeof(int));
        if (rv == 0) {
            return 0;
        }
        rv->_k = k;
        rv->_maxwds = x;
    }
    rv->_sign = rv->_wds = 0;
    return rv;
}

void _Bfree(Reent *ptr, _Bigint *v)
{
    if (v) {
        v->_next = ptr->freelist[v->_k];
        ptr->freelist[v->_k] = v;
    }
}

_Bigint *_multadd(Reent *ptr, _Bigint *b, int m, int a)
{
    _Bigint *b1;
    unsigned int *x;
    unsigned int xi, y, z;
    int i, wds;

    wds = b->_wds;
    x = b->_x;
    i = 0;
    do {
        xi = *x;
        y = (xi & 0xFFFF) * m + a;
        z = (xi >> 16) * m + (y >> 16);
        a = (int)(z >> 16);
        *x++ = (z << 16) + (y & 0xFFFF);
    } while (++i < wds);
    if (a != 0) {
        if (wds >= b->_maxwds) {
            b1 = _Balloc(ptr, b->_k + 1);
            memcpy((char *)&b1->_sign, (char *)&b->_sign, b->_wds * 4 + 8);
            _Bfree(ptr, b);
            b = b1;
        }
        b->_x[wds++] = a;
        b->_wds = wds;
    }
    return b;
}

_Bigint *_s2b(Reent *ptr, const char *s, int nd0, int nd, unsigned int y9)
{
    _Bigint *b;
    int i, k;
    int x, y;

    x = (nd + 8) / 9;
    for (k = 0, y = 1; x > y; y <<= 1, k++)
        ;
    b = _Balloc(ptr, k);
    b->_x[0] = y9;
    b->_wds = 1;
    i = 9;
    if (9 < nd0) {
        s += 9;
        do
            b = _multadd(ptr, b, 10, *s++ - '0');
        while (++i < nd0);
        s++;
    } else
        s += 10;
    for (; i < nd; i++)
        b = _multadd(ptr, b, 10, *s++ - '0');
    return b;
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

int _lo0bits(unsigned int *y)
{
    unsigned int v = *y;
    int n;
    if (v & 7) {
        if (v & 1) {
            return 0;
        }
        if (v & 2) {
            *y = v >> 1;
            return 1;
        }
        *y = v >> 2;
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
        *y = v;
    } else {
        v >>= 1;
        n += 1;
        if (v == 0) {
            return 0x20;
        }
        *y = v;
    }
    return n;
}

_Bigint *_i2b(Reent *ptr, int i)
{
    _Bigint *b;

    b = _Balloc(ptr, 1);
    b->_x[0] = i;
    b->_wds = 1;
    return b;
}

/* newlib mprec.h Storeinc for a little-endian target: the two halves of the
   word go out as halfword stores. */
#define Storeinc(a, b, c)                                                                          \
    (((unsigned short *)(a))[1] = (unsigned short)(b),                                             \
     ((unsigned short *)(a))[0] = (unsigned short)(c), (a)++)

_Bigint *_multiply(Reent *ptr, _Bigint *a, _Bigint *b)
{
    _Bigint *c;
    int k, wa, wb, wc;
    unsigned int carry, *x, *xa, *xae, *xb, *xbe, *xc, *xc0, y, z;
    unsigned int z2;

    if (a->_wds < b->_wds) {
        c = a;
        a = b;
        b = c;
    }
    k = a->_k;
    wa = a->_wds;
    wb = b->_wds;
    wc = wa + wb;
    if (wc > a->_maxwds) {
        k++;
    }
    c = _Balloc(ptr, k);
    for (x = c->_x, xa = x + wc; x < xa; x++) {
        *x = 0;
    }
    xa = a->_x;
    xae = xa + wa;
    xb = b->_x;
    xbe = xb + wb;
    xc0 = c->_x;
    for (; xb < xbe; xb++, xc0++) {
        if ((y = *xb & 0xFFFF) != 0) {
            x = xa;
            xc = xc0;
            carry = 0;
            do {
                z = (*x & 0xFFFF) * y + (*xc & 0xFFFF) + carry;
                carry = z >> 16;
                z2 = (*x++ >> 16) * y + (*xc >> 16) + carry;
                carry = z2 >> 16;
                Storeinc(xc, z2, z);
            } while (x < xae);
            *xc = carry;
        }
        if ((y = *xb >> 16) != 0) {
            x = xa;
            xc = xc0;
            carry = 0;
            z2 = *xc;
            do {
                z = (*x & 0xFFFF) * y + (*xc >> 16) + carry;
                carry = z >> 16;
                Storeinc(xc, z, z2);
                z2 = (*x++ >> 16) * y + (*xc & 0xFFFF) + carry;
                carry = z2 >> 16;
            } while (x < xae);
            *xc = z2;
        }
    }
    for (xc0 = c->_x, xc = xc0 + wc; wc > 0 && *--xc == 0; wc--) {
        ;
    }
    c->_wds = wc;
    return c;
}

_Bigint *_pow5mult(Reent *ptr, _Bigint *b, int k)
{
    _Bigint *b1;
    _Bigint *p5;
    _Bigint *p51;
    int i;
    static const int p05[3] = {5, 25, 125};

    i = k & 3;
    if (i != 0) {
        b = _multadd(ptr, b, p05[i - 1], 0);
    }
    k >>= 2;
    if (k == 0) {
        return b;
    }
    p5 = ptr->p5s;
    if (p5 == 0) {
        p5 = ptr->p5s = _i2b(ptr, 625);
        p5->_next = 0;
    }
    for (;;) {
        if (k & 1) {
            b1 = _multiply(ptr, b, p5);
            _Bfree(ptr, b);
            b = b1;
        }
        k >>= 1;
        if (k == 0) {
            break;
        }
        p51 = p5->_next;
        if (p51 == 0) {
            p51 = p5->_next = _multiply(ptr, p5, p5);
            p51->_next = 0;
        }
        p5 = p51;
    }
    return b;
}

_Bigint *_lshift(Reent *ptr, _Bigint *b, int k)
{
    int i, k1, n, n1;
    _Bigint *b1;
    unsigned int *x, *x1, *xe, z;

    n = k >> 5;
    k1 = b->_k;
    n1 = n + b->_wds + 1;
    for (i = b->_maxwds; n1 > i; i <<= 1) {
        k1++;
    }
    b1 = _Balloc(ptr, k1);
    x1 = b1->_x;
    for (i = 0; i < n; i++) {
        *x1++ = 0;
    }
    x = b->_x;
    xe = x + b->_wds;
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
    b1->_wds = n1 - 1;
    _Bfree(ptr, b);
    return b1;
}

int __mcmp(_Bigint *a, _Bigint *b)
{
    unsigned int *xa, *xa0, *xb, *xb0;
    int i, j;

    i = a->_wds;
    j = b->_wds;
    if (i -= j)
        return i;
    xa0 = a->_x;
    xa = xa0 + j;
    xb0 = b->_x;
    xb = xb0 + j;
    for (;;) {
        if (*--xa != *--xb)
            return *xa < *xb ? -1 : 1;
        if (xa <= xa0)
            break;
    }
    return 0;
}

_Bigint *__mdiff(Reent *ptr, _Bigint *a, _Bigint *b)
{
    _Bigint *c;
    int i, wa, wb;
    int borrow, y, z;
    unsigned int *xa, *xae, *xb, *xbe, *xc;

    i = __mcmp(a, b);
    if (i == 0) {
        c = _Balloc(ptr, 0);
        c->_wds = 1;
        c->_x[0] = 0;
        return c;
    }
    if (i < 0) {
        c = a;
        a = b;
        b = c;
        i = 1;
    } else {
        i = 0;
    }
    c = _Balloc(ptr, a->_k);
    c->_sign = i;
    wa = a->_wds;
    xa = a->_x;
    xae = xa + wa;
    wb = b->_wds;
    xb = b->_x;
    xbe = xb + wb;
    xc = c->_x;
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
    c->_wds = wa;
    return c;
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

double _b2d(_Bigint *a, int *e)
{
    unsigned int *xa, *xa0, w, y, z;
    int k;
    MpDouble d;

    xa0 = a->_x;
    xa = xa0 + a->_wds;
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

_Bigint *_d2b(Reent *ptr, double dd, int *e, int *bits)
{
    _Bigint *b;
    int de, i, k;
    unsigned int *x, y, z;
    MpDouble d;

    d.d = dd;
    b = _Balloc(ptr, 1);
    x = b->_x;
    z = word0(d) & 0xFFFFF;
    word0(d) &= 0x7FFFFFFF;
    de = (int)(word0(d) >> 20);
    if (de != 0) {
        z |= 0x100000;
    }
    y = word1(d);
    if (y != 0) {
        k = _lo0bits(&y);
        if (k != 0) {
            x[0] = y | z << (32 - k);
            z >>= k;
        } else {
            x[0] = y;
        }
        i = b->_wds = (x[1] = z) ? 2 : 1;
    } else {
        k = _lo0bits(&z);
        x[0] = z;
        i = b->_wds = 1;
        k += 32;
    }
    if (de != 0) {
        *e = de - 1023 - 52 + k;
        *bits = 53 - k;
    } else {
        *e = de - 1023 - 52 + 1 + k;
        *bits = 32 * i - _hi0bits(x[i - 1]);
    }
    return b;
}

double _ratio(_Bigint *a, _Bigint *b)
{
    MpDouble da;
    MpDouble db;
    int k, ka, kb;

    da.d = _b2d(a, &ka);
    db.d = _b2d(b, &kb);
    k = ka - kb + 32 * (a->_wds - b->_wds);
    if (k > 0) {
        word0(da) += k * 0x100000;
    } else {
        k = -k;
        word0(db) += k * 0x100000;
    }
    return da.d / db.d;
}

const double __mprec_tens[] = {
    1e0,  1e1,  1e2,  1e3,  1e4,  1e5,  1e6,  1e7,  1e8,  1e9,  1e10, 1e11, 1e12,
    1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19, 1e20, 1e21, 1e22, 1e23, 1e24,
};

const double __mprec_bigtens[] = {1e16, 1e32, 1e64, 1e128, 1e256};

const double __mprec_tinytens[] = {1e-16, 1e-32, 1e-64, 1e-128, 1e-256};

double _mprec_log10(int dig)
{
    double v = 1.0;

    if (dig < 24) {
        return __mprec_tens[dig];
    }
    while (dig > 0) {
        v *= 10;
        dig--;
    }
    return v;
}
