#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

typedef struct { unsigned int type; int f4; int f8; int fC; } PCmpV;

typedef struct { unsigned int type; int f4; int f8; int fC; unsigned long long f10; } PCmpV2;

extern PCmpV D_71EB88;

static inline PCmpV *func_0025FE30_div(PCmpV *a, PCmpV *b) {
    unsigned int at, bt;
    int e, q;
    unsigned int dvd, dvs, mask;

    at = a->type;
    if (at < 2) {
        return a;
    }
    bt = b->type;
    if (bt < 2) {
        return b;
    }
    a->f4 ^= b->f4;
    if ((at ^ 4) == 0 || (at ^ 2) == 0) {
        if (at == bt) {
            return &D_71EB88;
        }
        return a;
    }
    if ((bt ^ 4) == 0) {
        a->fC = 0;
        a->f8 = 0;
        return a;
    }
    if ((bt ^ 2) == 0) {
        a->type = 4;
        return a;
    }
    dvd = a->fC;
    dvs = b->fC;
    e = a->f8 - b->f8;
    a->f8 = e;
    if (dvd < dvs) {
        a->f8 = a->f8 - 1;
        dvd <<= 1;
    }
    mask = 0x40000000;
    q = 0;
    do {
        if (dvd >= dvs) {
            q |= mask;
            dvd -= dvs;
        }
        mask >>= 1;
        dvd <<= 1;
    } while (mask != 0);
    if ((q & 0x7F) == 0x40) {
        if (q & 0x80) {
            q += 0x40;
        } else if (dvd != 0) {
            q += 0x40;
        }
    }
    a->fC = q;
    return a;
}

extern void func_002591F0(int a0, int a1, int a2, int a3);

void func_0025E1E8(unsigned long long a0, unsigned int a1, int a2)
{
    if (a1 <= 0x7FFF && a2 >= 0 && a2 <= 0x7FFF && (a0 & 0xFF000000) == 0) {
        func_002591F0(0x4A, (int)a0, a1, a2);
    }
}

extern int func_00258CE0(void);

int func_0025E238(unsigned int a0)
{
    int ret = 0;
    if (a0 < 0x10) {
        int *p = func_00258CE0();
        ret = *(int *)((char *)p + (a0 << 2) + 0x180);
    }
    return ret;
}

int func_0025E280(int a0, long a1, int a2) {
    int ret;
    ret = -1;
    if ((unsigned int)a0 < 2 && (unsigned int)a2 <= 0x1FFFFF && (a1 & 0xFF000000) == 0) {
        func_002591F0(0x4F, a1, a2, a0);
        ret = 0;
    }
    return ret;
}

extern int func_0025F548(float x, float *y);
extern float func_0025FA60(float x, float y);
extern float func_00260508(float x, float y, int iy);

float func_0025E2E8(float x) {
    float y[2];
    int n;
    int ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;

    if (ix <= 0x3f490fd8) {
        return func_00260508(x, 0.0f, 0);
    } else if (ix >= 0x7f800000) {
        return x - x;
    } else {
        n = func_0025F548(x, y);
        switch (n & 3) {
        case 0:
            return func_00260508(y[0], y[1], 1);
        case 1:
            return func_0025FA60(y[0], y[1]);
        case 2:
            return -func_00260508(y[0], y[1], 1);
        default:
            return -func_0025FA60(y[0], y[1]);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_0025E3D8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_0025E4D8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_0025E5D8);

extern int D_0062F7D8[];
extern int func_00260610(void *);
extern int func_00264050(void);
/* Siblings defined further down this TU with an `int` return / `int` arg;
   the aug6 twin wants the float spelling.  Bind second identifiers to the
   same linker symbols instead of retyping the already-matched siblings. */
extern int func_002609E8__p4(float) __asm__("func_002609E8");
extern int func_00263FB0__p4(float) __asm__("func_00263FB0");
extern float func_002633B8__f(long) __asm__("func_002633B8");

float func_0025E700(float a, float b) {
    extern float func_0025F2F8(float a0, float a1);
    extern int D_0062F2D8[];
    extern long D_0062F2E0[];
    struct {
        int f0;
        void *f4;
        long f8;
        long f10;
        long f18;
        int f20;
    } buf;
    float f22;
    int s0;

    f22 = func_0025F2F8(a, b);
    s0 = D_0062F7D8[0];
    if (s0 == -1) {
        goto early;
    }
    if (func_002609E8__p4(b)) {
        goto early;
    }
    if (func_002609E8__p4(a)) {
        goto early;
    }
    if (b != 0.0f) {
        goto early;
    }
    buf.f0 = 1;
    buf.f4 = D_0062F2D8;
    buf.f20 = 0;
    buf.f8 = func_00263FB0__p4(a);
    buf.f10 = func_00263FB0__p4(b);
    if (s0 == 0) {
        buf.f18 = func_00263FB0__p4(a);
    } else {
        buf.f18 = D_0062F2E0[0];
    }
    if (D_0062F7D8[0] == 2 || func_00260610(&buf) == 0) {
        *(int *)func_00264050() = 0x21;
    }
    if (buf.f20 != 0) {
        *(int *)func_00264050() = buf.f20;
    }
    return func_002633B8__f(buf.f18);
early:
    return f22;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_0025E840);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_0025EC70);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_0025F010);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_0025F2F8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_0025F548);

