/* libgcc.a member dp-bit.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

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

#define CLASS_SNAN 0
#define CLASS_QNAN 1
#define CLASS_ZERO 2
#define CLASS_NUMBER 3
#define CLASS_INFINITY 4

/* The double number in unpacked form.  FRAC_NBITS is 64 and NGARDS is 8, so the
   implicit one sits at bit 60 and the fraction is a 64-bit field at 0x10. */
typedef struct {
    unsigned int class;
    int sign;
    int normal_exp;
    int pad;
    unsigned long long fraction;
} fp_number_type_d;

static __inline__ int isnan_d(fp_number_type_d *x)
{
    return x->class == CLASS_SNAN || x->class == CLASS_QNAN;
}

static __inline__ int isinf_d(fp_number_type_d *x)
{
    return x->class == CLASS_INFINITY;
}

static __inline__ int iszero_d(fp_number_type_d *x)
{
    return x->class == CLASS_ZERO;
}

/* the quiet NaN this build hands back for inf - inf */
extern char D_736170[];

static __inline__ fp_number_type_d *nan_d(void)
{
    return (fp_number_type_d *)D_736170;
}

typedef union {
    struct {
        unsigned long long fraction : 52;
        unsigned long long exp : 11;
        unsigned long long sign : 1;
    } bits;

    long long value;
} FLO_union_type_d;

long long __pack_d(void *s)
{
    fp_number_type_d *src = s;
    FLO_union_type_d dst;
    unsigned long long fraction = src->fraction;
    int sign = src->sign;
    int exp = 0;

    if (isnan_d(src)) {
        exp = 0x7FF;
        fraction |= 0x8000000000000ULL;
    } else if (isinf_d(src)) {
        exp = 0x7FF;
        fraction = 0;
    } else if (iszero_d(src)) {
        exp = 0;
        fraction = 0;
    } else if (fraction == 0) {
        exp = 0;
    } else {
        if (src->normal_exp < -1022) {
            /* the exponent is too low for a normal number: the integer part
               goes to zero and the fraction keeps what bits survive */
            int shift = -1022 - src->normal_exp;
            if (shift > 56) {
                exp = 0;
                fraction = 0;
            } else {
                exp = 0;
                fraction >>= shift;
            }
            fraction >>= 8;
        } else if (src->normal_exp > 1023) {
            exp = 0x7FF;
            fraction = 0;
        } else {
            exp = src->normal_exp + 1023;
            /* halfway between two numbers: round to the one whose low bit
               is zero, otherwise add a one to the guards to round up */
            if ((fraction & 0xFF) == 0x80) {
                if (fraction & 0x100) {
                    fraction += 0x80;
                }
            } else {
                fraction += 0x7F;
            }
            if (fraction >= 0x2000000000000000ULL) {
                fraction >>= 1;
                exp += 1;
            }
            fraction >>= 8;
        }
    }
    dst.bits.fraction = fraction;
    dst.bits.exp = exp;
    dst.bits.sign = sign;
    return dst.value;
}

INCLUDE_ASM("asm/nonmatchings/sce/libgcc/dp-bit", __unpack_d);

