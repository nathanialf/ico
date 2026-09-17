/* libc.a member strtod.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);

/* newlib's mprec.h configuration for this build, spelled out in the member
   that uses it.  Evidence rung: the SRCFILE.TXT line map of _strtod_r picks
   the arm of every switch below (lines 273..278 absent and 276/277 present
   so VAX is off; 306..309 present so Inaccurate_Divide is off; 328 present
   so _HAVE_STDC is on and the overflow value is HUGE_VAL; 443..448 absent
   and 450..454 present so Sudden_Underflow is off; 546 present so
   ROUND_BIASED is off; 592..605 absent so Check_FLT_ROUNDS is off and
   FLT_ROUNDS folds to 1; 362 and 625 present with their _DOUBLE_IS_32BITS
   arms absent, so doubles are 64-bit IEEE little-endian). */
typedef unsigned int ULong;

#define Long int
#define _CONST const
#define DBL_DIG 15
#define DBL_MAX_EXP 1024
#define DBL_MAX_10_EXP 308
#define FLT_RADIX 2
#define FLT_ROUNDS 1
#define ERANGE 34

struct _reent {
    int _errno; /* 0x0 */
};

struct _Bigint {
    struct _Bigint *_next; /* 0x00 */
    int _k;                /* 0x04 */
    int _maxwds;           /* 0x08 */
    int _sign;             /* 0x0C */
    int _wds;              /* 0x10 */
    ULong _x[1];           /* 0x14 */
};

typedef struct _Bigint _Bigint;

union double_union {
    double d;
    ULong i[2];
};

/* IEEE_8087 (little endian): word0 is the high half. */
#define word0(x) (x.i[1])
#define word1(x) (x.i[0])
#define Exp_shift 20
#define Exp_shift1 20
#define Exp_msk1 ((ULong)0x100000L)
#define Exp_msk11 ((ULong)0x100000L)
#define Exp_mask ((ULong)0x7ff00000L)
#define P 53
#define Bias 1023
#define IEEE_Arith
#define Emin (-1022)
#define Exp_1 ((ULong)0x3ff00000L)
#define Exp_11 ((ULong)0x3ff00000L)
#define Ebits 11
#define Frac_mask ((ULong)0xfffffL)
#define Frac_mask1 ((ULong)0xfffffL)
#define Ten_pmax 22
#define Bletch 0x10
#define Bndry_mask ((ULong)0xfffffL)
#define Bndry_mask1 ((ULong)0xfffffL)
#define LSB 1
#define Sign_bit ((ULong)0x80000000L)
#define Log2P 1
#define Tiny0 0
#define Tiny1 1
#define Quick_max 14
#define Int_max 14
#define rounded_product(a, b) a *= b
#define rounded_quotient(a, b) a /= b
#define Big0 (Frac_mask1 | Exp_msk1 * (DBL_MAX_EXP + Bias - 1))
#define Big1 ((ULong)0xffffffffL)
#define n_bigtens 5
#define Bcopy(x, y)                                                                                \
    memcpy((char *)&x->_sign, (char *)&y->_sign, y->_wds * sizeof(Long) + 2 * sizeof(int))

/* math.h's HUGE_VAL, the shared +infinity constant of s_infconst.o. */
union __dmath {
    ULong i[2];
    double d;
};

extern const union __dmath __infinity[1];

#define HUGE_VAL (__infinity[0].d)

/* mprec.o's shared power-of-ten tables: tens[0..24], bigtens[0..4] and
   tinytens[0..4] (evidence rung: ROM bytes, the three runs are contiguous
   at 0x006388A0, 0x00638968 and 0x00638990). */
extern const double D_006388A0[];
extern const double D_00638968[];
extern const double D_00638990[];

#define tens D_006388A0
#define bigtens D_00638968
#define tinytens D_00638990

extern _Bigint *_Balloc(struct _reent *p, int k);
extern void _Bfree(struct _reent *p, _Bigint *v);
extern _Bigint *_s2b(struct _reent *p, const char *s, int nd0, int nd, ULong y9);
extern _Bigint *_i2b(struct _reent *p, int i);
extern _Bigint *_multiply(struct _reent *p, _Bigint *a, _Bigint *b);
extern _Bigint *_pow5mult(struct _reent *p, _Bigint *b, int k);
extern _Bigint *_lshift(struct _reent *p, _Bigint *b, int k);
extern _Bigint *__mdiff(struct _reent *p, _Bigint *a, _Bigint *b);
extern int __mcmp(_Bigint *a, _Bigint *b);
extern double _ulp(double x);
extern _Bigint *_d2b(struct _reent *p, double d, int *e, int *bits);
extern double _ratio(_Bigint *a, _Bigint *b);