float func_0025F928(float x) {
    int ix, s, q, m, t, i;
    unsigned int r;
    float z;

    GET_FLOAT_WORD(ix, x);
    if ((ix & 0x7F800000) == 0x7F800000) {
        return x * x + x;
    }
    m = ix >> 23;
    if (ix <= 0) {
        if ((ix & 0x7FFFFFFF) == 0) {
            return x;
        }
        if (ix < 0) {
            return (x - x) / (x - x);
        }
    }
    if (m == 0) {
        for (i = 0; (ix & 0x800000) == 0; i++) {
            ix <<= 1;
        }
        m -= i - 1;
    }
    m -= 0x7F;
    ix = (ix & 0x7FFFFF) | 0x800000;
    ix <<= (m & 1);
    m >>= 1;
    ix <<= 1;
    q = s = 0;
    r = 0x1000000;
    do {
        t = s + r;
        if (t <= ix) {
            s = t + r;
            ix -= t;
            q += r;
        }
        r >>= 1;
        ix <<= 1;
    } while (r != 0);
    if (ix != 0) {
        q += q & 1;
    }
    ix = (q >> 1) + 0x3F000000;
    ix += m << 23;
    SET_FLOAT_WORD(z, ix);
    return z;
}

float func_0025FA60(float x, float y) {
    float a, hz, qx, z;
    int ix;
    register int cmp __asm__("$2");
    register float acc __asm__("$f0");
    register float c2 __asm__("$f2");
    register float c3 __asm__("$f3");
    register float c1 __asm__("$f1");
    register float c4 __asm__("$f4");
    register float c5 __asm__("$f5");

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;
    if (ix < 0x32000000) {
        if (((int)x) == 0) {
            return 1.0f;
        }
    }
    z = x * x;
    /* Emit the six polynomial coefficient loads (into $f0/$f2/$f3/$f1/$f4/$f5),
     * the first Horner multiply (acc = z*c0), and the |x|<0.3 comparison
     * (cmp = 0x3e999999 < ix) in the exact ROM instruction order — the EE
     * scheduler will not interleave GPR comparison ops among asm-opaque coeff
     * loads, so the interleave is hand-placed here. */
    __asm__(
        "lui   $1,0xad47\n\t"
        "ori   $1,$1,0xd74e\n\t"
        "mtc1  $1,%0\n\t"
        "lui   $1,0x310f\n\t"
        "ori   $1,$1,0x74f6\n\t"
        "mtc1  $1,%1\n\t"
        "lui   %6,0x3e99\n\t"
        "lui   $1,0xb493\n\t"
        "ori   $1,$1,0xf27c\n\t"
        "mtc1  $1,%2\n\t"
        "ori   %6,%6,0x9999\n\t"
        "mul.s %0,%7,%0\n\t"
        "lui   $1,0x37d0\n\t"
        "ori   $1,$1,0x0d01\n\t"
        "mtc1  $1,%3\n\t"
        "lui   $1,0xbab6\n\t"
        "ori   $1,$1,0x0b61\n\t"
        "mtc1  $1,%4\n\t"
        "slt   %6,%6,%8\n\t"
        "lui   $1,0x3d2a\n\t"
        "ori   $1,$1,0xaaab\n\t"
        "mtc1  $1,%5"
        : "=f"(acc), "=f"(c2), "=f"(c3), "=f"(c1), "=f"(c4), "=f"(c5), "=r"(cmp)
        : "f"(z), "r"(ix));
    acc = acc + c2;
    acc = z * acc + c3;
    acc = z * acc + c1;
    acc = z * acc + c4;
    acc = z * acc + c5;
    /* r = z*acc: reuse c1 (dead since the a3 step) so r lands in $f1, leaving
     * $f0 free for the 0.5 constant the tail branches load — matches ROM. */
    c1 = z * acc;
    if (!cmp) {
        return 1.0f - (0.5f * z - (z * c1 - x * y));
    } else {
        if (ix > 0x3f480000) {
            qx = 0.28125f;
        } else {
            SET_FLOAT_WORD(qx, ix - 0x01000000);
        }
        /* else-branch z*r lands in $f2 (ROM), not the just-freed $f1: reuse
         * dead c2 ($f2) to force it, leaving $f1 for a = 1.0 - qx. */
        c2 = z * c1;
        hz = 0.5f * z - qx;
        a = 1.0f - qx;
        return a - (hz - (c2 - x * y));
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_0025FBB8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00260508);

extern int func_00263110(long a0, long a1);

int func_00260610(void *a0) {
    long p = *(long *)((char *)a0 + 8);
    func_00263110(p, p);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00260638);

float func_002608E0(float a0) {
    unsigned int ix;
    GET_FLOAT_WORD(ix, a0);
    SET_FLOAT_WORD(a0, ix & 0x7fffffff);
    return a0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00260900);

int func_002609E8(float x) {
    int hx;
    GET_FLOAT_WORD(hx, x);
    hx &= 0x7fffffff;
    hx = 0x7f800000 - hx;
    return (unsigned)hx >> 31;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00260A10);

float func_00260B70(float a0, float a1) {
    unsigned int ix, iy;
    GET_FLOAT_WORD(ix, a0);
    GET_FLOAT_WORD(iy, a1);
    SET_FLOAT_WORD(a0, (ix & 0x7fffffff) | (iy & 0x80000000));
    return a0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00260BA0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00260BF8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00260CA8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00260CC8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_002613B8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_002614A8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00261540);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00261BA8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00261C08);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_002621D8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00262718);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00262848);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_002628E8);

