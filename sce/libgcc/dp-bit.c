/* libgcc.a member dp-bit.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

typedef struct {
    unsigned int type;
    int f4;
    int f8;
    int fC;
} PCmpV;

typedef struct {
    unsigned int type;
    int f4;
    int f8;
    int fC;
    unsigned long long f10;
} PCmpV2;

INCLUDE_ASM("asm/nonmatchings/sce/libgcc/dp-bit", __pack_d);
INCLUDE_ASM("asm/nonmatchings/sce/libgcc/dp-bit", __unpack_d);
INCLUDE_ASM("asm/nonmatchings/sce/libgcc/dp-bit", _fpadd_parts);

extern long long __pack_d(void *s);
extern void __unpack_d(void *in, void *out);
extern void *_fpadd_parts(void *a, void *b, void *c);

void dpadd(long a0, long a1)
{
    struct {
        int a, b, c, pad;
        long long d;
    } x, y, z;

    __unpack_d(&a0, &x);
    __unpack_d(&a1, &y);
    __pack_d(_fpadd_parts(&x, &y, &z));
}

long long dpsub(long a0, long a1)
{
    struct {
        int a, b, c, pad;
        long long d;
    } x, y, z;

    __unpack_d(&a0, &x);
    __unpack_d(&a1, &y);
    y.b ^= 1;
    return __pack_d(_fpadd_parts(&x, &y, &z));
}

INCLUDE_ASM("asm/nonmatchings/sce/libgcc/dp-bit", dpmul);

extern char D_736170[];

void dpdiv(long a0, long a1)
{
    struct {
        int a, b, c, pad;
        long long d;
    } x, y, *p;

    void *r;
    unsigned long long m1, m2, bit, q;
    int exp;

    __unpack_d(&a0, &x);
    __unpack_d(&a1, &y);
    p = &x;
    if ((unsigned int)x.a >= 2)
        goto op2check;
    r = &x;
    goto pack;
op2check:
    if ((unsigned int)y.a < 2) {
        r = &y;
        goto pack;
    }
    x.b = x.b ^ y.b;
    if ((x.a ^ 4) == 0)
        goto chk_same;
    if ((x.a ^ 2) != 0)
        goto op1_normal;
chk_same:
    r = &x;
    if (x.a != y.a)
        goto pack;
    r = D_736170;
    goto pack;
op1_normal:
    if ((y.a ^ 4) != 0)
        goto chk_zero;
    x.d = 0;
    x.c = 0;
    r = &x;
    goto pack;
chk_zero:
    if ((y.a ^ 2) != 0)
        goto divide;
    x.a = 4;
    r = &x;
    goto pack;
divide:
    m1 = (unsigned long long)x.d;
    m2 = (unsigned long long)y.d;
    x.c = x.c - y.c;
    if (m1 < m2) {
        x.c = x.c - 1;
        m1 <<= 1;
    }
    q = 0;
    bit = 0x1000000000000000ULL;
    do {
        if (m1 >= m2) {
            q |= bit;
            m1 -= m2;
        }
        bit >>= 1;
        m1 <<= 1;
    } while (bit != 0);
    if ((q & 0xFF) != 0x80) {
        p->d = q;
    } else {
        if (q & 0x100) {
            q += 0x80;
        } else {
            q = (m1 != 0) ? (q + 0x80) : q;
        }
        p->d = q;
    }
    r = p;
pack:
    __pack_d(r);
}

int __fpcmp_parts_d(PCmpV2 *a, PCmpV2 *b)
{
    unsigned int at = a->type;
    unsigned int bt;
    if (at < 2) {
        return 1;
    }
    bt = b->type;
    if (bt < 2) {
        return 1;
    }
    if ((at ^ 4) == 0) {
        if ((bt ^ 4) == 0) {
            return b->f4 - a->f4;
        }
        return a->f4 ? -1 : 1;
    }
    if ((bt ^ 4) == 0) {
        if (b->f4 == 0) {
            return -1;
        }
        return 1;
    }
    if ((at ^ 2) == 0) {
        if ((bt ^ 2) == 0) {
            return 0;
        }
        if (b->f4 != 0) {
            return 1;
        }
        return -1;
    }
    if ((bt ^ 2) == 0) {
        return a->f4 ? -1 : 1;
    }
    {
        int af4 = a->f4;
        int bf4 = b->f4;
        if (af4 != bf4) {
            return af4 ? -1 : 1;
        }
        {
            int af8 = a->f8;
            int bf8 = b->f8;
            if (bf8 < af8) {
                return af4 ? -1 : 1;
            }
            if (af8 < bf8) {
                return af4 ? 1 : -1;
            }
            {
                unsigned long long af10 = a->f10;
                unsigned long long bf10 = b->f10;
                if (bf10 < af10) {
                    return af4 ? -1 : 1;
                }
                if (af10 < bf10) {
                    return af4 ? 1 : -1;
                }
                return 0;
            }
        }
    }
}

int dpcmp(long a0, long a1)
{
    struct {
        int a, b, c, pad;
        long long d;
    } x, y;

    __unpack_d(&a0, &x);
    __unpack_d(&a1, &y);
    return __fpcmp_parts_d(&x, &y);
}

INCLUDE_ASM("asm/nonmatchings/sce/libgcc/dp-bit", litodp);
INCLUDE_ASM("asm/nonmatchings/sce/libgcc/dp-bit", dptoli);
INCLUDE_ASM("asm/nonmatchings/sce/libgcc/dp-bit", dptoul);

void __negdf2(long long a0)
{
    struct {
        int a, b, c, pad;
        long long d;
    } s;

    long long t = a0;
    __unpack_d(&t, &s);
    s.b = (s.b == 0);
    __pack_d(&s);
}

int __make_dp(int a0, int a1, int a2, long long a3)
{
    struct {
        int a, b, c, pad;
        long long d;
    } s;

    s.a = a0;
    s.b = a1;
    s.c = a2;
    s.d = a3;
    __pack_d(&s);
}

extern void __make_fp(int a0, int a1, int a2, int a3);

float dptofp(long a0)
{
    struct {
        int f0;
        int f4;
        int f8;
        int fC;
        long long f10;
    } buf;

    long long m;
    int hi, t;
    __unpack_d(&a0, &buf);
    m = buf.f10;
    hi = (int)(m >> 30);
    t = hi | 1;
    if ((m & 0x3FFFFFFF) == 0)
        t = hi;
    __make_fp(buf.f0, buf.f4, buf.f8, t);
}