#define Balloc _Balloc
#define Bfree _Bfree
#define s2b _s2b
#define i2b _i2b
#define mult _multiply
#define pow5mult _pow5mult
#define lshift _lshift
#define cmp __mcmp
#define diff __mdiff
#define ulp _ulp
#define d2b _d2b
#define ratio _ratio

double _strtod_r(struct _reent *ptr, const char *s00, char **se)
{
    int bb2, bb5, bbe, bd2, bd5, bbbits, bs2, c, dsign, e1, esign, i, j, k, nd, nd0, nf, nz, nz0,
        sign;
    long e;
    _CONST char *s, *s0, *s1;
    double aadj, aadj1, adj;
    long L;
    unsigned long z;
    ULong y;
    union double_union rv, rv0;

    _Bigint *bb, *bb1, *bd, *bd0, *bs, *delta;
    sign = nz0 = nz = 0;
    rv.d = 0.;
    for (s = s00;; s++)
        switch (*s) {
        case '-':
            sign = 1;
            /* no break */
        case '+':
            if (*++s)
                goto break2;
            /* no break */
        case 0:
            s = s00;
            goto ret;
        case '\t':
        case '\n':
        case '\v':
        case '\f':
        case '\r':
        case ' ':
            continue;
        default:
            goto break2;
        }
break2:
    if (*s == '0') {
        nz0 = 1;
        while (*++s == '0')
            ;
        if (!*s)
            goto ret;
    }
    s0 = s;
    y = z = 0;
    for (nd = nf = 0; (c = *s) >= '0' && c <= '9'; nd++, s++)
        if (nd < 9)
            y = 10 * y + c - '0';
        else if (nd < 16)
            z = 10 * z + c - '0';
    nd0 = nd;
    if (c == '.') {
        c = *++s;
        if (!nd) {
            for (; c == '0'; c = *++s)
                nz++;
            if (c > '0' && c <= '9') {
                s0 = s;
                nf += nz;
                nz = 0;
                goto have_dig;
            }
            goto dig_done;
        }
        for (; c >= '0' && c <= '9'; c = *++s) {
        have_dig:
            nz++;
            if (c -= '0') {
                nf += nz;
                for (i = 1; i < nz; i++)
                    if (nd++ < 9)
                        y *= 10;
                    else if (nd <= DBL_DIG + 1)
                        z *= 10;
                if (nd++ < 9)
                    y = 10 * y + c;
                else if (nd <= DBL_DIG + 1)
                    z = 10 * z + c;
                nz = 0;
            }
        }
    }
dig_done:
    e = 0;
    if (c == 'e' || c == 'E') {
        if (!nd && !nz && !nz0) {
            s = s00;
            goto ret;
        }
        s00 = s;
        esign = 0;
        switch (c = *++s) {
        case '-':
            esign = 1;
        case '+':
            c = *++s;
        }
        if (c >= '0' && c <= '9') {
            while (c == '0')
                c = *++s;
            if (c > '0' && c <= '9') {
                e = c - '0';
                s1 = s;
                while ((c = *++s) >= '0' && c <= '9')
                    e = 10 * e + c - '0';
                if (s - s1 > 8)
                    /* Avoid confusion from exponents
                     * so large that e might overflow.
                     */
                    e = 9999999L;
                if (esign)
                    e = -e;
            } else
                e = 0;
        } else
            s = s00;
    }
    if (!nd) {
        if (!nz && !nz0)
            s = s00;
        goto ret;
    }
    e1 = e -= nf;

    /* Now we have nd0 digits, starting at s0, followed by a
     * decimal point, followed by nd-nd0 digits.  The number we're
     * after is the integer represented by those digits times
     * 10**e */

    if (!nd0)
        nd0 = nd;
    k = nd < DBL_DIG + 1 ? nd : DBL_DIG + 1;
    rv.d = y;
    if (k > 9)
        rv.d = tens[k - 9] * rv.d + z;
    bd0 = 0;
    if (nd <= DBL_DIG && FLT_ROUNDS == 1) {
        if (!e)
            goto ret;
        if (e > 0) {
            if (e <= Ten_pmax) {
                /* rv.d = */ rounded_product(rv.d, tens[e]);
                goto ret;
            }
            i = DBL_DIG - nd;
            if (e <= Ten_pmax + i) {
                /* A fancier test would sometimes let us do
                 * this for larger i values.
                 */
                e -= i;
                rv.d *= tens[i];
                /* rv.d = */ rounded_product(rv.d, tens[e]);
                goto ret;
            }
        } else if (e >= -Ten_pmax) {
            /* rv.d = */ rounded_quotient(rv.d, tens[-e]);
            goto ret;
        }
    }
    e1 += nd - k;

    /* Get starting approximation = rv.d * 10**e1 */

    if (e1 > 0) {
        if (i = e1 & 15)
            rv.d *= tens[i];
        if (e1 &= ~15) {
            if (e1 > DBL_MAX_10_EXP) {
            ovfl:
                ptr->_errno = ERANGE;
                rv.d = HUGE_VAL;
                if (bd0)
                    goto retfree;
                goto ret;
            }
            if (e1 >>= 4) {
                for (j = 0; e1 > 1; j++, e1 >>= 1)
                    if (e1 & 1)
                        rv.d *= bigtens[j];
                /* The last multiplication could overflow. */
                word0(rv) -= P * Exp_msk1;
                rv.d *= bigtens[j];
                if ((z = word0(rv) & Exp_mask) > Exp_msk1 * (DBL_MAX_EXP + Bias - P))
                    goto ovfl;
                if (z > Exp_msk1 * (DBL_MAX_EXP + Bias - 1 - P)) {
                    /* set to largest number */
                    /* (Can't trust DBL_MAX) */
                    word0(rv) = Big0;
                    word1(rv) = Big1;
                } else
                    word0(rv) += P * Exp_msk1;
            }
        }
    } else if (e1 < 0) {
        e1 = -e1;
        if (i = e1 & 15)
            rv.d /= tens[i];
        if (e1 &= ~15) {
            e1 >>= 4;
            if (e1 >= 1 << n_bigtens)
                goto undfl;
            for (j = 0; e1 > 1; j++, e1 >>= 1)
                if (e1 & 1)
                    rv.d *= tinytens[j];
            /* The last multiplication could underflow. */
            rv0.d = rv.d;
            rv.d *= tinytens[j];
            if (!rv.d) {
                rv.d = 2. * rv0.d;
                rv.d *= tinytens[j];
                if (!rv.d) {
                undfl:
                    rv.d = 0.;
                    ptr->_errno = ERANGE;
                    if (bd0)
                        goto retfree;
                    goto ret;
                }
                word0(rv) = Tiny0;
                word1(rv) = Tiny1;
                /* The refinement below will clean
                 * this approximation up.
                 */
            }
        }
    }

    /* Now the hard part -- adjusting rv to the correct value.*/

    /* Put digits into bd: true value = bd * 10^e */

    bd0 = s2b(ptr, s0, nd0, nd, y);

    for (;;) {
        bd = Balloc(ptr, bd0->_k);
        Bcopy(bd, bd0);
        bb = d2b(ptr, rv.d, &bbe, &bbbits); /* rv.d = bb * 2^bbe */
        bs = i2b(ptr, 1);

        if (e >= 0) {
            bb2 = bb5 = 0;
            bd2 = bd5 = e;
        } else {
            bb2 = bb5 = -e;
            bd2 = bd5 = 0;
        }
        if (bbe >= 0)
            bb2 += bbe;
        else
            bd2 -= bbe;
        bs2 = bb2;
        i = bbe + bbbits - 1; /* logb(rv.d) */
        if (i < Emin)         /* denormal */
            j = bbe + (P - Emin);
        else
            j = P + 1 - bbbits;
        bb2 += j;
        bd2 += j;
        i = bb2 < bd2 ? bb2 : bd2;
        if (i > bs2)
            i = bs2;
        if (i > 0) {
            bb2 -= i;
            bd2 -= i;
            bs2 -= i;
        }
        if (bb5 > 0) {
            bs = pow5mult(ptr, bs, bb5);
            bb1 = mult(ptr, bs, bb);
            Bfree(ptr, bb);
            bb = bb1;
        }
        if (bb2 > 0)
            bb = lshift(ptr, bb, bb2);
        if (bd5 > 0)
            bd = pow5mult(ptr, bd, bd5);
        if (bd2 > 0)
            bd = lshift(ptr, bd, bd2);
        if (bs2 > 0)
            bs = lshift(ptr, bs, bs2);
        delta = diff(ptr, bb, bd);
        dsign = delta->_sign;
        delta->_sign = 0;
        i = cmp(delta, bs);
        if (i < 0) {
            /* Error is less than half an ulp -- check for
             * special case of mantissa a power of two.
             */
            if (dsign || word1(rv) || word0(rv) & Bndry_mask)
                break;
            delta = lshift(ptr, delta, Log2P);
            if (cmp(delta, bs) > 0)
                goto drop_down;
            break;
        }
        if (i == 0) {
            /* exactly half-way between */
            if (dsign) {
                if ((word0(rv) & Bndry_mask1) == Bndry_mask1 && word1(rv) == 0xffffffff) {
                    /*boundary case -- increment exponent*/
                    word0(rv) = (word0(rv) & Exp_mask) + Exp_msk1;
                    word1(rv) = 0;
                    break;
                }
            } else if (!(word0(rv) & Bndry_mask) && !word1(rv)) {
            drop_down:
                /* boundary case -- decrement exponent */
                L = (word0(rv) & Exp_mask) - Exp_msk1;
                word0(rv) = L | Bndry_mask1;
                word1(rv) = 0xffffffff;
                break;
            }
            if (!(word1(rv) & LSB))
                break;
            if (dsign)
                rv.d += ulp(rv.d);
            else {
                rv.d -= ulp(rv.d);
                if (!rv.d)
                    goto undfl;
            }
            break;
        }
        if ((aadj = ratio(delta, bs)) <= 2.) {
            if (dsign)
                aadj = aadj1 = 1.;
            else if (word1(rv) || word0(rv) & Bndry_mask) {
                if (word1(rv) == Tiny1 && !word0(rv))
                    goto undfl;
                aadj = 1.;
                aadj1 = -1.;
            } else {
                /* special case -- power of FLT_RADIX to be */
                /* rounded down... */

                if (aadj < 2. / FLT_RADIX)
                    aadj = 1. / FLT_RADIX;
                else
                    aadj *= 0.5;
                aadj1 = -aadj;
            }
        } else {
            aadj *= 0.5;
            aadj1 = dsign ? aadj : -aadj;
            if (FLT_ROUNDS == 0)
                aadj1 += 0.5;
        }
        y = word0(rv) & Exp_mask;

        /* Check for overflow */

        if (y == Exp_msk1 * (DBL_MAX_EXP + Bias - 1)) {
            rv0.d = rv.d;
            word0(rv) -= P * Exp_msk1;
            adj = aadj1 * ulp(rv.d);
            rv.d += adj;
            if ((word0(rv) & Exp_mask) >= Exp_msk1 * (DBL_MAX_EXP + Bias - P)) {
                if (word0(rv0) == Big0 && word1(rv0) == Big1)
                    goto ovfl;
                word0(rv) = Big0;
                word1(rv) = Big1;
                goto cont;
            } else
                word0(rv) += P * Exp_msk1;
        } else {
            /* Compute adj so that the IEEE rounding rules will
             * correctly round rv.d + adj in some half-way cases.
             * If rv.d * ulp(rv.d) is denormalized (i.e.,
             * y <= (P-1)*Exp_msk1), we must adjust aadj to avoid
             * trouble from bits lost to denormalization;
             * example: 1.2e-307 .
             */
            if (y <= (P - 1) * Exp_msk1 && aadj >= 1.) {
                aadj1 = (double)(int)(aadj + 0.5);
                if (!dsign)
                    aadj1 = -aadj1;
            }
            adj = aadj1 * ulp(rv.d);
            rv.d += adj;
        }
        z = word0(rv) & Exp_mask;
        if (y == z) {
            /* Can we stop now? */
            L = aadj;
            aadj -= L;
            /* The tolerances below are conservative. */
            if (dsign || word1(rv) || word0(rv) & Bndry_mask) {
                if (aadj < .4999999 || aadj > .5000001)
                    break;
            } else if (aadj < .4999999 / FLT_RADIX)
                break;
        }
    cont:
        Bfree(ptr, bb);
        Bfree(ptr, bd);
        Bfree(ptr, bs);
        Bfree(ptr, delta);
    }
retfree:
    Bfree(ptr, bb);
    Bfree(ptr, bd);
    Bfree(ptr, bs);
    Bfree(ptr, bd0);
    Bfree(ptr, delta);
ret:
    if (se)
        *se = (char *)s;
    return sign ? -rv.d : rv.d;
}

double strtod(const char *s00, char **se)
{
    return _strtod_r((struct _reent *)D_0054CEAC[0], s00, se);
}

float strtodf(const char *s00, char **se)
{
    return strtod(s00, se);
}