extern long long func_00262718(void *s);
extern void func_00262848(void *in, void *out);
extern void *func_002628E8(void *a, void *b, void *c);

void func_00262B28(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y, z;
    func_00262848(&a0, &x);
    func_00262848(&a1, &y);
    func_00262718(func_002628E8(&x, &y, &z));
}

long long func_00262B80(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y, z;
    func_00262848(&a0, &x);
    func_00262848(&a1, &y);
    y.b ^= 1;
    return func_00262718(func_002628E8(&x, &y, &z));
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00262BE8);

extern char D_71EB70[];

void func_00262E90(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y, *p;
    void *r;
    unsigned long long m1, m2, bit, q;
    int exp;

    func_00262848(&a0, &x);
    func_00262848(&a1, &y);
    p = &x;
    if ((unsigned int) x.a >= 2) goto op2check;
    r = &x;
    goto pack;
op2check:
    if ((unsigned int) y.a < 2) {
        r = &y;
        goto pack;
    }
    x.b = x.b ^ y.b;
    if ((x.a ^ 4) == 0) goto chk_same;
    if ((x.a ^ 2) != 0) goto op1_normal;
chk_same:
    r = &x;
    if (x.a != y.a) goto pack;
    r = D_71EB70;
    goto pack;
op1_normal:
    if ((y.a ^ 4) != 0) goto chk_zero;
    x.d = 0;
    x.c = 0;
    r = &x;
    goto pack;
chk_zero:
    if ((y.a ^ 2) != 0) goto divide;
    x.a = 4;
    r = &x;
    goto pack;
divide:
    m1 = (unsigned long long) x.d;
    m2 = (unsigned long long) y.d;
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
    func_00262718(r);
}

