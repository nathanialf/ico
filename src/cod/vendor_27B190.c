#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

typedef struct { unsigned int type; int f4; int f8; int fC; } PCmpV;

typedef struct { unsigned int type; int f4; int f8; int fC; unsigned long long f10; } PCmpV2;

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __do_global_dtors);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __do_global_ctors);
extern void __do_global_ctors();

extern int D_00736168[];
void __main(void) {
    if (D_00736168[0] == 0) {
        D_00736168[0] = 1;
        __do_global_ctors();
    }
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __divdi3);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __fixunsdfdi);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __floatdidf);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __moddi3);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __muldi3);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __udivdi3);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __umoddi3);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __pack_d);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __unpack_d);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", _fpadd_parts);
extern long long __pack_d(void *s);
extern void __unpack_d(void *in, void *out);
extern void *_fpadd_parts(void *a, void *b, void *c);

void dpadd(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y, z;
    __unpack_d(&a0, &x);
    __unpack_d(&a1, &y);
    __pack_d(_fpadd_parts(&x, &y, &z));
}
long long dpsub(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y, z;
    __unpack_d(&a0, &x);
    __unpack_d(&a1, &y);
    y.b ^= 1;
    return __pack_d(_fpadd_parts(&x, &y, &z));
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", dpmul);
extern char D_736170[];

void dpdiv(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y, *p;
    void *r;
    unsigned long long m1, m2, bit, q;
    int exp;

    __unpack_d(&a0, &x);
    __unpack_d(&a1, &y);
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
    r = D_736170;
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
    __pack_d(r);
}
int __fpcmp_parts_d(PCmpV2 *a, PCmpV2 *b) {
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
int dpcmp(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y;
    __unpack_d(&a0, &x);
    __unpack_d(&a1, &y);
    return __fpcmp_parts_d(&x, &y);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", litodp);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", dptoli);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", dptoul);
void __negdf2(long long a0) {
    struct { int a, b, c, pad; long long d; } s;
    long long t = a0;
    __unpack_d(&t, &s);
    s.b = (s.b == 0);
    __pack_d(&s);
}
int __make_dp(int a0, int a1, int a2, long long a3) {
    struct { int a, b, c, pad; long long d; } s;
    s.a = a0;
    s.b = a1;
    s.c = a2;
    s.d = a3;
    __pack_d(&s);
}
extern void __make_fp(int a0, int a1, int a2, int a3);

float dptofp(long a0) {
    struct { int f0; int f4; int f8; int fC; long long f10; } buf;
    long long m; int hi, t;
    __unpack_d(&a0, &buf);
    m = buf.f10;
    hi = (int)(m >> 30);
    t = hi | 1;
    if ((m & 0x3FFFFFFF) == 0) t = hi;
    __make_fp(buf.f0, buf.f4, buf.f8, t);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __pack_f);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", __unpack_f);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", func_0027DBA0);
extern int __pack_f(void *s);
extern void __unpack_f(void *in, void *out);
extern int func_0027DBA0();

int fpadd(float a0, float a1) {
    char buf[0x40];
    int ret;
    *(float *)(buf + 0x30) = a0;
    *(float *)(buf + 0x34) = a1;
    __unpack_f(buf + 0x30, buf);
    __unpack_f(buf + 0x34, buf + 0x10);
    ret = func_0027DBA0(buf, buf + 0x10, buf + 0x20);
    return __pack_f(ret);
}
int fpsub(float a0, float a1) {
    char buf[0x40];
    int ret;
    *(float *)(buf + 0x30) = a0;
    *(float *)(buf + 0x34) = a1;
    __unpack_f(buf + 0x30, buf);
    __unpack_f(buf + 0x34, buf + 0x10);
    *(int *)(buf + 0x14) ^= 1;
    ret = func_0027DBA0(buf, buf + 0x10, buf + 0x20);
    return __pack_f(ret);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", fpmul);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", fpdiv);
int __fpcmp_parts_f(PCmpV *a, PCmpV *b) {
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
int fpcmp(float a0, float a1) {
    char buf[0x30];
    *(float *)(buf + 0x20) = a0;
    *(float *)(buf + 0x24) = a1;
    __unpack_f(buf + 0x20, buf);
    __unpack_f(buf + 0x24, buf + 0x10);
    return __fpcmp_parts_f(buf, buf + 0x10);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", sitofp);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", fptosi);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_27B190", fptoui);
int __negsf2(float f12)
{
    int o[4];
    float in[4];
    in[0] = f12;
    __unpack_f(in, o);
    o[1] = (o[1] == 0);
    return __pack_f(o);
}
void __make_fp(int a0, int a1, int a2, int a3) {
    int buf[4];
    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = a3;
    __pack_f(buf);
}
int fptodp(float f12)
{
    int local0[4];
    float local1[4];
    long long a3_val;
    local1[0] = f12;
    __unpack_f(local1, local0);
    a3_val = (long long)(unsigned int)local0[3] << 32;
    return __make_dp(local0[0], local0[1], local0[2],
                         (long long)((unsigned long long)a3_val >> 2));
}