fp_number_type_d *_fpadd_parts(fp_number_type_d *a, fp_number_type_d *b, fp_number_type_d *tmp)
{
    long long tfraction;
    int a_normal_exp;
    int b_normal_exp;
    unsigned long long a_fraction;
    unsigned long long b_fraction;
    int diff;

    if (isnan_d(a))
        return a;
    if (isnan_d(b))
        return b;
    if (isinf_d(a)) {
        /* adding infinities with opposite signs yields a NaN */
        if (isinf_d(b) && a->sign != b->sign)
            return nan_d();
        return a;
    }
    if (isinf_d(b))
        return b;
    if (iszero_d(b)) {
        if (iszero_d(a)) {
            *tmp = *a;
            tmp->sign = a->sign & b->sign;
            return tmp;
        }
        return a;
    }
    if (iszero_d(a))
        return b;

    a_normal_exp = a->normal_exp;
    b_normal_exp = b->normal_exp;
    a_fraction = a->fraction;
    b_fraction = b->fraction;

    diff = a_normal_exp - b_normal_exp;
    if (diff < 0)
        diff = -diff;
    if (diff < 64) {
        while (a_normal_exp > b_normal_exp) {
            b_normal_exp++;
            b_fraction = (b_fraction & 1) | (b_fraction >> 1);
        }
        while (b_normal_exp > a_normal_exp) {
            a_normal_exp++;
            a_fraction = (a_fraction & 1) | (a_fraction >> 1);
        }
    } else {
        if (a_normal_exp > b_normal_exp) {
            b_fraction = 0;
            b_normal_exp = a_normal_exp;
        } else {
            a_fraction = 0;
            a_normal_exp = b_normal_exp;
        }
    }

    if (a->sign != b->sign) {
        if (a->sign)
            tfraction = -a_fraction + b_fraction;
        else
            tfraction = a_fraction - b_fraction;

        if (tfraction >= 0) {
            tmp->sign = 0;
            tmp->normal_exp = a_normal_exp;
            tmp->fraction = tfraction;
        } else {
            tmp->sign = 1;
            tmp->normal_exp = a_normal_exp;
            tmp->fraction = -tfraction;
        }
        while (tmp->fraction < 0x1000000000000000ULL && tmp->fraction) {
            tmp->fraction <<= 1;
            tmp->normal_exp--;
        }
    } else {
        tmp->sign = a->sign;
        tmp->normal_exp = a_normal_exp;
        tmp->fraction = a_fraction + b_fraction;
    }
    tmp->class = CLASS_NUMBER;

    if (tmp->fraction >= 0x2000000000000000ULL) {
        tmp->fraction = (tmp->fraction & 1) | (tmp->fraction >> 1);
        tmp->normal_exp++;
    }
    return tmp;
}

extern long long __pack_d(void *s);
extern void __unpack_d(void *in, void *out);
extern fp_number_type_d *_fpadd_parts(fp_number_type_d *a, fp_number_type_d *b,
                                      fp_number_type_d *tmp);

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

extern long long __pack_d(void *s);

long long litodp(int arg_a)
{
    fp_number_type_d in;

    in.class = CLASS_NUMBER;
    in.sign = arg_a < 0;
    if (!arg_a) {
        in.class = CLASS_ZERO;
    } else {
        in.normal_exp = 60;
        if (in.sign) {
            /* there is no positive representation of the most negative int;
               the literal is the IEEE-754 double -2147483648.0 */
            if (arg_a == (-0x7FFFFFFF) - 1) {
                return 0xC1E0000000000000LL;
            }
            in.fraction = -arg_a;
        } else {
            in.fraction = arg_a;
        }
        while (in.fraction < 0x1000000000000000ULL) {
            in.fraction <<= 1;
            in.normal_exp--;
        }
    }
    return __pack_d(&in);
}

int dptoli(long a0)
{
    fp_number_type_d a;
    int tmp;

    __unpack_d(&a0, &a);

    if (iszero_d(&a)) {
        return 0;
    }
    if (isnan_d(&a)) {
        return 0;
    }
    if (isinf_d(&a)) {
        return a.sign ? (-0x7FFFFFFF) - 1 : 0x7FFFFFFF;
    }
    if (a.normal_exp < 0) {
        return 0;
    }
    if (a.normal_exp > 30) {
        return a.sign ? (-0x7FFFFFFF) - 1 : 0x7FFFFFFF;
    }
    tmp = a.fraction >> (60 - a.normal_exp);
    return a.sign ? -tmp : tmp;
}

unsigned int dptoul(long a0)
{
    fp_number_type_d a;

    __unpack_d(&a0, &a);

    if (iszero_d(&a)) {
        return 0;
    }
    if (isnan_d(&a)) {
        return 0;
    }
    if (a.sign) {
        return 0;
    }
    if (isinf_d(&a)) {
        return 0xFFFFFFFF;
    }
    if (a.normal_exp < 0) {
        return 0;
    }
    if (a.normal_exp > 31) {
        return 0xFFFFFFFF;
    }
    if (a.normal_exp > 60) {
        return a.fraction << (a.normal_exp - 60);
    }
    return a.fraction >> (60 - a.normal_exp);
}

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