int func_00262FF8(PCmpV2 *a, PCmpV2 *b) {
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

int func_00263110(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y;
    func_00262848(&a0, &x);
    func_00262848(&a1, &y);
    return func_00262FF8(&x, &y);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00263160);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00263218);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_002632B0);

void func_00263350(long long a0) {
    struct { int a, b, c, pad; long long d; } s;
    long long t = a0;
    func_00262848(&t, &s);
    s.b = (s.b == 0);
    func_00262718(&s);
}

int func_00263388(int a0, int a1, int a2, long long a3) {
    struct { int a, b, c, pad; long long d; } s;
    s.a = a0;
    s.b = a1;
    s.c = a2;
    s.d = a3;
    func_00262718(&s);
}

extern void func_00263F80(int a0, int a1, int a2, int a3);

int func_002633B8(long a0) {
    struct { int f0; int f4; int f8; int fC; long long f10; } buf;
    long long m; int hi, t;
    func_00262848(&a0, &buf);
    m = buf.f10;
    hi = (int)(m >> 30);
    t = hi | 1;
    if ((m & 0x3FFFFFFF) == 0) t = hi;
    func_00263F80(buf.f0, buf.f4, buf.f8, t);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00263410);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00263520);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_002635B0);

extern int func_00263410(void *s);
extern void func_00263520(void *in, void *out);
extern int func_002635B0();

int func_002637E8(float a0, float a1) {
    char buf[0x40];
    int ret;
    *(float *)(buf + 0x30) = a0;
    *(float *)(buf + 0x34) = a1;
    func_00263520(buf + 0x30, buf);
    func_00263520(buf + 0x34, buf + 0x10);
    ret = func_002635B0(buf, buf + 0x10, buf + 0x20);
    return func_00263410(ret);
}

int func_00263840(float a0, float a1) {
    char buf[0x40];
    int ret;
    *(float *)(buf + 0x30) = a0;
    *(float *)(buf + 0x34) = a1;
    func_00263520(buf + 0x30, buf);
    func_00263520(buf + 0x34, buf + 0x10);
    *(int *)(buf + 0x14) ^= 1;
    ret = func_002635B0(buf, buf + 0x10, buf + 0x20);
    return func_00263410(ret);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_002638A8);


int func_00263AA0(float a0, float a1) {
    PCmpV a, b;
    float fa, fb;

    fa = a0;
    fb = a1;
    func_00263520(&fa, &a);
    func_00263520(&fb, &b);

    return func_00263410(func_0025FE30_div(&a, &b));
}

int func_00263C00(PCmpV *a, PCmpV *b) {
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
                unsigned int afC = a->fC;
                unsigned int bfC = b->fC;
                if (bfC < afC) {
                    return af4 ? -1 : 1;
                }
                if (afC < bfC) {
                    return af4 ? 1 : -1;
                }
                return 0;
            }
        }
    }
}

int func_00263D18(float a0, float a1) {
    char buf[0x30];
    *(float *)(buf + 0x20) = a0;
    *(float *)(buf + 0x24) = a1;
    func_00263520(buf + 0x20, buf);
    func_00263520(buf + 0x24, buf + 0x10);
    return func_00263C00(buf, buf + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00263D68);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00263E20);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00263EB0);

int func_00263F48(float f12)
{
    int o[4];
    float in[4];
    in[0] = f12;
    func_00263520(in, o);
    o[1] = (o[1] == 0);
    return func_00263410(o);
}

void func_00263F80(int a0, int a1, int a2, int a3) {
    int buf[4];
    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = a3;
    func_00263410(buf);
}

int func_00263FB0(float f12)
{
    int local0[4];
    float local1[4];
    long long a3_val;
    local1[0] = f12;
    func_00263520(local1, local0);
    a3_val = (long long)(unsigned int)local0[3] << 32;
    return func_00263388(local0[0], local0[1], local0[2],
                         (long long)((unsigned long long)a3_val >> 2));
}

extern int D_00553244[];
extern char D_0062FC48[];
/* func_00264060 is a varargs forwarder, defined below.  An unprototyped
   `extern void func_00264060();` here is incompatible with that `...`
   prototype under ee-gcc 2.9, so the caller reaches it through an alias
   identifier; K&R-unprototyped call codegen is identical either way. */
