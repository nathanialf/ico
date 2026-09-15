/* libgcc.a member fp-bit.o.  MAIN.MAP member spans tile this run exactly and
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

extern void __unpack_d(void *in, void *out);
extern void __make_fp(int a0, int a1, int a2, int a3);

INCLUDE_ASM("asm/nonmatchings/sce/libgcc/fp-bit", __pack_f);
INCLUDE_ASM("asm/nonmatchings/sce/libgcc/fp-bit", __unpack_f);

extern int __pack_f(void *s);
extern void __unpack_f(void *in, void *out);

/* The single-float number in unpacked form.  FRAC_NBITS is 32, NGARDS is 7,
   so the implicit one sits at bit 30 and the overflow bit at bit 31.  The
   file static shares its name with the double build's global in dp-bit.o. */
#define CLASS_SNAN 0
#define CLASS_QNAN 1
#define CLASS_ZERO 2
#define CLASS_NUMBER 3
#define CLASS_INFINITY 4
#define IMPLICIT_1 0x40000000
#define IMPLICIT_2 0x80000000

typedef struct {
    unsigned int class;
    int sign;
    int normal_exp;
    unsigned int fraction;
} fp_number_type;

/* the quiet NaN this build hands back for inf - inf */
extern char D_736188[];

static __inline__ int isnan(fp_number_type *x)
{
    return x->class == CLASS_SNAN || x->class == CLASS_QNAN;
}

static __inline__ int isinf(fp_number_type *x)
{
    return x->class == CLASS_INFINITY;
}

static __inline__ int iszero(fp_number_type *x)
{
    return x->class == CLASS_ZERO;
}

static __inline__ fp_number_type *nan(void)
{
    return (fp_number_type *)D_736188;
}

static fp_number_type *_fpadd_parts(fp_number_type *a, fp_number_type *b, fp_number_type *tmp)
{
    int tfraction;
    int a_normal_exp;
    int b_normal_exp;
    unsigned int a_fraction;
    unsigned int b_fraction;
    int diff;

    if (isnan(a))
        return a;
    if (isnan(b))
        return b;
    if (isinf(a)) {
        /* adding infinities with opposite signs yields a NaN */
        if (isinf(b) && a->sign != b->sign)
            return nan();
        return a;
    }
    if (isinf(b))
        return b;
    if (iszero(b)) {
        if (iszero(a)) {
            *tmp = *a;
            tmp->sign = a->sign & b->sign;
            return tmp;
        }
        return a;
    }
    if (iszero(a))
        return b;

    a_normal_exp = a->normal_exp;
    b_normal_exp = b->normal_exp;
    a_fraction = a->fraction;
    b_fraction = b->fraction;

    diff = a_normal_exp - b_normal_exp;
    if (diff < 0)
        diff = -diff;
    if (diff < 32) {
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
        while (tmp->fraction < IMPLICIT_1 && tmp->fraction) {
            tmp->fraction <<= 1;
            tmp->normal_exp--;
        }
    } else {
        tmp->sign = a->sign;
        tmp->normal_exp = a_normal_exp;
        tmp->fraction = a_fraction + b_fraction;
    }
    tmp->class = CLASS_NUMBER;

    if (tmp->fraction >= IMPLICIT_2) {
        tmp->fraction = (tmp->fraction & 1) | (tmp->fraction >> 1);
        tmp->normal_exp++;
    }
    return tmp;
}

int fpadd(float a0, float a1)
{
    char buf[0x40];
    int ret;
    *(float *)(buf + 0x30) = a0;
    *(float *)(buf + 0x34) = a1;
    __unpack_f(buf + 0x30, buf);
    __unpack_f(buf + 0x34, buf + 0x10);
    ret = (int)_fpadd_parts((fp_number_type *)buf, (fp_number_type *)(buf + 0x10),
                            (fp_number_type *)(buf + 0x20));
    return __pack_f(ret);
}

int fpsub(float a0, float a1)
{
    char buf[0x40];
    int ret;
    *(float *)(buf + 0x30) = a0;
    *(float *)(buf + 0x34) = a1;
    __unpack_f(buf + 0x30, buf);
    __unpack_f(buf + 0x34, buf + 0x10);
    *(int *)(buf + 0x14) ^= 1;
    ret = (int)_fpadd_parts((fp_number_type *)buf, (fp_number_type *)(buf + 0x10),
                            (fp_number_type *)(buf + 0x20));
    return __pack_f(ret);
}

INCLUDE_ASM("asm/nonmatchings/sce/libgcc/fp-bit", fpmul);
INCLUDE_ASM("asm/nonmatchings/sce/libgcc/fp-bit", fpdiv);

int __fpcmp_parts_f(PCmpV *a, PCmpV *b)
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

int fpcmp(float a0, float a1)
{
    char buf[0x30];
    *(float *)(buf + 0x20) = a0;
    *(float *)(buf + 0x24) = a1;
    __unpack_f(buf + 0x20, buf);
    __unpack_f(buf + 0x24, buf + 0x10);
    return __fpcmp_parts_f(buf, buf + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/sce/libgcc/fp-bit", sitofp);
INCLUDE_ASM("asm/nonmatchings/sce/libgcc/fp-bit", fptosi);
INCLUDE_ASM("asm/nonmatchings/sce/libgcc/fp-bit", fptoui);

int __negsf2(float f12)
{
    int o[4];
    float in[4];
    in[0] = f12;
    __unpack_f(in, o);
    o[1] = (o[1] == 0);
    return __pack_f(o);
}

void __make_fp(int a0, int a1, int a2, int a3)
{
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
    return __make_dp(local0[0], local0[1], local0[2], (long long)((unsigned long long)a3_val >> 2));
}