extern void func_00264060__k() __asm__("func_00264060");
extern void func_00268F08(void);

void func_00263FF0(int a0, int a1, int a2) {
    func_00264060__k(*(int *)(D_00553244[0] + 0xC), (int)D_0062FC48, a2, a0, a1);
    func_00268F08();
}

extern long long func_00265AF0(void *a0, int a1, int a2);

int func_00264028(void *a0) {
    return (int)func_00265AF0(a0, 0, 0xA);
}

int func_00264050(void) {
    return D_00553244[0];
}

extern void func_00265C28(int a0, int a1, void *args);

void func_00264060(int a0, int a1, ...) {
    char *ap = (char *)__builtin_next_arg(a1) - 48;
    func_00265C28(a0, a1, ap);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00264094);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00264128);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_002641D8\n"
    "    .type func_002641D8, @function\n"
    "    .align 3\n"
    "func_002641D8:\n"
    "    sltiu  $2, $6, 0x8\n"
    "    bnez   $2, .L002641D8002605E8\n"
    "    daddu  $3, $4, $0\n"
    "    andi   $2, $4, 0xF\n"
    "    bnez   $2, .L002641D8002605E8\n"
    "    daddu  $7, $4, $0\n"
    "    andi   $9, $5, 0xFF\n"
    "    sltiu  $10, $6, 0x20\n"
    "    daddu  $8, $9, $0\n"
    "    dsll   $3, $8, 8\n"
    "    or     $8, $3, $9\n"
    "    pcpyh  $3, $8\n"
    "    bnez   $10, .L002641D8002605D4\n"
    "    sltiu  $2, $6, 0x8\n"
    "    pcpyld $8, $3, $3\n"
    "    .align 2\n"
    ".L002641D8002605A4:\n"
    "    sq     $8, 0x0($7)\n"
    "    addiu  $6, $6, -0x20\n"
    "    addiu  $7, $7, 0x10\n"
    "    sltiu  $2, $6, 0x20\n"
    "    sq     $8, 0x0($7)\n"
    "    beqz   $2, .L002641D8002605A4\n"
    "    addiu  $7, $7, 0x10\n"
    "    b      .L002641D8002605D4\n"
    "    sltiu  $2, $6, 0x8\n"
    "    .align 2\n"
    ".L002641D8002605C8:\n"
    "    addiu  $6, $6, -0x8\n"
    "    addiu  $7, $7, 0x8\n"
    "    sltiu  $2, $6, 0x8\n"
    "    .align 2\n"
    ".L002641D8002605D4:\n"
    "    nop\n"
    "    nop\n"
    "    beql   $2, $0, .L002641D8002605C8\n"
    "    sd     $3, 0x0($7)\n"
    "    daddu  $3, $7, $0\n"
    "    .align 2\n"
    ".L002641D8002605E8:\n"
    "    lui    $2, 0xFFFF\n"
    "    addiu  $6, $6, -0x1\n"
    "    ori    $2, $2, 0xFFFF\n"
    "    beq    $6, $2, .L002641D800260620\n"
    "    nop\n"
    "    lui    $2, 0xFFFF\n"
    "    ori    $2, $2, 0xFFFF\n"
    "    .align 2\n"
    ".L002641D800260604:\n"
    "    sb     $5, 0x0($3)\n"
    "    addiu  $6, $6, -0x1\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    bne    $6, $2, .L002641D800260604\n"
    "    addiu  $3, $3, 0x1\n"
    "    .align 2\n"
    ".L002641D800260620:\n"
    "    jr     $31\n"
    "    daddu  $2, $4, $0\n"
    "    .size func_002641D8, . - func_002641D8\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern int func_002669E8(int *self, int subj, int b, void *args);

int func_00264298(int *self, int b, ...)
{
    void *args = (char *)__builtin_next_arg(b) - 0x30;
    return func_002669E8(self, self[2], b, args);
}

extern int func_00266970();

void func_002642D8(void *a0, ...) {
    void *args = (char *)__builtin_next_arg(a0) - 0x38;
    int s = D_00553244[0];
    *(int *)(*(int *)(s + 8) + 0x54) = s;
    func_00266970(*(int *)(s + 8), a0, args);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00264328);

extern void *D_0054D504_alias[] __asm__("D_00553244");

void func_00264D50(int a0) {
    char *p = (char *)D_0054D504_alias[0];
    *(int *)(p + 0x58) = a0;
}

int func_00264D60(void) {
    char *p = (char *)D_0054D504_alias[0];
    int s = *(int *)(p + 0x58) * 0x41C64E6D + 0x3039;
    *(int *)(p + 0x58) = s;
    return s & 0x7fffffff;
}

int func_00264D90(void *a0, int a1, int a2, ...) {
    char buf[0x60];
    char *va = (char *)__builtin_next_arg(a2) - 40;
    int n;
    *(int *)(buf + 0x0) = a1;
    *(int *)(buf + 0x8) = 0x7FFFFFFF;
    *(short *)(buf + 0xC) = 0x208;
    *(int *)(buf + 0x10) = a1;
    *(int *)(buf + 0x14) = 0x7FFFFFFF;
    *(int *)(buf + 0x54) = (int)a0;
    n = func_00266970(buf, a2, va);
    *(char *)(*(int *)(buf + 0x0)) = 0;
    return n;
}


int func_00264DF8(void *a0, int a1, ...) {
    char buf[0x60];
    char *va = (char *)__builtin_next_arg(a1) - 48;
    int n;
    *(int *)(buf + 0x0) = (int)a0;
    *(int *)(buf + 0x8) = 0x7FFFFFFF;
    *(short *)(buf + 0xC) = 0x208;
    *(int *)(buf + 0x10) = (int)a0;
    *(int *)(buf + 0x14) = 0x7FFFFFFF;
    *(int *)(buf + 0x54) = D_00553244[0];
    n = func_00266970(buf, a1, va);
    *(char *)(*(int *)(buf + 0x0)) = 0;
    return n;
}

int func_00264E68(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00264E70);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00264EF8\n"
    "    .type func_00264EF8, @function\n"
    "    .align 3\n"
    "func_00264EF8:\n"
    "    addiu  $29, $29, -0x20\n"
    "    sq     $16, 0x0($29)\n"
    "    daddu  $16, $4, $0\n"
    "    andi   $2, $16, 0x7\n"
    "    bnez   $2, .L0026137C\n"
    "    sq     $31, 0x10($29)\n"
    "    andi   $2, $16, 0xF\n"
    "    lui    $3, 0x101\n"
    "    ori    $3, $3, 0x101\n"
    "    dsll   $3, $3, 16\n"
    "    ori    $3, $3, 0x101\n"
    "    dsll   $3, $3, 16\n"
    "    ori    $3, $3, 0x101\n"
    "    lui    $4, 0x8080\n"
    "    ori    $4, $4, 0x8080\n"
    "    dsll   $4, $4, 16\n"
    "    ori    $4, $4, 0x8080\n"
    "    dsll   $4, $4, 16\n"
    "    ori    $4, $4, 0x8080\n"
    "    bnez   $2, .L00261338\n"
    "    ld     $6, 0x0($16)\n"
    "    lq     $2, 0x0($16)\n"
    "    pcpyld $7, $3, $3\n"
    "    pcpyld $8, $4, $4\n"
    "    psubb  $3, $2, $7\n"
    "    pnor   $2, $0, $2\n"
    "    pand   $3, $3, $2\n"
    "    pand   $3, $3, $8\n"
    "    pcpyud $2, $3, $3\n"
    "    or     $3, $2, $3\n"
    "    bnez   $3, .L0026137C\n"
    "    daddu  $4, $16, $0\n"
    "    addiu  $6, $4, 0x10\n"
    "    .align 2\n"
    ".L0026130C:\n"
    "    lq     $2, 0x0($6)\n"
    "    pnor   $3, $0, $2\n"
    "    psubb  $2, $2, $7\n"
    "    pand   $2, $2, $3\n"
    "    pand   $2, $2, $8\n"
    "    pcpyud $3, $2, $2\n"
    "    or     $2, $2, $3\n"
    "    beql   $2, $0, .L0026130C\n"
    "    addiu  $6, $6, 0x10\n"
    "    b      .L0026137C\n"
    "    daddu  $4, $6, $0\n"
    "    .align 2\n"
    ".L00261338:\n"
    "    daddu  $7, $3, $0\n"
    "    daddu  $8, $4, $0\n"
    "    dsubu  $3, $6, $3\n"
    "    nor    $2, $0, $6\n"
    "    and    $3, $3, $2\n"
    "    and    $3, $3, $4\n"
    "    bnez   $3, .L0026137C\n"
    "    daddu  $4, $16, $0\n"
    "    addiu  $6, $16, 0x8\n"
    "    .align 2\n"
    ".L0026135C:\n"
    "    ld     $2, 0x0($6)\n"
    "    nor    $3, $0, $2\n"
    "    dsubu  $2, $2, $7\n"
    "    and    $2, $2, $3\n"
    "    and    $2, $2, $8\n"
    "    beql   $2, $0, .L0026135C\n"
    "    addiu  $6, $6, 0x8\n"
    "    daddu  $4, $6, $0\n"
    "    .align 2\n"
    ".L0026137C:\n"
    "    lb     $2, 0x0($4)\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    bnel   $2, $0, .L0026137C\n"
    "    addiu  $4, $4, 0x1\n"
    "    jal    func_00265168\n"
    "    nop\n"
    "    daddu  $2, $16, $0\n"
    "    lq     $31, 0x10($29)\n"
    "    lq     $16, 0x0($29)\n"
    "    jr     $31\n"
    "    addiu  $29, $29, 0x20\n"
    "    .size func_00264EF8, . - func_00264EF8\n"
    "    .set reorder\n"
    "    .set at\n"
);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00265024);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00265168);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_0026527C);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_002653B8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00265570);

char *func_00265730(char *s, char c) {
    char *last = 0;
    while (*s != 0) {
        if (*s == c) {
            last = s;
        }
        s++;
    }
    return (*s == c) ? s : last;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00265780);

extern int func_00265818(int a0, int a1, int a2);

int func_002657F0(int a0, int a1) {
    return func_00265818(a0, a1, D_00553244[0] + 0x5C);
}

/* Re-entrant token scanner (a `strtok_r`): skip leading delimiters, then
 * scan to the next one, NUL-terminating the token in place and leaving the
 * resume point in *last.  Derived from the disassembly -- the two scans,
 * the `goto cont` restart when a delimiter matches, and the s = NULL case
 * when the token runs to the end of the string are all visible in the
 * branch structure. */
/* The sibling above prototypes this as `int (int, int, int)`; keep that
 * signature and take the real types locally rather than changing a
 * declaration a matched caller depends on. */
int func_00265818(int a0, int a1, int a2) {
    char *s = (char *)a0;
    char *delim = (char *)a1;
    char **last = (char **)a2;
    char *spanp;
    char *tok;
    int c;
    int sc;

    if (s == 0 && (s = *last) == 0) {
        return 0;
    }

cont:
    c = *s++;
    for (spanp = delim; (sc = *spanp++) != 0;) {
        if (c == sc) {
            goto cont;
        }
    }

    if (c == 0) {
        *last = 0;
        return 0;
    }
    tok = s - 1;

    for (;;) {
        c = *s++;
        spanp = delim;
        do {
            if ((sc = *spanp++) == c) {
                if (c == 0) {
                    s = 0;
                } else {
                    s[-1] = 0;
                }
                *last = s;
                return (int)tok;
            }
        } while (sc != 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_002658B8);

extern long long func_002658B8(void *a0, void *a1, int a2, int a3);

long long func_00265AF0(void *a0, int a1, int a2) {
    return func_002658B8((void *)D_00553244[0], a0, a1, a2);
}

extern int func_0026AC40();

int func_00265B28(int a0, int *a1) {
    int ret;
    if (a1[2] == 0) {
        a1[1] = 0;
        return 0;
    }
    ret = func_0026AC40(a0, a1);
    a1[2] = 0;
    a1[1] = 0;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00265B70);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00265C28);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25E1E8", func_00265CA0);

int func_00266870(int a0, int *a1) {
    int ret;
    if (a1[2] == 0) {
        a1[1] = 0;
        return 0;
    }
    ret = func_0026AC40(a0, a1);
    a1[2] = 0;
    a1[1] = 0;
    return ret;
}
